----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------
 Introduction:
--------------------------------------------------------------------------------------
/* This document contains information on the structure of the DCAN Loopback 
 * example and build instructions for RTOS and Baremetal projects.
 */

--------------------------------------------------------------------------------------
 DCAN Example Overview:
--------------------------------------------------------------------------------------
 * The DCAN example has two subfolders 
	1. RTOS
	2. Baremetal
 * RTOS folder contains the files specific to RTOS environment
	This includes configuration files and text file for supported cores and main file
 * Baremetal contains the files specific to baremetal testing
	This includes main file and makefile
 * The dcan top level folder contains the files for core test logic of DCAN example
   that is common across RTOS and Baremetal environment
	
--------------------------------------------------------------------------------------
 RTOS Testing:
--------------------------------------------------------------------------------------
 * Create CCS project for the respective cores using pdkProjectCreate.bat
	- Use following command to create DCAN project for a specific core
		pdkProjectCreate.bat AM572x all little dcan all <core> <pkgdir>
			core   - arm / dsp / m4
			pkgdir - "C:\ti\pdk_am57xx_1_0_8\packages"
 * Load the created projects in CCS using Project -> Import CCS Projects
 * The project contains the include files, core test file, RTOS main file and
   the *.cfg file
 * The RTOS main file initiates BIOS and creates task to execute the DCAN Loopback Test
 * This file also configures DCAN interrupt0 Line and provides DCAN ISR to service 
   the interrupt.
 * The dcan_loopback_app.c file contains the core test logic for the Loopback test
 * The OSAL, UART and other required LLDs are integrated using xdc.loadPackage in 
   the *.cfg file of the project.
 * Build the projects using Project -> Build Project
 * Load and Test the binary 
 
--------------------------------------------------------------------------------------
 Baremetal Testing:
--------------------------------------------------------------------------------------
 * The baremetal main file makes a funtion call to the DCAN Loopback Test and handles 
   the Parity Error Interrupt.
 * This file configures DCAN Parity Error interrupt Line and provides DCAN ParityISR 
   to service the interrupt.
 * Build the baremetal test binary using gmake command
 * gmake csl command from the package directory will build the DCAN binaries for all 
   the three cores (arm, dsp, m4)
 * Binaries can be obtained from the <path_to_package_directory>\ti\binary folder
 * Load and Test the binaries
 
 
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 
 
 
 
	