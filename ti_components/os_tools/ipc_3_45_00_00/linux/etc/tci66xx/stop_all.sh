for i in 0 1 2 3 4 5 6 7
do
echo "Resetting core $i..."
mpmcl reset dsp$i
mpmcl status dsp$i
done
echo "Done"
