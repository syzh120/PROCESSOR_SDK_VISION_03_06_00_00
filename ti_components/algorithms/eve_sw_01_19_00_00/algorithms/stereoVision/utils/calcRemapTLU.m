% /*==========================================================================*/
% /*      Copyright (C) 2009-2015 Texas Instruments Incorporated.             */
% /*                      All Rights Reserved                                 */
% /*==========================================================================*/

function [px_0, py_0] = calcRemapTLU(I,R,f,c,k,alpha,KK_new,qFactor);


if nargin < 5,
   k = [0;0;0;0;0];
   if nargin < 4,
      c = [0;0];
      if nargin < 3,
         f = [1;1];
         if nargin < 2,
            R = eye(3);
            if nargin < 1,
               error('ERROR: Need an image to rectify');
               %break;
            end;
         end;
      end;
   end;
end;


if nargin < 7,
   if nargin < 6,
		KK_new = [f(1) 0 c(1);0 f(2) c(2);0 0 1];
   else
   	KK_new = alpha; % the 6th argument is actually KK_new   
   end;
   alpha = 0;
end;



% Note: R is the motion of the points in space
% So: X2 = R*X where X: coord in the old reference frame, X2: coord in the new ref frame.


if ~exist('KK_new'),
   KK_new = [f(1) alpha_c*fc(1) c(1);0 f(2) c(2);0 0 1];
end;


[nr,nc] = size(I);

Irec = 255*ones(nr,nc);

[mx,my] = meshgrid(1:nc, 1:nr);
px = reshape(mx',nc*nr,1);
py = reshape(my',nc*nr,1);

rays = inv(KK_new)*[(px - 1)';(py - 1)';ones(1,length(px))];


% Rotation: (or affine transformation):

rays2 = R'*rays;

x = [rays2(1,:)./rays2(3,:);rays2(2,:)./rays2(3,:)];


% Add distortion:
xd = apply_distortion(x,k);


% Reconvert in pixels:

px2 = f(1)*(xd(1,:)+alpha*xd(2,:))+c(1);
py2 = f(2)*xd(2,:)+c(2);


% Interpolate between the closest pixels:

px_0 = floor(px2.*qFactor);
py_0 = floor(py2.*qFactor);



return;

