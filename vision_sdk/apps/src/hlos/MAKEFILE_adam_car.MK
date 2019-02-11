include $(vision_sdk_PATH)/build/hlos/makerules/linux/env.mk
include $(vision_sdk_PATH)/build/hlos/makerules/linux/components.mk
include $(vision_sdk_PATH)/build/hlos/makerules/linux/functions.mk

# Organization
# "Components" represent things that vsdk is combined with, such as startware, bsp, etc.
#    -> things outside the vision_sdk directory
# "Modules" represent pieces of reused lib code within vision sdk and are put into archives (.a)
#    -> define headers and libraries that we need for compilation and linking
# "Apps" are the top-level piece that is compiled into an executable after linking
#    -> Build into .out files on linux

# @todo:
# - Expand CXXFLAGS support yet again (too much C++ just uses CFLAGS by default, which works but
#     isn't the cleanest)

APPBASEPATH := $(vision_sdk_PATH)/apps/src/hlos/adam_car/apps

CC := $(A15_TOOLCHAIN_PREFIX)gcc
CX := $(A15_TOOLCHAIN_PREFIX)g++
AR := $(A15_TOOLCHAIN_PREFIX)ar
LD := $(A15_TOOLCHAIN_PREFIX)g++

CORE := a15_0
MODNAME := adam_car_linux
OBJ_BASE_DIR := $(DEST_ROOT)/obj/$(MODNAME)/$(PLATFORM)/$(CORE)/$(PROFILE_a15_0)
EXE_BASE_DIR := $(DEST_ROOT)/vision_sdk/bin/$(PLATFORM)
LIB_DIR := $(DEST_ROOT)/lib/$(PLATFORM)/$(CORE)/$(PROFILE_a15_0)

CFLAGS := -Wall -Warray-bounds
CXXFLAGS := -Wall -Warray-bounds

ifeq ($(TREAT_WARNINGS_AS_ERROR),yes)
CFLAGS += -Werror
endif

ifeq ($(CONFIG),debug)
CFLAGS += -g -DDEBUG
CXXFLAGS += -g -DDEBUG
else
CFLAGS += -O3 -mfpu=neon -funsafe-math-optimizations
CXXFLAGS += -O3 -mfpu=neon -funsafe-math-optimizations
endif

PROCLIST := IPU1_0 IPU1_1 IPU2 DSP1 DSP2 EVE1 EVE2 EVE3 EVE4 A15_0
DEFINE := -DA15_TARGET_OS_LINUX -DLINUX_BUILD
DEFINE += $(strip $(foreach proc,$(PROCLIST),$(call TEST_PROC,$(proc))))
DEFINE += $(vision_sdk_CFLAGS)

AR_OPTS := -rc

INCLUDE := -I$(vision_sdk_PATH)
LDFLAGS := -lpthread -lm -L$(LINUX_TARGETFS)/usr/lib -Wl,--rpath-link,$(LINUX_TARGETFS)/usr/lib
LDFLAGS += -L$(LINUX_TARGETFS)/lib -Wl,--rpath-link,$(LINUX_TARGETFS)/lib -lrt
LDFLAGS += -flto -O3 -mfpu=neon -funsafe-math-optimizations

# Initialize these to empty strings so that subfiles append to the right "type"
ALL_APPS :=
ALL_MODULES :=

all: adam_car_app

# Find all submakefiles, which declare apps or modules, and include them here automatically
$(foreach cmd,$(shell find $(vision_sdk_PATH)/apps/src/hlos/adam_car -name Makefile.include),$(eval -include $(cmd)))
$(foreach mod,$(ALL_MODULES),$(eval $(call DECL_MODULE,$(mod))))
$(foreach mod,$(ALL_MODULES),$(eval $(call IMPL_MODULE,$(mod))))
$(foreach app,$(ALL_APPS),$(eval $(call IMPL_APP,$(app))))

# Need to copy this file from configuro; use make to determine when it is out of date
$(vision_sdk_PATH)/hlos/src/osa/include/osa_mem_map.h: $(vision_sdk_PATH)/binaries/$(MAKECONFIG)/obj/vision_sdk/$(PLATFORM)/$(IPU_PRIMARY_CORE)/$(PROFILE_$(IPU_PRIMARY_CORE))/vision_sdk_configuro/osa_mem_map.h
	-cp $(vision_sdk_PATH)/binaries/$(MAKECONFIG)/obj/vision_sdk/$(PLATFORM)/ipu1_0/$(PROFILE_ipu1_0)/vision_sdk_configuro/osa_mem_map.h $(vision_sdk_PATH)/hlos/src/osa/include

adam_car_app: $(addsuffix _app,$(ALL_APPS))
	$(ECHO) "$(COLOR_FIN)[FIN-]$(COLOR_NONE) $(COLOR_DATE)$(shell date)$(COLOR_NONE) - Build completed."

clean: $(addsuffix _app_clean,$(ALL_APPS)) $(addsuffix _mod_clean,$(ALL_MODULES))

$(OBJ_BASE_DIR):
	mkdir -p $(OBJ_BASE_DIR)

$(EXE_BASE_DIR): $(OBJ_BASE_DIR)
	mkdir -p $(EXE_BASE_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)
