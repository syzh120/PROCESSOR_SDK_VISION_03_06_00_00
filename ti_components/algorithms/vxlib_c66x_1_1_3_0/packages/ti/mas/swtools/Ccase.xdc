/*
 * This configuration module helps us define
 * *list* of required packages listed in 
 * package.xdc.xml file *but* which should be 
 * ignored by Ccase.js while generating
 * configspec.clearcase file for a 
 * any given 'package of interest'.
 * Update the ignoreList as necessary, and
 * build this package so that the change holds.
 */
/*
 *  ======== Ccase  ========
 *  Ccase for the ti.mas.swtools package
 */
metaonly module Ccase {
	config String ignoreList[] = ["ti.sdoarch.standards.pkg",
	                              "ti.xdais"];
}

/* nothing past this point */
