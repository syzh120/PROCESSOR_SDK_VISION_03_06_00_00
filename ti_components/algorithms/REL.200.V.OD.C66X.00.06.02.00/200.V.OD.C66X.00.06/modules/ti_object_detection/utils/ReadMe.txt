AdaboostTableGen.exe utility can be used to convert AdaBoost weights from descriptor file format to binary file format which is recognized by Object Detection application.
The descriptor file is generated using open source training framework available here,

 https://github.com/tidsp/acf-jacinto 

The converted binary file is supplied to the application via test\testvecs\object_detection.cfg
Refer User Guide for more details.

The executable was built using Microsoft Visual Studio 2015. 
To run the executable a Microsoft Visual Studio 2015 Redistributable package should be installed from here, 

 https://www.microsoft.com/en-in/download/details.aspx?id=48145



