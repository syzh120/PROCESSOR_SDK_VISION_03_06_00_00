#!/bin/bash
echo " Linux Build Setup"

#update the sdk path
SDK_PATH=$(pwd)
CURR_DIR=$(pwd)
LINUX_TOOLS_PATH=$SDK_PATH/../../ti_components
mkdir -p $LINUX_TOOLS_PATH/os_tools/linux/kernel
cd $LINUX_TOOLS_PATH/os_tools/linux/kernel
echo "Cloning Kernel"
git clone git://git.ti.com/glsdk/infoadas-kernel.git omap
cd omap/
git checkout -b kernel_dev tags/REL_VISION_SDK_03_06_00_00

cd $CURR_DIR
echo "Cloning Cmem"
mkdir -p $LINUX_TOOLS_PATH/os_tools/linux/kernel/cmem
cd $LINUX_TOOLS_PATH/os_tools/linux/kernel/cmem
git clone git://git.ti.com/ipc/ludev.git
cd ludev/
git checkout -b cmem_dev tags/"4.14.01.00"

cd $CURR_DIR
echo "Cloning UBoot"
mkdir -p $LINUX_TOOLS_PATH/os_tools/linux/u-boot
cd $LINUX_TOOLS_PATH/os_tools/linux/u-boot
git clone git://git.ti.com/glsdk/infoadas-u-boot.git u-boot
cd u-boot/
git checkout -b uboot_dev tags/REL_VISION_SDK_03_06_00_00

cd $CURR_DIR
echo "Cloning SGX ddk"
mkdir -p $LINUX_TOOLS_PATH/os_tools/linux/sgx
cd $LINUX_TOOLS_PATH/os_tools/linux/sgx
git clone git://git.ti.com/graphics/omap5-sgx-ddk-linux.git
cd omap5-sgx-ddk-linux/
git checkout -b sgx_dev fd47e44


echo "Basic Linux Setup for 4.4 done"
echo "Download the filesystem and untar"
