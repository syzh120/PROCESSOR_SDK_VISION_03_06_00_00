
include ./Rules.mak

NUM_CPUS ?= $(shell grep -c ^processor /proc/cpuinfo)

.PHONY: all clean checkxdc env.sh

env.sh:
	@echo "export XDC_VERSION=$(XDC_VERSION)"       > $@
	@echo "export XDC_ROOT=$(XDC_ROOT)"             >> $@
	@echo "export NDK_VERSION=$(NDK_VERSION)"       >> $@
	@echo "export NDK_ROOT=$(NDK_ROOT)"             >> $@
	@echo "export BIOS_VERSION=$(BIOS_VERSION)"     >> $@
	@echo "export BIOS_ROOT=$(BIOS_ROOT)"           >> $@
	@echo "export UIA_VERSION=$(UIA_VERSION)"       >> $@
	@echo "export UIA_ROOT=$(UIA_ROOT)"             >> $@
	@echo "export COMPILER_DIR=$(COMPILER_DIR)"     >> $@
	@echo "export TOOLS_DIR=$(TOOLS_DIR)"           >> $@
	@echo "export TIARMCGT_ROOT=$(TIARMCGT_ROOT)"   >> $@
	@echo "export GCC_ROOT=$(GCC_ROOT)"             >> $@
	@echo "export CGT6X_ROOT=$(CGT6X_ROOT)"         >> $@
	@echo "export EDMA3_ROOT=$(EDMA3_ROOT)"         >> $@
	@echo "export EDMA3_VERSION=$(EDMA3_VERSION)"   >> $@
	@chmod a+x env.sh

all: checkxdc
	$(XDC_ROOT)/xdc --xdcpath="$(BIOS_ROOT)/packages" --jobs $(NUM_CPUS) -P packages/ti/nsp/drv/

clean: checkxdc
	$(XDC_ROOT)/xdc --xdcpath="$(BIOS_ROOT)/packages" --jobs $(NUM_CPUS) clean -P packages/ti/nsp/drv/
	rm -f env.sh

checkxdc:
	@if [ ! -d $(XDC_ROOT) ]; then \
        echo "XDC was not found at $(XDC_ROOT). Please define the proper path in XDC_ROOT!"; \
        exit 1; \
    fi
