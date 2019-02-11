echo "Loading and Running " $1 "..."
for i in 0 1 2 3 4 5 6 7
do
./mpmcl load dsp$i $1
./mpmcl run dsp$i
done
