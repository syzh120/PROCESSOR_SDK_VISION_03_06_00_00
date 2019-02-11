% /*==========================================================================*/
% /*      Copyright (C) 2009-2015 Texas Instruments Incorporated.             */
% /*                      All Rights Reserved                                 */
% /*==========================================================================*/

% stereoBatchProcess.m
%
% Function that batch processes a dataset of images
%
% Parameters:
% stereoVision_tb_dir: Directory where the PC executables for census + disparity calculation is located. 
% stereoPostproc_tb_dir: Directory where the PC executables for post-processing is located.
% left_dir: input directory to left images, can be *.bmp, *.png or *.pgm. File names in left dir must be identical to file names in right dir.
% right_dir: input directory to right images, can be *.bmp, *.png or *.pgm .File names in left dir must be identical to file names in left dir.
% output_dir: output directory to where raw disparity map in *.ppm format will be written to
% output_post_proc_dir: output directory to where post-processed disparity map in *.ppm format will be written to
function stereoBatchProcess(stereoVision_tb_dir, stereoPostproc_tb_dir, left_dir, right_dir, output_dir, output_postproc_dir),

% Change any of the 5 parameters
% Note that currently census transform window is set to 9x9 and cannot be changed
stereoMode='CENSUS'; % can be set 'SAD'
censusWinWidth= 9; % FIXED - DO NOT CHANGE - Window width for the census window
censusWinHeight= 9; % FIXED - DO NOT CHANGE - Window height for the census window
censusWinHorzStep= 2; % FIXED - DO NOT CHANGE - census horizontal window step
censusWinVertStep= 2; % FIXED - DO NOT CHANGE - census vertical window step

disparityWinWidth= 11; % Window width for the local block matching [5, 7, 9, 11, 13, 15, 17, 19]
disparityWinHeight= 11; % Window height for the local block matching [5, 7, 9, 11, 13, 15, 17, 19]
numDisparities= 128; % Number of disparities to search, [8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 128]
disparityStep= 2; % Step between disparities [1, 2, 4]
searchDir= 0; % 0: left to right, 1: right to left 
lrCheck= 1; % 0: disable, 1: enable

% The 5 parameters below control the post-processing. Note tha
% post-processeing is only effective when stereoMode='CENSUS'
smoothingStrength= 0; % Strength of smoothing [0, 1, 2, 3]. 0 means smoothing disabled. Note that smoothing has not been optimized on the target platform and will result in poor real-time performance (7 fps VGA)
costMaxThreshold= 90; % Used to invalidate disparities based on their normalized cost values. 100%= all disparities are kept irrespective to their cost values.
minConfidenceThreshold= 98; % Used to invalidate disparities based on soem confidence value 100%= all disparities are kept irrespective to their confidence values.
holeFillingStrength= 0; % Strength of hole filling algorithm [0 100]. Recommended values are 0, 1, 2
textureThreshold= 98; % Used to invalidate disparity values based on texture thresholding. This normalized threshold value is in the range [0 100]. Pixels whose texture value is below (100 – textureThreshold) are marked invalid. In other word, if textureThreshold = 100, all pixels are valid and if textureThreshold = 0, all pixels are invalid.
textureLumaLoThresh = 0; % Used to assign texture value of 0 to regions that are too dark. Range [0 100] maps to pixel value of [0 255]. If textureLumaLoThresh=50 then any pixel value below 127 will have its texture value set to 0.
textureLumaHiThresh = 100; % Used to assign texture value of 0 to regions that are too bright. Range [0 100] maps to pixel value of [0 255]. If textureLumaHiThresh=50 then any pixel value above 127 will have its texture value set to 0.
lrMaxDiffThreshold= 3; % Used in left-right check: the maximum disparity difference between the main disparity map and the auxiliary disparity map, which can be tolerated. A large value means a large tolerance. This is used for left right check. Only effective if lrCheck= 1. 
maxDispDissimilarity = 4; % Used in disparity map noise cleaning, based on neighborhood uniformity: the maximum disparity difference between a pixel and its neighbor before starting a new segment. Pixels within a segment have their confidence values examined in order to declare the segment as valid or invalid.
minConfidentNSegment = 6; % Used in disparity map noise cleaning, based on neighborhood uniformity: number of pixels within a segment whose confidence value must exceed minConfidenceThreshold to keep the entire segment as valid.

