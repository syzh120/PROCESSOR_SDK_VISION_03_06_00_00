#!/bin/bash
# Show frame information about some number of records

source functions.sh

case "$#" in
	1)
		file=$1
		start=0
		stop=0
		;;
	2)
		file=$2
		start=$1
		stop=$1
		;;
	3)
		file=$3
		start=$1
		stop=$2
		;;
	*)
		echo
		echo "Show information about frames in a data dump file."
		echo
		echo "Usage: "
		echo
		echo "  frameinfo.sh [starting record] [ending record] [file]"
		echo
		echo "  [starting record], [ending record], or both may be omitted"
		echo "  which will print information about the first record in the file"
		echo
		exit 1;
		;;
esac

get_index_file ${file}
file=${idxfile}

get_buffIdx_size ${file}
get_size_offset ${version}
get_offset_offset ${version}
get_timestamp_offset ${version}

for ii in $(seq ${start} ${stop});
do
	skip=$((${ii}*${buffIdxSize} + 24))
	read_int32_field $((4+${skip})) ${file}
	datatype=$field

	read_int32_field $((${sizeOffset}+${skip})) ${file}
	parse_LE32_hex ${field}
	hexsize=$hexresult
	size=$result

	read_int32_field $((${offsetOffset}+${skip})) ${file}
	parse_LE32_hex ${field}
	hexoffset=$hexresult
	offset=$result

	read_int64_field $((${timestampOffset}+${skip})) ${file}
	parse_LE64_hex ${field}
	hextime=$hexresult
	timestamp=$result

	format_timestamp ${timestamp}
	echo -n "[${timestamp}] Record ${ii} is "

	if is_yuv420_frame ${datatype}; then
		echo -n "YUV420sp frame"
	elif is_yonly_frame ${datatype}; then
		echo -n "YUV400 (luma-only) frame"
	elif is_meta_frame ${datatype}; then
		if is_lidar_frame ${size}; then
			echo -n "LiDAR frame"
		elif is_imu_frame ${size}; then
			echo -n "IMU frame"
		else
			echo -n "Unrecognized metadata frame"
		fi
	elif is_bitstream_frame ${datatype}; then
		echo -n "Bistream (Compressed video) frame"
	else
		echo -n "Unrecognized data type (${datatype})"
	fi

	echo -n ": ${size} bytes (0x${hexsize})"
	echo " located at offset ${offset} (0x${hexoffset})"
done
