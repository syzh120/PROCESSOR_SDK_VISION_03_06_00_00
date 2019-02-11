#*******************************************************************************
#* FILE PURPOSE: Lower level makefile for Creating Component Libraries
#*******************************************************************************
#* FILE NAME: lib/mathlib.a66e.mk
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
CC = "$(C6X_GEN_INSTALL_DIR)/bin/"cl6x -c -mv6600 -me --abi=coffabi
AC = "$(C6X_GEN_INSTALL_DIR)/bin/"cl6x -c -mv6600 -me --abi=coffabi
ARIN = "$(C6X_GEN_INSTALL_DIR)/bin/"ar6x rq
LIBINFO = "$(C6X_GEN_INSTALL_DIR)/bin/libinfo6x"
LD = "$(C6X_GEN_INSTALL_DIR)/bin/"lnk6x --abi=coffabi 
CGINCS = $(strip $(subst $(space),\$(space),$(C6X_GEN_INSTALL_DIR)/include))
RTSLIB = -l "$(C6X_GEN_INSTALL_DIR)/lib/undefined"
INCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(subst \,/,$(INCDIR)))))
OBJEXT = o66e
AOBJEXT = s66e
INTERNALDEFS =  -Dti_targets_C66_big_endian -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep 
INTERNALLINKDEFS =  -o $@ -m $@.map
OBJDIR = ./package/lib/lib/mathliba66e

