#!/usr/bin/env python3

# Time complexity analyser

import argparse
import numpy as np
import os
import re
from sklearn import linear_model
import subprocess
import sys
import tempfile

MIN_INPUT_SIZES = 4

def main():
	args = parse_arguments()

	command_prefix = args.command
	function_name = args.function_name
	input_sizes = args.input_sizes

	op_counts = collect_op_counts(command_prefix, function_name, input_sizes)

	most_likely_complexity = analyse_complexity(input_sizes, op_counts)

########################################################################

def parse_arguments():
	parser = argparse.ArgumentParser(
		description="Analyse the time complexity of a C function"
	)

	parser.add_argument('command')
	parser.add_argument('function_name')
	parser.add_argument('input_sizes', nargs='+', type=int)

	args = parser.parse_args()
	check_arguments(args)
	return args

def check_arguments(args):
	if len(args.input_sizes) < MIN_INPUT_SIZES:
		print(f'error: at least {MIN_INPUT_SIZES} input sizes are required',
		      file=sys.stderr)
		sys.exit(1)

########################################################################

def collect_op_counts(command_prefix, function_name, input_sizes):
	op_counts = []

	with tempfile.NamedTemporaryFile() as fp:
		for input_size in input_sizes:
			command = f'{command_prefix} {input_size}'
			op_count = get_op_count(command, function_name, fp.name)

			op_counts.append(op_count)

	return op_counts

def get_op_count(command, function_name, temp_file_name):
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
			timeout=5,
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

def analyse_complexity(input_sizes, op_counts):
	print(input_sizes)
	print(op_counts)

	X = np.array(input_sizes).reshape(-1, 1)
	y = np.array(op_counts)

	log_X = np.log2(X)
	X_log_X = X * np.log2(X)
	X_squared = X * X
	X_cubed = X * X * X
	exp_theta_X = ((1 + 5 ** 0.5) / 2) ** X
	exp_2_X = 2 ** X

	# O(1)
	# y = a
	reg1 = linear_model.LinearRegression(positive=True)
	reg1.fit(X * 0, y)
	print(reg1.coef_)
	print(reg1.intercept_)

	# O(log n)
	# y = a + b log x
	reg2 = linear_model.LinearRegression(positive=True)
	reg2.fit(log_X, y)
	print(reg2.coef_)
	print(reg2.intercept_)

	# O(n)
	# y = a + b log x + cx
	reg3 = linear_model.LinearRegression(positive=True)
	reg3.fit(np.concatenate((log_X, X), axis=1), y)
	print(reg3.coef_)
	print(reg3.intercept_)

	# O(n log n)
	# y = a + b log x + cx + dx log x
	reg5 = linear_model.LinearRegression(positive=True)
	reg5.fit(np.concatenate((log_X, X, X_log_X), axis=1), y)
	print(reg5.coef_)
	print(reg5.intercept_)

	# O(n^2)
	# y = a + b log x + cx + dx log x + ex^2
	reg6 = linear_model.LinearRegression(positive=True)
	reg6.fit(np.concatenate((log_X, X, X_log_X, X_squared), axis=1), y)
	print(reg6.coef_)
	print(reg6.intercept_)

	# O(n^(golden ratio))
	# y = a + b log x + cx + dx log x + ex^2 + f(golden ratio)^x
	reg7 = linear_model.LinearRegression(positive=True)
	reg7.fit(np.concatenate((log_X, X, X_log_X, X_squared, exp_theta_X), axis=1), y)
	print(reg7.coef_)
	print(reg7.intercept_)

########################################################################

if __name__ == '__main__':
	main()



































