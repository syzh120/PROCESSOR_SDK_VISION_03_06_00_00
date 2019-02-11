
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x tda3xx dra78x am335x am437x am574x))
PACKAGE_SRCS_COMMON += cslr_timer.h csl_timer.h src/ip/timer/src_files_timer.mk src/ip/timer/V1
SRCDIR += src/ip/timer/V1/priv
INCDIR += . src/ip/timer/V1
SRCS_COMMON += timer.c
endif

ifeq ($(SOC),$(filter $(SOC), am335x am437x))
SRCS_COMMON += dmtimer1ms.c
endif

ifeq ($(SOC),$(filter $(SOC), k2h k2k k2l k2e k2g c6678 c6657 omapl137 omapl138))
PACKAGE_SRCS_COMMON += cslr_cp_timer16.h  cslr_synctimer.h  cslr_timer.h  cslr_wd_timer.h
PACKAGE_SRCS_COMMON += csl_timer.h  csl_wd_timer.h src/ip/timer/V0/cslr_tmr.h
PACKAGE_SRCS_COMMON += src/ip/timer/src_files_timer.mk src/ip/timer/V0
SRCDIR += src/ip/timer/V0
INCDIR += . src/ip/timer/V0
SRCS_COMMON += csl_tmrClose.c  csl_tmrGetHwSetup.c  csl_tmrGetHwStatus.c  csl_tmrHwControl.c
SRCS_COMMON += csl_tmrHwSetup.c  csl_tmrHwSetupRaw.c  csl_tmrInit.c  csl_tmrOpen.c
endif
