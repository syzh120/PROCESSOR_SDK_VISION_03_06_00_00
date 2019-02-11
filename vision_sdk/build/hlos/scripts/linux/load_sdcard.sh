#!/bin/bash
# Load only m4, c66, and a15 linux binaries onto an SD card, bypassing the need to create a new
# targetfs image and unpack it onto the device, which can take up to 15 minutes
# a complete targetfs must have been previously installed!

DEVICE=/dev/mmcblk0
PART=$(ls ${DEVICE}*1)
PART2=$(ls ${DEVICE}*2)
TARGETFSROOT=../../../../../ti_components/os_tools/linux/targetfs

if [[ -z "${PART2}" ]]; then
    echo "${DEVICE} not present--eject card and try again"
    exit;
fi

MTBOOT=$(cat /proc/mounts | grep "${PART}" | awk '{ print $2; }')
MTROOT=$(cat /proc/mounts | grep "${PART2}" | awk '{ print $2; }')

if [[ ! -d "${MTROOT}" ]]; then
    echo "${PART2} not mounted--remount or eject card and try again"
    exit;
fi

echo "Loading binaries to mmc at ${MTROOT}..."
cp -R ${TARGETFSROOT}/opt/vision_sdk/* ${MTROOT}/opt/vision_sdk
cp ${TARGETFSROOT}/lib/firmware/*.xem4 ${MTROOT}/lib/firmware/
cp ${TARGETFSROOT}/lib/firmware/*.xe66 ${MTROOT}/lib/firmware/

echo "Unmounting ${DEVICE}..."
[[ ! -z "${MTBOOT}" ]] && umount ${MTBOOT}
umount ${MTROOT}
