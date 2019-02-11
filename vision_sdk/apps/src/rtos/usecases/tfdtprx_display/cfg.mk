ifeq ($(NDK_PROC_TO_USE), none)
    $(error NDK_PROC_TO_USE should be enabled to run this use-case)
endif
ifeq ($(NDK_PROC_TO_USE), a15_0)
    NEED_PROC_A15_0=yes
endif
ifeq ($(NDK_PROC_TO_USE), ipu1_0)
    NEED_PROC_IPU1_0=yes
endif
ifeq ($(NDK_PROC_TO_USE), ipu1_1)
    NEED_PROC_IPU1_1=yes
endif
