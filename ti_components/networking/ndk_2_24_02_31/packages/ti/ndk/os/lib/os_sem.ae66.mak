#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.elf.C66{1,0,7.4,2
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/os_sem/package/package_ti.ndk.os.oe66.dep
package/lib/lib/os_sem/package/package_ti.ndk.os.oe66.dep: ;
endif

package/lib/lib/os_sem/package/package_ti.ndk.os.oe66: | .interfaces
package/lib/lib/os_sem/package/package_ti.ndk.os.oe66: package/package_ti.ndk.os.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem/package -fr=./package/lib/lib/os_sem/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem/package -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem/package -fr=./package/lib/lib/os_sem/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/package/package_ti.ndk.os.oe66: export C_DIR=
package/lib/lib/os_sem/package/package_ti.ndk.os.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

package/lib/lib/os_sem/package/package_ti.ndk.os.se66: | .interfaces
package/lib/lib/os_sem/package/package_ti.ndk.os.se66: package/package_ti.ndk.os.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem/package -fr=./package/lib/lib/os_sem/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem/package -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem/package -fr=./package/lib/lib/os_sem/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/package/package_ti.ndk.os.se66: export C_DIR=
package/lib/lib/os_sem/package/package_ti.ndk.os.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/os_sem/efs.oe66.dep
package/lib/lib/os_sem/efs.oe66.dep: ;
endif

package/lib/lib/os_sem/efs.oe66: | .interfaces
package/lib/lib/os_sem/efs.oe66: efs.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/efs.oe66: export C_DIR=
package/lib/lib/os_sem/efs.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

package/lib/lib/os_sem/efs.se66: | .interfaces
package/lib/lib/os_sem/efs.se66: efs.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/efs.se66: export C_DIR=
package/lib/lib/os_sem/efs.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/os_sem/mem.oe66.dep
package/lib/lib/os_sem/mem.oe66.dep: ;
endif

package/lib/lib/os_sem/mem.oe66: | .interfaces
package/lib/lib/os_sem/mem.oe66: mem.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/mem.oe66: export C_DIR=
package/lib/lib/os_sem/mem.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

package/lib/lib/os_sem/mem.se66: | .interfaces
package/lib/lib/os_sem/mem.se66: mem.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/mem.se66: export C_DIR=
package/lib/lib/os_sem/mem.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/os_sem/mem_data.oe66.dep
package/lib/lib/os_sem/mem_data.oe66.dep: ;
endif

package/lib/lib/os_sem/mem_data.oe66: | .interfaces
package/lib/lib/os_sem/mem_data.oe66: mem_data.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/mem_data.oe66: export C_DIR=
package/lib/lib/os_sem/mem_data.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

package/lib/lib/os_sem/mem_data.se66: | .interfaces
package/lib/lib/os_sem/mem_data.se66: mem_data.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/mem_data.se66: export C_DIR=
package/lib/lib/os_sem/mem_data.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/os_sem/oem.oe66.dep
package/lib/lib/os_sem/oem.oe66.dep: ;
endif

package/lib/lib/os_sem/oem.oe66: | .interfaces
package/lib/lib/os_sem/oem.oe66: oem.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/oem.oe66: export C_DIR=
package/lib/lib/os_sem/oem.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

package/lib/lib/os_sem/oem.se66: | .interfaces
package/lib/lib/os_sem/oem.se66: oem.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/oem.se66: export C_DIR=
package/lib/lib/os_sem/oem.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/os_sem/ossys.oe66.dep
package/lib/lib/os_sem/ossys.oe66.dep: ;
endif

package/lib/lib/os_sem/ossys.oe66: | .interfaces
package/lib/lib/os_sem/ossys.oe66: ossys.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/ossys.oe66: export C_DIR=
package/lib/lib/os_sem/ossys.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

package/lib/lib/os_sem/ossys.se66: | .interfaces
package/lib/lib/os_sem/ossys.se66: ossys.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/ossys.se66: export C_DIR=
package/lib/lib/os_sem/ossys.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/os_sem/task.oe66.dep
package/lib/lib/os_sem/task.oe66.dep: ;
endif

package/lib/lib/os_sem/task.oe66: | .interfaces
package/lib/lib/os_sem/task.oe66: task.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/task.oe66: export C_DIR=
package/lib/lib/os_sem/task.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

