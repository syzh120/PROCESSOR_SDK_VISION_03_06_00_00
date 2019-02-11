#
_XDCBUILDCOUNT = 1
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = 
override XDCROOT = C:/PROGRA~1/TEXASI~1/xdctools_3_22_04_44_eng
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/PROGRA~1/TEXASI~1/xdctools_3_22_04_44_eng/packages;../..
HOSTOS = Windows
endif
