/* ======================================================================= */
/* DSPF_sp_nrand_cn.c -- natural C Implementation                            */
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
#include <math.h>
#include <float.h>
#include "DSPF_sp_nrand_cn.h"

/*=========================================================================*/
/* Ziggurat Constants                                                      */
/*=========================================================================*/
#define DSPF_sp_nrand_UINT32_TO_FLOAT 2.3283063e-010
#define DSPF_sp_nrand_AREA_DIV_Y0 3.910757959537090
#define DSPF_sp_nrand_RIGHT_MOST_X 3.654152885361009

/*=========================================================================*/
/* Internal Function Prototypes                                            */
/*=========================================================================*/
static float generate_random_normal_cn(_ti_uint32 *state);
static inline float sample_tail_cn(_ti_uint32 *state);

/*=========================================================================*/
/* External Function Prototypes                                            */
/*=========================================================================*/
extern unsigned int generate_random_ti_uint32_cn(_ti_uint32 *state);
extern float generate_random_float_cn(_ti_uint32 *state);

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
//#pragma DATA_SECTION(x_cn,".data:x_tbl_nrand_cn");
const float x_cn[] =
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

//#pragma DATA_SECTION(y_cn,".data:y_tbl_nrand_cn");
const float y_cn[] =
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
 *
 * Let right_most_x = 7.6971174701310501
 *     area = 0.0039496598225815571993
 *
 *
 *  1) ratios[0] = (uint32)(right_most * y[0]) / area) * 0xFFFFFFFFFFFFFFFF);
 *
 *  2) ratios[256] = 0;
 *
 *  3)  for i = 1:255
 *         ratios[i] = (uint32) ((x[i+1] / x[i]) * 0xFFFFFFFFFFFFFFFF);
 *      end loop;
 *
 *
 */

//#pragma DATA_SECTION(ratios_cn,".data:ratios_tbl_nrand_cn");
const unsigned int ratios_cn[] =
{
  4013152257, 4054164658, 4134297470, 4171211913, 4192825823, 4207150465,
  4217400383, 4225128475, 4231181040, 4236060395, 4240084356, 4243464262,
  4246346362, 4248835229, 4251007706, 4252921587, 4254621210, 4256141185,
  4257508945, 4258746523, 4259871830, 4260899585, 4261841997, 4262709286,
  4263510072, 4264251682, 4264940381, 4265581566, 4266179906, 4266739464,
  4267263794, 4267756018, 4268218890, 4268654849, 4269066064, 4269454471,
  4269821800, 4270169606, 4270499291, 4270812118, 4271109232, 4271391673,
  4271660385, 4271916231, 4272159998, 4272392407, 4272614120, 4272825744,
  4273027839, 4273220921, 4273405467, 4273581917, 4273750681, 4273912135,
  4274066634, 4274214503, 4274356047, 4274491551, 4274621280, 4274745480,
  4274864383, 4274978207, 4275087153, 4275191413, 4275291164, 4275386575,
  4275477802, 4275564994, 4275648290, 4275727821, 4275803711, 4275876075,
  4275945025, 4276010662, 4276073085, 4276132385, 4276188650, 4276241961,
  4276292397, 4276340029, 4276384927, 4276427155, 4276466777, 4276503848,
  4276538425, 4276570558, 4276600297, 4276627686, 4276652770, 4276675588,
  4276696178, 4276714577, 4276730817, 4276744930, 4276756945, 4276766889,
  4276774787, 4276780663, 4276784539, 4276786433, 4276786365, 4276784351,
  4276780405, 4276774542, 4276766773, 4276757109, 4276745558, 4276732128,
  4276716825, 4276699654, 4276680619, 4276659722, 4276636963, 4276612342,
  4276585858, 4276557506, 4276527284, 4276495185, 4276461203, 4276425328,
  4276387553, 4276347866, 4276306255, 4276262707, 4276217208, 4276169740,
  4276120288, 4276068831, 4276015352, 4275959826, 4275902233, 4275842547,
  4275780742, 4275716791, 4275650665, 4275582333, 4275511763, 4275438920,
  4275363769, 4275286273, 4275206391, 4275124082, 4275039302, 4274952007,
  4274862148, 4274769675, 4274674536, 4274576676, 4274476037, 4274372561,
  4274266184, 4274156842, 4274044464, 4273928981, 4273810318, 4273688395,
  4273563133, 4273434445, 4273302242, 4273166430, 4273026914, 4272883589,
  4272736350, 4272585084, 4272429676, 4272270002, 4272105934, 4271937337,
  4271764072, 4271585990, 4271402936, 4271214748, 4271021255, 4270822278,
  4270617630, 4270407111, 4270190514, 4269967620, 4269738198, 4269502006,
  4269258786, 4269008271, 4268750173, 4268484192, 4268210011, 4267927292,
  4267635680, 4267334797, 4267024243, 4266703596, 4266372403, 4266030188,
  4265676440, 4265310620, 4264932148, 4264540410, 4264134748, 4263714460,
  4263278794, 4262826945, 4262358049, 4261871178, 4261365336, 4260839449,
  4260292359, 4259722818, 4259129474, 4258510864, 4257865402, 4257191364,
  4256486875, 4255749888, 4254978169, 4254169273, 4253320518, 4252428955,
  4251491335, 4250504072, 4249463192, 4248364286, 4247202445, 4245972188,
  4244667376, 4243281112, 4241805614, 4240232079, 4238550499, 4236749457,
  4234815862, 4232734637, 4230488322, 4228056590, 4225415631, 4222537369,
  4219388469, 4215929044, 4212110960, 4207875596, 4203150820, 4197846871,
  4191850620, 4185017459, 4177159543, 4168028357, 4157288129, 4144473940,
  4128923200, 4109658453, 4085175839, 4053037230, 4009015318, 3945094812,
  3844040683, 3660926890, 3230394766, 0000000000
};

