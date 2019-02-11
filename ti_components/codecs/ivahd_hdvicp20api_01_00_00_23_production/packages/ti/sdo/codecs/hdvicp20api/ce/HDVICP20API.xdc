/*!
 *  ======== HDVICP20API========
 *  HDVICP20API codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.universal.IUNIVERSAL, HDVICP20API declares that it "is
 *  a" universal algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the HDVICP20API algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module HDVICP20API inherits ti.sdo.ce.universal.IUNIVERSAL
{
    readonly config ti.sdo.codecs.hdvicp20api.HDVICP20API.Module alg =
        ti.sdo.codecs.hdvicp20api.HDVICP20API;
    
}
