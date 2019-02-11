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
**|         Copyright (c) 2015 Texas Instruments Incorporated                |**
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

#ifndef VLIB_HAARDETECTOBJECT_TYPES_H_
#define VLIB_HAARDETECTOBJECT_TYPES_H_ 1

#include "VLIB_types.h"

/*! Maximum number of rectangles in a node */
#define VLIB_HAARDETOBJ_MAX_RECT_PER_NODE      (3)

/*! For word aligned memory. It should be ((VLIB_HAARDETOBJ_MAX_RECT_PER_NODE + 0x3) & 0xFFFFFFFCU) */
#define VLIB_HAARDETOBJ_MAX_RECT_PER_NODE_A    (4)

/*! Maximum number of nodes per tree */
#define VLIB_HAARDETOBJ_MAX_NODE_PER_TREE      (3)

/*! It should be VLIB_HAARDETOBJ_MAX_NODE_PER_TREE. 2^VLIB_HAARDETOBJ_MAX_NODE_PER_TREE */
#define VLIB_HAARDETOBJ_MAX_LEAVE_PER_TREE     (8)

/*! Total Number of week classifier i.e. number of stages */
#define VLIB_HAARDETOBJ_MAX_STAGES             (32)

/**
 *******************************************************************************
 *  @struct VLIB_HAARDETOBJ_sRect
 *  @brief  Defines each feature-rectangle's property from base location. Base location
 *          is the top left location of probable object patch. E.g if the base location
 *          is (x,y) then feature rectangle will be placed at (x + offsetTL, y + offsetTR).
 *          Hence as base location changes, feature-rectangle property remains same.
 *
 *  @param offsetTL   Offset of top left corner of rectangular feature from base location
 *  @param offsetTR   Offset of top right corner of rectangular feature from base location
 *  @param offsetBL   Offset of bottom left corner of rectangular feature from base location
 *  @param offsetBR   Offset of bottom right corner of rectangular feature from base location
 *******************************************************************************
*/

typedef struct {
    int16_t offsetTL;       /*!< Offset of top left corner of rectangular feature from base location */
    int16_t offsetTR;       /*!< Offset of top right corner of rectangular feature from base location */
    int16_t offsetBL;       /*!< Offset of bottom left corner of rectangular feature from base location */
    int16_t offsetBR;       /*!< Offset of bottom right corner of rectangular feature from base location */
} VLIB_HAARDETOBJ_sRect;

/**
 *******************************************************************************
 *  @enum VLIB_HAARDETOBJ_rectType
 *  @brief  This enum defines Haar feature (rectangle) type. This is helpfull in
 *          providing the rectangle property so that some of the data reads can be
 *          avoided in Haar feature calculation
 *
 *  @param VLIB_HAAR_X2    Two adjacent rectangles, with one of the common vertical edge.
 *                         Basically one bigger rectangle divided horizontally
 *                         into two smaller rectangles.
                            @verbatim
                              _ _ _ _ _ _ _ _ _ _ _ _ _ _
                             |              |             |
                             |      #1      |   #2        |
                             |              |             |
                             |_ _ _ _ _ _ _ |_ _ _ _ _ _ _|
                            @endverbatim
 *
 *  @param VLIB_HAAR_Y2    Two adjacent rectangles, with one of the common horizontal edge.
 *                         Basically one bigger rectangle divided vertically
 *                         into two smaller rectangles.
                            @verbatim
                              _ _ _ _ _ _ _
                             |      #1      |
                             |_ _ _ _ _ _ _ |
                             |      #2      |
                             |_ _ _ _ _ _ _ |
                            @endverbatim
 *
 *  @param VLIB_HAAR_X2_Y2 A particular three rectangle scenario. First rectangle is the
 *                         outer bigger rectangle, and other two rectangles are diagnoal
 *                         inner rectangles.
                            @verbatim
                              _ _ _ _ _ _ _ _ _ _ _ _ _ _ _#1
                             |      #2       |             |
                             |_ _ _ _ _ _ _ _|_ _ _ _ _ _ _|
                             |               |    #3       |
                             |_ _ _ _ _ _ _ _|_ _ _ _ _ _ _|
                            @endverbatim
 *
 *  @param VLIB_HAAR_GEN2  Generic two rectangle scenario
 *
 *  @param VLIB_HAAR_GEN3  Generic three rectangle scenario
 *******************************************************************************
 */

