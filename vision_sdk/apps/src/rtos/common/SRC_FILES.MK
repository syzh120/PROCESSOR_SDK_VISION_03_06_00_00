
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/common

SRCS_$(IPU_PRIMARY_CORE) += \
		chains_main_bios_settings.c \
		chains_main_bios.c \


ifeq ($(A15_TARGET_OS), Bios)
ifneq ($(RADAR_ONLY),yes)
SRCS_$(IPU_PRIMARY_CORE) += \
		chains_main_bios_settings_vision.c \
		chains_main_bios_stereo.c \
		chains_main_bios_avb.c \
		chains_main_bios_multi_cam.c \
		chains_main_bios_single_cam.c \
		chains_main_bios_iss.c \
		chains_main_bios_opencl.c \
		chains_main_bios_misc.c \
		chains_main_bios_vision.c \
		chains_main_bios_rsvp.c \
		chains_main_bios_tidl.c \
		chains_main_bios_cam_radar_combo.c

ifeq ($(OPENVX_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += chains_main_bios_openvx.c
endif

endif
endif

ifeq ($(A15_TARGET_OS), Linux)
ifeq ($(ROBUST_RVC_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += \
		chains_main_robust_rvc.c
else
SRCS_$(IPU_PRIMARY_CORE) += \
		chains_main_linux.c
ifeq ($(EARLY_USECASE_ENABLE), yes)
SRCS_$(IPU_PRIMARY_CORE) += \
		chains_early_usecase.c
endif

INCLUDE_INTERNAL_INTERFACES += radar
INCLUDE_EXTERNAL_INTERFACES += radarLink \
                               radarFirmware
endif
endif

ifeq ($(A15_TARGET_OS), Qnx)
SRCS_$(IPU_PRIMARY_CORE) += \
		chains_main_linux.c
endif
