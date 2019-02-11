# (c) Texas Instruments

ifndef $(COMMON_FOOTER_MK)
COMMON_FOOTER_MK = 1

OBJS=$(subst .c,.o, $(FILES) )

OBJ_DIR=$(OBJ_BASE_DIR)/$(MODULE)/$(CONFIG)

vpath %.o $(OBJ_DIR)

LIB = $(MODULE).a

ifeq ($(BUILD_OS),Linux)
EXE_EXT = out
else
EXE_EXT = exe
endif

EXE = $(EXE_BASE_DIR)/$(CONFIG)/$(MODULE).$(EXE_EXT)

.c.o:
	@echo  $(MODULE): Compiling $<
	$(CC) $(CC_OPTS) $(OPTI_OPTS) $(DEFINE) $(INCLUDE) -o$(OBJ_DIR)/$@ $<


lib : $(LIB_DIR)/$(LIB)

$(LIB_DIR)/$(LIB) : $(OBJS)
	@echo  $(MODULE): Creating archive $(LIB)
	$(AR)	$(AR_OPTS) $(LIB_DIR)/$(LIB) $(OBJ_DIR)/*.o

obj: $(OBJS)

clean:
	@echo $(MODULE): Deleting temporary files
	-rm -f $(LIB_DIR)/$(LIB)
	-rm -f $(OBJ_DIR)/*.*

depend:
	@echo $(MODULE): Making Directories, if not already created
	-mkdir -p $(LIB_DIR)
	-mkdir -p $(OBJ_DIR)
	-mkdir -p $(EXE_BASE_DIR)
	@echo $(MODULE): Building dependancies
	$(CC)	$(CC_OPTS) $(DEFINE) $(INCLUDE) $(FILES) -M > MAKEFILE.DEPEND

exe:
	@echo $(MODULE): Linking
	$(LD) -o$(EXE) $(LIBS) $(LD_OPTS)
	@echo Final executable $(EXE) !!!

install:


-include MAKEFILE.DEPEND

endif # ifndef $(COMMON_FOOTER_MK)

