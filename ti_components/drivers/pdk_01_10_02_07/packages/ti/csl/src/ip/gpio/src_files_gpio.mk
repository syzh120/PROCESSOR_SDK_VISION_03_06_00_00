
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x am574x tda3xx am335x am437x dra78x))
PACKAGE_SRCS_COMMON += cslr_gpio.h csl_gpio.h src/ip/gpio/src_files_gpio.mk src/ip/gpio/csl_gpio.h src/ip/gpio/V1
SRCS_COMMON += gpio_v2.c
SRCDIR += src/ip/gpio/V1/priv
INCDIR += . src/ip/gpio/V1
endif

ifeq ($(SOC),$(filter $(SOC), k2h k2k k2l k2e k2g c6657 c6678 omapl137 omapl138))
PACKAGE_SRCS_COMMON += cslr_gpio.h src/ip/gpio/src_files_gpio.mk src/ip/gpio/csl_gpio.h src/ip/gpio/V0
SRCS_COMMON += gpio.c
SRCDIR += src/ip/gpio/V0/priv
ifeq ($(SOC),$(filter $(SOC), k2g))
PACKAGE_SRCS_COMMON += src/ip/gpio/V2
INCDIR += . src/ip/gpio/V2
else
INCDIR += . src/ip/gpio/V0
endif
endif
