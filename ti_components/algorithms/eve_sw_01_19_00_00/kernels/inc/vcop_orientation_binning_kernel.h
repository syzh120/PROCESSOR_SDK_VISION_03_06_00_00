#ifndef _TI_vcop_orientation_binning_kernel_h_
#define _TI_vcop_orientation_binning_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_orientation_binning[54];

/* Basic Runner Function */
void vcop_orientation_binning(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint8 outBin,
   __vptr_int16 wSinTab,
   __vptr_int16 wCosTab,
   unsigned short numBins,
   unsigned short width,
   unsigned short height,
   unsigned short pitch);
/* Custom Runner Function */
void vcop_orientation_binning_custom(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint8 outBin,
   __vptr_int16 wSinTab,
   __vptr_int16 wCosTab,
   unsigned short numBins,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_orientation_binning_init(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint8 outBin,
   __vptr_int16 wSinTab,
   __vptr_int16 wCosTab,
   unsigned short numBins,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_orientation_binning_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_orientation_binning ((unsigned int)54)
unsigned int vcop_orientation_binning_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_orientation_binning ((unsigned int)0)
unsigned int vcop_orientation_binning_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_orientation_binning_even[64];

/* Basic Runner Function */
void vcop_orientation_binning_even(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint8 absGradX,
   __vptr_uint8 absGradY,
   __vptr_uint8 outBin,
   __vptr_int16 wSinTab,
   __vptr_int16 wCosTab,
   unsigned short numBins,
   unsigned short width,
   unsigned short height,
   unsigned short pitch);
/* Custom Runner Function */
void vcop_orientation_binning_even_custom(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint8 absGradX,
   __vptr_uint8 absGradY,
   __vptr_uint8 outBin,
   __vptr_int16 wSinTab,
   __vptr_int16 wCosTab,
   unsigned short numBins,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_orientation_binning_even_init(
   __vptr_int16 gradX,
   __vptr_int16 gradY,
   __vptr_uint8 absGradX,
   __vptr_uint8 absGradY,
   __vptr_uint8 outBin,
   __vptr_int16 wSinTab,
   __vptr_int16 wCosTab,
   unsigned short numBins,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_orientation_binning_even_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_orientation_binning_even ((unsigned int)64)
unsigned int vcop_orientation_binning_even_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_orientation_binning_even ((unsigned int)0)
unsigned int vcop_orientation_binning_even_ctrl_count(void);

/***********************************************************/
#endif

