/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file audio_codec.h
 *
 * This file contains audio codec configuration definitions
 *
 */

#ifndef AUDIO_CODEC_H_
#define AUDIO_CODEC_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *                       MACRO DEFINITIONS
 *******************************************************************************/
/**
 *  \brief  Page Select
 **/
#define Aic31_P0_REG0      (uint8_t) (0)

/**
 *  \brief  Software Reset
 **/
#define Aic31_P0_REG1      (uint8_t) (1)

/**
 *  \brief  Codec Sample Rate Select
 **/
#define Aic31_P0_REG2      (uint8_t) (2)

/**
 *  \brief  PLL Programming A
 **/
#define Aic31_P0_REG3      (uint8_t) (3)

/**
 *  \brief  PLL Programming B
 **/
#define Aic31_P0_REG4      (uint8_t) (4)

/**
 *  \brief  PLL Programming C
 **/
#define Aic31_P0_REG5      (uint8_t) (5)

/**
 *  \brief  PLL Programming D
 **/
#define Aic31_P0_REG6      (uint8_t) (6)

/**
 *  \brief  Codec Datapath Setup
 **/
#define Aic31_P0_REG7      (uint8_t) (7)

/**
 *  \brief  Audio Serial Data Interface Control A
 **/
#define Aic31_P0_REG8      (uint8_t) (8)

/**
 *  \brief  Audio Serial Data Interface Control B
 **/
#define Aic31_P0_REG9      (uint8_t) (9)

/**
 *  \brief  Audio Serial Data Interface Control C
 **/
#define Aic31_P0_REG10     (uint8_t) (10)

/**
 *  \brief  Audio Codec Overflow Flag
 **/
#define Aic31_P0_REG11     (uint8_t) (11)

/**
 *  \brief  Audio Codec Digital Filter Control
 **/
#define Aic31_P0_REG12     (uint8_t) (12)

/**
 *  \brief  Headset / Button Press Detection A
 **/
#define Aic31_P0_REG13     (uint8_t) (13)

/**
 *  \brief  Headset / Button Press Detection B
 **/
#define Aic31_P0_REG14     (uint8_t) (14)

/**
 *  \brief  Left ADC PGA Gain Control
 **/
#define Aic31_P0_REG15     (uint8_t) (15)

/**
 *  \brief  Right ADC PGA Gain Control
 **/
#define Aic31_P0_REG16     (uint8_t) (16)

/**
 *  \brief  MIC3L/R to Left ADC Control
 **/
#define Aic31_P0_REG17     (uint8_t) (17)

/**
 *  \brief  MIC3L/R to Right ADC Control
 **/
#define Aic31_P0_REG18     (uint8_t) (18)

/**
 *  \brief  LINE1L to Left ADC Control
 **/
#define Aic31_P0_REG19     (uint8_t) (19)

/**
 *  \brief  LINE2L to Left ADC Control
 **/
#define Aic31_P0_REG20     (uint8_t) (20)

/**
 *  \brief  LINE1R to Left ADC Control
 **/
#define Aic31_P0_REG21     (uint8_t) (21)

/**
 *  \brief  LINE1R to Right ADC Control
 **/
#define Aic31_P0_REG22     (uint8_t) (22)

/**
 *  \brief  LINE2R to Right ADC Control
 **/
#define Aic31_P0_REG23     (uint8_t) (23)

/**
 *  \brief  LINE1L to Right ADC Control
 **/
#define Aic31_P0_REG24     (uint8_t) (24)

/**
 *  \brief  MICBIAS Control
 **/
#define Aic31_P0_REG25     (uint8_t) (25)

/**
 *  \brief  Left AGC Control A
 **/
#define Aic31_P0_REG26     (uint8_t) (26)

/**
 *  \brief  Left AGC Control B
 **/
#define Aic31_P0_REG27     (uint8_t) (27)

/**
 *  \brief  Left AGC Control C
 **/
#define Aic31_P0_REG28     (uint8_t) (28)

/**
 *  \brief  Right AGC Control A
 **/
#define Aic31_P0_REG29     (uint8_t) (29)

