ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)
include $(vision_sdk_PATH)/apps/configs/cfg.mk

ifeq ($(VSDK_BOARD_TYPE),TDA2XX_EVM)
NAME = adas_j6
endif

ifeq ($(VSDK_BOARD_TYPE),TDA2XX_RVP)
NAME = adas_j6
endif

ifeq ($(VSDK_BOARD_TYPE),TDA2EX_EVM)
NAME = adas_j6eco
endif
ifeq ($(VSDK_BOARD_TYPE),TDA2PX_EVM)
NAME = adas_j6plus
endif

ifeq ($(VSDK_BOARD_TYPE),TDA2XX_EVM)
define PINFO
PINFO DESCRIPTION=QNX INFOADAS USER LIBRARY for J6/DRA74x/TDA2xx
endef
endif

ifeq ($(VSDK_BOARD_TYPE),TDA2XX_RVP)
define PINFO
PINFO DESCRIPTION=QNX INFOADAS USER LIBRARY for J6/DRA74x/TDA2xx
endef
endif

ifeq ($(VSDK_BOARD_TYPE),TDA2EX_EVM)
define PINFO
PINFO DESCRIPTION=QNX INFOADAS USER LIBRARY for J6Eco/DRA72x/TDA2Ex
endef
endif
ifeq ($(VSDK_BOARD_TYPE),TDA2PX_EVM)
define PINFO
PINFO DESCRIPTION=QNX INFOADAS USER LIBRARY for J6Plus/DRA76x/TDA2Px
endef
endif

INSTALLDIR = usr/lib

LIBS +=utils cache

CCOPTS += -DQNX_BUILD=1
CCOPTS += -DBUILD_INFOADAS=1
ifeq ($(VSDK_BOARD_TYPE),TDA2XX_EVM)
CCOPTS += -DTDA2XX_BUILD=1
CCOPTS += -DTDA2XX_FAMILY_BUILD=1
endif

ifeq ($(VSDK_BOARD_TYPE),TDA2XX_RVP)
CCOPTS += -DTDA2XX_BUILD=1
CCOPTS += -DTDA2XX_FAMILY_BUILD=1
endif
ifeq ($(VSDK_BOARD_TYPE),TDA2EX_EVM)
CCOPTS += -DTDA2EX_BUILD=1
CCOPTS += -DTDA2XX_FAMILY_BUILD=1
endif
ifeq ($(VSDK_BOARD_TYPE),TDA2PX_EVM)
CCOPTS += -DTDA2PX_BUILD=1
CCOPTS += -DTDA2XX_FAMILY_BUILD=1
endif
ifeq ($(PROC_IPU1_0_INCLUDE),yes)
CCOPTS += -DPROC_IPU1_0_INCLUDE=1
endif
ifeq ($(PROC_IPU1_1_INCLUDE),yes)
CCOPTS += -DPROC_IPU1_1_INCLUDE=1
endif
ifeq ($(PROC_DSP1_INCLUDE),yes)
CCOPTS += -DPROC_DSP1_INCLUDE=1
endif
ifeq ($(PROC_DSP2_INCLUDE),yes)
CCOPTS += -DPROC_DSP2_INCLUDE=1
endif
ifeq ($(PROC_EVE1_INCLUDE),yes)
CCOPTS += -DPROC_EVE1_INCLUDE=1
endif
ifeq ($(PROC_EVE2_INCLUDE),yes)
CCOPTS += -DPROC_EVE2_INCLUDE=1
endif
ifeq ($(PROC_EVE3_INCLUDE),yes)
CCOPTS += -DPROC_EVE3_INCLUDE=1
endif
ifeq ($(PROC_EVE4_INCLUDE),yes)
CCOPTS += -DPROC_EVE4_INCLUDE=1
endif
ifeq ($(PROC_A15_0_INCLUDE),yes)
CCOPTS += -DPROC_A15_0_INCLUDE=1
endif
ifeq ($(IPU_PRIMARY_CORE),ipu1_0)
CCOPTS += -DIPU_PRIMARY_CORE_IPU1
endif
ifeq ($(IPU_PRIMARY_CORE),ipu2)
CCOPTS += -DIPU_PRIMARY_CORE_IPU2
endif
ifeq ($(IPUMM_INCLUDE), yes)
CCOPTS += -DIPUMM_INCLUDE
endif
ifeq ($(ISS_INCLUDE), yes)
CCOPTS += -DISS_INCLUDE
endif

CCFLAGS += -fms-extensions

# Include path
EXTRA_INCVPATH += $(INSTALL_ROOT_nto)/usr/include
EXTRA_INCVPATH += $(pvr_PATH)/Tools
EXTRA_INCVPATH += $(pvr_PATH)/Tools/OGLES2
EXTRA_INCVPATH += $(pvr_PATH)/Include
EXTRA_INCVPATH += $(vision_sdk_PATH)/apps
EXTRA_INCVPATH += $(vision_sdk_PATH)/links_fw
EXTRA_INCVPATH += $(vision_sdk_PATH)/links_fw/include/link_api
EXTRA_INCVPATH += $(vision_sdk_PATH)/links_fw/include/config/apps/$(MAKECONFIG)
EXTRA_INCVPATH += $(vision_sdk_PATH)
EXTRA_INCVPATH += $(vision_sdk_PATH)/links_fw/src/hlos/osa/include

EXTRA_INCVPATH += $(infoadas_PATH)/include
EXTRA_INCVPATH += $(infoadas_PATH)/ti-plugins/include
EXTRA_INCVPATH += $(infoadas_PATH)/ti-plugins/srv
ifeq ($(UC_lvds_vip_single_cam_analytics),yes)
  EXTRA_INCVPATH += $(infoadas_PATH)/ti-plugins/sca
