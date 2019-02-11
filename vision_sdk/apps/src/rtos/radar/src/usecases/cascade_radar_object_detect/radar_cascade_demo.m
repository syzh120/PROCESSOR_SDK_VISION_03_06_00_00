
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
%tgt_ip_addr : Target IP Address
%host_ip_addr: Host IP Address
%host_mac_addr: Host MAC Address
%platform: 'CUSTOM' or 'TI' platform

%usage: radar_cascade_demo('128.247.75.78', '128.247.75.131', 'aa-bb-cc-dd-00-11', 'TI', RangeDepthInMeters, profileNum);
function [] = radar_cascade_demo(tgt_ip_addr, host_ip_addr, host_mac_address, platform, range_depth, profileNum)
    global EXIT_KEY_PRESSED
    global tcpCmdSock
    global udpSock
    global figHnd
    global dataSize
    global dataArray
    global DEBUG_RANDOM_POINTS

    VERBOSE = 0;
    PLOT_STATIC_HEATMAP = 1;
    PLOT_POINT_CLOUD = 1;

    OP_SECTION_DATATYPE_DETECTED_POINTS = 1;
    OP_SECTION_DATATYPE_RANGE_PROFILE   = 2;
    OP_SECTION_DATATYPE_AZIMUT_STATIC_HEAT_MAP = 3;
    OP_SECTION_DATATYPE_RANGE_DOPPLER_HEAT_MAP = 4;
    OP_SECTION_DATATYPE_SYSTEM_INFO = 5;
    OP_SECTION_DATATYPE_CALIBRATION_COEFFS = 6;
    OP_SECTION_DATATYPE_NOISE_PROFILE   = 7;

    ELEV_VIEW = 2;
    DEBUG_RANDOM_POINTS = 0;

    Params.platform = platform;
    Params.fCarrier = 77e9;

    if ischar(profileNum)
        profileNum = str2num(profileNum);
    end

    if (profileNum == 1)
        %MIMO - 8 Tx Profile
        % chirpPeriod = <Idle time in seconds> <ramp end time in seconds>
        Params.chirpPeriod = 5e-6 + 40e-6;
        % Fsamp = sampling rate in sampless per second
        Params.Fsamp = 8e6;
        % freqSlope = Frequency slope in Hz per second.
        Params.freqSlope = 79e12;
    elseif (profileNum == 2)
        %BF Profile
        % chirpPeriod = <Idle time in seconds> <ramp end time in seconds>
        Params.chirpPeriod = 5e-6 + 35e-6;
        % Fsamp = sampling rate in sampless per second
        Params.Fsamp = 9e6;
        % freqSlope = Frequency slope in Hz per second.
        Params.freqSlope = 2529e14;
    elseif (profileNum == 3)
        %SRR Profile
        % chirpPeriod = <Idle time in seconds> <ramp end time in seconds>
        Params.chirpPeriod = 23e-6; %3e-6 + 56e-6;
        % Fsamp = sampling rate in sampless per second
        Params.Fsamp = 16e6;
        % freqSlope = Frequency slope in Hz per second.
        Params.freqSlope = 8.43*4e12;
        elseif (profileNum == 3)
        %SRR Profile
        % chirpPeriod = <Idle time in seconds> <ramp end time in seconds>
        Params.chirpPeriod = 40e-6; %3e-6 + 56e-6;
        % Fsamp = sampling rate in sampless per second
        Params.Fsamp = 9e6;
        % freqSlope = Frequency slope in Hz per second.
        Params.freqSlope = 8.43*3e12;
    else
        fprintf('Profile number %d not supported!\n', profileNum);
        return;
    end

    if strcmp(Params.platform, 'TI')
        % Params
        Params.numSensor = 4;
        Params.numRxAntPerSensor = 4;
        Params.numTxAzimAnt = 5;
        Params.numTxElevAnt = 3;
        Params.numTxAnt = Params.numTxAzimAnt + Params.numTxElevAnt;
        Params.numVirtualAnt = (Params.numTxAnt )...
                                 * Params.numRxAntPerSensor * Params.numSensor;
        Params.numRangeBins = 256;
        Params.numDopplerBins = 64;
        Params.numAzimuthBins = 128;
        Params.numElevBins = 64;
        Params.azimuthRowLength = 86;
    elseif strcmp(Params.platform, 'TI1DEV')
        % Params
        Params.numSensor = 1;
        Params.numRxAntPerSensor = 4;
        Params.numTxAzimAnt = 0;
        Params.numTxElevAnt = 3;
        Params.numTxAnt = Params.numTxAzimAnt + Params.numTxElevAnt;
        Params.numVirtualAnt = (Params.numTxAnt )...
                                 * Params.numRxAntPerSensor * Params.numSensor;
        Params.numRangeBins = 256;
        Params.numDopplerBins = 64;
        Params.numAzimuthBins = 128;
        Params.numElevBins = 64;
        Params.azimuthRowLength = 86;
    elseif strcmp(Params.platform, 'TI5ANT')
        % Params
        Params.numSensor = 4;
        Params.numRxAntPerSensor = 4;
        Params.numTxAzimAnt = 5;
        Params.numTxElevAnt = 0;
        Params.numTxAnt = Params.numTxAzimAnt + Params.numTxElevAnt;
        Params.numVirtualAnt = (Params.numTxAnt )...
                                 * Params.numRxAntPerSensor * Params.numSensor;
        Params.numRangeBins = 256;
        Params.numDopplerBins = 32;
        Params.numAzimuthBins = 128;
        Params.numElevBins = 64;
        Params.azimuthRowLength = 86;
    elseif strcmp(Params.platform, 'TI9ANT')
        % Params
        Params.numSensor = 4;
        Params.numRxAntPerSensor = 4;
        Params.numTxAzimAnt = 6;
        Params.numTxElevAnt = 3;
        Params.numTxAnt = Params.numTxAzimAnt + Params.numTxElevAnt;
        Params.numVirtualAnt = (Params.numTxAnt )...
                                 * Params.numRxAntPerSensor * Params.numSensor;
        Params.numRangeBins = 256;
        Params.numDopplerBins = 32;
        Params.numAzimuthBins = 128;
        Params.numElevBins = 64;
        Params.azimuthRowLength = 86;
    elseif strcmp(Params.platform, 'TIBF')
        % Params
        Params.numSensor = 4;
        Params.numRxAntPerSensor = 4;
        Params.numTxAzimAnt = 1;
        Params.numTxElevAnt = 0;
        Params.numTxAnt = Params.numTxAzimAnt + Params.numTxElevAnt;
        Params.numVirtualAnt = (Params.numTxAnt )...
                                 * Params.numRxAntPerSensor * Params.numSensor;
        Params.numRangeBins = 256;
        Params.numDopplerBins = 128;
        Params.numAzimuthBins = 128;
        Params.numElevBins = 64;
        Params.azimuthRowLength = 86;
    elseif strcmp(Params.platform, 'TI10ANT')
        % Params
        Params.numSensor = 4;
        Params.numRxAntPerSensor = 4;
        Params.numTxAzimAnt = 7;
        Params.numTxElevAnt = 3;
        Params.numTxAnt = Params.numTxAzimAnt + Params.numTxElevAnt;
        Params.numVirtualAnt = (Params.numTxAnt )...
                                 * Params.numRxAntPerSensor * Params.numSensor;
        Params.numRangeBins = 256;
        Params.numDopplerBins = 128;
        Params.numAzimuthBins = 256;
        Params.numElevBins = 64;
        Params.azimuthRowLength = 86;
    else        
        fprintf('Platform %s is not supported!\n', Params.platform);
    end
    [Params] = aoaInitLookupTable (Params);
    %Init more parameters
    Params.dopplerResolutionMps = 3e8/(2 * Params.fCarrier * Params.chirpPeriod * Params.numTxAnt * Params.numDopplerBins);
    Params.rangeIdxToMeters = 3e8 * Params.Fsamp/ (2 * Params.freqSlope * Params.numRangeBins);

    %Init GUI plotting flags
    qqParams.gui.cloudPoints = 1;
    Params.gui.rangeProfile = 1;
    Params.gui.azimHeatMap = 1;
    Params.gui.rangeDopplerHeatMap = 1;


    if ischar(range_depth)
        range_depth = str2num(range_depth);
    end
    range_width = range_depth/2;
    % Setup the figure
    figHandle = figure(1);
    clf(figHandle);
    set(figHandle, 'WindowStyle','normal');
    set(figHandle,'Name','Texas Instruments - Cascade demo','NumberTitle','off')

    set(figHandle,'currentchar',' ')         % set a dummy character

    warning off MATLAB:HandleGraphics:ObsoletedProperty:JavaFrame
    jframe=get(figHandle,'javaframe');
    jIcon=javax.swing.ImageIcon('texas_instruments.gif');
    jframe.setFigureIcon(jIcon);
    %set(figHnd, 'MenuBar', 'none');
    set(figHandle, 'Color', [0.8 0.8 0.8]);
    set(figHandle, 'KeyPressFcn', @myKeyPressFcn,'Interruptible','on')
    set(figHandle,'ResizeFcn',@Resize_clbk,'Interruptible','on');
    pause(0.00001);
    set(jframe,'Maximized',1);
    pause(0.00001);




    %Cloud points
    figCloudPoint.position = [0 1/2 .5 .5];
    figCloudPoint.hTabGroup = uitabgroup(figHandle, 'Position', figCloudPoint.position);
    figCloudPoint.htab1 = uitab(figCloudPoint.hTabGroup, 'Title', 'Cloud Points');
    figCloudPoint.hax1 = axes('Parent', figCloudPoint.htab1);
    figCloudPoint.hplotLen = 2;
    figCloudPoint.hplotInd = 1;
    xx=zeros(2,figCloudPoint.hplotLen);
    yy=zeros(2,figCloudPoint.hplotLen);
    zz=zeros(2,figCloudPoint.hplotLen);

    figCloudPoint.hplot = plot3(figCloudPoint.hax1, xx,yy,zz,'b.','MarkerSize',10);

    hold on
    figCloudPoint.hplot_yAxis = plot3(figCloudPoint.hax1,[0 0],[0 range_depth],[0 0],'-r');
    figCloudPoint.hplot_xAxis = plot3(figCloudPoint.hax1,[-range_width range_width],[0 0],[0 0],'-r');
    figCloudPoint.hplot_zAxis = plot3(figCloudPoint.hax1,[0 0],[0 0],[-range_width range_width],'-r');
    figCloudPoint.hplot_000 = plot3(figCloudPoint.hax1,0,0,0,'ro','MarkerSize',5);
    grid on
    set(figCloudPoint.hax1,'XLim',[-range_width range_width]);
    set(figCloudPoint.hax1,'YLim',[0 range_depth]);
    set(figCloudPoint.hax1,'ZLim',[-range_width range_width]);
    xlabel('meters');
    ylabel('meters');
    title('3D Scatter Plot')
    axis(figCloudPoint.hax1,'equal');
    set(figCloudPoint.hax1, 'XLimMode', 'manual');
    set(figCloudPoint.hax1, 'YLimMode', 'manual');
    set(figCloudPoint.hax1, 'ZLimMode', 'manual');
    %view([41 21]);%ELEV_VIEW);
    view(ELEV_VIEW);

    %rotate3d on

    %Range/Doppler Group
    figRangeDoppler.hTabGroup = uitabgroup(figHandle, 'Position', [0 0 .5 .5]);

    %Range/Doppler points
    figRangeDoppler.htab1 = uitab(figRangeDoppler.hTabGroup, 'Title', 'Range-Doppler points');
    figRangeDoppler.hax1 = axes('Parent', figRangeDoppler.htab1);
    figRangeDoppler.hplot_00 = plot(figRangeDoppler.hax1, 0,0,'Color',[0 0 0.5]);
    hold on
    set(figRangeDoppler.hax1, 'Color', [0 0 0.5]);
    dopplerRange = Params.dopplerResolutionMps * Params.numDopplerBins / 2;
    axis(figRangeDoppler.hax1, [0 range_depth -Params.numTxAnt*dopplerRange Params.numTxAnt*dopplerRange])
    xlabel(figRangeDoppler.hax1,'Range (meters)');
    ylabel(figRangeDoppler.hax1,'Doppler (m/s)');
    title(figRangeDoppler.hax1,'Doppler-Range Plot')
    grid on;
    set(figRangeDoppler.hax1,'Xcolor',[0.5 0.5 0.5]);
    set(figRangeDoppler.hax1,'Ycolor',[0.5 0.5 0.5]);
    figRangeDoppler.hplot1 = plot(figRangeDoppler.hax1, 0,0,'g.', 'Marker', '.','MarkerSize',15);
    set(figRangeDoppler.hplot1, 'Xdata', rand(10,1), 'Ydata', rand(10,1));

    if (Params.gui.rangeDopplerHeatMap)
        %Range/Doppler Heatmap
        figRangeDoppler.htab2 = uitab(figRangeDoppler.hTabGroup, 'Title', 'Range-Doppler Heatmap');
        figRangeDoppler.hax2 = axes('Parent', figRangeDoppler.htab2);

        figRangeDoppler.hPlot2 = surf(Params.rangeIdxToMeters*[0:Params.numRangeBins-1],...
                Params.dopplerResolutionMps*[-Params.numDopplerBins/2:Params.numDopplerBins/2-1],...
                zeros(Params.numDopplerBins, Params.numRangeBins));


        axis(figRangeDoppler.hax2, [0 range_depth -dopplerRange dopplerRange]);
        xlabel(figRangeDoppler.hax2,'Range (meters)');
        ylabel(figRangeDoppler.hax2,'Doppler (m/s)');
        title(figRangeDoppler.hax2,'Doppler-Range Heatmap')
        shading interp
        view(2);

        %Range/Doppler profiles
        figRangeDoppler.htab3 = uitab(figRangeDoppler.hTabGroup, 'Title', 'Range-Doppler Profiles');
        figRangeDoppler.hax3 = axes('Parent', figRangeDoppler.htab3);

        %figRangeDoppler.hPlot3 = plot(figRangeDoppler.hax3, (0:Params.numRangeBins-1), num2cell(zeros(Params.numRangeBins,Params.numDopplerBins),2));
        figRangeDoppler.hPlot3 = plot(figRangeDoppler.hax3, (0:Params.numRangeBins-1)*Params.rangeIdxToMeters, zeros(Params.numRangeBins,Params.numDopplerBins));


        xlabel(figRangeDoppler.hax3,'Range (meters)');
        ylabel(figRangeDoppler.hax3,'Magnitude squared');
        title(figRangeDoppler.hax3,'Range-Doppler Profiles')
        axis(figRangeDoppler.hax3, [0  Params.numRangeBins*Params.rangeIdxToMeters 10 120]);
        set(figRangeDoppler.hax3, 'YLimMode', 'manual');

    end



    %Range profile
    if (Params.gui.rangeProfile)
        figRangeProfile.position = [0.5 0.5 .5 .5];
        figRangeProfile.hTabGroup = uitabgroup(figHandle, 'Position', figRangeProfile.position);
        figRangeProfile.htab1 = uitab(figRangeProfile.hTabGroup, 'Title', 'Range Profile');
        figRangeProfile.hax1 = axes('Parent', figRangeProfile.htab1);
        figRangeProfile.hplot = plot(figRangeProfile.hax1, [0:Params.numRangeBins-1], zeros(Params.numRangeBins,1));
        xlabel(figRangeProfile.hax1,'Range index');
        axis(figRangeProfile.hax1, [0 Params.numRangeBins 10 120]);
        set(figRangeProfile.hax1, 'YLimMode', 'manual');
    end

    if (Params.gui.azimHeatMap)
        %Azimuth Heatmap
        figAzimuthHeatmap.position = [0.5 0 .5 .5];
        figAzimuthHeatmap.hTabGroup = uitabgroup(figHandle, 'Position', figAzimuthHeatmap.position);
        figAzimuthHeatmap.htab1 = uitab(figAzimuthHeatmap.hTabGroup, 'Title', 'Azimuth Heatmap');
        figAzimuthHeatmap.hax1 = axes('Parent', figAzimuthHeatmap.htab1);

        figAzimuthHeatmap.theta = asind([-Params.numAzimuthBins/2+1 : Params.numAzimuthBins/2-1]'*(2/Params.numAzimuthBins));
        figAzimuthHeatmap.range = [0:Params.numRangeBins-1] * Params.rangeIdxToMeters;
        figAzimuthHeatmap.posX = figAzimuthHeatmap.range' * sind(figAzimuthHeatmap.theta');
        figAzimuthHeatmap.posY = figAzimuthHeatmap.range' * cosd(figAzimuthHeatmap.theta');
        figAzimuthHeatmap.xlin=linspace(-range_width,range_width,200);
        figAzimuthHeatmap.ylin=linspace(0,range_depth,200);
        [figAzimuthHeatmap.X,figAzimuthHeatmap.Y]=meshgrid(figAzimuthHeatmap.xlin, figAzimuthHeatmap.ylin);
        QQ = zeros(Params.numRangeBins, Params.numAzimuthBins -1);
        warning off
        Z=griddata(figAzimuthHeatmap.posX,figAzimuthHeatmap.posY, QQ, figAzimuthHeatmap.X,figAzimuthHeatmap.Y,'linear');
        warning on
        figAzimuthHeatmap.hPlot = surf(figAzimuthHeatmap.xlin, figAzimuthHeatmap.ylin, Z);
        shading interp
        view(ELEV_VIEW);
        set(figAzimuthHeatmap.hax1,'Color',[0 0 0.5]);
        axis(figAzimuthHeatmap.hax1, 'equal')
        axis(figAzimuthHeatmap.hax1, [-range_width range_width 0 range_depth])
        xlabel(figAzimuthHeatmap.hax1, 'Distance along lateral axis (meters)');
        ylabel(figAzimuthHeatmap.hax1, 'Distance along longitudinal axis (meters)');
        title(figAzimuthHeatmap.hax1, 'Azimuth-Range Heatmap')

        figAzimuthHeatmap.htab2 = uitab(figAzimuthHeatmap.hTabGroup, 'Title', 'Azimuth FFT out Debug');
        figAzimuthHeatmap.hax2 = axes('Parent', figAzimuthHeatmap.htab2);
        figAzimuthHeatmap.hPlot2 = plot(figAzimuthHeatmap.hax2, [-Params.numAzimuthBins/2+1:Params.numAzimuthBins/2-1], zeros(Params.numAzimuthBins-1,1));
        axis(figAzimuthHeatmap.hax2, [-Params.numAzimuthBins/2+1 Params.numAzimuthBins/2-1 40 90]);
        set(figAzimuthHeatmap.hax2, 'YLimMode', 'manual');

        %DEBUG_AZIMUTH_FFT_INPUT
        figAzimuthHeatmap.htab3 = uitab(figAzimuthHeatmap.hTabGroup, 'Title', 'Azimuth FFT Input');
        figAzimuthHeatmap.hax3 = axes('Parent', figAzimuthHeatmap.htab3);
        %figAzimuthHeatmap.hPlot3 = plot(figAzimuthHeatmap.hax3, (0:29), zeros(30,1),'.-');
        figAzimuthHeatmap.hPlot3 = plot(figAzimuthHeatmap.hax3, (-64:63), zeros(128,1),'.-');
        axis(figAzimuthHeatmap.hax3, [0 30 0 700]);
        set(figAzimuthHeatmap.hax3, 'XLimMode', 'manual');
        set(figAzimuthHeatmap.hax3, 'YLimMode', 'manual');
        set(figAzimuthHeatmap.hax3, 'ZLimMode', 'manual');

        figAzimuthHeatmap.htab4 = uitab(figAzimuthHeatmap.hTabGroup, 'Title', 'Azimuth FFT Input - Phase');
        figAzimuthHeatmap.hax4 = axes('Parent', figAzimuthHeatmap.htab4);
    end

    EXIT_KEY_PRESSED = 0;

    % Register a Clean-up object
    cleanUpHndl = onCleanup(@cleanUp);

    tcp_port_num = 29172;
    udp_port_num = 29173;

    % Open UDP & TCP connections
    openConnection(tgt_ip_addr, host_ip_addr,tcp_port_num, udp_port_num);
    tfdtp_init(host_mac_address, host_ip_addr);

