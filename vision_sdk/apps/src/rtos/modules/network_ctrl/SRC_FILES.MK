
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/modules/network_ctrl

NETWORK_SRCS = \
		network_ctrl_tsk.c \
		network_ctrl_handle_echo.c \
		network_ctrl_handle_mem_rd.c \
		network_ctrl_handle_qspi_wr.c \
		network_ctrl_handle_mmc_wr_proxy.c \
		network_ctrl_handle_sys_reset.c \
		network_ctrl_handle_mem_save.c \
		network_ctrl_handle_device_comm.c

ifneq ($(RADAR_ONLY),yes)
NETWORK_SRCS += \
		network_ctrl_handle_stereo_calib_image_save.c \
		network_ctrl_handle_stereo_set_params.c \
		network_ctrl_handle_stereo_set_dynamic_params.c \
		network_ctrl_handle_iss_raw_save.c \
		network_ctrl_handle_object_detect_set_dynamic_params.c
endif

SRCS_$(IPU_PRIMARY_CORE) += network_ctrl_handle_mmc_wr.c
SRCS_$(IPU_PRIMARY_CORE) += $(NETWORK_SRCS)
SRCS_a15_0 += $(NETWORK_SRCS)
