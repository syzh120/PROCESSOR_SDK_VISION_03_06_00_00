INCDIR += $(mathlib_PATH)/packages/ti/mathlib
INCDIR += $(mathlib_PATH)/packages
SRCDIR += sceneobstruction

SRCS_c66xdsp_1 += sceneObstructionDetectLink_algPlugin.c 
SRCS_$(IPU_PRIMARY_CORE) += sceneObstructionDetectLink_algPlugin.c
