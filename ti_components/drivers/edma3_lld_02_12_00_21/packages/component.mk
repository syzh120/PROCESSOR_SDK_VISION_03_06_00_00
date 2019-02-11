# File: component.mk
#       This file is component include make file of OMX.

# List of variables set in this file and their purpose:
# <mod>_RELPATH        - This is the relative path of the module, typically from
#                        top-level directory of the package
# <mod>_PATH           - This is the absolute path of the module. It derives from
#                        absolute path of the top-level directory (set in env.mk)
#                        and relative path set above
# <mod>_INCLUDE        - This is the path that has interface header files of the
#                        module. This can be multiple directories (space separated)
# <mod>_PKG_LIST       - Names of the modules (and sub-modules) that are a part
#                        part of this module, including itself.
# <mod>_PLATFORM_DEPENDENCY - "yes": means the code for this module depends on
#                             platform and the compiled obj/lib has to be kept
#                             under <platform> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no platform dependent code and hence
#                             the obj/libs are not kept under <platform> dir.
# <mod>_CORE_DEPENDENCY     - "yes": means the code for this module depends on
#                             core and the compiled obj/lib has to be kept
#                             under <core> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no core dependent code and hence
#                             the obj/libs are not kept under <core> dir.
# <mod>_APP_STAGE_FILES     - List of source files that belongs to the module
#                             <mod>, but that needs to be compiled at application
#                             build stage (in the context of the app). This is
#                             primarily for link time configurations or if the
#                             source file is dependent on options/defines that are
#                             application dependent. This can be left blank or
#                             not defined at all, in which case, it means there
#                             no source files in the module <mod> that are required
#                             to be compiled in the application build stage.
#

# List of modules under EDMA3 LLD
edma3_lld_COMP_LIST_c6xdsp = edma3_lld_rm edma3_lld_drv

# List of examples under EDMA3 LLD
edma3_lld_EXAMPLES_LIST = edma3_drv_ti816x-evm_m3_example edma3_drv_c6748-evm_674_example \
                          edma3_drv_da830-evm_674_example edma3_drv_omapl138-evm_674_example \
                          edma3_drv_ti816x-evm_674_example \
                          edma3_drv_ti816x_sim_sample  \
                          edma3_drv_ti814x-evm_674_example edma3_drv_ti814x-evm_a8_example \
                          edma3_drv_tci6608-sim_66_example edma3_drv_tci6608-sim_66_be_example  \
                          edma3_drv_tci6616-sim_66_example edma3_drv_tci6616-sim_66_be_example  \
                          edma3_drv_tci6638k2k-sim_66_example edma3_drv_tci6638k2k-sim_66_be_example  \
                          edma3_drv_c6670-evm_66_example edma3_drv_c6670-evm_66_be_example  \
                          edma3_drv_c6678-evm_66_example edma3_drv_c6678-evm_66_be_example  \
                          edma3_drv_c6657-evm_66_example edma3_drv_c6657-evm_66_be_example  \
                          edma3_drv_c66ak2e-evm_66_example edma3_drv_c66ak2e-evm_66_be_example  \
                          edma3_drv_tci6638k2k-evm_66_example edma3_drv_tci6638k2k-evm_66_be_example  \
                          edma3_drv_tci6630k2l-evm_66_example edma3_drv_tci6630k2l-evm_66_be_example  \
                          edma3_drv_tci6636k2h-evm_66_example edma3_drv_tci6636k2h-evm_66_be_example  \
                          edma3_drv_tci66ak2g02-evm_66_example edma3_drv_tci66ak2g02-evm_66_be_example  \
                          edma3_drv_tci6638k2k-evm_a15_example \
                          edma3_drv_tci6636k2h-evm_a15_example \
                          edma3_drv_tci66ak2g02-evm_a15_example \
                          edma3_drv_am335x-evm_a8_example \
                          edma3_drv_am437x-evm_a9_example \
                          edma3_drv_omapl138-evm_arm9_example edma3_drv_omap4-evm_64t_example

# List of libraries



ifeq ($(PLATFORM),)
PLATFORM = am572x-evm am571x-evm dra72x-evm tda2ex-evm tda3xx-evm tda2xx-evm am335x-evm am437x-evm ti816x-evm ti814x-evm c6a811x-evm c6670-evm c6678-evm c6748-evm da830-evm omapl138-evm tci6608-sim tci6616-sim c6657-evm c66ak2e-evm tci6638k2k-evm tci6630k2l-evm tci6638k2k-sim tci6636k2h-evm tci66ak2g02-evm
endif

