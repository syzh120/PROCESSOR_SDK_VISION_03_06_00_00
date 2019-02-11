/* ======================================================================= */
/* DSPF_sp_nrand.c -- Optimized C Implementation                           */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* Copyright (c) 2011 Mutsuo Saito, Makoto Matsumoto, Hiroshima            */
/* University and The University of Tokyo. All rights reserved.            */
/*                                                                         */
/* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/  */
/*                                                                         */
/*                                                                         */
/*  Redistribution and use in source and binary forms, with or without     */
/*  modification, are permitted provided that the following conditions     */
/*  are met:                                                               */
/*                                                                         */
/*    Redistributions of source code must retain the above copyright       */
/*    notice, this list of conditions and the following disclaimer.        */
/*                                                                         */
/*    Redistributions in binary form must reproduce the above copyright    */
/*    notice, this list of conditions and the following disclaimer in the  */
/*    documentation and/or other materials provided with the               */
/*    distribution.                                                        */
/*                                                                         */
/*    Neither the name of Texas Instruments Incorporated nor the names of  */
/*    its contributors may be used to endorse or promote products derived  */
/*    from this software without specific prior written permission.        */
/*                                                                         */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                         */
/* ======================================================================= */

/*=========================================================================*/
/* Includes                                                                */
/*=========================================================================*/
#include <float.h>
#include <stdbool.h>
#include "..\..\DSP_urand32\c66\DSPF_sp_math_i.h"
#include "DSPF_sp_nrand.h"

/*=========================================================================*/
/* Ziggurat Constants                                                      */
/*=========================================================================*/
#define DSPF_sp_nrand_AREA_DIV_Y0 (float)3.910757959537090
#define DSPF_sp_nrand_RIGHT_MOST_X (float)3.654152885361009
#define DSPF_sp_nrand_ONE_OVER_RIGHT_MOST_X (float)0.273661237329758

/*=========================================================================*/
/* Internal Function Prototypes                                            */
/*=========================================================================*/

static inline float sample_tail_nrand(
    _ti_uint32 *s0,         /*Status_0*/
    _ti_uint32 *s1,         /*Status_1*/
    _ti_uint32 *s2,         /*Status_2*/
    _ti_uint32 *s3,         /*Status_3*/
    const _ti_uint32 mat1,  /*Polynomial constant mat1*/
    const _ti_uint32 mat2,  /*Polynomial constant mat2*/
    const _ti_uint32 tmat); /*Polynomial constant tmat*/

/*=========================================================================*/
/* Precomputed Tables                                                      */
/*=========================================================================*/

/* Precomputed tables of x and y values for ziggurat boxes. These values were
 *  computed with the following algorithm:
 *
 * Let right_most_x = 3.6541528853610088
 *     area = 0.00492867323399
 *
 * 1)  x[0] = right_most_x;    -- by definition (Marsaglia and Tsang)
 *
 * 2)  y[0] = exp(-x[0] * x[0] * 0.5);    -- f(x) = e^(-(x^2)/2))
 *
 * 3)  x[1] = x[0];            -- by definition (Marsaglia and Tsang)
 *
 * 4)  y[1] = y[0] + (area / x[1]);
 *
 * 5)  for i = 2:255
 *          x[i] = sqrt(-2.0 * ln(y[i-1]))
 *          y[i] = y[i-1] + (area/x[i]);
 *     end loop;
 *
 * 6)  x[256] = 0;
 *
 *     *Note: For definitions, see "The Ziggurat Method for Generating
 *            Random Variables" by Marsaglia and Tsang.
 */

