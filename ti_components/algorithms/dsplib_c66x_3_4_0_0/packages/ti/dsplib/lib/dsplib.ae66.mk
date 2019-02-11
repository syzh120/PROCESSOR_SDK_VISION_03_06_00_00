#*******************************************************************************
#* FILE PURPOSE: Lower level makefile for Creating Component Libraries
#*******************************************************************************
#* FILE NAME: lib/dsplib.ae66.mk
#*
#* DESCRIPTION: Defines Source Files, Compilers flags and build rules
#*
#*
#* This is an auto-generated file          
#*******************************************************************************
#

#
# Macro definitions referenced below
#
empty =
space =$(empty) $(empty)
CC = "$(C6X_GEN_INSTALL_DIR)/bin/"cl6x -c -mv6600 --abi=eabi
AC = "$(C6X_GEN_INSTALL_DIR)/bin/"cl6x -c -mv6600 --abi=eabi
ARIN = "$(C6X_GEN_INSTALL_DIR)/bin/"ar6x rq
LIBINFO = "$(C6X_GEN_INSTALL_DIR)/bin/libinfo6x"
LD = "$(C6X_GEN_INSTALL_DIR)/bin/"lnk6x --abi=eabi 
CGINCS = $(strip $(subst $(space),\$(space),$(C6X_GEN_INSTALL_DIR)/include))
RTSLIB = -l "$(C6X_GEN_INSTALL_DIR)/lib/undefined"
INCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(subst \,/,$(INCDIR)))))
OBJEXT = oe66
AOBJEXT = se66
INTERNALDEFS =  -Dti_targets_elf_C66 -Dxdc_target_types__=ti/targets/std.h -eo.$(OBJEXT) -ea.$(AOBJEXT) -fr=$(@D) -fs=$(@D) -ppa -ppd=$@.dep 
INTERNALLINKDEFS =  -o $@ -m $@.map
OBJDIR = ./package/lib/lib/dsplibae66

