#!/bin/bash

function usage()
{
    echo `basename $0`: " <mjpeg input_file.avi>"
    exit 1;
}

# Everything here assume 4 inputs, but you can do up to 6 now
if [ $# -lt 4 ]; then
    usage
fi
INPUT_FILE="$1 $2 $3 $4"
shift 4

DEVNAME=eth0
IP=192.168.1.200
DATARATE=280

trap abort SIGINT

# Do a single ping to the IP address to bring the IP->MAC mapping into the system ARP cache
ping -c 1 -q $IP

# Now run the AVB talker
# --src-mac-spoof sets the source mac address to match the DRA7xx evm demo app expected MAC address
# If not used, the true source mac address of the interface is used
#
# If --dest-mac is provided, the value provided is used as the destination MAC address
# If --dest-ip is provided, a mac address lookup (ARP lookup) happens to get the MAC address
# If neither is provided, then the broadcast address is used
#
# If --data-rate not provided, then it will be set to the input count x 100 (100Mbps for each "camera")
./avbtp_talker --dev $DEVNAME --src-mac-spoof 01:23:45:67:89:AB --dest-ip $IP --data-rate $DATARATE --input $INPUT_FILE $@
