/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 */

package runscript;

/*!
 *  ======== Run ========
 *
 */
metaonly module Run 
{

    /*!
     *  ======== runTest ========
     *  Runs a single MP test (comprised of 1 or more apps) on the appropriate
     *  dss sessions 
     */
    metaonly String runTest(String fileName, Int numCores, String refFile);
    
    /*!
     *  ======== tempLogDir ========
     */
    metaonly config String tempLogDir = "";
}
/*
 *  @(#) regression.mp; 1,0,0,24; 11-19-2010 17:08:21; /db/vtree/library/trees/regresstest/regresstest.git/src/ regresstest-a45
 */

