# File: vps_ut_component.mk
#       This file is component include make file of VPS unit test.
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
# <mod>_BOARD_DEPENDENCY - "yes": means the code for this module depends on
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
ifeq ($(vps_ut_component_make_include), )

# VIP unit test
vps_test_capture_COMP_LIST = vps_test_capture
vps_test_capture_RELPATH = ti/drv/vps/unit_test/captureUt
vps_test_capture_PATH = $(PDK_VPS_COMP_PATH)/unit_test/captureUt
vps_test_capture_BOARD_DEPENDENCY = yes
vps_test_capture_CORE_DEPENDENCY = no
vps_test_capture_XDC_CONFIGURO = yes
export vps_test_capture_COMP_LIST
export vps_test_capture_BOARD_DEPENDENCY
export vps_test_capture_CORE_DEPENDENCY
export vps_test_capture_XDC_CONFIGURO
vps_test_capture_PKG_LIST = vps_test_capture
vps_test_capture_INCLUDE = $(vps_test_capture_PATH)
vps_test_capture_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm idkAM572x idkAM571x evmAM572x idkAM574x
export vps_test_capture_BOARDLIST
vps_test_capture_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_test_capture_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_test_capture
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_test_capture_SBL_APPIMAGEGEN = yes
  export vps_test_capture_SBL_APPIMAGEGEN
endif

# DSS Example
vps_test_display_COMP_LIST = vps_test_display
vps_test_display_RELPATH = ti/drv/vps/unit_test/displayUt
vps_test_display_PATH = $(PDK_VPS_COMP_PATH)/unit_test/displayUt
vps_test_display_BOARD_DEPENDENCY = yes
vps_test_display_CORE_DEPENDENCY = no
vps_test_display_XDC_CONFIGURO = yes
export vps_test_display_COMP_LIST
export vps_test_display_BOARD_DEPENDENCY
export vps_test_display_CORE_DEPENDENCY
export vps_test_display_XDC_CONFIGURO
vps_test_display_PKG_LIST = vps_test_display
vps_test_display_INCLUDE = $(vps_test_display_PATH)
vps_test_display_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm idkAM572x idkAM571x evmAM572x idkAM574x
export vps_test_display_BOARDLIST
vps_test_display_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_test_display_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_test_display
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_test_display_SBL_APPIMAGEGEN = yes
  export vps_test_display_SBL_APPIMAGEGEN
endif

# VPE unit test
vps_test_vpe_COMP_LIST = vps_test_vpe
vps_test_vpe_RELPATH = ti/drv/vps/unit_test/vpeUt
vps_test_vpe_PATH = $(PDK_VPS_COMP_PATH)/unit_test/vpeUt
vps_test_vpe_BOARD_DEPENDENCY = yes
vps_test_vpe_CORE_DEPENDENCY = no
vps_test_vpe_XDC_CONFIGURO = yes
export vps_test_vpe_COMP_LIST
export vps_test_vpe_BOARD_DEPENDENCY
export vps_test_vpe_CORE_DEPENDENCY
export vps_test_vpe_XDC_CONFIGURO
vps_test_vpe_PKG_LIST = vps_test_vpe
vps_test_vpe_INCLUDE = $(vps_test_vpe_PATH)
vps_test_vpe_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm idkAM572x idkAM571x evmAM572x idkAM574x
export vps_test_vpe_BOARDLIST
vps_test_vpe_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_test_vpe_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_test_vpe
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_test_vpe_SBL_APPIMAGEGEN = yes
  export vps_test_vpe_SBL_APPIMAGEGEN
endif

# Cascade Radar unit test
vps_test_cascade_radar_COMP_LIST = vps_test_cascade_radar
vps_test_cascade_radar_RELPATH = ti/drv/vps/unit_test/cascadeRadarUt
vps_test_cascade_radar_PATH = $(PDK_VPS_COMP_PATH)/unit_test/cascadeRadarUt
vps_test_cascade_radar_BOARD_DEPENDENCY = yes
vps_test_cascade_radar_CORE_DEPENDENCY = no
vps_test_cascade_radar_XDC_CONFIGURO = yes
export vps_test_cascade_radar_COMP_LIST
export vps_test_cascade_radar_BOARD_DEPENDENCY
export vps_test_cascade_radar_CORE_DEPENDENCY
export vps_test_cascade_radar_XDC_CONFIGURO
vps_test_cascade_radar_PKG_LIST = vps_test_cascade_radar
vps_test_cascade_radar_INCLUDE = $(vps_test_cascade_radar_PATH)
vps_test_cascade_radar_BOARDLIST = tda2xx-evm-radar tda2xx-cascade-radar
export vps_test_cascade_radar_BOARDLIST
vps_test_cascade_radar_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_test_cascade_radar_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_test_cascade_radar
ifeq ($(SOC),$(filter $(SOC), tda2xx))
  vps_test_cascade_radar_SBL_APPIMAGEGEN = yes
  export vps_test_cascade_radar_SBL_APPIMAGEGEN
