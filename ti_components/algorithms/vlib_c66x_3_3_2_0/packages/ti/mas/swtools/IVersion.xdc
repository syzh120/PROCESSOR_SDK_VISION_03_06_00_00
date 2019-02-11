/*!
 *  ======== IVersion ========
 *  Standard package version number interface
 *
 *  This interface is part of the SDO Package Standard.  Each conformant
 *  package that supplies a version number contains a module named
 *  `Version` that implements this interface.  In other words,
 *  @p(blist)
 *      - the package's `package.xdc` file declares `Version` as one of it's
 *        modules
 *      - the package contains a spec for the `Version` module (named
 *        `Version.xdc`) and a header generated from this spec (named
 *        `Version.h`)
 *      - the `Version.xdc` file may optionally be generated from the
 *        `ti/sdoarch/standards/pkg/Version.xdt` template when the package's
 *        build script runs.
 *  @p
 *
 *  This interface defines a set of values that are used to 
 *  @p(nlist)
 *      - informally communicate the "degree" of change between successive
 *        releases of a package,
 *      - provide a "key" that enables the producer to unambigeously identify
 *        the sources (and tools) used to produce the package, and
 *      - enable consumers to easily communicate to producers the version(s)
 *        of the package(s) they are using.
 *  @p
 */
metaonly interface IVersion {
    /*!
     *  ======== MAJOR ========
     *  Major version number
     *
     *  This number should be changed when major changes in the package
     *  occur. Examples include adding new modules, adding substantial new
     *  features to the algorithm(s).
     */
    const UInt16 MAJOR;

    /*!
     *  ======== MINOR ========
     *  Minor version number
     *
     *  This number should be changed when minor changes in the package
     *  occur. Examples include minor changes to the existing APIs,
     *  adding minor features to the algorithms(s) including expanding the
     *  configuration options.
     */
    const UInt16 MINOR;

    /*!
     *  ======== PATCH ========
     *  Patch level
     *
     *  This number should be changed when bug fixes or performance
     *  improvements are introduced. There should be no changes in the APIs
     *  in this case.
     */
    const UInt16 PATCH;

    /*!
     *  ======== WIDTH ========
     *  Minimum width of print fields
     *
     *  When denoting version numbers using '.' to separate fields
     *  there is a danger of confusing version "6.1" and version "6.10";
     *  because, in decimal notation 6.1 == 6.10.  To avoid
     *  this confusion, it is common practice to adopt a fixed minimum field
     *  width that's when printing version dimensions (other than MAJOR);
     *  e.g., rather than printing "6.1", if WIDTH == 2 then the version would
     *  be displayed as "6.01".
     */
    const UInt16 WIDTH;

    /*!
     *  ======== getString ========
     *  Returns a string representation of the version
     *
     *  This method return a string of the form:
     *  @p(code)
     *      MAJOR<sep>MINOR<sep>PATCH
     *  @p
     *  where `MAJOR`, `MINOR`, and `PATCH` are
     *  the values sepcified in this interface and `<sep>` is the (optional)
     *  argument to this method.  If `separator` is not supplied (or is
     *  `null`), `<sep>` defaults to `'.'`.
     */
    function getString(separator);
}
