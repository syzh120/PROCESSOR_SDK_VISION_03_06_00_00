/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 */

package runscript;

/*!
 *  ======== Regression Scripts ========   
 */
metaonly module Main 
{
    /* All required information/state for a regression cpu */
    metaonly struct RegressionCpu {
        String      buildName;      /* i.e. ti.platforms.evmDM6446  */
        String      ccsName;        /* i.e. C64XP_0                 */
        Bool        alwaysConnect;  /* Whether we need to always
                                       connect to this CPU          */
        Any         session;        /* DSS session for the CPU      */
    }
    
    /* Mapping element between platform and cpu */
    metaonly struct PlatformTargetMap {
        String      platform;      /* i.e. ti.platforms.evmDM6446   */
        String      target;        /* i.e. ti.targets.C64P          */
    }

    /*
     * The following config paramters should be set before calling run.
     */ 
    //!Read/Write the testList with the specified filename.
    metaonly config String testListFileName = "";
    
    //!The full CCS platform name as it appears in CCS setup
    metaonly config String CCSPlatform = "";
    
    //!'Friendly' name for the platform
    metaonly config String shortPlatformName = "";
    
    //!Contains everything we need to 'remember' for each cpu
    metaonly config RegressionCpu cpus[length] = [];
    
    //!Maps a platform name to a specific target
    metaonly config PlatformTargetMap platformTargetMap[length] = [];    
    
    //!The target configuration to run
    metaonly config String ccxmlConfigFile = "";

	metaonly config String gelFile = "";
    
    //!Run tests with the specified build profile
    metaonly config String profile = "";

    /*
     * The following config parameters are computed or parsed from the
     * command line.
     */   
    //!Read test list from file
    metaonly config Bool readTestList = false;

    //!Write test list to file only
    metaonly config Bool writeTestListOnly = false;

    //!Capsule of settings.xs file
    metaonly config Any settings;
    
    metaonly config Int numCores;

	metaonly config Int iter = 1;
    
    metaonly config String fileName;
    
    //!Enable trace
    metaonly config Bool enableTracing = false;

    /*!
     *  ======== run ========
     */
    metaonly Void run(Any args);
    
    /*!
     *  ======== addCpu ========
     */
    metaonly Void addCpu(String buildCpuName, String ccsName, Bool alwaysConnect);
    
    /*!
     *  ======== getFreeCpu ========
     */
    metaonly RegressionCpu getFreeCpu(String buildCpuName);
    
    /*!
     *  ======== getCpu ========
     *  Used to retrieve a specific CPU when multiple of a same type are present.
     */
    metaonly RegressionCpu getCpu(String buildCpuName, UInt cpuNum);

    /*!
     *  ======== containsCpu ========
     *  Return true if the RegressionPlatform contains the build cpu
     *  i.e. ti.platforms.evmTCI6488
     */
    metaonly Bool containsCpu(String buildCpuName);
    
    /*!
     *  ======== setPlatformTarget ========
     *  Called by user in testMP.xs to pick a single target for a given platform
     */
    metaonly Void setPlatformTarget(String platform, String target);
    
    /*!
     *  ======== getPlatformTarget ========
     *  Used by TestList module to filter by target based on user configuration
     *  supplied in setPlatformTarget.
     */
    metaonly String getPlatformTarget(String platform);    

    /*!
     *  ======== getSession ========
     */
    metaonly Any getSession(Int coreNum);

	/*!
     *  ======== loadGel ========
     */
    metaonly Any loadGel(Any debugServer);

    /*!
     *  ======== connectCpus ========
     */
    metaonly Void connectCpus(Any debugServer);
    
    /*!
     *  ======== terminateSessions ========
     */
    metaonly Void terminateSessions();
    
    /*!
     *  ======== resetCpus ========
     *  Resets all the used cpus
     */
    metaonly Void resetCpus();
    
    /*!
     *  ======== setUsed ========
     */
    metaonly Void setUsed(String ccsCpuName);
    
    /*!
     *  ======== setUnusedCpus ========
     */
    metaonly Void setUnusedCpus();
    
    /*!
     *  ======== loadProgram ========
     *  Print debugging messages...
     */
    metaonly Void logPrint(String str);
    
}
/*
 *  @(#) regression.mp; 1,0,0,24; 11-19-2010 17:08:21; /db/vtree/library/trees/regresstest/regresstest.git/src/ regresstest-a45
 */

