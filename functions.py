
from enum import StrEnum

import numpy as np

PHI = (1 + 5 ** 0.5) / 2

class FunctionName(StrEnum):
	CONSTANT = 'O(1) (constant)'
	LOGARITHMIC = 'O(log n) (logarithmic)'
	LINEAR = 'O(n) (linear)'
	LOGLINEAR = 'O(n log n) (loglinear)'
	QUADRATIC = 'O(n^2) (quadratic)'
	CUBIC = 'O(n^3) (cubic)'
	EXPONENTIAL_PHI = 'O(phi^n) (exponential)'
	EXPONENTIAL_2 = 'O(2^n) (exponential)'

# Note: Functions must be ordered from
#       slowest-growing to fastest-growing
common_functions = [
	{
		'name': FunctionName.CONSTANT,
		'fn': lambda x: x * 0,
	},
	{
		'name': FunctionName.LOGARITHMIC,
		'fn': lambda x: np.log2(x),
	},
	{
		'name': FunctionName.LINEAR,
		'fn': lambda x: x,
	},
	{
		'name': FunctionName.LOGLINEAR,
		'fn': lambda x: x * np.log2(x),
	},
	{
		'name': FunctionName.QUADRATIC,
		'fn': lambda x: x * x,
	},
	{
		'name': FunctionName.CUBIC,
		'fn': lambda x: x * x * x,
	},
	{
		'name': FunctionName.EXPONENTIAL_PHI,
		'fn': lambda x: PHI ** x,
	},
	{
		'name': FunctionName.EXPONENTIAL_2,
		'fn': lambda x: 2 ** x,
	},
]

