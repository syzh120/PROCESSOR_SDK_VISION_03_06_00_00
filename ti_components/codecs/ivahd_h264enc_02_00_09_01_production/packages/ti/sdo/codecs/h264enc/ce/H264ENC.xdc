/*!
 *  ======== H264ENC========
 *  H264ENC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video2.IVIDENC2, H264ENC declares that it "is
 *  a" video2 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the H264ENC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module H264ENC inherits ti.sdo.ce.video2.IVIDENC2
{
    readonly config ti.sdo.codecs.h264enc.H264ENC.Module alg =
        ti.sdo.codecs.h264enc.H264ENC;
    
    override readonly config String ialgFxns = "H264ENC_TI_IH264ENC";

    override readonly config String iresFxns = "H264ENC_TI_IRES";

}