ifeq ($(TARGET),)
TARGET = 674 m3 a8 64p 66 m4 a15 eve
edma3_lld_LIBS_ALL = edma3_lld_rm_generic
endif

tda2xx-evm_supported_targets = m4 a15 66 eve
tda2xx-evm_m4_cores = m4
tda2xx-evm_a15_cores = a15host
tda2xx-evm_66_cores = c6xdsp
tda2xx-evm_eve_cores = eve
tda2xx-evm_m4_format_support = ELF
tda2xx-evm_a15_format_support = ELF
tda2xx-evm_66_format_support = ELF
tda2xx-evm_eve_format_support = ELF
#tda2xx-evm_profiles = debug release
tda2xx-evm_m4_addn_params = "IPUCORE=1" "IPUCORE=0"

tda3xx-evm_supported_targets = m4 66 eve
tda3xx-evm_m4_cores = m4
tda3xx-evm_66_cores = c6xdsp
tda3xx-evm_eve_cores = eve
tda3xx-evm_m4_format_support = ELF
tda3xx-evm_66_format_support = ELF
tda3xx-evm_eve_format_support = ELF

dra72x-evm_supported_targets = a15 m4 66
dra72x-evm_a15_cores = a15host
dra72x-evm_m4_cores = m4
dra72x-evm_66_cores = c6xdsp
dra72x-evm_a15_format_support = ELF
dra72x-evm_m4_format_support = ELF
dra72x-evm_66_format_support = ELF

tda2ex-evm_supported_targets = a15 m4 66
tda2ex-evm_a15_cores = a15host
tda2ex-evm_m4_cores = m4
tda2ex-evm_66_cores = c6xdsp
tda2ex-evm_a15_format_support = ELF
tda2ex-evm_m4_format_support = ELF
tda2ex-evm_66_format_support = ELF

am572x-evm_supported_targets = a15 m4 66
am572x-evm_a15_cores = a15host
am572x-evm_m4_cores = m4
am572x-evm_66_cores = c6xdsp
am572x-evm_a15_format_support = ELF
am572x-evm_m4_format_support = ELF
am572x-evm_66_format_support = ELF

am571x-evm_supported_targets = a15 m4 66
am571x-evm_a15_cores = a15host
am571x-evm_m4_cores = m4
am571x-evm_66_cores = c6xdsp
am571x-evm_a15_format_support = ELF
am571x-evm_m4_format_support = ELF
am571x-evm_66_format_support = ELF

#Prepare library list to build from the PLATFORM and TARGET
ifeq ($(PLATFORM),generic)
edma3_lld_LIBS_ALL = edma3_lld_rm_generic
else
edma3_lld_LIBS_ALL += edma3_lld_lib_target $(foreach plat, $(PLATFORM),$(foreach targ,$(TARGET),edma3_lld_$(plat)_$(targ)_libs))
endif

#Prepare Example list from PLATFORM and TARGET
ifeq ($(ENDIAN),big)
edma3_lld_EXAMPLES_LIST = $(foreach plat, $(PLATFORM),$(foreach targ,$(TARGET),edma3_drv_$(plat)_$(targ)_be_example))
else
edma3_lld_EXAMPLES_LIST = edma3_drv_example_target $(foreach plat, $(PLATFORM),$(foreach targ,$(TARGET),edma3_drv_$(plat)_$(targ)_example))
endif


# EDMA3 LLD RM - Resource manager
edma3_lld_rm_RELPATH = ti/sdo/edma3/rm
edma3_lld_rm_PATH = $(edma3_lld_PATH)/packages/$(edma3_lld_rm_RELPATH)
edma3_lld_rm_INCLUDE = $(edma3_lld_rm_PATH) $(edma3_lld_rm_PATH)/src
edma3_lld_rm_PKG_LIST = edma3_lld_rm edma3_lld_rm_sample
edma3_lld_rm_PLATFORM_DEPENDENCY = yes

edma3_lld_rm_sample_RELPATH = ti/sdo/edma3/rm/sample
edma3_lld_rm_sample_PATH = $(edma3_lld_PATH)/packages/$(edma3_lld_rm_sample_RELPATH)
edma3_lld_rm_sample_INCLUDE = $(edma3_lld_rm_sample_PATH) $(edma3_lld_rm_sample_PATH)/src
edma3_lld_rm_sample_PLATFORM_DEPENDENCY = yes