endif

# monitor Radar unit test
vps_test_monitor_radar_COMP_LIST = vps_test_monitor_radar
vps_test_monitor_radar_RELPATH = ti/drv/vps/unit_test/monitorRadarUt
vps_test_monitor_radar_PATH = $(PDK_VPS_COMP_PATH)/unit_test/monitorRadarUt
vps_test_monitor_radar_BOARD_DEPENDENCY = yes
vps_test_monitor_radar_CORE_DEPENDENCY = no
vps_test_monitor_radar_XDC_CONFIGURO = yes
export vps_test_monitor_radar_COMP_LIST
export vps_test_monitor_radar_BOARD_DEPENDENCY
export vps_test_monitor_radar_CORE_DEPENDENCY
export vps_test_monitor_radar_XDC_CONFIGURO
vps_test_monitor_radar_PKG_LIST = vps_test_monitor_radar
vps_test_monitor_radar_INCLUDE = $(vps_test_monitor_radar_PATH)
vps_test_monitor_radar_BOARDLIST = tda3xx-ar12-booster
export vps_test_monitor_radar_BOARDLIST
vps_test_monitor_radar_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_test_monitor_radar_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_test_monitor_radar
ifeq ($(SOC),$(filter $(SOC), tda3xx))
  vps_test_monitor_radar_SBL_APPIMAGEGEN = yes
  export vps_test_monitor_radar_SBL_APPIMAGEGEN
endif

# Cascade Radar Fpga unit test
vps_test_cascade_flash_fpga_COMP_LIST = vps_test_cascade_flash_fpga
vps_test_cascade_flash_fpga_RELPATH = ti/drv/vps/unit_test/cascadeFpgaNorFlash
vps_test_cascade_flash_fpga_PATH = $(PDK_VPS_COMP_PATH)/unit_test/cascadeFpgaNorFlash
vps_test_cascade_flash_fpga_BOARD_DEPENDENCY = yes
vps_test_cascade_flash_fpga_CORE_DEPENDENCY = no
vps_test_cascade_flash_fpga_XDC_CONFIGURO = yes
export vps_test_cascade_flash_fpga_COMP_LIST
export vps_test_cascade_flash_fpga_BOARD_DEPENDENCY
export vps_test_cascade_flash_fpga_CORE_DEPENDENCY
export vps_test_cascade_flash_fpga_XDC_CONFIGURO
vps_test_cascade_flash_fpga_PKG_LIST = vps_test_cascade_flash_fpga
vps_test_cascade_flash_fpga_INCLUDE = $(vps_test_cascade_flash_fpga_PATH)
vps_test_cascade_flash_fpga_BOARDLIST = tda2xx-evm-radar tda2xx-cascade-radar
export vps_test_cascade_flash_fpga_BOARDLIST
vps_test_cascade_flash_fpga_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_test_cascade_flash_fpga_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_test_cascade_flash_fpga
ifeq ($(SOC),$(filter $(SOC), tda2xx))
  vps_test_cascade_flash_fpga_SBL_APPIMAGEGEN = yes
  export vps_test_cascade_flash_fpga_SBL_APPIMAGEGEN
endif

# Queue unit test
vps_test_queue_utils_COMP_LIST = vps_test_queue_utils
vps_test_queue_utils_RELPATH = ti/drv/vps/unit_test/queueUt
vps_test_queue_utils_PATH = $(PDK_VPS_COMP_PATH)/unit_test/queueUt
vps_test_queue_utils_BOARD_DEPENDENCY = yes
vps_test_queue_utils_CORE_DEPENDENCY = no
vps_test_queue_utils_XDC_CONFIGURO = yes
export vps_test_queue_utils_COMP_LIST
export vps_test_queue_utils_BOARD_DEPENDENCY
export vps_test_queue_utils_CORE_DEPENDENCY
export vps_test_queue_utils_XDC_CONFIGURO
vps_test_queue_utils_PKG_LIST = vps_test_queue_utils
vps_test_queue_utils_INCLUDE = $(vps_test_queue_utils_PATH)
vps_test_queue_utils_BOARDLIST = tda2xx-evm tda2px-evm tda2ex-evm tda3xx-evm
export vps_test_queue_utils_BOARDLIST
vps_test_queue_utils_$(SOC)_CORELIST = $(vps_$(SOC)_CORELIST)
export vps_test_queue_utils_$(SOC)_CORELIST
vps_EXAMPLE_LIST += vps_test_queue_utils
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx))
  vps_test_queue_utils_SBL_APPIMAGEGEN = yes
  export vps_test_queue_utils_SBL_APPIMAGEGEN
endif

vps_ut_component_make_include := 1
endif
