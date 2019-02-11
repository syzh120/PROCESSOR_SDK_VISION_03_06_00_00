/*
 *  @brief This function returns defaults params for requested target.
 *
 *  @param[in]  localTarget  Requested Target.
 *
 *  @retval     targParams   Params of the requested target.
 *
 */

 /* Default C flags for C54x */
   var commonC54xCopts = " -pds815 -pds817 -pds1112 -pds825 -pds838 -pds828 -pds827 -pds77 -pds837 -pds824 -ss -k -ms -g -as -dC548 -v548";
  
   /* Default A flags for C54x */
   var commonC54xAopts = " -s -dC548 -mf -v548";

   /* Default compiler option for C54x */
   var c54_libParams = 
         {
            copts: commonC54xCopts,
            aopts: commonC54xAopts
         };  
         
   /* Default compiler option for MVARM9 */
   var mvarm9_libParams = 
         {
            copts: " -O2",
            aopts: ""
         };  
         
  /* Default compiler option for GCARMV6 */
   var armv6_libParams = 
         {
            copts: " -O2",
            aopts: ""
         };         

  /* Default compiler option for GCARMV7A */
  /* Default arm v7a CPU is cortex A8 */
   var armcpu = "cortex-a8";
   var cortexa8_libParams = 
         {
            copts: " -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=softfp -O2 -ftree-vectorize ",
            aopts: ""
         };         
   var cortexa9_libParams = 
         {
            copts: " -mcpu=cortex-a9 -mfpu=neon -mfloat-abi=softfp -O2 -ftree-vectorize ",
            aopts: ""
         };         




  /* Default compiler option for WinCE */
   var wince_libParams = 
         {
            copts: " -Ot",
            aopts: ""
         };  

   var wince_dbgParams = 
         {
            copts: " -Zi -Od",
            aopts: ""
         };  
         
 /* Default compiler option for WinCE */
   var vc98_libParams = 
         {
            copts: " -Ot -Zi",
            aopts: ""
         };  

   var vc98_dbgParams = 
         {
            copts: " -Z7 -Odi -MTd -D_DEBUG=1",
            aopts: ""
         };           
  
  /* CPU flag for C55x */
 
   /* Common C flags for C55x */
   var commonC55xCopts = " -c -pds1112 -pds825 -pds838 -pds828 -pds827 -pds77 -pds837 -pds824 -vcpu:2.1 -mg -ss -k -dC5510 -as -g --ptrdiff_size=16";

   /* Common A flags for C55x */
   var commonC55xAopts = " -vcpu:2.1 -as -al -g";
  
   /* C55x compiler option for speed */
   var C55xSpeedOpts = " -o2 -mn";
  
   /* C55x compiler option for size */
   var C55xSizeOpts = " -ms";

   /* Common C flags for C55x V3 */
   var commonC55xv3Copts = " -c -pds1112 -pds825 -pds838 -pds828 -pds827 -pds77 -pds837 -pds824 -vcpu:3.3 -mg -ss -k -dC5510 -as -g --ptrdiff_size=16";

   /* Common A flags for C55x */
   var commonC55xv3Aopts = " -vcpu:3.3 -as -al -g";
  
 
   /* Default compiler option for C55x - Debug */
   const c55_libParams_debug = 
         {
            copts: commonC55xCopts,
            aopts: commonC55xAopts
         };  /* compiler options for debug */

   /* Default compiler option for C55x - Speed more critical */
   const c55_libParams_speed = 
         {
            copts: commonC55xCopts+C55xSpeedOpts,
            aopts: commonC55xAopts
         };  /* compiler options for speed optimization */

   /* Default compiler option for C55x - Size more critical */
   const c55_libParams_size  = 
         {
            copts: commonC55xCopts+C55xSpeedOpts+C55xSizeOpts,
            aopts: commonC55xAopts
         };  /* compiler options for size optimization */

