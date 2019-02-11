#!/bin/bash
# Get images from a file, truncate to y-only, and append to given output

source functions.sh

case "$#" in
	2)
		file=$1
		dest=$2
		get_record_count ${file}
		count=${records}
		start=0
		;;
	3)
		start=$1
		file=$2
		dest=$3
		get_record_count ${file}
		count=${records}
		;;
	4)
		start=$1
		count=$2
		file=$3
		dest=$4
		;;
	*)
		echo
		echo "Get images from a data collect file, truncate to luma-only, and store sequentially"
		echo "in destination file"
		echo
		echo "Usage:"
		echo
		echo "  yframes.sh [source] [destination]"
		echo "  yframes.sh [start] [source] [destination]"
		echo "  yframes.sh [start] [count] [source] [destination]"
		echo
		exit 1;
		;;
esac

echo "Total records to extract ${count}"
echo "Appending image data to ${dest}"

basepath=$(dirname ${file})

get_index_file ${file}
get_record_count ${idxfile}
total_records=$records

get_buffIdx_size ${file}

imgcount=0
rec=${start}
capturesize=$((1280*720))

while [ "${imgcount}" -lt "${count}" ] && [ "${rec}" -le "${total_records}" ]; do
	skip=$((${rec}*${buffIdxSize} + 24))
	read_int32_field $((4+${skip})) ${idxfile}

	if is_yuv420_frame ${field} || is_yonly_frame ${field}; then
		./extractframe.sh ${rec} ${file} | head -c ${capturesize} >> ${dest}
		imgcount=$((imgcount+1))
	fi

	show_progress_bar ${count} ${imgcount} "Extracting images"
	rec=$((rec+1))
done

echo
echo "Extracted ${imgcount} images"
