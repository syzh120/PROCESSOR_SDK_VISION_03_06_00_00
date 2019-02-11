
Steps to build
==============

- Open Rules.make

- Edit paths for the below variables according to your system environment

  In case of windows machine edit below paths,
  TOOLCHAIN_PATH_A8 ?= c:/ti/ccsv5/tools/compiler/gcc-arm-none-eabi-4_7-2012q4
  TOOLCHAIN_PATH_A9 ?= c:/ti/ccsv5/tools/compiler/gcc-arm-none-eabi-4_7-2012q4
  TOOLCHAIN_PATH_A15 ?= c:/ti/ccsv5/tools/compiler/gcc-arm-none-eabi-4_7-2012q4
  TOOLCHAIN_PATH_M4 ?= c:/ti/TMS470_5.1.5
  C6X_GEN_INSTALL_PATH ?= c:/ti/c6000_7.4.2
  PDK_INSTALL_PATH ?= c:/ti/pdk
  BIOS_INSTALL_PATH ?= c:/ti/bios_6_41_02_41
  XDC_INSTALL_PATH ?= c:/ti/xdctools_3_30_06_67
  EDMA3LLD_BIOS6_INSTALLDIR ?= c:/ti/edma3_lld_02_12_01_21

  In case of linux machine edit below paths,
  TOOLCHAIN_PATH_A8 ?= /opt/tools/cgtools/gcc-arm-none-eabi-4_7-2012q4
  TOOLCHAIN_PATH_A9 ?= /opt/tools/cgtools/gcc-arm-none-eabi-4_7-2012q4
  TOOLCHAIN_PATH_A15 ?= /opt/tools/cgtools/gcc-arm-none-eabi-4_7-2012q4
  TOOLCHAIN_PATH_M4 ?= /opt/tools/cgtools/TIARMCGT5.1.5
  C6X_GEN_INSTALL_PATH ?= /opt/tools/cgtools/C6000_7.4.2
  PDK_INSTALL_PATH ?= /opt/ti/pdk
  BIOS_INSTALL_PATH ?= /opt/tools/bios6/bios_6_41_02_41
  XDC_INSTALL_PATH ?= /opt/tools/xdc/xdctools_3_30_06_67
  EDMA3LLD_BIOS6_INSTALLDIR ?= /opt/tools/edma3/edma3_lld_02_12_01_21

  IMPORTANT:
  Make sure the paths specified above DO NOT have any spaces in them.

- Make sure "gmake" is in your system path.
  Typically when XDC is installed "gmake" is installed along with it and
  it becomes part of the system path by default.

- Open command prompt and type the below
  gmake -s all

  This will clean all and build all PDK drivers as well as all PDK
  examples

- TIP: Always use "-s" option with make to see user friendly prints
       during build.

- Optionally before build, edit the below in Rules.make file,
  depending on the kind of build you want to do:

  BOARD:=
  BUILD_PROFILE_$(CORE)?=

  Valid values for BOARD are:
  tda2xx-evm    - TDA2XX EVM with Si build
  evmDRA75x     - DRA75X EVM with Si build
  am572x-evm    - AM572X EVM with Si build
  tda2px-evm    - TDA2PX EVM with Si build
  tda2ex-evm    - TDA2XX EVM with Si build
  tda2ex-eth-srv        - TDA2EX Ethernet Surround view board
  evmDRA72x     - DRA72x EVM with Si build
  am571x-evm    - AM571X EVM with Si build
  tda3xx-evm    - TDA3XX EVM with Si build
  tda3xx-rvp    - TDA3XX RVP board
  evmDRA78x     - DRA78X EVM with Si build
  tda3xx-evm-radar      - TDA3XX EVM with RADAR build
  tda2xx-evm-radar      - TDA2XX EVM with RADAR build
  tda2xx-cascade-radar  - TDA2XX EVM with RADAR build
  tda2px-evm-radar      - TDA2PX EVM with RADAR build
  tda3xx-ar12-booster   - TDA3XX AR12xx booster board
  tda3xx-ar12-alps      - TDA3XX AR12xx ALPS board
  tda3xx-ar12-rvp       - TDA3XX AR12xx RVP board

  Valid values for BUILD_PROFILE_$(CORE) are:
  debug                 - Debug build with NO compiler optimizations
                          and symbolic debug info included
  release               - Release build with FULL compiler optimizations
                          and symbolic debug info included
  prod_release          - Production release build with FULL compiler
                          optimizations with parameter check and asserts disabled
- Include or Exclude Components
  User can include or exclude a component build by changing variables like below
  in Rules.make. This could be used to disable any reference to a component when
  a particular component is not present or cloned.

  PDK_PM_INCLUDE = yes
  PDK_RTOS_I2C_INCLUDE = yes
  PDK_OSAL_INCLUDE = yes
  PDK_VPS_INCLUDE = yes

- PACKAGE_SELECT (Supported values: all, vps-hal-only, vps-vip-only, vps-vpe-only, vps-vip-dss, vps-vip-vpe)
  all: All libraries are built
  vps-hal-only: Only VPS HAL and common libraries are built
  vps-vip-only: Only VIP libraries are built
  vps-vpe-only: Only VPE libraries are built
  vps-dss-only: Only DSS libraries are built
  vps-vip-dss : VIP and DSS libraries are built
  vps-vip-vpe : VIP and VPE libraries are built

- The generated files are placed in the below folders,
  Executables   - $(DEST_ROOT)/<APP_NAME>/bin/$(BOARD)/<APP_NAME>_$(CORE)_$(BUILD_PROFILE).xe$(ISA)
  Libraries     - $(DEST_ROOT)/<MODULE_RELPATH>/lib/$(BOARD)/$(ISA)/$(BUILD_PROFILE)/*.ae$(ISA)
  Objects       - $(DEST_ROOT)/<MODULE_RELPATH>/obj/$(BOARD)/$(ISA)/$(BUILD_PROFILE)/*.oe$(ISA)
  XDC configuro - $(DEST_ROOT)/<APP_NAME>/obj/$(BOARD)/$(CORE)/$(BUILD_PROFILE)/<APP_NAME>_configuro/*
  Dependancies  - $(DEST_ROOT)/<APP_NAME>/obj/$(BOARD)/$(CORE)/$(BUILD_PROFILE)/.deps/*.P

  Make sure to do a clean build while doing the above as it may not recompile the
  PDK libarary again.

- During development the below "gmake" targets can be also used be used for
  convenience:

  gmake -s examples         - incrementally builds PDK drivers
                              and all examples

  gmake -s platforms        - incrementally builds for all supported BOARDs
  gmake -s profiles         - incrementally builds for all supported BUILD_PROFILEs

  gmake -s all              - clean all and build all drivers, examples
  gmake -s allall           - incrementally builds for all supported BOARDs
                              AND BUILD_PROFILEs

  gmake -s clean            - clean all drivers, examples
  gmake -s examplesclean    - clean all examples ONLY
  gmake -s platformsclean   - cleans for all supported BOARDs
  gmake -s profilesclean    - cleans for all supported BUILD_PROFILEs
  gmake -s allclean         - cleans for all supported BOARDs AND BUILD_PROFILEs

  gmake -s <examplename>    - incrementally builds PDK drivers
                              and the specific example ONLY.
