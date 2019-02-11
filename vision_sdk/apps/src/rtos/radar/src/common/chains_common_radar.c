/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/common/chains_radar.h>
#include <src/rtos/utils_common/include/utils_prcm_stats.h>
#include <src/rtos/utils_common/include/utils_stat_collector.h>
#include <src/include/link_stats_monitor.h>
#include <math.h>

/**< \brief Value of Pi */
#define CHAINS_RADAR_PI_VALUE (3.1415927)

/**< \brief Max Horizontal Angle */
#define CHAINS_RADAR_MAX_HORZ_ANGLE (60)
#define CHAINS_RADAR_HORZ_RES (2)

/**< \brief Max Vertical Angle */
#define CHAINS_RADAR_MAX_VERT_ANGLE (0)
#define CHAINS_RADAR_VERT_RES (5)

#pragma DATA_ALIGN(gFftWindowx64, 128)
static Int16 gFftWindowx64[] =
{
    2621, 2696, 2920, 3291, 3804, 4456, 5240, 6147, 7169, 8296, 9516, 10817, 12187,
    13611, 15076, 16567, 18069, 19568, 21048, 22494, 23893, 25230, 26492, 27667,
    28743, 29709, 30555, 31274, 31857, 32300, 32598, 32748, 32748, 32598, 32300,
    31857, 31274, 30555, 29709, 28743, 27667, 26492, 25230, 23893, 22494, 21048,
    19568, 18069, 16567, 15076, 13611, 12187, 10817, 9516, 8296, 7169, 6147, 5240,
    4456, 3804, 3291, 2920, 2696, 2621
};

#pragma DATA_ALIGN(gFftWindowx128, 128)
static Int16 gFftWindowx128[] =
{
    2621, 2639, 2695, 2787, 2915, 3080, 3280, 3516, 3786,
    4091, 4428, 4798, 5200, 5632, 6094, 6584, 7102, 7645,
    8213, 8804, 9417, 10050, 10702, 11371, 12055, 12753,
    13463, 14184, 14913, 15649, 16390, 17135, 17880, 18625,
    19368, 20107, 20840, 21565, 22280, 22985, 23676, 24353,
    25014, 25656, 26280, 26882, 27461, 28017, 28548, 29052,
    29528, 29975, 30392, 30778, 31132, 31453, 31741, 31994,
    32212, 32394, 32541, 32651, 32725, 32762, 32762, 32725,
    32651, 32541, 32394, 32212, 31994, 31741, 31453, 31132,
    30778, 30392, 29975, 29528, 29052, 28548, 28017, 27461,
    26882, 26280, 25656, 25014, 24353, 23676, 22985, 22280,
    21565, 20840, 20107, 19368, 18625, 17880, 17135, 16390,
    15649, 14913, 14184, 13463, 12753, 12055, 11371, 10702,
    10050, 9417, 8804, 8213, 7645, 7102, 6584, 6094, 5632,
    5200, 4798, 4428, 4091, 3786, 3516, 3280, 3080, 2915,
    2787, 2695, 2639, 2621
};

#pragma DATA_ALIGN(gFftWindowx256, 128)
static Int16 gFftWindowx256[] =
{
    2621, 2625, 2639, 2662, 2694, 2735, 2785, 2845, 2913,
    2990, 3076, 3171, 3275, 3388, 3509, 3639, 3777, 3924,
    4079, 4243, 4414, 4594, 4782, 4977, 5180, 5391, 5610,
    5835, 6068, 6308, 6555, 6808, 7068, 7335, 7608, 7887,
    8172, 8463, 8759, 9061, 9368, 9680, 9997, 10319, 10645,
    10975, 11310, 11648, 11990, 12335, 12684, 13036, 13391,
    13748, 14107, 14469, 14833, 15198, 15565, 15934, 16303,
    16673, 17044, 17415, 17787, 18158, 18529, 18899, 19269,
    19638, 20006, 20372, 20737, 21099, 21460, 21819, 22174,
    22528, 22878, 23225, 23569, 23909, 24245, 24578, 24906,
    25230, 25549, 25864, 26174, 26478, 26777, 27071, 27359,
    27641, 27917, 28186, 28450, 28707, 28957, 29200, 29437,
    29666, 29888, 30102, 30309, 30509, 30700, 30884, 31060,
    31227, 31387, 31538, 31681, 31815, 31940, 32057, 32165,
    32265, 32355, 32437, 32510, 32574, 32628, 32674, 32710,
    32738, 32756, 32765, 32765, 32756, 32738, 32710, 32674,
    32628, 32574, 32510, 32437, 32355, 32265, 32165, 32057,
    31940, 31815, 31681, 31538, 31387, 31227, 31060, 30884,
    30700, 30509, 30309, 30102, 29888, 29666, 29437, 29200,
    28957, 28707, 28450, 28186, 27917, 27641, 27359, 27071,
    26777, 26478, 26174, 25864, 25549, 25230, 24906, 24578,
    24245, 23909, 23569, 23225, 22878, 22528, 22174, 21819,
    21460, 21099, 20737, 20372, 20006, 19638, 19269, 18899,
    18529, 18158, 17787, 17415, 17044, 16673, 16303, 15934,
    15565, 15198, 14833, 14469, 14107, 13748, 13391, 13036,
    12684, 12335, 11990, 11648, 11310, 10975, 10645, 10319,
    9997, 9680, 9368, 9061, 8759, 8463, 8172, 7887, 7608,
    7335, 7068, 6808, 6555, 6308, 6068, 5835, 5610, 5391,
    5180, 4977, 4782, 4594, 4414, 4243, 4079, 3924, 3777,
    3639, 3509, 3388, 3275, 3171, 3076, 2990, 2913, 2845,
    2785, 2735, 2694, 2662, 2639, 2625, 2621
};

