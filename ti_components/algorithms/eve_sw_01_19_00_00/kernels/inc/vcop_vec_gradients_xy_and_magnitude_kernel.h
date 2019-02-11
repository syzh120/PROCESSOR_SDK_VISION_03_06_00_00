#ifndef _TI_vcop_vec_gradients_xy_and_magnitude_kernel_h_
#define _TI_vcop_vec_gradients_xy_and_magnitude_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_vec_gradients_xy_magnitudeu8[28];

/* Basic Runner Function */
void vcop_vec_gradients_xy_magnitudeu8(
   __vptr_uint8 pIn,
   __vptr_int16 pGradX,
   __vptr_int16 pGradY,
   __vptr_uint8 pMag,
   unsigned short pitch,
   unsigned short width,
   unsigned short height);
/* Custom Runner Function */
void vcop_vec_gradients_xy_magnitudeu8_custom(
   __vptr_uint8 pIn,
   __vptr_int16 pGradX,
   __vptr_int16 pGradY,
   __vptr_uint8 pMag,
   unsigned short pitch,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_vec_gradients_xy_magnitudeu8_init(
   __vptr_uint8 pIn,
   __vptr_int16 pGradX,
   __vptr_int16 pGradY,
   __vptr_uint8 pMag,
   unsigned short pitch,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_vec_gradients_xy_magnitudeu8_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_vec_gradients_xy_magnitudeu8 ((unsigned int)28)
unsigned int vcop_vec_gradients_xy_magnitudeu8_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_vec_gradients_xy_magnitudeu8 ((unsigned int)0)
unsigned int vcop_vec_gradients_xy_magnitudeu8_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_vec_gradients_xy_and_magnitude[24];

/* Basic Runner Function */
void vcop_vec_gradients_xy_and_magnitude(
   __vptr_uint8 pIn,
   __vptr_int16 pGradX,
   __vptr_int16 pGradY,
   __vptr_int16 pMag,
   unsigned short pitch,
   unsigned short width,
   unsigned short height);
/* Custom Runner Function */
void vcop_vec_gradients_xy_and_magnitude_custom(
   __vptr_uint8 pIn,
   __vptr_int16 pGradX,
   __vptr_int16 pGradY,
   __vptr_int16 pMag,
   unsigned short pitch,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_vec_gradients_xy_and_magnitude_init(
   __vptr_uint8 pIn,
   __vptr_int16 pGradX,
   __vptr_int16 pGradY,
   __vptr_int16 pMag,
   unsigned short pitch,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_vec_gradients_xy_and_magnitude_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_vec_gradients_xy_and_magnitude ((unsigned int)24)
unsigned int vcop_vec_gradients_xy_and_magnitude_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_vec_gradients_xy_and_magnitude ((unsigned int)0)
unsigned int vcop_vec_gradients_xy_and_magnitude_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_gradients_xy_list[46];

/* Basic Runner Function */
void vcop_gradients_xy_list(
   __vptr_uint8 pIn,
   __vptr_uint32 pUpperLeftXY,
   __vptr_uint8 pEdgeMap,
   __vptr_uint32 xSequence_C,
   __vptr_int32 pGradXY,
   __vptr_uint32 pEdgeListXY,
   __vptr_uint16 pListSize,
   unsigned short width,
   unsigned short height,
   unsigned short pitchInData,
   unsigned short pitchEdgeMap);
/* Custom Runner Function */
void vcop_gradients_xy_list_custom(
   __vptr_uint8 pIn,
   __vptr_uint32 pUpperLeftXY,
   __vptr_uint8 pEdgeMap,
   __vptr_uint32 xSequence_C,
   __vptr_int32 pGradXY,
   __vptr_uint32 pEdgeListXY,
   __vptr_uint16 pListSize,
   unsigned short width,
   unsigned short height,
   unsigned short pitchInData,
   unsigned short pitchEdgeMap,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_gradients_xy_list_init(
   __vptr_uint8 pIn,
   __vptr_uint32 pUpperLeftXY,
   __vptr_uint8 pEdgeMap,
   __vptr_uint32 xSequence_C,
   __vptr_int32 pGradXY,
   __vptr_uint32 pEdgeListXY,
   __vptr_uint16 pListSize,
   unsigned short width,
   unsigned short height,
   unsigned short pitchInData,
   unsigned short pitchEdgeMap,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_gradients_xy_list_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_gradients_xy_list ((unsigned int)46)
unsigned int vcop_gradients_xy_list_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_gradients_xy_list ((unsigned int)0)
unsigned int vcop_gradients_xy_list_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_gradients_xy_mag_lut_index_calulcation[36];

/* Basic Runner Function */
void vcop_gradients_xy_mag_lut_index_calulcation(
   __vptr_int16 gradXY,
   __vptr_uint16 lutIdxPtr,
   __vptr_int8 log4aPtr,
   unsigned short width,
   unsigned short height,
   unsigned short pitch);
/* Custom Runner Function */
void vcop_gradients_xy_mag_lut_index_calulcation_custom(
   __vptr_int16 gradXY,
   __vptr_uint16 lutIdxPtr,
   __vptr_int8 log4aPtr,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_gradients_xy_mag_lut_index_calulcation_init(
   __vptr_int16 gradXY,
   __vptr_uint16 lutIdxPtr,
   __vptr_int8 log4aPtr,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_gradients_xy_mag_lut_index_calulcation_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_gradients_xy_mag_lut_index_calulcation ((unsigned int)36)
unsigned int vcop_gradients_xy_mag_lut_index_calulcation_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_gradients_xy_mag_lut_index_calulcation ((unsigned int)0)
unsigned int vcop_gradients_xy_mag_lut_index_calulcation_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_reciprocal_sqrt_lookup[12];

/* Basic Runner Function */
void vcop_reciprocal_sqrt_lookup(
   __vptr_uint16 lutIdxPtr,
   __vptr_uint8 reciSqrtLut,
   __vptr_uint8 reciSqrtLutOutput,
   unsigned short listSize);
/* Custom Runner Function */
void vcop_reciprocal_sqrt_lookup_custom(
   __vptr_uint16 lutIdxPtr,
   __vptr_uint8 reciSqrtLut,
   __vptr_uint8 reciSqrtLutOutput,
   unsigned short listSize,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_reciprocal_sqrt_lookup_init(
   __vptr_uint16 lutIdxPtr,
   __vptr_uint8 reciSqrtLut,
   __vptr_uint8 reciSqrtLutOutput,
   unsigned short listSize,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_reciprocal_sqrt_lookup_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_reciprocal_sqrt_lookup ((unsigned int)12)
unsigned int vcop_reciprocal_sqrt_lookup_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_reciprocal_sqrt_lookup ((unsigned int)0)
unsigned int vcop_reciprocal_sqrt_lookup_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_gradients_xy_unit_vecs[24];

/* Basic Runner Function */
void vcop_gradients_xy_unit_vecs(
   __vptr_int16 gradXY,
   __vptr_int8 log4aPtr,
   __vptr_uint8 reciprocalLutOutput,
   __vptr_int16 unitXYptr,
   unsigned short listSize);
/* Custom Runner Function */
void vcop_gradients_xy_unit_vecs_custom(
   __vptr_int16 gradXY,
   __vptr_int8 log4aPtr,
   __vptr_uint8 reciprocalLutOutput,
   __vptr_int16 unitXYptr,
   unsigned short listSize,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_gradients_xy_unit_vecs_init(
   __vptr_int16 gradXY,
   __vptr_int8 log4aPtr,
   __vptr_uint8 reciprocalLutOutput,
   __vptr_int16 unitXYptr,
   unsigned short listSize,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_gradients_xy_unit_vecs_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_gradients_xy_unit_vecs ((unsigned int)24)
unsigned int vcop_gradients_xy_unit_vecs_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_gradients_xy_unit_vecs ((unsigned int)0)
unsigned int vcop_gradients_xy_unit_vecs_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_gradients_xy_update_param_block[28];

/* Basic Runner Function */
void vcop_gradients_xy_update_param_block(
   __vptr_uint16 pBlockGradientsXyMagLutIndexCalulcation,
   __vptr_uint16 pBlockReciprocalSqrtLookup,
   __vptr_uint16 pBlockGradientsXyUnitVecs,
   __vptr_uint16 pListSize,
   __vptr_uint16 pListSizeWbuf);
/* Custom Runner Function */
void vcop_gradients_xy_update_param_block_custom(
   __vptr_uint16 pBlockGradientsXyMagLutIndexCalulcation,
   __vptr_uint16 pBlockReciprocalSqrtLookup,
   __vptr_uint16 pBlockGradientsXyUnitVecs,
   __vptr_uint16 pListSize,
   __vptr_uint16 pListSizeWbuf,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_gradients_xy_update_param_block_init(
   __vptr_uint16 pBlockGradientsXyMagLutIndexCalulcation,
   __vptr_uint16 pBlockReciprocalSqrtLookup,
   __vptr_uint16 pBlockGradientsXyUnitVecs,
   __vptr_uint16 pListSize,
   __vptr_uint16 pListSizeWbuf,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_gradients_xy_update_param_block_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_gradients_xy_update_param_block ((unsigned int)28)
unsigned int vcop_gradients_xy_update_param_block_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_gradients_xy_update_param_block ((unsigned int)0)
unsigned int vcop_gradients_xy_update_param_block_ctrl_count(void);

/***********************************************************/
#endif

