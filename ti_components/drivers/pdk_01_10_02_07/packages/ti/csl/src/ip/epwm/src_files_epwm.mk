
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx dra72x dra75x dra78x am571x am572x am574x  am437x am335x k2g))
PACKAGE_SRCS_COMMON += cslr_pwmss.h cslr_epwm.h csl_epwm.h src/ip/epwm/src_files_epwm.mk src/ip/epwm/V0
PACKAGE_SRCS_COMMON += src/ip/epwm/hw_pwmss_submodule_offsets.h
SRCDIR += src/ip/epwm/V0/priv
INCDIR += src/ip/epwm/V0
SRCS_COMMON += csl_epwm.c
endif

ifeq ($(SOC),$(filter $(SOC), k2g))
PACKAGE_SRCS_COMMON += src/ip/epwm/V0_1
endif
