#!/bin/bash

function usage()
{
    echo `basename $0`: " <input_file.jpg>"
    exit 1;
}

if [ $# -lt 4 ]; then
    usage
fi

INPUT_FILE="$1 $2 $3 $4"
shift 4

DEVNAME=eth0
IP=192.168.1.200

trap abort SIGINT

# Now run the AVB talker
# Spoof the source mac address to match the DRA7xx evm demo app expected MAC address
# The --loop option repeats playback of the MJPEG input files
./avbtp_test_client --dev $DEVNAME --src-mac-spoof 00:01:02:03:04:05 --ip $IP --input $INPUT_FILE --loop $@
