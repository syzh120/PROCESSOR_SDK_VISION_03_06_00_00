#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************


##############################################################
ARP32_TOOLS ?= "C:\Program Files\Texas Instruments\ARP32_tools"
##############################################################

##############################################################
CC = $(ARP32_TOOLS)\bin\cl-arp32.exe
LD = $(ARP32_TOOLS)\bin\lnk-arp32.exe
AR = $(ARP32_TOOLS)\bin\ar-arp32.exe
##############################################################

##############################################################
# host compiler (must be C++)
HOSTCC = "g++"
HOSTCC_FLAGS = -g -fpermissive -I $(ARP32_TOOLS)\include\vcop
HOSTCC_FLAGS += -D VCOP_HOST_EMULATION
##############################################################

##############################################################
BUILDDIR =  ..\build
OUTDIR =  ..\elf_out

CFLAGS = -kh -kv -g --silicon_version=v210  --gen_func_subsections 
CFLAGS += -I $(ARP32_TOOLS)\include -I $(ARP32_TOOLS)\include\vcop -I $(BUILDDIR)
CFLAGS += --obj_directory=$(BUILDDIR) --temp_directory=$(BUILDDIR)

LDFLAGS = -cr -x
LDFLAGS+= -l $(ARP32_TOOLS)\lib\rtsarp32_v200.lib

ARFLAGS = r
##############################################################


##############################################################
TEMPINC1 ="..\..\..\..\starterware\inc"
TEMPINC2 ="..\..\..\..\starterware\inc\baseaddress\vayu\eve"

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.k))
CFILES+= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))
HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

CFILES:= $(subst /,\,$(CFILES))

CFILESK:= $(filter %.k,$(CFILES))
CFILESC:= $(filter %.c,$(CFILES))
CFILESASM:= $(filter %.asm,$(CFILES))
CFILES:= $(CFILESK) $(CFILESC) $(CFILESASM)

OFILES:= $(addsuffix .obj, $(basename $(notdir $(CFILES))))
OFILES:= $(OFILES:%.obj=$(BUILDDIR)/%.obj)
##############################################################


##############################################################
# 'host' rules
host: a.out

a.out: $(FILE).c
	$(HOSTCC) $(HOSTCC_FLAGS) $(FILE).c

# 'hostrun' rules
hostrun: a.out
	a.out

# 'target' rules
target : $(BUILDDIR) $(OUTDIR) $(OUTFILE)

$(OUTFILE): $(OFILES) $(LDFILES)
	$(LD) $(LDFLAGS) --output_file=$(OUTFILE) $(OFILES) -I$(TEMPINC1) -I$(TEMPINC2)  $(LDFILES) -m "$(OUTFILE)".map
    
$(OFILES): $(CFILES) $(HFILES)
	$(CC) $(CFLAGS) -c $(CFILES) -I$(TEMPINC1) -I$(TEMPINC2) 

$(BUILDDIR):
	(cd $(BUILDDIR)) || (mkdir $(BUILDDIR))

$(OUTDIR):
	(cd $(OUTDIR)) || (mkdir $(OUTDIR))

%.obj : %.asm
	$(CC) $(CFLAGS) --no_compress -c $^ --output_file=$@ 
##############################################################


##############################################################
# clean rules
.IGNORE: clean
clean: 
	if exist a.exe del a.exe
	@rmdir/s/q "$(BUILDDIR)"
	@rmdir/s/q "$(OUTDIR)"
##############################################################




