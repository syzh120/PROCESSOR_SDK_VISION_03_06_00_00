/* ======================================================================= */
/* DSPF_sp_erand_cn.c -- Natural C Implementation                          */
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
#include <stddef.h>
#include <stdlib.h>
#include "DSPF_sp_erand_cn.h"

/*=========================================================================*/
/* Ziggurat Constants                                                      */
/*=========================================================================*/
#define DSPF_sp_erand_UINT32_TO_FLOAT 2.3283063e-010
#define DSPF_sp_erand_AREA_DIV_Y0 8.697117470131053
#define DSPF_sp_erand_RIGHT_MOST_X 7.697117470131050

/*=========================================================================*/
/* Internal Function Prototypes                                            */
/*=========================================================================*/
static float generate_random_exp_cn(_ti_uint32 *state);
static inline float sample_tail_cn(_ti_uint32 rnd_num);

/*=========================================================================*/
/* External Function Prototypes                                            */
/*=========================================================================*/
extern unsigned int generate_random_ti_uint32_cn(_ti_uint32 *state);
extern float generate_random_float_cn(_ti_uint32 *state);


/*=========================================================================*/
/* Precomputed Tables                                                      */
/*=========================================================================*/

/*  Precomputed tables of x and y values for ziggurat boxes. These values were
 *  computed with the following algorithm:
 *
 * Let right_most_x = 7.6971174701310501
 *     area = 0.0039496598225815571993
 *
 * 1)  x[0] = right_most_x;    -- by definition (Marsaglia and Tsang)
 *
 * 2)  y[0] = exp(-x[0]);      -- f(x) = e^(-x)
 *
 * 3)  x[1] = x[0];            -- by definition (Marsaglia and Tsang)
 *
 * 4)  y[1] = y[0] + (area / x[1]);
 *
 * 5)  for i = 2:255
 *          x[i] = -ln(x);
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
  7.6971173, 7.6971173, 6.9410338, 6.4783783, 6.1441646, 5.8821445, 5.6664100,
  5.4828906, 5.3230906, 5.1814871, 5.0542884, 4.9387770, 4.8329396, 4.7352428,
  4.6444917, 4.5597372, 4.4802117, 4.4052877, 4.3344436, 4.2672424, 4.2033138,
  4.1423407, 4.0840511, 4.0282087, 3.9746060, 3.9230626, 3.8734176, 3.8255293,
  3.7792709, 3.7345288, 3.6912010, 3.6491954, 3.6084287, 3.5688252, 3.5303159,
  3.4928377, 3.4563329, 3.4207485, 3.3860354, 3.3521490, 3.3190475, 3.2866921,
  3.2550473, 3.2240796, 3.1937580, 3.1640534, 3.1349390, 3.1063890, 3.0783801,
  3.0508900, 3.0238974, 2.9973829, 2.9713278, 2.9457145, 2.9205263, 2.8957477,
  2.8713641, 2.8473608, 2.8237252, 2.8004444, 2.7775061, 2.7548993, 2.7326126,
  2.7106361, 2.6889596, 2.6675739, 2.6464701, 2.6256390, 2.6050730, 2.5847638,
  2.5647042, 2.5448866, 2.5253043, 2.5059507, 2.4868193, 2.4679041, 2.4491990,
  2.4306984, 2.4123969, 2.3942890, 2.3763702, 2.3586349, 2.3410792, 2.3236978,
  2.3064868, 2.2894418, 2.2725589, 2.2558339, 2.2392628, 2.2228425, 2.2065690,
  2.1904390, 2.1744490, 2.1585958, 2.1428764, 2.1272876, 2.1118267, 2.0964901,
  2.0812759, 2.0661807, 2.0512023, 2.0363381, 2.0215852, 2.0069418, 1.9924049,
  1.9779727, 1.9636427, 1.9494127, 1.9352808, 1.9212447, 1.9073025, 1.8934522,
  1.8796918, 1.8660195, 1.8524336, 1.8389319, 1.8255131, 1.8121753, 1.7989168,
  1.7857360, 1.7726312, 1.7596009, 1.7466437, 1.7337579, 1.7209420, 1.7081947,
  1.6955146, 1.6829001, 1.6703500, 1.6578629, 1.6454375, 1.6330724, 1.6207665,
  1.6085185, 1.5963271, 1.5841911, 1.5721092, 1.5600805, 1.5481036, 1.5361774,
  1.5243009, 1.5124729, 1.5006921, 1.4889578, 1.4772687, 1.4656237, 1.4540218,
  1.4424621, 1.4309433, 1.4194646, 1.4080249, 1.3966233, 1.3852586, 1.3739300,
  1.3626364, 1.3513769, 1.3401506, 1.3289564, 1.3177934, 1.3066607, 1.2955571,
  1.2844820, 1.2734343, 1.2624129, 1.2514172, 1.2404459, 1.2294981, 1.2185732,
  1.2076699, 1.1967874, 1.1859246, 1.1750807, 1.1642547, 1.1534455, 1.1426523,
  1.1318740, 1.1211096, 1.1103581, 1.0996186, 1.0888900, 1.0781711, 1.0674613,
  1.0567590, 1.0460634, 1.0353734, 1.0246879, 1.0140057, 1.0033256, 0.9926464,
  0.9819670, 0.9712862, 0.9606027, 0.9499152, 0.9392223, 0.9285228, 0.9178152,
  0.9070981, 0.8963700, 0.8856295, 0.8748749, 0.8641046, 0.8533170, 0.8425103,
  0.8316829, 0.8208326, 0.8099577, 0.7990562, 0.7881259, 0.7771646, 0.7661701,
  0.7551400, 0.7440717, 0.7329627, 0.7218101, 0.7106110, 0.6993625, 0.6880611,
  0.6767036, 0.6652861, 0.6538050, 0.6422560, 0.6306347, 0.6189365, 0.6071562,
  0.5952886, 0.5833277, 0.5712673, 0.5591006, 0.5468201, 0.5344179, 0.5218850,
  0.5092120, 0.4963880, 0.4834015, 0.4702393, 0.4568868, 0.4433279, 0.4295439,
  0.4155142, 0.4012147, 0.3866180, 0.3716922, 0.3563998, 0.3406965, 0.3245291,
  0.3078330, 0.2905280, 0.2725132, 0.2536584, 0.2337905, 0.2126715, 0.1899587,
  0.1651276, 0.1373050, 0.1048385, 0.0638522, 0.0000000
};

//#pragma DATA_SECTION(y_cn,".data:y_tbl_nrand_cn");
const float y_cn[] =
{
  0.0004541, 0.0009673, 0.0015363, 0.0021460, 0.0027888, 0.0034603, 0.0041573,
  0.0048777, 0.0056196, 0.0063819, 0.0071634, 0.0079631, 0.0087803, 0.0096144,
  0.0104648, 0.0113310, 0.0122126, 0.0131092, 0.0140204, 0.0149460, 0.0158856,
  0.0168391, 0.0178062, 0.0187867, 0.0197804, 0.0207872, 0.0218069, 0.0228393,
  0.0238844, 0.0249420, 0.0260120, 0.0270944, 0.0281889, 0.0292957, 0.0304144,
  0.0315452, 0.0326880, 0.0338426, 0.0350090, 0.0361873, 0.0373773, 0.0385790,
  0.0397924, 0.0410174, 0.0422541, 0.0435024, 0.0447623, 0.0460338, 0.0473168,
  0.0486114, 0.0499175, 0.0512352, 0.0525645, 0.0539053, 0.0552577, 0.0566216,
  0.0579972, 0.0593843, 0.0607830, 0.0621934, 0.0636154, 0.0650491, 0.0664945,
  0.0679516, 0.0694204, 0.0709011, 0.0723935, 0.0738977, 0.0754139, 0.0769419,
  0.0784819, 0.0800340, 0.0815980, 0.0831741, 0.0847623, 0.0863627, 0.0879754,
  0.0896003, 0.0912375, 0.0928871, 0.0945492, 0.0962237, 0.0979109, 0.0996106,
  0.1013230, 0.1030482, 0.1047861, 0.1065370, 0.1083008, 0.1100777, 0.1118676,
  0.1136708, 0.1154872, 0.1173169, 0.1191601, 0.1210167, 0.1228870, 0.1247709,
  0.1266686, 0.1285802, 0.1305057, 0.1324453, 0.1343991, 0.1363671, 0.1383494,
  0.1403462, 0.1423576, 0.1443837, 0.1464246, 0.1484804, 0.1505512, 0.1526371,
  0.1547384, 0.1568550, 0.1589871, 0.1611349, 0.1632985, 0.1654780, 0.1676736,
  0.1698854, 0.1721135, 0.1743582, 0.1766195, 0.1788975, 0.1811926, 0.1835048,
  0.1858343, 0.1881812, 0.1905458, 0.1929282, 0.1953285, 0.1977471, 0.2001840,
  0.2026394, 0.2051136, 0.2076068, 0.2101192, 0.2126509, 0.2152022, 0.2177732,
  0.2203644, 0.2229758, 0.2256077, 0.2282603, 0.2309339, 0.2336288, 0.2363452,
  0.2390833, 0.2418435, 0.2446260, 0.2474311, 0.2502591, 0.2531103, 0.2559850,
  0.2588835, 0.2618062, 0.2647534, 0.2677254, 0.2707226, 0.2737453, 0.2767939,
  0.2798688, 0.2829704, 0.2860991, 0.2892552, 0.2924393, 0.2956517, 0.2988929,
  0.3021634, 0.3054636, 0.3087941, 0.3121552, 0.3155477, 0.3189719, 0.3224285,
  0.3259180, 0.3294410, 0.3329981, 0.3365899, 0.3402171, 0.3438804, 0.3475805,
  0.3513180, 0.3550937, 0.3589085, 0.3627630, 0.3666581, 0.3705947, 0.3745736,
  0.3785958, 0.3826622, 0.3867738, 0.3909317, 0.3951370, 0.3993907, 0.4036940,
  0.4080482, 0.4124545, 0.4169142, 0.4214287, 0.4259996, 0.4306282, 0.4353161,
  0.4400651, 0.4448769, 0.4497533, 0.4546961, 0.4597076, 0.4647897, 0.4699448,
  0.4751752, 0.4804834, 0.4858720, 0.4913439, 0.4969020, 0.5025495, 0.5082898,
  0.5141264, 0.5200632, 0.5261042, 0.5322539, 0.5385169, 0.5448982, 0.5514034,
  0.5580383, 0.5648092, 0.5717230, 0.5787874, 0.5860103, 0.5934009, 0.6009690,
  0.6087254, 0.6166822, 0.6248527, 0.6332520, 0.6418967, 0.6508058, 0.6600009,
  0.6695063, 0.6793506, 0.6895665, 0.7001926, 0.7112747, 0.7228677, 0.7350381,
  0.7478686, 0.7614634, 0.7759569, 0.7915276, 0.8084217, 0.8269933, 0.8477855,
  0.8717043, 0.9004700, 0.9381437, 1.0000000
};

/*  Precomputed table of ratios. These numbers represent
 *  the ratio of box[i+1] that is contained within box[i].
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
  3801129272, 3873074894, 4008685916, 4073393723, 4111806704,
  4137444619, 4155865042, 4169789475, 4180713890, 4189531419,
  4196809522, 4202926709, 4208145537, 4212654084, 4216590757,
  4220059768, 4223141146, 4225897409, 4228378137, 4230623175,
  4232664929, 4234530035, 4236240596, 4237815117, 4239269214,
  4240616155, 4241867296, 4243032411, 4244119962, 4245137315,
  4246090909, 4246986403, 4247828790, 4248622490, 4249371434,
  4250079132, 4250748721, 4251383021, 4251984570, 4252555661,
  4253098369, 4253614578, 4254106001, 4254574202, 4255020607,
  4255446525, 4255853154, 4256241598, 4256612870, 4256967906,
  4257307571, 4257632664, 4257943926, 4258242044, 4258527656,
  4258801356, 4259063697, 4259315194, 4259556328, 4259787549,
  4260009277, 4260221905, 4260425801, 4260621313, 4260808763,
  4260988456, 4261160680, 4261325703, 4261483780, 4261635147,
  4261780032, 4261918645, 4262051187, 4262177846, 4262298801,
  4262414219, 4262524261, 4262629075, 4262728803, 4262823581,
  4262913533, 4262998781, 4263079437, 4263155607, 4263227394,
  4263294892, 4263358191, 4263417377, 4263472529, 4263523724,
  4263571031, 4263614519, 4263654251, 4263690284, 4263722675,
  4263751476, 4263776734, 4263798496, 4263816803, 4263831694,
  4263843205, 4263851369, 4263856217, 4263857776, 4263856070,
  4263851123, 4263842955, 4263831582, 4263817020, 4263799281,
  4263778376, 4263754314, 4263727098, 4263696735, 4263663224,
  4263626565, 4263586755, 4263543789, 4263497659, 4263448357,
  4263395871, 4263340187, 4263281288, 4263219158, 4263153775,
  4263085118, 4263013161, 4262937878, 4262859238, 4262777212,
  4262691763, 4262602857, 4262510454, 4262414512, 4262314988,
  4262211835, 4262105003, 4261994440, 4261880092, 4261761899,
  4261639802, 4261513735, 4261383631, 4261249420, 4261111027,
  4260968374, 4260821379, 4260669957, 4260514019, 4260353469,
  4260188211, 4260018142, 4259843154, 4259663134, 4259477966,
  4259287525, 4259091684, 4258890309, 4258683257, 4258470382,
  4258251531, 4258026541, 4257795244, 4257557463, 4257313014,
  4257061702, 4256803325, 4256537669, 4256264513, 4255983621,
  4255694749, 4255397639, 4255092021, 4254777611, 4254454110,
  4254121205, 4253778565, 4253425843, 4253062674, 4252688672,
  4252303431, 4251906522, 4251497493, 4251075867, 4250641138,
  4250192772, 4249730205, 4249252838, 4248760036, 4248251126,
  4247725393, 4247182078, 4246620373, 4246039418, 4245438297,
  4244816031, 4244171578, 4243503821, 4242811568, 4242093538,
  4241348361, 4240574564, 4239770562, 4238934651, 4238064993,
  4237159603, 4236216335, 4235232865, 4234206673, 4233135020,
  4232014925, 4230843138, 4229616108, 4228329950, 4226980399,
  4225562769, 4224071895, 4222502073, 4220846988, 4219099625,
  4217252176, 4215295923, 4213221097, 4211016720, 4208670407,
  4206168141, 4203493986, 4200629752, 4197554582, 4194244442,
  4190671498, 4186803325, 4182601930, 4178022497, 4173011791,
  4167506076, 4161428406, 4154685009, 4147160434, 4138710915,
  4129155133, 4118261129, 4105727351, 4091154506, 4074002619,
  4053523342, 4028649212, 3997804264, 3958562474, 3906990442,
  3836274811, 3733536696, 3571300751, 3279400049, 2615860924,
  0000000000, 0000000000
};

/*=========================================================================*/
/* Internal Functions                                                      */
/*=========================================================================*/