#pragma DATA_SECTION(x,".data:x_tbl_nrand");
const float x[] =
{
  3.6541529, 3.6541529, 3.4492784, 3.3202448, 3.2245750, 3.1478894, 3.0835261,
  3.0278378, 2.9786034, 2.9343669, 2.8941212, 2.8571386, 2.8228774, 2.7909212,
  2.7609439, 2.7326853, 2.7059336, 2.6805146, 2.6562831, 2.6331165, 2.6109104,
  2.5895760, 2.5690355, 2.5492215, 2.5300753, 2.5115445, 2.4935830, 2.4761500,
  2.4592085, 2.4427254, 2.4266710, 2.4110184, 2.3957431, 2.3808229, 2.3662372,
  2.3519673, 2.3379962, 2.3243079, 2.3108883, 2.2977233, 2.2848008, 2.2721090,
  2.2596371, 2.2473750, 2.2353134, 2.2234433, 2.2117567, 2.2002456, 2.1889029,
  2.1777215, 2.1666951, 2.1558177, 2.1450837, 2.1344872, 2.1240232, 2.1136870,
  2.1034741, 2.0933797, 2.0833998, 2.0735302, 2.0637674, 2.0541079, 2.0445480,
  2.0350842, 2.0257139, 2.0164337, 2.0072408, 1.9981325, 1.9891061, 1.9801589,
  1.9712887, 1.9624931, 1.9537697, 1.9451165, 1.9365314, 1.9280124, 1.9195573,
  1.9111645, 1.9028322, 1.8945585, 1.8863418, 1.8781805, 1.8700730, 1.8620176,
  1.8540131, 1.8460579, 1.8381506, 1.8302900, 1.8224746, 1.8147032, 1.8069746,
  1.7992876, 1.7916410, 1.7840337, 1.7764645, 1.7689325, 1.7614363, 1.7539753,
  1.7465483, 1.7391542, 1.7317923, 1.7244616, 1.7171609, 1.7098897, 1.7026469,
  1.6954317, 1.6882432, 1.6810807, 1.6739433, 1.6668303, 1.6597408, 1.6526742,
  1.6456295, 1.6386062, 1.6316035, 1.6246206, 1.6176568, 1.6107116, 1.6037842,
  1.5968738, 1.5899799, 1.5831017, 1.5762388, 1.5693902, 1.5625554, 1.5557340,
  1.5489250, 1.5421282, 1.5353426, 1.5285677, 1.5218030, 1.5150478, 1.5083016,
  1.5015637, 1.4948335, 1.4881105, 1.4813941, 1.4746835, 1.4679785, 1.4612782,
  1.4545821, 1.4478897, 1.4412003, 1.4345133, 1.4278282, 1.4211444, 1.4144613,
  1.4077783, 1.4010948, 1.3944101, 1.3877238, 1.3810352, 1.3743436, 1.3676486,
  1.3609494, 1.3542453, 1.3475358, 1.3408203, 1.3340981, 1.3273686, 1.3206310,
  1.3138846, 1.3071290, 1.3003632, 1.2935867, 1.2867987, 1.2799984, 1.2731853,
  1.2663583, 1.2595168, 1.2526603, 1.2457875, 1.2388979, 1.2319906, 1.2250646,
  1.2181194, 1.2111537, 1.2041669, 1.1971577, 1.1901255, 1.1830691, 1.1759876,
  1.1688799, 1.1617448, 1.1545814, 1.1473885, 1.1401649, 1.1329093, 1.1256205,
  1.1182972, 1.1109381, 1.1035417, 1.0961066, 1.0886314, 1.0811144, 1.0735540,
  1.0659487, 1.0582964, 1.0505956, 1.0428443, 1.0350405, 1.0271820, 1.0192667,
  1.0112925, 1.0032567, 0.9951570, 0.9869907, 0.9787552, 0.9704473, 0.9620641,
  0.9536024, 0.9450587, 0.9364293, 0.9277105, 0.9188982, 0.9099879, 0.9009752,
  0.8918551, 0.8826222, 0.8732710, 0.8637955, 0.8541892, 0.8444449, 0.8345553,
  0.8245122, 0.8143067, 0.8039291, 0.7933691, 0.7826150, 0.7716544, 0.7604734,
  0.7490566, 0.7373872, 0.7254462, 0.7132123, 0.7006618, 0.6877679, 0.6744998,
  0.6608226, 0.6466957, 0.6320722, 0.6168970, 0.6011046, 0.5846168, 0.5673382,
  0.5491517, 0.5299097, 0.5094233, 0.4874440, 0.4636343, 0.4375184, 0.4083891,
  0.3751213, 0.3357375, 0.2861746, 0.2152419, 0.0000000
};


