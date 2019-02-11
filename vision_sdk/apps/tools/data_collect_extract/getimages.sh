#!/bin/bash
# Get images from an archive file

source functions.sh

case "$#" in
	1)
		file=$1
		start=0
		get_record_count ${file}
		count=$records
		format=png
		;;
	2)
		file=$2
		start=$1
		get_record_count ${file}
		count=$records
		format=png
		;;
	3)
		start=$1
		count=$2
		file=$3
		format=png
		;;
	4)
		start=$1
		count=$2
		format=$3
		file=$4
		;;
	*)
		echo
		echo "Get images from a data collect file in png or jpg format"
		echo
		echo "Usage:"
		echo
		echo "  getimages.sh [filename]"
		echo "  getimages.sh [start] [filename]"
		echo "  getimages.sh [start] [count] [filename]"
		echo "  getimages.sh [start] [count] [png|jpg] [filename]"
		echo
		echo "If the [png|jpg] parameter is omitted, the default is png"
		echo
		exit 1;
		;;
esac

echo "Total records to extract: ${count}"

basepath=$(dirname ${file})
get_index_file ${file}

get_record_count ${idxfile}
total_records=$records

get_buffIdx_size ${file}

imgcount=0
rec=${start}

while [ "${imgcount}" -lt "${count}" ] && [ "${rec}" -le "${total_records}" ]; do
	skip=$((${rec}*${buffIdxSize} + 24))
	read_int32_field $((4+${skip})) ${idxfile}

	if is_yuv420_frame ${field}; then
		yuvpath=${basepath}/frame$((${imgcount}+${start})).yuv
		./extractframe.sh ${rec} ${file} > $yuvpath
		echo "yuv2rgb('${yuvpath}', 720, 1280, '420sp', '${format}');" | octave --no-gui --quiet --norc > /dev/null 2>&1
		imgcount=$((imgcount+1))
		rm $yuvpath

		show_progress_bar ${count} ${imgcount} "Converting images"
	fi

	rec=$((rec+1))
done

echo
echo "Extracted ${imgcount} images"
