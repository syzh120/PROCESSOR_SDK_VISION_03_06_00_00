#!/bin/bash
# Extract the actual yuv frame data from a dumplink .yuv file, which has an extra
# 8 byte header associated with it, and print to stdout

if [ "$#" -ne 1 ]; then
	echo
	echo "Extract yuv data from a file saved with dump link"
	echo
	echo "Usage:"
	echo
	echo "  dumplink_yuv_extract.sh [filename]"
	echo
	exit 1;
fi

file=$1

tail -c +277 ${file}
