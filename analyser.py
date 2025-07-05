#!/usr/bin/env python3

# Time complexity analyser

import argparse
import logging
import os
import re
import subprocess
import sys
import tempfile

import numpy as np
from sklearn import linear_model

from functions import common_functions

MIN_INPUT_SIZES = 5
DEFAULT_TIMEOUT = 5

class Model:
	name: str
	model: linear_model.LinearRegression
	score: float = None

	def __init__(self, name):
		self.name = name
		self.model = linear_model.LinearRegression(positive=True)

	def fit_and_score(self, X, y):
		X_train, X_test, y_train, y_test = self.train_test_split(X, y)

		try:
			self.model.fit(X_train, y_train)
			self.score = self.model.score(X_test, y_test)

		except ValueError as e:
			self.score = float('-inf')

		return self.score		

	def train_test_split(self, X, y):
		n = np.size(y)
		split_idx = n // 2
		return X[:split_idx], X[split_idx:], y[:split_idx], y[split_idx:]

	def log(self):
		logging.info(f'{self.name}')
		logging.info(f'Coefficients: {self.model.coef_}')
		logging.info(f'Intercept: {self.model.intercept_}')
		logging.info(f'Score: {self.score}')
		logging.info(f'')

########################################################################

def main():
	args = parse_arguments()

	if args.verbose:
		logging.basicConfig(format='%(message)s', level=logging.INFO)

	command_prefix = args.command
	function_name = args.function_name
	input_sizes = args.input_size
	timeout = args.timeout

	complexity = analyse(command_prefix, function_name, input_sizes, timeout)

	print(f'Best-fitting time complexity: {complexity}')

########################################################################

def parse_arguments():
	parser = argparse.ArgumentParser(
		description="Analyse the time complexity of a C function"
	)

	parser.add_argument('command')
	parser.add_argument('function_name')
	parser.add_argument('input_size', nargs='+', type=int)
	parser.add_argument('-t', '--timeout', default=DEFAULT_TIMEOUT, type=int,
			help='maximum allowed execution time for each run of the command')
	parser.add_argument('-v', '--verbose', action='store_true',
			help='display instruction counts and fitted models')

	args = parser.parse_args()
	check_arguments(args)
	return args

def check_arguments(args):
	args.input_size = sorted(set(args.input_size))
	if len(args.input_size) < MIN_INPUT_SIZES:
		print(f'error: at least {MIN_INPUT_SIZES} unique input sizes are '
		      f'required', file=sys.stderr)
		sys.exit(1)

########################################################################

def analyse(command_prefix, function_name, input_sizes,
            timeout=DEFAULT_TIMEOUT):
	op_counts = collect_op_counts(command_prefix, function_name, input_sizes,
	                              timeout)

	logging.info(f'Input sizes: {input_sizes}')
	logging.info(f'Instruction counts: {op_counts}')
	logging.info(f'')

	best_model = analyse_data(input_sizes, op_counts)
	return best_model.name

###############
# Collect data

def collect_op_counts(command_prefix, function_name, input_sizes, timeout):
	op_counts = []

	with tempfile.NamedTemporaryFile() as fp:
		for input_size in input_sizes:
			command = f'{command_prefix} {input_size}'
			op_count = get_op_count(command, function_name, timeout, fp.name)

			op_counts.append(op_count)

	return op_counts

def get_op_count(command, function_name, timeout, temp_file_name):
	log_file = temp_file_name

	try:
		valgrind_cmd = (
			f'valgrind --tool=callgrind --log-file={log_file} '
			f'--callgrind-out-file=/dev/null --toggle-collect={function_name} '
			f'{command} > /dev/null'
		)
		process = subprocess.run(
			valgrind_cmd,
			shell=True,
			timeout=timeout,
			check=True,
		)
	except subprocess.TimeoutExpired as e:
		print(f'error: command timed out')
		sys.exit(1) # TODO: handle more gracefully
	except subprocess.CalledProcessError as e:
		print(f'error: command exited with code {e.returncode}')
		sys.exit(1) # TODO: handle more gracefully

	try:
		with open(log_file) as f:
			for line in f:
				if re.match('==[0-9]+== *Collected *: *', line):
					return int(re.search('[0-9]+$', line).group(0))

		print(f'error: could not find line containing instruction count')
		sys.exit(1) # TODO: handle more gracefully
	except Exception as e:
		print(f'error: an error occurred while reading valgrind log file: {e}')
		sys.exit(1) # TODO: handle more gracefully

###############
# Analyse data

def analyse_data(input_sizes, op_counts):
	x = np.array(input_sizes).reshape(-1, 1)
	y = np.array(op_counts)

	models = create_models(common_functions, x, y)

	best_model = choose_best_model(models)

	return best_model

def create_models(functions, x, y):
	models = []

	X_cols = []
	for function in functions:
		X_cols.append(function['fn'](x))

		model = Model(function['name'])
		model.fit_and_score(np.concatenate(X_cols, axis=1), y)
		models.append(model)

	return models

def choose_best_model(models):
	best_score = float('-inf')
	best_model = None

	for model in models:
		model.log()

		if model.score > best_score + 0.01:
			best_score = model.score
			best_model = model

	return best_model

########################################################################

if __name__ == '__main__':
	main()