#pragma DATA_SECTION(y,".data:y_tbl_nrand");
const float y[] =
{
  0.0012603, 0.0026091, 0.0040380, 0.0055224, 0.0070509, 0.0086166, 0.0102150,
  0.0118430, 0.0134970, 0.0151770, 0.0168800, 0.0186050, 0.0203510, 0.0221170,
  0.0239020, 0.0257060, 0.0275270, 0.0293660, 0.0312210, 0.0330930, 0.0349810,
  0.0368840, 0.0388030, 0.0407360, 0.0426840, 0.0446470, 0.0466230, 0.0486140,
  0.0506180, 0.0526350, 0.0546660, 0.0567110, 0.0587680, 0.0608380, 0.0629210,
  0.0650170, 0.0671250, 0.0692450, 0.0713780, 0.0735230, 0.0756800, 0.0778490,
  0.0800310, 0.0822240, 0.0844290, 0.0866450, 0.0888740, 0.0911140, 0.0933650,
  0.0956290, 0.0979030, 0.1001900, 0.1024900, 0.1048000, 0.1071200, 0.1094500,
  0.1117900, 0.1141500, 0.1165100, 0.1188900, 0.1212800, 0.1236800, 0.1260900,
  0.1285100, 0.1309400, 0.1333900, 0.1358400, 0.1383100, 0.1407900, 0.1432700,
  0.1457800, 0.1482900, 0.1508100, 0.1533400, 0.1558900, 0.1584400, 0.1610100,
  0.1635900, 0.1661800, 0.1687800, 0.1714000, 0.1740200, 0.1766600, 0.1793000,
  0.1819600, 0.1846300, 0.1873100, 0.1900000, 0.1927100, 0.1954300, 0.1981500,
  0.2008900, 0.2036400, 0.2064100, 0.2091800, 0.2119700, 0.2147600, 0.2175700,
  0.2204000, 0.2232300, 0.2260800, 0.2289300, 0.2318000, 0.2346900, 0.2375800,
  0.2404900, 0.2434100, 0.2463400, 0.2492800, 0.2522400, 0.2552100, 0.2581900,
  0.2611900, 0.2642000, 0.2672200, 0.2702500, 0.2733000, 0.2763600, 0.2794300,
  0.2825200, 0.2856200, 0.2887300, 0.2918600, 0.2950000, 0.2981500, 0.3013200,
  0.3045000, 0.3077000, 0.3109100, 0.3141300, 0.3173700, 0.3206200, 0.3238900,
  0.3271700, 0.3304700, 0.3337800, 0.3371100, 0.3404500, 0.3438100, 0.3471800,
  0.3505700, 0.3539700, 0.3573900, 0.3608300, 0.3642800, 0.3677500, 0.3712400,
  0.3747400, 0.3782500, 0.3817900, 0.3853400, 0.3889100, 0.3925000, 0.3961000,
  0.3997200, 0.4033600, 0.4070200, 0.4106900, 0.4143900, 0.4181000, 0.4218300,
  0.4255800, 0.4293500, 0.4331400, 0.4369500, 0.4407900, 0.4446400, 0.4485100,
  0.4524000, 0.4563100, 0.4602500, 0.4642000, 0.4681800, 0.4721800, 0.4762000,
  0.4802500, 0.4843200, 0.4884100, 0.4925300, 0.4966700, 0.5008400, 0.5050300,
  0.5092500, 0.5134900, 0.5177600, 0.5220500, 0.5263700, 0.5307300, 0.5351000,
  0.5395100, 0.5439500, 0.5484100, 0.5529100, 0.5574400, 0.5620000, 0.5665900,
  0.5712100, 0.5758700, 0.5805600, 0.5852900, 0.5900500, 0.5948500, 0.5996800,
  0.6045600, 0.6094700, 0.6144200, 0.6194100, 0.6244500, 0.6295300, 0.6346500,
  0.6398200, 0.6450400, 0.6503000, 0.6556100, 0.6609800, 0.6663900, 0.6718600,
  0.6773900, 0.6829700, 0.6886200, 0.6943200, 0.7000900, 0.7059300, 0.7118300,
  0.7178100, 0.7238600, 0.7300000, 0.7362100, 0.7425100, 0.7488900, 0.7553700,
  0.7619500, 0.7686400, 0.7754300, 0.7823400, 0.7893800, 0.7965400, 0.8038500,
  0.8113100, 0.8189300, 0.8267300, 0.8347200, 0.8429200, 0.8513500, 0.8600300,
  0.8690100, 0.8783100, 0.8879800, 0.8981000, 0.9087300, 0.9199900, 0.9320600,
  0.9452000, 0.9598800, 0.9771000, 1.0000000
};


