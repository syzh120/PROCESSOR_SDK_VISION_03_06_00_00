SRCDIR += openvx

ifeq ($(OPENVX_INCLUDE),yes)
SRCS_ipu1_0 += openvx_algPlugin.c openvx.c
endif

