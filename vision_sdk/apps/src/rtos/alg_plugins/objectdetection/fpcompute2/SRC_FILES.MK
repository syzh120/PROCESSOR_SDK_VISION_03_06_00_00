
SRCDIR += objectdetection/fpcompute2

EVE_ALG_SRCS2 = imagePreProcess_algPlugin.c \
                fpComputeLink_algPlugin.c \
                alg_fpCompute2.c \

SRCS_arp32_1 += $(EVE_ALG_SRCS2)

SRCS_$(IPU_PRIMARY_CORE) += imgPyramid_algPlugin.c

ifeq ($(ISS_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += iss_resizer.c
endif

ifeq ($(VPE_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += vpe_resizer.c
endif