CC = [];
dopHist = ones(513,1);

    % Start reading the UDP data
    dataArray = zeros(65536, 1, 'uint8');
    %tfdtp_flushUDPBuffer();
    tStart = tic;
    frameNum = 0;
    frameNumMod20 = 0;
    while ~EXIT_KEY_PRESSED
%         if get(gcf,'currentchar') ~= ' '
%             break;
%         end
        bufferReceived = tfdtp_recvUDPBuffer();

        % check if a buffer is received
        if (bufferReceived == 0)
           continue;
        end
        tFrame = toc(tStart);
        tStart = tic;

        tStartMatlabProc = tic;

        % get the packet header
        [msgHeader, byteVecIdx, frameNum] = getBufferHeader(dataArray, frameNum);

        if  msgHeader.totalLength == 0
            continue;
        end
        Params.gui.cloudPointsPresent = 0;
        Params.gui.rangeProfilePresent = 0;
        Params.gui.azimHeatMapPresent = 0;
        Params.gui.rangeDopplerHeatMapPresent = 0;
        pointCloud.numObj = 0;

        for tlvIdx = 1: msgHeader.numTLVs
            [tlv, byteVecIdx] = getNextTLV(dataArray, byteVecIdx);
             switch tlv.type
                case OP_SECTION_DATATYPE_SYSTEM_INFO
                    [systemInfo, byteVecIdx] = getSystemInfo(dataArray,...
                                               byteVecIdx);
                    if systemInfo.numDopplerBins ~= Params.numDopplerBins
                        fprintf('ERROR: Unexpected Doppler FFT size!\n');
                        return;
                        EXIT_KEY_PRESSED = 1;
                    end
                case OP_SECTION_DATATYPE_CALIBRATION_COEFFS
                    [calibrationCoeffs, byteVecIdx] = getCalibrationCoeffs(dataArray,...
                                               byteVecIdx,...
                                               tlv.length);
                    figure(100)
                    plot(real(calibrationCoeffs))
                    hold on
                    CC = [CC calibrationCoeffs];
                    save CC CC
                case OP_SECTION_DATATYPE_DETECTED_POINTS
                    if msgHeader.numDetObjs > 0
                        % Point Cloud
                        [pointCloud, byteVecIdx] = getPointCloud(dataArray,...
                                                   byteVecIdx,...
                                                   msgHeader.numDetObjs,...
                                                   Params.azimuthRowLength);
                        Params.gui.cloudPointsPresent = 1;
                    end
                case OP_SECTION_DATATYPE_RANGE_PROFILE
                    [rp,  byteVecIdx] = getRangeProfile( dataArray, ...
                                                         byteVecIdx,...
                                                         tlv.length);
                    Params.gui.rangeProfilePresent = 1;
                case OP_SECTION_DATATYPE_NOISE_PROFILE
                    [np,  byteVecIdx] = getRangeProfile( dataArray, ...
                                                         byteVecIdx,...
                                                         tlv.length);

                case OP_SECTION_DATATYPE_AZIMUT_STATIC_HEAT_MAP
                    [Q, q, byteVecIdx] = getAzimuthStaticHeatMap(dataArray, ...
                                                byteVecIdx, ...
                                                Params);
                    Params.gui.azimHeatMapPresent = 1;
                case OP_SECTION_DATATYPE_RANGE_DOPPLER_HEAT_MAP
                    [rangeDoppler, byteVecIdx] = getRangeDopplerHeatMap(dataArray, ...
                                                byteVecIdx, ...
                                                Params.numDopplerBins, ...
                                                Params.numRangeBins);
                    Params.gui.rangeDopplerHeatMapPresent = 1;
                otherwise
            end
        end

        %fprintf('EXTENDED VELO: false detections: %d\n',length(find(pointCloud.dopplerInd ~= 0)));

        %Plot Cloud Points
        
    if(PLOT_POINT_CLOUD)
        if pointCloud.numObj > 0
             set(figCloudPoint.hplot(figCloudPoint.hplotInd), 'Xdata', pointCloud.x, 'Ydata', pointCloud.y, ...
                 'Zdata', pointCloud.z);
       else
            set(figCloudPoint.hplot(figCloudPoint.hplotInd), 'Xdata',[], 'Ydata',[], 'Zdata',[]);
        end
        title(figCloudPoint.hax1,sprintf('3D Scatter Plot - %3d points', msgHeader.numDetObjs))
    end


