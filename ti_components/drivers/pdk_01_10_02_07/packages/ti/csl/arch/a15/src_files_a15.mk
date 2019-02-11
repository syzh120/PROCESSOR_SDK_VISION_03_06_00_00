
ifeq ($(SOC),$(filter $(SOC),tda2xx tda2px dra75x tda2ex dra72x am574x am572x am571x k2h k2k k2l k2e k2g))

  PACKAGE_SRCS_COMMON += csl_a15.h csl_armGic.h csl_armGicAux.h arch/a15 src/ip/arm_gic/V0
  ifeq ($(ARCH),armv7a)
    SRCDIR += ./arch/a15/src ./arch/a15/V0
    INCDIR += ./arch/a15 ./arch/a15/V0

    ifeq ($(SOC),$(filter $(SOC),tda2xx tda2px dra75x tda2ex dra72x am574x am572x am571x))
      SRCS_COMMON += mpu_wugen.c interrupt.c
    endif

    ifeq ($(SOC),$(filter $(SOC),tda2xx tda2px tda2ex dra72x dra75x am574x))
      SRCDIR += ./arch/a15/V1
      INCDIR += ./arch/a15/V1
      SRCS_COMMON += cpu.c cp15.c cache_a15.c mmu_a15.c
      SRCS_ASM_COMMON += cache_a15_gcc.asm mmu_a15_gcc.asm performance_unit.asm cache_a15_rom_api_calls.asm
      SRCS_tda2ex += ecc_a15.c
      SRCS_ASM_tda2ex += ecc_a15_gcc.asm
    endif

    SRCS_COMMON += csl_a15.c
    SRCS_ASM_COMMON += csl_a15Asm.asm
  endif

endif
