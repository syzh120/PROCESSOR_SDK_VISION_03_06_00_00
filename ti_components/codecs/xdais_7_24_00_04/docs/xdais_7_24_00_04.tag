<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>disclaimer.dox</name>
    <path>/db/toolsrc/library/tools/default/doxygen_templates/</path>
    <filename>disclaimer_8dox</filename>
  </compound>
  <compound kind="file">
    <name>doxygen.txt</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/</path>
    <filename>doxygen_8txt</filename>
  </compound>
  <compound kind="file">
    <name>acpy.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/</path>
    <filename>acpy_8h</filename>
    <includes id="idma_8h" name="idma.h" local="yes" imported="no">idma.h</includes>
    <member kind="function">
      <type>Int</type>
      <name>ACPY_complete</name>
      <anchorfile>acpy_8h.html</anchorfile>
      <anchor>adac525d6fc385adf253acc151059359b</anchor>
      <arglist>(IDMA_Handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY_configure</name>
      <anchorfile>acpy_8h.html</anchorfile>
      <anchor>a9cd1b627dce1ca6765504c5708b6c2ca</anchor>
      <arglist>(IDMA_Handle, IDMA_Params *)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY_start</name>
      <anchorfile>acpy_8h.html</anchorfile>
      <anchor>acc04e7169b9967d98524f66ebb11cc45</anchor>
      <arglist>(IDMA_Handle, Void *, Void *, Uns, IDMA_Params *)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY_wait</name>
      <anchorfile>acpy_8h.html</anchorfile>
      <anchor>a8a450a70109eead25f91454a6677e955</anchor>
      <arglist>(IDMA_Handle)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>acpy2.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/</path>
    <filename>acpy2_8h</filename>
    <includes id="idma2_8h" name="idma2.h" local="yes" imported="no">idma2.h</includes>
    <member kind="function">
      <type>Int</type>
      <name>ACPY2_complete</name>
      <anchorfile>acpy2_8h.html</anchorfile>
      <anchor>aae1a660830d10fd213a11dc4b53290ab</anchor>
      <arglist>(IDMA2_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY2_configure</name>
      <anchorfile>acpy2_8h.html</anchorfile>
      <anchor>a6281f71b9340d7100d158b86288f97f5</anchor>
      <arglist>(IDMA2_Handle handle, IDMA2_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY2_exit</name>
      <anchorfile>acpy2_8h.html</anchorfile>
      <anchor>ae41264cd4cbc6d7e9a97d789c47a8c37</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>Uns</type>
      <name>ACPY2_getChanObjSize</name>
      <anchorfile>acpy2_8h.html</anchorfile>
      <anchor>ac07469b1c500b9d363826296dad80d49</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY2_init</name>
      <anchorfile>acpy2_8h.html</anchorfile>
      <anchor>ae553e384aee9be2e33dc06a49937805c</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY2_initChannel</name>
      <anchorfile>acpy2_8h.html</anchorfile>
      <anchor>a44801f88134ec26501d1d7802b92be55</anchor>
      <arglist>(IDMA2_Handle handle, Int queueId)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY2_setDstFrameIndex</name>
      <anchorfile>acpy2_8h.html</anchorfile>
      <anchor>a7ff95609c73dd8c9f89e5e2193f4a120</anchor>
      <arglist>(IDMA2_Handle handle, Int frameIndex)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY2_setNumFrames</name>
      <anchorfile>acpy2_8h.html</anchorfile>
      <anchor>a053d3535deba7ca3b23a3abbb884d28d</anchor>
      <arglist>(IDMA2_Handle handle, Uns numFrames)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY2_setSrcFrameIndex</name>
      <anchorfile>acpy2_8h.html</anchorfile>
      <anchor>a18cb088c3f9cb7a509c22ee911764092</anchor>
      <arglist>(IDMA2_Handle handle, Int frameIndex)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY2_start</name>
      <anchorfile>acpy2_8h.html</anchorfile>
      <anchor>afcd3cc4eb1bf9f20d31e6e36e0527a75</anchor>
      <arglist>(IDMA2_Handle handle, IDMA2_AdrPtr src, IDMA2_AdrPtr dst, Uns count)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY2_startAligned</name>
      <anchorfile>acpy2_8h.html</anchorfile>
      <anchor>a5c78185624511a2a5b0d8fb907137a0d</anchor>
      <arglist>(IDMA2_Handle handle, IDMA2_AdrPtr src, IDMA2_AdrPtr dst, Uns count)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ACPY2_wait</name>
      <anchorfile>acpy2_8h.html</anchorfile>
      <anchor>a1a750df5e122aa6104912fac66490104</anchor>
      <arglist>(IDMA2_Handle handle)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iauddec.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>iauddec_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="iaudio_8h" name="iaudio.h" local="yes" imported="no">iaudio.h</includes>
    <class kind="struct">IAUDDEC_Obj</class>
    <class kind="struct">IAUDDEC_Params</class>
    <class kind="struct">IAUDDEC_DynamicParams</class>
    <class kind="struct">IAUDDEC_InArgs</class>
    <class kind="struct">IAUDDEC_Status</class>
    <class kind="struct">IAUDDEC_OutArgs</class>
    <class kind="struct">IAUDDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gae550832bf925622e32ea891f9a64f840</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga0447e3d9eba91c950b0ca6533f090b4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga9ba0561ce6c276ef9a4b9d6dc1b66aa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gacfdf5e7ab31ee37a9b168bbcf7d71309</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Obj</type>
      <name>IAUDDEC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga6634b0496d752d9e3ad71601d824867f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Obj *</type>
      <name>IAUDDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga849224ef7d8add16e7152e3c2cef1cb0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Params</type>
      <name>IAUDDEC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gacb141d33623cf82cc46d17fea7703e9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_DynamicParams</type>
      <name>IAUDDEC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga5820d588b117ad5217930662abac99f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_InArgs</type>
      <name>IAUDDEC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gaa9b870e05b3cbbf90dbf4330480e29e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Status</type>
      <name>IAUDDEC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gab809863924a3c0762af2b67492ed6de7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_OutArgs</type>
      <name>IAUDDEC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga45698ad1d6198f7cde140f48788a310a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga8a44a541760fefd4c41ea1d29c80d71e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Fxns</type>
      <name>IAUDDEC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gac12eb0bbd9b46fef4203abbb59034bba</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iauddec1.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>iauddec1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="iaudio_8h" name="iaudio.h" local="yes" imported="no">iaudio.h</includes>
    <class kind="struct">IAUDDEC1_Obj</class>
    <class kind="struct">IAUDDEC1_Params</class>
    <class kind="struct">IAUDDEC1_DynamicParams</class>
    <class kind="struct">IAUDDEC1_InArgs</class>
    <class kind="struct">IAUDDEC1_Status</class>
    <class kind="struct">IAUDDEC1_OutArgs</class>
    <class kind="struct">IAUDDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga2875d67b3c5af6d7a16b373ec21cf567</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga2ac49534acb4a9fef6c32355b9883664</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga690d6e129037630a13d1b80eb1e2480d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Obj</type>
      <name>IAUDDEC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga50c2c19b82f699c8db66b2deb8786b4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Obj *</type>
      <name>IAUDDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga2287de2327bdc6e94ada6971506a2fe4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Params</type>
      <name>IAUDDEC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>gaf00ecb15843c90924d700e36aaf599df</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_DynamicParams</type>
      <name>IAUDDEC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga1082e6d4d48745641f0870c050d874e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_InArgs</type>
      <name>IAUDDEC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>gaaaf5baa42d137368fddde42bd8b8a086</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Status</type>
      <name>IAUDDEC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga8bfe7fe4aaf4bdd967956c0145badf7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_OutArgs</type>
      <name>IAUDDEC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga9c77ccf6c02b80d5d7e4cb5f45254544</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga4c0ee4ad90447b42d3a39dd6e81ca3c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Fxns</type>
      <name>IAUDDEC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga3cf12da7344d61bf93655a0d032143e3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iaudenc.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>iaudenc_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="iaudio_8h" name="iaudio.h" local="yes" imported="no">iaudio.h</includes>
    <class kind="struct">IAUDENC_Obj</class>
    <class kind="struct">IAUDENC_Params</class>
    <class kind="struct">IAUDENC_DynamicParams</class>
    <class kind="struct">IAUDENC_InArgs</class>
    <class kind="struct">IAUDENC_Status</class>
    <class kind="struct">IAUDENC_OutArgs</class>
    <class kind="struct">IAUDENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga2c2cde30bd98faf8f6e88058e766c432</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>gac95ad430142a56f43f9f822372cd55fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga277eb1ae03f2becd10f2e62804e68876</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga8955b9b4eff0b4105d71a7e13e4b1292</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Obj</type>
      <name>IAUDENC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga5d9ff04b4365072edd2c884f82edd3f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Obj *</type>
      <name>IAUDENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga67b207a9e6d7ac649cf393bf9b89a758</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Params</type>
      <name>IAUDENC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga2dae626a844575f47e1c21cbcf840b35</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_DynamicParams</type>
      <name>IAUDENC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>gae0ec8b69b82b7b74261447fc165bc045</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_InArgs</type>
      <name>IAUDENC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>gaf5ff788677b23b690544cfa786a0f50c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Status</type>
      <name>IAUDENC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>gaf0f5c27286ce1a431b7a56dc618cf66f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_OutArgs</type>
      <name>IAUDENC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>gacaa7c792adc803608e262b3b8b27464b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga875abe1167c5304cec0cb23421f3215a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Fxns</type>
      <name>IAUDENC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga0bc230f35392261fbca693a29af3dd14</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iaudenc1.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>iaudenc1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="iaudio_8h" name="iaudio.h" local="yes" imported="no">iaudio.h</includes>
    <class kind="struct">IAUDENC1_Obj</class>
    <class kind="struct">IAUDENC1_Params</class>
    <class kind="struct">IAUDENC1_DynamicParams</class>
    <class kind="struct">IAUDENC1_InArgs</class>
    <class kind="struct">IAUDENC1_Status</class>
    <class kind="struct">IAUDENC1_OutArgs</class>
    <class kind="struct">IAUDENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gaca757d01864682f891f4e79e27612615</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga3b351ca3f8350018b9411570be9a0e63</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gace019d488c6e5825adcf3950246b2ea5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Obj</type>
      <name>IAUDENC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga2a374221a000c97a35d1b461d092a154</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Obj *</type>
      <name>IAUDENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga674429c3839d2412844c94f288c88493</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Params</type>
      <name>IAUDENC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga65b4efd16306faeb757913240b470810</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_DynamicParams</type>
      <name>IAUDENC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga77dc068499de50015a259e6e6d24f67a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_InArgs</type>
      <name>IAUDENC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga9e03d59eba817233e0ce4ec4bf9841ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Status</type>
      <name>IAUDENC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga8c69f4914aa7cb790ebaf233f881bff7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_OutArgs</type>
      <name>IAUDENC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gac4d65960aeb5375bd15f1fdc908b8568</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gab08988284a4cb6779e196509c28705d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Fxns</type>
      <name>IAUDENC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gaed934ee1e76ebff885651644504786d3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iaudio.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>iaudio_8h</filename>
    <member kind="enumeration">
      <name>IAUDIO_ChannelId</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga2f7957b5da562687498a612165664179</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_MONO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a5f4470f75c884f7e4b04ca5f14ad7acf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_STEREO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a99e682b79cf46c280e7bafb9470b8f2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_THREE_ZERO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179aeabcf85e87c1c856a80b9824220aaaa2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_FIVE_ZERO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a9f5cb587cdcfb58952ecebce56532568</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_FIVE_ONE</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a05f535ae3ec20c8f007b9139eda2be73</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_SEVEN_ONE</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a092297b5eee8fa4bf24b7bac35a5c8ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_ChannelMode</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga42c416b540264a57d8728b07d765b14d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_1_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da4a44a2c8361fe98d5a083c7a067933e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da8cf64356a7097cea1e401ab31d7f5f8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_11_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da97b04f3a5f55abc03ec813694b1236d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da66f93b5b1244b8c4386f7f2bfdd81783</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_1</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da1f7b4e0d6455df92a428c33848351b45</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_1</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da77f0db8024cbb1df8d501f11b3b6ee11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_2</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14dacafa604d4031971085a63e74c6a1377a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_2</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14dac912907baaca2ef193290fb54359d022</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_3</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da022f51b4b16ed20be3a67fba6247a54a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_3</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14dae2eaa060c3dc06e7126eb088f2639466</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_4</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da0de8b72246498dc39781fa6f8f88feb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_DualMonoMode</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga3d6a55ad8d567db30ddca14e0180b501</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_LR</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a91fc7e77ba226b15008e2bcdc54e196b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_LEFT</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a33cf98bc81668fe9dc4eae0f5c41780b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_RIGHT</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a7ac285c92ea3048e5ed006af3d453b42</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_LR_MIX</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a0358f0cc0ad00b1551e0f7387b112e3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_PcmFormat</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gac631266018b8f5df7df1e52f65c2757f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_BLOCK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ggac631266018b8f5df7df1e52f65c2757faa072981204cf2b0d1cdddce4d9644154</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_INTERLEAVED</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ggac631266018b8f5df7df1e52f65c2757fa12f80fc0827105d6dc1df1dda485d161</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_EncMode</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga1d8af2cbae15bc609badbb328ab3a08c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_CBR</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga1d8af2cbae15bc609badbb328ab3a08ca422efb88eb135a5212bfa6b3600c35a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_VBR</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga1d8af2cbae15bc609badbb328ab3a08caf311198449fe7e6c2e20f79d66b7a0e8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iimgdec.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>iimgdec_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <class kind="struct">IIMGDEC_Obj</class>
    <class kind="struct">IIMGDEC_Params</class>
    <class kind="struct">IIMGDEC_DynamicParams</class>
    <class kind="struct">IIMGDEC_InArgs</class>
    <class kind="struct">IIMGDEC_Status</class>
    <class kind="struct">IIMGDEC_OutArgs</class>
    <class kind="struct">IIMGDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga399a3c00c3d9181c9b84a86549c76344</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga4c2d7f1c15e1bfb70a61ae987979ad3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gaf11d65f2c57f70bfa994221f201fe483</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gac0a3c1ac74db21cce563ac1af0dcdcf9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Obj</type>
      <name>IIMGDEC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga4a37e31051dc54e2f24e31952aea3771</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Obj *</type>
      <name>IIMGDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gaafcce966766ae1ec2ba860294450603c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Params</type>
      <name>IIMGDEC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gae77c64aa29500fd75d6e7d79c8ae909d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_DynamicParams</type>
      <name>IIMGDEC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga21ebec27806ebbb0c1a0ce4263cd8b84</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_InArgs</type>
      <name>IIMGDEC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gaaec68bfa0d974501d8fe18b2d6633f53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Status</type>
      <name>IIMGDEC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga6caf0f4102b77f7840ea43101baa4b04</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_OutArgs</type>
      <name>IIMGDEC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga2ae8d6af59574eddb03bf185c03a9b85</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga6d702c2802e8827926120bfeef5de0ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Fxns</type>
      <name>IIMGDEC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga96d1dab6f581fa305a2d2de30e3e74c2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iimgdec1.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>iimgdec1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <class kind="struct">IIMGDEC1_Obj</class>
    <class kind="struct">IIMGDEC1_Params</class>
    <class kind="struct">IIMGDEC1_DynamicParams</class>
    <class kind="struct">IIMGDEC1_InArgs</class>
    <class kind="struct">IIMGDEC1_Status</class>
    <class kind="struct">IIMGDEC1_OutArgs</class>
    <class kind="struct">IIMGDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga71491761ce7894192d0953f62e87922e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga31103bf98612d017b2f5c11cc14ac842</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga184dc94b44712d77629d785cefe1398e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_Obj</type>
      <name>IIMGDEC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga7c18c8764f01b58c8acb40cdbc73f45a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_Obj *</type>
      <name>IIMGDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga8b9b9364f2c4232397b36890618b250e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_Params</type>
      <name>IIMGDEC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga1dc5bbefb7b02e6af196f5cd1974d1de</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_DynamicParams</type>
      <name>IIMGDEC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga5cc0992263406368f5de6dfd225230ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_InArgs</type>
      <name>IIMGDEC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga2fa41b603e298cfaa2e8675520779c3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_Status</type>
      <name>IIMGDEC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga60b6beba711cabc46b9c7c1b443709e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_OutArgs</type>
      <name>IIMGDEC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>gabb908d91ec302f5e671f24ac7c566d64</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga7bf45653f5c04d9407d13394663a896c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_Fxns</type>
      <name>IIMGDEC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga4d874f449b94550ca794ac4796fac454</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iimgenc.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>iimgenc_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <class kind="struct">IIMGENC_Obj</class>
    <class kind="struct">IIMGENC_Params</class>
    <class kind="struct">IIMGENC_DynamicParams</class>
    <class kind="struct">IIMGENC_InArgs</class>
    <class kind="struct">IIMGENC_Status</class>
    <class kind="struct">IIMGENC_OutArgs</class>
    <class kind="struct">IIMGENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>gac529fc95d138993ea754d7ec6018a76c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga784e32991d906518f37e7a5146f5bf13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga827d911bc03c756096d03677ecef5f39</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga04b132637a7c8ee29f0738fce76fed32</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Obj</type>
      <name>IIMGENC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga4217146884145131fe78ca50e2f6bcaa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Obj *</type>
      <name>IIMGENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga58729c682862e2e74a9b2abb916f4b88</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Params</type>
      <name>IIMGENC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga679f323646f1e14be4d9f868da227d94</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_DynamicParams</type>
      <name>IIMGENC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>gabde1297efe8f8e72bc2d3a7b4021420e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_InArgs</type>
      <name>IIMGENC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>gade8888b678afcee660768f9b1941a323</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Status</type>
      <name>IIMGENC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga23972a48a687c0e9368c1951e4125287</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_OutArgs</type>
      <name>IIMGENC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga58685c09a0cd079a38b4a9b9a488c88f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>gabe17217ceb746ff5b0e564a6f3dafa36</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Fxns</type>
      <name>IIMGENC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga637288210ec18230b78533fd7e649e0c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iimgenc1.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>iimgenc1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <class kind="struct">IIMGENC1_Obj</class>
    <class kind="struct">IIMGENC1_Params</class>
    <class kind="struct">IIMGENC1_DynamicParams</class>
    <class kind="struct">IIMGENC1_InArgs</class>
    <class kind="struct">IIMGENC1_Status</class>
    <class kind="struct">IIMGENC1_OutArgs</class>
    <class kind="struct">IIMGENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga9397909ae52d3bb547e18fd8719c333f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga28ded0a8bcf744f7ba289e9b6ae576ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>gad065eddb703a62fa12207544e8546f1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Obj</type>
      <name>IIMGENC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>gae883e427f4108a6268dfabb41ecc9425</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Obj *</type>
      <name>IIMGENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga93fe674dab191daf45489f5bf84134fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Params</type>
      <name>IIMGENC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga9d42d07332b63e9e52dc4269150ff28c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_DynamicParams</type>
      <name>IIMGENC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga1828bd15b50a8e53bc1d6c8894b7c2fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_InArgs</type>
      <name>IIMGENC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga0dbb4ebafcbb6338c02b0b93eac3bbd0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Status</type>
      <name>IIMGENC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga98a45ae63a86a4a872de58c32d3740f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_OutArgs</type>
      <name>IIMGENC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga7c68d329b86a4573b946685413235613</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga391d9f36711efa2b355c14a03af7abf8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Fxns</type>
      <name>IIMGENC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga125998b1a450463583b220ea0dae7ea5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ispeech_8h</filename>
    <member kind="enumeration">
      <name>ISPEECH_VoiceMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ga2a5ad3bdafe1e87e2aece51b52700694</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_VOICED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>gga2a5ad3bdafe1e87e2aece51b52700694aabfd422047de38c75ff1caf9f22c7ce0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_UNVOICED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>gga2a5ad3bdafe1e87e2aece51b52700694a980404cd1fc1ad41d588319dbe3ed14e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH_CompoundLaw</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>gaed9882c92cb24a565d63fb157a3bc0c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ggaed9882c92cb24a565d63fb157a3bc0c8a8913b9e1f47a5e7ab97578c12a115a06</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_ALAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ggaed9882c92cb24a565d63fb157a3bc0c8a254d39814c846c8f5574226162efb458</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_ULAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ggaed9882c92cb24a565d63fb157a3bc0c8a1edb2eb2e360b5292385c671181cfafd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ispeech1_8h</filename>
    <member kind="enumeration">
      <name>ISPEECH1_NullTrafficMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ga89ae95d0bce445642cc16c57c0d0968b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_NULLTRAFFICMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga89ae95d0bce445642cc16c57c0d0968ba87608e5344ca37912234e93b7da59630</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_NULLTRAFFICMODE_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga89ae95d0bce445642cc16c57c0d0968baa933263447c238bac7df6321e0a11694</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_NULLTRAFFICMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga89ae95d0bce445642cc16c57c0d0968bab4fa5328474e29188aee74797c414aec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_PostFilter</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gac1c8b96d345c0fe4220cdc18669223ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_POSTFILTER_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ggac1c8b96d345c0fe4220cdc18669223aca6f4c302f3c9af56f64806d0861abdd04</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_POSTFILTER_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ggac1c8b96d345c0fe4220cdc18669223acac8e86af79d47c31e04829919bd972705</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_POSTFILTER_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ggac1c8b96d345c0fe4220cdc18669223aca37e583ca98bc612bd7dd9c5c451b3cb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_VADFlag</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ga6a40ba3d92ffc5b64a9987f870f57f9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_VADFLAG_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga6a40ba3d92ffc5b64a9987f870f57f9aa4d73bb62c3d482112334d7d84cc3cce4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_VADFLAG_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga6a40ba3d92ffc5b64a9987f870f57f9aaa11a5dcd1ae9d5e026cc83cfbb330919</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_VADFLAG_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga6a40ba3d92ffc5b64a9987f870f57f9aa7e66df60583013e51ba279139d13e0b8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_amr.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ispeech1__amr_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ga566156cfc46f87e73de6bba8eba536c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_4P75</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a99fc4c000b12f09fdcad255694d96d9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_5P15</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a5e8739090838a47dded4ce9c617b2446</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_5P9</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a633eb6129d753bd00318c91d5c00647d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_6P7</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a61ffd17b289e507380d69e1eca1c2142</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_7P4</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a45de32cc24a76e2a16bb7f9eecdccb48</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_7P95</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a3d3312de4a395a0a154c13043e6be957</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_10P2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a7ca5663dc228a321dff14edaa5887aa1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_12P2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9af65cf724c197d3cad7dd932c44e7cba1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a4943c07dd5924193d6a0a8ce7986c295</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_CodecSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gaf6d3e11e5b975770afd11caadcfd8d20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_CODECSELECT_PRIMARY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaf6d3e11e5b975770afd11caadcfd8d20ab414f0b43b46c6407188ab18f07abcd5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_CODECSELECT_SECONDARY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaf6d3e11e5b975770afd11caadcfd8d20a06effe2e6cda9dce3ce1773be4a941ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_CODECSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaf6d3e11e5b975770afd11caadcfd8d20a055d66e70f1130f7dd8eab2f05e01e88</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_PackingType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gaeecf736d60bd00c5ac86924b1404ad90</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_IF1_NOCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90af79b43d1eb83abaa5510928b71a4abe4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_IF1_WITHCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90a387c71ba08310d9668dae3883fe3ec28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_IF2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90af1bbe3a63ca9d6f595b83fa6b91a424c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_MIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90a71f0423b70c34ca2afc083e5a62585e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPEFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90aa00c9bc982212f0c55d9f1477bb62ded</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_VADSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gabcb3c4ae9c054b69eabd71bde775d86f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_VADSELECT_VAD1</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggabcb3c4ae9c054b69eabd71bde775d86faf55aa3a28417e1d0da82b546a9b1789d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_VADSELECT_VAD2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggabcb3c4ae9c054b69eabd71bde775d86fa35a83e8d85620ee0316880049aef8078</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_VADSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggabcb3c4ae9c054b69eabd71bde775d86fa4789cd0dfd81240681e04f81d7ead9fd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_evrc.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ispeech1__evrc_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_NoisePreProc</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gac0650f1ca8b6e4b6770c038653594633</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NOISEPREPROC_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggac0650f1ca8b6e4b6770c038653594633a9265da05d970eef081d3dd7ce9dbd4be</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NOISEPREPROC_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggac0650f1ca8b6e4b6770c038653594633aea1b311ebb57531b23d73857aca828d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NOISEPREPROC_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggac0650f1ca8b6e4b6770c038653594633a7805bfa6106590db880f7bf892c680d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_TTYMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ga84ecf83f56e51c826bda7095a90b989c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989ca38d82305bbfabe8919932618e2fdbae3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_45P45BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989cae7259cf80bda232f425379647111b048</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_50BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989ca602b2e9a9e7a1dbaaeafa889230811ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989ca1d60ffd9d5228746176eff0117c948fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_Mode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gafe2167d2bb6dc8269af94931fdedc9f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_PREMIUM</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1ae8264ae8cb01ccb0953e29e0c3b21cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_STANDARD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a8fc2dd52641a64b43d8034b4c0acd1c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_ECONOMY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a044dbd71700d328377606f5285bdde2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_CAPACITYSAVE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a7d31d7179ec70e3e28954a6d989d688a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_HALFRATE_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a5920a92eccc31bc941e54ab46a84a80b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1ad54aeffbd74c41175c7c3f7d427ad144</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_NullTrafficMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gaf9e99a0ee5da7b5ccc1125cb851f62d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NULLTRAFFICMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggaf9e99a0ee5da7b5ccc1125cb851f62d5ac0a7d8a945501ece57576b2083109b51</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NULLTRAFFICMODE_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggaf9e99a0ee5da7b5ccc1125cb851f62d5a09e4988544590cc4e625e206f4492a95</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NULLTRAFFICMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggaf9e99a0ee5da7b5ccc1125cb851f62d5acd73322310099c31a2ff72efa14aff98</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_g722.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ispeech1__g722_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_G722_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>gac295a2de036479d0d0ed7b0664a9e176</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_BITRATE_RATE0</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>ggac295a2de036479d0d0ed7b0664a9e176a1d894b6e89d40900bfcba147e6f8b827</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_BITRATE_RATE1</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>ggac295a2de036479d0d0ed7b0664a9e176a88bbc54c47fdbb88e7fd8919aacafc4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_BITRATE_RATE2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>ggac295a2de036479d0d0ed7b0664a9e176ad17ce0b8ef52bbfee2a015dd7e924418</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_BITRATE_RATE3</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>ggac295a2de036479d0d0ed7b0664a9e176ae162cb433c4f245b7378ce466d0c07ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>ggac295a2de036479d0d0ed7b0664a9e176a585d72fb1c9625ed9efa3096f10f18a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G722_CodecSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>ga1353c3c849712e0709adba818caea0b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_CODECSELECT_NONITUMODE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>gga1353c3c849712e0709adba818caea0b8a5d8d9b028450107199bfffb5bebee792</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_CODECSELECT_ITUMODE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>gga1353c3c849712e0709adba818caea0b8a9fa58c61e2d05cca46d352590652e4fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_CODECSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>gga1353c3c849712e0709adba818caea0b8a94bdb07ea62d12e5e05607730b523465</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_g7221.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ispeech1__g7221_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_G7221_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>ga475f2396658334f14e87f0c7b29369e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G7221_BITRATE_24</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga475f2396658334f14e87f0c7b29369e7affa175c8d6f26adfb882b092a5d46a2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G7221_BITRATE_32</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga475f2396658334f14e87f0c7b29369e7a74cf5d33d219f0a9bf9d5c5dd4cd9130</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G7221_BITRATE_48</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga475f2396658334f14e87f0c7b29369e7a7ce021f6c3be432c82353ae502b6c491</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G7221_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga475f2396658334f14e87f0c7b29369e7aae637f95da55289db536dbe8bf4be58f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH2_G7221_SamplingRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>ga43703aaa2b3cf853bd549425787cbd7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH2_G7221_SAMPLINGRATE_WIDEBAND</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga43703aaa2b3cf853bd549425787cbd7eabe6965a9f25aeb890f86228d40b331a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH2_G7221_SAMPLINGRATE_SUPEWIDEBAND</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga43703aaa2b3cf853bd549425787cbd7eac4ad50e850479bd4b0b575b924c569d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH2_G7221_SAMPLINGRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga43703aaa2b3cf853bd549425787cbd7ea9ecedebcd3c8dc4938152e6745963232</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_g723.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ispeech1__g723_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_G723_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>ga3a60101c5d140281222eac55ceff3da7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_BITRATE_5P3</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga3a60101c5d140281222eac55ceff3da7a25ef1e08d5e98120471e2c1526c27d2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_BITRATE_6P3</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga3a60101c5d140281222eac55ceff3da7a1e8c817ed1c0bdb7fb55444d6e009353</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga3a60101c5d140281222eac55ceff3da7a27554cc9a39b340e0ecd8103719dbffd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G723_NoisePreProc</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>ga6030020ca3fe69e0d0aaf01728097eae</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_NOISEPREPROC_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga6030020ca3fe69e0d0aaf01728097eaeaf62d62d2826cc658130274930660ebb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_NOISEPREPROC_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga6030020ca3fe69e0d0aaf01728097eaeaae41fd25b630c16118a4ffd24276a990</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_NOISEPREPROC_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga6030020ca3fe69e0d0aaf01728097eaea889aecb01aca1afc4152f95a8616c147</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_g726.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ispeech1__g726_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_G726_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ga5842c3df33b0aec82142cf1fd3ece12e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_16</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12ead390f395f226d55baf122302237cdf96</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_24</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12eab03a295d41900a44a9c94f3c94baceb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_32</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12ea769ceb35bd641aac0e5531f1641285ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_40</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12ea8548d58b48b1e6ed42f18024d4793a0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12eac2a351d221bfea5d27b09134cb59e89f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G726_CompandingLaw</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gaa397870da5177152ea1b53fe9e3b6265</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265ad0d2189fda7ed821f96577af3b5ba01c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_ALAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265ada1a67c0602e35ec5c10fba0044d6eae</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_ULAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265a1177bc10761f7968fb1787cf2c5bf599</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265a386b0d978c9c63729567540b953c7105</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G726_PackingType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ga889c3788d8981cec15df6971d29306ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_PACKTYPE_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga889c3788d8981cec15df6971d29306eaadc717daa84241ac0f3964a2e5a0f564a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_PACKTYPE_RTPSPECIAL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga889c3788d8981cec15df6971d29306eaa3e3a96fa9418c89e58ee8dcd75868ada</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_PACKTYPEFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga889c3788d8981cec15df6971d29306eaa9cfac3209bb22296fa011e0875b37d27</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_ilbc.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ispeech1__ilbc_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_ILBC_CodecSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___i_l_b_c.html</anchorfile>
      <anchor>gae9f39439122ced4e48605f36eeae838c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_ILBC_CODECSELECT_20MS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___i_l_b_c.html</anchorfile>
      <anchor>ggae9f39439122ced4e48605f36eeae838ca00f4cc23be9bc2a5ac8813cd5016bfdf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_ILBC_CODECSELECT_30MS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___i_l_b_c.html</anchorfile>
      <anchor>ggae9f39439122ced4e48605f36eeae838cafc795d957f51cd2402f0d9f1ab33909a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_ILBC_CODECSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___i_l_b_c.html</anchorfile>
      <anchor>ggae9f39439122ced4e48605f36eeae838cac527f79667c672cd8637376288b4998d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_pcm.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ispeech1__pcm_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_PCM_CompandingLaw</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>ga88faff6d78d80fbb0d3712642a16e1de</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1dea9b50f6c66d7d1250dcede6c3076bdd45</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_ALAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1deaee6ede174249a7ee7b67daccf7437037</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_ULAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1deac8a7be49178242066ee82b6800905614</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1dea5b651f269b71e3d9cfa3fe8e6d494957</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_smv.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ispeech1__smv_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_NoisePreProc</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gab60bcb3149344cd20bc1d9d1696a208d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208da499e6a288509dc326fa6b2a3a211d092</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_NSA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208da5adad45c8630058c96bdafdb030931f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_NSB</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208dab44c90dd52dc8fa6cf0c528ffd540e77</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208da39b444aeb37c32f83aee67c415679c04</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_VADSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gafb1b4ac5540a4d13c730aaf88dc023be</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_VADSELECT_VADA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggafb1b4ac5540a4d13c730aaf88dc023bea1c29ab48b1ef4af475eb3e95c3e99613</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_VADSELECT_VADB</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggafb1b4ac5540a4d13c730aaf88dc023bea6b4ba999b85279488c3db4cae5aee7f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_VADSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggafb1b4ac5540a4d13c730aaf88dc023bea7db43399885c4cf5f1d122913fb1f0ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_TTYMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gad14fd77adfb92f65088ef0b2e6affebd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebdafe82060bfabefca805a51b04c4381003</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_45P45BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebda0105f17fb6d97417b56dccc9fde3c73e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_50BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebda34cd37f4c8438ade28d24ba1bf3d401b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebda3bbed1bf636d4ccbca35915ca01cff7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_DTMFMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ga91d61a3a68a62af8f73afb871f1d0d5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DTMFMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga91d61a3a68a62af8f73afb871f1d0d5eabb2bce58703d51269e15c8a9bbbcc11f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DTMFMODE_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga91d61a3a68a62af8f73afb871f1d0d5ea325b10e0073a2d82e2d272b2dba7149e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DTMFMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga91d61a3a68a62af8f73afb871f1d0d5eafa3d0d05dcad59534119e6d6f60326a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_DataMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ga9edbd6e156d41f8673e3c26841e4d1bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfa2c0c4bae0b4e38ec003b221f01bc6c4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_HALFRATE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfae9e8887b1b23fc33614aab40523f7f5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_FULLRATE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfa02c442553dc94438337a7f0b5217d587</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfa94de3a5a683830f5e91b1f488a7598d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_Mode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gae79f94ea770cb63e97b6b08e7021a7d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_PREMIUM</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a605f932ca11a86e867b24a87f7c2cb4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_STANDARD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a0a3ab57cb83cc3b78664e5f8ee9dc0af</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_ECONOMY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a30a76e29dc26f9d6b58461669bbc485f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_CAPACITYSAVE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a3013d7d320c975226bb2785ce39ca852</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_PREMIUM_HALFRATE_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a764290efa25fc2f82cba26bed3b788ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_STANDARD_HALFRATE_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a02765b3d59b321e563dcfb2aefdeb8b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a04f904d973435832277167859b16647b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_wbamr.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ispeech1__wbamr_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_WBAMR_PackingType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>ga8561c34af4f9307ee99eec22b9023da7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_IF1_NOCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a0fefa4be1b4fb97d523329d3bbc3d42e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_IF1_WITHCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a54c89d0a6ae8cb89e5097e39a5e4b06d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_IF2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a67d42cd4150cd7c05378bc1960a92375</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_MIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7acc83cc0d4a577f3f93025e2eff1e2bb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPEFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a568e1ddb1a8b6fff6d9c018c9ac3c7a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_WBAMR_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>ga60889eeb323f514221f3623e9f749716</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_6P60</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a7821bf03d8f659a4835541eb711741e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_8P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a5109ab789372f28d132350cef02cbe70</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_12P65</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a6cf6726fa2af44d0362bebdbbb05b642</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_14P25</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a823b5ea1854bf86a1534e790e1410b3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_15P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a82efce13fac3031b423f01efa1e00969</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_18P25</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716ab306cb8177634d2dadd04c0ab3aadb32</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_19P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716abf4b551e950f3dca496dd1781d7d8811</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_23P05</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716adc1493eee4d5e1df49cade040980d720</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_23P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a45f6d3b08c97d14e0e4017c9328bc965</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716ac599e0494b8cbc4788a5abf95232d87f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>isphdec.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>isphdec_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ispeech_8h" name="ispeech.h" local="yes" imported="no">ispeech.h</includes>
    <class kind="struct">ISPHDEC_Obj</class>
    <class kind="struct">ISPHDEC_Params</class>
    <class kind="struct">ISPHDEC_DynamicParams</class>
    <class kind="struct">ISPHDEC_InArgs</class>
    <class kind="struct">ISPHDEC_Status</class>
    <class kind="struct">ISPHDEC_OutArgs</class>
    <class kind="struct">ISPHDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga1f604442aeef3232e6acc17de9ab51be</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga59bee2fd448023ee04185aaf874cfb45</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga6f7990140490a16e025ffc1d670503a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga48b7104fbe8c5c6cbe2d17b7725e278b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Obj</type>
      <name>ISPHDEC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>gabf3985c40fe62d218e3e746f6bb1f476</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Obj *</type>
      <name>ISPHDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga31722647a0a3b99c36ef57af89d1351a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Params</type>
      <name>ISPHDEC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga03ad8e6acbd271d49c8ba35094709fff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_DynamicParams</type>
      <name>ISPHDEC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga2993b719fc8801698bbd1cf7a28161ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_InArgs</type>
      <name>ISPHDEC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga25a73337c1b6b67ef315490e5873e521</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Status</type>
      <name>ISPHDEC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>gaa4dd6d6f5dfbcfec97f62b25771bc7e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_OutArgs</type>
      <name>ISPHDEC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>gaace4fafa512b9570b0591d3887233561</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga73cebce9e1ccbbb0afbb14a4f984a94e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Fxns</type>
      <name>ISPHDEC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga52c95d9aeafde3769cd70225a108dbd2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>isphdec1.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>isphdec1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <class kind="struct">ISPHDEC1_Obj</class>
    <class kind="struct">ISPHDEC1_Params</class>
    <class kind="struct">ISPHDEC1_DynamicParams</class>
    <class kind="struct">ISPHDEC1_InArgs</class>
    <class kind="struct">ISPHDEC1_Status</class>
    <class kind="struct">ISPHDEC1_OutArgs</class>
    <class kind="struct">ISPHDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga87514ee862e0b5a35fcf460a65277a59</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga4d2a2279596c72d1d505a94504af9028</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga712c57b5a16ed53f484260f8ea48c1ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_Obj</type>
      <name>ISPHDEC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaac7e3af97812cbcdb7541ee5765e3d62</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_Obj *</type>
      <name>ISPHDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga65c6e2d620b2b46594453ed84ded159f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_Params</type>
      <name>ISPHDEC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaae2328eefd20007f1193b99877cdabc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_DynamicParams</type>
      <name>ISPHDEC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga38991e2c05062852fe48758b52f4fb0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_InArgs</type>
      <name>ISPHDEC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga04ee73d7eec05a20e95f8026763dfcc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_Status</type>
      <name>ISPHDEC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga4e817a5cec631fe3ad390c43da78dfb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_OutArgs</type>
      <name>ISPHDEC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga742ed560c798cc48436f89deb14542d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaef02eb7c18d91b4d4183284c0c4c1d79</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_Fxns</type>
      <name>ISPHDEC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga8124c15f66854b30e6326f78ffef1b9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPHDEC1_FrameType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga80a8f44022a98fb899a102310489ebf9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SPEECHGOOD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a1813dc29630e6fd7c6054187077f1b0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SIDUPDATE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a10c27d875c65247b78a99e1d28916dbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_NODATA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a46a224a6fd50ee1f3fe602c64759c158</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SPEECHLOST</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9ad7f3cff31625d40f310aaf0a575c1117</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_DEGRADED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9abce8dcb8ad83419dc8225b66d2a36c84</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_BAD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9ab576985e54ff855753483500e17362ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SIDFIRST</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a6bcbda5d5df41d58f5a5034fdabffed2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SIDBAD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a4cf9a9b2ba2919adf36aac69de785623</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_ONSET</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a0a642d1a2df6645d04a98d198b42a5b3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>isphenc.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>isphenc_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ispeech_8h" name="ispeech.h" local="yes" imported="no">ispeech.h</includes>
    <class kind="struct">ISPHENC_Obj</class>
    <class kind="struct">ISPHENC_Params</class>
    <class kind="struct">ISPHENC_DynamicParams</class>
    <class kind="struct">ISPHENC_InArgs</class>
    <class kind="struct">ISPHENC_Status</class>
    <class kind="struct">ISPHENC_OutArgs</class>
    <class kind="struct">ISPHENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gaa70981aaff27acca8dc15214ad0538ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga7e16b5ce02a4ae9c232445e1b1628f78</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gac472f9baf3f8de53cfef7d83a05df2fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga3769ec58a3fb188995557ab5f4986a0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Obj</type>
      <name>ISPHENC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga0a9e3d70ceb2e325ce5dd936acf32627</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Obj *</type>
      <name>ISPHENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga53d4faeb65284507a1eab034036a11ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Params</type>
      <name>ISPHENC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gaf645de0a409f1f764ae9b957267b3d1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_DynamicParams</type>
      <name>ISPHENC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gab3320909767956c29645f21df627119f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_InArgs</type>
      <name>ISPHENC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga1cb1ad45116d81d3f36778e5212bce70</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Status</type>
      <name>ISPHENC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga10dd91e813a3f77d33b3159467114fe6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_OutArgs</type>
      <name>ISPHENC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gad186fc61c770aff4e10a815e8178f6ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga835dc5261cc96bd0c6a77c1b33f5f197</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Fxns</type>
      <name>ISPHENC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga1bc5d2ae806ac94ac61781db9e02ef2c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>isphenc1.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>isphenc1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <class kind="struct">ISPHENC1_Obj</class>
    <class kind="struct">ISPHENC1_Params</class>
    <class kind="struct">ISPHENC1_DynamicParams</class>
    <class kind="struct">ISPHENC1_InArgs</class>
    <class kind="struct">ISPHENC1_Status</class>
    <class kind="struct">ISPHENC1_OutArgs</class>
    <class kind="struct">ISPHENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga332d5aa164c31b5681b2cea91d7e5016</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga22ade7510d7d35abb25a60b64f44a92d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga8f31ee15e0081314b41914efc29c5a9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_ENOOUTPUT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaa82f51e92fce79e8c507771c443b3e35</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Obj</type>
      <name>ISPHENC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga37332094aad46d9682ce2fbd5321acb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Obj *</type>
      <name>ISPHENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga995e9ed220499520c23c0df118d7acd8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Params</type>
      <name>ISPHENC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga25b6c4e0bc7ee4c8958c147c7a1ba945</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_DynamicParams</type>
      <name>ISPHENC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga6a52fdc116344056168895e8d84b88e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_InArgs</type>
      <name>ISPHENC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga4b2e68bc0c6fe193573a9404d9be7514</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Status</type>
      <name>ISPHENC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga0278e96b820ef8de6b796e3b5542151c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_OutArgs</type>
      <name>ISPHENC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga9e0d5cfb53ab43d7c8979cac9115c942</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga16523cd9d058f54acb8f5d1bd4bd5d97</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Fxns</type>
      <name>ISPHENC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gac862de82f55bd5902ae3c5ffd6e39344</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPHENC1_FrameType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga8e6571f54c1264844aa2c0e05119a624</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHENC1_FTYPE_SPEECH</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gga8e6571f54c1264844aa2c0e05119a624ae24818a9a9b1a23146162bb950ab035a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHENC1_FTYPE_SIDFRAME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gga8e6571f54c1264844aa2c0e05119a624aa8c57b4e299ff4038b40a5911eff281d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHENC1_FTYPE_NODATA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gga8e6571f54c1264844aa2c0e05119a624a6e2c23204ce4ae3dd2001aa610644638</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iuniversal.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>iuniversal_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <class kind="struct">IUNIVERSAL_Obj</class>
    <class kind="struct">IUNIVERSAL_Params</class>
    <class kind="struct">IUNIVERSAL_DynamicParams</class>
    <class kind="struct">IUNIVERSAL_InArgs</class>
    <class kind="struct">IUNIVERSAL_Status</class>
    <class kind="struct">IUNIVERSAL_OutArgs</class>
    <class kind="struct">IUNIVERSAL_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IUNIVERSAL_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga27f56f76d4fd15aa0d7e0ebbcb861d4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IUNIVERSAL_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gad0ebbb98143ab6995c1268efa4cbf150</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IUNIVERSAL_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gacb40d81bebf31e7de2267d6cb9bde3a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Obj</type>
      <name>IUNIVERSAL_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gab924ddc6fe5969446bf90dd1c5e3d155</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Obj *</type>
      <name>IUNIVERSAL_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaa47732c807c80b94d7f29cf72d9ed694</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Params</type>
      <name>IUNIVERSAL_Params</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga59a62f39d4be49588cff623d988567a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_DynamicParams</type>
      <name>IUNIVERSAL_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga016853eb31ba4b4d283e58c1e9b4c587</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_InArgs</type>
      <name>IUNIVERSAL_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga8bbbcec1866c91d201e96133dd864b5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Status</type>
      <name>IUNIVERSAL_Status</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga19fd3dae8089c3fb72cfb1204181f013</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_OutArgs</type>
      <name>IUNIVERSAL_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gade6b48848cae054b9d3e218bdb042f0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IUNIVERSAL_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga17756fe87be378872a1647a668f18c9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Fxns</type>
      <name>IUNIVERSAL_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaf653adad151d5fad6f46da48ee4d5e1d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividanalytics.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ividanalytics_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <class kind="struct">IVIDANALYTICS_Grid</class>
    <class kind="struct">IVIDANALYTICS_Rule</class>
    <class kind="struct">IVIDANALYTICS_Obj</class>
    <class kind="struct">IVIDANALYTICS_Params</class>
    <class kind="struct">IVIDANALYTICS_DynamicParams</class>
    <class kind="struct">IVIDANALYTICS_InArgs</class>
    <class kind="struct">IVIDANALYTICS_Status</class>
    <class kind="struct">IVIDANALYTICS_OutArgs</class>
    <class kind="struct">IVIDANALYTICS_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaf9760765b216cdbc5079be6e1904b795</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gac314c2ce1b08297ccfbf0c63dc3a257c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaebc9260d46c5e53d35bb4f5f100b96ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_SETRULE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga3d56d0f1a5afc78401314d4fdee63dc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_CLEARRULE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga44579981d799141f6e0368acf999b8e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_MAXTARGETS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gade504e11b8b0bc9e3925640b2cafebd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_MAXEVENTS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaa71cddcd1d8b054c48f9966866e386b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Grid</type>
      <name>IVIDANALYTICS_Grid</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga2953e064ae804a213eaac01be39ef4a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Rule</type>
      <name>IVIDANALYTICS_Rule</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga94eac45c9f8561d031d32e6f98fd9135</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Obj</type>
      <name>IVIDANALYTICS_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga9ee894169be9a6fddc0c204f1df3be03</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Obj *</type>
      <name>IVIDANALYTICS_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga26ad8d51394ef852e42cc1c4948de0eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Params</type>
      <name>IVIDANALYTICS_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaee12c2935ce12fde35d3b1aa30a825c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_DynamicParams</type>
      <name>IVIDANALYTICS_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaba23676c5dbd3f62cf4c51c9813bfff6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_InArgs</type>
      <name>IVIDANALYTICS_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gad2f186cdde8a6a983250555ab1249e17</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Status</type>
      <name>IVIDANALYTICS_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga936e9423f461aafaa57e3f8c3710050d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_OutArgs</type>
      <name>IVIDANALYTICS_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga69b8679986bd047c3aec860a7cc6c164</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDANALYTICS_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga5be3d2530a181c9826dc4c3322344132</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Fxns</type>
      <name>IVIDANALYTICS_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gad48dd8e1ca56c90a761d1a96ede97cb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_AnalysisMask</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga4a8b524c62f02622465884156f2c6f59</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_MOTIONDETECT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga4a8b524c62f02622465884156f2c6f59a3cad03f6d20ecbdc0103df4e73101e47</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTRACKING</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga4a8b524c62f02622465884156f2c6f59ad6da9e357c2c7721f04b1ff5beb38929</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_USERBASE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga4a8b524c62f02622465884156f2c6f59af48becd353153ab4285b4305d3467624</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_ObjectType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga40e54ed88eb97360b4ca8f244c2b9f62</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTYPE_VEHICLE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga40e54ed88eb97360b4ca8f244c2b9f62ad9daa80daa5e20d4c010d577a7347918</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTYPE_HUMAN</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga40e54ed88eb97360b4ca8f244c2b9f62ad82eb960014d7ede011678c5705ee1ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTYPE_USERBASE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga40e54ed88eb97360b4ca8f244c2b9f62ab6cd25f42da6d9e7e43ebb4ce272cf97</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_ActionType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga47e8c8886c5d35981380c922db1eeab4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_LOITER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4aba5736e40d9f5ab0ff2590d66e04edc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_ENTER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a86e2c5b11a0e4c20d245cb6de0cf8bb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_EXIT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4af0f133918f8b9575ca32e05f512270a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_APPEAR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a681d3cbb139a67f813899f0be3250f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_DISAPPEAR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a570191d5b93ea4345fb5bcb91f3a4d52</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSL2R</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a25a21e42fece6687a27205a828e025e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSR2L</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4aa4df30a99741c60e039d8042476922c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSU2D</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a82b0a4cbd8efa23126decf532abcf6e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSD2U</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a899876b69418a4b7187e73a1fd22e0a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_USERBASE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a20b606cf024b3812694d53e0f9985cde</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_ViewState</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gab02bfb6a7b2a76eac00f1bb7d3801662</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_VIEWSTATE_BAD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ggab02bfb6a7b2a76eac00f1bb7d3801662a42c1e0003605067a4def8cfd4c061dba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_VIEWSTATE_GOOD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ggab02bfb6a7b2a76eac00f1bb7d3801662a093b1e31c7bb032707492cfe72cd8fe8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividdec.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ividdec_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDDEC_Obj</class>
    <class kind="struct">IVIDDEC_Params</class>
    <class kind="struct">IVIDDEC_DynamicParams</class>
    <class kind="struct">IVIDDEC_InArgs</class>
    <class kind="struct">IVIDDEC_Status</class>
    <class kind="struct">IVIDDEC_OutArgs</class>
    <class kind="struct">IVIDDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>gafa63f96dc4a5430e21a8454a609fe205</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga3fc5e8b896808e13dc4a1dd037592c61</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga0f3f0d74b7b4895adc3601998895b930</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga3ff96fb69baef4d04b31682234957de1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Obj</type>
      <name>IVIDDEC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga3cb6d20f12f75e317c23bc589c52c138</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Obj *</type>
      <name>IVIDDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>gabc249717018b892fafca9425887b7464</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Params</type>
      <name>IVIDDEC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga9353fb92232e5ee72309b8e6b6adf93d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_DynamicParams</type>
      <name>IVIDDEC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga855fb68e46e6667d0290e10ce8f8e204</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_InArgs</type>
      <name>IVIDDEC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>gaf3d7a7eb7592d3dba52093f8fb343376</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Status</type>
      <name>IVIDDEC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>gab1338cbc538494391df2616888eaa5bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_OutArgs</type>
      <name>IVIDDEC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga58be26a3c32d08b313af8285a718fdc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga7f8d05603824403adb994fe59d55bdcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Fxns</type>
      <name>IVIDDEC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga7d40d5c65617921d788f4eb3da32a79b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividdec1.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ividdec1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDDEC1_Obj</class>
    <class kind="struct">IVIDDEC1_Params</class>
    <class kind="struct">IVIDDEC1_DynamicParams</class>
    <class kind="struct">IVIDDEC1_InArgs</class>
    <class kind="struct">IVIDDEC1_Status</class>
    <class kind="struct">IVIDDEC1_OutArgs</class>
    <class kind="struct">IVIDDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gaee746b34bc5327d7755c36e9dbb93f99</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gac76d0185e99e4dfb7d33f8b06d73a731</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga8c35fdf3e5022078dfee9064ac08f52a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_FREE_BUFF_SIZE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gaf9fd4bffd14decc067ecf3f2c486605e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Obj</type>
      <name>IVIDDEC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga88edd89a93bd20b4ba77a57ba6ed2807</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Obj *</type>
      <name>IVIDDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga3470ccaa78e2f267e1b8e08c7ae25455</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Params</type>
      <name>IVIDDEC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga47b5d070c3f24100d0c9552d703d3a8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_DynamicParams</type>
      <name>IVIDDEC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga5d174b8b524e1ee158218ee56ad39c48</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_InArgs</type>
      <name>IVIDDEC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gaf9d8d831cf2d98e947ab90be6d30aba4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Status</type>
      <name>IVIDDEC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga5fd52b2bb90deee30a14d971f0b88c13</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_OutArgs</type>
      <name>IVIDDEC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gae2902f6a2c9d664ad06ffae854d14a51</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga88cf5de26dfa5e05400b2d6e25ea027d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Fxns</type>
      <name>IVIDDEC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga97fe72473710158dbe2ad783c675d0e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDDEC1_FrameOrder</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga499b0864c81e20998f743b9e834e10c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC_DISPLAY_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gga499b0864c81e20998f743b9e834e10c6a9fb1a3543d4c48a7c5a7cf9242058746</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC_DECODE_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gga499b0864c81e20998f743b9e834e10c6a3a281632bb399cb0c73a18ebff327706</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC_FRAMEORDER_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gga499b0864c81e20998f743b9e834e10c6aebd67fc7b931e0796cfa9a970137b12a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividdec2.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ividdec2_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDDEC2_Obj</class>
    <class kind="struct">IVIDDEC2_Params</class>
    <class kind="struct">IVIDDEC2_DynamicParams</class>
    <class kind="struct">IVIDDEC2_InArgs</class>
    <class kind="struct">IVIDDEC2_Status</class>
    <class kind="struct">IVIDDEC2_OutArgs</class>
    <class kind="struct">IVIDDEC2_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_MAX_IO_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaaf8c9523a27942aa46eba097398a0e49</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gac1f0ebc291c92f796a5144fa57f7390f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga7c8386cbcd58bcb8a16e15df6587f3f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gafa7a5979f7945ff9ce5822c8f5fa57d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_Obj</type>
      <name>IVIDDEC2_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaa23fa0665cc8848f3d30e7b654b850ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_Obj *</type>
      <name>IVIDDEC2_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gab044a3dd5967ff04c487062ed0586c2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_Params</type>
      <name>IVIDDEC2_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaad981f1fbf560cc8d7cf472423136830</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_DynamicParams</type>
      <name>IVIDDEC2_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga1cdd25796b18fba15e2198eee81f2900</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_InArgs</type>
      <name>IVIDDEC2_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gac94e861061dbc29600e7bc6443a9067a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_Status</type>
      <name>IVIDDEC2_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga9f508292db11280258aa94da832fc66d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_OutArgs</type>
      <name>IVIDDEC2_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga54a24dd5672ee41aab45540fd838ce77</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC2_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga8b9180923c067cbb47115d18189501c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_Fxns</type>
      <name>IVIDDEC2_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga95681f816462ba6be5dfc125782e8569</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDDEC2_FrameOrder</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga31f21bf0ec796b5506cd8a0f0cf7710f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC2_DISPLAY_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gga31f21bf0ec796b5506cd8a0f0cf7710fa4dc184c19c62190e5f933e46e5bccc2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC2_DECODE_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gga31f21bf0ec796b5506cd8a0f0cf7710fa33ea07222ede0a10cb27bad4b9db445d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC2_FRAMEORDER_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gga31f21bf0ec796b5506cd8a0f0cf7710fa3599bb4a0d320e3e36d2aa49a7ae79e3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividdec2.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/split/</path>
    <filename>split_2ividdec2_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">../xdm.h</includes>
    <includes id="ividdec2_8h" name="ividdec2.h" local="yes" imported="no">../ividdec2.h</includes>
    <class kind="struct">IVIDDEC2FRONT_Obj</class>
    <class kind="struct">IVIDDEC2BACK_Obj</class>
    <class kind="struct">IVIDDEC2FRONT_Status</class>
    <class kind="struct">IVIDDEC2FRONT_OutArgs</class>
    <class kind="struct">IVIDDEC2FRONT_Fxns</class>
    <class kind="struct">IVIDDEC2BACK_Fxns</class>
    <member kind="typedef">
      <type>struct IVIDDEC2FRONT_Obj</type>
      <name>IVIDDEC2FRONT_Obj</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga4786fd8ccf9177f92eef375a77db3b85</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2FRONT_Obj *</type>
      <name>IVIDDEC2FRONT_Handle</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaaa273ba82e5f6d894000c4031d905776</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2BACK_Obj</type>
      <name>IVIDDEC2BACK_Obj</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga240b2f2128f41b53c5fdacf96449ada7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2BACK_Obj *</type>
      <name>IVIDDEC2BACK_Handle</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga8aedc496483d9ad90fb544045934648d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2FRONT_Status</type>
      <name>IVIDDEC2FRONT_Status</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaed14e1cec0b623b4555118c2a15bd3fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2FRONT_OutArgs</type>
      <name>IVIDDEC2FRONT_OutArgs</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga23347d6ee3bf77df5feeca7d4356a227</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2FRONT_Fxns</type>
      <name>IVIDDEC2FRONT_Fxns</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga9f561432b2d206ccf19f62b871019840</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2BACK_Fxns</type>
      <name>IVIDDEC2BACK_Fxns</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaec42b2f747b1a47d02fe3d06a8a24256</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividdec3.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ividdec3_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDDEC3_Obj</class>
    <class kind="struct">IVIDDEC3_Params</class>
    <class kind="struct">IVIDDEC3_DynamicParams</class>
    <class kind="struct">IVIDDEC3_InArgs</class>
    <class kind="struct">IVIDDEC3_Status</class>
    <class kind="struct">IVIDDEC3_OutArgs</class>
    <class kind="struct">IVIDDEC3_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC3_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga62d249f67b8956db313fdde1bbf9e7bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC3_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gaa96164ab594abaa53a5d093f1118d598</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC3_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga9a551797046d313c29221d0a33a31ab0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_Obj</type>
      <name>IVIDDEC3_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gaf53c38e661114ed5dcabd35959f33397</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_Obj *</type>
      <name>IVIDDEC3_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga22f05e003b8d3e6421a43a6613a099a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_Params</type>
      <name>IVIDDEC3_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga3135bd1065774979da46dbc1a9b50895</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_DynamicParams</type>
      <name>IVIDDEC3_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gac4bf6713614802244d3f8206c0586b8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_InArgs</type>
      <name>IVIDDEC3_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga81b8cd90c54f029dac00b34871157577</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_Status</type>
      <name>IVIDDEC3_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga5e1e45b174202f8f5b9ef3042bf980d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_OutArgs</type>
      <name>IVIDDEC3_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga3887cf6a6fd26cbfe837eaf132850cf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC3_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga383b7ba75a305ad392d6acddbaf05f24</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_Fxns</type>
      <name>IVIDDEC3_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gaa3804ddf72db7324738e9b30b53293e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDDEC3_displayDelay</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga0719d3976b9704b17af4682c342e5b9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_AUTO</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9cad94dfba879f7d9affd9eeee52edf6491</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DECODE_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9caf99e7b194c6010ce16cc6467ee5ba3a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_1</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca651a402ab85ff0308874189db63cba62</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_2</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9cad3081be4fbc4f01801d4fba5eda5d97d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_3</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9cadb475d5e9998c276bd4ec65c52985cec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_4</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca0f315555ea55aff89fb367923662edba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_5</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca5c5ee506fa0008fbabccfd7d60b18edf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_6</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca100b919cc7f4dafdacabfbfb0e8fa7d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_7</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9cafe5e43674e632c2c4e851e6a9c1d4cdf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_8</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca3eee04ba68d82f6fc64df46448f53162</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_9</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9cac13725a8fc8ed26cfb15d7d85addc41f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_10</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca63910a5c260b16bee0e20d137061bafe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_11</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca83e775772411fd6151e53a2aefc0f8d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_12</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca5b44481490fa61a6278d6bf10b4061ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_13</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9caa80b3374dd5755352ff4325720a76594</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_14</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca1b7149e0ccc76db7bc55fa2cee6a7eca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_15</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca3a70527a1d082cd8e9a5526dd9f3950a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_16</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca2c29517c49d9e8375d4e1a6e5bfa2d97</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAYDELAY_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca7017dd8fc0362645bce26ee765700017</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDDEC3_DisplayBufsMode</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gaa0707d1c6133c25dc9a36f1c0f8b29f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAYBUFS_EMBEDDED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ggaa0707d1c6133c25dc9a36f1c0f8b29f5a603aedffe63a4a5efe368897e5fa0dc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAYBUFS_PTRS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ggaa0707d1c6133c25dc9a36f1c0f8b29f5a57c0b7265e5564379afd5c842f992887</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividenc.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ividenc_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDENC_Obj</class>
    <class kind="struct">IVIDENC_Params</class>
    <class kind="struct">IVIDENC_DynamicParams</class>
    <class kind="struct">IVIDENC_InArgs</class>
    <class kind="struct">IVIDENC_Status</class>
    <class kind="struct">IVIDENC_OutArgs</class>
    <class kind="struct">IVIDENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaeba527be430e1584897bc410ef06e08a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf31926403a1beba354092c33e6f8f41f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf0d8e925b556bc7d992afb7dc9005fe7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf08f3e2a75c1e39a184835d0683ca88e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Obj</type>
      <name>IVIDENC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gad44e237f9d57d8025b5c71228bed12bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Obj *</type>
      <name>IVIDENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gafe560b65239e58d0a48897db58ee33f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Params</type>
      <name>IVIDENC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>ga92af648d6d4edbae2b3a346fba9279c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_DynamicParams</type>
      <name>IVIDENC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gafe1dff162a002aae2dea5e7aab7a4208</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_InArgs</type>
      <name>IVIDENC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>ga05e0198b2f43284db0c107bcb1717b4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Status</type>
      <name>IVIDENC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>ga2ae6b7f1d67de2793d34db08197a487b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_OutArgs</type>
      <name>IVIDENC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf4063ab92747aadbef7bf42de9b0baac</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>ga13eaed2bcde87e35269eed69590e2313</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Fxns</type>
      <name>IVIDENC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gac46a9b4cbc916b66badaf5bbbe08c1ac</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividenc1.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ividenc1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDENC1_Obj</class>
    <class kind="struct">IVIDENC1_Params</class>
    <class kind="struct">IVIDENC1_DynamicParams</class>
    <class kind="struct">IVIDENC1_InArgs</class>
    <class kind="struct">IVIDENC1_Status</class>
    <class kind="struct">IVIDENC1_OutArgs</class>
    <class kind="struct">IVIDENC1_MbData</class>
    <class kind="struct">IVIDENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>gaf7b49aed126ab846bbcff9bb2d481533</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga8022d457cb04187a3b1a055eaa2d1629</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga1623748edce151d19caed068981773f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Obj</type>
      <name>IVIDENC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga7fd2f4ad244a9912b6a73b6151636600</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Obj *</type>
      <name>IVIDENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga953dc9cc5ece87d8b371bd2adbb5082f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Params</type>
      <name>IVIDENC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga95a9ebe6f467dd8194f4ca4826ab4f80</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_DynamicParams</type>
      <name>IVIDENC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga1a643f697bb5f0576383ebacc765d060</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_InArgs</type>
      <name>IVIDENC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>gaf935d97801c46b6fd6948867304f519f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Status</type>
      <name>IVIDENC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga48a16e03cc9f32885a41e7477bc8cf96</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_OutArgs</type>
      <name>IVIDENC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga74410ff6b9cf0620997b7a28fb72e21f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga2654e133ba490dec6e8dfa56d1b633ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_MbData</type>
      <name>IVIDENC1_MbData</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>gac1056d79229e955cf4a038590b596ef6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Fxns</type>
      <name>IVIDENC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga2866bd03283e54e2850c85a4c366d2a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividenc2.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ividenc2_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDENC2_Obj</class>
    <class kind="struct">IVIDENC2_Params</class>
    <class kind="struct">IVIDENC2_DynamicParams</class>
    <class kind="struct">IVIDENC2_InArgs</class>
    <class kind="struct">IVIDENC2_Status</class>
    <class kind="struct">IVIDENC2_OutArgs</class>
    <class kind="struct">IVIDENC2_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC2_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gaf2dc089029d9c193e6b6013197a49c49</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC2_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga4d7854622164735b48281a6b1a1ce352</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC2_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga0d3be28d9668178b05e0480c126c6f30</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC2_DEFAULTPROFILE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga73035620aa9c4cca081c2d3dc2129672</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC2_DEFAULTLEVEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga03051d2b393c1f4158178be021564f77</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_Obj</type>
      <name>IVIDENC2_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gabe1399751de5650dba249f7a8e0c9d6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_Obj *</type>
      <name>IVIDENC2_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga33a694f32ec23e1b2373f67ad7813028</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_Params</type>
      <name>IVIDENC2_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gaf55caadd47cd178c3c6af1e2c1102225</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_DynamicParams</type>
      <name>IVIDENC2_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga20550d2468a68111577de21dedbbabb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_InArgs</type>
      <name>IVIDENC2_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga904e0eda063ee36b18e959a1f58611d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_Status</type>
      <name>IVIDENC2_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gac3fdc1b08aa9966ec019d2efbed08f47</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_OutArgs</type>
      <name>IVIDENC2_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga3aca71ed966c879613ad7a84cfff8b97</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDENC2_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gac0226c5443ead6aaac0d9ea820e27e81</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_Fxns</type>
      <name>IVIDENC2_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga03b5516d3d63bf5c057b6f034d8b8cc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDENC2_MotionVectorAccuracy</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga8088be87ca6eafdf5f623d8a5d8b987f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_MOTIONVECTOR_PIXEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga8088be87ca6eafdf5f623d8a5d8b987fab71610998e62a743493b24cbb8f0f202</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_MOTIONVECTOR_HALFPEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga8088be87ca6eafdf5f623d8a5d8b987fae39104696d0ce05ee736ff5534a3892d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_MOTIONVECTOR_QUARTERPEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga8088be87ca6eafdf5f623d8a5d8b987fa4bb08dea6ac1da2f6f77ea554cca41f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_MOTIONVECTOR_EIGHTHPEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga8088be87ca6eafdf5f623d8a5d8b987fa72a845a2972198e6c23b2a8cbf7712c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_MOTIONVECTOR_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga8088be87ca6eafdf5f623d8a5d8b987faa2ce163fd3f51dafca03f6c342b955f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDENC2_Control</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga6daaba9e22ed6089a7335e556eceb680</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_CTRL_NONE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga6daaba9e22ed6089a7335e556eceb680a359f62b36ce860505881ce5f2c402bdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_CTRL_FORCESKIP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga6daaba9e22ed6089a7335e556eceb680aef62ea0725426fee25d1ec2d91e0e0c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_CTRL_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga6daaba9e22ed6089a7335e556eceb680a40f91c92e28340005e5f16a1a50b0ba4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ivideo.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ivideo_8h</filename>
    <class kind="struct">IVIDEO_BufDesc</class>
    <class kind="struct">IVIDEO1_BufDescIn</class>
    <class kind="struct">IVIDEO1_BufDesc</class>
    <class kind="struct">IVIDEO2_BufDesc</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDEO2_MAX_IO_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga5c9c455b5a7783d4aaab50592f1c1996</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDEO_MAX_YUV_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga6f88ee11da1a2397e9ac263ce3cdd537</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDEO_MAX_NUM_PLANES</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gad5d38681f3fa9038f5c0c32208c5bdd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDEO_MAX_NUM_METADATA_PLANES</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga18bf9000c7c50a1bb4c3ebd7ff844c7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDEO_BufDesc</type>
      <name>IVIDEO_BufDesc</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga607cd0917b009907d55f34f949ae2a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDEO1_BufDescIn</type>
      <name>IVIDEO1_BufDescIn</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga6d67d40d38f51e957feb48a0c17c6596</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDEO1_BufDesc</type>
      <name>IVIDEO1_BufDesc</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga4eba22c6a353adf80871820aea0ae9e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDEO2_BufDesc</type>
      <name>IVIDEO2_BufDesc</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga2038d77f5028a340e635bdbd3373818e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_FrameSkip</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga6533d232a1c479dd185945e9c10c2665</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NO_SKIP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a8089c337b034434f8d53d279022272f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_P</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a767894b6dfb8639c2298f2d31e5fee51</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_B</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a04cadb8d98980be81a2a8a3fdc0372fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_I</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a551353a345ce3929adcff79aa741724b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a1b9f609f763ae7d8b36262986bcf54a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IB</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665ad111bef6602a59d8998ba5b4adbce87b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_PB</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a2e82d4e64d50c7fae14a1ef6720d3588</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IPB</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665ad9ffc660a588536746fbdb3d8b5b4f33</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IDR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a98a74bb46bd05f43c4db0ae8f8f66eb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_NONREFERENCE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a27d1acbd4d4a7e9bc2fa59cf38f773cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a0f0844d71eeb68ce22bc9d9f840d93f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_FrameType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga7ad672ade5d380f42e0cfcfb2b38b6df</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NA_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfab4b11cfbf563ce054e55fa482fb67f79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_I_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfac2b378280d95551841dddec15fad1d43</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_P_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfad788ad7b0f7a8517de35c5cd0aefc28d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_B_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa7dd078d4f4f309da2e73494ddd01f2b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_IDR_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfad7a86650a7f248f11133e52da2cb3e36</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_II_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa3be138a2faa58c0d85e2ae533526af79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_IP_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa40d74846bed523f78efbd61e42736dea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_IB_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa9cc0602312932db087a8e89b807c59a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PI_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa394be4bc1774efef87892bcb6387d4d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PP_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa9ae131687a2c620b50be3cb9bdf9ef69</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PB_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa3eb025061d65605fa2613a1219203662</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BI_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa99b48bce066d122f86f67d281709c970</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BP_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfaf6d75d28ac6582ed372ca9dcffd7a31e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BB_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfaa8dad288ba397bafe98f9d3dcda06efd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_I_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfac0c3748111b37e34c2652e311b367f18</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_P_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa068cd4d6a1d797d1b3eba96255c64b5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_B_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfac34147d75fecab15f7692ff0be138df6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_IDR_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfaf9c5b520fe2612d88725de4bc1224d28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAMETYPE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa05a31e040d22bea216e10f2ce8cd6472</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_ContentType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gac397e10110dd59e8266cf5831c68f44f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_CONTENTTYPE_NA</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa61cc12c39b88ba4c10d51a9d9393405a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PROGRESSIVE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa6b7ae345e50ccd4c5589efd85e18194e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PROGRESSIVE_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa36a57cca2ad3435c423515e78dd7d1ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa53e2513e3f2b155abb3bb707ff2fbd04</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa399d126875549ace3806efddcfc45ce8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED_TOPFIELD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa74d16186e87100648b97eae32e72d90c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED_BOTTOMFIELD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa980c869708ff1245fd7f1859515da631</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_CONTENTTYPE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa35c626f7476288db897680bc43d92243</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_RateControlPreset</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga33dcd88e11f7c1a614c37729e6b99592</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_LOW_DELAY</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592aee9478fdaa09a124e84a5f52373213f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_STORAGE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592ad38ab0817089a19a753e2ca6b6e5d165</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TWOPASS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592abf4ba1f0aff97d13bf49af0d574ad040</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NONE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592ae222e2b721a93726945d9b563631fda0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_USER_DEFINED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592a8e5fffe1c7bb0d34fd55b8820cfdb7e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_RATECONTROLPRESET_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592abafd796f46fc51340a58dadf2f725e25</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_SkipMode</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga911b2a9c63a7a8c16b86ae2b43acb609</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_ENCODED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga911b2a9c63a7a8c16b86ae2b43acb609a899d064f2315fc727725330cec39a441</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_SKIPPED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga911b2a9c63a7a8c16b86ae2b43acb609a728d909773039ecb6c8481ce587ff948</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIPMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga911b2a9c63a7a8c16b86ae2b43acb609ac81722aae2d59cad8cb864dc68c81d23</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_OutputFrameStatus</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga7d713a3e9b5adacb039de4419d5527d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_NOERROR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4acb9c873639468d10824089bf2c196884</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_NOTAVAILABLE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4a3884312affd02cbb477b0bcf9ffa4a8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_ERROR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4ae22471e0df0ebdbc17ad840deec9ba24</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_OUTPUTSKIP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4a60ba8d0b4e654ac84e7f079e98e1db60</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_OUTPUTFRAMESTATUS_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4a4bcc02f48972d600ec61e933133b4587</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_PictureType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga90dd6a0a4863fcc6d3d523eda8a78ed2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NA_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2aed1dec6b10bca143d42b83d26218d26e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_I_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2a85a519797900b0bbbc5007c14e6bab37</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_P_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2a70166338c9fab34bb0fc6534a0890ea3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_B_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2aa8b180d5b01bb100e326d261684ba7f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PICTURE_TYPE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2a5373e837eb3564b15e0a0203ecdb503f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_Format</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga4aeb19b8e5cc42c49fc8820fc4e1b4aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG1</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa6b8d27c8e2c977e98780b30be68b4553</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG2SP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa1d3f020030f6624621f546640cd97195</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG2MP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa77ef7b91a48b372bb8fd6104ba4c53d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG2HP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa8cd7c6245521d4003ae12244eb8616e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG4SP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa58cce125a57189f5ad23250b0ea41dce</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG4ASP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa35e77ca8ec953280e5615eb9e799211b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264BP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaab62f85b5ad0f3716733800202de13725</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264MP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa65745c33e161b9e725dd1093d6afb535</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264HP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa204e56351a5162ac38b3abfe5456ab87</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_VC1SP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaabb227ae9ca9aea83e804a2afc9137e67</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_VC1MP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa673d0eb07f8c957878812eebe0074b8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_VC1AP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaadf58ee1effdc2c92756355575b471123</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264RCDO</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa940abd5ed2efa9a00f0e7a5e2a2251ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_RV8</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa212c3c3801cec7c79961c6fab9bb242a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_RV9</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa84b7151a1af4d3443ed2c577cad0686b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_RV10</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa8c978af8c5b684ebc5203db2d30991c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ON2VP6</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa7082472b4fdec97b92dac08143376138</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ON2VP7</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa1bd7003b68493f109700a299bf8dd9dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_AVS10</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa95db05d1c11baabdf45ee00686d87284</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SORENSONSPARK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa6b5c380386c305f53ae7493e5efa6962</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H263_PROFILE0</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaacb80b99b98079682a1d2bd613148503d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H263_PROFILE3</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa5c4909bd040996c8e7bea8ad18918c03</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264SVC</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaaa83519d4e4595e91ded18b9bc324a0ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MULTIVIEW</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa357c291c2ea19421b029517cff2f3f96</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MJPEG</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaaf7871050ba19ab4d4b042f7743bbf57f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_VideoLayout</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gad5a767cec56f1942d52c9ec3faa18834</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FIELD_INTERLEAVED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggad5a767cec56f1942d52c9ec3faa18834a35e0e62b9bdf7d0de033e3fb7cdd8caf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FIELD_SEPARATED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggad5a767cec56f1942d52c9ec3faa18834a7f0222be966d686037579effa3a21600</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TOP_ONLY</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggad5a767cec56f1942d52c9ec3faa18834a4146a860698b530dafb906dffdb347f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BOTTOM_ONLY</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggad5a767cec56f1942d52c9ec3faa18834a70e0715988493d9baea5dcdb39de7970</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_OperatingMode</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga04553d2ffa25358d955796800ae89c6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_DECODE_ONLY</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga04553d2ffa25358d955796800ae89c6ba21af514948b5593b99b1a7e87912a227</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ENCODE_ONLY</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga04553d2ffa25358d955796800ae89c6bad74400f6d18fec5031c1bb60a0b530a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TRANSCODE_FRAMELEVEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga04553d2ffa25358d955796800ae89c6ba760407b19d59c4e23d1b22b37799a0c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TRANSCODE_MBLEVEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga04553d2ffa25358d955796800ae89c6bac55c6f2f2fe3ddfa90bb1a325fbdcbbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TRANSRATE_FRAMELEVEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga04553d2ffa25358d955796800ae89c6baebbaa951b61fa8d03f1ccb6a8ca3b2a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TRANSRATE_MBLEVEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga04553d2ffa25358d955796800ae89c6ba0e168b9703b6143f2ee75c64179ae787</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_BitRange</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga783aa3e11653b7deb8fa6405d69a74bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_YUVRANGE_FULL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga783aa3e11653b7deb8fa6405d69a74bdaf3f8342f77d13b361853d3e5686329ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_YUVRANGE_ITU</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga783aa3e11653b7deb8fa6405d69a74bdafde08af7be610fe74b624d27c049dfeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_DataMode</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gaa869a20e1197180fdbc9a176b3ddb167</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FIXEDLENGTH</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggaa869a20e1197180fdbc9a176b3ddb167aad14f85c07b9afdf25538140c857b14b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SLICEMODE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggaa869a20e1197180fdbc9a176b3ddb167a48af869b96da08862e748db350e54d8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NUMROWS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggaa869a20e1197180fdbc9a176b3ddb167abc9d77cf9eecf58a401a028777570141</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ENTIREFRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggaa869a20e1197180fdbc9a176b3ddb167a9e0003c122588c7d84a74dfab0699699</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_ErrorInfoMode</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga010d63a13fa5c291d61403d1811c5775</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ERRORINFO_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga010d63a13fa5c291d61403d1811c5775a32b1d0efdebc3bb356a546b938090030</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ERRORINFO_ON_INPUT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga010d63a13fa5c291d61403d1811c5775a492f7ebc0bf13a68f4ee3c205d293db8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ERRORINFO_ON_OUTPUT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga010d63a13fa5c291d61403d1811c5775a3ef6e3039cc4aea47c81e6334ae9b3cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ERRORINFO_ON_BOTH</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga010d63a13fa5c291d61403d1811c5775ae8c7b2716a8a83c88ff92711300e6ff1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ERRORINFO_MODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga010d63a13fa5c291d61403d1811c5775a784a7b032e261400725d6423f1d51e78</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_MetadataType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga3e0d6c6bd8fa37db0b88aeae961962fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_METADATAPLANE_NONE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga3e0d6c6bd8fa37db0b88aeae961962fea78081d631dc40260b4eb2049a94b30c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_METADATAPLANE_MBINFO</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga3e0d6c6bd8fa37db0b88aeae961962fea6a080d2da5643120b53fb56b3e846f06</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_METADATAPLANE_EINFO</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga3e0d6c6bd8fa37db0b88aeae961962fea0ff3386a8c9cc68036c1925440f1787c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_METADATAPLANE_ALPHA</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga3e0d6c6bd8fa37db0b88aeae961962fea7b5b28108acbefabf93be70eda8b9131</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividtranscode.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>ividtranscode_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDTRANSCODE_Obj</class>
    <class kind="struct">IVIDTRANSCODE_Params</class>
    <class kind="struct">IVIDTRANSCODE_DynamicParams</class>
    <class kind="struct">IVIDTRANSCODE_InArgs</class>
    <class kind="struct">IVIDTRANSCODE_Status</class>
    <class kind="struct">IVIDTRANSCODE_OutArgs</class>
    <class kind="struct">IVIDTRANSCODE_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga69d74b9dad25f19d864771f9d81a9a6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga29ec01f0e1dea7abff118a9cf8792885</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gaf6e122d808cecd873a7f51e34c2fb4b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_MAXOUTSTREAMS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga9b9cc80049e4cebea89e7c4cf58d426c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Obj</type>
      <name>IVIDTRANSCODE_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gacacbc6165ddd6b023b58abad8aa0a59b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Obj *</type>
      <name>IVIDTRANSCODE_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga049f5b53ee2c04135a1ff19afbc215c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Params</type>
      <name>IVIDTRANSCODE_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga00d5710f24d7b9087dcd01d40921a21e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_DynamicParams</type>
      <name>IVIDTRANSCODE_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga043a74d49bc336696a4be8366ad4db2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_InArgs</type>
      <name>IVIDTRANSCODE_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gaf74fb25ea8e27a3be28bcd27a71f7eb8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Status</type>
      <name>IVIDTRANSCODE_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga694f55f6a32c7d080e6b9ee6026ef7c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_OutArgs</type>
      <name>IVIDTRANSCODE_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga4741c07a91091e7fdd3a894195a739aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDTRANSCODE_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gab5d20cf8d615294c7912796b79f85f5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Fxns</type>
      <name>IVIDTRANSCODE_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga145180087812e38dff35b3b2866adf99</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>xdm.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>xdm_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <class kind="struct">XDM_BufDesc</class>
    <class kind="struct">XDM_SingleBufDesc</class>
    <class kind="struct">XDM1_SingleBufDesc</class>
    <class kind="union">XDM2_BufSize</class>
    <class kind="struct">XDM2_SingleBufDesc</class>
    <class kind="struct">XDM1_BufDesc</class>
    <class kind="struct">XDM2_BufDesc</class>
    <class kind="struct">XDM1_AlgBufInfo</class>
    <class kind="struct">XDM_AlgBufInfo</class>
    <class kind="struct">XDM2_MoveBufDesc</class>
    <class kind="struct">XDM_Date</class>
    <class kind="struct">XDM_Point</class>
    <class kind="struct">XDM_Rect</class>
    <class kind="struct">XDM_ContextInfo</class>
    <class kind="struct">XDM_Context</class>
    <class kind="struct">XDM_DataSyncDesc</class>
    <member kind="define">
      <type>#define</type>
      <name>XDM_EOK</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga1cf6109227485a043be42d0761ed55b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac896f031d1997aae6f959aff6c6d8b54</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac502a6ae2494d2c4151e2a3be22c96e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaa1a1d3d9c0c8807cbe465633d76580e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_MAX_IO_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacb0db1cbd37d45e39368c0dff87d7cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga3446a438727f673f58cacd76947536d1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaa0360329abe8080abb150c24255fa3a7</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CLEARACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaedd624063fce29cfed9193ad4d46765c</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CLEARACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacaf2e719f6570fb074df83697f9665d1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac4c3d846ed83c34a06fd6e8fcb49b4b2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaef2577b3a010843a01d85a6e2bbf5487</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CUSTOMENUMBASE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf6eae9fc7c3a5e8aa08d3d23d870b583</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CUSTOMCMDBASE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga43093f03f01c2e4eed7f131795af84fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISFATALERROR</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf46ec0675f5fae35aaf29392aebbe3d3</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISUNSUPPORTEDPARAM</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gae1b52e8b2c8c062dd460f8a9bc737b77</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISUNSUPPORTEDINPUT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacc71215dc73ce6f3184f78be7c49ac09</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISCORRUPTEDHEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga4979bf4ca24fca5d9386896f9c319084</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISCORRUPTEDDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga180c829e45389f064af38a3e58278baa</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISINSUFFICIENTDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7714cc631b009ef2c574218006af0ebb</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISAPPLIEDCONCEALMENT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga24d74d9ea55947f6bf2bc90a532bc32c</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETFATALERROR</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gab0d647a23e89f0a11fb47493746bc254</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETUNSUPPORTEDPARAM</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad4b20720fe6a8d9eb46259206635c6ab</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETUNSUPPORTEDINPUT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf6a007a552f8849694b6c785531c9413</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETCORRUPTEDHEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad5b5a780c1df72c1a99f28c1e32531be</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETCORRUPTEDDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7cab971a59a1057febe113621ac68c1b</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETINSUFFICIENTDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga89f38db60d38746c435f8d9f2398bef2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETAPPLIEDCONCEALMENT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga22e33071e27e1f3d1624229986c79331</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_MAX_CONTEXT_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaed28c56a4d5a516897357c2fc647ac9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_BufDesc</type>
      <name>XDM_BufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga586b0ef904f6e6a226c8672e8f244027</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_SingleBufDesc</type>
      <name>XDM_SingleBufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad91f21f92a5fe3b6eeb1b66f2e18105b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM1_SingleBufDesc</type>
      <name>XDM1_SingleBufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf186abda0633960550b1eb54a65bf180</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM2_SingleBufDesc</type>
      <name>XDM2_SingleBufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga945ceb579f6b5decc09e9f5b22a8330e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM1_BufDesc</type>
      <name>XDM1_BufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac4c9636e78344de81de3d8845d8424d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM2_BufDesc</type>
      <name>XDM2_BufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga13ecf6839f07990bcd026943f66efaba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM1_AlgBufInfo</type>
      <name>XDM1_AlgBufInfo</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga682fe33611973b8ae6fa0052979ea9f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_AlgBufInfo</type>
      <name>XDM_AlgBufInfo</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga1e1612df49f286c564d5537627c8a937</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM2_MoveBufDesc</type>
      <name>XDM2_MoveBufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga9258b3a7baf02c84966b1b2018a4f79d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_Date</type>
      <name>XDM_Date</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf2d218d0a8f734916e12334c58c30c69</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_Point</type>
      <name>XDM_Point</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaac6b6d6d00c43cf5a58adb7a76045ebe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_Rect</type>
      <name>XDM_Rect</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga35979dd87228ffe41c9fcf83ee89cb0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_ContextInfo</type>
      <name>XDM_ContextInfo</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga6164a472952c526890eefe189d4e54a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_Context</type>
      <name>XDM_Context</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga652e360c99f2774d491684602cd1d076</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_DataSyncDesc</type>
      <name>XDM_DataSyncDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gabb26d49d7d9f070c778015d60c8ed1b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void *</type>
      <name>XDM_DataSyncHandle</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacf3c98f1d74864b1bd7dcfe295057540</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>XDM_DataSyncPutFxn</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga3b019dc50e38d3dcaefb6cfaeb05e71d</anchor>
      <arglist>)(XDM_DataSyncHandle dataSyncHandle, XDM_DataSyncDesc *dataSyncDesc)</arglist>
    </member>
    <member kind="typedef">
      <type>XDAS_Int32(*</type>
      <name>XDM_DataSyncGetFxn</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga045fd6e6754962733a798bf10446f8fd</anchor>
      <arglist>)(XDM_DataSyncHandle dataSyncHandle, XDM_DataSyncDesc *dataSyncDesc)</arglist>
    </member>
    <member kind="typedef">
      <type>XDAS_Int32(*</type>
      <name>XDM_DataSyncGetBufferFxn</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga500b152e73d1439982a6616f104ee1cf</anchor>
      <arglist>)(XDM_DataSyncHandle dataSyncHandle, XDM_DataSyncDesc *dataSyncDesc)</arglist>
    </member>
    <member kind="typedef">
      <type>XDAS_Int32(*</type>
      <name>XDM_DataSyncPutBufferFxn</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaaba438ffe2c12c416d878e4e708316f5</anchor>
      <arglist>)(XDM_DataSyncHandle dataSyncHandle, XDM_DataSyncDesc *dataSyncDesc)</arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_AccessMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad852bdfa0303e77939811768b8e905ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggad852bdfa0303e77939811768b8e905abadc6547990f2ba9c7a4bacdf3ad4f405a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggad852bdfa0303e77939811768b8e905ababd16ad36f147cf0e691a13590314a06c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_CmdId</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga4d2482d53629e138b96af2e3fe702477</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETSTATUS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a901d6409e5496dbc7720d0e952fb1b15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_SETPARAMS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477ab358f49d17f79c00b1ba5c2c645eb025</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RESET</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a2bf3cef324828ab92cd6cedead4c725e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_SETDEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a1b6cda1632a452aa55dbba763b53d746</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_FLUSH</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477acd0e4d7005b1df978b26f97bccf6df8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETBUFINFO</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477aac803fc3c3144acc395e3b9b79025653</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETVERSION</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a6531ed0c0766017f6caa01207d3ad4c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETCONTEXTINFO</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a7aa270e718dce742ef06b8d67be98055</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETDYNPARAMSDEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a7ebcd6a97cefdb944ce204bc6415bb15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_SETLATEACQUIREARG</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a1f3270dd03e6a6854d755b7fe107b61b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MOVEBUFS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a742a9d2abb13912edc149461252bb4cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_ErrorBit</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga993de0b923e61c59a996fc2be4783131</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_PARAMSCHANGE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a13eb40f973b1bc18df8263030d4a1be9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_APPLIEDCONCEALMENT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a143f0496fb2db7191d7ddbe9d9fb58f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_INSUFFICIENTDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131aeb5f7b677fb1d35ce8c9e4af0e1c5c2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CORRUPTEDDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a3df4766dd604b28652b8830f051a7e1a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CORRUPTEDHEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131afab843e2d029e916fc36e7550489dba9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_UNSUPPORTEDINPUT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a7c4145225db773b55c02bcc61be59756</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_UNSUPPORTEDPARAM</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a3440c95956b613e002620a71c77a5980</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_FATALERROR</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a8ebb569b30333486afaf576c366118e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_DataFormat</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga5b4416e5582cae4428a1f4695d6e5ac5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BYTE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5aa24eeba74896e53a4bb8874560e4f67d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_LE_16</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a286615517f0d85bbad01a61ca1b8355b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_LE_32</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a87cbb4b143f78faf0f5c67d45cd5a39a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_LE_64</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a111d1dcf71c52bd2c9886373a5d98e1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BE_16</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a3dac2b3e9961a294c89ffac5ceedb509</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BE_32</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a43e43097fd1b63ac44247df52fe88da4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BE_64</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a82ae547ec4f91e70c0dec56dd35c624d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_EncodingPreset</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7b522f4337b661bbf9fb649eb95b4e1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1ca72b9373f4561db5fc6b0a2904b4a40e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_HIGH_QUALITY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1cabef4cff45b90786a8583b027530bb927</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_HIGH_SPEED</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1caf553ad9672b1ee9a7b91d746980dc58a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_USER_DEFINED</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1caba3ac3c750ac0125c9f1aac6f8586b5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_HIGH_SPEED_MED_QUALITY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1cad17148dfa73f3485494c179347c87ea6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MED_SPEED_MED_QUALITY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1ca955aa675c06d09f1eb50965e864c5467</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MED_SPEED_HIGH_QUALITY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1cafcd8873674236968ef61010f625fb821</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ENCODING_PRESET_MAX</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1ca09059f7596f0c9721319ae545d24229e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_PRESET_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1caf0a33f87fd66b122a1b0d1bbd92aa177</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_DecMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga0e19341fdb7c698eb849896edaa33aff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_DECODE_AU</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga0e19341fdb7c698eb849896edaa33affa8c540496685639e09e8c1ef895565595</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_PARSE_HEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga0e19341fdb7c698eb849896edaa33affa20a585ea8dd3b153c5203499b54d862c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_EncMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7e9132a2379c6ac0ee9c9e925b932461</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ENCODE_AU</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7e9132a2379c6ac0ee9c9e925b932461a5822b75801cd51f3a5f3478d59c8bee4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GENERATE_HEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7e9132a2379c6ac0ee9c9e925b932461a98969caa951cc0b210bacdd2a1932abc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_ChromaFormat</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gab99980ebd17efe73aa5708b5f43107f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CHROMA_NA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4aef81026a1d1783d9628c19f5c8a78dac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_420P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a891298e42c828a4c56b2d20d8be7cca8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_422P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a9457339c11ffa04dca5f900e82a2346d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_422IBE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a638d86b7f38f9404348b38fa459bdee9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_422ILE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a9560c4d0b7a2ddb6aba01ca66e41e5ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_444P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a31ade59366a5116a6d74a4fe012021f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_411P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a6c2c3aac53d2a8da477f487d788bcb29</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GRAY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a45edf9e2ce7ab4045dfcdde062b4e423</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RGB</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a0491c6350cc8c9127610c2a6c31f3ee4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_420SP</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4acd45176e14ea9e5b53fc52ec88bddd9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ARGB8888</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a5979b38c73531a7bf71c12412232be5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RGB555</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4aa1ae21243fd451d6a8f75bd274a77934</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RGB565</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a6b8863fc2937c932888f3df04ff1bcc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_444ILE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4aaf1809f33e309f991f8c47b6af55399a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CHROMAFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4af01b00784f3926f7accfd6f0a8360a7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_MemoryType</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga69f8d5b708926a7e3ccb87264c741111</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMTYPE_ROW</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga69f8d5b708926a7e3ccb87264c741111a0cb3b4184849d9d46b93906d5fc3a2e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMTYPE_RAW</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga69f8d5b708926a7e3ccb87264c741111a9c268781b88e0db8ee97ed6e8a9bec18</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMTYPE_TILED8</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga69f8d5b708926a7e3ccb87264c741111aaa92c0c8b4d48c91bf26b80c6e070195</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMTYPE_TILED16</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga69f8d5b708926a7e3ccb87264c741111a98b6ee029a1e01d90ca54797958d8ad1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMTYPE_TILED32</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga69f8d5b708926a7e3ccb87264c741111acc7d0ff7ecb8e10beb1e22de281dc678</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMTYPE_TILEDPAGE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga69f8d5b708926a7e3ccb87264c741111ace88c29b4f7b98e2f2ff3c01b6758869</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_MemoryUsageMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga70f4f3f82fa67c5e06eb506bf4729a4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMUSAGE_DATASYNC</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga70f4f3f82fa67c5e06eb506bf4729a4aa3d06c95b07759d1c642dc7675e3d8796</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ialg.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/</path>
    <filename>ialg_8h</filename>
    <class kind="struct">IALG_MemRec</class>
    <class kind="struct">IALG_Obj</class>
    <class kind="struct">IALG_Params</class>
    <class kind="struct">IALG_Status</class>
    <class kind="struct">IALG_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IALG_DEFMEMRECS</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga8a220fa863380937542f6a38be47ceda</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_OBJMEMREC</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga0e3202a4d8dc0bd3cb300633922ffd54</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_SYSCMD</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga200f155f9e2720011270e99f17bb6675</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_EOK</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga2c15898121a23a164e4ea2bcc4f7e7dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_EFAIL</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga604e5600815cbd58846e0c5c05b6ba18</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_CUSTOMFAILBASE</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga1f655af6b5ce37aaf5328243d1993cf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_CUSTOMFAILEND</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gafbab7f3470d8b5a46615f1aca5c739b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_MPROG</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga86018453b8f991c8cb545b2e43c80c9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_MXTRN</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gafc53b940e2982a2e859bda0555180eb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_isProg</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga93e8704d8e88d2f3dde1a85317232b59</anchor>
      <arglist>(s)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_isOffChip</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gae2530ce6b07542f579871961a3fcfd4f</anchor>
      <arglist>(s)</arglist>
    </member>
    <member kind="typedef">
      <type>enum IALG_MemAttrs</type>
      <name>IALG_MemAttrs</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga20f514039bf67b319bff425fb8f36e5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IALG_MemSpace</type>
      <name>IALG_MemSpace</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga61ed32f432abc371aece4d839cdaee78</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_MemRec</type>
      <name>IALG_MemRec</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga99aa369e4d2b2e38444d7029ba09caed</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_Obj</type>
      <name>IALG_Obj</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga056d16e11872c72ef03832ebea91c946</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_Obj *</type>
      <name>IALG_Handle</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga16c037803ea218ba3dc5158f55ef27c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_Params</type>
      <name>IALG_Params</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gaa3e5c88152dd2b867de749e15c4bd01a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_Status</type>
      <name>IALG_Status</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga9cb14b478af2c5636bfb8ba78d06c3ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int</type>
      <name>IALG_Cmd</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga9032f20923ef2ba1d6b88c87a20075fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_Fxns</type>
      <name>IALG_Fxns</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gaf97260de3299a9304375dedca698572a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IALG_MemAttrs</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga805f1c1330403c05633277a073862e3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SCRATCH</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga805f1c1330403c05633277a073862e3da85e0509f7e82ebd01b57f899122de9b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_PERSIST</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga805f1c1330403c05633277a073862e3da68adbe0194074e0474333b76f7d1e090</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_WRITEONCE</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga805f1c1330403c05633277a073862e3da42356e6aa11869bfd15f31472f49a7c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IALG_MemSpace</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga262eb64dc7343999fa07d535ae163497</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_EPROG</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a6410b22d1d073ab55b289ca2f3c03b35</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_IPROG</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a946577db145f691f81d7085fc51e2201</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_ESDATA</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a85fff905ed5e83445e3424ce5ba03175</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_EXTERNAL</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497aa98151c21c55ddaf8c1918d8007e5493</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_DARAM0</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497af6a85bf972a4d090e2c0e4d31565f879</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_DARAM1</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497ad7b3b18fc0263be0f0702d263f600d9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497aa5c6d8cfdb63c11fafd22bb87204c5cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM0</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a4b31d959f6af27a012a87957c05d9c4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM1</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a4ac938c5e58e4d4a30458b63869f0095</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_DARAM2</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a17fc19eac565b29871efbfed54760414</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM2</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a6db79aaafcf9b4354f2828c2a94b8590</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>idma.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/</path>
    <filename>idma_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="yes" imported="no">ialg.h</includes>
    <class kind="struct">IDMA_Params</class>
    <class kind="struct">IDMA_ChannelRec</class>
    <class kind="struct">IDMA_Fxns</class>
    <member kind="typedef">
      <type>struct IDMA_Obj *</type>
      <name>IDMA_Handle</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>aa2b530ffca8ba1a5301887cf8aaa33fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IDMA_ElementSize</type>
      <name>IDMA_ElementSize</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>ac4c370ef06191421b5179ac9fd571b8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IDMA_TransferType</type>
      <name>IDMA_TransferType</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>a19bf3a99077c2ff1d1c6b41f1c8f4c2e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA_Params</type>
      <name>IDMA_Params</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>a8713ec0e61d52c9261bb7e79b34425cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA_ChannelRec</type>
      <name>IDMA_ChannelRec</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>a845aad8c3c6d8cf1e9536c75ccc3a657</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA_Fxns</type>
      <name>IDMA_Fxns</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>a712ce455e9cb694d03abd57cf37d074a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IDMA_ElementSize</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>a78ea5cb99f82ae923dc0ef52c878d6e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA_ELEM8</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>a78ea5cb99f82ae923dc0ef52c878d6e2a958857a3fbb40590230bf2167db64144</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA_ELEM16</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>a78ea5cb99f82ae923dc0ef52c878d6e2ad1d57b9bcaacb489d4ffb0f202348c36</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA_ELEM32</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>a78ea5cb99f82ae923dc0ef52c878d6e2a40821c710764b29c692d27c77c52b6f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IDMA_TransferType</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>aced0209dcc83ab325034f0a8153a12ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA_1D1D</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>aced0209dcc83ab325034f0a8153a12efa6afef4924b24e3dd9613d3088942e85f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA_1D2D</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>aced0209dcc83ab325034f0a8153a12efa141357d929472bd3afd43815a29ee889</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA_2D1D</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>aced0209dcc83ab325034f0a8153a12efaacdbae554e332e3e4244d78b2130291b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA_2D2D</name>
      <anchorfile>idma_8h.html</anchorfile>
      <anchor>aced0209dcc83ab325034f0a8153a12efa93a9ebfc56dd3f5f9e227f522ca96023</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>idma2.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/</path>
    <filename>idma2_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="yes" imported="no">ialg.h</includes>
    <class kind="struct">IDMA2_Params</class>
    <class kind="struct">IDMA2_ChannelRec</class>
    <class kind="struct">IDMA2_Fxns</class>
    <member kind="typedef">
      <type>struct IDMA2_Obj *</type>
      <name>IDMA2_Handle</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>adb968e96baf6acea1e1a986963dbe285</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void *</type>
      <name>IDMA2_AdrPtr</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>a540da68c307a9812ab3007646cebc67e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IDMA2_ElementSize</type>
      <name>IDMA2_ElementSize</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>ae9a502bf924284c4503d3c530f02ce1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IDMA2_TransferType</type>
      <name>IDMA2_TransferType</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>a344cddd14f07885a621f3675a769b156</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA2_Params</type>
      <name>IDMA2_Params</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>a05c816b6509bd21d11f2a2c852be0831</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA2_ChannelRec</type>
      <name>IDMA2_ChannelRec</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>a8cb595881862b9b561f7679ee6cbf645</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA2_Fxns</type>
      <name>IDMA2_Fxns</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>a13daf19c8fd6a4d052af172139e97349</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IDMA2_ElementSize</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>a18658615b957246edbf6187e40bdcbda</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA2_ELEM8</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>a18658615b957246edbf6187e40bdcbdaa149365d05bc07417550608733098fb8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA2_ELEM16</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>a18658615b957246edbf6187e40bdcbdaa225f99ea8ba0e9c26b91098eff260eaa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA2_ELEM32</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>a18658615b957246edbf6187e40bdcbdaa4a9356935e298b841a4a025a2671247e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IDMA2_TransferType</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>ac05d9e108ebe7cce58a6789acda0aaba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA2_1D1D</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>ac05d9e108ebe7cce58a6789acda0aabaa622996be1e7d2c5eb5fb3e8b54a70388</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA2_1D2D</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>ac05d9e108ebe7cce58a6789acda0aabaad1841df9b094d41b074418f8b64ca223</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA2_2D1D</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>ac05d9e108ebe7cce58a6789acda0aabaaefb6f7d506639ab5ccc64b9fedcf762c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA2_2D2D</name>
      <anchorfile>idma2_8h.html</anchorfile>
      <anchor>ac05d9e108ebe7cce58a6789acda0aabaa21cf9fd6049da96ceaf710dcadf1c018</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>idma3.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/</path>
    <filename>idma3_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="yes" imported="no">ialg.h</includes>
    <class kind="struct">IDMA3_MemRec</class>
    <class kind="struct">IDMA3_ChannelRec</class>
    <class kind="struct">IDMA3_Fxns</class>
    <class kind="struct">IDMA3_ProtocolObj</class>
    <class kind="struct">IDMA3_Obj</class>
    <member kind="define">
      <type>#define</type>
      <name>IDMA3_PROTOCOL_NULL</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ga85de540d61ac83857803528f25f44e4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IDMA3_MemType</type>
      <name>IDMA3_MemType</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gad7dca268a0fb944ec7da970a7064c93b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_MemRec</type>
      <name>IDMA3_MemRec</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gad9a9dde19d244a4552965b14abe2d96f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_Obj *</type>
      <name>IDMA3_Handle</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ga8960c528f0708a559bcaab34a865e1a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_ProtocolObj *</type>
      <name>IDMA3_ProtocolHandle</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gadd329735609d8384c3625554c0f2c58d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IDMA3_Priority</type>
      <name>IDMA3_Priority</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ga04af272ab4f16153137e3f39856078d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_ChannelRec</type>
      <name>IDMA3_ChannelRec</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gac8af8b3447a5ae88f4b14dc96e18eee1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_Fxns</type>
      <name>IDMA3_Fxns</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ga02d106a910bf5561419a755ab7f97e03</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_ProtocolObj</type>
      <name>IDMA3_ProtocolObj</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ga6705287956a84beb7d6f0eee6b6dfb55</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_Obj</type>
      <name>IDMA3_Obj</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gae5a0e05b6797ba0b914a41c90ea47a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IDMA3_MemType</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gabe0577eecc288b36121382daa765093a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA3_INTERNAL</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ggabe0577eecc288b36121382daa765093aa120151b2c6d2d5bcb2d59466b0d13287</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA3_EXTERNAL</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ggabe0577eecc288b36121382daa765093aa9e757f072f4782774d8cd4b647563c54</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IDMA3_Priority</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gafa41dccd2cc8f94915fffdda2c8b4a59</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA3_PRIORITY_URGENT</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ggafa41dccd2cc8f94915fffdda2c8b4a59a90abf287e878aedcfbc17d19266f207c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA3_PRIORITY_HIGH</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ggafa41dccd2cc8f94915fffdda2c8b4a59a2bd88e579d019a160876842f0c92f325</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA3_PRIORITY_MEDIUM</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ggafa41dccd2cc8f94915fffdda2c8b4a59a4f3bbe300c3ce513644f31991b6788ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA3_PRIORITY_LOW</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ggafa41dccd2cc8f94915fffdda2c8b4a59a8560a79ce3c83622bed84ecb31b57aff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ires.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/</path>
    <filename>ires_8h</filename>
    <includes id="ires__common_8h" name="ires_common.h" local="yes" imported="no">ires_common.h</includes>
    <class kind="struct">IRES_YieldContext</class>
    <class kind="struct">IRES_Fxns</class>
    <member kind="typedef">
      <type>enum IRES_YieldResourceType</type>
      <name>IRES_YieldResourceType</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga772c04e720ba2b67b4204bbccbe40945</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>IRES_ContextSaveFxn</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gaa00576c8c0c6d1e2c01cc32788c597c9</anchor>
      <arglist>)(IALG_Handle algHandle, Void *contextArgs)</arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>IRES_ContextRestoreFxn</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga618c74da111cc440a47fad6f7f575c89</anchor>
      <arglist>)(IALG_Handle algHandle, Void *contextArgs)</arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_YieldContext</type>
      <name>IRES_YieldContext</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gad70330927e4683909b1553bf0f2a5c75</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IRES_YieldContext *</type>
      <name>IRES_YieldContextHandle</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gafd901eec352839470db8e386baa1be66</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void *</type>
      <name>IRES_YieldArgs</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gafb1e285a8d30b447dc39fe05d5e4fdf0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>IRES_YieldFxn</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga21803b9b676c2579e59909062dc40079</anchor>
      <arglist>)(IRES_YieldResourceType resourceType, IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs)</arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_Fxns</type>
      <name>IRES_Fxns</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gad4918d3ae4c063a0bf6e76ac26c7c297</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IRES_YieldResourceType</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga9a68e109e02bf3f35e832ec4f767d0a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_ALL</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga9a68e109e02bf3f35e832ec4f767d0a3a0fd0c33808e89762c91dca8c2edc6aef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_SCRATCHMEMORY</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga9a68e109e02bf3f35e832ec4f767d0a3a99a353ef5a76fad49a805f0e3ba6e8e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_SCRATCHDMA</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga9a68e109e02bf3f35e832ec4f767d0a3aa8fe0182b728dbcd24900b9bf13221c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_RESOURCEHANDLE</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga9a68e109e02bf3f35e832ec4f767d0a3a737fd5b62997deb99125d2e0f4e47b74</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ires_common.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/</path>
    <filename>ires__common_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="yes" imported="no">ialg.h</includes>
    <class kind="struct">IRES_ProtocolRevision</class>
    <class kind="struct">IRES_ProtocolArgs</class>
    <class kind="struct">IRES_ResourceDescriptor</class>
    <class kind="struct">IRES_Properties</class>
    <class kind="struct">IRES_Obj</class>
    <member kind="enumeration">
      <name>IRES_Status</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga8db6eab013fc4569e080cb4361dfd65b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_OK</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba30253e67bb1b070685e4177bdf9587b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_EALG</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba432505b3fc40c3ae60c7b36624dc100d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_EEXISTS</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba5d1871ad076ad79c214cfe753f0513e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_EFAIL</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba79fa1a926f2b780120951d084fcc3bd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_EINIT</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65bacf083017e2e50c9f975e4d956d0dc440</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_ENOINIT</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba9cb3cdefe2de31efea9a9442e2ed7dd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_ENOMEM</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba72b429ce0c052c9fe5b079798ee08caa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_ENORESOURCE</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba82f5c8e224ec5ef57cae62a4e80bf2d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_ENOTFOUND</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba077a2999bf874acf2b556347a3c71e5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IRES_RequestMode</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga67d435865304c7bce199194e7ff07963</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_SCRATCH</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga67d435865304c7bce199194e7ff07963a4edb7db0f8cd8780a263c1e8ec686aa0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_PERSISTENT</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga67d435865304c7bce199194e7ff07963ab66403426900afab06c1459b4c8a1fc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_LATEACQUIRE</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga67d435865304c7bce199194e7ff07963aa8d4ddab65248eedc7d1ca3fb43a5ea2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_Status</type>
      <name>IRES_Status</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga09c6ef97314f2d27ce39bfcfac5da287</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_ProtocolRevision</type>
      <name>IRES_ProtocolRevision</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gaf7c3863c0ea3895fb86badf58b809a43</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_RequestMode</type>
      <name>IRES_RequestMode</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gae6d619d30b481ac725448b769d2ae2d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_ProtocolArgs</type>
      <name>IRES_ProtocolArgs</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga4808ad3c47785cbfb8a22bf50b096e11</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_ResourceDescriptor</type>
      <name>IRES_ResourceDescriptor</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga0b4bec3cd4dbe4556d72d9ed894d5246</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_Properties</type>
      <name>IRES_Properties</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga2ef376adca27740ff8285b0d1b7e272b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_Obj</type>
      <name>IRES_Obj</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga5d11994529489c6809bc2effd5f83f01</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_Obj *</type>
      <name>IRES_Handle</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gad0e33217f411f69c326180854b9f1cea</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>trace.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/</path>
    <filename>trace_8h</filename>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_ENTER</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>gae481bd98d6475b901f3bda374d7dd804</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_1CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>gab3b47227b7128f9dd7248cdbac20b28c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_2CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga97343ce207eec0b43621a7ce712f6a51</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_3CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga0a042541fabc495650334061087052a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_4CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga2bc4512b405185af7baa8ef4e160e6f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_5CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>gaeb138d21539b83c10d2c11c76c122552</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_6CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga95e0f1e59bc5d22e913fbd5a4cde68fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_7CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga1ceefde1affa0c508b0a6d523ae8860a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>XDAS_Int32(*</type>
      <name>XDAIS_TRACE_AssertFxn</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga404d7007d125c9e0fcb716f6d2a2e367</anchor>
      <arglist>)(IALG_Handle alg, XDAS_Int32 classId, String format, String arg1, XDAS_Int32 arg2)</arglist>
    </member>
    <member kind="typedef">
      <type>XDAS_Int32(*</type>
      <name>XDAIS_TRACE_PrintFxn</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga8395e2827ac16a7e8cfc36b23813beca</anchor>
      <arglist>)(IALG_Handle alg, XDAS_Int32 classId, String format,...)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>xdas.h</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/</path>
    <filename>xdas_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>XDAS_TRUE</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga0a1e9fe6b661ca6eafe982fe2b0787bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDAS_FALSE</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga5cd894ca3ba5c100f7f863dae8587293</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void</type>
      <name>XDAS_Void</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga125aad4180e7ca9a3ddaba59c9217513</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint8</type>
      <name>XDAS_Bool</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gac8ce48f3d618a6f0a37b4e55f978b825</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int8</type>
      <name>XDAS_Int8</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gaa0b0c4cc1bf0d8fa0d9b15de0e9204cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint8</type>
      <name>XDAS_UInt8</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gac9308edb855a360c27a47aaa6f3b39a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int16</type>
      <name>XDAS_Int16</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga8189aa7a8636f505d6a35e5744ac6392</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint16</type>
      <name>XDAS_UInt16</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gaa27605972947c862397ebee40c2ff917</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int32</type>
      <name>XDAS_Int32</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gae431579ed9eff9134de78ca00ddd5f3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint32</type>
      <name>XDAS_UInt32</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga615572fcd2279a6780dc1785d72ff421</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>Disclaimer</name>
    <title></title>
    <filename>_disclaimer</filename>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IAUDDEC</name>
    <title>IAUDDEC - XDM Audio Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_a_u_d_d_e_c.html</filename>
    <class kind="struct">IAUDDEC_Obj</class>
    <class kind="struct">IAUDDEC_Params</class>
    <class kind="struct">IAUDDEC_DynamicParams</class>
    <class kind="struct">IAUDDEC_InArgs</class>
    <class kind="struct">IAUDDEC_Status</class>
    <class kind="struct">IAUDDEC_OutArgs</class>
    <class kind="struct">IAUDDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gae550832bf925622e32ea891f9a64f840</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga0447e3d9eba91c950b0ca6533f090b4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga9ba0561ce6c276ef9a4b9d6dc1b66aa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gacfdf5e7ab31ee37a9b168bbcf7d71309</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Obj</type>
      <name>IAUDDEC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga6634b0496d752d9e3ad71601d824867f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Obj *</type>
      <name>IAUDDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga849224ef7d8add16e7152e3c2cef1cb0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Params</type>
      <name>IAUDDEC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gacb141d33623cf82cc46d17fea7703e9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_DynamicParams</type>
      <name>IAUDDEC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga5820d588b117ad5217930662abac99f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_InArgs</type>
      <name>IAUDDEC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gaa9b870e05b3cbbf90dbf4330480e29e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Status</type>
      <name>IAUDDEC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gab809863924a3c0762af2b67492ed6de7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_OutArgs</type>
      <name>IAUDDEC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga45698ad1d6198f7cde140f48788a310a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga8a44a541760fefd4c41ea1d29c80d71e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Fxns</type>
      <name>IAUDDEC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gac12eb0bbd9b46fef4203abbb59034bba</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IAUDDEC1</name>
    <title>IAUDDEC1 - XDM Audio Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</filename>
    <class kind="struct">IAUDDEC1_Obj</class>
    <class kind="struct">IAUDDEC1_Params</class>
    <class kind="struct">IAUDDEC1_DynamicParams</class>
    <class kind="struct">IAUDDEC1_InArgs</class>
    <class kind="struct">IAUDDEC1_Status</class>
    <class kind="struct">IAUDDEC1_OutArgs</class>
    <class kind="struct">IAUDDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga2875d67b3c5af6d7a16b373ec21cf567</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga2ac49534acb4a9fef6c32355b9883664</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga690d6e129037630a13d1b80eb1e2480d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Obj</type>
      <name>IAUDDEC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga50c2c19b82f699c8db66b2deb8786b4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Obj *</type>
      <name>IAUDDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga2287de2327bdc6e94ada6971506a2fe4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Params</type>
      <name>IAUDDEC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>gaf00ecb15843c90924d700e36aaf599df</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_DynamicParams</type>
      <name>IAUDDEC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga1082e6d4d48745641f0870c050d874e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_InArgs</type>
      <name>IAUDDEC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>gaaaf5baa42d137368fddde42bd8b8a086</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Status</type>
      <name>IAUDDEC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga8bfe7fe4aaf4bdd967956c0145badf7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_OutArgs</type>
      <name>IAUDDEC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga9c77ccf6c02b80d5d7e4cb5f45254544</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga4c0ee4ad90447b42d3a39dd6e81ca3c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Fxns</type>
      <name>IAUDDEC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga3cf12da7344d61bf93655a0d032143e3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IAUDENC</name>
    <title>IAUDENC - XDM Audio Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_a_u_d_e_n_c.html</filename>
    <class kind="struct">IAUDENC_Obj</class>
    <class kind="struct">IAUDENC_Params</class>
    <class kind="struct">IAUDENC_DynamicParams</class>
    <class kind="struct">IAUDENC_InArgs</class>
    <class kind="struct">IAUDENC_Status</class>
    <class kind="struct">IAUDENC_OutArgs</class>
    <class kind="struct">IAUDENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga2c2cde30bd98faf8f6e88058e766c432</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>gac95ad430142a56f43f9f822372cd55fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga277eb1ae03f2becd10f2e62804e68876</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga8955b9b4eff0b4105d71a7e13e4b1292</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Obj</type>
      <name>IAUDENC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga5d9ff04b4365072edd2c884f82edd3f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Obj *</type>
      <name>IAUDENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga67b207a9e6d7ac649cf393bf9b89a758</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Params</type>
      <name>IAUDENC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga2dae626a844575f47e1c21cbcf840b35</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_DynamicParams</type>
      <name>IAUDENC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>gae0ec8b69b82b7b74261447fc165bc045</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_InArgs</type>
      <name>IAUDENC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>gaf5ff788677b23b690544cfa786a0f50c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Status</type>
      <name>IAUDENC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>gaf0f5c27286ce1a431b7a56dc618cf66f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_OutArgs</type>
      <name>IAUDENC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>gacaa7c792adc803608e262b3b8b27464b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga875abe1167c5304cec0cb23421f3215a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Fxns</type>
      <name>IAUDENC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga0bc230f35392261fbca693a29af3dd14</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IAUDENC1</name>
    <title>IAUDENC1 - Audio Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</filename>
    <class kind="struct">IAUDENC1_Obj</class>
    <class kind="struct">IAUDENC1_Params</class>
    <class kind="struct">IAUDENC1_DynamicParams</class>
    <class kind="struct">IAUDENC1_InArgs</class>
    <class kind="struct">IAUDENC1_Status</class>
    <class kind="struct">IAUDENC1_OutArgs</class>
    <class kind="struct">IAUDENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gaca757d01864682f891f4e79e27612615</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga3b351ca3f8350018b9411570be9a0e63</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gace019d488c6e5825adcf3950246b2ea5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Obj</type>
      <name>IAUDENC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga2a374221a000c97a35d1b461d092a154</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Obj *</type>
      <name>IAUDENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga674429c3839d2412844c94f288c88493</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Params</type>
      <name>IAUDENC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga65b4efd16306faeb757913240b470810</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_DynamicParams</type>
      <name>IAUDENC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga77dc068499de50015a259e6e6d24f67a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_InArgs</type>
      <name>IAUDENC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga9e03d59eba817233e0ce4ec4bf9841ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Status</type>
      <name>IAUDENC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga8c69f4914aa7cb790ebaf233f881bff7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_OutArgs</type>
      <name>IAUDENC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gac4d65960aeb5375bd15f1fdc908b8568</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gab08988284a4cb6779e196509c28705d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Fxns</type>
      <name>IAUDENC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gaed934ee1e76ebff885651644504786d3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IAUDIO</name>
    <title>IAUDIO - XDM Audio Interface</title>
    <filename>group__ti__xdais__dm___i_a_u_d_i_o.html</filename>
    <member kind="enumeration">
      <name>IAUDIO_ChannelId</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga2f7957b5da562687498a612165664179</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_MONO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a5f4470f75c884f7e4b04ca5f14ad7acf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_STEREO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a99e682b79cf46c280e7bafb9470b8f2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_THREE_ZERO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179aeabcf85e87c1c856a80b9824220aaaa2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_FIVE_ZERO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a9f5cb587cdcfb58952ecebce56532568</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_FIVE_ONE</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a05f535ae3ec20c8f007b9139eda2be73</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_SEVEN_ONE</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a092297b5eee8fa4bf24b7bac35a5c8ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_ChannelMode</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga42c416b540264a57d8728b07d765b14d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_1_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da4a44a2c8361fe98d5a083c7a067933e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da8cf64356a7097cea1e401ab31d7f5f8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_11_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da97b04f3a5f55abc03ec813694b1236d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da66f93b5b1244b8c4386f7f2bfdd81783</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_1</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da1f7b4e0d6455df92a428c33848351b45</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_1</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da77f0db8024cbb1df8d501f11b3b6ee11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_2</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14dacafa604d4031971085a63e74c6a1377a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_2</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14dac912907baaca2ef193290fb54359d022</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_3</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da022f51b4b16ed20be3a67fba6247a54a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_3</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14dae2eaa060c3dc06e7126eb088f2639466</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_4</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da0de8b72246498dc39781fa6f8f88feb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_DualMonoMode</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga3d6a55ad8d567db30ddca14e0180b501</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_LR</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a91fc7e77ba226b15008e2bcdc54e196b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_LEFT</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a33cf98bc81668fe9dc4eae0f5c41780b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_RIGHT</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a7ac285c92ea3048e5ed006af3d453b42</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_LR_MIX</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a0358f0cc0ad00b1551e0f7387b112e3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_PcmFormat</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gac631266018b8f5df7df1e52f65c2757f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_BLOCK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ggac631266018b8f5df7df1e52f65c2757faa072981204cf2b0d1cdddce4d9644154</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_INTERLEAVED</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ggac631266018b8f5df7df1e52f65c2757fa12f80fc0827105d6dc1df1dda485d161</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_EncMode</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga1d8af2cbae15bc609badbb328ab3a08c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_CBR</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga1d8af2cbae15bc609badbb328ab3a08ca422efb88eb135a5212bfa6b3600c35a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_VBR</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga1d8af2cbae15bc609badbb328ab3a08caf311198449fe7e6c2e20f79d66b7a0e8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IIMGDEC</name>
    <title>IIMGDEC - XDM Image Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_i_m_g_d_e_c.html</filename>
    <class kind="struct">IIMGDEC_Obj</class>
    <class kind="struct">IIMGDEC_Params</class>
    <class kind="struct">IIMGDEC_DynamicParams</class>
    <class kind="struct">IIMGDEC_InArgs</class>
    <class kind="struct">IIMGDEC_Status</class>
    <class kind="struct">IIMGDEC_OutArgs</class>
    <class kind="struct">IIMGDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga399a3c00c3d9181c9b84a86549c76344</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga4c2d7f1c15e1bfb70a61ae987979ad3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gaf11d65f2c57f70bfa994221f201fe483</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gac0a3c1ac74db21cce563ac1af0dcdcf9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Obj</type>
      <name>IIMGDEC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga4a37e31051dc54e2f24e31952aea3771</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Obj *</type>
      <name>IIMGDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gaafcce966766ae1ec2ba860294450603c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Params</type>
      <name>IIMGDEC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gae77c64aa29500fd75d6e7d79c8ae909d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_DynamicParams</type>
      <name>IIMGDEC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga21ebec27806ebbb0c1a0ce4263cd8b84</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_InArgs</type>
      <name>IIMGDEC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gaaec68bfa0d974501d8fe18b2d6633f53</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Status</type>
      <name>IIMGDEC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga6caf0f4102b77f7840ea43101baa4b04</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_OutArgs</type>
      <name>IIMGDEC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga2ae8d6af59574eddb03bf185c03a9b85</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga6d702c2802e8827926120bfeef5de0ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Fxns</type>
      <name>IIMGDEC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga96d1dab6f581fa305a2d2de30e3e74c2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IIMGDEC1</name>
    <title>IIMGDEC1 - XDM Image Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</filename>
    <class kind="struct">IIMGDEC1_Obj</class>
    <class kind="struct">IIMGDEC1_Params</class>
    <class kind="struct">IIMGDEC1_DynamicParams</class>
    <class kind="struct">IIMGDEC1_InArgs</class>
    <class kind="struct">IIMGDEC1_Status</class>
    <class kind="struct">IIMGDEC1_OutArgs</class>
    <class kind="struct">IIMGDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga71491761ce7894192d0953f62e87922e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga31103bf98612d017b2f5c11cc14ac842</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga184dc94b44712d77629d785cefe1398e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_Obj</type>
      <name>IIMGDEC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga7c18c8764f01b58c8acb40cdbc73f45a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_Obj *</type>
      <name>IIMGDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga8b9b9364f2c4232397b36890618b250e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_Params</type>
      <name>IIMGDEC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga1dc5bbefb7b02e6af196f5cd1974d1de</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_DynamicParams</type>
      <name>IIMGDEC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga5cc0992263406368f5de6dfd225230ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_InArgs</type>
      <name>IIMGDEC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga2fa41b603e298cfaa2e8675520779c3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_Status</type>
      <name>IIMGDEC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga60b6beba711cabc46b9c7c1b443709e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_OutArgs</type>
      <name>IIMGDEC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>gabb908d91ec302f5e671f24ac7c566d64</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga7bf45653f5c04d9407d13394663a896c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_Fxns</type>
      <name>IIMGDEC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga4d874f449b94550ca794ac4796fac454</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IIMGENC</name>
    <title>IIMGENC - XDM Image Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_i_m_g_e_n_c.html</filename>
    <class kind="struct">IIMGENC_Obj</class>
    <class kind="struct">IIMGENC_Params</class>
    <class kind="struct">IIMGENC_DynamicParams</class>
    <class kind="struct">IIMGENC_InArgs</class>
    <class kind="struct">IIMGENC_Status</class>
    <class kind="struct">IIMGENC_OutArgs</class>
    <class kind="struct">IIMGENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>gac529fc95d138993ea754d7ec6018a76c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga784e32991d906518f37e7a5146f5bf13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga827d911bc03c756096d03677ecef5f39</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga04b132637a7c8ee29f0738fce76fed32</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Obj</type>
      <name>IIMGENC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga4217146884145131fe78ca50e2f6bcaa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Obj *</type>
      <name>IIMGENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga58729c682862e2e74a9b2abb916f4b88</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Params</type>
      <name>IIMGENC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga679f323646f1e14be4d9f868da227d94</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_DynamicParams</type>
      <name>IIMGENC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>gabde1297efe8f8e72bc2d3a7b4021420e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_InArgs</type>
      <name>IIMGENC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>gade8888b678afcee660768f9b1941a323</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Status</type>
      <name>IIMGENC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga23972a48a687c0e9368c1951e4125287</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_OutArgs</type>
      <name>IIMGENC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga58685c09a0cd079a38b4a9b9a488c88f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>gabe17217ceb746ff5b0e564a6f3dafa36</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Fxns</type>
      <name>IIMGENC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga637288210ec18230b78533fd7e649e0c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IIMGENC1</name>
    <title>IIMGENC1 - XDM Image Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</filename>
    <class kind="struct">IIMGENC1_Obj</class>
    <class kind="struct">IIMGENC1_Params</class>
    <class kind="struct">IIMGENC1_DynamicParams</class>
    <class kind="struct">IIMGENC1_InArgs</class>
    <class kind="struct">IIMGENC1_Status</class>
    <class kind="struct">IIMGENC1_OutArgs</class>
    <class kind="struct">IIMGENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga9397909ae52d3bb547e18fd8719c333f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga28ded0a8bcf744f7ba289e9b6ae576ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>gad065eddb703a62fa12207544e8546f1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Obj</type>
      <name>IIMGENC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>gae883e427f4108a6268dfabb41ecc9425</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Obj *</type>
      <name>IIMGENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga93fe674dab191daf45489f5bf84134fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Params</type>
      <name>IIMGENC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga9d42d07332b63e9e52dc4269150ff28c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_DynamicParams</type>
      <name>IIMGENC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga1828bd15b50a8e53bc1d6c8894b7c2fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_InArgs</type>
      <name>IIMGENC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga0dbb4ebafcbb6338c02b0b93eac3bbd0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Status</type>
      <name>IIMGENC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga98a45ae63a86a4a872de58c32d3740f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_OutArgs</type>
      <name>IIMGENC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga7c68d329b86a4573b946685413235613</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga391d9f36711efa2b355c14a03af7abf8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Fxns</type>
      <name>IIMGENC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga125998b1a450463583b220ea0dae7ea5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH</name>
    <title>ISPEECH - XDM Speech Interface</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h.html</filename>
    <member kind="enumeration">
      <name>ISPEECH_VoiceMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ga2a5ad3bdafe1e87e2aece51b52700694</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_VOICED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>gga2a5ad3bdafe1e87e2aece51b52700694aabfd422047de38c75ff1caf9f22c7ce0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_UNVOICED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>gga2a5ad3bdafe1e87e2aece51b52700694a980404cd1fc1ad41d588319dbe3ed14e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH_CompoundLaw</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>gaed9882c92cb24a565d63fb157a3bc0c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ggaed9882c92cb24a565d63fb157a3bc0c8a8913b9e1f47a5e7ab97578c12a115a06</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_ALAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ggaed9882c92cb24a565d63fb157a3bc0c8a254d39814c846c8f5574226162efb458</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_ULAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ggaed9882c92cb24a565d63fb157a3bc0c8a1edb2eb2e360b5292385c671181cfafd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1</name>
    <title>ISPEECH - XDM Speech Interface</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_NullTrafficMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ga89ae95d0bce445642cc16c57c0d0968b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_NULLTRAFFICMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga89ae95d0bce445642cc16c57c0d0968ba87608e5344ca37912234e93b7da59630</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_NULLTRAFFICMODE_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga89ae95d0bce445642cc16c57c0d0968baa933263447c238bac7df6321e0a11694</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_NULLTRAFFICMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga89ae95d0bce445642cc16c57c0d0968bab4fa5328474e29188aee74797c414aec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_PostFilter</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gac1c8b96d345c0fe4220cdc18669223ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_POSTFILTER_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ggac1c8b96d345c0fe4220cdc18669223aca6f4c302f3c9af56f64806d0861abdd04</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_POSTFILTER_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ggac1c8b96d345c0fe4220cdc18669223acac8e86af79d47c31e04829919bd972705</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_POSTFILTER_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ggac1c8b96d345c0fe4220cdc18669223aca37e583ca98bc612bd7dd9c5c451b3cb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_VADFlag</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ga6a40ba3d92ffc5b64a9987f870f57f9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_VADFLAG_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga6a40ba3d92ffc5b64a9987f870f57f9aa4d73bb62c3d482112334d7d84cc3cce4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_VADFLAG_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga6a40ba3d92ffc5b64a9987f870f57f9aaa11a5dcd1ae9d5e026cc83cfbb330919</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_VADFLAG_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga6a40ba3d92ffc5b64a9987f870f57f9aa7e66df60583013e51ba279139d13e0b8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_AMR</name>
    <title>ISPEECH_AMR - XDM Speech Interface (AMR)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ga566156cfc46f87e73de6bba8eba536c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_4P75</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a99fc4c000b12f09fdcad255694d96d9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_5P15</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a5e8739090838a47dded4ce9c617b2446</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_5P9</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a633eb6129d753bd00318c91d5c00647d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_6P7</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a61ffd17b289e507380d69e1eca1c2142</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_7P4</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a45de32cc24a76e2a16bb7f9eecdccb48</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_7P95</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a3d3312de4a395a0a154c13043e6be957</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_10P2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a7ca5663dc228a321dff14edaa5887aa1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_12P2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9af65cf724c197d3cad7dd932c44e7cba1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a4943c07dd5924193d6a0a8ce7986c295</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_CodecSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gaf6d3e11e5b975770afd11caadcfd8d20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_CODECSELECT_PRIMARY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaf6d3e11e5b975770afd11caadcfd8d20ab414f0b43b46c6407188ab18f07abcd5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_CODECSELECT_SECONDARY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaf6d3e11e5b975770afd11caadcfd8d20a06effe2e6cda9dce3ce1773be4a941ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_CODECSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaf6d3e11e5b975770afd11caadcfd8d20a055d66e70f1130f7dd8eab2f05e01e88</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_PackingType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gaeecf736d60bd00c5ac86924b1404ad90</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_IF1_NOCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90af79b43d1eb83abaa5510928b71a4abe4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_IF1_WITHCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90a387c71ba08310d9668dae3883fe3ec28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_IF2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90af1bbe3a63ca9d6f595b83fa6b91a424c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_MIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90a71f0423b70c34ca2afc083e5a62585e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPEFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90aa00c9bc982212f0c55d9f1477bb62ded</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_VADSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gabcb3c4ae9c054b69eabd71bde775d86f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_VADSELECT_VAD1</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggabcb3c4ae9c054b69eabd71bde775d86faf55aa3a28417e1d0da82b546a9b1789d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_VADSELECT_VAD2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggabcb3c4ae9c054b69eabd71bde775d86fa35a83e8d85620ee0316880049aef8078</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_VADSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggabcb3c4ae9c054b69eabd71bde775d86fa4789cd0dfd81240681e04f81d7ead9fd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_EVRC</name>
    <title>ISPEECH1_EVRC - XDM Speech Interface (EVRC)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_NoisePreProc</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gac0650f1ca8b6e4b6770c038653594633</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NOISEPREPROC_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggac0650f1ca8b6e4b6770c038653594633a9265da05d970eef081d3dd7ce9dbd4be</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NOISEPREPROC_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggac0650f1ca8b6e4b6770c038653594633aea1b311ebb57531b23d73857aca828d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NOISEPREPROC_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggac0650f1ca8b6e4b6770c038653594633a7805bfa6106590db880f7bf892c680d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_TTYMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ga84ecf83f56e51c826bda7095a90b989c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989ca38d82305bbfabe8919932618e2fdbae3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_45P45BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989cae7259cf80bda232f425379647111b048</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_50BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989ca602b2e9a9e7a1dbaaeafa889230811ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989ca1d60ffd9d5228746176eff0117c948fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_Mode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gafe2167d2bb6dc8269af94931fdedc9f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_PREMIUM</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1ae8264ae8cb01ccb0953e29e0c3b21cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_STANDARD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a8fc2dd52641a64b43d8034b4c0acd1c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_ECONOMY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a044dbd71700d328377606f5285bdde2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_CAPACITYSAVE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a7d31d7179ec70e3e28954a6d989d688a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_HALFRATE_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a5920a92eccc31bc941e54ab46a84a80b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1ad54aeffbd74c41175c7c3f7d427ad144</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_NullTrafficMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gaf9e99a0ee5da7b5ccc1125cb851f62d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NULLTRAFFICMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggaf9e99a0ee5da7b5ccc1125cb851f62d5ac0a7d8a945501ece57576b2083109b51</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NULLTRAFFICMODE_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggaf9e99a0ee5da7b5ccc1125cb851f62d5a09e4988544590cc4e625e206f4492a95</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NULLTRAFFICMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggaf9e99a0ee5da7b5ccc1125cb851f62d5acd73322310099c31a2ff72efa14aff98</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_G722</name>
    <title>ISPEECH1_G722 - XDM Speech Interface (G.722)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_G722_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>gac295a2de036479d0d0ed7b0664a9e176</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_BITRATE_RATE0</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>ggac295a2de036479d0d0ed7b0664a9e176a1d894b6e89d40900bfcba147e6f8b827</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_BITRATE_RATE1</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>ggac295a2de036479d0d0ed7b0664a9e176a88bbc54c47fdbb88e7fd8919aacafc4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_BITRATE_RATE2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>ggac295a2de036479d0d0ed7b0664a9e176ad17ce0b8ef52bbfee2a015dd7e924418</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_BITRATE_RATE3</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>ggac295a2de036479d0d0ed7b0664a9e176ae162cb433c4f245b7378ce466d0c07ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>ggac295a2de036479d0d0ed7b0664a9e176a585d72fb1c9625ed9efa3096f10f18a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G722_CodecSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>ga1353c3c849712e0709adba818caea0b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_CODECSELECT_NONITUMODE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>gga1353c3c849712e0709adba818caea0b8a5d8d9b028450107199bfffb5bebee792</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_CODECSELECT_ITUMODE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>gga1353c3c849712e0709adba818caea0b8a9fa58c61e2d05cca46d352590652e4fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G722_CODECSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g722.html</anchorfile>
      <anchor>gga1353c3c849712e0709adba818caea0b8a94bdb07ea62d12e5e05607730b523465</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_G7221</name>
    <title>ISPEECH1_G7221 - XDM Speech Interface (G.7221)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_G7221_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>ga475f2396658334f14e87f0c7b29369e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G7221_BITRATE_24</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga475f2396658334f14e87f0c7b29369e7affa175c8d6f26adfb882b092a5d46a2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G7221_BITRATE_32</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga475f2396658334f14e87f0c7b29369e7a74cf5d33d219f0a9bf9d5c5dd4cd9130</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G7221_BITRATE_48</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga475f2396658334f14e87f0c7b29369e7a7ce021f6c3be432c82353ae502b6c491</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G7221_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga475f2396658334f14e87f0c7b29369e7aae637f95da55289db536dbe8bf4be58f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH2_G7221_SamplingRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>ga43703aaa2b3cf853bd549425787cbd7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH2_G7221_SAMPLINGRATE_WIDEBAND</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga43703aaa2b3cf853bd549425787cbd7eabe6965a9f25aeb890f86228d40b331a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH2_G7221_SAMPLINGRATE_SUPEWIDEBAND</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga43703aaa2b3cf853bd549425787cbd7eac4ad50e850479bd4b0b575b924c569d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH2_G7221_SAMPLINGRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g7221.html</anchorfile>
      <anchor>gga43703aaa2b3cf853bd549425787cbd7ea9ecedebcd3c8dc4938152e6745963232</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_G723</name>
    <title>ISPEECH1_G723 - XDM Speech Interface (G.723)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_G723_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>ga3a60101c5d140281222eac55ceff3da7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_BITRATE_5P3</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga3a60101c5d140281222eac55ceff3da7a25ef1e08d5e98120471e2c1526c27d2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_BITRATE_6P3</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga3a60101c5d140281222eac55ceff3da7a1e8c817ed1c0bdb7fb55444d6e009353</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga3a60101c5d140281222eac55ceff3da7a27554cc9a39b340e0ecd8103719dbffd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G723_NoisePreProc</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>ga6030020ca3fe69e0d0aaf01728097eae</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_NOISEPREPROC_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga6030020ca3fe69e0d0aaf01728097eaeaf62d62d2826cc658130274930660ebb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_NOISEPREPROC_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga6030020ca3fe69e0d0aaf01728097eaeaae41fd25b630c16118a4ffd24276a990</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_NOISEPREPROC_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga6030020ca3fe69e0d0aaf01728097eaea889aecb01aca1afc4152f95a8616c147</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_G726</name>
    <title>ISPEECH1_G726 - XDM Speech Interface (G.726)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_G726_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ga5842c3df33b0aec82142cf1fd3ece12e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_16</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12ead390f395f226d55baf122302237cdf96</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_24</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12eab03a295d41900a44a9c94f3c94baceb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_32</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12ea769ceb35bd641aac0e5531f1641285ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_40</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12ea8548d58b48b1e6ed42f18024d4793a0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12eac2a351d221bfea5d27b09134cb59e89f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G726_CompandingLaw</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gaa397870da5177152ea1b53fe9e3b6265</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265ad0d2189fda7ed821f96577af3b5ba01c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_ALAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265ada1a67c0602e35ec5c10fba0044d6eae</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_ULAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265a1177bc10761f7968fb1787cf2c5bf599</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265a386b0d978c9c63729567540b953c7105</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G726_PackingType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ga889c3788d8981cec15df6971d29306ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_PACKTYPE_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga889c3788d8981cec15df6971d29306eaadc717daa84241ac0f3964a2e5a0f564a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_PACKTYPE_RTPSPECIAL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga889c3788d8981cec15df6971d29306eaa3e3a96fa9418c89e58ee8dcd75868ada</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_PACKTYPEFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga889c3788d8981cec15df6971d29306eaa9cfac3209bb22296fa011e0875b37d27</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_ILBC</name>
    <title>ISPEECH1_ILBC - XDM Speech Interface (iLBC)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___i_l_b_c.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_ILBC_CodecSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___i_l_b_c.html</anchorfile>
      <anchor>gae9f39439122ced4e48605f36eeae838c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_ILBC_CODECSELECT_20MS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___i_l_b_c.html</anchorfile>
      <anchor>ggae9f39439122ced4e48605f36eeae838ca00f4cc23be9bc2a5ac8813cd5016bfdf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_ILBC_CODECSELECT_30MS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___i_l_b_c.html</anchorfile>
      <anchor>ggae9f39439122ced4e48605f36eeae838cafc795d957f51cd2402f0d9f1ab33909a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_ILBC_CODECSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___i_l_b_c.html</anchorfile>
      <anchor>ggae9f39439122ced4e48605f36eeae838cac527f79667c672cd8637376288b4998d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_PCM</name>
    <title>ISPEECH1_PCM - XDM Speech Interface (PCM)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_PCM_CompandingLaw</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>ga88faff6d78d80fbb0d3712642a16e1de</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1dea9b50f6c66d7d1250dcede6c3076bdd45</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_ALAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1deaee6ede174249a7ee7b67daccf7437037</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_ULAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1deac8a7be49178242066ee82b6800905614</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1dea5b651f269b71e3d9cfa3fe8e6d494957</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_SMV</name>
    <title>ISPEECH1_SMV - XDM Speech Interface (SMV)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_NoisePreProc</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gab60bcb3149344cd20bc1d9d1696a208d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208da499e6a288509dc326fa6b2a3a211d092</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_NSA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208da5adad45c8630058c96bdafdb030931f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_NSB</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208dab44c90dd52dc8fa6cf0c528ffd540e77</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208da39b444aeb37c32f83aee67c415679c04</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_VADSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gafb1b4ac5540a4d13c730aaf88dc023be</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_VADSELECT_VADA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggafb1b4ac5540a4d13c730aaf88dc023bea1c29ab48b1ef4af475eb3e95c3e99613</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_VADSELECT_VADB</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggafb1b4ac5540a4d13c730aaf88dc023bea6b4ba999b85279488c3db4cae5aee7f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_VADSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggafb1b4ac5540a4d13c730aaf88dc023bea7db43399885c4cf5f1d122913fb1f0ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_TTYMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gad14fd77adfb92f65088ef0b2e6affebd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebdafe82060bfabefca805a51b04c4381003</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_45P45BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebda0105f17fb6d97417b56dccc9fde3c73e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_50BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebda34cd37f4c8438ade28d24ba1bf3d401b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebda3bbed1bf636d4ccbca35915ca01cff7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_DTMFMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ga91d61a3a68a62af8f73afb871f1d0d5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DTMFMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga91d61a3a68a62af8f73afb871f1d0d5eabb2bce58703d51269e15c8a9bbbcc11f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DTMFMODE_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga91d61a3a68a62af8f73afb871f1d0d5ea325b10e0073a2d82e2d272b2dba7149e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DTMFMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga91d61a3a68a62af8f73afb871f1d0d5eafa3d0d05dcad59534119e6d6f60326a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_DataMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ga9edbd6e156d41f8673e3c26841e4d1bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfa2c0c4bae0b4e38ec003b221f01bc6c4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_HALFRATE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfae9e8887b1b23fc33614aab40523f7f5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_FULLRATE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfa02c442553dc94438337a7f0b5217d587</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfa94de3a5a683830f5e91b1f488a7598d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_Mode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gae79f94ea770cb63e97b6b08e7021a7d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_PREMIUM</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a605f932ca11a86e867b24a87f7c2cb4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_STANDARD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a0a3ab57cb83cc3b78664e5f8ee9dc0af</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_ECONOMY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a30a76e29dc26f9d6b58461669bbc485f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_CAPACITYSAVE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a3013d7d320c975226bb2785ce39ca852</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_PREMIUM_HALFRATE_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a764290efa25fc2f82cba26bed3b788ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_STANDARD_HALFRATE_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a02765b3d59b321e563dcfb2aefdeb8b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a04f904d973435832277167859b16647b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_WBAMR</name>
    <title>ISPEECH1_WBAMR - XDM Speech Interface (WBAMR)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_WBAMR_PackingType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>ga8561c34af4f9307ee99eec22b9023da7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_IF1_NOCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a0fefa4be1b4fb97d523329d3bbc3d42e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_IF1_WITHCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a54c89d0a6ae8cb89e5097e39a5e4b06d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_IF2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a67d42cd4150cd7c05378bc1960a92375</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_MIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7acc83cc0d4a577f3f93025e2eff1e2bb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPEFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a568e1ddb1a8b6fff6d9c018c9ac3c7a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_WBAMR_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>ga60889eeb323f514221f3623e9f749716</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_6P60</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a7821bf03d8f659a4835541eb711741e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_8P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a5109ab789372f28d132350cef02cbe70</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_12P65</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a6cf6726fa2af44d0362bebdbbb05b642</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_14P25</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a823b5ea1854bf86a1534e790e1410b3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_15P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a82efce13fac3031b423f01efa1e00969</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_18P25</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716ab306cb8177634d2dadd04c0ab3aadb32</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_19P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716abf4b551e950f3dca496dd1781d7d8811</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_23P05</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716adc1493eee4d5e1df49cade040980d720</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_23P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a45f6d3b08c97d14e0e4017c9328bc965</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716ac599e0494b8cbc4788a5abf95232d87f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPHDEC</name>
    <title>ISPHDEC - XDM Speech Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_s_p_h_d_e_c.html</filename>
    <class kind="struct">ISPHDEC_Obj</class>
    <class kind="struct">ISPHDEC_Params</class>
    <class kind="struct">ISPHDEC_DynamicParams</class>
    <class kind="struct">ISPHDEC_InArgs</class>
    <class kind="struct">ISPHDEC_Status</class>
    <class kind="struct">ISPHDEC_OutArgs</class>
    <class kind="struct">ISPHDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga1f604442aeef3232e6acc17de9ab51be</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga59bee2fd448023ee04185aaf874cfb45</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga6f7990140490a16e025ffc1d670503a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga48b7104fbe8c5c6cbe2d17b7725e278b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Obj</type>
      <name>ISPHDEC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>gabf3985c40fe62d218e3e746f6bb1f476</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Obj *</type>
      <name>ISPHDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga31722647a0a3b99c36ef57af89d1351a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Params</type>
      <name>ISPHDEC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga03ad8e6acbd271d49c8ba35094709fff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_DynamicParams</type>
      <name>ISPHDEC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga2993b719fc8801698bbd1cf7a28161ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_InArgs</type>
      <name>ISPHDEC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga25a73337c1b6b67ef315490e5873e521</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Status</type>
      <name>ISPHDEC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>gaa4dd6d6f5dfbcfec97f62b25771bc7e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_OutArgs</type>
      <name>ISPHDEC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>gaace4fafa512b9570b0591d3887233561</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga73cebce9e1ccbbb0afbb14a4f984a94e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Fxns</type>
      <name>ISPHDEC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga52c95d9aeafde3769cd70225a108dbd2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPHDEC1</name>
    <title>ISPHDEC1 - XDM Speech Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</filename>
    <class kind="struct">ISPHDEC1_Obj</class>
    <class kind="struct">ISPHDEC1_Params</class>
    <class kind="struct">ISPHDEC1_DynamicParams</class>
    <class kind="struct">ISPHDEC1_InArgs</class>
    <class kind="struct">ISPHDEC1_Status</class>
    <class kind="struct">ISPHDEC1_OutArgs</class>
    <class kind="struct">ISPHDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga87514ee862e0b5a35fcf460a65277a59</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga4d2a2279596c72d1d505a94504af9028</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga712c57b5a16ed53f484260f8ea48c1ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_Obj</type>
      <name>ISPHDEC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaac7e3af97812cbcdb7541ee5765e3d62</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_Obj *</type>
      <name>ISPHDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga65c6e2d620b2b46594453ed84ded159f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_Params</type>
      <name>ISPHDEC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaae2328eefd20007f1193b99877cdabc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_DynamicParams</type>
      <name>ISPHDEC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga38991e2c05062852fe48758b52f4fb0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_InArgs</type>
      <name>ISPHDEC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga04ee73d7eec05a20e95f8026763dfcc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_Status</type>
      <name>ISPHDEC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga4e817a5cec631fe3ad390c43da78dfb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_OutArgs</type>
      <name>ISPHDEC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga742ed560c798cc48436f89deb14542d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaef02eb7c18d91b4d4183284c0c4c1d79</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_Fxns</type>
      <name>ISPHDEC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga8124c15f66854b30e6326f78ffef1b9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPHDEC1_FrameType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga80a8f44022a98fb899a102310489ebf9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SPEECHGOOD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a1813dc29630e6fd7c6054187077f1b0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SIDUPDATE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a10c27d875c65247b78a99e1d28916dbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_NODATA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a46a224a6fd50ee1f3fe602c64759c158</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SPEECHLOST</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9ad7f3cff31625d40f310aaf0a575c1117</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_DEGRADED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9abce8dcb8ad83419dc8225b66d2a36c84</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_BAD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9ab576985e54ff855753483500e17362ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SIDFIRST</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a6bcbda5d5df41d58f5a5034fdabffed2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SIDBAD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a4cf9a9b2ba2919adf36aac69de785623</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_ONSET</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a0a642d1a2df6645d04a98d198b42a5b3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPHENC</name>
    <title>ISPHENC - XDM Speech Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_s_p_h_e_n_c.html</filename>
    <class kind="struct">ISPHENC_Obj</class>
    <class kind="struct">ISPHENC_Params</class>
    <class kind="struct">ISPHENC_DynamicParams</class>
    <class kind="struct">ISPHENC_InArgs</class>
    <class kind="struct">ISPHENC_Status</class>
    <class kind="struct">ISPHENC_OutArgs</class>
    <class kind="struct">ISPHENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gaa70981aaff27acca8dc15214ad0538ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga7e16b5ce02a4ae9c232445e1b1628f78</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gac472f9baf3f8de53cfef7d83a05df2fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga3769ec58a3fb188995557ab5f4986a0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Obj</type>
      <name>ISPHENC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga0a9e3d70ceb2e325ce5dd936acf32627</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Obj *</type>
      <name>ISPHENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga53d4faeb65284507a1eab034036a11ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Params</type>
      <name>ISPHENC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gaf645de0a409f1f764ae9b957267b3d1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_DynamicParams</type>
      <name>ISPHENC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gab3320909767956c29645f21df627119f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_InArgs</type>
      <name>ISPHENC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga1cb1ad45116d81d3f36778e5212bce70</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Status</type>
      <name>ISPHENC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga10dd91e813a3f77d33b3159467114fe6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_OutArgs</type>
      <name>ISPHENC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gad186fc61c770aff4e10a815e8178f6ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga835dc5261cc96bd0c6a77c1b33f5f197</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Fxns</type>
      <name>ISPHENC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga1bc5d2ae806ac94ac61781db9e02ef2c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPHENC1</name>
    <title>ISPHENC1 - XDM Speech Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</filename>
    <class kind="struct">ISPHENC1_Obj</class>
    <class kind="struct">ISPHENC1_Params</class>
    <class kind="struct">ISPHENC1_DynamicParams</class>
    <class kind="struct">ISPHENC1_InArgs</class>
    <class kind="struct">ISPHENC1_Status</class>
    <class kind="struct">ISPHENC1_OutArgs</class>
    <class kind="struct">ISPHENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga332d5aa164c31b5681b2cea91d7e5016</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga22ade7510d7d35abb25a60b64f44a92d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga8f31ee15e0081314b41914efc29c5a9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_ENOOUTPUT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaa82f51e92fce79e8c507771c443b3e35</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Obj</type>
      <name>ISPHENC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga37332094aad46d9682ce2fbd5321acb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Obj *</type>
      <name>ISPHENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga995e9ed220499520c23c0df118d7acd8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Params</type>
      <name>ISPHENC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga25b6c4e0bc7ee4c8958c147c7a1ba945</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_DynamicParams</type>
      <name>ISPHENC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga6a52fdc116344056168895e8d84b88e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_InArgs</type>
      <name>ISPHENC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga4b2e68bc0c6fe193573a9404d9be7514</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Status</type>
      <name>ISPHENC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga0278e96b820ef8de6b796e3b5542151c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_OutArgs</type>
      <name>ISPHENC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga9e0d5cfb53ab43d7c8979cac9115c942</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga16523cd9d058f54acb8f5d1bd4bd5d97</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Fxns</type>
      <name>ISPHENC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gac862de82f55bd5902ae3c5ffd6e39344</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPHENC1_FrameType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga8e6571f54c1264844aa2c0e05119a624</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHENC1_FTYPE_SPEECH</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gga8e6571f54c1264844aa2c0e05119a624ae24818a9a9b1a23146162bb950ab035a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHENC1_FTYPE_SIDFRAME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gga8e6571f54c1264844aa2c0e05119a624aa8c57b4e299ff4038b40a5911eff281d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHENC1_FTYPE_NODATA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gga8e6571f54c1264844aa2c0e05119a624a6e2c23204ce4ae3dd2001aa610644638</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IUNIVERSAL</name>
    <title>IUNIVERSAL - XDM Beta Universal Algorithm Interface</title>
    <filename>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</filename>
    <class kind="struct">IUNIVERSAL_Obj</class>
    <class kind="struct">IUNIVERSAL_Params</class>
    <class kind="struct">IUNIVERSAL_DynamicParams</class>
    <class kind="struct">IUNIVERSAL_InArgs</class>
    <class kind="struct">IUNIVERSAL_Status</class>
    <class kind="struct">IUNIVERSAL_OutArgs</class>
    <class kind="struct">IUNIVERSAL_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IUNIVERSAL_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga27f56f76d4fd15aa0d7e0ebbcb861d4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IUNIVERSAL_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gad0ebbb98143ab6995c1268efa4cbf150</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IUNIVERSAL_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gacb40d81bebf31e7de2267d6cb9bde3a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Obj</type>
      <name>IUNIVERSAL_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gab924ddc6fe5969446bf90dd1c5e3d155</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Obj *</type>
      <name>IUNIVERSAL_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaa47732c807c80b94d7f29cf72d9ed694</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Params</type>
      <name>IUNIVERSAL_Params</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga59a62f39d4be49588cff623d988567a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_DynamicParams</type>
      <name>IUNIVERSAL_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga016853eb31ba4b4d283e58c1e9b4c587</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_InArgs</type>
      <name>IUNIVERSAL_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga8bbbcec1866c91d201e96133dd864b5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Status</type>
      <name>IUNIVERSAL_Status</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga19fd3dae8089c3fb72cfb1204181f013</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_OutArgs</type>
      <name>IUNIVERSAL_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gade6b48848cae054b9d3e218bdb042f0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IUNIVERSAL_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga17756fe87be378872a1647a668f18c9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Fxns</type>
      <name>IUNIVERSAL_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaf653adad151d5fad6f46da48ee4d5e1d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDANALYTICS</name>
    <title>IVIDANALYTICS - XDM Beta Video Analytics Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</filename>
    <class kind="struct">IVIDANALYTICS_Grid</class>
    <class kind="struct">IVIDANALYTICS_Rule</class>
    <class kind="struct">IVIDANALYTICS_Obj</class>
    <class kind="struct">IVIDANALYTICS_Params</class>
    <class kind="struct">IVIDANALYTICS_DynamicParams</class>
    <class kind="struct">IVIDANALYTICS_InArgs</class>
    <class kind="struct">IVIDANALYTICS_Status</class>
    <class kind="struct">IVIDANALYTICS_OutArgs</class>
    <class kind="struct">IVIDANALYTICS_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaf9760765b216cdbc5079be6e1904b795</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gac314c2ce1b08297ccfbf0c63dc3a257c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaebc9260d46c5e53d35bb4f5f100b96ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_SETRULE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga3d56d0f1a5afc78401314d4fdee63dc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_CLEARRULE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga44579981d799141f6e0368acf999b8e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_MAXTARGETS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gade504e11b8b0bc9e3925640b2cafebd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_MAXEVENTS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaa71cddcd1d8b054c48f9966866e386b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Grid</type>
      <name>IVIDANALYTICS_Grid</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga2953e064ae804a213eaac01be39ef4a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Rule</type>
      <name>IVIDANALYTICS_Rule</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga94eac45c9f8561d031d32e6f98fd9135</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Obj</type>
      <name>IVIDANALYTICS_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga9ee894169be9a6fddc0c204f1df3be03</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Obj *</type>
      <name>IVIDANALYTICS_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga26ad8d51394ef852e42cc1c4948de0eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Params</type>
      <name>IVIDANALYTICS_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaee12c2935ce12fde35d3b1aa30a825c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_DynamicParams</type>
      <name>IVIDANALYTICS_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaba23676c5dbd3f62cf4c51c9813bfff6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_InArgs</type>
      <name>IVIDANALYTICS_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gad2f186cdde8a6a983250555ab1249e17</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Status</type>
      <name>IVIDANALYTICS_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga936e9423f461aafaa57e3f8c3710050d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_OutArgs</type>
      <name>IVIDANALYTICS_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga69b8679986bd047c3aec860a7cc6c164</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDANALYTICS_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga5be3d2530a181c9826dc4c3322344132</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Fxns</type>
      <name>IVIDANALYTICS_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gad48dd8e1ca56c90a761d1a96ede97cb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_AnalysisMask</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga4a8b524c62f02622465884156f2c6f59</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_MOTIONDETECT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga4a8b524c62f02622465884156f2c6f59a3cad03f6d20ecbdc0103df4e73101e47</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTRACKING</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga4a8b524c62f02622465884156f2c6f59ad6da9e357c2c7721f04b1ff5beb38929</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_USERBASE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga4a8b524c62f02622465884156f2c6f59af48becd353153ab4285b4305d3467624</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_ObjectType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga40e54ed88eb97360b4ca8f244c2b9f62</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTYPE_VEHICLE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga40e54ed88eb97360b4ca8f244c2b9f62ad9daa80daa5e20d4c010d577a7347918</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTYPE_HUMAN</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga40e54ed88eb97360b4ca8f244c2b9f62ad82eb960014d7ede011678c5705ee1ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTYPE_USERBASE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga40e54ed88eb97360b4ca8f244c2b9f62ab6cd25f42da6d9e7e43ebb4ce272cf97</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_ActionType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga47e8c8886c5d35981380c922db1eeab4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_LOITER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4aba5736e40d9f5ab0ff2590d66e04edc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_ENTER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a86e2c5b11a0e4c20d245cb6de0cf8bb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_EXIT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4af0f133918f8b9575ca32e05f512270a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_APPEAR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a681d3cbb139a67f813899f0be3250f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_DISAPPEAR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a570191d5b93ea4345fb5bcb91f3a4d52</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSL2R</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a25a21e42fece6687a27205a828e025e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSR2L</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4aa4df30a99741c60e039d8042476922c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSU2D</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a82b0a4cbd8efa23126decf532abcf6e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSD2U</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a899876b69418a4b7187e73a1fd22e0a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_USERBASE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a20b606cf024b3812694d53e0f9985cde</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_ViewState</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gab02bfb6a7b2a76eac00f1bb7d3801662</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_VIEWSTATE_BAD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ggab02bfb6a7b2a76eac00f1bb7d3801662a42c1e0003605067a4def8cfd4c061dba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_VIEWSTATE_GOOD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ggab02bfb6a7b2a76eac00f1bb7d3801662a093b1e31c7bb032707492cfe72cd8fe8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDDEC</name>
    <title>IVIDDEC - XDM Video Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_d_e_c.html</filename>
    <class kind="struct">IVIDDEC_Obj</class>
    <class kind="struct">IVIDDEC_Params</class>
    <class kind="struct">IVIDDEC_DynamicParams</class>
    <class kind="struct">IVIDDEC_InArgs</class>
    <class kind="struct">IVIDDEC_Status</class>
    <class kind="struct">IVIDDEC_OutArgs</class>
    <class kind="struct">IVIDDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>gafa63f96dc4a5430e21a8454a609fe205</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga3fc5e8b896808e13dc4a1dd037592c61</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga0f3f0d74b7b4895adc3601998895b930</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga3ff96fb69baef4d04b31682234957de1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Obj</type>
      <name>IVIDDEC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga3cb6d20f12f75e317c23bc589c52c138</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Obj *</type>
      <name>IVIDDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>gabc249717018b892fafca9425887b7464</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Params</type>
      <name>IVIDDEC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga9353fb92232e5ee72309b8e6b6adf93d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_DynamicParams</type>
      <name>IVIDDEC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga855fb68e46e6667d0290e10ce8f8e204</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_InArgs</type>
      <name>IVIDDEC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>gaf3d7a7eb7592d3dba52093f8fb343376</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Status</type>
      <name>IVIDDEC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>gab1338cbc538494391df2616888eaa5bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_OutArgs</type>
      <name>IVIDDEC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga58be26a3c32d08b313af8285a718fdc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga7f8d05603824403adb994fe59d55bdcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Fxns</type>
      <name>IVIDDEC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga7d40d5c65617921d788f4eb3da32a79b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDDEC1</name>
    <title>IVIDDEC1 - XDM Video Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</filename>
    <class kind="struct">IVIDDEC1_Obj</class>
    <class kind="struct">IVIDDEC1_Params</class>
    <class kind="struct">IVIDDEC1_DynamicParams</class>
    <class kind="struct">IVIDDEC1_InArgs</class>
    <class kind="struct">IVIDDEC1_Status</class>
    <class kind="struct">IVIDDEC1_OutArgs</class>
    <class kind="struct">IVIDDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gaee746b34bc5327d7755c36e9dbb93f99</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gac76d0185e99e4dfb7d33f8b06d73a731</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga8c35fdf3e5022078dfee9064ac08f52a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_FREE_BUFF_SIZE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gaf9fd4bffd14decc067ecf3f2c486605e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Obj</type>
      <name>IVIDDEC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga88edd89a93bd20b4ba77a57ba6ed2807</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Obj *</type>
      <name>IVIDDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga3470ccaa78e2f267e1b8e08c7ae25455</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Params</type>
      <name>IVIDDEC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga47b5d070c3f24100d0c9552d703d3a8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_DynamicParams</type>
      <name>IVIDDEC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga5d174b8b524e1ee158218ee56ad39c48</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_InArgs</type>
      <name>IVIDDEC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gaf9d8d831cf2d98e947ab90be6d30aba4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Status</type>
      <name>IVIDDEC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga5fd52b2bb90deee30a14d971f0b88c13</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_OutArgs</type>
      <name>IVIDDEC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gae2902f6a2c9d664ad06ffae854d14a51</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga88cf5de26dfa5e05400b2d6e25ea027d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Fxns</type>
      <name>IVIDDEC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga97fe72473710158dbe2ad783c675d0e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDDEC1_FrameOrder</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga499b0864c81e20998f743b9e834e10c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC_DISPLAY_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gga499b0864c81e20998f743b9e834e10c6a9fb1a3543d4c48a7c5a7cf9242058746</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC_DECODE_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gga499b0864c81e20998f743b9e834e10c6a3a281632bb399cb0c73a18ebff327706</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC_FRAMEORDER_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gga499b0864c81e20998f743b9e834e10c6aebd67fc7b931e0796cfa9a970137b12a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDDEC2</name>
    <title>IVIDDEC2 - XDM Video Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</filename>
    <class kind="struct">IVIDDEC2_Obj</class>
    <class kind="struct">IVIDDEC2_Params</class>
    <class kind="struct">IVIDDEC2_DynamicParams</class>
    <class kind="struct">IVIDDEC2_InArgs</class>
    <class kind="struct">IVIDDEC2_Status</class>
    <class kind="struct">IVIDDEC2_OutArgs</class>
    <class kind="struct">IVIDDEC2_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_MAX_IO_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaaf8c9523a27942aa46eba097398a0e49</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gac1f0ebc291c92f796a5144fa57f7390f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga7c8386cbcd58bcb8a16e15df6587f3f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gafa7a5979f7945ff9ce5822c8f5fa57d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_Obj</type>
      <name>IVIDDEC2_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaa23fa0665cc8848f3d30e7b654b850ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_Obj *</type>
      <name>IVIDDEC2_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gab044a3dd5967ff04c487062ed0586c2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_Params</type>
      <name>IVIDDEC2_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaad981f1fbf560cc8d7cf472423136830</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_DynamicParams</type>
      <name>IVIDDEC2_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga1cdd25796b18fba15e2198eee81f2900</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_InArgs</type>
      <name>IVIDDEC2_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gac94e861061dbc29600e7bc6443a9067a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_Status</type>
      <name>IVIDDEC2_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga9f508292db11280258aa94da832fc66d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_OutArgs</type>
      <name>IVIDDEC2_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga54a24dd5672ee41aab45540fd838ce77</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC2_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga8b9180923c067cbb47115d18189501c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_Fxns</type>
      <name>IVIDDEC2_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga95681f816462ba6be5dfc125782e8569</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDDEC2_FrameOrder</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga31f21bf0ec796b5506cd8a0f0cf7710f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC2_DISPLAY_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gga31f21bf0ec796b5506cd8a0f0cf7710fa4dc184c19c62190e5f933e46e5bccc2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC2_DECODE_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gga31f21bf0ec796b5506cd8a0f0cf7710fa33ea07222ede0a10cb27bad4b9db445d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC2_FRAMEORDER_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gga31f21bf0ec796b5506cd8a0f0cf7710fa3599bb4a0d320e3e36d2aa49a7ae79e3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDDEC3</name>
    <title>IVIDDEC3 - XDM Video Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</filename>
    <class kind="struct">IVIDDEC3_Obj</class>
    <class kind="struct">IVIDDEC3_Params</class>
    <class kind="struct">IVIDDEC3_DynamicParams</class>
    <class kind="struct">IVIDDEC3_InArgs</class>
    <class kind="struct">IVIDDEC3_Status</class>
    <class kind="struct">IVIDDEC3_OutArgs</class>
    <class kind="struct">IVIDDEC3_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC3_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga62d249f67b8956db313fdde1bbf9e7bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC3_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gaa96164ab594abaa53a5d093f1118d598</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC3_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga9a551797046d313c29221d0a33a31ab0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_Obj</type>
      <name>IVIDDEC3_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gaf53c38e661114ed5dcabd35959f33397</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_Obj *</type>
      <name>IVIDDEC3_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga22f05e003b8d3e6421a43a6613a099a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_Params</type>
      <name>IVIDDEC3_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga3135bd1065774979da46dbc1a9b50895</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_DynamicParams</type>
      <name>IVIDDEC3_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gac4bf6713614802244d3f8206c0586b8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_InArgs</type>
      <name>IVIDDEC3_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga81b8cd90c54f029dac00b34871157577</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_Status</type>
      <name>IVIDDEC3_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga5e1e45b174202f8f5b9ef3042bf980d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_OutArgs</type>
      <name>IVIDDEC3_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga3887cf6a6fd26cbfe837eaf132850cf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC3_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga383b7ba75a305ad392d6acddbaf05f24</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC3_Fxns</type>
      <name>IVIDDEC3_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gaa3804ddf72db7324738e9b30b53293e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDDEC3_displayDelay</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ga0719d3976b9704b17af4682c342e5b9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_AUTO</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9cad94dfba879f7d9affd9eeee52edf6491</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DECODE_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9caf99e7b194c6010ce16cc6467ee5ba3a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_1</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca651a402ab85ff0308874189db63cba62</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_2</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9cad3081be4fbc4f01801d4fba5eda5d97d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_3</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9cadb475d5e9998c276bd4ec65c52985cec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_4</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca0f315555ea55aff89fb367923662edba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_5</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca5c5ee506fa0008fbabccfd7d60b18edf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_6</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca100b919cc7f4dafdacabfbfb0e8fa7d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_7</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9cafe5e43674e632c2c4e851e6a9c1d4cdf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_8</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca3eee04ba68d82f6fc64df46448f53162</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_9</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9cac13725a8fc8ed26cfb15d7d85addc41f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_10</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca63910a5c260b16bee0e20d137061bafe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_11</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca83e775772411fd6151e53a2aefc0f8d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_12</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca5b44481490fa61a6278d6bf10b4061ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_13</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9caa80b3374dd5755352ff4325720a76594</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_14</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca1b7149e0ccc76db7bc55fa2cee6a7eca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_15</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca3a70527a1d082cd8e9a5526dd9f3950a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAY_DELAY_16</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca2c29517c49d9e8375d4e1a6e5bfa2d97</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAYDELAY_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gga0719d3976b9704b17af4682c342e5b9ca7017dd8fc0362645bce26ee765700017</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDDEC3_DisplayBufsMode</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>gaa0707d1c6133c25dc9a36f1c0f8b29f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAYBUFS_EMBEDDED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ggaa0707d1c6133c25dc9a36f1c0f8b29f5a603aedffe63a4a5efe368897e5fa0dc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC3_DISPLAYBUFS_PTRS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c3.html</anchorfile>
      <anchor>ggaa0707d1c6133c25dc9a36f1c0f8b29f5a57c0b7265e5564379afd5c842f992887</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDENC</name>
    <title>IVIDENC - XDM Video Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_e_n_c.html</filename>
    <class kind="struct">IVIDENC_Obj</class>
    <class kind="struct">IVIDENC_Params</class>
    <class kind="struct">IVIDENC_DynamicParams</class>
    <class kind="struct">IVIDENC_InArgs</class>
    <class kind="struct">IVIDENC_Status</class>
    <class kind="struct">IVIDENC_OutArgs</class>
    <class kind="struct">IVIDENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaeba527be430e1584897bc410ef06e08a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf31926403a1beba354092c33e6f8f41f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf0d8e925b556bc7d992afb7dc9005fe7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf08f3e2a75c1e39a184835d0683ca88e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Obj</type>
      <name>IVIDENC_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gad44e237f9d57d8025b5c71228bed12bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Obj *</type>
      <name>IVIDENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gafe560b65239e58d0a48897db58ee33f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Params</type>
      <name>IVIDENC_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>ga92af648d6d4edbae2b3a346fba9279c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_DynamicParams</type>
      <name>IVIDENC_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gafe1dff162a002aae2dea5e7aab7a4208</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_InArgs</type>
      <name>IVIDENC_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>ga05e0198b2f43284db0c107bcb1717b4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Status</type>
      <name>IVIDENC_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>ga2ae6b7f1d67de2793d34db08197a487b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_OutArgs</type>
      <name>IVIDENC_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf4063ab92747aadbef7bf42de9b0baac</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>ga13eaed2bcde87e35269eed69590e2313</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Fxns</type>
      <name>IVIDENC_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gac46a9b4cbc916b66badaf5bbbe08c1ac</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDENC1</name>
    <title>IVIDENC1 - XDM Video Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</filename>
    <class kind="struct">IVIDENC1_Obj</class>
    <class kind="struct">IVIDENC1_Params</class>
    <class kind="struct">IVIDENC1_DynamicParams</class>
    <class kind="struct">IVIDENC1_InArgs</class>
    <class kind="struct">IVIDENC1_Status</class>
    <class kind="struct">IVIDENC1_OutArgs</class>
    <class kind="struct">IVIDENC1_MbData</class>
    <class kind="struct">IVIDENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>gaf7b49aed126ab846bbcff9bb2d481533</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga8022d457cb04187a3b1a055eaa2d1629</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga1623748edce151d19caed068981773f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Obj</type>
      <name>IVIDENC1_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga7fd2f4ad244a9912b6a73b6151636600</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Obj *</type>
      <name>IVIDENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga953dc9cc5ece87d8b371bd2adbb5082f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Params</type>
      <name>IVIDENC1_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga95a9ebe6f467dd8194f4ca4826ab4f80</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_DynamicParams</type>
      <name>IVIDENC1_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga1a643f697bb5f0576383ebacc765d060</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_InArgs</type>
      <name>IVIDENC1_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>gaf935d97801c46b6fd6948867304f519f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Status</type>
      <name>IVIDENC1_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga48a16e03cc9f32885a41e7477bc8cf96</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_OutArgs</type>
      <name>IVIDENC1_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga74410ff6b9cf0620997b7a28fb72e21f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga2654e133ba490dec6e8dfa56d1b633ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_MbData</type>
      <name>IVIDENC1_MbData</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>gac1056d79229e955cf4a038590b596ef6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Fxns</type>
      <name>IVIDENC1_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga2866bd03283e54e2850c85a4c366d2a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDENC2</name>
    <title>IVIDENC2 - XDM Video Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</filename>
    <class kind="struct">IVIDENC2_Obj</class>
    <class kind="struct">IVIDENC2_Params</class>
    <class kind="struct">IVIDENC2_DynamicParams</class>
    <class kind="struct">IVIDENC2_InArgs</class>
    <class kind="struct">IVIDENC2_Status</class>
    <class kind="struct">IVIDENC2_OutArgs</class>
    <class kind="struct">IVIDENC2_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC2_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gaf2dc089029d9c193e6b6013197a49c49</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC2_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga4d7854622164735b48281a6b1a1ce352</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC2_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga0d3be28d9668178b05e0480c126c6f30</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC2_DEFAULTPROFILE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga73035620aa9c4cca081c2d3dc2129672</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC2_DEFAULTLEVEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga03051d2b393c1f4158178be021564f77</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_Obj</type>
      <name>IVIDENC2_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gabe1399751de5650dba249f7a8e0c9d6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_Obj *</type>
      <name>IVIDENC2_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga33a694f32ec23e1b2373f67ad7813028</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_Params</type>
      <name>IVIDENC2_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gaf55caadd47cd178c3c6af1e2c1102225</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_DynamicParams</type>
      <name>IVIDENC2_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga20550d2468a68111577de21dedbbabb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_InArgs</type>
      <name>IVIDENC2_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga904e0eda063ee36b18e959a1f58611d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_Status</type>
      <name>IVIDENC2_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gac3fdc1b08aa9966ec019d2efbed08f47</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_OutArgs</type>
      <name>IVIDENC2_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga3aca71ed966c879613ad7a84cfff8b97</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDENC2_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gac0226c5443ead6aaac0d9ea820e27e81</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC2_Fxns</type>
      <name>IVIDENC2_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga03b5516d3d63bf5c057b6f034d8b8cc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDENC2_MotionVectorAccuracy</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga8088be87ca6eafdf5f623d8a5d8b987f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_MOTIONVECTOR_PIXEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga8088be87ca6eafdf5f623d8a5d8b987fab71610998e62a743493b24cbb8f0f202</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_MOTIONVECTOR_HALFPEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga8088be87ca6eafdf5f623d8a5d8b987fae39104696d0ce05ee736ff5534a3892d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_MOTIONVECTOR_QUARTERPEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga8088be87ca6eafdf5f623d8a5d8b987fa4bb08dea6ac1da2f6f77ea554cca41f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_MOTIONVECTOR_EIGHTHPEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga8088be87ca6eafdf5f623d8a5d8b987fa72a845a2972198e6c23b2a8cbf7712c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_MOTIONVECTOR_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga8088be87ca6eafdf5f623d8a5d8b987faa2ce163fd3f51dafca03f6c342b955f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDENC2_Control</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>ga6daaba9e22ed6089a7335e556eceb680</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_CTRL_NONE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga6daaba9e22ed6089a7335e556eceb680a359f62b36ce860505881ce5f2c402bdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_CTRL_FORCESKIP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga6daaba9e22ed6089a7335e556eceb680aef62ea0725426fee25d1ec2d91e0e0c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDENC2_CTRL_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c2.html</anchorfile>
      <anchor>gga6daaba9e22ed6089a7335e556eceb680a40f91c92e28340005e5f16a1a50b0ba4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDTRANSCODE</name>
    <title>IVIDTRANSCODE - XDM Video Transcoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</filename>
    <class kind="struct">IVIDTRANSCODE_Obj</class>
    <class kind="struct">IVIDTRANSCODE_Params</class>
    <class kind="struct">IVIDTRANSCODE_DynamicParams</class>
    <class kind="struct">IVIDTRANSCODE_InArgs</class>
    <class kind="struct">IVIDTRANSCODE_Status</class>
    <class kind="struct">IVIDTRANSCODE_OutArgs</class>
    <class kind="struct">IVIDTRANSCODE_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga69d74b9dad25f19d864771f9d81a9a6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga29ec01f0e1dea7abff118a9cf8792885</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gaf6e122d808cecd873a7f51e34c2fb4b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_MAXOUTSTREAMS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga9b9cc80049e4cebea89e7c4cf58d426c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Obj</type>
      <name>IVIDTRANSCODE_Obj</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gacacbc6165ddd6b023b58abad8aa0a59b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Obj *</type>
      <name>IVIDTRANSCODE_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga049f5b53ee2c04135a1ff19afbc215c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Params</type>
      <name>IVIDTRANSCODE_Params</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga00d5710f24d7b9087dcd01d40921a21e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_DynamicParams</type>
      <name>IVIDTRANSCODE_DynamicParams</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga043a74d49bc336696a4be8366ad4db2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_InArgs</type>
      <name>IVIDTRANSCODE_InArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gaf74fb25ea8e27a3be28bcd27a71f7eb8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Status</type>
      <name>IVIDTRANSCODE_Status</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga694f55f6a32c7d080e6b9ee6026ef7c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_OutArgs</type>
      <name>IVIDTRANSCODE_OutArgs</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga4741c07a91091e7fdd3a894195a739aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDTRANSCODE_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gab5d20cf8d615294c7912796b79f85f5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Fxns</type>
      <name>IVIDTRANSCODE_Fxns</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga145180087812e38dff35b3b2866adf99</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_IALG</name>
    <title>IALG - XDAIS Algorithm Interface</title>
    <filename>group__ti__xdais___i_a_l_g.html</filename>
    <class kind="struct">IALG_MemRec</class>
    <class kind="struct">IALG_Obj</class>
    <class kind="struct">IALG_Params</class>
    <class kind="struct">IALG_Status</class>
    <class kind="struct">IALG_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IALG_DEFMEMRECS</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga8a220fa863380937542f6a38be47ceda</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_OBJMEMREC</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga0e3202a4d8dc0bd3cb300633922ffd54</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_SYSCMD</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga200f155f9e2720011270e99f17bb6675</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_EOK</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga2c15898121a23a164e4ea2bcc4f7e7dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_EFAIL</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga604e5600815cbd58846e0c5c05b6ba18</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_CUSTOMFAILBASE</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga1f655af6b5ce37aaf5328243d1993cf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_CUSTOMFAILEND</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gafbab7f3470d8b5a46615f1aca5c739b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_MPROG</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga86018453b8f991c8cb545b2e43c80c9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_MXTRN</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gafc53b940e2982a2e859bda0555180eb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_isProg</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga93e8704d8e88d2f3dde1a85317232b59</anchor>
      <arglist>(s)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_isOffChip</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gae2530ce6b07542f579871961a3fcfd4f</anchor>
      <arglist>(s)</arglist>
    </member>
    <member kind="typedef">
      <type>enum IALG_MemAttrs</type>
      <name>IALG_MemAttrs</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga20f514039bf67b319bff425fb8f36e5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IALG_MemSpace</type>
      <name>IALG_MemSpace</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga61ed32f432abc371aece4d839cdaee78</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_MemRec</type>
      <name>IALG_MemRec</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga99aa369e4d2b2e38444d7029ba09caed</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_Obj</type>
      <name>IALG_Obj</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga056d16e11872c72ef03832ebea91c946</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_Obj *</type>
      <name>IALG_Handle</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga16c037803ea218ba3dc5158f55ef27c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_Params</type>
      <name>IALG_Params</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gaa3e5c88152dd2b867de749e15c4bd01a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_Status</type>
      <name>IALG_Status</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga9cb14b478af2c5636bfb8ba78d06c3ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int</type>
      <name>IALG_Cmd</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga9032f20923ef2ba1d6b88c87a20075fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_Fxns</type>
      <name>IALG_Fxns</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gaf97260de3299a9304375dedca698572a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IALG_MemAttrs</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga805f1c1330403c05633277a073862e3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SCRATCH</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga805f1c1330403c05633277a073862e3da85e0509f7e82ebd01b57f899122de9b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_PERSIST</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga805f1c1330403c05633277a073862e3da68adbe0194074e0474333b76f7d1e090</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_WRITEONCE</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga805f1c1330403c05633277a073862e3da42356e6aa11869bfd15f31472f49a7c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IALG_MemSpace</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga262eb64dc7343999fa07d535ae163497</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_EPROG</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a6410b22d1d073ab55b289ca2f3c03b35</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_IPROG</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a946577db145f691f81d7085fc51e2201</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_ESDATA</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a85fff905ed5e83445e3424ce5ba03175</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_EXTERNAL</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497aa98151c21c55ddaf8c1918d8007e5493</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_DARAM0</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497af6a85bf972a4d090e2c0e4d31565f879</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_DARAM1</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497ad7b3b18fc0263be0f0702d263f600d9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497aa5c6d8cfdb63c11fafd22bb87204c5cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM0</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a4b31d959f6af27a012a87957c05d9c4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM1</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a4ac938c5e58e4d4a30458b63869f0095</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_DARAM2</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a17fc19eac565b29871efbfed54760414</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM2</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a6db79aaafcf9b4354f2828c2a94b8590</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_IDMA3</name>
    <title>IDMA3 - Interface for requesting EDMA3 resources</title>
    <filename>group__ti__xdais___i_d_m_a3.html</filename>
    <class kind="struct">IDMA3_MemRec</class>
    <class kind="struct">IDMA3_ChannelRec</class>
    <class kind="struct">IDMA3_Fxns</class>
    <class kind="struct">IDMA3_ProtocolObj</class>
    <class kind="struct">IDMA3_Obj</class>
    <member kind="define">
      <type>#define</type>
      <name>IDMA3_PROTOCOL_NULL</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ga85de540d61ac83857803528f25f44e4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IDMA3_MemType</type>
      <name>IDMA3_MemType</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gad7dca268a0fb944ec7da970a7064c93b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_MemRec</type>
      <name>IDMA3_MemRec</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gad9a9dde19d244a4552965b14abe2d96f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_Obj *</type>
      <name>IDMA3_Handle</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ga8960c528f0708a559bcaab34a865e1a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_ProtocolObj *</type>
      <name>IDMA3_ProtocolHandle</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gadd329735609d8384c3625554c0f2c58d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IDMA3_Priority</type>
      <name>IDMA3_Priority</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ga04af272ab4f16153137e3f39856078d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_ChannelRec</type>
      <name>IDMA3_ChannelRec</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gac8af8b3447a5ae88f4b14dc96e18eee1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_Fxns</type>
      <name>IDMA3_Fxns</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ga02d106a910bf5561419a755ab7f97e03</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_ProtocolObj</type>
      <name>IDMA3_ProtocolObj</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ga6705287956a84beb7d6f0eee6b6dfb55</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IDMA3_Obj</type>
      <name>IDMA3_Obj</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gae5a0e05b6797ba0b914a41c90ea47a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IDMA3_MemType</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gabe0577eecc288b36121382daa765093a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA3_INTERNAL</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ggabe0577eecc288b36121382daa765093aa120151b2c6d2d5bcb2d59466b0d13287</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA3_EXTERNAL</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ggabe0577eecc288b36121382daa765093aa9e757f072f4782774d8cd4b647563c54</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IDMA3_Priority</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>gafa41dccd2cc8f94915fffdda2c8b4a59</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA3_PRIORITY_URGENT</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ggafa41dccd2cc8f94915fffdda2c8b4a59a90abf287e878aedcfbc17d19266f207c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA3_PRIORITY_HIGH</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ggafa41dccd2cc8f94915fffdda2c8b4a59a2bd88e579d019a160876842f0c92f325</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA3_PRIORITY_MEDIUM</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ggafa41dccd2cc8f94915fffdda2c8b4a59a4f3bbe300c3ce513644f31991b6788ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDMA3_PRIORITY_LOW</name>
      <anchorfile>group__ti__xdais___i_d_m_a3.html</anchorfile>
      <anchor>ggafa41dccd2cc8f94915fffdda2c8b4a59a8560a79ce3c83622bed84ecb31b57aff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>DSPIRES</name>
    <title>IRES</title>
    <filename>group___d_s_p_i_r_e_s.html</filename>
    <class kind="struct">IRES_YieldContext</class>
    <class kind="struct">IRES_Fxns</class>
    <member kind="typedef">
      <type>enum IRES_YieldResourceType</type>
      <name>IRES_YieldResourceType</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga772c04e720ba2b67b4204bbccbe40945</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>IRES_ContextSaveFxn</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gaa00576c8c0c6d1e2c01cc32788c597c9</anchor>
      <arglist>)(IALG_Handle algHandle, Void *contextArgs)</arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>IRES_ContextRestoreFxn</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga618c74da111cc440a47fad6f7f575c89</anchor>
      <arglist>)(IALG_Handle algHandle, Void *contextArgs)</arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_YieldContext</type>
      <name>IRES_YieldContext</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gad70330927e4683909b1553bf0f2a5c75</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IRES_YieldContext *</type>
      <name>IRES_YieldContextHandle</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gafd901eec352839470db8e386baa1be66</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void *</type>
      <name>IRES_YieldArgs</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gafb1e285a8d30b447dc39fe05d5e4fdf0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>IRES_YieldFxn</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga21803b9b676c2579e59909062dc40079</anchor>
      <arglist>)(IRES_YieldResourceType resourceType, IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs)</arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_Fxns</type>
      <name>IRES_Fxns</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gad4918d3ae4c063a0bf6e76ac26c7c297</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IRES_YieldResourceType</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga9a68e109e02bf3f35e832ec4f767d0a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_ALL</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga9a68e109e02bf3f35e832ec4f767d0a3a0fd0c33808e89762c91dca8c2edc6aef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_SCRATCHMEMORY</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga9a68e109e02bf3f35e832ec4f767d0a3a99a353ef5a76fad49a805f0e3ba6e8e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_SCRATCHDMA</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga9a68e109e02bf3f35e832ec4f767d0a3aa8fe0182b728dbcd24900b9bf13221c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_RESOURCEHANDLE</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga9a68e109e02bf3f35e832ec4f767d0a3a737fd5b62997deb99125d2e0f4e47b74</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IRES_Status</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga8db6eab013fc4569e080cb4361dfd65b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_OK</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba30253e67bb1b070685e4177bdf9587b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_EALG</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba432505b3fc40c3ae60c7b36624dc100d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_EEXISTS</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba5d1871ad076ad79c214cfe753f0513e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_EFAIL</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba79fa1a926f2b780120951d084fcc3bd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_EINIT</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65bacf083017e2e50c9f975e4d956d0dc440</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_ENOINIT</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba9cb3cdefe2de31efea9a9442e2ed7dd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_ENOMEM</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba72b429ce0c052c9fe5b079798ee08caa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_ENORESOURCE</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba82f5c8e224ec5ef57cae62a4e80bf2d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_ENOTFOUND</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gga8db6eab013fc4569e080cb4361dfd65ba077a2999bf874acf2b556347a3c71e5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IRES_RequestMode</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga67d435865304c7bce199194e7ff07963</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_SCRATCH</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga67d435865304c7bce199194e7ff07963a4edb7db0f8cd8780a263c1e8ec686aa0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_PERSISTENT</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga67d435865304c7bce199194e7ff07963ab66403426900afab06c1459b4c8a1fc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IRES_LATEACQUIRE</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga67d435865304c7bce199194e7ff07963aa8d4ddab65248eedc7d1ca3fb43a5ea2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_Status</type>
      <name>IRES_Status</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga09c6ef97314f2d27ce39bfcfac5da287</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_ProtocolRevision</type>
      <name>IRES_ProtocolRevision</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gaf7c3863c0ea3895fb86badf58b809a43</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_RequestMode</type>
      <name>IRES_RequestMode</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gae6d619d30b481ac725448b769d2ae2d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_ProtocolArgs</type>
      <name>IRES_ProtocolArgs</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga4808ad3c47785cbfb8a22bf50b096e11</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_ResourceDescriptor</type>
      <name>IRES_ResourceDescriptor</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga0b4bec3cd4dbe4556d72d9ed894d5246</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_Properties</type>
      <name>IRES_Properties</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga2ef376adca27740ff8285b0d1b7e272b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_Obj</type>
      <name>IRES_Obj</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga5d11994529489c6809bc2effd5f83f01</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_Obj *</type>
      <name>IRES_Handle</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>gad0e33217f411f69c326180854b9f1cea</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_TRACE</name>
    <title>XDAIS Trace Support (Experimental)</title>
    <filename>group__ti__xdais___t_r_a_c_e.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_ENTER</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>gae481bd98d6475b901f3bda374d7dd804</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_1CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>gab3b47227b7128f9dd7248cdbac20b28c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_2CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga97343ce207eec0b43621a7ce712f6a51</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_3CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga0a042541fabc495650334061087052a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_4CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga2bc4512b405185af7baa8ef4e160e6f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_5CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>gaeb138d21539b83c10d2c11c76c122552</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_6CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga95e0f1e59bc5d22e913fbd5a4cde68fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACE_7CLASS</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga1ceefde1affa0c508b0a6d523ae8860a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>XDAS_Int32(*</type>
      <name>XDAIS_TRACE_AssertFxn</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga404d7007d125c9e0fcb716f6d2a2e367</anchor>
      <arglist>)(IALG_Handle alg, XDAS_Int32 classId, String format, String arg1, XDAS_Int32 arg2)</arglist>
    </member>
    <member kind="typedef">
      <type>XDAS_Int32(*</type>
      <name>XDAIS_TRACE_PrintFxn</name>
      <anchorfile>group__ti__xdais___t_r_a_c_e.html</anchorfile>
      <anchor>ga8395e2827ac16a7e8cfc36b23813beca</anchor>
      <arglist>)(IALG_Handle alg, XDAS_Int32 classId, String format,...)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDEO</name>
    <title>IVIDEO - XDM Video Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_e_o.html</filename>
    <class kind="struct">IVIDEO_BufDesc</class>
    <class kind="struct">IVIDEO1_BufDescIn</class>
    <class kind="struct">IVIDEO1_BufDesc</class>
    <class kind="struct">IVIDEO2_BufDesc</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDEO2_MAX_IO_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga5c9c455b5a7783d4aaab50592f1c1996</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDEO_MAX_YUV_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga6f88ee11da1a2397e9ac263ce3cdd537</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDEO_MAX_NUM_PLANES</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gad5d38681f3fa9038f5c0c32208c5bdd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDEO_MAX_NUM_METADATA_PLANES</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga18bf9000c7c50a1bb4c3ebd7ff844c7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDEO_BufDesc</type>
      <name>IVIDEO_BufDesc</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga607cd0917b009907d55f34f949ae2a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDEO1_BufDescIn</type>
      <name>IVIDEO1_BufDescIn</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga6d67d40d38f51e957feb48a0c17c6596</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDEO1_BufDesc</type>
      <name>IVIDEO1_BufDesc</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga4eba22c6a353adf80871820aea0ae9e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDEO2_BufDesc</type>
      <name>IVIDEO2_BufDesc</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga2038d77f5028a340e635bdbd3373818e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_FrameSkip</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga6533d232a1c479dd185945e9c10c2665</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NO_SKIP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a8089c337b034434f8d53d279022272f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_P</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a767894b6dfb8639c2298f2d31e5fee51</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_B</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a04cadb8d98980be81a2a8a3fdc0372fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_I</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a551353a345ce3929adcff79aa741724b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a1b9f609f763ae7d8b36262986bcf54a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IB</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665ad111bef6602a59d8998ba5b4adbce87b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_PB</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a2e82d4e64d50c7fae14a1ef6720d3588</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IPB</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665ad9ffc660a588536746fbdb3d8b5b4f33</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IDR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a98a74bb46bd05f43c4db0ae8f8f66eb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_NONREFERENCE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a27d1acbd4d4a7e9bc2fa59cf38f773cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a0f0844d71eeb68ce22bc9d9f840d93f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_FrameType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga7ad672ade5d380f42e0cfcfb2b38b6df</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NA_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfab4b11cfbf563ce054e55fa482fb67f79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_I_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfac2b378280d95551841dddec15fad1d43</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_P_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfad788ad7b0f7a8517de35c5cd0aefc28d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_B_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa7dd078d4f4f309da2e73494ddd01f2b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_IDR_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfad7a86650a7f248f11133e52da2cb3e36</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_II_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa3be138a2faa58c0d85e2ae533526af79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_IP_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa40d74846bed523f78efbd61e42736dea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_IB_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa9cc0602312932db087a8e89b807c59a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PI_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa394be4bc1774efef87892bcb6387d4d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PP_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa9ae131687a2c620b50be3cb9bdf9ef69</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PB_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa3eb025061d65605fa2613a1219203662</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BI_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa99b48bce066d122f86f67d281709c970</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BP_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfaf6d75d28ac6582ed372ca9dcffd7a31e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BB_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfaa8dad288ba397bafe98f9d3dcda06efd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_I_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfac0c3748111b37e34c2652e311b367f18</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_P_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa068cd4d6a1d797d1b3eba96255c64b5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_B_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfac34147d75fecab15f7692ff0be138df6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_IDR_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfaf9c5b520fe2612d88725de4bc1224d28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAMETYPE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa05a31e040d22bea216e10f2ce8cd6472</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_ContentType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gac397e10110dd59e8266cf5831c68f44f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_CONTENTTYPE_NA</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa61cc12c39b88ba4c10d51a9d9393405a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PROGRESSIVE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa6b7ae345e50ccd4c5589efd85e18194e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PROGRESSIVE_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa36a57cca2ad3435c423515e78dd7d1ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa53e2513e3f2b155abb3bb707ff2fbd04</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa399d126875549ace3806efddcfc45ce8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED_TOPFIELD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa74d16186e87100648b97eae32e72d90c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED_BOTTOMFIELD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa980c869708ff1245fd7f1859515da631</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_CONTENTTYPE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa35c626f7476288db897680bc43d92243</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_RateControlPreset</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga33dcd88e11f7c1a614c37729e6b99592</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_LOW_DELAY</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592aee9478fdaa09a124e84a5f52373213f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_STORAGE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592ad38ab0817089a19a753e2ca6b6e5d165</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TWOPASS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592abf4ba1f0aff97d13bf49af0d574ad040</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NONE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592ae222e2b721a93726945d9b563631fda0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_USER_DEFINED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592a8e5fffe1c7bb0d34fd55b8820cfdb7e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_RATECONTROLPRESET_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592abafd796f46fc51340a58dadf2f725e25</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_SkipMode</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga911b2a9c63a7a8c16b86ae2b43acb609</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_ENCODED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga911b2a9c63a7a8c16b86ae2b43acb609a899d064f2315fc727725330cec39a441</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_SKIPPED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga911b2a9c63a7a8c16b86ae2b43acb609a728d909773039ecb6c8481ce587ff948</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIPMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga911b2a9c63a7a8c16b86ae2b43acb609ac81722aae2d59cad8cb864dc68c81d23</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_OutputFrameStatus</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga7d713a3e9b5adacb039de4419d5527d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_NOERROR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4acb9c873639468d10824089bf2c196884</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_NOTAVAILABLE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4a3884312affd02cbb477b0bcf9ffa4a8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_ERROR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4ae22471e0df0ebdbc17ad840deec9ba24</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_OUTPUTSKIP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4a60ba8d0b4e654ac84e7f079e98e1db60</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_OUTPUTFRAMESTATUS_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4a4bcc02f48972d600ec61e933133b4587</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_PictureType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga90dd6a0a4863fcc6d3d523eda8a78ed2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NA_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2aed1dec6b10bca143d42b83d26218d26e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_I_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2a85a519797900b0bbbc5007c14e6bab37</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_P_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2a70166338c9fab34bb0fc6534a0890ea3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_B_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2aa8b180d5b01bb100e326d261684ba7f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PICTURE_TYPE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2a5373e837eb3564b15e0a0203ecdb503f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_Format</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga4aeb19b8e5cc42c49fc8820fc4e1b4aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG1</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa6b8d27c8e2c977e98780b30be68b4553</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG2SP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa1d3f020030f6624621f546640cd97195</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG2MP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa77ef7b91a48b372bb8fd6104ba4c53d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG2HP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa8cd7c6245521d4003ae12244eb8616e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG4SP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa58cce125a57189f5ad23250b0ea41dce</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG4ASP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa35e77ca8ec953280e5615eb9e799211b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264BP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaab62f85b5ad0f3716733800202de13725</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264MP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa65745c33e161b9e725dd1093d6afb535</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264HP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa204e56351a5162ac38b3abfe5456ab87</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_VC1SP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaabb227ae9ca9aea83e804a2afc9137e67</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_VC1MP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa673d0eb07f8c957878812eebe0074b8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_VC1AP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaadf58ee1effdc2c92756355575b471123</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264RCDO</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa940abd5ed2efa9a00f0e7a5e2a2251ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_RV8</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa212c3c3801cec7c79961c6fab9bb242a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_RV9</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa84b7151a1af4d3443ed2c577cad0686b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_RV10</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa8c978af8c5b684ebc5203db2d30991c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ON2VP6</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa7082472b4fdec97b92dac08143376138</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ON2VP7</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa1bd7003b68493f109700a299bf8dd9dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_AVS10</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa95db05d1c11baabdf45ee00686d87284</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SORENSONSPARK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa6b5c380386c305f53ae7493e5efa6962</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H263_PROFILE0</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaacb80b99b98079682a1d2bd613148503d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H263_PROFILE3</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa5c4909bd040996c8e7bea8ad18918c03</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264SVC</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaaa83519d4e4595e91ded18b9bc324a0ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MULTIVIEW</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa357c291c2ea19421b029517cff2f3f96</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MJPEG</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaaf7871050ba19ab4d4b042f7743bbf57f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_VideoLayout</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gad5a767cec56f1942d52c9ec3faa18834</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FIELD_INTERLEAVED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggad5a767cec56f1942d52c9ec3faa18834a35e0e62b9bdf7d0de033e3fb7cdd8caf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FIELD_SEPARATED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggad5a767cec56f1942d52c9ec3faa18834a7f0222be966d686037579effa3a21600</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TOP_ONLY</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggad5a767cec56f1942d52c9ec3faa18834a4146a860698b530dafb906dffdb347f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BOTTOM_ONLY</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggad5a767cec56f1942d52c9ec3faa18834a70e0715988493d9baea5dcdb39de7970</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_OperatingMode</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga04553d2ffa25358d955796800ae89c6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_DECODE_ONLY</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga04553d2ffa25358d955796800ae89c6ba21af514948b5593b99b1a7e87912a227</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ENCODE_ONLY</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga04553d2ffa25358d955796800ae89c6bad74400f6d18fec5031c1bb60a0b530a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TRANSCODE_FRAMELEVEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga04553d2ffa25358d955796800ae89c6ba760407b19d59c4e23d1b22b37799a0c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TRANSCODE_MBLEVEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga04553d2ffa25358d955796800ae89c6bac55c6f2f2fe3ddfa90bb1a325fbdcbbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TRANSRATE_FRAMELEVEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga04553d2ffa25358d955796800ae89c6baebbaa951b61fa8d03f1ccb6a8ca3b2a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TRANSRATE_MBLEVEL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga04553d2ffa25358d955796800ae89c6ba0e168b9703b6143f2ee75c64179ae787</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_BitRange</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga783aa3e11653b7deb8fa6405d69a74bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_YUVRANGE_FULL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga783aa3e11653b7deb8fa6405d69a74bdaf3f8342f77d13b361853d3e5686329ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_YUVRANGE_ITU</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga783aa3e11653b7deb8fa6405d69a74bdafde08af7be610fe74b624d27c049dfeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_DataMode</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gaa869a20e1197180fdbc9a176b3ddb167</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FIXEDLENGTH</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggaa869a20e1197180fdbc9a176b3ddb167aad14f85c07b9afdf25538140c857b14b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SLICEMODE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggaa869a20e1197180fdbc9a176b3ddb167a48af869b96da08862e748db350e54d8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NUMROWS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggaa869a20e1197180fdbc9a176b3ddb167abc9d77cf9eecf58a401a028777570141</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ENTIREFRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggaa869a20e1197180fdbc9a176b3ddb167a9e0003c122588c7d84a74dfab0699699</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_ErrorInfoMode</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga010d63a13fa5c291d61403d1811c5775</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ERRORINFO_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga010d63a13fa5c291d61403d1811c5775a32b1d0efdebc3bb356a546b938090030</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ERRORINFO_ON_INPUT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga010d63a13fa5c291d61403d1811c5775a492f7ebc0bf13a68f4ee3c205d293db8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ERRORINFO_ON_OUTPUT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga010d63a13fa5c291d61403d1811c5775a3ef6e3039cc4aea47c81e6334ae9b3cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ERRORINFO_ON_BOTH</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga010d63a13fa5c291d61403d1811c5775ae8c7b2716a8a83c88ff92711300e6ff1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_ERRORINFO_MODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga010d63a13fa5c291d61403d1811c5775a784a7b032e261400725d6423f1d51e78</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_MetadataType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga3e0d6c6bd8fa37db0b88aeae961962fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_METADATAPLANE_NONE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga3e0d6c6bd8fa37db0b88aeae961962fea78081d631dc40260b4eb2049a94b30c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_METADATAPLANE_MBINFO</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga3e0d6c6bd8fa37db0b88aeae961962fea6a080d2da5643120b53fb56b3e846f06</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_METADATAPLANE_EINFO</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga3e0d6c6bd8fa37db0b88aeae961962fea0ff3386a8c9cc68036c1925440f1787c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_METADATAPLANE_ALPHA</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga3e0d6c6bd8fa37db0b88aeae961962fea7b5b28108acbefabf93be70eda8b9131</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_split_IVIDDEC2</name>
    <title>XDM IVIDDEC2-based Video Decoder Split Interface</title>
    <filename>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</filename>
    <class kind="struct">IVIDDEC2FRONT_Obj</class>
    <class kind="struct">IVIDDEC2BACK_Obj</class>
    <class kind="struct">IVIDDEC2FRONT_Status</class>
    <class kind="struct">IVIDDEC2FRONT_OutArgs</class>
    <class kind="struct">IVIDDEC2FRONT_Fxns</class>
    <class kind="struct">IVIDDEC2BACK_Fxns</class>
    <member kind="typedef">
      <type>struct IVIDDEC2FRONT_Obj</type>
      <name>IVIDDEC2FRONT_Obj</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga4786fd8ccf9177f92eef375a77db3b85</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2FRONT_Obj *</type>
      <name>IVIDDEC2FRONT_Handle</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaaa273ba82e5f6d894000c4031d905776</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2BACK_Obj</type>
      <name>IVIDDEC2BACK_Obj</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga240b2f2128f41b53c5fdacf96449ada7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2BACK_Obj *</type>
      <name>IVIDDEC2BACK_Handle</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga8aedc496483d9ad90fb544045934648d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2FRONT_Status</type>
      <name>IVIDDEC2FRONT_Status</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaed14e1cec0b623b4555118c2a15bd3fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2FRONT_OutArgs</type>
      <name>IVIDDEC2FRONT_OutArgs</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga23347d6ee3bf77df5feeca7d4356a227</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2FRONT_Fxns</type>
      <name>IVIDDEC2FRONT_Fxns</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga9f561432b2d206ccf19f62b871019840</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2BACK_Fxns</type>
      <name>IVIDDEC2BACK_Fxns</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaec42b2f747b1a47d02fe3d06a8a24256</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_XDM</name>
    <title>XDM - Shared XDM Definitions</title>
    <filename>group__ti__xdais__dm___x_d_m.html</filename>
    <class kind="struct">XDM_BufDesc</class>
    <class kind="struct">XDM_SingleBufDesc</class>
    <class kind="struct">XDM1_SingleBufDesc</class>
    <class kind="union">XDM2_BufSize</class>
    <class kind="struct">XDM2_SingleBufDesc</class>
    <class kind="struct">XDM1_BufDesc</class>
    <class kind="struct">XDM2_BufDesc</class>
    <class kind="struct">XDM1_AlgBufInfo</class>
    <class kind="struct">XDM_AlgBufInfo</class>
    <class kind="struct">XDM2_MoveBufDesc</class>
    <class kind="struct">XDM_Date</class>
    <class kind="struct">XDM_Point</class>
    <class kind="struct">XDM_Rect</class>
    <class kind="struct">XDM_ContextInfo</class>
    <class kind="struct">XDM_Context</class>
    <class kind="struct">XDM_DataSyncDesc</class>
    <member kind="define">
      <type>#define</type>
      <name>XDM_EOK</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga1cf6109227485a043be42d0761ed55b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac896f031d1997aae6f959aff6c6d8b54</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac502a6ae2494d2c4151e2a3be22c96e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaa1a1d3d9c0c8807cbe465633d76580e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_MAX_IO_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacb0db1cbd37d45e39368c0dff87d7cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga3446a438727f673f58cacd76947536d1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaa0360329abe8080abb150c24255fa3a7</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CLEARACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaedd624063fce29cfed9193ad4d46765c</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CLEARACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacaf2e719f6570fb074df83697f9665d1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac4c3d846ed83c34a06fd6e8fcb49b4b2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaef2577b3a010843a01d85a6e2bbf5487</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CUSTOMENUMBASE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf6eae9fc7c3a5e8aa08d3d23d870b583</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CUSTOMCMDBASE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga43093f03f01c2e4eed7f131795af84fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISFATALERROR</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf46ec0675f5fae35aaf29392aebbe3d3</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISUNSUPPORTEDPARAM</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gae1b52e8b2c8c062dd460f8a9bc737b77</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISUNSUPPORTEDINPUT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacc71215dc73ce6f3184f78be7c49ac09</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISCORRUPTEDHEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga4979bf4ca24fca5d9386896f9c319084</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISCORRUPTEDDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga180c829e45389f064af38a3e58278baa</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISINSUFFICIENTDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7714cc631b009ef2c574218006af0ebb</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISAPPLIEDCONCEALMENT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga24d74d9ea55947f6bf2bc90a532bc32c</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETFATALERROR</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gab0d647a23e89f0a11fb47493746bc254</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETUNSUPPORTEDPARAM</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad4b20720fe6a8d9eb46259206635c6ab</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETUNSUPPORTEDINPUT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf6a007a552f8849694b6c785531c9413</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETCORRUPTEDHEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad5b5a780c1df72c1a99f28c1e32531be</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETCORRUPTEDDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7cab971a59a1057febe113621ac68c1b</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETINSUFFICIENTDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga89f38db60d38746c435f8d9f2398bef2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETAPPLIEDCONCEALMENT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga22e33071e27e1f3d1624229986c79331</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_MAX_CONTEXT_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaed28c56a4d5a516897357c2fc647ac9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_BufDesc</type>
      <name>XDM_BufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga586b0ef904f6e6a226c8672e8f244027</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_SingleBufDesc</type>
      <name>XDM_SingleBufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad91f21f92a5fe3b6eeb1b66f2e18105b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM1_SingleBufDesc</type>
      <name>XDM1_SingleBufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf186abda0633960550b1eb54a65bf180</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM2_SingleBufDesc</type>
      <name>XDM2_SingleBufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga945ceb579f6b5decc09e9f5b22a8330e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM1_BufDesc</type>
      <name>XDM1_BufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac4c9636e78344de81de3d8845d8424d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM2_BufDesc</type>
      <name>XDM2_BufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga13ecf6839f07990bcd026943f66efaba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM1_AlgBufInfo</type>
      <name>XDM1_AlgBufInfo</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga682fe33611973b8ae6fa0052979ea9f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_AlgBufInfo</type>
      <name>XDM_AlgBufInfo</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga1e1612df49f286c564d5537627c8a937</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM2_MoveBufDesc</type>
      <name>XDM2_MoveBufDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga9258b3a7baf02c84966b1b2018a4f79d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_Date</type>
      <name>XDM_Date</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf2d218d0a8f734916e12334c58c30c69</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_Point</type>
      <name>XDM_Point</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaac6b6d6d00c43cf5a58adb7a76045ebe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_Rect</type>
      <name>XDM_Rect</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga35979dd87228ffe41c9fcf83ee89cb0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_ContextInfo</type>
      <name>XDM_ContextInfo</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga6164a472952c526890eefe189d4e54a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_Context</type>
      <name>XDM_Context</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga652e360c99f2774d491684602cd1d076</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct XDM_DataSyncDesc</type>
      <name>XDM_DataSyncDesc</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gabb26d49d7d9f070c778015d60c8ed1b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void *</type>
      <name>XDM_DataSyncHandle</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacf3c98f1d74864b1bd7dcfe295057540</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>XDM_DataSyncPutFxn</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga3b019dc50e38d3dcaefb6cfaeb05e71d</anchor>
      <arglist>)(XDM_DataSyncHandle dataSyncHandle, XDM_DataSyncDesc *dataSyncDesc)</arglist>
    </member>
    <member kind="typedef">
      <type>XDAS_Int32(*</type>
      <name>XDM_DataSyncGetFxn</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga045fd6e6754962733a798bf10446f8fd</anchor>
      <arglist>)(XDM_DataSyncHandle dataSyncHandle, XDM_DataSyncDesc *dataSyncDesc)</arglist>
    </member>
    <member kind="typedef">
      <type>XDAS_Int32(*</type>
      <name>XDM_DataSyncGetBufferFxn</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga500b152e73d1439982a6616f104ee1cf</anchor>
      <arglist>)(XDM_DataSyncHandle dataSyncHandle, XDM_DataSyncDesc *dataSyncDesc)</arglist>
    </member>
    <member kind="typedef">
      <type>XDAS_Int32(*</type>
      <name>XDM_DataSyncPutBufferFxn</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaaba438ffe2c12c416d878e4e708316f5</anchor>
      <arglist>)(XDM_DataSyncHandle dataSyncHandle, XDM_DataSyncDesc *dataSyncDesc)</arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_AccessMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad852bdfa0303e77939811768b8e905ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggad852bdfa0303e77939811768b8e905abadc6547990f2ba9c7a4bacdf3ad4f405a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggad852bdfa0303e77939811768b8e905ababd16ad36f147cf0e691a13590314a06c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_CmdId</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga4d2482d53629e138b96af2e3fe702477</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETSTATUS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a901d6409e5496dbc7720d0e952fb1b15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_SETPARAMS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477ab358f49d17f79c00b1ba5c2c645eb025</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RESET</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a2bf3cef324828ab92cd6cedead4c725e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_SETDEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a1b6cda1632a452aa55dbba763b53d746</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_FLUSH</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477acd0e4d7005b1df978b26f97bccf6df8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETBUFINFO</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477aac803fc3c3144acc395e3b9b79025653</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETVERSION</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a6531ed0c0766017f6caa01207d3ad4c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETCONTEXTINFO</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a7aa270e718dce742ef06b8d67be98055</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETDYNPARAMSDEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a7ebcd6a97cefdb944ce204bc6415bb15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_SETLATEACQUIREARG</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a1f3270dd03e6a6854d755b7fe107b61b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MOVEBUFS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a742a9d2abb13912edc149461252bb4cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_ErrorBit</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga993de0b923e61c59a996fc2be4783131</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_PARAMSCHANGE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a13eb40f973b1bc18df8263030d4a1be9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_APPLIEDCONCEALMENT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a143f0496fb2db7191d7ddbe9d9fb58f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_INSUFFICIENTDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131aeb5f7b677fb1d35ce8c9e4af0e1c5c2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CORRUPTEDDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a3df4766dd604b28652b8830f051a7e1a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CORRUPTEDHEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131afab843e2d029e916fc36e7550489dba9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_UNSUPPORTEDINPUT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a7c4145225db773b55c02bcc61be59756</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_UNSUPPORTEDPARAM</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a3440c95956b613e002620a71c77a5980</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_FATALERROR</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a8ebb569b30333486afaf576c366118e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_DataFormat</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga5b4416e5582cae4428a1f4695d6e5ac5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BYTE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5aa24eeba74896e53a4bb8874560e4f67d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_LE_16</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a286615517f0d85bbad01a61ca1b8355b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_LE_32</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a87cbb4b143f78faf0f5c67d45cd5a39a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_LE_64</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a111d1dcf71c52bd2c9886373a5d98e1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BE_16</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a3dac2b3e9961a294c89ffac5ceedb509</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BE_32</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a43e43097fd1b63ac44247df52fe88da4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BE_64</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a82ae547ec4f91e70c0dec56dd35c624d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_EncodingPreset</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7b522f4337b661bbf9fb649eb95b4e1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1ca72b9373f4561db5fc6b0a2904b4a40e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_HIGH_QUALITY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1cabef4cff45b90786a8583b027530bb927</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_HIGH_SPEED</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1caf553ad9672b1ee9a7b91d746980dc58a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_USER_DEFINED</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1caba3ac3c750ac0125c9f1aac6f8586b5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_HIGH_SPEED_MED_QUALITY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1cad17148dfa73f3485494c179347c87ea6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MED_SPEED_MED_QUALITY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1ca955aa675c06d09f1eb50965e864c5467</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MED_SPEED_HIGH_QUALITY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1cafcd8873674236968ef61010f625fb821</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ENCODING_PRESET_MAX</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1ca09059f7596f0c9721319ae545d24229e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_PRESET_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1caf0a33f87fd66b122a1b0d1bbd92aa177</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_DecMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga0e19341fdb7c698eb849896edaa33aff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_DECODE_AU</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga0e19341fdb7c698eb849896edaa33affa8c540496685639e09e8c1ef895565595</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_PARSE_HEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga0e19341fdb7c698eb849896edaa33affa20a585ea8dd3b153c5203499b54d862c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_EncMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7e9132a2379c6ac0ee9c9e925b932461</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ENCODE_AU</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7e9132a2379c6ac0ee9c9e925b932461a5822b75801cd51f3a5f3478d59c8bee4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GENERATE_HEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7e9132a2379c6ac0ee9c9e925b932461a98969caa951cc0b210bacdd2a1932abc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_ChromaFormat</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gab99980ebd17efe73aa5708b5f43107f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CHROMA_NA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4aef81026a1d1783d9628c19f5c8a78dac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_420P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a891298e42c828a4c56b2d20d8be7cca8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_422P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a9457339c11ffa04dca5f900e82a2346d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_422IBE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a638d86b7f38f9404348b38fa459bdee9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_422ILE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a9560c4d0b7a2ddb6aba01ca66e41e5ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_444P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a31ade59366a5116a6d74a4fe012021f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_411P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a6c2c3aac53d2a8da477f487d788bcb29</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GRAY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a45edf9e2ce7ab4045dfcdde062b4e423</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RGB</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a0491c6350cc8c9127610c2a6c31f3ee4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_420SP</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4acd45176e14ea9e5b53fc52ec88bddd9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ARGB8888</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a5979b38c73531a7bf71c12412232be5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RGB555</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4aa1ae21243fd451d6a8f75bd274a77934</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RGB565</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a6b8863fc2937c932888f3df04ff1bcc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_444ILE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4aaf1809f33e309f991f8c47b6af55399a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CHROMAFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4af01b00784f3926f7accfd6f0a8360a7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_MemoryType</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga69f8d5b708926a7e3ccb87264c741111</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMTYPE_ROW</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga69f8d5b708926a7e3ccb87264c741111a0cb3b4184849d9d46b93906d5fc3a2e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMTYPE_RAW</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga69f8d5b708926a7e3ccb87264c741111a9c268781b88e0db8ee97ed6e8a9bec18</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMTYPE_TILED8</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga69f8d5b708926a7e3ccb87264c741111aaa92c0c8b4d48c91bf26b80c6e070195</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMTYPE_TILED16</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga69f8d5b708926a7e3ccb87264c741111a98b6ee029a1e01d90ca54797958d8ad1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMTYPE_TILED32</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga69f8d5b708926a7e3ccb87264c741111acc7d0ff7ecb8e10beb1e22de281dc678</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMTYPE_TILEDPAGE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga69f8d5b708926a7e3ccb87264c741111ace88c29b4f7b98e2f2ff3c01b6758869</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_MemoryUsageMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga70f4f3f82fa67c5e06eb506bf4729a4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_MEMUSAGE_DATASYNC</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga70f4f3f82fa67c5e06eb506bf4729a4aa3d06c95b07759d1c642dc7675e3d8796</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_XDAS</name>
    <title>XDAIS Types and Constants</title>
    <filename>group__ti__xdais___x_d_a_s.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>XDAS_TRUE</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga0a1e9fe6b661ca6eafe982fe2b0787bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDAS_FALSE</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga5cd894ca3ba5c100f7f863dae8587293</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void</type>
      <name>XDAS_Void</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga125aad4180e7ca9a3ddaba59c9217513</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint8</type>
      <name>XDAS_Bool</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gac8ce48f3d618a6f0a37b4e55f978b825</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int8</type>
      <name>XDAS_Int8</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gaa0b0c4cc1bf0d8fa0d9b15de0e9204cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint8</type>
      <name>XDAS_UInt8</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gac9308edb855a360c27a47aaa6f3b39a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int16</type>
      <name>XDAS_Int16</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga8189aa7a8636f505d6a35e5744ac6392</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint16</type>
      <name>XDAS_UInt16</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gaa27605972947c862397ebee40c2ff917</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int32</type>
      <name>XDAS_Int32</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gae431579ed9eff9134de78ca00ddd5f3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint32</type>
      <name>XDAS_UInt32</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga615572fcd2279a6780dc1785d72ff421</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IALG_Fxns</name>
    <filename>struct_i_a_l_g___fxns.html</filename>
    <member kind="variable">
      <type>Void *</type>
      <name>implementationId</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a83963e2ca17632c15bdb01494481a615</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>algActivate</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>af1213efc8ac6fdfb72b50da9950baaa7</anchor>
      <arglist>)(IALG_Handle handle)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algAlloc</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a1640ba8f4033af1ce3887283c7a12746</anchor>
      <arglist>)(const IALG_Params *params, struct IALG_Fxns **parentFxns, IALG_MemRec *memTab)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algControl</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a4c506a1599a604b02b30097e61ff4b89</anchor>
      <arglist>)(IALG_Handle handle, IALG_Cmd cmd, IALG_Status *status)</arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>algDeactivate</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a10f29860ab8b3beab69b0f0128c3d969</anchor>
      <arglist>)(IALG_Handle handle)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algFree</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>ac6f87b240d96486e3e88e80b95046ade</anchor>
      <arglist>)(IALG_Handle handle, IALG_MemRec *memTab)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algInit</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a94eca7c58cceb112eccd970a6cf3f569</anchor>
      <arglist>)(IALG_Handle handle, const IALG_MemRec *memTab, IALG_Handle parent, const IALG_Params *params)</arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>algMoved</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a5456c5087825b808e18000c551a66ef1</anchor>
      <arglist>)(IALG_Handle handle, const IALG_MemRec *memTab, IALG_Handle parent, const IALG_Params *params)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algNumAlloc</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a098c1ca275465bb4acc1d3d0cf060160</anchor>
      <arglist>)(Void)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IALG_MemRec</name>
    <filename>struct_i_a_l_g___mem_rec.html</filename>
    <member kind="variable">
      <type>Uns</type>
      <name>size</name>
      <anchorfile>struct_i_a_l_g___mem_rec.html</anchorfile>
      <anchor>a6d4138068c5a30b4399464f5a8e3aca2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>alignment</name>
      <anchorfile>struct_i_a_l_g___mem_rec.html</anchorfile>
      <anchor>a86daec3754a4b918fff07efe28461748</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IALG_MemSpace</type>
      <name>space</name>
      <anchorfile>struct_i_a_l_g___mem_rec.html</anchorfile>
      <anchor>a41e307f25d01a4329f4f4bd794c9087c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IALG_MemAttrs</type>
      <name>attrs</name>
      <anchorfile>struct_i_a_l_g___mem_rec.html</anchorfile>
      <anchor>aa9dca3a637dc7e26069f4a11e7c82593</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void *</type>
      <name>base</name>
      <anchorfile>struct_i_a_l_g___mem_rec.html</anchorfile>
      <anchor>a2a51de211c96021ca4aa360e352aa90f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IALG_Obj</name>
    <filename>struct_i_a_l_g___obj.html</filename>
    <member kind="variable">
      <type>struct IALG_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_a_l_g___obj.html</anchorfile>
      <anchor>aa80d0fb968dce61561689d3793bd5b6c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IALG_Params</name>
    <filename>struct_i_a_l_g___params.html</filename>
    <member kind="variable">
      <type>Int</type>
      <name>size</name>
      <anchorfile>struct_i_a_l_g___params.html</anchorfile>
      <anchor>af8fa239e38c54b8202e30292e99089c4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IALG_Status</name>
    <filename>struct_i_a_l_g___status.html</filename>
    <member kind="variable">
      <type>Int</type>
      <name>size</name>
      <anchorfile>struct_i_a_l_g___status.html</anchorfile>
      <anchor>a852361d0183829e930a949268d9b0b02</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_DynamicParams</name>
    <filename>struct_i_a_u_d_d_e_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a62cb7a2795bc2071990488110d388a83</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>downSampleSbrFlag</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a7eba84061f598eed30d8167425533187</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_Fxns</name>
    <filename>struct_i_a_u_d_d_e_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___fxns.html</anchorfile>
      <anchor>ae84c356dd54c0dc761fb09d62d1da414</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___fxns.html</anchorfile>
      <anchor>a45764e3d0bdcbdda81515faecc1253fc</anchor>
      <arglist>)(IAUDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IAUDDEC1_InArgs *inArgs, IAUDDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___fxns.html</anchorfile>
      <anchor>a0669353a289747a5e1e4eec31ed55a21</anchor>
      <arglist>)(IAUDDEC1_Handle handle, IAUDDEC1_Cmd id, IAUDDEC1_DynamicParams *params, IAUDDEC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_InArgs</name>
    <filename>struct_i_a_u_d_d_e_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___in_args.html</anchorfile>
      <anchor>a365f92b03f0d9aa2e7a9aba991a0e157</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___in_args.html</anchorfile>
      <anchor>ae18cbd70e339b8eb6f1218d4d568342d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>desiredChannelMode</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___in_args.html</anchorfile>
      <anchor>a0e92ea373b568bb9b01fc597ea9328bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lfeFlag</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___in_args.html</anchorfile>
      <anchor>aa883674ad2acf2783bd6ce5dc814f3ee</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_Obj</name>
    <filename>struct_i_a_u_d_d_e_c1___obj.html</filename>
    <member kind="variable">
      <type>struct IAUDDEC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___obj.html</anchorfile>
      <anchor>a3c9d38b9e3bea6d67ec63ade24103c5f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_OutArgs</name>
    <filename>struct_i_a_u_d_d_e_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a7c96524400bdc69520d551556d90d2ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>ae2c89e897af375c11ecf4a9cf1efa20e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>aa43125deb8cd6ebc4cb52349d1d3706a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numSamples</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>ade0b9c3e6a1af7efa3b643c37f47011b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>channelMode</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a656b5500bc0c66e36038f71d38904599</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lfeFlag</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a31afcddf15d8a63834c6d6859c85c788</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dualMonoMode</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>aeb55f5e3fd6c23e5f428b599d63af23f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a34c8f7cca4b8fc7c9aaf4efd4c386a0c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_Params</name>
    <filename>struct_i_a_u_d_d_e_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___params.html</anchorfile>
      <anchor>ac3e81428345ce8f38072b84f0915a630</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputPCMWidth</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___params.html</anchorfile>
      <anchor>a30d01ee3e225da6d3f38d40fa3ab6e20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>pcmFormat</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___params.html</anchorfile>
      <anchor>a9e01bdc5d85fe05c3359fc61ae922674</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___params.html</anchorfile>
      <anchor>ad574cb974d9171e50681d4ba1d73005d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_Status</name>
    <filename>struct_i_a_u_d_d_e_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a826bd51574317cd6454992edd2bb90c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a1206c6c4de6b6ab149d6e9502593a736</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>ae945132c2fcc18cbfa0a2651ffb2e00f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>validFlag</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a799fead5a0069edef26fe4db6c0a3a67</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lfeFlag</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a31f366f22b6be11a265997894ee2882d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a0b3807ad0e57a843c931a6fe4dc5dae8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>af7bb03870761a517669ddb3a1c074f27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>channelMode</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a31e28d7e4f0d6695a75db5cd8e334981</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>pcmFormat</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a8f483fe1584f0586fa1c7a8870485376</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numSamples</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a85478d6381cf013ecc6da9c1152fa01b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputBitsPerSample</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a059f98573ce856e21685533ca92e5213</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a27c19357781a5f50808b84d590b702dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dualMonoMode</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a4781ae1f91603c4e2abfee78eb22590d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_DynamicParams</name>
    <filename>struct_i_a_u_d_d_e_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a3efdf1a5413ab93b0683871995b261d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputFormat</name>
      <anchorfile>struct_i_a_u_d_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a77c203a30a88437d6ef39a909ee79a98</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_Fxns</name>
    <filename>struct_i_a_u_d_d_e_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_a_u_d_d_e_c___fxns.html</anchorfile>
      <anchor>a7d21b3a9a68e97547db2622d31e5e072</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_a_u_d_d_e_c___fxns.html</anchorfile>
      <anchor>ac4c542a8b025b2eb9625ef3fc0b4eec8</anchor>
      <arglist>)(IAUDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IAUDDEC_InArgs *inArgs, IAUDDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_a_u_d_d_e_c___fxns.html</anchorfile>
      <anchor>a58c2671fe58764d1efb786c55033e6be</anchor>
      <arglist>)(IAUDDEC_Handle handle, IAUDDEC_Cmd id, IAUDDEC_DynamicParams *params, IAUDDEC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_InArgs</name>
    <filename>struct_i_a_u_d_d_e_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c___in_args.html</anchorfile>
      <anchor>aff9bb0f0b05b08f11d4e63dfd59292ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_a_u_d_d_e_c___in_args.html</anchorfile>
      <anchor>a5779c96d5ac6b17bb72d8130c6012220</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_Obj</name>
    <filename>struct_i_a_u_d_d_e_c___obj.html</filename>
    <member kind="variable">
      <type>struct IAUDDEC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_a_u_d_d_e_c___obj.html</anchorfile>
      <anchor>ab4599f02c2e0ad7374f5cab60144b975</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_OutArgs</name>
    <filename>struct_i_a_u_d_d_e_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c___out_args.html</anchorfile>
      <anchor>a636d9cf7182daa83dde40b91503cb7d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_d_e_c___out_args.html</anchorfile>
      <anchor>ab36a174af0ebd1260366a2a3d6c420b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_a_u_d_d_e_c___out_args.html</anchorfile>
      <anchor>a36f1f3942a95eb2e0ef5a5abdfe18ce1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_Params</name>
    <filename>struct_i_a_u_d_d_e_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c___params.html</anchorfile>
      <anchor>abefd49970a0d7019a2149caceca25202</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxSampleRate</name>
      <anchorfile>struct_i_a_u_d_d_e_c___params.html</anchorfile>
      <anchor>a1d17ef20b3588b611da85987f190f051</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitrate</name>
      <anchorfile>struct_i_a_u_d_d_e_c___params.html</anchorfile>
      <anchor>aaec1f709e08221e4c57918f1cedba413</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxNoOfCh</name>
      <anchorfile>struct_i_a_u_d_d_e_c___params.html</anchorfile>
      <anchor>a7734e3b82506ac1984fb192d1570d2dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_a_u_d_d_e_c___params.html</anchorfile>
      <anchor>a1026e2790111047eb5abf97981eb24af</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_Status</name>
    <filename>struct_i_a_u_d_d_e_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a3ac44e0a364b869ade33de2367041eb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a92e4be96393ae49b63dd903046d45207</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a6ac5aa3f76443a4af8bf371ddfef2a1a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a308118960ef09f2d09efd00b0960b4b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numChannels</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>ae8b964499514d8faaee5a705e2a27c38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numLFEChannels</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a651beebf6269ed638c061deb6110ed20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputFormat</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>adf26589fae5a43e85c1d75fccc7fc5f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>autoPosition</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a5e88a20c8f23cbacfcdc6f3e4f4888d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>fastFwdLen</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a26aca932d0dd5b45e55b672e10bf2daa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameLen</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a12fbec1763df3e9927173b67fad59ac4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputBitsPerSample</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a8c1e5dbdd574b862d6496e17d7072e9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a85d70038b7e369f13f0d38a9464dc959</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_DynamicParams</name>
    <filename>struct_i_a_u_d_e_n_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a38669fd83b7e8bafd7df795ffba90e81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a2f9a6d0fc78715b6f011279974b60e09</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a5d1a59bfc159d8bb5295e2e3c50e3b5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>channelMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a282afbb193fb496790a1be716e4150ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lfeFlag</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a3e0ff85b937bdf6cadcbfc9a2ca1044f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dualMonoMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a07ce37dda31a8610bea11d291dc862c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputBitsPerSample</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a48a91dff3b69d89222787dfa0f942f96</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_Fxns</name>
    <filename>struct_i_a_u_d_e_n_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___fxns.html</anchorfile>
      <anchor>a7bf4105d2612bc042264f0cf82664522</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___fxns.html</anchorfile>
      <anchor>a2175ac4f31d6428adcdedff1adbe4ca1</anchor>
      <arglist>)(IAUDENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IAUDENC1_InArgs *inArgs, IAUDENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___fxns.html</anchorfile>
      <anchor>a5174d4a35ad3697b070c88fe863f7c7d</anchor>
      <arglist>)(IAUDENC1_Handle handle, IAUDENC1_Cmd id, IAUDENC1_DynamicParams *params, IAUDENC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_InArgs</name>
    <filename>struct_i_a_u_d_e_n_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___in_args.html</anchorfile>
      <anchor>a5a94c918431ae8a8de2062b475743225</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numInSamples</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___in_args.html</anchorfile>
      <anchor>a19afbc4c865d2c67145e9fa34bdc44ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>ancData</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___in_args.html</anchorfile>
      <anchor>aaacc03a3126aff730e2efddce672088b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_Obj</name>
    <filename>struct_i_a_u_d_e_n_c1___obj.html</filename>
    <member kind="variable">
      <type>struct IAUDENC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___obj.html</anchorfile>
      <anchor>a09b3f5bf9282709ddb3271a67b9b419b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_OutArgs</name>
    <filename>struct_i_a_u_d_e_n_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___out_args.html</anchorfile>
      <anchor>ad8ae4ff0472af0f3c4d0b1460e6f62f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a786ad251b077d9ea2fca7ed2a439737c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a602245d6b2522cdf47602e52f6abd9bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numZeroesPadded</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a1a66bd054185791eec49e7b23b32014f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numInSamples</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a624915bcdafb599bfc65c3ead26a5207</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_Params</name>
    <filename>struct_i_a_u_d_e_n_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>a863c8890eba38e149b9babd74b64472f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>a55b8e1d5f54dbd7ce3f7935bbf42be4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>af441094e0b6b7e080c39404a99298b6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>channelMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>ad6585c74128f70787cef03e3d51f64f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>a42ee7259bc8041c7b653b452ffbb526b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>aeb577e33a8a9cc3ed2895e7e55d64a4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFormat</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>a47267b88d7d0fbfcde6021abc876cb2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputBitsPerSample</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>a12495c4f1e6b27a024a79229a33c82cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>acbf7c107c1fee67764c066a33c221b53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dualMonoMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>ac0db971806a5564a262fea039168f338</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>crcFlag</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>ad8360020e2a4ee0d72175c3d6dae91ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>ancFlag</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>acced022f0aafffa576aebfe45bf0774b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lfeFlag</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>ac8289c3bd4154b9f10fb86c169cdc33b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_Status</name>
    <filename>struct_i_a_u_d_e_n_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a90db5b78e9f03f587a79978453866247</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a32d98a3c40437e07a9fcbea86257bd48</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a342aa2f4ef1e90bd55d6878d4cd65984</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a8d18605b6f4ddec8301e5677f50ede13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>validFlag</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a24c7cd3c841eaf2c94517b8eae61958b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lfeFlag</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a1a0e020552be775cf6889f8997dc5575</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a4764128db2b65d1c8b7b160e5a3c7663</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a524d800bdabb32aaf50cf719c0615e13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>channelMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>adf6a73a1aaf242ccc9f57831bc14fc13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a30b9ac5fa09ccfb1e3e5e584dbc39812</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_DynamicParams</name>
    <filename>struct_i_a_u_d_e_n_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>aece1b773849b274e83937c90afcfbbd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFormat</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>ab3bb1b4c908f342a66746ec4812c8a03</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a7e69f9c93e5fe34ab54226aa9efeacc7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a2551605459f2a3380045bef36eeec318</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numChannels</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a4d6ef3837f6e4a466a53fecd5ada26b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numLFEChannels</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>aa07be071f60ec426a25fdc7daa2d7703</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputBitsPerSample</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a845c8c4530de9b87179338c5116e170f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_Fxns</name>
    <filename>struct_i_a_u_d_e_n_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_a_u_d_e_n_c___fxns.html</anchorfile>
      <anchor>a76c6c607f10d91ffcf5a8288a14f6e1a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_a_u_d_e_n_c___fxns.html</anchorfile>
      <anchor>a6ceea92a81bde38833a084999912a721</anchor>
      <arglist>)(IAUDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IAUDENC_InArgs *inArgs, IAUDENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_a_u_d_e_n_c___fxns.html</anchorfile>
      <anchor>a30ecbc7373f4ad3c0f7eba39ae7ac585</anchor>
      <arglist>)(IAUDENC_Handle handle, IAUDENC_Cmd id, IAUDENC_DynamicParams *params, IAUDENC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_InArgs</name>
    <filename>struct_i_a_u_d_e_n_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c___in_args.html</anchorfile>
      <anchor>af1063c6ebc40bb5e0666b3bd4f4aaa39</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_Obj</name>
    <filename>struct_i_a_u_d_e_n_c___obj.html</filename>
    <member kind="variable">
      <type>struct IAUDENC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_a_u_d_e_n_c___obj.html</anchorfile>
      <anchor>a95d82873d8c890474e61acb69022996f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_OutArgs</name>
    <filename>struct_i_a_u_d_e_n_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c___out_args.html</anchorfile>
      <anchor>a8617cbe09b473159306623e0ab8e7664</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_e_n_c___out_args.html</anchorfile>
      <anchor>a84d7cbd368a512d72797ef1b295c3c83</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_a_u_d_e_n_c___out_args.html</anchorfile>
      <anchor>a7cc460eba6286f3c0c72e648e4a72c3e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_Params</name>
    <filename>struct_i_a_u_d_e_n_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c___params.html</anchorfile>
      <anchor>a121321ce5cfa852dbad28d1c5bbb3dff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodingPreset</name>
      <anchorfile>struct_i_a_u_d_e_n_c___params.html</anchorfile>
      <anchor>a23b6f1b1e86535831b5c3907d78765b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxSampleRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c___params.html</anchorfile>
      <anchor>a0c62620ea85d3e7f3f0e059f9450afa8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitrate</name>
      <anchorfile>struct_i_a_u_d_e_n_c___params.html</anchorfile>
      <anchor>a302736e97cd0a8473e850bf981dd58f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxNoOfCh</name>
      <anchorfile>struct_i_a_u_d_e_n_c___params.html</anchorfile>
      <anchor>adb1a33f7967138a4af5f2fe2696fee58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_a_u_d_e_n_c___params.html</anchorfile>
      <anchor>a9d1edc1ea5e41a532906f8740b85da46</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_Status</name>
    <filename>struct_i_a_u_d_e_n_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c___status.html</anchorfile>
      <anchor>aeee4d26ddd0bf88fc0d02afc49e72e61</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_e_n_c___status.html</anchorfile>
      <anchor>a446f27ae2c13dde94db6c99c8b65f7dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameLen</name>
      <anchorfile>struct_i_a_u_d_e_n_c___status.html</anchorfile>
      <anchor>aed3f3896aa0d2692de7acbb69bfcd6ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_a_u_d_e_n_c___status.html</anchorfile>
      <anchor>a2d5481a11c8b9b7d51b03b9e548a7d9e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IDMA2_ChannelRec</name>
    <filename>struct_i_d_m_a2___channel_rec.html</filename>
    <member kind="variable">
      <type>IDMA2_Handle</type>
      <name>handle</name>
      <anchorfile>struct_i_d_m_a2___channel_rec.html</anchorfile>
      <anchor>a72455ff8587e5ad789c6e20d5bda7462</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>queueId</name>
      <anchorfile>struct_i_d_m_a2___channel_rec.html</anchorfile>
      <anchor>a32e5c88e8c980f89abe5c8e8c9016118</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IDMA2_Fxns</name>
    <filename>struct_i_d_m_a2___fxns.html</filename>
    <member kind="variable">
      <type>Void *</type>
      <name>implementationId</name>
      <anchorfile>struct_i_d_m_a2___fxns.html</anchorfile>
      <anchor>ae4aec69c1b4eb01a41cc6c6e829407f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>dmaChangeChannels</name>
      <anchorfile>struct_i_d_m_a2___fxns.html</anchorfile>
      <anchor>a95cd1349592c225a9522f7703a2e416d</anchor>
      <arglist>)(IALG_Handle, IDMA2_ChannelRec *)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>dmaGetChannelCnt</name>
      <anchorfile>struct_i_d_m_a2___fxns.html</anchorfile>
      <anchor>a5167242c706e82691948e2ea1e02b935</anchor>
      <arglist>)(Void)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>dmaGetChannels</name>
      <anchorfile>struct_i_d_m_a2___fxns.html</anchorfile>
      <anchor>a9682012e1b5f2da7fcaaefcc0209a9ed</anchor>
      <arglist>)(IALG_Handle, IDMA2_ChannelRec *)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>dmaInit</name>
      <anchorfile>struct_i_d_m_a2___fxns.html</anchorfile>
      <anchor>a9acd35b0ae4bd56d6c4abe821f6ce91b</anchor>
      <arglist>)(IALG_Handle, IDMA2_ChannelRec *)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IDMA2_Params</name>
    <filename>struct_i_d_m_a2___params.html</filename>
    <member kind="variable">
      <type>IDMA2_TransferType</type>
      <name>xType</name>
      <anchorfile>struct_i_d_m_a2___params.html</anchorfile>
      <anchor>ac4cb949aa8af4570381ab19df60dfc68</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IDMA2_ElementSize</type>
      <name>elemSize</name>
      <anchorfile>struct_i_d_m_a2___params.html</anchorfile>
      <anchor>afe4c86c6657ebf21b1fc1f075ab73c7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Uns</type>
      <name>numFrames</name>
      <anchorfile>struct_i_d_m_a2___params.html</anchorfile>
      <anchor>aecc5e74a8409e081bbf58109198efc85</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>srcElementIndex</name>
      <anchorfile>struct_i_d_m_a2___params.html</anchorfile>
      <anchor>ab71f2d841255494a3af5f003726881cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>dstElementIndex</name>
      <anchorfile>struct_i_d_m_a2___params.html</anchorfile>
      <anchor>ae02a3357d3fd13b67414b2b4e553cd38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>srcFrameIndex</name>
      <anchorfile>struct_i_d_m_a2___params.html</anchorfile>
      <anchor>a7c1c6e45e45f8b641bdcc3aa74048d69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>dstFrameIndex</name>
      <anchorfile>struct_i_d_m_a2___params.html</anchorfile>
      <anchor>ac474fa21772cffed279cc883d9cc4763</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IDMA3_ChannelRec</name>
    <filename>struct_i_d_m_a3___channel_rec.html</filename>
    <member kind="variable">
      <type>IDMA3_Handle</type>
      <name>handle</name>
      <anchorfile>struct_i_d_m_a3___channel_rec.html</anchorfile>
      <anchor>a5632bb9719d49836987e3b4ae9b3d692</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>numTransfers</name>
      <anchorfile>struct_i_d_m_a3___channel_rec.html</anchorfile>
      <anchor>a725990b773355d1dfd5fc9af66179d22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>numWaits</name>
      <anchorfile>struct_i_d_m_a3___channel_rec.html</anchorfile>
      <anchor>a9be5abbc86b57d28e1d65cc6ea1ed294</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IDMA3_Priority</type>
      <name>priority</name>
      <anchorfile>struct_i_d_m_a3___channel_rec.html</anchorfile>
      <anchor>ae8b3740a842ad7ebb28cecf135f0c88f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IDMA3_ProtocolHandle</type>
      <name>protocol</name>
      <anchorfile>struct_i_d_m_a3___channel_rec.html</anchorfile>
      <anchor>aa7a4ff7549fd7be65a22cba0b8d50fad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>persistent</name>
      <anchorfile>struct_i_d_m_a3___channel_rec.html</anchorfile>
      <anchor>ac7a418727b547fe8f9d88f74f7d4c764</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IDMA3_Fxns</name>
    <filename>struct_i_d_m_a3___fxns.html</filename>
    <member kind="variable">
      <type>Void *</type>
      <name>implementationId</name>
      <anchorfile>struct_i_d_m_a3___fxns.html</anchorfile>
      <anchor>a4ee5aca6d6f29e0e09c83eaae2a44aec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>dmaChangeChannels</name>
      <anchorfile>struct_i_d_m_a3___fxns.html</anchorfile>
      <anchor>a1b05e503408ceb2849174d520932aa08</anchor>
      <arglist>)(IALG_Handle handle, IDMA3_ChannelRec *chnlRec)</arglist>
    </member>
    <member kind="variable">
      <type>Uns(*</type>
      <name>dmaGetChannelCnt</name>
      <anchorfile>struct_i_d_m_a3___fxns.html</anchorfile>
      <anchor>a2f893a5ce598a401aecf9e79a5d973d2</anchor>
      <arglist>)(Void)</arglist>
    </member>
    <member kind="variable">
      <type>Uns(*</type>
      <name>dmaGetChannels</name>
      <anchorfile>struct_i_d_m_a3___fxns.html</anchorfile>
      <anchor>a91d2edc4e5202ab46028a272cf8f7ad6</anchor>
      <arglist>)(IALG_Handle handle, IDMA3_ChannelRec *chnlRec)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>dmaInit</name>
      <anchorfile>struct_i_d_m_a3___fxns.html</anchorfile>
      <anchor>a080578d0edab90882b4fe8124c74eea2</anchor>
      <arglist>)(IALG_Handle handle, IDMA3_ChannelRec *chnlRec)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IDMA3_MemRec</name>
    <filename>struct_i_d_m_a3___mem_rec.html</filename>
    <member kind="variable">
      <type>Void *</type>
      <name>base</name>
      <anchorfile>struct_i_d_m_a3___mem_rec.html</anchorfile>
      <anchor>a2b6835f2ed01fd1ffc7e45c5daa04de1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Uns</type>
      <name>size</name>
      <anchorfile>struct_i_d_m_a3___mem_rec.html</anchorfile>
      <anchor>a667c10232578b390f66e698d796b4d2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Uns</type>
      <name>align</name>
      <anchorfile>struct_i_d_m_a3___mem_rec.html</anchorfile>
      <anchor>a18a74cc1005f251748f198ff09f8e76f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IDMA3_MemType</type>
      <name>memType</name>
      <anchorfile>struct_i_d_m_a3___mem_rec.html</anchorfile>
      <anchor>a6036233a20bd80fe13a6921db305ee9d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IDMA3_Obj</name>
    <filename>struct_i_d_m_a3___obj.html</filename>
    <member kind="variable">
      <type>unsigned short</type>
      <name>numTccs</name>
      <anchorfile>struct_i_d_m_a3___obj.html</anchorfile>
      <anchor>aa76e185f21e92e2949ecce7991f22780</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>numPaRams</name>
      <anchorfile>struct_i_d_m_a3___obj.html</anchorfile>
      <anchor>aa5adc01f587497ae3f7fac70d55116e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>tccTable</name>
      <anchorfile>struct_i_d_m_a3___obj.html</anchorfile>
      <anchor>a185dbbfdd7f200a4d692e6b6fcc6a7f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Uns *</type>
      <name>paRamAddr</name>
      <anchorfile>struct_i_d_m_a3___obj.html</anchorfile>
      <anchor>a61e6a45019fbc04e526cdd8cadbb6d59</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>qdmaChan</name>
      <anchorfile>struct_i_d_m_a3___obj.html</anchorfile>
      <anchor>a105710f5f0915241d4ebfb7640385338</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>transferPending</name>
      <anchorfile>struct_i_d_m_a3___obj.html</anchorfile>
      <anchor>a95914721dbaef8bce045253b0cb81468</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void *</type>
      <name>env</name>
      <anchorfile>struct_i_d_m_a3___obj.html</anchorfile>
      <anchor>a900c29cb46bab73d88002d88a5ca41a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IDMA3_ProtocolHandle</type>
      <name>protocol</name>
      <anchorfile>struct_i_d_m_a3___obj.html</anchorfile>
      <anchor>a74d1aa95d8583438686b86229a33a429</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>persistent</name>
      <anchorfile>struct_i_d_m_a3___obj.html</anchorfile>
      <anchor>aa45d155055413e89a97d98744809ee12</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IDMA3_ProtocolObj</name>
    <filename>struct_i_d_m_a3___protocol_obj.html</filename>
    <member kind="variable">
      <type>String</type>
      <name>name</name>
      <anchorfile>struct_i_d_m_a3___protocol_obj.html</anchorfile>
      <anchor>ae79494308149dd394cf13ceb8ba7c439</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>getEnvMemRec</name>
      <anchorfile>struct_i_d_m_a3___protocol_obj.html</anchorfile>
      <anchor>a8985b385f24d611a7e65f1b6fc867159</anchor>
      <arglist>)(IDMA3_ChannelRec *chnlRec, IDMA3_MemRec *memRec)</arglist>
    </member>
    <member kind="variable">
      <type>Bool(*</type>
      <name>initHandle</name>
      <anchorfile>struct_i_d_m_a3___protocol_obj.html</anchorfile>
      <anchor>a147bfd9a69a93542195adcdea86a6a58</anchor>
      <arglist>)(IDMA3_Handle handle)</arglist>
    </member>
    <member kind="variable">
      <type>Bool(*</type>
      <name>deInitHandle</name>
      <anchorfile>struct_i_d_m_a3___protocol_obj.html</anchorfile>
      <anchor>a7ce1036a56ee66ca9d0a195c04e40518</anchor>
      <arglist>)(IDMA3_Handle handle)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IDMA_ChannelRec</name>
    <filename>struct_i_d_m_a___channel_rec.html</filename>
    <member kind="variable">
      <type>Int</type>
      <name>depth</name>
      <anchorfile>struct_i_d_m_a___channel_rec.html</anchorfile>
      <anchor>a3dc100d443d6e1e9fbe753f4568cdac0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>dimensions</name>
      <anchorfile>struct_i_d_m_a___channel_rec.html</anchorfile>
      <anchor>a9f17d6841425e36a1f14c252b704ee97</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IDMA_Handle</type>
      <name>handle</name>
      <anchorfile>struct_i_d_m_a___channel_rec.html</anchorfile>
      <anchor>ab98b60551f6f9876cba38b70e5b211c3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IDMA_Fxns</name>
    <filename>struct_i_d_m_a___fxns.html</filename>
    <member kind="variable">
      <type>Void *</type>
      <name>implementationId</name>
      <anchorfile>struct_i_d_m_a___fxns.html</anchorfile>
      <anchor>ab2a26e0902c63ffc6fe0367d8253e8ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>dmaChangeChannels</name>
      <anchorfile>struct_i_d_m_a___fxns.html</anchorfile>
      <anchor>a5cefddb6241a75e15947dad3293fc8af</anchor>
      <arglist>)(IALG_Handle, IDMA_ChannelRec *)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>dmaGetChannelCnt</name>
      <anchorfile>struct_i_d_m_a___fxns.html</anchorfile>
      <anchor>ab964f73e5a790758a484797f1567ce91</anchor>
      <arglist>)(Void)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>dmaGetChannels</name>
      <anchorfile>struct_i_d_m_a___fxns.html</anchorfile>
      <anchor>af6e7e42594863be0f5123fa595eaf8d2</anchor>
      <arglist>)(IALG_Handle, IDMA_ChannelRec *)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>dmaInit</name>
      <anchorfile>struct_i_d_m_a___fxns.html</anchorfile>
      <anchor>a2f5573bcea1ecd878e3e3453025e80ac</anchor>
      <arglist>)(IALG_Handle, IDMA_ChannelRec *)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IDMA_Params</name>
    <filename>struct_i_d_m_a___params.html</filename>
    <member kind="variable">
      <type>IDMA_TransferType</type>
      <name>xType</name>
      <anchorfile>struct_i_d_m_a___params.html</anchorfile>
      <anchor>af4fd7bd692fa5a28316f7a8539a02f4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IDMA_ElementSize</type>
      <name>elemSize</name>
      <anchorfile>struct_i_d_m_a___params.html</anchorfile>
      <anchor>a2f2393a026be04557a80756d52dd3ad0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>numFrames</name>
      <anchorfile>struct_i_d_m_a___params.html</anchorfile>
      <anchor>a5f2f4352abea70ed866d6d128aeb457f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>stride</name>
      <anchorfile>struct_i_d_m_a___params.html</anchorfile>
      <anchor>a15153a13cd26b183e4896637b823925c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_DynamicParams</name>
    <filename>struct_i_i_m_g_d_e_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>aa4c9d6477d1b69da4a794235a9372dec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numAU</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>ab090944f3fe152ff41db1ac355ba991e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodeHeader</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a314c9a6c607b0717bb279ef154887322</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a4ab23a661fb362efb4908096191db7bf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_Fxns</name>
    <filename>struct_i_i_m_g_d_e_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___fxns.html</anchorfile>
      <anchor>a1673d23b38f9e6977a33b53aa65a923e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___fxns.html</anchorfile>
      <anchor>a13a91dc7eef87f708ddcfd547ff27d04</anchor>
      <arglist>)(IIMGDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IIMGDEC1_InArgs *inArgs, IIMGDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___fxns.html</anchorfile>
      <anchor>a5286ec4d1f0ac863a44908f68eca2995</anchor>
      <arglist>)(IIMGDEC1_Handle handle, IIMGDEC1_Cmd id, IIMGDEC1_DynamicParams *params, IIMGDEC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_InArgs</name>
    <filename>struct_i_i_m_g_d_e_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___in_args.html</anchorfile>
      <anchor>aea309a5bfa38760ab68185646ed4e9c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___in_args.html</anchorfile>
      <anchor>a9b784b066b2ec561358f36394ccfa1d9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_Obj</name>
    <filename>struct_i_i_m_g_d_e_c1___obj.html</filename>
    <member kind="variable">
      <type>struct IIMGDEC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___obj.html</anchorfile>
      <anchor>ad6d0a0e1c1ca47a5eac48d91c1109605</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_OutArgs</name>
    <filename>struct_i_i_m_g_d_e_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___out_args.html</anchorfile>
      <anchor>af2ec3b3eddf342cde6f9980439bed26f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___out_args.html</anchorfile>
      <anchor>acc8c984f3d9480504d47416f523fad91</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___out_args.html</anchorfile>
      <anchor>ac02d0a13f9df372d84b6799da82a3bf4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>currentAU</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___out_args.html</anchorfile>
      <anchor>af21d67faba69291bdf538e058cf97288</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>currentScan</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___out_args.html</anchorfile>
      <anchor>aa0beab4e9cb5cef8c62a85574dc14930</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_Params</name>
    <filename>struct_i_i_m_g_d_e_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___params.html</anchorfile>
      <anchor>a68ef28de7eeb2c1be8109d74a851f4ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___params.html</anchorfile>
      <anchor>a28a9950c839329471d708f4e176171a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___params.html</anchorfile>
      <anchor>aade2a8cf1f3ccdb0d980938261ddd37d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxScans</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___params.html</anchorfile>
      <anchor>a7c103d1347316a69abae2190b8dea17c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___params.html</anchorfile>
      <anchor>aaeef8352b4a4f9da7c78ff5822eee807</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___params.html</anchorfile>
      <anchor>a72c85f144a784198e26b432964f1bdb1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_Status</name>
    <filename>struct_i_i_m_g_d_e_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>af59caabb4e4ccc358630e6b363c107fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a37dfba8ab0c467adb7f6c1db717ecab6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a81ec5049fd6fa9600a624832e278f71e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a56f796a7a31a85e509398e7b16710885</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a4ac439b05ac11c19f601830757a22c65</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>imageWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a1307dd910542f436544c4d323a6ae1eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputChromaFormat</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a22a4a4cc9e80680bc8b7c8c0748e5130</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>totalAU</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a5179894a90ac9dbccee34da8f9867b11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>totalScan</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>acb0416bbc4b12fc1ed47e8884a2841f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a390e30541edc5cf2e8c1e34861acdf50</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_DynamicParams</name>
    <filename>struct_i_i_m_g_d_e_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a254655a6ad7c7193c53f999347aed127</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numAU</name>
      <anchorfile>struct_i_i_m_g_d_e_c___dynamic_params.html</anchorfile>
      <anchor>af065eaae9f3739fda81e8825984c9ef2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodeHeader</name>
      <anchorfile>struct_i_i_m_g_d_e_c___dynamic_params.html</anchorfile>
      <anchor>aae784db8ba465f6a24a79a7acd47a0bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a31786a33a7a9c554184e9c6dfe0db690</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_Fxns</name>
    <filename>struct_i_i_m_g_d_e_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_i_m_g_d_e_c___fxns.html</anchorfile>
      <anchor>a8e416fe391cd2f3105d31f222d1ba2e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_i_m_g_d_e_c___fxns.html</anchorfile>
      <anchor>a31fb7fbbffe4e089edf33b837bcc0118</anchor>
      <arglist>)(IIMGDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IIMGDEC_InArgs *inArgs, IIMGDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_i_m_g_d_e_c___fxns.html</anchorfile>
      <anchor>aa6fd366aa0ffb9739bbcf76236f56a48</anchor>
      <arglist>)(IIMGDEC_Handle handle, IIMGDEC_Cmd id, IIMGDEC_DynamicParams *params, IIMGDEC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_InArgs</name>
    <filename>struct_i_i_m_g_d_e_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c___in_args.html</anchorfile>
      <anchor>ab9f89a0eb8c44316d89b8e756fb4fbe0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_i_m_g_d_e_c___in_args.html</anchorfile>
      <anchor>a1b87bd7c64b4eae54f0242969171c97a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_Obj</name>
    <filename>struct_i_i_m_g_d_e_c___obj.html</filename>
    <member kind="variable">
      <type>struct IIMGDEC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_i_m_g_d_e_c___obj.html</anchorfile>
      <anchor>ae8899a18eb4544d8df8cd7a169650d5b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_OutArgs</name>
    <filename>struct_i_i_m_g_d_e_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c___out_args.html</anchorfile>
      <anchor>a184969265be2f68bd8057ce80787a858</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_d_e_c___out_args.html</anchorfile>
      <anchor>a8674f98d668855ebc621403037ac923e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesconsumed</name>
      <anchorfile>struct_i_i_m_g_d_e_c___out_args.html</anchorfile>
      <anchor>ab61e84a080a3b4a694b26cd281f40614</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>currentAU</name>
      <anchorfile>struct_i_i_m_g_d_e_c___out_args.html</anchorfile>
      <anchor>ac0b707601295096111ff8d68a768f0b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>currentScan</name>
      <anchorfile>struct_i_i_m_g_d_e_c___out_args.html</anchorfile>
      <anchor>a1cb086ad5fca07497045e8048602c7d9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_Params</name>
    <filename>struct_i_i_m_g_d_e_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c___params.html</anchorfile>
      <anchor>ac4d727a2d02d60c16fb9a14c0ff2b49c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_i_m_g_d_e_c___params.html</anchorfile>
      <anchor>aebd38c58951121af2fa1f065ce3850b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c___params.html</anchorfile>
      <anchor>a857319dc296cde870cd1ae319d843bdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxScans</name>
      <anchorfile>struct_i_i_m_g_d_e_c___params.html</anchorfile>
      <anchor>a535ad75b4f0ba9b6a71d974006ef47cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_i_m_g_d_e_c___params.html</anchorfile>
      <anchor>a845a59a3956acdaba154eb3a3db1e872</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_i_m_g_d_e_c___params.html</anchorfile>
      <anchor>a221f6bf52d0292e0a7aa86155c3fa8c6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_Status</name>
    <filename>struct_i_i_m_g_d_e_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>ad0152f6a4cc1559e839ea46d345fee71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>aa915f496c44181936937111c063d514c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>ac548c3f2d341ee948e9882da5dbdc43a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>af2e8f4997fe73adb906fcead9326d589</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>imageWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>a3181d0dcf4d20c8c616de7c14102a686</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outChromaformat</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>ab3c00954da4df2698d841e32dd4e6b2e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>totalAU</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>a4eac921b7c6ee4521c38e84f35c7f279</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>totalScan</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>ad33c5c68bd43da2c542a5071d5425b5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>a68ebe9eb6f5f695e0cfd9b3d5959338d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_DynamicParams</name>
    <filename>struct_i_i_m_g_e_n_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a204c149d672eb0ec2a804ed32b5f4f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numAU</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a399b147e439c80078ff6eb90f64867bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputChromaFormat</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a5997bc006ae260875c03bba4822ef831</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputHeight</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a5dff404be26d01f893c9a949f398c2eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputWidth</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a2f98fa2e18ca9e574b4ff03a835cd673</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>captureWidth</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a596b0b97d9470d219cb42a39dc7d0131</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>generateHeader</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a0bc97e319bfced1788bc7fbe2beb426e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>qValue</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a5acb90b702778906448f36559cf0db0c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_Fxns</name>
    <filename>struct_i_i_m_g_e_n_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___fxns.html</anchorfile>
      <anchor>a96bab6b9557586374244a47decc33ac7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___fxns.html</anchorfile>
      <anchor>aa54e936ca1e55be977939d0bcb932675</anchor>
      <arglist>)(IIMGENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IIMGENC1_InArgs *inArgs, IIMGENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___fxns.html</anchorfile>
      <anchor>a21fd3831f13a37f9944b09269599406a</anchor>
      <arglist>)(IIMGENC1_Handle handle, IIMGENC1_Cmd id, IIMGENC1_DynamicParams *params, IIMGENC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_InArgs</name>
    <filename>struct_i_i_m_g_e_n_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___in_args.html</anchorfile>
      <anchor>ab5daa9ec3ed4ebfc98b97a7071bcdd83</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_Obj</name>
    <filename>struct_i_i_m_g_e_n_c1___obj.html</filename>
    <member kind="variable">
      <type>struct IIMGENC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___obj.html</anchorfile>
      <anchor>a6e7640244d9414cc018dd20a4f493b28</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_OutArgs</name>
    <filename>struct_i_i_m_g_e_n_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___out_args.html</anchorfile>
      <anchor>a97fad74938d4965d2a7d287dae43cbf0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___out_args.html</anchorfile>
      <anchor>a950a903ecd2280b1f5d1a557ec011a53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___out_args.html</anchorfile>
      <anchor>a5475f48ec868746d031f014da5d9c6e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>currentAU</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___out_args.html</anchorfile>
      <anchor>a3e7a1946235ba233f417193956a37373</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_Params</name>
    <filename>struct_i_i_m_g_e_n_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___params.html</anchorfile>
      <anchor>a835e41b45a222e18f987d4baa8cdd8c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___params.html</anchorfile>
      <anchor>aa403e29e6bdf59d846d47a4993488113</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___params.html</anchorfile>
      <anchor>a7cff78e35b12cb9a5108851a482bcada</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxScans</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___params.html</anchorfile>
      <anchor>a552ff0784420f66be77a8a74e7220abe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___params.html</anchorfile>
      <anchor>a7c3d94b5c755a3bef6b11848da0224cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___params.html</anchorfile>
      <anchor>a9effdda884dcdf570e82549d9fb06908</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_Status</name>
    <filename>struct_i_i_m_g_e_n_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___status.html</anchorfile>
      <anchor>af9d5e1bc284efefcb16dc83bb967eb54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___status.html</anchorfile>
      <anchor>a74178f2a698da0e8ff167404d362a461</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___status.html</anchorfile>
      <anchor>ad2e308395a24a1eaef3b7329f6cb819f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>totalAU</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___status.html</anchorfile>
      <anchor>a92330058d2f29b19d6af03879e1db231</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___status.html</anchorfile>
      <anchor>aba6710131d4c45e1d66edbfed3a1cee9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_DynamicParams</name>
    <filename>struct_i_i_m_g_e_n_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a917db70323ce8e73f24eb2d48765d599</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numAU</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>ac881f6fbd5aff7fea90b226cd65570e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputChromaFormat</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>abc6397cc8192155d63a626f14a3046b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputHeight</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a4d0f6a5b443c13145c993ccb201e5904</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputWidth</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a7a0c2a88716feb3b60eb5eb875cbfed1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>captureWidth</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a4955921c6b4ceeb20f54b6337cbfdc93</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>generateHeader</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a51769be40d35f6de0e7189794da61683</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>qValue</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a2776a330ed24ff7d009c10ae158b0aec</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_Fxns</name>
    <filename>struct_i_i_m_g_e_n_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_i_m_g_e_n_c___fxns.html</anchorfile>
      <anchor>a9e2a218029f6f8dff34b312b519bcdfb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_i_m_g_e_n_c___fxns.html</anchorfile>
      <anchor>ace8cdefa23da4b6168834ca386bd2de4</anchor>
      <arglist>)(IIMGENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IIMGENC_InArgs *inArgs, IIMGENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_i_m_g_e_n_c___fxns.html</anchorfile>
      <anchor>a0ed53076380f314058c68dc5b6b0e9f8</anchor>
      <arglist>)(IIMGENC_Handle handle, IIMGENC_Cmd id, IIMGENC_DynamicParams *params, IIMGENC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_InArgs</name>
    <filename>struct_i_i_m_g_e_n_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c___in_args.html</anchorfile>
      <anchor>acd1a68fd6621f915df4bdabfe994387d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_Obj</name>
    <filename>struct_i_i_m_g_e_n_c___obj.html</filename>
    <member kind="variable">
      <type>struct IIMGENC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_i_m_g_e_n_c___obj.html</anchorfile>
      <anchor>a3ff20a14f6b60864f563bcf5af0eca02</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_OutArgs</name>
    <filename>struct_i_i_m_g_e_n_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c___out_args.html</anchorfile>
      <anchor>a60e743c4af4f564dcdf85649759902d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_e_n_c___out_args.html</anchorfile>
      <anchor>a95e9f3335445d1a4114d4d993f4d5ba6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_i_m_g_e_n_c___out_args.html</anchorfile>
      <anchor>a17bc924d654d6feb65f154c4a096c075</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>currentAU</name>
      <anchorfile>struct_i_i_m_g_e_n_c___out_args.html</anchorfile>
      <anchor>ac8c6a91a72d4cdadbacdfa2fb18f1e81</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_Params</name>
    <filename>struct_i_i_m_g_e_n_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c___params.html</anchorfile>
      <anchor>a6c6bd3222a36f376344d1bdd882679a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_i_m_g_e_n_c___params.html</anchorfile>
      <anchor>a8d5646fa9ada0fb55c21783c9d54cb3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_i_m_g_e_n_c___params.html</anchorfile>
      <anchor>aad4f389bbc2ea97a487aea0b9d8b60fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxScans</name>
      <anchorfile>struct_i_i_m_g_e_n_c___params.html</anchorfile>
      <anchor>a7e9f93fb240043a66dc3022220bad74e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_i_m_g_e_n_c___params.html</anchorfile>
      <anchor>a9c19691c3ab4f617a6b3d98087b8bfcf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_i_m_g_e_n_c___params.html</anchorfile>
      <anchor>a6377413cc5d331424b12b50264ac4711</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_Status</name>
    <filename>struct_i_i_m_g_e_n_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c___status.html</anchorfile>
      <anchor>a5552865d6cb4558209650d9224eedd4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_e_n_c___status.html</anchorfile>
      <anchor>a4bcea737f9177a0458c7844f8893d9d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>totalAU</name>
      <anchorfile>struct_i_i_m_g_e_n_c___status.html</anchorfile>
      <anchor>a6575078c14a7632304b47902bffa6eec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_i_m_g_e_n_c___status.html</anchorfile>
      <anchor>a4df69be928122e608cc562d464cc6bdf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_Fxns</name>
    <filename>struct_i_r_e_s___fxns.html</filename>
    <member kind="variable">
      <type>Void *</type>
      <name>implementationId</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a9e320f3ea97f6746f6687ab970cd1648</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>getResourceDescriptors</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a7a09d4c2d0b9d6ea00a238434f13a896</anchor>
      <arglist>)(IALG_Handle handle, IRES_ResourceDescriptor *resourceDescriptors)</arglist>
    </member>
    <member kind="variable">
      <type>Int32(*</type>
      <name>numResourceDescriptors</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a4dfe8c6eb0bc509a9a74517d06ec444b</anchor>
      <arglist>)(IALG_Handle handle)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>initResources</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a13d55bc4ddf27675771fc591cca1bebd</anchor>
      <arglist>)(IALG_Handle handle, IRES_ResourceDescriptor *resourceDescriptor, IRES_YieldFxn yieldFxn, IRES_YieldArgs yieldArgs)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>reinitResources</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a53b93ddb7af70df1b4d30de8a68b14f4</anchor>
      <arglist>)(IALG_Handle handle, IRES_ResourceDescriptor *resourceDescriptor, IRES_YieldFxn yieldFxn, IRES_YieldArgs yieldArgs)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>deinitResources</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a505e5cc4df9d8df3afa1fd93d79607d8</anchor>
      <arglist>)(IALG_Handle handle, IRES_ResourceDescriptor *resourceDescriptor)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>activateResource</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a168fba039eac1b1e5b69cc3837ae4c30</anchor>
      <arglist>)(IALG_Handle handle, IRES_Handle resourceHandle)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>activateAllResources</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a5be6be2dd432d0df47c45b40c0f9741f</anchor>
      <arglist>)(IALG_Handle handle)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>deactivateResource</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a3b3bd5cfca1d704cc9801585b7702f46</anchor>
      <arglist>)(IALG_Handle handle, IRES_Handle resourceHandle)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>deactivateAllResources</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a1aa3029eea7a037909974f2f39d80a98</anchor>
      <arglist>)(IALG_Handle handle)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_Obj</name>
    <filename>struct_i_r_e_s___obj.html</filename>
    <member kind="variable">
      <type>Int32</type>
      <name>persistent</name>
      <anchorfile>struct_i_r_e_s___obj.html</anchorfile>
      <anchor>a3e006a68f51d639510a5c4c40a9f6c5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>getStaticProperties</name>
      <anchorfile>struct_i_r_e_s___obj.html</anchorfile>
      <anchor>a6f851ab721d73bb546632ca59176fcc9</anchor>
      <arglist>)(struct IRES_Obj *resourceHandle, IRES_Properties *resourceProperties)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_Properties</name>
    <filename>struct_i_r_e_s___properties.html</filename>
    <member kind="variable">
      <type>Int32</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s___properties.html</anchorfile>
      <anchor>a1a09949a3cf97c048bb9de995fae07bf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_ProtocolArgs</name>
    <filename>struct_i_r_e_s___protocol_args.html</filename>
    <member kind="variable">
      <type>Int32</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s___protocol_args.html</anchorfile>
      <anchor>a22815469d186167c7c6ef6a61e8370e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_RequestMode</type>
      <name>mode</name>
      <anchorfile>struct_i_r_e_s___protocol_args.html</anchorfile>
      <anchor>afc5243b51314f144cd8e1c6e9a8aa339</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_ProtocolRevision</name>
    <filename>struct_i_r_e_s___protocol_revision.html</filename>
    <member kind="variable">
      <type>unsigned int</type>
      <name>Major</name>
      <anchorfile>struct_i_r_e_s___protocol_revision.html</anchorfile>
      <anchor>ab87b0887f1cddec8bce82b58cdd7f128</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>Source</name>
      <anchorfile>struct_i_r_e_s___protocol_revision.html</anchorfile>
      <anchor>af316c476cb1698db013aa50b30681178</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>Radius</name>
      <anchorfile>struct_i_r_e_s___protocol_revision.html</anchorfile>
      <anchor>ab3d416ec6cf89163f2a4c71b4e90e00e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_ResourceDescriptor</name>
    <filename>struct_i_r_e_s___resource_descriptor.html</filename>
    <member kind="variable">
      <type>String</type>
      <name>resourceName</name>
      <anchorfile>struct_i_r_e_s___resource_descriptor.html</anchorfile>
      <anchor>a5973fb17ebaef2af33b062c83b80dc09</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct IRES_ProtocolArgs *</type>
      <name>protocolArgs</name>
      <anchorfile>struct_i_r_e_s___resource_descriptor.html</anchorfile>
      <anchor>abf4eb84081251fe2ae5f47edfec3b277</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_ProtocolRevision *</type>
      <name>revision</name>
      <anchorfile>struct_i_r_e_s___resource_descriptor.html</anchorfile>
      <anchor>ac763c830eaa0da73edafcabdc9990b05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct IRES_Obj *</type>
      <name>handle</name>
      <anchorfile>struct_i_r_e_s___resource_descriptor.html</anchorfile>
      <anchor>a45b8e88d5f2e1dd20292f6f90783fed2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_YieldContext</name>
    <filename>struct_i_r_e_s___yield_context.html</filename>
    <member kind="variable">
      <type>IALG_Handle</type>
      <name>algHandle</name>
      <anchorfile>struct_i_r_e_s___yield_context.html</anchorfile>
      <anchor>a7e57c67d7eaa92e777ec01ee783235a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_Handle</type>
      <name>resourceHandle</name>
      <anchorfile>struct_i_r_e_s___yield_context.html</anchorfile>
      <anchor>ad641392437c775a78dfeae74d8f6ab24</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_ContextSaveFxn</type>
      <name>contextSave</name>
      <anchorfile>struct_i_r_e_s___yield_context.html</anchorfile>
      <anchor>a916710952108beb0b6d5d2ef0dac3094</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_ContextRestoreFxn</type>
      <name>contextRestore</name>
      <anchorfile>struct_i_r_e_s___yield_context.html</anchorfile>
      <anchor>aac53739996c8c602f74949c1c350b9c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void *</type>
      <name>contextArgs</name>
      <anchorfile>struct_i_r_e_s___yield_context.html</anchorfile>
      <anchor>adf3ac7ac9954a2b8df2dafbc42041f3f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_DynamicParams</name>
    <filename>struct_i_s_p_h_d_e_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>aa80dbc4b1adab84f34bdfc87f20dba59</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>postFilter</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a2011eaca87837ea467fc5c160ac4ad01</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_Fxns</name>
    <filename>struct_i_s_p_h_d_e_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___fxns.html</anchorfile>
      <anchor>ae8f8acf1b191b805ee9ae2ce749d72ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___fxns.html</anchorfile>
      <anchor>a1528fd9997b1c8f10b4f0e90e41f2984</anchor>
      <arglist>)(ISPHDEC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, ISPHDEC1_InArgs *inArgs, ISPHDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___fxns.html</anchorfile>
      <anchor>a83d133bb27e0e59f5edefc327cd87c18</anchor>
      <arglist>)(ISPHDEC1_Handle handle, ISPHDEC1_Cmd id, ISPHDEC1_DynamicParams *params, ISPHDEC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_InArgs</name>
    <filename>struct_i_s_p_h_d_e_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___in_args.html</anchorfile>
      <anchor>a45573006d595ec7e02613c1ac23426b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>frameType</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___in_args.html</anchorfile>
      <anchor>a9ede028467059e0d566bafe42933966c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___in_args.html</anchorfile>
      <anchor>a3a54f5846955c1f79d11e4b90cd75bc5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_Obj</name>
    <filename>struct_i_s_p_h_d_e_c1___obj.html</filename>
    <member kind="variable">
      <type>struct ISPHDEC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___obj.html</anchorfile>
      <anchor>a820bfb1636e6112b60185a66c8dcd80a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_OutArgs</name>
    <filename>struct_i_s_p_h_d_e_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___out_args.html</anchorfile>
      <anchor>a9072041fcbbf6aed30c2c286f1a31709</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>dataSize</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___out_args.html</anchorfile>
      <anchor>af5f61f240741989786abb67ac599fb08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___out_args.html</anchorfile>
      <anchor>a31dd580740fa35e7ee89953bfcedbbce</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_Params</name>
    <filename>struct_i_s_p_h_d_e_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>a150293e4c3110f3d4d076e0408d2a9ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>compandingLaw</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>a86b1a7c0a3097ba622357b46649580c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>packingType</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>a6a12afd16b8bcb17b0e6a7297c3131fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>codecSelection</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>adc0e9a85ccf92a99e57d9a40dc1b94df</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>adb1b22225f324f421d0552078c727e34</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>reserved</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>a0e95534b18d38e18a2ae953f08d62b72</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int8 **</type>
      <name>tablesPtr</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>a7bdee67fcfdecaa52441dbc7d597dd54</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_Status</name>
    <filename>struct_i_s_p_h_d_e_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>afcf7cc947701f22368d207b5e131554c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>postFilter</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>ad5dd7e6a43220b9fb692b1d4a22eaa3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>ae3e61248edeeaaa883da2c9e9d1e6e68</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>a43828548e9cbe9f8d9d3e68f34211322</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>compandingLaw</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>a4d95d33d7e021796289df9a0a292fdb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>packingType</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>aac6319cce34942d24a437d0f4e121a1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>ab6ac3e7ce838a59fb108df9996c3d66e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>codecSelection</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>a2b7136b6d521d7bee05cf824fb7b0b57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>ac3acec4581c20c9a44536da145cf9ba8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_DynamicParams</name>
    <filename>struct_i_s_p_h_d_e_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a69d0c7eb681ba0e6b3f0ffee99f2a867</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>postFilter</name>
      <anchorfile>struct_i_s_p_h_d_e_c___dynamic_params.html</anchorfile>
      <anchor>af345bcd1722adcb770f9817fb2cd44bc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_Fxns</name>
    <filename>struct_i_s_p_h_d_e_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_s_p_h_d_e_c___fxns.html</anchorfile>
      <anchor>a26f77c1d91e749fd168f047a3c96d799</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_s_p_h_d_e_c___fxns.html</anchorfile>
      <anchor>a5503c387e8d4d0c19bac44502262a3fa</anchor>
      <arglist>)(ISPHDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, ISPHDEC_InArgs *inArgs, ISPHDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_s_p_h_d_e_c___fxns.html</anchorfile>
      <anchor>a68fb3f93b8b7043dc1fe6e3e14f03a65</anchor>
      <arglist>)(ISPHDEC_Handle handle, ISPHDEC_Cmd id, ISPHDEC_DynamicParams *params, ISPHDEC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_InArgs</name>
    <filename>struct_i_s_p_h_d_e_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c___in_args.html</anchorfile>
      <anchor>a4d51fb5ac0aa12cf3a80f7ccf008b8b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameType</name>
      <anchorfile>struct_i_s_p_h_d_e_c___in_args.html</anchorfile>
      <anchor>ab7c8a4c2eaac00268c7655c5f5a48fda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inBufferSize</name>
      <anchorfile>struct_i_s_p_h_d_e_c___in_args.html</anchorfile>
      <anchor>abb3ac1b9a729328cd7ce7aa8f7045798</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bfiFlag</name>
      <anchorfile>struct_i_s_p_h_d_e_c___in_args.html</anchorfile>
      <anchor>aa61efbf8cb2a0a6796de0f74a3d150e5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_Obj</name>
    <filename>struct_i_s_p_h_d_e_c___obj.html</filename>
    <member kind="variable">
      <type>struct ISPHDEC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_s_p_h_d_e_c___obj.html</anchorfile>
      <anchor>a54f99ede68e33cecc93c7e4e236af75f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_OutArgs</name>
    <filename>struct_i_s_p_h_d_e_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c___out_args.html</anchorfile>
      <anchor>ab538e6e2fb343331efae12ff703ccf9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mode</name>
      <anchorfile>struct_i_s_p_h_d_e_c___out_args.html</anchorfile>
      <anchor>a359a57b1de038428926e31b4b700dd49</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_Params</name>
    <filename>struct_i_s_p_h_d_e_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c___params.html</anchorfile>
      <anchor>ac229d338e2023f649ec9f5a919ce7af6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEnable</name>
      <anchorfile>struct_i_s_p_h_d_e_c___params.html</anchorfile>
      <anchor>ac3fcf69d59409092de9fac52f16d8424</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>compandingLaw</name>
      <anchorfile>struct_i_s_p_h_d_e_c___params.html</anchorfile>
      <anchor>a05b1acdd03d9afc0889c21287a6b20e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>packingType</name>
      <anchorfile>struct_i_s_p_h_d_e_c___params.html</anchorfile>
      <anchor>a17361b8876ba4566cd049cc14f364349</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_Status</name>
    <filename>struct_i_s_p_h_d_e_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c___status.html</anchorfile>
      <anchor>ac9ba939e27d759b58681209896404f7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_s_p_h_d_e_c___status.html</anchorfile>
      <anchor>aaa5760ae19aadf956429f768d59dd3c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>postFilter</name>
      <anchorfile>struct_i_s_p_h_d_e_c___status.html</anchorfile>
      <anchor>a4f6a588c75a2b2c1954dd0ca035c69ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataMode</name>
      <anchorfile>struct_i_s_p_h_d_e_c___status.html</anchorfile>
      <anchor>a09c625c1d8d5da7403d5feec6d2bc091</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_s_p_h_d_e_c___status.html</anchorfile>
      <anchor>ab5bd8caf50e5ac128ae7a3fdeb57e81d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_DynamicParams</name>
    <filename>struct_i_s_p_h_e_n_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>aed45782060e60f187f0feadd0c789a8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>frameSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a4437394a8d96b7fa06dd52713414878b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>ae1373dedffee3604fb2cec5f4f4ae237</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>mode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a30e446e8f1a7f5eeb41e30f7feefc044</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>vadFlag</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a92326b689b7849a2e88fec8b87e5a641</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>noiseSuppressionMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>ae77ce3b38ad8d6b3ee8e3f36cc826776</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>ttyTddMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a9605fa7c93a86e744dfe1360b0b39f21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>dtmfMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>abb206a3c91bd2482ae51bb9ab99ed41a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>dataTransmit</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>aedfa37091dbde8ef4b7ebf50ee7b312e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>reserved</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a996dce6c5654b65aac19600fbc805e13</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_Fxns</name>
    <filename>struct_i_s_p_h_e_n_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___fxns.html</anchorfile>
      <anchor>a6a14f0e7d1a8641cf5f22be8b21d6ed4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___fxns.html</anchorfile>
      <anchor>a43e82ca6e0fa6e80f9f9e77b41d61362</anchor>
      <arglist>)(ISPHENC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, ISPHENC1_InArgs *inArgs, ISPHENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___fxns.html</anchorfile>
      <anchor>ad9db876aa3817ce0d4c302836b752e01</anchor>
      <arglist>)(ISPHENC1_Handle handle, ISPHENC1_Cmd id, ISPHENC1_DynamicParams *params, ISPHENC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_InArgs</name>
    <filename>struct_i_s_p_h_e_n_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___in_args.html</anchorfile>
      <anchor>a8795bb208ec9aa0838210f60192740e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>nullTrafficChannel</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___in_args.html</anchorfile>
      <anchor>ab4b97eb4d6ec791504cdfb7bae5175a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___in_args.html</anchorfile>
      <anchor>a5a0c3ba88718f5ea6b7615e843f021e0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_Obj</name>
    <filename>struct_i_s_p_h_e_n_c1___obj.html</filename>
    <member kind="variable">
      <type>struct ISPHENC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___obj.html</anchorfile>
      <anchor>a8daccb2c03641870da2c5ea613d516d2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_OutArgs</name>
    <filename>struct_i_s_p_h_e_n_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___out_args.html</anchorfile>
      <anchor>a10a1dc52e2670c743435650cefc64e69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>frameType</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___out_args.html</anchorfile>
      <anchor>a3b3756aaa580605720e141c2b181742c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___out_args.html</anchorfile>
      <anchor>ab60d44742ed5bcb09c76c185b7890f01</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_Params</name>
    <filename>struct_i_s_p_h_e_n_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>ac3ed9cc730c55ded22ca0106eb8c7b81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>frameSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>a3c0fc73a4453be910b7fa7f839cd6bfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>compandingLaw</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>a294eb4a70b58ba4855d6a7be6edcff25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>packingType</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>a00bcdc92adaca6dde2e016fcd67d977b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>vadSelection</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>aa9e0f5bd11b4139a668e70a8e12c1f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>codecSelection</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>a61a56a09221795892a17d263791e7e4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>a8ee2d360abce8bce78fcbcfe64096a38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>reserved</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>a6e7e4a4b1ddf71036b1924efb656c490</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int8 **</type>
      <name>tablesPtr</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>af97ca42a83ab32b534d96fa7c1f79c5d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_Status</name>
    <filename>struct_i_s_p_h_e_n_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a89a6a1e91831b571a7c8307b03983385</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>frameSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>ab642b0e66c77e4cb23b2fc6d6d985842</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a966d94b3e82336d3bae68d371c2c91b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>aaf8b77469771204141f263a50fc21ddf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a6331d68b41434a85591adade72ed5dbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>mode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a580eb5e7ec546e662d624fb1264ee234</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>vadFlag</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a25a68e90cdb9c2a3dfbd6a4f40418da9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>noiseSuppressionMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>ad62aee90031890bac72c38f8cdb6f77a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>ttyTddMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a09cd795e3aebe95dfccded3b59dd6ff1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>dataTransmit</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a3ac6b41cbfd395e7e04a53a646388f5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>compandingLaw</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>aab6fb0582c9e6dfb74a0a3918bd60286</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>packingType</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>ab1497f19b4f3892b08741d6ba997ce3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>vadSelection</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a0c83f887a70d682870b1ab12624463e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>codecSelection</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a73c4340fd3e638c3e68fa4dde57b871f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a97430d5b68ed94e0ac72b5055688890d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_DynamicParams</name>
    <filename>struct_i_s_p_h_e_n_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>ae9c89ae7ddabe50e8859d551972d498c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a2281e59eb159955391c4ff4671912f0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a0f2a2397c0da0230024b3cf728c20fc3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>abc9eb329f94aa7fa8b1ab8e1d373c6da</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>vadFlag</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a800e821077e744a3bafe40c012d38a99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>noiseSuppressionMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>af307f8dad51fdc45b99b187f2dd18cb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>ttyTddMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a52ef158dd0c071bae86ec620eba81cb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dtmfMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a8d4619f29a70e5adec01566a44b8d6a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataTransmit</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a9fe622f273a17ed40140f4110b6666f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>homingMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a95466225694803c1cb293591f7d85710</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_Fxns</name>
    <filename>struct_i_s_p_h_e_n_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_s_p_h_e_n_c___fxns.html</anchorfile>
      <anchor>ab4b06da0cf49039ff6b4082044a2b4e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_s_p_h_e_n_c___fxns.html</anchorfile>
      <anchor>a0e9da2ef8390270414527bdcf5c3fbb7</anchor>
      <arglist>)(ISPHENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_s_p_h_e_n_c___fxns.html</anchorfile>
      <anchor>a5003aafa401748cc192937e0f2f60506</anchor>
      <arglist>)(ISPHENC_Handle handle, ISPHENC_Cmd id, ISPHENC_DynamicParams *params, ISPHENC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_InArgs</name>
    <filename>struct_i_s_p_h_e_n_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c___in_args.html</anchorfile>
      <anchor>af9a0b560b9715d0e235eb9ae2838c9c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>nullTrafficChannel</name>
      <anchorfile>struct_i_s_p_h_e_n_c___in_args.html</anchorfile>
      <anchor>ac97de35c9a329850ada08e3afb1859f1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_Obj</name>
    <filename>struct_i_s_p_h_e_n_c___obj.html</filename>
    <member kind="variable">
      <type>struct ISPHENC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_s_p_h_e_n_c___obj.html</anchorfile>
      <anchor>a5b3a8200c044373c19a3465b2a809274</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_OutArgs</name>
    <filename>struct_i_s_p_h_e_n_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c___out_args.html</anchorfile>
      <anchor>adf03c48d4a0ee962eacbff1c8ebc53fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>rate</name>
      <anchorfile>struct_i_s_p_h_e_n_c___out_args.html</anchorfile>
      <anchor>ae5ba034f9c0748545bf8674a7d285a7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameType</name>
      <anchorfile>struct_i_s_p_h_e_n_c___out_args.html</anchorfile>
      <anchor>ab55c2dc506493a6a6860e075e52e8158</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outbufferSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c___out_args.html</anchorfile>
      <anchor>a6edfb6b938404329a60626afc140e5ae</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_Params</name>
    <filename>struct_i_s_p_h_e_n_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c___params.html</anchorfile>
      <anchor>a1eeaa38d0dd3be8f8b98002d35494395</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c___params.html</anchorfile>
      <anchor>acb6c0b813aead1aaab8090e9efff8be6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>compandingLaw</name>
      <anchorfile>struct_i_s_p_h_e_n_c___params.html</anchorfile>
      <anchor>ae347c74c98a906f83b5a2c005f0f7b6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>packingType</name>
      <anchorfile>struct_i_s_p_h_e_n_c___params.html</anchorfile>
      <anchor>aeafe6470d58388f75605a4b2a9ee3353</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>vadSelection</name>
      <anchorfile>struct_i_s_p_h_e_n_c___params.html</anchorfile>
      <anchor>ada2463e8eff933b2afc2b3a5ba181dde</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_Status</name>
    <filename>struct_i_s_p_h_e_n_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a9fe7c098724d9e48869d8cf1c5835058</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a3484a924fe8912812cf33546307516f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>af4f194cea891f8a5ac5ca9bd59d80058</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>abcef129c023f16336325924b70837f8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>ad69484eb3965162bd70c5c387c1649fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>vadFlag</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a10c25a825c2aeac37e7cbc94fc50d4bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>noiseSuppressionMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>aae2940bea7804c160bd687b9484bac51</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>ttyTddMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a60445311e7c3c938ee4329b30addf124</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dtmfMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a21ae87e405581a1f2f3f0f1607417c3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataTransmit</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a1399d6462179fd0d0aab6bc132444d38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>homingMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a8c12a4ec0aef606445e7eb8b978efc15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a77477c93c7ae260c00212d50d98700c1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_DynamicParams</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___dynamic_params.html</anchorfile>
      <anchor>a15355c4f8e6d2afadf99bda670980e62</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_Fxns</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___fxns.html</anchorfile>
      <anchor>a8427e1827bd68ef315a8787b91e50597</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___fxns.html</anchorfile>
      <anchor>a4fe46a93d02d5ae1b5aeab84e8cf69a9</anchor>
      <arglist>)(IUNIVERSAL_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs, IUNIVERSAL_InArgs *inArgs, IUNIVERSAL_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___fxns.html</anchorfile>
      <anchor>ab32eb3ab35b9fa34c9777c68d0b19f2b</anchor>
      <arglist>)(IUNIVERSAL_Handle handle, IUNIVERSAL_Cmd id, IUNIVERSAL_DynamicParams *params, IUNIVERSAL_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_InArgs</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___in_args.html</anchorfile>
      <anchor>af9be414dfa950c062a3583962f0267fc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_Obj</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___obj.html</filename>
    <member kind="variable">
      <type>struct IUNIVERSAL_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___obj.html</anchorfile>
      <anchor>afb8fb7ade7c834512e353dd2aabb3590</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_OutArgs</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___out_args.html</anchorfile>
      <anchor>a3901f8ee5a120892ccca1c686f137d77</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___out_args.html</anchorfile>
      <anchor>a3c9565d7505e4f1124fa1bdd7dfb2f61</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_Params</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___params.html</anchorfile>
      <anchor>ad1dc428353fb7a3a3be6d8925a9e2f16</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_Status</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___status.html</anchorfile>
      <anchor>a94a07151dc36836a90c27943da2e6548</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___status.html</anchorfile>
      <anchor>a942ebb5d34f7c52fdfcc854b8c6dbf2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_BufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___status.html</anchorfile>
      <anchor>abb4cd323acf4504cb16f0e7c0f301ecb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_DynamicParams</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___dynamic_params.html</anchorfile>
      <anchor>a89a472b058a47b48bf35f9d630b2eb8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDANALYTICS_Grid *</type>
      <name>grid</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___dynamic_params.html</anchorfile>
      <anchor>a9a1c3eda1f8954941e6baf1481c5e3d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_Date</type>
      <name>date</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___dynamic_params.html</anchorfile>
      <anchor>ad86e3a05938f2085187c6e2d2c265000</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDANALYTICS_Rule</type>
      <name>rule</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___dynamic_params.html</anchorfile>
      <anchor>a9f6ff5f1a8ba77b1bfc23e75e991ded4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_Fxns</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___fxns.html</anchorfile>
      <anchor>ae78c7ef8aee125ed17a9e9846832f4f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___fxns.html</anchorfile>
      <anchor>a697152bc6e993db00d13da49ce02df46</anchor>
      <arglist>)(IVIDANALYTICS_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IVIDANALYTICS_InArgs *inArgs, IVIDANALYTICS_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___fxns.html</anchorfile>
      <anchor>ad944512b2eae910d991086e1279ab8d5</anchor>
      <arglist>)(IVIDANALYTICS_Handle handle, IVIDANALYTICS_Cmd id, IVIDANALYTICS_DynamicParams *params, IVIDANALYTICS_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_Grid</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___grid.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>blockHeight</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___grid.html</anchorfile>
      <anchor>aadad9de1da8bc5f7a83c7efda589bc4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>blockWidth</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___grid.html</anchorfile>
      <anchor>a2653d8f67279b20e05f0b228981acaa0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBlockHorizontal</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___grid.html</anchorfile>
      <anchor>a8943afaeff1a3034ec8ea885979850cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBlockVertical</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___grid.html</anchorfile>
      <anchor>a9463008dad159614786f625342f62299</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>enableMaskArray</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___grid.html</anchorfile>
      <anchor>a22d4103ed181b76db5b2a71ecf29825a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_InArgs</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___in_args.html</anchorfile>
      <anchor>a4139d117f5a65a36aa44d07bedbcf8af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_Date</type>
      <name>date</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___in_args.html</anchorfile>
      <anchor>a6ebd0affa3fb133be773deb53004be35</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_Obj</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDANALYTICS_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___obj.html</anchorfile>
      <anchor>a818a9697131a5a07e102c61ed6103be2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_OutArgs</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>aa28507409a7754351df49a0584399767</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numTargets</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>a14f86950466cfb603ed8cc828bd3f4a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_Rect</type>
      <name>targets</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>ab93f3d95de67e25a7febf41a3dc19bc1</anchor>
      <arglist>[128]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numEvents</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>a58a2b2a64e196119da2a1299173c6b2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>eventId</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>ad78c6da1b3a6b1fd1a869cd29bc3dd60</anchor>
      <arglist>[128]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>acec206bd09ad8acbcc6842f4832d978e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_Date</type>
      <name>date</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>a883c5d7eb424f36cc54f4a7f75a1621c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_Params</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>a5836dcd5adf13b19001fb22393d89575</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>ad337a654a3fd847395443390aa712f94</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>a03bf452b002c12bcc44b2301975f0159</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>ab6264d6f76a9ad2917b468a4f97258d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>a980c99733f0208bc582d5819ed7e1933</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>ad9e76064d1d91da019ec118c22edf902</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxRules</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>a9eac89ed14d607b8b8b8c42746ece5f5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_Rule</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___rule.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___rule.html</anchorfile>
      <anchor>a973da95662eb1b24ccd59eacf6e5ba7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>id</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___rule.html</anchorfile>
      <anchor>adba91d965b0ff28788736df77016b8be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDANALYTICS_ObjectType</type>
      <name>objectType</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___rule.html</anchorfile>
      <anchor>a2baa2a52ff057f7033356631b60f3719</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDANALYTICS_ActionType</type>
      <name>actionType</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___rule.html</anchorfile>
      <anchor>a865a0736f761a0b2ad3de3ad36956896</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_Status</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___status.html</anchorfile>
      <anchor>aef5c85f56b6491b34c7c3a7668765bb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___status.html</anchorfile>
      <anchor>a34b4b953d61ac2abba683989c434b709</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_BufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___status.html</anchorfile>
      <anchor>acbf73996a05f3a1835732c63d3c3c8d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___status.html</anchorfile>
      <anchor>ade1e749887cf799d722930085f393cb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>viewState</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___status.html</anchorfile>
      <anchor>aea3e08dce00a80d491939e5a82997877</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_DynamicParams</name>
    <filename>struct_i_v_i_d_d_e_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>acfe23316a964cabf5f2803ebca48130b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodeHeader</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>aeba527b40a39cbf8ab2d1cf55b6e0d3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>aa914dbaa8ccd4be77444e48321a2b74f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSkipMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>ae75efcb3647729a7cbfc053137c0d4ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameOrder</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a97415f8d6295264ccfb297a2c3e7fa1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>newFrameFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a15905a53f770cac2d89aa014996d8c12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mbDataFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a1585382a02fb971aa5030a85586e2a32</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_Fxns</name>
    <filename>struct_i_v_i_d_d_e_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___fxns.html</anchorfile>
      <anchor>a277bba41de7d779c3f6d4629a0530a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___fxns.html</anchorfile>
      <anchor>aeb14b43b7212ac2de116381f5b07b1d4</anchor>
      <arglist>)(IVIDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDDEC1_InArgs *inArgs, IVIDDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___fxns.html</anchorfile>
      <anchor>a907ccbcc0221e6cf27c6a6d9ac08719b</anchor>
      <arglist>)(IVIDDEC1_Handle handle, IVIDDEC1_Cmd id, IVIDDEC1_DynamicParams *params, IVIDDEC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_InArgs</name>
    <filename>struct_i_v_i_d_d_e_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___in_args.html</anchorfile>
      <anchor>a220a48292999de7a753b53cb38c201dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___in_args.html</anchorfile>
      <anchor>aa9e5c1ef5e0e5cad7deccc27e3f4f8bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___in_args.html</anchorfile>
      <anchor>a15a674a4a16aac9c5016ba6eceda0026</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_Obj</name>
    <filename>struct_i_v_i_d_d_e_c1___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDDEC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___obj.html</anchorfile>
      <anchor>a1cbed5bb6a1174539b8e06afe216b739</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_OutArgs</name>
    <filename>struct_i_v_i_d_d_e_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a57bf5f028cef1b3104daf1d204434389</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a036474c89354f0b5b281ca144769bff0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>ac9098671bed458a00c0834d255efd358</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO1_BufDesc</type>
      <name>decodedBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a9b0fbaf05d3941fdb7a384e55704b21d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO1_BufDesc</type>
      <name>displayBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>ac6a36e629bdeaf31dc5880e644ad3e15</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputMbDataID</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a894cb60736b6b6ace11736bf0c060fe6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>mbDataBuf</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a0e063681f3c945bf22642c2b46c57f0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>freeBufID</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a908c3ae1727f4b2307893ab51d42240a</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outBufsInUseFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a2814bb51f173cb8ea092e2a512bdb8e3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_Params</name>
    <filename>struct_i_v_i_d_d_e_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>a601096b5c6de01527a2ef5d0020719e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>ae1392ad3e68fb20d03da126a6c02d941</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>a803208ae11e51ea7afa70c4612c4b515</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>a76ab8c9e7b93549a78b3f570a4bbfe82</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>a499b80580198e47aaa527c7fbef74730</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>a89108ef2f6456fc160468cdb97aea779</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>ae8e32f2729f945c4086b45b389e6a71b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_Status</name>
    <filename>struct_i_v_i_d_d_e_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>ac4e76fb6d3d81df993f40a4040debeae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>a226a2e4def4e023df187378384d2950b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>a6c9e519948896577c29071e9ee3e8dd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>a3c288f74c6f5773b946414eec8434df8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>a72686d6a7606abb98a5c35a8e14ce053</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>a908fa7a6e55bd3a38361e26c5e410faf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>a02334a7d28900fafe2ab02a2689a0cdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>contentType</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>aaf3360bf85d0d4b8ccf0e868056a03e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>ac0e652666b3961bdc0201292ff2eb8e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>afe9bb65d9adb45bd57129e1cd9352367</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_DynamicParams</name>
    <filename>struct_i_v_i_d_d_e_c2___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>ac57ff901de30b99b9aa701fb0f330365</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodeHeader</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>abea5bae5ff70e10a2d7010f9bda4d697</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>a858643bd8ae939383b1566a57d38deeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSkipMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>a2981f5f0fb15a6f52bb29a4e85c0eb35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameOrder</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>a03b80fd9ba446f1e5001e9ea9e500719</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>newFrameFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>aab05384e3ca3e7ae577b7feffad8b46d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mbDataFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>a645451aa3f5781816b7d850a4a0f1d80</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_Fxns</name>
    <filename>struct_i_v_i_d_d_e_c2___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___fxns.html</anchorfile>
      <anchor>a51d7618bc466b06f8c8c53bf910cacaf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___fxns.html</anchorfile>
      <anchor>a4ab91427d87c22d67136c65d848de2cf</anchor>
      <arglist>)(IVIDDEC2_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___fxns.html</anchorfile>
      <anchor>aff1ed678af0e3c7794920c5948733922</anchor>
      <arglist>)(IVIDDEC2_Handle handle, IVIDDEC2_Cmd id, IVIDDEC2_DynamicParams *params, IVIDDEC2_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_InArgs</name>
    <filename>struct_i_v_i_d_d_e_c2___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___in_args.html</anchorfile>
      <anchor>aabeef7351fcd66648100d115723118c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___in_args.html</anchorfile>
      <anchor>a061e6d40fc11ea2c9174c20ca4a01da0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___in_args.html</anchorfile>
      <anchor>a6dce78fe6188b7ee5f6f1ca75986f364</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_Obj</name>
    <filename>struct_i_v_i_d_d_e_c2___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDDEC2_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___obj.html</anchorfile>
      <anchor>a1105edcc8ba848020ed15e7414e40766</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_OutArgs</name>
    <filename>struct_i_v_i_d_d_e_c2___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>a46b3e25df2e65f7f80a5c21eec02ad3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>aa67374f1e59de1711f8203995643f989</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>ab1eb379f6d362275660110a30094574e</anchor>
      <arglist>[20]</arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO1_BufDesc</type>
      <name>decodedBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>a08eee7bf1ab385b15753c9b533c9ed1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO1_BufDesc</type>
      <name>displayBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>a2ccb366f52e56f40e6c9daf7907bf1c3</anchor>
      <arglist>[20]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputMbDataID</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>a15e0061a4df48edeb0f32202da60c071</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>mbDataBuf</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>a8ce0694a291539fd42702f1f41fb859c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>freeBufID</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>ab82f6aa7b2be10068fc9ac811c7691da</anchor>
      <arglist>[20]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outBufsInUseFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>a1aaf58c88d9ddfad32419d2e6fd51447</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_Params</name>
    <filename>struct_i_v_i_d_d_e_c2___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>a45489c314fccd6caecaf413141ebdaf4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>a0d61886b3e936242be35a9f8b8869872</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>afb23d618cd7c1651be31d911abc90465</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>af492673482410574e9bc7851e265267f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>ab0df257678abb1d57a16c89207385240</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>ac68e5f9651f085c171a974890da3350d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>ace5541457fd9ecf4ec3a196222090f83</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_Status</name>
    <filename>struct_i_v_i_d_d_e_c2___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a81c8b25dfc840080ea8e8633e1f161b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a259d22a5829769e697b986bc4b8ee7cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>abb374cb803cf489492ef6f45c0a3d29f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxNumDisplayBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a8fa9d26c6e4b19492b509b4be33735f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>abab82bc0d1552fe43a3f8db08262bd58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a8b35ac68f8e49ab93c50f818398714cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a3e4c0a0dc0d49ae4aff5321b037ccd07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a6737984a1ebdc67d112840e6424ccdcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>contentType</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a502ea67283d50ab69057f487ba92a33f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>aad298369668b4cafafe33f0d5adf817d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>ad6c769ede28a7e7a6724ea86da1e20d2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2BACK_Fxns</name>
    <filename>struct_i_v_i_d_d_e_c2_b_a_c_k___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_b_a_c_k___fxns.html</anchorfile>
      <anchor>a24301868fe755edc445f3b19d6387614</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_b_a_c_k___fxns.html</anchorfile>
      <anchor>abee1d2e9a4b63e97cfef3dcea6c8be70</anchor>
      <arglist>)(IVIDDEC2BACK_Handle handle, XDM_Context *context, IVIDDEC2_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_b_a_c_k___fxns.html</anchorfile>
      <anchor>a40034aadeb676ad32f9be5470bb5d49b</anchor>
      <arglist>)(IVIDDEC2BACK_Handle handle, XDM_Context *context, IVIDDEC2_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2BACK_Obj</name>
    <filename>struct_i_v_i_d_d_e_c2_b_a_c_k___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDDEC2BACK_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_b_a_c_k___obj.html</anchorfile>
      <anchor>a73e45c9876cb548abdb45d1d577c1fc2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2FRONT_Fxns</name>
    <filename>struct_i_v_i_d_d_e_c2_f_r_o_n_t___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___fxns.html</anchorfile>
      <anchor>a1da0af3f11e9d2f24b6aa309d7bdbee9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___fxns.html</anchorfile>
      <anchor>afe05e338773c1ad9f0ebef9297a3d1dd</anchor>
      <arglist>)(IVIDDEC2FRONT_Handle handle, IVIDDEC2_InArgs *inArgs, XDM_Context *context, IVIDDEC2FRONT_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___fxns.html</anchorfile>
      <anchor>ab41b180cea576791103366f0b516f620</anchor>
      <arglist>)(IVIDDEC2FRONT_Handle handle, IVIDDEC2_Cmd id, IVIDDEC2_DynamicParams *params, XDM_Context *context, IVIDDEC2FRONT_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2FRONT_Obj</name>
    <filename>struct_i_v_i_d_d_e_c2_f_r_o_n_t___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDDEC2FRONT_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___obj.html</anchorfile>
      <anchor>a21a530d43b07993973e50d16a8a5dc7f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2FRONT_OutArgs</name>
    <filename>struct_i_v_i_d_d_e_c2_f_r_o_n_t___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___out_args.html</anchorfile>
      <anchor>abc4a4d10e3c660d2f4b0aa2ea4214918</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___out_args.html</anchorfile>
      <anchor>a609a5deafeeb993df1fe35181796297f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___out_args.html</anchorfile>
      <anchor>ac1c49e75c61c69bb5fdc3c051760af83</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2FRONT_Status</name>
    <filename>struct_i_v_i_d_d_e_c2_f_r_o_n_t___status.html</filename>
    <member kind="variable">
      <type>XDM_ContextInfo</type>
      <name>contextInfo</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___status.html</anchorfile>
      <anchor>a1838863a9212bc08aa8f1af036dbde7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>nextPartRequiredFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___status.html</anchorfile>
      <anchor>a6b4b87950cf2a84fb1fd62136f96abc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>partialExtendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___status.html</anchorfile>
      <anchor>a2e3560140b3489c4b0ccf5a472591a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDDEC2_Status</type>
      <name>fullStatus</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___status.html</anchorfile>
      <anchor>aeb46aad479a78d7f6de03aa7a81419bc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC3_DynamicParams</name>
    <filename>struct_i_v_i_d_d_e_c3___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___dynamic_params.html</anchorfile>
      <anchor>a2935b2905f1f8c7dbe4294c426419754</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodeHeader</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___dynamic_params.html</anchorfile>
      <anchor>ad0d0900454ff2438659b96ee37226b46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___dynamic_params.html</anchorfile>
      <anchor>aa09174c9a4321f11eec70bc090dfe18b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSkipMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___dynamic_params.html</anchorfile>
      <anchor>a39adaddc481aa3ad9d612ed5e0b7e05e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>newFrameFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___dynamic_params.html</anchorfile>
      <anchor>a84b85b8a21d9d83bf5a9bf534474beef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_DataSyncPutFxn</type>
      <name>putDataFxn</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___dynamic_params.html</anchorfile>
      <anchor>af7fb7b5d55a4387cf782bcc9a8e95c35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_DataSyncHandle</type>
      <name>putDataHandle</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___dynamic_params.html</anchorfile>
      <anchor>adc9c489ed1d891c8a4cb5ab2cbd45720</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_DataSyncGetFxn</type>
      <name>getDataFxn</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___dynamic_params.html</anchorfile>
      <anchor>a8d426348d76fcc2652b5697522e52465</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_DataSyncHandle</type>
      <name>getDataHandle</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___dynamic_params.html</anchorfile>
      <anchor>afd11d304fef5bee08485e7890c5751b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_DataSyncPutBufferFxn</type>
      <name>putBufferFxn</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___dynamic_params.html</anchorfile>
      <anchor>a90f506de1522bbfe53a88dcd8832c92c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_DataSyncHandle</type>
      <name>putBufferHandle</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___dynamic_params.html</anchorfile>
      <anchor>a1c1240c993fcf522c7c1f535b74b1048</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lateAcquireArg</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___dynamic_params.html</anchorfile>
      <anchor>a9e768d633d282978737ca490d3c69538</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC3_Fxns</name>
    <filename>struct_i_v_i_d_d_e_c3___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___fxns.html</anchorfile>
      <anchor>a8a0785d667d5b9e1c4c9c7554aeac69a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___fxns.html</anchorfile>
      <anchor>ae6e77dd3687a0ffc9b697e7cd5827457</anchor>
      <arglist>)(IVIDDEC3_Handle handle, XDM2_BufDesc *inBufs, XDM2_BufDesc *outBufs, IVIDDEC3_InArgs *inArgs, IVIDDEC3_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___fxns.html</anchorfile>
      <anchor>a6578ce467d286efd906fcb88e8fc1355</anchor>
      <arglist>)(IVIDDEC3_Handle handle, IVIDDEC3_Cmd id, IVIDDEC3_DynamicParams *params, IVIDDEC3_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC3_InArgs</name>
    <filename>struct_i_v_i_d_d_e_c3___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___in_args.html</anchorfile>
      <anchor>a87d8a18fe305f76a4ad428fce2c2a06f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___in_args.html</anchorfile>
      <anchor>a4dcd64725ed6e86c448d7c12590ffffd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___in_args.html</anchorfile>
      <anchor>aded67d42aa6fe4631be41abac10cffb5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC3_Obj</name>
    <filename>struct_i_v_i_d_d_e_c3___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDDEC3_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___obj.html</anchorfile>
      <anchor>a94bfff90a0d97f43175817f9e32635e6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC3_OutArgs</name>
    <filename>struct_i_v_i_d_d_e_c3___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___out_args.html</anchorfile>
      <anchor>abf4f29dbcb98587b8f595e3914845bbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___out_args.html</anchorfile>
      <anchor>a04fc8d3ceceb51044119f681250cc664</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___out_args.html</anchorfile>
      <anchor>a0f1cafd500a230c55e28ae9f1971d4b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___out_args.html</anchorfile>
      <anchor>adfdb66ae43ebecde4be7c1f9d372e43a</anchor>
      <arglist>[20]</arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO2_BufDesc</type>
      <name>decodedBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___out_args.html</anchorfile>
      <anchor>a93ac9a64705819644963c29727270ac8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>freeBufID</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___out_args.html</anchorfile>
      <anchor>af65a2b64191b97352af76d0fbddcd104</anchor>
      <arglist>[20]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outBufsInUseFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___out_args.html</anchorfile>
      <anchor>a4165a49c333d66a73200f6bc91c80f3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayBufsMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___out_args.html</anchorfile>
      <anchor>aabe5840661c7c719ea3564ef4a096728</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>union IVIDDEC3_OutArgs::@0</type>
      <name>displayBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___out_args.html</anchorfile>
      <anchor>af969421bdd9f9b8a62ff74a4bed7d5b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO2_BufDesc</type>
      <name>bufDesc</name>
      <anchorfile>union_i_v_i_d_d_e_c3___out_args_1_1@0.html</anchorfile>
      <anchor>af3ff3b9050fa5760558fe536b9e4617f</anchor>
      <arglist>[1]</arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO2_BufDesc *</type>
      <name>pBufDesc</name>
      <anchorfile>union_i_v_i_d_d_e_c3___out_args_1_1@0.html</anchorfile>
      <anchor>a0c1a9e0ae4f5028fe5875e1f3c90c71c</anchor>
      <arglist>[20]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC3_Params</name>
    <filename>struct_i_v_i_d_d_e_c3___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>a93453ab4d68860ff8f31d3dc77564d4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>aecea1b526d00a1dd5c0a561422a99425</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>a9f4e6d15ac581b3d856e0355326bfd7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>a503610a5071744c65bc973bdeb1ab6ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>ad567c5a172160702831f3587ce64346e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>a44a825dff0ea2921280907bf7c77ec9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>ac3a0ac201520113b2ae31697d1fc7186</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>operatingMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>a9fb13e156f470f4e7cb2e36db62988b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayDelay</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>a98638187cec5be17f89d7c80c2839ef2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputDataMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>ad7a08306996e6892a3f41bfd56c31c89</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputDataMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>abda33c68d84aee44461e9e73de6744c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numInputDataUnits</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>abc1aeccc6fb35e891f67f2a13118dca4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numOutputDataUnits</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>a851df38a5b536cfa027c2712bbe13a64</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>errorInfoMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>a73213c70b594535223ff98cdad6578fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayBufsMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>adac6b095e6873439b2430f5ea0a70fb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>metadataType</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___params.html</anchorfile>
      <anchor>a5471912f9770b229b9a27a9f8352c0d5</anchor>
      <arglist>[3]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC3_Status</name>
    <filename>struct_i_v_i_d_d_e_c3___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a9c11cccaf4570f06701c517fe3066fdd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a1de97989025ac20a18a1465713781e1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>adf7362fec88f2f4620a5cd833d3609b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxNumDisplayBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>ab581d7d48fa23c56ea255bf048bb705b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxOutArgsDisplayBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a1fa2fbb73d2f833d85217990949b868b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>afdae56f1af498cca6410e125ad8c9cb0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a22c1c72224ea3be183e9fd0f44302bb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>ae4fbab1acf3b7e30cc5d7f50a68500f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a1e8b40a897cc04af10d708f9669573d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>contentType</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a7fbdbe7ea3decc6000cd1c1d0cc461ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleAspectRatioHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a5728f1000a3ad3f539b9c8265a5c76dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleAspectRatioWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a35eaefeff1cefbb92ee1bca170de8c28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRange</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a996965dcece58bd0d0c90d2a1181e3b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a2f11956d1273778f8bed0a56bb78646e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>operatingMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>af0dcd71c847a811abd269f2c7692775f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameOrder</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>ae7ab2835323976e5cc11061342fba790</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputDataMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>aa125aedbdf43f7b14eab6f3a977b7315</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputDataMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a383fbc4592f77ea0eece9fb1e819e28c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>adefc1fd2f0ee5fb5cbf402869299c451</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numInputDataUnits</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a2b2696ccdd2044241103022eace9a0a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numOutputDataUnits</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>ad612bf207eb37e5cafd8f2c20dfb58ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>configurationID</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>ad851586a0585b6f0d61926a2d7d921d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>metadataType</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a7e57bd7a169816fb5c13d06752746877</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>IVIDDEC3_DynamicParams</type>
      <name>decDynamicParams</name>
      <anchorfile>struct_i_v_i_d_d_e_c3___status.html</anchorfile>
      <anchor>a208b35388119350be3e7aae397a24503</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_DynamicParams</name>
    <filename>struct_i_v_i_d_d_e_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a724d728955f5ff98a352184f302e5c10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodeHeader</name>
      <anchorfile>struct_i_v_i_d_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a52482680b2bbf9c6e1d3853e229fe117</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c___dynamic_params.html</anchorfile>
      <anchor>aab0602030993aaab21f3942b4e6e94cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSkipMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a60f87b60ed218e4d55e6cd8bd4718095</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_Fxns</name>
    <filename>struct_i_v_i_d_d_e_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_d_e_c___fxns.html</anchorfile>
      <anchor>a04451418eb8c2e22322942fb38574cb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_d_e_c___fxns.html</anchorfile>
      <anchor>aafdaab50710b66ee2104d6e1d880a465</anchor>
      <arglist>)(IVIDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDDEC_InArgs *inArgs, IVIDDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_d_e_c___fxns.html</anchorfile>
      <anchor>af1b9b9ead4248c6423841c503f3c0241</anchor>
      <arglist>)(IVIDDEC_Handle handle, IVIDDEC_Cmd id, IVIDDEC_DynamicParams *params, IVIDDEC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_InArgs</name>
    <filename>struct_i_v_i_d_d_e_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c___in_args.html</anchorfile>
      <anchor>a004ff9f5a6272b79b6b6b3dda49b217e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_v_i_d_d_e_c___in_args.html</anchorfile>
      <anchor>a8feea5ef537f4e573d7f23554574f3da</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c___in_args.html</anchorfile>
      <anchor>ab9faa778dc3c1a42a1479ca5968becbf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_Obj</name>
    <filename>struct_i_v_i_d_d_e_c___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDDEC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_d_e_c___obj.html</anchorfile>
      <anchor>aef1a7f4a14b3af6b518bf5d4f9e6f026</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_OutArgs</name>
    <filename>struct_i_v_i_d_d_e_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c___out_args.html</anchorfile>
      <anchor>add17e78667df29acfc52f01822e1583b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c___out_args.html</anchorfile>
      <anchor>afb2c2ed91ffcee062dd75b6a7d59baf5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_v_i_d_d_e_c___out_args.html</anchorfile>
      <anchor>a8c8dad1d10afa49ee7090beaa9189361</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodedFrameType</name>
      <anchorfile>struct_i_v_i_d_d_e_c___out_args.html</anchorfile>
      <anchor>a47d05e2ae2e85e3203882e37a16feeb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c___out_args.html</anchorfile>
      <anchor>ae926f3d3ef8ee7ab71cf82db718bdb7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO_BufDesc</type>
      <name>displayBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c___out_args.html</anchorfile>
      <anchor>a1b92e3bc402ee4b64164d244628a7040</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_Params</name>
    <filename>struct_i_v_i_d_d_e_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>aa4bf340158b515f6ea5e54f7973dfc83</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>a4b9fa2e0c94c60af4adb95c98e545bb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>aa7cb3c68c69b29a7da94c30083ead6b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>a1c578cd3ca486b35919d9c09bd0a9af7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>ac5306a39305dc3eaee2779303207424e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>a09ef5e0e092f4e2fdb29bb96eada7c3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>a500e3b69bc7207b1b4518f8e10e5baa8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_Status</name>
    <filename>struct_i_v_i_d_d_e_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>a749fe221b3a9a9f4e389e5285cdf2653</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>af9734920ddf82abd74ea1e86a7cebf40</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>aea46a001b1af8efa60b5eabea9e04e19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>a1cd8f6470f8aa60ed2a608d0eb8bdbbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>ac44eec0c38b9376bf57c40968e63eaeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>abbb37318036241450b81452584d52734</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>contentType</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>a0f8379a42340c6a1336025f6fd0d0757</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>adda6498f4da63268c0a8f2c06e2d8ee8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>a3973152cbffcb657d1e1117cad17b2c9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_DynamicParams</name>
    <filename>struct_i_v_i_d_e_n_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a489c343510f1fa50f84055e4b7045329</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputHeight</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>ae93a29e557c5d61180159b9c11c0c1d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>ac985fdf2b369f26596edef125ece3be5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>refFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a80ce9bb1e2feb81eeddf0d5d5293ee43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>targetFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>aa9a41d61a27f63f7bdf011636f9371c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>targetBitRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>ad970e1d843d1a76e93999fdafb7fc68a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>intraFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>ae87fe97fc61de6ce3ea4c064b8e79b6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>generateHeader</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a115309d80e5ee49ad12fd2b27d522f09</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>captureWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>aedf2f59085908e721d28ec190d9ce616</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceFrame</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a68e26f9b591fb6a8c65aee114d7e8d18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>interFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a173bb3a21e19964fe0af27ff30e191de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mbDataFlag</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>acf24d69c70907fcb19a8f38407b06daa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_Fxns</name>
    <filename>struct_i_v_i_d_e_n_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___fxns.html</anchorfile>
      <anchor>adc0a1d06f7ae43793ce895562652ec98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___fxns.html</anchorfile>
      <anchor>aa4247d185bc5a015147cfd42f516111d</anchor>
      <arglist>)(IVIDENC1_Handle handle, IVIDEO1_BufDescIn *inBufs, XDM_BufDesc *outBufs, IVIDENC1_InArgs *inArgs, IVIDENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___fxns.html</anchorfile>
      <anchor>a2ed409eed307f42fe7e3aaedbf081f07</anchor>
      <arglist>)(IVIDENC1_Handle handle, IVIDENC1_Cmd id, IVIDENC1_DynamicParams *params, IVIDENC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_InArgs</name>
    <filename>struct_i_v_i_d_e_n_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___in_args.html</anchorfile>
      <anchor>adad9db74820009e7a1621d06e0347ec2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputID</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___in_args.html</anchorfile>
      <anchor>a585d2442323056cdd61f66e196d0658b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>topFieldFirstFlag</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___in_args.html</anchorfile>
      <anchor>a5d4dc8e55e03eb69f035fd7cd26d0c4e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_MbData</name>
    <filename>struct_i_v_i_d_e_n_c1___mb_data.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mbMode</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___mb_data.html</anchorfile>
      <anchor>ad5f71db4894b7c2f4fa27cc1cffaa0af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>QP</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___mb_data.html</anchorfile>
      <anchor>a67f67068f048a8a612c3fe18cd769432</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mvFwdXY</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___mb_data.html</anchorfile>
      <anchor>af081a2b06b14cca3538b4c76633bc8b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mvBwdXY</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___mb_data.html</anchorfile>
      <anchor>ac49f52a1b362799b5e4205aad72d1555</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_Obj</name>
    <filename>struct_i_v_i_d_e_n_c1___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDENC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___obj.html</anchorfile>
      <anchor>a48243d06fe2e480272019fdcf3f8cce2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_OutArgs</name>
    <filename>struct_i_v_i_d_e_n_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a3d278124523dc17b36624e7031aefe25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>ac828cb5ed028e9f244d7497db79ce885</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a5ace229c1e049582f74913572c9b920d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodedFrameType</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a5a4e85d4f0a27de4672aa7aa40553034</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFrameSkip</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>af5881d8a6d39e1feffab343d2609dc25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputID</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a5f5e04e01c1074223f9ab973bb0dfcb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>encodedBuf</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a084284ba0a81fcdd501a1d5c7114cffa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO1_BufDesc</type>
      <name>reconBufs</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a2a8e9941e9f0130bf8ee0b6cb98d655e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_Params</name>
    <filename>struct_i_v_i_d_e_n_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a5ee2d4064a258de5333aefff7596e354</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodingPreset</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>afc35f26f61dbd811d24bc3f79fdf8360</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>rateControlPreset</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a535c201ff37d0dfa730066529ad37f61</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>ac412b8143362fd31738fef01a3186a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a2aedfe4ebbbba9fff8584eba862038e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a836ce8d8ac908c3331ab23cd41169ccb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>aadca2c4e03720839c307b9cc5ef6725c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>ac6bcb7e34fa71e7250bd806b9a3d3842</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxInterFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>ac2c24101728082e7832a1e2bad0a92ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a5b29b3bbe4909783f2b9842f28ff4d99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputContentType</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a0f8ae7b2cbc0465c773186ef1fcad7bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>reconChromaFormat</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a0d38c9a7be268b6ea4fafd8349266bf4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_Status</name>
    <filename>struct_i_v_i_d_e_n_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___status.html</anchorfile>
      <anchor>abf7188f0a82eecbd8f5cf681420dae15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___status.html</anchorfile>
      <anchor>aa4d8b297809354dcd04637def44dcd75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___status.html</anchorfile>
      <anchor>ae8549df00ae60654319529046e88f35e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___status.html</anchorfile>
      <anchor>af759092bb3361da6d7e77505e41c4f71</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC2_DynamicParams</name>
    <filename>struct_i_v_i_d_e_n_c2___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>a2db3842d894eb04b5273f5c004f8cd8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputHeight</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>aea95dba898b3b06a084a8ecbcbc2773a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>a90846a0f3fbbf546640ddbbbe9721292</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>refFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>ab24a2c923e5e48a308e5a6ee749a13c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>targetFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>a4e5716ee30977bb40fa0c1c0aa7695b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>targetBitRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>ae8de0b39eaaa0d993571b3f7c2ddfbef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>intraFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>a98573e80d83377d3890e5d279f18aa8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>generateHeader</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>adb89424162db29b2fe5e45d61ffaf1ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>captureWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>a37b1c998816bebd5a0906b8055704234</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceFrame</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>aafd6b806672a28bf4da58d7117fc8b8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>interFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>a1c3a47c4b44e736465eb149b597c303b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mvAccuracy</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>abd81225d5aab8658fc7ec93cdde90f82</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleAspectRatioHeight</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>ad61d1afeae3dee3843f5b9127e6c8949</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleAspectRatioWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>a7c27ddaa68bb0a58ff12ff79c245b979</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>ignoreOutbufSizeFlag</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>aceda753a13575fbd602b2e0450aafc48</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_DataSyncPutFxn</type>
      <name>putDataFxn</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>a853d9e4034da5996a0e77c6971529e9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_DataSyncHandle</type>
      <name>putDataHandle</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>a15e60c983bc76f50aba35ec10a8e0341</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_DataSyncGetFxn</type>
      <name>getDataFxn</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>adfaec9af763c9212796303bbaf66154d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_DataSyncHandle</type>
      <name>getDataHandle</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>a0378b36aa0b2eb57e94831758df07006</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_DataSyncGetBufferFxn</type>
      <name>getBufferFxn</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>ac9bbac064cbd7e401ee7ead04e93971c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_DataSyncHandle</type>
      <name>getBufferHandle</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>a14fb79f43e01c0e9175f32ed1ff71a6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lateAcquireArg</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___dynamic_params.html</anchorfile>
      <anchor>abaab64f3a31181cd55460394e0bfff5a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC2_Fxns</name>
    <filename>struct_i_v_i_d_e_n_c2___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___fxns.html</anchorfile>
      <anchor>ac59c608d5d890dc840c65eb768fea6f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___fxns.html</anchorfile>
      <anchor>af274944fecaaaa93da7b8d61b547b776</anchor>
      <arglist>)(IVIDENC2_Handle handle, IVIDEO2_BufDesc *inBufs, XDM2_BufDesc *outBufs, IVIDENC2_InArgs *inArgs, IVIDENC2_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___fxns.html</anchorfile>
      <anchor>a30733b5bb8c5940866786c8410b7d1cf</anchor>
      <arglist>)(IVIDENC2_Handle handle, IVIDENC2_Cmd id, IVIDENC2_DynamicParams *params, IVIDENC2_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC2_InArgs</name>
    <filename>struct_i_v_i_d_e_n_c2___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___in_args.html</anchorfile>
      <anchor>aa4f6c716eb674b8f09e2f98e342edb77</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputID</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___in_args.html</anchorfile>
      <anchor>a2eb4a66d465fd367451412270073adac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___in_args.html</anchorfile>
      <anchor>ade09ae795bd2890ef4afef23b1e91567</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC2_Obj</name>
    <filename>struct_i_v_i_d_e_n_c2___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDENC2_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___obj.html</anchorfile>
      <anchor>afb9679ed47252c9f24ff7284186cbe01</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC2_OutArgs</name>
    <filename>struct_i_v_i_d_e_n_c2___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___out_args.html</anchorfile>
      <anchor>a7014b8268c07d9e88a721b00c84e411f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___out_args.html</anchorfile>
      <anchor>acfd19f3bb50d04990cc53f2da42654ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___out_args.html</anchorfile>
      <anchor>a28b9eb53243228d00967d79eb3549d8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodedFrameType</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___out_args.html</anchorfile>
      <anchor>a250a362ea8a40520c207c51081e1f5a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFrameSkip</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___out_args.html</anchorfile>
      <anchor>adec499cc50f334f7a4f547c57a4dbb2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>freeBufID</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___out_args.html</anchorfile>
      <anchor>a0b82c9f83ce8e571041767dd0b868167</anchor>
      <arglist>[20]</arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO2_BufDesc</type>
      <name>reconBufs</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___out_args.html</anchorfile>
      <anchor>ae9f893d7f7e9a5ecf2eb528fd68c3f91</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC2_Params</name>
    <filename>struct_i_v_i_d_e_n_c2___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>a1f349b4b1c672bca1cd51bed23df42af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodingPreset</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>a461bd89fb11b17e553062e21d886139a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>rateControlPreset</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>aa15ae54d5228a223ca2ab9cc47c4d8e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>aceb22c48c3d78161d18bd1f5d81fb37d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>a4ff9c2574da4d64729e347f5854cdbe7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>ab85f7cb28994f562e5a17ac9b8ef695d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxInterFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>a9101e87d0a2a43793b9f4eae24f712ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>a2e9b52e44c02f3505fc7f39287cd09f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minBitRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>aceb8c85851a9730faee4d6157cdabb28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>a0abc319a6139b2244da0b74d7dd23589</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputContentType</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>abca2895408a20344a89368ee7fcf68d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>operatingMode</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>a3c548c4caf4cf138354a30662d71bb16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>profile</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>ac53de2eb9283e4ad4a2bcd247245cca8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>level</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>ad31936c01a98eb947e876f071217db0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputDataMode</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>ada0dcc82ab146b034ecb7521e923226d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputDataMode</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>ae2996b3e0ee87b8e5838fee9abb233ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numInputDataUnits</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>a9450f958e69f445e31a64767bfd662d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numOutputDataUnits</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>ac056fabb0dd1aae0245dab39e9da4dd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>metadataType</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___params.html</anchorfile>
      <anchor>ad039f4a26e28513d783e0ceea2944bee</anchor>
      <arglist>[3]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC2_Status</name>
    <filename>struct_i_v_i_d_e_n_c2___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>a5a97f6c20be2ad69af9e8ad3274e0e9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>adc08bb4385b34e3e6ff0169733c42c88</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>aa7f045977123d1fb42b6775b69844ee3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodingPreset</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>acd481480d8561b27a819e3d6681bedb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>rateControlPreset</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>a2eed293a87eec1313abe4c762ab2963c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxInterFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>af6cefe61688464e44e5f57d00968d2c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>a9a3001376268005c96678c485ef2a21e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputContentType</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>aaa2dec3999ca351aadc0de5652d10f61</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>operatingMode</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>a294a4b0002883410f9de90d52eaa0c8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>profile</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>a62b46c5772f9120649b65f1c9211f898</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>level</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>aa322804ad61c7e47db88e0fb65b96467</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputDataMode</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>a2585a88d66892a2c8826de5ef9651eb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputDataMode</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>ae944b0ffd43765f0693bcaf7d58f294f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numInputDataUnits</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>af242c21812e669487124499752a5d661</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numOutputDataUnits</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>a43e08e60b81135198e85ca0560d74fe7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>configurationID</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>abff744e9d20365e2ab30dfee8fb196fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>a5c1a308a3ff1a2956b520b8e58aa50cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>metadataType</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>ac15e85dd1bcc3d709f5c38ac3c243741</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>IVIDENC2_DynamicParams</type>
      <name>encDynamicParams</name>
      <anchorfile>struct_i_v_i_d_e_n_c2___status.html</anchorfile>
      <anchor>a61b57bbabc4ec4e6bc7fe2b156d3e430</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_DynamicParams</name>
    <filename>struct_i_v_i_d_e_n_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a98eba6b02ca906bfa9d5cbe083540d98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputHeight</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>aa02d428378d4a56c033113bdca825ff6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>ad200571290f2cafa1e612e1d396be378</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>refFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a5b23cf9832abdad3a7ea5f1181961f61</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>targetFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a12d0d0b205549f63da4bb0cc57acd162</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>targetBitRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a5409bcb2aca77a54f0b58d91c145c9b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>intraFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a5f05ef1fa666e0ca5f72a06b0c44c91e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>generateHeader</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>ab66404bf763f5fec96103290666f9df7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>captureWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a80bbc137ed001f8d3b164420c28f8a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceIFrame</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a67945462578816ca2be1b56c58ff48c2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_Fxns</name>
    <filename>struct_i_v_i_d_e_n_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_e_n_c___fxns.html</anchorfile>
      <anchor>ac47a41d81910244f6ab29f526aa52e5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_e_n_c___fxns.html</anchorfile>
      <anchor>a0d97541aab401b55c7f0be829a506c7c</anchor>
      <arglist>)(IVIDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDENC_InArgs *inArgs, IVIDENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_e_n_c___fxns.html</anchorfile>
      <anchor>ad99a6d6ebe14b818a63f179665af98bd</anchor>
      <arglist>)(IVIDENC_Handle handle, IVIDENC_Cmd id, IVIDENC_DynamicParams *params, IVIDENC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_InArgs</name>
    <filename>struct_i_v_i_d_e_n_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c___in_args.html</anchorfile>
      <anchor>a3299ddd3111ebd0fdc00dd72beeff3ec</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_Obj</name>
    <filename>struct_i_v_i_d_e_n_c___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDENC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_e_n_c___obj.html</anchorfile>
      <anchor>a8ef6f8f0b78b70f1460f2c35d540b14e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_OutArgs</name>
    <filename>struct_i_v_i_d_e_n_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c___out_args.html</anchorfile>
      <anchor>afd2cac7f08ba6278452494e4e074398d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_n_c___out_args.html</anchorfile>
      <anchor>a963f9c1107899eb8e4f2ada9e3a87dcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_v_i_d_e_n_c___out_args.html</anchorfile>
      <anchor>a4a9eb44e2d428084879ef1388a8891a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodedFrameType</name>
      <anchorfile>struct_i_v_i_d_e_n_c___out_args.html</anchorfile>
      <anchor>aeca9f172c78c0b54cfcbf7d894abfdb8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFrameSkip</name>
      <anchorfile>struct_i_v_i_d_e_n_c___out_args.html</anchorfile>
      <anchor>a295ded297386d8eee50dce16848a989a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO_BufDesc</type>
      <name>reconBufs</name>
      <anchorfile>struct_i_v_i_d_e_n_c___out_args.html</anchorfile>
      <anchor>a602f9a889f7e7d463cde193c81c22c4c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_Params</name>
    <filename>struct_i_v_i_d_e_n_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>affe3f89977ba6a7919247f9193e002a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodingPreset</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a16a1a6439db8d384752cc2b14d68fadf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>rateControlPreset</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a0a14471207fd0da5611e06e4e6cd8c1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>affa8e31a39d1024ebfac440f3d1b90ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a73fd4b94c772bed243cef7043c1c989a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a995486cb7842251b9c4ba319d9f7e8bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a598111fa7941cfab3a3a66f23510e82f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>aaeb2aea677340d7a2d3bc6c4f5f24d37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxInterFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a1655f549fac120285abd37e0d10d22f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a43d8db5ae1321f4c162a6c2ef3ed98fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputContentType</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a831c15d0ee24f5bac987867e0be5a83e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_Status</name>
    <filename>struct_i_v_i_d_e_n_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c___status.html</anchorfile>
      <anchor>a9cf63fd66da1ba66952919a10d4ea043</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_n_c___status.html</anchorfile>
      <anchor>a1a7bc44c3a862ec9c31588d015bd9be3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_e_n_c___status.html</anchorfile>
      <anchor>a4b60d4421ae14fa616762a0619cc1fa0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDEO1_BufDesc</name>
    <filename>struct_i_v_i_d_e_o1___buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBufs</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a563276f15eadb93140fcc867bd83fbee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameWidth</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a7171c1f434d206bd47bff61ee1ee5ff8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameHeight</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a212f9f5576c65b04f8f469fd4ce722b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>framePitch</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>aea457ad964dcfa2f084cdc79e4d59453</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>bufDesc</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>afc3e2ae20b9c0a073a4c1d6d89248f51</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>ac1287f7d9d947895d000133cd6361c05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameType</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a23b93700f305277b0be3fef34a7c79f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>topFieldFirstFlag</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a0e77f5f253f8a17d41cb35a3dff1866a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>repeatFirstFieldFlag</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a5ba727127a0a4e282de30f7d0cb632b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameStatus</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>ab3363491ad62027696388804cc313f3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>repeatFrame</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a0715059571ff444e1fd8fde93cef1c4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>contentType</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a33e4295bca640fd6550d557aa4a1741a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>chromaFormat</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a057facc459db9fecda02ed1be138f4f2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDEO1_BufDescIn</name>
    <filename>struct_i_v_i_d_e_o1___buf_desc_in.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBufs</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc_in.html</anchorfile>
      <anchor>a4dfd6b4c21298ac7562a5e062bd6d69e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameWidth</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc_in.html</anchorfile>
      <anchor>a7723b31ade67afbe6036e9215dc9f126</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameHeight</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc_in.html</anchorfile>
      <anchor>a46f0d86c006c987569e4d9c730f52fc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>framePitch</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc_in.html</anchorfile>
      <anchor>a7046bea1dcc1731ede9981d1a1515528</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>bufDesc</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc_in.html</anchorfile>
      <anchor>abc19804f6895c76a09f40f9e71001d38</anchor>
      <arglist>[XDM_MAX_IO_BUFFERS]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDEO2_BufDesc</name>
    <filename>struct_i_v_i_d_e_o2___buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numPlanes</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>aad0cd3bc5b2b959a8235b02ebd0d6703</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numMetaPlanes</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a9f3da0d43c74eda2fd6fe94a21f8a0e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataLayout</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>ae91252a8f142cb946fbf71d510ec1739</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM2_SingleBufDesc</type>
      <name>planeDesc</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a268e3032bb231015245af58a674fb9d5</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>XDM2_SingleBufDesc</type>
      <name>metadataPlaneDesc</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a7dd8958ce7916a98fa96f4f3039506b5</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>secondFieldOffsetWidth</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a0ca4deaddf30435e17dcfefd153f5879</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>secondFieldOffsetHeight</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>ab8309841222f0215fa8afb4b6ae41996</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>imagePitch</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a12ac3d60113b7e0f7cb684232155e00d</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>XDM_Rect</type>
      <name>imageRegion</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a617ee02d880cd6f5b0f912e04d7048cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_Rect</type>
      <name>activeFrameRegion</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a35e351384e21e0e508ee62b7a7d4520f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a891c84b9d834bceafdb6e0f41162bba3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameType</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>af133989ddab9818af19df293a9c2d05f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>topFieldFirstFlag</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a4e5acc7170fe0927821c209c08330b21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>repeatFirstFieldFlag</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a2892c5422ca8ca6b4aac42aa4bca61d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameStatus</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a8a946d936d9eecc0b0f970a9d41aedb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>repeatFrame</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>aba8c70fe055aeada747b4cf71491849d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>contentType</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a222ed38644bf8c8e289a7f0361e12272</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>chromaFormat</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a879f722f2c438480dc77f2f54a047dc3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>scalingWidth</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a0c3b765b9aadb5bb70f49fafa5b998dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>scalingHeight</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a38e061f2e78b9ca410cd38578b985d2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>rangeMappingLuma</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>afbdd4518db4cc15fd5f524df45a73585</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>rangeMappingChroma</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a778adcb6961fff8346bb0385bdffc81d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>enableRangeReductionFlag</name>
      <anchorfile>struct_i_v_i_d_e_o2___buf_desc.html</anchorfile>
      <anchor>a3cd93a4f970dfef146b3e050f04f772c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDEO_BufDesc</name>
    <filename>struct_i_v_i_d_e_o___buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBufs</name>
      <anchorfile>struct_i_v_i_d_e_o___buf_desc.html</anchorfile>
      <anchor>a4b573a1cb65d666485d2a03ed17c9e95</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>width</name>
      <anchorfile>struct_i_v_i_d_e_o___buf_desc.html</anchorfile>
      <anchor>a6b6726ea8e06f258d59c649fbf985ce7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int8 *</type>
      <name>bufs</name>
      <anchorfile>struct_i_v_i_d_e_o___buf_desc.html</anchorfile>
      <anchor>a51ee0b81967a3306d3e091fbc81a38a6</anchor>
      <arglist>[XDM_MAX_IO_BUFFERS]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bufSizes</name>
      <anchorfile>struct_i_v_i_d_e_o___buf_desc.html</anchorfile>
      <anchor>a925dd5695afe66711bdc0c3ada614fe2</anchor>
      <arglist>[XDM_MAX_IO_BUFFERS]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_DynamicParams</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a98cc0ea4d936f8c972ddfc84bb225ae5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>readHeaderOnlyFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>aa951419bb5af977888b92936087ebac9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>keepInputResolutionFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a95260da3ba755de635b1950e52d9b67b</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a03b473acd5cb95aeab754a7bcfc6eb03</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a279a4ccdff85f35308292d201e5666cd</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>keepInputFrameRateFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>aa443d68d2d427f97f731a29be6df2705</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFrameRate</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a86851c98010bcfe6e998841a8cb95b51</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputFrameRate</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a52d8329cfee67f5d18d3720b6b0edc62</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>targetBitRate</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a8bb8bfabd89d507e736b1a6b709b2e26</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>rateControl</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a97f553d1d58d3c448120e074fcd71f13</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>keepInputGOPFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a29e3ade6cf84c1e854fe107ca0132366</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>intraFrameInterval</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>aec20f697b5a609fa0bc964121ce97b2d</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>interFrameInterval</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a24900a188335c7dddac1d97bd54ae537</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceFrame</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a53277e5a3b166083d1acea344cb0178d</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSkipTranscodeFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a56851a58acea8a5a5f23e1cedab89fdc</anchor>
      <arglist>[2]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_Fxns</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___fxns.html</anchorfile>
      <anchor>a00a8d6fcd816e541445cbffb7d572d3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___fxns.html</anchorfile>
      <anchor>ae1f9478ee3ed195162e901e41ef4bafc</anchor>
      <arglist>)(IVIDTRANSCODE_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs, IVIDTRANSCODE_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___fxns.html</anchorfile>
      <anchor>abd9deef58e96781eb52b91b4f42dce34</anchor>
      <arglist>)(IVIDTRANSCODE_Handle handle, IVIDTRANSCODE_Cmd id, IVIDTRANSCODE_DynamicParams *params, IVIDTRANSCODE_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_InArgs</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___in_args.html</anchorfile>
      <anchor>a369131f165301ff566f3396265bb89fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___in_args.html</anchorfile>
      <anchor>af9e5ddb4d5b77a1c6641e685c350a61a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputID</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___in_args.html</anchorfile>
      <anchor>a6eb9c1f6eec0cd42a7437915089c2112</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_Obj</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDTRANSCODE_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___obj.html</anchorfile>
      <anchor>aa26c81e61c53a7eb397f6123a5d64d28</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_OutArgs</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a46367326d4ff223657cd42ae7258114a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>ad552ac49e07818ada5b1f9704401dc54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitsConsumed</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a8ba51d9a51c5c47005c80d186d850a30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitsGenerated</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a72ebef4f6a96d7362faf89764c64312d</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodedPictureType</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>adba4f0481ff4679f34ec661f6f8e45bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodedPictureStructure</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a0941d9a0187a7dd27ba8ad367727b3b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodedPictureType</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a30574aaf1af1060d0f4f19dae6a2ae5e</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodedPictureStructure</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a077dcad3cf77db21ced1e679a19792b2</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodedHeight</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a8d0121348bdc359d42d4909e5e3eb793</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodedWidth</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a2b71370ceeda0bf2e4639b5d81ec3ea8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputID</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a5cf133cb2fd5c39b96f0684b4c3e82f4</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFrameSkipTranscodeFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a550034f1df2ec83a894cbefc1718d7e0</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>encodedBuf</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a6c4eaab6595ae3a1c8fba7a42fc0a7f2</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outBufsInUseFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a94bf3a6788838c68e5c7dbe57cbb8a44</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_Params</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a79d39b07d4a8f0818bdd00b97f2684cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numOutputStreams</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a940c0bbd6b0992814a6a2f37742a6b6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>formatInput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a130380061ebff67a68c36f5246b07d9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>formatOutput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a28d64e676cb384be4889d51ad4ff8839</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeightInput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>ae98568eef86ddd44e877f5b5e2cd3ead</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidthInput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a6fe80a4a33170b65865ecae1d4cc5819</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRateInput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a79834d1d0fb5282e84cdb184e284edd2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRateInput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a9c4692f8f6f661904f404ba9049f492b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeightOutput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>afba039a90e6d8b95d8100c0b01300b70</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidthOutput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a902f9dd976de613b662e13659682de6a</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRateOutput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>ae6283acffcb489920bc4e945655c9c40</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRateOutput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>af3369094666dd2eccf50de897cb53e60</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a9bc4dc747100a365d8a6180e128108ff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_Status</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___status.html</anchorfile>
      <anchor>ac25ec58daf95e011c44401d55891adbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___status.html</anchorfile>
      <anchor>a3f577b4e0f0f1b128b46d4d94c7c4d05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___status.html</anchorfile>
      <anchor>a5f558a163c0252362f67b5f8d64cf120</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___status.html</anchorfile>
      <anchor>acf679f7bd2bdd52724e109775b700795</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM1_AlgBufInfo</name>
    <filename>struct_x_d_m1___alg_buf_info.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minNumInBufs</name>
      <anchorfile>struct_x_d_m1___alg_buf_info.html</anchorfile>
      <anchor>afd26a71977977ad6e9e1f617735be297</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minNumOutBufs</name>
      <anchorfile>struct_x_d_m1___alg_buf_info.html</anchorfile>
      <anchor>a84001c41ee6e60e7e1b8b5b3bd1e5967</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM2_BufSize</type>
      <name>minInBufSize</name>
      <anchorfile>struct_x_d_m1___alg_buf_info.html</anchorfile>
      <anchor>ad63e4b42966fd4d6da573db3d28d6cf8</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>XDM2_BufSize</type>
      <name>minOutBufSize</name>
      <anchorfile>struct_x_d_m1___alg_buf_info.html</anchorfile>
      <anchor>a37566e4f929560b15625c381f59a7929</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inBufMemoryType</name>
      <anchorfile>struct_x_d_m1___alg_buf_info.html</anchorfile>
      <anchor>a4dfa3944172ba123318c83d5976a7013</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outBufMemoryType</name>
      <anchorfile>struct_x_d_m1___alg_buf_info.html</anchorfile>
      <anchor>a61b11ffee59b4bf387cceb429fa4c0f3</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minNumBufSets</name>
      <anchorfile>struct_x_d_m1___alg_buf_info.html</anchorfile>
      <anchor>a84cc697960170c77d7e1d01432429b41</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM1_BufDesc</name>
    <filename>struct_x_d_m1___buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBufs</name>
      <anchorfile>struct_x_d_m1___buf_desc.html</anchorfile>
      <anchor>ace565469a1d5d01af34c086777ad0498</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>descs</name>
      <anchorfile>struct_x_d_m1___buf_desc.html</anchorfile>
      <anchor>a8d932c31ffeeb1c11f7345a30f8f0db1</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM1_SingleBufDesc</name>
    <filename>struct_x_d_m1___single_buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int8 *</type>
      <name>buf</name>
      <anchorfile>struct_x_d_m1___single_buf_desc.html</anchorfile>
      <anchor>acd2b309ae89361a09bf3511e45f2f8c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bufSize</name>
      <anchorfile>struct_x_d_m1___single_buf_desc.html</anchorfile>
      <anchor>a138bcbac3e40333ec1983963ba8028cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>accessMask</name>
      <anchorfile>struct_x_d_m1___single_buf_desc.html</anchorfile>
      <anchor>a9795495a0ea10e9c5f9e321b2aa3e3e6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM2_BufDesc</name>
    <filename>struct_x_d_m2___buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBufs</name>
      <anchorfile>struct_x_d_m2___buf_desc.html</anchorfile>
      <anchor>a04d4aac82091a3aaf235f97115fe1e96</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM2_SingleBufDesc</type>
      <name>descs</name>
      <anchorfile>struct_x_d_m2___buf_desc.html</anchorfile>
      <anchor>ad1a111540da79773bc7d34e183ebc729</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="union">
    <name>XDM2_BufSize</name>
    <filename>union_x_d_m2___buf_size.html</filename>
    <member kind="variable">
      <type>struct XDM2_BufSize::@1</type>
      <name>tileMem</name>
      <anchorfile>union_x_d_m2___buf_size.html</anchorfile>
      <anchor>a13aee38379c17d730b7eaef088c195ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>width</name>
      <anchorfile>struct_x_d_m2___buf_size_1_1@1.html</anchorfile>
      <anchor>ae774ce37361fe9f18c738c597b6c1f91</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>height</name>
      <anchorfile>struct_x_d_m2___buf_size_1_1@1.html</anchorfile>
      <anchor>a0bbf8d8bf1ea3377dfa10ec87039568a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytes</name>
      <anchorfile>union_x_d_m2___buf_size.html</anchorfile>
      <anchor>ac66bbf1a2448616742db8ca65450960a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM2_MoveBufDesc</name>
    <filename>struct_x_d_m2___move_buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>id</name>
      <anchorfile>struct_x_d_m2___move_buf_desc.html</anchorfile>
      <anchor>a6c1ad9d227004a5c237ef572ee59d086</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM2_BufDesc</type>
      <name>bufDesc</name>
      <anchorfile>struct_x_d_m2___move_buf_desc.html</anchorfile>
      <anchor>a4d0660175c275005ec568694752c62b6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM2_SingleBufDesc</name>
    <filename>struct_x_d_m2___single_buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int8 *</type>
      <name>buf</name>
      <anchorfile>struct_x_d_m2___single_buf_desc.html</anchorfile>
      <anchor>a5a6cb3b285c58726d378568050b116c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>memType</name>
      <anchorfile>struct_x_d_m2___single_buf_desc.html</anchorfile>
      <anchor>a0149d5abf01e9611ed00fce3977a0e1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>usageMode</name>
      <anchorfile>struct_x_d_m2___single_buf_desc.html</anchorfile>
      <anchor>a45259725516b8dea3cdb55d3ca8d49c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM2_BufSize</type>
      <name>bufSize</name>
      <anchorfile>struct_x_d_m2___single_buf_desc.html</anchorfile>
      <anchor>a2375f95126b7262b4717d3a88c04787b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>accessMask</name>
      <anchorfile>struct_x_d_m2___single_buf_desc.html</anchorfile>
      <anchor>a23403b28fa3db0053828071fc17de201</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_AlgBufInfo</name>
    <filename>struct_x_d_m___alg_buf_info.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minNumInBufs</name>
      <anchorfile>struct_x_d_m___alg_buf_info.html</anchorfile>
      <anchor>adc9062dc88f377394cce8d084f9998af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minNumOutBufs</name>
      <anchorfile>struct_x_d_m___alg_buf_info.html</anchorfile>
      <anchor>a1c0f70a8452105b3684cc01b7f56efc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minInBufSize</name>
      <anchorfile>struct_x_d_m___alg_buf_info.html</anchorfile>
      <anchor>a015d0f09a3e361fa82209fd071133b8e</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minOutBufSize</name>
      <anchorfile>struct_x_d_m___alg_buf_info.html</anchorfile>
      <anchor>ab4074aff4d3b8179e21199390682a76c</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_BufDesc</name>
    <filename>struct_x_d_m___buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int8 **</type>
      <name>bufs</name>
      <anchorfile>struct_x_d_m___buf_desc.html</anchorfile>
      <anchor>aece1843a93b99e6c6451264208dd16ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBufs</name>
      <anchorfile>struct_x_d_m___buf_desc.html</anchorfile>
      <anchor>a3c4b5a0406ad1fab1aa0977de9e8e3a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32 *</type>
      <name>bufSizes</name>
      <anchorfile>struct_x_d_m___buf_desc.html</anchorfile>
      <anchor>a44b447ce14cecf3e17702c82f5ce277d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_Context</name>
    <filename>struct_x_d_m___context.html</filename>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>algContext</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>ada38c0878618615e6acb50e1a1c6b9d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numInBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>a9b0ebd9daf101e296d3f70301874d2b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numOutBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>adf4a68410dd00a7bcbaf11b93a019492</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numInOutBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>ac1d40006838339031a28d03f5fc331cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>inBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>a74044ab712df28a47157e537932a2263</anchor>
      <arglist>[32]</arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>outBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>a9ee540275d6f4680e64625099893d864</anchor>
      <arglist>[32]</arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>inOutBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>a300e622b9d8a7e9ff88e42e684366863</anchor>
      <arglist>[32]</arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>intermediateBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>aa388cac43ec41696b463bd7a004f8e10</anchor>
      <arglist>[32]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_ContextInfo</name>
    <filename>struct_x_d_m___context_info.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minContextSize</name>
      <anchorfile>struct_x_d_m___context_info.html</anchorfile>
      <anchor>af6249efc3c2a1d1ea8f9031888d901a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minIntermediateBufSizes</name>
      <anchorfile>struct_x_d_m___context_info.html</anchorfile>
      <anchor>a2060d35bda9af2ac860bda8eb7774434</anchor>
      <arglist>[32]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_DataSyncDesc</name>
    <filename>struct_x_d_m___data_sync_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_x_d_m___data_sync_desc.html</anchorfile>
      <anchor>ae521a4e352d511f4ad9c814257ede414</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>scatteredBlocksFlag</name>
      <anchorfile>struct_x_d_m___data_sync_desc.html</anchorfile>
      <anchor>a8be3631673bee915794728b52bed0dd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32 *</type>
      <name>baseAddr</name>
      <anchorfile>struct_x_d_m___data_sync_desc.html</anchorfile>
      <anchor>aa93f4370c264dc8d1a65fb8b35e4c6bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBlocks</name>
      <anchorfile>struct_x_d_m___data_sync_desc.html</anchorfile>
      <anchor>ab94f8dcc4aa6d402d0eb66f33f2bc788</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>varBlockSizesFlag</name>
      <anchorfile>struct_x_d_m___data_sync_desc.html</anchorfile>
      <anchor>a8b5bb3c90e4a3581d7eb95fffc6464dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32 *</type>
      <name>blockSizes</name>
      <anchorfile>struct_x_d_m___data_sync_desc.html</anchorfile>
      <anchor>ac3c072d5302e95cd61b0bce0d438c4cf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_Date</name>
    <filename>struct_x_d_m___date.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>msecsOfDay</name>
      <anchorfile>struct_x_d_m___date.html</anchorfile>
      <anchor>a629ae642cdbad0f125be9f1f3b3b519c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>month</name>
      <anchorfile>struct_x_d_m___date.html</anchorfile>
      <anchor>a453fe75a9bcdf0892284b093bd5dde99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dayOfMonth</name>
      <anchorfile>struct_x_d_m___date.html</anchorfile>
      <anchor>a83f49e069389b965d6db9b3797ee86bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dayOfWeek</name>
      <anchorfile>struct_x_d_m___date.html</anchorfile>
      <anchor>a351425bd2fff9f01679941b7c2ef5fde</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>year</name>
      <anchorfile>struct_x_d_m___date.html</anchorfile>
      <anchor>a4e7602f0ebd0bf5282aa61b1efb3b4ec</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_Point</name>
    <filename>struct_x_d_m___point.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>x</name>
      <anchorfile>struct_x_d_m___point.html</anchorfile>
      <anchor>a328754afc6863d3939c5823207c1724c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>y</name>
      <anchorfile>struct_x_d_m___point.html</anchorfile>
      <anchor>ae9b4eb16c8b0f76372b3ce5c219b6e14</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_Rect</name>
    <filename>struct_x_d_m___rect.html</filename>
    <member kind="variable">
      <type>XDM_Point</type>
      <name>topLeft</name>
      <anchorfile>struct_x_d_m___rect.html</anchorfile>
      <anchor>a9ddace330c4514c9282c9b48d5aad7a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_Point</type>
      <name>bottomRight</name>
      <anchorfile>struct_x_d_m___rect.html</anchorfile>
      <anchor>ae59a1d16898d45c5a6f8cfb3e8d3e6f2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_SingleBufDesc</name>
    <filename>struct_x_d_m___single_buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int8 *</type>
      <name>buf</name>
      <anchorfile>struct_x_d_m___single_buf_desc.html</anchorfile>
      <anchor>a0205618de83e9bdf7285a6d449837d27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bufSize</name>
      <anchorfile>struct_x_d_m___single_buf_desc.html</anchorfile>
      <anchor>abebb7b78b54fd5ef3b3414db48245292</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>packages/ti/xdais/dm/</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/</path>
    <filename>dir_adb0356a5afedcffe48f3608230f17ad.html</filename>
    <dir>packages/ti/xdais/dm/split/</dir>
    <file>iauddec.h</file>
    <file>iauddec1.h</file>
    <file>iaudenc.h</file>
    <file>iaudenc1.h</file>
    <file>iaudio.h</file>
    <file>iimgdec.h</file>
    <file>iimgdec1.h</file>
    <file>iimgenc.h</file>
    <file>iimgenc1.h</file>
    <file>ispeech.h</file>
    <file>ispeech1.h</file>
    <file>ispeech1_amr.h</file>
    <file>ispeech1_evrc.h</file>
    <file>ispeech1_g722.h</file>
    <file>ispeech1_g7221.h</file>
    <file>ispeech1_g723.h</file>
    <file>ispeech1_g726.h</file>
    <file>ispeech1_ilbc.h</file>
    <file>ispeech1_pcm.h</file>
    <file>ispeech1_smv.h</file>
    <file>ispeech1_wbamr.h</file>
    <file>isphdec.h</file>
    <file>isphdec1.h</file>
    <file>isphenc.h</file>
    <file>isphenc1.h</file>
    <file>iuniversal.h</file>
    <file>ividanalytics.h</file>
    <file>ividdec.h</file>
    <file>ividdec1.h</file>
    <file>ividdec2.h</file>
    <file>ividdec3.h</file>
    <file>ividenc.h</file>
    <file>ividenc1.h</file>
    <file>ividenc2.h</file>
    <file>ivideo.h</file>
    <file>ividtranscode.h</file>
    <file>xdm.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/</path>
    <filename>dir_f650a7b4a5278f6a28c26c315616e733.html</filename>
    <dir>packages/ti/</dir>
  </compound>
  <compound kind="dir">
    <name>packages/ti/xdais/dm/split/</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/dm/split/</path>
    <filename>dir_b337884439af7fe08ca60c949b152681.html</filename>
    <file>ividdec2.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/</path>
    <filename>dir_123da16bad7097d778602eb7fb9b9596.html</filename>
    <dir>packages/ti/xdais/</dir>
  </compound>
  <compound kind="dir">
    <name>packages/ti/xdais/</name>
    <path>/db/wtree/library/trees/dais/dais-x04/src/xdais_7_24_00_04/packages/ti/xdais/</path>
    <filename>dir_c942bbd581916fdb4d32b4568b9548ac.html</filename>
    <dir>packages/ti/xdais/dm/</dir>
    <file>acpy.h</file>
    <file>acpy2.h</file>
    <file>ialg.h</file>
    <file>idma.h</file>
    <file>idma2.h</file>
    <file>idma3.h</file>
    <file>ires.h</file>
    <file>ires_common.h</file>
    <file>trace.h</file>
    <file>xdas.h</file>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>XDAIS Interface Reference</title>
    <filename>index</filename>
    <docanchor file="index">modules</docanchor>
  </compound>
</tagfile>
