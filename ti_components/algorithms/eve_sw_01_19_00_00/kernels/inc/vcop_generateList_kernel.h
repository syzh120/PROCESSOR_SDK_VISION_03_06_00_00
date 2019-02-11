#ifndef _TI_vcop_generateList_kernel_h_
#define _TI_vcop_generateList_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_generateList[70];

/* Basic Runner Function */
void vcop_generateList(
   __vptr_uint8 pIn,
   __vptr_uint8 pEndRowPadVal,
   __vptr_uint16 pXval,
   __vptr_uint16 pYval,
   __vptr_uint16 pBlockX,
   __vptr_uint16 pBlockY,
   unsigned short numHorzBlock,
   unsigned short numVertBlock,
   __vptr_uint16 pListX,
   __vptr_uint16 pListY,
   __vptr_uint16 pNumElmtsX,
   __vptr_uint16 pNumElmtsY,
   unsigned short maxNumElmts,
   unsigned short width,
   unsigned short height,
   unsigned short inStride,
   unsigned char qShift);
/* Custom Runner Function */
void vcop_generateList_custom(
   __vptr_uint8 pIn,
   __vptr_uint8 pEndRowPadVal,
   __vptr_uint16 pXval,
   __vptr_uint16 pYval,
   __vptr_uint16 pBlockX,
   __vptr_uint16 pBlockY,
   unsigned short numHorzBlock,
   unsigned short numVertBlock,
   __vptr_uint16 pListX,
   __vptr_uint16 pListY,
   __vptr_uint16 pNumElmtsX,
   __vptr_uint16 pNumElmtsY,
   unsigned short maxNumElmts,
   unsigned short width,
   unsigned short height,
   unsigned short inStride,
   unsigned char qShift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_generateList_init(
   __vptr_uint8 pIn,
   __vptr_uint8 pEndRowPadVal,
   __vptr_uint16 pXval,
   __vptr_uint16 pYval,
   __vptr_uint16 pBlockX,
   __vptr_uint16 pBlockY,
   unsigned short numHorzBlock,
   unsigned short numVertBlock,
   __vptr_uint16 pListX,
   __vptr_uint16 pListY,
   __vptr_uint16 pNumElmtsX,
   __vptr_uint16 pNumElmtsY,
   unsigned short maxNumElmts,
   unsigned short width,
   unsigned short height,
   unsigned short inStride,
   unsigned char qShift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_generateList_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_generateList ((unsigned int)70)
unsigned int vcop_generateList_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_generateList ((unsigned int)0)
unsigned int vcop_generateList_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_updateGenerateList[16];

/* Basic Runner Function */
void vcop_updateGenerateList(
   __vptr_uint32 preg,
   unsigned int pListX,
   unsigned int pListY,
   __vptr_uint16 pNumElmtsX,
   unsigned short listXOfst,
   unsigned short listYOfst);
/* Custom Runner Function */
void vcop_updateGenerateList_custom(
   __vptr_uint32 preg,
   unsigned int pListX,
   unsigned int pListY,
   __vptr_uint16 pNumElmtsX,
   unsigned short listXOfst,
   unsigned short listYOfst,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_updateGenerateList_init(
   __vptr_uint32 preg,
   unsigned int pListX,
   unsigned int pListY,
   __vptr_uint16 pNumElmtsX,
   unsigned short listXOfst,
   unsigned short listYOfst,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_updateGenerateList_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_updateGenerateList ((unsigned int)16)
unsigned int vcop_updateGenerateList_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_updateGenerateList ((unsigned int)0)
unsigned int vcop_updateGenerateList_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_copyListToOutBuff[22];

/* Basic Runner Function */
void vcop_copyListToOutBuff(
   __vptr_uint16 pListX,
   __vptr_uint16 pListY,
   __vptr_uint16 pListXY,
   __vptr_uint16 pNumElmts,
   __vptr_uint16 pNumElmtsOut,
   unsigned short NumElmts,
   unsigned short offsetX,
   unsigned short offsetY);
/* Custom Runner Function */
void vcop_copyListToOutBuff_custom(
   __vptr_uint16 pListX,
   __vptr_uint16 pListY,
   __vptr_uint16 pListXY,
   __vptr_uint16 pNumElmts,
   __vptr_uint16 pNumElmtsOut,
   unsigned short NumElmts,
   unsigned short offsetX,
   unsigned short offsetY,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_copyListToOutBuff_init(
   __vptr_uint16 pListX,
   __vptr_uint16 pListY,
   __vptr_uint16 pListXY,
   __vptr_uint16 pNumElmts,
   __vptr_uint16 pNumElmtsOut,
   unsigned short NumElmts,
   unsigned short offsetX,
   unsigned short offsetY,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_copyListToOutBuff_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_copyListToOutBuff ((unsigned int)22)
unsigned int vcop_copyListToOutBuff_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_copyListToOutBuff ((unsigned int)0)
unsigned int vcop_copyListToOutBuff_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_copyNumElementsToOutBuff_init[8];

/* Basic Runner Function */
void vcop_copyNumElementsToOutBuff_init(
   __vptr_uint16 src,
   __vptr_uint16 dst);
/* Custom Runner Function */
void vcop_copyNumElementsToOutBuff_init_custom(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_copyNumElementsToOutBuff_init_init(
   __vptr_uint16 src,
   __vptr_uint16 dst,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_copyNumElementsToOutBuff_init_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_copyNumElementsToOutBuff_init ((unsigned int)8)
unsigned int vcop_copyNumElementsToOutBuff_init_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_copyNumElementsToOutBuff_init ((unsigned int)0)
unsigned int vcop_copyNumElementsToOutBuff_init_ctrl_count(void);

/***********************************************************/
#endif

