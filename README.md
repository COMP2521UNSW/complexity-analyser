# `cs2521`-complexity-analyser

A small project for the COMP2521 Team, that makes use of callgrind to estimate code/function runtime complexity.

# Basic Idea

Run the program, collect the number of operations it takes to run a certain function, and match that with 
common time complexities, i.e., $(O(1), O(\log(n)), O(n), O(n \log(n)), O(n^2), O(n^3), O(2^n))$.

# Implementation

\*Write up required here\*

# Upcoming Changes (aka Need To Do)
* **Important: Differentiate between $O(n^3)$ and $O(a^n)$**
* Make the program run with custom input that isn't purely numeric.
  * E.g., ensuring that assignment code can be tested, albeit usually being in an altenrative format where size is not easily discernable.
  * The working idea (in my head) is to take in a delimited .tca file, in the form \< program arguments \> | \<size this represents\>