#pragma DATA_ALIGN(gFftWindowx512, 128)
static Int16 gFftWindowx512[] =
{
    2621, 2622, 2625, 2631, 2639, 2649, 2662, 2677, 2694,
    2713, 2735, 2759, 2785, 2813, 2844, 2877, 2912, 2949,
    2989, 3030, 3074, 3121, 3169, 3220, 3272, 3327, 3385,
    3444, 3505, 3569, 3635, 3703, 3773, 3845, 3919, 3995,
    4074, 4154, 4236, 4321, 4407, 4496, 4587, 4679, 4773,
    4870, 4968, 5069, 5171, 5275, 5381, 5489, 5598, 5710,
    5823, 5938, 6055, 6174, 6294, 6416, 6540, 6666, 6793,
    6922, 7052, 7184, 7318, 7453, 7590, 7728, 7868, 8009,
    8152, 8296, 8442, 8589, 8737, 8887, 9038, 9190, 9344,
    9499, 9655, 9812, 9971, 10131, 10291, 10453, 10617,
    10781, 10946, 11112, 11279, 11448, 11617, 11787, 11958,
    12129, 12302, 12476, 12650, 12825, 13001, 13177, 13354,
    13532, 13711, 13890, 14069, 14249, 14430, 14611, 14793,
    14975, 15157, 15340, 15524, 15707, 15891, 16075, 16260,
    16444, 16629, 16814, 16999, 17184, 17369, 17555, 17740,
    17925, 18111, 18296, 18481, 18666, 18851, 19036, 19220,
    19404, 19588, 19772, 19955, 20138, 20321, 20503, 20685,
    20867, 21048, 21228, 21408, 21587, 21766, 21944, 22122,
    22299, 22475, 22650, 22825, 22999, 23172, 23344, 23515,
    23686, 23855, 24024, 24192, 24358, 24524, 24689, 24853,
    25015, 25177, 25337, 25496, 25654, 25811, 25966, 26121,
    26274, 26425, 26576, 26725, 26872, 27019, 27164, 27307,
    27449, 27590, 27729, 27866, 28002, 28137, 28270, 28401,
    28530, 28658, 28785, 28909, 29032, 29154, 29273, 29391,
    29507, 29621, 29734, 29844, 29953, 30060, 30165, 30268,
    30369, 30469, 30566, 30661, 30755, 30846, 30936, 31023,
    31109, 31192, 31274, 31353, 31431, 31506, 31579, 31650,
    31719, 31786, 31850, 31913, 31973, 32032, 32088, 32142,
    32193, 32243, 32290, 32335, 32378, 32419, 32457, 32494,
    32528, 32559, 32589, 32616, 32641, 32664, 32684, 32702,
    32718, 32732, 32743, 32753, 32759, 32764, 32766, 32766,
    32764, 32759, 32753, 32743, 32732, 32718, 32702, 32684,
    32664, 32641, 32616, 32589, 32559, 32528, 32494, 32457,
    32419, 32378, 32335, 32290, 32243, 32193, 32142, 32088,
    32032, 31973, 31913, 31850, 31786, 31719, 31650, 31579,
    31506, 31431, 31353, 31274, 31192, 31109, 31023, 30936,
    30846, 30755, 30661, 30566, 30469, 30369, 30268, 30165,
    30060, 29953, 29844, 29734, 29621, 29507, 29391, 29273,
    29154, 29032, 28909, 28785, 28658, 28530, 28401, 28270,
    28137, 28002, 27866, 27729, 27590, 27449, 27307, 27164,
    27019, 26872, 26725, 26576, 26425, 26274, 26121, 25966,
    25811, 25654, 25496, 25337, 25177, 25015, 24853, 24689,
    24524, 24358, 24192, 24024, 23855, 23686, 23515, 23344,
    23172, 22999, 22825, 22650, 22475, 22299, 22122, 21944,
    21766, 21587, 21408, 21228, 21048, 20867, 20685, 20503,
    20321, 20138, 19955, 19772, 19588, 19404, 19220, 19036,
    18851, 18666, 18481, 18296, 18111, 17925, 17740, 17555,
    17369, 17184, 16999, 16814, 16629, 16444, 16260, 16075,
    15891, 15707, 15524, 15340, 15157, 14975, 14793, 14611,
    14430, 14249, 14069, 13890, 13711, 13532, 13354, 13177,
    13001, 12825, 12650, 12476, 12302, 12129, 11958, 11787,
    11617, 11448, 11279, 11112, 10946, 10781, 10617, 10453,
    10291, 10131, 9971, 9812, 9655, 9499, 9344, 9190,
    9038, 8887, 8737, 8589, 8442, 8296, 8152, 8009, 7868,
    7728, 7590, 7453, 7318, 7184, 7052, 6922, 6793, 6666,
    6540, 6416, 6294, 6174, 6055, 5938, 5823, 5710, 5598,
    5489, 5381, 5275, 5171, 5069, 4968, 4870, 4773, 4679,
    4587, 4496, 4407, 4321, 4236, 4154, 4074, 3995, 3919,
    3845, 3773, 3703, 3635, 3569, 3505, 3444, 3385, 3327,
    3272, 3220, 3169, 3121, 3074, 3030, 2989, 2949, 2912,
    2877, 2844, 2813, 2785, 2759, 2735, 2713, 2694, 2677,
    2662, 2649, 2639, 2631, 2625, 2622, 2621
};

