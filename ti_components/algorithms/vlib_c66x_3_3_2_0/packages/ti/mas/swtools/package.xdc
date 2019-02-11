/*! swtools package
 * 
 * @a(NAME)  `ti.mas.swtools
 *
 *  This package contains the following files:
 *  @p(nlist)
 *      - `package.xdc` this file, and
 *      - `package.bld` this is package's build script.
 *      - `cygwinxdc.bat`
 *      - `cpytools.pl` used to copy tools by other packages
 *      - `Version.xdt` used to generate Version.xdc by other packages
 *	  - 'Ccase.js' generates configspec.clearcase for a given package of interest.
 *      - 'Ccase.xdc' is used to configure Ccase.js.
 *      - '\src' contains all sub-routiens of Ccase.js & its documentation.
 *  @p
 *  This package's build script uses a COPY of the `ti.sdoarch.standard`
 *  package's templates to generate the Version module required of every
 *  conformant package.
 *
 */
package ti.mas.swtools [3,0,0,0]
{
    interface IVersion;
    interface IVersion2;
    module Version;
    module Ccase;
    module CommonBld;
}
