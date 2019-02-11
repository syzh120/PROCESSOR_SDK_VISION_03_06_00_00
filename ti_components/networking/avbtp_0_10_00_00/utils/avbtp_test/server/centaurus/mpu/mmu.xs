function MMU_init()
{
    var MMU = xdc.useModule('ti.sysbios.family.arm.a8.Mmu');

    MMU.enableMMU = true;

    /* Program code/data memory */
    // Force internal and external memory to be normal, outer and inner write-back, no write allocate, non-shareable
    var inner = 3;
    var outer = 3;
    var attrs =
    {
        type: MMU.FirstLevelDesc_SECTION,  // SECTION descriptor
        tex: 4 + outer,                    // tex =
        shareable: false,                  // shareable
        cacheable: ((inner & 0x2)!=0),     // cacheable
        bufferable: ((inner & 0x1)!=0),    // bufferable
    };
    // Set the descriptor for each entry in the address range
    for (var i=0x40000000; i < 0x40400000; i = i + 0x00100000)
    {
        // Each 'SECTION' descriptor entry spans a 1MB address range
        MMU.setFirstLevelDescMeta(i, i, attrs);
    }
    for (var i=0x80000000; i < 0x90000000; i = i + 0x00100000)
    {
        // Each 'SECTION' descriptor entry spans a 1MB address range
        MMU.setFirstLevelDescMeta(i, i, attrs);
    }

    /* Packet Buffer Memory */
    // Force shared memory to be normal, outer and inner write-back, no write allocate, non-shareable, non-executable
    var inner = 3;
    var outer = 3;
    var attrs =
    {
        type: MMU.FirstLevelDesc_SECTION,  // SECTION descriptor
        tex: 4 + outer,                    // tex =
        shareable: false,                  // shareable
        cacheable: ((inner & 0x2)!=0),     // cacheable
        bufferable: ((inner & 0x1)!=0),    // bufferable
        noexecute  : true                  // not executable
    };
    for (var i=0x8E000000; i < 0x8F000000; i = i + 0x00100000)
    {
        // Each 'SECTION' descriptor entry spans a 1MB address range
        MMU.setFirstLevelDescMeta(i, i, attrs);
    }

    // Force peripheral section to be NON cacheable, strongly-ordered memory
    var attrs = {
        type : MMU.FirstLevelDesc_SECTION, // SECTION descriptor
        tex: 0,                            // tex = 0
        bufferable : false,                // bufferable
        cacheable  : false,                // cacheable
        shareable  : false,                // shareable
        noexecute  : true,                 // not executable
        accPerm    : 3                     // read/write
    };

    // Configure the corresponding MMU page descriptor accordingly
    for (var i=0x40400000; i < 0x50000000; i = i + 0x00100000)
    {
        // Each 'SECTION' descriptor entry spans a 1MB address range
        MMU.setFirstLevelDescMeta(i, i, attrs);
    }
}