/* Default compiler option for C55x - Debug */
   const c55v3_libParams_debug = 
         {
            copts: commonC55xv3Copts,
            aopts: commonC55xv3Aopts
         };  /* compiler options for debug */

   /* Default compiler option for C55x - Speed more critical */
   const c55v3_libParams_speed = 
         {
            copts: commonC55xv3Copts+C55xSpeedOpts,
            aopts: commonC55xv3Aopts
         };  /* compiler options for speed optimization */

   /* Default compiler option for C55x - Size more critical */
   const c55v3_libParams_size  = 
         {
            copts: commonC55xv3Copts+C55xSpeedOpts+C55xSizeOpts,
            aopts: commonC55xv3Aopts
         };  /* compiler options for size optimization */


   /* Common C flags for C64x */
   var commonC64xCopts = " -c -k -q --mem_model:data=far -al -pds1111 -pds827 -pds824 -pds837 -pds1037 -pds195 -pdsw225 -pdsw994 -pdsw262 -pds77 -pden -pds232 -mw -os -g -mi10000 -as -ss";
   
   var commonknlC6xCopt = " -c -k -mw ";
   
   var commonknlC6xElfCopt = " -c -k -mw --strip_coff_underscore";
   
   var commonknlC6xAopt = " -ea.s -c -k ";
   
   var commonknlC6xElfAopt = " -ea.s -c -k --strip_coff_underscore";


   /* Common A flags for C64x */
   var commonC64xAopts = " -ea.s -c -k -mi1000";
  
   /* C64x compiler option for speed */
   var C64xSpeedOpts = " -o3 --optimize_with_debug";
   
   /* C6x Kernel option */
   var C6xKernelOpts = " -o3 --symdebug:none";

   /* C64x compiler option for size */
   var C64xSizeOpts = " -ms3";

   /* Default compiler option for C64x - debug */
   var c64_libParams_debug = 
       {
          copts: commonC64xCopts,
          aopts: commonC64xAopts
       };  /* compiler options for debug */

   /* Default compiler option for C64x - Speed more critical */
   var c64_libParams_speed = 
       {
          copts: commonC64xCopts + C64xSpeedOpts,
          aopts: commonC64xAopts
       };  /* compiler options for speed optimization */
       
  var c6x_Knl_libParams_speed = 
       {
          copts: commonknlC6xCopt + C6xKernelOpts,
          aopts: commonknlC6xAopt
       };  /* compiler options for speed optimization */       

  var c6x_Knl_elf_libParams_speed = 
       {
          copts: commonknlC6xElfCopt + C6xKernelOpts,
          aopts: commonknlC6xElfAopt
       };  /* compiler options for speed optimization */       
	   
	   
   /* Default compiler option for C64x - Size more critical */
   var c64_libParams_size  = 
       {
          copts: commonC64xCopts + C64xSpeedOpts + C64xSizeOpts,
          aopts: commonC64xAopts
       };  /* compiler options for size optimization */
       
  /* C66x option */      
   var c66_libParams_debug = 
       {
          copts: commonC64xCopts ,
          aopts: commonC64xAopts + " --strip_coff_underscore"
       };  /* compiler options for debug */

   /* Default compiler option for C66x - Speed more critical */
   var c66_libParams_speed = 
       {
          copts: commonC64xCopts + C64xSpeedOpts,
          aopts: commonC64xAopts + " --strip_coff_underscore"
       };  /* compiler options for speed optimization */
       
       

   /* Default compiler option for C66x - Size more critical */
   var c66_libParams_size  = 
       {
          copts: commonC64xCopts + C64xSpeedOpts + C64xSizeOpts,
          aopts: commonC64xAopts + " --strip_coff_underscore"
       };  /* compiler options for size optimization */
  

