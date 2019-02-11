@echo off

mkdir c_files
call :convert2c 000
call :convert2c 001
call :convert2c 002
call :convert2c 003
call :convert2c 004
call :convert2c 005
call :convert2c 006
call :convert2c 007
call :convert2c 008
call :convert2c 009
call :convert2c 010
call :convert2c 011
call :convert2c 012
call :convert2c 013
call :convert2c 014
call :convert2c 015
call :convert2c 016
call :convert2c 017
call :convert2c 018
call :convert2c 019
call :convert2c 020
call :convert2c 021
call :convert2c 022
call :convert2c 023
call :convert2c 024
call :convert2c 025
call :convert2c 026
call :convert2c 027
call :convert2c 028
call :convert2c 029
call :convert2c 030
call :convert2c 031
 
echo DONE !!!

goto:eof


:convert2c
echo Converting %~1 !!!
convert %~1.png c_files\%~1.rgb
image_convert -i c_files\%~1.rgb rgb888i 32 32 32 -o c_files\%~1.yuv420sp yyuv420 32
bin2c c_files\%~1.yuv420sp > c_files\%~1_1.h 2> log.txt
del c_files\%~1.yuv420sp
del c_files\%~1.rgb
del log.txt
GOTO:EOF