# EDMA3 LLD DRV - Driver
edma3_lld_drv_RELPATH = ti/sdo/edma3/drv
edma3_lld_drv_PATH = $(edma3_lld_PATH)/packages/$(edma3_lld_drv_RELPATH)
edma3_lld_drv_INCLUDE = $(edma3_lld_drv_PATH) $(edma3_lld_drv_PATH)/src
edma3_lld_drv_PKG_LIST = edma3_lld_drv edma3_lld_drv_sample
edma3_lld_drv_PLATFORM_DEPENDENCY = no

edma3_lld_drv_sample_RELPATH = ti/sdo/edma3/drv/sample
edma3_lld_drv_sample_PATH = $(edma3_lld_PATH)/packages/$(edma3_lld_drv_sample_RELPATH)
edma3_lld_drv_sample_INCLUDE = $(edma3_lld_drv_sample_PATH) $(edma3_lld_drv_sample_PATH)/src
edma3_lld_drv_sample_PLATFORM_DEPENDENCY = yes

# EDMA3 LLD top level
edma3_lld_INCLUDE = $(edma3_lld_PATH)/packages $(edma3_lld_rm_INCLUDE) $(edma3_lld_drv_INCLUDE) \
                    $(edma3_lld_rm_sample_INCLUDE) $(edma3_lld_drv_sample_INCLUDE)

# EDMA3 LLD examples
edma3_drv_c6472-evm_64p_example_EXAMPLES_RELPATH = examples/edma3_driver/evm6472
edma3_drv_c6472-evm_64p_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6472-evm_64p_example_EXAMPLES_RELPATH)

edma3_drv_c6472-evm_64p_be_example_EXAMPLES_RELPATH = examples/edma3_driver/evm6472BE
edma3_drv_c6472-evm_64p_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6472-evm_64p_be_example_EXAMPLES_RELPATH)

edma3_drv_c6748-evm_674_example_EXAMPLES_RELPATH = examples/edma3_driver/evm6748
edma3_drv_c6748-evm_674_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6748-evm_674_example_EXAMPLES_RELPATH)

edma3_drv_da830-evm_674_example_EXAMPLES_RELPATH = examples/edma3_driver/evmDA830
edma3_drv_da830-evm_674_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_da830-evm_674_example_EXAMPLES_RELPATH)

edma3_drv_omapl137-evm_674_example_EXAMPLES_RELPATH = examples/edma3_driver/evmOMAPL137
edma3_drv_omapl137-evm_674_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_omapl137-evm_674_example_EXAMPLES_RELPATH)

edma3_drv_omapl138-evm_674_example_EXAMPLES_RELPATH = examples/edma3_driver/evmOMAPL138
edma3_drv_omapl138-evm_674_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_omapl138-evm_674_example_EXAMPLES_RELPATH)

edma3_drv_omap4-evm_64t_example_EXAMPLES_RELPATH = examples/edma3_driver/evmOMAP4
edma3_drv_omap4-evm_64t_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_omap4-evm_64t_example_EXAMPLES_RELPATH)

edma3_drv_omapl137-evm_arm9_example_EXAMPLES_RELPATH = examples/edma3_driver/evmOMAPL137_ARM
edma3_drv_omapl137-evm_arm9_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_omapl137-evm_arm9_example_EXAMPLES_RELPATH)

edma3_drv_omapl138-evm_arm9_example_EXAMPLES_RELPATH = examples/edma3_driver/evmOMAPL138_ARM
edma3_drv_omapl138-evm_arm9_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_omapl138-evm_arm9_example_EXAMPLES_RELPATH)

edma3_drv_tci6486-evm_64p_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI6486
edma3_drv_tci6486-evm_64p_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6486-evm_64p_example_EXAMPLES_RELPATH)

edma3_drv_tci6486-evm_64p_be_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI6486BE
edma3_drv_tci6486-evm_64p_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6486-evm_64p_be_example_EXAMPLES_RELPATH)

edma3_drv_ti814x-evm_674_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTI814x
edma3_drv_ti814x-evm_674_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_ti814x-evm_674_example_EXAMPLES_RELPATH)

edma3_drv_ti814x-evm_a8_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTI814x_A8
edma3_drv_ti814x-evm_a8_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_ti814x-evm_a8_example_EXAMPLES_RELPATH)

edma3_drv_ti814x-evm_m3_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTI814x_M3
edma3_drv_ti814x-evm_m3_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_ti814x-evm_m3_example_EXAMPLES_RELPATH)

