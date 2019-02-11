#! /bin/bash -e
# Script to update boot partition for early-boot and late-attach
#
Usage () {
		cat <<EOF
Usage
=====

flash-qspi.sh <makeconfig> <path to target FS> <path to MLO>

Arguments
=========

Argument 1 is mandatory and indicates the current configuration being built. The
list of valid arguments inlcude "tda2xx_evm_linux_all", "tda2px_evm_linux_all",
"tda2ex_evm_linux_all" and "tda2ex_17x17_evm_linux_all"

Argument 2 is mandatory and indicates path where the Linux target file-system 
is present

Argument 3 is mandatory and indicates the location of the MLO which is the 
boot-loader. Typically this file is found in 
binaries/apps/<MAKECONFIG>tda2xx_evm_linux_all/hlos/linux/boot/MLO
folder in vision-SDK

Prerequisites
=============

Ensure that all the patches for early-boot and late attach are applied
on the kernel and the below commands are run before using this utility

	 make linux
	 make linux_install

Only when the above steps are completed run this utility, or else the system 
boot will fail due to missing dependecies.

WARNING
=============

This command will delete existing contents on the QSPI.

EOF
}

if [ "$#" -lt 3 ]; then
Usage
exit 1
fi

echo "## This will update flash contents to the QSPI and will need sudo permissions...."
echo "## Before running this script ensure that the target is halted at u-boot and run below command"
echo "      => fastboot 0"


MAKECONFIG=$1
LINUX_TARGETFS=$2
MLO=$3

if [ ! -f $MLO ]; then
    echo "MLO path not found!"
    exit 1
fi

rm -rf /tmp/dra7*fw.uImage

mkimage -d $LINUX_TARGETFS/lib/firmware/dra7-ipu2-fw.lzop /tmp/dra7-ipu2-fw.uImage
mkimage -d $LINUX_TARGETFS/lib/firmware/dra7-dsp1-fw.lzop /tmp/dra7-dsp1-fw.uImage
if [ "$MAKECONFIG" = "tda2xx_evm_linux_all" ]; then
mkimage -d $LINUX_TARGETFS/lib/firmware/dra7-dsp2-fw.lzop /tmp/dra7-dsp2-fw.uImage

echo "Erasing contents of SPI"
fastboot oem spi
echo "Flashing MLO"
fastboot flash xloader $MLO
echo "Flashing DTB"
fastboot flash environment $LINUX_TARGETFS/boot/dra7-evm-infoadas.dtb
echo "Flashing uImage"
fastboot flash kernel $LINUX_TARGETFS/boot/uImage

echo "Flashing IPU2 firmware image"
fastboot flash ipu2 /tmp/dra7-ipu2-fw.uImage
echo "Flashing DSP1 firmware image"
fastboot flash dsp1 /tmp/dra7-dsp1-fw.uImage
echo "Flashing DSP2 firmware image"
fastboot flash dsp2 /tmp/dra7-dsp2-fw.uImage
elif [ "$MAKECONFIG" = "tda2px_evm_linux_all" ]; then
mkimage -d $LINUX_TARGETFS/lib/firmware/dra7-dsp2-fw.lzop /tmp/dra7-dsp2-fw.uImage

echo "Erasing contents of SPI"
fastboot oem spi
echo "Flashing MLO"
fastboot flash xloader $MLO
echo "Flashing DTB"
fastboot flash environment $LINUX_TARGETFS/boot/dra76-evm-infoadas.dtb
echo "Flashing uImage"
fastboot flash kernel $LINUX_TARGETFS/boot/uImage

echo "Flashing IPU2 firmware image"
fastboot flash ipu2 /tmp/dra7-ipu2-fw.uImage
echo "Flashing DSP1 firmware image"
fastboot flash dsp1 /tmp/dra7-dsp1-fw.uImage
echo "Flashing DSP2 firmware image"
fastboot flash dsp2 /tmp/dra7-dsp2-fw.uImage

elif [ "$MAKECONFIG" = "tda2ex_evm_linux_all" ]; then
echo "Erasing contents of SPI"
fastboot oem spi
echo "Flashing MLO"
fastboot flash xloader $MLO
echo "Flashing DTB"
fastboot flash environment $LINUX_TARGETFS/boot/dra72-evm-infoadas.dtb
echo "Flashing uImage"
fastboot flash kernel $LINUX_TARGETFS/boot/uImage

echo "Flashing IPU2 firmware image"
fastboot flash ipu2 /tmp/dra7-ipu2-fw.uImage
echo "Flashing DSP1 firmware image"
fastboot flash dsp1 /tmp/dra7-dsp1-fw.uImage

elif [ "$MAKECONFIG" = "tda2ex_17x17_evm_linux_all" ]; then
echo "Erasing contents of SPI"
fastboot oem spi
echo "Flashing MLO"
fastboot flash xloader $MLO
echo "Flashing DTB"
fastboot flash environment $LINUX_TARGETFS/boot/dra71-evm-infoadas.dtb
echo "Flashing uImage"
fastboot flash kernel $LINUX_TARGETFS/boot/uImage

echo "Flashing IPU2 firmware image"
fastboot flash ipu2 /tmp/dra7-ipu2-fw.uImage
echo "Flashing DSP1 firmware image"
fastboot flash dsp1 /tmp/dra7-dsp1-fw.uImage
fi

rm -rf /tmp/dra7*fw.uImage

echo "All files flashed to QSPI.. Set the board to QSPI boot mode and reboot board"
