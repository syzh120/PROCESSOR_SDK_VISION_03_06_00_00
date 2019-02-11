#!/bin/sh
# Run MessageQMulti in parallel processes
#

g=""

if [ $# -ne 2 ]
then
    echo "Usage: multi_process <num_processes> <iterations_per_process>"
    exit
fi

i=0; while [ $i -le $(($1 - 1)) ]; do
	echo "MessageQMulti Test #" $i
	# This calls MessageQMulti with One Thread, a process #, and
	# number of iterations per thread.
	MessageQMulti$g 1 $2 $i &
	((i = $i + 1))
done