% Modify stereoVision\test\testvecs\config\config_list.txt
configList_path= [stereoVision_tb_dir, '\test\testvecs\config\config_list.txt'];
fid=fopen(configList_path, 'w');
if (fid==-1)
    fprintf(2, 'Could not create file %s\n', configList_path);
end;
fprintf(fid,'1 ../testvecs/config/batch.cfg');
fprintf(fid,'\n0\n');
fclose(fid);

% create config file for stereoVision_tb
calib_path= [stereoVision_tb_dir, '\test\testvecs\config\batch.cfg'];
fid=fopen(calib_path, 'w');
if (fid==-1)
    fprintf(2, 'Could not create file %s\n', calib_path);
end;
fprintf(fid,'numTestCases = 1\n');
fprintf(fid,'0inImageRight     = "input/TI/right/right.pgm"');
fprintf(fid,'\n0inImageLeft    = "input/TI/left/left.pgm"');
fprintf(fid,'\n0gtScale		 = 1');
fprintf(fid,'\n0stereoMode		 = "%s"', stereoMode);
fprintf(fid,'\n0censusWinWidth  = %d', censusWinWidth);
fprintf(fid,'\n0censusWinHeight = %d', censusWinHeight);
fprintf(fid,'\n0censusWinHorzStep = %d', censusWinHorzStep);
fprintf(fid,'\n0censusWinVertStep = %d', censusWinVertStep);
fprintf(fid,'\n0disparityWinWidth = %d', disparityWinWidth);
fprintf(fid,'\n0disparityWinHeight = %d', disparityWinHeight);
fprintf(fid,'\n0numDisparities = %d', numDisparities);
fprintf(fid,'\n0disparityStep   = %d', disparityStep);
fprintf(fid,'\n0searchDir = %d', searchDir);
fprintf(fid,'\n0lrCheck = %d', 1);
fprintf(fid,'\n0maxMinCostRatio = 1.0');
fprintf(fid,'\n0outImage        = "output/TI/output.pgm"');
fprintf(fid,'\n0pattern         = 1');
fprintf(fid,'\n0disparityOffset= 0');
fclose(fid);

% create config file for stereoVision_tb
calib_path= [stereoPostproc_tb_dir, '\test\testvecs\config\stereovision.cfg'];
fid=fopen(calib_path, 'w');
if (fid==-1)
    fprintf(2, 'Could not create file %s\n', calib_path);
end;
fprintf(fid,'numTestCases = 1\n');
fprintf(fid,'inImageFileName0     = "../testvecs/input/left.pgm"');
fprintf(fid,'\ninCostFileName0    = "../testvecs/input/outputCost.bin"');
fprintf(fid,'\ninDisparityFileName0    = "../testvecs/input/output.pgm"');
if (searchDir== 0)
    fprintf(fid,'\ninAuxDisparityFileName0   = "../testvecs/input/output__rl.pgm"');
else
    fprintf(fid,'\ninAuxDisparityFileName0   = "../testvecs/input/output__lr.pgm"');
end
fprintf(fid,'\noutFileName0    = "../testvecs/output/output_disp.pgm"');
fprintf(fid,'\ninputBitDepth0		 = 8');
fprintf(fid,'\nmaxImageWidth0		 = 1280');
fprintf(fid,'\nmaxImageHeight0		 = 720');
fprintf(fid,'\nmaxFrames0  = 1');
if (searchDir== 0)
    fprintf(fid,'\nstartX0 = %d', 4 + floor(disparityWinWidth/2) + numDisparities - 1);
else
    fprintf(fid,'\nstartX0 = %d', 4 + floor(disparityWinWidth/2));