/**
 *  \brief  Right AGC Control B
 **/
#define Aic31_P0_REG30     (uint8_t) (30)

/**
 *  \brief  Right AGC Control C
 **/
#define Aic31_P0_REG31     (uint8_t) (31)

/**
 *  \brief  Left AGC Gain
 **/
#define Aic31_P0_REG32     (uint8_t) (32)

/**
 *  \brief  Right AGC Gain
 **/
#define Aic31_P0_REG33     (uint8_t) (33)

/**
 *  \brief  Left AGC Noise Gate Debounce
 **/
#define Aic31_P0_REG34     (uint8_t) (34)

/**
 *  \brief  Right AGC Noise Gate Debounce
 **/
#define Aic31_P0_REG35     (uint8_t) (35)

/**
 *  \brief  ADC Flag
 **/
#define Aic31_P0_REG36     (uint8_t) (36)

/**
 *  \brief  DAC Power and Output Driver control
 **/
#define Aic31_P0_REG37     (uint8_t) (37)

/**
 *  \brief  High Power Output Driver Control
 **/
#define Aic31_P0_REG38     (uint8_t) (38)

/**
 *  \brief  High Power Output Stage Control
 **/
#define Aic31_P0_REG40     (uint8_t) (40)

/**
 *  \brief  DAC Output Switching Control
 **/
#define Aic31_P0_REG41     (uint8_t) (41)

/**
 *  \brief  Output Driver Pop Reduction
 **/
#define Aic31_P0_REG42     (uint8_t) (42)

/**
 *  \brief  Left DAC Digital Volume Control
 **/
#define Aic31_P0_REG43     (uint8_t) (43)

/**
 *  \brief  Right DAC Digital Volume Control
 **/
#define Aic31_P0_REG44     (uint8_t) (44)

/**
 *  \brief  LINE2L to HPLOUT Volume Control
 **/
#define Aic31_P0_REG45     (uint8_t) (45)

/**
 *  \brief  PGA_L to HPLOUT Volume Control
 **/
#define Aic31_P0_REG46     (uint8_t) (46)

/**
 *  \brief  DAC_L1 to HPLOUT Volume Control
 **/
#define Aic31_P0_REG47     (uint8_t) (47)

/**
 *  \brief  LINE2R to HPLOUT Volume Control
 **/
#define Aic31_P0_REG48     (uint8_t) (48)

/**
 *  \brief  PGA_R to HPLOUT Volume Control
 **/
#define Aic31_P0_REG49     (uint8_t) (49)

/**
 *  \brief  DAC_R1 to HPLOUT Volume Control
 **/
#define Aic31_P0_REG50     (uint8_t) (50)

/**
 *  \brief  HPLOUT Output Level Control
 **/
#define Aic31_P0_REG51     (uint8_t) (51)

/**
 *  \brief  LINE2L to HPLCOM Volume Control
 **/
#define Aic31_P0_REG52     (uint8_t) (52)

/**
 *  \brief  PGA_L to HPLCOM Volume Control
 **/
#define Aic31_P0_REG53     (uint8_t) (53)

/**
 *  \brief  DAC_L1 to HPLCOM Volume Control
 **/
#define Aic31_P0_REG54     (uint8_t) (54)

/**
 *  \brief  LINE2R to HPLCOM Volume Control
 **/
#define Aic31_P0_REG55     (uint8_t) (55)

/**
 *  \brief  PGA_R to HPLCOM Volume Control
 **/
#define Aic31_P0_REG56     (uint8_t) (56)

/**
 *  \brief  DAC_R1 to HPLCOM Volume Control
 **/
#define Aic31_P0_REG57     (uint8_t) (57)

/**
 *  \brief  HPLCOM Output Level Control
 **/
#define Aic31_P0_REG58     (uint8_t) (58)

/**
 *  \brief  LINE2L to HPROUT Volume Control
 **/
#define Aic31_P0_REG59     (uint8_t) (59)

/**
 *  \brief  PGA_L to HPROUT Volume Control
 **/
#define Aic31_P0_REG60     (uint8_t) (60)

