/*
 *  ======== GMACSW.xdc ========
 *  Empty module that brings in the GMACSW driver library.
 */

/*!
 *  ======== GMACSW ========
 *  This module contains two configuration parameters.
 */

metaonly module GMACSW
{
    enum Device
    {
        DEVICE_VAYU,
        DEVICE_TDA3XX,
        DEVICE_J5ECO,
        DEVICE_DM385,
        DEVICE_SUBARCTIC,
        DEVICE_CENTAURUS
    };

    /* Do not use intsrumented build by default */
    config Bool instrumentedBuild = false;
    /* Do not use TIFDTP build by default */
    config Bool tfdtpBuild = false;
    
    /* Select the Vayu device by default */
    config Device device = DEVICE_VAYU;
}
