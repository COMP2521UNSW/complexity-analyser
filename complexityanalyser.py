# Complexity Analyser Program
# By Kevin Luxa, Ravindu Abeykoon Herath, COMP2521 25T2
# Makes use of callgrind
import sys
import os
import subprocess
import numpy as np
# The below import is used to remove the indenting from the multi-line help message string.
import textwrap
# Enum import
from complexitytypes import ComplexityType

def print_result_message(complexity_type: str, function: str, program: str) -> None:
    print(f"The function {function} of {program} is {complexity_type}")
    sys.exit(0)

def print_error_msg(error: str) -> None:
    print(f"ERROR: {error}")
    print("Usage: complexity-analyser.py <program-name> <function-name> [--c <start> <end> <step> | --s <size1> <size2> ...]")
    sys.exit(1)
    
def print_help_msg() -> None:
    print(textwrap.dedent("""\
    Usage: complexity-analyser.py <program-name> <function-name> [--r|--s] <start> <end> <step>
        complexity-analyser.py <program-name> <function-name> [--r|--s] <input_size_1> <input_size_2> ...

    Arguments:
    <program-name>       Path to the executable program
    <function-name>      Name of the function to analyse
    --c, --s             Mode of input: range (--r) or specific sizes (--s)
    <start> <end> <step> Input size range (used with --r)
    <input_size_*>       Explicit input sizes (used with --s)

    Examples:
    complexity-analyser.py ./sort.exe quicksort --r 10 100 10
    complexity-analyser.py ./sort.exe mergesort --s 10 20 40 80
    """))

def main() -> None:
    # Check if the user asks for help, printing this and exiting.
    if len(sys.argv) == 2 and sys.argv[1] == "--help":
        print_help_msg()
        sys.exit(0)
    
    # Parse relevant information from arguments.
    try:
        program_name, function_name, flag = sys.argv[1:4]
        match flag:
            case "--r":
                start, stop, step = [int(x) for x in sys.argv[4:7]]
                input_sizes = [x for x in range(start, stop, step)]
            case "--s":
                input_sizes = [int(x) for x in sys.argv[4:]]
            case _:
                print_error_msg("Invalid flag used! Use --r for a range of values, --s for specific values.")
    except ValueError:
        print_error_msg("Input size provided is invalid. Ensure input sizes provided are integers!")
    
    # Ensure that the program exists, and that we have a valid amount of inputs
    # NOTE: For now, I make the assumption that we'd at least three to make an estimate, but ideally we change this
    MIN_INPUTS = 3
    num_inputs = len(input_sizes)
    if not os.path.exists(program_name):
        print_error_msg("The given file does not exist!")
    elif not os.access(program_name, mode=os.X_OK):
        print_error_msg("The given file is not executable!")
    elif num_inputs < MIN_INPUTS:
        print_error_msg(f"Not enough inputs! There is a minimum requirement of {MIN_INPUTS} inputs.")
    
    # Now, for each of the input sizes, run the opcount program, collect the number of each operations performed in
    # each. Ideally, this is a sorted map, but I think we can use a tuple? We'll see, I think we can zip it together
    # and go from there.
    output_sizes = []
    for size in input_sizes:
        try:
            result = subprocess.run(
            ["./opcount.sh", "--fn", function_name, program_name, str(size)],
            stdout=subprocess.PIPE,
            check=True,
            text=True)
        except subprocess.CalledProcessError as e:
            print_error_msg(e.returncode, e.output)
        
        output_sizes.append(int(result.stdout.strip()))
    
    # Trivial Case: If the output sizes are all the same, the function is constant.
    if len(set(output_sizes)) == 1:
        print_result_message(ComplexityType.CONSTANT, function_name, program_name)
    
    # Data Processing stage
    # Make use of Numpy regression fitting in order to determine the closest model.
    # However, we need to make the relationships polynomial to do so - the data is transformed in some cases.
    x = np.array(input_sizes)
    y = np.array(output_sizes)
    
    # Linear
    # Definition: y = a*x + b
    p_linear = np.polyfit(x, y, 1)
    
    # Logarithmic
    # Definition: y = a*log(x) + b
    x_log = np.log2(x)
    p_logarithmic = np.polyfit(x_log, y, 1)
    
    # Loglinear
    # Definition: y = a*xlog(x) + b
    x_loglin = x * np.log2(x)
    p_loglinear = np.polyfit(x_loglin, y, 1)
    
    # Quadratic
    # Definition: y = ax^2 + bx + c
    p_quadratic = np.polyfit(x, y, 2)
    
    # Cubic
    # Definition: y = ax^3 + bx^2 + cx + d
    p_cubic = np.polyfit(x, y, 3)
    
    # Exponential
    log_y = np.log2(y)
    p_exponential = np.polyfit(x, log_y, 1)

    # The above gives the relevant coefficients. To actually get predicted values, we sub them into the polynomial
    y_linear = np.polyval(p_linear, x)
    y_logarithmic = np.polyval(p_logarithmic, x_log)
    y_loglinear = np.polyval(p_loglinear, x_loglin)
    y_quadratic = np.polyval(p_quadratic, x)
    y_cubic = np.polyval(p_cubic, x)
    
    # For the exponential, we fit log(y) = a*x + b, so to get back to y, we take the exponential:
    log_y_pred = np.polyval(p_exponential, x)
    y_exponential = 2 ** log_y_pred

    # From here, we calculate the residual sum of squares, to see how close we are using each model
    def rss(y_true, y_pred):
        return np.sum((y_pred - y_true) ** 2)
    
    # Make a hashmap with the rss values for each and their complexity type:
    rss_scores = {
        ComplexityType.LINEAR : rss(y, y_linear),
        ComplexityType.LOGARITHMIC : rss(y, y_logarithmic),
        ComplexityType.LOGLINEAR : rss(y, y_loglinear),
        ComplexityType.QUADRATIC : rss(y, y_quadratic),
        ComplexityType.CUBIC : rss(y, y_cubic),
        ComplexityType.EXPONENTIAL: rss(y, y_exponential),
    }

    # Display the current RSS scores.
    for complexity, score in rss_scores.items():
        print(score, complexity)
    
    # To account for the fact that quadratics/cubics can easily map to a linear, we introduce a penalty function,
    # (Akaike information criterion) that penalises based on the number of parameters used in the model.
    # NOTE: could branch this out to be conducted only when required.
    n = len(y)
    param_counts = {
        ComplexityType.CONSTANT: 1,
        ComplexityType.LOGARITHMIC: 2,
        ComplexityType.LOGLINEAR: 2,
        ComplexityType.LINEAR: 2,
        ComplexityType.QUADRATIC: 3,
        ComplexityType.CUBIC: 4,
        ComplexityType.EXPONENTIAL: 2,
    }

    # Compute the Akaike scores.
    def aic(rss, k):
        return 2*k + n * np.log(rss / n)
    aic_scores = {c: aic(rss_scores[c], param_counts[c]) for c in rss_scores}
    
    # Take the minimum Akaike score as the best result, and output the estimated time complexity.
    best = min(aic_scores, key=aic_scores.get)
    print_result_message(best, function_name, program_name)

if __name__ == "__main__":
    main()

