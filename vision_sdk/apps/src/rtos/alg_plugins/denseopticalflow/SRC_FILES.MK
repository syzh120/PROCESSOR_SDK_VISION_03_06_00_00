

SRCDIR += denseopticalflow denseopticalflow/algorithmSrc/src 

SRCS_DENSE_OPTICAL_FLOW = denseOpticalFlowLink_algPlugin.c 

SRCS_VECTOR_TO_IMAGE = vectorToImgLink_algPlugin.c \
                        vectorToImgLink_dma.c \
			vectorToImageLUT_65x65_0.c vectorToImageLUT_65x65_1.c \
			vectorToImageLUT_129x129_0.c vectorToImageLUT_129x129_1.c

SRCS_c66xdsp_1 += $(SRCS_VECTOR_TO_IMAGE)
SRCS_c66xdsp_2 += $(SRCS_VECTOR_TO_IMAGE)

SRCS_arp32_1 += $(SRCS_DENSE_OPTICAL_FLOW)

