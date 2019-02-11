
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/srv_calibration
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/srv_calibration/srv_calib_usecase_iss
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/srv_calibration/srv_calib_usecase_vip
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/srv_calibration/srv_calib_usecase_csi2Cal
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/srv_calibration/srv_calib_usecase_avb
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/usecases/srv_calibration/srv_calib_usecase_csi2Cal_issRsz

SRCS_$(IPU_PRIMARY_CORE) += \
        chains_srvCalibration_Display.c \
        chains_srvCalibration_vip_priv.c \
        chains_srvCalibration_csi2Cal_priv.c \
        chains_srvCalibration_avb_priv.c

ifeq ($(ISS_INCLUDE),yes)
    SRCS_$(IPU_PRIMARY_CORE) += chains_srvCalibration_iss_priv.c chains_srvCalibration_csi2Cal_issRsz_priv.c
endif
