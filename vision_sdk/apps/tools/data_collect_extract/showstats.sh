#!/bin/bash
# Show summary information about a single file

source functions.sh

if [ "$#" -ne 1 ]; then
	echo
	echo "Show summary information about a data file"
	echo
	echo "Usage:"
	echo
	echo "  showstats.sh [file]"
	echo
	exit 1;
fi

file=$1
get_index_file ${file}
get_record_count ${idxfile}
get_buffIdx_size ${file}
get_size_offset ${version}

lidar=0
imu=0
yuv420=0
yonly=0
bitstream=0
unknown=0

for rec in $(seq 0 $((${records}-1))); do
	skip=$((${rec}*${buffIdxSize} + 24))
	read_int32_field $((4+${skip})) ${idxfile}
	datatype=$field

	read_int32_field $((${sizeOffset}+${skip})) ${idxfile}
	parse_LE32_hex ${field}
	hexsize=$hexresult
	size=$result

	if is_yuv420_frame ${datatype}; then
		yuv420=$((yuv420+1))
	elif is_yonly_frame ${datatype}; then
		yonly=$((yonly+1))
	elif is_meta_frame ${datatype}; then
		if is_lidar_frame ${size}; then
			lidar=$((lidar+1))
		elif is_imu_frame ${size}; then
			imu=$((imu+1))
		else
			unknown=$((unknown+1))
		fi
	elif is_bitstream_frame ${datatype}; then
		bitstream=$((bitstream+1))
	else
		unknown=$((unknown+1))
	fi

    show_progress_bar ${records} ${rec} "Reading index file"
done

echo

echo "${file} (version ${version}) contains ${records} records:"
echo "  ${yuv420} yuv420 frames,"
echo "  ${yonly} y-only frames,"
echo "  ${bitstream} bitstream (compressed video) frames,"
echo "  ${lidar} lidar frames,"
echo "  ${imu} imu frames,"
echo "  ${unknown} unidentified frames"

