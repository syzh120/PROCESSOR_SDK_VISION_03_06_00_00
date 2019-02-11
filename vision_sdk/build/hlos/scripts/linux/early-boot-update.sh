#! /bin/bash -e
# Script to update boot partition for early-boot and late-attach
#
Usage () {
		cat <<EOF
Usage
=====

early-boot-update.sh <makeconfig> <path to target FS> <path to boot-partition>

Arguments
=========

Argument 1 is mandatory and indicates the current configuration being built. The
list of valid arguments inlcude "tda2xx_evm_linux_all", "tda2px_evm_linux_all",
"tda2ex_evm_linux_all" and "tda2ex_17x17_evm_linux_all"

Argument 2 is mandatory and indicates path where the Linux target file-system 
is present

Argument 3 is mandatory and indicates the path to the target boot
partition. Usually this is /media/<username>/boot

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

This command will delete existing uImage, zImage, uenv.txt, dtb and remote-core
firmwares present in the boot partition and update it with the necessary files

EOF
}

if [ "$#" -lt 3 ]; then
Usage
exit 1
fi

echo "## This will update the contents of the boot partition for early-boot ..."
echo "## WARNING: THIS SCRIPT WILL REMOVE SOME CONTENTS OF THE BOOT-PARTION ..."

echo "## Deleting contents of the boot-partition ..."
MAKECONFIG=$1
LINUX_TARGETFS=$2
BOOT=$3

rm -f $BOOT/uImage
rm -f $BOOT/zImage
rm -f $BOOT/dra7*
rm -f $BOOT/uenv.txt
rm -f $BOOT/u-boot.img

echo "## Updating boot partition ..."
cp -fr $LINUX_TARGETFS/boot/uImage $BOOT/
if [ "$MAKECONFIG" = "tda2xx_evm_linux_all" ]; then
	cp $LINUX_TARGETFS/boot/dra7-evm-infoadas.dtb $BOOT/single-stage-boot.dtb
	cp $LINUX_TARGETFS/lib/firmware/dra7-ipu2-fw.lzop $BOOT/dra7-ipu2-fw.lzop
	cp $LINUX_TARGETFS/lib/firmware/dra7-dsp1-fw.lzop $BOOT/dra7-dsp1-fw.lzop
	cp $LINUX_TARGETFS/lib/firmware/dra7-dsp2-fw.lzop $BOOT/dra7-dsp2-fw.lzop
elif [ "$MAKECONFIG" = "tda2xx_evm_linux_autosar" ]; then
	cp $LINUX_TARGETFS/boot/dra7-evm-infoadas.dtb $BOOT/single-stage-boot.dtb
	cp $LINUX_TARGETFS/lib/firmware/dra7-ipu1-fw.lzop $BOOT/dra7-ipu1-fw.lzop
	cp $LINUX_TARGETFS/lib/firmware/dra7-ipu2-fw.lzop $BOOT/dra7-ipu2-fw.lzop
	cp $LINUX_TARGETFS/lib/firmware/dra7-dsp1-fw.lzop $BOOT/dra7-dsp1-fw.lzop
	cp $LINUX_TARGETFS/lib/firmware/dra7-dsp2-fw.lzop $BOOT/dra7-dsp2-fw.lzop
elif [ "$MAKECONFIG" = "tda2px_evm_linux_all" ]; then
	cp $LINUX_TARGETFS/boot/dra76-evm-infoadas.dtb $BOOT/single-stage-boot.dtb
	cp $LINUX_TARGETFS/lib/firmware/dra7-ipu2-fw.lzop $BOOT/dra7-ipu2-fw.lzop
	cp $LINUX_TARGETFS/lib/firmware/dra7-dsp1-fw.lzop $BOOT/dra7-dsp1-fw.lzop
	cp $LINUX_TARGETFS/lib/firmware/dra7-dsp2-fw.lzop $BOOT/dra7-dsp2-fw.lzop
elif [ "$MAKECONFIG" = "tda2ex_evm_linux_all" ]; then
	cp $LINUX_TARGETFS/boot/dra72-evm-infoadas.dtb $BOOT/single-stage-boot.dtb
	cp $LINUX_TARGETFS/lib/firmware/dra7-ipu2-fw.lzop $BOOT/dra7-ipu2-fw.lzop
	cp $LINUX_TARGETFS/lib/firmware/dra7-dsp1-fw.lzop $BOOT/dra7-dsp1-fw.lzop
elif [ "$MAKECONFIG" = "tda2ex_17x17_evm_linux_all" ]; then
	cp $LINUX_TARGETFS/boot/dra71-evm-infoadas.dtb $BOOT/single-stage-boot.dtb
	cp $LINUX_TARGETFS/lib/firmware/dra7-ipu2-fw.lzop $BOOT/dra7-ipu2-fw.lzop
	cp $LINUX_TARGETFS/lib/firmware/dra7-dsp1-fw.lzop $BOOT/dra7-dsp1-fw.lzop
fi

