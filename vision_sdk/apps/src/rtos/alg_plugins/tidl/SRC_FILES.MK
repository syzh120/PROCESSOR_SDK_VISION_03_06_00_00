

SRCDIR += tidl

SRCS_c66xdsp_1 += tidlLink_algPlugin.c
SRCS_c66xdsp_2 += tidlLink_algPlugin.c
SRCS_arp32_1 += tidlLink_algPlugin.c
SRCS_arp32_2 += tidlLink_algPlugin.c
SRCS_arp32_3 += tidlLink_algPlugin.c
SRCS_arp32_4 += tidlLink_algPlugin.c

ifeq ($(SOC), $(filter $(SOC), tda2xx tda2px))
    SRCS_a15_0 += tidlpreprocLink_algPlugin.c
    SRCS_a15_0 += tidlpostprocLink_algPlugin.c
endif

ifeq ($(SOC), tda3xx)
    SRCS_$(IPU_PRIMARY_CORE) += tidlpreprocLink_algPlugin.c
endif




