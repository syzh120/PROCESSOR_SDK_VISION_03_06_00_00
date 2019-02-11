
ifeq ($(SOC),$(filter $(SOC), tda2xx tda2px dra75x tda2ex dra72x am571x am572x am574x tda3xx dra78x))
PACKAGE_SRCS_COMMON += cslr_mailbox.h csl_mailbox.h src/ip/mailbox/src_files_mailbox.mk src/ip/mailbox/V0 src/ip/mailbox/V0/V0_0
SRCS_COMMON += mailbox.c
SRCDIR += src/ip/mailbox/V0/priv
INCDIR += . src/ip/mailbox/V0 src/ip/mailbox/V0/V0_0
endif