/*  Precomputed table of ratios. These numbers represent
 *  the ratio of box[i+1] that is contained within box[i].
 *  These values are computed as follows
 *
 * Let right_most_x = 3.6541528853610088
 *     area = 0.00492867323399
 *
 *
 *  1) ratios[0] = ((right_most * y[0]) / area);
 *
 *  2) ratios[256] = 0;
 *
 *  3)  for i = 1:255
 *         ratios[i] = (x[i+1] / x[i]);
 *      end loop;
 *
 *
 */
#pragma DATA_SECTION(ratios,".data:ratios_tbl_nrand");
const float ratios[] =
{
  0.9343953, 0.9439338, 0.9625912, 0.9711859, 0.9762183, 0.9795535, 0.9819400,
  0.9837394, 0.9851486, 0.9862847, 0.9872215, 0.9880086, 0.9886796, 0.9892590,
  0.9897649, 0.9902105, 0.9906062, 0.9909602, 0.9912785, 0.9915666, 0.9918287,
  0.9920680, 0.9922874, 0.9924894, 0.9926758, 0.9928484, 0.9930089, 0.9931581,
  0.9932974, 0.9934277, 0.9935498, 0.9936644, 0.9937722, 0.9938737, 0.9939694,
  0.9940598, 0.9941453, 0.9942264, 0.9943030, 0.9943759, 0.9944451, 0.9945109,
  0.9945734, 0.9946330, 0.9946897, 0.9947439, 0.9947955, 0.9948448, 0.9948918,
  0.9949367, 0.9949797, 0.9950209, 0.9950601, 0.9950977, 0.9951337, 0.9951682,
  0.9952011, 0.9952326, 0.9952627, 0.9952917, 0.9953195, 0.9953460, 0.9953712,
  0.9953956, 0.9954188, 0.9954410, 0.9954623, 0.9954826, 0.9955019, 0.9955204,
  0.9955381, 0.9955549, 0.9955710, 0.9955863, 0.9956009, 0.9956146, 0.9956278,
  0.9956402, 0.9956520, 0.9956630, 0.9956735, 0.9956833, 0.9956925, 0.9957011,
  0.9957092, 0.9957167, 0.9957236, 0.9957300, 0.9957358, 0.9957411, 0.9957459,
  0.9957502, 0.9957540, 0.9957573, 0.9957601, 0.9957623, 0.9957642, 0.9957656,
  0.9957665, 0.9957670, 0.9957669, 0.9957665, 0.9957655, 0.9957642, 0.9957624,
  0.9957600, 0.9957575, 0.9957542, 0.9957508, 0.9957467, 0.9957423, 0.9957374,
  0.9957321, 0.9957264, 0.9957202, 0.9957137, 0.9957066, 0.9956992, 0.9956912,
  0.9956829, 0.9956741, 0.9956648, 0.9956551, 0.9956450, 0.9956344, 0.9956233,
  0.9956119, 0.9955998, 0.9955873, 0.9955745, 0.9955610, 0.9955472, 0.9955328,
  0.9955178, 0.9955025, 0.9954866, 0.9954701, 0.9954532, 0.9954357, 0.9954177,
  0.9953991, 0.9953799, 0.9953602, 0.9953398, 0.9953189, 0.9952974, 0.9952753,
  0.9952525, 0.9952289, 0.9952049, 0.9951802, 0.9951547, 0.9951286, 0.9951017,
  0.9950740, 0.9950456, 0.9950165, 0.9949865, 0.9949558, 0.9949241, 0.9948915,
  0.9948583, 0.9948239, 0.9947888, 0.9947526, 0.9947153, 0.9946772, 0.9946378,
  0.9945976, 0.9945562, 0.9945135, 0.9944697, 0.9944246, 0.9943783, 0.9943307,
  0.9942816, 0.9942312, 0.9941792, 0.9941258, 0.9940709, 0.9940143, 0.9939560,
  0.9938958, 0.9938339, 0.9937701, 0.9937043, 0.9936364, 0.9935663, 0.9934940,
  0.9934193, 0.9933423, 0.9932625, 0.9931802, 0.9930950, 0.9930069, 0.9929157,
  0.9928212, 0.9927234, 0.9926220, 0.9925168, 0.9924075, 0.9922942, 0.9921765,
  0.9920539, 0.9919266, 0.9917939, 0.9916559, 0.9915118, 0.9913615, 0.9912046,
  0.9910406, 0.9908689, 0.9906893, 0.9905011, 0.9903033, 0.9900958, 0.9898775,
  0.9896475, 0.9894052, 0.9891495, 0.9888790, 0.9885923, 0.9882887, 0.9879659,
  0.9876224, 0.9872559, 0.9868646, 0.9864450, 0.9859949, 0.9855103, 0.9849873,
  0.9844212, 0.9838064, 0.9831360, 0.9824028, 0.9815976, 0.9807084, 0.9797224,
  0.9786223, 0.9773874, 0.9759913, 0.9744003, 0.9725708, 0.9704447, 0.9679441,
  0.9649604, 0.9613399, 0.9568545, 0.9511540, 0.9436713, 0.9334216, 0.9185390,
  0.8950105, 0.8523760, 0.7521349, 0.0000000,
};