/**
 *  \brief  DAC_L1 to HPROUT Volume Control
 **/
#define Aic31_P0_REG61     (uint8_t) (61)

/**
 *  \brief  LINE2R to HPROUT Volume Control
 **/
#define Aic31_P0_REG62     (uint8_t) (62)

/**
 *  \brief  PGA_R to HPROUT Volume Control
 **/
#define Aic31_P0_REG63     (uint8_t) (63)

/**
 *  \brief  DAC_R1 to HPROUT Volume Control
 **/
#define Aic31_P0_REG64     (uint8_t) (64)

/**
 *  \brief  HPROUT Output Level Control
 **/
#define Aic31_P0_REG65     (uint8_t) (65)

/**
 *  \brief  LINE2L to HPRCOM Volume
 **/
#define Aic31_P0_REG66     (uint8_t) (66)

/**
 *  \brief  PGA_L to HPRCOM Volume Control
 **/
#define Aic31_P0_REG67     (uint8_t) (67)

/**
 *  \brief  DAC_L1 to HPRCOM Volume Control
 **/
#define Aic31_P0_REG68     (uint8_t) (68)

/**
 *  \brief  LINE2R to HPRCOM Volume Control
 **/
#define Aic31_P0_REG69     (uint8_t) (69)

/**
 *  \brief  PGA_R to HPRCOM Volume Control
 **/
#define Aic31_P0_REG70     (uint8_t) (70)

/**
 *  \brief  DAC_R1 to HPRCOM Volume Control
 **/
#define Aic31_P0_REG71     (uint8_t) (71)

/**
 *  \brief  HPRCOM Output Level Control
 **/
#define Aic31_P0_REG72     (uint8_t) (72)

/**
 *  \brief  LINE2L to MONO_LOP/M Volume Control
 **/
#define Aic31_P0_REG73     (uint8_t) (73)

/**
 *  \brief  PGA_L to MONO_LOP/M Volume Control
 **/
#define Aic31_P0_REG74     (uint8_t) (74)

/**
 *  \brief  DAC_L1 to MONO_LOP/M Volume Control
 **/
#define Aic31_P0_REG75     (uint8_t) (75)

/**
 *  \brief  LINE2R to MONO_LOP/M Volume Control
 **/
#define Aic31_P0_REG76     (uint8_t) (76)

/**
 *  \brief  PGA_R to MONO_LOP/M Volume Control
 **/
#define Aic31_P0_REG77     (uint8_t) (77)

/**
 *  \brief  DAC_R1 to MONO_LOP/M Volume Control
 **/
#define Aic31_P0_REG78     (uint8_t) (78)

/**
 *  \brief  MONO_LOP/M Output Level Control
 **/
#define Aic31_P0_REG79     (uint8_t) (79)

/**
 *  \brief  LINE2L to LEFT_LOP/M Volume Control
 **/
#define Aic31_P0_REG80     (uint8_t) (80)

/**
 *  \brief  PGA_L to LEFT_LOP/M Volume Control
 **/
#define Aic31_P0_REG81     (uint8_t) (81)

/**
 *  \brief  DAC_L1 to LEFT_LOP/M Volume Control
 **/
#define Aic31_P0_REG82     (uint8_t) (82)

/**
 *  \brief  LINE2R to LEFT_LOP/M Volume Control
 **/
#define Aic31_P0_REG83     (uint8_t) (83)

/**
 *  \brief  PGA_R to LEFT_LOP/M Volume Control
 **/
#define Aic31_P0_REG84     (uint8_t) (84)

/**
 *  \brief  DAC_R1 to LEFT_LOP/M Volume Control
 **/
#define Aic31_P0_REG85     (uint8_t) (85)

/**
 *  \brief  LEFT_LOP/M Output Level Control
 **/
#define Aic31_P0_REG86     (uint8_t) (86)

/**
 *  \brief  LINE2L to RIGHT_LOP/M Volume Control
 **/
#define Aic31_P0_REG87     (uint8_t) (87)

/**
 *  \brief  PGA_L to RIGHT_LOP/M Volume Control
 **/
