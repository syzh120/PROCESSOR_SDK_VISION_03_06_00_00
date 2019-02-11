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
#include "../common/VLIB_memory.h"
#include "VLIB_matchTemplate_idat.h"

static uint8_t    origImg[48 * 56]     =
{
    0X80, 0X80, 0X80, 0X80, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X80, 0X80, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XA0, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0XA0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XA0, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0XA0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0XA0, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0XA0, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0XA0, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0XA0, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0XA0, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0XA0, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0XA0, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0XA0, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X80, 0X80, 0X80, 0X80, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X80, 0X80, 0X80, 0X80, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XA0, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0XA0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0XA0, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0XA0, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X20, 0X20, 0X20, 0X20, 0X20, 0X20, 0XA0, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0XA0, 0X20, 0X20, 0X20, 0X20, 0X20, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0XA0, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0XA0, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0XA0, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0XA0, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0XA0, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0XA0, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0XB0, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0XB0, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0XC0, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0XC0, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0XD0, 0XE0, 0XF0, 0XE0, 0XD0, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0XE0, 0XF0, 0XE0, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X10, 0X10, 0XF0, 0X10, 0X10, 0X10, 0X10, 0X10, 0X30, 0X30, 0XFF, 0X10, 0X10, 0X10, 0X10, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
};

static uint8_t    pattern1[24 * 24] =
{
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10, 0x10, 0xE0, 0xF0, 0xE0, 0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10, 0x10, 0xE0, 0xF0, 0xE0, 0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0x10, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0x10, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0xC0, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0xC0, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xC0, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0xC0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0xC0, 0xB0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0xC0, 0xB0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0xC0, 0xB0, 0xA0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0xC0, 0xB0, 0xA0, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0xC0, 0xB0, 0xA0, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0xC0, 0xB0, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0xC0, 0xB0, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0xC0, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0xC0, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0xC0, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0xC0, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0x10, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10, 0xD0, 0xE0, 0xF0, 0xE0, 0xD0, 0x10, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10, 0x10, 0xE0, 0xF0, 0xE0, 0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10, 0x10, 0xE0, 0xF0, 0xE0, 0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0xFF, 0x10, 0x10, 0x10, 0x10,
};

