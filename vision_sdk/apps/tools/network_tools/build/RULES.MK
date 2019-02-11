BASE_DIR = $(abspath .)
CONFIG=
BUILD_OS=Windows_NT

ifeq ($(BUILD_OS),Windows_NT)
  MAKE = gmake
  CGTOOLS_PATH="c:/Program Files (x86)/CodeBlocks/MinGW"
  NSP_INCLUDE_PATH= c:/ti/nsp_gmacsw_4_15_00_00/packages
endif



ifeq ($(BUILD_OS),Linux)
  MAKE = make
  CGTOOLS_PATH=/usr/
  NSP_INCLUDE_PATH=/datalocal/ti_components/networking/nsp_gmacsw_4_15_00_00/packages
endif

export CONFIG
export BASE_DIR
export MAKE
export CGTOOLS_PATH
export NSP_INCLUDE_PATH
export BUILD_OS
