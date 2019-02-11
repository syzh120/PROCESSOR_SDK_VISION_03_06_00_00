/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 * The present file contains source code taken from the file 
 * opencv_2.4.11\sources\samples\cpp\tutorial_code\calib3d\camera_calibration\camera_calibration.cpp
 * and opencv_2.4.11\sources\samples\cpp\stereo_calib.cpp  .
 *
 *
 *                               License Agreement
 *         For Camera Automatic Calibration tool based on openCV library .
 *                              (3-clause BSD License)
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * - Neither the names of the copyright holders nor the names of the contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * This software is provided by the copyright holders and contributors “as is” and any express or implied warranties, including, but not limited to, the implied warranties of merchantability and fitness for a particular purpose are disclaimed. In no event shall copyright holders or contributors be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to, procurement of substitute goods or services; loss of use, data, or profits; or business interruption) however caused and on any theory of liability, whether in contract, strict liability, or tort (including negligence or otherwise) arising in any way out of
 * the use of this software, even if advised of the possibility of such damage.
 *
 *******************************************************************************
 */
 
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <process.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

using namespace cv;
using namespace std;

static void help()
{
	cout<< "Usage: camAutoCalib configurationFile [-i]" << endl
		<< "configurationFile is a  XML/YAML file used to configure parameteres" << endl
		<< "Option -i is to enable interactive mode: application will wait for user's keys stroke between each frame." << endl;
}
class Settings
{
public:
	Settings() : goodInput(false) {}
	enum Pattern { NOT_EXISTING, CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };
	enum InputType { INVALID, CAMERA, VIDEO_FILE, IMAGE_LIST };

	void write(FileStorage& fs) const                        //Write serialization for this class
	{
		fs << "{" << "BoardSize_Width" << boardSize.width
			<< "BoardSize_Height" << boardSize.height
			<< "Square_Size" << squareSize
			<< "Calibrate_Pattern" << patternToUse
			<< "Calibrate_NrOfFrameToUse" << nrFrames
			//<< "Calibrate_FixAspectRatio" << aspectRatio
			//<< "Calibrate_AssumeZeroTangentialDistortion" << calibZeroTangentDist
			//<< "Calibrate_FixPrincipalPointAtTheCenter" << calibFixPrincipalPoint

			<< "Write_DetectedFeaturePoints" << bwritePoints
			<< "Write_extrinsicParameters" << bwriteExtrinsics
			<< "Write_outputFileName" << leftOutputFileName

			<< "Show_UndistortedImage" << showUndistorsed

			<< "Input_FlipAroundHorizontalAxis" << flipVertical
			<< "InputLeft" << inputLeft
			<< "InputRight" << inputRight
			<< "}";
	}
	void read(const FileNode& node)                          //Read serialization for this class
	{
		node["BoardSize_Width"] >> boardSize.width;
		node["BoardSize_Height"] >> boardSize.height;
		node["Calibrate_Pattern"] >> patternToUse;
		node["Square_Size"] >> squareSize;
		node["Use_Hints"] >> useHints;
		node["FocalX_Hint"] >> fx;
		node["FocalY_Hint"] >> fy;
		node["CenterX_Hint"] >> cx;
		node["CenterY_Hint"] >> cy;
		node["Reproj_Error_Thresh"] >> reprojErrThresh;
		node["Calibrate_NrOfFrameToUse"] >> nrFrames;
		//node["Calibrate_FixAspectRatio"] >> aspectRatio;
		node["Write_DetectedFeaturePoints"] >> bwritePoints;
		node["Write_extrinsicParameters"] >> bwriteExtrinsics;
		node["Write_leftOutputFileName"] >> leftOutputFileName;
		node["Write_rightOutputFileName"] >> rightOutputFileName;
		//node["Calibrate_AssumeZeroTangentialDistortion"] >> calibZeroTangentDist;
		//node["Calibrate_FixPrincipalPointAtTheCenter"] >> calibFixPrincipalPoint;
		node["Input_FlipAroundHorizontalAxis"] >> flipVertical;
		node["OutputMap_qShift"] >> qShift;
		node["Show_UndistortedImage"] >> showUndistorsed;
		node["Calibrate_Stereo"] >> calibStereo;
		node["Stereo_alpha_factor"] >> alpha;
		node["InputLeft"] >> inputLeft;
		node["InputRight"] >> inputRight;
		node["Write_leftOutputMapFileName"] >> leftOutputMapFileName;
		node["Write_rightOutputMapFileName"] >> rightOutputMapFileName;
		node["GenerateEveRemapFiles"] >> generateEveRemapFiles;
		node["RemapBlockWidth"] >> remapBlockWidth;
		node["RemapBlockHeight"] >> remapBlockHeight;
		node["RemapColorFormat"] >> remapColorFormat;
		interprate();
	}
	void interprate()
	{
		goodInput = true;
		if (boardSize.width <= 0 || boardSize.height <= 0)
		{
			cerr << "Invalid Board size: " << boardSize.width << " " << boardSize.height << endl;
			goodInput = false;
		}
		if (squareSize <= 10e-6)
		{
			cerr << "Invalid square size " << squareSize << endl;
			goodInput = false;
		}
		if (nrFrames <= 0)
		{
			cerr << "Invalid number of frames " << nrFrames << endl;
			goodInput = false;
		}

		if (inputLeft.empty() || inputRight.empty())      // Check for valid inputLeft
			inputType = INVALID;
		else
		{
			if (inputLeft[0] >= '0' && inputLeft[0] <= '9' && inputRight[0] >= '0' && inputRight[0] <= '9')
			{
				stringstream ssLeft(inputLeft);
				ssLeft >> leftCameraID;

				stringstream ssRight(inputRight);
				ssRight >> rightCameraID;

				inputType = CAMERA;
			}
			else
			{
				if (readStringList(inputLeft, leftImageList))
				{
					inputType = IMAGE_LIST;
					nrFrames = (nrFrames < (int)leftImageList.size()) ? nrFrames : (int)leftImageList.size();
					readStringList(inputRight, rightImageList);
				}
				else
					inputType = VIDEO_FILE;
			}
			if (inputType == CAMERA) {
				inputLeftCapture.open(leftCameraID);
				inputRightCapture.open(rightCameraID);
			}
			if (inputType == VIDEO_FILE) {
				inputLeftCapture.open(inputLeft);
				inputRightCapture.open(inputRight);
			}
			if (inputType != IMAGE_LIST && !inputLeftCapture.isOpened() && !inputRightCapture.isOpened())
				inputType = INVALID;
		}
		if (inputType == INVALID)
		{
			cerr << " Inexistent inputLeft: " << inputLeft;
			goodInput = false;
		}

		qScale = 1 << qShift;
		flag = 0;
		/*
		if(calibFixPrincipalPoint) flag |= CV_CALIB_FIX_PRINCIPAL_POINT;
		if(calibZeroTangentDist)   flag |= CV_CALIB_ZERO_TANGENT_DIST;
		if(aspectRatio)            flag |= CV_CALIB_FIX_ASPECT_RATIO;
		*/
		//flag |= CV_CALIB_FIX_ASPECT_RATIO; /* It looks like this flag shoudl be set otherwise calibration results can often be bad */
		if (useHints) {
			flag|= CV_CALIB_USE_INTRINSIC_GUESS;
		}

		calibrationPattern = NOT_EXISTING;
		if (!patternToUse.compare("CHESSBOARD")) calibrationPattern = CHESSBOARD;
		if (!patternToUse.compare("CIRCLES_GRID")) calibrationPattern = CIRCLES_GRID;
		if (!patternToUse.compare("ASYMMETRIC_CIRCLES_GRID")) calibrationPattern = ASYMMETRIC_CIRCLES_GRID;
		if (calibrationPattern == NOT_EXISTING)
		{
			cerr << " Inexistent camera calibration mode: " << patternToUse << endl;
			goodInput = false;
		}
		atLeftImageList = 0;
		atRightImageList = 0;

	}

