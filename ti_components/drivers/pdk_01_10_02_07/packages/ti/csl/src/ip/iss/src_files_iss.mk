
ifeq ($(SOC),$(filter $(SOC), tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_iss.h src/ip/iss/src_files_iss.mk src/ip/iss/V0
endif
