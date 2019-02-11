@echo off
:: Import tool exe name/path
set TIDL_DIR=..\..\test\out
set TIDL_EXE=eve_test_dl_algo.out.exe

set WORKING_DIR=%~dp0

:: List of test cases to import
:: testvecs\config\caffe_jacinto_models
set TEST_CASES_LIST=j11_v2, j11_bn, j11_cifar, jseg21,

:: testvecs\config\caffe_models\imagenet_jacintonet_prelu_11v2
set TEST_CASES_LIST=%TEST_CASES_LIST% j11_prelu, jseg21_tiscapes, j11_controlLayers,

:: testvecs\config\caffe_models\SqueezeNet-master
set TEST_CASES_LIST=%TEST_CASES_LIST% squeeze1_1,

:: testvecs\config\caffe_models\dense_examplesr
set TEST_CASES_LIST=%TEST_CASES_LIST% dense_1x1, smallRoi, smallRoi_2,

:: testvecs\config\tensorflow_models
set TEST_CASES_LIST=%TEST_CASES_LIST% inceptionNetv1, mobileNet1,

:: Object Detect Models
set TEST_CASES_LIST=%TEST_CASES_LIST% JDetNet, JDetNet_512x256,

::set TEST_CASES_LIST=j11_v2

echo %TEST_CASES_LIST%

:: Importing testces in the list
FOR %%T in (%TEST_CASES_LIST%) do (call :tidlInferModel %%T)
goto:eof


:: Method to import a caffe/tensor flow model for TIDL execution
:tidlInferModel
cd %TIDL_DIR%
echo Runnign Inference for  test case %~1
echo 1 tidl_config.txt > config_list.txt
echo 0 >> config_list.txt
copy ..\..\test\testvecs\config\infer\tidl_config_%~1.txt tidl_config.txt
%TIDL_EXE% config_list.txt  > tidl_log.txt
mkdir trace_%~1
move *.bin trace_%~1\
move *.y trace_%~1\
move  tidl_log.txt trace_%~1\
move trace_%~1 %WORKING_DIR%\
cd %WORKING_DIR%\
goto:eof
