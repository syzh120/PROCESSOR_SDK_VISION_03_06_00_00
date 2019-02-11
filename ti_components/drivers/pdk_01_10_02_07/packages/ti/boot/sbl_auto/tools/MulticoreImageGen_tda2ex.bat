REM @echo off
REM Define Device Id J6 ECO - 66 - choosen random value will be updated
REM Device ID & CPU ID should be in sync with SBL. Refer SBL user guide for values
set Dev_ID=66
set MPU_CPU0_ID=0
set IPU1_CPU0_ID=2
set IPU1_CPU1_ID=3
set IPU1_CPU_SMP_ID=4
set IPU2_CPU0_ID=5
set IPU2_CPU1_ID=6
set IPU2_CPU_SMP_ID=7
set DSP1_ID=8

REM Define Output file path
set Out_Path=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_app\

IF NOT EXIST %Out_Path%\ mkdir %Out_Path%

REM Define Input file paths; To skip the core leave it blank
set App_MPU_CPU0=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_mbx\bin\tda2ex-evm\sbl_multicore_mbx_a15_0_release.xa15fg
set App_IPU1_CPU0=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_mbx\bin\tda2ex-evm\sbl_multicore_mbx_ipu1_0_release.xem4
set App_IPU1_CPU1=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_mbx\bin\tda2ex-evm\sbl_multicore_mbx_ipu1_1_release.xem4
REM App_IPU1_CPU_SMP is to define the IPU SMP application
set App_IPU1_CPU_SMP=
set App_IPU2_CPU0=
set App_IPU2_CPU1=
REM App_IPU2_CPU_SMP is to define the IPU SMP application
set App_IPU2_CPU_SMP=
set App_DSP1=C:\pdk_xx_yy_zz_aa\packages\ti\binary\sbl_multicore_mbx\bin\tda2ex-evm\sbl_multicore_mbx_c66xdsp_1_release.xe66

if defined App_MPU_CPU0 (
set MPU_CPU0=%MPU_CPU0_ID%
set image_gen=1
set App_MPU_CPU0_RPRC=%App_MPU_CPU0%.rprc )
if defined App_MPU_CPU0 (
"out2rprc\out2rprc.exe" %App_MPU_CPU0% %App_MPU_CPU0_RPRC% )

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

if defined App_IPU1_CPU_SMP (
set IPU1_CPU_SMP=%IPU1_CPU_SMP_ID%
set image_gen=1
set App_IPU1_CPU_SMP_RPRC=%App_IPU1_CPU_SMP%.rprc )
if defined App_IPU1_CPU_SMP (
"out2rprc\out2rprc.exe" %App_IPU1_CPU_SMP% %App_IPU1_CPU_SMP_RPRC% )

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

if defined App_IPU2_CPU_SMP (
set IPU2_CPU_SMP=%IPU2_CPU_SMP_ID%
set image_gen=1
set App_IPU2_CPU_SMP_RPRC=%App_IPU2_CPU_SMP%.rprc )
if defined App_IPU2_CPU_SMP (
"out2rprc\out2rprc.exe" %App_IPU2_CPU_SMP% %App_IPU2_CPU_SMP_RPRC% )

if defined App_DSP1 (
set DSP1_CPU=%DSP1_ID%
set image_gen=1
set App_DSP1_RPRC=%App_DSP1%.rprc )
if defined App_DSP1 (
"out2rprc\out2rprc.exe" %App_DSP1% %App_DSP1_RPRC% )

REM ImageGen
if defined image_gen (

REM Gerating MulticoreImage Gen
"multicore_image_generator\v1\MulticoreImageGen.exe" LE %Dev_ID% %Out_Path%\AppImage_LE %MPU_CPU0% %App_MPU_CPU0_RPRC% %IPU1_CPU0% %App_IPU1_CPU0_RPRC% %IPU1_CPU1% %App_IPU1_CPU1_RPRC% %IPU1_CPU_SMP% %App_IPU1_CPU_SMP_RPRC% %IPU2_CPU0% %App_IPU2_CPU0_RPRC% %IPU2_CPU1% %App_IPU2_CPU1_RPRC% %IPU2_CPU_SMP% %App_IPU2_CPU_SMP_RPRC% %DSP1_CPU% %App_DSP1_RPRC%

"multicore_image_generator\v1\MulticoreImageGen.exe" BE %Dev_ID% %Out_Path%\AppImage_BE %MPU_CPU0% %App_MPU_CPU0_RPRC% %IPU1_CPU0% %App_IPU1_CPU0_RPRC% %IPU1_CPU1% %App_IPU1_CPU1_RPRC% %IPU1_CPU_SMP% %App_IPU1_CPU_SMP_RPRC% %IPU2_CPU0% %App_IPU2_CPU0_RPRC% %IPU2_CPU1% %App_IPU2_CPU1_RPRC% %IPU2_CPU_SMP% %App_IPU2_CPU_SMP_RPRC% %DSP1_CPU% %App_DSP1_RPRC%
)
pause