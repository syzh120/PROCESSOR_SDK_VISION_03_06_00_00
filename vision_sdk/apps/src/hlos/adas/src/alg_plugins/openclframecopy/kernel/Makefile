CL_FILES = $(foreach dir, ./, $(wildcard $(dir)/*.cl))
CL_OFILES = $(addsuffix .dsp_h, $(basename $(CL_FILES)))

%.dsp_h : %.cl
	echo Compiling OpenCL file $<
	$(CLOCL) -t $<

all: $(CL_OFILES)
