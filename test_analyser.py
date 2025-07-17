
import unittest

from analyser import analyse
from functions import FunctionName

########################################################################

class TestSuite(unittest.TestCase):
	def run_test(self, program_name, input_sizes):
		program_path = f'test_programs/bin/{self.subdir_name}/{program_name}'
		# the function name is the same as the program name
		function_name = program_name
		complexity = analyse(program_path, function_name, input_sizes)
		self.assertEqual(complexity, self.expected_complexity)

########################################################################

class TestConstantComplexity(TestSuite):
	subdir_name = 'constant'
	expected_complexity = FunctionName.CONSTANT

	def test_listPrepend(self):
		self.run_test('listPrepend', [10, 20, 30, 40, 50, 60, 70, 80])

class TestLogarithmicComplexity(TestSuite):
	subdir_name = 'logarithmic'
	expected_complexity = FunctionName.LOGARITHMIC

	def test_binarySearch(self):
		self.run_test('binarySearch', [10, 20, 30, 40, 50, 60, 70, 80])

	def test_numOneBits(self):
		self.run_test('numOneBits', [10, 20, 30, 40, 50, 60, 70, 80])

class TestLinearComplexity(TestSuite):
	subdir_name = 'linear'
	expected_complexity = FunctionName.LINEAR

	def test_simpleLoop(self):
		self.run_test('simpleLoop', [10, 20, 30, 40, 50, 60, 70, 80])

	def test_dynamicArray(self):
		self.run_test('dynamicArray', [10, 20, 30, 40, 50, 60, 70, 80])
		self.run_test('dynamicArray', [20, 40, 60, 80, 100, 120, 140, 160])

	def test_heapify(self):
		self.run_test('heapify', [10, 20, 30, 40, 50, 60, 70, 80])
		self.run_test('heapify', [20, 40, 60, 80, 100, 120, 140, 160])

	def test_disguiseAttempt(self):
		self.run_test('disguiseAttempt', [10, 20, 30, 40, 50, 60, 70, 80])

class TestLoglinearComplexity(TestSuite):
	subdir_name = 'loglinear'
	expected_complexity = FunctionName.LOGLINEAR

	def test_mergeSort(self):
		self.run_test('mergeSort', [10, 20, 30, 40, 50, 60, 70, 80])

	def test_quickSort(self):
		self.run_test('quickSort', [10, 20, 30, 40, 50, 60, 70, 80])

class TestQuadraticComplexity(TestSuite):
	subdir_name = 'quadratic'
	expected_complexity = FunctionName.QUADRATIC

	def test_doubleNestedLoop(self):
		self.run_test('doubleNestedLoop', [10, 20, 30, 40, 50, 60, 70, 80])

	def test_selectionSort(self):
		self.run_test('selectionSort', [10, 20, 30, 40, 50, 60, 70, 80])

	def test_twoSum(self):
		self.run_test('twoSum', [10, 20, 30, 40, 50, 60, 70, 80])

	def test_disguiseAttempt(self):
		self.run_test('disguiseAttempt', [10, 20, 30, 40, 50, 60, 70, 80])

class TestCubicComplexity(TestSuite):
	subdir_name = 'cubic'
	expected_complexity = FunctionName.CUBIC

	def test_tripleNestedLoop(self):
		self.run_test('tripleNestedLoop', [10, 20, 30, 40, 50, 60, 70, 80])

class TestExponentialComplexity(TestSuite):
	subdir_name = 'exponential'

	def test_slowFibonacci(self):
		self.expected_complexity = FunctionName.EXPONENTIAL_PHI
		self.run_test('slowFibonacci', [5, 6, 7, 8, 9, 10, 11, 12])

	def test_subsetSum(self):
		self.expected_complexity = FunctionName.EXPONENTIAL_2
		self.run_test('subsetSum', [5, 6, 7, 8, 9, 10, 11, 12])

########################################################################

if __name__ == '__main__':
	unittest.main()

