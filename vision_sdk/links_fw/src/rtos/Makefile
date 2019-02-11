

include linksfw_component.mk

linksfw_LIB_LIST_CLEAN = $(addsuffix _clean, $(linksfw_LIB_LIST))
linksfw_LIB_LIST_DEPEND = $(addsuffix _depend, $(linksfw_LIB_LIST))

.PHONY : linkfw_libs linkfw_libs_clean linkfw_depend $(linksfw_LIB_LIST) $(linksfw_LIB_LIST_CLEAN) $(linksfw_LIB_LIST_DEPEND)

linkfw_libs: $(linksfw_LIB_LIST)

linkfw_libs_clean: $(linksfw_LIB_LIST_CLEAN)

linkfw_depend: $(linksfw_LIB_LIST_DEPEND)

#=================================================================
#Link FW libs
$(linksfw_LIB_LIST):
	$(if $(filter $(SOC), $(subst emptyreplacement,,$($@_SOCLIST))),\
		$(foreach curCore, $(BUILD_CORE_LIST),\
			$(if $(filter $(curCore), $(subst emptyreplacement,,$($@_$(SOC)_CORELIST))),\
				$(MAKE) -C $($@_PATH) CORE=$(curCore) $(COMMAND_SEPERATOR))))

$(linksfw_LIB_LIST_CLEAN):
	$(if $(filter $(SOC), $(subst emptyreplacement,,$($(subst _clean,,$@)_SOCLIST))),\
		$(foreach curCore, $(BUILD_CORE_LIST),\
			$(if $(filter $(curCore), $(subst emptyreplacement,,$($(subst _clean,,$@)_$(SOC)_CORELIST))),\
				$(MAKE) -C $($(subst _clean,,$@)_PATH) CORE=$(curCore) clean $(COMMAND_SEPERATOR))))

$(linksfw_LIB_LIST_DEPEND):
	$(if $(filter $(SOC), $(subst emptyreplacement,,$($(subst _depend,,$@)_SOCLIST))),\
		$(foreach curCore, $(BUILD_CORE_LIST),\
			$(if $(filter $(curCore), $(subst emptyreplacement,,$($(subst _depend,,$@)_$(SOC)_CORELIST))),\
				$(MAKE) -C $($(subst _depend,,$@)_PATH) CORE=$(curCore) depend $(COMMAND_SEPERATOR))))

# Nothing beyond this point
