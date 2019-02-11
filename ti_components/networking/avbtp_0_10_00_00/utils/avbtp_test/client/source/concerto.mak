include $(PRELUDE)
TARGET := avbtp_test_client
TARGETTYPE := exe
CPPSOURCES := $(all-cpp-files)
CFLAGS := -std=c++0x
SYS_STATIC_LIBS := avformat avcodec
LOPT := -pthread
include $(FINALE)