	Mat nextLeftImage()
	{
		Mat result;
		if (inputLeftCapture.isOpened())
		{
			Mat view0;
			inputLeftCapture >> view0;
			if (view0.type() == CV_8UC1){
				cvtColor(view0, result, COLOR_GRAY2BGR);
			}
			else {
				view0.copyTo(result);
			}
		}
		else if (atLeftImageList < (int)leftImageList.size())
			result = imread(leftImageList[atLeftImageList++], CV_LOAD_IMAGE_COLOR);

		return result;
	}

	Mat nextRightImage()
	{
		Mat result;
		if (inputRightCapture.isOpened())
		{
			Mat view0;
			inputRightCapture >> view0;
			if (view0.type() == CV_8UC1){
				cvtColor(view0, result, COLOR_GRAY2BGR);
			}
			else {
				view0.copyTo(result);
			}
		}
		else if (atRightImageList < (int)rightImageList.size())
			result = imread(rightImageList[atRightImageList++], CV_LOAD_IMAGE_COLOR);

		return result;
	}

	void resetCapture() {
		if (inputLeftCapture.isOpened())
		{
			inputLeftCapture.release();
			inputLeftCapture.open(inputLeft);
		}
		if (inputRightCapture.isOpened())
		{
			inputRightCapture.release();
			inputRightCapture.open(inputRight);
		}
	}

	static bool readStringList(const string& filename, vector<string>& l)
	{
		l.clear();
		FileStorage fs(filename, FileStorage::READ);
		if (!fs.isOpened())
			return false;
		FileNode n = fs.getFirstTopLevelNode();
		if (n.type() != FileNode::SEQ)
			return false;
		FileNodeIterator it = n.begin(), it_end = n.end();
		for (; it != it_end; ++it)
			l.push_back((string)*it);
		return true;
	}
public:
	Size boardSize;            // The size of the board -> Number of items by width and height
	Pattern calibrationPattern;// One of the Chessboard, circles, or asymmetric circle pattern
	float squareSize;          // The size of a square in your defined unit (point, millimeter,etc).
	int nrFrames;              // The number of frames to use from the inputLeft for calibration
	float reprojErrThresh;
	//float aspectRatio;         // The aspect ratio
	bool bwritePoints;         //  Write detected feature points
	bool bwriteExtrinsics;     // Write extrinsic parameters
	bool useHints;
	float fx;
	float fy;
	float cx;
	float cy;
	//bool calibZeroTangentDist; // Assume zero tangential distortion
	//bool calibFixPrincipalPoint;// Fix the principal point at the center
	bool flipVertical;          // Flip the captured images around the horizontal axis
	bool calibStereo;
	float alpha;
	bool generateEveRemapFiles; // generate EVE remap files to be compiled with vision SDK
	int remapBlockWidth;
	int remapBlockHeight;
	int remapColorFormat;
	string leftOutputFileName;      // The name of the file where to write
	string rightOutputFileName;
	int qShift;					// Q scale applied to the map file when converting from float to int
	int qScale;
	string leftOutputMapFileName;	// The name of the file where to write the map file in (X,Y) format
	string rightOutputMapFileName;	// The name of the file where to write the map file in (X,Y) format
	bool showUndistorsed;       // Show undistorted images after calibration
	string inputLeft;               // The inputLeft ->
	string inputRight;               // The inputLeft ->



	int leftCameraID;
	int rightCameraID;
	vector<string> leftImageList;
	vector<string> rightImageList;
	int atLeftImageList;
	int atRightImageList;
	VideoCapture inputLeftCapture;
	VideoCapture inputRightCapture;
	InputType inputType;
	bool goodInput;
	int flag;

private:
	string patternToUse;


};

static void read(const FileNode& node, Settings& x, const Settings& default_value = Settings())
{
	if (node.empty())
		x = default_value;
	else
		x.read(node);
}

enum { DETECTION = 0, CAPTURING = 1, CALIBRATED = 2 };

bool runCalibrationAndSave(Settings& s, Size imageSize, Mat&  cameraMatrix, Mat& distCoeffs,
	vector<vector<Point2f> > imagePoints);

bool runCalibrationLeftRightAndSave(Settings& s, Size imageSize, Mat&  l_cameraMatrix, Mat&  r_cameraMatrix, Mat& l_distCoeffs, Mat& r_distCoeffs, vector<vector<Point2f> > l_imagePoints, vector<vector<Point2f> > r_imagePoints);

int writeFile_PGM(const char *outfilename,
	Mat image);

