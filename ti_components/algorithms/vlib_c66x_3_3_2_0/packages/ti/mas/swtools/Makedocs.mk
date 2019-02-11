# ==============================================================================
# File            : Makedocs.mk
# Description     : 
#
#   GNU makefile to generate release notes using Doxygen
#
# ==============================================================================

# The target for generating release Notes using doxygen is releasenotes

RELEASE_DOC=./docs/doxygen/release.chm

releasenotes : $(RELEASE_DOC)

$(RELEASE_DOC): ./docs/doxygen/release.h
	-@echo generating Release Notes ...
	if test ! -d ./docs/doxygen/html; then mkdir ./docs/doxygen/html; fi
	cp $(TI_DOXYGEN_TEMPLATES)/*.* ./docs/doxygen/html
	doxygen ../swtools/docs/doxygen/releaseDoxyfile
	@xs -f release.js

SWTOOLS_DOC=./docs/doxygen/SWTOOLS.chm

release : $(SWTOOLS_DOC)

gendocs $(SWTOOLS_DOC): ./docs/doxygen/doxygen.h
	-@echo generating SWTOOLS documentation ...
	if test ! -d ./docs/doxygen/html; then mkdir ./docs/doxygen/html; fi
	cp $(TI_DOXYGEN_TEMPLATES)/*.* ./docs/doxygen/html
	doxygen ./docs/doxygen/genDoxyfile

# End of Makedocs.mk