#define Aic31_P0_REG88     (uint8_t) (88)

/**
 *  \brief  DAC_L1 to RIGHT_LOP/M Volume Control
 **/
#define Aic31_P0_REG89     (uint8_t) (89)

/**
 *  \brief  LINE2R to RIGHT_LOP/M Volume Control
 **/
#define Aic31_P0_REG90     (uint8_t) (90)

/**
 *  \brief  PGA_R to RIGHT_LOP/M Volume Control
 **/
#define Aic31_P0_REG91     (uint8_t) (91)

/**
 *  \brief  DAC_R1 to RIGHT_LOP/M Volume Control
 **/
#define Aic31_P0_REG92     (uint8_t) (92)

/**
 *  \brief  RIGHT_LOP/M Output Level Control
 **/
#define Aic31_P0_REG93     (uint8_t) (93)

/**
 *  \brief  Module Power Status
 **/
#define Aic31_P0_REG94     (uint8_t) (94)

/**
 *  \brief  O/P Driver Short CircuitDetection Status
 **/
#define Aic31_P0_REG95     (uint8_t) (95)

/**
 *  \brief  Sticky Interrupt Flags
 **/
#define Aic31_P0_REG96     (uint8_t) (96)

/**
 *  \brief  Real-time Interrupt Flags
 **/
#define Aic31_P0_REG97     (uint8_t) (97)

/**
 *  \brief  GPIO1 Control
 **/
#define Aic31_P0_REG98     (uint8_t) (98)

/**
 *  \brief  GPIO2 Control
 **/
#define Aic31_P0_REG99     (uint8_t) (99)

/**
 *  \brief  Additional GPIO Control A
 **/
#define Aic31_P0_REG100    (uint8_t) (100)

/**
 *  \brief  Additional GPIO Control B
 **/
#define Aic31_P0_REG101    (uint8_t) (101)

/**
 *  \brief  Clock Generation Control
 **/
#define Aic31_P0_REG102    (uint8_t) (102)

/**
 *  \brief  Left AGC New Programmable AttackTime
 **/
#define Aic31_P0_REG103    (uint8_t) (103);

/**
 *  \brief  Left AGC New Programmable DecayTime
 **/
#define Aic31_P0_REG104    (uint8_t) (104);

/**
 *  \brief  Right AGC New Programmable AttackTime
 **/
#define Aic31_P0_REG105    (uint8_t) (105);

/**
 *  \brief  Right AGC New Programmable DecayTime
 **/
#define Aic31_P0_REG106    (uint8_t) (106);

/**
 *  \brief  New Programmable ADC Digital Pathand I2C Bus Condition
 **/
#define Aic31_P0_REG107    (uint8_t) (107);

/**
 *  \brief  Passive Analog Signal BypassSelection During Powerdown
 **/
#define Aic31_P0_REG108    (uint8_t) (108);

/**
 *  \brief  DAC Quiescent Current Adjustment
 **/
#define Aic31_P0_REG109    (uint8_t) (109);

