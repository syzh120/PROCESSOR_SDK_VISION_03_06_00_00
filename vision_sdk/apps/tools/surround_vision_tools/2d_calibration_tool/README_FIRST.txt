SurroundView Demonstration Package
===================================

HOWTO:
------
3 steps to run SurroundView demonstration PC (Windows) code:

1) fisheye_tool: (estimate distortion centers for fisheye images)
	- If distortion_center files (.txt and .csv) are not available, execute the tool in folder fisheye_tool.
	- the output (txt-file and csv-file) needs to be stored in the same folder as the input fisheye images.
	- Requires MCR (Matlab Compiler Runtime) 8.4
	- Check 2DSurroundView_DemoGuide Chapter 4 for details.

2) calibration_tool: (compute perspective calibration matrix)
	- If InitialPerspectiveParams files (.c and .csv) are not available, execute the tool in folder calibration_tool.
	- the output (c-file and csv-file) needs to be stored in the same folder as the input fisheye images.
	- Requires MCR (Matlab Compiler Runtime) 8.4
	- Check 2DSurroundView_DemoGuide Chapter 3 for details.

3) surroundview.exe: (run SurroundView Demo)
	- Read README in folder ./surroundview
	- file run_example.bat shows an example call for SurroundView.exe. 
	  Make sure to adjust input arguments to your situation!

NOTES:
------
i)  ./sample_data/ contains 4 sample fisheye images and a reference image, which may be used to test the 3 steps above.
ii) ./sample_data/sample_calibration contains calibration files  for the sample images, that were created using the fisheye and calibration tools.
    To test only step 3, move these files to ./sample_data/ and execute run_example.bat in ./surroundview/ .




