SRCDIR += $(vision_sdk_PATH)/apps/src/rtos/radar/src/alg_plugins/alg_fxns/radardraw

SRC_RADAR_DRAW = radarDraw.c radarDraw_priv.c

SRCS_c66xdsp_1 += $(SRC_RADAR_DRAW)
SRCS_c66xdsp_2 += $(SRC_RADAR_DRAW)
SRCS_a15_0 += $(SRC_RADAR_DRAW)
SRCS_ipu1_0 += $(SRC_RADAR_DRAW)