endif
EXTRA_INCVPATH += $(infoadas_PATH)/ti-plugins/preview

# C file to exlude for QNX build
EXCLUDE_OBJS+= system_gbm_allocator.o osa_dma.o system_pvrscope_if.o
EXCLUDE_OBJS+= system_ipc.o system_rpmsg_notify.o

ifeq ($(UC_lvds_vip_single_cam_analytics),yes)
else
  EXCLUDE_OBJS += sca_chain.o
endif

# Source path
#EXTRA_SRCVPATH +=  $(PROJECT_ROOT)
EXTRA_SRCVPATH += $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/ipcOut
EXTRA_SRCVPATH += $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/ipcIn
EXTRA_SRCVPATH += $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/null
EXTRA_SRCVPATH += $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/nullSrc
EXTRA_SRCVPATH += $(vision_sdk_PATH)/links_fw/src/hlos/links_a15/ep
EXTRA_SRCVPATH += $(vision_sdk_PATH)/links_fw/src/hlos/utils/multiproc
EXTRA_SRCVPATH += $(vision_sdk_PATH)/links_fw/src/hlos/system
EXTRA_SRCVPATH += $(vision_sdk_PATH)/links_fw/src/hlos/system/qnx
EXTRA_SRCVPATH += $(vision_sdk_PATH)/links_fw/src/hlos/osa/src
EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/common
EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/infoadas/src/ti-plugins
EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/infoadas/src/common
EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/rtos/common_srv
EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/rtos/modules/osal
EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/modules/sgx3Dsrv
EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils
ifeq ($(UC_lvds_vip_2d_srv),yes)
  EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/lvds_vip_2d_srv
endif
ifeq ($(UC_lvds_vip_3d_srv),yes)
  EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/lvds_vip_3d_srv
endif
ifeq ($(UC_lvds_vip_single_cam),yes)
  EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/lvds_vip_single_cam
endif
ifeq ($(UC_lvds_vip_multi_cam),yes)
  EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/lvds_vip_multi_cam
endif
ifeq ($(UC_a15source_2d_srv),yes)
  EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/a15source_2d_srv
endif
ifeq ($(UC_a15source_2d_srv),yes)
  EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/a15source_3d_srv
endif
ifeq ($(UC_lvds_vip_single_cam_analytics),yes)
  EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/lvds_vip_single_cam_analytics
endif
ifeq ($(UC_buf_loop),yes)
  EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/buf_loop
endif
ifeq ($(UC_csi2Cal_multi_cam_view),yes)
  EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/csi2Cal_multi_cam_view
endif
ifeq ($(UC_iss_multi_cam_isp_sgx_3d_srv_display),yes)
  EXTRA_SRCVPATH += $(vision_sdk_PATH)/apps/src/hlos/infoadas/src/chains/iss_multi_cam_isp_sgx_3d_srv_display
endif

# install the headers
POST_INSTALL += \
    mkdir -p $(INSTALL_ROOT_nto)/usr/include/ti/vision_sdk; \
    cp -fRv $(vision_sdk_PATH)/links_fw/src/hlos/osa/include/osa_debug.h $(INSTALL_ROOT_nto)/usr/include/ti/vision_sdk/osa_debug.h; \
    cp -fRv $(vision_sdk_PATH)/links_fw/src/hlos/osa/include/osa_types.h $(INSTALL_ROOT_nto)/usr/include/ti/vision_sdk/osa_types.h; \
    cp -fRv $(vision_sdk_PATH)/links_fw/src/hlos/osa/include/osa_mem_shared.h $(INSTALL_ROOT_nto)/usr/include/ti/vision_sdk/osa_mem_shared.h; \
    cp -fRv $(vision_sdk_PATH)/links_fw/include/link_api/system_buffer.h $(INSTALL_ROOT_nto)/usr/include/ti/vision_sdk/system_buffer.h; \
    cp -fRv $(vision_sdk_PATH)/links_fw/include/link_api/system_const.h $(INSTALL_ROOT_nto)/usr/include/ti/vision_sdk/system_const.h; \
    cp -fRv $(vision_sdk_PATH)/links_fw/include/link_api/system_link_info.h $(INSTALL_ROOT_nto)/usr/include/ti/vision_sdk/system_link_info.h; \
    mkdir -p $(INSTALL_ROOT_nto)/armle-v7/infoadas; \
    cp -fR $(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils/models $(INSTALL_ROOT_nto)/armle-v7/infoadas/; \
    cp -fRv $(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils/CALMAT.BIN $(INSTALL_ROOT_nto)/armle-v7/infoadas/; \
    cp -fRv $(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils/LENS.BIN $(INSTALL_ROOT_nto)/armle-v7/infoadas/; \
    #cp -fRv $(vision_sdk_PATH)/apps/tools/surround_vision_tools/ViewToWorld_Mesh_tool/srv_views.txt $(INSTALL_ROOT_nto)/armle-v7/infoadas/; \
    cp -fRv $(vision_sdk_PATH)/apps/tools/surround_vision_tools/ViewToWorld_Mesh_tool/srv_params.txt $(INSTALL_ROOT_nto)/armle-v7/infoadas/; \
    cp -fRv $(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils/FragShader.fsh $(INSTALL_ROOT_nto)/armle-v7/infoadas/; \
    cp -fRv $(vision_sdk_PATH)/apps/src/hlos/modules/sgxRenderUtils/VertShader.vsh $(INSTALL_ROOT_nto)/armle-v7/infoadas/; \

include $(MKFILES_ROOT)/qtargets.mk
OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))
