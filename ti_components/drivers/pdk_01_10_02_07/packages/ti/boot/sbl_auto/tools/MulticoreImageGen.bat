REM @echo off
REM Define Device Id Vayu - 55
REM Device ID & CPU ID should be in sync with SBL. Refer SBL user guide for values
set Dev_ID=55
set MPU_CPU0_ID=0
set MPU_CPU1_ID=1
set	IPU1_CPU0_ID=2
set IPU1_CPU1_ID=3
set	IPU2_CPU0_ID=4
set	IPU2_CPU1_ID=5
set DSP1_ID=6
set	DSP2_ID=7
set	EVE1_ID=8
set	EVE2_ID=9
set	EVE3_ID=10
set	EVE4_ID=11

REM Define Output file path
set Out_Path=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_app\

IF NOT EXIST %Out_Path%\ mkdir %Out_Path%


REM Define Input file paths; To skip the core leave it blank
set App_MPU_CPU0=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_mbx\bin\tda2xx-evm\sbl_multicore_mbx_a15_0_release.xa15fg
set App_MPU_CPU1=
set App_IPU1_CPU0=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_mbx\bin\tda2xx-evm\sbl_multicore_mbx_ipu1_0_release.xem4
set App_IPU1_CPU1=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_mbx\bin\tda2xx-evm\sbl_multicore_mbx_ipu1_1_release.xem4
set App_IPU2_CPU0=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_mbx\bin\tda2xx-evm\sbl_multicore_mbx_ipu2_0_release.xem4
set App_IPU2_CPU1=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_mbx\bin\tda2xx-evm\sbl_multicore_mbx_ipu2_1_release.xem4
set App_DSP1=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_mbx\bin\tda2xx-evm\sbl_multicore_mbx_c66xdsp_1_release.xe66
set App_DSP2=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_mbx\bin\tda2xx-evm\sbl_multicore_mbx_c66xdsp_2_release.xe66
set App_EVE1=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_mbx\bin\tda2xx-evm\sbl_multicore_mbx_arp32_1_release.xearp32F
set App_EVE2=
set App_EVE3=
set App_EVE4=

if defined App_MPU_CPU0 (
set MPU_CPU0=%MPU_CPU0_ID%
set image_gen=1
set App_MPU_CPU0_RPRC=%App_MPU_CPU0%.rprc )
if defined App_MPU_CPU0 (
"out2rprc\out2rprc.exe" %App_MPU_CPU0% %App_MPU_CPU0_RPRC% )

if defined App_MPU_CPU1 (
set MPU_CPU1=%MPU_CPU1_ID%
set image_gen=1
set App_MPU_CPU1_RPRC=%App_MPU_CPU1%.rprc )
if defined App_MPU_CPU1 (
"out2rprc\out2rprc.exe" %App_MPU_CPU1% %App_MPU_CPU1_RPRC% )

if defined App_IPU1_CPU0 (
set IPU1_CPU0=%IPU1_CPU0_ID%
set image_gen=1
set App_IPU1_CPU0_RPRC=%App_IPU1_CPU0%.rprc )
if defined App_IPU1_CPU0 (
"out2rprc\out2rprc.exe" %App_IPU1_CPU0% %App_IPU1_CPU0_RPRC% )

if defined App_IPU1_CPU1 (
set IPU1_CPU1=%IPU1_CPU1_ID%
set image_gen=1
set App_IPU1_CPU1_RPRC=%App_IPU1_CPU1%.rprc )
if defined App_IPU1_CPU1 (
"out2rprc\out2rprc.exe" %App_IPU1_CPU1% %App_IPU1_CPU1_RPRC% )

if defined App_IPU2_CPU0 (
set IPU2_CPU0=%IPU2_CPU0_ID%
set image_gen=1
set App_IPU2_CPU0_RPRC=%App_IPU2_CPU0%.rprc )
if defined App_IPU2_CPU0 (
"out2rprc\out2rprc.exe" %App_IPU2_CPU0% %App_IPU2_CPU0_RPRC% )

