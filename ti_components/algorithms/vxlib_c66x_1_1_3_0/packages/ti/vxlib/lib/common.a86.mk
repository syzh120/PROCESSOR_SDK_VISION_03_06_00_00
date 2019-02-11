#*******************************************************************************
#* FILE PURPOSE: Lower level makefile for Creating Component Libraries
#*******************************************************************************
#* FILE NAME: lib/common.a86.mk
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
CC = cl.exe -nologo -c -DWIN32 /EHsc /W3 /wd4068 /DWIN32_LEAN_AND_MEAN /D_CRT_SECURE_NO_DEPRECATE
AC = cl.exe -nologo -c
ARIN = lib.exe 
LD = link.exe 
CGINCS = $(strip $(subst $(space),\$(space),$(MSVC_GEN_INSTALL_DIR)/VC/include))
RTSLIB = -libpath:"$(MSVC_GEN_INSTALL_DIR)/VC/lib" -libpath:"$(MSVC_GEN_INSTALL_DIR)/Common7/IDE"
INCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(subst \,/,$(INCDIR)))))
OBJEXT = o86
AOBJEXT = s86
INTERNALDEFS =  -Dmicrosoft_targets_VC98 -Dxdc_target_types__=microsoft/targets/std.h -Fo$@ 
INTERNALLINKDEFS =  -map:$@.map -pdb:$@.pdb -out:$@ 
OBJDIR = ./package/lib/lib/commona86


#Debug Build options
ifneq (,$(findstring $(DEBUG), yesYES))
  CC += /Od /MDd /Gm /Zi /RTC1
  INTERNALLINKDEFS += /DEBUG
else
  CC += /Ox /MD
endif


INTERNALLINKDEFS += /MACHINE:X86

#List the commonHost Files
COMMONHOSTC= \
    ./src/common/TI_profile.c\
    ./src/common/TI_test.c\
    ./src/common/TI_memory.c\
    ./src/common/c6x/TI_cache.c\
    ./src/common/c6xsim/C6xSimulator.c\
    ./src/common/c6xsim/c66_ag_intrins.c\
    ./src/common/c6xsim/c66_data_sim.c

# FLAGS for the commonHost Files
COMMONHOSTCFLAGS =  -Ot -Zi -DTMS320C66X -D_TMS320C6600 -DLITTLE_ENDIAN_HOST -D_LITTLE_ENDIAN -D_HOST_BUILD -Icommon/c6xsim

# Make Rule for the commonHost Files
COMMONHOSTCOBJS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(COMMONHOSTC))

$(COMMONHOSTCOBJS): $(OBJDIR)/%.$(OBJEXT): %.c
	-@echo cl86 $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	$(CC) $(COMMONHOSTCFLAGS) $(INTERNALDEFS) $(INCS) -I$(CGINCS) $< 

#Create Empty rule for dependency
$(COMMONHOSTCOBJS):lib\common.a86.mk
lib\common.a86.mk:

#Include Depedency for commonHost Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(COMMONHOSTCOBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif


lib/common.a86 : $(COMMONHOSTCOBJS)
	@echo archiving $? into $@ ...
	@echo "-nologo -out:$@ $^">$@.cmd
	$(ARIN) @$@.cmd
