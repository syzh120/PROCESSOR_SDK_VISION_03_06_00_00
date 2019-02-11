#
#  ======== ndk.mak ========
#

#
# Where to install/stage the packages
# Typically this would point to the devkit location
#
DESTDIR ?= <UNDEFINED>

prefix ?= /
docdir ?= /docs/ndk
packagesdir ?= /packages

# USER STEP: user must define below path to xdc installation
# Set up dependencies
XDC_INSTALL_DIR ?= /datalocal1/user/surya/vsdk_02_12_RC1/ti_components/os_tools/linux/xdctools_3_32_00_06_core
SYSBIOS_INSTALL_DIR ?= /datalocal1/user/surya/vsdk_02_12_RC1/ti_components/os_tools/bios_6_46_00_23

#
# Set location of various cgtools
# These variables can be set here or on the command line.
#
# USER STEP: user must define below paths to compilers
ti.targets.C64P ?=
ti.targets.C64P_big_endian ?=
ti.targets.C674 ?=

ti.targets.elf.C66 ?= /datalocal1/user/surya/vsdk_02_12_RC1/ti_components/cg_tools/linux/C6000_7.4.2
ti.targets.elf.C66_big_endian ?=
ti.targets.elf.C674 ?=

ti.targets.arm.elf.Arm9 ?=
ti.targets.arm.elf.A8F ?=
ti.targets.arm.elf.A8Fnv ?=
ti.targets.arm.elf.M3 ?=
ti.targets.arm.elf.M4 ?=
ti.targets.arm.elf.M4F ?= /datalocal1/user/surya/vsdk_02_12_RC1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5

gnu.targets.arm.M3 ?=
gnu.targets.arm.M4 ?=
gnu.targets.arm.M4F ?=
gnu.targets.arm.A8F ?=
gnu.targets.arm.A9F ?=
gnu.targets.arm.A15F ?= /datalocal1/user/surya/vsdk_02_12_RC1/ti_components/cg_tools/linux/gcc-arm-none-eabi-4_9-2015q3

iar.targets.arm.M3 ?=
iar.targets.arm.M4F ?=
iar.targets.arm.M4 ?=

# Set BUILDMINSTACK to 1 to only build base stack libraries (stk.a* and stk6.a*)
BUILDMINSTACK ?= 0

#
# Set XDCARGS to some of the variables above.  XDCARGS are passed
# to the XDC build engine... which will load ndk.bld... which will
# extract these variables and use them to determine what to build and which
# toolchains to use.
#
# Note that not all of these variables need to be set to something valid.
# Unfortunately, since these vars are unconditionally assigned, your build line
# will be longer and more noisy than necessary (e.g., it will include CC_V5T
# assignment even if you're just building for C64P).
#
# Some background is here:
#     http://rtsc.eclipse.org/docs-tip/Command_-_xdc#Environment_Variables
#
XDCARGS= \
    ti.targets.C64P=\"$(ti.targets.C64P)\" \
    ti.targets.C64P_big_endian=\"$(ti.targets.C64P_big_endian)\" \
    ti.targets.C674=\"$(ti.targets.C674)\" \
    ti.targets.arm.elf.Arm9=\"$(ti.targets.arm.elf.Arm9)\" \
    ti.targets.arm.elf.A8F=\"$(ti.targets.arm.elf.A8F)\" \
    ti.targets.arm.elf.A8Fnv=\"$(ti.targets.arm.elf.A8Fnv)\" \
    ti.targets.arm.elf.M3=\"$(ti.targets.arm.elf.M3)\" \
    ti.targets.arm.elf.M4=\"$(ti.targets.arm.elf.M4)\" \
    ti.targets.arm.elf.M4F=\"$(ti.targets.arm.elf.M4F)\" \
    ti.targets.elf.C66=\"$(ti.targets.elf.C66)\" \
    ti.targets.elf.C66_big_endian=\"$(ti.targets.elf.C66_big_endian)\" \
    ti.targets.elf.C674=\"$(ti.targets.elf.C674)\" \
    gnu.targets.arm.M3=\"$(gnu.targets.arm.M3)\" \
    gnu.targets.arm.M4=\"$(gnu.targets.arm.M4)\" \
    gnu.targets.arm.M4F=\"$(gnu.targets.arm.M4F)\" \
    gnu.targets.arm.A8F=\"$(gnu.targets.arm.A8F)\" \
    gnu.targets.arm.A9F=\"$(gnu.targets.arm.A9F)\" \
    gnu.targets.arm.A15F=\"$(gnu.targets.arm.A15F)\" \
    iar.targets.arm.M3=\"$(iar.targets.arm.M3)\" \
    iar.targets.arm.M4F=\"$(iar.targets.arm.M4F)\" \
    iar.targets.arm.M4=\"$(iar.targets.arm.M4)\" \
    BUILDMINSTACK=\"$(BUILDMINSTACK)\"

#
# Set XDCPATH to contain necessary repositories.
#
XDCPATH = $(SYSBIOS_INSTALL_DIR)/packages
export XDCPATH

#
# Set XDCOPTIONS.  Use -v for a verbose build.
#
#XDCOPTIONS=v
export XDCOPTIONS

#
# Set XDC executable command
# Note that XDCBUILDCFG points to the ndk.bld file which uses
# the arguments specified by XDCARGS
#
XDC = $(XDC_INSTALL_DIR)/xdc XDCARGS="$(XDCARGS)" XDCBUILDCFG=./ndk.bld

######################################################
## Shouldnt have to modify anything below this line ##
######################################################

all:
	@ echo building ndk packages ...
	@ $(XDC) -Pr ./packages

clean:
	@ echo cleaning ndk packages ...
	@ $(XDC) clean -Pr ./packages

install-packages:
	@ echo installing ndk packages to $(DESTDIR) ...
	@ mkdir -p $(DESTDIR)/$(prefix)/$(docdir)
	@ cp -rf $(wildcard ndk_*_ReleaseNotes.html) docs/* $(DESTDIR)/$(prefix)/$(docdir)
	@ mkdir -p $(DESTDIR)/$(prefix)/$(packagesdir)
	@ cp -rf packages/* $(DESTDIR)/$(prefix)/$(packagesdir)
