#!/bin/bash
export PATH=/usr/bin:/sbin:/bin
mount -t sysfs none /sys
mount -t dev none /sys
mount -t proc none /proc
mount -t tmpfs -o size=51200K /var/volatile
mkdir /var/volatile/tmp

LAUNCH_DEMO=0

if [ $LAUNCH_DEMO -eq 1 ]; then

#Late attach with remote cores
echo Remoteproc
FW_NAMES="dra7-ipu2-fw.xem4 dra7-dsp1-fw.xe66 dra7-dsp2-fw.xe66"
for FW in $FW_NAMES ; do
	if [ -e /sys/class/firmware/$FW/loading ]; then
		echo "Loading $FW"
		echo 1 > /sys/class/firmware/$FW/loading
		cat /lib/firmware/$FW > /sys/class/firmware/$FW/data
		echo 0 > /sys/class/firmware/$FW/loading
	else
		echo "$FW loaded already"
	fi
done

#Insert kernel modules
modprobe omap_remoteproc
modprobe rpmsg-rpc
modprobe virtio_rpmsg_bus

#Initiale SGX and EGL
/etc/init.d/rc.pvr start

#Launch weston and wait for it
source /etc/profile.d/wayland_env.sh
/etc/init.d/weston start
usleep 200000
weston --tty=1 --backend=drm-backend.so &
for i in `seq 1 100`; do
	weston-info
	if [ $? -eq "0" ]; then
		break
	fi
	usleep 10000
done

#Launch 2DRV upon startup
cd /opt/infoadas
./memcache_load.sh >> /tmp/loadvsdk.txt
cd /opt/infoadas/bin
./infoadas-app --autolaunch surr_view:lvds-srv-2d-880x1080 --layout layouts-lcd10.xml

bash
fi

#Launch prompt
exec /sbin/init
