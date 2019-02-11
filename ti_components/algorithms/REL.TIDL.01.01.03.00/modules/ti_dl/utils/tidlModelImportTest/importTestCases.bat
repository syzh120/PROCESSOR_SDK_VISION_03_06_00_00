@echo off
:: Import tool exe name/path
set IMPORT_EXE=..\importTool\tidl_model_import.out.exe

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

:: Object Detect models
set TEST_CASES_LIST=%TEST_CASES_LIST% JDetNet, JDetNet_512x256

::set TEST_CASES_LIST=profile_conv2d_3x3_pool, profile_conv2d_3x3_relu, profile_conv2d_5x5_relu, profile_max_pool_3x3, profile_max_pool_2x2, profile_avg_pool_3x3,

echo %TEST_CASES_LIST%

:: Importing testces in the list
FOR %%T in (%TEST_CASES_LIST%) do (call :tidlImportModel %%T)
goto:eof


:: Method to import a caffe/tensor flow model for TIDL execution
:tidlImportModel
echo importing test case %~1
%IMPORT_EXE% ..\..\test\testvecs\config\import\\tidl_import_%~1.txt > tidl_log.txt
if not exist tempDir mkdir tempDir
rename tempDir trace_%~1
move tidl_log.txt trace_%~1
goto:eof
