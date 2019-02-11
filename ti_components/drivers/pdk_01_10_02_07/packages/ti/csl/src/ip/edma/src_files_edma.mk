
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x am574x tda3xx dra78x omapl137 omapl138))
PACKAGE_SRCS_COMMON += cslr_edma.h csl_edma.h src/ip/edma/src_files_edma.mk src/ip/edma/V1
SRCS_COMMON += edma.c
SRCDIR += src/ip/edma/V1/priv
INCDIR += . src/ip/edma/V1
endif

ifeq ($(SOC),$(filter $(SOC), am571x am572x am574x k2h k2k k2l k2e k2g c6678 c6657))
PACKAGE_SRCS_COMMON += src/ip/edma/V0
SRCS_COMMON += csl_edma3Init.c csl_edma3Open.c csl_edma3Close.c
SRCS_COMMON += csl_edma3HwSetup.c csl_edma3HwControl.c csl_edma3GetHwStatus.c
SRCS_COMMON += csl_edma3GetHwSetup.c csl_edma3ChannelOpen.c csl_edma3ChannelClose.c
SRCS_COMMON += csl_edma3HwChannelSetup.c csl_edma3HwChannelControl.c
SRCS_COMMON += csl_edma3GetHwChannelStatus.c csl_edma3GetHwChannelSetup.c csl_edma3Param.c

SRCDIR += src/ip/edma/V0
INCDIR += . src/ip/edma/V0
endif