end
fprintf(fid,'\nstartY0 = %d', 4 + floor(disparityWinHeight/2));
fprintf(fid,'\ncensusWinWidth0  = 9');
fprintf(fid,'\ncensusWinHeight0 = 9');
fprintf(fid,'\ncensusWinHorzStep0 = 2');
fprintf(fid,'\ncensusWinVertStep0 = 2');
fprintf(fid,'\ncostSupportWinWidth0 = %d', disparityWinWidth);
fprintf(fid,'\ncostSupportWinHeight0 = %d', disparityWinHeight);
fprintf(fid,'\nnumDisparities0 = %d', numDisparities);
fprintf(fid,'\ndisparityStep0 = %d', disparityStep);
fprintf(fid,'\nsearchDir0 = %d', searchDir);
fprintf(fid,'\nsmoothingStrength0 = %d', smoothingStrength);
fprintf(fid,'\ndisparityNumFracBits0 = 0');
fprintf(fid,'\ndisparityMinThreshold0 = 0');
fprintf(fid,'\ndisparityMaxThreshold0 = %d', numDisparities);
fprintf(fid,'\ncostMaxThreshold0 = %d', costMaxThreshold);
fprintf(fid,'\nminConfidenceThreshold0 = %d', minConfidenceThreshold);
fprintf(fid,'\nholeFillingStrength0 = %d', holeFillingStrength);
fprintf(fid,'\ntextureLumaLoThresh0 = %d', textureLumaLoThresh);
fprintf(fid,'\ntextureLumaHiThresh0 = %d', textureLumaHiThresh);
fprintf(fid,'\ntextureThreshold0 = %d', textureThreshold);
if (lrCheck== 0)
    fprintf(fid,'\nlrMaxDiffThreshold0 = 255');
else
    fprintf(fid,'\nlrMaxDiffThreshold0 = %d', lrMaxDiffThreshold);
end
fprintf(fid,'\nmaxDispDissimilarity0 = %d', maxDispDissimilarity);
fprintf(fid,'\nminConfidentNSegment0 = %d', minConfidentNSegment);
fclose(fid);

left_sequence = dir(left_dir);
if isempty(left_sequence),
    fprintf(1,'No image found\n');
    return;
end;

right_sequence = dir(right_dir);
if isempty(right_sequence),
    fprintf(1,'No image found\n');
    return;
end;

if (length(left_sequence) ~= length(right_sequence)),
    fprintf(1,'Number of left images different than number of right images, taking the minimum\n');
end;

n_seq= min([length(left_sequence) length(right_sequence)]);
% From this point, the rest of matlab code deals with invoking a PC
% executable called stereoVision_tb, which converts the
% file rectMapLeft_int.bin and rectMapLeft_int.bin into EVE
% format for the remap function.
% The path of the executable is provided through the input parameter stereoVision_tb_dir

disp('Execute stereoVision_tb ... ');