edma3_drv_ti816x-evm_674_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTI816x
edma3_drv_ti816x-evm_674_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_ti816x-evm_674_example_EXAMPLES_RELPATH)

edma3_drv_ti816x-evm_a8_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTI816x_A8
edma3_drv_ti816x-evm_a8_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_ti816x-evm_a8_example_EXAMPLES_RELPATH)

edma3_drv_ti816x-evm_m3_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTI816x_M3
edma3_drv_ti816x-evm_m3_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_ti816x-evm_m3_example_EXAMPLES_RELPATH)

edma3_drv_c6a811x-evm_674_example_EXAMPLES_RELPATH = examples/edma3_driver/evmC6A811x
edma3_drv_c6a811x-evm_674_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6a811x-evm_674_example_EXAMPLES_RELPATH)

edma3_drv_c6a811x-evm_a8_example_EXAMPLES_RELPATH = examples/edma3_driver/evmC6A811x_A8
edma3_drv_c6a811x-evm_a8_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6a811x-evm_a8_example_EXAMPLES_RELPATH)

edma3_drv_c6a811x-evm_m3_example_EXAMPLES_RELPATH = examples/edma3_driver/evmC6A811x_M3
edma3_drv_c6a811x-evm_m3_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6a811x-evm_m3_example_EXAMPLES_RELPATH)

edma3_drv_tci6608-sim_66_example_EXAMPLES_RELPATH = examples/edma3_driver/simTCI6608
edma3_drv_tci6608-sim_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6608-sim_66_example_EXAMPLES_RELPATH)

edma3_drv_tci6608-sim_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/simTCI6608BE
edma3_drv_tci6608-sim_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6608-sim_66_be_example_EXAMPLES_RELPATH)

edma3_drv_tci6616-sim_66_example_EXAMPLES_RELPATH = examples/edma3_driver/simTCI6616
edma3_drv_tci6616-sim_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6616-sim_66_example_EXAMPLES_RELPATH)

edma3_drv_tci6616-sim_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/simTCI6616BE
edma3_drv_tci6616-sim_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6616-sim_66_be_example_EXAMPLES_RELPATH)

edma3_drv_tci6614-sim_66_example_EXAMPLES_RELPATH = examples/edma3_driver/simTCI6614
edma3_drv_tci6614-sim_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6614-sim_66_example_EXAMPLES_RELPATH)

edma3_drv_tci6614-sim_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/simTCI6614BE
edma3_drv_tci6614-sim_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6614-sim_66_be_example_EXAMPLES_RELPATH)

edma3_drv_c6657-sim_66_example_EXAMPLES_RELPATH = examples/edma3_driver/simC6657
edma3_drv_c6657-sim_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6657-sim_66_example_EXAMPLES_RELPATH)

edma3_drv_c6657-sim_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/simC6657BE
edma3_drv_c6657-sim_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6657-sim_66_be_example_EXAMPLES_RELPATH)

edma3_drv_tci6638k2k-sim_66_example_EXAMPLES_RELPATH = examples/edma3_driver/simKepler
edma3_drv_tci6638k2k-sim_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6638k2k-sim_66_example_EXAMPLES_RELPATH)

edma3_drv_tci6638k2k-sim_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/simKeplerBE
edma3_drv_tci6638k2k-sim_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6638k2k-sim_66_be_example_EXAMPLES_RELPATH)

edma3_drv_c6670-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evm6670
edma3_drv_c6670-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6670-evm_66_example_EXAMPLES_RELPATH)

edma3_drv_c6670-evm_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/evm6670BE
edma3_drv_c6670-evm_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6670-evm_66_be_example_EXAMPLES_RELPATH)

edma3_drv_c6678-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evm6678
edma3_drv_c6678-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6678-evm_66_example_EXAMPLES_RELPATH)

edma3_drv_c6678-evm_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/evm6678BE
edma3_drv_c6678-evm_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6678-evm_66_be_example_EXAMPLES_RELPATH)

edma3_drv_c66ak2e-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evmC66AK2E
edma3_drv_c66ak2e-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c66ak2e-evm_66_example_EXAMPLES_RELPATH)
edma3_drv_c66ak2e-evm_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/evmC66AK2EBE
edma3_drv_c66ak2e-evm_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c66ak2e-evm_66_be_example_EXAMPLES_RELPATH)

edma3_drv_tci6614-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI6614
edma3_drv_tci6614-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6614-evm_66_example_EXAMPLES_RELPATH)

edma3_drv_tci6614-evm_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI6614BE
edma3_drv_tci6614-evm_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6614-evm_66_be_example_EXAMPLES_RELPATH)

