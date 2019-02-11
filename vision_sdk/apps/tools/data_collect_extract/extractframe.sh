#!/bin/bash
# Extract a frame from a file and print to stdout

source functions.sh

if [ "$#" -ne 2 ]; then
	echo
	echo "Extract frames from a data dump file"
	echo
	echo "Usage:"
	echo
	echo "  extractframe.sh [frame number] [file name]"
	echo
	exit 1;
fi

frame=$1
file=$2

get_index_file ${file}
get_buffIdx_size ${file}

skip=$((${frame}*${buffIdxSize} + 24))

# Read size of the record in the data file
get_size_offset ${version}
read_int32_field $((${sizeOffset}+${skip})) ${idxfile}
parse_LE32_hex ${field}
hexsize=$hexresult
size=$result

# Read starting address of record in the data file (offset)
get_offset_offset ${version}
read_int32_field $((${offsetOffset}+${skip})) ${idxfile}
parse_LE32_hex ${field}
hexoffset=$hexresult
offset=$result

dd if=${file} ibs=1 skip=${offset} count=${size} 2>/dev/null
