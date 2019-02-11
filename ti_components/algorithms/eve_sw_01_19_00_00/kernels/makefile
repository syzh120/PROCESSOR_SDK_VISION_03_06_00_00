#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************
all:
	@echo .
	@echo ======== IP KERNELS KERNELC =================
	gmake -f makefile_generatelib KERNEL_MODE=KERNELC FILE_LIST=kernel_priv_list.txt LIB_NAME=libeveprivkernels.eve.lib
	@echo .
	@echo ======== IP KERNELS NATC =================
	gmake -f makefile_generatelib KERNEL_MODE=NATC FILE_LIST=kernel_priv_list.txt LIB_NAME=libeveprivnatckernels.eve.lib
	@echo .
	@echo ======== NON IP KERNELS KERNELC =================
	gmake -f makefile_generatelib KERNEL_MODE=KERNELC FILE_LIST=kernel_list.txt LIB_NAME=libevekernels.eve.lib
	@echo .
	@echo ======== NON IP KERNELS NATC =================
	gmake -f makefile_generatelib KERNEL_MODE=NATC FILE_LIST=kernel_list.txt LIB_NAME=libevenatckernels.eve.lib
	@echo .
	@echo ======== MERGE =================
	gmake -f makefile_mergelib

.IGNORE: clean
clean:
	@echo .
	@echo ======== IP and non IP KERNELS KERNELC =================
	gmake -f makefile_generatelib KERNEL_MODE=KERNELC FILE_LIST=kernel_priv_list.txt LIB_NAME=libeveprivkernels.eve.lib clean
	@echo .
	@echo ======== IP and non IP KERNELS NATC =================
	gmake -f makefile_generatelib KERNEL_MODE=NATC FILE_LIST=kernel_priv_list.txt LIB_NAME=libeveprivnatckernels.eve.lib clean
	@echo .
	@echo ======== NON IP KERNELS KERNELC =================
	gmake -f makefile_generatelib KERNEL_MODE=KERNELC FILE_LIST=kernel_list.txt LIB_NAME=libevekernels.eve.lib clean
	@echo .
	@echo ======== NON IP KERNELS NATC =================
	gmake -f makefile_generatelib KERNEL_MODE=NATC FILE_LIST=kernel_list.txt LIB_NAME=libevenatckernels.eve.lib clean
