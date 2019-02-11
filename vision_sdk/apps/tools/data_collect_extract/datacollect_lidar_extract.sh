#!/bin/bash
# Extract a specific laser record from a given data file (or several)
# @todo for "to the end of the file" versions, get the total lidar scans
#       instead of simply relying on reaching the end of the file for better
#       progress indicators

source functions.sh

case "$#" in
	1)
		file=$1
		start=0
		get_record_count ${file}
		count=${records}
		;;
	2)
		start=$1
		file=$2
		get_record_count ${file}
		count=${records}
		;;
	3)
		start=$1
		count=$2
		file=$3
		;;
	*)
		echo
		echo "Extract laser data records from a data collect binary file"
		echo
		echo "Usage:"
		echo
		echo "  datacollect_lidar_extract.sh [file]"
		echo "  datacollect_lidar_extract.sh [start] [file]"
		echo "  datacollect_lidar_extract.sh [start] [count] [file]"
		echo
		exit 1;
		;;
esac

echo "Total records to extract: ${count}"

basepath=$(dirname ${file})
get_index_file ${file}

get_record_count ${idxfile}
total_records=$records

get_buffIdx_size ${idxfile}

found=0
rec=${start}

while [ "${found}" -lt "${count}" ] && [ "${rec}" -le "${total_records}" ]; do
	skip=$((${rec}*${buffIdxSize} + 24))
	read_int32_field $((4+${skip})) ${idxfile}

	if is_lidar_frame ${field}; then
		printf -v outputpath "${basepath}/lidar_%04d_${rec}.lxyz" ${found}
		found=$((found+1))

		./extractframe.sh ${rec} ${file} | ./lidar_convert dc > $outputpath
		show_progress_bar ${count} ${found} "Extracting LiDAR scans"
	fi

	rec=$((rec+1))
done

echo
echo "Extracted ${found} LiDAR scans"
