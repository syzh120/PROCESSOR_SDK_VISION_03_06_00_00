
SENSOR_DIR = $($(MAKEAPPNAME)_PATH)/src/rtos/iss/src/sensor
SRCDIR += $(SENSOR_DIR)

SRCDIR += $(SENSOR_DIR)/ar0140 $(SENSOR_DIR)/ov10640 $(SENSOR_DIR)/imx224 \
          $(SENSOR_DIR)/ar0132  $(SENSOR_DIR)/ov2775 $(SENSOR_DIR)/ar0143 \
          $(SENSOR_DIR)/imx390 $(SENSOR_DIR)/ar0233

INCDIR += $(SENSOR_DIR)

SRCS_$(IPU_PRIMARY_CORE) += iss_sensors.c \
               iss_sensor_ar0140.c \
               iss_sensor_ar0143.c \
               iss_sensor_ov10640.c \
               iss_sensor_imx224.c \
               iss_sensor_ar0132.c \
               iss_sensor_ov2775.c \
               iss_sensor_imx390.c \
               iss_sensor_ar0233.c

ifeq ($(SOC), tda3xx)
SRCS_$(IPU_PRIMARY_CORE) += \
    iss_sensor_tda3xx.c
endif

ifeq ($(SOC), tda2px)
SRCS_$(IPU_PRIMARY_CORE) += \
    iss_sensor_tda2px.c
endif


