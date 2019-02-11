/*
 * This configuration module helps us to define the common processing
 * functions for ti.mas package.bld. These functions can be called from 
 * package.bld to do standard processing
 */
/*
 *  ======== CommonBld  ========
 *  CommonBld for the ti.mas.swtools package
 */
metaonly module CommonBld {

     /**
   *  @brief This function parses the XDCARGS of the packages
   *
   *  @param[in]  arguments            XDCARGS
   *  @param[in]  targs                Supported Targets 
   *  @param[in]  packageSpecificArgs  Package specific Arguments
   *
   */
   function parseArgs(arguments,targs,packageSpecificArgs);

   /**
   *  @brief This function creates library for ti.mas packages
   *
   *  @param[in]  libName            Library name
   *  @param[in]  targArray          Target 
   *  @param[in]  source             source files
   *
   */
   function createLib(libName, targArray, source);

   /**
   *  @brief This function creates executable for ti.mas packages
   *
   *  @param[in]  exeName            Exe name
   *  @param[in]  targArray          Target 
   *  @param[in]  source             source files
   *
   */
   function createExe(exeName,targArray, source);

   /**
   *  @brief This function creates TAR file for ti.mas packages
   *
   *  @param[in]  pkgName            Package name
   *  @param[in]  targArray          Target 
   *
   */
   function createTar(pkgName,targArray);

   /**
   *  @brief This function cleans ti.mas packages
   *
   *
   */
   function packageClean();

  /**
   *  @brief This function initializes Print Buffer used for displaying Print Usage.
   *
   *  @param[in]  print_buffer  Pointer to Print buffer Structure.
   *
   *  @retval     print_buffer  Pointer to Print buffer  Structure.
   *
   */
   function printUsage(print_buffer);



   /**
   *  @brief This function initializes Print Buffer Options used for displaying Print Usage.
   *         This is used for displaying package specific arguments.   
   *
   *  @param[in]  print_buffer  Pointer to Print buffer Structure.
   *  @param[in]  SpecificArgs  Pointer to Package Specific Argument Structure.
   *
   *  @retval     print_buffer  Pointer to Print buffer.
   *
   */
   function addUsage(print_buffer,SpecificArgs);


}

/* nothing past this point */
