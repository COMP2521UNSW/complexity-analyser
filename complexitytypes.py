# Complexity Type Enums
from enum import StrEnum

class ComplexityType(StrEnum):
    CONSTANT = "O(1) (constant)"
    LINEAR = "O(n) (linear)"
    LOGARITHMIC = "O(log(n)) (logarithmic)"
    LOGLINEAR = "O(nlog(n)) (loglinear)"
    QUADRATIC = "O(n^2) (quadratic)"
    CUBIC = "O(n^3) (cubic)"
    EXPONENTIAL = "O(2^n) (exponential)"