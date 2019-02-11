INCDIR += $($(MAKEAPPNAME)_PATH)
SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/iss/src/common

SRCS_$(IPU_PRIMARY_CORE) += iss_utils.c

ifeq ($(ISS_INCLUDE),yes)
SRCS_$(IPU_PRIMARY_CORE) += app_util_iss.c
endif
