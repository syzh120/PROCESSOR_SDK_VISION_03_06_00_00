
ifeq ($(FATFS_PROC_TO_USE),ipu1_0)
UC_radar_read_fft_write=yes
endif

ifeq ($(NDK_PROC_TO_USE),ipu1_1)
UC_radar_read_fft_write=yes
endif


ifeq ($(RADAR_BOARD),TDA3XX_AR12_VIB_DAB_BOOSTER)
UC_radar_capture_only=yes
UC_radar_objectdetect_display=yes
UC_radar_objectdetect_null=yes
UC_radar_capture_process=yes
endif
