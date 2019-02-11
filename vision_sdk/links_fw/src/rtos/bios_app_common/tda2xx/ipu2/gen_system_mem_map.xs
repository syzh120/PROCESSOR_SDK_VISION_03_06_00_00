/*
 *  This file auto generates a .h file using 
 *  XDC varaiables defined in mem_segment_definition_xxx_xxx.xs
 *  This file is include on Linux side in A15 and used by A15 
 *  application to map shared region memory's 
 *  
 */



function Value2HexString(Value)
{
    return ("0x" + java.lang.Long.toHexString(Value));
}


function Value2IntString(Value)
{
    return (java.lang.Long.toString(Value));
}

function GenSystemMemMap()
{
    print (" ### Generating System memory map header file ... ");

    var File = xdc.useModule('xdc.services.io.File');

    var fd = File.open( "osa_mem_map.h" ,"w");

    var Program             = xdc.useModule('xdc.cfg.Program');
    var SR0                 = Program.cpu.memoryMap['SR0'];
    var SR1                 = Program.cpu.memoryMap['SR1_FRAME_BUFFER_MEM'];
    var SR2                 = Program.cpu.memoryMap['SR2_MEM'];
    var REMOTE_LOG_MEM      = Program.cpu.memoryMap['REMOTE_LOG_MEM'];
    var SYSTEM_IPC_SHM_MEM  = Program.cpu.memoryMap['SYSTEM_IPC_SHM_MEM'];
    var SYSTEM_AUTOSAR_IPC_SHM_MEM  = Program.cpu.memoryMap['SYSTEM_AUTOSAR_IPC_SHM_MEM'];
    var OVX_MEM             = Program.cpu.memoryMap['OPENVX_SHM_MEM'];

    fd.writeLine("");
    fd.writeLine(" /*****************************************************************");
    fd.writeLine("  * This is auto generated file from [gen_system_mem_map.xs] ");
    fd.writeLine("  * ");
    fd.writeLine("  * If you are editing this file then make sure these values match ");
    fd.writeLine("  * the values in the IPU1 memory map                              ");
    fd.writeLine("  *****************************************************************");
    fd.writeLine("  */");
    fd.writeLine("");
    fd.writeLine("#ifndef _SYSTEM_MEM_MAP_H_");
    fd.writeLine("#define _SYSTEM_MEM_MAP_H_");
    fd.writeLine("");
    fd.writeLine("");
    fd.writeLine("#define SR0_ADDR    " + Value2HexString(SR0.base));
    fd.writeLine("#define SR0_SIZE    " + Value2HexString(SR0.len) );
    fd.writeLine("");
    fd.writeLine("#define SYSTEM_IPC_SHM_MEM_ADDR    " + Value2HexString(SYSTEM_IPC_SHM_MEM.base));
    fd.writeLine("#define SYSTEM_IPC_SHM_MEM_SIZE    " + Value2HexString(SYSTEM_IPC_SHM_MEM.len) );
    fd.writeLine("");
    fd.writeLine("#define SYSTEM_AUTOSAR_IPC_SHM_MEM_ADDR    " + Value2HexString(SYSTEM_AUTOSAR_IPC_SHM_MEM.base));
    fd.writeLine("#define SYSTEM_AUTOSAR_IPC_SHM_MEM_SIZE    " + Value2HexString(SYSTEM_AUTOSAR_IPC_SHM_MEM.len) );
    fd.writeLine("");
    fd.writeLine("#define REMOTE_LOG_MEM_ADDR       " + Value2HexString(REMOTE_LOG_MEM.base));
    fd.writeLine("#define REMOTE_LOG_MEM_SIZE       " + Value2HexString(REMOTE_LOG_MEM.len) );
    fd.writeLine("");
    fd.writeLine("#define SR1_FRAME_BUFFER_MEM_ADDR " + Value2HexString(SR1.base));
    fd.writeLine("#define SR1_FRAME_BUFFER_MEM_SIZE " + Value2HexString(SR1.len) );
    fd.writeLine("");
    fd.writeLine("#define SR2_FRAME_BUFFER_MEM_ADDR " + Value2HexString(SR2.base));
    fd.writeLine("#define SR2_FRAME_BUFFER_MEM_SIZE " + Value2HexString(SR2.len) );
    fd.writeLine("");
    if (java.lang.System.getenv("OPENVX_INCLUDE") == "yes")
    {
        fd.writeLine("#define OPENVX_OBJ_DESC_MEM_ADDR " + Value2HexString(OVX_MEM.base));
        fd.writeLine("#define OPENVX_OBJ_DESC_MEM_SIZE " + Value2HexString(OVX_MEM.len) );
        fd.writeLine("");
    }
    fd.writeLine("#endif /* _SYSTEM_MEM_MAP_H_ */");
    fd.writeLine("");
    fd.close();

    print (" ### Generating System memory map header file ... DONE !!!");
}

