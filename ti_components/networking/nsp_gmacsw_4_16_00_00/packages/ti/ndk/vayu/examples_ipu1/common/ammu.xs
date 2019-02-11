/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

function AMMU_init()
{
    var AMMU = xdc.useModule('ti.sysbios.hal.ammu.AMMU');

    AMMU.configureAmmu = true;

    /*********************** Small Pages *************************/
    /* smallPages[0] & smallPages[1] are auto-programmed by h/w */
    /* Overwrite smallPage[1] so that 16K is covered. H/w reset value configures
    * only 4K */
    AMMU.smallPages[0].pageEnabled = AMMU.Enable_YES;
    AMMU.smallPages[0].logicalAddress = 0x00000000;
    AMMU.smallPages[0].translatedAddress = 0x55020000;
    AMMU.smallPages[0].translationEnabled = AMMU.Enable_YES;
    AMMU.smallPages[0].size = AMMU.Small_16K;
    AMMU.smallPages[0].volatileQualifier = AMMU.Volatile_FOLLOW;  
    AMMU.smallPages[0].L1_cacheable = AMMU.CachePolicy_CACHEABLE;

    /* Overwrite smallPage[1] so that 16K is covered. H/w reset value configures
    * only 4K */
    AMMU.smallPages[1].pageEnabled = AMMU.Enable_YES;
    AMMU.smallPages[1].logicalAddress = 0x40000000;
    AMMU.smallPages[1].translatedAddress = 0x55080000;
    AMMU.smallPages[1].translationEnabled = AMMU.Enable_YES;
    AMMU.smallPages[1].size = AMMU.Small_16K;
    AMMU.smallPages[1].volatileQualifier = AMMU.Volatile_FOLLOW;  


    /*********************** Medium Pages *************************/
    /* OCMC space is mapped */
    /* Make it L1 cacheable */
    AMMU.mediumPages[0].pageEnabled = AMMU.Enable_YES;
    AMMU.mediumPages[0].logicalAddress = 0x00300000;
    AMMU.mediumPages[0].translatedAddress = 0x40300000;
    AMMU.mediumPages[0].translationEnabled = AMMU.Enable_YES;
    AMMU.mediumPages[0].size = AMMU.Medium_256K;
    AMMU.mediumPages[0].L1_cacheable = AMMU.CachePolicy_CACHEABLE;
    AMMU.mediumPages[0].L1_writePolicy = AMMU.WritePolicy_WRITE_BACK;
    AMMU.mediumPages[0].L1_allocate    = AMMU.AllocatePolicy_ALLOCATE;
    AMMU.mediumPages[0].L1_posted = AMMU.PostedPolicy_POSTED;

    AMMU.mediumPages[1].pageEnabled = AMMU.Enable_YES;
    AMMU.mediumPages[1].logicalAddress = 0x63300000;
    AMMU.mediumPages[1].translatedAddress = 0x43300000;
    AMMU.mediumPages[1].translationEnabled = AMMU.Enable_YES;
    AMMU.mediumPages[1].size = AMMU.Medium_256K;
    AMMU.mediumPages[1].L1_cacheable = AMMU.CachePolicy_NON_CACHEABLE;
    AMMU.mediumPages[1].L1_posted = AMMU.PostedPolicy_NON_POSTED;
    AMMU.mediumPages[1].L2_cacheable = AMMU.CachePolicy_NON_CACHEABLE;
    AMMU.mediumPages[1].L2_posted = AMMU.PostedPolicy_NON_POSTED;

    /*********************** Large Pages *************************/

    /* config large page[0] to map 512MB VA 0x40000000 to Config space */    
    AMMU.largePages[0].pageEnabled = AMMU.Enable_YES;    
    AMMU.largePages[0].logicalAddress = 0x40000000;
    AMMU.largePages[0].translationEnabled = AMMU.Enable_NO;
    AMMU.largePages[0].size = AMMU.Large_512M;
    AMMU.largePages[0].L1_cacheable = AMMU.CachePolicy_NON_CACHEABLE;
    AMMU.largePages[0].L1_posted = AMMU.PostedPolicy_NON_POSTED;
    AMMU.largePages[0].L2_cacheable = AMMU.CachePolicy_NON_CACHEABLE;
    AMMU.largePages[0].L2_posted = AMMU.PostedPolicy_NON_POSTED;

    /* Code/Data: Large page  (512M); cacheable */
    AMMU.largePages[1].pageEnabled = AMMU.Enable_YES;
    AMMU.largePages[1].logicalAddress = 0x80000000;
    AMMU.largePages[1].translationEnabled = AMMU.Enable_NO;
    AMMU.largePages[1].size = AMMU.Large_512M;
    AMMU.largePages[1].volatileQualifier = AMMU.Volatile_FOLLOW;
    AMMU.largePages[1].L1_cacheable = AMMU.CachePolicy_CACHEABLE;
    AMMU.largePages[1].L1_posted = AMMU.PostedPolicy_POSTED;
    AMMU.largePages[1].L2_cacheable = AMMU.CachePolicy_NON_CACHEABLE;
    AMMU.largePages[1].L2_posted = AMMU.PostedPolicy_NON_POSTED;    

    /* Code/Data: Large page  (512M); cacheable */
    AMMU.largePages[2].pageEnabled = AMMU.Enable_YES;
    AMMU.largePages[2].logicalAddress = 0xA0000000;
    AMMU.largePages[2].translationEnabled = AMMU.Enable_NO;
    AMMU.largePages[2].size = AMMU.Large_512M;
    AMMU.largePages[2].volatileQualifier = AMMU.Volatile_FOLLOW;
    AMMU.largePages[2].L1_cacheable = AMMU.CachePolicy_CACHEABLE;
    AMMU.largePages[2].L1_posted = AMMU.PostedPolicy_POSTED;
    AMMU.largePages[2].L2_cacheable = AMMU.CachePolicy_NON_CACHEABLE;
    AMMU.largePages[2].L2_posted = AMMU.PostedPolicy_NON_POSTED;

    AMMU.largePages[3].pageEnabled = AMMU.Enable_YES;
    AMMU.largePages[3].logicalAddress = 0xC0000000;
    AMMU.largePages[3].translationEnabled = AMMU.Enable_NO;
    AMMU.largePages[3].size = AMMU.Large_512M;
    AMMU.largePages[3].L1_cacheable = AMMU.CachePolicy_NON_CACHEABLE;
    AMMU.largePages[3].L1_posted = AMMU.PostedPolicy_NON_POSTED;
    AMMU.largePages[3].L2_cacheable = AMMU.CachePolicy_NON_CACHEABLE;
    AMMU.largePages[3].L2_posted = AMMU.PostedPolicy_NON_POSTED;
}
