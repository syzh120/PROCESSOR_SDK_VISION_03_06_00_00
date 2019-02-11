/*!
 *  ======== JPEGVENC========
 *  JPEGVENC codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video2.IVIDENC2, JPEGVENC declares that it "is
 *  a" video2 algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the JPEGVENC algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module JPEGVENC inherits ti.sdo.ce.video2.IVIDENC2
{
    readonly config ti.sdo.codecs.jpegvenc.JPEGVENC.Module alg =
        ti.sdo.codecs.jpegvenc.JPEGVENC;
    
    override readonly config String ialgFxns = "JPEGVENC_TI_IJPEGVENC";

    override readonly config String iresFxns = "JPEGVENC_TI_IRES";

}
