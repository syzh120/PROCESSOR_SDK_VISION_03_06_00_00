#!/bin/bash
# Collection of functions used by other data collect parser-related functions

shopt -s extglob

# Convert a maybe data maybe index filename into an index filename
# $1 = maybe filename
get_index_file() {
	bf=$(basename $1)
	bp=$(dirname $1)
	idxfile=${bp}/${bf/data/idx}
}

# Get the BuffIdx size for a given index file (wrap up all the work), with
# the side effect of also getting the version
# $1 = maybe filename
get_buffIdx_size() {
	get_index_file $1
	read_int32_field 4 ${idxfile}
	parse_LE32_hex ${field}
	version=${result}
	version_to_buffIdx_size ${version}
}

# Convert form a version number into a header size
# $1 = version number
version_to_buffIdx_size() {
	case $1 in
		0) buffIdxSize=40 ;;
		1) buffIdxSize=48 ;;
		*) buffIdxSize=0 ;;
	esac
}

# Get the size field's offset, depending on version number
# $1 = version number
get_size_offset() {
	case $1 in
		0) sizeOffset=20 ;;
		1) sizeOffset=28 ;;
		*) sizeOffset=0 ;;
	esac
}

# Get the offset field's offset, depending on the version number
# $1 = version number
get_offset_offset() {
	case $1 in
		0) offsetOffset=32 ;;
		1) offsetOffset=40 ;;
		*) offsetOffset=0 ;;
	esac
}

# Get the timestamp field's offset, depending on the version number
# $1 = version number
get_timestamp_offset() {
	case $1 in
		0) timestampOffset=24 ;;
		1) timestampOffset=32 ;;
		*) timestampOffset=0 ;;
	esac
}

# Format a timestamp as seconds.fraction for easier to understand display
# $1 = timestamp as a decimal integer
format_timestamp() {
	timestamp=$(echo "6k${1} 1000000/p" | dc)
}

# Parse a little endian hex string into the corresponding hex and decimal values
# $1 = hex string
parse_LE64_hex() {
	hexresult=${1:14:2}${1:12:2}${1:10:2}${1:8:2}${1:6:2}${1:4:2}${1:2:2}${1:0:2}
	result=$((16#${hexresult}))
}

# Parse a little endian hex string like 01020304 into the corresponding
# hex and decimal number (0x04030201 and 67305985 respectively)
# $1 = hex string
parse_LE32_hex() {
	hexresult=${1:6:2}${1:4:2}${1:2:2}${1:0:2}
	result=$((16#${hexresult}))
}

# Parse a 16 bit little endian hex string (4 characters) into the
# corresponding hex and decimal number
# $1 = hex string
parse_LE16_hex() {
	hexresult=${1:2:2}${1:0:2}
	result=$((16#${hexresult}))
}

# Get the number of records in an index file
# $1 = filename (data or index, will be fixed regardless)
get_record_count() {
	get_index_file $1
	read_int32_field 12 ${idxfile}
	parse_LE32_hex ${field}
	records=${result}
}

# Read a 16-bit field as a hex string, not converted
# $1 = skip bytes to start of field
# $2 = index filename
read_int16_field() {
	field=$(xxd -p -s +$1 $2 | head -c 4)
}

# Read a 32-bit field as a hex string, not converted
# $1 = skip bytes to start of field
# $2 = index filename
read_int32_field() {
	field=$(xxd -p -s +$1 $2 | head -c 8)
}

# Read a 64-bit field as a hex string, not converted
# $1 = skip bytes to start of field
# $2 = index filename
read_int64_field() {
	field=$(xxd -p -s +$1 $2 | head -c 8)
}

# Read the channel number from a hex string, which is two characters after the type in flags
# $1 = string of flags field read from +4 bytes after the start of packet
get_channel() {
	local tmp="${1:2:2}"
	channel=$((${tmp##+(0)}))
}

# Test if the hex string given identifies a yuv420 frame
# $1 = string of flags field read from +4 bytes after start of packet
is_yuv420_frame() {
	case "${1:0:2}" in
		00)
			return 0 ;;
		*)
			return 1 ;;
	esac
}

# Test if the hex string given a luma only (y-frame)
# $1 = string of flags field read from +4 bytes after start of packet
is_yonly_frame() {
	case "${1:0:2}" in
		02)
			return 0 ;;
		*)
			return 1 ;;
	esac
}

# Test if the hex string given identifies a metadata frame
# $1 = string of flags field read from +4 bytes after start of packet
is_meta_frame() {
	case "${1:0:2}" in
		03)
			return 0 ;;
		*)
			return 1 ;;
	esac
}

# Test if the hex string given identifies a bitstream frame
# $1 = string of flags field read from +4 bytes after start of packet
is_bitstream_frame() {
	case "${1:0:2}" in
		04)
			return 0 ;;
		*)
			return 1 ;;
	esac
}

# Test if the frame is IMU based on the size
# $1 = size of frame
is_imu_frame() {
	case "$1" in
		150800)
			return 0 ;;
		*)
			return 1 ;;
	esac
}

# Test if the frame is LiDAR based on the size
# $1 = size of frame
is_lidar_frame() {
	case "$1" in
		220096)
			return 0 ;;
		*)
			return 1 ;;
	esac
}

# Render a progress bar with the given options
# $1 = max count
# $2 = current count
# $3 = prefix message
# $4 = hash marks to include (default to 25)
show_progress_bar() {
	local marks=25

	if [ "$#" -eq 4 ]; then
		marks=$5
	fi

	steps=$(bc <<< "$2 * ${marks} / ${1}")

	statusline=""

	for ((i=0; i < ${steps}; i++)); do
		statusline="${statusline}#"
	done

	for ((i=${steps}; i < ${marks}; i++)); do
		statusline="${statusline} "
	done

	echo -ne "\r$3 [${statusline}] ($2/$1)"
}
