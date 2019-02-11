#  ============================================================================
#  (C) Copyright 2016-2017 Texas Instruments, Inc.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#    Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#    Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the
#    distribution.
#
#    Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#  ============================================================================

XDC = $(XDC_INSTALL_PATH)/xdc

# check if we need to limit the Build to limitted SOCS
ifdef LIMIT_BOARDS
  BOARD_LIST_ALL = $(filter $(LIMIT_BOARDS), $($(COMP)_BOARDLIST))
else
  BOARD_LIST_ALL = $($(COMP)_BOARDLIST)
endif

# check if we need to limit the Build to limitted SOCS
ifdef LIMIT_SOCS
  SOC_LIST_ALL = $(filter $(LIMIT_SOCS), $($(COMP)_SOCLIST))
else
  SOC_LIST_ALL = $($(COMP)_SOCLIST)
endif

# check if we need to limit the build to limitted cores
ifdef LIMIT_CORES
  CORE_LIST_ALL = $(filter $(LIMIT_CORES), $($(COMP)_$(SOC)_CORELIST))
else
  CORE_LIST_ALL = $($(COMP)_$(SOC)_CORELIST)
endif

PRUCORE_LIST = pru_0 pru_1

ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),soc)
    lib_BOARD_SOC_LIST_ALL = $(addsuffix _lib, $(SOC_LIST_ALL))
endif
ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),board)
    lib_BOARD_SOC_LIST_ALL = $(addsuffix _lib, $(BOARD_LIST_ALL))
endif
lib_CORE_LIST_ALL = $(addsuffix _lib, $(filter-out $(PRUCORE_LIST),$(CORE_LIST_ALL)))
lib_LIB_ENDIAN_LIST = $(addsuffix _lib, $(LIB_ENDIAN_LIST))
ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),soc)
    lib_BOARD_SOC_LIST_ALL_CLEAN = $(addsuffix _lclean, $(SOC_LIST_ALL))
endif
ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),board)
    lib_BOARD_SOC_LIST_ALL_CLEAN = $(addsuffix _lclean, $(BOARD_LIST_ALL))
endif
lib_CORE_LIST_ALL_CLEAN = $(addsuffix _lclean, $(filter-out $(PRUCORE_LIST),$(CORE_LIST_ALL)))
lib_LIB_ENDIAN_LIST_CLEAN = $(addsuffix _lclean, $(LIB_ENDIAN_LIST))

ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),soc)
    app_lib_BOARD_SOC_LIST_ALL = $(addsuffix _app_lib, $(SOC_LIST_ALL))
endif
ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),board)
    app_lib_BOARD_SOC_LIST_ALL = $(addsuffix _app_lib, $(BOARD_LIST_ALL))
endif
app_lib_CORE_LIST_ALL = $(addsuffix _app_lib, $(CORE_LIST_ALL))
app_lib_LIB_ENDIAN_LIST = $(addsuffix _app_lib, $(LIB_ENDIAN_LIST))
ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),soc)
    app_lib_BOARD_SOC_LIST_ALL_CLEAN = $(addsuffix _app_lclean, $(SOC_LIST_ALL))
endif
ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),board)
    app_lib_BOARD_SOC_LIST_ALL_CLEAN = $(addsuffix _app_lclean, $(BOARD_LIST_ALL))
endif
app_lib_CORE_LIST_ALL_CLEAN = $(addsuffix _app_lclean, $(CORE_LIST_ALL))
app_lib_LIB_ENDIAN_LIST_CLEAN = $(addsuffix _app_lclean, $(LIB_ENDIAN_LIST))

app_BOARD_LIST_ALL = $(addsuffix _app, $(BOARD_LIST_ALL))
app_CORE_LIST_ALL = $(addsuffix _app, $(CORE_LIST_ALL))
app_LIB_ENDIAN_LIST = $(addsuffix _app, $(LIB_ENDIAN_LIST))
app_BOARD_LIST_ALL_CLEAN = $(addsuffix _aclean, $(BOARD_LIST_ALL))
app_CORE_LIST_ALL_CLEAN = $(addsuffix _aclean, $(CORE_LIST_ALL))
app_LIB_ENDIAN_LIST_CLEAN = $(addsuffix _aclean, $(LIB_ENDIAN_LIST))

