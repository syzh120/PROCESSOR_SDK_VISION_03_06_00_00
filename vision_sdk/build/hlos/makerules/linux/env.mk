ECHO=@/bin/echo -e

STEP_DEP := \e[34;1m[DEPS]\e[0m
STEP_CC := \e[34;1m[ CC ]\e[0m
STEP_AR := \e[36;1m[ AR ]\e[0m
STEP_LD := \e[36;1m[ LD ]\e[0m
STEP_CONFIGURO := \e[34;1m[CONF]\e[0m
STEP_MAKE := \e[36;1m[MAKE]\e[0m
STEP_UCGEN := \e[35m[UCGN]\e[0m
COLOR_CORE := \e[31m
COLOR_NONE := \e[0m
COLOR_APP := \e[33m
COLOR_MOD := \e[35m
COLOR_FILE := \e[32m
COLOR_FIN := \e[35;1m
COLOR_DATE := \e[37;1m

UCGEN := $(vision_sdk_PATH)/apps/tools/vision_sdk_usecase_gen/bin/vsdk_linux.out

LABEL_CORE_A15 := $(COLOR_CORE)a15_0$(COLOR_NONE)

CP = cp
CMAKE = cmake
CHDIR_SHELL=$(SHELL)
define chdir
	$(eval _D=$(firstword $(1) $(@D)))
	echo $_
	$(info $(MAKE): cd $(_D)) $(eval SHELL = cd $(_D); $(CHDIR_SHELL))
endef