edma3_drv_c6657-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evm6657
edma3_drv_c6657-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6657-evm_66_example_EXAMPLES_RELPATH)

edma3_drv_c6657-evm_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/evm6657BE
edma3_drv_c6657-evm_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c6657-evm_66_be_example_EXAMPLES_RELPATH)

edma3_drv_tci6638k2k-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI6638K2K
edma3_drv_tci6638k2k-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6638k2k-evm_66_example_EXAMPLES_RELPATH)

edma3_drv_tci6638k2k-evm_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI6638K2KBE
edma3_drv_tci6638k2k-evm_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6638k2k-evm_66_be_example_EXAMPLES_RELPATH)

edma3_drv_tci6630k2l-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI6630K2L
edma3_drv_tci6630k2l-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6630k2l-evm_66_example_EXAMPLES_RELPATH)

edma3_drv_tci6630k2l-evm_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI6630K2LBE
edma3_drv_tci6630k2l-evm_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6630k2l-evm_66_be_example_EXAMPLES_RELPATH)

edma3_drv_tci6636k2h-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI6636K2H
edma3_drv_tci6636k2h-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6636k2h-evm_66_example_EXAMPLES_RELPATH)

edma3_drv_tci6636k2h-evm_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI6636K2HBE
edma3_drv_tci6636k2h-evm_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6636k2h-evm_66_be_example_EXAMPLES_RELPATH)

edma3_drv_tci66ak2g02-evm_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI6636AK2G02BE
edma3_drv_tci66ak2g02-evm_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci66ak2g02-evm_66_be_example_EXAMPLES_RELPATH)

edma3_drv_tda2xx-evm_m4_example_EXAMPLES_RELPATH = examples/edma3_driver/evmtda2xx_M4
edma3_drv_tda2xx-evm_m4_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tda2xx-evm_m4_example_EXAMPLES_RELPATH)

edma3_drv_tda2xx-evm_a15_example_EXAMPLES_RELPATH = examples/edma3_driver/evmtda2xx_A15
edma3_drv_tda2xx-evm_a15_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tda2xx-evm_a15_example_EXAMPLES_RELPATH)

edma3_drv_tda2xx-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evmtda2xx
edma3_drv_tda2xx-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tda2xx-evm_66_example_EXAMPLES_RELPATH)

edma3_drv_tci6636k2h-evm_a15_example_EXAMPLES_RELPATH = examples/edma3_user_space_driver/evmTCI6636K2H
edma3_drv_tci6636k2h-evm_a15_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6636k2h-evm_a15_example_EXAMPLES_RELPATH)

edma3_drv_tci6636k2h-evm_a15_example_bios_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI6636K2H_A15
edma3_drv_tci6636k2h-evm_a15_example_bios_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6636k2h-evm_a15_example_bios_EXAMPLES_RELPATH)

edma3_drv_tci6638k2k-evm_a15_example_EXAMPLES_RELPATH = examples/edma3_user_space_driver/evmTCI6638K2K
edma3_drv_tci6638k2k-evm_a15_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6638k2k-evm_a15_example_EXAMPLES_RELPATH)

edma3_drv_c66ak2e-evm_a15_example_EXAMPLES_RELPATH = examples/edma3_user_space_driver/evmC66AK2E
edma3_drv_c66ak2e-evm_a15_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_c66ak2e-evm_a15_example_EXAMPLES_RELPATH)

edma3_drv_tci6630k2l-evm_a15_example_EXAMPLES_RELPATH = examples/edma3_user_space_driver/evmTCI6630K2L
edma3_drv_tci6630k2l-evm_a15_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci6630k2l-evm_a15_example_EXAMPLES_RELPATH)

edma3_drv_tci66ak2g02-evm_a15_example_EXAMPLES_RELPATH = examples/edma3_user_space_driver/evmTCI66AK2G02
edma3_drv_tci66ak2g02-evm_a15_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci66ak2g02-evm_a15_example_EXAMPLES_RELPATH)

edma3_drv_tda2xx-evm_eve_example_EXAMPLES_RELPATH = examples/edma3_driver/evmtda2xx_EVE
edma3_drv_tda2xx-evm_eve_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tda2xx-evm_eve_example_EXAMPLES_RELPATH)