#List the kernelc66 Files
KERNELC66C= \
    ./src/DSPF_dp_cholesky//c66/DSPF_dp_cholesky.c\
    ./src/DSPF_dp_cholesky_cmplx//c66/DSPF_dp_cholesky_cmplx.c\
    ./src/DSPF_dp_fftDPxDP//c66/DSPF_dp_fftDPxDP.c\
    ./src/DSPF_dp_ifftDPxDP//c66/DSPF_dp_ifftDPxDP.c\
    ./src/DSPF_dp_lud//c66/DSPF_dp_lud.c\
    ./src/DSPF_dp_lud_cmplx//c66/DSPF_dp_lud_cmplx.c\
    ./src/DSPF_dp_lud_inv//c66/DSPF_dp_lud_inv.c\
    ./src/DSPF_dp_lud_inv_cmplx//c66/DSPF_dp_lud_inv_cmplx.c\
    ./src/DSPF_dp_lud_sol//c66/DSPF_dp_lud_sol.c\
    ./src/DSPF_dp_lud_sol_cmplx//c66/DSPF_dp_lud_sol_cmplx.c\
    ./src/DSPF_dp_mat_mul_gemm//c66/DSPF_dp_mat_mul_gemm.c\
    ./src/DSPF_dp_mat_submat_copy//c66/DSPF_dp_mat_submat_copy.c\
    ./src/DSPF_dp_mat_trans//c66/DSPF_dp_mat_trans.c\
    ./src/DSPF_dp_qrd//c66/DSPF_dp_qrd.c\
    ./src/DSPF_dp_qrd_cmplx//c66/DSPF_dp_qrd_cmplx.c\
    ./src/DSPF_dp_svd//c66/DSPF_dp_svd.c\
    ./src/DSPF_dp_svd_cmplx//c66/DSPF_dp_svd_cmplx.c\
    ./src/DSPF_sp_autocor//c66/DSPF_sp_autocor.c\
    ./src/DSPF_sp_biquad//c66/DSPF_sp_biquad.c\
    ./src/DSPF_sp_bitrev_cplx//c66/DSPF_sp_bitrev_cplx.c\
    ./src/DSPF_sp_cholesky//c66/DSPF_sp_cholesky.c\
    ./src/DSPF_sp_cholesky_cmplx//c66/DSPF_sp_cholesky_cmplx.c\
    ./src/DSPF_sp_convol//c66/DSPF_sp_convol.c\
    ./src/DSPF_sp_dotprod//c66/DSPF_sp_dotprod.c\
    ./src/DSPF_sp_dotp_cplx//c66/DSPF_sp_dotp_cplx.c\
    ./src/DSPF_sp_erand//c66/DSPF_sp_erand.c\
    ./src/DSPF_sp_fftSPxSP_r2c//c66/DSPF_sp_fftSPxSP_r2c.c\
    ./src/DSPF_sp_fircirc//c66/DSPF_sp_fircirc.c\
    ./src/DSPF_sp_fir_cplx//c66/DSPF_sp_fir_cplx.c\
    ./src/DSPF_sp_fir_gen//c66/DSPF_sp_fir_gen.c\
    ./src/DSPF_sp_fir_r2//c66/DSPF_sp_fir_r2.c\
    ./src/DSPF_sp_ifftSPxSP_c2r//c66/DSPF_sp_ifftSPxSP_c2r.c\
    ./src/DSPF_sp_iir//c66/DSPF_sp_iir.c\
    ./src/DSPF_sp_iirlat//c66/DSPF_sp_iirlat.c\
    ./src/DSPF_sp_lms//c66/DSPF_sp_lms.c\
    ./src/DSPF_sp_lud//c66/DSPF_sp_lud.c\
    ./src/DSPF_sp_lud_cmplx//c66/DSPF_sp_lud_cmplx.c\
    ./src/DSPF_sp_lud_inv//c66/DSPF_sp_lud_inv.c\
    ./src/DSPF_sp_lud_inv_cmplx//c66/DSPF_sp_lud_inv_cmplx.c\
    ./src/DSPF_sp_lud_sol//c66/DSPF_sp_lud_sol.c\
    ./src/DSPF_sp_lud_sol_cmplx//c66/DSPF_sp_lud_sol_cmplx.c\
    ./src/DSPF_sp_mat_mul//c66/DSPF_sp_mat_mul.c\
    ./src/DSPF_sp_mat_mul_cplx//c66/DSPF_sp_mat_mul_cplx.c\
    ./src/DSPF_sp_mat_mul_gemm//c66/DSPF_sp_mat_mul_gemm.c\
    ./src/DSPF_sp_mat_mul_gemm_cplx//c66/DSPF_sp_mat_mul_gemm_cplx.c\
    ./src/DSPF_sp_mat_submat_copy//c66/DSPF_sp_mat_submat_copy.c\
    ./src/DSPF_sp_mat_submat_copy_cplx//c66/DSPF_sp_mat_submat_copy_cplx.c\
    ./src/DSPF_sp_mat_trans//c66/DSPF_sp_mat_trans.c\
    ./src/DSPF_sp_mat_trans_cplx//c66/DSPF_sp_mat_trans_cplx.c\
    ./src/DSPF_sp_maxidx//c66/DSPF_sp_maxidx.c\
    ./src/DSPF_sp_maxval//c66/DSPF_sp_maxval.c\
    ./src/DSPF_sp_minerr//c66/DSPF_sp_minerr.c\
    ./src/DSPF_sp_minval//c66/DSPF_sp_minval.c\
    ./src/DSPF_sp_nrand//c66/DSPF_sp_nrand.c\
    ./src/DSPF_sp_qrd//c66/DSPF_sp_qrd.c\
    ./src/DSPF_sp_qrd_cmplx//c66/DSPF_sp_qrd_cmplx.c\
    ./src/DSPF_sp_svd//c66/DSPF_sp_svd.c\
    ./src/DSPF_sp_svd_cmplx//c66/DSPF_sp_svd_cmplx.c\
    ./src/DSPF_sp_urand//c66/DSPF_sp_urand.c\
    ./src/DSPF_sp_vecadd//c66/DSPF_sp_vecadd.c\
    ./src/DSPF_sp_vecmul//c66/DSPF_sp_vecmul.c\
    ./src/DSPF_sp_vecrecip//c66/DSPF_sp_vecrecip.c\
    ./src/DSPF_sp_vecsum_sq//c66/DSPF_sp_vecsum_sq.c\
    ./src/DSPF_sp_w_vec//c66/DSPF_sp_w_vec.c\
    ./src/DSP_add16//c66/DSP_add16.c\
    ./src/DSP_add32//c66/DSP_add32.c\
    ./src/DSP_autocor//c66/DSP_autocor.c\
    ./src/DSP_bexp//c66/DSP_bexp.c\
    ./src/DSP_blk_eswap16//c66/DSP_blk_eswap16.c\
    ./src/DSP_blk_eswap32//c66/DSP_blk_eswap32.c\
    ./src/DSP_blk_eswap64//c66/DSP_blk_eswap64.c\
    ./src/DSP_blk_move//c66/DSP_blk_move.c\
    ./src/DSP_dotprod//c66/DSP_dotprod.c\
    ./src/DSP_dotp_sqr//c66/DSP_dotp_sqr.c\
    ./src/DSP_fft16x16//c66/DSP_fft16x16.c\
    ./src/DSP_fft16x16r//c66/DSP_fft16x16r.c\
    ./src/DSP_fft16x16_imre//c66/DSP_fft16x16_imre.c\
    ./src/DSP_fft16x32//c66/DSP_fft16x32.c\
    ./src/DSP_fft32x32//c66/DSP_fft32x32.c\
    ./src/DSP_fft32x32s//c66/DSP_fft32x32s.c\
    ./src/DSP_firlms2//c66/DSP_firlms2.c\
    ./src/DSP_fir_cplx//c66/DSP_fir_cplx.c\
    ./src/DSP_fir_cplx_hM4X4//c66/DSP_fir_cplx_hM4X4.c\
    ./src/DSP_fir_gen//c66/DSP_fir_gen.c\
    ./src/DSP_fir_gen_hM17_rA8X8//c66/DSP_fir_gen_hM17_rA8X8.c\
    ./src/DSP_fir_r4//c66/DSP_fir_r4.c\
    ./src/DSP_fir_r8//c66/DSP_fir_r8.c\
    ./src/DSP_fir_r8_h16//c66/DSP_fir_r8_h16.c\
    ./src/DSP_fir_r8_h24//c66/DSP_fir_r8_h24.c\
    ./src/DSP_fir_r8_h8//c66/DSP_fir_r8_h8.c\
    ./src/DSP_fir_r8_hM16_rM8A8X8//c66/DSP_fir_r8_hM16_rM8A8X8.c\
    ./src/DSP_fir_sym//c66/DSP_fir_sym.c\
    ./src/DSP_fltoq15//c66/DSP_fltoq15.c\
    ./src/DSP_ifft16x16//c66/DSP_ifft16x16.c\
    ./src/DSP_ifft16x16_imre//c66/DSP_ifft16x16_imre.c\
    ./src/DSP_ifft16x32//c66/DSP_ifft16x32.c\
    ./src/DSP_ifft32x32//c66/DSP_ifft32x32.c\
    ./src/DSP_iir//c66/DSP_iir.c\
    ./src/DSP_iir_lat//c66/DSP_iir_lat.c\
    ./src/DSP_iir_ss//c66/DSP_iir_ss.c\
    ./src/DSP_mat_mul//c66/DSP_mat_mul.c\
    ./src/DSP_mat_mul_cplx//c66/DSP_mat_mul_cplx.c\
    ./src/DSP_mat_trans//c66/DSP_mat_trans.c\
    ./src/DSP_maxidx//c66/DSP_maxidx.c\
    ./src/DSP_maxval//c66/DSP_maxval.c\
    ./src/DSP_minerror//c66/DSP_minerror.c\
    ./src/DSP_minval//c66/DSP_minval.c\
    ./src/DSP_mul32//c66/DSP_mul32.c\
    ./src/DSP_neg32//c66/DSP_neg32.c\
    ./src/DSP_q15tofl//c66/DSP_q15tofl.c\
    ./src/DSP_recip16//c66/DSP_recip16.c\
    ./src/DSP_urand16//c66/DSP_urand16.c\
    ./src/DSP_urand32//c66/DSP_urand32.c\
    ./src/DSP_vecsumsq//c66/DSP_vecsumsq.c\
    ./src/DSP_w_vec//c66/DSP_w_vec.c