function getTargParams(localTarget, libraryPath,armcpu,c55x_cpu_version, bundletype)
{
    var targParams={};
    targParams.ofd="";
    
    if (bundletype == "kernel")
    {
      c64_libParams_speed=c6x_Knl_libParams_speed;
      c66_libParams_speed=c6x_Knl_libParams_speed;
	  if(String(localTarget).toLowerCase().match("elf"))
	  {
		 c64_libParams_speed=c6x_Knl_elf_libParams_speed;
         c66_libParams_speed=c6x_Knl_elf_libParams_speed;
	  }
	  
    }

    switch(localTarget)
    {
    case C54: 
      targParams.libParams_speed=c54_libParams;
      targParams.libParams_size=c54_libParams;
      targParams.libParams_debug=c54_libParams;
      targParams.target="c54n";
      targParams.ext = "c54n";
      targParams.targDirectory = "c54";   
      targParams.platform="ti.platforms.sim54xx";
      targParams.dstDir="c" + C54.suffix;
      targParams.ofd=C54.rootDir.toString().replace(/\\/g,"\/")+"/bin/ofd500";
      targParams.envtoolvar="C54X_GEN_INSTALL_DIR";
      targParams.internaldefs=" -Dti_targets_C54 -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";
        targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C54x Near Memory Model";
        targParams.targstring="C54";
      break;

    case C54_far:
      targParams.libParams_speed=c54_libParams;
      targParams.libParams_size=c54_libParams;
      targParams.libParams_debug=c54_libParams;
      targParams.target="c54f";
      targParams.ext = "c54f";
      targParams.targDirectory = "c54";   
      targParams.platform="ti.platforms.sim54xx";
      targParams.dstDir="c" + C54_far.suffix;
      targParams.ofd=C54_far.rootDir.toString().replace(/\\/g,"\/")+"/bin/ofd500";
      targParams.envtoolvar="C54X_GEN_INSTALL_DIR";
      targParams.internaldefs=" -Dti_targets_C54_far -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";            
        targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C54x Far Memory Model"; 
        targParams.targstring="C54_far";     
      break;

    case C55: 
      targParams.libParams_speed=c55_libParams_speed;
      targParams.libParams_size=c55_libParams_size;
      targParams.libParams_debug=c55_libParams_debug;
      targParams.target="c55s";
      targParams.ext = "c55s";
      targParams.targDirectory = "c55";   
      targParams.platform="ti.platforms.sim55xx";
      targParams.dstDir="c" + C55.suffix;
      targParams.ofd=C55.rootDir.toString().replace(/\\/g,"\/")+"/bin/ofd55";
      targParams.envtoolvar="C55X_GEN_INSTALL_DIR";   
      targParams.internaldefs=" -Dti_targets_C55 -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                     
        targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C55x Small Memory Model";   
        targParams.targstring="C55";         
      break;

    case C55_large: 
      if(c55x_cpu_version == "3.3")
      {
        targParams.libParams_speed=c55v3_libParams_speed;
        targParams.libParams_size=c55v3_libParams_size;
        targParams.libParams_debug=c55v3_libParams_debug;
        targParams.string="C55x Large Memory Model CPU 3.3"; 
        targParams.ext = "c55l_cpuv3.3";

           
      }
      else
      {
        targParams.libParams_speed=c55_libParams_speed;
        targParams.libParams_size=c55_libParams_size;
        targParams.libParams_debug=c55_libParams_debug;
        targParams.string="C55x Large Memory Model"; 
        targParams.ext = "c55l";

          
      }
      targParams.target="c55l";
      targParams.targstring="C55_large";
      targParams.targDirectory = "c55";   
      targParams.platform="ti.platforms.sim55xx";
      targParams.dstDir="c" + C55_large.suffix;
      targParams.ofd=C55_large.rootDir.toString().replace(/\\/g,"\/")+"/bin/ofd55";
      targParams.envtoolvar="C55X_GEN_INSTALL_DIR";      
      targParams.internaldefs=" -Dti_targets_C55_large -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";
        targParams.internallinkdefs=" -o $@ -m $@.map";      
                      
      break;

    case C64:
      targParams.libParams_speed=c64_libParams_speed;
      targParams.libParams_size=c64_libParams_size;
      targParams.libParams_debug=c64_libParams_debug;
      targParams.target="c64le";
      targParams.ext = "c64le";
      targParams.targDirectory = "c64";   
      targParams.platform="ti.platforms.sim64xx";
      targParams.dstDir="c" + C64.suffix;
      targParams.ofd=C64.rootDir.toString().replace(/\\/g,"\/")+"/bin/ofd6x";
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR";      
      targParams.internaldefs=" -Dti_targets_C64 -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";     
        targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C64x Little Endian"; 
      targParams.targstring="C64";                
      break;

    case C64_big_endian:       
      targParams.libParams_speed=c64_libParams_speed;
      targParams.libParams_size=c64_libParams_size;
      targParams.libParams_debug=c64_libParams_debug;
      targParams.target="c64be";
      targParams.ext = "c64be";
      targParams.targDirectory = "c64";   
      targParams.platform="ti.platforms.sim64xx";
      targParams.dstDir="c" + C64_big_endian.suffix;
      targParams.ofd=C64_big_endian.rootDir.toString().replace(/\\/g,"\/")+"/bin/ofd6x";
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR";   
      targParams.internaldefs=" -Dti_targets_C64_big_endian -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                    
        targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C64x Big Endian";   
        targParams.targstring="C64_big_endian";                     
      break;
      
    case C674:
      targParams.libParams_speed=c64_libParams_speed;
      targParams.libParams_size=c64_libParams_size;
      targParams.libParams_debug=c64_libParams_debug;
      targParams.target="c674le";
      targParams.ext = "c674le";
      targParams.targDirectory = "c64";   
      targParams.platform="ti.platforms.evmDA830";
      targParams.dstDir="c" + C674.suffix;
      targParams.ofd="";
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR";         
      targParams.internaldefs=" -Dti_targets_C674 -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                          
        targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C67x Little Endian";      
        targParams.targstring="C674";                        
      break;

    case C674_big_endian:       
      targParams.libParams_speed=c64_libParams_speed;
      targParams.libParams_size=c64_libParams_size;
      targParams.libParams_debug=c64_libParams_debug;
      targParams.target="c674be";
      targParams.ext = "c674be";
      targParams.targDirectory = "c64";   
      targParams.platform="ti.platforms.evmDA830";
      targParams.dstDir="c" + C674_big_endian.suffix;
      targParams.ofd="";
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR";               
      targParams.internaldefs=" -Dti_targets_C674_big_endian -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                          
        targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C67x Big Endian";
        targParams.targstring="C674_big_endian";                                    
      break;      


case C674_elf:
      targParams.libParams_speed=c66_libParams_speed;
      targParams.libParams_size=c66_libParams_size;
      targParams.libParams_debug=c66_libParams_debug;
      targParams.target="ce674le";
      targParams.ext = "ce674le";
      targParams.targDirectory = "c64";   
      targParams.platform="ti.platforms.evmDA830";
      targParams.dstDir="c" + C674_elf.suffix;
      targParams.ofd="";
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR";         
      targParams.internaldefs=" -Dti_targets_elf_C674 -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(OBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                          
        targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C67x ELF Little Endian";      
        targParams.targstring="C674_elf";                        
      break;

    case C674_big_endian_elf:       
      targParams.libParams_speed=c66_libParams_speed;
      targParams.libParams_size=c66_libParams_size;
      targParams.libParams_debug=c66_libParams_debug;
      targParams.target="ce674be";
      targParams.ext = "ce674be";
      targParams.targDirectory = "c64";   
      targParams.platform="ti.platforms.evmDA830";
      targParams.dstDir="c" + C674_big_endian_elf.suffix;
      targParams.ofd="";
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR";               
      targParams.internaldefs=" -Dti_targets_elf_C674_big_endian -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                          
        targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C67x ELF Big Endian";
        targParams.targstring="C674_big_endian_elf";                                    
      break;     
      
    case C66:
      targParams.libParams_speed=c64_libParams_speed;
      targParams.libParams_size=c64_libParams_size;
      targParams.libParams_debug=c64_libParams_debug;
      targParams.target="c66le";
      targParams.ext = "c66le";
      targParams.targDirectory = "c64";   
      targParams.platform=C66.platform;
      targParams.dstDir="c" + C66.suffix;
      targParams.ofd="";
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR";            
      targParams.internaldefs=" -Dti_targets_C66 -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                          
        targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C66x COFF Little Endian";    
        targParams.targstring="C66";                                
      break;

    case C66_big_endian:       
      targParams.libParams_speed=c64_libParams_speed;
      targParams.libParams_size=c64_libParams_size;
      targParams.libParams_debug=c64_libParams_debug;
      targParams.target="c66be";
      targParams.ext = "c66be";
      targParams.targDirectory = "c64";   
      targParams.platform=C66_big_endian.platform;
      targParams.dstDir="c" + C66_big_endian.suffix;
      targParams.ofd="";
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR";                  
      targParams.internaldefs=" -Dti_targets_C66_big_endian -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                          
      targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C66x COFF Big Endian";  
      targParams.targstring="C66_big_endian";                                  
      break;       

  case C66_elf:
      targParams.libParams_speed=c66_libParams_speed;
      targParams.libParams_size=c66_libParams_size;
      targParams.libParams_debug=c66_libParams_debug;
      targParams.target="ce66le";
      targParams.ext = "ce66le";
      targParams.targDirectory = "c64";   
      targParams.platform=C66_elf.platform;
      targParams.dstDir="c" + C66_elf.suffix;
      targParams.ofd="";
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR";            
      targParams.internaldefs=" -Dti_targets_elf_C66 -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                          
      targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C66x ELF Little Endian"; 
      targParams.targstring="C66_elf";                                   
      break;

    case C66_big_endian_elf:       
      targParams.libParams_speed=c66_libParams_speed;
      targParams.libParams_size=c66_libParams_size;
      targParams.libParams_debug=c66_libParams_debug;
      targParams.target="ce66be";
      targParams.ext = "ce66be";
      targParams.targDirectory = "c64";   
      targParams.platform=C66_big_endian_elf.platform;
      targParams.dstDir="c" + C66_big_endian_elf.suffix;
      targParams.ofd="";
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR";                  
      targParams.internaldefs=" -Dti_targets_elf_C66_big_endian -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                          
      targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C66x ELF Big Endian";   
      targParams.targstring="C66_big_endian_elf";                                 
      break;    

    case C64P:
      targParams.libParams_speed=c64_libParams_speed;
      targParams.libParams_size=c64_libParams_size;
      targParams.libParams_debug=c64_libParams_debug;
      targParams.target="c64Ple";
      targParams.ext = "c64Ple"; 
      targParams.targDirectory = "c64";   
      targParams.platform="ti.platforms.sim64Pxx";
      targParams.dstDir="c" + C64P.suffix;
      targParams.ofd=C64P.rootDir.toString().replace(/\\/g,"\/")+"/bin/ofd6x";
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR"; 
      targParams.internaldefs=" -Dti_targets_C64P -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                                     
      targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C64x+ COFF Little Endian";  
      targParams.targstring="C64P";                                  
      break;

    case C64P_big_endian:       
      targParams.libParams_speed=c64_libParams_speed;
      targParams.libParams_size=c64_libParams_size;
      targParams.libParams_debug=c64_libParams_debug;
      targParams.target="c64Pbe";
      targParams.ext = "c64Pbe";
      targParams.targDirectory = "c64";   
      targParams.platform="ti.platforms.sim64Pxx";
      targParams.dstDir="c" + C64P_big_endian.suffix;
      targParams.ofd=C64P_big_endian.rootDir.toString().replace(/\\/g,"\/")+"/bin/ofd6x";
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR"; 
      targParams.internaldefs=" -Dti_targets_C64P_big_endian -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                                     
      targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C64x+ COFF Big Endian";   
      targParams.targstring="C64P_big_endian";                                       
      break;

    case C64P_elf:
      targParams.libParams_speed=c66_libParams_speed;
      targParams.libParams_size=c66_libParams_size;
      targParams.libParams_debug=c66_libParams_debug;
      targParams.target="ce64Ple";
      targParams.ext = "ce64Ple"; 
      targParams.targDirectory = "c64";   
      targParams.platform="ti.platforms.sim64Pxx";
      targParams.dstDir="c" + C64P_elf.suffix;
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR"; 
      targParams.internaldefs=" -Dti_targets_elf_C64P -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                                     
      targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C64x+ ELF Little Endian";  
      targParams.targstring="C64P_elf";                                  
      break;

    case C64P_big_endian_elf:       
      targParams.libParams_speed=c66_libParams_speed;
      targParams.libParams_size=c66_libParams_size;
      targParams.libParams_debug=c66_libParams_debug;
      targParams.target="ce64Pbe";
      targParams.ext = "ce64Pbe";
      targParams.targDirectory = "c64";   
      targParams.platform="ti.platforms.sim64Pxx";
      targParams.dstDir="c" + C64P_big_endian_elf.suffix;
      targParams.envtoolvar="C6X_GEN_INSTALL_DIR"; 
      targParams.internaldefs=" -Dti_targets_elf_C64P_big_endian -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                                     
      targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="C64x+ Big Endian";   
      targParams.targstring="C64P_big_endian_elf";                                       
      break;

   case MVArm9:       
      targParams.libParams_speed=mvarm9_libParams;
      targParams.libParams_size=mvarm9_libParams;
      targParams.libParams_debug=mvarm9_libParams;
      targParams.target="mvarm9";
      targParams.ext = "mvarm9";
      targParams.targDirectory = "arm";   
      targParams.platform=MVArm9.platform;
      targParams.dstDir="mvarm9";
      targParams.envtoolvar="MONTAVISTA_ARM9_GEN_INSTALL_DIR"; 
      targParams.internaldefs=" -Dgnu_targets_MVArm9 -Dxdc_target_types__=gnu/targets/arm/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -o $@ ";  
      targParams.internallinkdefs="-Wl,-Map=$@.map -o $@";                                               
      targParams.string="Montavista Arm9";    
      targParams.targstring="MVArm9";                                      
      break;      

   case GCArmv6:       
      targParams.libParams_speed=armv6_libParams;
      targParams.libParams_size=armv6_libParams;
      targParams.libParams_debug=armv6_libParams;
      targParams.target="gcarmv6";
      targParams.ext = "gcarmv6";
      targParams.targDirectory = "arm";   
      targParams.platform=GCArmv6.platform;
      targParams.dstDir="gcarmv6";
      targParams.envtoolvar="GNU_ARM11_GEN_INSTALL_DIR"; 
      targParams.internaldefs=" -Dgnu_targets_arm_GCArmv6 -Dxdc_target_types__=gnu/targets/arm/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -o $@ ";                                     
      targParams.internallinkdefs="-Wl,-Map=$@.map -o $@ ";                                              
      targParams.string="GCC Arm11";   
      targParams.targstring="GCArmv6";                                             
      break;      

   case GCArmv7A:       
      if(armcpu == "cortex-a8")
      {
        targParams.envtoolvar="GNU_ARM_CORTEXA8_GEN_INSTALL_DIR"; 
        targParams.string="GCC Arm Cortex A8";
        targParams.libParams_speed=cortexa8_libParams;
        targParams.libParams_size=cortexa8_libParams;
        targParams.libParams_debug=cortexa8_libParams;

      }
      else if(armcpu == "cortex-a9")
      {
         targParams.envtoolvar="GNU_ARM_CORTEXA9_GEN_INSTALL_DIR"; 
         targParams.string="GCC Arm Cortex A9";
         targParams.libParams_speed=cortexa9_libParams;
         targParams.libParams_size=cortexa9_libParams;
         targParams.libParams_debug=cortexa9_libParams;

      }
      
      targParams.target="gcarmv7a";
      targParams.ext = "gcarmv7a";
      targParams.targDirectory = "arm";   
      targParams.platform=GCArmv7A.platform;
      targParams.dstDir="gcarmv7a";
      targParams.internaldefs=" -Dgnu_targets_arm_GCArmv7A -Dxdc_target_types__=gnu/targets/arm/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -o $@ ";                                     
        targParams.internallinkdefs="-Wl,-Map=$@.map -o $@ ";                                            
      targParams.targstring="GCArmv7A";                                               
      break; 
      
  case TIArmv6le:       
      targParams.libParams_speed=armv6_libParams;
      targParams.libParams_size=armv6_libParams;
      targParams.libParams_debug=armv6_libParams;
      targParams.target="tiarmv6le";
      targParams.ext = "tiarmv6le";
      targParams.targDirectory = "arm";   
      targParams.platform=TIArmv6le.platform;
      targParams.dstDir="tiarmv6le";
      targParams.envtoolvar="TI_ARM11_GEN_INSTALL_DIR"; 
      targParams.internaldefs=" -Dti_targets_arm_Arm11 -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                                     
      targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="TI Arm11 Little Endian"; 
      targParams.targstring="TIArmv6le";                                               
      break;            

  case TIArmv6be:       
      targParams.libParams_speed=armv6_libParams;
      targParams.libParams_size=armv6_libParams;
      targParams.libParams_debug=armv6_libParams;
      targParams.target="tiarmv6be";
      targParams.ext = "tiarmv6be";
      targParams.targDirectory = "arm";   
      targParams.platform=TIArmv6be.platform;
      targParams.dstDir="tiarmv6be";
      targParams.envtoolvar="TI_ARM11_GEN_INSTALL_DIR"; 
      targParams.internaldefs=" -Dti_targets_arm_Arm11_big_endian -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep ";                                     
      targParams.internallinkdefs=" -o $@ -m $@.map";      
      targParams.string="TI Arm11 Big Endian";  
      targParams.targstring="TIArmv6be";                                                    
      break;            

   case WinCE:       
      targParams.libParams_speed=wince_libParams;
      targParams.libParams_size=wince_libParams;
      targParams.libParams_debug=wince_dbgParams;
      targParams.target="wince";
      targParams.ext = "wince";
      targParams.targDirectory = "arm";   
      targParams.platform=WinCE.platform;
      targParams.dstDir="wince";
      targParams.string="Windows CE";      
      targParams.targstring="WinCE";                                          
      break;      
   
   case VC98:       
      targParams.libParams_speed=vc98_libParams;
      targParams.libParams_size=vc98_libParams;
      targParams.libParams_debug=vc98_dbgParams;
      targParams.target="vc98";
      targParams.ext = "vc98";
      targParams.targDirectory = "arm";   
      targParams.platform=VC98.platform;
      targParams.dstDir="vc98";
      targParams.string="MSVC 98";     
      targParams.envtoolvar="MSVC_GEN_INSTALL_DIR"; 
      targParams.internaldefs=" -Dmicrosoft_targets_VC98 -Dxdc_target_types__=microsoft/targets/std.h -Fo$@ ";
      /* mfc42.lib mfcs42.lib msvcirt.lib */
      targParams.internallinkdefs=" -map:$@.map -pdb:$@.pdb -out:$@ ";                                            
      targParams.string="Microsoft VC98";                                                      
      targParams.targstring="VC98";
      break;      

   case VC98_64:
      targParams.libParams_speed=vc98_libParams;
      targParams.libParams_size=vc98_libParams;
      targParams.libParams_debug=vc98_dbgParams;
      targParams.target="vc98_64";
      targParams.ext = "vc98_64";
      targParams.targDirectory = "arm";
      targParams.platform=VC98_64.platform;
      targParams.dstDir="vc98_64";
      targParams.string="MSVC 98_64";
      targParams.envtoolvar="MSVC_GEN_INSTALL_DIR";
      targParams.internaldefs=" -Dmicrosoft_targets_VC98 -Dxdc_target_types__=local/targets/std.h -Fo$@ ";
      /* mfc42.lib mfcs42.lib msvcirt.lib */
      targParams.internallinkdefs=" -map:$@.map -pdb:$@.pdb -out:$@ ";
      targParams.string="Microsoft VC98_64";
      targParams.targstring="VC98_64";
      break;
      }

     if(libraryPath == "")
       targParams.libpath="lib";
     else
       targParams.libpath=libraryPath;  
        
     return(targParams);
}