%         scatter3( pointCloud.x, pointCloud.y, pointCloud.z,45,( pointCloud.doppler),'filled');
%             caxis([-2 2])
%             c = colorbar;
%             c.Label.String = 'velocity (m/s)';
%             %lim(ii,:) = caxis;
%             grid on;
%             %hold on
%             xlim([-2 2])
%             ylim([1 6])
%             zlim([-1.5 1.5])
%             xlabel('X (m)')
%             ylabel('y (m)')
%             zlabel('Z (m)')
%             title('3D point cloud(cascade)')



        figCloudPoint.hplotInd = figCloudPoint.hplotInd + 1;
        if (figCloudPoint.hplotInd > figCloudPoint.hplotLen)
            figCloudPoint.hplotInd = 1;
        end

%         ind = figCloudPoint.hplotInd;
%         ro  = .3;
%         fade = 1;
%         col = [ 1 1 1];
%         for kk = 1: figCloudPoint.hplotLen-1
%             set(figCloudPoint.hplot(ind), 'color', col);
%             col(1:2) = col(1:2) - (1/figCloudPoint.hplotLen);
%
%             ind = ind + 1;
%             if ind > figCloudPoint.hplotLen
%                 ind = 1;
%             end
%         end

        %Plot Cloud Range/Doppler Points
        if pointCloud.numObj > 0
            set(figRangeDoppler.hplot1, 'Xdata', pointCloud.range, 'Ydata', pointCloud.doppler);
        else
            set(figRangeDoppler.hplot1, 'Xdata',[], 'Ydata',[]);
        end

        if DEBUG_RANDOM_POINTS
            if ~isempty(find(pointCloud.rangeIdx == 33))
                %fprintf('FOUND\n');
                %DEBUG - remove

                foundInd = find(pointCloud.rangeIdx == 33);

                %set(figAzimuthHeatmap.hPlot3, 'Ydata', abs(pointCloud.azimInput(:,foundInd(1))));
                set(figAzimuthHeatmap.hPlot3, 'Ydata', fftshift(abs(fft(pointCloud.azimInput(:,foundInd(1)),128)).^2));
                axis(figAzimuthHeatmap.hax3,'auto')
