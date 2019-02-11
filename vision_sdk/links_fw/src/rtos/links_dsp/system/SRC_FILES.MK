
SRCS_SYSTEMDSP  = system_c6xdsp.c systemLink_tsk_c6xdsp.c 

# This is an example usage of file specific compiler flags.
# The format of CFLAGS_<filename_without_extension> = <Your desired file specific options>
# can be used for any specific file as part of EVE and DSP build.
CFLAGS_system_c6xdsp = --keep_asm

SRCS_c66xdsp_1 += $(SRCS_SYSTEMDSP) 

SRCS_c66xdsp_2 += $(SRCS_SYSTEMDSP)