/*=========================================================================*/
/* Internal Functions                                                      */
/*=========================================================================*/

/*  Function Name: sample_tail
 *
 *  Purpose: This function is used internally to sample the tails of the
 *  normal distribution should the generated random x value fall inside the
 *  lowest horizontal slice of the bell-curve, but outside of the rectangle
 *  associated with that section and instead inside the tail.
 *
 *  Precondition: The calling function has passed valid state variable
 *  pointers and polynomial constants.
 *
 *  Postcondition: A random @b float based on the current state of the RNG
 *  that is located within the tail region of the bell-curve has been
 *  returned.
 *
 *  @param s0 : Pointer to the STATUS_0 variable of type @b _ti_uint32
 *  @param s1 : Pointer to the STATUS_1 variable of type @b _ti_uint32
 *  @param s2 : Pointer to the STATUS_2 variable of type @b _ti_uint32
 *  @param s3 : Pointer to the STATUS_3 variable of type @b _ti_uint32
 *
 *  @param mat1 : constant polynomial characteristic number MAT_1
 *   of type @b _ti_uint32
 *
 *  @param mat2 : constant polynomial characteristic number MAT_2
 *   of type @b _ti_uint32
 *
 *  @param tmat : constant polynomial characteristic number TMAT
 *   of type @b _ti_uint32
 *
 *  @returns A random @b float value located in the tail section of the
 *  bell-curve.
 *
 */

#pragma CODE_SECTION(sample_tail_nrand,".text:ansi");
#pragma FUNC_ALWAYS_INLINE (sample_tail_nrand);
static inline float sample_tail_nrand(
    _ti_uint32 *s0,         /*Status_0*/
    _ti_uint32 *s1,         /*Status_1*/
    _ti_uint32 *s2,         /*Status_2*/
    _ti_uint32 *s3,          /*Status_3*/
    const _ti_uint32 mat1,  /*Polynomial constant mat1*/
    const _ti_uint32 mat2,  /*Polynomial constant mat2*/
    const _ti_uint32 tmat)  /*Polynomial constant tmat*/

{
  float x, y;

  do
  {
    x = DSP_logsp_i(GENERATE_RANDOM_FLOAT(s0,s1,s2,s3,mat1,mat2,tmat))
        * DSPF_sp_nrand_ONE_OVER_RIGHT_MOST_X;

    y = -DSP_logsp_i(GENERATE_RANDOM_FLOAT(s0,s1,s2,s3,mat1,mat2,tmat));
  } while (y + y < x * x);
  return DSPF_sp_nrand_RIGHT_MOST_X + x;
} /* sample_tail_nrand */

