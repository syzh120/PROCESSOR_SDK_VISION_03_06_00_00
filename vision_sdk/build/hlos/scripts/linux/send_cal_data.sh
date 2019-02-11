#!/bin/bash

cd /tmp

echo "Sending .yuv camera files..."
for filename in /tmp/*.yuv; do
    echo "Sending ${filename}."
    echo $filename | nc 192.168.1.2 2000
    cat $filename | nc 192.168.1.2 2000
done

echo "Sending .lxyz lidar files..."
for filename in /tmp/*.lxyz; do
    echo "Sending ${filename}."
    echo $filename | nc 192.168.1.2 2000
    cat $filename | nc 192.168.1.2 2000
done

echo "Done sending calibration files."