for kk = 3:n_seq,
    
    left_file = left_sequence(kk).name;
    right_file = right_sequence(kk).name;
    
    % This breaks up the input file name (image_file) into the directory (pathstr)
    % the file name without the extention (name) and extention (ext)
    [pathstr, name, ext] = fileparts(left_file);
    % Only performs conversion if correct file types given
    if(ext=='.bmp')
        image_data=imread([left_dir '\' left_file], 'bmp');
        width= size(image_data, 2);
        height= size(image_data, 1);
        fidOut= fopen([stereoVision_tb_dir, '\test\testvecs\input\TI\left\left.pgm'], 'w');
        fprintf(fidOut, 'P5%c%d %d%c255%c', 10, width, height, 10, 10);
        count= fwrite(fidOut, image_data');
        fclose(fidOut);
    elseif(ext=='.png')
        image_data=imread([left_dir '\' left_file], 'png');
        width= size(image_data, 2);
        height= size(image_data, 1);
        fidOut= fopen([stereoVision_tb_dir, '\test\testvecs\input\TI\left\left.pgm'], 'w');
        fprintf(fidOut, 'P5%c%d %d%c255%c', 10, width, height, 10, 10);
        count= fwrite(fidOut, image_data');
        fclose(fidOut);
    elseif (ext=='.pgm')
        copyfile([left_dir '\' left_file],[stereoVision_tb_dir, '\test\testvecs\input\TI\left\left.pgm']);
    end
    
    % This breaks up the input file name (image_file) into the directory (pathstr)
    % the file name without the extention (name) and extention (ext)
    [pathstr, name, ext] = fileparts(right_file);
    % Only performs conversion if correct file types given
    if(ext=='.bmp')
        image_data=imread([right_dir '\' right_file], 'bmp');
        width= size(image_data, 2);
        height= size(image_data, 1);
        fidOut= fopen([stereoVision_tb_dir, '\test\testvecs\input\TI\right\right.pgm'], 'w');
        fprintf(fidOut, 'P5%c%d %d%c255%c', 10, width, height, 10, 10);
        count= fwrite(fidOut, image_data');
        fclose(fidOut);
    elseif(ext=='.png')
        image_data=imread([right_dir '\' right_file], 'png');
        width= size(image_data, 2);
        height= size(image_data, 1);
        fidOut= fopen([stereoVision_tb_dir, '\test\testvecs\input\TI\right\right.pgm'], 'w');
        fprintf(fidOut, 'P5%c%d %d%c255%c', 10, width, height, 10, 10);
        count= fwrite(fidOut, image_data');
        fclose(fidOut);
    elseif (ext=='.pgm')
        copyfile([right_dir '\' right_file],[stereoVision_tb_dir, '\test\testvecs\input\TI\right\right.pgm']);
    end
    
    % Call stereovision
    oldFolder= cd([stereoVision_tb_dir '\test\elf_out']);
    system('test_stereoVision.eve.out.exe');
    cd(oldFolder);
    % Copy output disparity map into output_dir and also into post processing dir
    warning('OFF','MATLAB:MKDIR:DirectoryExists');
    mkdir(output_dir);
    warning('ON','MATLAB:MKDIR:DirectoryExists');
    % Copy output disparity map into output_dir
    copyfile([stereoVision_tb_dir, '\test\testvecs\output\TI\output.ppm'], [output_dir,'\output',num2str(kk-3,'%05d'),'.ppm']);
    copyfile([stereoVision_tb_dir, '\test\testvecs\output\TI\output.pgm'], [output_dir,'\output',num2str(kk-3,'%05d'),'.pgm']);
    % Copy output cost map into output_dir
    copyfile([stereoVision_tb_dir, '\test\testvecs\output\TI\outputCost.bin'], [output_dir,'\outputCost',num2str(kk-3,'%05d'),'.bin']);
   
    disp(' ');
        
    % Copy output disparity map into post processing dir
    copyfile([stereoVision_tb_dir, '\test\testvecs\output\TI\output.pgm'], [stereoPostproc_tb_dir, '\test\testvecs\input']);
    % Copy output disparity map of opposite search direction (right-left) into post processing dir
    if (searchDir== 0)
        copyfile([stereoVision_tb_dir, '\test\testvecs\output\TI\output__rl.pgm'], [stereoPostproc_tb_dir, '\test\testvecs\input']);
    else
        copyfile([stereoVision_tb_dir, '\test\testvecs\output\TI\output__lr.pgm'], [stereoPostproc_tb_dir, '\test\testvecs\input']);
    end
    % Copy output cost map into post processing dir
    copyfile([stereoVision_tb_dir, '\test\testvecs\output\TI\outputCost.bin'], [stereoPostproc_tb_dir, '\test\testvecs\input']);
    % Copy input left file into post processing dir
    copyfile([stereoVision_tb_dir, '\test\testvecs\input\TI\left\left.pgm'],[stereoPostproc_tb_dir, '\test\testvecs\input']);
    % Copy input left or right file into post processing dir, depending on
    % search direction
    if (searchDir== 0)
        copyfile([stereoVision_tb_dir, '\test\testvecs\input\TI\left\left.pgm'],[stereoPostproc_tb_dir, '\test\testvecs\input']);
    else
        copyfile([stereoVision_tb_dir, '\test\testvecs\input\TI\right\right.pgm'],[stereoPostproc_tb_dir, '\test\testvecs\input']);
    end
    
    % Call post-process stereovision
    oldFolder= cd([stereoPostproc_tb_dir '\test\out']);
    system('test_stereovision_algo.out.exe');
    cd(oldFolder);
    % Copy output disparity map into output_dir for post processing
    warning('OFF','MATLAB:MKDIR:DirectoryExists');
    mkdir(output_postproc_dir);
    warning('ON','MATLAB:MKDIR:DirectoryExists');
    % Copy disparity map into output_dir
    copyfile([stereoPostproc_tb_dir, '\test\testvecs\output\output_disp.ppm'], [output_postproc_dir,'\output',num2str(kk-3,'%05d'),'.ppm']);
    % Copy confidence map into output_dir
    copyfile([stereoPostproc_tb_dir, '\test\testvecs\output\output_dispConf.bin'], [output_postproc_dir,'\output',num2str(kk-3,'%05d'),'Conf.bin']);
    % Copy texture map into output_dir
    copyfile([stereoPostproc_tb_dir, '\test\testvecs\output\output_dispText.pgm'], [output_postproc_dir,'\output',num2str(kk-3,'%05d'),'Text.pgm']);
end;



