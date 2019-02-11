
ifeq ($(SOC),$(filter $(SOC), tda3xx tda2xx tda2px tda2ex am574x am572x am571x k2h k2e k2k k2l k2g dra78x))
PACKAGE_SRCS_COMMON += src/ip/arm_gic/src_files_arm_gic.mk
ifeq ($(ARCH),armv7a)
  SRCDIR += src/ip/arm_gic/V0
  INCDIR += src/ip/arm_gic/V0
  SRCS_ASM_COMMON += csl_a15_intr.asm
endif
endif
