function imgRgb = yuv2rgb(infile, height, width, yuvtype, outfileformat)
%load YUV image, convert to RGB image and save RGB image to file.
%
%  imgRgb = yuv2rgb(infile, height, width,...
%                           [yuvtype='420sp'], [outfileformat='png'])
%
%INPUT
% - infile: string, path to yuv input file
% - height: integer, image height
% - width: integer, image width
% - yuvtype: string, '420p', '420sp' or '422i', Default: '420sp'
% - outfileformat: string, any RGB extension that works with imwrite, e.g.,
%                  'png','bmp', Default: 'png'
%                   If outfileformat=[], output is not saved to file
%
%OUTPUT
% - imgRgb: uint8 RGB image
%
%   imgRgb is saved to file in the same folder as infile, if outfileformat~=[]


if nargin < 5
    outfileformat = 'png';
    if nargin < 4
        yuvtype = '420sp';
    end
end

fileId = fopen(infile, 'rb');

if strcmp(yuvtype,'420p')
%% 420p
    subSampleMat = [1, 1; 1, 1];
    % read Y component
    buf = fread(fileId, width * height, 'uchar');
    imgYuv(:, :, 1) = reshape(buf, width, height).'; % reshape
    % read U component
    buf = fread(fileId, width / 2 * height / 2, 'uchar');
    imgYuv(:, :, 2) = kron(reshape(buf, width / 2, height / 2).', subSampleMat); % reshape and upsample
    % read V component
    buf = fread(fileId, width / 2 * height / 2, 'uchar');
    imgYuv(:, :, 3) = kron(reshape(buf, width / 2, height / 2).', subSampleMat); % reshape and upsample

elseif strcmp(yuvtype,'420sp')
%% 420sp
    subSampleMat = [1, 1; 1, 1];
    % read Y component
    buf = fread(fileId, width*height, 'uchar');
    imgYuv(:, :, 1) = reshape(buf, width, height).'; % reshape
    % read U and V component
    bufUV = fread(fileId, (width*height)/2, 'uchar');
    bufU = zeros((width*height)/4,1);
    bufV = zeros((width*height)/4,1);
    cnt = 0;
    for a=1:2:width*height/2-1
        cnt = cnt + 1;
        bufU(cnt,1) = bufUV(a,1);
        bufV(cnt,1) = bufUV(a+1,1);
    end
    imgYuv(:, :, 2) = kron(reshape(bufU, width / 2, height / 2).', subSampleMat); % reshape and upsample
    imgYuv(:, :, 3) = kron(reshape(bufV, width / 2, height / 2).', subSampleMat); % reshape and upsample

elseif strcmp(yuvtype,'422i')
%% 422i
    subSampleMat = [1, 1];
    % read Y, U and V component
    bufYUV = fread(fileId, width*height*2, 'uchar');
    bufY = zeros((width*height),1);
    bufU = zeros((width*height)/2,1);
    bufV = zeros((width*height)/2,1);
    cnt = 0;
    for a=1:2:width*height*2-1
        cnt = cnt + 1;
        bufY(cnt,1) = bufYUV(a,1);
    end
    cnt = 0;
    for a=1:4:width*height*2-3
        cnt = cnt + 1;
        %     bufY(cnt,1) = bufYUV(a,1);
        %     cnt = cnt + 1;
        %     bufY(cnt,1) = bufYUV(a+2,1);
        bufU(cnt,1) = bufYUV(a+1,1);
        bufV(cnt,1) = bufYUV(a+3,1);
    end
    imgYuv(:, :, 1) = reshape(bufY, width, height).'; % reshape
    imgYuv(:, :, 2) = kron(reshape(bufU, width / 2, height).', subSampleMat); % reshape and upsample
    imgYuv(:, :, 3) = kron(reshape(bufV, width / 2, height).', subSampleMat); % reshape and upsample
else
    disp(['ERROR: yuvtype ' yuvtype ' not known. Abort.'])
end

fclose(fileId);
% convert YUV to RGB
imgRgb = reshape(convertYuvToRgb(reshape(imgYuv, height * width, 3)), height, width, 3);

if ~isempty(outfileformat)
    imwrite(imgRgb, [infile(1:end-3) outfileformat]);
end

end

function rgb = convertYuvToRgb(yuv)
% convert row vector YUV [0, 255] in row vector RGB [0, 255]
yuvToRgb =    [1.0000  1.0000 1.0000 ;
               0.0000  -0.3456 1.7710 ;
               1.4022  -0.7145  0.0000];
yuv = double(yuv);
yuv(:, 2 : 3) = yuv(:, 2 : 3) - 127;
%rgb = (yuvToRgb *yuv.').';
rgb = yuv * yuvToRgb;
rgb = uint8(clipLocal(rgb, 0, 255));
end

function in = clipLocal(in, valMin, valMax)
% clip IN at minimum Value VALMIN and maximum value VALMAX
%
%   OUT = clip(IN, VALMIN, VALMAX)
in(in<valMin) = valMin;
in(in>valMax) = valMax;
end