int main(int argc, char* argv[])
{
	bool keyPause;
	Rect validRoi[2];

	help();
	Settings s;
	const string inputSettingsFile = argc > 1 ? argv[1] : "default.xml";
	FileStorage fs(inputSettingsFile, FileStorage::READ); // Read the settings

	if (argc == 3 && !strcmp(argv[2], "-i")) {
		keyPause = true;
	}
	else {
		keyPause = false;
	}

	if (!fs.isOpened())
	{
		cout << "Could not open the configuration file: \"" << inputSettingsFile << "\"" << endl;
		return -1;
	}
	fs["Settings"] >> s;
	fs.release();                                         // close Settings file

	if (!s.goodInput)
	{
		cout << "Invalid inputLeft detected. Application stopping. " << endl;
		return -1;
	}

	vector<vector<Point2f> > l_imagePoints, r_imagePoints;
	vector<vector<Point2f> > stereo_l_imagePoints, stereo_r_imagePoints;
	Mat l_cameraMatrix, l_distCoeffs, r_cameraMatrix, r_distCoeffs;
	Size imageSize;
	int mode = s.inputType == Settings::IMAGE_LIST || s.inputType == Settings::VIDEO_FILE ? CAPTURING : DETECTION;
	clock_t prevTimestamp = 0;
	const Scalar RED(0, 0, 255), GREEN(0, 255, 0);
	const char ESC_KEY = 27;

	for (int i = 0;; ++i)
	{
		Mat l_view, r_view;
		bool blinkOutput = false;

		l_view = s.nextLeftImage();
		r_view = s.nextRightImage();

		/* If we are going to generate map file compatible with EVE, we want to save the first input into a pgm file
		   which will be automataically used by remapExecute to validate the converted map */
		if (s.generateEveRemapFiles && i==0) {

			//imwrite("eve_input_test_left.pgm", l_view);
			writeFile_PGM("eve_test_left.pgm", l_view);
			//imwrite("eve_input_test_right.pgm", r_view);
			writeFile_PGM("eve_test_right.pgm", r_view);

		}
#if 0
		//-----  If no more image, or got enough, then stop calibration and show result -------------
		if (mode == CAPTURING && l_imagePoints.size() >= (unsigned)s.nrFrames)
		{
			if (runCalibrationLeftRightAndSave(s, imageSize, l_cameraMatrix, r_cameraMatrix, l_distCoeffs, r_distCoeffs, l_imagePoints, r_imagePoints))
				mode = CALIBRATED;
			else
				mode = DETECTION;
		}
#endif
		if (l_view.empty()) {
			l_view = s.nextLeftImage();
		}

		if (r_view.empty()) {
			r_view = s.nextRightImage();
		}

		if (l_view.empty() || r_view.empty() || (l_imagePoints.size() >= (unsigned)s.nrFrames) )          // If no more images then run calibration, save and stop loop.
		{
			if (l_imagePoints.size() > 0)
				runCalibrationLeftRightAndSave(s, imageSize, l_cameraMatrix, r_cameraMatrix, l_distCoeffs, r_distCoeffs, l_imagePoints, r_imagePoints);
			break;
		}


		imageSize = l_view.size();  // Format inputLeft image.
		if (s.flipVertical)    {
			flip(l_view, l_view, 0);
			flip(r_view, r_view, 0);
		}

		vector<Point2f> l_pointBuf;
		vector<Point2f> r_pointBuf;

		bool l_found, r_found;
		switch (s.calibrationPattern) // Find feature points on the inputLeft format
		{
		case Settings::CHESSBOARD:
			l_found = findChessboardCorners(l_view, s.boardSize, l_pointBuf,
				CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
			r_found = findChessboardCorners(r_view, s.boardSize, r_pointBuf,
				CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
			break;
		case Settings::CIRCLES_GRID:
			l_found = findCirclesGrid(l_view, s.boardSize, l_pointBuf);
			r_found = findCirclesGrid(r_view, s.boardSize, r_pointBuf);
			break;
		case Settings::ASYMMETRIC_CIRCLES_GRID:
			l_found = findCirclesGrid(l_view, s.boardSize, l_pointBuf, CALIB_CB_ASYMMETRIC_GRID);
			r_found = findCirclesGrid(r_view, s.boardSize, r_pointBuf, CALIB_CB_ASYMMETRIC_GRID);
			break;
		default:
			l_found = false;
			r_found = false;
			break;
		}

		if (l_found)                // If done with success,
		{
			// improve the found corners' coordinate accuracy for chessboard
			if (s.calibrationPattern == Settings::CHESSBOARD)
			{
				Mat l_viewGray;

				cvtColor(l_view, l_viewGray, COLOR_BGR2GRAY);
				
				cornerSubPix(l_viewGray, l_pointBuf, Size(5, 5),
					Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
			}

			l_imagePoints.push_back(l_pointBuf);

			// Draw the corners.
			drawChessboardCorners(l_view, s.boardSize, Mat(l_pointBuf), l_found);
		}

		if (r_found)                // If done with success,
		{
			// improve the found corners' coordinate accuracy for chessboard
			if (s.calibrationPattern == Settings::CHESSBOARD)
			{
				Mat r_viewGray;

				cvtColor(r_view, r_viewGray, COLOR_BGR2GRAY);

				cornerSubPix(r_viewGray, r_pointBuf, Size(5, 5),
					Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
			}

			r_imagePoints.push_back(r_pointBuf);

			// Draw the corners.
			drawChessboardCorners(r_view, s.boardSize, Mat(r_pointBuf), r_found);
		}

		if (l_found && r_found) {
			if (s.calibStereo)  {
				stereo_l_imagePoints.push_back(l_pointBuf);
				stereo_r_imagePoints.push_back(r_pointBuf);
			}
		}

		//----------------------------- Output Text ------------------------------------------------
		string msg = (mode == CAPTURING) ? "100/100" :
			mode == CALIBRATED ? "Calibrated" : "Press 'g' to start";
		int baseLine = 0;
		Size textSize = getTextSize(msg, 1, 1, 1, &baseLine);
		Point textOrigin(l_view.cols - 2 * textSize.width - 10, l_view.rows - 2 * baseLine - 10);
		string l_msg, r_msg;

		if (mode == CAPTURING)
		{
			if (s.showUndistorsed) {
				l_msg = format("%d/%d Undist", (int)l_imagePoints.size(), s.nrFrames);
				r_msg = format("%d/%d Undist", (int)r_imagePoints.size(), s.nrFrames);
			}
			else {
				l_msg = format("%d/%d", (int)l_imagePoints.size(), s.nrFrames);
				r_msg = format("%d/%d", (int)l_imagePoints.size(), s.nrFrames);
			}
		}

		putText(l_view, l_msg, textOrigin, 1, 1, mode == CALIBRATED ? GREEN : RED);
		putText(r_view, r_msg, textOrigin, 1, 1, mode == CALIBRATED ? GREEN : RED);

		if (blinkOutput) {
			bitwise_not(l_view, l_view);
			bitwise_not(r_view, r_view);
		}

		//------------------------- Video capture  output  undistorted ------------------------------
		if (mode == CALIBRATED && s.showUndistorsed)
		{
			Mat temp = l_view.clone();
			undistort(temp, l_view, l_cameraMatrix, l_distCoeffs);
			temp = r_view.clone();
			undistort(temp, r_view, r_cameraMatrix, r_distCoeffs);
		}

		//------------------------------ Show image and check for inputLeft commands -------------------
		imshow("Left Image View", l_view);
		imshow("Right Image View", r_view);

		char key = (char)waitKey( (keyPause== true) ? 0 : 16);

		if (key == ESC_KEY)
			break;

		if (key == 'u' && mode == CALIBRATED)
			s.showUndistorsed = !s.showUndistorsed;

		if (s.inputLeftCapture.isOpened() && key == 'g')
		{
			mode = CAPTURING;
			l_imagePoints.clear();
			r_imagePoints.clear();
		}

	}

	Mat l_R, r_R, l_P, r_P, Q;

	if (s.calibStereo) {

		Mat R, T, E, F;
		vector<vector<Point3f> > objectPoints;
		int nimages = stereo_l_imagePoints.size();

		/* Set the real-world 3d coordinates of the checkerboard corners */
		objectPoints.resize(nimages);

		for (int i = 0; i < nimages; i++)
		{
			for (int j = 0; j < s.boardSize.height; j++)
			for (int k = 0; k < s.boardSize.width; k++)
				objectPoints[i].push_back(Point3f(j*s.squareSize, k*s.squareSize, 0));
		}

		cout << "\nRunning stereo calibration ...\n";

		double rms = stereoCalibrate(objectPoints, stereo_l_imagePoints, stereo_r_imagePoints,
			l_cameraMatrix, l_distCoeffs,
			r_cameraMatrix, r_distCoeffs,
			imageSize, R, T, E, F,
			TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 100, 1e-5),
			CV_CALIB_USE_INTRINSIC_GUESS);
		cout << "done with RMS error=" << rms << endl << endl;

		stereoRectify(l_cameraMatrix, l_distCoeffs,
			r_cameraMatrix, r_distCoeffs,
			imageSize, R, T, l_R, r_R, l_P, r_P, Q,
			CALIB_ZERO_DISPARITY, s.alpha, imageSize, &validRoi[0], &validRoi[1]);

		cout << "Valid ROI for left image @(x=" << validRoi[0].x << ", y=" << validRoi[0].y << "), width=" << validRoi[0].width << ", height=" << validRoi[0].height << endl;
		int l_x_botright = validRoi[0].x + validRoi[0].width - 1;
		int l_y_botright = validRoi[0].y + validRoi[0].height - 1;
		cout << "Valid ROI for right image @(x=" << validRoi[1].x << ", y=" << validRoi[1].y << "), width=" << validRoi[1].width << ", height=" << validRoi[1].height << endl;
		int r_x_botright = validRoi[1].x + validRoi[1].width - 1;
		int r_y_botright = validRoi[1].y + validRoi[1].height - 1;
		int common_x = MAX(validRoi[0].x, validRoi[1].x);
		int common_y = MAX(validRoi[0].y, validRoi[1].y);
		int commonRoiWidth = l_x_botright - common_x + 1;
		int commonRoiHeight = l_y_botright - common_y + 1;
		cout << "Common ROI for both images @(x=" << common_x << ", y=" << common_y << "), width=" << commonRoiWidth << ", height=" << commonRoiHeight << ")" << endl << endl;
	}

	{
		Mat view, rview, map1, map2;
		FILE *fid;
		float x, y;
		int x_int, y_int;
		const char * leftOutputMapFileName = s.leftOutputMapFileName.c_str();
		const char * rightOutputMapFileName = s.rightOutputMapFileName.c_str();

		if (s.calibStereo) {
			initUndistortRectifyMap(l_cameraMatrix, l_distCoeffs, l_R,
				l_P, imageSize, CV_32FC1, map1, map2);
		}
		else {
			initUndistortRectifyMap(l_cameraMatrix, l_distCoeffs, Mat(),
				getOptimalNewCameraMatrix(l_cameraMatrix, l_distCoeffs, imageSize, 1, imageSize, 0), imageSize, CV_32FC1, map1, map2);
		}

		for (int i = 0; i < imageSize.height; i++) {
			for (int j = 0; j < imageSize.width; j++) {
				if (map1.at<float>(i, j) < 0)
					map1.at<float>(i, j) = 0;
				if (map1.at<float>(i, j) >= imageSize.width)
					map1.at<float>(i, j) = (float)(imageSize.width - 1);
				if (map2.at<float>(i, j) < 0)
					map2.at<float>(i, j) = 0;
				if (map2.at<float>(i, j) >= imageSize.height)
					map2.at<float>(i, j) = (float)(imageSize.height - 1);
			}
		}

		fopen_s(&fid, leftOutputMapFileName, "wb");

		if (fid == NULL) {
			cout << "Cannot open output file " << endl;
		}

		for (int i = 0; i < imageSize.height; i++) {
			for (int j = 0; j < imageSize.width; j++) {
				x = map1.at<float>(i, j);
				x_int = (int)(x*s.qScale + 0.5);

				y = map2.at<float>(i, j);
				y_int = (int)(y*s.qScale + 0.5);

				fwrite(&x_int, sizeof(CV_32S), 1, fid);
				fwrite(&y_int, sizeof(CV_32S), 1, fid);
			}
		}

		fclose(fid);

		if (s.calibStereo) {
			initUndistortRectifyMap(r_cameraMatrix, r_distCoeffs, r_R,
				r_P, imageSize, CV_32FC1, map1, map2);
		}
		else {
			initUndistortRectifyMap(r_cameraMatrix, r_distCoeffs, Mat(),
				getOptimalNewCameraMatrix(r_cameraMatrix, r_distCoeffs, imageSize, 1, imageSize, 0), imageSize, CV_32FC1, map1, map2);
		}

		for (int i = 0; i < imageSize.height; i++) {
			for (int j = 0; j < imageSize.width; j++) {
				if (map1.at<float>(i, j) < 0)
					map1.at<float>(i, j) = 0;
				if (map1.at<float>(i, j) >= imageSize.width)
					map1.at<float>(i, j) = (float)(imageSize.width - 1);
				if (map2.at<float>(i, j) < 0)
					map2.at<float>(i, j) = 0;
				if (map2.at<float>(i, j) >= imageSize.height)
					map2.at<float>(i, j) = (float)(imageSize.height - 1);
			}
		}

		fopen_s(&fid, rightOutputMapFileName, "wb");

		if (fid == NULL) {
			cout << "Cannot open output file " << endl;
		}

		for (int i = 0; i < imageSize.height; i++) {
			for (int j = 0; j < imageSize.width; j++) {
				x = map1.at<float>(i, j);
				x_int = (int)(x*s.qScale + 0.5);

				y = map2.at<float>(i, j);
				y_int = (int)(y*s.qScale + 0.5);

				fwrite(&x_int, sizeof(CV_32S), 1, fid);
				fwrite(&y_int, sizeof(CV_32S), 1, fid);
			}
		}

		fclose(fid);
	}

	// -----------------------Show the undistorted image for the image list ------------------------
	if (s.showUndistorsed)
	{
		Mat l_view, l_rview, l_map1, l_map2;
		Mat r_view, r_rview, r_map1, r_map2;

		if (s.calibStereo) {
			initUndistortRectifyMap(l_cameraMatrix, l_distCoeffs, l_R,
				l_P,
				imageSize, CV_16SC2, l_map1, l_map2);

			initUndistortRectifyMap(r_cameraMatrix, r_distCoeffs, r_R,
				r_P,
				imageSize, CV_16SC2, r_map1, r_map2);
		}
		else {
			initUndistortRectifyMap(l_cameraMatrix, l_distCoeffs, Mat(),
				getOptimalNewCameraMatrix(l_cameraMatrix, l_distCoeffs, imageSize, 1, imageSize, 0),
				imageSize, CV_16SC2, l_map1, l_map2);

			initUndistortRectifyMap(r_cameraMatrix, r_distCoeffs, Mat(),
				getOptimalNewCameraMatrix(r_cameraMatrix, r_distCoeffs, imageSize, 1, imageSize, 0),
				imageSize, CV_16SC2, r_map1, r_map2);
		}

		if (s.generateEveRemapFiles) {

			FILE *fid;
			int error;

			fopen_s(&fid, "eveRemapConvertTable_config.txt", "wt");
			if (fid == NULL) {
				cout << "Cannot open master config file for convert" << endl;
				return 0;
			}
			fprintf_s(fid, "1 eveRemapConvertTable.cfg\n0\n");
			fclose(fid);
			fopen_s(&fid, "eveRemapConvertTable.cfg", "wt");
			if (fid == NULL) {
				cout << "Cannot open config file for convert" << endl;
				return 0;
			}
			fprintf_s(fid, "numTestCases = 4\n\n");

			fprintf_s(fid, "remapWidth0 = %d\n", imageSize.width);
			fprintf_s(fid, "remapHeight0 = %d\n", imageSize.height);
			fprintf_s(fid, "blockWidth0 = %d\n", s.remapBlockWidth);
			fprintf_s(fid, "blockHeight0 = %d\n", s.remapBlockHeight);
			fprintf_s(fid, "colorFormat0 = %d\n", s.remapColorFormat);
			fprintf_s(fid, "qShift0 = %d\n", s.qShift);
			fprintf_s(fid, "functionName0 = \"stereovision_getLeftBlockMap\"\n");
			fprintf_s(fid, "inputMapFileFormat0 = 0\n");
			fprintf_s(fid, "inputMapFile0 = \"leftInputMap_int.bin\"\n");
			fprintf_s(fid, "outputMapFileFormat0 = 0\n");
			fprintf_s(fid, "outputMapFile0 = \"rectMapLeft_int_converted.bin\"\n\n");
			remove("rectMapLeft_int_converted.bin");

			fprintf_s(fid, "remapWidth1 = %d\n", imageSize.width);
			fprintf_s(fid, "remapHeight1 = %d\n", imageSize.height);
			fprintf_s(fid, "blockWidth1 = %d\n", s.remapBlockWidth);
			fprintf_s(fid, "blockHeight1 = %d\n", s.remapBlockHeight);
			fprintf_s(fid, "colorFormat1 = %d\n", s.remapColorFormat);
			fprintf_s(fid, "qShift1 = %d\n", s.qShift);
			fprintf_s(fid, "functionName1 = \"stereovision_getLeftBlockMap\"\n");
			fprintf_s(fid, "inputMapFileFormat1 = 0\n");
			fprintf_s(fid, "inputMapFile1 = \"leftInputMap_int.bin\"\n");
			fprintf_s(fid, "outputMapFileFormat1 = 1\n");
			fprintf_s(fid, "outputMapFile1 = \"rectMapLeft_int_converted.c\"\n\n");
			remove("rectMapLeft_int_converted.c");

			fprintf_s(fid, "remapWidth2 = %d\n", imageSize.width);
			fprintf_s(fid, "remapHeight2 = %d\n", imageSize.height);
			fprintf_s(fid, "blockWidth2 = %d\n", s.remapBlockWidth);
			fprintf_s(fid, "blockHeight2 = %d\n", s.remapBlockHeight);
			fprintf_s(fid, "colorFormat2 = %d\n", s.remapColorFormat);
			fprintf_s(fid, "qShift2 = %d\n", s.qShift);
			fprintf_s(fid, "functionName2 = \"stereovision_getRightBlockMap\"\n");
			fprintf_s(fid, "inputMapFileFormat2 = 0\n");
			fprintf_s(fid, "inputMapFile2 = \"rightInputMap_int.bin\"\n");
			fprintf_s(fid, "outputMapFileFormat2 = 0\n");
			fprintf_s(fid, "outputMapFile2 = \"rectMapRight_int_converted.bin\"\n\n");
			remove("rectMapRight_int_converted.bin");

			fprintf_s(fid, "remapWidth3 = %d\n", imageSize.width);
			fprintf_s(fid, "remapHeight3 = %d\n", imageSize.height);
			fprintf_s(fid, "blockWidth3 = %d\n", s.remapBlockWidth);
			fprintf_s(fid, "blockHeight3 = %d\n", s.remapBlockHeight);
			fprintf_s(fid, "colorFormat3 = %d\n", s.remapColorFormat);
			fprintf_s(fid, "qShift3 = %d\n", s.qShift);
			fprintf_s(fid, "functionName3 = \"stereovision_getRightBlockMap\"\n");
			fprintf_s(fid, "inputMapFileFormat3 = 0\n");
			fprintf_s(fid, "inputMapFile3 = \"rightInputMap_int.bin\"\n");
			fprintf_s(fid, "outputMapFileFormat3 = 1\n");
			fprintf_s(fid, "outputMapFile3 = \"rectMapRight_int_converted.c\"\n\n");
			remove("recMapRight_int_converted.c");

			fclose(fid);

			fopen_s(&fid, "eveRemapExecute_config.txt", "wt");
			if (fid == NULL) {
				cout << "Cannot open master config file for remap execute" << endl;
				return 0;
			}
			fprintf_s(fid, "1 eveRemapExecute.cfg\n0\n");
			fclose(fid);

			fopen_s(&fid, "eveRemapExecute.cfg", "wt");
			if (fid == NULL) {
				cout << "Cannot open config file for remap execute" << endl;
				return 0;
			}
			fprintf_s(fid, "numTestCases = 2\n\n");

			fprintf_s(fid, "remapWidth0 = %d\n", imageSize.width);
			fprintf_s(fid, "remapHeight0 = %d\n", imageSize.height);
			fprintf_s(fid, "inputWidth0 = %d\n", imageSize.width);
			fprintf_s(fid, "inputHeight0 = %d\n", imageSize.height);
			fprintf_s(fid, "colorFormat0 = %d\n", s.remapColorFormat);
			fprintf_s(fid, "originalMapFile0 = \"leftInputMap_int.bin\"\n");
			fprintf_s(fid, "convertedBinMapFile0 = \"rectMapLeft_int_converted.bin\"\n");
			fprintf_s(fid, "inputFile0 = \"eve_test_left.pgm\"\n");
			fprintf_s(fid, "outputFile0 = \"eve_rect_test_left.pgm\"\n\n");
			remove("eve_rect_test_left.pgm");

			fprintf_s(fid, "remapWidth1 = %d\n", imageSize.width);
			fprintf_s(fid, "remapHeight1 = %d\n", imageSize.height);
			fprintf_s(fid, "inputWidth1 = %d\n", imageSize.width);
			fprintf_s(fid, "inputHeight1 = %d\n", imageSize.height);
			fprintf_s(fid, "colorFormat1 = %d\n", s.remapColorFormat);
			fprintf_s(fid, "originalMapFile1 = \"rightInputMap_int.bin\"\n");
			fprintf_s(fid, "convertedBinMapFile1 = \"rectMapRight_int_converted.bin\"\n");
			fprintf_s(fid, "inputFile1 = \"eve_test_right.pgm\"\n");
			fprintf_s(fid, "outputFile1 = \"eve_rect_test_right.pgm\"\n\n");
			remove("eve_rect_test_right.pgm");

			fclose(fid);

			error = system("remapConvertTable.eve.out.exe eveRemapConvertTable_config.txt");
			if (error == -1) {
				cout << "\nError executing EVE convert map:" << errno << endl;
			}
			else {
			}

			error = system("remapExecute.eve.out.exe eveRemapExecute_config.txt");
			if (error == -1) {
				cout << "Error executing EVE execute map:" << errno << endl;
			}
			else {
				fopen_s(&fid, "eve_rect_test_right.pgm", "rb");
				if (fid == NULL) {
					remove("rectMapRLeft_int_converted.bin");
					remove("rectMapLeft_int_converted.c");
					remove("rectMapRight_int_converted.bin");
					remove("rectMapRight_int_converted.c");
					cout << "Table conversion to EVE format failed, please try to reduce parameters RemapBlockWidth or RemapBlockHeight in the xml configuration file" << endl;
					
				}
				else {
					cout << "Table conversion to EVE format successful: tables converted into files rectMapLeft_int_converted.c and rectMapRight_int_converted.c" << endl;
					cout << "Rectified left and right images of the first stereo pair generated into eve_rect_test_left.pgm, eve_rect_test_right.pgm and available for inspection" << endl;
					cout << "Visualization of rectified left and right views enabled. Press any key to advance to the next set of views or 'q' or ESC to quit the visualization" << endl;
					fclose(fid);
				}	
			}
		}

		Mat canvas, cimg;
		double sf;
		int w, h;

		sf = 600. / MAX(imageSize.width, imageSize.height);
		w = cvRound(imageSize.width*sf);
		h = cvRound(imageSize.height*sf);
		canvas.create(h, w * 2, CV_8UC3);

		if (s.inputType == Settings::IMAGE_LIST) {
			
			for (int i = 0; i < (int)s.leftImageList.size(); i++)
			{
				l_view = imread(s.leftImageList[i], 1);
				r_view = imread(s.rightImageList[i], 1);

				if (l_view.empty())
					continue;
				remap(l_view, l_rview, l_map1, l_map2, INTER_LINEAR);
				remap(r_view, r_rview, r_map1, r_map2, INTER_LINEAR);
				//imshow("Left Image View", l_rview);
				//imshow("Right Image View", r_rview);

				Mat canvasPart = canvas(Rect(0, 0, w, h));
				resize(l_rview, canvasPart, canvasPart.size(), 0, 0, CV_INTER_AREA);

				Rect l_vroi(cvRound(validRoi[0].x*sf), cvRound(validRoi[0].y*sf),
					cvRound(validRoi[0].width*sf), cvRound(validRoi[0].height*sf));
				rectangle(canvasPart, l_vroi, Scalar(0, 0, 255), 3, 8);

				for (int j = 0; j < canvas.rows; j += 16)
					line(canvas, Point(0, j), Point(canvas.cols, j), Scalar(0, 255, 0), 1, 8);

				canvasPart = canvas(Rect(w, 0, w, h));
				resize(r_rview, canvasPart, canvasPart.size(), 0, 0, CV_INTER_AREA);

				Rect r_vroi(cvRound(validRoi[1].x*sf), cvRound(validRoi[1].y*sf),
					cvRound(validRoi[1].width*sf), cvRound(validRoi[1].height*sf));
				rectangle(canvasPart, r_vroi, Scalar(0, 0, 255), 3, 8);

				for (int j = 0; j < canvas.rows; j += 16)
					line(canvas, Point(0, j), Point(canvas.cols, j), Scalar(0, 255, 0), 1, 8);

				imshow("rectified", canvas);

				char c = (char)waitKey(0);
				if (c == ESC_KEY || c == 'q' || c == 'Q')
					break;
			}
		}
		else {
			s.resetCapture();
			l_view = s.nextLeftImage();
			r_view = s.nextRightImage();
			while (!l_view.empty())	{
				remap(l_view, l_rview, l_map1, l_map2, CV_INTER_LINEAR);
				remap(r_view, r_rview, r_map1, r_map2, CV_INTER_LINEAR);
				//imshow("Left Image View", l_rview);
				//imshow("Right Image View", r_rview);

				Mat canvasPart = canvas(Rect(0, 0, w, h));
				resize(l_rview, canvasPart, canvasPart.size(), 0, 0, CV_INTER_AREA);

				Rect l_vroi(cvRound(validRoi[0].x*sf), cvRound(validRoi[0].y*sf),
					cvRound(validRoi[0].width*sf), cvRound(validRoi[0].height*sf));
				rectangle(canvasPart, l_vroi, Scalar(0, 0, 255), 3, 8);

				for (int j = 0; j < canvas.rows; j += 16)
					line(canvas, Point(0, j), Point(canvas.cols, j), Scalar(0, 255, 0), 1, 8);

				canvasPart = canvas(Rect(w, 0, w, h));
				resize(r_rview, canvasPart, canvasPart.size(), 0, 0, CV_INTER_AREA);

				Rect r_vroi(cvRound(validRoi[1].x*sf), cvRound(validRoi[1].y*sf),
					cvRound(validRoi[1].width*sf), cvRound(validRoi[1].height*sf));
				rectangle(canvasPart, r_vroi, Scalar(0, 0, 255), 3, 8);

				for (int j = 0; j < canvas.rows; j += 16)
					line(canvas, Point(0, j), Point(canvas.cols, j), Scalar(0, 255, 0), 1, 8);

				imshow("rectified", canvas);

				char c = (char)waitKey(0);
				if (c == ESC_KEY || c == 'q' || c == 'Q')
					break;
				l_view = s.nextLeftImage();
				r_view = s.nextRightImage();
			};
		}
	}

	

	return 0;
}

static double computeReprojectionErrors(const vector<vector<Point3f> >& objectPoints,
	const vector<vector<Point2f> >& imagePoints,
	const vector<Mat>& rvecs, const vector<Mat>& tvecs,
	const Mat& cameraMatrix, const Mat& distCoeffs,
	vector<float>& perViewErrors)
{
	vector<Point2f> imagePoints2;
	int i, totalPoints = 0;
	double totalErr = 0, err;
	perViewErrors.resize(objectPoints.size());

	for (i = 0; i < (int)objectPoints.size(); ++i)
	{
		projectPoints(Mat(objectPoints[i]), rvecs[i], tvecs[i], cameraMatrix,
			distCoeffs, imagePoints2);
		err = norm(Mat(imagePoints[i]), Mat(imagePoints2), CV_L2);

		int n = (int)objectPoints[i].size();
		perViewErrors[i] = (float)std::sqrt(err*err / n);
		totalErr += err*err;
		totalPoints += n;
	}

	return std::sqrt(totalErr / totalPoints);
}

static void calcBoardCornerPositions(Size boardSize, float squareSize, vector<Point3f>& corners,
	Settings::Pattern patternType /*= Settings::CHESSBOARD*/)
{
	corners.clear();

	switch (patternType)
	{
	case Settings::CHESSBOARD:
	case Settings::CIRCLES_GRID:
		for (int i = 0; i < boardSize.height; ++i)
		for (int j = 0; j < boardSize.width; ++j)
			corners.push_back(Point3f(float(j*squareSize), float(i*squareSize), 0));
		break;

	case Settings::ASYMMETRIC_CIRCLES_GRID:
		for (int i = 0; i < boardSize.height; i++)
		for (int j = 0; j < boardSize.width; j++)
			corners.push_back(Point3f(float((2 * j + i % 2)*squareSize), float(i*squareSize), 0));
		break;
	default:
		break;
	}
}

static bool runCalibration(Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
	vector<vector<Point2f> > imagePoints, vector<Mat>& rvecs, vector<Mat>& tvecs,
	vector<float>& reprojErrs, double& totalAvgErr, int& finalSize)
{
	bool computeAgain, ok;
	unsigned int i, j;
	cameraMatrix = Mat::eye(3, 3, CV_64F);
	if (s.flag & CV_CALIB_FIX_ASPECT_RATIO)
		cameraMatrix.at<double>(0, 0) = 1.0;

	if (s.useHints == true) {
		cameraMatrix.at<double>(0, 0) = s.fx;
		cameraMatrix.at<double>(1, 1) = s.fy;
		cameraMatrix.at<double>(0, 2) = s.cx;
		cameraMatrix.at<double>(1, 2) = s.cy;
		cameraMatrix.at<double>(2, 2) = 1.0;
	}

	distCoeffs = Mat::zeros(8, 1, CV_64F);

	vector<vector<Point3f> > objectPoints(1);
	calcBoardCornerPositions(s.boardSize, s.squareSize, objectPoints[0], s.calibrationPattern);

	objectPoints.resize(imagePoints.size(), objectPoints[0]);

	do {
		//Find intrinsic and extrinsic camera parameters
		double rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix,
			distCoeffs, rvecs, tvecs, s.flag);// | CV_CALIB_FIX_K4 | CV_CALIB_FIX_K5);

		ok = checkRange(cameraMatrix) && checkRange(distCoeffs);

		totalAvgErr = computeReprojectionErrors(objectPoints, imagePoints,
			rvecs, tvecs, cameraMatrix, distCoeffs, reprojErrs);

		computeAgain = false;
		for (i = 0, j = 0; i < reprojErrs.size(); i++) {
			if (reprojErrs[i] > s.reprojErrThresh) {
				imagePoints.erase(imagePoints.begin() + j);
				objectPoints.erase(objectPoints.begin() + j);
				computeAgain = true;
				//break;
			}
			else {
				j++;
			}
		}
	} while (computeAgain== true);

	finalSize = reprojErrs.size();

	return ok;
}

// Print camera parameters to the output file
static void saveCameraParams(string outputFileName, Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
	const vector<Mat>& rvecs, const vector<Mat>& tvecs,
	const vector<float>& reprojErrs, const vector<vector<Point2f> >& imagePoints,
	double totalAvgErr)
{
	FileStorage fs(outputFileName, FileStorage::WRITE);

	time_t tm;
	time(&tm);
	struct tm t2;
	char buf[1024];

	localtime_s(&t2, &tm);
	strftime(buf, sizeof(buf)-1, "%c", &t2);

	fs << "calibration_Time" << buf;

	if (!rvecs.empty() || !reprojErrs.empty())
		fs << "nrOfFrames" << (int)std::max(rvecs.size(), reprojErrs.size());
	fs << "image_Width" << imageSize.width;
	fs << "image_Height" << imageSize.height;
	fs << "board_Width" << s.boardSize.width;
	fs << "board_Height" << s.boardSize.height;
	fs << "square_Size" << s.squareSize;

	//if( s.flag & CV_CALIB_FIX_ASPECT_RATIO )
	//   fs << "FixAspectRatio" << s.aspectRatio;

	if (s.flag)
	{
		sprintf_s(buf, 1024, "flags: %s%s%s%s",
			s.flag & CV_CALIB_USE_INTRINSIC_GUESS ? " +use_intrinsic_guess" : "",
			s.flag & CV_CALIB_FIX_ASPECT_RATIO ? " +fix_aspectRatio" : "",
			s.flag & CV_CALIB_FIX_PRINCIPAL_POINT ? " +fix_principal_point" : "",
			s.flag & CV_CALIB_ZERO_TANGENT_DIST ? " +zero_tangent_dist" : "");
		cvWriteComment(*fs, buf, 0);

	}

	fs << "flagValue" << s.flag;

	fs << "Camera_Matrix" << cameraMatrix;
	fs << "Distortion_Coefficients" << distCoeffs;

	fs << "Avg_Reprojection_Error" << totalAvgErr;
	if (!reprojErrs.empty())
		fs << "Per_View_Reprojection_Errors" << Mat(reprojErrs);

	if (!rvecs.empty() && !tvecs.empty())
	{
		CV_Assert(rvecs[0].type() == tvecs[0].type());
		Mat bigmat((int)rvecs.size(), 6, rvecs[0].type());
		for (int i = 0; i < (int)rvecs.size(); i++)
		{
			Mat r = bigmat(Range(i, i + 1), Range(0, 3));
			Mat t = bigmat(Range(i, i + 1), Range(3, 6));

			CV_Assert(rvecs[i].rows == 3 && rvecs[i].cols == 1);
			CV_Assert(tvecs[i].rows == 3 && tvecs[i].cols == 1);
			//*.t() is MatExpr (not Mat) so we can use assignment operator
			r = rvecs[i].t();
			t = tvecs[i].t();
		}
		cvWriteComment(*fs, "a set of 6-tuples (rotation vector + translation vector) for each view", 0);
		fs << "Extrinsic_Parameters" << bigmat;
	}

	if (!imagePoints.empty())
	{
		Mat imagePtMat((int)imagePoints.size(), (int)imagePoints[0].size(), CV_32FC2);
		for (int i = 0; i < (int)imagePoints.size(); i++)
		{
			Mat r = imagePtMat.row(i).reshape(2, imagePtMat.cols);
			Mat imgpti(imagePoints[i]);
			imgpti.copyTo(r);
		}
		fs << "Image_points" << imagePtMat;
	}
}

bool runCalibrationAndSave(Settings& s, Size imageSize, Mat&  cameraMatrix, Mat& distCoeffs, vector<vector<Point2f> > imagePoints)
{
	vector<Mat> rvecs, tvecs;
	vector<float> reprojErrs;
	int finalSize;
	double totalAvgErr = 0;

	bool ok = runCalibration(s, imageSize, cameraMatrix, distCoeffs, imagePoints, rvecs, tvecs,
		reprojErrs, totalAvgErr, finalSize);

	cout << (ok ? "Calibration succeeded" : "Calibration failed")
		<< ". avg re-projection error = " << totalAvgErr;
	cout << imagePoints.size() - finalSize << "out of " << imagePoints.size() << "frames were discarded due to re-projection error exceeding Reproj_Error_Thresh= " << s.reprojErrThresh << endl << endl;
	if (ok)
		saveCameraParams(s.leftOutputFileName, s, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs, reprojErrs,
		imagePoints, totalAvgErr);
	return ok;
}

bool runCalibrationLeftRightAndSave(Settings& s, Size imageSize, Mat&  l_cameraMatrix, Mat&  r_cameraMatrix, Mat& l_distCoeffs, Mat& r_distCoeffs, vector<vector<Point2f> > l_imagePoints, vector<vector<Point2f> > r_imagePoints)
{
	vector<Mat> l_rvecs, l_tvecs;
	vector<float> l_reprojErrs;
	int finalSize;
	double l_totalAvgErr = 0;

	vector<Mat> r_rvecs, r_tvecs;
	vector<float> r_reprojErrs;
	double r_totalAvgErr = 0;

	bool l_ok = runCalibration(s, imageSize, l_cameraMatrix, l_distCoeffs, l_imagePoints, l_rvecs, l_tvecs,
		l_reprojErrs, l_totalAvgErr, finalSize);
	cout << endl << (l_ok ? "Left Calibration succeeded" : "Calibration failed")
		<< ". avg re projection error = " << l_totalAvgErr << endl;
	cout << l_imagePoints.size() - finalSize << " out of " << l_imagePoints.size() << " frames were discarded due to re-projection error exceeding Reproj_Error_Thresh= " << s.reprojErrThresh << endl << endl;

	bool r_ok = runCalibration(s, imageSize, r_cameraMatrix, r_distCoeffs, r_imagePoints, r_rvecs, r_tvecs,
		r_reprojErrs, r_totalAvgErr, finalSize);
	cout << (r_ok ? "Right Calibration succeeded" : "Calibration failed")
		<< ". avg re projection error = " << r_totalAvgErr << endl;
	cout << r_imagePoints.size() - finalSize << " out of " << r_imagePoints.size() << " frames were discarded due to re-projection error exceeding Reproj_Error_Thresh= " << s.reprojErrThresh << endl << endl;


	if (l_ok && r_ok) {
		saveCameraParams(s.leftOutputFileName, s, imageSize, l_cameraMatrix, l_distCoeffs, l_rvecs, l_tvecs, l_reprojErrs,
			l_imagePoints, l_totalAvgErr);
		saveCameraParams(s.rightOutputFileName, s, imageSize, r_cameraMatrix, r_distCoeffs, r_rvecs, r_tvecs, r_reprojErrs,
			r_imagePoints, r_totalAvgErr);
	}

	return (l_ok && r_ok);
}

int writeFile_PGM(const char *outfilename,
	Mat image)
{
	FILE *fp;
	int i, j;
	int width, height;
	unsigned char pixel;
	int status = 0;

	width = image.size().width;
	height = image.size().height;

	/***************************************************************************
	* Open the output image file for writing if a filename was given. If no
	* filename was provided, set fp to write to standard output.
	***************************************************************************/
	fopen_s(&fp, (const char*)outfilename, "wb");
			
	/***************************************************************************
	* Write the header information to the PGM file.
	***************************************************************************/
	fprintf(fp, "P5\n%d %d\n", width, height);
	fprintf(fp, "255\n");

	/***************************************************************************
	* Write the image data to the file.
	***************************************************************************/
	for (i = 0; i < height; i++) {
		for (j = 0; j < 3*width; j+=3){
			pixel = image.at<unsigned char>(i, j);
			fwrite(&pixel, 1, 1, fp);
		}
	}

	fclose(fp);
	return status;
}