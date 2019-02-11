#ifndef _TI_vcop_feature_matching_kernel_h_
#define _TI_vcop_feature_matching_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_featureMatching_32[62];

/* Basic Runner Function */
void vcop_featureMatching_32(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint8 pScratch,
   __vptr_uint16 pHammingDistance,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx);
/* Custom Runner Function */
void vcop_featureMatching_32_custom(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint8 pScratch,
   __vptr_uint16 pHammingDistance,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_featureMatching_32_init(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint8 pScratch,
   __vptr_uint16 pHammingDistance,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_featureMatching_32_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_featureMatching_32 ((unsigned int)62)
unsigned int vcop_featureMatching_32_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_featureMatching_32 ((unsigned int)0)
unsigned int vcop_featureMatching_32_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_featureMatching_lt_32[58];

/* Basic Runner Function */
void vcop_featureMatching_lt_32(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint32 pDescriptorMask,
   __vptr_uint8 pScratch,
   __vptr_uint16 pHammingDistance,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx);
/* Custom Runner Function */
void vcop_featureMatching_lt_32_custom(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint32 pDescriptorMask,
   __vptr_uint8 pScratch,
   __vptr_uint16 pHammingDistance,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_featureMatching_lt_32_init(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint32 pDescriptorMask,
   __vptr_uint8 pScratch,
   __vptr_uint16 pHammingDistance,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_featureMatching_lt_32_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_featureMatching_lt_32 ((unsigned int)58)
unsigned int vcop_featureMatching_lt_32_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_featureMatching_lt_32 ((unsigned int)0)
unsigned int vcop_featureMatching_lt_32_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_featureMatching_gt_32[64];

/* Basic Runner Function */
void vcop_featureMatching_gt_32(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint32 pDescriptorMask,
   __vptr_uint16 pScratch,
   __vptr_uint16 pScatterOffsets,
   __vptr_uint16 pHammingDistance,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx);
/* Custom Runner Function */
void vcop_featureMatching_gt_32_custom(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint32 pDescriptorMask,
   __vptr_uint16 pScratch,
   __vptr_uint16 pScatterOffsets,
   __vptr_uint16 pHammingDistance,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_featureMatching_gt_32_init(
   __vptr_uint32 pString1,
   __vptr_uint32 pString2,
   __vptr_uint32 pDescriptorMask,
   __vptr_uint16 pScratch,
   __vptr_uint16 pScatterOffsets,
   __vptr_uint16 pHammingDistance,
   unsigned int xsize,
   unsigned int ysize,
   unsigned int mode,
   unsigned int xpitch,
   short startIdx,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_featureMatching_gt_32_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_featureMatching_gt_32 ((unsigned int)64)
unsigned int vcop_featureMatching_gt_32_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_featureMatching_gt_32 ((unsigned int)0)
unsigned int vcop_featureMatching_gt_32_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_featureMatch_initialize[12];

/* Basic Runner Function */
void vcop_featureMatch_initialize(
   __vptr_uint32 pMinDist0,
   __vptr_uint32 pMinDist1,
   unsigned int m);
/* Custom Runner Function */
void vcop_featureMatch_initialize_custom(
   __vptr_uint32 pMinDist0,
   __vptr_uint32 pMinDist1,
   unsigned int m,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_featureMatch_initialize_init(
   __vptr_uint32 pMinDist0,
   __vptr_uint32 pMinDist1,
   unsigned int m,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_featureMatch_initialize_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_featureMatch_initialize ((unsigned int)12)
unsigned int vcop_featureMatch_initialize_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_featureMatch_initialize ((unsigned int)0)
unsigned int vcop_featureMatch_initialize_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_findTwoBestMatches[18];

/* Basic Runner Function */
void vcop_findTwoBestMatches(
   __vptr_uint32 pHammingDistance,
   __vptr_uint32 pMinDist0,
   __vptr_uint32 pMinDist1,
   unsigned char stride,
   unsigned int n);
/* Custom Runner Function */
void vcop_findTwoBestMatches_custom(
   __vptr_uint32 pHammingDistance,
   __vptr_uint32 pMinDist0,
   __vptr_uint32 pMinDist1,
   unsigned char stride,
   unsigned int n,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_findTwoBestMatches_init(
   __vptr_uint32 pHammingDistance,
   __vptr_uint32 pMinDist0,
   __vptr_uint32 pMinDist1,
   unsigned char stride,
   unsigned int n,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_findTwoBestMatches_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_findTwoBestMatches ((unsigned int)18)
unsigned int vcop_findTwoBestMatches_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_findTwoBestMatches ((unsigned int)0)
unsigned int vcop_findTwoBestMatches_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_pickConfidentMatches[20];

/* Basic Runner Function */
void vcop_pickConfidentMatches(
   __vptr_uint16 pMinDist0,
   __vptr_uint16 pMinDist1,
   __vptr_uint16 pMatchIndex,
   unsigned int m,
   unsigned short minDistanceThres,
   unsigned short matchConfidence);
/* Custom Runner Function */
void vcop_pickConfidentMatches_custom(
   __vptr_uint16 pMinDist0,
   __vptr_uint16 pMinDist1,
   __vptr_uint16 pMatchIndex,
   unsigned int m,
   unsigned short minDistanceThres,
   unsigned short matchConfidence,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_pickConfidentMatches_init(
   __vptr_uint16 pMinDist0,
   __vptr_uint16 pMinDist1,
   __vptr_uint16 pMatchIndex,
   unsigned int m,
   unsigned short minDistanceThres,
   unsigned short matchConfidence,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_pickConfidentMatches_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_pickConfidentMatches ((unsigned int)20)
unsigned int vcop_pickConfidentMatches_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_pickConfidentMatches ((unsigned int)0)
unsigned int vcop_pickConfidentMatches_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_featureMatch_32_pblk_update[22];

/* Basic Runner Function */
void vcop_featureMatch_32_pblk_update(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr);
/* Custom Runner Function */
void vcop_featureMatch_32_pblk_update_custom(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_featureMatch_32_pblk_update_init(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_featureMatch_32_pblk_update_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_featureMatch_32_pblk_update ((unsigned int)22)
unsigned int vcop_featureMatch_32_pblk_update_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_featureMatch_32_pblk_update ((unsigned int)0)
unsigned int vcop_featureMatch_32_pblk_update_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_featureMatch_32_pblk_reset[34];

/* Basic Runner Function */
void vcop_featureMatch_32_pblk_reset(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr);
/* Custom Runner Function */
void vcop_featureMatch_32_pblk_reset_custom(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_featureMatch_32_pblk_reset_init(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_featureMatch_32_pblk_reset_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_featureMatch_32_pblk_reset ((unsigned int)34)
unsigned int vcop_featureMatch_32_pblk_reset_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_featureMatch_32_pblk_reset ((unsigned int)0)
unsigned int vcop_featureMatch_32_pblk_reset_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_featureMatch_lt_32_pblk_update[22];

/* Basic Runner Function */
void vcop_featureMatch_lt_32_pblk_update(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr);
/* Custom Runner Function */
void vcop_featureMatch_lt_32_pblk_update_custom(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_featureMatch_lt_32_pblk_update_init(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_featureMatch_lt_32_pblk_update_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_featureMatch_lt_32_pblk_update ((unsigned int)22)
unsigned int vcop_featureMatch_lt_32_pblk_update_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_featureMatch_lt_32_pblk_update ((unsigned int)0)
unsigned int vcop_featureMatch_lt_32_pblk_update_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_featureMatch_lt_32_pblk_reset[34];

/* Basic Runner Function */
void vcop_featureMatch_lt_32_pblk_reset(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr);
/* Custom Runner Function */
void vcop_featureMatch_lt_32_pblk_reset_custom(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_featureMatch_lt_32_pblk_reset_init(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_featureMatch_lt_32_pblk_reset_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_featureMatch_lt_32_pblk_reset ((unsigned int)34)
unsigned int vcop_featureMatch_lt_32_pblk_reset_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_featureMatch_lt_32_pblk_reset ((unsigned int)0)
unsigned int vcop_featureMatch_lt_32_pblk_reset_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_featureMatch_gt_32_pblk_update[22];

/* Basic Runner Function */
void vcop_featureMatch_gt_32_pblk_update(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr);
/* Custom Runner Function */
void vcop_featureMatch_gt_32_pblk_update_custom(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_featureMatch_gt_32_pblk_update_init(
   __vptr_uint32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short str2ByteIncr,
   unsigned short minDistIncr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_featureMatch_gt_32_pblk_update_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_featureMatch_gt_32_pblk_update ((unsigned int)22)
unsigned int vcop_featureMatch_gt_32_pblk_update_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_featureMatch_gt_32_pblk_update ((unsigned int)0)
unsigned int vcop_featureMatch_gt_32_pblk_update_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_featureMatch_gt_32_pblk_reset[34];

/* Basic Runner Function */
void vcop_featureMatch_gt_32_pblk_reset(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr);
/* Custom Runner Function */
void vcop_featureMatch_gt_32_pblk_reset_custom(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_featureMatch_gt_32_pblk_reset_init(
   __vptr_int32 pFeatureMatchParamBlk,
   __vptr_uint32 pBestMatchesParamBlk,
   unsigned short startIdxIncr,
   unsigned int maxStartIdx,
   unsigned int str2Addr,
   unsigned int minDist0Addr,
   unsigned int minDist1Addr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_featureMatch_gt_32_pblk_reset_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_featureMatch_gt_32_pblk_reset ((unsigned int)34)
unsigned int vcop_featureMatch_gt_32_pblk_reset_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_featureMatch_gt_32_pblk_reset ((unsigned int)0)
unsigned int vcop_featureMatch_gt_32_pblk_reset_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_twoBestMatches_update_n[8];

/* Basic Runner Function */
void vcop_twoBestMatches_update_n(
   __vptr_int16 pBestMatchesParamBlk,
   unsigned short n_new);
/* Custom Runner Function */
void vcop_twoBestMatches_update_n_custom(
   __vptr_int16 pBestMatchesParamBlk,
   unsigned short n_new,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_twoBestMatches_update_n_init(
   __vptr_int16 pBestMatchesParamBlk,
   unsigned short n_new,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_twoBestMatches_update_n_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_twoBestMatches_update_n ((unsigned int)8)
unsigned int vcop_twoBestMatches_update_n_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_twoBestMatches_update_n ((unsigned int)0)
unsigned int vcop_twoBestMatches_update_n_ctrl_count(void);

/***********************************************************/
#endif

