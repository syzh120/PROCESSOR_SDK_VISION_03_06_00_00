
ifeq ($(FATFS_PROC_TO_USE),ipu1_0)
UC_radar_read_fft_write=yes
endif

ifeq ($(NDK_PROC_TO_USE),ipu1_1)
UC_radar_read_fft_write=yes
endif