firm_SOC_LIST_ALL = $(addsuffix _firm, $(SOC_LIST_ALL))
firm_CORE_LIST_ALL = $(addsuffix _firm, $(filter $(PRUCORE_LIST),$(CORE_LIST_ALL)))
firm_HOST_CORE_LIST = $(addsuffix _firm, $(filter-out $(PRUCORE_LIST),$(CORE_LIST_ALL)))
firm_VERSION_LIST_ALL = $(addsuffix _firm, $(PRU_VERSION_LIST))
firm_SOC_LIST_ALL_CLEAN = $(addsuffix _fclean, $(SOC_LIST_ALL))
firm_CORE_LIST_ALL_CLEAN = $(addsuffix _fclean, $(filter $(PRUCORE_LIST),$(CORE_LIST_ALL)))
firm_HOST_CORE_LIST_CLEAN = $(addsuffix _fclean, $(filter-out $(PRUCORE_LIST),$(CORE_LIST_ALL)))
firm_VERSION_LIST_ALL_CLEAN = $(addsuffix _fclean, $(PRU_VERSION_LIST))

comp_PKG_LIST_ALL = $($(COMP)_EXAMPLE_LIST) $($(COMP)_DUP_EXAMPLE_LIST) $($(COMP)_APP_LIB_LIST) $($(COMP)_LIB_LIST) $($(COMP)_FIRM_LIST)
comp_LIB_LIST_CLEAN = $(addsuffix _clean, $($(COMP)_LIB_LIST))
comp_APP_LIB_LIST_CLEAN = $(addsuffix _clean, $($(COMP)_APP_LIB_LIST))
comp_EXAMPLE_LIST_CLEAN = $(addsuffix _clean, $($(COMP)_EXAMPLE_LIST))
comp_FIRM_LIST_CLEAN = $(addsuffix _clean, $($(COMP)_FIRM_LIST))
comp_PKG_LIST_ALL_CLEAN = $(addsuffix _clean, $(comp_PKG_LIST_ALL))
comp_PKG_LIST_PACKAGE = $(addsuffix _package, $(comp_PKG_LIST_ALL))

.PHONY : apps appcores app_clean clean_appcores \
         lib libcores lib_allendians lib_clean clean_libcores clean_lib_allendians  \
         all comp_libs comp_libs_clean examples examples_clean clean package $(comp_PKG_LIST_ALL) \
         doxygen release tar lib lib_clean \
         $(lib_BOARD_SOC_LIST_ALL) $(lib_CORE_LIST_ALL) $(lib_LIB_ENDIAN_LIST) $(lib_BOARD_SOC_LIST_ALL_CLEAN) \
         $(lib_CORE_LIST_ALL_CLEAN) $(lib_LIB_ENDIAN_LIST_CLEAN) \
         $(app_lib_BOARD_SOC_LIST_ALL) $(app_lib_CORE_LIST_ALL) $(app_lib_LIB_ENDIAN_LIST) \
	 $(firm_SOC_LIST_ALL) $(firm_CORE_LIST_ALL) $(firm_VERSION_LIST_ALL) $(firm_VERSION_LIST_ALL_CLEAN) $(firm_SOC_LIST_ALL_CLEAN) $(firm_CORE_LIST_ALL_CLEAN) \
         $(app_lib_BOARD_SOC_LIST_ALL_CLEAN) $(app_lib_CORE_LIST_ALL_CLEAN) $(app_lib_LIB_ENDIAN_LIST_CLEAN) \
         $(app_BOARD_LIST_ALL) $(app_CORE_LIST_ALL) $(app_BOARD_LIST_ALL_CLEAN) $(app_CORE_LIST_ALL_CLEAN)
		 

all: lib firm app_lib apps 
 
