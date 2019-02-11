ifeq ($(SOC),$(filter $(SOC), am574x tda2xx tda2px dra75x am572x tda2ex dra72x am571x k2h k2k k2g k2l k2e))

  PACKAGE_SRCS_COMMON += a15/src/csl_a15_startup.c a15/src/csl_a15_init.asm a15/src/src_files_a15init.mk
  ifeq ($(ARCH),armv7a)
    SRCDIR += a15/src
    INCDIR += a15/src
    INCDIR += a15

    SRCS_COMMON += csl_a15_startup.c
    SRCS_ASM_COMMON += csl_a15_init.asm

    ifeq ($(SOC),$(filter $(SOC), k2h k2k k2g k2l k2e))
            SRCS_ASM_COMMON += exceptionhandler_keystone.asm
            PACKAGE_SRCS_COMMON += a15/src/exceptionhandler_keystone.asm
    else
            SRCS_ASM_COMMON += exceptionhandler.asm
            PACKAGE_SRCS_COMMON += a15/src/exceptionhandler.asm
    endif
  endif

endif

