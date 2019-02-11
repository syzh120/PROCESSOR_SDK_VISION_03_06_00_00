

include linksfw_component.mk

linksfw_LIB_LIST_CLEAN = $(addsuffix _clean, $(linksfw_LIB_LIST))

.PHONY : linkfw_libs linkfw_libs_clean $(linksfw_LIB_LIST) $(linksfw_LIB_LIST_CLEAN)

linkfw_libs: $(linksfw_LIB_LIST)

linkfw_libs_clean: $(linksfw_LIB_LIST_CLEAN)

#=================================================================
#Link FW libs
$(linksfw_LIB_LIST):
	$(if $(filter $(SOC), $(subst emptyreplacement,,$($@_SOCLIST))),\
		$(if $(filter a15_0, $(subst emptyreplacement,,$($@_$(SOC)_CORELIST))),\
			$(MAKE) -C $($@_PATH) CORE=a15_0 depend $(COMMAND_SEPERATOR)))
	$(if $(filter $(SOC), $(subst emptyreplacement,,$($@_SOCLIST))),\
		$(if $(filter a15_0, $(subst emptyreplacement,,$($@_$(SOC)_CORELIST))),\
			$(MAKE) -C $($@_PATH) CORE=a15_0 $(COMMAND_SEPERATOR)))
$(linksfw_LIB_LIST_CLEAN):
	$(if $(filter $(SOC), $(subst emptyreplacement,,$($(subst _clean,,$@)_SOCLIST))),\
		$(MAKE) -C $($(subst _clean,,$@)_PATH) clean)

# Nothing beyond this point
