<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>disclaimer.dox</name>
    <path>/db/toolsrc/library/tools/default/doxygen_templates/</path>
    <filename>disclaimer_8dox</filename>
  </compound>
  <compound kind="file">
    <name>doxygen.txt</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/</path>
    <filename>doxygen_8txt</filename>
  </compound>
  <compound kind="file">
    <name>dskt2.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/dskt2/</path>
    <filename>dskt2_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="ires_8h" name="ires.h" local="no" imported="no">ti/xdais/ires.h</includes>
    <member kind="function">
      <type>Void</type>
      <name>DSKT2_activateAlg</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gaf946d426d6d9a95040d3967fa746cd7a</anchor>
      <arglist>(Int scratchMutexId, IALG_Handle alg)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>DSKT2_controlAlg</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga65d8c7ae9d40adcda0c92a9e51c6fd0b</anchor>
      <arglist>(IALG_Handle alg, IALG_Cmd cmd, IALG_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IALG_Handle</type>
      <name>DSKT2_createAlg</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga5528d73c34724bc310404da0dc2fbd69</anchor>
      <arglist>(Int scratchMutexId, IALG_Fxns *fxns, IALG_Handle parent, IALG_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>IALG_Handle</type>
      <name>DSKT2_createAlg2</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga427904cdb1e2a776ee6dfd32c6529682</anchor>
      <arglist>(Int scratchMutexId, IALG_Fxns *fxns, IALG_Handle parent, IALG_Params *params, xdc_runtime_IHeap_Handle extHeapId)</arglist>
    </member>
    <member kind="function">
      <type>IALG_Handle</type>
      <name>DSKT2_createAlgExt</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga6d39f16af2214fafad89ba06382a9a79</anchor>
      <arglist>(Int scratchId, IALG_Fxns *fxns, IALG_Handle parent, IALG_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>DSKT2_deactivateAlg</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga74b6b6feca63328906acade37d23b597</anchor>
      <arglist>(Int scratchMutexId, IALG_Handle alg)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>DSKT2_deactivateAll</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga2d252c736a3bb828d9f646cc379ac0e2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Bool</type>
      <name>DSKT2_freeAlg</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga8dffa02b3ca1ff6856ce3cf610be7435</anchor>
      <arglist>(Int scratchMutexId, IALG_Handle alg)</arglist>
    </member>
    <member kind="function">
      <type>Bool</type>
      <name>DSKT2_allocScratch</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga5aa4fbbf031e07f6bf450128ed8bd31d</anchor>
      <arglist>(IALG_Handle alg, Int mutexId, IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>DSKT2_getScratchId</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga4eda7abcc1ed22cb2183b27290e034b0</anchor>
      <arglist>(IALG_Handle alg)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>DSKT2_freeScratch</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga48fad0ce89b1de7f65adb9a06b4276a0</anchor>
      <arglist>(Int mutexId, Void *addr, UInt size)</arglist>
    </member>
    <member kind="function">
      <type>Bool</type>
      <name>DSKT2_allocPersistent</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga3c37794b3c2fbf0070b473c711e275ca</anchor>
      <arglist>(IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>DSKT2_freePersistent</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga6bc8b2ebbadb2f72325c1b297597fc44</anchor>
      <arglist>(IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DSKT2_NUM_SCRATCH_GROUPS</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga6ea3f0bc0c9a697930cf7d8411975ac2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DSKT2_MAX_MEM_ALLOCATION_SIZE</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gab7906673f1c60a08206bd37c7f7d1178</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DSKT2_NUM_SHAREDHEAPS</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gacb5e98129cb03f61436195c9fd240804</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DSKT2_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga10d952cbb68bf248a0fcb6cc92c6b58e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>DSKT2_CacheWBInvFxn</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga6c3fc2026cef662f1d6b3b80d7eda604</anchor>
      <arglist>)(Ptr blockPtr, size_t byteCnt, Bool wait)</arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ DSKT2_CacheWBInvFxn</type>
      <name>DSKT2_cacheWBInvFxn</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga13251e1daaba43dd400d382dbf0dbc58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_daram0Heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gab7668c1e42befc02a40b6312cf5cadb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_daram1Heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga6fdd0cc306ad1247bace4256312617fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_daram2Heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga35657e20f9076dba1406daef4caa81a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_saram0Heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gae1abc75e1d4b699fc94c500c9d6d9251</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_saram1Heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga4a530ac87148ae36343e0e74acc0e123</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_saram2Heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga0ed925016c6378b654dc9b079fd6e698</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_iprogHeap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga3a675912955b528ba4b0b27dfb2805b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_eprogHeap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga09ad1608c1199fbf9d8a5f3ea351be1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_esdataHeap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga252f21bd5d12a0ff250b09ebea3d2c90</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>_DSKT2_heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga6637aa74e81ac3663dfc1a7dbcf0fa10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ UInt</type>
      <name>_DSKT2_ALLOW_EXTERNAL_SCRATCH</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga5163b360c871f2c8c4e12d6abbb55868</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ UInt</type>
      <name>_DSKT2_DARAM_SCRATCH_SIZES</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gaa1a9d8512d70e7513183736b4e64a27e</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ UInt</type>
      <name>_DSKT2_SARAM_SCRATCH_SIZES</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga7fa8f736c9517857613bab91ccc6f32c</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ Bool</type>
      <name>ti_sdo_fc_dskt2_DSKT2_disableLazyDeactivate</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gaac47654880b79bdf547b27c46361a2cf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>dskt2_qos.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/dskt2/</path>
    <filename>dskt2__qos_8h</filename>
    <member kind="function">
      <type>Void</type>
      <name>DSKT2_QOS_getStat</name>
      <anchorfile>dskt2__qos_8h.html</anchorfile>
      <anchor>a9e737a55019c3dd16fe9bb7313941270</anchor>
      <arglist>(UInt heapType, UInt mutexId, UInt *sizeSharedScratch, xdc_runtime_IHeap_Handle *inHeap)</arglist>
    </member>
    <member kind="typedef">
      <type>enum DSKT2_QOS_TI_MsgArg1Types</type>
      <name>DSKT2_QOS_TI_MsgArg1Types</name>
      <anchorfile>dskt2__qos_8h.html</anchorfile>
      <anchor>a495b1a836c770924c2a0cd9bf97a5329</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum DSKT2_QOS_TI_GetSharedScratchMsgArg2</type>
      <name>DSKT2_QOS_TI_GetSharedScratchMsgArg2</name>
      <anchorfile>dskt2__qos_8h.html</anchorfile>
      <anchor>a76e9bfed31ef5b2c418b02d1a5eed779</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>DSKT2_QOS_TI_MsgArg1Types</name>
      <anchorfile>dskt2__qos_8h.html</anchorfile>
      <anchor>aa4b7cb5a2c0e1b6d0e6d1eed6ded728c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>DSKT2_QOS_TI_GetSharedScratchMsgArg2</name>
      <anchorfile>dskt2__qos_8h.html</anchorfile>
      <anchor>a002e0ce93e06aa89b5e4231f7fd0e683</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ecpy.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/ecpy/</path>
    <filename>ecpy_8h</filename>
    <includes id="ires__edma3_chan_8h" name="ires_edma3Chan.h" local="no" imported="no">ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h</includes>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_configure</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gab36a69debff280508406036c8c998a28</anchor>
      <arglist>(ECPY_Handle handle, ECPY_Params *restrict params, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directConfigure</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gaf0380c28be53fce116f2c56823d61b7e</anchor>
      <arglist>(ECPY_Handle handle, ECPY_Params *restrict params, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_configure16</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga0b7ae91529bc356a3bd81eda9d21a421</anchor>
      <arglist>(ECPY_Handle handle, ECPY_ParamField16b fieldId, unsigned short value, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directConfigure16</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gad27b66a14d13c228eb49b17acbd024aa</anchor>
      <arglist>(ECPY_Handle handle, ECPY_ParamField16b fieldId, unsigned short value, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_configure32</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gaea38193e1199d4a33d4878e916b9b429</anchor>
      <arglist>(ECPY_Handle handle, ECPY_ParamField32b fieldId, unsigned int value, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directConfigure32</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gad46ed17a5d0f1a2a0bc2c7f47aad7fcd</anchor>
      <arglist>(ECPY_Handle handle, ECPY_ParamField32b fieldId, unsigned int value, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_setFinal</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga910393e8b722717de7b84b837adb1921</anchor>
      <arglist>(ECPY_Handle handle, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directSetFinal</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gac377bd43289a832c94c73b20a08c8c26</anchor>
      <arglist>(ECPY_Handle handle, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_setDestinationMemoryMode</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga3101247586aa75cc25a7733c6c4a9679</anchor>
      <arglist>(ECPY_Handle handle, short mode)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_start</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gaf574cd0eabdf2f673009018d7cd3408c</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directStartEdma</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gaf794837c161e60951b4b0c41af37ce1d</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directStartQdma</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gafeab08ae1a1b97bcaa7b207d62df528b</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_wait</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga8adc4be8a9f83b92484dd3aea18d96b1</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directWait</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga0187836c1fb6e00b16741e5daf69308b</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_activate</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gacc1922d7764bb915e1132d955e4b273f</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>ECPY_Handle</type>
      <name>ECPY_createHandle</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gaf27ccab70603cbf148f46a5068a497e0</anchor>
      <arglist>(IRES_EDMA3CHAN2_Handle handle, IALG_Handle alg)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_deleteHandle</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga7d98039c8cea805547bd8ddde71eff6a</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_deactivate</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga06f88eefc91f79ba958d1dee9e7fbb63</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_setEarlyCompletionMode</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga53d14a24649b65b10b817466c7c5b63f</anchor>
      <arglist>(ECPY_Handle handle, short enabled)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_init</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gae699f2d7ac858fecfc83655b3df12037</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_exit</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gade95f79a09ed57206ae1236a23c03764</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ti_sdo_fc_ires_NOPROTOCOLREV</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga33eacaa6cefc41cfe527b740449250dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ECPY_GTNAME</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga20a251dafbbc7b6f6b630d65f95882a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ECPY_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga41a9eb2392433a4d485892a130a1a0f6</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">ECPY_Params</class>
    <class kind="struct">ECPY_CfgParams</class>
    <member kind="typedef">
      <type>enum ECPY_ParamField16b</type>
      <name>ECPY_ParamField16b</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gad6043a14cff5cf11e6124f8ad848e060</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum ECPY_ParamField32b</type>
      <name>ECPY_ParamField32b</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga9a316b6b71fa073d355c25ef48ddf9e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum ECPY_TransferType</type>
      <name>ECPY_TransferType</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga5e69c0ab60fd992aaf644c5dae21a983</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ECPY_Obj *</type>
      <name>ECPY_Handle</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga5e6504458adc98bbbaebfd75c6708add</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ECPY_Params</type>
      <name>ECPY_Params</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga85cefc02e34b1ae7d62fb38564c64422</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Bool(</type>
      <name>ECPY_PersistentAllocFxn</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga083c0fc5d0b23680f4ab5ed6da46c61c</anchor>
      <arglist>)(IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="typedef">
      <type>Void(</type>
      <name>ECPY_PersistentFreeFxn</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gac9814ab64fbb1a77a7cc3f267b6a46fb</anchor>
      <arglist>)(IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="typedef">
      <type>Bool(</type>
      <name>ECPY_ScratchAllocFxn</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga98a6fb304f763c2ff1f4d0a99dc1ec1a</anchor>
      <arglist>)(IALG_Handle alg, Int scratchId, IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="typedef">
      <type>Void(</type>
      <name>ECPY_ScratchFreeFxn</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gad4c1411f84b9db63eae9eb41c2068f4b</anchor>
      <arglist>)(Int mutexId, Void *addr, UInt size)</arglist>
    </member>
    <member kind="typedef">
      <type>Int(</type>
      <name>ECPY_getScratchIdFxn</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gab83b6cb5f227392f82a4799278c2ec4c</anchor>
      <arglist>)(IALG_Handle alg)</arglist>
    </member>
    <member kind="typedef">
      <type>struct ECPY_CfgParams</type>
      <name>ECPY_CfgParams</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga54c1cdb98daaa54a05871b834f02037c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ECPY_ParamField16b</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga7d9083dd908144dea99d282b5e4c8b13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ECPY_ParamField32b</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga59f221145cdc648d305f9c2d49ec2f87</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ECPY_TransferType</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga263a661327490e9f8226271c6f478011</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ ECPY_CfgParams</type>
      <name>ECPY_CFG_PARAMS</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gabcc5234b3b928c407413afc3aa15a92b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>edmamgr.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/edmamgr/</path>
    <filename>edmamgr_8h</filename>
    <includes id="ecpy_8h" name="ecpy.h" local="no" imported="no">ti/sdo/fc/ecpy/ecpy.h</includes>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="ires_8h" name="ires.h" local="no" imported="no">ti/xdais/ires.h</includes>
    <includes id="ires__edma3_chan_8h" name="ires_edma3Chan.h" local="no" imported="no">ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h</includes>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_init</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga34b0b3947862ffadce6244b1b2e9bd95</anchor>
      <arglist>(int32_t proc_id, void *edma3_config)</arglist>
    </member>
    <member kind="function">
      <type>EdmaMgr_Handle</type>
      <name>EdmaMgr_alloc</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaf0294a961780a183c7b87ab00bf397d7</anchor>
      <arglist>(int32_t max_linked_transfers)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_getSizesLarge</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga91b956aa648a04f38f3be9d970f6e584</anchor>
      <arglist>(EdmaMgr_ConfigLarge *cfg, IALG_MemRec memTab[])</arglist>
    </member>
    <member kind="function">
      <type>EdmaMgr_Handle</type>
      <name>EdmaMgr_allocLarge</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gabc2860d277c3aeed80d895a679d8eb19</anchor>
      <arglist>(EdmaMgr_ConfigLarge *cfg, IALG_MemRec memTab[])</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_free</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaf4bd48f313ef582613d90a5081963b4d</anchor>
      <arglist>(EdmaMgr_Handle h)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_hwFreeAll</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga52575ab5ae053dcb10c60a5250399d79</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_hwAllocAll</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaa904519337f6802670ea7148a1e0198c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EdmaMgr_wait</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga4195deee760b9295f9805dfe89488f0b</anchor>
      <arglist>(EdmaMgr_Handle h)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy1D1D</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga505e955ac44bbe71bd1e3daab1ea0b2f</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy1D2D</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga875d6e42712a08d57b250a150287e19f</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes, int32_t num_lines, int32_t pitch)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D1D</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga89dfe4a866ec36f8b7adea8b4a5394de</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes, int32_t num_lines, int32_t pitch)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D2D</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga8888b3b0af91f51ad0c3549d7b3a8cce</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes, int32_t num_lines, int32_t pitch)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D2DSep</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gae6633520a0b320b377b5b033cc141c5c</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes, int32_t num_lines, int32_t src_pitch, int32_t dst_pitch)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy1D1DLinked</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gab68d6b8da1b15f9824f510a779a726ce</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src[], void *restrict dst[], int32_t num_bytes[], int32_t num_transfers)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy1D2DLinked</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaa0686f84566bf694809e5389a511a9f8</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src[], void *restrict dst[], int32_t num_bytes[], int32_t num_lines[], int32_t pitch[], int32_t num_transfers)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D1DLinked</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga788194a05f15b3f2ea2c619d469d0194</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src[], void *restrict dst[], int32_t num_bytes[], int32_t num_lines[], int32_t pitch[], int32_t num_transfers)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D2DLinked</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaf45b4c568858e438198ca56f6f5737a1</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src[], void *restrict dst[], int32_t num_bytes[], int32_t num_lines[], int32_t pitch[], int32_t num_transfers)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D2DSepLinked</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga5cf14039980959b3dac0af544d3adeef</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src[], void *restrict dst[], int32_t num_bytes[], int32_t num_lines[], int32_t src_pitch[], int32_t dst_pitch[], int32_t num_transfers)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy1D2DLarge</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga07c5095814d61fe51d9293aded7e9233</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes, int32_t num_lines, int32_t pitch)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D1DLarge</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga971ca76b7244813602ab33412b8de285</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes, int32_t num_lines, int32_t pitch)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copyFast</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga6aebdb61c28a58f0e63f03fce243ba9d</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copyLinkedFast</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga9cbf51d816c26038cbc11e3b63b8fd31</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src[], void *restrict dst[], int32_t num_transfers)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_SUCCESS</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaa8024d7e4cec1168dff2cb1ef7e9962f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_ERROR_INVARG</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga16c73229c0977d6a712c854bc7a81c36</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_ERROR_INVCFG</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga1de726847679ee71afd50006d878185e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_ERROR_RMANINIT</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga0d07816b60be478a71c08f4d1fde9bcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_ERROR_INVHANDLE</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gad2c98139c17fa8698697129e14d8dc7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_ERROR_FREE</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga547518dd36d8c845f7dfbd75fa7d5a96</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_MAX_NUM_MEMRECS_LARGE</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaa29f173a399a3b514c608c40b375d1af</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">_EdmaMgr_ConfigLarge</class>
    <member kind="typedef">
      <type>void *</type>
      <name>EdmaMgr_Handle</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gad100f526edd5ac876ba81ae8a78d4e00</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct _EdmaMgr_ConfigLarge</type>
      <name>EdmaMgr_ConfigLarge</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga7d68c85b3f0cba1c17fcb223ef89a9a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ialg.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/fctools/packages/ti/xdais/</path>
    <filename>ialg_8h</filename>
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
    <class kind="struct">IALG_MemRec</class>
    <class kind="struct">IALG_Obj</class>
    <class kind="struct">IALG_Params</class>
    <class kind="struct">IALG_Status</class>
    <class kind="struct">IALG_Fxns</class>
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
      <type></type>
      <name>IALG_MemAttrs</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga805f1c1330403c05633277a073862e3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IALG_MemSpace</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga262eb64dc7343999fa07d535ae163497</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ires.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/fctools/packages/ti/xdais/</path>
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
      <anchor>ga75c11dac719363507ceb70374f72aacc</anchor>
      <arglist>)(IALG_Handle algHandle, Void *contextArgs)</arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>IRES_ContextRestoreFxn</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga6efda82d9cbe44a6badad08c0807d07b</anchor>
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
      <anchor>ga138778ff0e07cfa1dd96c20e5168a776</anchor>
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
      <type></type>
      <name>IRES_YieldResourceType</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga9a68e109e02bf3f35e832ec4f767d0a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ires_common.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/fctools/packages/ti/xdais/</path>
    <filename>ires__common_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="yes" imported="no">ialg.h</includes>
    <class kind="struct">IRES_ProtocolRevision</class>
    <class kind="struct">IRES_ProtocolArgs</class>
    <class kind="struct">IRES_ResourceDescriptor</class>
    <class kind="struct">IRES_Properties</class>
    <class kind="struct">IRES_Obj</class>
    <member kind="enumeration">
      <type></type>
      <name>IRES_Status</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga8db6eab013fc4569e080cb4361dfd65b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_RequestMode</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga67d435865304c7bce199194e7ff07963</anchor>
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
    <name>ires_edma3Chan.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/ires/edma3chan/</path>
    <filename>ires__edma3_chan_8h</filename>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="ires__common_8h" name="ires_common.h" local="no" imported="no">ti/xdais/ires_common.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_PROTOCOLNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gaf4730270fcd589bd84292642aa0767ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EDMA3CHAN_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gab7814ae21cc501d4882aaeb43153fc0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_PROTOCOLREVISION_1_0_0</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga3e72cddac269ede3215c67681bd06358</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_SETPROTOCOLREVISION_1_0_0</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gabc9fa9788be85eddc9696b9a778270c9</anchor>
      <arglist>(rev)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_PROTOCOLREVISION_2_0_0</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gafaf0878b09c1cc9708821d19d801e182</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_SETPROTOCOLREVISION_2_0_0</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga13b7ccd6e711b7469b8823a5c957b536</anchor>
      <arglist>(rev)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_MAXPARAMS</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga8510375de41242e3526a4afa007e131a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_MAXTCCS</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga18eb05e3510d748f04269c39cce62733</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_NUMDESTTYPES</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gadb7b5e24785c0749d8717e0d740ebdd4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_PARAM_ANY</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga2b610a75bc94fcf953c9c2c5a5884847</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_PARAM_NONE</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga06bed242a94eb48126e04f267f0d4895</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_TCC_ANY</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga3dad6458e12ad42c2158727991822037</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_TCC_NONE</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga1920c58bedf3e0cc0609b86ec384c892</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_EDMACHAN_ANY</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gae3c157030381908d1353fccf406fdd38</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_QDMACHAN_ANY</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga0b99333ee5984dab27d5d84c05b63078</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_CHAN_NONE</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gae4140c679d6eaaf4d20dc4554995edf3</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRES_EDMA3CHAN_PaRamStruct</class>
    <class kind="struct">IRES_EDMA3CHAN_ProtocolArgs</class>
    <class kind="struct">IRES_EDMA3CHAN_Obj</class>
    <class kind="struct">IRES_EDMA3CHAN_EDMA3ShadowRegister</class>
    <class kind="struct">IRES_EDMA3CHAN_EDMA3DraeRegister</class>
    <class kind="struct">IRES_EDMA3CHAN_EDMA3RegisterLayer</class>
    <class kind="struct">IRES_EDMA3CHAN_Properties</class>
    <class kind="struct">IRES_EDMA3CHAN2_Obj</class>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_Obj *</type>
      <name>IRES_EDMA3CHAN_Handle</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga44e66cb70f336bdb105e54983930c8e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN2_Obj *</type>
      <name>IRES_EDMA3CHAN2_Handle</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gac7ec31fb6115f2df8b43f0a66d3bb09f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_PaRamStruct</type>
      <name>IRES_EDMA3CHAN_PaRamStruct</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga3d1f7dd722d7b1eac3940a6d0eff63c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_ProtocolArgs</type>
      <name>IRES_EDMA3CHAN_ProtocolArgs</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga4f0e8e331a7135fa21c62da8e1d3fced</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_Obj</type>
      <name>IRES_EDMA3CHAN_Obj</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga8910a3fc26939a5f592191fb4400d0d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_EDMA3ShadowRegister</type>
      <name>IRES_EDMA3CHAN_EDMA3ShadowRegister</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gaa2977a19f877b1d3cf7538c3457db58d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_EDMA3DraeRegister</type>
      <name>IRES_EDMA3CHAN_EDMA3DraeRegister</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga0a01c3ca97f02a526edb0360eff504ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_EDMA3RegisterLayer</type>
      <name>IRES_EDMA3CHAN_EDMA3RegisterLayer</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga2ceee1967c04a37f016e0184b5f6040d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_Properties</type>
      <name>IRES_EDMA3CHAN_Properties</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga271d231160ea9cf90f4387b7aecfb34e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_EDMA3CHAN_DmaDestType</type>
      <name>IRES_EDMA3CHAN_DmaDestType</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gaa2c61cb7db74a0e2cef3e3c66c383b68</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN2_Obj</type>
      <name>IRES_EDMA3CHAN2_Obj</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga5734d8411fde66f0d75892044293e9f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_EDMA3CHAN_DmaDestType</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga6cbd16008d4c8eb007e03412b12fc778</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ires_hdvicp.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/ires/hdvicp/</path>
    <filename>ires__hdvicp_8h</filename>
    <includes id="ires__common_8h" name="ires_common.h" local="no" imported="no">ti/xdais/ires_common.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP_PROTOCOLNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>gaf41453e3afb59b32d1a0c41961fe50a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HDVICP_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>gab17613f289eb3239624de87c31d57116</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRES_HDVICP_ProtocolArgs</class>
    <class kind="struct">IRES_HDVICP_Obj</class>
    <class kind="struct">IRES_HDVICP_RegisterLayer</class>
    <class kind="struct">IRES_HDVICP_Properties</class>
    <member kind="typedef">
      <type>struct IRES_HDVICP_Obj *</type>
      <name>IRES_HDVICP_Handle</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>gafcb53c4662e46499ee68c7dfad662bfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_HDVICP_RequestType</type>
      <name>IRES_HDVICP_RequestType</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga4019a15f38f2854f0e52f457d724449b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP_ProtocolArgs</type>
      <name>IRES_HDVICP_ProtocolArgs</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga0aeea51623159606d5bc6a7a15ed4043</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP_Obj</type>
      <name>IRES_HDVICP_Obj</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>gad85f85ba4b0fdaf7cf9e8921cad229fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP_RegisterLayer</type>
      <name>IRES_HDVICP_RegisterLayer</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga36d6cd1fdd8c0a88840e5b6af0fabd0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP_Properties</type>
      <name>IRES_HDVICP_Properties</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga7a41d6c63373b559c3fc5ee90280d4ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_HDVICP_RequestType</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga995d4dd1dfb80daa5eb01690cc33cc7f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ires_hdvicp2.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/ires/hdvicp/</path>
    <filename>ires__hdvicp2_8h</filename>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="ires__common_8h" name="ires_common.h" local="no" imported="no">ti/xdais/ires_common.h</includes>
    <includes id="ires_8h" name="ires.h" local="no" imported="no">ti/xdais/ires.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP2_PROTOCOLNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga6e9fc2b0904862eb35cf23ec5d06fd31</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HDVICP2_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga9c465c385b96523dd172495898a2a648</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP2_ID_ANY</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga5036e671af0585ea57d8e0197e4e90ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP2_ID_LATE_ACQUIRE</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga64e2059f8468faeac050da0d3db026f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP2_INVALID_ADDR</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga58cf2d89d0831f062da6b1392dc2630a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP2_TIMEOUTFOREVER</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga02602060d994d0ee40fade0f38475687</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP2_UNKNOWNLATEACQUIREARG</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga89573d4d420b01f3b2c3bedb20e52dab</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRES_HDVICP2_ProtocolArgs</class>
    <class kind="struct">IRES_HDVICP2_Obj</class>
    <class kind="struct">IRES_HDVICP2_RegisterLayer</class>
    <class kind="struct">IRES_HDVICP2_Properties</class>
    <member kind="typedef">
      <type>struct IRES_HDVICP2_Obj *</type>
      <name>IRES_HDVICP2_Handle</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>gadd0f77cea05c41ade2f2f6c29937eb7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IRES_YieldArgs(*</type>
      <name>ti_sdo_fc_ires_hdvicp_HDVICP2_GetYieldArgsFxn</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga983c2886f86746cf7d0d428e3474c916</anchor>
      <arglist>)(Int scratchId)</arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>ti_sdo_fc_ires_hdvicp_HDVICP2_YieldFxn</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga5f7f18c485cdc75a0fb2f225edf9dcd1</anchor>
      <arglist>)(IRES_YieldResourceType resource, IRES_YieldContextHandle ctxt, IRES_YieldArgs args)</arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP2_ProtocolArgs</type>
      <name>IRES_HDVICP2_ProtocolArgs</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga01d21d4eea4b38bba75890a474f5e146</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>IRES_HDVICP2_CallbackFxn</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga4f26754ef203eaeece311f2695dcbe6a</anchor>
      <arglist>)(IALG_Handle handle, Void *args)</arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_HDVICP2_Status</type>
      <name>IRES_HDVICP2_Status</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga4d0929cc91ef9058c626bc3f8eb5a580</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP2_Obj</type>
      <name>IRES_HDVICP2_Obj</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>gab164d36df22fa1187459bf656fb41f83</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP2_RegisterLayer</type>
      <name>IRES_HDVICP2_RegisterLayer</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>gab207e5ba3c1be67f41aca898cd1af06c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP2_Properties</type>
      <name>IRES_HDVICP2_Properties</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga347620d5e79bdf4a441045fe9a5efc21</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IRES_Status(*</type>
      <name>ti_sdo_fc_ires_hdvicp_HDVICP2_GetHdvicp2Fxn</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga4145e66e0498a362506bc9994136d1eb</anchor>
      <arglist>)(XDAS_Int32 *Id, IALG_Handle alg, IRES_HDVICP2_Handle handle)</arglist>
    </member>
    <member kind="typedef">
      <type>IRES_Status(*</type>
      <name>ti_sdo_fc_ires_hdvicp_HDVICP2_FreeHdvicp2Fxn</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga52891d16a972bf3795668fce2a069537</anchor>
      <arglist>)(XDAS_Int32 Id, IALG_Handle alg, IRES_HDVICP2_Handle handle)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_HDVICP2_Status</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga918fdab9a544c5ffcc1e76117d0f79f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>ti_sdo_fc_ires_hdvicp_HDVICP2_timeoutVal</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga5b423e92e03fa325059695a892b2af42</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ires_tiledmemory.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/ires/tiledmemory/</path>
    <filename>ires__tiledmemory_8h</filename>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="ires__common_8h" name="ires_common.h" local="no" imported="no">ti/xdais/ires_common.h</includes>
    <includes id="ires_8h" name="ires.h" local="no" imported="no">ti/xdais/ires.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>IRES_TILEDMEMORY_PROTOCOLNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga68b4b8898e77e090fd96541494fa6422</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TILEDMEMORY_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga623d30fd5f51a591fb1d7ba6bedd0dab</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRES_TILEDMEMORY_ProtocolArgs</class>
    <class kind="struct">IRES_TILEDMEMORY_Obj</class>
    <class kind="struct">IRES_TILEDMEMORY_RegisterLayer</class>
    <class kind="struct">IRES_TILEDMEMORY_Properties</class>
    <member kind="typedef">
      <type>struct IRES_TILEDMEMORY_Obj *</type>
      <name>IRES_TILEDMEMORY_Handle</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga30b122a78fafc18f16f4b584c55ddf39</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_TILEDMEMORY_AccessDimension</type>
      <name>IRES_TILEDMEMORY_AccessDimension</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gaa6cd7292c7e04c77735f0d9b2c0e6a47</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_TILEDMEMORY_AccessUnit</type>
      <name>IRES_TILEDMEMORY_AccessUnit</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga9a4638e18510604f93bafbaac2d85917</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_TILEDMEMORY_ProtocolArgs</type>
      <name>IRES_TILEDMEMORY_ProtocolArgs</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga87e40295a0e896827ff16239c6677182</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_TILEDMEMORY_Obj</type>
      <name>IRES_TILEDMEMORY_Obj</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga7bd47c3771425981890d1973719bc4e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_TILEDMEMORY_RegisterLayer</type>
      <name>IRES_TILEDMEMORY_RegisterLayer</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gae5bceac65ea5bf226b3985d0a45703a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_TILEDMEMORY_Properties</type>
      <name>IRES_TILEDMEMORY_Properties</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga3a240a3b912b366e5925b5d4348fe2cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_TILEDMEMORY_AccessDimension</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga6bf19883a3a359c69a7a7cc98b9fb974</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_TILEDMEMORY_AccessUnit</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gac19627dfd380195372144adab80be234</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ires_vicp.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/ires/vicp/</path>
    <filename>ires__vicp_8h</filename>
    <includes id="ires__common_8h" name="ires_common.h" local="no" imported="no">ti/xdais/ires_common.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>IRES_VICP_MAXRESOURCES</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>gab443b20263d6d15d38353016d2caef35</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_VICP_PROTOCOLNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>ga8f238b30de8eb64ef69362f215837eb0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VICP_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>ga6ed720f53f0ec97580795ac36998cc32</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRES_VICP_ProtocolArgs</class>
    <class kind="struct">IRES_VICP_Obj</class>
    <class kind="struct">IRES_VICP_Registers</class>
    <class kind="struct">IRES_VICP_Properties</class>
    <member kind="typedef">
      <type>struct IRES_VICP_Obj *</type>
      <name>IRES_VICP_Handle</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>gaa23fbe3626f54ecc7754e908083f5f14</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_VICP_ProtocolArgs</type>
      <name>IRES_VICP_ProtocolArgs</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>ga6b0466ea2e923232a5f2bf5d99b83663</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_VICP_Obj</type>
      <name>IRES_VICP_Obj</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>ga78dd89d90d8364d4ff126b4647228819</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_VICP_Registers</type>
      <name>IRES_VICP_Registers</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>ga12d9b10adf3be5345c5acf16def14707</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_VICP_Properties</type>
      <name>IRES_VICP_Properties</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>gad8355b5acd95ef810245a947c87a3847</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iresman.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/ires/</path>
    <filename>iresman_8h</filename>
    <includes id="ires__common_8h" name="ires_common.h" local="no" imported="no">ti/xdais/ires_common.h</includes>
    <includes id="ires_8h" name="ires.h" local="no" imported="no">ti/xdais/ires.h</includes>
    <class kind="struct">IRESMAN_Params</class>
    <class kind="struct">IRESMAN_Fxns</class>
    <member kind="typedef">
      <type>Bool(</type>
      <name>IRESMAN_PersistentAllocFxn</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>gace2b51f833e4570240469eb3a379ff96</anchor>
      <arglist>)(IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="typedef">
      <type>Void(</type>
      <name>IRESMAN_PersistentFreeFxn</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>ga99674bfeffe75b236ebe916e4f588237</anchor>
      <arglist>)(IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="typedef">
      <type>struct IRESMAN_Params</type>
      <name>IRESMAN_Params</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>ga2a8b6374104f86177742127e0e9db690</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRESMAN_Fxns</type>
      <name>IRESMAN_Fxns</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>ga3ccaac5d069a8c8d1f136c29bf3cbeb0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iresman_edma3Chan.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/ires/edma3chan/</path>
    <filename>iresman__edma3_chan_8h</filename>
    <includes id="iresman_8h" name="iresman.h" local="no" imported="no">ti/sdo/fc/ires/iresman.h</includes>
    <includes id="iresman__protocol_8h" name="iresman_protocol.h" local="no" imported="no">ti/sdo/fc/ires/iresman_protocol.h</includes>
    <member kind="function">
      <type>String</type>
      <name>IRESMAN_EDMA3CHAN_getProtocolName</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gaeb774220d0deb5da8bbfe8aa25c15094</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_ProtocolRevision *</type>
      <name>IRESMAN_EDMA3CHAN_getProtocolRevision</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga695084a1271cf138b383a2a7c42e1e20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_EDMA3CHAN_init</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga941b3ff64286bcfaa3bb5205bb669d55</anchor>
      <arglist>(IRESMAN_Params *initArgs)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_EDMA3CHAN_exit</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gac67268cf9b8f5bf523caffebfe8dc148</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Handle</type>
      <name>IRESMAN_EDMA3CHAN_getHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gad30ebcbc0fed976c39cdf716677b2080</anchor>
      <arglist>(IALG_Handle algHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId, IRES_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_EDMA3CHAN_freeHandle</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gabd5e4de994bdaf06fe5a45f5c41fe265</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Handle algResourceHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId)</arglist>
    </member>
    <class kind="struct">IRESMAN_Edma3ChanParams</class>
    <member kind="typedef">
      <type>struct IRESMAN_Edma3ChanParams</type>
      <name>IRESMAN_Edma3ChanParams</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga6f72d404957e3bde256dab036a6ee460</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentAllocFxn</type>
      <name>_RMAN_allocPersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gaadc2b94c8a7fe6dd08fcc18deec7d992</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentFreeFxn</type>
      <name>_RMAN_freePersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga0c23ac2d5d2854f5941c0b3098790df1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRESMAN_Fxns</type>
      <name>IRESMAN_EDMA3CHAN</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga7fb20979fe105a5310a48f2b2ccaf8c4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iresman_hdvicp.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/ires/hdvicp/</path>
    <filename>iresman__hdvicp_8h</filename>
    <includes id="iresman_8h" name="iresman.h" local="no" imported="no">ti/sdo/fc/ires/iresman.h</includes>
    <member kind="function">
      <type>String</type>
      <name>IRESMAN_HDVICP_getProtocolName</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga263a6e5378a5a80ec72cbe1e1996d4e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_ProtocolRevision *</type>
      <name>IRESMAN_HDVICP_getProtocolRevision</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga1e6757007676bb59bc49b976c7082d68</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_HDVICP_init</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga9b2d49524494e6c589a17b8d3f6e2b83</anchor>
      <arglist>(IRESMAN_Params *initArgs)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_HDVICP_exit</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga66e789620a153083717fe8b73f576ad8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Handle</type>
      <name>IRESMAN_HDVICP_getHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga91dcd1ec36206aeb58649b7361d7904b</anchor>
      <arglist>(IALG_Handle algHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId, IRES_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_HDVICP_freeHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga8082e13e6d0f726991c2e78659f7d82c</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Handle algResourceHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP_MAXRESOURCES</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga626db578ddcda783f8354c734b51a876</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRESMAN_HdVicpParams</class>
    <member kind="typedef">
      <type>struct IRESMAN_HdVicpParams</type>
      <name>IRESMAN_HdVicpParams</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>gaa0cc26209d78b2914c0353319983e7b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentAllocFxn</type>
      <name>_RMAN_allocPersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>gaadc2b94c8a7fe6dd08fcc18deec7d992</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentFreeFxn</type>
      <name>_RMAN_freePersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga0c23ac2d5d2854f5941c0b3098790df1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRESMAN_Fxns</type>
      <name>IRESMAN_HDVICP</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga3f269556325eb4b7ac1b7aad594e3f6c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iresman_protocol.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/ires/</path>
    <filename>iresman__protocol_8h</filename>
    <includes id="ires__common_8h" name="ires_common.h" local="no" imported="no">ti/xdais/ires_common.h</includes>
    <class kind="struct">IRESMAN_ConstructArgs</class>
    <class kind="struct">IRESMAN_ConstructFxns</class>
    <member kind="typedef">
      <type>struct IRESMAN_ConstructArgs</type>
      <name>IRESMAN_ConstructArgs</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>ga93fe96948b8c064f1244daae12abba54</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRESMAN_ConstructFxns</type>
      <name>IRESMAN_ConstructFxns</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>gab9da36e13f19c05d045611d22e23f184</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRESMAN_ConstructArgs</type>
      <name>IRESMAN_ConstructArgs</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>ga93fe96948b8c064f1244daae12abba54</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRESMAN_ConstructFxns</type>
      <name>IRESMAN_ConstructFxns</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>gab9da36e13f19c05d045611d22e23f184</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iresman_tiledmemory.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/ires/tiledmemory/</path>
    <filename>iresman__tiledmemory_8h</filename>
    <includes id="iresman_8h" name="iresman.h" local="no" imported="no">ti/sdo/fc/ires/iresman.h</includes>
    <member kind="function">
      <type>String</type>
      <name>IRESMAN_TILEDMEMORY_getProtocolName</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gabea58ade569b614d4b8c55f455ea2833</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_ProtocolRevision *</type>
      <name>IRESMAN_TILEDMEMORY_getProtocolRevision</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga4832f10ae177316cf1e73a29c6713531</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_TILEDMEMORY_init</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gaf0587262c783dfdf65faaaf6eea0807a</anchor>
      <arglist>(IRESMAN_Params *initArgs)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_TILEDMEMORY_exit</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga9415a0ced325b5467295b8771e52d304</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Handle</type>
      <name>IRESMAN_TILEDMEMORY_getHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gadfa289400bc20009f0a0758bc7087aea</anchor>
      <arglist>(IALG_Handle algHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId, IRES_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_TILEDMEMORY_freeHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gac62245768c47931560eeed6d7d73e02b</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Handle algResourceHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_TILEDMEMORY_MAXRESOURCES</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga397775317ba851a3c541c861dc455c67</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRESMAN_TiledmemoryParams</class>
    <member kind="typedef">
      <type>struct IRESMAN_TiledmemoryParams</type>
      <name>IRESMAN_TiledmemoryParams</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga53b69a325a2aef702b5627cc01f49400</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentAllocFxn</type>
      <name>_RMAN_allocPersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gaadc2b94c8a7fe6dd08fcc18deec7d992</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentFreeFxn</type>
      <name>_RMAN_freePersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga0c23ac2d5d2854f5941c0b3098790df1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRESMAN_Fxns</type>
      <name>IRESMAN_TILEDMEMORY</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gab09c8ecb9ece591a08a86b0b4a51ee23</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iresman_vicp.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/ires/vicp/</path>
    <filename>iresman__vicp_8h</filename>
    <includes id="iresman_8h" name="iresman.h" local="no" imported="no">ti/sdo/fc/ires/iresman.h</includes>
    <member kind="function">
      <type>String</type>
      <name>IRESMAN_VICP_getProtocolName</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga4bf0fa4a35386dcd6f04c16a468984dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_ProtocolRevision *</type>
      <name>IRESMAN_VICP_getProtocolRevision</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga01841f095420ce69ce02aaf644d7250d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_VICP_init</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga613cdf62d35efa5fb1a02f9e07c73dd9</anchor>
      <arglist>(IRESMAN_Params *initArgs)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_VICP_exit</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga5d1eb79a6ad9c7a9e75fe48d70a2da58</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Handle</type>
      <name>IRESMAN_VICP_getHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga64636048ebc7e7a1a41e96552297f022</anchor>
      <arglist>(IALG_Handle algHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId, IRES_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_VICP_freeHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>gaa7bb21ce4147fab50131169877ab7f37</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Handle algResourceHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId)</arglist>
    </member>
    <class kind="struct">IRESMAN_VicpParams</class>
    <member kind="typedef">
      <type>struct IRESMAN_VicpParams</type>
      <name>IRESMAN_VicpParams</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga29f8ab6aaf9a18490216e300f12d2522</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentAllocFxn</type>
      <name>_RMAN_allocPersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>gaadc2b94c8a7fe6dd08fcc18deec7d992</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentFreeFxn</type>
      <name>_RMAN_freePersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga0c23ac2d5d2854f5941c0b3098790df1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRESMAN_Fxns</type>
      <name>IRESMAN_VICP</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga45a0fdbcf9e8610a403161583983578d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>memutils.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/memutils/</path>
    <filename>memutils_8h</filename>
    <member kind="function">
      <type>Void</type>
      <name>MEMUTILS_cacheInv</name>
      <anchorfile>group__ti__sdo__fc__memutils___m_e_m_u_t_i_l_s.html</anchorfile>
      <anchor>gad07c8ac40bec004e2cc0a386f86570dd</anchor>
      <arglist>(Ptr addr, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>MEMUTILS_cacheWb</name>
      <anchorfile>group__ti__sdo__fc__memutils___m_e_m_u_t_i_l_s.html</anchorfile>
      <anchor>ga9ec3a005cfbd44003b9dc57e737d32b1</anchor>
      <arglist>(Ptr addr, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>MEMUTILS_cacheWbInv</name>
      <anchorfile>group__ti__sdo__fc__memutils___m_e_m_u_t_i_l_s.html</anchorfile>
      <anchor>ga3ecacfd8a0771af6d1a532fbbe35adfe</anchor>
      <arglist>(Ptr addr, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Void *</type>
      <name>MEMUTILS_getPhysicalAddr</name>
      <anchorfile>group__ti__sdo__fc__memutils___m_e_m_u_t_i_l_s.html</anchorfile>
      <anchor>gae67c1ceb1e529cbb9b10abee89101f75</anchor>
      <arglist>(Ptr addr)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MEMUTILS_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__memutils___m_e_m_u_t_i_l_s.html</anchorfile>
      <anchor>gaad6bedcf19bfc91b3b86ae7640ea7a9e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>rman.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/packages/ti/sdo/fc/rman/</path>
    <filename>rman_8h</filename>
    <includes id="ires_8h" name="ires.h" local="no" imported="no">ti/xdais/ires.h</includes>
    <includes id="iresman_8h" name="iresman.h" local="no" imported="no">ti/sdo/fc/ires/iresman.h</includes>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_init</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga2553157eede6b63b0037b0db72fbdae8</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_exit</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gaedbbc06da21c2e842c890d4ff4ac9aed</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_register</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gae8fe0e0bcdcb46afb0d09d1997136347</anchor>
      <arglist>(IRESMAN_Fxns *resmanFxns, IRESMAN_Params *initArgs)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_unregister</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gaa6f966711380ecf89ad79db2ebf8619a</anchor>
      <arglist>(IRESMAN_Fxns *resmanFxns)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_assignResources</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gaa7772ccd9856ccc0b0492c018807b2b3</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Fxns *resFxns, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_allocateResources</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga0fdeaec06650e512ffd765613a3accaf</anchor>
      <arglist>(Int requestId, IRES_ResourceDescriptor *resDesc, Int numResources, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_freeResources</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga98911d4d4049d1805ae9eac2b71d9ec0</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Fxns *resFxns, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_freeAllocatedResources</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gafac26c9edf744af2d0b1f4f24862975b</anchor>
      <arglist>(Int requestId, IRES_ResourceDescriptor *resDesc, Int numResources, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_activateResource</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga3135611a668b07aad926247bbd0e37a9</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Handle resourceHandle, IRES_Fxns *resFxns, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_activateAllResources</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga354e1ad9ac34e6c41b0bd2184bc3e9fb</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Fxns *resFxns, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_deactivateResource</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga1c20b46e28a17783654674f9e109e46e</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Handle resourceHandle, IRES_Fxns *resFxns, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_deactivateAllResources</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga7343843e4acd15df9997315b4cb9bcf3</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Fxns *resFxns, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RMAN_yield</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gaa9da95739776c293fb4e27ec5207a668</anchor>
      <arglist>(IRES_YieldResourceType resource, IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ti_sdo_fc_ires_NOPROTOCOLREV</name>
      <anchorfile>rman_8h.html</anchorfile>
      <anchor>a33eacaa6cefc41cfe527b740449250dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RMAN_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga2df9395a0c498e45a8fb68942197a9eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RMAN_GTNAME</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga548fc91df8bfb9a8a30cbaab812110c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RMAN_PROTOCOLNAMESIZE</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga69dd3d9e63a604b0cb10037c60bfd4fa</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">RMAN_Params</class>
    <member kind="typedef">
      <type>struct Sem_Obj *</type>
      <name>RMAN_SemHandle</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga841a70da51acb69fde1f53d60faae1bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IRES_YieldArgs(*</type>
      <name>ti_sdo_fc_rman_RMAN_YieldArgsFxn</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gafe7fe1defb485927628dfa78dd2ebe97</anchor>
      <arglist>)(Int scratchId, Bool yieldFlag)</arglist>
    </member>
    <member kind="typedef">
      <type>struct RMAN_Params</type>
      <name>RMAN_Params</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga2b477ea38c1ae71bc320a1384f6b536e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ RMAN_Params</type>
      <name>RMAN_PARAMS</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gae12d774b050c8c27f780ed91dd7c2a33</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_Fxns *</type>
      <name>RMAN_TABLE</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gab2ff62cddcbbbd3c6a2819703a96bcca</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ short</type>
      <name>RMAN_FREE_ENTRIES</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga758ab45c1418c384bf578ea5558b9d7b</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ short</type>
      <name>RMAN_numRegistryEntries</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga60e319affb35f0df44bfa9e5576cbd05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_Fxns **</type>
      <name>RMAN_registryEntries</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gae4b796a7aead262ea31848120b07d54d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_Params **</type>
      <name>RMAN_registryResmanArgs</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga4a461e9e2f1b613ef55dbe4574abd5b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ unsigned int **</type>
      <name>RMAN_iresVTable</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga343604b8ef45f3565e25b0ea911a4173</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ unsigned int</type>
      <name>ti_sdo_fc_rman_RMAN_MAXALGS</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga8ec03181fc11e30d8c10c7eb54d248d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UInt32</type>
      <name>ti_sdo_fc_rman_RMAN_ipcKey</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gaa67b89289e5ff8dab19e2c011417dabb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ti_sdo_fc_rman_RMAN_YieldArgsFxn</type>
      <name>ti_sdo_fc_rman_RMAN_setYieldArgs</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gacfc9b966702c5a037e299e8b7b016ce3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>xdas.h</name>
    <path>/db/atree/library/trees/fc/fc-v07/src/framework_components_3_40_02_07/fctools/packages/ti/xdais/</path>
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
  <compound kind="struct">
    <name>_EdmaMgr_ConfigLarge</name>
    <filename>struct___edma_mgr___config_large.html</filename>
    <member kind="variable">
      <type>int32_t</type>
      <name>max_num_lines</name>
      <anchorfile>struct___edma_mgr___config_large.html</anchorfile>
      <anchor>a71a97405643c60f89261ba89d0c6587c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ECPY_CfgParams</name>
    <filename>struct_e_c_p_y___cfg_params.html</filename>
    <member kind="variable">
      <type>ECPY_PersistentAllocFxn *</type>
      <name>allocFxn</name>
      <anchorfile>struct_e_c_p_y___cfg_params.html</anchorfile>
      <anchor>ad05322d9c1c310c23f5c95812132d11d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ECPY_PersistentFreeFxn *</type>
      <name>freeFxn</name>
      <anchorfile>struct_e_c_p_y___cfg_params.html</anchorfile>
      <anchor>a68e01584bcf9d7050a770a5e3554203c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ECPY_ScratchAllocFxn *</type>
      <name>scratchAllocFxn</name>
      <anchorfile>struct_e_c_p_y___cfg_params.html</anchorfile>
      <anchor>a270e23d4710def5f1c22dcbed00f640e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ECPY_ScratchFreeFxn *</type>
      <name>scratchFreeFxn</name>
      <anchorfile>struct_e_c_p_y___cfg_params.html</anchorfile>
      <anchor>ab0dc3d5147909e3ff2c9cb48c200195a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ECPY_getScratchIdFxn *</type>
      <name>getScratchIdFxn</name>
      <anchorfile>struct_e_c_p_y___cfg_params.html</anchorfile>
      <anchor>a0493036e00791d10fd0e31ee1bd4d85e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ECPY_Params</name>
    <filename>struct_e_c_p_y___params.html</filename>
    <member kind="variable">
      <type>ECPY_TransferType</type>
      <name>transferType</name>
      <anchorfile>struct_e_c_p_y___params.html</anchorfile>
      <anchor>a93f77d9aaa134ee7df1849b412560d30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void *</type>
      <name>srcAddr</name>
      <anchorfile>struct_e_c_p_y___params.html</anchorfile>
      <anchor>a33a9323129706ecf45051f0511b44418</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void *</type>
      <name>dstAddr</name>
      <anchorfile>struct_e_c_p_y___params.html</anchorfile>
      <anchor>a3384cbdf302872ec290f2fabde55a785</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>elementSize</name>
      <anchorfile>struct_e_c_p_y___params.html</anchorfile>
      <anchor>a89c95f8116ac4779f91e035c23d51a8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>numElements</name>
      <anchorfile>struct_e_c_p_y___params.html</anchorfile>
      <anchor>adb8d423582c44e4f2fa494ffdc999b09</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>numFrames</name>
      <anchorfile>struct_e_c_p_y___params.html</anchorfile>
      <anchor>aa789f8cdd9701c66d83baf481cdee923</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>srcElementIndex</name>
      <anchorfile>struct_e_c_p_y___params.html</anchorfile>
      <anchor>af8e28f9a7b11381ec681076b4a6ad049</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>dstElementIndex</name>
      <anchorfile>struct_e_c_p_y___params.html</anchorfile>
      <anchor>a91cacfb281c520af816662bc1aec0ba6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>srcFrameIndex</name>
      <anchorfile>struct_e_c_p_y___params.html</anchorfile>
      <anchor>a6d373a3f073e84972388028101e19f6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>dstFrameIndex</name>
      <anchorfile>struct_e_c_p_y___params.html</anchorfile>
      <anchor>af84438c2ec8c98dc6ee6442a5e79ee8e</anchor>
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
      <anchor>a9731237e4ce31f732a140fb972cdb6f4</anchor>
      <arglist>)(IALG_Handle handle)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algAlloc</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a467cf4d7ff3cac7561c2fd691b69760a</anchor>
      <arglist>)(const IALG_Params *params, struct IALG_Fxns **parentFxns, IALG_MemRec *memTab)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algControl</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a7134239e72c6822ebfbf9443a3d30207</anchor>
      <arglist>)(IALG_Handle handle, IALG_Cmd cmd, IALG_Status *status)</arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>algDeactivate</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>adf78a97d273eaa4b28b15ce22f07524a</anchor>
      <arglist>)(IALG_Handle handle)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algFree</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a4d93144558ea45820690821bf840746b</anchor>
      <arglist>)(IALG_Handle handle, IALG_MemRec *memTab)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algInit</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a6ab3c831b6ef72e6d4667f41b48f7300</anchor>
      <arglist>)(IALG_Handle handle, const IALG_MemRec *memTab, IALG_Handle parent, const IALG_Params *params)</arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>algMoved</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>aef1c83e8c183a7bfd788d58d8116d6be</anchor>
      <arglist>)(IALG_Handle handle, const IALG_MemRec *memTab, IALG_Handle parent, const IALG_Params *params)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algNumAlloc</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a5329fd8561939d45eafeda8566739fb9</anchor>
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
    <name>IRES_EDMA3CHAN2_Obj</name>
    <filename>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</filename>
    <member kind="variable">
      <type>IRES_Obj</type>
      <name>ires</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>af8a6fbcd41a7bfea6d4ce035538b3689</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_EDMA3CHAN_PaRamStruct *</type>
      <name>shadowPaRams</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>aaf1fbddf122d96bb6802b5c2bc164bc8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int *</type>
      <name>assignedPaRamAddresses</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>a0d2ae43094786a57bebdffadd1be15cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short *</type>
      <name>assignedPaRamIndices</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>aa507f3c6c6b5cc44a0ab667cef3c5310</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short *</type>
      <name>assignedTccIndices</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>aea7fc25d4d88d7618610d1f45e079109</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>assignedNumPaRams</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>a664ed2015328cde495a15cf518826628</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>assignedNumTccs</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>ae2957a5c4a885db0e6132adeab685b6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>assignedQdmaChannelIndex</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>aebfec493501da098ecac1439800b45de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>assignedEdmaChannelIndex</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>ad4c37d53c1ea67522e5bb7496c74d82a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>esrBitMaskL</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>ab81943b0dbe175e744af97bfc29bd3e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>esrBitMaskH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>ae575185c8df81406240f13d5cb05ceae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>iprBitMaskL</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>ab0477b5b9fccf326eeca05c5fa1d7c9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>iprBitMaskH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>ad60f9ce1eb9b09de81a877baa73e472a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32 *</type>
      <name>queueMap</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n2___obj.html</anchorfile>
      <anchor>a845e36697dc7ccbf7e013f954fb0fc6f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_EDMA3CHAN_EDMA3DraeRegister</name>
    <filename>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_drae_register.html</filename>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>DRAE</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_drae_register.html</anchorfile>
      <anchor>a9e808ae96d25190d8514ec5797518bef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>DRAEH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_drae_register.html</anchorfile>
      <anchor>a8ae174d478321b4e40afc98a14fadfe4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_EDMA3CHAN_EDMA3RegisterLayer</name>
    <filename>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</filename>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>REV</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ac54e4d8b303bae2fc0aa242f68e7b1be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>CCCFG</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a7a12dcd2b6c210b9a9307d70e5c401da</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD0</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>affea5712c405c19ae00f5773fbf4a83c</anchor>
      <arglist>[248]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>DCHMAP</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>aef4650a40f852f94c4976d3e0c2b368f</anchor>
      <arglist>[64]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QCHMAP</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>adbfc0ec2fe907f29ea58107e2f2a8bbf</anchor>
      <arglist>[8]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD1</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a1ef92ffe3d8a2623596fcebcd49e07e8</anchor>
      <arglist>[32]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>DMAQNUM</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a437e85b07c251f21a1c6bfacaa30c220</anchor>
      <arglist>[8]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QDMAQNUM</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a8b394162eec4bd1245fe84c83328a79f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD2</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>aac1cb8c69373226881a063059125f72c</anchor>
      <arglist>[28]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QUETCMAP</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>aac61c501760dfa8716596d30f11c1bf3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QUEPRI</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ae9503cd36dace0bb203fcd0698929c08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD3</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ab7634b40b367fc2eef9be4b429d94407</anchor>
      <arglist>[120]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EMR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ae03a011b22283645271cef808affd3b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EMRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ac1b9c9e9a35b03e2836a8ce8e09fe6a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EMCR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a288ebef22b61b85aa372a589e3791197</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EMCRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a53cabc051fae87880ad326a6131efc19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QEMR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a55a88ea4d8813e2d66f4737e86838a00</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QEMCR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a40ab7ec5b7d762f038642bf071067026</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>CCERR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a3122e94a7d0229cb1b11bffdf48f5d74</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>CCERRCLR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a87fbd1a5fb5b206384da5c0a3f01dc97</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EEVAL</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>adb9f4a5ee2fee596d1002fcb81921e63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD4</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a92a72b6f9f27d90fc8016a60a07318cd</anchor>
      <arglist>[28]</arglist>
    </member>
    <member kind="variable">
      <type>IRES_EDMA3CHAN_EDMA3DraeRegister</type>
      <name>DRA</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a03d33a097d27d6e7119829df50a0eb8a</anchor>
      <arglist>[8]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QRAE</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a150169c8b6c463e24f641b2685a5621f</anchor>
      <arglist>[8]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD5</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a4d92cb7657c85619bd9470c4d8dd4fb0</anchor>
      <arglist>[96]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QUEEVTENTRY</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>abcdcfb3fb01888f9d16a1153e6d9dd06</anchor>
      <arglist>[8][16]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QSTAT</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a6e919f590b7e2543a00b6477175d585f</anchor>
      <arglist>[8]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QWMTHRA</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>aada7476d787c8300951abadb3520c0b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QWMTHRB</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a856fa7ff1cc28d896ab8a71b8fd977e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD6</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>acee1638682f2c80864c05be606279551</anchor>
      <arglist>[24]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>CCSTAT</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>af3e8e8e61da799a8c12696f9b2b5aacb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD7</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>aa86878e266fc897493ff26f5a219b75b</anchor>
      <arglist>[188]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>AETCTL</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a7d96f9048e37ac74146857f5c9fefc84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>AETSTAT</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>adad98cc5663eb941ef5fcfba4bcdccf4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>AETCMD</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ad0d6f7f01770a93b46c7903b7bdb4f27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD8</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a59e10a5efae47b72bfe5d0d0c3377f61</anchor>
      <arglist>[244]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>MPFAR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ae2219e147269e62e12ff77dbf3061e1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>MPFSR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ab27bd35a6b1d568b3e940fde95cf39e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>MPFCR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a9cbf38b017c3e9507587483e23594826</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>MPPAG</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>aa6618180fb1ace6ab623c3dec0a87508</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>MPPA</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>abb43d07de6af261423ed1dcf119f6de7</anchor>
      <arglist>[8]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD9</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a807214d2a8a2f0662cc49ceb98b64a9b</anchor>
      <arglist>[2000]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a6965d078d0b04d266a9991bf9c9830ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ERH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a031bd43d639c4d6150809e82088569dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ECR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ac4a3851eee637396ca269f8d93e1835c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ECRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a220964a3364efa894f37f769aab2434b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ESR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a5bdc0cf6e86492817018f55ad876ce60</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ESRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ae7d659959adf2f5dd16caaab3671537f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>CER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ab7567083f34aaf3e455fb68c17bc8805</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>CERH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a7b15dfa0f19d1a41183fcda8cc80f41d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>af5ca383e2d00e408c57d2cf1c1ddb449</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EERH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a3960ec87a5529a08ff0a512148f18f59</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EECR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ab6121bab1262f1a716d3037f1f14dd35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EECRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>aa8a3dcd54a0ec08ac423c73134f482f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EESR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>adede8230a0476ee4e92771d6a7946b81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EESRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a8632fa9dfdab0717d8eebac48e9ea7d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>SER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a00412e6d3a41f2eb2684d5b6e11b121b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>SERH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>aaa86a93aa8c0f5b22e9414face78e3ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>SECR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a0fdcba15b63d16547ca36d36a3370a7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>SECRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a054a21331013040c2e0e26a84fa3b997</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD10</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ab3fdd9f0150bf4ab0837ba22d8efdcc2</anchor>
      <arglist>[8]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a8c61e1695ecdca0d8bbb9f6649c3c1d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IERH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a618aab4bb2abe895c57cbbdeda846718</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IECR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ad86c88e1823be37f36b55191da7adbc7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IECRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>abe5fbf1a714fad9a2f3d6c7d651d7245</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IESR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>aca60ccffd95dec84500ea4b01713f4ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IESRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a7645192f36a2cf333fbb0aabab54184d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IPR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>aa044b6f447c8b65f26d4ef0145ca7259</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IPRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>af0467677613773f41c4c24636d919765</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ICR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>aa2cac41d44028fd3041c1cdc2a21c71e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ICRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a5155f2bd21c7c575d024f2e8370a9fbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IEVAL</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a38f807cbc5488bc3bab38e921a3da631</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD11</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a67545db52008b0061deac7f739f1a996</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>af0261cb0f503a97ef2bfd0bc0da5d88e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QEER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a9b330d2d57f24bf9e9fc700b2409afd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QEECR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ad8d5d4bf7b036c73f0f88fd93a0c3176</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QEESR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>af92bb426d5bf017e78cb8dd47df88324</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QSER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a01d3fefa43a804c82cd6680aee3a2ce4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QSECR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ac8acc518f9e72c5e3071b031597dba59</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD12</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>aae236f70ae48f7335f7c33fad85b2386</anchor>
      <arglist>[3944]</arglist>
    </member>
    <member kind="variable">
      <type>IRES_EDMA3CHAN_EDMA3ShadowRegister</type>
      <name>SHADOW</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a4310e25138662eb7ca91776c07446726</anchor>
      <arglist>[8]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD13</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>ae4b83eef72621e2bcf549bd75d023d80</anchor>
      <arglist>[4096]</arglist>
    </member>
    <member kind="variable">
      <type>IRES_EDMA3CHAN_PaRamStruct</type>
      <name>PARAMENTRY</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_register_layer.html</anchorfile>
      <anchor>a38304d07bef1e415081f467fab48def6</anchor>
      <arglist>[512]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_EDMA3CHAN_EDMA3ShadowRegister</name>
    <filename>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</filename>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>aee23cdf984110f26d52b3487251a5bc8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ERH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a8162f08b6b337da84b2c39eec97ed7ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ECR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>aae811c5b95e7ff7efb8bb6cf3264979d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ECRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>add9f0a486048274ea7e4443fefa62276</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ESR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a6af4dec422b16655e8811bd7307700e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ESRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a27c406f710a7fa7ef2f838398c6c9801</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>CER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>aed02a479ec8ea7eeb04207858bef1c08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>CERH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a92862b2078232caa5bf2a7f5e27eb95c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a34f42f3e84ca1fb9baad0bc8d625a14c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EERH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a3075403fd0ed0300a22313a351853e01</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EECR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a8f8503639eb8151ed829ff3ef0f1b5e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EECRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>ae4843261a7e8e6fb28f9d3cfd258ea5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EESR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a7940489d971522c98e43962a5aa4640e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>EESRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>ae80f612ea4be945a70fc8b409b25d661</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>SER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>aeccb35f278854ab17fc2db8442f46989</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>SERH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a2a15c9130f535881a525596fb0acac2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>SECR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>ac98f10cb00323a98ec3b04d6977f34e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>SECRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a591011f3b030e83ceae7e607d297bbd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD0</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>ae796ce9db0169d174dbbb3a3d1ea0108</anchor>
      <arglist>[8]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>ae9a3c71acbbbc96f74fabc239adcf6cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IERH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>af26ffeebd6430e416be7b8df2cc019fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IECR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>ae314a97c5a28fe56b97f220f9d0b0554</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IECRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>ad9d12d3ed110cec8eebe07d1f5873689</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IESR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a687cd004877cc6fb3d39353cad624b32</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IESRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a248019fbc22fe2972c1502d6028b77be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IPR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a9a7ce2c9eb6d1722b903f2b4f14dcde6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IPRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>ab7f1ada93243bf3958db3177ce2ee631</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ICR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>af22a274535b89aea6a936172cc99ad96</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>ICRH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a2749efe7a75210c5bb5e01e8d8fb6ebd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>IEVAL</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a31f09ac9bb272adb473e2b9dfb165365</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD1</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a7a1b4ed06a1f0b69c57710784651b3be</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a69946bd3f4fb9815d771ff8c7793e888</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QEER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>ad5e12ab54cc9bdef77f75151de348255</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QEECR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a0946e306b21dca2ef1b1eac81339bc20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QEESR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a2fa6787ac82799457610e55bf353ba2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QSER</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>ab31e4248421eb24e3372e20bb3002fbd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned int</type>
      <name>QSECR</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a3294a3855b38f96ab1958fe5647aa377</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile unsigned char</type>
      <name>RSVD2</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___e_d_m_a3_shadow_register.html</anchorfile>
      <anchor>a06affbc35d9f64fc8ba04ebf50317fca</anchor>
      <arglist>[360]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_EDMA3CHAN_Obj</name>
    <filename>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</filename>
    <member kind="variable">
      <type>IRES_Obj</type>
      <name>ires</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>a40e1756b5ade03bf300b54f9b5eab496</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_EDMA3CHAN_PaRamStruct *</type>
      <name>shadowPaRams</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>a3f596af3cf04045734257017a2faab51</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int *</type>
      <name>assignedPaRamAddresses</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>abeba0335a802812f0e33b6203b525f14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short *</type>
      <name>assignedPaRamIndices</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>aee12c9bbedb02739f17d845cabc8c7bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short *</type>
      <name>assignedTccIndices</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>a0705537b7ed97c2e2d73c9bf8882a790</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>assignedNumPaRams</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>aacdfe6d10510f6672a07fdbac1a51317</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>assignedNumTccs</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>a37a425062c3fb91289537baec35e97f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>assignedQdmaChannelIndex</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>a3cbedb9826bb63c25f5210b82c97b372</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>assignedEdmaChannelIndex</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>a130ad94d4cf5e93304628f196b6135b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>esrBitMaskL</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>a7490ef52be82d57a2037dc3cfbe74126</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>esrBitMaskH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>a079c7289178eea20f68ffda6d1168c23</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>iprBitMaskL</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>ab3108be5ce9944687096baee11ed4eb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>iprBitMaskH</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___obj.html</anchorfile>
      <anchor>a95cd4bdd4c90afd49e95f6bebc5423b7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_EDMA3CHAN_PaRamStruct</name>
    <filename>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</filename>
    <member kind="variable">
      <type>unsigned int</type>
      <name>opt</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>a54a02381e9429650b325c4d1847293ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>src</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>a2d0bfd960a1bc7d869cca153eaa4ae38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>acnt</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>a16d93e85dcea4eca1e6707f16917d570</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>bcnt</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>a8ad41154ec256a516f99fd554dd30c13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>dst</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>a785e14c057576dd51a7b5568c4c62210</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>srcElementIndex</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>ab73b73792be92a58b09ea552765dad08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>dstElementIndex</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>a3ec0b8153b52d319894302579e938b40</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>link</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>ad46dd22e92d137d72facd6ff4c0967a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>bCntrld</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>a5b69579dcbe7038ea31152c099be3360</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>srcFrameIndex</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>a2aa917bf2e3f21fb3eacea36607d5433</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>dstFrameIndex</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>a8114c17ee881e165d8ce6dd41858a4ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>ccnt</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>ad7737b41e5ed2c3d61188833c3ff415b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>rsvd</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___pa_ram_struct.html</anchorfile>
      <anchor>a6ae099a297021bdbdc77b95823078520</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_EDMA3CHAN_Properties</name>
    <filename>struct_i_r_e_s___e_d_m_a3_c_h_a_n___properties.html</filename>
    <member kind="variable">
      <type>unsigned int</type>
      <name>numDmaChannels</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___properties.html</anchorfile>
      <anchor>a2b72ba415dbad5a579d88d5da0d5ea21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>numQdmaChannels</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___properties.html</anchorfile>
      <anchor>ad7c214e2680edf2f4d37383d0ea9f4fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>numTccs</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___properties.html</anchorfile>
      <anchor>af85f3c00300b2022b36910b9428de0e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>numPaRAMSets</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___properties.html</anchorfile>
      <anchor>a21f26eed1ca54246f784e1a4851ec934</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>numEvtQueue</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___properties.html</anchorfile>
      <anchor>aed314c1dd26caa680e199c1ef831dd8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>numTcs</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___properties.html</anchorfile>
      <anchor>aa1fc9e49b3edbd219de01ceb1f3d5d25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>numRegions</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___properties.html</anchorfile>
      <anchor>a7d823a7951834832d0a9ea78810f1e1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>dmaChPaRAMMapExists</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___properties.html</anchorfile>
      <anchor>a7d85ecf6b8c1543397a2a32d716045a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>memProtectionExists</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___properties.html</anchorfile>
      <anchor>aaf9a918aba3ab6d7958928613f3a438a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_EDMA3CHAN_EDMA3RegisterLayer *</type>
      <name>globalRegs</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___properties.html</anchorfile>
      <anchor>a617dc2263a7b5e3ce910840494e1bd1e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_EDMA3CHAN_ProtocolArgs</name>
    <filename>struct_i_r_e_s___e_d_m_a3_c_h_a_n___protocol_args.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___protocol_args.html</anchorfile>
      <anchor>a398c7be80d9e6c2f3fd1c7025f8b7a79</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_RequestMode</type>
      <name>mode</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___protocol_args.html</anchorfile>
      <anchor>a8fd3eb87fd47f66fcb2f268fe9f5c77f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>numPaRams</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___protocol_args.html</anchorfile>
      <anchor>a3582de3c4dceaedbedf669da00fbd6cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>paRamIndex</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___protocol_args.html</anchorfile>
      <anchor>a0d8ca2609faf57e0bd0f7315d7404510</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>numTccs</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___protocol_args.html</anchorfile>
      <anchor>a4fe328fbbdcd32def3074a8905c7d0b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>tccIndex</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___protocol_args.html</anchorfile>
      <anchor>a4aaabc6616f5a34186e87667316ce0a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>qdmaChan</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___protocol_args.html</anchorfile>
      <anchor>a04f48281a7c858224698bf0e24d5d22c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>edmaChan</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___protocol_args.html</anchorfile>
      <anchor>a23001551faec579b5b5d049258fb8f28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>contiguousAllocation</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___protocol_args.html</anchorfile>
      <anchor>a019cb773321cee58f158e42532b412b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>shadowPaRamsAllocation</name>
      <anchorfile>struct_i_r_e_s___e_d_m_a3_c_h_a_n___protocol_args.html</anchorfile>
      <anchor>a7105c440bacc9831a3057c8bec804647</anchor>
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
      <anchor>aafff7b730f481d643706d38d4599ada9</anchor>
      <arglist>)(IALG_Handle handle, IRES_ResourceDescriptor *resourceDescriptors)</arglist>
    </member>
    <member kind="variable">
      <type>Int32(*</type>
      <name>numResourceDescriptors</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a15e33bb3d48b502fd8199c3adb5b13cb</anchor>
      <arglist>)(IALG_Handle handle)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>initResources</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a922ef12ad56d5081bf67322531f88925</anchor>
      <arglist>)(IALG_Handle handle, IRES_ResourceDescriptor *resourceDescriptor, IRES_YieldFxn yieldFxn, IRES_YieldArgs yieldArgs)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>reinitResources</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a6b275deb501b66dc07cac7127bb38134</anchor>
      <arglist>)(IALG_Handle handle, IRES_ResourceDescriptor *resourceDescriptor, IRES_YieldFxn yieldFxn, IRES_YieldArgs yieldArgs)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>deinitResources</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>ac5eff1b13ce9e99e0e2c930621d07afb</anchor>
      <arglist>)(IALG_Handle handle, IRES_ResourceDescriptor *resourceDescriptor)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>activateResource</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a4baf80aa0e0bd97aee11f213e1e9a24f</anchor>
      <arglist>)(IALG_Handle handle, IRES_Handle resourceHandle)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>activateAllResources</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a5e30d62f92085777078d970c177b89ba</anchor>
      <arglist>)(IALG_Handle handle)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>deactivateResource</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>aeb234f8dfb228bfd97596ef98f4d1bc6</anchor>
      <arglist>)(IALG_Handle handle, IRES_Handle resourceHandle)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>deactivateAllResources</name>
      <anchorfile>struct_i_r_e_s___fxns.html</anchorfile>
      <anchor>a092f33a62cba89dd8fba5f8ded9dc73c</anchor>
      <arglist>)(IALG_Handle handle)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_HDVICP2_Obj</name>
    <filename>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</filename>
    <member kind="variable">
      <type>IRES_Obj</type>
      <name>ires</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>ae06d76d124b8511ed08ac8f70086bbb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void *</type>
      <name>info</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>a5b06dc398640e9f6f70eafdf73cc2489</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>id</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>a4cf3360bf2107055e1c09487cfcf4e85</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Void *</type>
      <name>registerBaseAddress</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>a0e330a5db9f04cf398e47ffe91fb5ece</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Void *</type>
      <name>memoryBaseAddress</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>ad2d09f4a58ec8e2332cd7f89bcd27305</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Void *</type>
      <name>resetControlAddress</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>a95360d5c2f0f17dad26880ea0114ae8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Void(*</type>
      <name>acquire</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>a101b73b428efa487440bda31bf2f434b</anchor>
      <arglist>)(IALG_Handle algHandle, struct IRES_HDVICP2_Obj *hdvicpHandle, IRES_YieldContext *yieldCtxt, XDAS_UInt32 *hdvicp2Status, XDAS_UInt32 *configurationId, XDAS_Int32 lateAcquireArg)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Void(*</type>
      <name>release</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>aae335da2802f795dcb65586e49d56845</anchor>
      <arglist>)(IALG_Handle algHandle, struct IRES_HDVICP2_Obj *hdvicpHandle)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_UInt32(*</type>
      <name>reacquireIfOwner</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>abbb5d377c0ae5d4c9b369d7ca9fd4109</anchor>
      <arglist>)(IALG_Handle algHandle, struct IRES_HDVICP2_Obj *hdvicpHandle)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Void(*</type>
      <name>configure</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>a94cac0c439f41490ecff903e80e9e7a3</anchor>
      <arglist>)(IALG_Handle algHandle, struct IRES_HDVICP2_Obj *hdvicpHandle, IRES_HDVICP2_CallbackFxn cbFunctionPtr, XDAS_Void *cbArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_UInt32(*</type>
      <name>wait</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>a4f833c1b2d1cee458aabf71d2c13ef4f</anchor>
      <arglist>)(IALG_Handle algHandle, struct IRES_HDVICP2_Obj *hdvicpHandle, IRES_YieldContext *yieldCtxt)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Void(*</type>
      <name>done</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>a445fe463634bf3f89856c2843f6c2051</anchor>
      <arglist>)(IALG_Handle algHandle, struct IRES_HDVICP2_Obj *hdvicpHandle)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_UInt32(*</type>
      <name>reset</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___obj.html</anchorfile>
      <anchor>a9f3cdedb06f449df2985e29aba807581</anchor>
      <arglist>)(IALG_Handle algHandle, struct IRES_HDVICP2_Obj *hdvicpHandle)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_HDVICP2_Properties</name>
    <filename>struct_i_r_e_s___h_d_v_i_c_p2___properties.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___properties.html</anchorfile>
      <anchor>a98a0846453e1074c7d4982f016dc64b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_HDVICP2_RegisterLayer *</type>
      <name>globalRegs</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___properties.html</anchorfile>
      <anchor>ab0ef58b1868d8263b659f77b5ada49d7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_HDVICP2_ProtocolArgs</name>
    <filename>struct_i_r_e_s___h_d_v_i_c_p2___protocol_args.html</filename>
    <member kind="variable">
      <type>IRES_ProtocolArgs</type>
      <name>base</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___protocol_args.html</anchorfile>
      <anchor>a66f759dc45020ec40885177ab6b48de7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>id</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___protocol_args.html</anchorfile>
      <anchor>abe3d3255bf68273f33603bc44e0f74bb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_HDVICP2_RegisterLayer</name>
    <filename>struct_i_r_e_s___h_d_v_i_c_p2___register_layer.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p2___register_layer.html</anchorfile>
      <anchor>ad0b49c8186268337bd18d8ead510db2c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_HDVICP_Obj</name>
    <filename>struct_i_r_e_s___h_d_v_i_c_p___obj.html</filename>
    <member kind="variable">
      <type>IRES_Obj</type>
      <name>ires</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p___obj.html</anchorfile>
      <anchor>a5d4026e15d60feda5e84dd3eb918e6fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void *</type>
      <name>info</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p___obj.html</anchorfile>
      <anchor>aa313d7af9092b431d6667e704df8ed44</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>id</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p___obj.html</anchorfile>
      <anchor>ad310c8bdd68ee2f2ff8942c29359ac5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void *</type>
      <name>registerBaseAddress</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p___obj.html</anchorfile>
      <anchor>ac573c0a37c83536214a504e20bc36805</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void *</type>
      <name>memoryBaseAddress</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p___obj.html</anchorfile>
      <anchor>acb98c73e26d8845171ce86e6d5a77894</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>pscRegisterSpace</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p___obj.html</anchorfile>
      <anchor>a3fdc51d26670a7c19226d1b290e75655</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_HDVICP_Properties</name>
    <filename>struct_i_r_e_s___h_d_v_i_c_p___properties.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p___properties.html</anchorfile>
      <anchor>aba443d8563f35b2c823f0fb1785731cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_HDVICP_RegisterLayer *</type>
      <name>globalRegs</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p___properties.html</anchorfile>
      <anchor>aac58b5a8cbb86d0c5f0ff397d795fb93</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_HDVICP_ProtocolArgs</name>
    <filename>struct_i_r_e_s___h_d_v_i_c_p___protocol_args.html</filename>
    <member kind="variable">
      <type>IRES_ProtocolArgs</type>
      <name>base</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p___protocol_args.html</anchorfile>
      <anchor>a997ef9081ec10e67512ddfd5323ff86b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_HDVICP_RequestType</type>
      <name>id</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p___protocol_args.html</anchorfile>
      <anchor>a1e0d8a64eff399ecbc6d3f9f569d0ccf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_HDVICP_RegisterLayer</name>
    <filename>struct_i_r_e_s___h_d_v_i_c_p___register_layer.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s___h_d_v_i_c_p___register_layer.html</anchorfile>
      <anchor>a64b05fc704c8ca0f5292f0e4d67cf86c</anchor>
      <arglist></arglist>
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
      <anchor>a75a8301de516ab54247b960cdc4366d9</anchor>
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
    <name>IRES_TILEDMEMORY_Obj</name>
    <filename>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___obj.html</filename>
    <member kind="variable">
      <type>IRES_Obj</type>
      <name>ires</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___obj.html</anchorfile>
      <anchor>a3146482fb8a79ddbfe7a9604441baad9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Void *</type>
      <name>info</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___obj.html</anchorfile>
      <anchor>a1d3fe9f1186f47f828cd6e199ea0382c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Void *</type>
      <name>memoryBaseAddress</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___obj.html</anchorfile>
      <anchor>a5a7b295412151d5acac69137dd72567c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_UInt32</type>
      <name>isTiledMemory</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___obj.html</anchorfile>
      <anchor>af13e300742f1fdef8ac212eb3b7831de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_UInt32</type>
      <name>accessUnit</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___obj.html</anchorfile>
      <anchor>a3fdec399b3ce2e3094e31aca70b06f91</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Void *</type>
      <name>tilerBaseAddress</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___obj.html</anchorfile>
      <anchor>a61656ed9ab49f6945894411dacf4bd3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Void *</type>
      <name>systemSpaceBaseAddress</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___obj.html</anchorfile>
      <anchor>a96d0e320468088dff50d952cc89df656</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_TILEDMEMORY_Properties</name>
    <filename>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___properties.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___properties.html</anchorfile>
      <anchor>a90c348d66f0ff30c7c0bb76f5382c2eb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_TILEDMEMORY_ProtocolArgs</name>
    <filename>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___protocol_args.html</filename>
    <member kind="variable">
      <type>IRES_ProtocolArgs</type>
      <name>base</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___protocol_args.html</anchorfile>
      <anchor>ac80bb14fb6b3fd931c5c78b7d19831bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_UInt32</type>
      <name>accessDimension</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___protocol_args.html</anchorfile>
      <anchor>a573824791ca49e9ebe7cc1118787267b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_UInt32</type>
      <name>accessUnit</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___protocol_args.html</anchorfile>
      <anchor>ae2328111c90b608ba8f8b48d698004ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>sizeDim0</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___protocol_args.html</anchorfile>
      <anchor>aa8dc63bf23d93a8961b99ae58d9834ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>sizeDim1</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___protocol_args.html</anchorfile>
      <anchor>a0292f4b3d664923a98bcff201c33fdf7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>alignment</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___protocol_args.html</anchorfile>
      <anchor>a8b065e50b2f796e03ac8931a8e578315</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_TILEDMEMORY_RegisterLayer</name>
    <filename>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___register_layer.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s___t_i_l_e_d_m_e_m_o_r_y___register_layer.html</anchorfile>
      <anchor>a1b16edf76dc04230e1898ad2942fb40d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_VICP_Obj</name>
    <filename>struct_i_r_e_s___v_i_c_p___obj.html</filename>
    <member kind="variable">
      <type>IRES_Obj</type>
      <name>ires</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___obj.html</anchorfile>
      <anchor>a947469519efc1b89aafbdc1075c21571</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>assignedIMX</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___obj.html</anchorfile>
      <anchor>a1bffad04e8b1cb7dbb813f8c6d558653</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>assignedVLCD</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___obj.html</anchorfile>
      <anchor>afcb450273d9ff097fdf2415fcf6dfb4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>assignedSEQ</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___obj.html</anchorfile>
      <anchor>a6fbc47f1d1cf64977bba5a0cb81545e8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_VICP_Properties</name>
    <filename>struct_i_r_e_s___v_i_c_p___properties.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___properties.html</anchorfile>
      <anchor>a6090b7a3e55c436f481f03f4cb76d7a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_VICP_Registers *</type>
      <name>globalRegs</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___properties.html</anchorfile>
      <anchor>a6de89d575cca5a32a08ad0e3534047d1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_VICP_ProtocolArgs</name>
    <filename>struct_i_r_e_s___v_i_c_p___protocol_args.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___protocol_args.html</anchorfile>
      <anchor>a079d6d341243657f2d4d03f0447e5dd5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_RequestMode</type>
      <name>mode</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___protocol_args.html</anchorfile>
      <anchor>a07d4c5c4fff6cf66b40b193193f9304e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>requestIMX</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___protocol_args.html</anchorfile>
      <anchor>ac9de71be6f9a0b7a54c67149dcfc3b11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>requestVLCD</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___protocol_args.html</anchorfile>
      <anchor>a7e180a4534bfe1b6b468340fd6fb4268</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>requestSEQ</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___protocol_args.html</anchorfile>
      <anchor>a67c3d1339650ff811984920fb027a968</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRES_VICP_Registers</name>
    <filename>struct_i_r_e_s___v_i_c_p___registers.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a151ad24c1e02ade3cd04d85650c32a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>vicp_umap1_base</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a0f6e91812dbffc7874114af66ffae1d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>vicp_cfg_base</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>af5d2bbf3f9b074f99162a777a46896a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>imgBuf_base</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a53be2eeac69bc66286611dab8556952b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>imgBufA_base</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a38de26b57d6fa4f496e4049342f44e0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>imgBufB_base</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a0052d755403ef88539c3af79d914f4a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>imxCoeffBuff_base</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a96b47040a92ab913e5c7157edb30a989</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>imxCmdBuf_base</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>ac0bf909463fe7446736195c5bc288a37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>vlcdDataBuf_base</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a0caf5299ac86fdf415017d714e626a08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>qiqBuf_base</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a323a1f84109536b6f71e1e9d48f65ccd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>vlcdBuf_base</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>af2b38d1142a8f7632ffb21919b33fe2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>seqProgMem_base</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a68c918e30670319fbaee2fb4f8c1e99e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char *</type>
      <name>seqDataMem_base</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>ab83e637507a80ff5eee3c28b60f15618</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>imgBuf_length</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a708e8eba45c595f2dd37656c4815f1d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>imgBufA_length</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a48b731bdb2fe5657af2c049ab1386a70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>imgBufB_length</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a63465f075fe4ce3fe35b910051419152</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>imxCoeffBuff_length</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a936609723cb277e5fe735edc272bd9f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>imxCmdBuf_length</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>aca2da2ad8a380af56a0ab206a11691c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>vlcdDataBuf_length</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a5f9f73ce6c861d9e154d349d3a7607fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>qiqBuf_length</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a4dbb358ce7b28e86a8bbe81f52b7756a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>vlcdBuf_length</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>a3849f0810461dde216c3dfe42a079dad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>seqProgMem_length</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>acbe08afc7b5cee0ab62eab82754b3889</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>seqDataMem_length</name>
      <anchorfile>struct_i_r_e_s___v_i_c_p___registers.html</anchorfile>
      <anchor>ab17337e4cff1feff72b414f268a1a97b</anchor>
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
    <name>IRESMAN_ConstructArgs</name>
    <filename>struct_i_r_e_s_m_a_n___construct_args.html</filename>
    <member kind="variable">
      <type>Int32</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s_m_a_n___construct_args.html</anchorfile>
      <anchor>a60cbf903a6dd0a5d169facc760176aba</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRESMAN_ConstructFxns</name>
    <filename>struct_i_r_e_s_m_a_n___construct_fxns.html</filename>
    <member kind="variable">
      <type>String(*</type>
      <name>getName</name>
      <anchorfile>struct_i_r_e_s_m_a_n___construct_fxns.html</anchorfile>
      <anchor>a21183646365f14097915bf37f7a012f8</anchor>
      <arglist>)()</arglist>
    </member>
    <member kind="variable">
      <type>IRES_ProtocolRevision *(*</type>
      <name>getRevision</name>
      <anchorfile>struct_i_r_e_s_m_a_n___construct_fxns.html</anchorfile>
      <anchor>aa7ac1597a63f3f75f7a3460e3c8ec633</anchor>
      <arglist>)()</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>getMemRecs</name>
      <anchorfile>struct_i_r_e_s_m_a_n___construct_fxns.html</anchorfile>
      <anchor>a3034c60437d8b65eaad447c51811c88d</anchor>
      <arglist>)(IRES_Handle handle, IRES_ProtocolArgs *protocolArgs, IALG_MemRec *memRecs)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>getNumMemRecs</name>
      <anchorfile>struct_i_r_e_s_m_a_n___construct_fxns.html</anchorfile>
      <anchor>a2099acc5ea372b39d16e47bac2da9756</anchor>
      <arglist>)(IRES_ProtocolArgs *protocolArgs)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Handle(*</type>
      <name>constructHandle</name>
      <anchorfile>struct_i_r_e_s_m_a_n___construct_fxns.html</anchorfile>
      <anchor>a4e150d2b008e0e98813267f2e5ac6d96</anchor>
      <arglist>)(IRES_ProtocolArgs *protocolArgs, IALG_MemRec *memRecs, IRESMAN_ConstructArgs *constructHandleArgs, IRES_Status *status)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>destructHandle</name>
      <anchorfile>struct_i_r_e_s_m_a_n___construct_fxns.html</anchorfile>
      <anchor>a197626b7ff05704cbf389f3cec4f467a</anchor>
      <arglist>)(IRES_Handle handle)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRESMAN_Edma3ChanParams</name>
    <filename>struct_i_r_e_s_m_a_n___edma3_chan_params.html</filename>
    <member kind="variable">
      <type>IRESMAN_Params</type>
      <name>baseConfig</name>
      <anchorfile>struct_i_r_e_s_m_a_n___edma3_chan_params.html</anchorfile>
      <anchor>a89c283e85347fd83686db9f2d6c3919a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRESMAN_Fxns</name>
    <filename>struct_i_r_e_s_m_a_n___fxns.html</filename>
    <member kind="variable">
      <type>String(*</type>
      <name>getProtocolName</name>
      <anchorfile>struct_i_r_e_s_m_a_n___fxns.html</anchorfile>
      <anchor>acfd7ade74206af2184d9a2080c99134c</anchor>
      <arglist>)()</arglist>
    </member>
    <member kind="variable">
      <type>IRES_ProtocolRevision *(*</type>
      <name>getProtocolRevision</name>
      <anchorfile>struct_i_r_e_s_m_a_n___fxns.html</anchorfile>
      <anchor>a8354a2ced61dabd6c505df8a45fd719c</anchor>
      <arglist>)()</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>init</name>
      <anchorfile>struct_i_r_e_s_m_a_n___fxns.html</anchorfile>
      <anchor>a2ef015a20e38b8ad6e3bfa320534c21c</anchor>
      <arglist>)(IRESMAN_Params *initArgs)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>exit</name>
      <anchorfile>struct_i_r_e_s_m_a_n___fxns.html</anchorfile>
      <anchor>aa2b8fb8ee986d7b6a3c1506deac7a319</anchor>
      <arglist>)()</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Handle(*</type>
      <name>getHandle</name>
      <anchorfile>struct_i_r_e_s_m_a_n___fxns.html</anchorfile>
      <anchor>af4c071fa93302686a067870b73649515</anchor>
      <arglist>)(IALG_Handle algHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId, IRES_Status *status)</arglist>
    </member>
    <member kind="variable">
      <type>IRES_Status(*</type>
      <name>freeHandle</name>
      <anchorfile>struct_i_r_e_s_m_a_n___fxns.html</anchorfile>
      <anchor>a328de487a09025534200b0540e6b3f0b</anchor>
      <arglist>)(IALG_Handle algHandle, IRES_Handle resourceHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId)</arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>activateResource</name>
      <anchorfile>struct_i_r_e_s_m_a_n___fxns.html</anchorfile>
      <anchor>afb9589312338fa9434c651560bafd77d</anchor>
      <arglist>)(IALG_Handle algHandle, IRES_Fxns *resFxns)</arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>deactivateResource</name>
      <anchorfile>struct_i_r_e_s_m_a_n___fxns.html</anchorfile>
      <anchor>a2f257a662ceee203f85d27f92f87fda6</anchor>
      <arglist>)(IALG_Handle algHandle, IRES_Fxns *resFxns)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRESMAN_HdVicpParams</name>
    <filename>struct_i_r_e_s_m_a_n___hd_vicp_params.html</filename>
    <member kind="variable">
      <type>IRESMAN_Params</type>
      <name>baseConfig</name>
      <anchorfile>struct_i_r_e_s_m_a_n___hd_vicp_params.html</anchorfile>
      <anchor>af7f3a53efe26e5fc55e354fb2ff08375</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>numResources</name>
      <anchorfile>struct_i_r_e_s_m_a_n___hd_vicp_params.html</anchorfile>
      <anchor>a6954cbbcc7ad4251557b6fb6fb6e5916</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void *</type>
      <name>info</name>
      <anchorfile>struct_i_r_e_s_m_a_n___hd_vicp_params.html</anchorfile>
      <anchor>a3e92352df809d1ac42bdc8c7fd22a722</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRESMAN_Params</name>
    <filename>struct_i_r_e_s_m_a_n___params.html</filename>
    <member kind="variable">
      <type>Int32</type>
      <name>size</name>
      <anchorfile>struct_i_r_e_s_m_a_n___params.html</anchorfile>
      <anchor>a21a3aeee735737e5767d99156dae769e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRESMAN_PersistentAllocFxn *</type>
      <name>allocFxn</name>
      <anchorfile>struct_i_r_e_s_m_a_n___params.html</anchorfile>
      <anchor>ad69d52192d1c92a341b82656762bad3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRESMAN_PersistentFreeFxn *</type>
      <name>freeFxn</name>
      <anchorfile>struct_i_r_e_s_m_a_n___params.html</anchorfile>
      <anchor>a8f3146cbb29a050aad883b46bc9e00ea</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRESMAN_TiledmemoryParams</name>
    <filename>struct_i_r_e_s_m_a_n___tiledmemory_params.html</filename>
    <member kind="variable">
      <type>IRESMAN_Params</type>
      <name>baseConfig</name>
      <anchorfile>struct_i_r_e_s_m_a_n___tiledmemory_params.html</anchorfile>
      <anchor>ae41f3d6524df4e2f70d4f3b16cfe3987</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>numResources</name>
      <anchorfile>struct_i_r_e_s_m_a_n___tiledmemory_params.html</anchorfile>
      <anchor>a2a694e21cec68d304953fcc378f75cde</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void *</type>
      <name>info</name>
      <anchorfile>struct_i_r_e_s_m_a_n___tiledmemory_params.html</anchorfile>
      <anchor>ac67616da6720aabc7c7bad3126cc73ae</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IRESMAN_VicpParams</name>
    <filename>struct_i_r_e_s_m_a_n___vicp_params.html</filename>
    <member kind="variable">
      <type>IRESMAN_Params</type>
      <name>baseConfig</name>
      <anchorfile>struct_i_r_e_s_m_a_n___vicp_params.html</anchorfile>
      <anchor>af538db4fdee7057e68a32664a22d8c13</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RMAN_Params</name>
    <filename>struct_r_m_a_n___params.html</filename>
    <member kind="variable">
      <type>short</type>
      <name>numRegistries</name>
      <anchorfile>struct_r_m_a_n___params.html</anchorfile>
      <anchor>a634fc86d4de527ca05223b36f8e0bf2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRESMAN_PersistentAllocFxn *</type>
      <name>allocFxn</name>
      <anchorfile>struct_r_m_a_n___params.html</anchorfile>
      <anchor>ad115f18b64e09188be8d2094ac41fc53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRESMAN_PersistentFreeFxn *</type>
      <name>freeFxn</name>
      <anchorfile>struct_r_m_a_n___params.html</anchorfile>
      <anchor>ab3319fbf76d2fd7df082ad50ea027a9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRES_YieldFxn</type>
      <name>yieldFxn</name>
      <anchorfile>struct_r_m_a_n___params.html</anchorfile>
      <anchor>abde199a7e3a760e5b0b85d5ec8a9da71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>yieldSamePriority</name>
      <anchorfile>struct_r_m_a_n___params.html</anchorfile>
      <anchor>a2767cefebab08289f0522bdf2940d722</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_IALG</name>
    <title>IALG - XDAIS Algorithm Interface</title>
    <filename>group__ti__xdais___i_a_l_g.html</filename>
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
    <class kind="struct">IALG_MemRec</class>
    <class kind="struct">IALG_Obj</class>
    <class kind="struct">IALG_Params</class>
    <class kind="struct">IALG_Status</class>
    <class kind="struct">IALG_Fxns</class>
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
      <type></type>
      <name>IALG_MemAttrs</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga805f1c1330403c05633277a073862e3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IALG_MemSpace</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga262eb64dc7343999fa07d535ae163497</anchor>
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
      <anchor>ga75c11dac719363507ceb70374f72aacc</anchor>
      <arglist>)(IALG_Handle algHandle, Void *contextArgs)</arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>IRES_ContextRestoreFxn</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga6efda82d9cbe44a6badad08c0807d07b</anchor>
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
      <anchor>ga138778ff0e07cfa1dd96c20e5168a776</anchor>
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
      <type></type>
      <name>IRES_YieldResourceType</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga9a68e109e02bf3f35e832ec4f767d0a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_Status</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga8db6eab013fc4569e080cb4361dfd65b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_RequestMode</name>
      <anchorfile>group___d_s_p_i_r_e_s.html</anchorfile>
      <anchor>ga67d435865304c7bce199194e7ff07963</anchor>
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
    <name>ti_sdo_fc_dskt2_DSKT2</name>
    <title>DSKT2</title>
    <filename>group__ti__sdo__fc__dskt2___d_s_k_t2.html</filename>
    <member kind="function">
      <type>Void</type>
      <name>DSKT2_activateAlg</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gaf946d426d6d9a95040d3967fa746cd7a</anchor>
      <arglist>(Int scratchMutexId, IALG_Handle alg)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>DSKT2_controlAlg</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga65d8c7ae9d40adcda0c92a9e51c6fd0b</anchor>
      <arglist>(IALG_Handle alg, IALG_Cmd cmd, IALG_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IALG_Handle</type>
      <name>DSKT2_createAlg</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga5528d73c34724bc310404da0dc2fbd69</anchor>
      <arglist>(Int scratchMutexId, IALG_Fxns *fxns, IALG_Handle parent, IALG_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>IALG_Handle</type>
      <name>DSKT2_createAlg2</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga427904cdb1e2a776ee6dfd32c6529682</anchor>
      <arglist>(Int scratchMutexId, IALG_Fxns *fxns, IALG_Handle parent, IALG_Params *params, xdc_runtime_IHeap_Handle extHeapId)</arglist>
    </member>
    <member kind="function">
      <type>IALG_Handle</type>
      <name>DSKT2_createAlgExt</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga6d39f16af2214fafad89ba06382a9a79</anchor>
      <arglist>(Int scratchId, IALG_Fxns *fxns, IALG_Handle parent, IALG_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>DSKT2_deactivateAlg</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga74b6b6feca63328906acade37d23b597</anchor>
      <arglist>(Int scratchMutexId, IALG_Handle alg)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>DSKT2_deactivateAll</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga2d252c736a3bb828d9f646cc379ac0e2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Bool</type>
      <name>DSKT2_freeAlg</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga8dffa02b3ca1ff6856ce3cf610be7435</anchor>
      <arglist>(Int scratchMutexId, IALG_Handle alg)</arglist>
    </member>
    <member kind="function">
      <type>Bool</type>
      <name>DSKT2_allocScratch</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga5aa4fbbf031e07f6bf450128ed8bd31d</anchor>
      <arglist>(IALG_Handle alg, Int mutexId, IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>DSKT2_getScratchId</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga4eda7abcc1ed22cb2183b27290e034b0</anchor>
      <arglist>(IALG_Handle alg)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>DSKT2_freeScratch</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga48fad0ce89b1de7f65adb9a06b4276a0</anchor>
      <arglist>(Int mutexId, Void *addr, UInt size)</arglist>
    </member>
    <member kind="function">
      <type>Bool</type>
      <name>DSKT2_allocPersistent</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga3c37794b3c2fbf0070b473c711e275ca</anchor>
      <arglist>(IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>DSKT2_freePersistent</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga6bc8b2ebbadb2f72325c1b297597fc44</anchor>
      <arglist>(IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DSKT2_NUM_SCRATCH_GROUPS</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga6ea3f0bc0c9a697930cf7d8411975ac2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DSKT2_MAX_MEM_ALLOCATION_SIZE</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gab7906673f1c60a08206bd37c7f7d1178</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DSKT2_NUM_SHAREDHEAPS</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gacb5e98129cb03f61436195c9fd240804</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DSKT2_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga10d952cbb68bf248a0fcb6cc92c6b58e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>DSKT2_CacheWBInvFxn</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga6c3fc2026cef662f1d6b3b80d7eda604</anchor>
      <arglist>)(Ptr blockPtr, size_t byteCnt, Bool wait)</arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ DSKT2_CacheWBInvFxn</type>
      <name>DSKT2_cacheWBInvFxn</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga13251e1daaba43dd400d382dbf0dbc58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_daram0Heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gab7668c1e42befc02a40b6312cf5cadb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_daram1Heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga6fdd0cc306ad1247bace4256312617fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_daram2Heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga35657e20f9076dba1406daef4caa81a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_saram0Heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gae1abc75e1d4b699fc94c500c9d6d9251</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_saram1Heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga4a530ac87148ae36343e0e74acc0e123</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_saram2Heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga0ed925016c6378b654dc9b079fd6e698</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_iprogHeap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga3a675912955b528ba4b0b27dfb2805b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_eprogHeap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga09ad1608c1199fbf9d8a5f3ea351be1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>DSKT2_esdataHeap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga252f21bd5d12a0ff250b09ebea3d2c90</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ xdc_runtime_IHeap_Handle</type>
      <name>_DSKT2_heap</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga6637aa74e81ac3663dfc1a7dbcf0fa10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ UInt</type>
      <name>_DSKT2_ALLOW_EXTERNAL_SCRATCH</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga5163b360c871f2c8c4e12d6abbb55868</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ UInt</type>
      <name>_DSKT2_DARAM_SCRATCH_SIZES</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gaa1a9d8512d70e7513183736b4e64a27e</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ UInt</type>
      <name>_DSKT2_SARAM_SCRATCH_SIZES</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>ga7fa8f736c9517857613bab91ccc6f32c</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ Bool</type>
      <name>ti_sdo_fc_dskt2_DSKT2_disableLazyDeactivate</name>
      <anchorfile>group__ti__sdo__fc__dskt2___d_s_k_t2.html</anchorfile>
      <anchor>gaac47654880b79bdf547b27c46361a2cf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_ecpy_ECPY</name>
    <title>ECPY</title>
    <filename>group__ti__sdo__fc__ecpy___e_c_p_y.html</filename>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_configure</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gab36a69debff280508406036c8c998a28</anchor>
      <arglist>(ECPY_Handle handle, ECPY_Params *restrict params, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directConfigure</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gaf0380c28be53fce116f2c56823d61b7e</anchor>
      <arglist>(ECPY_Handle handle, ECPY_Params *restrict params, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_configure16</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga0b7ae91529bc356a3bd81eda9d21a421</anchor>
      <arglist>(ECPY_Handle handle, ECPY_ParamField16b fieldId, unsigned short value, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directConfigure16</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gad27b66a14d13c228eb49b17acbd024aa</anchor>
      <arglist>(ECPY_Handle handle, ECPY_ParamField16b fieldId, unsigned short value, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_configure32</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gaea38193e1199d4a33d4878e916b9b429</anchor>
      <arglist>(ECPY_Handle handle, ECPY_ParamField32b fieldId, unsigned int value, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directConfigure32</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gad46ed17a5d0f1a2a0bc2c7f47aad7fcd</anchor>
      <arglist>(ECPY_Handle handle, ECPY_ParamField32b fieldId, unsigned int value, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_setFinal</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga910393e8b722717de7b84b837adb1921</anchor>
      <arglist>(ECPY_Handle handle, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directSetFinal</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gac377bd43289a832c94c73b20a08c8c26</anchor>
      <arglist>(ECPY_Handle handle, short transferNo)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_setDestinationMemoryMode</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga3101247586aa75cc25a7733c6c4a9679</anchor>
      <arglist>(ECPY_Handle handle, short mode)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_start</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gaf574cd0eabdf2f673009018d7cd3408c</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directStartEdma</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gaf794837c161e60951b4b0c41af37ce1d</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directStartQdma</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gafeab08ae1a1b97bcaa7b207d62df528b</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_wait</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga8adc4be8a9f83b92484dd3aea18d96b1</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_directWait</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga0187836c1fb6e00b16741e5daf69308b</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_activate</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gacc1922d7764bb915e1132d955e4b273f</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>ECPY_Handle</type>
      <name>ECPY_createHandle</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gaf27ccab70603cbf148f46a5068a497e0</anchor>
      <arglist>(IRES_EDMA3CHAN2_Handle handle, IALG_Handle alg)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_deleteHandle</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga7d98039c8cea805547bd8ddde71eff6a</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_deactivate</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga06f88eefc91f79ba958d1dee9e7fbb63</anchor>
      <arglist>(ECPY_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_setEarlyCompletionMode</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga53d14a24649b65b10b817466c7c5b63f</anchor>
      <arglist>(ECPY_Handle handle, short enabled)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_init</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gae699f2d7ac858fecfc83655b3df12037</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>ECPY_exit</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gade95f79a09ed57206ae1236a23c03764</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ti_sdo_fc_ires_NOPROTOCOLREV</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga33eacaa6cefc41cfe527b740449250dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ECPY_GTNAME</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga20a251dafbbc7b6f6b630d65f95882a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ECPY_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga41a9eb2392433a4d485892a130a1a0f6</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">ECPY_Params</class>
    <class kind="struct">ECPY_CfgParams</class>
    <member kind="typedef">
      <type>enum ECPY_ParamField16b</type>
      <name>ECPY_ParamField16b</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gad6043a14cff5cf11e6124f8ad848e060</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum ECPY_ParamField32b</type>
      <name>ECPY_ParamField32b</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga9a316b6b71fa073d355c25ef48ddf9e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum ECPY_TransferType</type>
      <name>ECPY_TransferType</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga5e69c0ab60fd992aaf644c5dae21a983</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ECPY_Obj *</type>
      <name>ECPY_Handle</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga5e6504458adc98bbbaebfd75c6708add</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ECPY_Params</type>
      <name>ECPY_Params</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga85cefc02e34b1ae7d62fb38564c64422</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Bool(</type>
      <name>ECPY_PersistentAllocFxn</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga083c0fc5d0b23680f4ab5ed6da46c61c</anchor>
      <arglist>)(IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="typedef">
      <type>Void(</type>
      <name>ECPY_PersistentFreeFxn</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gac9814ab64fbb1a77a7cc3f267b6a46fb</anchor>
      <arglist>)(IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="typedef">
      <type>Bool(</type>
      <name>ECPY_ScratchAllocFxn</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga98a6fb304f763c2ff1f4d0a99dc1ec1a</anchor>
      <arglist>)(IALG_Handle alg, Int scratchId, IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="typedef">
      <type>Void(</type>
      <name>ECPY_ScratchFreeFxn</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gad4c1411f84b9db63eae9eb41c2068f4b</anchor>
      <arglist>)(Int mutexId, Void *addr, UInt size)</arglist>
    </member>
    <member kind="typedef">
      <type>Int(</type>
      <name>ECPY_getScratchIdFxn</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gab83b6cb5f227392f82a4799278c2ec4c</anchor>
      <arglist>)(IALG_Handle alg)</arglist>
    </member>
    <member kind="typedef">
      <type>struct ECPY_CfgParams</type>
      <name>ECPY_CfgParams</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga54c1cdb98daaa54a05871b834f02037c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ECPY_ParamField16b</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga7d9083dd908144dea99d282b5e4c8b13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ECPY_ParamField32b</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga59f221145cdc648d305f9c2d49ec2f87</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ECPY_TransferType</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>ga263a661327490e9f8226271c6f478011</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ ECPY_CfgParams</type>
      <name>ECPY_CFG_PARAMS</name>
      <anchorfile>group__ti__sdo__fc__ecpy___e_c_p_y.html</anchorfile>
      <anchor>gabcc5234b3b928c407413afc3aa15a92b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_edmamgr_EdmaMgr</name>
    <title>EdmaMgr</title>
    <filename>group__ti__sdo__fc__edmamgr___edma_mgr.html</filename>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_init</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga34b0b3947862ffadce6244b1b2e9bd95</anchor>
      <arglist>(int32_t proc_id, void *edma3_config)</arglist>
    </member>
    <member kind="function">
      <type>EdmaMgr_Handle</type>
      <name>EdmaMgr_alloc</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaf0294a961780a183c7b87ab00bf397d7</anchor>
      <arglist>(int32_t max_linked_transfers)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_getSizesLarge</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga91b956aa648a04f38f3be9d970f6e584</anchor>
      <arglist>(EdmaMgr_ConfigLarge *cfg, IALG_MemRec memTab[])</arglist>
    </member>
    <member kind="function">
      <type>EdmaMgr_Handle</type>
      <name>EdmaMgr_allocLarge</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gabc2860d277c3aeed80d895a679d8eb19</anchor>
      <arglist>(EdmaMgr_ConfigLarge *cfg, IALG_MemRec memTab[])</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_free</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaf4bd48f313ef582613d90a5081963b4d</anchor>
      <arglist>(EdmaMgr_Handle h)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_hwFreeAll</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga52575ab5ae053dcb10c60a5250399d79</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_hwAllocAll</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaa904519337f6802670ea7148a1e0198c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EdmaMgr_wait</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga4195deee760b9295f9805dfe89488f0b</anchor>
      <arglist>(EdmaMgr_Handle h)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy1D1D</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga505e955ac44bbe71bd1e3daab1ea0b2f</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy1D2D</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga875d6e42712a08d57b250a150287e19f</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes, int32_t num_lines, int32_t pitch)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D1D</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga89dfe4a866ec36f8b7adea8b4a5394de</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes, int32_t num_lines, int32_t pitch)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D2D</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga8888b3b0af91f51ad0c3549d7b3a8cce</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes, int32_t num_lines, int32_t pitch)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D2DSep</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gae6633520a0b320b377b5b033cc141c5c</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes, int32_t num_lines, int32_t src_pitch, int32_t dst_pitch)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy1D1DLinked</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gab68d6b8da1b15f9824f510a779a726ce</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src[], void *restrict dst[], int32_t num_bytes[], int32_t num_transfers)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy1D2DLinked</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaa0686f84566bf694809e5389a511a9f8</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src[], void *restrict dst[], int32_t num_bytes[], int32_t num_lines[], int32_t pitch[], int32_t num_transfers)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D1DLinked</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga788194a05f15b3f2ea2c619d469d0194</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src[], void *restrict dst[], int32_t num_bytes[], int32_t num_lines[], int32_t pitch[], int32_t num_transfers)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D2DLinked</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaf45b4c568858e438198ca56f6f5737a1</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src[], void *restrict dst[], int32_t num_bytes[], int32_t num_lines[], int32_t pitch[], int32_t num_transfers)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D2DSepLinked</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga5cf14039980959b3dac0af544d3adeef</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src[], void *restrict dst[], int32_t num_bytes[], int32_t num_lines[], int32_t src_pitch[], int32_t dst_pitch[], int32_t num_transfers)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy1D2DLarge</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga07c5095814d61fe51d9293aded7e9233</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes, int32_t num_lines, int32_t pitch)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copy2D1DLarge</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga971ca76b7244813602ab33412b8de285</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst, int32_t num_bytes, int32_t num_lines, int32_t pitch)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copyFast</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga6aebdb61c28a58f0e63f03fce243ba9d</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src, void *restrict dst)</arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>EdmaMgr_copyLinkedFast</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga9cbf51d816c26038cbc11e3b63b8fd31</anchor>
      <arglist>(EdmaMgr_Handle h, void *restrict src[], void *restrict dst[], int32_t num_transfers)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_SUCCESS</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaa8024d7e4cec1168dff2cb1ef7e9962f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_ERROR_INVARG</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga16c73229c0977d6a712c854bc7a81c36</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_ERROR_INVCFG</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga1de726847679ee71afd50006d878185e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_ERROR_RMANINIT</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga0d07816b60be478a71c08f4d1fde9bcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_ERROR_INVHANDLE</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gad2c98139c17fa8698697129e14d8dc7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_ERROR_FREE</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga547518dd36d8c845f7dfbd75fa7d5a96</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EdmaMgr_MAX_NUM_MEMRECS_LARGE</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gaa29f173a399a3b514c608c40b375d1af</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">_EdmaMgr_ConfigLarge</class>
    <member kind="typedef">
      <type>void *</type>
      <name>EdmaMgr_Handle</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>gad100f526edd5ac876ba81ae8a78d4e00</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct _EdmaMgr_ConfigLarge</type>
      <name>EdmaMgr_ConfigLarge</name>
      <anchorfile>group__ti__sdo__fc__edmamgr___edma_mgr.html</anchorfile>
      <anchor>ga7d68c85b3f0cba1c17fcb223ef89a9a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_ires_IRESMAN</name>
    <title>Resource manager interface</title>
    <filename>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</filename>
    <class kind="struct">IRESMAN_Params</class>
    <class kind="struct">IRESMAN_Fxns</class>
    <class kind="struct">IRESMAN_ConstructArgs</class>
    <member kind="typedef">
      <type>Bool(</type>
      <name>IRESMAN_PersistentAllocFxn</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>gace2b51f833e4570240469eb3a379ff96</anchor>
      <arglist>)(IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="typedef">
      <type>Void(</type>
      <name>IRESMAN_PersistentFreeFxn</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>ga99674bfeffe75b236ebe916e4f588237</anchor>
      <arglist>)(IALG_MemRec *memTab, Int numRecs)</arglist>
    </member>
    <member kind="typedef">
      <type>struct IRESMAN_Params</type>
      <name>IRESMAN_Params</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>ga2a8b6374104f86177742127e0e9db690</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRESMAN_Fxns</type>
      <name>IRESMAN_Fxns</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>ga3ccaac5d069a8c8d1f136c29bf3cbeb0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRESMAN_ConstructArgs</type>
      <name>IRESMAN_ConstructArgs</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>ga93fe96948b8c064f1244daae12abba54</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRESMAN_ConstructFxns</type>
      <name>IRESMAN_ConstructFxns</name>
      <anchorfile>group__ti__sdo__fc__ires___i_r_e_s_m_a_n.html</anchorfile>
      <anchor>gab9da36e13f19c05d045611d22e23f184</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_memutils_MEMUTILS</name>
    <title>MEMUTILS</title>
    <filename>group__ti__sdo__fc__memutils___m_e_m_u_t_i_l_s.html</filename>
    <member kind="function">
      <type>Void</type>
      <name>MEMUTILS_cacheInv</name>
      <anchorfile>group__ti__sdo__fc__memutils___m_e_m_u_t_i_l_s.html</anchorfile>
      <anchor>gad07c8ac40bec004e2cc0a386f86570dd</anchor>
      <arglist>(Ptr addr, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>MEMUTILS_cacheWb</name>
      <anchorfile>group__ti__sdo__fc__memutils___m_e_m_u_t_i_l_s.html</anchorfile>
      <anchor>ga9ec3a005cfbd44003b9dc57e737d32b1</anchor>
      <arglist>(Ptr addr, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>MEMUTILS_cacheWbInv</name>
      <anchorfile>group__ti__sdo__fc__memutils___m_e_m_u_t_i_l_s.html</anchorfile>
      <anchor>ga3ecacfd8a0771af6d1a532fbbe35adfe</anchor>
      <arglist>(Ptr addr, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Void *</type>
      <name>MEMUTILS_getPhysicalAddr</name>
      <anchorfile>group__ti__sdo__fc__memutils___m_e_m_u_t_i_l_s.html</anchorfile>
      <anchor>gae67c1ceb1e529cbb9b10abee89101f75</anchor>
      <arglist>(Ptr addr)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MEMUTILS_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__memutils___m_e_m_u_t_i_l_s.html</anchorfile>
      <anchor>gaad6bedcf19bfc91b3b86ae7640ea7a9e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_rman_RMAN</name>
    <title>Resource Manager for IRES-based resources</title>
    <filename>group__ti__sdo__fc__rman___r_m_a_n.html</filename>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_init</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga2553157eede6b63b0037b0db72fbdae8</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_exit</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gaedbbc06da21c2e842c890d4ff4ac9aed</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_register</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gae8fe0e0bcdcb46afb0d09d1997136347</anchor>
      <arglist>(IRESMAN_Fxns *resmanFxns, IRESMAN_Params *initArgs)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_unregister</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gaa6f966711380ecf89ad79db2ebf8619a</anchor>
      <arglist>(IRESMAN_Fxns *resmanFxns)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_assignResources</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gaa7772ccd9856ccc0b0492c018807b2b3</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Fxns *resFxns, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_allocateResources</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga0fdeaec06650e512ffd765613a3accaf</anchor>
      <arglist>(Int requestId, IRES_ResourceDescriptor *resDesc, Int numResources, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_freeResources</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga98911d4d4049d1805ae9eac2b71d9ec0</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Fxns *resFxns, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_freeAllocatedResources</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gafac26c9edf744af2d0b1f4f24862975b</anchor>
      <arglist>(Int requestId, IRES_ResourceDescriptor *resDesc, Int numResources, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_activateResource</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga3135611a668b07aad926247bbd0e37a9</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Handle resourceHandle, IRES_Fxns *resFxns, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_activateAllResources</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga354e1ad9ac34e6c41b0bd2184bc3e9fb</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Fxns *resFxns, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_deactivateResource</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga1c20b46e28a17783654674f9e109e46e</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Handle resourceHandle, IRES_Fxns *resFxns, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>RMAN_deactivateAllResources</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga7343843e4acd15df9997315b4cb9bcf3</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Fxns *resFxns, Int scratchGroupId)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RMAN_yield</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gaa9da95739776c293fb4e27ec5207a668</anchor>
      <arglist>(IRES_YieldResourceType resource, IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RMAN_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga2df9395a0c498e45a8fb68942197a9eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RMAN_GTNAME</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga548fc91df8bfb9a8a30cbaab812110c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RMAN_PROTOCOLNAMESIZE</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga69dd3d9e63a604b0cb10037c60bfd4fa</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">RMAN_Params</class>
    <member kind="typedef">
      <type>struct Sem_Obj *</type>
      <name>RMAN_SemHandle</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga841a70da51acb69fde1f53d60faae1bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IRES_YieldArgs(*</type>
      <name>ti_sdo_fc_rman_RMAN_YieldArgsFxn</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gafe7fe1defb485927628dfa78dd2ebe97</anchor>
      <arglist>)(Int scratchId, Bool yieldFlag)</arglist>
    </member>
    <member kind="typedef">
      <type>struct RMAN_Params</type>
      <name>RMAN_Params</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga2b477ea38c1ae71bc320a1384f6b536e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ RMAN_Params</type>
      <name>RMAN_PARAMS</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gae12d774b050c8c27f780ed91dd7c2a33</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_Fxns *</type>
      <name>RMAN_TABLE</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gab2ff62cddcbbbd3c6a2819703a96bcca</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ short</type>
      <name>RMAN_FREE_ENTRIES</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga758ab45c1418c384bf578ea5558b9d7b</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ short</type>
      <name>RMAN_numRegistryEntries</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga60e319affb35f0df44bfa9e5576cbd05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_Fxns **</type>
      <name>RMAN_registryEntries</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gae4b796a7aead262ea31848120b07d54d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_Params **</type>
      <name>RMAN_registryResmanArgs</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga4a461e9e2f1b613ef55dbe4574abd5b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ unsigned int **</type>
      <name>RMAN_iresVTable</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga343604b8ef45f3565e25b0ea911a4173</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ unsigned int</type>
      <name>ti_sdo_fc_rman_RMAN_MAXALGS</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>ga8ec03181fc11e30d8c10c7eb54d248d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UInt32</type>
      <name>ti_sdo_fc_rman_RMAN_ipcKey</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gaa67b89289e5ff8dab19e2c011417dabb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ti_sdo_fc_rman_RMAN_YieldArgsFxn</type>
      <name>ti_sdo_fc_rman_RMAN_setYieldArgs</name>
      <anchorfile>group__ti__sdo__fc__rman___r_m_a_n.html</anchorfile>
      <anchor>gacfc9b966702c5a037e299e8b7b016ce3</anchor>
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
  <compound kind="group">
    <name>ti_sdo_fc_ires_edma3chan_IRES_EDMA3CHAN</name>
    <title>IRES EDMA3 Protocol</title>
    <filename>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_PROTOCOLNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gaf4730270fcd589bd84292642aa0767ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EDMA3CHAN_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gab7814ae21cc501d4882aaeb43153fc0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_PROTOCOLREVISION_1_0_0</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga3e72cddac269ede3215c67681bd06358</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_SETPROTOCOLREVISION_1_0_0</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gabc9fa9788be85eddc9696b9a778270c9</anchor>
      <arglist>(rev)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_PROTOCOLREVISION_2_0_0</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gafaf0878b09c1cc9708821d19d801e182</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_SETPROTOCOLREVISION_2_0_0</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga13b7ccd6e711b7469b8823a5c957b536</anchor>
      <arglist>(rev)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_MAXPARAMS</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga8510375de41242e3526a4afa007e131a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_MAXTCCS</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga18eb05e3510d748f04269c39cce62733</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_NUMDESTTYPES</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gadb7b5e24785c0749d8717e0d740ebdd4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_PARAM_ANY</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga2b610a75bc94fcf953c9c2c5a5884847</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_PARAM_NONE</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga06bed242a94eb48126e04f267f0d4895</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_TCC_ANY</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga3dad6458e12ad42c2158727991822037</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_TCC_NONE</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga1920c58bedf3e0cc0609b86ec384c892</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_EDMACHAN_ANY</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gae3c157030381908d1353fccf406fdd38</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_QDMACHAN_ANY</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga0b99333ee5984dab27d5d84c05b63078</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_EDMA3CHAN_CHAN_NONE</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gae4140c679d6eaaf4d20dc4554995edf3</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRES_EDMA3CHAN_PaRamStruct</class>
    <class kind="struct">IRES_EDMA3CHAN_ProtocolArgs</class>
    <class kind="struct">IRES_EDMA3CHAN_Obj</class>
    <class kind="struct">IRES_EDMA3CHAN_EDMA3ShadowRegister</class>
    <class kind="struct">IRES_EDMA3CHAN_EDMA3DraeRegister</class>
    <class kind="struct">IRES_EDMA3CHAN_EDMA3RegisterLayer</class>
    <class kind="struct">IRES_EDMA3CHAN_Properties</class>
    <class kind="struct">IRES_EDMA3CHAN2_Obj</class>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_Obj *</type>
      <name>IRES_EDMA3CHAN_Handle</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga44e66cb70f336bdb105e54983930c8e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN2_Obj *</type>
      <name>IRES_EDMA3CHAN2_Handle</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gac7ec31fb6115f2df8b43f0a66d3bb09f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_PaRamStruct</type>
      <name>IRES_EDMA3CHAN_PaRamStruct</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga3d1f7dd722d7b1eac3940a6d0eff63c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_ProtocolArgs</type>
      <name>IRES_EDMA3CHAN_ProtocolArgs</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga4f0e8e331a7135fa21c62da8e1d3fced</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_Obj</type>
      <name>IRES_EDMA3CHAN_Obj</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga8910a3fc26939a5f592191fb4400d0d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_EDMA3ShadowRegister</type>
      <name>IRES_EDMA3CHAN_EDMA3ShadowRegister</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gaa2977a19f877b1d3cf7538c3457db58d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_EDMA3DraeRegister</type>
      <name>IRES_EDMA3CHAN_EDMA3DraeRegister</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga0a01c3ca97f02a526edb0360eff504ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_EDMA3RegisterLayer</type>
      <name>IRES_EDMA3CHAN_EDMA3RegisterLayer</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga2ceee1967c04a37f016e0184b5f6040d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN_Properties</type>
      <name>IRES_EDMA3CHAN_Properties</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga271d231160ea9cf90f4387b7aecfb34e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_EDMA3CHAN_DmaDestType</type>
      <name>IRES_EDMA3CHAN_DmaDestType</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gaa2c61cb7db74a0e2cef3e3c66c383b68</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_EDMA3CHAN2_Obj</type>
      <name>IRES_EDMA3CHAN2_Obj</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga5734d8411fde66f0d75892044293e9f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_EDMA3CHAN_DmaDestType</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga6cbd16008d4c8eb007e03412b12fc778</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_ires_edma3chan_IRESMAN_EDMA3CHAN</name>
    <title>IRESMAN EDMA3 -</title>
    <filename>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</filename>
    <member kind="function">
      <type>String</type>
      <name>IRESMAN_EDMA3CHAN_getProtocolName</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gaeb774220d0deb5da8bbfe8aa25c15094</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_ProtocolRevision *</type>
      <name>IRESMAN_EDMA3CHAN_getProtocolRevision</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga695084a1271cf138b383a2a7c42e1e20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_EDMA3CHAN_init</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga941b3ff64286bcfaa3bb5205bb669d55</anchor>
      <arglist>(IRESMAN_Params *initArgs)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_EDMA3CHAN_exit</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gac67268cf9b8f5bf523caffebfe8dc148</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Handle</type>
      <name>IRESMAN_EDMA3CHAN_getHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gad30ebcbc0fed976c39cdf716677b2080</anchor>
      <arglist>(IALG_Handle algHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId, IRES_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_EDMA3CHAN_freeHandle</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gabd5e4de994bdaf06fe5a45f5c41fe265</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Handle algResourceHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId)</arglist>
    </member>
    <class kind="struct">IRESMAN_Edma3ChanParams</class>
    <member kind="typedef">
      <type>struct IRESMAN_Edma3ChanParams</type>
      <name>IRESMAN_Edma3ChanParams</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga6f72d404957e3bde256dab036a6ee460</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentAllocFxn</type>
      <name>_RMAN_allocPersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>gaadc2b94c8a7fe6dd08fcc18deec7d992</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentFreeFxn</type>
      <name>_RMAN_freePersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga0c23ac2d5d2854f5941c0b3098790df1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRESMAN_Fxns</type>
      <name>IRESMAN_EDMA3CHAN</name>
      <anchorfile>group__ti__sdo__fc__ires__edma3chan___i_r_e_s_m_a_n___e_d_m_a3_c_h_a_n.html</anchorfile>
      <anchor>ga7fb20979fe105a5310a48f2b2ccaf8c4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_ires_hdvicp_IRES_HDVICP</name>
    <title>IRES HDVICP Protocol</title>
    <filename>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP_PROTOCOLNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>gaf41453e3afb59b32d1a0c41961fe50a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HDVICP_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>gab17613f289eb3239624de87c31d57116</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRES_HDVICP_ProtocolArgs</class>
    <class kind="struct">IRES_HDVICP_Obj</class>
    <class kind="struct">IRES_HDVICP_RegisterLayer</class>
    <class kind="struct">IRES_HDVICP_Properties</class>
    <member kind="typedef">
      <type>struct IRES_HDVICP_Obj *</type>
      <name>IRES_HDVICP_Handle</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>gafcb53c4662e46499ee68c7dfad662bfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_HDVICP_RequestType</type>
      <name>IRES_HDVICP_RequestType</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga4019a15f38f2854f0e52f457d724449b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP_ProtocolArgs</type>
      <name>IRES_HDVICP_ProtocolArgs</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga0aeea51623159606d5bc6a7a15ed4043</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP_Obj</type>
      <name>IRES_HDVICP_Obj</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>gad85f85ba4b0fdaf7cf9e8921cad229fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP_RegisterLayer</type>
      <name>IRES_HDVICP_RegisterLayer</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga36d6cd1fdd8c0a88840e5b6af0fabd0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP_Properties</type>
      <name>IRES_HDVICP_Properties</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga7a41d6c63373b559c3fc5ee90280d4ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_HDVICP_RequestType</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga995d4dd1dfb80daa5eb01690cc33cc7f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_ires_hdvicp_IRES_HDVICP2</name>
    <title>IRES HDVICP2 Protocol</title>
    <filename>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP2_PROTOCOLNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga6e9fc2b0904862eb35cf23ec5d06fd31</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HDVICP2_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga9c465c385b96523dd172495898a2a648</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP2_ID_ANY</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga5036e671af0585ea57d8e0197e4e90ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP2_ID_LATE_ACQUIRE</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga64e2059f8468faeac050da0d3db026f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP2_INVALID_ADDR</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga58cf2d89d0831f062da6b1392dc2630a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP2_TIMEOUTFOREVER</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga02602060d994d0ee40fade0f38475687</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP2_UNKNOWNLATEACQUIREARG</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga89573d4d420b01f3b2c3bedb20e52dab</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRES_HDVICP2_ProtocolArgs</class>
    <class kind="struct">IRES_HDVICP2_Obj</class>
    <class kind="struct">IRES_HDVICP2_RegisterLayer</class>
    <class kind="struct">IRES_HDVICP2_Properties</class>
    <member kind="typedef">
      <type>struct IRES_HDVICP2_Obj *</type>
      <name>IRES_HDVICP2_Handle</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>gadd0f77cea05c41ade2f2f6c29937eb7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IRES_YieldArgs(*</type>
      <name>ti_sdo_fc_ires_hdvicp_HDVICP2_GetYieldArgsFxn</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga983c2886f86746cf7d0d428e3474c916</anchor>
      <arglist>)(Int scratchId)</arglist>
    </member>
    <member kind="typedef">
      <type>Void(*</type>
      <name>ti_sdo_fc_ires_hdvicp_HDVICP2_YieldFxn</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga5f7f18c485cdc75a0fb2f225edf9dcd1</anchor>
      <arglist>)(IRES_YieldResourceType resource, IRES_YieldContextHandle ctxt, IRES_YieldArgs args)</arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP2_ProtocolArgs</type>
      <name>IRES_HDVICP2_ProtocolArgs</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga01d21d4eea4b38bba75890a474f5e146</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>IRES_HDVICP2_CallbackFxn</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga4f26754ef203eaeece311f2695dcbe6a</anchor>
      <arglist>)(IALG_Handle handle, Void *args)</arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_HDVICP2_Status</type>
      <name>IRES_HDVICP2_Status</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga4d0929cc91ef9058c626bc3f8eb5a580</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP2_Obj</type>
      <name>IRES_HDVICP2_Obj</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>gab164d36df22fa1187459bf656fb41f83</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP2_RegisterLayer</type>
      <name>IRES_HDVICP2_RegisterLayer</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>gab207e5ba3c1be67f41aca898cd1af06c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_HDVICP2_Properties</type>
      <name>IRES_HDVICP2_Properties</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga347620d5e79bdf4a441045fe9a5efc21</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IRES_Status(*</type>
      <name>ti_sdo_fc_ires_hdvicp_HDVICP2_GetHdvicp2Fxn</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga4145e66e0498a362506bc9994136d1eb</anchor>
      <arglist>)(XDAS_Int32 *Id, IALG_Handle alg, IRES_HDVICP2_Handle handle)</arglist>
    </member>
    <member kind="typedef">
      <type>IRES_Status(*</type>
      <name>ti_sdo_fc_ires_hdvicp_HDVICP2_FreeHdvicp2Fxn</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga52891d16a972bf3795668fce2a069537</anchor>
      <arglist>)(XDAS_Int32 Id, IALG_Handle alg, IRES_HDVICP2_Handle handle)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_HDVICP2_Status</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga918fdab9a544c5ffcc1e76117d0f79f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>ti_sdo_fc_ires_hdvicp_HDVICP2_timeoutVal</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s___h_d_v_i_c_p2.html</anchorfile>
      <anchor>ga5b423e92e03fa325059695a892b2af42</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_ires_hdvicp_IRESMAN_HDVICP</name>
    <title>IRESMAN PROTOCOL - HDVICP</title>
    <filename>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</filename>
    <member kind="function">
      <type>String</type>
      <name>IRESMAN_HDVICP_getProtocolName</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga263a6e5378a5a80ec72cbe1e1996d4e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_ProtocolRevision *</type>
      <name>IRESMAN_HDVICP_getProtocolRevision</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga1e6757007676bb59bc49b976c7082d68</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_HDVICP_init</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga9b2d49524494e6c589a17b8d3f6e2b83</anchor>
      <arglist>(IRESMAN_Params *initArgs)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_HDVICP_exit</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga66e789620a153083717fe8b73f576ad8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Handle</type>
      <name>IRESMAN_HDVICP_getHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga91dcd1ec36206aeb58649b7361d7904b</anchor>
      <arglist>(IALG_Handle algHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId, IRES_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_HDVICP_freeHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga8082e13e6d0f726991c2e78659f7d82c</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Handle algResourceHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_HDVICP_MAXRESOURCES</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga626db578ddcda783f8354c734b51a876</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRESMAN_HdVicpParams</class>
    <member kind="typedef">
      <type>struct IRESMAN_HdVicpParams</type>
      <name>IRESMAN_HdVicpParams</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>gaa0cc26209d78b2914c0353319983e7b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentAllocFxn</type>
      <name>_RMAN_allocPersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>gaadc2b94c8a7fe6dd08fcc18deec7d992</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentFreeFxn</type>
      <name>_RMAN_freePersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga0c23ac2d5d2854f5941c0b3098790df1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRESMAN_Fxns</type>
      <name>IRESMAN_HDVICP</name>
      <anchorfile>group__ti__sdo__fc__ires__hdvicp___i_r_e_s_m_a_n___h_d_v_i_c_p.html</anchorfile>
      <anchor>ga3f269556325eb4b7ac1b7aad594e3f6c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_ires_tiledmemory_IRES_TILEDMEMORY</name>
    <title>IRES TILEDMEMORY Protocol (Beta)</title>
    <filename>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>IRES_TILEDMEMORY_PROTOCOLNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga68b4b8898e77e090fd96541494fa6422</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TILEDMEMORY_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga623d30fd5f51a591fb1d7ba6bedd0dab</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRES_TILEDMEMORY_ProtocolArgs</class>
    <class kind="struct">IRES_TILEDMEMORY_Obj</class>
    <class kind="struct">IRES_TILEDMEMORY_RegisterLayer</class>
    <class kind="struct">IRES_TILEDMEMORY_Properties</class>
    <member kind="typedef">
      <type>struct IRES_TILEDMEMORY_Obj *</type>
      <name>IRES_TILEDMEMORY_Handle</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga30b122a78fafc18f16f4b584c55ddf39</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_TILEDMEMORY_AccessDimension</type>
      <name>IRES_TILEDMEMORY_AccessDimension</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gaa6cd7292c7e04c77735f0d9b2c0e6a47</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>enum IRES_TILEDMEMORY_AccessUnit</type>
      <name>IRES_TILEDMEMORY_AccessUnit</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga9a4638e18510604f93bafbaac2d85917</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_TILEDMEMORY_ProtocolArgs</type>
      <name>IRES_TILEDMEMORY_ProtocolArgs</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga87e40295a0e896827ff16239c6677182</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_TILEDMEMORY_Obj</type>
      <name>IRES_TILEDMEMORY_Obj</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga7bd47c3771425981890d1973719bc4e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_TILEDMEMORY_RegisterLayer</type>
      <name>IRES_TILEDMEMORY_RegisterLayer</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gae5bceac65ea5bf226b3985d0a45703a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_TILEDMEMORY_Properties</type>
      <name>IRES_TILEDMEMORY_Properties</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga3a240a3b912b366e5925b5d4348fe2cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_TILEDMEMORY_AccessDimension</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga6bf19883a3a359c69a7a7cc98b9fb974</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IRES_TILEDMEMORY_AccessUnit</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gac19627dfd380195372144adab80be234</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_ires_tiledmemory_IRESMAN_TILEDMEMORY</name>
    <title>IRESMAN TILEDMEM</title>
    <filename>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</filename>
    <member kind="function">
      <type>String</type>
      <name>IRESMAN_TILEDMEMORY_getProtocolName</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gabea58ade569b614d4b8c55f455ea2833</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_ProtocolRevision *</type>
      <name>IRESMAN_TILEDMEMORY_getProtocolRevision</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga4832f10ae177316cf1e73a29c6713531</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_TILEDMEMORY_init</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gaf0587262c783dfdf65faaaf6eea0807a</anchor>
      <arglist>(IRESMAN_Params *initArgs)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_TILEDMEMORY_exit</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga9415a0ced325b5467295b8771e52d304</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Handle</type>
      <name>IRESMAN_TILEDMEMORY_getHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gadfa289400bc20009f0a0758bc7087aea</anchor>
      <arglist>(IALG_Handle algHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId, IRES_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_TILEDMEMORY_freeHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gac62245768c47931560eeed6d7d73e02b</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Handle algResourceHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_TILEDMEMORY_MAXRESOURCES</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga397775317ba851a3c541c861dc455c67</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRESMAN_TiledmemoryParams</class>
    <member kind="typedef">
      <type>struct IRESMAN_TiledmemoryParams</type>
      <name>IRESMAN_TiledmemoryParams</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga53b69a325a2aef702b5627cc01f49400</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentAllocFxn</type>
      <name>_RMAN_allocPersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gaadc2b94c8a7fe6dd08fcc18deec7d992</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentFreeFxn</type>
      <name>_RMAN_freePersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>ga0c23ac2d5d2854f5941c0b3098790df1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRESMAN_Fxns</type>
      <name>IRESMAN_TILEDMEMORY</name>
      <anchorfile>group__ti__sdo__fc__ires__tiledmemory___i_r_e_s_m_a_n___t_i_l_e_d_m_e_m_o_r_y.html</anchorfile>
      <anchor>gab09c8ecb9ece591a08a86b0b4a51ee23</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_ires_vicp_IRES_VICP</name>
    <title>IRES VICP Protocol</title>
    <filename>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>IRES_VICP_MAXRESOURCES</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>gab443b20263d6d15d38353016d2caef35</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IRES_VICP_PROTOCOLNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>ga8f238b30de8eb64ef69362f215837eb0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VICP_MODNAME</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>ga6ed720f53f0ec97580795ac36998cc32</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">IRES_VICP_ProtocolArgs</class>
    <class kind="struct">IRES_VICP_Obj</class>
    <class kind="struct">IRES_VICP_Registers</class>
    <class kind="struct">IRES_VICP_Properties</class>
    <member kind="typedef">
      <type>struct IRES_VICP_Obj *</type>
      <name>IRES_VICP_Handle</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>gaa23fbe3626f54ecc7754e908083f5f14</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_VICP_ProtocolArgs</type>
      <name>IRES_VICP_ProtocolArgs</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>ga6b0466ea2e923232a5f2bf5d99b83663</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_VICP_Obj</type>
      <name>IRES_VICP_Obj</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>ga78dd89d90d8364d4ff126b4647228819</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_VICP_Registers</type>
      <name>IRES_VICP_Registers</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>ga12d9b10adf3be5345c5acf16def14707</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IRES_VICP_Properties</type>
      <name>IRES_VICP_Properties</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s___v_i_c_p.html</anchorfile>
      <anchor>gad8355b5acd95ef810245a947c87a3847</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_fc_ires_vicp_IRESMAN_VICP</name>
    <title>IRESMAN PROTOCOL - VICP</title>
    <filename>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</filename>
    <member kind="function">
      <type>String</type>
      <name>IRESMAN_VICP_getProtocolName</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga4bf0fa4a35386dcd6f04c16a468984dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_ProtocolRevision *</type>
      <name>IRESMAN_VICP_getProtocolRevision</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga01841f095420ce69ce02aaf644d7250d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_VICP_init</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga613cdf62d35efa5fb1a02f9e07c73dd9</anchor>
      <arglist>(IRESMAN_Params *initArgs)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_VICP_exit</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga5d1eb79a6ad9c7a9e75fe48d70a2da58</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IRES_Handle</type>
      <name>IRESMAN_VICP_getHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga64636048ebc7e7a1a41e96552297f022</anchor>
      <arglist>(IALG_Handle algHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId, IRES_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IRES_Status</type>
      <name>IRESMAN_VICP_freeHandles</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>gaa7bb21ce4147fab50131169877ab7f37</anchor>
      <arglist>(IALG_Handle algHandle, IRES_Handle algResourceHandle, IRES_ResourceDescriptor *resDesc, Int scratchGroupId)</arglist>
    </member>
    <class kind="struct">IRESMAN_VicpParams</class>
    <member kind="typedef">
      <type>struct IRESMAN_VicpParams</type>
      <name>IRESMAN_VicpParams</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga29f8ab6aaf9a18490216e300f12d2522</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentAllocFxn</type>
      <name>_RMAN_allocPersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>gaadc2b94c8a7fe6dd08fcc18deec7d992</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>__FAR__ IRESMAN_PersistentFreeFxn</type>
      <name>_RMAN_freePersistent</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga0c23ac2d5d2854f5941c0b3098790df1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IRESMAN_Fxns</type>
      <name>IRESMAN_VICP</name>
      <anchorfile>group__ti__sdo__fc__ires__vicp___i_r_e_s_m_a_n___v_i_c_p.html</anchorfile>
      <anchor>ga45a0fdbcf9e8610a403161583983578d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>Disclaimer</name>
    <title></title>
    <filename>_disclaimer</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Framework Components API Reference</title>
    <filename>index</filename>
    <docanchor file="index" title="Modules">modules</docanchor>
  </compound>
</tagfile>
