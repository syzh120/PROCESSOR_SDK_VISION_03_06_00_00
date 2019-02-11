/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2007-2012 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/
#include "../common/VLIB_test.h"
#include "../common/VLIB_memory.h"
#include "../common/VLIB_profile.h"

/* Blob analysis works on the processing result of connected component labeling, so CCL header file is included */
#include "../VLIB_Connected_Components_Labeling/VLIB_Connected_Components_Labeling.h"

/* blob analysis head files */
#include "VLIB_blobAnalysis.h"
#include "VLIB_blobAnalysis_cn.h"
#include "VLIB_blobAnalysis_idat.h"

#define  GENERATE_MATLAB       (0)
/* The MINBLOBAREA must be set to 1 */
#define  MINBLOBAREA           (1)
#define  ERROR_THRESHOLD       (0.05f)

uint32_t blobAnalysis_malloc(uint32_t *ptr,
                             int32_t sizeInByte);

uint32_t convert_uint8_to_packedBits(uint8_t *img,
                                     uint8_t *mask,
                                     int32_t imageHeight,
                                     int32_t imageWidth);

uint32_t convert_uint8_to_packedBits(
    uint8_t *img,
    uint8_t *mask,
    int32_t imageHeight,
    int32_t imageWidth)
{
    int32_t     i, j, k, n, m, roundWidth;
    uint32_t    wordMask, wordMask_tmp, flag;

    k = 0;
    n = 0;

    roundWidth = (imageWidth >> 5) << 5;
    wordMask_tmp = 32 - (imageWidth - roundWidth);

    /* X86 (ANSI C) does not support a right shift of 32 for a uint32_t, so this condition
       is to ensure this case */
    if( wordMask_tmp == 32 ) {
        wordMask = 0;
    } else {
        wordMask =  (0xffffffff >> wordMask_tmp) << wordMask_tmp;
    }

    for( i = 0; i < imageHeight; i++ ) {
        for( j = 0; j < roundWidth; j+=32 ) {
            flag = 0;

            for( m = 0; m < 32; m++ ) {
                flag += (img[k + m] > 0) << (31 - m);
            }

            mask[n + 3] = (flag >> 24) & 0xff;
            mask[n + 2] = (flag >> 16) & 0xff;
            mask[n + 1] = (flag >> 8) & 0xff;
            mask[n + 0] = (flag >> 0) & 0xff;
            k += 32;
            n+=4;
        }

        if( wordMask ) {
            flag = 0;

            for( m = 0; m < 32; m++ ) {
                flag += (img[k + m] > 0) << (31 - m);
            }

            k += (imageWidth - roundWidth);
            flag &= wordMask;
            mask[n + 3] = (flag >> 24) & 0xff;
            mask[n + 2] = (flag >> 16) & 0xff;
            mask[n + 1] = (flag >> 8) & 0xff;
            mask[n + 0] = (flag >> 0) & 0xff;
            n+=4;
        }
    }

    if( wordMask ) {
        return (roundWidth + 32);
    } else {
        return (roundWidth);
    }
}

uint32_t  blobAnalysis_malloc(uint32_t *ptr, int sizeInByte)
{
    uint32_t    tmpPtr;

    tmpPtr = (*ptr + 7) & 0xfffffff8;
    *ptr = ((tmpPtr + sizeInByte + 7) & 0xfffffff8);
    return (tmpPtr);
}

