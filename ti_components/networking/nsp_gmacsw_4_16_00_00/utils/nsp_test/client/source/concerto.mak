include $(PRELUDE)
TARGET := nsp_test_client
TARGETTYPE := exe
CPPSOURCES := $(all-cpp-files)
CFLAGS := -std=c++0x
LOPT := -pthread
include $(FINALE)