#List the kernelc66 Files
KERNELC66C= \
    ./src/atan2dp//c66/atan2dp_c.c\
    ./src/atan2dp/atan2dp_v.c\
    ./src/atan2sp//c66/atan2sp_c.c\
    ./src/atan2sp/atan2sp_v.c\
    ./src/atandp//c66/atandp_c.c\
    ./src/atandp//c66/atandp_v.c\
    ./src/atansp//c66/atansp_c.c\
    ./src/atansp/atansp_v.c\
    ./src/cosdp//c66/cosdp_c.c\
    ./src/cosdp/cosdp_v.c\
    ./src/cossp//c66/cossp_c.c\
    ./src/cossp/cossp_v.c\
    ./src/divdp//c66/divdp_c.c\
    ./src/divdp/divdp_v.c\
    ./src/divsp//c66/divsp_c.c\
    ./src/divsp/divsp_v.c\
    ./src/exp10dp//c66/exp10dp_c.c\
    ./src/exp10dp/exp10dp_v.c\
    ./src/exp10sp//c66/exp10sp_c.c\
    ./src/exp10sp/exp10sp_v.c\
    ./src/exp2dp//c66/exp2dp_c.c\
    ./src/exp2dp/exp2dp_v.c\
    ./src/exp2sp//c66/exp2sp_c.c\
    ./src/exp2sp/exp2sp_v.c\
    ./src/expdp//c66/expdp_c.c\
    ./src/expdp/expdp_v.c\
    ./src/expsp//c66/expsp_c.c\
    ./src/expsp/expsp_v.c\
    ./src/log10dp//c66/log10dp_c.c\
    ./src/log10dp/log10dp_v.c\
    ./src/log10sp//c66/log10sp_c.c\
    ./src/log10sp/log10sp_v.c\
    ./src/log2dp//c66/log2dp_c.c\
    ./src/log2dp/log2dp_v.c\
    ./src/log2sp//c66/log2sp_c.c\
    ./src/log2sp/log2sp_v.c\
    ./src/logdp//c66/logdp_c.c\
    ./src/logdp/logdp_v.c\
    ./src/logsp//c66/logsp_c.c\
    ./src/logsp/logsp_v.c\
    ./src/powdp//c66/powdp_c.c\
    ./src/powdp/powdp_v.c\
    ./src/powsp//c66/powsp_c.c\
    ./src/powsp/powsp_v.c\
    ./src/recipdp//c66/recipdp_c.c\
    ./src/recipdp/recipdp_v.c\
    ./src/recipsp//c66/recipsp_c.c\
    ./src/recipsp/recipsp_v.c\
    ./src/rsqrtdp//c66/rsqrtdp_c.c\
    ./src/rsqrtdp/rsqrtdp_v.c\
    ./src/rsqrtsp//c66/rsqrtsp_c.c\
    ./src/rsqrtsp/rsqrtsp_v.c\
    ./src/sindp//c66/sindp_c.c\
    ./src/sindp/sindp_v.c\
    ./src/sinsp//c66/sinsp_c.c\
    ./src/sinsp/sinsp_v.c\
    ./src/sqrtdp//c66/sqrtdp_c.c\
    ./src/sqrtdp/sqrtdp_v.c\
    ./src/sqrtsp//c66/sqrtsp_c.c\
    ./src/sqrtsp/sqrtsp_v.c\
    ./src/asindp//c66/asindp.c\
    ./src/asindp//c66/asindp_c.c\
    ./src/asindp//c66/asindp_v.c\
    ./src/asinsp//c66/asinsp.c\
    ./src/asinsp//c66/asinsp_c.c\
    ./src/asinsp/asinsp_v.c\
    ./src/acosdp//c66/acosdp.c\
    ./src/acosdp//c66/acosdp_c.c\
    ./src/acosdp//c66/acosdp_v.c\
    ./src/acossp//c66/acossp.c\
    ./src/acossp//c66/acossp_c.c\
    ./src/acossp/acossp_v.c\
    ./src/sinhdp//c66/sinhdp.c\
    ./src/sinhdp//c66/sinhdp_c.c\
    ./src/sinhdp//c66/sinhdp_v.c\
    ./src/sinhsp//c66/sinhsp.c\
    ./src/sinhsp//c66/sinhsp_c.c\
    ./src/sinhsp/sinhsp_v.c\
    ./src/coshdp//c66/coshdp.c\
    ./src/coshdp//c66/coshdp_c.c\
    ./src/coshdp//c66/coshdp_v.c\
    ./src/coshsp//c66/coshsp.c\
    ./src/coshsp//c66/coshsp_c.c\
    ./src/coshsp/coshsp_v.c\
    ./src/tandp//c66/tandp.c\
    ./src/tandp//c66/tandp_c.c\
    ./src/tandp/tandp_v.c\
    ./src/tansp//c66/tansp.c\
    ./src/tansp//c66/tansp_c.c\
    ./src/tansp/tansp_v.c\
    ./src/tanhdp//c66/tanhdp.c\
    ./src/tanhdp//c66/tanhdp_c.c\
    ./src/tanhdp//c66/tanhdp_v.c\
    ./src/tanhsp//c66/tanhsp.c\
    ./src/tanhsp//c66/tanhsp_c.c\
    ./src/tanhsp/tanhsp_v.c\
    ./src/acoshdp//c66/acoshdp.c\
    ./src/acoshdp//c66/acoshdp_c.c\
    ./src/acoshdp/acoshdp_v.c\
    ./src/acoshsp//c66/acoshsp.c\
    ./src/acoshsp//c66/acoshsp_c.c\
    ./src/acoshsp/acoshsp_v.c\
    ./src/asinhdp//c66/asinhdp.c\
    ./src/asinhdp//c66/asinhdp_c.c\
    ./src/asinhdp/asinhdp_v.c\
    ./src/asinhsp//c66/asinhsp.c\
    ./src/asinhsp//c66/asinhsp_c.c\
    ./src/asinhsp/asinhsp_v.c\
    ./src/atanhdp//c66/atanhdp.c\
    ./src/atanhdp//c66/atanhdp_c.c\
    ./src/atanhdp//c66/atanhdp_v.c\
    ./src/atanhsp//c66/atanhsp.c\
    ./src/atanhsp//c66/atanhsp_c.c\
    ./src/atanhsp/atanhsp_v.c