/* VLIB_blobAnalysis_d:  Test Driver Routine */
int32_t VLIB_blobAnalysis_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */
    int32_t    status = 0;

    /* Test Parameters */
    blobAnalysis_testParams_t   *prm;

    blobAnalysis_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_blobAnalysis");
    printf("                                                                                      num of blobs, scratch buffer size (in bytes) for\n");
    printf("                                                                                                              CCL,  Create Blob list, Blob analysis\n");

    /* Run each test case */
    for( tpi = 0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS;  /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS;  /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size =   prm[tpi].imageWidth * prm[tpi].imageHeight;

        /* Allocate buffers for each test vector */
        uint8_t   *input_image      =  (uint8_t *) malloc(inp_size);

        if( input_image ) {

            int32_t          i, maxBytesRequired, eightConnected, sizeOfCCHandle;
            int32_t          numCCs;
            VLIB_blobList    imagBlobs, imagBlobs_cn;
            void            *blobListScratch, *blobListScratch_cn;
            void            *pBlobScratch = NULL, *pBlobScratch_cn = NULL;
            uint32_t         tmpPtr, tmpPtr_cn;

            VLIB_CCHandle   *handle;
            uint32_t        *maskBuf;
            void            *CCLBuf;
            uint8_t         *CCMap;

            int32_t    ccMapSize;
            int32_t    maskBufSize;
            int32_t    fail;
            int32_t    ccl_totalBuf;
            int32_t    blobList_totalBuf;
            int32_t    Blob_analysis_totalBuf;

            int32_t    imageWidth        = prm[tpi].imageWidth;
            int32_t    imageHeight       = prm[tpi].imageHeight;

            uint32_t                   *perimeter, *perimeter_cn;
            VLIB_blobAnalysis_box      *boxes, *boxes_cn;
            VLIB_blobAnalysis_circle   *circles, *circles_cn;
            VLIB_blobAnalysis_point    *blobBoundary, *blobBoundary_cn;
            VLIB_blobAnalysis_point    *polygonBoundary, *polygonBoundary_cn;
            AVMii                      *blob_ii, *blob_ii_cn;
            VLIB_blob                  *vlibBlobList, *vlibBlobList_cn;

            int32_t    maxSize_x, maxSize_y;
            int32_t    numBlobs;
            int32_t    maxNumItervals;

            uint32_t    boxBufSize, circleBufSize, boundaryBufSize;
            uint32_t    polygonBufSize, blobIIBufSize, perimeterBufSize;

            int32_t    error;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            input_image, prm[tpi].staticIn,
                            prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].imageWidth * sizeof(input_image[0]),
                            sizeof(input_image[0]), testPatternString);

            /* Threshold random input to make it binary image */
            if( prm[tpi].testPattern == RANDOM ) {
                for( i=0; i < inp_size; i++ ) {
                    input_image[i] = (input_image[i] > 100) ? 1 : 0;
                }
            }

            /* =============================== Connected component labeling =============================== */
            /* Allocate scratch buffer for CC labeling */
            sizeOfCCHandle =  VLIB_GetSizeOfCCHandle();
            maskBufSize    = ((imageWidth + 31) / 32) * imageHeight * sizeof(uint32_t);
            ccMapSize      = (imageWidth + 31) / 32 * 32 * imageHeight * sizeof(uint8_t);
            VLIB_calcConnectedComponentsMaxBufferSize(imageWidth, imageHeight, MINBLOBAREA, &maxBytesRequired);
            ccl_totalBuf = maskBufSize + sizeOfCCHandle + maxBytesRequired + ccMapSize + 8 * 4;

            handle  = (VLIB_CCHandle *)malloc(sizeOfCCHandle);
            maskBuf = (uint32_t      *)malloc(maskBufSize);
            CCLBuf  = (void          *)malloc(maxBytesRequired);
            CCMap   = (uint8_t       *)malloc(ccMapSize);

            if( handle == NULL || maskBuf == NULL || CCLBuf == NULL || CCMap == NULL ) {
                free(input_image);
                free(handle);
                free(maskBuf);
                free(CCLBuf);
                free(CCMap);
                goto SKIP_TEST;
            }

            /* convert_uint8_to_packedBits */
            memset(maskBuf, 0, maskBufSize);
            imageWidth = convert_uint8_to_packedBits(
                input_image,
                (uint8_t *)maskBuf,
                imageHeight,
                imageWidth);

            status  = VLIB_initConnectedComponentsList(handle, CCLBuf, maxBytesRequired);

            eightConnected = 2;
            status = VLIB_createConnectedComponentsList(
                handle,
                imageWidth,
                imageHeight,
                maskBuf,
                MINBLOBAREA,
                eightConnected - 1);
            VLIB_getNumCCs(handle, &numCCs);

            memset(CCMap, 0, ccMapSize);
            status = VLIB_createCCMap8Bit(
                handle,
                CCMap,
                imageWidth,
                imageHeight);

            /* =============================== create blob list  =============================== */
            blobList_totalBuf  =  sizeof(VLIB_blob) * numCCs;
            blobListScratch    =  VLIB_malloc(blobList_totalBuf);
            blobListScratch_cn =  malloc(blobList_totalBuf);

            if((blobListScratch == NULL) || (blobListScratch_cn == NULL)) {
                if( blobListScratch ) {
                    VLIB_free(blobListScratch);
                }
                if( blobListScratch_cn ) {
                    free(blobListScratch_cn);
                }
                free(input_image);
                goto SKIP_TEST;
            }

            tmpPtr    = (uint32_t)blobListScratch;
            tmpPtr_cn = (uint32_t)blobListScratch_cn;

            imagBlobs.blobList  = (VLIB_blob *)blobAnalysis_malloc(&tmpPtr, blobList_totalBuf);
            imagBlobs_cn.blobList  = (VLIB_blob *)blobAnalysis_malloc(&tmpPtr_cn, blobList_totalBuf);

            VLIB_createBlobList(handle,
                                &imagBlobs);

            VLIB_createBlobList_cn(handle,
                                   &imagBlobs_cn);

            error = 0;
            if((imagBlobs.maxSize_y != imagBlobs_cn.maxSize_y) ||\
               (imagBlobs.maxSize_x != imagBlobs_cn.maxSize_x) ||\
               (imagBlobs.numBlobs != imagBlobs_cn.numBlobs) ||\
               (imagBlobs.maxNumItervals != imagBlobs_cn.maxNumItervals)) {
                error++;
            }

            if( error > 0 ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
                goto FREE_AND_CONTINUE;
            }

            vlibBlobList        = imagBlobs.blobList;
            vlibBlobList_cn     = imagBlobs_cn.blobList;

            for( i = 0; i < imagBlobs.numBlobs; i++ ) {
                if((vlibBlobList[i].xmin != vlibBlobList_cn[i].xmin) || \
                   (vlibBlobList[i].xmax != vlibBlobList_cn[i].xmax) || \
                   (vlibBlobList[i].ymin != vlibBlobList_cn[i].ymin) || \
                   (vlibBlobList[i].ymax != vlibBlobList_cn[i].ymax) || \
                   (vlibBlobList[i].area != vlibBlobList_cn[i].area) || \
                   (vlibBlobList[i].numIntervals != vlibBlobList_cn[i].numIntervals) || \
                   (vlibBlobList[i].iiValue != vlibBlobList_cn[i].iiValue) || \
                   (vlibBlobList[i].ccmapColor != vlibBlobList_cn[i].ccmapColor)) {
                    error++;
                }
            }

            if( error > 0 ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
                goto FREE_AND_CONTINUE;
            }
            /* =============================== blob analysis =============================== */
            /* Allocate scratch buffer for blob analysis */
            maxSize_y        = imagBlobs.maxSize_y;
            maxSize_x        = imagBlobs.maxSize_x;
            numBlobs         = imagBlobs.numBlobs;
            maxNumItervals   = imagBlobs.maxNumItervals;
            vlibBlobList     = imagBlobs.blobList;

            boxBufSize      = sizeof(VLIB_blobAnalysis_box) * numBlobs;
            circleBufSize   = sizeof(VLIB_blobAnalysis_circle) * numBlobs;
            boundaryBufSize = sizeof(VLIB_blobAnalysis_point) * (maxSize_y + maxSize_x) * 2;
            polygonBufSize  = sizeof(VLIB_blobAnalysis_point) * (maxSize_y + maxSize_x) * 2;
            VLIB_getblobIIBufSize(imageHeight, maxNumItervals, &blobIIBufSize);
            perimeterBufSize= sizeof(int32_t) * numBlobs;

            Blob_analysis_totalBuf = boxBufSize       +\
                                     circleBufSize    +\
                                     boundaryBufSize  +\
                                     polygonBufSize   +\
                                     blobIIBufSize    +\
                                     perimeterBufSize + 8 * 6;
            pBlobScratch       = VLIB_malloc(Blob_analysis_totalBuf);
            pBlobScratch_cn    = malloc(Blob_analysis_totalBuf);

            /* Only run the test if the buffer allocations fit in the heap */
            if( pBlobScratch && pBlobScratch_cn ) {

                /* Blob analysis using optimized c66 code */
                tmpPtr = (uint32_t)pBlobScratch;
                boxes           = (VLIB_blobAnalysis_box     *)blobAnalysis_malloc(&tmpPtr, boxBufSize);
                circles         = (VLIB_blobAnalysis_circle  *)blobAnalysis_malloc(&tmpPtr, circleBufSize);
                blobBoundary    = (VLIB_blobAnalysis_point   *)blobAnalysis_malloc(&tmpPtr, boundaryBufSize);
                polygonBoundary = (VLIB_blobAnalysis_point   *)blobAnalysis_malloc(&tmpPtr, polygonBufSize);
                blob_ii         = (AVMii                     *)blobAnalysis_malloc(&tmpPtr, blobIIBufSize);
                perimeter       = (uint32_t                 *)blobAnalysis_malloc(&tmpPtr, perimeterBufSize);

                /* Test optimized kernel */
                VLIB_profile_start(vlib_KERNEL_OPT);

                for( i = 0; i < numBlobs; i++ ) {
                    int32_t    numPolygonPt;

                    /* Construct the interval image for the blob */
                    VLIB_createBlobIntervalImg(handle, blob_ii, &vlibBlobList[i]);

                    /* calculate the perimeter */
                    VLIB_calcBlobPerimeter(
                        imagBlobs.blobList[i].ccmapColor,
                        imageWidth,
                        blob_ii,
                        CCMap,
                        &perimeter[i]);

                    VLIB_calcBlobMinEnclosedPolygon(blob_ii, blobBoundary, polygonBoundary, &numPolygonPt);

                    VLIB_calcBlobMinEnclosedRect(numPolygonPt, polygonBoundary, &boxes[i]);

                    VLIB_calcBlobMinEnclosedCircle(numPolygonPt, polygonBoundary, &circles[i]);
                }

                VLIB_profile_stop();

                /* Blob analysis using normal C code */
                tmpPtr = (uint32_t)pBlobScratch_cn;
                boxes_cn           = (VLIB_blobAnalysis_box     *)blobAnalysis_malloc(&tmpPtr, boxBufSize);
                circles_cn         = (VLIB_blobAnalysis_circle  *)blobAnalysis_malloc(&tmpPtr, circleBufSize);
                blobBoundary_cn    = (VLIB_blobAnalysis_point   *)blobAnalysis_malloc(&tmpPtr, boundaryBufSize);
                polygonBoundary_cn = (VLIB_blobAnalysis_point   *)blobAnalysis_malloc(&tmpPtr, polygonBufSize);
                blob_ii_cn         = (AVMii                     *)blobAnalysis_malloc(&tmpPtr, blobIIBufSize);
                perimeter_cn       = (uint32_t                  *)blobAnalysis_malloc(&tmpPtr, perimeterBufSize);

                /* Test _cn kernel */
                VLIB_profile_start(vlib_KERNEL_CN);

                for( i = 0; i < numBlobs; i++ ) {
                    int32_t    numPolygonPt_cn;

                    /* Construct the interval image for the blob */
                    VLIB_createBlobIntervalImg_cn(handle, blob_ii_cn, &vlibBlobList_cn[i]);

                    /* calculate the perimeter */
                    VLIB_calcBlobPerimeter_cn(
                        imagBlobs_cn.blobList[i].ccmapColor,
                        imageWidth,
                        blob_ii_cn,
                        CCMap,
                        &perimeter_cn[i]);

                    VLIB_calcBlobMinEnclosedPolygon_cn(blob_ii_cn, blobBoundary_cn, polygonBoundary_cn, &numPolygonPt_cn);

                    VLIB_calcBlobMinEnclosedRect_cn(numPolygonPt_cn, polygonBoundary_cn, &boxes_cn[i]);

                    VLIB_calcBlobMinEnclosedCircle_cn(numPolygonPt_cn, polygonBoundary_cn, &circles_cn[i]);
                }

                VLIB_profile_stop();

                /* Compare natural C Output and Optimized Output */
                for( i = 0; i < numBlobs; i++ ) {
                    error += perimeter[i] != perimeter_cn[i];
                    error += vlibBlobList[i].ccmapColor != vlibBlobList_cn[i].ccmapColor;

                    error += vlibBlobList[i].area != vlibBlobList_cn[i].area;
                    /* Verify the bounding rectangle */
                    error += vlibBlobList[i].ymin != vlibBlobList_cn[i].ymin;
                    error += vlibBlobList[i].ymax != vlibBlobList_cn[i].ymax;
                    error += vlibBlobList[i].xmin != vlibBlobList_cn[i].xmin;
                    error += vlibBlobList[i].xmax != vlibBlobList_cn[i].xmax;
                    /* Verify the minimal enclosed circle */
                    error += fabs(circles[i].x      - circles_cn[i].x) > ERROR_THRESHOLD;
                    error += fabs(circles[i].y      - circles_cn[i].y) > ERROR_THRESHOLD;
                    error += fabs(circles[i].radius - circles_cn[i].radius) > ERROR_THRESHOLD;

                    /* Verify the minimal enclosed rectangle */
                    /* In the procedure of calculating minimal enclosed rectangle, the optimized
                       code uses _rcpsp and _rsqrsp to calculate Reciprocal and Square-Root Reciprocal
                       although Newton-Rhapson interpolation is used to further extend the mantissa's
                       precision, but still has precission difference comparing with standard math lib.
                       As a result, the output rectangle may be presented slightly different:
                                                   center.x  center.y  rotate degree  width   height
                      normal C reference result:    29.500,     4.5,        90.0,      7.00,  23.00
                      optimized C result:           29.500,     4.5,         0.0,     23.00,   7.00
                      So, special processing is needed for verification.
                     */
                    error += fabs(boxes[i].x - boxes_cn[i].x) > ERROR_THRESHOLD;
                    error += fabs(boxes[i].y - boxes_cn[i].y) > ERROR_THRESHOLD;
                    if( fabs(boxes[i].angle - boxes_cn[i].angle - 0.f) < ERROR_THRESHOLD ) {
                        error += fabs(boxes[i].w - boxes_cn[i].w) > ERROR_THRESHOLD;
                        error += fabs(boxes[i].h - boxes_cn[i].h) > ERROR_THRESHOLD;
                    } else if( fabs(fabs(boxes[i].angle - boxes_cn[i].angle) - 90.f) < ERROR_THRESHOLD ) {
                        error += fabs(boxes[i].w - boxes_cn[i].h) > ERROR_THRESHOLD;
                        error += fabs(boxes[i].h - boxes_cn[i].w) > ERROR_THRESHOLD;
                    } else if( fabs(fabs(boxes[i].angle - boxes_cn[i].angle) - 180.f) < ERROR_THRESHOLD ) {
                        error += fabs(boxes[i].w - boxes_cn[i].w) > ERROR_THRESHOLD;
                        error += fabs(boxes[i].h - boxes_cn[i].h) > ERROR_THRESHOLD;
                    } else {
                        error++;
                    }
                }

                status_nat_vs_int = (error == 0) ? vlib_KERNEL_PASS : vlib_KERNEL_FAIL;

                /* If static output is available, then additionally compares natural C output with static reference output data */
                if( prm[tpi].staticOut != NULL ) {
                    if( prm[tpi].numBlobs == numBlobs ) {
                        blobAnalysis_resultParams_t   *staticOutPtr;
                        staticOutPtr = prm[tpi].staticOut;
                        error = 0;

                        for( i = 0; i < numBlobs; i++ ) {
                            error += perimeter[i] != staticOutPtr[i].perimeter;
                            error += vlibBlobList[i].ccmapColor != staticOutPtr[i].ccMapColor;

                            error += vlibBlobList[i].area != staticOutPtr[i].area;
                            /* Verify the bounding rectangle */
                            error += vlibBlobList[i].ymin != staticOutPtr[i].ymin;
                            error += vlibBlobList[i].ymax + 1 != staticOutPtr[i].ymax;
                            error += vlibBlobList[i].xmin != staticOutPtr[i].xmin;
                            error += vlibBlobList[i].xmax + 1 != staticOutPtr[i].xmax;
                            /* Verify the minimal enclosed circle */
                            error += fabs(circles[i].x - staticOutPtr[i].circle_x) > ERROR_THRESHOLD;
                            error += fabs(circles[i].y - staticOutPtr[i].circle_y) > ERROR_THRESHOLD;
                            error += fabs(circles[i].radius - staticOutPtr[i].circle_r) > ERROR_THRESHOLD;

                            /* Verify the minimal enclosed rectangle */
                            /* In the procedure of calculating minimal enclosed rectangle, the optimized
                               code uses _rcpsp and _rsqrsp to calculate Reciprocal and Square-Root Reciprocal
                               although Newton-Rhapson interpolation is used to further extend the mantissa's
                               precision, but still has precission difference comparing with standard math lib.
                               As a result, the output rectangle may be presented slightly different:
                                                           center.x  center.y  rotate degree  width   height
                              normal C reference result:    29.500,     4.5,        90.0,      7.00,  23.00
                              optimized C result:           29.500,     4.5,         0.0,     23.00,   7.00
                              So, special processing is needed for verification.
                             */
                            error += fabs(boxes[i].x - staticOutPtr[i].rect_center_x) > ERROR_THRESHOLD;
                            error += fabs(boxes[i].y - staticOutPtr[i].rect_center_y) > ERROR_THRESHOLD;

                            if( fabs(fabs(boxes[i].angle - staticOutPtr[i].rect_sita) - 0.f) < ERROR_THRESHOLD ) {
                                error += fabs(boxes[i].w - staticOutPtr[i].rect_width) > ERROR_THRESHOLD;
                                error += fabs(boxes[i].h - staticOutPtr[i].rect_height) > ERROR_THRESHOLD;
                            } else if( fabs(fabs(boxes[i].angle - staticOutPtr[i].rect_sita) - 90.f) < ERROR_THRESHOLD ) {
                                error += fabs(boxes[i].w - staticOutPtr[i].rect_height) > ERROR_THRESHOLD;
                                error += fabs(boxes[i].h - staticOutPtr[i].rect_width) > ERROR_THRESHOLD;
                            } else if( fabs(fabs(boxes[i].angle - staticOutPtr[i].rect_sita) - 180.f) < ERROR_THRESHOLD ) {
                                error += fabs(boxes[i].w - staticOutPtr[i].rect_width) > ERROR_THRESHOLD;
                                error += fabs(boxes[i].h - staticOutPtr[i].rect_height) > ERROR_THRESHOLD;
                            } else {
                                error++;
                            }
                        }

                        status_nat_vs_ref = (error > 0) ? vlib_KERNEL_FAIL : vlib_KERNEL_PASS;
                    } else {
                        status_nat_vs_ref = vlib_KERNEL_FAIL;
                    }
                }

FREE_AND_CONTINUE:
                /* Set the 'fail' flag based on test vector comparison results */
                fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;
                est_test=1;

                /* Profile display and preparation for cycle estimation */
                sprintf(desc, "%3d blobs, %8d bytes, %6d bytes, %6d bytes",\
                        (int)numBlobs,
                        ccl_totalBuf,\
                        blobList_totalBuf,\
                        Blob_analysis_totalBuf);
                VLIB_formula_add_test(imageWidth * imageHeight, (int)NULL, (int)NULL, fail, desc, (int)NULL);

                /*************************************************************************************************/

                #if GENERATE_MATLAB
                FILE      *fmat;
                int32_t    xmin, ymin, xmax, ymax, area;
                char       name[32]={ "..\\..\\" };

                sprintf(&name[6], "img%d.m", tpi + 1);

                fmat = fopen(name, "w");
                fprintf(fmat, "bmp = [\n");

                for( i = 0; i < prm[tpi].imageHeight; i++ ) {
                    int    j;

                    for( j = 0; j < prm[tpi].imageWidth; j++ ) {
                        fprintf(fmat, "%2d", prm[tpi].staticIn[i * prm[tpi].imageWidth + j] > 0);
                    }

                    fprintf(fmat, "\n");
                }

                fprintf(fmat, "];\n");
                fprintf(fmat, "colormap('gray');\n");
                fprintf(fmat, "imagesc(bmp)\n");
                fprintf(fmat, "\n");

                fprintf(fmat, " center=[\n");

                for( i = 0; i < numBlobs; i++ ) {
                    ymin = vlibBlobList[i].ymin;
                    ymax = vlibBlobList[i].ymax + 1;
                    xmin = vlibBlobList[i].xmin;
                    xmax = vlibBlobList[i].xmax + 1;
                    area = vlibBlobList[i].area;
                    fprintf(fmat, " %3d, %4d, %4d, %4d, %4d, %4d, %4d, %3.3f, %3.2f, %3.2f, %3.2f, %3.2f, %3.2f, %3.2f, %3.2f\n", vlibBlobList[i].ccmapColor, area, perimeter[i], xmin, ymin, xmax, ymax,\
                            boxes[i].x, boxes[i].y, boxes[i].angle,\
                            boxes[i].w, boxes[i].h,\
                            circles[i].x, circles[i].y, circles[i].radius);
                }

                fprintf(fmat, "];\n");

                /* matlab code to draw the rectangle */
                fprintf(fmat, "for i = 1:size(center,1)\n");
                fprintf(fmat, "base = 7;               \n");
                fprintf(fmat, "  x = center(i,base+1);                                  \n");
                fprintf(fmat, "  y = center(i,base+2);                                  \n");
                fprintf(fmat, "  sita = center(i,base+3)/90*pi/2;                       \n");
                fprintf(fmat, "  imageWidth = center(i,base+4);                              \n");
                fprintf(fmat, "  imageHeight = center(i,base+5);                             \n");
                fprintf(fmat, "                                                         \n");
                fprintf(fmat, "  A(1) = x + imageHeight/2*cos(pi/2+sita);                    \n");
                fprintf(fmat, "  A(2) = y + imageHeight/2*sin(pi/2+sita);                    \n");
                fprintf(fmat, "  B(1) = x + imageWidth/2*cos(sita);                          \n");
                fprintf(fmat, "  B(2) = y + imageWidth/2*sin(sita);                          \n");
                fprintf(fmat, "  C(1) = x - imageHeight/2*cos(pi/2+sita);                    \n");
                fprintf(fmat, "  C(2) = y - imageHeight/2*sin(pi/2+sita);                    \n");
                fprintf(fmat, "  D(1) = x - imageWidth/2*cos(sita);                          \n");
                fprintf(fmat, "  D(2) = y - imageWidth/2*sin(sita);                          \n");
                fprintf(fmat, "                                                         \n");
                fprintf(fmat, "  Left_bottom(1)  = C(1) - imageWidth/2*cos(sita);            \n");
                fprintf(fmat, "  Left_bottom(2)  = C(2) - imageWidth/2*sin(sita);            \n");
                fprintf(fmat, "  Left_top(1)     = D(1) + imageHeight/2*cos(pi/2+sita);      \n");
                fprintf(fmat, "  Left_top(2)     = D(2) + imageHeight/2*sin(pi/2+sita);      \n");
                fprintf(fmat, "  Right_top(1)    = A(1) + imageWidth/2*cos(sita);            \n");
                fprintf(fmat, "  Right_top(2)    = A(2) + imageWidth/2*sin(sita);            \n");
                fprintf(fmat, "  Right_bottom(1) = B(1) - imageHeight/2*cos(pi/2+sita);      \n");
                fprintf(fmat, "  Right_bottom(2) = B(2) - imageHeight/2*sin(pi/2+sita);      \n");
                fprintf(fmat, "                                                         \n");
                fprintf(fmat, "  a = [Left_bottom; Left_top; Right_bottom; Right_top];  \n");
                fprintf(fmat, "  a = a + 1;\n");
                fprintf(fmat, "  position = [a(1,:);a(2,:)]; position = position'; line(position(1,:),position(2,:),'color','g');\n");
                fprintf(fmat, "  position = [a(2,:);a(4,:)]; position = position'; line(position(1,:),position(2,:),'color','g');\n");
                fprintf(fmat, "  position = [a(4,:);a(3,:)]; position = position'; line(position(1,:),position(2,:),'color','g');\n");
                fprintf(fmat, "  position = [a(3,:);a(1,:)]; position = position'; line(position(1,:),position(2,:),'color','g');\n");
                fprintf(fmat, "  text(x,y,int2str(center(i)))\n");
                fprintf(fmat, "end\n");

                /* matlab code to draw the circle */
                fprintf(fmat, "hold on;                                            \n");
                fprintf(fmat, "sita = (2*pi/360*[0:359]);                          \n");
                fprintf(fmat, "for i = 1: size(center,1)                           \n");
                fprintf(fmat, "    x = center(i,base+6)+1;                         \n");
                fprintf(fmat, "    y = center(i,base+7)+1;                         \n");
                fprintf(fmat, "    r = center(i,base+8);                           \n");
                fprintf(fmat, "    circle = [x + r*sin(sita); y + r*cos(sita)];    \n");
                fprintf(fmat, "    plot(circle(1,:),circle(2,:),'r');              \n");
                fprintf(fmat, "    hold on;                                        \n");
                fprintf(fmat, "end                                                 \n");
                fclose(fmat);
                #endif  /* #if GENERATE_MATLAB */
                /*************************************************************************************************/

            } else {
                /* Display the error printout for this test vector before moving on to the next test vector */
                sprintf(desc, "imageWidth=%d, imageHeight=%d",
                        (int)imageWidth, (int)imageHeight);
                VLIB_skip_test(desc);
            }

            /* Free buffers for each test vector */
            if( pBlobScratch_cn ) {
                free(pBlobScratch_cn);
            }
            if( pBlobScratch ) {
                VLIB_free(pBlobScratch);
            }

            free(blobListScratch_cn);
            VLIB_free(blobListScratch);
            free(CCMap);
            free(CCLBuf);
            free(maskBuf);
            free(handle);
            free(input_image);

        } else {
SKIP_TEST:
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "imageWidth=%d, imageHeight=%d",
                    prm[tpi].imageWidth, prm[tpi].imageHeight);
            VLIB_skip_test(desc);
        }
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "imageWidth * imageHeight");

    /* Provide memory requirements */
    VLIB_kernel_memory();

    return (status);
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST
int  main()
{
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_BlobAnalysis");
    } else {
        VLIB_blobAnalysis_d(0);
    }
    return (0);
}

#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_blobAnalysis_d.c                                     */
/* ======================================================================== */

