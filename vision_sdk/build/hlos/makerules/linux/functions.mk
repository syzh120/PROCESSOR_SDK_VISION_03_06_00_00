# File of makefile functions/templates which are used to generate rules based on the information
# provided in the Makefile.include files. These are typically not called by "users" or developers
# who are working with vision SDK, but are used internally to implement the build system itself,
# for example they are called from MAKEFILE_adam_car.mk, currently

# Arguments
# 1) Name of processor to test for (matching a PROC_x_INCLUDE value
# IPU1_0 IPU1_1 IPU2 DSP1 DSP2 EVE1 EVE2 EVE3 EVE4 A15_0 is one possible list of processor names
define TEST_PROC
$(if $(filter yes,$(PROC_$1_INCLUDE)),-DPROC_$1_INCLUDE)
endef

# Arguments:
# 1: app name
define IMPL_APP
$1_app_obj_dir := $(OBJ_BASE_DIR)/$1_app

$1_app_FILES := $(wildcard $(APPBASEPATH)/$1/*.c)
$1_app_FILESCPP := $(wildcard $(APPBASEPATH)/$1/*.cpp)
$1_app_FILESH := $(wildcard $(APPBASEPATH)/$1/*.h)
$1_app_UCG_OUTPUTS := $$(addprefix $(APPBASEPATH)/$1/,$$(addsuffix _priv.c,$$($1_app_USECASES)))
$1_app_UCG_DEPS := $$($1_app_UCG_OUTPUTS) $$(addprefix $(APPBASEPATH)/$1/,$$(addsuffix _priv.h,$$($1_app_USECASES)))
$1_app_UCG_IMGS := $$(addprefix $(APPBASEPATH)/$1/,$$(addsuffix _img.txt,$$($1_app_USECASES)) $$(addsuffix .jpg,$$($1_app_USECASES)))
$1_app_UCG_INPUTS := $$(addprefix $(APPBASEPATH)/$1/,$$(addsuffix .txt,$$($1_app_USECASES)))

$1_app_COBJECTS := $$(addprefix $$($1_app_obj_dir)/,$$(notdir $$($1_app_FILES:.c=.o)))
$1_app_CPPOBJECTS := $$(addprefix $$($1_app_obj_dir)/,$$(notdir $$($1_app_FILESCPP:.cpp=.o)))
$1_app_OBJECTS := $$($1_app_COBJECTS) $$($1_app_CPPOBJECTS)
$1_app_MODULES := $$(sort $$(call MAP_TO_NAME,$$($1_app_MODULE_DEP),_mod_ALL_MODULES))
$1_app_MODULE_ARCHIVES := $$(addsuffix _mod.a,$$(addprefix $(LIB_DIR)/,$$($1_app_MODULES)))

$1_app_MODULE_CFLAGS := $$(call MAP_TO_NAME,$$($1_app_MODULES),_mod_ALL_MODULE_CFLAGS)
$1_app_ALL_COMPONENTS := $$(sort $$($1_app_COMPONENT_DEP) $$(call MAP_TO_NAME,$$($1_app_MODULES),_mod_ALL_COMPONENTS))
$1_app_COMPONENT_CFLAGS := $$(call MAP_TO_NAME,$$($1_app_ALL_COMPONENTS),_component_CFLAGS)
$1_app_CFLAGS += $$(sort -I$(APPBASEPATH)/$1 $$($1_app_COMPONENT_CFLAGS) $$($1_app_MODULE_CFLAGS))

$1_app_MODULE_LDFLAGS := $$(call MAP_TO_NAME,$$($1_app_MODULES),_mod_LDFLAGS)
$1_app_COMPONENT_LDFLAGS :=$$(call MAP_TO_NAME,$$($1_app_ALL_COMPONENTS),_component_LDFLAGS)
$1_app_LDFLAGS += $(LDFLAGS) $$($1_app_MODULE_LDFLAGS) $$($1_app_COMPONENT_LDFLAGS)

$$($1_app_obj_dir):
	mkdir -p $$@

$(APPBASEPATH)/$1/.$1.d : $$($1_app_FILES) $$($1_app_FILESCPP) $$($1_app_FILESH) $$($1_app_UCG_DEPS)
	$(ECHO) "$(STEP_DEP) $(LABEL_CORE_A15) $(COLOR_APP)$1$(COLOR_NONE)"
	$(CC) $(DEFINE) $(INCLUDE) $$($1_app_CFLAGS) $$($1_app_FILES) $$($1_app_FILESCPP) -M \
    | sed -e "s,^\(\S\),$$($1_app_obj_dir)/\1," > $(APPBASEPATH)/$1/.$1.d

-include $(APPBASEPATH)/$1/.$1.d

$1_COPTS := $(CFLAGS) $(DEFINE) $(INCLUDE) $$($1_app_CFLAGS)
$1_CPPOPTS := $(CXXFLAGS) $(DEFINE) $(INCLUDE) $$($1_app_CFLAGS)

$$(eval $$(call BUILD_EACH_WITH_RULE,BUILD_APP_CC_RULE,$$($1_app_COBJECTS),$$($1_app_FILES),$$($1_COPTS),$1))
$$(eval $$(call BUILD_EACH_WITH_RULE,BUILD_APP_CPP_RULE,$$($1_app_CPPOBJECTS),$$($1_app_FILESCPP),$$($1_CPPOPTS),$1))
$$(eval $$(call BUILD_EACH_WITH_RULE,BUILD_APP_USECASE,$$($1_app_UCG_OUTPUTS),$$($1_app_UCG_INPUTS),$1))

$(EXE_BASE_DIR)/$1_app.out : $$($1_app_OBJECTS) $$($1_app_MODULE_ARCHIVES) | $(EXE_BASE_DIR)
	$(ECHO) "$(STEP_LD) $(LABEL_CORE_A15) $(COLOR_APP)$1$(COLOR_NONE)"
	$(LD) $$($1_app_OBJECTS) -Wl,--start-group $$($1_app_MODULE_ARCHIVES) $$($1_app_LDFLAGS) -Wl,--end-group -o $(EXE_BASE_DIR)/$1_app.out

$1_app : $(EXE_BASE_DIR)/$1_app.out

$1_app_clean:
	rm -f $(APPBASEPATH)/$1/.$1.d
	rm -f $$($1_app_UCG_DEPS)
	rm -f $$($1_app_UCG_IMGS)
	rm -rf $$($1_app_obj_dir)
	rm -f $(EXE_BASE_DIR)/$1_app.out

endef

# Arguments:
# 1) Object file, full path
# 2) Source file, full path
# 3) CFLAGS to use (including all options)
# 4) App name for status display
define BUILD_APP_CC_RULE
$1 : $2 | $($4_app_obj_dir)
	$(ECHO) "$(STEP_CC) $(LABEL_CORE_A15) $(COLOR_APP)$4$(COLOR_NONE) $(COLOR_FILE)$$(notdir $2)$(COLOR_NONE)"
	$(CC) $3 -Wa,-ahsln=$(1:.o=.s) -c -o $1 $2

endef

# Arguments:
# 1) Object file, full path
# 2) Source file, full path
# 3) CFLAGS to use (including all options)
# 4) App name for status display
define BUILD_APP_CPP_RULE
$1 : $2 | $($4_app_obj_dir)
	$(ECHO) "$(STEP_CC) $(LABEL_CORE_A15) $(COLOR_APP)$4$(COLOR_NONE) $(COLOR_FILE)$$(notdir $2)$(COLOR_NONE)"
	$(CX) $3 -Wa,-ahsln=$(1:.o=.s) -c -o $1 $2

endef

# Arguments:
# 1) C source file, full path
# 2) Matching .txt input to usecasegen, full path
# 3) App name for status display
define BUILD_APP_USECASE
$1 : $2 $(UCGEN)
	$(ECHO) "$(STEP_UCGEN) $(LABEL_CORE_A15) $(COLOR_APP)$3$(COLOR_NONE) $(COLOR_FILE)$$(notdir $2)$(COLOR_NONE)"
	$(UCGEN) -file -img $2 -path $(APPBASEPATH)/$3

endef

# Arguments:
# 1) Object file, full path
# 2) Source file, full path
# 3) CFLAGS to use (including all options)
# 4) Module name for status display
define BUILD_MOD_CC_RULE
$1 : $2 | $($4_mod_obj_dir)
	$(ECHO) "$(STEP_CC) $(LABEL_CORE_A15) $(COLOR_MOD)$4$(COLOR_NONE) $(COLOR_FILE)$$(notdir $2)$(COLOR_NONE)"
	$(CC) $3 -Wa,-ahsln=$(1:.o=.s) -c -o $1 $2

endef

# Arguments:
# 1) Object file, full path
# 2) Source file, full path
# 3) CFLAGS to use (including all options)
# 4) Module name for status display
define BUILD_MOD_CPP_RULE
$1 : $2 | $($4_mod_obj_dir)
	$(ECHO) "$(STEP_CC) $(LABEL_CORE_A15) $(COLOR_MOD)$4$(COLOR_NONE) $(COLOR_FILE)$$(notdir $2)$(COLOR_NONE)"
	$(CX) $3 -Wa,-ahsln=$(1:.o=.s) -c -o $1 $2

endef

# Arguments
# 1) Function to call for each, which takes arguments: target, prereq, build opts, name for display
# 2) List of targets/object files
# 3) List of prereq/source files, one per object
# 4) Build options to pass to sub-function
# 5) Name being built (app or module)
define BUILD_EACH_WITH_RULE
TOTAL := $$(words $2)
COUNTER := $$(shell seq $$(TOTAL))
$$(foreach ii,$$(COUNTER),$$(eval $$(call $1,$$(word $$(ii),$2),$$(word $$(ii),$3),$4,$5)))

endef

define MAP_TO_NAME
$(foreach name,$1,$($(name)$2))
endef

# This declares a module and sets up the recusively expanded variables for dependencies
# Arguments
# 1) Module name
define DECL_MODULE
$1_mod_obj_dir := $$(OBJ_BASE_DIR)/$1_mod
$1_mod_INTERNAL_CFLAGS += $$(addprefix -I,$$($1_mod_PATHS))
$1_mod_FILES := $$(foreach path,$$($1_mod_PATHS),$$(wildcard $$(path)/*.c))
$1_mod_FILES_CPP := $$(foreach path,$$($1_mod_PATHS),$$(wildcard $$(path)/*.cpp))

$1_mod_ALL_COMPONENTS = $$($1_mod_COMPONENT_DEP) $$(call MAP_TO_NAME,$$($1_mod_MODULE_DEP),_mod_ALL_COMPONENTS)
$1_mod_ALL_MODULE_CFLAGS = $$($1_mod_CFLAGS) $$(call MAP_TO_NAME,$$($1_mod_MODULE_DEP),_mod_ALL_MODULE_CFLAGS)
$1_mod_ALL_MODULES = $1 $$(call MAP_TO_NAME,$$($1_mod_MODULE_DEP),_mod_ALL_MODULES)

$$($1_mod_obj_dir):
	mkdir -p $$@

endef

# This constructs the actual rules for building a module and exports information that an app needs
# to link against a module (+ all dependencies without listing them)
# Arguments
# 1) Module name
define IMPL_MODULE
$1_mod_COMPONENT_CFLAGS := $$(call MAP_TO_NAME,$$($1_mod_ALL_COMPONENTS),_component_CFLAGS)
$1_mod_CONCRETE_CFLAGS := $$(sort $$($1_mod_INTERNAL_CFLAGS) $$($1_mod_ALL_MODULE_CFLAGS) $$($1_mod_COMPONENT_CFLAGS))

$1_COBJECTS := $$(addprefix $$($1_mod_obj_dir)/,$$(notdir $$($1_mod_FILES:.c=.o)))
$1_CPPOBJECTS := $$(addprefix $$($1_mod_obj_dir)/,$$(notdir $$($1_mod_FILES_CPP:.cpp=.o)))
$1_OBJECTS := $$($1_COBJECTS) $$($1_CPPOBJECTS)
$1_COPTS := $(CFLAGS) $(DEFINE) $(INCLUDE) $$($1_mod_CONCRETE_CFLAGS)
$1_CPPOPTS := $(CXXFLAGS) $(DEFINE) $(INCLUDE) $$($1_mod_CONCRETE_CFLAGS)

$$(eval $$(call BUILD_EACH_WITH_RULE,BUILD_MOD_CC_RULE,$$($1_COBJECTS),$$($1_mod_FILES),$$($1_COPTS),$1))
$$(eval $$(call BUILD_EACH_WITH_RULE,BUILD_MOD_CPP_RULE,$$($1_CPPOBJECTS),$$($1_mod_FILES_CPP),$$($1_CPPOPTS),$1))

$(LIB_DIR)/$1_mod.d: $$($1_mod_FILES) $$($1_mod_FILES_CPP) | $(LIB_DIR)
	$(ECHO) "$(STEP_DEP) $(LABEL_CORE_A15) $(COLOR_MOD)$1$(COLOR_NONE)"
	mkdir -p $$($1_mod_obj_dir)
	$(CC) $$($1_COPTS) $$($1_mod_FILES) $$($1_mod_FILES_CPP) -M \
    | sed -e "s,^\(\S\),$$($1_mod_obj_dir)/\1," > $$@

-include $(LIB_DIR)/$1_mod.d

$(LIB_DIR)/$1_mod.a: $$($1_OBJECTS) | $(LIB_DIR)
	$(ECHO) "$(STEP_AR) $(LABEL_CORE_A15) $(COLOR_MOD)$1$(COLOR_NONE)"
	$(AR) $(AR_OPTS) $(LIB_DIR)/$1_mod.a $$($1_OBJECTS)

$1_mod_clean:
	rm -f $(LIB_DIR)/$1_mod.d
	rm -f $$($1_OBJECTS)
	rm -f $(LIB_DIR)/$1_mod.a

endef
