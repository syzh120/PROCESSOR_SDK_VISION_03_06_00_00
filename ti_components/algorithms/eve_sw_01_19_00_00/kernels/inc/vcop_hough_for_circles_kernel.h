#ifndef _TI_vcop_hough_for_circles_kernel_h_
#define _TI_vcop_hough_for_circles_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_hough_circle_compute_idx[44];

/* Basic Runner Function */
void vcop_hough_circle_compute_idx(
   __vptr_int16 gradUnitVecXY,
   __vptr_uint16 xyList,
   __vptr_int16 scratch,
   __vptr_uint16 houghSpaceIndex,
   unsigned short numEdgePoints,
   char radius,
   unsigned char downShift,
   unsigned short houghSpaceSaturateX,
   unsigned short houghSpaceSaturateY,
   unsigned short houghSpacePitch);
/* Custom Runner Function */
void vcop_hough_circle_compute_idx_custom(
   __vptr_int16 gradUnitVecXY,
   __vptr_uint16 xyList,
   __vptr_int16 scratch,
   __vptr_uint16 houghSpaceIndex,
   unsigned short numEdgePoints,
   char radius,
   unsigned char downShift,
   unsigned short houghSpaceSaturateX,
   unsigned short houghSpaceSaturateY,
   unsigned short houghSpacePitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_hough_circle_compute_idx_init(
   __vptr_int16 gradUnitVecXY,
   __vptr_uint16 xyList,
   __vptr_int16 scratch,
   __vptr_uint16 houghSpaceIndex,
   unsigned short numEdgePoints,
   char radius,
   unsigned char downShift,
   unsigned short houghSpaceSaturateX,
   unsigned short houghSpaceSaturateY,
   unsigned short houghSpacePitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_hough_circle_compute_idx_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_hough_circle_compute_idx ((unsigned int)44)
unsigned int vcop_hough_circle_compute_idx_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_hough_circle_compute_idx ((unsigned int)0)
unsigned int vcop_hough_circle_compute_idx_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_hough_circle_compute_idx_param_block_update[24];

/* Basic Runner Function */
void vcop_hough_circle_compute_idx_param_block_update(
   __vptr_uint16 pBlock,
   __vptr_int32 pBlockSigned,
   __vptr_uint16 pListSizePtr,
   __vptr_int8 pCurrRadiusPtr);
/* Custom Runner Function */
void vcop_hough_circle_compute_idx_param_block_update_custom(
   __vptr_uint16 pBlock,
   __vptr_int32 pBlockSigned,
   __vptr_uint16 pListSizePtr,
   __vptr_int8 pCurrRadiusPtr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_hough_circle_compute_idx_param_block_update_init(
   __vptr_uint16 pBlock,
   __vptr_int32 pBlockSigned,
   __vptr_uint16 pListSizePtr,
   __vptr_int8 pCurrRadiusPtr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_hough_circle_compute_idx_param_block_update_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_hough_circle_compute_idx_param_block_update ((unsigned int)24)
unsigned int vcop_hough_circle_compute_idx_param_block_update_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_hough_circle_compute_idx_param_block_update ((unsigned int)0)
unsigned int vcop_hough_circle_compute_idx_param_block_update_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_hough_circle_init_hough_space[10];

/* Basic Runner Function */
void vcop_hough_circle_init_hough_space(
   __vptr_uint32 houghSpacePtr,
   unsigned short houghSpacePitch,
   unsigned short houghSpaceHeight);
/* Custom Runner Function */
void vcop_hough_circle_init_hough_space_custom(
   __vptr_uint32 houghSpacePtr,
   unsigned short houghSpacePitch,
   unsigned short houghSpaceHeight,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_hough_circle_init_hough_space_init(
   __vptr_uint32 houghSpacePtr,
   unsigned short houghSpacePitch,
   unsigned short houghSpaceHeight,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_hough_circle_init_hough_space_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_hough_circle_init_hough_space ((unsigned int)10)
unsigned int vcop_hough_circle_init_hough_space_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_hough_circle_init_hough_space ((unsigned int)0)
unsigned int vcop_hough_circle_init_hough_space_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_hough_circle_vote_to_hough_space[12];

/* Basic Runner Function */
void vcop_hough_circle_vote_to_hough_space(
   __vptr_uint16 houghSpaceIndex,
   __vptr_uint8 houghSpacePtr,
   unsigned short numEdgePoints);
/* Custom Runner Function */
void vcop_hough_circle_vote_to_hough_space_custom(
   __vptr_uint16 houghSpaceIndex,
   __vptr_uint8 houghSpacePtr,
   unsigned short numEdgePoints,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_hough_circle_vote_to_hough_space_init(
   __vptr_uint16 houghSpaceIndex,
   __vptr_uint8 houghSpacePtr,
   unsigned short numEdgePoints,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_hough_circle_vote_to_hough_space_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_hough_circle_vote_to_hough_space ((unsigned int)12)
unsigned int vcop_hough_circle_vote_to_hough_space_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_hough_circle_vote_to_hough_space ((unsigned int)0)
unsigned int vcop_hough_circle_vote_to_hough_space_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_hough_circle_vote_to_hough_space_param_block_update[10];

/* Basic Runner Function */
void vcop_hough_circle_vote_to_hough_space_param_block_update(
   __vptr_uint16 pBlock,
   unsigned short numElemsInLastBlk);
/* Custom Runner Function */
void vcop_hough_circle_vote_to_hough_space_param_block_update_custom(
   __vptr_uint16 pBlock,
   unsigned short numElemsInLastBlk,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_hough_circle_vote_to_hough_space_param_block_update_init(
   __vptr_uint16 pBlock,
   unsigned short numElemsInLastBlk,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_hough_circle_vote_to_hough_space_param_block_update_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_hough_circle_vote_to_hough_space_param_block_update ((unsigned int)10)
unsigned int vcop_hough_circle_vote_to_hough_space_param_block_update_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_hough_circle_vote_to_hough_space_param_block_update ((unsigned int)0)
unsigned int vcop_hough_circle_vote_to_hough_space_param_block_update_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_hough_for_circle_detect[38];

/* Basic Runner Function */
void vcop_hough_for_circle_detect(
   __vptr_uint8 houghSpacePtr,
   __vptr_uint32 pUpperLeftXY,
   __vptr_uint32 xSequence,
   __vptr_uint16 pNumCircles,
   __vptr_uint32 pCenterListXY,
   __vptr_uint8 pHoughScoreList,
   unsigned char houghScoreThreshold,
   unsigned short houghSpaceWidth,
   unsigned short houghSpaceHeight,
   unsigned short houghSpacePitch,
   unsigned char houghSpaceShift);
/* Custom Runner Function */
void vcop_hough_for_circle_detect_custom(
   __vptr_uint8 houghSpacePtr,
   __vptr_uint32 pUpperLeftXY,
   __vptr_uint32 xSequence,
   __vptr_uint16 pNumCircles,
   __vptr_uint32 pCenterListXY,
   __vptr_uint8 pHoughScoreList,
   unsigned char houghScoreThreshold,
   unsigned short houghSpaceWidth,
   unsigned short houghSpaceHeight,
   unsigned short houghSpacePitch,
   unsigned char houghSpaceShift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_hough_for_circle_detect_init(
   __vptr_uint8 houghSpacePtr,
   __vptr_uint32 pUpperLeftXY,
   __vptr_uint32 xSequence,
   __vptr_uint16 pNumCircles,
   __vptr_uint32 pCenterListXY,
   __vptr_uint8 pHoughScoreList,
   unsigned char houghScoreThreshold,
   unsigned short houghSpaceWidth,
   unsigned short houghSpaceHeight,
   unsigned short houghSpacePitch,
   unsigned char houghSpaceShift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_hough_for_circle_detect_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_hough_for_circle_detect ((unsigned int)38)
unsigned int vcop_hough_for_circle_detect_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_hough_for_circle_detect ((unsigned int)0)
unsigned int vcop_hough_for_circle_detect_ctrl_count(void);

/***********************************************************/
#endif