#pragma DATA_ALIGN(gFftWindowx1024, 128)
static Int16 gFftWindowx1024[] =
{
    2621, 2621, 2622, 2623, 2625, 2628, 2631, 2635, 2639,
    2644, 2649, 2655, 2662, 2669, 2677, 2685, 2694, 2703,
    2713, 2723, 2734, 2746, 2758, 2771, 2784, 2798, 2813,
    2828, 2843, 2859, 2876, 2893, 2911, 2929, 2948, 2968,
    2988, 3008, 3030, 3051, 3073, 3096, 3120, 3143, 3168,
    3193, 3218, 3245, 3271, 3298, 3326, 3354, 3383, 3412,
    3442, 3473, 3504, 3535, 3567, 3600, 3633, 3666, 3701,
    3735, 3770, 3806, 3842, 3879, 3916, 3954, 3993, 4031,
    4071, 4111, 4151, 4192, 4233, 4275, 4318, 4361, 4404,
    4448, 4492, 4537, 4583, 4629, 4675, 4722, 4769, 4817,
    4866, 4914, 4964, 5014, 5064, 5115, 5166, 5218, 5270,
    5322, 5376, 5429, 5483, 5538, 5593, 5648, 5704, 5760,
    5817, 5874, 5932, 5990, 6049, 6108, 6167, 6227, 6287,
    6348, 6409, 6471, 6533, 6595, 6658, 6721, 6785, 6849,
    6914, 6978, 7044, 7109, 7176, 7242, 7309, 7376, 7444,
    7512, 7581, 7649, 7719, 7788, 7858, 7928, 7999, 8070,
    8142, 8213, 8286, 8358, 8431, 8504, 8578, 8652, 8726,
    8800, 8875, 8951, 9026, 9102, 9178, 9255, 9332, 9409,
    9486, 9564, 9642, 9721, 9799, 9878, 9958, 10037,
    10117, 10197, 10278, 10359, 10440, 10521, 10602, 10684,
    10766, 10849, 10931, 11014, 11097, 11181, 11264, 11348,
    11432, 11517, 11601, 11686, 11771, 11856, 11942, 12027,
    12113, 12199, 12286, 12372, 12459, 12546, 12633, 12720,
    12808, 12895, 12983, 13071, 13159, 13248, 13336, 13425,
    13514, 13603, 13692, 13781, 13871, 13960, 14050, 14140,
    14230, 14320, 14411, 14501, 14592, 14682, 14773, 14864,
    14955, 15046, 15137, 15228, 15320, 15411, 15503, 15594,
    15686, 15778, 15870, 15962, 16054, 16146, 16238, 16330,
    16422, 16515, 16607, 16699, 16792, 16884, 16976, 17069,
    17161, 17254, 17347, 17439, 17532, 17624, 17717, 17809,
    17902, 17995, 18087, 18180, 18272, 18365, 18457, 18550,
    18642, 18734, 18827, 18919, 19011, 19103, 19196, 19288,
    19380, 19472, 19564, 19655, 19747, 19839, 19930, 20022,
    20113, 20205, 20296, 20387, 20478, 20569, 20660, 20750,
    20841, 20932, 21022, 21112, 21202, 21292, 21382, 21472,
    21561, 21651, 21740, 21829, 21918, 22007, 22095, 22184,
    22272, 22360, 22448, 22536, 22624, 22711, 22798, 22885,
    22972, 23059, 23145, 23231, 23317, 23403, 23489, 23574,
    23659, 23744, 23829, 23913, 23997, 24081, 24165, 24248,
    24332, 24415, 24497, 24580, 24662, 24744, 24826, 24907,
    24988, 25069, 25150, 25230, 25310, 25390, 25469, 25548,
    25627, 25706, 25784, 25862, 25940, 26017, 26094, 26171,
    26247, 26323, 26399, 26474, 26550, 26624, 26699, 26773,
    26846, 26920, 26993, 27066, 27138, 27210, 27281, 27353,
    27424, 27494, 27564, 27634, 27703, 27772, 27841, 27909,
    27977, 28045, 28112, 28179, 28245, 28311, 28376, 28441,
    28506, 28570, 28634, 28698, 28761, 28823, 28886, 28947,
    29009, 29070, 29130, 29190, 29250, 29309, 29368, 29426,
    29484, 29542, 29599, 29655, 29711, 29767, 29822, 29877,
    29931, 29985, 30038, 30091, 30144, 30196, 30247, 30298,
    30349, 30399, 30448, 30497, 30546, 30594, 30642, 30689,
    30736, 30782, 30827, 30873, 30917, 30961, 31005, 31048,
    31091, 31133, 31175, 31216, 31257, 31297, 31336, 31375,
    31414, 31452, 31490, 31527, 31563, 31599, 31635, 31670,
    31704, 31738, 31771, 31804, 31836, 31868, 31899, 31930,
    31960, 31990, 32019, 32047, 32075, 32103, 32130, 32156,
    32182, 32207, 32232, 32256, 32280, 32303, 32325, 32347,
    32368, 32389, 32410, 32429, 32449, 32467, 32485, 32503,
    32520, 32536, 32552, 32567, 32582, 32596, 32610, 32623,
    32635, 32647, 32659, 32669, 32680, 32689, 32698, 32707,
    32715, 32722, 32729, 32735, 32741, 32746, 32751, 32754,
    32758, 32761, 32763, 32765, 32766, 32766, 32766, 32766,
    32765, 32763, 32761, 32758, 32754, 32751, 32746, 32741,
    32735, 32729, 32722, 32715, 32707, 32698, 32689, 32680,
    32669, 32659, 32647, 32635, 32623, 32610, 32596, 32582,
    32567, 32552, 32536, 32520, 32503, 32485, 32467, 32449,
    32429, 32410, 32389, 32368, 32347, 32325, 32303, 32280,
    32256, 32232, 32207, 32182, 32156, 32130, 32103, 32075,
    32047, 32019, 31990, 31960, 31930, 31899, 31868, 31836,
    31804, 31771, 31738, 31704, 31670, 31635, 31599, 31563,
    31527, 31490, 31452, 31414, 31375, 31336, 31297, 31257,
    31216, 31175, 31133, 31091, 31048, 31005, 30961, 30917,
    30873, 30827, 30782, 30736, 30689, 30642, 30594, 30546,
    30497, 30448, 30399, 30349, 30298, 30247, 30196, 30144,
    30091, 30038, 29985, 29931, 29877, 29822, 29767, 29711,
    29655, 29599, 29542, 29484, 29426, 29368, 29309, 29250,
    29190, 29130, 29070, 29009, 28947, 28886, 28823, 28761,
    28698, 28634, 28570, 28506, 28441, 28376, 28311, 28245,
    28179, 28112, 28045, 27977, 27909, 27841, 27772, 27703,
    27634, 27564, 27494, 27424, 27353, 27281, 27210, 27138,
    27066, 26993, 26920, 26846, 26773, 26699, 26624, 26550,
    26474, 26399, 26323, 26247, 26171, 26094, 26017, 25940,
    25862, 25784, 25706, 25627, 25548, 25469, 25390, 25310,
    25230, 25150, 25069, 24988, 24907, 24826, 24744, 24662,
    24580, 24497, 24415, 24332, 24248, 24165, 24081, 23997,
    23913, 23829, 23744, 23659, 23574, 23489, 23403, 23317,
    23231, 23145, 23059, 22972, 22885, 22798, 22711, 22624,
    22536, 22448, 22360, 22272, 22184, 22095, 22007, 21918,
    21829, 21740, 21651, 21561, 21472, 21382, 21292, 21202,
    21112, 21022, 20932, 20841, 20750, 20660, 20569, 20478,
    20387, 20296, 20205, 20113, 20022, 19930, 19839, 19747,
    19655, 19564, 19472, 19380, 19288, 19196, 19103, 19011,
    18919, 18827, 18734, 18642, 18550, 18457, 18365, 18272,
    18180, 18087, 17995, 17902, 17809, 17717, 17624, 17532,
    17439, 17347, 17254, 17161, 17069, 16976, 16884, 16792,
    16699, 16607, 16515, 16422, 16330, 16238, 16146, 16054,
    15962, 15870, 15778, 15686, 15594, 15503, 15411, 15320,
    15228, 15137, 15046, 14955, 14864, 14773, 14682, 14592,
    14501, 14411, 14320, 14230, 14140, 14050, 13960, 13871,
    13781, 13692, 13603, 13514, 13425, 13336, 13248, 13159,
    13071, 12983, 12895, 12808, 12720, 12633, 12546, 12459,
    12372, 12286, 12199, 12113, 12027, 11942, 11856, 11771,
    11686, 11601, 11517, 11432, 11348, 11264, 11181, 11097,
    11014, 10931, 10849, 10766, 10684, 10602, 10521, 10440,
    10359, 10278, 10197, 10117, 10037, 9958, 9878, 9799,
    9721, 9642, 9564, 9486, 9409, 9332, 9255, 9178, 9102,
    9026, 8951, 8875, 8800, 8726, 8652, 8578, 8504, 8431,
    8358, 8286, 8213, 8142, 8070, 7999, 7928, 7858, 7788,
    7719, 7649, 7581, 7512, 7444, 7376, 7309, 7242, 7176,
    7109, 7044, 6978, 6914, 6849, 6785, 6721, 6658, 6595,
    6533, 6471, 6409, 6348, 6287, 6227, 6167, 6108, 6049,
    5990, 5932, 5874, 5817, 5760, 5704, 5648, 5593, 5538,
    5483, 5429, 5376, 5322, 5270, 5218, 5166, 5115, 5064,
    5014, 4964, 4914, 4866, 4817, 4769, 4722, 4675, 4629,
    4583, 4537, 4492, 4448, 4404, 4361, 4318, 4275, 4233,
    4192, 4151, 4111, 4071, 4031, 3993, 3954, 3916, 3879,
    3842, 3806, 3770, 3735, 3701, 3666, 3633, 3600, 3567,
    3535, 3504, 3473, 3442, 3412, 3383, 3354, 3326, 3298,
    3271, 3245, 3218, 3193, 3168, 3143, 3120, 3096, 3073,
    3051, 3030, 3008, 2988, 2968, 2948, 2929, 2911, 2893,
    2876, 2859, 2843, 2828, 2813, 2798, 2784, 2771, 2758,
    2746, 2734, 2723, 2713, 2703, 2694, 2685, 2677, 2669,
    2662, 2655, 2649, 2644, 2639, 2635, 2631, 2628, 2625,
    2623, 2622, 2621, 2621
};