typedef enum {
    VLIB_HAAR_X2 = 1,   /*!< Two adjacent rectangles, with one of the common vertical edge. */
    VLIB_HAAR_Y2,       /*!< Two adjacent rectangles, with one of the common horizontal edge. */
    VLIB_HAAR_X2_Y2,    /*!< A particular three rectangle scenario. */
    VLIB_HAAR_GEN2,     /*!< Generic two rectangle scenario */
    VLIB_HAAR_GEN3      /*!< Generic three rectangle scenario */
} VLIB_HAARDETOBJ_rectType;

/**
 *******************************************************************************
 *  @struct VLIB_HAARDETOBJ_sTree
 *  @brief  This structure holds property of one tree. Each tree has maximum
 *          VLIB_HAARDETOBJ_MAX_NODE_PER_TREE (3) number of nodes and each node can
 *          have maximum VLIB_HAARDETOBJ_MAX_RECT_PER_NODE (3) rectangles. Each
 *          rectangle is associated with weight to it. Each node will have a threshold
 *          (referred as alpha here) to compare with.
 *          There are VLIB_HAARDETOBJ_MAX_NODE_PER_TREE (3) number of  conditions checks
 *          in a tree and the bit packed result of these condition checks can be used to
 *          select one of the tree score from 'result[]'. It might be required to put some
 *          duplicate elements in 'results' to have desire result for each bit packed index.
 *
 *  @param weight     All possible rectangles weights. Each element is signed 8 bit quantity for
 *                    each rectangle. If a rectangle is not present then make the 8 bit weight
 *                    corresponding to that rectangle as 0. '-1' weight is represented by 0xFF.
 *
 *  @param numNodes   Number of nodes in given tree.
 *
 *  @param rect       All possible rectangle offset in a node - 3 (Rect/Node) * 3 (Node/Tree)
 *
 *  @param alpha      Threshold to be compared with evaluated feature in each node.
 *
 *  @param result     Tree result for various combination of outcome of nodes feature comparisions
 *
 *                    Lets assume that feature for each node is termed as FR1, FR2 and FR3
 *                    Threshold for respective node is alpha1, alpha2, alpha3
 *                    and flag1 = FR1 > alpha1, flag2 = FR2 > alpha2, flag3 = FR3 > alpha3
 *                    form a index = ((flag3 << 2) | (flag2 << 1) | (flag1))
 *                    Now this index if used in 'result' array of 8 values then it should
 *                    give proper value. All this is off-line computed and 'result' array
 *                    is populated.
 *                    From above logic - below table can be formed, as for three node tree
 *                    there are four possible value for tree score lets say these scores are
 *                    R0,R1,R2,R3. Same logic can be extended for any number of nodes in tree.
 *
 *                     flag3  flag2   flag1    Result
 *                       0        0        0     R3
 *                       0        0        1     R0
 *                       0        1        0     R1
 *                       0        1        1     R0
 *                       1        0        0     R2
 *                       1        0        1     R0
 *                       1        1        0     R1
 *                       1        1        1     R0
 *  @param rectType   Rectangle type for each rectangle in tree. Refer \ref VLIB_HAARDETOBJ_rectType
 *******************************************************************************
*/
typedef struct {
    uint8_t               weight[VLIB_HAARDETOBJ_MAX_NODE_PER_TREE][VLIB_HAARDETOBJ_MAX_RECT_PER_NODE_A];   /*!< All possible rectangles weights. */
    int16_t               numNodes;                                                                         /*!< Number of nodes in given tree. */
    VLIB_HAARDETOBJ_sRect rect[VLIB_HAARDETOBJ_MAX_NODE_PER_TREE][VLIB_HAARDETOBJ_MAX_RECT_PER_NODE];       /*!< All possible rectangle offset in a node - 3 (Rect/Node) * 3 (Node/Tree) */
    int32_t               alpha[VLIB_HAARDETOBJ_MAX_NODE_PER_TREE];                                         /*!< Threshold to be compared with evaluated feature in each node. */
    int16_t               result[VLIB_HAARDETOBJ_MAX_LEAVE_PER_TREE];                                       /*!< Tree result for various combination of outcome of nodes feature comparisions */
    uint8_t               rectType[VLIB_HAARDETOBJ_MAX_NODE_PER_TREE];                                      /*!< Rectangle type for each rectangle in tree. Refer \ref VLIB_HAARDETOBJ_rectType */
} VLIB_HAARDETOBJ_sTree;