clean: lib_clean firm_clean app_lib_clean app_clean

ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),soc)
$(lib_BOARD_SOC_LIST_ALL):
	$(MAKE) libcores SOC=$(subst _lib,,$@)
endif
ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),board)
$(lib_BOARD_SOC_LIST_ALL):
	$(MAKE) libcores BOARD=$(subst _lib,,$@)
endif

$(lib_CORE_LIST_ALL):
	$(MAKE) lib_allendians CORE=$(subst _lib,,$@) BUILD_PROFILE_$(subst _lib,,$@)=$(BUILD_PROFILE)

$(lib_LIB_ENDIAN_LIST):
	$(MAKE) comp_libs ENDIAN=$(subst _lib,,$@)

ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),soc)
$(lib_BOARD_SOC_LIST_ALL_CLEAN):
	$(MAKE) clean_libcores SOC=$(subst _lclean,,$@)
endif
ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),board)
$(lib_BOARD_SOC_LIST_ALL_CLEAN):
	$(MAKE) clean_libcores BOARD=$(subst _lclean,,$@)
endif

$(lib_CORE_LIST_ALL_CLEAN):
	$(MAKE) clean_lib_allendians CORE=$(subst _lclean,,$@) BUILD_PROFILE_$(subst _lclean,,$@)=$(BUILD_PROFILE)

$(lib_LIB_ENDIAN_LIST_CLEAN):
	$(MAKE) comp_libs_clean ENDIAN=$(subst _lclean,,$@)

ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),soc)
$(app_lib_BOARD_SOC_LIST_ALL):
	$(MAKE) app_libcores SOC=$(subst _app_lib,,$@)
endif
ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),board)
$(app_lib_BOARD_SOC_LIST_ALL):
	$(MAKE) app_libcores BOARD=$(subst _app_lib,,$@)
endif
$(firm_SOC_LIST_ALL):
	$(MAKE) firmcores SOC=$(subst _firm,,$@)

$(firm_CORE_LIST_ALL):
	$(MAKE) firm_allhostcores CORE=$(subst _firm,,$@)

$(firm_HOST_CORE_LIST):
	$(MAKE) firm_allversion HOSTCORE=$(subst _firm,,$@)

$(firm_VERSION_LIST_ALL):
	$(MAKE) comp_firm PRUVERSION=$(subst _firm,,$@)

$(app_lib_CORE_LIST_ALL):
	$(MAKE) app_lib_allendians CORE=$(subst _app_lib,,$@) BUILD_PROFILE_$(subst _app_lib,,$@)=$(BUILD_PROFILE)
$(firm_SOC_LIST_ALL_CLEAN):
	$(MAKE) clean_firmcores SOC=$(subst _fclean,,$@)

$(app_lib_LIB_ENDIAN_LIST):
	$(MAKE) comp_app_libs ENDIAN=$(subst _app_lib,,$@)
$(firm_CORE_LIST_ALL_CLEAN):
	$(MAKE) clean_firm_allhostcores CORE=$(subst _fclean,,$@)

$(firm_HOST_CORE_LIST_CLEAN):
	$(MAKE) clean_firm_allversion HOSTCORE=$(subst _fclean,,$@)

$(firm_VERSION_LIST_ALL_CLEAN):
	$(MAKE) comp_firm_clean PRUVERSION=$(subst _fclean,,$@)

ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),soc)
$(app_lib_BOARD_SOC_LIST_ALL_CLEAN):
	$(MAKE) clean_app_libcores SOC=$(subst _app_lclean,,$@)
endif
ifeq ($(lib_$(COMP)_BUILD_DEPENDENCY),board)
$(app_lib_BOARD_SOC_LIST_ALL_CLEAN):
	$(MAKE) clean_app_libcores BOARD=$(subst _app_lclean,,$@)
endif

$(app_lib_CORE_LIST_ALL_CLEAN):
	$(MAKE) clean_app_lib_allendians CORE=$(subst _app_lclean,,$@) BUILD_PROFILE_$(subst _app_lclean,,$@)=$(BUILD_PROFILE)

