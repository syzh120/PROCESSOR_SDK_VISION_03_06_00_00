/*!
 *  ======== JPEGVDEC========
 *  JPEGVDEC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video3.IVIDDEC3, JPEGVDEC declares that it "is
 *  a" video3 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the JPEGVDEC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module JPEGVDEC inherits ti.sdo.ce.video3.IVIDDEC3
{
    readonly config ti.sdo.codecs.jpegvdec.JPEGVDEC.Module alg =
        ti.sdo.codecs.jpegvdec.JPEGVDEC;
    
    override readonly config String ialgFxns = "JPEGVDEC_TI_IJPEGVDEC";

    override readonly config String iresFxns = "JPEGVDEC_TI_IRES";

}
