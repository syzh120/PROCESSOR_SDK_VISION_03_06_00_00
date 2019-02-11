
SECTIONS
{
    .tidl_lib_txtdata
    {
       *dmautils.lib<*.o*>(.text)
       *tidl_algo.lib<*kernel*.o*>(.text)
       *tidl_algo.lib<*alg*.o*>(.text)
    } align = 0x8000 > EVE4_CODE_MEM PAGE 1

    .tidl_lib_fardata
    {
       *tidl_algo.lib<*.o*> (.far)
       *tidl_algo.lib<*.o*> (.const)
    }  > DMEM  PAGE 1
    .edma_utils_lib_fardata
    {
    *dmautils.lib<*.o*> (.bss)
    *dmautils.lib<*.o*> (.const)
    }  > DMEM  PAGE 1

    .ttbSection > EVE4_DATA_MEM PAGE 1
}
