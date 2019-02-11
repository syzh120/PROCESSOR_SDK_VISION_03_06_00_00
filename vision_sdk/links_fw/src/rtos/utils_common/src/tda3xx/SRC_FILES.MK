
SRCDIR += tda3xx

SRCS_COMMON += utils_clk.c

SRCS_$(IPU_PRIMARY_CORE) += utils_l3_emif_bw.c \
               utils_boot_slaves.c \
               utils_esm.c \
               utils_ipu_ecc.c \
               utils_dcc.c

SRCS_ipu1_1 +=

SRCS_$(IPU_SECONDARY_CORE) +=

