function MMU_init()
{
    var MMU = xdc.useModule('ti.sysbios.family.arm.a15.Mmu');

    // Enable the MMU (Required for L1/L2 data caching)
    MMU.enableMMU = true;

    // Write memory region attribute in mairRegAttr[1] i.e. MAIR0 Reg Byte1
    MMU.setMAIRMeta(3, 0xEE);               // Mark mem regions as normal, outer- and inner- cacheable, read-allocate

    // Write memory region attribute in mairRegAttr[1] i.e. MAIR0 Reg Byte1
    MMU.setMAIRMeta(4, 0x00);               // Mark mem regions as strongly-ordered, non-cacheable

    // Write memory region attribute in mairRegAttr[2] i.e. MAIR0 Reg Byte2
    MMU.setMAIRMeta(5, 0xFF);              // Mark mem regions as normal, outer- and inner- cacheable, read/write-allocate


    // Region for program code and data
    var attrs = new MMU.DescriptorAttrs();
    MMU.initDescAttrsMeta(attrs);
    attrs.type = MMU.DescriptorType_BLOCK;    // BLOCK descriptor
    attrs.shareable = 0;                      // non-shareable
    attrs.attrIndx = 5;                       // MAIR0 byte 5 describes memory attributes for this level2 entry
    // Set the descriptor for each entry in the address range
    for (var i=0x40000000; i < 0x40600000; i = i + 0x00200000)
    {
        // Each 'BLOCK' descriptor entry spans a 2MB address range
        MMU.setSecondLevelDescMeta(i, i, attrs);
    }
    // Set the descriptor for each entry in the address range
    for (var i=0x80000000; i < 0xA0000000; i = i + 0x00200000)
    {
        // Each 'BLOCK' descriptor entry spans a 2MB address range
        MMU.setSecondLevelDescMeta(i, i, attrs);
    }


    // Region for packet data buffers (reuse same attribute field in MAIR0 byte 3)
    var attrs = new MMU.DescriptorAttrs();
    MMU.initDescAttrsMeta(attrs);
    attrs.type = MMU.DescriptorType_BLOCK;    // BLOCK descriptor
    attrs.noExecute = true;                   // not executable
    attrs.shareable = 0;                      // non-shareable
    attrs.accPerm = 0;                        // read/write at PL1
    attrs.attrIndx = 3;                       // MAIR0 byte 3 describes memory attributes for this level2 entry
    // Set the descriptor for each entry in the address range
    for (var i=0x8E000000; i < 0x90000000; i = i + 0x00200000)
    {
        // Each 'BLOCK' descriptor entry spans a 2MB address range
        MMU.setSecondLevelDescMeta(i, i, attrs);
    }


    // Device Memory for peripheral region
    var attrs = new MMU.DescriptorAttrs();
    MMU.initDescAttrsMeta(attrs);
    attrs.type = MMU.DescriptorType_BLOCK;    // BLOCK descriptor
    attrs.noExecute = true;                   // not executable
    attrs.accPerm = 0;                        // read/write at PL1
    attrs.attrIndx = 4;                       // MAIR0 byte 4 describes memory attributes for this level2 entry
    // Configure the corresponding MMU page descriptor accordingly
    for (var i=0x40600000; i < 0x60000000; i = i + 0x00200000)
    {
        // Each 'BLOCK' descriptor entry spans a 2MB address range
        MMU.setSecondLevelDescMeta(i, i, attrs);
    }
}
