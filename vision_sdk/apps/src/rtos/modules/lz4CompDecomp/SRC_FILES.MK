SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/modules/lz4CompDecomp

ifeq ($(PROC_DSP1_INCLUDE),yes)
SRCS_c66xdsp_1  += lz4CompDecomp_tsk.c
SRCS_c66xdsp_1  += lz4.c
endif

ifeq ($(PROC_DSP2_INCLUDE),yes)
SRCS_c66xdsp_2  += lz4CompDecomp_tsk.c
SRCS_c66xdsp_2  += lz4.c
endif

SRCS_$(IPU_PRIMARY_CORE) += lz4CompDecomp_tsk.c
SRCS_$(IPU_PRIMARY_CORE) += lz4.c

