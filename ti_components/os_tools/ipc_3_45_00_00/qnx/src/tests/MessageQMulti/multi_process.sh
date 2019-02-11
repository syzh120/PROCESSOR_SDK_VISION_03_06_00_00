# Run MessageQMulti in parallel processes
#
if [ $# -ne 2 ]
then
    echo "Usage: multi_process <num_processes> <iterations_per_process>"
    echo "Max # processes: 10"
    exit
fi

if [ $1 -gt 10 ]
then
    echo "Number of processes cannot exceed 10."
    exit
fi

num=0; while [ $num -lt $1 ];  do
    echo "MessageQMulti Test #" $num
    # This calls MessageQMulti with One Thread, a process #, and
    # number of iterations per thread.
    MessageQMulti 1 $2 $num &
    ((num = $num + 1))
done