/*=========================================================================*/
/* Internal Functions                                                      */
/*=========================================================================*/

/*  Function Name: generate_random_normal
 *
 *  Purpose: This function is used internally to generate individual
 *  normally-distributed random \b floats. It should not be called by the user.
 *
 *  Precondition: The user has maintained the state array
 *
 *  Postcondition: A normally-distributed random \b float has been generated
 *
 *  \param state The array which was initialized with the "DSPF_sp_nrand32_init"
 *  function and maintained (but NEVER modified) by the user between subsequent
 *  calls to the "DSPF_sp_nrand32" function.
 *
 *  \returns A normally distributed random \b float.
 *
 */
#pragma CODE_SECTION(generate_random_normal_cn,".text:ansi")
static float generate_random_normal_cn(_ti_uint32 *state)
{
  /* local variables */
  _ti_uint32 rnd_num;
  _ti_uint32 box_index;
  _ti_int32 sign;
  float x_val;

  for (;;)
  {
    /*Select random box.*/
    rnd_num = generate_random_ti_uint32_cn(state);
    box_index = rnd_num & 0xFF;

    /*Determine sign based on the signed representation of rnd_num*/
    sign = ((_ti_int32) rnd_num < 0) ? -1 : 1;

    /*Generate uniform random integer with range [0,0xffffffff].*/
    rnd_num = generate_random_ti_uint32_cn(state);

    /* If at base segment of curve (ie. box_index == 0) */
    if (box_index == 0)
    {
      if (rnd_num < ratios_cn[0])
      {
        /* Generated x is within bottom box. */
        return rnd_num * DSPF_sp_nrand_UINT32_TO_FLOAT
            * DSPF_sp_nrand_AREA_DIV_Y0 * sign;
      }
      /* else the value is in the tail of the curve.
       * This path is the least likely to execute, so the calls
       * to log in sample_tail() are insignificant
       */
      return sample_tail_cn(state) * sign;
    }

    /* If at any other segment in the curve */
    if (rnd_num < ratios_cn[box_index])
    {
      /* Generated value is inside a rectangle.
       * This is the most common path
       */
      return rnd_num * DSPF_sp_nrand_UINT32_TO_FLOAT * x_cn[box_index] * sign;
    }

    /* else, generated value MAY BE outside rectangle. */
    x_val = rnd_num * DSPF_sp_nrand_UINT32_TO_FLOAT * x_cn[box_index];

    if (y_cn[box_index - 1] + ((y_cn[box_index] - y_cn[box_index - 1])
        * generate_random_float_cn(state))
        < expf((double) -(x_val * x_val / 2.0)))
    {
      return x_val * sign;
    }
  }
} /* generate_random_normal_cn */

/*  Function Name: sample_tail
 *
 *  Purpose: This function is used internally to sample the tails of the
 *  normal distribution should the generated random x value fall inside the
 *  lowest horizontal slice of the bell-curve, but outside of the rectangle
 *  associated with that section and instead inside the tail.
 *
 *  Precondition: The user has maintained the state array
 *
 *  Postcondition: A random \b based on the current state of the RNG that is
 *  located within the tail region of the bell-curve has been returned.
 *
 *  \param state The array which was initialized with the
 *  "DSPF_sp_nrand32_init" function and maintained (but NEVER modified) by the
 *  user between subsequent calls to the "DSPF_sp_nrand32" function.
 *
 *  @returns A random \b float value located in the tail section of the
 *  bell-curve.
 */
#pragma CODE_SECTION(sample_tail_cn,".text:ansi")
static inline float sample_tail_cn(_ti_uint32 *state)
{
  float x, y;
  do
  {
    x = logf(generate_random_float_cn(state) + FLT_MIN)
        / DSPF_sp_nrand_RIGHT_MOST_X;

    y = -logf(generate_random_float_cn(state) + FLT_MIN);

  } while (y + y < x * x);
  return DSPF_sp_nrand_RIGHT_MOST_X + x;
} /* sample_tail_cn */

/*=========================================================================*/
/* User Functions                                                          */
/*=========================================================================*/

#pragma CODE_SECTION(DSPF_sp_nrand_cn,".text:ansi");
void DSPF_sp_nrand_cn(int size, float *vector, void *state)
{
  /* New pointers to take care of void pointers */
  _ti_uint32* v_state = (_ti_uint32*) state;
  float* array = vector;

  int i = 0; /* loop counter */
  while (i < size)
  {
    array[i++] = generate_random_normal_cn((_ti_uint32*) v_state);
  }
} /* DSPF_sp_nrand_cn */

/* ======================================================================== */
/*  End of file:  DSPF_sp_nrand_cn.c                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