package/lib/lib/os_sem/task.se66: | .interfaces
package/lib/lib/os_sem/task.se66: task.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/task.se66: export C_DIR=
package/lib/lib/os_sem/task.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/os_sem/semaphore.oe66.dep
package/lib/lib/os_sem/semaphore.oe66.dep: ;
endif

package/lib/lib/os_sem/semaphore.oe66: | .interfaces
package/lib/lib/os_sem/semaphore.oe66: semaphore.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/semaphore.oe66: export C_DIR=
package/lib/lib/os_sem/semaphore.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

package/lib/lib/os_sem/semaphore.se66: | .interfaces
package/lib/lib/os_sem/semaphore.se66: semaphore.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/semaphore.se66: export C_DIR=
package/lib/lib/os_sem/semaphore.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/os_sem/intmgmt.oe66.dep
package/lib/lib/os_sem/intmgmt.oe66.dep: ;
endif

package/lib/lib/os_sem/intmgmt.oe66: | .interfaces
package/lib/lib/os_sem/intmgmt.oe66: intmgmt.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c  -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C   -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/intmgmt.oe66: export C_DIR=
package/lib/lib/os_sem/intmgmt.oe66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

package/lib/lib/os_sem/intmgmt.se66: | .interfaces
package/lib/lib/os_sem/intmgmt.se66: intmgmt.c lib/os_sem.ae66.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cle66 -n $< ...
	$(ti.targets.elf.C66.rootDir)/bin/cl6x -c -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/os_sem -s oe66 $< -C  -n -s --symdebug:none -qq -pdsw225 -mv6600 --abi=eabi -eo.oe66 -ea.se66  -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 -ms2  -Dxdc_target_name__=C66 -Dxdc_target_types__=ti/targets/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_4_2 -O2 -DUSE_LL_SEMAPHORE=1 -D_NDK_EXTERN_CONFIG   -I$(PKGROOT)/ti/ndk//inc -I$(PKGROOT)/ti/ndk//inc/tools $(XDCINCS) -I$(ti.targets.elf.C66.rootDir)/include -fs=./package/lib/lib/os_sem -fr=./package/lib/lib/os_sem
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/os_sem/intmgmt.se66: export C_DIR=
package/lib/lib/os_sem/intmgmt.se66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

clean,e66 ::
	-$(RM) package/lib/lib/os_sem/package/package_ti.ndk.os.oe66
	-$(RM) package/lib/lib/os_sem/efs.oe66
	-$(RM) package/lib/lib/os_sem/mem.oe66
	-$(RM) package/lib/lib/os_sem/mem_data.oe66
	-$(RM) package/lib/lib/os_sem/oem.oe66
	-$(RM) package/lib/lib/os_sem/ossys.oe66
	-$(RM) package/lib/lib/os_sem/task.oe66
	-$(RM) package/lib/lib/os_sem/semaphore.oe66
	-$(RM) package/lib/lib/os_sem/intmgmt.oe66
	-$(RM) package/lib/lib/os_sem/package/package_ti.ndk.os.se66
	-$(RM) package/lib/lib/os_sem/efs.se66
	-$(RM) package/lib/lib/os_sem/mem.se66
	-$(RM) package/lib/lib/os_sem/mem_data.se66
	-$(RM) package/lib/lib/os_sem/oem.se66
	-$(RM) package/lib/lib/os_sem/ossys.se66
	-$(RM) package/lib/lib/os_sem/task.se66
	-$(RM) package/lib/lib/os_sem/semaphore.se66
	-$(RM) package/lib/lib/os_sem/intmgmt.se66

lib/os_sem.ae66: package/lib/lib/os_sem/package/package_ti.ndk.os.oe66 package/lib/lib/os_sem/efs.oe66 package/lib/lib/os_sem/mem.oe66 package/lib/lib/os_sem/mem_data.oe66 package/lib/lib/os_sem/oem.oe66 package/lib/lib/os_sem/ossys.oe66 package/lib/lib/os_sem/task.oe66 package/lib/lib/os_sem/semaphore.oe66 package/lib/lib/os_sem/intmgmt.oe66 lib/os_sem.ae66.mak

clean::
	-$(RM) lib/os_sem.ae66.mak