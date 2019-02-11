#ifndef _TI_vcop_location_matrix_kernel_h_
#define _TI_vcop_location_matrix_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_vec_L_matrix_u8_Mag[34];

/* Basic Runner Function */
void vcop_vec_L_matrix_u8_Mag(
   __vptr_uint8 pIn,
   __vptr_uint8 pMag,
   __vptr_uint8 pOut1,
   __vptr_uint8 pOut2,
   __vptr_uint32 pOutClear1,
   __vptr_uint32 pOutClear2,
   unsigned short width,
   unsigned short height,
   unsigned short numBins,
   __vptr_uint8 binIdx);
/* Custom Runner Function */
void vcop_vec_L_matrix_u8_Mag_custom(
   __vptr_uint8 pIn,
   __vptr_uint8 pMag,
   __vptr_uint8 pOut1,
   __vptr_uint8 pOut2,
   __vptr_uint32 pOutClear1,
   __vptr_uint32 pOutClear2,
   unsigned short width,
   unsigned short height,
   unsigned short numBins,
   __vptr_uint8 binIdx,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_vec_L_matrix_u8_Mag_init(
   __vptr_uint8 pIn,
   __vptr_uint8 pMag,
   __vptr_uint8 pOut1,
   __vptr_uint8 pOut2,
   __vptr_uint32 pOutClear1,
   __vptr_uint32 pOutClear2,
   unsigned short width,
   unsigned short height,
   unsigned short numBins,
   __vptr_uint8 binIdx,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_vec_L_matrix_u8_Mag_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_vec_L_matrix_u8_Mag ((unsigned int)34)
unsigned int vcop_vec_L_matrix_u8_Mag_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_vec_L_matrix_u8_Mag ((unsigned int)0)
unsigned int vcop_vec_L_matrix_u8_Mag_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_vec_L_matrix_u16_Mag[36];

/* Basic Runner Function */
void vcop_vec_L_matrix_u16_Mag(
   __vptr_uint8 pIn,
   __vptr_uint16 pMag,
   __vptr_uint16 pOut1,
   __vptr_uint16 pOut2,
   __vptr_uint32 pOutClear1,
   __vptr_uint32 pOutClear2,
   unsigned short width,
   unsigned short height,
   unsigned short numBins,
   __vptr_uint8 binIdx);
/* Custom Runner Function */
void vcop_vec_L_matrix_u16_Mag_custom(
   __vptr_uint8 pIn,
   __vptr_uint16 pMag,
   __vptr_uint16 pOut1,
   __vptr_uint16 pOut2,
   __vptr_uint32 pOutClear1,
   __vptr_uint32 pOutClear2,
   unsigned short width,
   unsigned short height,
   unsigned short numBins,
   __vptr_uint8 binIdx,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_vec_L_matrix_u16_Mag_init(
   __vptr_uint8 pIn,
   __vptr_uint16 pMag,
   __vptr_uint16 pOut1,
   __vptr_uint16 pOut2,
   __vptr_uint32 pOutClear1,
   __vptr_uint32 pOutClear2,
   unsigned short width,
   unsigned short height,
   unsigned short numBins,
   __vptr_uint8 binIdx,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_vec_L_matrix_u16_Mag_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_vec_L_matrix_u16_Mag ((unsigned int)36)
unsigned int vcop_vec_L_matrix_u16_Mag_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_vec_L_matrix_u16_Mag ((unsigned int)0)
unsigned int vcop_vec_L_matrix_u16_Mag_ctrl_count(void);

/***********************************************************/
#endif

