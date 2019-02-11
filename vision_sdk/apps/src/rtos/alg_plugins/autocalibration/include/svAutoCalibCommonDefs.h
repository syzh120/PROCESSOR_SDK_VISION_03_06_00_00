#ifndef _SV_AUTOCALIBCOMMONDEFS_H_
#define _SV_AUTOCALIBCOMMONDEFS_H_


#ifdef PC_VERSION
#include "../algorithmSrc/include/globalDefs.h"
#endif

#define FP_TO_DETECT          2   // # of charts to detect
#define NUM_CHART_CORNERS     8   // # of corners in a image
#define NUM_CORNERS_PER_CHART (NUM_CHART_CORNERS/FP_TO_DETECT) // # of corners / chart


#define ALGORITHM_PROCESS_OK 0
#define ALGORITHM_PROCESS_FAIL -1
#define ALGORITHM_PROCESS_DISABLED 2

#ifndef PC_VERSION
	#include <include/link_api/system.h>
#endif
#ifdef PC_VERSION
//	#include "../../system/system_simulator.h"
	#include <stdio.h>
	#include <math.h>
	#include <stdlib.h>
	#include <string.h>
#endif

typedef UInt32  uWord32;
typedef Int32   Word32;
typedef UInt16  uWord16;
typedef Int16   Word16;
typedef UInt8   Byte;


#endif
