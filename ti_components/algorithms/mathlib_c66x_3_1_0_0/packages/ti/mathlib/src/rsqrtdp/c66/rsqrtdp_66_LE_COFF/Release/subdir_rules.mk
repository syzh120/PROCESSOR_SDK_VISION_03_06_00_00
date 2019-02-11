################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
driver.obj: C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/common/driver.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/MATHLIB_Tools/CCSV5_4_0/ccsv5/tools/compiler/c6000_7.4.2/bin/cl6x" -mv6600 --abi=coffabi -O3 --symdebug:none --include_path="C:/MATHLIB_Tools/CCSV5_4_0/ccsv5/tools/compiler/c6000_7.4.2/include" --include_path="../../../../../../../" --include_path="../../../../common/c66" --include_path="../../../" --include_path="../../" --include_path="../../../../common" --define=ti_targets_C66 --display_error_number --diag_warning=225 --diag_wrap=off --mem_model:data=far --debug_software_pipeline -k --preproc_with_compile --preproc_dependency="driver.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drvdp.obj: C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/common/drvdp.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/MATHLIB_Tools/CCSV5_4_0/ccsv5/tools/compiler/c6000_7.4.2/bin/cl6x" -mv6600 --abi=coffabi -O3 --symdebug:none --include_path="C:/MATHLIB_Tools/CCSV5_4_0/ccsv5/tools/compiler/c6000_7.4.2/include" --include_path="../../../../../../../" --include_path="../../../../common/c66" --include_path="../../../" --include_path="../../" --include_path="../../../../common" --define=ti_targets_C66 --display_error_number --diag_warning=225 --diag_wrap=off --mem_model:data=far --debug_software_pipeline -k --preproc_with_compile --preproc_dependency="drvdp.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rsqrtdp_d.obj: C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/rsqrtdp/rsqrtdp_d.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/MATHLIB_Tools/CCSV5_4_0/ccsv5/tools/compiler/c6000_7.4.2/bin/cl6x" -mv6600 --abi=coffabi -O3 --symdebug:none --include_path="C:/MATHLIB_Tools/CCSV5_4_0/ccsv5/tools/compiler/c6000_7.4.2/include" --include_path="../../../../../../../" --include_path="../../../../common/c66" --include_path="../../../" --include_path="../../" --include_path="../../../../common" --define=ti_targets_C66 --display_error_number --diag_warning=225 --diag_wrap=off --mem_model:data=far --debug_software_pipeline -k --preproc_with_compile --preproc_dependency="rsqrtdp_d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tables.obj: C:/builds/DEV_TI_MATHLIB_3_1_0_0/mathlib/ti/mathlib/src/common/tables.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/MATHLIB_Tools/CCSV5_4_0/ccsv5/tools/compiler/c6000_7.4.2/bin/cl6x" -mv6600 --abi=coffabi -O3 --symdebug:none --include_path="C:/MATHLIB_Tools/CCSV5_4_0/ccsv5/tools/compiler/c6000_7.4.2/include" --include_path="../../../../../../../" --include_path="../../../../common/c66" --include_path="../../../" --include_path="../../" --include_path="../../../../common" --define=ti_targets_C66 --display_error_number --diag_warning=225 --diag_wrap=off --mem_model:data=far --debug_software_pipeline -k --preproc_with_compile --preproc_dependency="tables.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


