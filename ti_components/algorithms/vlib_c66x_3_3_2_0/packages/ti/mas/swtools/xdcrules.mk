#
#  ======== xdcrules.mk ========
#  definition of XDC rules
#

# If not set in the environment, set XDCOPTIONS to verbose (the 'v' option)
XDCOPTIONS ?= v
XDCARGS :=
DOT :=.
SLASH :=/
COMPONENT :=ti.mas.swtools
COMP=$(subst $(DOT),$(SLASH),$(COMPONENT))
BUILD := -PD

# This command actually performs the build.
# Note that the "-PD ." says "build the package in this directory ("-P ."),
# and all of the packages it depends on ("-D").
all:
%::
	$(XDC_INSTALL_DIR)/xdc XDCARGS="$(XDCARGS)" XDCPATH="$(XDC_PATH)" \
		XDCOPTIONS=$(XDCOPTIONS) $@ $(BUILD) ../../../$(COMP)