#define Aic31_PAGE_SELECT_ADDR                      (uint8_t) (0x0000)
#define Aic31_RESET_ADDR                            (uint8_t) (0x0001)
#define Aic31_CODEC_SAMPLE_RATE_ADDR                (uint8_t) (0x0002)
#define Aic31_PLLA_PROG_ADDR                        (uint8_t) (0x0003)
#define Aic31_PLLB_PROG_ADDR                        (uint8_t) (0x0004)
#define Aic31_PLLC_PROG_ADDR                        (uint8_t) (0x0005)
#define Aic31_PLLD_PROG_ADDR                        (uint8_t) (0x0006)
#define Aic31_CODEC_DATAPATH_SETUP_ADDR             (uint8_t) (0x0007)
#define Aic31_SERIAL_INTERFACEA_ADDR                (uint8_t) (0x0008)
#define Aic31_SERIAL_INTERFACEB_ADDR                (uint8_t) (0x0009)
#define Aic31_SERIAL_INTERFACEC_ADDR                (uint8_t) (0x000A)
#define Aic31_CODEC_OVERFLOW_FLAG_ADDR              (uint8_t) (0x000B)
#define Aic31_CODEC_DIGIFILTER_CTRL_ADDR            (uint8_t) (0x000C)
#define Aic31_CODEC_HEADSET_DETA_ADDR               (uint8_t) (0x000D)
#define Aic31_CODEC_HEADSET_DETB_ADDR               (uint8_t) (0x000E)
#define Aic31_LEFT_ADCPGA_GAIN_CTRL_ADDR            (uint8_t) (0x000F)
#define Aic31_RIGHT_ADCPGA_GAIN_CTRL_ADDR           (uint8_t) (0x0010)
#define Aic31_MIC3LR_TO_LEFTADC_CTRL_ADDR           (uint8_t) (0x0011)
#define Aic31_MIC3LR_TO_RIGHTADC_CTRL_ADDR          (uint8_t) (0x0012)
#define Aic31_LINE1L_TO_LEFT_ADC_CTRL_ADDR          (uint8_t) (0x0013)
#define Aic31_LINE2L_TO_LEFT_ADC_CTRL_ADDR          (uint8_t) (0x0014)
#define Aic31_LINE1R_TO_LEFT_ADC_CTRL_ADDR          (uint8_t) (0x0015)
#define Aic31_LINE1R_TO_RIGHT_ADC_CTL_ADDR          (uint8_t) (0x0016)
#define Aic31_LINE2R_TO_RIGTH_ADC_CTRL_ADDR         (uint8_t) (0x0017)
#define Aic31_LINE1L_TO_RIGTH_ADC_CTRL_ADDR         (uint8_t) (0x0018)
#define Aic31_MICBIAS_CTRL_ADDR                     (uint8_t) (0x0019)
#define Aic31_LEFT_AGC_CTRLA_ADDR                   (uint8_t) (0x001A)
#define Aic31_LEFT_AGC_CTRLB_ADDR                   (uint8_t) (0x001B)
#define Aic31_LEFT_AGC_CTRLC_ADDR                   (uint8_t) (0x001C)
#define Aic31_RIGHT_AGC_CTRLA_ADDR                  (uint8_t) (0x001D)
#define Aic31_RIGHT_AGC_CTRLB_ADDR                  (uint8_t) (0x001E)
#define Aic31_RIGHT_AGC_CTRLC_ADDR                  (uint8_t) (0x001F)
#define Aic31_LEFT_AGC_GAIN_ADDR                    (uint8_t) (0x0020)
#define Aic31_RIGHT_AGC_GAIN_ADDR                   (uint8_t) (0x0021)
#define Aic31_LEFT_AGC_NOISE_GATE_DEBOUNCE_ADDR     (uint8_t) (0x0022)
#define Aic31_RIGHT_AGC_NOISE_GATE_DEBOUNCE_ADDR    (uint8_t) (0x0023)
#define Aic31_ADC_FLAG_ADDR                         (uint8_t) (0x0024)
#define Aic31_DAC_POWER_OUTPUT_DRIVER_CTRL_ADDR     (uint8_t) (0x0025)
#define Aic31_HP_OUTPUT_DRIVER_CTRL_ADDR            (uint8_t) (0x0026)
#define Aic31_RESERVE                               (uint8_t) (0x0027)
#define Aic31_HP_OUTPUT_STAGE_CTRL_ADDR             (uint8_t) (0x0028)
#define Aic31_DAC_OUTPUT_SWITCH_CTRL_ADDR           (uint8_t) (0x0029)
#define Aic31_OUTPUT_DRV_POP_REDUCTION_ADDR         (uint8_t) (0x002A)
#define Aic31_LEFT_DAC_VOL_CTRL_ADDR                (uint8_t) (0x002B)
#define Aic31_RIGHT_DAC_VOL_CTRL_ADDR               (uint8_t) (0x002C)
#define Aic31_LINE2L_TO_HPLOUT_VOL_CTRL_ADDR        (uint8_t) (0x002D)
#define Aic31_PGA_L_TO_HPLOUT_VOL_CTRL_ADDR         (uint8_t) (0x002E)
#define Aic31_DAC_L1_TO_HPLOUT_VOL_CTRL_ADDR        (uint8_t) (0x002F)
#define Aic31_LINE2R_TO_HPLOUT_VOL_CTRL_ADDR        (uint8_t) (0x0030)
#define Aic31_PGA_R_TO_HPLOUT_VOL_CTRL_ADDR         (uint8_t) (0x0031)
#define Aic31_DAC_R1_TO_HPLOUT_VOL_CTRL_ADDR        (uint8_t) (0x0032)
#define Aic31_HPLOUT_OUTPUT_LEVEL_CTRL_ADDR         (uint8_t) (0x0033)
#define Aic31_LIN2L_TO_HPLCOM_VOL_CTRL_ADDR         (uint8_t) (0x0034)
#define Aic31_PGA_L_TO_HPLCOM_VOL_CTRL_ADDR         (uint8_t) (0x0035)
#define Aic31_DAC_L1_TO_HPLCOM_VOL_CTRL_ADDR        (uint8_t) (0x0036)
#define Aic31_LINE2R_TO_HPLCOM_VOL_CTRL_ADDR        (uint8_t) (0x0037)
#define Aic31_PGA_R_TO_HPLCOM_VOL_CTRL_ADDR         (uint8_t) (0x0038)
#define Aic31_DAC_R1_TO_HPLCOM_VOL_CTRL_ADDR        (uint8_t) (0x0039)
#define Aic31_HPLCOM_OUTPUT_LEVEL_CTRL_ADDR         (uint8_t) (0x003A)
#define Aic31_LINE2L_TO_HPROUT_VOL_CTRL_ADDR        (uint8_t) (0x003B)
#define Aic31_PGA_L_TO_HPROUT_VOL_CTRL_ADDR         (uint8_t) (0x003C)
#define Aic31_DAC_L1_TO_HPROUT_VOL_CTRL_ADDR        (uint8_t) (0x003D)
#define Aic31_LINE2R_TO_HPROUT_VOL_CTRL_ADDR        (uint8_t) (0x003E)
#define Aic31_PGA_R_TO_HPROUT_VOL_CTRL_ADDR         (uint8_t) (0x003F)
#define Aic31_DAC_R1_TO_HPROUT_VOL_CTRL_ADDR        (uint8_t) (0x0040)
#define Aic31_HPROUT_OUTPUT_LEVEL_CTRL_ADDR         (uint8_t) (0x0041)
#define Aic31_LIN2L_TO_HPRCOM_VOL_CTRL_ADDR         (uint8_t) (0x0042)
#define Aic31_PGA_L_TO_HPRCOM_VOL_CTRL_ADDR         (uint8_t) (0x0043)
#define Aic31_DAC_L1_TO_HPRCOM_VOL_CTRL_ADDR        (uint8_t) (0x0044)
#define Aic31_LINE2R_TO_HPRCOM_VOL_CTRL_ADDR        (uint8_t) (0x0045)
#define Aic31_PGA_R_TO_HPRCOM_VOL_CTRL_ADDR         (uint8_t) (0x0046)
#define Aic31_DAC_R1_TO_HPRCOM_VOL_CTRL_ADDR        (uint8_t) (0x0047)
#define Aic31_HPRCOM_OUTPUT_LEVEL_CTRL_ADDR         (uint8_t) (0x0048)
#define Aic31_LIN2L_TO_MONO_LOPM_VOL_CTRL_ADDR      (uint8_t) (0x0049)
#define Aic31_PGA_L_TO_MONO_LOPM_VOL_CTRL_ADDR      (uint8_t) (0x004A)
#define Aic31_DAC_L1_TO_MONO_LOPM_VOL_CTRL_ADDR     (uint8_t) (0x004B)
#define Aic31_LINE2R_TO_MONO_LOPM_VOL_CTRL_ADDR     (uint8_t) (0x004C)
#define Aic31_PGA_R_TO_MONO_LOPM_VOL_CTRL_ADDR      (uint8_t) (0x004D)
#define Aic31_DAC_R1_TO_MONO_LOPM_VOL_CTRL_ADDR     (uint8_t) (0x004E)
#define Aic31_MONO_LOPM_OUTPUT_LEVEL_CTRL_ADDR      (uint8_t) (0x004F)
#define Aic31_LIN2L_TO_LEFT_LOPM_VOL_CTRL_ADDR      (uint8_t) (0x0050)
#define Aic31_PGA_L_TO_LEFT_LOPM_VOL_CTRL_ADDR      (uint8_t) (0x0051)
#define Aic31_DAC_L1_TO_LEFT_LOPM_VOL_CTRL_ADDR     (uint8_t) (0x0052)
#define Aic31_LINE2R_TO_LEFT_LOPM_VOL_CTRL_ADDR     (uint8_t) (0x0053)
#define Aic31_PGA_R_TO_LEFT_LOPM_VOL_CTRL_ADDR      (uint8_t) (0x0054)
#define Aic31_DAC_R1_TO_LEFT_LOPM_VOL_CTRL_ADDR     (uint8_t) (0x0055)
#define Aic31_LEFT_LOPM_OUTPUT_LEVEL_CTRL_ADDR      (uint8_t) (0x0056)
#define Aic31_LIN2L_TO_RIGHT_LOPM_VOL_CTRL_ADDR     (uint8_t) (0x0057)
#define Aic31_PGA_L_TO_RIGHT_LOPM_VOL_CTRL_ADDR     (uint8_t) (0x0058)
#define Aic31_DAC_L1_TO_RIGHT_LOPM_VOL_CTRL_ADDR    (uint8_t) (0x0059)
#define Aic31_LINE2R_TO_RIGHT_LOPM_VOL_CTRL_ADDR    (uint8_t) (0x005A)
#define Aic31_PGA_R_TO_RIGHT_LOPM_VOL_CTRL_ADDR     (uint8_t) (0x005B)
#define Aic31_DAC_R1_TO_RIGHT_LOPM_VOL_CTRL_ADDR    (uint8_t) (0x005C)
#define Aic31_RIGHT_LOPM_OUTPUT_LEVEL_CTRL_ADDR     (uint8_t) (0x005D)
#define Aic31_MODULE_POWER_STAT_ADDR                (uint8_t) (0x005E)
#define Aic31_OUTPUT_DRV_SHORTCKT_DET_STAT_ADDR     (uint8_t) (0x005F)
#define Aic31_STICKY_INTR_FLAGS_ADDR                (uint8_t) (0x0060)
#define Aic31_REALTIME_INTR_FLAGS_ADDR              (uint8_t) (0x0061)
#define Aic31_GPIO1_CTRL_ADDR                       (uint8_t) (0x0062)
#define Aic31_GPIO2_CTRL_ADDR                       (uint8_t) (0x0063)
#define Aic31_ADDITIONAL_GPIOCTRLA_ADDR             (uint8_t) (0x0064)
#define Aic31_ADDITIONAL_GPIOCTRLB_ADDR             (uint8_t) (0x0065)
#define Aic31_CLKGEN_CTRL_ADDR                      (uint8_t) (0x0066)

/**
 *  \brief  Select Aic31 page 0 registers
 **/
#define Aic31_PAGE_0              (uint8_t) (0x00)
#define Aic31_PAGE_1              (uint8_t) (0x01)

/**
 *  \brief  Max value of gain to be programmed to the DAC
 **/
#define Aic31_MAX_DAC_GAIN_VALUE  (uint8_t) (0x7F)

/**
 *  \brief  Max value of gain to be programmed to the AGC
 **/
#define Aic31_MAX_AGC_GAIN_VALUE  (uint8_t) (0x77)

/**
 *  \brief   Max value of gain to be programmed to the PGA
 **/
#define Aic31_MAX_PGA_GAIN_VALUE  (uint8_t) (0x77)

/**
 *  \brief  MAX percent of the gain allowed
 **/
#define Aic31_MAX_GAIN_PERCENT    (uint8_t) (100U)

#ifdef __cplusplus
}
#endif

#endif
