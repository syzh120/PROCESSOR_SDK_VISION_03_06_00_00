
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 %      (C) Copyright 2017 Texas Instruments, Inc.
 %
 %  Redistribution and use in source and binary forms, with or without
 %  modification, are permitted provided that the following conditions
 %  are met:
 %
 %    Redistributions of source code must retain the above copyright
 %    notice, this list of conditions and the following disclaimer.
 %
 %    Redistributions in binary form must reproduce the above copyright
 %    notice, this list of conditions and the following disclaimer in the
 %    documentation and/or other materials provided with the
 %    distribution.
 %
 %    Neither the name of Texas Instruments Incorporated nor the names of
 %    its contributors may be used to endorse or promote products derived
 %    from this software without specific prior written permission.
 %
 %  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 %  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 %  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 %  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 %  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 %  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 %  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 %  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 %  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 %  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 %  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Load calibration coefficients
%It is a matrix of size:  number_of_virtual_antennas X number of recorded frames
load CC

%plot to visually check that all frames have the same pattern
figure
plot(unwrap(angle(CC)))



%save the first frame to binary file, (imaginary value goes first)
cc1 = CC(:,end);
cc1 = [imag(cc1) real(cc1)];
cc1 = cc1.';
cc1=cc1(:);

for kk = 1:2:length(cc1)
    fprintf('{%.7f, %.7f},\n', cc1(kk), cc1(kk+1));
end


fid = fopen('calib_coef.bin','wb');
fwrite(fid, cc1, 'single');
fclose(fid);

