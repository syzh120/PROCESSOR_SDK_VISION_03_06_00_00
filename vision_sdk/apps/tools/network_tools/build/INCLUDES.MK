# (c) Texas Instruments

ifndef $(INCLUDES_MK)
INCLUDES_MK = 1

COMMON_INC=-I$(BASE_DIR)/../common/inc -I../inc -I../priv -I. -I$(NSP_INCLUDE_PATH)

endif # ifndef $(INCLUDES_MK)

