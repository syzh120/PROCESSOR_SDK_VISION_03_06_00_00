
SRCDIR += codec_utils/src iva_dec iva_enc

ifeq ($(IVAHD_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += iresman_hdvicp2_fwif.c \
        utils_encdec.c iresman_tiledmemory.c hdvicp2_config.c \
        alg_control.c alg_create.c alg_malloc.c \
        encLink_tsk.c encLink_common.c \
        decLink_tsk.c decLink_common.c \
        encLink_jpeg.c encLink_h264.c \
        decLink_jpeg.c decLink_h264.c
endif