/*=========================================================================*/
/* User Functions                                                          */
/*=========================================================================*/

#pragma CODE_SECTION(DSPF_sp_nrand,".text:ansi");
void DSPF_sp_nrand(int size, float *vector, void *state)
{
  /* New pointers to take care of void pointers */
  _ti_uint32 *v_state = (_ti_uint32*) state;

  /* local variables for state */
  _ti_uint32 s0 = v_state[DSP_urand32_STATUS_0];
  _ti_uint32 s1 = v_state[DSP_urand32_STATUS_1];
  _ti_uint32 s2 = v_state[DSP_urand32_STATUS_2];
  _ti_uint32 s3 = v_state[DSP_urand32_STATUS_3];

  /* local variables for polynomial */
  const _ti_uint32 mat1 = v_state[DSP_urand32_MAT_1];
  const _ti_uint32 mat2 = v_state[DSP_urand32_MAT_2];
  const _ti_uint32 tmat = v_state[DSP_urand32_TMAT];

  /* Ziggurat Variables */
  register _ti_uint32 box_index;
  register _ti_uint32 temp;
  register _ti_int32 sign;
  register float rnd_num;
  register float random_y;
  register float accepted_y;
  register float result;
  register float sample;
  register bool number_found = false;

  /* Loop Counter, signed for optimization, --see SPRA666 Section 3.2-- */
  register signed int i = 0;


  /* Start Loop */
  while (i < size)
  {
    /*Select random box.*/
    temp = DSP_urand32_generate_random_ti_uint32(&s0,&s1,&s2,&s3,mat1,mat2,tmat);
    box_index = temp & 0xFF;

    /*Determine sign based on the signed representation of temp */
    sign = ((_ti_int32) temp < 0) ? -1 : 1;

    /*Generate uniform random value with range (0,1). */
    rnd_num = (DSP_urand32_generate_random_ti_uint32(&s0,&s1,&s2,&s3,mat1,mat2,tmat)
                           * DSPF_sp_urand_UINT_TO_FLOAT +  FLT_MIN);

    /* pre-load most-common samples from table for simpler control code */
    sample  = rnd_num * sign * x[box_index];

    /* If at base segment of curve (ie. box_index == 0) */
    if (box_index == 0)
    {
      if (rnd_num < ratios[0])
      {
        /* Generated x is within bottom box. */
        result = rnd_num * DSPF_sp_nrand_AREA_DIV_Y0 * sign;
      }

      /* else the value is in the tail of the curve.
       * This path is the least likely to execute, so the calls
       * to log in sample_tail() are insignificant
       */
      else
      {
        result = sample_tail_nrand(&s0, &s1, &s2, &s3, mat1, mat2, tmat) * sign;
      }
      number_found = true;
    }

    /* If at any other segment in the curve */
    if ((!number_found) & (rnd_num < ratios[box_index]))
    {
      /* Generated value is inside a rectangle.
       * This is the most common path
       */
      result = sample;
      number_found = true;
    }

    /* else, generated value MAY BE outside rectangle. */
    if (!number_found)
    {
      random_y = y[box_index - 1] + ((y[box_index] - y[box_index - 1]) *
          (DSP_urand32_generate_random_ti_uint32(&s0,&s1,&s2,&s3,mat1,mat2,tmat)
                                     * DSPF_sp_urand_UINT_TO_FLOAT +  FLT_MIN));

      accepted_y = DSP_expsp_i(-(sample * sample * 0.5));

      if (random_y < accepted_y)
      {
        result = sample;
        number_found = true;
      }
    }

    /* If a number fitting the curve is found, store it and find next number */
    if (number_found)
    {
      vector[i++] = result;
      number_found = false;
    }

    /* else, keep looking for a number that fits the curve */
  }

  /* Save the state of the RNG for future use. */
  DSP_urand32_SAVE_STATE(s0, s1, s2, s3);
} /* DSPF_sp_nrand */

/* ======================================================================== */
/*  End of file:  DSPF_sp_nrand.c                                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
