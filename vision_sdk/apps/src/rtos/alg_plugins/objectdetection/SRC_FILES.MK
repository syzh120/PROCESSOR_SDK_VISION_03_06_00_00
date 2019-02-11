
SRCDIR += objectdetection

include $(MODULE_SRC_BASE_PATH)/objectdetection/fpcompute1/SRC_FILES.MK
include $(MODULE_SRC_BASE_PATH)/objectdetection/fpcompute2/SRC_FILES.MK

OBJECT_DRAW_FILES = objectDrawLink_algPlugin.c objectDrawLink_trafficSigns.c objectDrawLink_trafficLights.c

SRCS_arp32_1 += alg_filter2d.c alg_clahe.c
SRCS_c66xdsp_1 += objectDetectionLink_algPlugin.c
SRCS_c66xdsp_1 += objectClassificationLink_algPlugin.c
SRCS_c66xdsp_2 += objectDetectionLink_algPlugin.c
SRCS_c66xdsp_2 += objectClassificationLink_algPlugin.c

SRCS_c66xdsp_1 += $(OBJECT_DRAW_FILES)
SRCS_a15_0 += $(OBJECT_DRAW_FILES)
SRCS_$(IPU_PRIMARY_CORE) += $(OBJECT_DRAW_FILES)
SRCS_ipu1_1 += $(OBJECT_DRAW_FILES)

