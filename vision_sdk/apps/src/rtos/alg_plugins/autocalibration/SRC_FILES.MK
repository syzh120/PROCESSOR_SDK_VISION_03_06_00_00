

SRCDIR += autocalibration

SRCS_AC_ACDETECT = acDetectLink_algPlugin.c

SRCS_AC_PESTIMATE = pEstimateLink_algPlugin.c

SRCS_c66xdsp_1 += $(SRCS_AC_ACDETECT) $(SRCS_AC_PESTIMATE) calMatGen_If.c

SRCS_c66xdsp_2 += $(SRCS_AC_ACDETECT) $(SRCS_AC_PESTIMATE) calMatGen_If.c


