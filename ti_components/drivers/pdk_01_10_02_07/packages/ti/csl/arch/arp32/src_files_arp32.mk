
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px tda2ex tda3xx am572x am574x))

PACKAGE_SRCS_COMMON += arch/arp32
ifeq ($(ARCH),arp32)
SRCDIR += ./arch/arp32/src
INCDIR += ./arch/arp32
SRCS_COMMON += arp32_wugen.c intctl.c interrupt.c inth.c
SRCS_ASM_COMMON += boot_arp32.asm
endif

endif