# FLAGS for the kernelc66 Files
KERNELC66CFLAGS =  -c -k -mw  -o3 --symdebug:none --mem_model:data=far

# Make Rule for the kernelc66 Files
KERNELC66COBJS = $(patsubst %.c, $(OBJDIR)/%.$(OBJEXT), $(KERNELC66C))

$(KERNELC66COBJS): $(OBJDIR)/%.$(OBJEXT): %.c
	-@echo cle66 $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	-$(RM) $@.dep
	$(CC) $(KERNELC66CFLAGS) $(INTERNALDEFS) $(INCS) -I$(CGINCS) -fc $< 
	-@cp $@.dep $@.pp; \
         $(SED) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
             -e '/^$$/ d' -e 's/$$/ :/' < $@.pp >> $@.dep; \
         $(RM) $@.pp 

#Create Empty rule for dependency
$(KERNELC66COBJS):lib\dsplib.ae66.mk
lib\dsplib.ae66.mk:

#Include Depedency for kernelc66 Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(KERNELC66COBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif

#List the kernelc66 Files
KERNELC66SA= \
    ./src/DSPF_sp_fftSPxSP//c66/DSPF_sp_fftSPxSP.sa\
    ./src/DSPF_sp_ifftSPxSP//c66/DSPF_sp_ifftSPxSP.sa

# FLAGS for the kernelc66 Files
KERNELC66SAFLAGS =  -c -k -mw  -o3 --symdebug:none --mem_model:data=far

# Make Rule for the kernelc66 Files
KERNELC66SAOBJS = $(patsubst %.sa, $(OBJDIR)/%.$(OBJEXT), $(KERNELC66SA))

$(KERNELC66SAOBJS): $(OBJDIR)/%.$(OBJEXT): %.sa
	-@echo asme66 $< ...
	if [ ! -d $(@D) ]; then $(MKDIR) $(@D) ; fi;
	$(AC) $(KERNELC66SAFLAGS) $(INTERNALDEFS) $(INCS) -I$(CGINCS) $< 

#Create Empty rule for dependency
$(KERNELC66SAOBJS):lib\dsplib.ae66.mk
lib\dsplib.ae66.mk:

#Include Depedency for kernelc66 Files
ifneq (clean,$(MAKECMDGOALS))
 -include $(KERNELC66SAOBJS:%.$(OBJEXT)=%.$(OBJEXT).dep)
endif


lib/dsplib.ae66 : $(KERNELC66COBJS) $(KERNELC66SAOBJS)
	@echo archiving $? into $@ ...
	$(ARIN) $@ $?
	if [ -f $(@D)/dsplib.lib  ]; then $(LIBINFO) -u -o=$(@D)/dsplib.lib $@; else $(LIBINFO) -o=$(@D)/dsplib.lib $@; fi;
