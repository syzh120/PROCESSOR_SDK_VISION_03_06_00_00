
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/tidl_OD_radar_process_display

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_tidlOD_radarProcess_display_priv.c \
        chains_tidlOD_radarProcess_display.c

INCLUDE_INTERNAL_INTERFACES += radar
INCLUDE_EXTERNAL_INTERFACES += radarLink     \
                               radarFirmware \
                               evealg
        