if defined App_IPU2_CPU1 (
set IPU2_CPU1=%IPU2_CPU1_ID%
set image_gen=1
set App_IPU2_CPU1_RPRC=%App_IPU2_CPU1%.rprc )
if defined App_IPU2_CPU1 (
"out2rprc\out2rprc.exe" %App_IPU2_CPU1% %App_IPU2_CPU1_RPRC% )

if defined App_DSP1 (
set DSP1_CPU=%DSP1_ID%
set image_gen=1
set App_DSP1_RPRC=%App_DSP1%.rprc )
if defined App_DSP1 (
"out2rprc\out2rprc.exe" %App_DSP1% %App_DSP1_RPRC% )

if defined App_DSP2 (
set DSP2_CPU=%DSP2_ID%
set image_gen=1
set App_DSP2_RPRC=%App_DSP2%.rprc )
if defined App_DSP2 (
"out2rprc\out2rprc.exe" %App_DSP2% %App_DSP2_RPRC% )

if defined App_EVE1 (
set EVE1_CPU=%EVE1_ID%
set image_gen=1
set App_EVE1_RPRC=%App_EVE1%.rprc )
if defined App_EVE1 (
"out2rprc\out2rprc.exe" %App_EVE1% %App_EVE1_RPRC% )

if defined App_EVE2 (
set EVE2_CPU=%EVE2_ID%
set image_gen=1
set App_EVE2_RPRC=%App_EVE2%.rprc )
if defined App_EVE2 (
"out2rprc\out2rprc.exe" %App_EVE2% %App_EVE2_RPRC% )

if defined App_EVE3 (
set EVE3_CPU=%EVE3_ID%
set image_gen=1
set App_EVE3_RPRC=%App_EVE3%.rprc )
if defined App_EVE3 (
"out2rprc\out2rprc.exe" %App_EVE3% %App_EVE3_RPRC% )

if defined App_EVE4 (
set EVE4_CPU=%EVE4_ID%
set image_gen=1
set App_EVE4_RPRC=%App_EVE4%.rprc )
if defined App_EVE4 (
"out2rprc\out2rprc.exe" %App_EVE4% %App_EVE4_RPRC% )

REM ImageGen
if defined image_gen (

REM Gerating MulticoreImage Gen
"multicore_image_generator\v1\MulticoreImageGen.exe" LE %Dev_ID% %Out_Path%\AppImage_LE %MPU_CPU0% %App_MPU_CPU0_RPRC%  %MPU_CPU1% %App_MPU_CPU1_RPRC% %IPU1_CPU0% %App_IPU1_CPU0_RPRC% %IPU1_CPU1% %App_IPU1_CPU1_RPRC% %IPU2_CPU0% %App_IPU2_CPU0_RPRC% %IPU2_CPU1% %App_IPU2_CPU1_RPRC%  %DSP1_CPU% %App_DSP1_RPRC% %DSP2_CPU% %App_DSP2_RPRC% %EVE1_CPU% %App_EVE1_RPRC% %EVE2_CPU% %App_EVE2_RPRC% %EVE3_CPU% %App_EVE3_RPRC% %EVE4_CPU% %App_EVE4_RPRC%

"multicore_image_generator\v1\MulticoreImageGen.exe" BE %Dev_ID% %Out_Path%\AppImage_BE %MPU_CPU0% %App_MPU_CPU0_RPRC%  %MPU_CPU1% %App_MPU_CPU1_RPRC% %IPU1_CPU0% %App_IPU1_CPU0_RPRC% %IPU1_CPU1% %App_IPU1_CPU1_RPRC% %IPU2_CPU0% %App_IPU2_CPU0_RPRC% %IPU2_CPU1% %App_IPU2_CPU1_RPRC%  %DSP1_CPU% %App_DSP1_RPRC% %DSP2_CPU% %App_DSP2_RPRC% %EVE1_CPU% %App_EVE1_RPRC% %EVE2_CPU% %App_EVE2_RPRC% %EVE3_CPU% %App_EVE3_RPRC% %EVE4_CPU% %App_EVE4_RPRC%
)
pause