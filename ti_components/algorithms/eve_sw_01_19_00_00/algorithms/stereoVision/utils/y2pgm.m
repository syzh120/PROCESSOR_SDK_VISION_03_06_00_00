% /*==========================================================================*/
% /*      Copyright (C) 2009-2015 Texas Instruments Incorporated.             */
% /*                      All Rights Reserved                                 */
% /*==========================================================================*/

function y2pgm(seq_name, format_image_seq, width, height),

if isempty(format_image_seq),
    format_image_seq = 'yuv';
else
    if lower(format_image_seq(1)) == 'y',
        format_image_seq = 'yuv';
    else
        if lower(format_image_seq(1)) == 'b',
            format_image_seq = 'bin';
        else
            disp('Invalid image format');
            return;
        end;
    end;
end;

ima_sequence = dir( [ seq_name '*.' format_image_seq]);

if isempty(ima_sequence),
    fprintf(1,'No image found\n');
    return;
end;

n_seq = length(ima_sequence);

for kk = 1:n_seq,
    
    ima_name = ima_sequence(kk).name;
    ima_name2 = [ima_name(1:end-3), 'pgm'];
    fprintf(1,'Loading original image %s ...\n',ima_name);
    fidIn= fopen(ima_name, 'r');
    fidOut= fopen(ima_name2, 'w');
    fprintf(fidOut, 'P5%c%d %d%c255%c', 10, width, height, 10, 10);
    A= fread(fidIn);
    fprintf(1,'Saving pgm image under %s ...\n\n',ima_name2);
    count= fwrite(fidOut, A);
    fclose(fidIn);
    fclose(fidOut);
    
end;