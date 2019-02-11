use strict;
use File::Basename;

# open
open fin, "$ARGV[0]" or die " could not open the $ARGV[0]\n";


my @configs = <fin>;
my $count =0;
my $linecount =0;
my $testcaseno = 0;
my $instId = 0;
my $tempVar1 = 0;
my $tempVar2 = 0;

    my $configName =  "displayUtTestInput_gblcfg".".h>;
    open foutGblCfg, ">$configName" or die " could not open the $configName\n";
    my $configName =  "displayUtTestInput_instcfg".".h>;
    open foutInstCfg, ">$configName" or die " could not open the $configName\n";

    foreach my $line (@configs)
    {
        if(($count==0) | ($count==1))
        {
            $count++;
            $linecount = 0;
            next;
        }
        chomp($line);
        #printf "$line\n";
        my @vect = split(",",$line);
        #printf "@vect\n";
        #printf "$vect[0]\n";

        if($count==2)
        {
            printf foutGblCfg "/* This is a generated Header file Donot Edit manually.\n * To update the test cases modify the displayUtTestInput.xls file, save it as .csv.\n * run vayu_displayUt_headerfile_generator.pl perl script with csv file as input */\n";
            printf foutInstCfg "/* This is a generated Header file Donot Edit manually.\n * To update the test cases modify the displayUtTestInput.xls file, save it as .csv.\n * run vayu_displayUt_headerfile_generator.pl perl script with csv file as input */\n";
            printf foutGblCfg "static st_DispDssTestCfg gTestDispDssTestCfg[] =\n";
            printf foutGblCfg "{\n";
            printf foutInstCfg "static st_DispDssTestInstCfg gTestDispDssTestInstCfg[ST_DISP_DSS_NUM_TESTCASES][VPS_DISP_INST_MAX] =\n";
            printf foutInstCfg "{\n";

            $linecount = 1;
        }
        else
        {
            if (($vect[1] == 4) | ($vect[1] == 5) | ($vect[1] == 6) | ($vect[1] == 7))    {
                $linecount ++;
            }
            else
            {
                printf foutInstCfg "    }, \n";
                $linecount = 1;

            }

        }

        if($linecount ==1)
        {
            $testcaseno++;
            $instId = 0;
            printf foutGblCfg "    { /* Test Case $testcaseno */ \n";
            printf foutInstCfg "    { /* Test Case $testcaseno */ \n";
            if ($vect[1] ne '')    {
                    printf foutGblCfg "        $vect[1], /* TestEnable  */\n";
            }
            else {
                    printf foutGblCfg "        0,/* TestEnable */\n";
            }
            if ($vect[0] ne '')    {
                    printf foutGblCfg "        $vect[0],/* TestCaseID */\n";
            }
            else {
                    printf foutGblCfg "        0,/* TestCaseID */\n";
            }
            if ($vect[2] ne '')    {
                    printf foutGblCfg "        $vect[2], /* TestCaseType  */\n";
            }
            else {
                    printf foutGblCfg "        0,/* TestCaseType */\n";
            }
            printf foutGblCfg "        {/* RequirementID */\n";
            if ($vect[3] ne '')    {
                    printf foutGblCfg "            \"$vect[3]\",\n";
            }
            else {
                    printf foutGblCfg "            NULL,\n";
            }
            printf foutGblCfg "        },\n";
            printf foutGblCfg "        {/* TestCaseDescription */\n";
            if ($vect[4] ne '')    {
                    printf foutGblCfg "            \"$vect[4]\",\n";
            }
            else {
                    printf foutGblCfg "            NULL,\n";
            }
            printf foutGblCfg "        },\n";
            printf foutGblCfg "        {/* TestCaseDisableReason */\n";
            if ($vect[5] ne '')    {
                if($vect[5] ne "NULL") {
                    printf foutGblCfg "            \"$vect[5]\",\n";
                } else {
                    printf foutGblCfg "            $vect[5],\n";
                }
            }
            else {
                    printf foutGblCfg "            0,\n";
            }
            printf foutGblCfg "        },\n";
            if ($vect[6] ne '')    {
                    printf foutGblCfg "        $vect[6], /* PrintEnable  */\n";
            }
            else {
                    printf foutGblCfg "        0,/* PrintEnable */\n";
            }
            if ($vect[7] ne '')    {
                    printf foutGblCfg "        $vect[7], /* TestType  */\n";
            }
            else {
                    printf foutGblCfg "        0,/* TestType */\n";
            }
            printf foutGblCfg "        0,/* IsRun */\n";
            printf foutGblCfg "        0,/* TestResult */\n";
            if ($vect[8] ne '')    {
                    printf foutGblCfg "        $vect[8], /* NumInstances  */\n";
            }
            else {
                    printf foutGblCfg "        0,/* NumInstances */\n";
            }
            printf foutGblCfg "    },\n";
        }
        if(($linecount ==2) | ($linecount ==3) | ($linecount ==4) | ($linecount ==5))
        {
            $instId++;
            printf foutInstCfg "        { /* inst Id $instId */\n";
            if ($vect[0] ne '')    {
                    printf foutInstCfg "            $vect[0], /* VideoNode */\n";
            }else {
                    printf foutInstCfg "            0, /* VideoNode */\n";
            }
            if ($vect[1] ne '')    {
                    printf foutInstCfg "            $vect[1], /* OverLayNode */\n";
            } else {
                    printf foutInstCfg "            0, /* OverLayNode */\n";
            }
            if ($vect[2] ne '')    {
                    printf foutInstCfg "            $vect[2], /* DisplayNode */\n";
            } else {
                    printf foutInstCfg "            0, /* DisplayNode */\n";
            }
            printf foutInstCfg "            { /* Vps_DispDssParams */\n";
                printf foutInstCfg "                { /* Fvid2_Format */\n";
                    if ($vect[3] ne '')    {
                            printf foutInstCfg "                    $vect[3], /* chNum */\n";
                    } else {
                            printf foutInstCfg "                    0, /* chNum */\n";
                    }
                    if ($vect[4] ne '')    {
                            printf foutInstCfg "                    $vect[4], /* width */\n";
                    } else {
                            printf foutInstCfg "                    0, /* width */\n";
                    }
                    if ($vect[5] ne '')    {
                            printf foutInstCfg "                    $vect[5], /* height */\n";
                    } else {
                            printf foutInstCfg "                    0, /* height */\n";
                    }
                    if ($vect[6] ne '')    {
                            printf foutInstCfg "                    $vect[6], /* pitch[0] */\n";
                    } else {
                            printf foutInstCfg "                    0, /* pitch[0] */\n";
                    }
                    if ($vect[7] ne '')    {
                            printf foutInstCfg "                    $vect[7], /* pitch[1] */\n";
                    } else {
                            printf foutInstCfg "                    0, /* pitch[1] */\n";
                    }
                    if ($vect[8] ne '')    {
                            printf foutInstCfg "                    $vect[8], /* pitch[2] */\n";
                    } else {
                            printf foutInstCfg "                    0, /* pitch[2] */\n";
                    }
                    if ($vect[9] ne '')    {
                            printf foutInstCfg "                    $vect[9], /* fieldMerged[0] */\n";
                    } else {
                            printf foutInstCfg "                    0, /* fieldMerged[0] */\n";
                    }
                    if ($vect[10] ne '')    {
                            printf foutInstCfg "                    $vect[10], /* fieldMerged[1] */\n";
                    } else {
                            printf foutInstCfg "                    0, /* fieldMerged[1] */\n";
                    }
                    if ($vect[11] ne '')    {
                            printf foutInstCfg "                    $vect[11], /* fieldMerged[2] */\n";
                    } else {
                            printf foutInstCfg "                    0, /* fieldMerged[2] */\n";
                    }
                    if ($vect[12] ne '')    {
                            printf foutInstCfg "                    $vect[12], /* dataFormat */\n";
                    } else {
                            printf foutInstCfg "                    0, /* dataFormat */\n";
                    }
                    if ($vect[13] ne '')    {
                            printf foutInstCfg "                    $vect[13], /* scanFormat */\n";
                    } else {
                            printf foutInstCfg "                    0, /* scanFormat */\n";
                    }
                    if ($vect[14] ne '')    {
                            printf foutInstCfg "                    $vect[14], /* bpp */\n";
                    } else {
                            printf foutInstCfg "                    0, /* bpp */\n";
                    }
                printf foutInstCfg "                }, /* End Fvid2_Format */\n";
                if ($vect[15] ne '')    {
                        printf foutInstCfg "                $vect[15], /* tarWidth */\n";
                } else {
                        printf foutInstCfg "                0, /* tarWidth */\n";
                }
                if ($vect[16] ne '')    {
                        printf foutInstCfg "                $vect[16], /* tarHeight */\n";
                } else {
                        printf foutInstCfg "                0, /* tarHeight */\n";
                }
                if ($vect[17] ne '')    {
                        printf foutInstCfg "                $vect[17], /* posX */\n";
                } else {
                        printf foutInstCfg "                0, /* posX */\n";
                }
                if ($vect[18] ne '')    {
                        printf foutInstCfg "                $vect[18], /* posY */\n";
                } else {
                        printf foutInstCfg "                0, /* posY */\n";
                }
                if ($vect[19] ne '')    {
                        printf foutInstCfg "                $vect[19], /* memType */\n";
                } else {
                        printf foutInstCfg "                0, /* memType */\n";
                }
                $tempVar1 = $testcaseno - 1;
                $tempVar2 = $instId - 1;
                printf foutInstCfg "                &gTestDispDssTestInstCfg[$tempVar1][$tempVar2].vidCfg, /* Vps_DssDispcVidConfig Ptr*/\n";
                printf foutInstCfg "                &gTestDispDssTestInstCfg[$tempVar1][$tempVar2].gfxCfg, /* Vps_DssDispcGfxConfig Ptr*/\n";
            printf foutInstCfg "            }, /* End Vps_DispDssParams */\n";
            printf foutInstCfg "            { /* Vps_DssDispcVidConfig */\n";
                printf foutInstCfg "                { /* Vps_DssDispcVidPipeConfig */\n";
                    if ($vect[20] ne '')    {
                            printf foutInstCfg "                    $vect[20], /* repliEnable */\n";
                    } else {
                            printf foutInstCfg "                    0, /* repliEnable */\n";
                    }
                    if ($vect[21] ne '')    {
                            printf foutInstCfg "                    $vect[21], /* scEnable */\n";
                    } else {
                            printf foutInstCfg "                    0, /* scEnable */\n";
                    }
                    if ($vect[22] ne '')    {
                            printf foutInstCfg "                    $vect[22], /* cscFullRngEnable */\n";
                    } else {
                            printf foutInstCfg "                    0, /* cscFullRngEnable */\n";
                    }
                    if ($vect[23] ne '')    {
                            printf foutInstCfg "                    $vect[23], /* chromaSampling */\n";
                    } else {
                            printf foutInstCfg "                    0, /* chromaSampling */\n";
                    }
                printf foutInstCfg "                }, /* End Vps_DssDispcVidPipeConfig */\n";
                printf foutInstCfg "                &gTestDispDssTestInstCfg[$tempVar1][$tempVar2].vidadvDmaCfg, /* Vps_DssDispcAdvDmaConfig Ptr*/\n";
                printf foutInstCfg "                &gTestDispDssTestInstCfg[$tempVar1][$tempVar2].vidvc1Cfg, /* Vps_DssDispcVidVC1Config Ptr*/\n";
            printf foutInstCfg "            }, /* End Vps_DssDispcVidConfig */\n";
            printf foutInstCfg "            { /* Vps_DssDispcAdvDmaConfig */\n";
                if ($vect[24] ne '')    {
                        printf foutInstCfg "                $vect[24], /* burstSize */\n";
                } else {
                        printf foutInstCfg "                0, /* burstSize */\n";
                }
                if ($vect[25] ne '')    {
                        printf foutInstCfg "                $vect[25], /* burstType */\n";
                } else {
                        printf foutInstCfg "                0, /* burstType */\n";
                }
                if ($vect[26] ne '')    {
                        printf foutInstCfg "                $vect[26], /* bufPreloadType */\n";
                } else {
                        printf foutInstCfg "                0, /* bufPreloadType */\n";
                }
                if ($vect[27] ne '')    {
                        printf foutInstCfg "                $vect[27], /* bufLowThreshold */\n";
                } else {
                        printf foutInstCfg "                0, /* bufLowThreshold */\n";
                }
                if ($vect[28] ne '')    {
                        printf foutInstCfg "                $vect[28], /* bufHighThreshold */\n";
                } else {
                        printf foutInstCfg "                0, /* bufHighThreshold */\n";
                }
                if ($vect[29] ne '')    {
                        printf foutInstCfg "                $vect[29], /* selfRefreshEnable */\n";
                } else {
                        printf foutInstCfg "                0, /* selfRefreshEnable */\n";
                }
                if ($vect[30] ne '')    {
                        printf foutInstCfg "                $vect[30], /* arbitration */\n";
                } else {
                        printf foutInstCfg "                0, /* arbitration */\n";
                }
                if ($vect[31] ne '')    {
                        printf foutInstCfg "                $vect[31], /* pixelInc */\n";
                } else {
                        printf foutInstCfg "                0, /* pixelInc */\n";
                }
            printf foutInstCfg "            }, /* End Vps_DssDispcAdvDmaConfig */\n";
            printf foutInstCfg "            { /* Vps_DssDispcVidVC1Config */\n";
                if ($vect[32] ne '')    {
                        printf foutInstCfg "                $vect[32], /* VC1_enable */\n";
                } else {
                        printf foutInstCfg "                0, /* VC1_enable */\n";
                }
                if ($vect[33] ne '')    {
                        printf foutInstCfg "                $vect[33], /* rangeY */\n";
                } else {
                        printf foutInstCfg "                0, /* rangeY */\n";
                }
                if ($vect[34] ne '')    {
                        printf foutInstCfg "                $vect[34], /* rangeUV */\n";
                } else {
                        printf foutInstCfg "                0, /* rangeUV */\n";
                }
            printf foutInstCfg "            }, /* End Vps_DssDispcVidVC1Config */\n";
            printf foutInstCfg "            { /* Vps_DssDispcGfxConfig */\n";
                printf foutInstCfg "                { /* Vps_DssDispcGfxPipeConfig */\n";
                    if ($vect[35] ne '')    {
                            printf foutInstCfg "                    $vect[35], /* GFX1_repliEnable */\n";
                    } else {
                            printf foutInstCfg "                    0, /* GFX1_repliEnable */\n";
                    }
                    if ($vect[36] ne '')    {
                            printf foutInstCfg "                    $vect[36], /* GFX1_antiFlickerEnable */\n";
                    } else {
                            printf foutInstCfg "                    0, /* GFX1_antiFlickerEnable */\n";
                    }
                printf foutInstCfg "                }, /* End Vps_DssDispcGfxPipeConfig */\n";
                printf foutInstCfg "                &gTestDispDssTestInstCfg[$tempVar1][$tempVar2].gfxadvDmaCfg, /* Vps_DssDispcAdvDmaConfig Ptr*/\n";
            printf foutInstCfg "            }, /* End Vps_DssDispcGfxConfig */\n";
            printf foutInstCfg "            { /* Vps_DssDispcAdvDmaConfig */\n";
                if ($vect[37] ne '')    {
                        printf foutInstCfg "                $vect[37], /* GFX1_burstSize */\n";
                } else {
                        printf foutInstCfg "                0, /* GFX1_burstSize */\n";
                }
                if ($vect[38] ne '')    {
                        printf foutInstCfg "                $vect[38], /* GFX1_burstType */\n";
                } else {
                        printf foutInstCfg "                0, /* GFX1_burstType */\n";
                }
                if ($vect[39] ne '')    {
                        printf foutInstCfg "                $vect[39], /* GFX1_bufPreloadType */\n";
                } else {
                        printf foutInstCfg "                0, /* GFX1_bufPreloadType */\n";
                }
                if ($vect[40] ne '')    {
                        printf foutInstCfg "                $vect[40], /* GFX1_bufLowThreshold */\n";
                } else {
                        printf foutInstCfg "                0, /* GFX1_bufLowThreshold */\n";
                }
                if ($vect[41] ne '')    {
                        printf foutInstCfg "                $vect[41], /* GFX1_bufHighThreshold */\n";
                } else {
                        printf foutInstCfg "                0, /* GFX1_bufHighThreshold */\n";
                }
                if ($vect[42] ne '')    {
                        printf foutInstCfg "                $vect[42], /* GFX1_selfRefreshEnable */\n";
                } else {
                        printf foutInstCfg "                0, /* GFX1_selfRefreshEnable */\n";
                }
                if ($vect[43] ne '')    {
                        printf foutInstCfg "                $vect[43], /* GFX1_arbitration */\n";
                } else {
                        printf foutInstCfg "                0, /* GFX1_arbitration */\n";
                }
                if ($vect[44] ne '')    {
                        printf foutInstCfg "                $vect[44], /* GFX1_pixelInc */\n";
                } else {
                        printf foutInstCfg "                0, /* GFX1_pixelInc */\n";
                }
            printf foutInstCfg "            }, /* End Vps_DssDispcAdvDmaConfig */\n";

            printf foutInstCfg "            { /* Vps_DssDispcOvlyPanelConfig */\n";
            if ($vect[45] ne '')    {
                    printf foutInstCfg "                $vect[45], /* vencId */\n";
            } else {
                    printf foutInstCfg "                0, /* vencId */\n";
            }
            if ($vect[46] ne '')    {
                    printf foutInstCfg "                $vect[46], /* colorKeyEnable */\n";
            } else {
                    printf foutInstCfg "                0, /* colorKeyEnable */\n";
            }
            if ($vect[47] ne '')    {
                    printf foutInstCfg "                $vect[47], /* colorKeySel */\n";
            } else {
                    printf foutInstCfg "                0, /* colorKeySel */\n";
            }
            if ($vect[48] ne '')    {
                    printf foutInstCfg "                $vect[48], /* deltaLinesPerPanel */\n";
            } else {
                    printf foutInstCfg "                0, /* deltaLinesPerPanel */\n";
            }
            if ($vect[49] ne '')    {
                    printf foutInstCfg "                $vect[49], /* transColorKey */\n";
            } else {
                    printf foutInstCfg "                0, /* transColorKey */\n";
            }
            if ($vect[50] ne '')    {
                    printf foutInstCfg "                $vect[50], /* backGroundColor */\n";
            } else {
                    printf foutInstCfg "                0, /* backGroundColor */\n";
            }
            if ($vect[51] ne '')    {
                    printf foutInstCfg "                $vect[52], /* alphaBlenderEnable */\n";
            } else {
                    printf foutInstCfg "                0, /* alphaBlenderEnable */\n";
            }
            if ($vect[52] ne '')    {
                    printf foutInstCfg "                $vect[52], /* ovlyOptimization */\n";
            } else {
                    printf foutInstCfg "                0, /* ovlyOptimization */\n";
            }
            printf foutInstCfg "            }, /* End Vps_DssDispcOvlyPanelConfig */\n";
            printf foutInstCfg "            { /* Vps_DssDispcOvlyPipeConfig */\n";
            if ($vect[53] ne '')    {
                    printf foutInstCfg "                $vect[53], /* pipeLine */\n";
            } else {
                    printf foutInstCfg "                0, /* pipeLine */\n";
            }
            if ($vect[54] ne '')    {
                    printf foutInstCfg "                $vect[54], /* zorder */\n";
            } else {
                    printf foutInstCfg "                0, /* zorder */\n";
            }
            if ($vect[55] ne '')    {
                    printf foutInstCfg "                $vect[55], /* zorderEnable */\n";
            } else {
                    printf foutInstCfg "                0, /* zorderEnable */\n";
            }
            if ($vect[56] ne '')    {
                    printf foutInstCfg "                $vect[56], /* globalAlpha */\n";
            } else {
                    printf foutInstCfg "                0, /* globalAlpha */\n";
            }
            if ($vect[57] ne '')    {
                    printf foutInstCfg "                $vect[57], /* preMultiplyAlpha */\n";
            } else {
                    printf foutInstCfg "                0, /* preMultiplyAlpha */\n";
            }
            printf foutInstCfg "            }, /* End Vps_DssDispcOvlyPipeConfig */\n";
            printf foutInstCfg "            { /* Fvid2_ModeInfo */\n";
            if ($vect[58] ne '')    {
                    printf foutInstCfg "                $vect[58], /* mInfo_standard */\n";
            } else {
                    printf foutInstCfg "                0, /* mInfo_standard */\n";
            }
            if ($vect[59] ne '')    {
                    printf foutInstCfg "                $vect[59], /* mInfo_width */\n";
            } else {
                    printf foutInstCfg "                0, /* mInfo_width */\n";
            }
            if ($vect[60] ne '')    {
                    printf foutInstCfg "                $vect[60], /* mInfo_height */\n";
            } else {
                    printf foutInstCfg "                0, /* mInfo_height */\n";
            }
            if ($vect[61] ne '')    {
                    printf foutInstCfg "                $vect[61], /* mInfo_scanFormat */\n";
            } else {
                    printf foutInstCfg "                0, /* mInfo_scanFormat */\n";
            }
            if ($vect[62] ne '')    {
                    printf foutInstCfg "                $vect[62], /* mInfo_pixelClock */\n";
            } else {
                    printf foutInstCfg "                0, /* mInfo_pixelClock */\n";
            }
            if ($vect[63] ne '')    {
                    printf foutInstCfg "                $vect[63], /* mInfo_fps */\n";
            } else {
                    printf foutInstCfg "                0, /* mInfo_fps */\n";
            }
            if ($vect[64] ne '')    {
                    printf foutInstCfg "                $vect[64], /* mInfo_hFrontPorch */\n";
            } else {
                    printf foutInstCfg "                0, /* mInfo_hFrontPorch */\n";
            }
            if ($vect[65] ne '')    {
                    printf foutInstCfg "                $vect[65], /* mInfo_hBackPorch */\n";
            } else {
                    printf foutInstCfg "                0, /* mInfo_hBackPorch */\n";
            }
            if ($vect[66] ne '')    {
                    printf foutInstCfg "                $vect[66], /* mInfo_hSyncLen */\n";
            } else {
                    printf foutInstCfg "                0, /* mInfo_hSyncLen */\n";
            }
            if ($vect[67] ne '')    {
                    printf foutInstCfg "                $vect[67], /* mInfo_vFrontPorch */\n";
            } else {
                    printf foutInstCfg "                0, /* mInfo_vFrontPorch */\n";
            }
            if ($vect[68] ne '')    {
                    printf foutInstCfg "                $vect[68], /* mInfo_vBackPorch */\n";
            } else {
                    printf foutInstCfg "                0, /* mInfo_vBackPorch */\n";
            }
            if ($vect[69] ne '')    {
                    printf foutInstCfg "                $vect[69], /* mInfo_vSyncLen */\n";
            } else {
                    printf foutInstCfg "                0, /* mInfo_vSyncLen */\n";
            }
            printf foutInstCfg "            }, /* End Fvid2_ModeInfo */\n";
            if ($vect[70] ne '')    {
                    printf foutInstCfg "            $vect[70], /* loopCount */\n";
            } else {
                    printf foutInstCfg "            0, /* loopCount */\n";
            }
            if ($vect[71] ne '')    {
                    printf foutInstCfg "            $vect[71], /* frameSwitchRate */\n";
            } else {
                    printf foutInstCfg "            0, /* frameSwitchRate */\n";
            }
            printf foutInstCfg "            { /* Vps_DssDispcAdvLcdTdmConfig */\n";
            if ($vect[72] ne '')    {
                    printf foutInstCfg "                $vect[72], /* dispcAdvLcdTdmConfig_vencId */\n";
            } else {
                    printf foutInstCfg "                0, /* dispcAdvLcdTdmConfig_vencId */\n";
            }
            if ($vect[73] ne '')    {
                    printf foutInstCfg "                $vect[73], /* tdmEnable */\n";
            } else {
                    printf foutInstCfg "                0, /* tdmEnable */\n";
            }
            if ($vect[74] ne '')    {
                    printf foutInstCfg "                $vect[74], /* noBitsPixel1Cycle1 */\n";
            } else {
                    printf foutInstCfg "                0, /* noBitsPixel1Cycle1 */\n";
            }
            if ($vect[75] ne '')    {
                    printf foutInstCfg "                $vect[75], /* noBitsPixel1Cycle2 */\n";
            } else {
                    printf foutInstCfg "                0, /* noBitsPixel1Cycle2 */\n";
            }
            if ($vect[76] ne '')    {
                    printf foutInstCfg "                $vect[76], /* noBitsPixel1Cycle3 */\n";
            } else {
                    printf foutInstCfg "                0, /* noBitsPixel1Cycle3 */\n";
            }
            if ($vect[77] ne '')    {
                    printf foutInstCfg "                $vect[77], /* bitAlignPixel1Cycle1 */\n";
            } else {
                    printf foutInstCfg "                0, /* bitAlignPixel1Cycle1 */\n";
            }
            if ($vect[78] ne '')    {
                    printf foutInstCfg "                $vect[78], /* bitAlignPixel1Cycle2 */\n";
            } else {
                    printf foutInstCfg "                0, /* bitAlignPixel1Cycle2 */\n";
            }
            if ($vect[79] ne '')    {
                    printf foutInstCfg "                $vect[79], /* bitAlignPixel1Cycle3 */\n";
            } else {
                    printf foutInstCfg "                0, /* bitAlignPixel1Cycle3 */\n";
            }
            if ($vect[80] ne '')    {
                    printf foutInstCfg "                $vect[80], /* noBitsPixel2Cycle1 */\n";
            } else {
                    printf foutInstCfg "                0, /* noBitsPixel2Cycle1 */\n";
            }
            if ($vect[81] ne '')    {
                    printf foutInstCfg "                $vect[81], /* noBitsPixel2Cycle2 */\n";
            } else {
                    printf foutInstCfg "                0, /* noBitsPixel2Cycle2 */\n";
            }
            if ($vect[82] ne '')    {
                    printf foutInstCfg "                $vect[82], /* noBitsPixel2Cycle3 */\n";
            } else {
                    printf foutInstCfg "                0, /* noBitsPixel2Cycle3 */\n";
            }
            if ($vect[83] ne '')    {
                    printf foutInstCfg "                $vect[83], /* bitAlignPixel2Cycle1 */\n";
            } else {
                    printf foutInstCfg "                0, /* bitAlignPixel2Cycle1 */\n";
            }
            if ($vect[84] ne '')    {
                    printf foutInstCfg "                $vect[84], /* bitAlignPixel2Cycle2 */\n";
            } else {
                    printf foutInstCfg "                0, /* bitAlignPixel2Cycle2 */\n";
            }
            if ($vect[85] ne '')    {
                    printf foutInstCfg "                $vect[85], /* bitAlignPixel2Cycle3 */\n";
            } else {
                    printf foutInstCfg "                0, /* bitAlignPixel2Cycle3 */\n";
            }
            if ($vect[86] ne '')    {
                    printf foutInstCfg "                $vect[86], /* tdmUnusedBits */\n";
            } else {
                    printf foutInstCfg "                0, /* tdmUnusedBits */\n";
            }
            if ($vect[87] ne '')    {
                    printf foutInstCfg "                $vect[87], /* tdmCycleFormat */\n";
            } else {
                    printf foutInstCfg "                0, /* tdmCycleFormat */\n";
            }
            if ($vect[88] ne '')    {
                    printf foutInstCfg "                $vect[88], /* tdmParallelMode */\n";
            } else {
                    printf foutInstCfg "                0, /* tdmParallelMode */\n";
            }
            printf foutInstCfg "            }, /* End Vps_DssDispcAdvLcdTdmConfig */\n";
            printf foutInstCfg "            { /* Vps_DctrlOutputInfo */\n";
            if ($vect[89] ne '')    {
                    printf foutInstCfg "                $vect[89], /* dCtrlOutInfo_vencId */\n";
            } else {
                    printf foutInstCfg "                0, /* dCtrlOutInfo_vencId */\n";
            }
            if ($vect[90] ne '')    {
                    printf foutInstCfg "                $vect[90], /* dCtrlOutInfo_dataFormat */\n";
            } else {
                    printf foutInstCfg "                0, /* dCtrlOutInfo_dataFormat */\n";
            }
            if ($vect[91] ne '')    {
                    printf foutInstCfg "                $vect[91], /* dvoFormat */\n";
            } else {
                    printf foutInstCfg "                0, /* dvoFormat */\n";
            }
            if ($vect[92] ne '')    {
                    printf foutInstCfg "                $vect[92], /* aFmt */\n";
            } else {
                    printf foutInstCfg "                0, /* aFmt */\n";
            }
            if ($vect[93] ne '')    {
                    printf foutInstCfg "                $vect[93], /* videoIfWidth */\n";
            } else {
                    printf foutInstCfg "                0, /* videoIfWidth */\n";
            }
            if ($vect[94] ne '')    {
                    printf foutInstCfg "                $vect[94], /* fidPolarity */\n";
            } else {
                    printf foutInstCfg "                0, /* fidPolarity */\n";
            }
            if ($vect[95] ne '')    {
                    printf foutInstCfg "                $vect[95], /* vsPolarity */\n";
            } else {
                    printf foutInstCfg "                0, /* vsPolarity */\n";
            }
            if ($vect[96] ne '')    {
                    printf foutInstCfg "                $vect[96], /* hsPolarity */\n";
            } else {
                    printf foutInstCfg "                0, /* hsPolarity */\n";
            }
            if ($vect[97] ne '')    {
                    printf foutInstCfg "                $vect[97], /* actVidPolarity */\n";
            } else {
                    printf foutInstCfg "                0, /* actVidPolarity */\n";
            }
            if ($vect[98] ne '')    {
                    printf foutInstCfg "                $vect[98], /* pixelClkPolarity */\n";
            } else {
                    printf foutInstCfg "                0, /* pixelClkPolarity */\n";
            }
            printf foutInstCfg "            }, /* End Vps_DctrlOutputInfo */\n";
            if ($vect[99] ne '')    {
                    printf foutInstCfg "            $vect[99], /* boardMode */\n";
            } else {
                    printf foutInstCfg "            0, /* boardMode */\n";
            }
            if ($vect[100] ne '')    {
                    printf foutInstCfg "            $vect[100], /* encDrvId */\n";
            } else {
                    printf foutInstCfg "            0, /* encDrvId */\n";
            }
            if ($vect[101] ne '')    {
                    printf foutInstCfg "            $vect[101], /* isSdVenc */\n";
            } else {
                    printf foutInstCfg "            0, /* isSdVenc */\n";
            }
            if ($vect[102] ne '')    {
                    printf foutInstCfg "            $vect[102], /* platformSocId */\n";
            } else {
                    printf foutInstCfg "            0, /* platformSocId */\n";
            }
            printf foutInstCfg "        },\n";			
        }
    $count++;
    }
printf foutGblCfg "};\n";
printf foutInstCfg "    }, \n";
printf foutInstCfg "};\n";
printf "Global config and Instance Config header files are generated\n";
close foutGblCfg;
close foutInstCfg;
close fin;