%                  figure(107)
%                  plot(angle(pointCloud.azimInput(:,foundInd(1))),'o')
%                  axis([0 90 -4 4])
            end
        end

        %Plot Range Profile
        if (Params.gui.rangeProfilePresent && Params.gui.rangeProfile)
            %set(figRangeProfile.hplot, {'Ydata'}, num2cell([rp rpDet np].',2));
            set(figRangeProfile.hplot, {'Ydata'}, num2cell([10*log10(rp) ].',2));
        end

        if (Params.gui.azimHeatMapPresent && Params.gui.azimHeatMap)
            
            if (PLOT_STATIC_HEATMAP)
            %Plot Azimuth Heatmap
            powFac = 0.7;
            QQ=fftshift(abs(Q),1);
            QQ=QQ.';
            QQ=QQ(:,2:end);
            %temporary remove near end bump...
            QQ(1:5,:) = 0;
            QQ = sqrt(QQ).^powFac;
            colormap(jet)
            warning off
            Z=griddata(figAzimuthHeatmap.posX,figAzimuthHeatmap.posY,double(QQ),figAzimuthHeatmap.X,figAzimuthHeatmap.Y,'linear');
            warning on
            set(figAzimuthHeatmap.hPlot, 'Zdata', Z);
            end
        end

        if (Params.gui.rangeDopplerHeatMapPresent && Params.gui.rangeDopplerHeatMap)
            %Plot Range Doppler Heatmap
            rangeDopplerLog = 10*log10(rangeDoppler');
            set(figRangeDoppler.hPlot2, 'Zdata', rangeDopplerLog);

            %Plot Range Doppler Profiles
            %figRangeDoppler.hPlot3 = plot(figRangeDoppler.hax3, [0:Params.numRangeBins-1], rangeDopplerLog);
            set(figRangeDoppler.hPlot3, {'Ydata'}, num2cell(rangeDopplerLog,2));
        end

        %fprintf('%10d ', round(tFrame*1000));
        if VERBOSE
            fprintf('Frame Period = %10d, MatlabProcess = %10d ms\n',...
                    round(tFrame*1000), round(toc(tStartMatlabProc)*1000));
        end
      pause(0.001);
      frameNumMod20 = mod(frameNumMod20+1, 20);
      if frameNumMod20 == 0
          pause(.1)
      end
     end
    % Wait for 5 seconds before de-activating
    pause(500000);
    tfdtp_deinit();

    fprintf('tfdtp deinit finished...\n');


return % tcp_radar_app()
function [systeminfo, offset] = getSystemInfo(dataArray, offset)

    systeminfo.rangeRes = typecast(dataArray(offset+(1:4)), 'single');
    offset = offset + 4;
    systeminfo.dopplerRes = typecast(dataArray(offset+(1:4)), 'single');
    offset = offset + 4;
    systeminfo.numRangeBins = typecast(dataArray(offset+(1:2)), 'int16');
    offset = offset + 2;
    systeminfo.numDopplerBins = typecast(dataArray(offset+(1:2)), 'int16');
    offset = offset + 2;

    systeminfo.numSensors = typecast(dataArray(offset+1), 'int8');
    offset = offset + 1;
    systeminfo.numTxAntPerSensor = typecast(dataArray(offset+1), 'int8');
    offset = offset + 1;
    systeminfo.numRxAntPerSensor = typecast(dataArray(offset+1), 'int8');
    offset = offset + 1;
    systeminfo.numTxAzimuthAnt = typecast(dataArray(offset+1), 'int8');
    offset = offset + 1;
    systeminfo.numTxElevationAnt = typecast(dataArray(offset+1), 'int8');
    offset = offset + 1;
    offset = offset + 3; % for padding
return


function [header, offset, curFrameNum] = getBufferHeader(dataArray, prevFrameNum)

    dataInt = typecast (dataArray, 'uint32');

    %header.syncword =
    offset = 8;
    header.frameId = dataInt(3);
    offset = offset + 4;
    header.coreId = dataInt(4);
    offset = offset + 4;
    header.numTLVs = dataInt(5);
    offset = offset + 4;
    header.totalLength = dataInt(6);
    offset = offset + 4;
    header.numDetObjs = dataInt(7);
    offset = offset + 4;
    %fprintf('Debug: frame = %d, core=%d, numDetObjects=%d numTLV=%d\n', header.frameId,header.coreId, header.numDetObjs, header.numTLVs );
    curFrameNum = header.frameId;
    if curFrameNum ~= (prevFrameNum+1)
    fprintf('Debug: Missed %d frames, frame = %d, core=%d, numDetObjects=%d numTLV=%d\n', curFrameNum-prevFrameNum, header.frameId,header.coreId, header.numDetObjs, header.numTLVs );
    end
return


function [tlv, offset] = getNextTLV(dataArray, offset)
    tlv.type =  typecast(dataArray(offset+1:offset+4),'uint32');
    tlv.length = typecast(dataArray(offset+5:offset+8),'uint32');
    offset = offset + 8;
return

function [rp, idx] = getRangeProfile(bytevec, idx, len)
   rp = typecast(bytevec(idx+(1:len)), 'single');
   idx = idx + len;
return


function [calibrationCoeffs, idx] = getCalibrationCoeffs(bytevec, idx, len)
   calibrationCoeffs = typecast(bytevec(idx+(1:len)), 'single');
   %Imag(1), Real(1), Imag(2), Real(2),...
   calibrationCoeffs = calibrationCoeffs(2:2:end) + 1j*calibrationCoeffs(1:2:end);
   idx = idx + len;
return

function [Q, qq, idx] = getAzimuthStaticHeatMap(bytevec, idx, params)
   len = (params.numAzimuthBins*params.numRangeBins)*4 ;
   qq = typecast(bytevec(double(idx)+(1:len)), 'single');
   idx = idx + len;
   Q = reshape(qq, [params.numAzimuthBins  params.numRangeBins]);
return

function [rangeDoppler, idx] = getRangeDopplerHeatMap(bytevec, idx, numDopplerBins, numRangeBins)
    len = numDopplerBins * numRangeBins * 4;  % float
    rangeDoppler = typecast(bytevec(double(idx)+(1:len)), 'single');
    idx = idx + len;

    rangeDoppler = reshape(rangeDoppler, numRangeBins, numDopplerBins);
    rangeDoppler = fftshift(rangeDoppler, 2); % swap on Doppler dimension
return

function [recvCmdHdrFlag] = tfdtp_recvOneCmdHdr()
   global tcpCmdSock
   global dataSize


    % Expect an rx command header with following format.
    %   numBuf - 4bytes
    %   header - 4 bytes
    %   payloadtype - 4 bytes
    %   chNum - 4 bytes
    %   dataSize - 4 bytes
    %   width - 4 bytes
    %   height - 4 bytes
    %   pitch - 8 bytes
    % total 36 bytes - 9 words
    recvCmdHdrFlag = 0;

    % Command header length in words
    cmdHdrLen = 9;
    while (recvCmdHdrFlag == 0)

        [datavec, byteCount] = fread(tcpCmdSock, cmdHdrLen, 'uint');
        if byteCount == 0
            continue;
        end
        numBuf = datavec(1);
        if ~(numBuf == 1)
            fprintf('Error: Unexpected command hdr with numBuf=%d \n', numBuf);
            continue;
        end
        header = dec2hex(uint32(datavec(2)));
        payloadtype=datavec(3);
        chNum = datavec(4);
        if (header == 'ABCD4321')
            %fprintf('Debug: header = %s \n',header);
            ack = 1;
            recvCmdHdrFlag = 1;
            dataSize = datavec(5);

           % Send transmit ack
            tfdtp_sendAck(ack);
        else
            fprintf('Error: Incorrect header = %s \n',header);
        end
    end

return

function tfdtp_flushUDPBuffer()
   global udpSock

   bytesInBuffer = udpSock.BytesAvailable;
   while (bytesInBuffer > 0)
      [dumpBuf hwSize] = fread(udpSock, bytesInBuffer, 'uint8');
      bytesInBuffer = udpSock.BytesAvailable;
   end
return
function [tfdtpHeader] = getTfdtpHeader(dataArray, headerSize)

    % Start reading the UDP data
    % flags - 4 bytes
    % frame id - 2 bytes
    % channel num - 2 bytes, always 55
    % current seq - 2 bytes
    % total seq for the buffer - 2 bytes
    % length of this packet - 4 bytes
    % offset of this packet in the buffer - 4 bytes
    % Reserved - 4 bytes
    header = uint8(dataArray(1:headerSize));
    headerInWord = typecast(header, 'uint32');

    tfdtpHeader.flags = headerInWord(1);
    tfdtpHeader.dataLen = headerInWord(4);
    tfdtpHeader.offset = headerInWord(5);

    headerInHalfWord = typecast (header, 'uint16');
    tfdtpHeader.frameId = headerInHalfWord(3);
    tfdtpHeader.chNum = headerInHalfWord(4);
    tfdtpHeader.seq = headerInHalfWord(5);
    tfdtpHeader.totalSeq = headerInHalfWord(6);
return

function [valid] = validateTfdtpHeader(tfdtpHeader, frameId)

    valid = 1;
    if ~(tfdtpHeader.chNum == 55)
        valid = 0;
    end

    if ~(tfdtpHeader.frameId == frameId)
        valid = 0;
    end
return

function [bufferRecved] = tfdtp_recvUDPBuffer()
   global udpSock
   global dataArray

   % TFDTP header definition
   TFDTP_HEADER_SIZE = 24;
   TFDTP_MAX_PACKET_SIZE = 1472;
   TFDTP_SOF = '0000BE00';
   TFDTP_EOF = '000000EF';
   TFDTP_VER = '01000000';
   TFDTP_SOF_MASK = '0000FF00';
   TFDTP_EOF_MASK = '000000FF';
   TFDTP_VER_MASK = 'FF000000';

   endOfFrame = 0;
   startOfFrame = 0;
   totalSeqRecved = 0;
   currSeq = 0;
   currFrameId = 0;
   dataSize = 65535;
   bufferRecved = 0;

   bytes = udpSock.BytesAvailable;

%    if(bytes > 32767)
%         %fprintf('UDP buffer size=%d\n', bytes);
%    end

   % Cycle through tfdtp packets and save one frame in buffer
   while((endOfFrame == 0) && (bytes > 0))

       [tmpData hwRecvSize] = fread(udpSock, TFDTP_MAX_PACKET_SIZE, 'uint8');

       % No data is available before timeout
        if ((hwRecvSize == 0) || (hwRecvSize < TFDTP_HEADER_SIZE))
            bufferRecved = 0;
            break;
        end

        % Get TFDTP header
        tfdtpHeader = getTfdtpHeader(tmpData, TFDTP_HEADER_SIZE);
        if(currFrameId == 0)
            currFrameId = tfdtpHeader.frameId;
        end

         if (validateTfdtpHeader(tfdtpHeader, currFrameId) == 0)
             break;
         end

        % New Frame indication
        if (bitand(tfdtpHeader.flags , hex2dec(TFDTP_SOF_MASK)) == hex2dec(TFDTP_SOF))
            startOfFrame = 1;
            currFrameId = tfdtpHeader.frameId;
            totalSeqRecved = 0;
            currSeq = tfdtpHeader.seq;
        end

        % Other indication of new frame starts in case of packets lost
        if ((tfdtpHeader.frameId > currFrameId ) || ...
            (tfdtpHeader.seq < currSeq))
            startOfFrame = 1;

            currFrameId = tfdtpHeader.frameId;
            totalSeqRecved = 0;
            currSeq = tfdtpHeader.seq;
        end


        % Save Data
        if(hwRecvSize == (tfdtpHeader.dataLen + TFDTP_HEADER_SIZE))
            tmpDataBytes(1:hwRecvSize) = uint8(tmpData(1:hwRecvSize));

            dataArray(tfdtpHeader.offset + (1:tfdtpHeader.dataLen)) = tmpDataBytes( (TFDTP_HEADER_SIZE+1): hwRecvSize);
            %bytes = udpSock.BytesAvailable;
            %fprintf('                  %3d %10d,%10d\n', tfdtpHeader.seq, tfdtpHeader.offset + tfdtpHeader.dataLen, bytes);
            % Track the total received seq
            currSeq = tfdtpHeader.seq;
            totalSeqRecved = totalSeqRecved + 1;
        else
            %fprintf('dataLen =%d, hwRecvSize = %d\n',tfdtpHeader.dataLen, hwRecvSize);
            bufferRecved = 0;
        end
        % End of Frame?
        if (bitand(tfdtpHeader.flags , hex2dec(TFDTP_EOF_MASK)) == hex2dec(TFDTP_EOF))

            % At the end of frame, if not all data received, print error
            if( ~(totalSeqRecved == tfdtpHeader.totalSeq))
                %fprintf('Error: End of frame, but did not get all packets, %d out of %d are received\n',totalSeqRecved, tfdtpHeader.totalSeq);
                bufferRecved = 0;
            else
                bufferRecved = 1;
            end

%             bytes = udpSock.BytesAvailable;
%             fprintf('                  %3d %10d %10d\n', tfdtpHeader.frameId, tfdtpHeader.offset + tfdtpHeader.dataLen, bytes);
            endOfFrame = 1;
        end

        %bytes = udpSock.BytesAvailable;
    end
    ack = 1;
    % send ACK
    tfdtp_sendAck(ack);
return

function tfdtp_init(host_MAC_address, host_ip_address)
   global tcpCmdSock
   global dataSize

   % TFDTP Initialization parameter set - Channel config
   % channelId (4 bytes)
   % thruput (4 bytes) - channelId
   % IPAddress (4 bytes)
   % MacAddr (16 bytes)

    chanId  = typecast(uint32(55), 'uint8');
    macAddr = hex2dec(strsplit(host_MAC_address, '-'));
    MAC_address = uint8(macAddr);
    MAC_address_padding = uint8([0; 0; 0; 0; 0; 0; 0; 0; 0; 0]);
    ipAddrStr = strsplit(host_ip_address, '.');
    IP_Address = fliplr(str2double(ipAddrStr));

    % Send the RADAR_NW_LINK_TFDTP_INIT message
    msg = [chanId chanId IP_Address MAC_address' MAC_address_padding'];

    fwrite(tcpCmdSock, msg);
    fprintf('Sent RADAR_NW_LINK_TFDTP_INIT message on TCP socket\n');
return

function tfdtp_sendAck(ack)
   global tcpCmdSock

    % Send transmit ack
    ack_bytes  = typecast(uint32(ack), 'uint8');
    msg = [ack_bytes];
    fwrite(tcpCmdSock, msg);
    %fprintf('Sent ACK message on TCP socket, ack=%drecvCmdHdr\n', ack);
return
function tfdtp_deinit()
   global tcpCmdSock

    % Send the RADAR_NW_LINK_TFDTP_DEINIT message
%     msg = RADAR_NW_LINK_TFDTP_DEINIT;
%
%     fwrite(tcpCmdSock, msg, 'uint');
%     fprintf('Sent RADAR_NW_LINK_TFDTP_DEINIT message on TCP socket\n');

    % Expect an ACK.
%     header = fread(tcpCmdSock, 1, 'uint');
%     fprintf('Received ACK for RADAR_NW_LINK_TFDTP_DEINIT message on TCP socket\n');

    % Cleanup and exit
    cleanUp();
return

function openConnection(tgt_ip_addr, host_ip_addr,tcp_port_num, udp_port_num)
    global tcpCmdSock
    global udpSock

    MAX_PACKET_SIZE_BYTES = 65535; % bytes

    % Define the connection type and associated parameters
    tcpCmdSock = tcpip(tgt_ip_addr, tcp_port_num,'NetworkRole', 'client');

    % Set the Endianness
    tcpCmdSock.ByteOrder = 'littleEndian';

    % Define UDP connection parameters
    udpSock = udp(tgt_ip_addr, udp_port_num);

    udpSock.ByteOrder = 'littleEndian';

    % Bind to the local port number
    udpSock.LocalHost = host_ip_addr;
    udpSock.LocalPort = udp_port_num + 1;

    % Set the output buffer size
    tcpCmdSock.OutputBufferSize = MAX_PACKET_SIZE_BYTES;

    % Set the Input buffer size
    tcpCmdSock.InputBufferSize = MAX_PACKET_SIZE_BYTES;

    % Set the output buffer size
    udpSock.OutputBufferSize = MAX_PACKET_SIZE_BYTES;

    % Set the output buffer size
    udpSock.OutputDatagramPacketSize = MAX_PACKET_SIZE_BYTES;

    % Set the Input buffer size
    udpSock.InputBufferSize = MAX_PACKET_SIZE_BYTES;

    % Set the datagram termination mode
    udpSock.DatagramTerminateMode = 'on';

    % Set the timeout value
    udpSock.Timeout = 0.01;

    % Open the connection
    fopen(tcpCmdSock);
    fprintf('Opened connection to TCP Command Server\n');

    fopen(udpSock);
    fprintf('Opened connection to UDP server\n');

return
function closeConnection()
    global tcpCmdSock
    global udpSock

    % Close the connections
    fprintf('Closing the TCP Command server connection\n');
    fclose(tcpCmdSock);
    delete(tcpCmdSock);

    fprintf('Closing the UDP connection\n');
    fclose(udpSock);
    delete(udpSock);

return

function myKeyPressFcn(hObject, event)
    global EXIT_KEY_PRESSED

    if lower(event.Key) == 'q'
        EXIT_KEY_PRESSED  = 1;
    end

return

function cleanUp()
    global figHndl

    fprintf('CleanUp called\n');

    % Close the connection
    closeConnection();

    close(figHndl);
return

function [detObj, idx] = getPointCloud(bytevec, idx, numDetObjs, azimuthRowLength)
    global DEBUG_RANDOM_POINTS

    if DEBUG_RANDOM_POINTS
        debugRandomPointsBytes = azimuthRowLength*2*4;
    else
        debugRandomPointsBytes = 0;
    end

    OBJ_STRUCT_SIZE_BYTES = 44 + debugRandomPointsBytes;
    detObj =[];
    detObj.numObj = numDetObjs;

    bytes = bytevec(idx+(1:numDetObjs*OBJ_STRUCT_SIZE_BYTES));
    idx = idx + numDetObjs*OBJ_STRUCT_SIZE_BYTES;

    bytes = reshape(bytes, OBJ_STRUCT_SIZE_BYTES, numDetObjs);

    %detObj.rangeIdx = (bytes(1,:)+bytes(2,:)*256);
    ofs = 0;
    tmp = bytes(ofs + (1:2),:);
    detObj.rangeIdx = typecast(tmp(:), 'int16');
    ofs = ofs + 2;

    tmp = bytes(ofs + (1:2),:);
    detObj.dopplerInd = typecast(tmp(:), 'int16');
    ofs = ofs + 2;

    tmp = bytes(ofs + (1:2),:);
    detObj.azimuthAngleInd = typecast(tmp(:), 'int16');
    ofs = ofs + 2;

    tmp = bytes(ofs + (1:2),:);
    detObj.elevationAngleInd = typecast(tmp(:), 'int16');
    ofs = ofs + 2;

    tmp = bytes(ofs + (1:4),:);
    detObj.range = typecast(tmp(:), 'single');
    ofs = ofs + 4;

    tmp = bytes(ofs + (1:4),:);
    detObj.doppler = typecast(tmp(:), 'single');
    ofs = ofs + 4;

    tmp = bytes(ofs + (1:4),:);
    detObj.azimuthAngle = typecast(tmp(:), 'single');
    ofs = ofs + 4;

    tmp = bytes(ofs + (1:4),:);
    detObj.elevationAngle = typecast(tmp(:), 'single');
    ofs = ofs + 4;

    tmp = bytes(ofs + (1:4),:);
    detObj.snr = typecast(tmp(:), 'single');
    ofs = ofs + 4;

    tmp = bytes(ofs + (1:4),:);
    detObj.rangeVar = typecast(tmp(:), 'single');
    ofs = ofs + 4;

    tmp = bytes(ofs + (1:4),:);
    detObj.dopplerVar = typecast(tmp(:), 'single');
    ofs = ofs + 4;

    tmp = bytes(ofs + (1:4),:);
    detObj.azimAngleVar = typecast(tmp(:), 'single');
    ofs = ofs + 4;

    tmp = bytes(ofs + (1:4),:);
    detObj.elevAngleVar = typecast(tmp(:), 'single');
    ofs = ofs + 4;

    if DEBUG_RANDOM_POINTS
        tmp = bytes(ofs + (1:debugRandomPointsBytes),:);
        detObj.azimInput = typecast(tmp(:), 'single');
        detObj.azimInput = detObj.azimInput(1:2:end) + 1j*detObj.azimInput(2:2:end);
        detObj.azimInput = reshape(detObj.azimInput, azimuthRowLength, numDetObjs);
        ofs = ofs + debugRandomPointsBytes;
    end

    inRange = find(detObj.azimuthAngle < pi*60/180 & ...
                    detObj.azimuthAngle > -pi*60/180 & ...
                    detObj.elevationAngle > -pi*20/180  & ...
                    detObj.elevationAngle < pi*20/180); % & ...
                    %detObj.dopplerInd ~= 0 &...
                    %detObj.dopplerInd ~= 1 &...
                    %detObj.dopplerInd ~= -1);

    cosElevation = cos(detObj.elevationAngle);
    detObj.x = detObj.range .* cosElevation .* sin(detObj.azimuthAngle);
    detObj.y = detObj.range .* cosElevation .* cos(detObj.azimuthAngle);
    detObj.z = -detObj.range .* sin(detObj.elevationAngle);

    detObj.x = detObj.x(inRange);
    detObj.y = detObj.y(inRange);
    detObj.z = detObj.z(inRange);
    detObj.rangeIdx            = detObj.rangeIdx(inRange);
    detObj.dopplerInd          = detObj.dopplerInd(inRange);
    detObj.azimuthAngleInd     = detObj.azimuthAngleInd(inRange);
    detObj.elevationAngleInd   = detObj.elevationAngleInd(inRange);
    detObj.range               = detObj.range(inRange);
    detObj.doppler             = detObj.doppler(inRange);
    detObj.azimuthAngle        = detObj.azimuthAngle(inRange);
    detObj.elevationAngle      = detObj.elevationAngle(inRange);
    detObj.snr                 = detObj.snr(inRange);
    detObj.rangeVar            = detObj.rangeVar(inRange);
    detObj.dopplerVar          = detObj.dopplerVar(inRange);
    detObj.azimAngleVar        = detObj.azimAngleVar(inRange);
    detObj.elevAngleVar        = detObj.elevAngleVar(inRange);


    detObj.numObj = length(inRange);

return

function [Params] = aoaInitLookupTable (Params )
     % sensorRxOffset[Number of Sensors]
     %      -> sensorAzimOffs
     %      -> antAzimOffs[ numRxAntPerSensor ]
     %      -> antElevOffs[ numRxAntPerSensor ] --> Not used
     %      -> antRowOffs [ numRxAntPerSensor ]
     %
     % txAntOffset
     %      -> antAzimOffs [ numTxAnt ] (numTxAnt = numTxAzimAnt +
     %      numTxElevAnt)
     %      -> antElevOffs [ numTxAnt ]
     %      -> antRowOffs  [ numTxAnt ]
     % rowToElevationIdx
     if strcmp(Params.platform, 'TI')
        sensorRxOffset{1}.sensorAzimOffs = 0;
        sensorRxOffset{1}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{1}.antElevOffs = [0 0 0 0];
        sensorRxOffset{1}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{2}.sensorAzimOffs = 11;
        sensorRxOffset{2}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{2}.antElevOffs = [0 0 0 0];
        sensorRxOffset{2}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{3}.sensorAzimOffs = 50;
        sensorRxOffset{3}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{3}.antElevOffs = [0 0 0 0];
        sensorRxOffset{3}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{4}.sensorAzimOffs = 46;
        sensorRxOffset{4}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{4}.antElevOffs = [0 0 0 0];
        sensorRxOffset{4}.antRowOffs =  [0 0 0 0];

        txAntOffset.antAzimOffs = [0 8 16 24 32 9 10 11];
        txAntOffset.antElevOffs = [0 0  0  0  0 1  4  6];
        txAntOffset.antRowOffs =  [0 0  0  0  0 1  2  3];

        rowToElevationIdx = [0 1 4 6];
        rxMainRowIndex = 0;
    elseif strcmp(Params.platform, 'TI1DEV')
        sensorRxOffset{1}.sensorAzimOffs = 0;
        sensorRxOffset{1}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{1}.antElevOffs = [0 0 0 0];
        sensorRxOffset{1}.antRowOffs =  [0 0 0 0];

        txAntOffset.antAzimOffs = [0 8 16];
        txAntOffset.antElevOffs = [0 0  0];
        txAntOffset.antRowOffs =  [0 0  0];

        rowToElevationIdx = [0 1 4 6];
        rxMainRowIndex = 0;
     elseif strcmp(Params.platform, 'TI5ANT')
        sensorRxOffset{1}.sensorAzimOffs = 0;
        sensorRxOffset{1}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{1}.antElevOffs = [0 0 0 0];
        sensorRxOffset{1}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{2}.sensorAzimOffs = 11;
        sensorRxOffset{2}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{2}.antElevOffs = [0 0 0 0];
        sensorRxOffset{2}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{3}.sensorAzimOffs = 50;
        sensorRxOffset{3}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{3}.antElevOffs = [0 0 0 0];
        sensorRxOffset{3}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{4}.sensorAzimOffs = 46;
        sensorRxOffset{4}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{4}.antElevOffs = [0 0 0 0];
        sensorRxOffset{4}.antRowOffs =  [0 0 0 0];

        txAntOffset.antAzimOffs = [0 8 16 24 32];
        txAntOffset.antElevOffs = [0 0  0  0  0 ];
        txAntOffset.antRowOffs =  [0 0  0  0  0 ];

        rowToElevationIdx = [0];
        rxMainRowIndex = 0;

     elseif strcmp(Params.platform, 'TI9ANT')
        sensorRxOffset{1}.sensorAzimOffs = 0;
        sensorRxOffset{1}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{1}.antElevOffs = [0 0 0 0];
        sensorRxOffset{1}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{2}.sensorAzimOffs = 11;
        sensorRxOffset{2}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{2}.antElevOffs = [0 0 0 0];
        sensorRxOffset{2}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{3}.sensorAzimOffs = 50;
        sensorRxOffset{3}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{3}.antElevOffs = [0 0 0 0];
        sensorRxOffset{3}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{4}.sensorAzimOffs = 46;
        sensorRxOffset{4}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{4}.antElevOffs = [0 0 0 0];
        sensorRxOffset{4}.antRowOffs =  [0 0 0 0];

        txAntOffset.antAzimOffs = [0 8 16 24 28 32 9 10 11];
        txAntOffset.antElevOffs = [0 0  0  0  0  0 1  4  6];
        txAntOffset.antRowOffs =  [0 0  0  0  0  0 1  2  3];

        rowToElevationIdx = [0 1 4 6];
        rxMainRowIndex = 0;
    elseif strcmp(Params.platform, 'TIBF')
        sensorRxOffset{1}.sensorAzimOffs = 0;
        sensorRxOffset{1}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{1}.antElevOffs = [0 0 0 0];
        sensorRxOffset{1}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{2}.sensorAzimOffs = 11;
        sensorRxOffset{2}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{2}.antElevOffs = [0 0 0 0];
        sensorRxOffset{2}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{3}.sensorAzimOffs = 50;
        sensorRxOffset{3}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{3}.antElevOffs = [0 0 0 0];
        sensorRxOffset{3}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{4}.sensorAzimOffs = 46;
        sensorRxOffset{4}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{4}.antElevOffs = [0 0 0 0];
        sensorRxOffset{4}.antRowOffs =  [0 0 0 0];

        txAntOffset.antAzimOffs = [0 8 16 24 28 32 9 10 11];
        txAntOffset.antElevOffs = [0 0  0  0  0  0 1  4  6];
        txAntOffset.antRowOffs =  [0 0  0  0  0  0 1  2  3];
        rowToElevationIdx = [0 1 4 6];
        rxMainRowIndex = 0;
       elseif strcmp(Params.platform, 'TI10ANT')
        sensorRxOffset{1}.sensorAzimOffs = 0;
        sensorRxOffset{1}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{1}.antElevOffs = [0 0 0 0];
        sensorRxOffset{1}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{2}.sensorAzimOffs = 11;
        sensorRxOffset{2}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{2}.antElevOffs = [0 0 0 0];
        sensorRxOffset{2}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{3}.sensorAzimOffs = 50;
        sensorRxOffset{3}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{3}.antElevOffs = [0 0 0 0];
        sensorRxOffset{3}.antRowOffs =  [0 0 0 0];

        sensorRxOffset{4}.sensorAzimOffs = 46;
        sensorRxOffset{4}.antAzimOffs = [0 1 2 3];
        sensorRxOffset{4}.antElevOffs = [0 0 0 0];
        sensorRxOffset{4}.antRowOffs =  [0 0 0 0];
        
        txAntOffset.antAzimOffs = [0  4  8  16  24  28  32 9 10 11];
        txAntOffset.antElevOffs = [0  0  0  0   0   0   0  1  4  6];
        txAntOffset.antRowOffs =  [0  0  0  0   0   0   0  1  2  3];

        rowToElevationIdx = [0 1 4 6];
        rxMainRowIndex = 0;
     else
         fprintf('Platform %s is not supported!\n', Params.platform);
     end

    rxAngleIndxLUT = zeros(Params.numRxAntPerSensor, Params.numTxAnt, Params.numSensor);
    rxRowIndxLUT = zeros(Params.numRxAntPerSensor, Params.numTxAnt, Params.numSensor);
    reverseLUT = zeros(Params.azimuthRowLength,1);
    for sensInd = 0 : Params.numSensor-1
        for txInd = 0 : Params.numTxAnt-1
            for rxInd = 0 : Params.numRxAntPerSensor-1
                rxAngleIndxLUT(1+rxInd,1+txInd,1+sensInd) = txAntOffset.antAzimOffs(1+txInd) + ...
                                            sensorRxOffset{1+sensInd}.sensorAzimOffs + ...
                                            sensorRxOffset{1+sensInd}.antAzimOffs(1+rxInd);

                rxRowIndxLUT(1+rxInd,1+txInd,1+sensInd) = txAntOffset.antRowOffs(1+txInd) + ...
                                          sensorRxOffset{1+sensInd}.antRowOffs(1+rxInd);

                %reverse LUT table only for the first row, the main row for
                %azimuth FFT calculation
                if rxRowIndxLUT(1+rxInd,1+txInd,1+sensInd) == 0
                    reverseLUT(1+rxAngleIndxLUT(1+rxInd,1+txInd,1+sensInd)) = ...
                        1+ sensInd*Params.numTxAnt*Params.numRxAntPerSensor + txInd*Params.numRxAntPerSensor + rxInd;
                end
            end
        end
    end

    Params.rxAngleIndxLUT = rxAngleIndxLUT;
    Params.rxRowIndxLUT = rxRowIndxLUT;
    Params.rowToElevationIdx = rowToElevationIdx;
    Params.rxMainRowIndex = rxMainRowIndex;
    reverseLUT(reverseLUT==0)=Params.numVirtualAnt + 1;
    Params.reverseLUT = reverseLUT;

return


function Resize_clbk(hObject, ~)
return