/*  Function Name: generate_random_exp
 *
 *  Purpose: This function is used internally to generate individual
 *  exponentially-distributed random @b floats. It should not be called by
 *  the user.
 *
 *  Precondition: The user has maintained the state array
 *
 *  Postcondition: A exponentially-distributed random @b float has been
 *  generated
 *
 *  @param state The array which was initialized with the "DSPF_sp_erand_init"
 *  function and maintained (but NEVER modified) by the user between subsequent
 *  calls to the "DSPF_sp_erand" function.
 *
 *  \returns A exponentially distributed random @b float.
 *
 */
#pragma CODE_SECTION(generate_random_exp_cn,".text:ansi")
static float generate_random_exp_cn(_ti_uint32 *state)
{
  /* local variables */
  _ti_uint32 rnd_num;
  _ti_uint32 box_index;
  float x_val;

  for (;;)
  {
    /*Select random box.*/
    rnd_num = generate_random_ti_uint32_cn(state);
    box_index = rnd_num & 0xFF;

    /*Generate uniform random integer with range [0,0xffffffff].*/
    rnd_num = generate_random_ti_uint32_cn(state);

    /* If at base segment of curve (ie. box_index == 0) */
    if (box_index == 0)
    {
      if (rnd_num < ratios_cn[0])
      {
        /* Generated x is within bottom box. */
        return rnd_num * DSPF_sp_erand_UINT32_TO_FLOAT
            * DSPF_sp_erand_AREA_DIV_Y0;
      }
      /* else the value is in the tail of the curve.
       * This path is the least likely to execute, so the calls
       * to log in sample_tail() are insignificant
       */
      return sample_tail_cn(rnd_num);
    }

    /* If at any other segment in the curve */
    if (rnd_num < ratios_cn[box_index])
    {
      /* Generated value is inside a rectangle.
       * This is the most common path
       */
      return rnd_num * DSPF_sp_erand_UINT32_TO_FLOAT * x_cn[box_index];
    }

    /* else, generated value MAY BE outside rectangle. */
    x_val = rnd_num * DSPF_sp_erand_UINT32_TO_FLOAT * x_cn[box_index];
    if (y_cn[box_index - 1]
        + ((y_cn[box_index] - y_cn[box_index - 1])
            * generate_random_float_cn(state))
        < expf(-x_val))
    {
      return x_val;
    }
  }
}

