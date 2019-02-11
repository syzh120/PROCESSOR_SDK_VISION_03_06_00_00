#!/bin/bash
# Decode the mjpeg-encoded bitstream frames into jpg images named in sequence by channel

source functions.sh

case "$#" in
	1)
		file=$1
		start=0
		get_record_count ${file}
		count=${records}
		;;
	2)
		file=$2
		count=$1
		start=0
		;;
	*)
		echo
		echo "Decode MJPEG-encoded bitstream frames into a sequence of jpg images"
		echo
		echo "Usage"
		echo
		echo "  decodeimages.sh [filename]"
		echo "  decodeimages.sh [count] [filename]"
		echo
		echo "Decodes the first [count] images from the given file. If no count is given, all"
		echo "contained compressed images are decoded. Results will be named"
		echo "frame_[channel]_[number].jpg"
		echo
		exit 1;
		;;
esac

echo "Total frames to scan: ${count}"

basepath=$(dirname ${file})
get_index_file ${file}

get_buffIdx_size ${file}

get_record_count ${idxfile}
total_records=${records}
found=0
rec=${start}

while [ "${found}" -lt "${count}" ] && [ "${rec}" -le "${total_records}" ]; do
	skip=$((rec*buffIdxSize + 24))
	read_int32_field $((4+skip)) ${idxfile}

	if is_bitstream_frame ${field}; then
		get_channel ${field}
		if [ -z "${chCounts[${channel}]}" ]; then
			chCounts[${channel}]=0
		fi

		imgpath=${basepath}/frame_${channel}_${chCounts[${channel}]}.jpg
		./extractframe.sh ${rec} ${file} > ${imgpath}

		found=$((found+1))
		chCounts[${channel}]=$((${chCounts[${channel}]}+1))
		show_progress_bar ${count} ${found} "Decoding images"
	fi

	rec=$((rec+1))
done

echo
echo "Extracted ${found} images"
