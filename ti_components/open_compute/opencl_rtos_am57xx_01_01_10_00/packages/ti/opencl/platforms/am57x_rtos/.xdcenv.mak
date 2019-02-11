#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /datalocal1/ti_components/os_tools/bios_6_45_01_29/packages
override XDCROOT = /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /datalocal1/ti_components/os_tools/bios_6_45_01_29/packages;/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages;../../../..
HOSTOS = Linux
endif
