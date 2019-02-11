//To include system type def header
#ifndef _SV_ACDCOMMONDEFS_H_
#define _SV_ACDCOMMONDEFS_H_

#ifndef PC_VERSION
#include <include/link_api/system.h>
#endif
#ifdef PC_VERSION
#include "../algorithmSrc/include/globalDefs.h"
#endif




/*#define INPUT_480P           0
#define INPUT_720P           1*/
#define NUM_PT_BOUNDARY      128

// For automatic initial calibration, configurable parameters
#define ENABLE_ROI            1

#define MAX_FP_ALL            80  // Max # of chart in an image



// For 480p
/*#if INPUT_480P
#define BINARIZE_OFFSET       40  // in svBinarizeImage()
#define BINARIZE_OFFSET_SMALL_WINDOW    30 

#define BORDER_OFFSET         40  // in svSearchFinderPatterns()
#define SMALLEST_CENTER       1   // in svSearchFinderPatterns()
#define LARGEST_CENTER        30  // in svSearchFinderPatterns()

#define MIN_MAX_CHART_RATIO   7   // in svCheckAllDirections()

#define MAX_WIN_WIDTH         140 // in svCheckPatternProfileHiDia()
#define MAX_WIN_HEIGHT        140 // in svCheckPatternProfileHiDia()
#define MAX_BAND_LEN          99  // in svCheckPatternProfileHiDia()
#define MIN_BAND_LEN          2   // in svCheckPatternProfileHiDia()
#define MIN_CHART_SIZE        10  // in svCheckPatternProfileHiDia()
#define HIGH_MID_TH           6.0 // in svCheckPatternProfileHiDia()
#define LOW_MID_TH            0.15 // in svCheckPatternProfileHiDia()
#define SIDE_TH               5.0 // in svCheckPatternProfileHiDia()

#define MAX_HOR_LENGTH_RATIO  2.5 // in svCheckFPCondition()
#define MAX_VER_LENGTH_RATIO  2.5 // in svCheckFPCondition()
#define MAX_DIA_LENGTH_RATIO  5.0 // in svCheckFPCondition()
#define MIN_HOR_LENGTH        10
#define MIN_VER_LENGTH        20
#define MIN_CHART_LENGTH      100

#define MIN_SAMPLE_IN_CLUSTER 2   // Minimum # of samples in one cluster, in svRemoveNoiseFP()

#define FIRST_ROI_TOP         80
#define FIRST_ROI_BOTTOM      400
#define FIRST_ROI_LEFT        50
#define FIRST_ROI_RIGHT       280

#define SECOND_ROI_TOP        80
#define SECOND_ROI_BOTTOM     400
#define SECOND_ROI_LEFT       440
#define SECOND_ROI_RIGHT      686*/

#define BINARIZE_OFFSET_SMALL_WINDOW     50
#define MIN_MAX_CHART_RATIO   5   // in svCheckAllDirections()
#define MIN_CHART_SIZE        20  // in svCheckPatternProfileHiDia()
#define HIGH_MID_TH           5.0 // in svCheckPatternProfileHiDia()
#define LOW_MID_TH            0.2 // in svCheckPatternProfileHiDia()
#define SIDE_TH               4.0 // in svCheckPatternProfileHiDia()

#define MAX_HOR_LENGTH_RATIO  2.5 // in svCheckFPCondition()
#define MAX_VER_LENGTH_RATIO  2.5 // in svCheckFPCondition()
#define MAX_DIA_LENGTH_RATIO  5.0 // in svCheckFPCondition()
#define MIN_HOR_LENGTH        15
#define MIN_VER_LENGTH        30
#define MIN_CHART_LENGTH      150

/*#if INPUT_720P

// for 720P
#define SRV_ROI_WIDTH       (1280U)
#define SRV_ROI_HEIGHT      (720U)

#define BINARIZE_OFFSET       75  // in svBinarizeImage()

#define BORDER_OFFSET         50  // in svSearchFinderPatterns()
#define SMALLEST_CENTER       2   // in svSearchFinderPatterns()
#define LARGEST_CENTER        50  // in svSearchFinderPatterns()

#define MAX_WIN_WIDTH         180 // in svCheckPatternProfileHiDia()
#define MAX_WIN_HEIGHT        180 // in svCheckPatternProfileHiDia()
#define MAX_BAND_LEN          160  // in svCheckPatternProfileHiDia()
#define MIN_BAND_LEN          2   // in svCheckPatternProfileHiDia()

#define MIN_SAMPLE_IN_CLUSTER 4   // Minimum # of samples in one cluster, in svRemoveNoiseFP()

#define FIRST_ROI_TOP         150
#define FIRST_ROI_BOTTOM      670
#define FIRST_ROI_LEFT        100
#define FIRST_ROI_RIGHT       600

#define SECOND_ROI_TOP        150
#define SECOND_ROI_BOTTOM     670
#define SECOND_ROI_LEFT       700
#define SECOND_ROI_RIGHT      1200

#else

// for 1080P
#define SRV_ROI_WIDTH       (1920U)
#define SRV_ROI_HEIGHT      (1080U)

#define BINARIZE_OFFSET       80  // in svBinarizeImage()

#define BORDER_OFFSET         80  // in svSearchFinderPatterns()
#define SMALLEST_CENTER       10   // in svSearchFinderPatterns()
#define LARGEST_CENTER        50  // in svSearchFinderPatterns()

#define MAX_WIN_WIDTH         400 // in svCheckPatternProfileHiDia()
#define MAX_WIN_HEIGHT        400 // in svCheckPatternProfileHiDia()
#define MAX_BAND_LEN          400  // in svCheckPatternProfileHiDia()
#define MIN_BAND_LEN          4   // in svCheckPatternProfileHiDia()

#define MIN_SAMPLE_IN_CLUSTER 16   // Minimum # of samples in one cluster, in svRemoveNoiseFP()

#define FIRST_ROI_TOP         300
#define FIRST_ROI_BOTTOM      1050
#define FIRST_ROI_LEFT        50
#define FIRST_ROI_RIGHT       900

#define SECOND_ROI_TOP        300
#define SECOND_ROI_BOTTOM     1050
#define SECOND_ROI_LEFT       950
#define SECOND_ROI_RIGHT      1870

#endif*/


typedef struct
{
    double xPos[4];
    double yPos[4];

    double centerRun;
    double firstBrun;
    double secondBrun;

} SV_ACDetect_FPBoundaryPos;


#endif