$(app_lib_LIB_ENDIAN_LIST_CLEAN):
	$(MAKE) comp_app_libs_clean ENDIAN=$(subst _app_lclean,,$@)

$(app_BOARD_LIST_ALL):
	$(MAKE) appcores BOARD=$(subst _app,,$@)

$(app_CORE_LIST_ALL):
	$(MAKE) examples CORE=$(subst _app,,$@) BUILD_PROFILE_$(subst _app,,$@)=$(BUILD_PROFILE)

$(app_BOARD_LIST_ALL_CLEAN):
	$(MAKE) clean_appcores BOARD=$(subst _aclean,,$@)
	
$(app_CORE_LIST_ALL_CLEAN):
	$(MAKE) examples_clean CORE=$(subst _aclean,,$@) BUILD_PROFILE_$(subst _aclean,,$@)=$(BUILD_PROFILE)

xdc_meta:
	$(XDC) XDCBUILDCFG=config_mk.bld

xdc_meta_clean:
	$(XDC) clean XDCBUILDCFG=config_mk.bld

doxygen:
ifeq ($($(COMP)_DOXYGEN_SUPPORT),yes)
	$(ECHO) Creating Doxygen API guide ...
	@doxygen docs/Doxyfile
else
	$(ECHO) No Doxygen Support available ...
endif

clean_doxygen:
ifeq ($($(COMP)_DOXYGEN_SUPPORT),yes)
	$(ECHO) cleaned Doxygen API guide ...
	$(RM) -rf docs/doxygen
else
	$(ECHO) No Doxygen Support available ...
endif

tar: lib firm xdc_meta doxygen
	$(ECHO) Creating the Release Tar ball for $(COMP)...
	$(XDC) clean   XDCBUILDCFG=config_mk.bld	
	$(XDC) release XDCBUILDCFG=config_mk.bld
	$(ECHO) please check $(COMP)/packages folder for the release tarball
	
lib: $(lib_BOARD_SOC_LIST_ALL)

libcores: $(lib_CORE_LIST_ALL)

lib_allendians: $(lib_LIB_ENDIAN_LIST)

lib_clean: $(lib_BOARD_SOC_LIST_ALL_CLEAN)

clean_libcores:$(lib_CORE_LIST_ALL_CLEAN)

clean_lib_allendians: $(lib_LIB_ENDIAN_LIST_CLEAN)

app_lib: $(app_lib_BOARD_SOC_LIST_ALL)
firm: $(firm_SOC_LIST_ALL)

app_libcores: $(app_lib_CORE_LIST_ALL)
firmcores: $(firm_CORE_LIST_ALL)

app_lib_allendians: $(app_lib_LIB_ENDIAN_LIST)
firm_allhostcores: $(firm_HOST_CORE_LIST)
firm_allversion: $(firm_VERSION_LIST_ALL)
app_lib_clean: $(app_lib_BOARD_SOC_LIST_ALL_CLEAN)
firm_clean: $(firm_SOC_LIST_ALL_CLEAN)

clean_app_libcores:$(app_lib_CORE_LIST_ALL_CLEAN)
clean_firmcores: $(firm_CORE_LIST_ALL_CLEAN)
clean_firm_allversion: $(firm_VERSION_LIST_ALL_CLEAN)
clean_app_lib_allendians: $(app_lib_LIB_ENDIAN_LIST_CLEAN)
clean_firm_allhostcores: $(firm_HOST_CORE_LIST_CLEAN)

apps: $(app_BOARD_LIST_ALL)

appcores: $(app_CORE_LIST_ALL)

app_clean: $(app_BOARD_LIST_ALL_CLEAN)

clean_appcores: $(app_CORE_LIST_ALL_CLEAN)
	
comp_all: lib_allendians app_lib_allendians examples firm_allhostcores

comp_clean: clean_lib_allendians clean_app_lib_allendians examples_clean clean_firm_allhostcores

