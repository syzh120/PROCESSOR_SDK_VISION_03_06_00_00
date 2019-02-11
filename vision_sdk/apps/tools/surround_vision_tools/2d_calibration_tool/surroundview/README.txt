================
SurroundView.exe
================
Runs surround view on 4 fisheye images

See run_example.bat file for example call of SurroundView.exe

-----------------------------------------------------------------------
IMPORTANT:
** make sure you set your actual working path -p

** If distortion csv file was created with fisheye_tool:
- pass the correct csv file name (-d), which must be in the same folder as input fisheye images

** If perspective matrix csv file was created with calibration_tool, 
- pass the correct perspective matrix csv file name (-m), which must be in the same folder as input fisheye images
- pass the same distortion_center csv file name (-d), as used in calibration_tool
- pass the output vertical dimension/height (-V), horizontal dimension/height (-H) and pitch (-J) as used in calibration_tool
- pass the same focal length (-F), carbox horizontal width (-X), carbox vertical height (-Y) as used in calibration_tool

-----------------------------------------------------------------------
Mandatory input arguments:
  -n  number of cameras
  -p  working directory (needs to appear before -i, -o, -d, -m) where all files (images, calibration, output) are located
  -i  input fisheye images filenames
  -o  output surroundview image filename
  -v  input vertical dimension
  -h  input horizontal dimension
  -j  input image pitch
  -V  output vertical dimension
  -H  output horizontal dimension
  -J  output image pitch
Optional arguments include
  -c  number of color channels 
  -d  fisheye distortion csv file path (Default: center of fisheye images)
  -m  perspective matrix csv file path (Default: matrix specific to TI lab's setup)
  -F  focal length of fisheye cameras in pixels (Default: 455)
  -X  carbox width in pixels (Default: 240)
  -Y  carbox height in pixels (Default: 360)