/*  Function Name: sample_tail
 *
 *  Purpose: This function is used internally to sample the tails of the
 *  exponential distribution should the generated random x value fall inside the lowest
 *  horizontal slice of the exponential curve, but outside of the rectangle associated with
 *  that section and instead inside the tail.
 *
 *  Precondition: The user has maintained the state array
 *
 *  Postcondition: A random @b based on the current state of the RNG that is
 *  located within the tail region of the exponential curve has been returned.
 *
 *  @param state The array which was initialized with the "DSPF_sp_erand_init"
 *  function and maintained (but NEVER modified) by the user between subsequent
 *  calls to the "DSPF_sp_erand" function.
 *
 *  \returns A random @b float value located in the tail section of the exponential curve.
 *
 */
#pragma CODE_SECTION(sample_tail_cn,".text:ansi")
static inline float sample_tail_cn(_ti_uint32 rnd_num)
{
  return (DSPF_sp_erand_RIGHT_MOST_X
      - logf((float) rnd_num * DSPF_sp_erand_UINT32_TO_FLOAT));

}

/*=========================================================================*/
/* User Functions                                                          */
/*=========================================================================*/
#pragma CODE_SECTION(DSPF_sp_erand_cn,".text:ansi");
void DSPF_sp_erand_cn(int size, void *vector, void *state)
{
  /* New pointers to take care of void pointers */
  _ti_uint32* v_state = (_ti_uint32*) state;
  float* array = vector;

  int i = 0; /* loop counter */
  while (i < size)
  {
    array[i++] = generate_random_exp_cn((_ti_uint32*) v_state);
  }
}

/* ======================================================================== */
/*  End of file:  DSPF_sp_erand_cn.c                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