comp_libs: $($(COMP)_LIB_LIST)

comp_libs_clean: $(comp_LIB_LIST_CLEAN)

comp_app_libs: $($(COMP)_APP_LIB_LIST)
comp_firm: $($(COMP)_FIRM_LIST)

comp_app_libs_clean: $(comp_APP_LIB_LIST_CLEAN)
comp_firm_clean: $(comp_FIRM_LIST_CLEAN)

examples: $($(COMP)_EXAMPLE_LIST)

examples_clean: $(comp_EXAMPLE_LIST_CLEAN)

package: $(comp_PKG_LIST_PACKAGE)

release: lib tar firm

#=================================================================
#COMP libs app_libs and apps
$(comp_PKG_LIST_ALL):
	$(if $(filter $(SOC), $(subst emptyreplacement,,$($@_SOCLIST))),\
	    $(if $(filter $(CORE), $(subst emptyreplacement,,$($@_$(SOC)_CORELIST))),\
	        $(if $(filter yes, $(subst emptyreplacement,,$($@_XDC_CONFIGURO))),\
	            $(MAKE) -C $($@_PATH) $($@_MAKEFILE) xdc_configuro,),),\
	$(if $(filter $(BOARD), $(subst emptyreplacement,,$($@_BOARDLIST))),\
	    $(if $(filter $(CORE), $(subst emptyreplacement,,$($@_$(SOC)_CORELIST))),\
	        $(if $(filter yes, $(subst emptyreplacement,,$($@_XDC_CONFIGURO))),\
	            $(MAKE) -C $($@_PATH) $($@_MAKEFILE) xdc_configuro,),),))
	$(if $(filter $(SOC), $(subst emptyreplacement,,$($@_SOCLIST))),\
	    $(if $(filter $(CORE), $(subst emptyreplacement,,$($@_$(SOC)_CORELIST))),\
	        $(MAKE) -C $($@_PATH) $($@_MAKEFILE),$(ECHO) Nothing to be done for $(SOC) $(CORE) $@),\
	$(if $(filter $(BOARD), $(subst emptyreplacement,,$($@_BOARDLIST))),\
	    $(if $(filter $(CORE), $(subst emptyreplacement,,$($@_$(SOC)_CORELIST))),\
	        $(MAKE) -C $($@_PATH) $($@_MAKEFILE),$(ECHO) Nothing to be done for $(BOARD) $(SOC) $(CORE) $@),$(ECHO) Nothing to be done for $(SOC) $@))

$(comp_PKG_LIST_ALL_CLEAN):
	$(if $(filter $(SOC), $(subst emptyreplacement,,$($(subst _clean,,$@)_SOCLIST))),\
	        $(MAKE) -C $($(subst _clean,,$@)_PATH) $($(subst _clean,,$@)_MAKEFILE) clean,\
	$(if $(filter $(BOARD), $(subst emptyreplacement,,$($(subst _clean,,$@)_BOARDLIST))),\
	        $(MAKE) -C $($(subst _clean,,$@)_PATH) $($(subst _clean,,$@)_MAKEFILE) clean,))

$(comp_PKG_LIST_PACKAGE):
	$(if $(filter $(SOC), $(subst emptyreplacement,,$($(subst _package,,$@)_SOCLIST))),\
	        $(MAKE) -C $($(subst _package,,$@)_PATH) $($(subst _package,,$@)_MAKEFILE) package,\
	$(if $(filter $(BOARD), $(subst emptyreplacement,,$($(subst _package,,$@)_BOARDLIST))),\
	        $(MAKE) -C $($(subst _package,,$@)_PATH) $($(subst _package,,$@)_MAKEFILE) package,$(ECHO) Nothing to be done for $(SOC) $(subst _package,,$@)))

#Below is used only for checking c++ build errors during development, not to be used for any other purpose
cplusplus_build:
	$(MAKE) all BUILD_PROFILE=debug CPLUSPLUS_BUILD=yes

# Nothing beyond this point
