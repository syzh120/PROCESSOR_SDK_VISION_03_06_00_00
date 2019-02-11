#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************


##############################################################
DSP_TOOLS ?= "C:\Program Files\Texas Instruments\ccsv5\tools\compiler\c6000_7.4.2"
##############################################################


##############################################################
CC=$(DSP_TOOLS)\bin\cl6x.exe
LD=$(DSP_TOOLS)\bin\lnk6x.exe
AR=$(DSP_TOOLS)\bin\ar6x.exe
##############################################################


##############################################################
BUILDDIR =  .\build
LIBDIR =  .\lib
OUTDIR =  .\elf_out

CFLAGS = -mv6740 -O0 -g
CFLAGS += -I $(DSP_TOOLS)\include -I $(BUILDDIR)
CFLAGS += --obj_directory=$(BUILDDIR) --temp_directory=$(BUILDDIR)

LDFLAGS = -cr -x

ARFLAGS = r
##############################################################


##############################################################
CFILES:= $(subst /,\,$(CFILES))

CFILESK:= $(filter %.k,$(CFILES))
CFILESC:= $(filter %.c,$(CFILES))
CFILESASM:= $(filter %.asm,$(CFILES))
CFILES:= $(CFILESK) $(CFILESC) $(CFILESASM)

OFILES:= $(addsuffix .obj, $(basename $(notdir $(CFILES))))
OFILES:= $(OFILES:%.obj=$(BUILDDIR)/%.obj)

CFILESK_C:= $(CFILESK:%.k=%.c)
CFILESK_C+= $(CFILESK:%.k=%.h)
##############################################################


##############################################################
# 'all' rules
all : $(BUILDDIR) $(OUTFILE)

$(OUTFILE): $(OFILES)

$(OFILES): $(CFILES) $(HFILES)
	$(CC) $(CFLAGS) -c $(CFILES)

$(BUILDDIR):
	mkdir $(BUILDDIR)

%.obj : %.asm
	$(CC) $(CFLAGS) --no_compress -c $^ --output_file=$@ 
##############################################################


##############################################################
# clean rules
.IGNORE: clean
clean: 
	@rmdir/s/q "$(BUILDDIR)"
	@rmdir/s/q "$(LIBDIR)"
	@rmdir/s/q "$(OUTDIR)"
	@del/f/q "$(OUTFILE)" $(CFILESK_C)
##############################################################


##############################################################
.PHONY: libfile
libfile: $(LIBDIR) $(OFILES) $(ARFILES)
	@$(AR) $(ARFLAGS) $(OUTFILE) $(OFILES) $(ARFILES)

$(LIBDIR):
	mkdir $(LIBDIR) || cd $(LIBDIR)
##############################################################


##############################################################
.PHONY: outfile
outfile: $(OUTDIR) $(OFILES) $(LDFILES)
	$(LD) $(LDFLAGS) --output_file=$(OUTFILE) $(OFILES) $(LDFILES) -m "$(OUTFILE)".map

$(OUTDIR):
	mkdir $(OUTDIR) || cd $(OUTDIR)
##############################################################



