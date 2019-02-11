
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_l4fw.h csl_l4fw.h src/ip/l4fw/src_files_l4fw.mk src/ip/l4fw/V0
SRCDIR += src/ip/l4fw/V0/priv
INCDIR += src/ip/l4fw/V0
SRCS_COMMON += l4fw.c
endif
