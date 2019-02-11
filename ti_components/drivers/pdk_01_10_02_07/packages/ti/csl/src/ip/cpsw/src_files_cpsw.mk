
ifeq ($(SOC),$(filter $(SOC), k2h k2k c6678))
PACKAGE_SRCS_COMMON += csl_cpswAux.h  csl_cpsw.h  csl_cpsw_ssAux.h  csl_cpsw_ss_s.h  cslr_cpsw.h
PACKAGE_SRCS_COMMON += cslr_cpsw_ss_s.h  cslr_cpsw_thread_mapper.h  cslr_xge_cpsw.h  cslr_xge_cpsw_ss_s.h
endif

ifeq ($(SOC),$(filter $(SOC), k2h k2k))

PACKAGE_SRCS_COMMON += src/ip/cpsw/V0/csl_cpsw_5gfAux.h src/ip/cpsw/V0/csl_cpsw_5gfssAux.h
PACKAGE_SRCS_COMMON += src/ip/cpsw/V0/csl_cpswAux.h  src/ip/cpsw/V0/csl_cpsw_ss_s.h
PACKAGE_SRCS_COMMON += src/ip/cpsw/V0/csl_cpts.h src/ip/cpsw/V0/cslr_cpsw_5gfss_s.h
PACKAGE_SRCS_COMMON += src/ip/cpsw/V0/csl_cpsw_5gf.h src/ip/cpsw/V0/csl_cpsw_5gfss_s.h
PACKAGE_SRCS_COMMON += src/ip/cpsw/V0/csl_cpsw_ssAux.h  src/ip/cpsw/V0/csl_cptsAux.h
PACKAGE_SRCS_COMMON += src/ip/cpsw/V0/cslr_cpsw_5gf.h  src/ip/cpsw/V0/cslr_cpts.h
PACKAGE_SRCS_COMMON += src/ip/cpsw/src_files_cpsw.mk src/ip/cpsw/V0
SRCS_COMMON += csl_cpsw_5gf.c  cslr_cpts_resetread.c
SRCDIR += src/ip/cpsw/V0
INCDIR += . src/ip/cpsw/V0

endif

ifeq ($(SOC),$(filter $(SOC), c6678))
PACKAGE_SRCS_COMMON += src/ip/cpsw/V4/csl_cpsw_3gfAux.h  src/ip/cpsw/V4/csl_cpsw_3gfssAux.h
PACKAGE_SRCS_COMMON += src/ip/cpsw/V4/csl_cpswAux.h     src/ip/cpsw/V4/csl_cpsw_ss_s.h
PACKAGE_SRCS_COMMON += src/ip/cpsw/V4/csl_cpts.h       src/ip/cpsw/V4/cslr_cpsw_3gfss_s.h
PACKAGE_SRCS_COMMON += src/ip/cpsw/V4/csl_cpsw_3gf.h     src/ip/cpsw/V4/csl_cpsw_3gfss_s.h
PACKAGE_SRCS_COMMON += src/ip/cpsw/V4/csl_cpsw_ssAux.h  src/ip/cpsw/V4/csl_cptsAux.h
PACKAGE_SRCS_COMMON += src/ip/cpsw/V4/cslr_cpsw_3gf.h  src/ip/cpsw/V4/cslr_cpts.h
PACKAGE_SRCS_COMMON += src/ip/cpsw/src_files_cpsw.mk src/ip/cpsw/V4
SRCS_COMMON += csl_cpsw_3gf.c

SRCDIR += src/ip/cpsw/V4
INCDIR += . src/ip/cpsw/V4

endif

ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px am572x am574x dra75x tda2ex dra72x am571x tda3xx dra78x))
  PACKAGE_SRCS_COMMON += cslr_cpsw.h src/ip/cpsw/src_files_cpsw.mk src/ip/cpsw/V3 src/ip/cpdma/V0
endif
