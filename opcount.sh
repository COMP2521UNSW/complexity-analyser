#!/bin/sh
# Usage: opcount [--fn <function name>] <command (must be a C program)>
fn="main"

while true
do
	# count instructions executed by a specified function
	if [ $1 = "--fn" ]
	then
		shift
		fn="$1"
		shift
	else
		break
	fi
done

# Collect the operation count. 
valgrind --tool=callgrind --log-file=valgrind.out --callgrind-out-file=/dev/null --toggle-collect="$fn" "$@" > /dev/null
egrep '^==[0-9]+== *Collected *: *' valgrind.out | egrep -o "[0-9]+$" 

# Remove the valgrind result file.
rm valgrind.out