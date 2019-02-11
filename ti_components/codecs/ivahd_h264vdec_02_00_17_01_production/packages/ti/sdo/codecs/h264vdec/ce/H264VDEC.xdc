/*!
 *  ======== H264VDEC========
 *  H264VDEC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video3.IVIDDEC3, H264VDEC declares that it "is
 *  a" video3 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the H264VDEC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module H264VDEC inherits ti.sdo.ce.video3.IVIDDEC3
{
    readonly config ti.sdo.codecs.h264vdec.H264VDEC.Module alg =
        ti.sdo.codecs.h264vdec.H264VDEC;
    
    override readonly config String ialgFxns = "H264VDEC_TI_IH264VDEC";

    override readonly config String iresFxns = "H264VDEC_TI_IRES";

}