/**
 *******************************************************************************
 *
 * \brief   Function to Set up the FFT parameters
 *
 * \param   pFFTParams  FFT create time parameters
 * \param   pAr12xxCfg  AR12 configuration obtained from
 *                      #ChainsCommon_ar12xxConfig
 *
 * \return  None
 *
 *******************************************************************************
*/
Void ChainsCommon_ar12xxSetFFTParams(AlgorithmFxn_RadarFftCreateParams *pFFTParams,
                                     ChainsCommon_Ar12xxConfigOut *pAr12xxCfg)
{
    UInt32 i = 0U;
    UInt32 rangeScaleFactors[FFT_TI_MAX_NUM_STAGES] = {2, 2, 2, 2, 2};
    UInt32 dopplerScaleFactors[FFT_TI_MAX_NUM_STAGES] = {2, 2, 2, 2, 2};

    /* Algorithm Function Initialization */
    AlgorithmFxn_RadarFft_Init(pFFTParams);
    pFFTParams->workQcpuId = SYSTEM_PROC_EVE1;
    pFFTParams->pRadarCfg = pAr12xxCfg;
    pFFTParams->dataFormat = SYSTEM_DF_BAYER_BGGR;
    pFFTParams->algFFTMode = RADAR_FFT_MODE_HORZ_AND_VERT;
    pFFTParams->algCreatePrm[0].enableWindowing = 1;
    pFFTParams->algCreatePrm[0].enableDcoffset = 1;
    pFFTParams->algCreatePrm[0].enableInterferenceZeroOut = 0;
    pFFTParams->algCreatePrm[0].enableDopplerCorrection = 0;
    pFFTParams->algCreatePrm[0].windowingScaleFactor = 15;
    pFFTParams->algCreatePrm[0].interferenceThreshold = 0;
    pFFTParams->algCreatePrm[0].enableOverFlowDetection = 0;
    pFFTParams->algCreatePrm[0].outputContainerFormat = FFT_TI_CONTAINER_FORMAT_16BIT;
    for (i = 0U; i < FFT_TI_MAX_NUM_STAGES; i++)
    {
        pFFTParams->algCreatePrm[0].scaleFactors[i] = rangeScaleFactors[i];
        pFFTParams->algCreatePrm[1].scaleFactors[i] = dopplerScaleFactors[i];
    }
    pFFTParams->algCreatePrm[1].enableWindowing = 1;
    pFFTParams->algCreatePrm[1].enableDcoffset = 0;
    pFFTParams->algCreatePrm[1].enableInterferenceZeroOut = 0;
    pFFTParams->algCreatePrm[1].enableDopplerCorrection = 0;
    pFFTParams->algCreatePrm[1].windowingScaleFactor = 15;
    pFFTParams->algCreatePrm[1].interferenceThreshold = 0;
    pFFTParams->algCreatePrm[1].enableOverFlowDetection = 0;
    pFFTParams->algCreatePrm[1].outputContainerFormat = FFT_TI_CONTAINER_FORMAT_16BIT;

    pFFTParams->algCreatePrm[0].windowCoeffAddr[RADAR_FFT_NUM_POINTS_1024] = (UInt32) gFftWindowx1024;
    pFFTParams->algCreatePrm[0].windowCoeffAddr[RADAR_FFT_NUM_POINTS_512] = (UInt32) gFftWindowx512;
    pFFTParams->algCreatePrm[0].windowCoeffAddr[RADAR_FFT_NUM_POINTS_256] = (UInt32) gFftWindowx256;
    pFFTParams->algCreatePrm[0].windowCoeffAddr[RADAR_FFT_NUM_POINTS_128] = (UInt32) gFftWindowx128;
    pFFTParams->algCreatePrm[0].windowCoeffAddr[RADAR_FFT_NUM_POINTS_64] = (UInt32) gFftWindowx64;
    pFFTParams->algCreatePrm[1].windowCoeffAddr[RADAR_FFT_NUM_POINTS_1024] = (UInt32) gFftWindowx1024;
    pFFTParams->algCreatePrm[1].windowCoeffAddr[RADAR_FFT_NUM_POINTS_512] = (UInt32) gFftWindowx512;
    pFFTParams->algCreatePrm[1].windowCoeffAddr[RADAR_FFT_NUM_POINTS_256] = (UInt32) gFftWindowx256;
    pFFTParams->algCreatePrm[1].windowCoeffAddr[RADAR_FFT_NUM_POINTS_128] = (UInt32) gFftWindowx128;
    pFFTParams->algCreatePrm[1].windowCoeffAddr[RADAR_FFT_NUM_POINTS_64] = (UInt32) gFftWindowx64;
}
/**
 *******************************************************************************
 *
 * \brief   Function to Set up the peak detection parameters
 *
 * \param   pPkDetParams    Peak detection create time parameters
 * \param   pAr12xxCfg      AR12 configuration obtained from
 *                          #ChainsCommon_ar12xxConfig
 *
 * \return  None
 *
 *******************************************************************************
*/
Void ChainsCommon_ar12xxSetPkDetectParams(AlgorithmFxn_RadarPkDetectCreateParams *pPkDetParams,
                                          ChainsCommon_Ar12xxConfigOut *pAr12xxCfg)
{
    UInt32 i = 0U;
    AlgorithmFxn_RadarPkDetect_Init(pPkDetParams);
    pPkDetParams->maxNumAntenna = 12U;
    pPkDetParams->maxNumTx = 3U;
    pPkDetParams->maxRangeDimension = 1024U;
    pPkDetParams->maxDopplerDimension = 512U;
    pPkDetParams->detectionMethod = PEAK_DETECTION_TI_METHOD_CFARCA_DB;
    pPkDetParams->enableAntennaDataOut = 1;
    pPkDetParams->algoCreateParams.cfarCaDb.maxNoiseLen = 16;
    pPkDetParams->algoCreateParams.cfarCaDb.maxGaurdLen = 16;
    pPkDetParams->cfarCaDb.noiseLen = 8;
    pPkDetParams->cfarCaDb.gaurdLen = 4;
    pPkDetParams->cfarCaDb.constant1 = 256;
    pPkDetParams->cfarCaDb.constant2 = 3;
    if (pAr12xxCfg->radarParams[0].bpmEnabled == 1U)
    {
        pPkDetParams->enableTxDecoding = 1;
    }
    else
    {
        pPkDetParams->enableTxDecoding = 0;
    }
    memset(pPkDetParams->txDecodingCoefficients, 0, RADAR_PKDETECT_MAX_TX * RADAR_PKDETECT_MAX_TX);
    ((Int16*)pPkDetParams->txDecodingCoefficients)[0] = 16384; /* 1 */
    ((Int16*)pPkDetParams->txDecodingCoefficients)[1] = 16384; /* 1 */
    ((Int16*)pPkDetParams->txDecodingCoefficients)[2] = 16384; /* 1 */
    ((Int16*)pPkDetParams->txDecodingCoefficients)[3] = -16384;/* -1 */
    pPkDetParams->numProfiles = pAr12xxCfg->radarParams[0].numProfiles;
    for (i = 0U; i < pAr12xxCfg->radarParams[0].numProfiles; i++)
    {
    	pPkDetParams->numTx[i] = pAr12xxCfg->radarParams[0].numTxAntenna[i];
    	pPkDetParams->numRx[i] = pAr12xxCfg->radarParams[0].numRxAntenna[i];
        pPkDetParams->rangeDim[i] = pAr12xxCfg->radarParams[0].radarWidth[i];
        pPkDetParams->dopplerDim[i] = pAr12xxCfg->radarParams[0].radarHeight[i];
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to Set up the beam forming parameters
 *
 * \param   pBeamFormParams     Beam Forming create time parameters
 * \param   pAr12xxCfg          AR12 configuration obtained from
 *                              #ChainsCommon_ar12xxConfig
 *
 * \return  None
 *
 *******************************************************************************
*/
Void ChainsCommon_ar12xxSetBeamFormParams(
    AlgorithmFxn_RadarBeamFormCreateParams *pBeamFormParams,
    ChainsCommon_Ar12xxConfigOut *pAr12xxCfg)
{
    UInt32 i = 0U;
    UInt32 maxAnt = 0U;
    AlgorithmFxn_RadarBeamForm_Init(pBeamFormParams);
    pBeamFormParams->maxNumDetection = RADAR_BEAMFORM_MAX_DETECTED_OBJS;
    pBeamFormParams->maxNumAngle = (2 * CHAINS_RADAR_MAX_HORZ_ANGLE/CHAINS_RADAR_HORZ_RES + 1)* (2 * CHAINS_RADAR_MAX_VERT_ANGLE/CHAINS_RADAR_VERT_RES + 1);
    pBeamFormParams->coordinateBufFormat = BEAM_FORMING_TI_COORDINATE_BUF_FORMAT_2;
    pBeamFormParams->numAngles = pBeamFormParams->maxNumAngle;
    pBeamFormParams->beamFormingScaling = 15;
    pBeamFormParams->energyScaling = 15;
    for (i = 0U; i < pAr12xxCfg->radarParams[0].numProfiles; i++)
    {
        pBeamFormParams->numAntennas[i] = pAr12xxCfg->radarParams[0].numTxAntenna[i] * pAr12xxCfg->radarParams[0].numRxAntenna[i];
        if (maxAnt < pBeamFormParams->numAntennas[i])
        {
            maxAnt = pBeamFormParams->numAntennas[i];
        }
        pBeamFormParams->steeringBuf[i] = (UInt8*) Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                pBeamFormParams->maxNumAngle * pBeamFormParams->numAntennas[i] * 4, 128);
        Chains_RadarCalculateSteeringMatrix((Int16*)pBeamFormParams->steeringBuf[i],
            CHAINS_RADAR_HORZ_RES,  pAr12xxCfg->radarParams[0].numRxAntenna[i],
            CHAINS_RADAR_VERT_RES,  pAr12xxCfg->radarParams[0].numTxAntenna[i],
            0.5, CHAINS_RADAR_MAX_HORZ_ANGLE, CHAINS_RADAR_MAX_VERT_ANGLE);
    }
    pBeamFormParams->maxNumAntenna = maxAnt;
}

Void ChainsCommon_ar12xxBeamFormDeInit(
    ChainsCommon_Ar12xxConfigOut *pAr12xxCfg,
    AlgorithmFxn_RadarBeamFormCreateParams *pBeamFormParams)
{
    UInt32 i = 0U;
    for (i = 0U; i < pAr12xxCfg->radarParams[0].numProfiles; i++)
    {
        Int32 status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, (Ptr)pBeamFormParams->steeringBuf[i],
            pBeamFormParams->maxNumAngle * pBeamFormParams->numAntennas[i] * 4);
        UTILS_assert(status==0);
    }
}
/**
 *******************************************************************************
 *
 * \brief   Function to Set up the FFT Heat Map draw parameters
 *
 * \param   pRadarDrawFFTHeatMapPrm FFT Heat Map Draw create time parameters
 * \param   pAr12xxCfg              AR12 configuration obtained from
 *                                  #ChainsCommon_ar12xxConfig
 * \param   displayWidth            Output display width
 * \param   displayHeight           Output display height
 *
 * \return  None
 *
 *******************************************************************************
*/
Void ChainsCommon_ar12xxSetFFTHeatMapParams(
        AlgorithmFxn_RadarDrawFFTHeatMapCreateParams *pRadarDrawFFTHeatMapPrm,
        ChainsCommon_Ar12xxConfigOut *pAr12xxCfg,
        UInt32 displayWidth, UInt32 displayHeight)
{
    UInt32 cnt;
    UInt32 i = 0U;
    UInt32 range[8] = {5, 50, 100, 150, 200,
                       250, 300, 800000};
    UInt32 color[8] = {RGB888_TO_RGB565(0, 0, 225) /* Dark Blue */,
                       RGB888_TO_RGB565(0, 128, 225) /* Blue */,
                       RGB888_TO_RGB565(0, 255, 225), /* Light Blue */
                       RGB888_TO_RGB565(0, 255, 0), /* Green */
                       RGB888_TO_RGB565(128, 255, 0), /* Dirty Green */
                       RGB888_TO_RGB565(255, 255, 0), /* Yellow */
                       RGB888_TO_RGB565(255, 128, 0), /* Orange */
                       RGB888_TO_RGB565(255, 0, 0), /* Red */};

    AlgorithmFxn_RadarDrawFFTHeatMap_Init(pRadarDrawFFTHeatMapPrm);
    pRadarDrawFFTHeatMapPrm->numProfiles = pAr12xxCfg->radarParams[0].numProfiles;
    pRadarDrawFFTHeatMapPrm->outBufWidth = displayWidth;
    pRadarDrawFFTHeatMapPrm->outBufHeight = displayHeight;
    pRadarDrawFFTHeatMapPrm->outBufStartX = 240;
    pRadarDrawFFTHeatMapPrm->outBufStartY = 270;
    pRadarDrawFFTHeatMapPrm->numBins = 8;
    pRadarDrawFFTHeatMapPrm->baseClassCreateParams.numOutputBuffers = 3;
    for (i = 0U; i < pRadarDrawFFTHeatMapPrm->numProfiles; i++)
    {
        pRadarDrawFFTHeatMapPrm->rangeRes[i] = pAr12xxCfg->radarParams[0].rangeRes[i];
        pRadarDrawFFTHeatMapPrm->velocityRes[i] = pAr12xxCfg->radarParams[0].velocityRes[i];
    	pRadarDrawFFTHeatMapPrm->numTxAntenna[i] = pAr12xxCfg->radarParams[0].numTxAntenna[i];
    	pRadarDrawFFTHeatMapPrm->numRxAntenna[i] = pAr12xxCfg->radarParams[0].numRxAntenna[i];
    }

    for (cnt = 0; cnt <  pRadarDrawFFTHeatMapPrm->numBins; cnt ++)
    {
        pRadarDrawFFTHeatMapPrm->rgb565Color[cnt] = color[cnt];
        pRadarDrawFFTHeatMapPrm->binRange[cnt] = range[cnt];
    }


}

