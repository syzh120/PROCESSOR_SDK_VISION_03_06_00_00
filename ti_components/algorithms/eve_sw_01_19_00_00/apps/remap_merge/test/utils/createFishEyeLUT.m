%==========================================================================
%      Copyright (C) 2009-2015 Texas Instruments Incorporated.             
%                      All Rights Reserved                                 
%==========================================================================
% This script generates the LUT corresponding to a fish-eye geometric
% transformation. 

% qFactor is scaling factor to increase precision
qFactor= 4;
% A checkerboard will be generated in order to illustrate
% the effect of the fish-eye transform.
% The checkerboard will have 2 * NC squares horizontally
% and 2 * NR squares vertically.
% Each square is of dimension NPIX * NPIX pixels
%NC=20; 
%NR=10;
NC=4; 
NR=2;
NPIX=32;

% Create image pattern consisting of a checker board
I=checkerboard(NPIX,NR,NC);
subplot(2,1,1);

% Show the checkerboard
imshow(I);
title('original image');
[nr,nc]=size(I);

Icolor= zeros(2*nc, nr);
Icolor(2:2:end,:)= I'.*255;
Icolor(1:4:end/2,:)= 84;
Icolor(3:4:end/2,:)= 255;

filepath=['../testvecs/input/checkerboard_gray_', num2str(NC*NPIX*2),'x',num2str(NR*NPIX*2)];
% Save checker board in pgm format
fidOut= fopen([filepath, '.pgm'], 'w');
fprintf(fidOut, 'P5%c%d %d%c255%c', 10, NPIX*NC*2, NPIX*NR*2, 10, 10);
count= fwrite(fidOut, I'.*255);
fclose(fidOut);

% Save checker board in y format
fidOut= fopen([filepath, '.yuv'], 'w');
count= fwrite(fidOut, I'.*255);
fclose(fidOut);

filepath=['../testvecs/input/checkerboard_color_', num2str(NC*NPIX*2),'x',num2str(NR*NPIX*2)];
% Save checker board in yuv format
fidOut= fopen([filepath, '.yuv'], 'w');
count= fwrite(fidOut, Icolor);
fclose(fidOut);

% Create coordinate grid, which will be used to map the pixels
% to a fish-eye model.
[mx,my] = meshgrid(1:nc, 1:nr);
mx = reshape(mx',1,nc*nr);
my = reshape(my',1,nc*nr);

cenx= nc/2;
ceny= nr/2;
% Normalize x & y between -1 and 1
normx= ((mx - cenx)./(nc/2));
normy= ((my - ceny)./(nr/2));

% Calculate radius r
r = sqrt(normx.^2 + normy.^2);

% Set radis r >1 to 1
r(r>=1)=1;

% Apply fish-eye distortion by calculating new r value using special equation 
newr= sqrt(1-r.*r);
newr= (r+(1.0-newr))./2.0;

% calculate the angle for polar coordinate
theta= atan2(normy, normx);
% calculate new x position with new distance in same angle
x= newr.*cos(theta);
% calculate new y position with new distance in same angle
y= newr.*sin(theta);
% map from -1 ... 1 to image coordinates
x = (x+1).*nc/2; 
y = (y+1).*nr/2;

% Apply the scaling factor
x=floor(x.*qFactor);
y=floor(y.*qFactor);

% Correct coordinates if they fall outside of the input image
x(x < 0)=0;
x(x >= qFactor*nc)= qFactor*nc - 1;
y(y < 0)=0;
y(y >= qFactor*nr)= qFactor*nr -1;

% Interleave x,y before saving to a file
xy=zeros(1,size(x,2)*2);
xy(1:2:end)= x;
xy(2:2:end)= y;

% Save LUT in binary format
filepath=['../testvecs/input/fishEyeMap', num2str(NC*NPIX*2),'x',num2str(NR*NPIX*2)];
fid=fopen([filepath, '.bin'],'wb');
fwrite(fid, xy, 'uint32');
fclose(fid);

% Save LUT in txt format
fid=fopen([filepath, '.txt']','w');
fprintf(fid, '    %d, %d,\n', xy);
fclose(fid);

% Save LUT in dat format
fid=fopen([filepath, '.dat'],'w');
fprintf(fid, '    %d %d\n', xy);
fclose(fid);

% Calculate ind, which will be used for visualization
ind= uint32(floor((x./qFactor)) + floor(y./qFactor)*nc) + 1;

% For visualization, we apply the fish-eye model. We use simple nearest-neighbour
% as example.
J=reshape(I',[1 size(I,1)*size(I,2)]);
K=J(ind);
L=reshape(K',[size(I,2) size(I,1)])';

% Show the distorted checker board
subplot(2,1,2);
imshow(L);
title('Remapped image using nearest neighbour interpolation');
