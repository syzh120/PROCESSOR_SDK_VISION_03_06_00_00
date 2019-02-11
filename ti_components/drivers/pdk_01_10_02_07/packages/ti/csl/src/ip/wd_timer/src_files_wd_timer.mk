
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x am574x))
PACKAGE_SRCS_COMMON += cslr_wd_timer.h csl_wd_timer.h src/ip/wd_timer/src_files_wd_timer.mk src/ip/wd_timer/V0
SRCDIR += src/ip/wd_timer/V0/priv
INCDIR += . src/ip/wd_timer/V0
SRCS_COMMON += wd_timer.c
endif