# FLAGS for the kernelc66 Files
KERNELC66CFLAGS =  -c -k -mw  -o3 --symdebug:none --mem_model:data=far -dOVERRIDE_RTS=0 

# Make Rule for the kernelc66 Files
KERNELC66COBJS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(KERNELC66C))

$(KERNELC66COBJS): $(OBJDIR)/%.$(OBJEXT): %.c
	-@echo cl66e $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	-$(RM) $@.dep
	$(CC) $(KERNELC66CFLAGS) $(INTERNALDEFS) $(INCS) -I$(CGINCS) -fc $< 
	-@cp $@.dep $@.pp; \
         $(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
             -e '/^$$/ d' -e 's/$$/ :/' < $@.pp >> $@.dep; \
         $(RM) $@.pp 

#Create Empty rule for dependency
$(KERNELC66COBJS):lib\mathlib.a66e.mk
lib\mathlib.a66e.mk:

#Include Depedency for kernelc66 Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(KERNELC66COBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif

#List the kernelc66 Files
KERNELC66ASM= \
    ./src/atan2dp//c66/atan2dp.asm\
    ./src/atan2sp//c66/atan2sp.asm\
    ./src/atandp//c66/atandp.asm\
    ./src/atansp//c66/atansp.asm\
    ./src/cosdp//c66/cosdp.asm\
    ./src/cossp//c66/cossp.asm\
    ./src/divdp//c66/divdp.asm\
    ./src/divsp//c66/divsp.asm\
    ./src/exp10dp//c66/exp10dp.asm\
    ./src/exp10sp//c66/exp10sp.asm\
    ./src/exp2dp//c66/exp2dp.asm\
    ./src/exp2sp//c66/exp2sp.asm\
    ./src/expdp//c66/expdp.asm\
    ./src/expsp//c66/expsp.asm\
    ./src/log10dp//c66/log10dp.asm\
    ./src/log10sp//c66/log10sp.asm\
    ./src/log2dp//c66/log2dp.asm\
    ./src/log2sp//c66/log2sp.asm\
    ./src/logdp//c66/logdp.asm\
    ./src/logsp//c66/logsp.asm\
    ./src/powdp//c66/powdp.asm\
    ./src/powsp//c66/powsp.asm\
    ./src/recipdp//c66/recipdp.asm\
    ./src/recipsp//c66/recipsp.asm\
    ./src/rsqrtdp//c66/rsqrtdp.asm\
    ./src/rsqrtsp//c66/rsqrtsp.asm\
    ./src/sindp//c66/sindp.asm\
    ./src/sinsp//c66/sinsp.asm\
    ./src/sqrtdp//c66/sqrtdp.asm\
    ./src/sqrtsp//c66/sqrtsp.asm

# FLAGS for the kernelc66 Files
KERNELC66ASMFLAGS =  -ea.s -c -k  --mem_model:data=far -dOVERRIDE_RTS=0 

# Make Rule for the kernelc66 Files
KERNELC66ASMOBJS = $(patsubst %.asm, $(OBJDIR)/%.$(OBJEXT), $(KERNELC66ASM))

$(KERNELC66ASMOBJS): $(OBJDIR)/%.$(OBJEXT): %.asm
	-@echo asm66e $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	$(AC) $(KERNELC66ASMFLAGS) $(INTERNALDEFS) $(INCS) -I$(CGINCS) -fa $< 

#Create Empty rule for dependency
$(KERNELC66ASMOBJS):lib\mathlib.a66e.mk
lib\mathlib.a66e.mk:

#Include Depedency for kernelc66 Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(KERNELC66ASMOBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif


lib/mathlib.a66e : $(KERNELC66COBJS) $(KERNELC66ASMOBJS)
	@echo archiving $? into $@ ...
	$(ARIN) $@ $?
	if [ -f $(@D)/mathlib.lib  ]; then $(LIBINFO) -u -o=$(@D)/mathlib.lib $@; else $(LIBINFO) -o=$(@D)/mathlib.lib $@; fi;
