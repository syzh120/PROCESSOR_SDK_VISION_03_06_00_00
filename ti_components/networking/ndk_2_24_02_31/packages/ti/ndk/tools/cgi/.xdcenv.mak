#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /datalocal1/user/surya/vsdk_02_12_RC1/ti_components/os_tools/bios_6_46_00_23/packages
override XDCROOT = /datalocal1/user/surya/vsdk_02_12_RC1/ti_components/os_tools/linux/xdctools_3_32_00_06_core
override XDCBUILDCFG = /datalocal1/user/surya/vsdk_02_12_RC1/ti_components/networking/ndk_2_24_02_31/ndk.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = ti.targets.C64P="" ti.targets.C64P_big_endian="" ti.targets.C674="" ti.targets.arm.elf.Arm9="" ti.targets.arm.elf.A8F="" ti.targets.arm.elf.A8Fnv="" ti.targets.arm.elf.M3="" ti.targets.arm.elf.M4="" ti.targets.arm.elf.M4F="/datalocal1/user/surya/vsdk_02_12_RC1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5" ti.targets.elf.C66="/datalocal1/user/surya/vsdk_02_12_RC1/ti_components/cg_tools/linux/C6000_7.4.2" ti.targets.elf.C66_big_endian="" ti.targets.elf.C674="" gnu.targets.arm.M3="" gnu.targets.arm.M4="" gnu.targets.arm.M4F="" gnu.targets.arm.A8F="" gnu.targets.arm.A9F="" gnu.targets.arm.A15F="/datalocal1/user/surya/vsdk_02_12_RC1/ti_components/cg_tools/linux/gcc-arm-none-eabi-4_9-2015q3" iar.targets.arm.M3="" iar.targets.arm.M4F="" iar.targets.arm.M4="" BUILDMINSTACK="0"
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /datalocal1/user/surya/vsdk_02_12_RC1/ti_components/os_tools/bios_6_46_00_23/packages;/datalocal1/user/surya/vsdk_02_12_RC1/ti_components/os_tools/linux/xdctools_3_32_00_06_core/packages;../../../..
HOSTOS = Linux
endif
