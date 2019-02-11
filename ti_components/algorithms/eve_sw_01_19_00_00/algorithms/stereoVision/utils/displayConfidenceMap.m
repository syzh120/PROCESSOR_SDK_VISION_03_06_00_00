% /*==========================================================================*/
% /*      Copyright (C) 2009-2015 Texas Instruments Incorporated.             */
% /*                      All Rights Reserved                                 */
% /*==========================================================================*/

function displayConfidenceMap(confFile, width, height)

close all;

fid= fopen(confFile, 'rb');
confidence= fread(fid, [width, height], 'uint16')';
fclose(fid);

confMap= confidence./(max(max(confidence)));
figure('Name','Confidence map');
imshow(confMap);
