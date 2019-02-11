1. Usage
----------
1) Copy the content of the directory vsion_sdk/tools/camera_calibration_tools/bin into the
directory where you image files are located.

2) Edit the file calib.xml.
Edit the fields InputLeft and InputRight with the file patterns corresponding to your
left and right image sequences.
The field values FocalX_Hint, FocalY_Hint, CenterX_Hint, CenterY_Hint in calib.xml are initialized
for the lens M13B0618IRR4 from Xiamen Leading Optics Co., Ltd shipped with the MultiSensor Fusion camera.
If calibration is desired for another lens, please set these fields to different values or set
the field Use_Hints to 0. 

3) Open a command window in this directory and type:
camAutoCalib.exe calib.xml

Refer to the VisionSDK_MultiSensorFusionStereoCalibrationGuide.pdf for more details.

2. Rebuilding and customizing camAutoCalib.exe
-----------------------------------------------
The directory src/ contains the source file camera_calibration.cpp and the directory build/
contains the Visual Studio 2013 solution file camAutoCalib.sln to rebuild the executable camAutoCalib.exe