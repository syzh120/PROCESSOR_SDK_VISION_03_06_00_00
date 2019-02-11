#*******************************************************************************
#* FILE PURPOSE: Lower level makefile for Creating Component Libraries
#*******************************************************************************
#* FILE NAME: lib/common.ae66.mk
#*
#* DESCRIPTION: Defines Source Files, Compilers flags and build rules
#*
#*
#* This is an auto-generated file          
#*******************************************************************************
#

#
# Macro definitions referenced below
#
empty =
space =$(empty) $(empty)
CC = "$(C6X_GEN_INSTALL_DIR)/bin/"cl6x -c -mv6600 --abi=eabi
AC = "$(C6X_GEN_INSTALL_DIR)/bin/"cl6x -c -mv6600 --abi=eabi
ARIN = "$(C6X_GEN_INSTALL_DIR)/bin/"ar6x 
LIBINFO = "$(C6X_GEN_INSTALL_DIR)/bin/libinfo6x"
LD = "$(C6X_GEN_INSTALL_DIR)/bin/"lnk6x --abi=eabi 
CGINCS = $(strip $(subst $(space),\$(space),$(C6X_GEN_INSTALL_DIR)/include))
RTSLIB = -l "$(C6X_GEN_INSTALL_DIR)/lib/undefined"
INCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(subst \,/,$(INCDIR)))))
OBJEXT = oe66
AOBJEXT = se66
INTERNALDEFS =  -Dti_targets_elf_C66 -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep 
INTERNALLINKDEFS =  -o $@ -m $@.map
OBJDIR = ./package/lib/lib/commonae66


#Debug Build options
ifneq (,$(findstring $(DEBUG), yesYES))
  OPTFLAGS = -g
else
  OPTFLAGS = -o3 --symdebug:none
endif



#List the common Files
COMMONC= \
    ./src/common/TI_profile.c\
    ./src/common/TI_test.c\
    ./src/common/TI_memory.c\
    ./src/common/c6x/TI_cache.c

# FLAGS for the common Files
COMMONCFLAGS =  -c -k -mw --strip_coff_underscore $(OPTFLAGS) --mem_model:data=far --legacy

# Make Rule for the common Files
COMMONCOBJS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(COMMONC))

$(COMMONCOBJS): $(OBJDIR)/%.$(OBJEXT): %.c
	-@echo cle66 $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	-$(RM) $@.dep
	$(CC) $(COMMONCFLAGS) $(INTERNALDEFS) $(INCS) -I$(CGINCS) -fc $< 
	-@cp $@.dep $@.pp; \
         $(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
             -e '/^$$/ d' -e 's/$$/ :/' < $@.pp >> $@.dep; \
         $(RM) $@.pp 

#Create Empty rule for dependency
$(COMMONCOBJS):lib\common.ae66.mk
lib\common.ae66.mk:

#Include Depedency for common Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(COMMONCOBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif


lib/common.ae66 : $(COMMONCOBJS)
	@echo archiving $? into $@ ...
	@echo "rq $@ $?">$@.cmd
	$(ARIN) @$@.cmd
	if [ -f $(@D)/common.lib  ]; then $(LIBINFO) -u -o=$(@D)/common.lib $@; else $(LIBINFO) -o=$(@D)/common.lib $@; fi;
