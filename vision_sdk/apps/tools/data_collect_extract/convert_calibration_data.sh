#!/bin/bash
# Convert a directory full of dump link data to a format used by matlab for calibration

usage()
{
    echo "Usage:"
    echo
    echo "    $0 [ldr|dly] <path>"
    echo
    echo "where"
    echo
    echo "  ldr specifies lidar data, dly specifies camera data"
    echo "  <path> is the folder containing the data to convert"
    exit;
}

if [[ "$#" -ne 2 ]]; then
    usage;
fi

if [[ ! -d "$2" ]]; then
    usage;
fi

case $1 in
    ldr)
        find $2 -name "*.ldr" | sed -e "s/\.ldr$//" | xargs -t -I {} sh -c './lidar_convert {}.ldr > {}.lxyz'
        ;;
    dly)
        find $2 -name "*.dly" | sed -e "s/\.dly$//" | xargs -t -I {} sh -c './dumplink_yuv_extract.sh {}.dly > {}.yuv'
        ;;
esac
