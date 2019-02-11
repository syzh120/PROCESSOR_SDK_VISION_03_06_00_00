===================================================================================
Running standalone example on EVE core, it is required to configure EVE mmu setting.
For this gels6 is mandatory CCS_CSP_ADAS_S28_ES1.0_NDA_TRM_vA_gels6 which configures
default EVE mmu setting or Customer has to configure following address mapping.

EVE MMU0 TLB entry 1: 0x00000000 --> 0x40500000  : 4K Page size
EVE MMU0 TLB entry 2: 0x4A000000 --> 0x4A000000  : 1M Page size
EVE MMU0 TLB entry 3: 0x81000000 --> 0x81000000  : 16M Page size
EVE MMU0 TLB entry 4: 0x40000000 --> 0x40000000  : 16M Page size
===================================================================================