/**
 *******************************************************************************
 *
 * \brief   Function to Set up the Radar draw parameters
 *
 * \param   pRadarDrawFFTHeatMapPrm FFT Heat Map Draw create time parameters
 * \param   pAr12xxCfg              AR12 configuration obtained from
 *                                  #ChainsCommon_ar12xxConfig
 * \param   displayWidth            Output display width
 * \param   displayHeight           Output display height
 *
 * \return  None
 *
 *******************************************************************************
*/
Void ChainsCommon_ar12xxSetRadarDrawParams(
        AlgorithmFxn_RadarDrawCreateParams *pRadarDrawPrm,
        ChainsCommon_Ar12xxConfigOut *pAr12xxCfg,
        UInt32 displayWidth, UInt32 displayHeight)
{
    UInt32 i = 0U;
    AlgorithmFxn_RadarDraw_Init(pRadarDrawPrm);
    pRadarDrawPrm->numProfiles = pAr12xxCfg->radarParams[0].numProfiles;
    pRadarDrawPrm->imgFrameWidth = displayWidth;
    pRadarDrawPrm->imgFrameHeight = displayHeight;
    pRadarDrawPrm->numDrawAlg = 1;
    pRadarDrawPrm->drawAlgId[0] = ALG_FXN_RADAR_DRAW_ALG_DETECT;
    pRadarDrawPrm->drawOption = ALG_FXN_RADAR_DRAW_DETECT_OUTPUT;
    pRadarDrawPrm->baseClassCreateParams.numOutputBuffers = 3;
    pRadarDrawPrm->numHorzAngles = 2*CHAINS_RADAR_MAX_HORZ_ANGLE/CHAINS_RADAR_HORZ_RES + 1;
    pRadarDrawPrm->numVertAngles = 2*CHAINS_RADAR_MAX_VERT_ANGLE/CHAINS_RADAR_VERT_RES + 1;
    for (i = 0U; i < pRadarDrawPrm->numProfiles; i++)
    {
        pRadarDrawPrm->rangeRes[i] = pAr12xxCfg->radarParams[0].rangeRes[i];
        pRadarDrawPrm->velocityRes[i] = pAr12xxCfg->radarParams[0].velocityRes[i];
        pRadarDrawPrm->azimAngleRes[i] = CHAINS_RADAR_HORZ_RES;
        pRadarDrawPrm->elevAngleRes[i] = CHAINS_RADAR_VERT_RES;
        pRadarDrawPrm->maxVelocityBinNum[i] = pAr12xxCfg->radarParams[0].radarHeight[i];
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to Set up the FFT Heat Map draw control parameters
 *
 * \param   algId       Algorithm Link ID for the FFT Heat Map
 * \param   pAr12xxCfg  Pointer to the configuration structure.
 * \param   profId      Profile ID to which the profile will change to.
 *
 * \return  None
 *
 *******************************************************************************
*/
Void ChainsCommon_ar12xxSetFFTHeatMapProfile(UInt32 algId,
                                             ChainsCommon_Ar12xxConfigOut *pAr12xxCfg,
                                             UInt32 profId)
{
    AlgorithmFxn_RadarDrawFFTHeatMapControlParams ctrlPrms;
    ctrlPrms.baseClassControl.baseClassControl.size =
        sizeof(AlgorithmFxn_RadarDrawFFTHeatMapControlParams);
    ctrlPrms.baseClassControl.controlCmd =
        ALGORITHM_LINK_RADAR_PROCESS_CONTROL_CMD;
    if (profId < pAr12xxCfg->radarParams[0].numProfiles)
    {
        ctrlPrms.profileId = profId;
    }
    else
    {
        ctrlPrms.profileId = pAr12xxCfg->radarParams[0].numProfiles - 1;
        Vps_printf(" CHAINS: AR1243: Profile ID provided not supported. Defaulting to maximum profile number.\n\r");
    }
    ctrlPrms.rangeRes = pAr12xxCfg->radarParams[0].rangeRes[ctrlPrms.profileId];
    ctrlPrms.velocityRes = pAr12xxCfg->radarParams[0].velocityRes[ctrlPrms.profileId];

    System_linkControl(
                    algId,
                    ALGORITHM_LINK_CMD_CONFIG,
                    &ctrlPrms,
                    sizeof(ctrlPrms),
                    TRUE
                    );

}
/**
 *******************************************************************************
 *
 * \brief   Function to Set up the FFT Heat Map draw control parameters
 *
 * \param   algId       Algorithm Link ID for the FFT Heat Map
 * \param   pAr12xxCfg  Pointer to the configuration structure.
 * \param   profId      Profile ID to which the profile will change to.
 *
 * \return  None
 *
 *******************************************************************************
*/
Void ChainsCommon_ar12xxSetDrawProfile(UInt32 algId,
                                      ChainsCommon_Ar12xxConfigOut *pAr12xxCfg,
                                      UInt32 profId)
{
    AlgorithmFxn_RadarDrawControlParams ctrlPrms;
    ctrlPrms.baseClassControl.baseClassControl.size =
        sizeof(AlgorithmFxn_RadarDrawControlParams);
    ctrlPrms.baseClassControl.controlCmd =
        ALGORITHM_LINK_RADAR_PROCESS_CONTROL_CMD;
    if (profId < pAr12xxCfg->radarParams[0].numProfiles)
    {
        ctrlPrms.profileId = profId;
    }
    else
    {
        ctrlPrms.profileId = pAr12xxCfg->radarParams[0].numProfiles - 1;
        Vps_printf(" CHAINS: AR1243: Profile ID provided not supported. Defaulting to maximum profile number.\n\r");
    }
    ctrlPrms.rangeRes = pAr12xxCfg->radarParams[0].rangeRes[ctrlPrms.profileId];
    ctrlPrms.velocityRes = pAr12xxCfg->radarParams[0].velocityRes[ctrlPrms.profileId];
    ctrlPrms.azimAngleRes = CHAINS_RADAR_HORZ_RES;
    ctrlPrms.elevAngleRes = CHAINS_RADAR_VERT_RES;
    System_linkControl(
                    algId,
                    ALGORITHM_LINK_CMD_CONFIG,
                    &ctrlPrms,
                    sizeof(ctrlPrms),
                    TRUE
                    );

}


/**
 *******************************************************************************
 *
 * \brief   Function to calculate the steering Matrix
 *
 * \param   buffer          Steering Matrix Buffer Pointer
 * \param   angleStep       Step value between two angles.
 * \param   numAntenna      Number of Virtual Antennas.
 * \param   antSeparation   Antenna separation in wavelengths.
 *
 * \return  None
 *
 *******************************************************************************
*/
Void Chains_RadarCalculateSteeringMatrix(Int16 * buffer,
    double horzAngleStep, int32_t numHorzAntenna,
    double vertAngleStep, int32_t numVertAntenna,
    double antSeparation,
    double maxHorzAbsAngle, double maxVertAbsAngle)
{
    double currHorzAngle = -maxHorzAbsAngle, currVertAngle = -maxVertAbsAngle;
    double horzSineVal, vertSineVal, vertCosVal;
    Int32 i = 0, j = 0, k = 0, l = 0;
    Int32 numHorzAngles = (int32_t)((2 * maxHorzAbsAngle)/horzAngleStep) + 1;
    Int32 numVertAngles = (int32_t)((2 * maxVertAbsAngle)/vertAngleStep) + 1;
    Int16 *steerMatrix = (Int16*) buffer;
    /*
     * Generate the steering matrix (numVirtualAnt x numHorzAngles)
     * antSeparation = 0.5;    % in wavelength
     * antPosition   = [0:numVirtualAnt-1];
     * azimuthStep   = 1;
     * azimuthAngle  = [-60:azimuthStep:60];
     * steeringMat   = exp(1i*2*pi*antSeparation*antPosition'
     *                 *sin(azimuthAngle*pi/180));
     * Use Euler's formula:
     * e^(k) = cos(k) + i*sin(k)
     */
    for (i = 0; i < numVertAngles; i++)
    {
        vertCosVal = cos(currVertAngle * CHAINS_RADAR_PI_VALUE/180.0);
        vertSineVal = sin(currVertAngle * CHAINS_RADAR_PI_VALUE/180.0);
        for (j = 0; j < numHorzAngles; j++)
        {
            horzSineVal = sin(currHorzAngle * CHAINS_RADAR_PI_VALUE/180.0);
            for (k = 0; k < numVertAntenna; k++)
            {
                for (l = 0; l < numHorzAntenna; l++)
                {
                    double powerVal =
                        2* CHAINS_RADAR_PI_VALUE * antSeparation * (l * horzSineVal * vertCosVal + k * vertSineVal);
                    *(steerMatrix) = (Int16)(32767.0 * cos(powerVal));
                    steerMatrix++;
                    *(steerMatrix) = (Int16)(32767.0 * sin(powerVal));
                    steerMatrix++;
                }
            }
            currHorzAngle = currHorzAngle + horzAngleStep;
        }
        currVertAngle = currVertAngle + vertAngleStep;
        currHorzAngle = -maxHorzAbsAngle;
    }
}