static matchTemplate_testParams_t    testParams[]=
{
    /********************************************
    {
      uint8_t                       testPattern;
      uint8_t                       *orgImg;
      int32_t                       orgImgWidth;
      int32_t                       orgImgHeight;
      int32_t                       orgImgPitch;
      uint8_t                       *tempImg;
      int32_t                       tempImgWidth;
      int32_t                       tempImgHeight;
      int32_t                       tempImgPitch;
      uint8_t                       xDirJump;
      uint8_t                       yDirJump;
      int32_t                       outScorePitch;
      int32_t                       method;
      uint32_t                      *outScore;
      char                          *desc;
    },
    *********************************************/
    {
        RANDOM,
        NULL,
        120,
        120,
        120,
        NULL,
        66,
        32,
        66,
        1,
        1,
        120,
        0,
        NULL,
        "Test Case with template size of 66x32, Square Template"
    },
    {
        STATIC,
        origImg,
        48,
        48,
        56,
        pattern1,
        24,
        24,
        24,
        1,
        1,
        25,
        0,
        NULL,
        "Test Case with template size of 24x24"
    },
    {
        STATIC,
        origImg,
        48,
        48,
        56,
        pattern1,
        32,
        32,
        32,
        1,
        1,
        25,
        0,
        NULL,
        "Test Case with template size of 32x32"
    },
    {
        STATIC,
        origImg,
        48,
        48,
        56,
        pattern1,
        30,
        30,
        30,
        1,
        1,
        25,
        0,
        NULL,
        "Test Case with template size of 30x30"
    },
    {
        STATIC,
        origImg,
        48,
        48,
        57,
        pattern1,
        24,
        24,
        24,
        3,
        3,
        57,
        0,
        NULL,
        "Test Case with template size of 24x24 with jump of '3' in both direction"
    },
    {
        RANDOM,
        NULL,
        128,
        128,
        128,
        NULL,
        24,
        24,
        32,
        1,
        1,
        128,
        0,
        NULL,
        "Test Case with template size of 24x24"
    },
    {
        RANDOM,
        NULL,
        120,
        120,
        120,
        NULL,
        24,
        24,
        32,
        1,
        1,
        120,
        0,
        NULL,
        "Test Case with template size of 24x24"
    },
    {
        RANDOM,
        origImg,
        48,
        48,
        56,
        pattern1,
        40,
        40,
        40,
        1,
        1,
        25,
        0,
        NULL,
        "Test Case with template size of 40x40"
    },
    {
        CONSTANT,
        origImg,
        48,
        48,
        56,
        pattern1,
        24,
        24,
        24,
        1,
        1,
        25,
        0,
        NULL,
        "Constant Test Case with template size of 24x24"
    },
    {
        STATIC,
        origImg,
        40,
        40,
        56,
        pattern1,
        24,
        24,
        24,
        1,
        1,
        25,
        0,
        NULL,
        "Test Case with template size of 24x24"
    },
    {
        STATIC,
        origImg,
        32,
        32,
        56,
        pattern1,
        24,
        24,
        24,
        1,
        1,
        25,
        0,
        NULL,
        "Test Case with template size of 24x24"
    },
    {
        STATIC,
        origImg,
        48,
        48,
        56,
        pattern1,
        24,
        24,
        24,
        1,
        1,
        56,
        0,
        NULL,
        "Test Case with template size of 24x24"
    },
    {
        STATIC,
        origImg,
        48,
        48,
        56,
        pattern1,
        24,
        24,
        24,
        1,
        1,
        56,
        0,
        NULL,
        "Test Case with template size of 24x24"
    },
    {
        STATIC,
        origImg,
        48,
        48,
        56,
        pattern1,
        24,
        24,
        24,
        4,
        4,
        56,
        0,
        NULL,
        "Test Case with template size of 24x24"
    },
    {
        CONSTANT,
        NULL,
        48,
        48,
        56,
        NULL,
        24,
        20,
        24,
        1,
        1,
        56,
        0,
        NULL,
        "Test Case with template size of 24x20, Non Square Template"
    },
    {
        CONSTANT,
        NULL,
        48,
        48,
        56,
        NULL,
        20,
        24,
        24,
        1,
        1,
        56,
        0,
        NULL,
        "Test Case with template size of 20x24, Non Square Template"
    },
    {
        CONSTANT,
        NULL,
        128,
        128,
        128,
        NULL,
        44,
        44,
        46,
        1,
        1,
        128,
        0,
        NULL,
        "Test Case with template size of 44x44"
    },
    {
        RANDOM,
        NULL,
        128,
        128,
        128,
        NULL,
        48,
        48,
        48,
        1,
        1,
        160,
        0,
        NULL,
        "Test Case with template size of 48x48, Square Template"
    },
    {
        CONSTANT,
        NULL,
        128,
        128,
        128,
        NULL,
        32,
        64,
        64,
        1,
        1,
        128,
        0,
        NULL,
        "Test Case with template size of 32x64, Non Square Template"
    },
    {
        CONSTANT,
        NULL,
        120,
        120,
        120,
        NULL,
        64,
        32,
        64,
        1,
        1,
        120,
        0,
        NULL,
        "Test Case with template size of 64x32, Non Square Template"
    },

};
/*
 *  Sends the test parameter structure and number of tests
 */
void matchTemplate_getTestParams(matchTemplate_testParams_t * *params,  int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(matchTemplate_testParams_t);
}

/* ======================================================================== */
/*  End of file:  VLIB_matchTemplate_idat.c                       */
/* ======================================================================== */

