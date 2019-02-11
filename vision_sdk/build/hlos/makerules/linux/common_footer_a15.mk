# (c) Texas Instruments

ifndef $(COMMON_FOOTER_MK)
COMMON_FOOTER_MK = 1

OBJS=$(subst .c,.o, $(FILES) )
OBJSCPP=$(subst .cpp,.o, $(FILESCPP) )


OBJ_DIR=$(OBJ_BASE_DIR)

vpath %.o $(OBJ_DIR)

LIB = $(MODNAME).a

OPENCV_LIBS =
ifeq ($(ENABLE_OPENCV),yes)
ifeq ($(BUILD_OPENCV_SRC),yes)
OPENCV_LIBS +=  $(OpenCV_SRC_PATH)/$(OpenCV_BUILD_PATH)/install/lib/libopencv_imgproc.a
OPENCV_LIBS +=  $(OpenCV_SRC_PATH)/$(OpenCV_BUILD_PATH)/install/lib/libopencv_imgcodecs.a
OPENCV_LIBS +=  $(OpenCV_SRC_PATH)/$(OpenCV_BUILD_PATH)/install/lib/libopencv_imgproc.a
OPENCV_LIBS +=  $(OpenCV_SRC_PATH)/$(OpenCV_BUILD_PATH)/install/lib/libopencv_core.a
OPENCV_LIBS +=  $(OpenCV_PREBUILD_PATH)/libs_linux/libpng.a
OPENCV_LIBS +=  $(OpenCV_PREBUILD_PATH)/libs_linux/libzlib.a
OPENCV_LIBS +=  $(OpenCV_SRC_PATH)/$(OpenCV_BUILD_PATH)/install/lib/libopencv_genericio.a
else
OPENCV_LIBS +=  $(OpenCV_PREBUILD_PATH)/libs_linux/libopencv_imgproc.a
OPENCV_LIBS +=  $(OpenCV_PREBUILD_PATH)/libs_linux/libopencv_imgcodecs.a
OPENCV_LIBS +=  $(OpenCV_PREBUILD_PATH)/libs_linux/libopencv_imgproc.a
OPENCV_LIBS +=  $(OpenCV_PREBUILD_PATH)/libs_linux/libopencv_core.a
OPENCV_LIBS +=  $(OpenCV_PREBUILD_PATH)/libs_linux/libpng.a
OPENCV_LIBS +=  $(OpenCV_PREBUILD_PATH)/libs_linux/libzlib.a
OPENCV_LIBS +=  $(OpenCV_PREBUILD_PATH)/libs_linux/libopencv_genericio.a
endif
OPENCV_LIBS += -ldl
endif

EXE = $(EXE_BASE_DIR)/$(MODNAME).out

SO_LIB= $(EXE_BASE_DIR)/lib$(MODNAME).so
ifneq ("$(wildcard $(LINUX_TARGETFS)/usr/lib/libogles2tools.a)","")
	LIB_SRV= $(LINUX_TARGETFS)/usr/lib/libogles2tools.a
endif

ifdef MODNAME
	ifneq ("$(wildcard $(DEST_ROOT)/appLiblist_$(CORE).txt)","")
		APP_LIB_LIST = $(shell $(CAT) $(DEST_ROOT)/appLiblist_$(CORE).txt)
	endif
	APP_LIB = $(LIB_DIR)/$(MODNAME).a
	ifneq ($(APP_LIB),$(filter $(APP_LIB), $(APP_LIB_LIST)))
		NEW_LIB = $(APP_LIB)
	endif
endif

lib : $(LIB_DIR)/$(LIB)

.c.o:
	@echo \# $(MODNAME): $(PLATFORM): Compiling $<
	$(CC) $(CC_OPTS) $(OPTI_OPTS) $(DEFINE) $(INCLUDE) -o$(OBJ_DIR)/$@ $<

.cpp.o:
	@echo \# $(MODNAME): $(PLATFORM): Compiling $<
	$(CX) $(CX_OPTS) $(OPTI_OPTS) $(DEFINE) $(INCLUDE) -o$(OBJ_DIR)/$@ $<

$(LIB_DIR)/$(LIB) : $(OBJS) $(OBJSCPP)
	@echo \# $(MODNAME): $(PLATFORM): Creating archive $(LIB)
	$(AR)	$(AR_OPTS) $(LIB_DIR)/$(LIB) $(OBJ_DIR)/*.o
ifeq ($(NEW_LIB),$(APP_LIB))
	@echo $(NEW_LIB) >> $(DEST_ROOT)/appLiblist_$(CORE).txt
endif

obj: $(OBJS) $(OBJSCPP)

clean:
	@echo \# $(MODNAME): $(PLATFORM): Deleting temporary files
	-rm -f $(LIB_DIR)/$(LIB)
	-rm -f $(OBJ_DIR)/*.*

depend:
#	@echo \# $(MODNAME): $(PLATFORM): Making Directories, if not already created
	-mkdir -p $(LIB_DIR)
	-mkdir -p $(OBJ_DIR)
	-mkdir -p $(EXE_BASE_DIR)
#	@echo \# $(MODNAME): $(PLATFORM): Building dependancies
	$(CC)	$(DEFINE) $(INCLUDE) $(FILES) $(FILESCPP) -M > MAKEFILE.DEPEND

so:
	@echo \# $(MODNAME): $(PLATFORM): Linking to .so
	$(LD) $(LD_OPTS) -shared -o $(SO_LIB) $(OBJ_DIR)/*.o $(LIBS)
	@echo \# Final shared library $(SO_LIB) !!!
	@echo \#
exe:
	@echo \# $(MODNAME): $(PLATFORM): Linking
	$(LD) $(LD_OPTS) $(LIBS) $(OPENCV_LIBS) $(LIB_SRV) -o$(EXE)
	@echo \# Final executable $(EXE) !!!
	@echo \#

install:


-include MAKEFILE.DEPEND

endif # ifndef $(COMMON_FOOTER_MK)

