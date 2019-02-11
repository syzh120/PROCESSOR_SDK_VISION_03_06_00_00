
include $($(MAKEAPPNAME)_PATH)/configs/cfg.mk

SRCDIR += $($(MAKEAPPNAME)_PATH)/src/rtos/draw2d
INCDIR += $($(MAKEAPPNAME)_PATH)

SRCS_IPU_A15 = \
		draw2d_font01.c \
		draw2d_font03.c \
		draw2d_font04.c \
        draw2d_font05.c \
        draw2d_font06.c \
        draw2d_font07.c \
        draw2d_font08.c \
        draw2d_font09.c \
        draw2d_font14.c \
        draw2d_ti_logo_white.c \
        draw2d_ti_logo_white_1.c \
        draw2d_ti_logo_white_small.c

SRCS_COMMON += \
	draw2d.c \
	draw2d_font_bmp.c \
	draw2d_font10_yuv.c \
	draw2d_font11_yuv.c \
	draw2d_font12_yuv.c \
	draw2d_font13_yuv.c \

ifeq ($(ALG_radarprocess),yes)
SRCS_COMMON += \
	draw2d_font02.c \
	draw2d_font00.c
else
SRCS_IPU_A15 += \
	draw2d_font02.c \
	draw2d_font00.c
endif

ifeq ($(ALG_objectdetection),yes)
SRCS_IPU_A15 += \
	draw2d_frontcam_logo.c
endif

ifeq ($(ALG_denseopticalflow),yes)
SRCS_IPU_A15 += \
	lut16x16x0_25_129x129_0.c \
	lut16x16x0_25_129x129_1.c
endif

ifeq ($(ALG_surroundview),yes)
SRCS_IPU_A15 += \
        draw2d_sv_logo.c \
        draw2d_sv_logo_small.c \
        draw2d_3d_perception_sfm_logo.c \
        draw2d_jeep_Image_220x330.c \
        draw2d_jeep_Image_228x432.c \
        draw2d_jeep_Image_288x432.c \
        draw2d_suv_topView_348x480.c \
        draw2d_tda2x.c \
        draw2d_tda3x.c \
        draw2d_ford_sf_lines_rearview_left.c \
        draw2d_ford_sf_lines_rearview_right.c \
        draw2d_ford_sf_lines_topdown_rearview_left.c \
        draw2d_ford_sf_lines_topdown_rearview_right.c
endif

ifeq ($(ALG_rear_view_panorama),yes)
SRCS_IPU_A15 += \
	draw2d_rvp_logo.c \
	draw2d_car_Image.c \
        draw2d_jeep1.c \
        draw2d_rsvp_jeep1.c \
        draw2d_jeep2.c
endif

ifeq ($(ALG_stereo_postprocessing),yes)
SRCS_IPU_A15 += \
	draw2d_colorbar_20x720.c \
	draw2d_colorbar_35x450.c
endif

ifeq "$(or $(ALG_surroundview),$(ALG_clr))""yes"
SRCS_IPU_A15 += \
	draw2c_tl_green.c \
	draw2c_tl_red.c
endif

SRCS_$(IPU_PRIMARY_CORE) += $(SRCS_IPU_A15)
SRCS_a15_0 += $(SRCS_IPU_A15)