/**
 *******************************************************************************
 *  @struct VLIB_HAARDETOBJ_sClassifier
 *  @brief  This structure holds property of all the stages in the classifier.
 *          Each stage is a group of trees. Each stage also have one Threshold
 *          to decide to go to next stage or not.
 *          You can visualize it as a series of trees and then you have
 *          milestones placed at predefined location. At those locations you
 *          make decision of continuing further or aborting. The categorization
 *          of these trees in multiple parts is actually stages
 *
 *  @param numStages         Number of stages in classifier
 *  @param maxNodesPerTree   Maximum Number of nodes per tree
 *  @param patchSize         Size of the object for which training has been done
 *  @param numTrees          Array indicating number of trees in each stage.
 *  @param maxRectangle      Maximum number of rectangles in a node for each stage. It is
 *                           possible that each stage's nodes might have different restriction
 *                           on maximum number of rectangles for a node.
 *  @param stageTh           Array indicating Th of each stage, this is used to perform the check to
 *                           perform the check to proceed or not to proceed for next stage.
 *  @param tree              Array describing property of each tree.
 *******************************************************************************
*/
typedef struct {
    int32_t                numStages;                                   /*!< Number of stages in classifier */
    int32_t                maxNodesPerTree;                             /*!< Maximum Number of nodes per tree */
    int32_t                patchSize[2];                                /*!< Size of the object for which training has been done */
    uint8_t                numTrees[VLIB_HAARDETOBJ_MAX_STAGES];        /*!< Array indicating number of trees in each stage. */
    uint8_t                maxRectangle[VLIB_HAARDETOBJ_MAX_STAGES];    /*!< Maximum number of rectangles in a node for each stage. */
    int32_t                stageTh[VLIB_HAARDETOBJ_MAX_STAGES];         /*!< Array indicating Th of each stage */
    VLIB_HAARDETOBJ_sTree *tree;                                        /*!< Array describing property of each tree. */
} VLIB_HAARDETOBJ_sClassifier;

/**
 *******************************************************************************
 *  @struct VLIB_HAARDETOBJ_sObjectList
 *  @brief  This structure holds object list information
 *
 *  @param numObjects      Total number of objects
 *  @param objectPos       Pointer to the buffer where \ref numObjects number of
 *                         object information is stored. Each object information
 *                         is defined as packed format of its 'Y' & 'X' co-ordinate.
 *                         Upper 16 bit is the 'Y' co-ordinate, lower 16 bit is
 *                         'X' co-ordinate.
 *******************************************************************************
 */
typedef struct {
    int16_t   numObjects;   /*!< Total number of objects */
    uint32_t *objectPos;    /*!< Pointer to the buffer where \ref numObjects number of object information is stored. */
} VLIB_HAARDETOBJ_sObjectList;

#endif
/* ======================================================================== */
/*  End of file:  VLIB_haarDetectObjects_types.h                            */
/* ======================================================================== */