edma3_drv_tda3xx-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTDA3xx_DSP
edma3_drv_tda3xx-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tda3xx-evm_66_example_EXAMPLES_RELPATH)
edma3_drv_tda3xx-evm_m4_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTDA3xx_M4
edma3_drv_tda3xx-evm_m4_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tda3xx-evm_m4_example_EXAMPLES_RELPATH)
edma3_drv_tda3xx-evm_eve_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTDA3xx_EVE
edma3_drv_tda3xx-evm_eve_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tda3xx-evm_eve_example_EXAMPLES_RELPATH)

edma3_drv_dra72x-evm_a15_example_EXAMPLES_RELPATH = examples/edma3_driver/evmDRA72x_A15
edma3_drv_dra72x-evm_a15_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_dra72x-evm_a15_example_EXAMPLES_RELPATH)
edma3_drv_dra72x-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evmDRA72x_DSP
edma3_drv_dra72x-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_dra72x-evm_66_example_EXAMPLES_RELPATH)
edma3_drv_dra72x-evm_m4_example_EXAMPLES_RELPATH = examples/edma3_driver/evmDRA72x_M4
edma3_drv_dra72x-evm_m4_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_dra72x-evm_m4_example_EXAMPLES_RELPATH)

edma3_drv_tda2ex-evm_a15_example_EXAMPLES_RELPATH = examples/edma3_driver/evmDRA72x_A15
edma3_drv_tda2ex-evm_a15_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tda2ex-evm_a15_example_EXAMPLES_RELPATH)
edma3_drv_tda2ex-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evmDRA72x_DSP
edma3_drv_tda2ex-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tda2ex-evm_66_example_EXAMPLES_RELPATH)
edma3_drv_tda2ex-evm_m4_example_EXAMPLES_RELPATH = examples/edma3_driver/evmDRA72x_M4
edma3_drv_tda2ex-evm_m4_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tda2ex-evm_m4_example_EXAMPLES_RELPATH)

edma3_drv_am572x-evm_a15_example_EXAMPLES_RELPATH = examples/edma3_driver/evmAM572x_A15
edma3_drv_am572x-evm_a15_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_am572x-evm_a15_example_EXAMPLES_RELPATH)
edma3_drv_am572x-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evmAM572x_DSP
edma3_drv_am572x-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_am572x-evm_66_example_EXAMPLES_RELPATH)
edma3_drv_am572x-evm_m4_example_EXAMPLES_RELPATH = examples/edma3_driver/evmAM572x_M4
edma3_drv_am572x-evm_m4_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_am572x-evm_m4_example_EXAMPLES_RELPATH)


edma3_drv_am571x-evm_a15_example_EXAMPLES_RELPATH = examples/edma3_driver/evmAM571x_A15
edma3_drv_am571x-evm_a15_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_am571x-evm_a15_example_EXAMPLES_RELPATH)
edma3_drv_am571x-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evmAM571x_DSP
edma3_drv_am571x-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_am571x-evm_66_example_EXAMPLES_RELPATH)
edma3_drv_am571x-evm_m4_example_EXAMPLES_RELPATH = examples/edma3_driver/evmAM571x_M4
edma3_drv_am571x-evm_m4_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_am571x-evm_m4_example_EXAMPLES_RELPATH)

edma3_drv_am335x-evm_a8_example_EXAMPLES_RELPATH = examples/edma3_driver/evmAM335x_A8
edma3_drv_am335x-evm_a8_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_am335x-evm_a8_example_EXAMPLES_RELPATH)

edma3_drv_am437x-evm_a9_example_EXAMPLES_RELPATH = examples/edma3_driver/evmAM437x_A9
edma3_drv_am437x-evm_a9_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_am437x-evm_a9_example_EXAMPLES_RELPATH)

edma3_drv_tci66ak2g02-evm_66_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI66AK2G02
edma3_drv_tci66ak2g02-evm_66_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci66ak2g02-evm_66_example_EXAMPLES_RELPATH)

edma3_drv_tci66ak2g02-evm_66_be_example_EXAMPLES_RELPATH = examples/edma3_driver/evmTCI66AK2G02BE
edma3_drv_tci66ak2g02-evm_66_be_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci66ak2g02-evm_66_be_example_EXAMPLES_RELPATH)

edma3_drv_tci66ak2g02-evm_a15_example_EXAMPLES_RELPATH = examples/edma3_user_space_driver/evmTCI66AK2G02
edma3_drv_tci66ak2g02-evm_a15_example_EXAMPLES_PATH = $(edma3_lld_PATH)/$(edma3_drv_tci66ak2g02-evm_a15_example_EXAMPLES_RELPATH)

# Nothing beyond this point
