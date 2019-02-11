

SRCDIR += structurefrommotion

SRCS_SFM_MAIN = sfmMainLink_algPlugin.c dumpedSOFtestdata.c

SRCS_SFM_LTV = sfmLinearTwoViewLink_algPlugin.c   

SRCS_SFM_MAP = sfmMapLink_algPlugin.c 

SRCS_c66xdsp_1 += $(SRCS_SFM_MAIN) $(SRCS_SFM_LTV) $(SRCS_SFM_MAP) 

SRCS_c66xdsp_2 += $(SRCS_SFM_MAIN) $(SRCS_SFM_LTV) $(SRCS_SFM_MAP) 


