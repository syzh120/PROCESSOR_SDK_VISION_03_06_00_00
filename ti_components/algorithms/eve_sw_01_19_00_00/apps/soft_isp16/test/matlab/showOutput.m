clear;

W=1280;
H=720;
fid=fopen('../testvecs/output/output_gbrg.raw');
I=fread(fid,[W, 3*H],'uint16')';
fclose(fid);
Ifloat= I./max(max(I));
Irgb=zeros([H W 3]);
Irgb(:,:,1)= Ifloat(1:H, 1:end);
Irgb(:,:,2)= Ifloat(H+1:2*H, 1:end);
Irgb(:,:,3)= Ifloat(2*H+1:3*H, 1:end);
figure;imshow(Irgb); title('gbrg');

W=1280;
H=720;
fid=fopen('../testvecs/output/output_grbg.raw');
I=fread(fid,[W, 3*H],'uint16')';
fclose(fid);
Ifloat= I./max(max(I));
Irgb=zeros([H W 3]);
Irgb(:,:,1)= Ifloat(1:H, 1:end);
Irgb(:,:,2)= Ifloat(H+1:2*H, 1:end);
Irgb(:,:,3)= Ifloat(2*H+1:3*H, 1:end);
figure;imshow(Irgb); title('grbg');

W=1280;
H=720;
fid=fopen('../testvecs/output/output_bggr.raw');
I=fread(fid,[W, 3*H],'uint16')';
fclose(fid);
Ifloat= I./max(max(I));
Irgb=zeros([H W 3]);
Irgb(:,:,1)= Ifloat(1:H, 1:end);
Irgb(:,:,2)= Ifloat(H+1:2*H, 1:end);
Irgb(:,:,3)= Ifloat(2*H+1:3*H, 1:end);
figure; imshow(Irgb); title('bggr');

W=1280;
H=720;
fid=fopen('../testvecs/output/output_rggb.raw');
I=fread(fid,[W, 3*H],'uint16')';
fclose(fid);
Ifloat= I./max(max(I));
Irgb=zeros([H W 3]);
Irgb(:,:,1)= Ifloat(1:H, 1:end);
Irgb(:,:,2)= Ifloat(H+1:2*H, 1:end);
Irgb(:,:,3)= Ifloat(2*H+1:3*H, 1:end);
figure;imshow(Irgb); title('rggb');