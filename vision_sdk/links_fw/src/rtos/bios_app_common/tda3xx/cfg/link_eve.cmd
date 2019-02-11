

IMEML_SIZE = 0x4000;
IMEMH_SIZE = 0x4000;
WMEM_SIZE  = 0x7E00;

SECTIONS
{
    .tidl_lib_txtdata
    {
       *dmautils.lib<*.o*>(.text)
       *tidl_algo.lib<*kernel*.o*>(.text)
       *tidl_algo.lib<*alg*.o*>(.text)
    } align = 0x8000 > EVE1_CODE_MEM PAGE 1

    .tidl_lib_fardata
    {
        *tidl_algo.lib<*.o*>(.far)
    }  > DMEM  PAGE 1

    .edma_utils_lib_fardata
    {
        *dmautils.lib<*.o*>(.const)
    }  > DMEM  PAGE 1

    .ttbSection > EVE1_DATA_MEM PAGE 1
}