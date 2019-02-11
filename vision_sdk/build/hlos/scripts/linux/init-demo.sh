#!/bin/bash
export PATH=/usr/bin:/sbin:/bin
mount -t sysfs none /sys
mount -t dev none /dev
mount -t proc none /proc
mount -t tmpfs -o size=51200K /var/volatile
mkdir /var/volatile/tmp

LAUNCH_DEMO=0

if [ $LAUNCH_DEMO -eq 1 ]; then

#Late attach with remote cores
FW_NAMES="dra7-ipu2-fw.xem4 dra7-dsp1-fw.xe66 dra7-dsp2-fw.xe66"
for FW in $FW_NAMES ; do
	if [ -e /sys/class/firmware/$FW/loading ]; then
		echo "Loading $FW"
		echo 1 > /sys/class/firmware/$FW/loading
		cat /lib/firmware/$FW.rsc > /sys/class/firmware/$FW/data
		echo 0 > /sys/class/firmware/$FW/loading
	else
		echo "$FW loaded already"
	fi
done &

#Initiale SGX and EGL
/etc/init.d/rc.pvr start

#Launch 2DRV upon startup
cd /opt/vision_sdk
./vision_sdk_load.sh
./apps.out
sleep 1
ROOT_DEV=`cat /proc/cmdline | sed -e 's/^.*root=//' -e 's/ .*$//'`
mount -o remount -o ro $ROOT_DEV
fsck $ROOT_DEV
bash

fi

#Launch prompt
exec /sbin/init
