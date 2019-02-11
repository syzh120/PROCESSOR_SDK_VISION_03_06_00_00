#*******************************************************************************
#* FILE PURPOSE: Lower level makefile for Creating Component Libraries
#*******************************************************************************
#* FILE NAME: lib/common.a86l.mk
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
CC = gcc -c
AC = gcc -c
ARIN = ar
LD = g++
CGINCS =
RTSLIB =
INCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(subst \,/,$(INCDIR)))))
OBJEXT = o86l
AOBJEXT = s86l
INTERNALDEFS = -std=c99 -DHOST_EMULATION -m32
INTERNALLINKDEFS =  -map:$@.map -pdb:$@.pdb -out:$@ 
OBJDIR = ./package/lib/lib/commona86l


#Debug Build options
ifneq (,$(findstring $(DEBUG), yesYES))
  CC += -ggdb -ggdb3 -gdwarf-2
  INTERNALLINKDEFS += -DEBUG
else
  CC += -O3
endif


INTERNALLINKDEFS +=

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
COMMONHOSTCFLAGS =  -DTMS320C66X -D_TMS320C6600 -DLITTLE_ENDIAN_HOST -D_LITTLE_ENDIAN -D_HOST_BUILD -Icommon/c6xsim

# Make Rule for the commonHost Files
COMMONHOSTCOBJS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(COMMONHOSTC))

$(COMMONHOSTCOBJS): $(OBJDIR)/%.$(OBJEXT): %.c
	-@echo cl86l $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	$(CC) $(COMMONHOSTCFLAGS) $(INTERNALDEFS) $(INCS) -MMD -MF $@.dep -MT '$@' $< -o $@

#Create Empty rule for dependency
$(COMMONHOSTCOBJS):lib\common.a86l.mk
lib\common.a86l.mk:

#Include Depedency for commonHost Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(COMMONHOSTCOBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif


lib/common.a86l : $(COMMONHOSTCOBJS)
	@echo archiving $? into $@ ...
	@echo "-rscu $@ $^">$@.cmd
	$(ARIN) @$@.cmd
