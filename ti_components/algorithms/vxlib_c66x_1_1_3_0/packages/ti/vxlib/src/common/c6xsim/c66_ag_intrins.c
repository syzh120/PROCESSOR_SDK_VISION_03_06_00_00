/* This code is auto-generated.  Any manual modifications will be lost!    */
/* Most of the C66 intrinsics functions are implemented here, but not all. */
#include "C6xSimulator.h"

#if defined(TMS320C66X) || defined(TMS320C67X)

#define NO_GLOBAL_DATA_DECLS   // Disable global data decls in global.h
#define AVOID_LONG_LONG        // Disable use of "long long" in global.h
#include "global.h"            // included only in this one .c file

#define unit 'L'

static csr_type               CSR;
static fadcr_type             FADCR;
static faucr_type             FAUCR;
static fmcr_type              FMCR;
static word                   GPLYA;
static word                   GPLYB;
static word                   GFPGFR;
static enum datapath_types    datapath = a_path;

void _setFADCR(uint32 value)
{
    FADCR.NAN1ADD1 = (value>>0) & 1;
    FADCR.NAN2ADD1 = (value>>1);
    FADCR.DEN1ADD1 = (value>>2) & 1;
    FADCR.DEN2ADD1 = (value>>3) & 1;
    FADCR.INVALADD1 = (value>>4) & 1;
    FADCR.INFOADD1 = (value>>5) & 1;
    FADCR.OVERADD1 = (value>>6) & 1;
    FADCR.INEXADD1 = (value>>7) & 1;
    FADCR.UNDERADD1 = (value>>8) & 1;
    FADCR.ROUNDINGMODEADD1 = (value>>9) & 3;
    FADCR.RSV1 = (value>>11) & 31;
    FADCR.NAN1ADD2 = (value>>16) & 1;
    FADCR.NAN2ADD2 = (value>>17) & 1;
    FADCR.DEN1ADD2 = (value>>18) & 1;
    FADCR.DEN2ADD2 = (value>>19) & 1;
    FADCR.INVALADD2 = (value>>20) & 1;
    FADCR.INFOADD2 = (value>>21) & 1;
    FADCR.OVERADD2 = (value>>22) & 1;
    FADCR.INEXADD2 = (value>>23) & 1;
    FADCR.UNDERADD2 = (value>>24) & 1;
    FADCR.ROUNDINGMODEADD2 = (value>>25) & 3;
    FADCR.RSV2 = (value>>27) & 31;
}

uint32 _getFADCR(void)
{
    uint32 value;
    value =
        (FADCR.NAN1ADD1) |
        (FADCR.NAN2ADD1 << 1) |
        (FADCR.DEN1ADD1 << 2) |
        (FADCR.DEN2ADD1 << 3) |
        (FADCR.INVALADD1 << 4) |
        (FADCR.INFOADD1 << 5) |
        (FADCR.OVERADD1 << 6) |
        (FADCR.INEXADD1 << 7) |
        (FADCR.UNDERADD1 << 8) |
        (FADCR.ROUNDINGMODEADD1 << 9) |
        (FADCR.RSV1 << 11) |
        (FADCR.NAN1ADD2 << 16) |
        (FADCR.NAN2ADD2 << 17) |
        (FADCR.DEN1ADD2 << 18) |
        (FADCR.DEN2ADD2 << 19) |
        (FADCR.INVALADD2 << 20) |
        (FADCR.INFOADD2 << 21) |
        (FADCR.OVERADD2 << 22) |
        (FADCR.INEXADD2 << 23) |
        (FADCR.UNDERADD2 << 24) |
        (FADCR.ROUNDINGMODEADD2 << 25) |
        (FADCR.RSV2 << 27);
    return value;
}

#endif /* #if defined(TMS320C66X) || defined(TMS320C67X) */

#ifdef TMS320C66X
static word Lmask(word a);
static word add2(word a, word b);
static word add_sp(word op1, word op2, int cr_wr_delay);
static word avg2(word a, word b);
static word avgnr2(word a, word b);
static word avgnru4(word a, word b);
static word avgu4(word a, word b);
static qword ccmatmpy(dword op1, qword op2);
static dword ccmatmpyr1(dword op1, qword op2);
static dword ccmpy(word a, word b);
static dword ccmpy32r1(dword op1, dword op2);
static two_longlong ccmpy_cgem075(word a, word b);
static word ccmpyr1(word a, word b);
static qword cmatmpy(dword op1, qword op2);
static dword cmatmpyr1(dword op1, qword op2);
static word cmpeq2(word a, word b);
static word cmpeq4(word a, word b);
static word cmpgt2(word a, word b);
static dword cmpy32r1(dword op1, dword op2);
static two_longlong cmpy_cgem075(word a, word b);
static dword cmpy_joule(word a, word b);
static word cmpyr1_joule(word a, word b);
static word complex_rot270(word op1);
static word complex_rot90(word op1);
static dword dadd(dword op1, dword op2);
static dword dadd2(dword op1, dword op2);
static dword dadd_c(word op1, dword op2);
static dword dapys2(dword op1, dword op2);
static qword dccmpy(dword op1, dword op2);
static dword dccmpyr1(dword op1, dword op2);
static qword dcmpy(dword op1, dword op2);
static dword dcmpyr1(dword op1, dword op2);
static dword dcomplex_rot270(dword op1);
static dword dcomplex_rot90(dword op1);
static dword ddotp4h(qword qwop1, qword qwop2);
static dword ddotpsu4h(qword qwop1, qword qwop2);
static word dotp4h(dword dwop1, dword dwop2);
static dword dotp4h_l(dword dwop1, dword dwop2);
static word dotpsu4h(dword dwop1, dword dwop2);
static dword dotpsu4h_l(dword dwop1, dword dwop2);
static dword dpackh2(dword op1, dword op2);
static dword dpackhl2(dword op1, dword op2);
static dword dpackl2(dword op1, dword op2);
static dword dpacklh2(dword op1, dword op2);
static dword dsadd(dword op1, dword op2);
static dword dsadd2(dword op1, dword op2);
static dword dshl(dword op1, word op2);
static dword dshl2(dword op1, word op2);
static dword dshr(dword op1, word op2);
static dword dshr2(dword op1, word op2);
static dword dshru(dword op1, word op2);
static dword dshru2(dword op1, word op2);
static qword dsmpy2(dword op1, dword op2);
static dword dssub(dword op1, dword op2);
static dword dssub2(dword op1, dword op2);
static dword dsub(dword op1, dword op2);
static dword dsub2(dword op1, dword op2);
static word excp_chk_add_sp(word op1, word op2, int cr_wr_delay);
static word expand2(word a);
static word expand4(word a);
static word intsp(word op, int cr_wr_delay);
static word intspu(word op, int cr_wr_delay);
static word max2(word a, word b);
static word max4(word a, word b);
static word min2(word a, word b);
static word min4(word a, word b);
static dword mpy32_joule(word a, word b);
static word mpy_sp(word op1, word op2);
static word round_inth(word op, word sign, word round, word sticky);
static word round_ofuf_chk_sp(word sign, word exp, word man, word round, word sticky, word adder, int cr_wr_delay);
static word sadd(word a, word b);
static word sadd2(word a, word b);
static word sat_check32(int64_ll a);
static word sat_jz(int64_ll a);
static word sbyte0(word src);
static word sbyte1(word src);
static word sbyte2(word src);
static word sbyte3(word src);
static word shigh16(word src);
static word shl(word a, word l);
static word shl2(word op1, word op2);
static word shr(word a, word r);
static word shr2(word a, word r);
static word shru(word a, word r);
static word shru2(word a, word r);
static word slow16(word src);
static dword smpy2(word op1, word op2, word op3, word op4);
static word smpy32r1(word a, word b);
static word spack2(word a, word b);
static word spack4(word a, word b);
static word spinth(word op);
static word ssub(word a, word b);
static word ssub2_joule(word a, word b);
static word sub2(word a, word b);
static word sub_sp(word op1, word op2, int cr_wr_delay);
static word ubyte0(word src);
static word ubyte1(word src);
static word ubyte2(word src);
static word ubyte3(word src);
static word uhigh16(word src);
static word ulow16(word src);
static word unpkhu4(word a);
static word unpklu4(word a);
static dword xor_cl(word op1, dword op2);
#endif /* #ifdef TMS320C66X */

#ifdef TMS320C67X
static word denorm_chk_dp(dword op);
static word dpint(dword op);
static word excp_chk_mpy_spdp(word op1, dword op2);
static word extract_exp_dp(dword op);
static dword extract_man_dp(dword op);
static dword increment_dp(dword op);
static word inf_chk_dp(dword op);
static dword lshift_dp(dword op, word shift);
static dword mpy_sp2dp(word op1, word op2);
static dword mpy_spdp(word op1, dword op2);
static word qnan_chk_dp(dword op);
static uword rcp(uword index);
static dword rcp_dp(dword op);
static word rcp_sp(word op);
static uword rcpsq(uword index);
static dword rcpsq_dp(dword op);
static word rcpsq_sp(word op);
static dword round_ofuf_chk_dp(word sign, word exp, dword man, word round, word sticky, word adder, int cr_wr_delay);
static dword rshift_dp(dword op, word shift);
static word snan_chk_dp(dword op);
#endif /* #ifdef TMS320C67X */

#if defined(TMS320C66X) || defined(TMS320C67X)
static word carry_out(word op1, word op2);
static word denorm_chk_sp(word op);
static word excp_chk_mpy_sp(word op1, word op2);
static word extract_exp_sp(word op);
static word extract_man_sp(word op);
static word extract_sign(word op);
static word inf_chk_sp(word op);
static dword mpyid(word op1, word op2);
static word qnan_chk_sp(word op);
static word round_int(word op, word sign, word round, word sticky, int cr_wr_delay);
static word snan_chk_sp(word op);
static word spint(word op, int cr_wr_delay);
#endif /* #if defined(TMS320C66X) || defined(TMS320C67X) */


#ifdef TMS320C66X
static word Lmask(word a)
{
    int    count;

    count = a & 0x1f;
    if( !count ) {
        return (0);
    }
    return (((unsigned) 0x80000000 >> count - 1) - 1 ^ 0xffffffff);
}

static word add2(word a, word b)
{
    word    d_low, d_high;

    d_low  =  0x0000ffff & (a + b);                 /* Add the low 16-bits */
    d_high = (0xffff0000 & a) + (0xffff0000 & b);   /* Add the high 16-bits */

    return (d_high | d_low);
}

static word add_sp(word op1, word op2, int cr_wr_delay)
{
    word    rc;
    word    sign1, sign2;
    word    exp1, exp2;
    word    round_mode;
    word    man1, man2;
    word    exp_diff;
    word    sticky, round;
    word    result_exp;
    word    result_man;
    word    result_sign;
    word    result;

    /* call exception checks */
    rc = excp_chk_add_sp(op1, op2, cr_wr_delay);
    if( rc == 1 ) {
        return (0x7fffffff);                      /* QNaN */
    } else if( rc == 2 ) {
        return (0x7f800000);                      /* +infinity */
    } else if( rc == 3 ) {
        return (0xff800000);                      /* -infinity */

    }
    sign1 = extract_sign(op1);
    sign2 = extract_sign(op2);

    exp1 = extract_exp_sp(op1);
    exp2 = extract_exp_sp(op2);
    round_mode = (datapath == a_path) ? FADCR.ROUNDINGMODEADD1 : FADCR.ROUNDINGMODEADD2;

    /* zero operand */
    if( !exp1 ) {                                             /* test op1 == zero (or denormal)          */
        if( !exp2 ) {                                             /*  both operands are zero                 */
            if( sign1 == sign2 ) {
                return (sign1 ? 0x80000000 : 0);                 /*  if same sign, return that sign of zero */
            } else {                                              /*  for different signed zeros             */
                if( round_mode == 3 ) {
                    return (0x80000000);                          /*    return -zero if round down           */
                } else { return (0);                              /*    return +zero for other roundings     */
                }
            }
        } else { return (op2);                                    /*  return op2 if op1==0 && op2!=0         */
        }
    }
    if( !exp2 ) {
        return (op1);                                             /*  return op1 if op2==0 && op1!=0         */

    }
    /* real additions */
    man1 = extract_man_sp(op1) << 3;      /* shift mantissa 3 bits for guard/round/sticky bits */
    man2 = extract_man_sp(op2) << 3;
    if( exp1 > exp2 ) {
        result_exp = exp1;
        result_sign = sign1;
        exp_diff = exp1 - exp2;
        if( exp_diff > 31 ) {
            man2 = 1;                                  /* just sticky bit is set */
        } else {
            sticky = (man2 << (32 - exp_diff)) ? 1 : 0; /* or of bits shifted out */
            man2 = (man2 >> exp_diff) | sticky;        /* or sticky into LSB */
        }
        result_man = (sign1 == sign2) ? man1 + man2 : man1 - man2;
    } else if( exp2 > exp1 ) {
        result_exp = exp2;
        result_sign = sign2;
        exp_diff = exp2 - exp1;
        if( exp_diff > 31 ) {
            man1 = 1;
        } else {
            sticky = (man1 << (32 - exp_diff)) ? 1 : 0;
            man1 = (man1 >> exp_diff) | sticky;
        }
        result_man = (sign1 == sign2) ? man2 + man1 : man2 - man1;
    } else { /* exponents are equal */
        if((man1 == man2) && (sign1 != sign2)) {
            if( round_mode == 3 ) {
                return (0x80000000);
            } else { return (0);
            }
        } else {
            result_exp = exp1;
            result_sign = sign1;
            result_man = (sign1 == sign2) ? man1 + man2 : man1 - man2;
            if( result_man < 0 ) {
                result_man = -result_man;
                result_sign = !result_sign;
            }
        }
    }

    /* normalize result mantissa and extract round bit */
    if( result_man & 0x08000000 ) {   /* correct mantissa overflow */
        round = (result_man & 8) ? 1 : 0;
        sticky = (result_man & 7) ? 1 : 0;
        result_man >>= 4;
        result_exp++;
    } else {
        if( result_man & 0x07ffffff ) { /* to prevent an infinite while loop */
            while( !(result_man & 0x04000000)) {
                result_man <<= 1;
                result_exp--;
            }
        }
        round = (result_man & 4) ? 1 : 0;
        sticky = (result_man & 3) ? 1 : 0;
        result_man >>= 3;
    }

    result = round_ofuf_chk_sp(result_sign, result_exp, result_man, round, sticky, 1, cr_wr_delay);
    return (result);
}

static word avg2(word a, word b)
{
    word    a_lo, a_hi, t0, t1;
    word    b_lo, b_hi;
    word    c_lo, c_hi;

    a_lo =  a & 0xFFFF;
    a_lo |= a_lo & 0x00008000 ? 0xFFFF0000 : 0;
    b_lo =  b & 0xFFFF;
    b_lo |= b_lo & 0x00008000 ? 0xFFFF0000 : 0;

    a_hi = (a >> 16) & 0xFFFF;
    a_hi |= a_hi & 0x00008000 ? 0xFFFF0000 : 0;
    b_hi = (b >> 16) & 0xFFFF;
    b_hi |= b_hi & 0x00008000 ? 0xFFFF0000 : 0;

    t0 = a_lo + b_lo + 1;
    t1 = a_hi + b_hi + 1;

    c_lo = 0x0000FFFF & (t0 >>  1);
    c_hi = 0xFFFF0000 & (t1 << 15);

    return (c_hi | c_lo);
}

static word avgnr2(word a, word b)
{
    word    a_lo, a_hi, t0, t1;
    word    b_lo, b_hi;
    word    c_lo, c_hi;

    a_lo =  a & 0xFFFF;
    a_lo |= a_lo & 0x00008000 ? 0xFFFF0000 : 0;
    b_lo =  b & 0xFFFF;
    b_lo |= b_lo & 0x00008000 ? 0xFFFF0000 : 0;

    a_hi = (a >> 16) & 0xFFFF;
    a_hi |= a_hi & 0x00008000 ? 0xFFFF0000 : 0;
    b_hi = (b >> 16) & 0xFFFF;
    b_hi |= b_hi & 0x00008000 ? 0xFFFF0000 : 0;

    t0 = a_lo + b_lo;
    t1 = a_hi + b_hi;

    c_lo = 0x0000FFFF & (t0 >>  1);
    c_hi = 0xFFFF0000 & (t1 << 15);

    return (c_hi | c_lo);
}

static word avgnru4(word a, word b)
{
    word    a0, a1, a2, a3, b0, b1, b2, b3, c0, c1, c2, c3;

    a0 = (a & 0xFF000000) >> 24;
    a1 = (a & 0x00FF0000) >> 16;
    a2 = (a & 0x0000FF00) >>  8;
    a3 = (a & 0x000000FF);

    b0 = (b & 0xFF000000) >> 24;
    b1 = (b & 0x00FF0000) >> 16;
    b2 = (b & 0x0000FF00) >>  8;
    b3 = (b & 0x000000FF);

    c0 = ((a0 + b0) << 23) & 0xFF000000;
    c1 = ((a1 + b1) << 15) & 0x00FF0000;
    c2 = ((a2 + b2) <<  7) & 0x0000FF00;
    c3 = ((a3 + b3) >>  1) & 0x000000FF;

    return (c0 | c1 | c2 | c3);
}

static word avgu4(word a, word b)
{
    word    a0, a1, a2, a3, b0, b1, b2, b3, c0, c1, c2, c3;

    a0 = (a & 0xFF000000) >> 24;
    a1 = (a & 0x00FF0000) >> 16;
    a2 = (a & 0x0000FF00) >>  8;
    a3 = (a & 0x000000FF);

    b0 = (b & 0xFF000000) >> 24;
    b1 = (b & 0x00FF0000) >> 16;
    b2 = (b & 0x0000FF00) >>  8;
    b3 = (b & 0x000000FF);

    c0 = ((a0 + b0 + 1) << 23) & 0xFF000000;
    c1 = ((a1 + b1 + 1) << 15) & 0x00FF0000;
    c2 = ((a2 + b2 + 1) <<  7) & 0x0000FF00;
    c3 = ((a3 + b3 + 1) >>  1) & 0x000000FF;

    return (c0 | c1 | c2 | c3);
}

static qword ccmatmpy(dword op1, qword op2)
{
    two_longlong    result0, result1, result2, result3;
    int64_ll        temp_01_re, temp_01_im, temp_23_re, temp_23_im;
    int             sat;
    qword           result;

    sat  = 0;
    result0    = (ccmpy_cgem075(op2.word0, op1.low));
    result1    = (ccmpy_cgem075(op2.word2, op1.high));
    result2    = (ccmpy_cgem075(op2.word1, op1.low));
    result3    = (ccmpy_cgem075(op2.word3, op1.high));

    temp_01_im    = (result0.low  + result1.low);
    temp_01_re    = (result0.high + result1.high);
    temp_23_im    = (result2.low  + result3.low);
    temp_23_re    = (result2.high + result3.high);

    result.word0  =  ((sat_jz(temp_01_im))  & 0xffffffff);
    sat           = sat_check32(temp_01_im);
    result.word1  =  ((sat_jz(temp_01_re))  & 0xffffffff);
    sat           |= sat_check32(temp_01_re);
    result.word2  =  ((sat_jz(temp_23_im))  & 0xffffffff);
    sat           |= sat_check32(temp_23_im);
    result.word3  =  ((sat_jz(temp_23_re))  & 0xffffffff);
    sat           |= sat_check32(temp_23_re);

    if( sat ) {
        CSR.SAT |= 1;    // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }
    }

    return (result);
}

static dword ccmatmpyr1(dword op1, qword op2)
{
    two_longlong    result0, result1, result2, result3;
    int64_ll        temp_01_re, temp_01_im, temp_23_re, temp_23_im;
    int             sat;
    dword           result;

    sat  = 0;
    result0    = (ccmpy_cgem075(op2.word0, op1.low));
    result1    = (ccmpy_cgem075(op2.word2, op1.high));
    result2    = (ccmpy_cgem075(op2.word1, op1.low));
    result3    = (ccmpy_cgem075(op2.word3, op1.high));

    temp_01_im    = (sat_jz(((result0.low  + result1.low) + ((int64_ll) 0x4000)) << 1) >> 16) & 0xffff;
    sat           = sat_check32(((result0.low  + result1.low) + ((int64_ll) 0x4000)) << 1);
    temp_01_re    = (sat_jz(((result0.high + result1.high) + ((int64_ll) 0x4000)) << 1) >> 16) & 0xffff;
    sat           |= sat_check32(((result0.high + result1.high) + ((int64_ll) 0x4000)) << 1);
    temp_23_im    = (sat_jz(((result2.low  + result3.low) + ((int64_ll) 0x4000)) << 1) >> 16) & 0xffff;
    sat           |= sat_check32(((result2.low  + result3.low) + ((int64_ll) 0x4000)) << 1);
    temp_23_re    = (sat_jz(((result2.high + result3.high) + ((int64_ll) 0x4000)) << 1) >> 16) & 0xffff;
    sat           |= sat_check32(((result2.high + result3.high) + ((int64_ll) 0x4000)) << 1);

    result.low    = temp_01_re << 16  | temp_01_im;
    result.high   = temp_23_re << 16 | temp_23_im;

    if( sat ) {
        CSR.SAT |= 1;    // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }
    }

    return (result);
}

static dword ccmpy(word a, word b)
{
    dword    sum;

    // update to arch spec definition not the original Hoyle one

    if( a == 0x80008000 && b == 0x80008000 ) {
        sum.high = 0x7fffffff; // special case ?!

        // sat test on results
        CSR.SAT |= 1; // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }

    } else {
        sum.high = (shigh16(a) * shigh16(b)) + (slow16(a) * slow16(b));
    }

    sum.low  = (slow16(a) * shigh16(b)) - (shigh16(a) * slow16(b));


    return (sum);
}

static dword ccmpy32r1(dword op1, dword op2)
{
    int64_ll    src1_real;
    int64_ll    src1_im;
    int64_ll    src2_real;
    int64_ll    src2_im;
    int64_ll    tmp_real, tmp_im;
    int         sat;
    dword       mpy_res;

    // Cast 32-bit signed integer to 64-bits
    src1_real = op1.high;
    src1_real <<= 32;
    src1_real >>= 32;
    src1_im   = op1.low;
    src1_im   <<= 32;
    src1_im   >>= 32;
    src2_real = op2.high;
    src2_real <<= 32;
    src2_real >>= 32;
    src2_im   = op2.low;
    src2_im   <<= 32;
    src2_im   >>= 32;

    if( op1.high == 0x80000000 &&
        op1.low == 0x80000000 &&
        op2.high == 0x80000000 &&
        op2.low == 0x80000000 ) {
        tmp_real = 0x7fffffff;
        sat = 1;
        mpy_res.high = tmp_real;
    } else {
        tmp_real = (src1_real * src2_real + src1_im * src2_im + (1 << 30)) >> 31;
        sat           = sat_check32(tmp_real);
        mpy_res.high  = sat_jz(tmp_real);
    }

    tmp_im = (src1_real * -src2_im + src1_im * src2_real + (1 << 30)) >> 31;

    sat         |= sat_check32(tmp_im);
    mpy_res.low  = sat_jz(tmp_im);

    // set the bit in the CSR m1/m2 bit setting ?!?
    if( sat ) {
        CSR.SAT |= 1;  // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }
    }

    return (mpy_res);
}

static two_longlong ccmpy_cgem075(word a, word b)
{
    two_longlong    result;

    // msb 32
    result.high = (int64_ll )  (shigh16(a) * shigh16(b)) + (int64_ll ) (slow16(a) * slow16(b));
    // lsb 32
    result.low  = (int64_ll )  (slow16(a) * shigh16(b)) - (int64_ll) (shigh16(a) * slow16(b));
    return (result);
}

static word ccmpyr1(word a, word b)
{
    int         a_lo, a_hi, b_lo, b_hi;
    int         sat;
    int64_ll    temp;
    word        result;
    word        result1;

    sat  = 0;
    a_hi = shigh16(a);
    a_lo = slow16(a);
    b_hi = shigh16(b);
    b_lo = slow16(b);

    // lsb 16

    temp    = (int64_ll)(a_lo * b_hi) - (a_hi * b_lo) + ((int64_ll) 0x4000);
    result  = ((sat_jz(temp << 1)) >> 16) & 0xffff;
    sat     = sat_check32(temp << 1);

    // msb16

    temp   = (int64_ll)(a_hi * b_hi) + (a_lo * b_lo) + ((int64_ll) 0x4000);

    sat    |= sat_check32(temp << 1);
    result1 = sat_jz(temp << 1) & 0xffff0000;
    result |= result1;

    // set the bit in the CSR m1/m2 bit setting ?!?
    if( sat ) {
        CSR.SAT |= 1; // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }
    }

    return (result);
}

static qword cmatmpy(dword op1, qword op2)
{
    two_longlong    result0, result1, result2, result3;
    int64_ll        temp_01_re, temp_01_im, temp_23_re, temp_23_im;
    int             sat;
    qword           result;

    sat  = 0;
    result0    = (cmpy_cgem075(op2.word0, op1.low));
    result1    = (cmpy_cgem075(op2.word2, op1.high));
    result2    = (cmpy_cgem075(op2.word1, op1.low));
    result3    = (cmpy_cgem075(op2.word3, op1.high));

    temp_01_im    = (result0.low  + result1.low);
    temp_01_re    = (result0.high + result1.high);
    temp_23_im    = (result2.low  + result3.low);
    temp_23_re    = (result2.high + result3.high);

    result.word0  =  ((sat_jz(temp_01_im))  & 0xffffffff);
    sat           = sat_check32(temp_01_im);
    result.word1  =  ((sat_jz(temp_01_re))  & 0xffffffff);
    sat           |= sat_check32(temp_01_re);
    result.word2  =  ((sat_jz(temp_23_im))  & 0xffffffff);
    sat           |= sat_check32(temp_23_im);
    result.word3  =  ((sat_jz(temp_23_re))  & 0xffffffff);
    sat           |= sat_check32(temp_23_re);

    if( sat ) {
        CSR.SAT |= 1;    // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }
    }

    return (result);
}

static dword cmatmpyr1(dword op1, qword op2)
{
    two_longlong    result0, result1, result2, result3;
    int64_ll        temp_01_re, temp_01_im, temp_23_re, temp_23_im;
    int             sat;
    dword           result;

    sat  = 0;
    result0    = (cmpy_cgem075(op2.word0, op1.low));
    result1    = (cmpy_cgem075(op2.word2, op1.high));
    result2    = (cmpy_cgem075(op2.word1, op1.low));
    result3    = (cmpy_cgem075(op2.word3, op1.high));

    temp_01_im    = (sat_jz(((result0.low  + result1.low) + ((int64_ll) 0x4000)) << 1) >> 16) & 0xffff;
    sat           = sat_check32(((result0.low  + result1.low) + ((int64_ll) 0x4000)) << 1);
    temp_01_re    = (sat_jz(((result0.high + result1.high) + ((int64_ll) 0x4000)) << 1) >> 16) & 0xffff;
    sat           |= sat_check32(((result0.high + result1.high) + ((int64_ll) 0x4000)) << 1);
    temp_23_im    = (sat_jz(((result2.low  + result3.low) + ((int64_ll) 0x4000)) << 1) >> 16) & 0xffff;
    sat           |= sat_check32(((result2.low  + result3.low) + ((int64_ll) 0x4000)) << 1);
    temp_23_re    = (sat_jz(((result2.high + result3.high) + ((int64_ll) 0x4000)) << 1) >> 16) & 0xffff;
    sat           |= sat_check32(((result2.high + result3.high) + ((int64_ll) 0x4000)) << 1);

    result.low    = temp_01_re << 16  | temp_01_im;
    result.high   = temp_23_re << 16 | temp_23_im;

    if( sat ) {
        CSR.SAT |= 1;    // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }
    }

    return (result);
}

static word cmpeq2(word a, word b)
{
    int    carry[2];

    carry[0] = ((a & 0xffff) == (b & 0xffff)) ? 1 : 0;
    a >>= 16;
    b >>= 16;

    carry[1] = ((a & 0xffff) == (b & 0xffff)) ? 1 : 0;

    return (carry[1] << 1 | carry[0]);
}

static word cmpeq4(word a, word b)
{
    int    carry[4];

    carry[0] = ((a & 0xff) == (b & 0xff)) ? 1 : 0;
    a >>= 8;
    b >>= 8;

    carry[1] = ((a & 0xff) == (b & 0xff)) ? 1 : 0;
    a >>= 8;
    b >>= 8;

    carry[2] = ((a & 0xff) == (b & 0xff)) ? 1 : 0;
    a >>= 8;
    b >>= 8;

    carry[3] = ((a & 0xff) == (b & 0xff)) ? 1 : 0;

    return (carry[3] << 3 | carry[2] << 2 | carry[1] << 1 | carry[0]);
}

static word cmpgt2(word a, word b)
{
    word    l1, l2, h1, h2, c;

    l1 = 0xffff & a;
    if( 0x8000 & l1 ) {
        l1 |= 0xffff0000;
    }
    h1 = 0xffff & (a >> 16);
    if( 0x8000 & h1 ) {
        h1 |= 0xffff0000;
    }
    l2 = 0xffff & b;
    if( 0x8000 & l2 ) {
        l2 |= 0xffff0000;
    }
    h2 = 0xffff & (b >> 16);
    if( 0x8000 & h2 ) {
        h2 |= 0xffff0000;
    }

    c = ((word) (l1) > (word) (l2) ? 1 : 0) |
        ((word) (h1) > (word) (h2) ? 2 : 0);
    return (c);
}

static dword cmpy32r1(dword op1, dword op2)
{
    int64_ll    src1_real;
    int64_ll    src1_im;
    int64_ll    src2_real;
    int64_ll    src2_im;
    int64_ll    tmp_real, tmp_im;
    dword       mpy_res;

    int    sat;

    // Make sure we get the right sign here:
    src1_real = op1.high;
    src1_real <<= 32;
    src1_real >>= 32;
    src1_im   = op1.low;
    src1_im   <<= 32;
    src1_im   >>= 32;
    src2_real = op2.high;
    src2_real <<= 32;
    src2_real >>= 32;
    src2_im   = op2.low;
    src2_im   <<= 32;
    src2_im   >>= 32;

    tmp_real     = (src1_real * src2_real - src1_im * src2_im + (1 << 30)) >> 31;
    sat          = sat_check32(tmp_real);
    mpy_res.high = sat_jz(tmp_real);

    if( op1.high == 0x80000000 &&
        op1.low == 0x80000000 &&
        op2.high == 0x80000000 &&
        op2.low == 0x80000000 ) {
        tmp_im = 0x7fffffff;
        sat = 1;
        mpy_res.low = tmp_im;
    } else {
        tmp_im        = (src1_real * src2_im + src1_im * src2_real + (1 << 30)) >> 31;
        sat          |= sat_check32(tmp_im);
        mpy_res.low   = sat_jz(tmp_im);
    }

    // set the bit in the CSR m1/m2 bit setting ?!?
    if( sat ) {
        CSR.SAT |= 1;  // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }
    }

    return (mpy_res);
}

static two_longlong cmpy_cgem075(word a, word b)
{
    two_longlong    result;

    // msb 32
    result.high = (int64_ll )  (shigh16(a) * shigh16(b))  - (int64_ll ) (slow16(a) * slow16(b));
    // lsb 32
    result.low  = (int64_ll )  (slow16(a) * shigh16(b)) +  (int64_ll) (shigh16(a) * slow16(b));
    return (result);
}

static dword cmpy_joule(word a, word b)
{
    dword    sum;

    // update to arch spec definition not the original Hoyle one

    if( a == 0x80008000 && b == 0x80008000 ) {
        sum.low = 0x7fffffff; // special case ?!

        // sat test on results
        CSR.SAT |= 1; // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }

    } else {
        sum.low  = (slow16(a) * shigh16(b)) + (shigh16(a) * slow16(b));
    }

    sum.high = (shigh16(a) * shigh16(b)) - (slow16(a) * slow16(b));


    return (sum);
}

static word cmpyr1_joule(word a, word b)
{
    int         a_lo, a_hi, b_lo, b_hi;
    int         sat;
    int64_ll    temp;
    word        result;
    word        result1;

    sat  = 0;
    a_hi = shigh16(a);
    a_lo = slow16(a);
    b_hi = shigh16(b);
    b_lo = slow16(b);

    // lsb 16

    temp    = (int64_ll)(a_lo * b_hi) + (a_hi * b_lo) + ((int64_ll) 0x4000);
    result  = ((sat_jz(temp << 1)) >> 16) & 0xffff;
    sat     = sat_check32(temp << 1);

    // msb16

    temp   = (int64_ll)(a_hi * b_hi) - (a_lo * b_lo) + ((int64_ll) 0x4000);

    sat    |= sat_check32(temp << 1);
    result1 = sat_jz(temp << 1) & 0xffff0000;
    result |= result1;

    // set the bit in the CSR m1/m2 bit setting ?!?
    if( sat ) {
        CSR.SAT |= 1; // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }
    }

    return (result);
}

static word complex_rot270(word op1)
{
    word    op1_high;
    word    op1_low;

    op1_high = uhigh16(op1);
    op1_low  = ulow16(op1);

    if( op1_high == 0x8000 ) {
        return ((op1_low << 16) | 0x7fff);
    }

    return ((op1_low << 16) | (0xFFFF & - op1_high));
}

static word complex_rot90(word op1)
{
    word    op1_high;
    word    op1_low;

    op1_high = uhigh16(op1);
    op1_low  = ulow16(op1);

    if( op1_low == 0x8000 ) {
        return (0x7fff0000 | op1_high);
    }

    return (((0xFFFF & - op1_low) << 16) | op1_high);
}

static dword dadd(dword op1, dword op2)
{
    dword    result;

    result.high =  op1.high + op2.high;
    result.low  =  op1.low  + op2.low;

    return (result);
}

static dword dadd2(dword op1, dword op2)
{
    dword    result;

    result.high = add2(op1.high, op2.high);
    result.low  = add2(op1.low, op2.low);

    return (result);
}

static dword dadd_c(word op1, dword op2)
{
    dword    result;

    result.high =  op1 + op2.high;
    result.low  =  op1 + op2.low;

    return (result);
}

static dword dapys2(dword op1, dword op2)
{

    word     res0, res1, res2, res3;
    dword    result;

    if( op1.low & 0x00008000 ) {
        if((op2.low & 0xFFFF) == 0x8000 ) {
            res0 = 0x7FFF;
        } else {
            res0 = (-op2.low) & 0xFFFF;
        }
    } else {
        res0 = op2.low & 0xFFFF;
    }

    if( op1.low & 0x80000000 ) {
        if((op2.low & 0xFFFF0000) == 0x80000000 ) {
            res1 = 0x7FFF0000;
        } else {
            res1 = ((-(op2.low >> 16)) & 0xFFFF) << 16;
        }
    } else {
        res1 = op2.low & 0xFFFF0000;
    }

    if( op1.high & 0x00008000 ) {
        if((op2.high & 0xFFFF) == 0x8000 ) {
            res2 = 0x7FFF;
        } else {
            res2 = (-op2.high) & 0xFFFF;
        }
    } else {
        res2 = op2.high & 0xFFFF;
    }

    if( op1.high & 0x80000000 ) {
        if((op2.high & 0xFFFF0000) == 0x80000000 ) {
            res3 = 0x7FFF0000;
        } else {
            res3 = ((-(op2.high >> 16)) & 0xFFFF) << 16;
        }
    } else {
        res3 = op2.high & 0xFFFF0000;
    }

    result.high = res3 | res2;
    result.low  = res1 | res0;

    return (result);
}

static qword dccmpy(dword op1, dword op2)
{
    dword    tmp_low;
    dword    tmp_high;
    qword    result;

    tmp_high = ccmpy(op1.high, op2.high);
    tmp_low  = ccmpy(op1.low, op2.low);

    result.word3 = tmp_high.high;
    result.word2 = tmp_high.low;
    result.word1 = tmp_low.high;
    result.word0 = tmp_low.low;

    return (result);
}

static dword dccmpyr1(dword op1, dword op2)
{
    dword    result;

    result.high = ccmpyr1(op1.high, op2.high);
    result.low  = ccmpyr1(op1.low,  op2.low);

    return (result);
}

static qword dcmpy(dword op1, dword op2)
{
    dword    tmp_low;
    dword    tmp_high;
    qword    result;

    tmp_low    = cmpy_joule(op1.low, op2.low);   // 3 delay slots
    tmp_high   = cmpy_joule(op1.high, op2.high); // 3 delay slots

    result.word3 = tmp_high.high;
    result.word2 = tmp_high.low;
    result.word1 = tmp_low.high;
    result.word0 = tmp_low.low;

    return (result);
}

static dword dcmpyr1(dword op1, dword op2)
{
    dword    result;

    result.high = cmpyr1_joule(op1.high, op2.high);
    result.low  = cmpyr1_joule(op1.low, op2.low);

    return (result);
}

static dword dcomplex_rot270(dword op1)
{
    dword    result;

    result.high = complex_rot270(op1.high);
    result.low  = complex_rot270(op1.low);

    return (result);
}

static dword dcomplex_rot90(dword op1)
{
    dword    result;

    result.high = complex_rot90(op1.high);
    result.low  = complex_rot90(op1.low);

    return (result);
}

static dword ddotp4h(qword qwop1, qword qwop2)
{
    dword    tmp1, tmp2, mpy_res;

    tmp1.low  = qwop1.word0;
    tmp1.high = qwop1.word1;

    tmp2.low  = qwop2.word0;
    tmp2.high = qwop2.word1;

    mpy_res.low = dotp4h(tmp1, tmp2);

    tmp1.low  = qwop1.word2;
    tmp1.high = qwop1.word3;

    tmp2.low  = qwop2.word2;
    tmp2.high = qwop2.word3;

    mpy_res.high = dotp4h(tmp1, tmp2);

    return (mpy_res);
}

static dword ddotpsu4h(qword qwop1, qword qwop2)
{
    dword    tmp1, tmp2, mpy_res;

    tmp1.low  = qwop1.word0;
    tmp1.high = qwop1.word1;

    tmp2.low  = qwop2.word0;
    tmp2.high = qwop2.word1;

    mpy_res.low = dotpsu4h(tmp1, tmp2);

    tmp1.low  = qwop1.word2;
    tmp1.high = qwop1.word3;

    tmp2.low  = qwop2.word2;
    tmp2.high = qwop2.word3;

    mpy_res.high = dotpsu4h(tmp1, tmp2);

    return (mpy_res);
}

static word dotp4h(dword dwop1, dword dwop2)
{
    int64_ll    temp;
    word        mpy_res;
    int         sat;

    temp  = ((int64_ll)slow16(dwop1.low))   * ((int64_ll)slow16(dwop2.low)) +
            ((int64_ll)shigh16(dwop1.low))  * ((int64_ll)shigh16(dwop2.low)) +
            ((int64_ll)slow16(dwop1.high))  * ((int64_ll)slow16(dwop2.high)) +
            ((int64_ll)shigh16(dwop1.high)) * ((int64_ll)shigh16(dwop2.high));

    mpy_res = sat_jz(temp);
    sat     = sat_check32(temp);

    // sat test on results
    if( sat ) {
        CSR.SAT |= 1; // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }
    }

    return (mpy_res);
}

static dword dotp4h_l(dword dwop1, dword dwop2)
{
    int64_ll    temp;
    dword       mpy_res;

    temp  = ((int64_ll)slow16(dwop1.low))   * ((int64_ll)slow16(dwop2.low)) +
            ((int64_ll)shigh16(dwop1.low))  * ((int64_ll)shigh16(dwop2.low)) +
            ((int64_ll)slow16(dwop1.high))  * ((int64_ll)slow16(dwop2.high)) +
            ((int64_ll)shigh16(dwop1.high)) * ((int64_ll)shigh16(dwop2.high));

    mpy_res.low  =  temp      & 0xFFFFFFFF;
    mpy_res.high = (temp >> 32) & 0xFFFFFFFF;

    return (mpy_res);
}

static word dotpsu4h(dword dwop1, dword dwop2)
{
    int64_ll    temp;
    word        mpy_res;
    int         sat;

    temp  = ((int64_ll)slow16(dwop1.low))   * ((int64_ll)ulow16(dwop2.low)) +
            ((int64_ll)shigh16(dwop1.low))  * ((int64_ll)uhigh16(dwop2.low)) +
            ((int64_ll)slow16(dwop1.high))  * ((int64_ll)ulow16(dwop2.high)) +
            ((int64_ll)shigh16(dwop1.high)) * ((int64_ll)uhigh16(dwop2.high));

    mpy_res = sat_jz(temp);
    sat     = sat_check32(temp);

    // sat test on results
    if( sat ) {
        CSR.SAT |= 1; // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }
    }

    return (mpy_res);
}

static dword dotpsu4h_l(dword dwop1, dword dwop2)
{
    int64_ll    temp;
    dword       mpy_res;

    temp  = ((int64_ll)slow16(dwop1.low))   * ((int64_ll)ulow16(dwop2.low)) +
            ((int64_ll)shigh16(dwop1.low))  * ((int64_ll)uhigh16(dwop2.low)) +
            ((int64_ll)slow16(dwop1.high))  * ((int64_ll)ulow16(dwop2.high)) +
            ((int64_ll)shigh16(dwop1.high)) * ((int64_ll)uhigh16(dwop2.high));

    mpy_res.low  =  temp      & 0xFFFFFFFF;
    mpy_res.high = (temp >> 32) & 0xFFFFFFFF;

    return (mpy_res);
}

static dword dpackh2(dword op1, dword op2)
{
    dword    result;

    result.high = (op1.high << 0) & 0xffff0000 | (op2.high >> 16) & 0x0000ffff;
    result.low  = (op1.low << 0) & 0xffff0000 | (op2.low  >> 16) & 0x0000ffff;

    return (result);
}

static dword dpackhl2(dword op1, dword op2)
{
    dword    result;

    result.high = (op1.high) & 0xffff0000 | (op2.high) & 0x0000ffff;
    result.low  = (op1.low) & 0xffff0000 | (op2.low) & 0x0000ffff;

    return (result);
}

static dword dpackl2(dword op1, dword op2)
{
    dword    result;

    result.high = (op1.high << 16) & 0xffff0000 | (op2.high  >> 0) & 0x0000ffff;
    result.low  = (op1.low << 16) & 0xffff0000 | (op2.low   >> 0) & 0x0000ffff;

    return (result);
}

static dword dpacklh2(dword op1, dword op2)
{
    dword    result;

    result.high = (op1.high << 16) & 0xffff0000 | (op2.high >> 16) & 0x0000ffff;
    result.low  = (op1.low << 16) & 0xffff0000 | (op2.low  >> 16) & 0x0000ffff;

    return (result);
}

static dword dsadd(dword op1, dword op2)
{
    dword    result;

    result.high = sadd(op1.high, op2.high);
    result.low  = sadd(op1.low, op2.low);

    return (result);
}

static dword dsadd2(dword op1, dword op2)
{
    dword    result;

    result.high = sadd2(op1.high, op2.high);
    result.low  = sadd2(op1.low, op2.low);

    return (result);
}

static dword dshl(dword op1, word op2)
{
    dword    result;

    result.high = shl(op1.high, op2);
    result.low  = shl(op1.low, op2);

    return (result);
}

static dword dshl2(dword op1, word op2)
{
    dword    result;

    result.high = shl2(op1.high, op2);
    result.low  = shl2(op1.low, op2);

    return (result);
}

static dword dshr(dword op1, word op2)
{
    dword    result;

    result.high = shr(op1.high, op2);
    result.low  = shr(op1.low, op2);

    return (result);
}

static dword dshr2(dword op1, word op2)
{
    dword    result;

    result.high = shr2(op1.high, op2);
    result.low  = shr2(op1.low, op2);

    return (result);
}

static dword dshru(dword op1, word op2)
{
    dword    result;

    result.high = shru(op1.high, op2);
    result.low  = shru(op1.low, op2);

    return (result);
}

static dword dshru2(dword op1, word op2)
{
    dword    result;

    result.high = shru2(op1.high, op2);
    result.low  = shru2(op1.low, op2);

    return (result);
}

static qword dsmpy2(dword op1, dword op2)
{
    dword    dwdst0, dwdst1;
    qword    result;

    dwdst0  = smpy2(slow16(op1.low),  slow16(op2.low),
                    shigh16(op1.low),  shigh16(op2.low));
    dwdst1  = smpy2(slow16(op1.high),  slow16(op2.high),
                    shigh16(op1.high),  shigh16(op2.high));


    result.word0 = dwdst0.low;
    result.word1 = dwdst0.high;
    result.word2 = dwdst1.low;
    result.word3 = dwdst1.high;


    return (result);
}

static dword dssub(dword op1, dword op2)
{
    dword    result;

    result.high = ssub(op1.high, op2.high);
    result.low  = ssub(op1.low, op2.low);

    return (result);
}

static dword dssub2(dword op1, dword op2)
{
    dword    result;

    result.high = ssub2_joule(op1.high, op2.high);
    result.low  = ssub2_joule(op1.low, op2.low);

    return (result);
}

static dword dsub(dword op1, dword op2)
{
    dword    result;

    result.high =  op1.high - op2.high;
    result.low  =  op1.low  - op2.low;

    return (result);
}

static dword dsub2(dword op1, dword op2)
{
    dword    result;

    result.high = sub2(op1.high, op2.high);
    result.low  = sub2(op1.low, op2.low);

    return (result);
}

static word excp_chk_add_sp(word op1, word op2, int cr_wr_delay)
{
    word    sign1, sign2;

    /* SNaN checks */
    if( snan_chk_sp(op1)) {
        if( datapath == a_path ) {
            FADCR.INVALADD1 |= 1;                           // cr_wr_delay delay slots
            FADCR.NAN1ADD1  |= 1;                           // cr_wr_delay delay slots
            FADCR.NAN2ADD1  |= (snan_chk_sp(op2) || qnan_chk_sp(op2));      // cr_wr_delay delay slots
            FADCR.DEN2ADD1  |= denorm_chk_sp(op2);                  // cr_wr_delay delay slots
        } else {
            FADCR.INVALADD2 |= 1;                           // cr_wr_delay delay slots
            FADCR.NAN1ADD2  |= 1;                           // cr_wr_delay delay slots
            FADCR.NAN2ADD2  |= (snan_chk_sp(op2) || qnan_chk_sp(op2));      // cr_wr_delay delay slots
            FADCR.DEN2ADD2  |= denorm_chk_sp(op2);                  // cr_wr_delay delay slots
        }
        return (1);
    }
    if( snan_chk_sp(op2)) {
        if( datapath == a_path ) {
            FADCR.INVALADD1 |= 1;           // cr_wr_delay delay slots
            FADCR.NAN1ADD1  |= qnan_chk_sp(op1); // cr_wr_delay delay slots
            FADCR.NAN2ADD1  |= 1;           // cr_wr_delay delay slots
            FADCR.DEN1ADD1  |= denorm_chk_sp(op1);  // cr_wr_delay delay slots
        } else {
            FADCR.INVALADD2 |= 1;           // cr_wr_delay delay slots
            FADCR.NAN1ADD2  |= qnan_chk_sp(op1); // cr_wr_delay delay slots
            FADCR.NAN2ADD2  |= 1;           // cr_wr_delay delay slots
            FADCR.DEN1ADD2  |= denorm_chk_sp(op1);  // cr_wr_delay delay slots
        }
        return (1);
    }
    /* QNaN checks */
    if( qnan_chk_sp(op1)) {
        if( datapath == a_path ) {
            FADCR.NAN1ADD1  |= 1;           // cr_wr_delay delay slots
            FADCR.NAN2ADD1  |= qnan_chk_sp(op2); // cr_wr_delay delay slots
            FADCR.DEN2ADD1  |= denorm_chk_sp(op2);  // cr_wr_delay delay slots
        } else {
            FADCR.NAN1ADD2  |= 1;           // cr_wr_delay delay slots
            FADCR.NAN2ADD2  |= qnan_chk_sp(op2); // cr_wr_delay delay slots
            FADCR.DEN2ADD2  |= denorm_chk_sp(op2);  // cr_wr_delay delay slots
        }
        return (1);
    }
    if( qnan_chk_sp(op2)) {
        if( datapath == a_path ) {
            FADCR.NAN2ADD1  |= 1;           // cr_wr_delay delay slots
            FADCR.DEN1ADD1  |= denorm_chk_sp(op1);  // cr_wr_delay delay slots
        } else {
            FADCR.NAN2ADD2  |= 1;           // cr_wr_delay delay slots
            FADCR.DEN1ADD2  |= denorm_chk_sp(op1);  // cr_wr_delay delay slots
        }
        return (1);
    }

    sign1 = extract_sign(op1);
    sign2 = extract_sign(op2);

    /* infinity checks */
    if( inf_chk_sp(op1)) {
        if( inf_chk_sp(op2) && (sign1 != sign2)) {
            if( datapath == a_path ) {
                FADCR.INVALADD1 |= 1; // cr_wr_delay delay slots
            } else {
                FADCR.INVALADD2 |= 1; // cr_wr_delay delay slots
            }
            return (1);
        } else {
            if( datapath == a_path ) {
                FADCR.INFOADD1 |= 1;        // cr_wr_delay delay slots
                FADCR.DEN2ADD1 |= denorm_chk_sp(op2); // cr_wr_delay delay slots
            } else {
                FADCR.INFOADD2 |= 1;        // cr_wr_delay delay slots
                FADCR.DEN2ADD2 |= denorm_chk_sp(op2); // cr_wr_delay delay slots
            }
            return (2 + sign1);
        }
    }

    if( inf_chk_sp(op2)) {
        if( datapath == a_path ) {
            FADCR.INFOADD1 |= 1;            // cr_wr_delay delay slots
            FADCR.DEN1ADD1 |= denorm_chk_sp(op1);   // cr_wr_delay delay slots
        } else {
            FADCR.INFOADD2 |= 1;            // cr_wr_delay delay slots
            FADCR.DEN1ADD2 |= denorm_chk_sp(op1);   // cr_wr_delay delay slots
        }
        return (2 + sign2);
    }

    /* denormal checks */
    /* denormal will only set the FADCR bits   */
    /* the add/subtract will continue with the */
    /* denormal treated as a zero              */
    if( denorm_chk_sp(op1)) {
        if( datapath == a_path ) {
            FADCR.DEN1ADD1 |= 1; // cr_wr_delay delay slots
            FADCR.INEXADD1 |= 1; // cr_wr_delay delay slots
        } else {
            FADCR.DEN1ADD2 |= 1; // cr_wr_delay delay slots
            FADCR.INEXADD2 |= 1; // cr_wr_delay delay slots
        }
    }
    if( denorm_chk_sp(op2)) {
        if( datapath == a_path ) {
            FADCR.DEN2ADD1 |= 1; // cr_wr_delay delay slots
            FADCR.INEXADD1 |= 1; // cr_wr_delay delay slots
        } else {
            FADCR.DEN2ADD2 |= 1; // cr_wr_delay delay slots
            FADCR.INEXADD2 |= 1; // cr_wr_delay delay slots
        }
    }
    return (0);
}

static word expand2(word a)
{
    word    result;

    result = 0;
    if( a & 1 ) {
        result |= 0xffff;
    }
    if( a & 2 ) {
        result |= 0xffff0000;
    }

    return (result);
}

static word expand4(word a)
{
    word    result;

    result = 0;
    if( a & 1 ) {
        result |= 0xff;
    }
    if( a & 2 ) {
        result |= 0xff00;
    }
    if( a & 4 ) {
        result |= 0xff0000;
    }
    if( a & 8 ) {
        result |= 0xff000000;
    }

    return (result);
}

static word intsp(word op, int cr_wr_delay)
{
    dword    man;
    word     sign;
    word     exp;
    word     round_mode;
    word     check;
    int      i;

    if( !op ) {
        return (0);
    }

    if( op & 0x80000000 ) {
        sign = 1;
        op = -op;
    } else { sign = 0;
    }

    man.high = op >> 8;
    man.low  = op << 24;
    exp = 158;

    for( i=0; i < 56; i++ ) {
        if( man.high & 0x00800000 ) {
            break;
        }
        man.high = (man.high << 1) | (((uword)man.low) >> (31));
        man.low <<= 1;
        exp--;
    }

    if( man.low ) {
        if( datapath == a_path ) {
            FADCR.INEXADD1 |= 1;                      // cr_wr_delay delay slots
        } else { FADCR.INEXADD2 |= 1;                 // cr_wr_delay delay slots
        }
        round_mode = (datapath == a_path) ? FADCR.ROUNDINGMODEADD1 : FADCR.ROUNDINGMODEADD2;
        check = 0;
        if((round_mode == 0) && ((man.low & 0x80000000) && ((man.low & 0x7fffffff) || (man.high & 1)))) {
            check = 1;
        }
        if((round_mode == 2) && !sign && man.low ) {
            check = 1;
        }
        if((round_mode == 3) && sign && man.low ) {
            check = 1;
        }
        if( check ) {
            if((man.high & 0x00ffffff) == 0x00ffffff ) {
                man.high = 0;
                exp++;
            } else { man.high++;
            }
        }
    }
    return ((sign << 31) | (exp << 23) | (man.high & 0x007fffff));
}

static word intspu(word op, int cr_wr_delay)
{
    dword    man;
    word     exp;
    word     round_mode;
    word     check;
    int      i;

    if( !op ) {
        return (0);
    }

    man.high = op >> 8;
    man.low  = op << 24;
    exp = 158;

    for( i=0; i < 56; i++ ) {
        if( man.high & 0x00800000 ) {
            break;
        }
        man.high = (man.high << 1) | (((uword)man.low) >> (31));
        man.low <<= 1;
        exp--;
    }

    if( man.low ) {
        if( datapath == a_path ) {
            FADCR.INEXADD1 |= 1;                      // cr_wr_delay delay slots
        } else { FADCR.INEXADD2 |= 1;                 // cr_wr_delay delay slots
        }
        round_mode = (datapath == a_path) ? FADCR.ROUNDINGMODEADD1 : FADCR.ROUNDINGMODEADD2;
        check = 0;
        if((round_mode == 0) && ((man.low & 0x80000000) && ((man.low & 0x7fffffff) || (man.high & 1)))) {
            check = 1;
        }
        if((round_mode == 2) && man.low ) {
            check = 1;
        }
        if( check ) {
            if((man.high & 0x00ffffff) == 0x00ffffff ) {
                man.high = 0;
                exp++;
            } else { man.high++;
            }
        }
    }
    return ((exp << 23) | (man.high & 0x007fffff));

}

static word max2(word a, word b)
{
    word    alo, blo, c;

    c = 0;
    alo = 0xffff & a;
    if( alo & 0x8000 ) {
        alo |= 0xffff0000;
    }
    blo = 0xffff & b;
    if( blo & 0x8000 ) {
        blo |= 0xffff0000;
    }
    if( alo > blo ) {
        c |= a & 0xffff;
    } else { c |= b & 0xffff;
    }

    alo = 0xffff & (a >> 16);
    if( alo & 0x8000 ) {
        alo |= 0xffff0000;
    }
    blo = 0xffff & (b >> 16);
    if( blo & 0x8000 ) {
        blo |= 0xffff0000;
    }
    if( alo > blo ) {
        c |= (a & 0xffff0000);
    } else { c |= (b & 0xffff0000);
    }
    return (c);
}

static word max4(word a, word b)
{
    word    alo, blo, c;

    c = 0;
    alo = 0xff & a;
    blo = 0xff & b;
    if( alo > blo ) {
        c |= alo;
    } else { c |= blo;
    }
    a>>=8;
    b>>=8;
    alo = 0xff & a;
    blo = 0xff & b;
    if( alo > blo ) {
        c |= alo << 8;
    } else { c |= blo << 8;
    }
    a>>=8;
    b>>=8;
    alo = 0xff & a;
    blo = 0xff & b;
    if( alo > blo ) {
        c |= alo << 16;
    } else { c |= blo << 16;
    }
    a>>=8;
    b>>=8;
    alo = 0xff & a;
    blo = 0xff & b;
    if( alo > blo ) {
        c |= alo << 24;
    } else { c |= blo << 24;
    }
    return (c);
}

static word min2(word a, word b)
{
    word    alo, blo, c;

    c = 0;
    alo = 0xffff & a;
    if( alo & 0x8000 ) {
        alo |= 0xffff0000;
    }
    blo = 0xffff & b;
    if( blo & 0x8000 ) {
        blo |= 0xffff0000;
    }
    if( alo < blo ) {
        c |= a & 0xffff;
    } else { c |= b & 0xffff;
    }

    alo = 0xffff & (a >> 16);
    if( alo & 0x8000 ) {
        alo |= 0xffff0000;
    }
    blo = 0xffff & (b >> 16);
    if( blo & 0x8000 ) {
        blo |= 0xffff0000;
    }
    if( alo < blo ) {
        c |= (a & 0xffff0000);
    } else { c |= (b & 0xffff0000);
    }
    return (c);
}

static word min4(word a, word b)
{
    uword    alo, blo, c;

    c = 0;
    alo = 0xff & a;
    blo = 0xff & b;
    if( alo < blo ) {
        c |= alo;
    } else { c |= blo;
    }
    a>>=8;
    b>>=8;
    alo = 0xff & a;
    blo = 0xff & b;
    if( alo < blo ) {
        c |= alo << 8;
    } else { c |= blo << 8;
    }
    a>>=8;
    b>>=8;
    alo = 0xff & a;
    blo = 0xff & b;
    if( alo < blo ) {
        c |= alo << 16;
    } else { c |= blo << 16;
    }
    a>>=8;
    b>>=8;
    alo = 0xff & a;
    blo = 0xff & b;
    if( alo < blo ) {
        c |= alo << 24;
    } else { c |= blo << 24;
    }
    return (c);
}

static dword mpy32_joule(word a, word b)
{
    int64_ll    a64, b64, c64;
    dword       result;

    a64 = (int64_ll) a;   // NOTE:  We ARE expecting the 32-bit signed operand to be sign extended to 64-bits!
    b64 = (int64_ll) b;
    c64 = a64 * b64;

    result.low = c64 & 0xFFFFFFFF;
    result.high = c64 >> 32;

    return (result);
}

static word mpy_sp(word op1, word op2)
{
    word     sign1, sign2, result_sign;
    word     rc;
    word     exp1, exp2;
    word     man1, man2;
    dword    prod_man;
    word     result_man;
    word     result_exp;
    word     result;
    word     round, sticky;

    sign1 = extract_sign(op1);
    sign2 = extract_sign(op2);
    result_sign = sign1 ? !sign2 : sign2;

    rc = excp_chk_mpy_sp(op1, op2);

    if( rc == 1 ) {
        return (result_sign ? 0xffffffff : 0x7fffffff);
    } else if( rc == 2 ) {
        return (result_sign ? 0xff800000 : 0x7f800000);
    }

    exp1 = extract_exp_sp(op1);
    exp2 = extract_exp_sp(op2);

    if( !exp1 || !exp2 ) {
        return (result_sign ? 0x80000000 : 0);                     /* one operand is zero or denormal */

    }
    result_exp = exp1 + exp2 - 127;

    man1 = extract_man_sp(op1);
    man2 = extract_man_sp(op2);

    prod_man = mpyid(man1, man2);
    if( prod_man.high & 0x00008000 ) {
        result_man = (prod_man.high << 8) | ((prod_man.low >> 24) & 0x000000ff);
        result_exp++;
        round = (prod_man.low & 0x00800000) ? 1 : 0;
        sticky = (prod_man.low & 0x007fffff) ? 1 : 0;
    } else {
        result_man = (prod_man.high << 9) | ((prod_man.low >> 23) & 0x000001ff);
        round = (prod_man.low & 0x00400000) ? 1 : 0;
        sticky = (prod_man.low & 0x003fffff) ? 1 : 0;
    }
    result = round_ofuf_chk_sp(result_sign, result_exp, result_man, round, sticky, 0, 3);    // 3 delay slots for wr_cr update
    return (result);
}

static word round_inth(word op, word sign, word round, word sticky)
{
    word    round_mode;
    word    result;
    word    check;

    if( round || sticky ) {
        if( datapath == a_path ) {
            FADCR.INEXADD1 |= 1;  // 2 delay slots
        } else {
            FADCR.INEXADD2 |= 1;  // 2 delay slots
        }
    }
    result = op;

    round_mode = (datapath == a_path) ? FADCR.ROUNDINGMODEADD1 : FADCR.ROUNDINGMODEADD2;
    if( round_mode == 0 ) {
        if( round && (sticky || (result & 1))) {
            check = 0;
            if((result == 0x7fff) && !sign ) {
                check = 1;
            }
            if((result == 0x8000) && sign ) {
                check = 1;
            }
            if( check ) {
                if( datapath == a_path ) {
                    FADCR.OVERADD1 |= 1; // 2 delay slots
                } else {
                    FADCR.OVERADD2 |= 1; // 2 delay slots
                }
            } else { result++;
            }
        }
    } else if( round_mode == 2 ) {
        if( !sign && (round || sticky)) {
            if( result == 0x7fff ) {
                if( datapath == a_path ) {
                    FADCR.OVERADD1 |= 1; // 2 delay slots
                } else {
                    FADCR.OVERADD2 |= 1; // 2 delay slots
                }
            } else { result++;
            }
        }
    } else if( round_mode == 3 ) {
        if( sign && (round || sticky)) {
            if( result == 0x8000 ) {
                if( datapath == a_path ) {
                    FADCR.OVERADD1 |= 1; // 2 delay slots
                } else {
                    FADCR.OVERADD2 |= 1; // 2 delay slots
                }
            } else { result++;
            }
        }
    }
    if( sign ) {
        result = -result;
    }
    return (result);
}

static word round_ofuf_chk_sp(word sign, word exp, word man, word round, word sticky, word adder, int cr_wr_delay)
{
    word    round_mode;
    word    overflow;
    word    underflow;
    word    infinity;
    word    inexact;

    if( adder ) {
        round_mode = (datapath == a_path) ? FADCR.ROUNDINGMODEADD1 : FADCR.ROUNDINGMODEADD2;
    } else { round_mode = (datapath == a_path) ? FMCR.ROUNDINGMODEMPY1 : FMCR.ROUNDINGMODEMPY2;
    }

    inexact = round || sticky;
    overflow = 0;
    underflow = 0;
    infinity = 0;

    switch( round_mode ) {
        case 0 : /* round to nearest */
            if( round && (sticky || (man & 1))) {
                man++;
                if( man & 0x01000000 ) {
                    man >>= 1;
                    exp++;
                }
            }
            if( exp > 0x000000fe ) { /* overflow */
                man = 0;
                exp = 0x000000ff;
                overflow = 1;
                infinity = 1;
                inexact = 1;
            }
            if( exp < 1 ) { /* underflow */
                man = 0;
                exp = 0;
                underflow = 1;
                inexact = 1;
            }
            break;

        case 1 : /* round to zero */
            if( exp > 0x000000fe ) { /* overflow */
                man = 0x00ffffff;
                exp = 0x000000fe;
                overflow = 1;
                inexact = 1;
            }
            if( exp < 1 ) { /* underflow */
                man = 0;
                exp = 0;
                underflow = 1;
                inexact = 1;
            }
            break;

        case 2 : /* round to +infinity */
            if( !sign ) {
                if( round || sticky ) {
                    man++;
                    if( man & 0x01000000 ) {
                        man >>= 1;
                        exp++;
                    }
                }
            }
            if( exp > 0x000000fe ) { /* overflow */
                if( sign ) {
                    man = 0x00ffffff;
                    exp = 0x000000fe;
                } else {
                    man = 0;
                    exp = 0x000000ff;
                    infinity = 1;
                }
                overflow = 1;
                inexact = 1;
            }
            if( exp < 1 ) { /* underflow */
                if( sign ) {
                    man = 0;
                    exp = 0;
                } else {
                    man = 0;
                    exp = 1;
                }
                underflow = 1;
                inexact = 1;
            }
            break;

        case 3 : /* round to -infinity */
            if( sign ) {
                if( round || sticky ) {
                    man++;
                    if( man & 0x01000000 ) {
                        man >>= 1;
                        exp++;
                    }
                }
            }
            if( exp > 0x000000fe ) { /* overflow */
                if( sign ) {
                    man = 0;
                    exp = 0x000000ff;
                    infinity = 1;
                } else {
                    man = 0x00ffffff;
                    exp = 0x000000fe;
                }
                overflow = 1;
                inexact = 1;
            }
            if( exp < 1 ) { /* underflow */
                if( sign ) {
                    man = 0;
                    exp = 1;
                } else {
                    man = 0;
                    exp = 0;
                }
                underflow = 1;
                inexact = 1;
            }
            break;
    }

    if( adder ) {
        if( datapath == a_path ) {
            FADCR.UNDERADD1 |= underflow; // cr_wr_delay delay slots
            FADCR.INEXADD1  |= inexact; // cr_wr_delay delay slots
            FADCR.OVERADD1  |= overflow; // cr_wr_delay delay slots
            FADCR.INFOADD1  |= infinity; // cr_wr_delay delay slots
        } else {
            FADCR.UNDERADD2 |= underflow; // cr_wr_delay delay slots
            FADCR.INEXADD2  |= inexact; // cr_wr_delay delay slots
            FADCR.OVERADD2  |= overflow; // cr_wr_delay delay slots
            FADCR.INFOADD2  |= infinity; // cr_wr_delay delay slots
        }
    } else {
        if( datapath == a_path ) {
            FMCR.UNDERMPY1 |= underflow; // cr_wr_delay delay slots
            FMCR.INEXMPY1  |= inexact; // cr_wr_delay delay slots
            FMCR.OVERMPY1  |= overflow; // cr_wr_delay delay slots
            FMCR.INFOMPY1  |= infinity; // cr_wr_delay delay slots
        } else {
            FMCR.UNDERMPY2 |= underflow; // cr_wr_delay delay slots
            FMCR.INEXMPY2  |= inexact; // cr_wr_delay delay slots
            FMCR.OVERMPY2  |= overflow; // cr_wr_delay delay slots
            FMCR.INFOMPY2  |= infinity; // cr_wr_delay delay slots
        }
    }

    return ((sign << 31) | (exp << 23) | (man & 0x007fffff));
}

static word sadd(word a, word b)
{
    word    c;

    c = a + b;
    if((a < 0) && (b < 0) && (c >= 0)) {
        /* If a and b are negative, but result is positive, saturate negative */
        c = 0x80000000;
        CSR.SAT |= 1; // 1 delay slot
        if( datapath == a_path && unit == 'L' ) {
            ; // 1 delay slot
        } else if( unit == 'L' ) {
            ; // 1 delay slot
        } else if( datapath == a_path && unit == 'S' ) {
            ; // 1 delay slot
        } else if( unit == 'S' ) {
            ; // 1 delay slot
        }

    } else if((a >= 0) && (b >= 0) && (c < 0)) {
        /* If a and b are positive, but result is negative, saturate positive */
        c = 0x7fffffff;
        CSR.SAT |= 1; // 1 delay slot
        if( datapath == a_path && unit == 'L' ) {
            ; // 1 delay slot
        } else if( unit == 'L' ) {
            ; // 1 delay slot
        } else if( datapath == a_path && unit == 'S' ) {
            ; // 1 delay slot
        } else if( unit == 'S' ) {
            ; // 1 delay slot
        }
    }
    return (c);
}

static word sadd2(word a, word b)
{
    word    d_low, d_high, a_low, a_high, b_low, b_high;

    a_low = a & 0xffff;
    b_low = b & 0xffff;
    if( a_low & 0x8000 ) {
        a_low = a_low | 0xffff0000;
    }
    if( b_low & 0x8000 ) {
        b_low = b_low | 0xffff0000;
    }
    d_low  =  a_low + b_low;               /* Add the low 16-bits */
    if( d_low > (int) 0x7fff ) {
        d_low = 0x7fff;
    } else if( d_low < (int) 0xffff8000 ) {
        d_low = 0x8000;
    }

    d_low &= 0xFFFF; /* mask off upper bits */

    a_high = a >> 16;
    b_high = b >> 16;
    if( a_high & 0x8000 ) {
        a_high = a_high | 0xffff0000;
    }
    if( b_high & 0x8000 ) {
        b_high = b_high | 0xffff0000;
    }
    d_high  =  a_high + b_high;               /* Add the high 16-bits */
    if( d_high > (int) 0x7fff ) {
        d_high = 0x7fff;
    } else if( d_high < (int) 0xffff8000 ) {
        d_high = 0x8000;
    }

    d_high &= 0xffff; /* mask off upper bits */

    return ((d_high << 16) | d_low);
}

static word sat_check32(int64_ll a)
{
    int    i;

    // Joe Zbiciak test for saturation - just return sat or not

    i = 0x0;
    if( a >= ((int64_ll) 0x80000000)) {
        i = 0x1;
    }
    if( a < -((int64_ll) 0x80000000)) {
        i = 0x1;
    }

    return (i);
}

static word sat_jz(int64_ll a)
{
    int    i;

    // Joe Zbiciak test for saturation

    i = a;
    if( a >= ((int64_ll) 0x80000000)) {
        i = 0x7FFFFFFF;
    }
    if( a < -((int64_ll) 0x80000000)) {
        i = 0x80000000;
    }

    return (i);
}

static word sbyte0(word src)
{
    word    op;

    op = src & 0x000000ff;
    if( op & 0x00000080 ) {    /* Number is negative */
        return (0xffffff00 | op);
    } else {
        return (op);
    }
}

static word sbyte1(word src)
{
    word    op;

    op = (src & 0x0000ff00) >> 8;
    if( op & 0x00000080 ) {    /* Number is negative */
        return (0xffffff00 | op);
    } else {
        return (op);
    }
}

static word sbyte2(word src)
{
    word    op;

    op = (src & 0x00ff0000) >> 16;
    if( op & 0x00000080 ) {    /* Number is negative */
        return (0xffffff00 | op);
    } else {
        return (op);
    }
}

static word sbyte3(word src)
{
    word    op;

    op = (src & 0xff000000) >> 24;
    if( op & 0x00000080 ) {    /* Number is negative */
        return (0xffffff00 | op);
    } else {
        return (op);
    }
}

static word shigh16(word src)
{
    word    op;

    op = (src >> 16) & 0x0000FFFF;
    if( op & 0x00008000 ) {    /* Number is negative */
        return (0xffff0000 | op);
    } else {
        return (op);
    }
}

static word shl(word a, word l)
{
    if( l & 0x20 ) {   /* If bit 5 is set, then return all zeros */
        return (0);
    } else {
        return (a << (l & 0x1f));
    }
}

static word shl2(word op1, word op2)
{
    word    result;

    if( op2 & 0x10 ) {
        return (0);   // If we shift more than 16-bits, it's all zero!

    }
    // Perform low 1/2 shift
    result  = ((op1 & 0x0000FFFF) << (op2 & 0xf));
    result &= 0xFFFF;   // Truncate the shift of the low 16-bits to 16-bits

    // Perform high shift, and OR in the result
    result |= ((op1 & 0xFFFF0000) << (op2 & 0xf));

    return (result);
}

static word shr(word a, word r)
{
    word    shft;
    word    res;

    if( r & 0x20 ) {                   // Is bit 5 set?
        shft = 0x1f;
    } else {
        shft = r & 0x1f;               // Look at the bottom 5 bits for shift value
    }
    res = a >> shft;                   // perform shift

    // Perform the sign extension.
    if((a & 0x80000000) != 0 ) {       // if the sign bit is one (negative)
        res |=  Lmask(shft);         // then fill with 1's
    } else {
        res &= ~Lmask(shft);         // else fill with 0's
    }
    return (res);
}

static word shr2(word a, word r)
{
    word    upper_half, lower_half, result;

    r &= 0x1f;                          // shift count only observes bits 0-3
    upper_half = a >> r;   // break into separate operations
    lower_half = a >> r;   // both halves of word are shifted

    if((a & 0x80000000) != 0 ) {        // if msb of upper half is one (negative)
        upper_half |= Lmask(r);       // then fill upper half with 1's
    } else {
        upper_half &= ~Lmask (r);     // else fill upper half with 0's
    }

    if((a & 0x8000) != 0 ) {            // if msb of lower half is one (negative)
        lower_half |= (Lmask(r) >> 16);     // then fill lower half with 1's
    } else {
        lower_half &= ~(Lmask(r) >> 16);    // else fill lower half with 0's
    }

    lower_half &=  0x0000ffff;          // build result
    upper_half &=  0xffff0000;
    result = upper_half | lower_half;
    return (result);
}

static word shru(word a, word r)
{
    if( r & 0x20 ) {                     // 32 <= r < 64
        return (0);
    } else {
        return (((uword) a) >> (r & 0x1f)); // Look at the bottom 5 bits for shift value
    }
}

static word shru2(word a, word r)
{
    word    upper_half, lower_half, result;

    r &= 0x1f;                          // shift count only observes bits 0-3
    upper_half = a >> r;
    lower_half = a >> r;   // both halves of word are shifted

    upper_half &= ~Lmask (r);         // fill upper half with 0's
    lower_half &= ~(Lmask(r) >> 16);          // fill lower half with 0's

    lower_half &=  0x0000ffff;          // build result
    upper_half &=  0xffff0000;
    result = upper_half | lower_half;
    return (result);
}

static word slow16(word src)
{
    word    op;

    op = src & 0x0000FFFF;
    if( op & 0x00008000 ) {    /* Number is negative */
        return (0xffff0000 | op);
    } else {
        return (op);
    }
}

static dword smpy2(word op1, word op2, word op3, word op4)
{
    dword    prod;
    uword    sat;

    sat = 0;
    prod.low = ((op1 * op2) << 1);
    if( prod.low == 0x80000000 ) {
        prod.low = 0x7FFFFFFF;
        sat = 1;
    }
    prod.high = ((op3 * op4) << 1);
    if( prod.high == 0x80000000 ) {
        prod.high = 0x7FFFFFFF;
        sat = 1;
    }
    if( sat ) {
        CSR.SAT |= 1; // 4 delay slots
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }
    }
    return (prod);
}

static word smpy32r1(word a, word b)
{
    dword       temp;
    int64_ll    temp2;
    word        result;

    // preliminary change to match the yet to be released function

    if( a == 0x80000000 && b == 0x80000000 ) {
        // special case - due to precision cannot produce result - spec says sat to 0x7fffffff
        // only case of possible sat
        result = 0x7fffffff;

        // sat test on results
        CSR.SAT |= 1; // 4 delay slot
        if( datapath == a_path ) {
            ; // 4 delay slot
        } else {
            ; // 4 delay slot
        }

    } else {
        temp = mpy32_joule(a, b);

        temp2 = ((((int64_ll) temp.high) << 32) | (temp.low & 0xffffffff)) + ((int64_ll) 0x40000000);

        result = temp2 >> 31;
    }

    return (result);
}

static word spack2(word a, word b)
{
    word    d0, d1, dst;

    if( a > (int)0x00007fff ) {
        d0 = 0x7fff;
    } else if( a < (int)0xffff8000 ) {
        d0 = 0x8000;
    } else { d0 = a & 0xffff;
    }

    if( b > (int)0x00007fff ) {
        d1 = 0x7fff;
    } else if( b < (int)0xffff8000 ) {
        d1 = 0x8000;
    } else { d1 = b & 0xffff;
    }

    dst = (d0 << 16) | d1;
    return (dst);
}

static word spack4(word a, word b)
{
    word    x0, x1, x2, x3, d0, d1, d2, d3, dst;

    x0 = (a >> 16) & 0xffff;
    x1 = a & 0xffff;
    x2 = (b >> 16) & 0xffff;
    x3 = b & 0xffff;

    d0 = x0 & 0xff;
    if( x0 & 0xff00 ) {
        if( x0 & 0x8000 ) {
            d0 = 0;
        } else { d0 = 0xff;
        }
    }

    d1 = x1 & 0xff;
    if( x1 & 0xff00 ) {
        if( x1 & 0x8000 ) {
            d1 = 0;
        } else { d1 = 0xff;
        }
    }

    d2 = x2 & 0xff;
    if( x2 & 0xff00 ) {
        if( x2 & 0x8000 ) {
            d2 = 0;
        } else { d2 = 0xff;
        }
    }

    d3 = x3 & 0xff;
    if( x3 & 0xff00 ) {
        if( x3 & 0x8000 ) {
            d3 = 0;
        } else { d3 = 0xff;
        }
    }

    dst = (d0 << 24) | (d1 << 16) | (d2 << 8) | d3;

    return (dst);
}

static word spinth(word op)
{
    word    sign;
    word    exp;
    word    man;
    word    round;
    word    sticky;
    word    result;
    word    check;

    sign = extract_sign(op);
    if( snan_chk_sp(op) || qnan_chk_sp(op)) {
        if( datapath == a_path ) {
            FADCR.INVALADD1 |= 1; // 2 delay slots
            FADCR.NAN2ADD1 |= 1; // 2 delay slots
        } else {
            FADCR.INVALADD2 |= 1; // 2 delay slots
            FADCR.NAN2ADD2 |= 1; // 2 delay slots
        }
        return (sign ? 0x80008000 : 0x7fff7fff);
    }

    exp = extract_exp_sp(op) - 127;
    man = extract_man_sp(op);
    check = 0;
    if( inf_chk_sp(op)) {
        check = 1;
    }
    if( exp > 15 ) {
        check = 1;
    }
    if((exp == 15) && !sign ) {
        check = 1;
    }
    if((exp == 15) && sign && (op & 0x007fff00)) {
        check = 1;
    }
    if( check ) {
        if( datapath == a_path ) {
            FADCR.INEXADD1 |= 1; // 2 delay slots
            FADCR.OVERADD1 |= 1; // 2 delay slots
        } else {
            FADCR.INEXADD2 |= 1; // 2 delay slots
            FADCR.OVERADD2 |= 1; // 2 delay slots
        }
        return (sign ? 0x80008000 : 0x7fff7fff);
    }

    if( denorm_chk_sp(op)) {
        if( datapath == a_path ) {
            FADCR.INEXADD1 |= 1; // 2 delay slots
            FADCR.DEN2ADD1 |= 1; // 2 delay slots
        } else {
            FADCR.INEXADD2 |= 1; // 2 delay slots
            FADCR.DEN2ADD2 |= 1; // 2 delay slots
        }
        return (0);
    }

    if( exp == -127 ) {
        return (0);
    }

    if( exp < 0 ) {
        result = 0;
        round = (exp == -1);
        sticky = (exp == -1) ? (man & 0x007fffff) : 1;
    } else if( exp >= 23 ) {
        result = man << (exp - 23);
        round = 0;
        sticky = 0;
    } else {
        result = man >> (23 - exp);
        man <<= exp + 9;
        round = (man & 0x80000000) ? 1 : 0;
        sticky = (man & 0x7fffffff) ? 1 : 0;
    }

    result = round_inth(result, sign, round, sticky);
    return (result);
}

static word ssub(word a, word b)
{
    word    c;

    c = a - b;
    if((a < 0) && (b >= 0) && (c >= 0)) {
        /* If a is negative and b is positive, but result is positive, saturate negative */
        c = 0x80000000;
        CSR.SAT |= 1; // 1 delay slot
        if( datapath == a_path ) {
            ; // 1 delay slot
        } else {
            ; // 1 delay slot
        }
    } else if((a >= 0) && (b < 0) && (c < 0)) {
        /* If a is positive and b is negative, but result is negative, saturate positive */
        c = 0x7fffffff;
        CSR.SAT |= 1; // 1 delay slot
        if( datapath == a_path ) {
            ; // 1 delay slot
        } else {
            ; // 1 delay slot
        }
    }
    return (c);
}

static word ssub2_joule(word a, word b)
{
    int     a_lo, b_lo, a_hi, b_hi;
    word    result;
    int     u_tmp;

    // spec says this does not change the CSR.sat bit

    a_lo   = slow16(a);
    a_hi = shigh16(a);
    b_lo   = slow16(b);
    b_hi = shigh16(b);

    u_tmp  = a_hi - b_hi;

    // check to see if the result saturated

    if((a_hi & 0x8000) && !(b_hi & 0x8000) && !(u_tmp & 0x8000)) {
        u_tmp = 0x8000;
    }
    if( !(a_hi & 0x8000) && (b_hi & 0x8000) && (u_tmp & 0x8000)) {
        u_tmp = 0x7fff;
    }

    result = (u_tmp << 16) & 0xffff0000;

    u_tmp   = a_lo - b_lo;

    // check to see if the result saturated

    if((a_lo & 0x8000) && !(b_lo & 0x8000) && !(u_tmp & 0x8000)) {
        u_tmp = 0x8000;
    }
    if( !(a_lo & 0x8000) && (b_lo & 0x8000) && (u_tmp & 0x8000)) {
        u_tmp = 0x7fff;
    }

    result |= (u_tmp & 0x0000ffff);

    return (result);
}

static word sub2(word a, word b)
{
    word    d_low, d_high;

    d_low  =  0x0000ffff & (a - b);                 /* Subtract the low 16-bits */
    d_high = (0xffff0000 & a) - (0xffff0000 & b);   /* Subtract the high 16-bits */

    return (d_high | d_low);
}

static word sub_sp(word op1, word op2, int cr_wr_delay)
{

    return (add_sp(op1, op2 ^ 0x80000000, cr_wr_delay));
}

static word ubyte0(word src)
{
    word    op;

    op = src & 0x000000ff;
    return (op);
}

static word ubyte1(word src)
{
    word    op;

    op = (src & 0x0000ff00) >> 8;
    return (op);
}

static word ubyte2(word src)
{
    word    op;

    op = (src & 0x00ff0000) >> 16;
    return (op);
}

static word ubyte3(word src)
{
    word    op;

    op = (src >> 24) & 0x000000ff;
    return (op);
}

static word uhigh16(word src)
{
    word    op;

    op = (src >> 16) & 0x0000FFFF;
    return (op);
}

static word ulow16(word src)
{
    word    op;

    op = src & 0x0000FFFF;
    return (op);
}

static word unpkhu4(word a)
{
    word    upper_half, lower_half, result;

    upper_half = a >> 8 & 0x00ff0000;
    lower_half = a >> 16 & 0x000000ff;
    result = upper_half | lower_half;
    return (result);
}

static word unpklu4(word a)
{
    word    upper_half, lower_half, result;

    upper_half = a << 8 & 0x00ff0000;
    lower_half = a & 0x000000ff;
    result = upper_half | lower_half;
    return (result);
}

static dword xor_cl(word op1, dword op2)
{
    dword    result;

    result.high = op1 ^ op2.high;
    result.low  = op1 ^ op2.low;

    return (result);
}

#endif /* #ifdef TMS320C66X */

#ifdef TMS320C67X
static word denorm_chk_dp(dword op)
{

    //return( !(op.high & 0x7ff00000) &&
    //        ( (op.high & 0x000fffff) || op.low ) ) ;

    if( !(op.high & 0x7ff00000) && ((op.high & 0x000fffff) || op.low)) {
        return (1);
    } else {
        return (0);
    }
}

static word dpint(dword op)
{
    word     sign;
    word     exp;
    dword    man;
    word     round;
    word     sticky;
    word     result;
    word     check;

    sign = extract_sign(op.high);
    if( snan_chk_dp(op) || qnan_chk_dp(op)) {
        if( datapath == a_path ) {
            FADCR.NAN2ADD1 |= 1; // 3 delay slots
            FADCR.INVALADD1 |= 1; // 3 delay slots
        } else {
            FADCR.NAN2ADD2 |= 1; // 3 delay slots
            FADCR.INVALADD2 |= 1; // 3 delay slots
        }
        return (sign ? 0x80000000 : 0x7fffffff);
    }

    check = 0;
    exp = extract_exp_dp(op) - 1023;
    man = extract_man_dp(op);
    if( inf_chk_dp(op)) {
        check = 1;
    }
    if( exp > 31 ) {
        check = 1;
    }
    if((exp == 31) && !sign ) {
        check = 1;
    }
    if((exp == 31) && sign & ((op.high & 0x000fffff) || (op.low & 0xffe00000))) {
        check = 1;
    }
    if( check ) {
        if( datapath == a_path ) {
            FADCR.INEXADD1 |= 1; // 3 delay slots
            FADCR.OVERADD1 |= 1; // 3 delay slots
        } else {
            FADCR.INEXADD2 |= 1; // 3 delay slots
            FADCR.OVERADD2 |= 1; // 3 delay slots
        }
        return (sign ? 0x80000000 : 0x7fffffff);
    }

    if( denorm_chk_dp(op)) {
        if( datapath == a_path ) {
            FADCR.INEXADD1 |= 1; // 3 delay slots
            FADCR.DEN2ADD1 |= 1; // 3 delay slots
        } else {
            FADCR.INEXADD2 |= 1; // 3 delay slots
            FADCR.DEN2ADD2 |= 1; // 3 delay slots
        }
        return (0);
    }

    if( exp == -1023 ) {
        return (0);
    }

    if( exp < 0 ) {
        result = 0;
        round = (exp == -1);
        sticky = (exp == -1) ? ((man.high & 0x000fffff) || man.low) : 1;
    } else if( exp > 20 ) {
        man = lshift_dp(man, exp - 20);
        result = man.high;
        round = (man.low & 0x80000000) ? 1 : 0;
        sticky = (man.low & 0x7fffffff) ? 1 : 0;
    } else if( exp == 20 ) {
        result = man.high;
        round = (man.low & 0x80000000) ? 1 : 0;
        sticky = (man.low & 0x7fffffff);
    } else { // exp < 20
        man = rshift_dp(man, 20 - exp);
        result = man.high;
        round = (man.low & 0x80000000) ? 1 : 0;
        sticky = (man.low & 0x7fffffff) || (op.low << (exp + 12));
    }

    result = round_int(result, sign, round, sticky, 3);
    return (result);
}

static word excp_chk_mpy_spdp(word op1, dword op2)
{
    word    exp1, exp2, zero, inf, snan, qnan;

    if( snan_chk_sp(op1)) {
        if( datapath == a_path ) {
            FMCR.INVALMPY1 |= 1;                            // 5 delay slots
            FMCR.NAN1MPY1 |= 1;                             // 5 delay slots
            FMCR.NAN2MPY1 |= (snan_chk_dp(op2) || qnan_chk_dp(op2));    // 5 delay slots
            FMCR.DEN2MPY1 |= denorm_chk_dp(op2);                // 5 delay slots
        } else {
            FMCR.INVALMPY2 |= 1;                            // 5 delay slots
            FMCR.NAN1MPY2 |= 1;                             // 5 delay slots
            FMCR.NAN2MPY2 |= (snan_chk_dp(op2) || qnan_chk_dp(op2));    // 5 delay slots
            FMCR.DEN2MPY2 |= denorm_chk_dp(op2);                // 5 delay slots
        }
        return (1);
    }
    if( snan_chk_dp(op2)) {
        if( datapath == a_path ) {
            FMCR.INVALMPY1 |= 1;            // 5 delay slots
            FMCR.NAN1MPY1 |= qnan_chk_sp(op1);  // 5 delay slots
            FMCR.NAN2MPY1 |= 1;             // 5 delay slots
            FMCR.DEN1MPY1 |= denorm_chk_sp(op1); // 5 delay slots
        } else {
            FMCR.INVALMPY2 |= 1;            // 5 delay slots
            FMCR.NAN1MPY2 |= qnan_chk_sp(op1);  // 5 delay slots
            FMCR.NAN2MPY2 |= 1;             // 5 delay slots
            FMCR.DEN1MPY2 |= denorm_chk_sp(op1); // 5 delay slots
        }
        return (1);
    }
    if( qnan_chk_sp(op1)) {
        if( datapath == a_path ) {
            FMCR.NAN1MPY1 |= 1;             // 5 delay slots
            FMCR.NAN2MPY1 |= qnan_chk_dp(op2);  // 5 delay slots
            FMCR.DEN2MPY1 |= denorm_chk_dp(op2); // 5 delay slots
        } else {
            FMCR.NAN1MPY2 |= 1;             // 5 delay slots
            FMCR.NAN2MPY2 |= qnan_chk_dp(op2);  // 5 delay slots
            FMCR.DEN2MPY2 |= denorm_chk_dp(op2); // 5 delay slots
        }
        return (1);
    }
    if( qnan_chk_dp(op2)) {
        if( datapath == a_path ) {
            FMCR.NAN2MPY1 |= 1;             // 5 delay slots
            FMCR.DEN1MPY1 |= denorm_chk_sp(op1); // 5 delay slots
        } else {
            FMCR.NAN2MPY2 |= 1;             // 5 delay slots
            FMCR.DEN1MPY2 |= denorm_chk_sp(op1); // 5 delay slots
        }
        return (1);
    }

    exp1 = extract_exp_sp(op1);
    exp2 = extract_exp_dp(op2);

    if( denorm_chk_sp(op1)) {
        if( datapath == a_path ) {
            FMCR.DEN1MPY1 |= 1;                 // 5 delay slots
            zero = !((op2.high & 0x7fffffff) || op2.low);
            inf  = inf_chk_dp(op2);
            snan = qnan_chk_dp(op2);
            qnan = snan_chk_dp(op2);
            FMCR.INEXMPY1 |=  !(zero) && !(inf) && !(snan) && !(qnan); // 5 delay slots
        } else {
            FMCR.DEN1MPY2 |= 1;                 // 5 delay slots
            zero = !((op2.high & 0x7fffffff) || op2.low);
            inf  = inf_chk_dp(op2);
            snan = qnan_chk_dp(op2);
            qnan = snan_chk_dp(op2);
            FMCR.INEXMPY2 |=  !(zero) && !(inf) && !(snan) && !(qnan); // 5 delay slots
        }
    }
    if( denorm_chk_dp(op2)) {
        if( datapath == a_path ) {
            FMCR.DEN2MPY1 |= 1;                 // 5 delay slots
            zero = !(op1 & 0x7fffffff);
            inf  = inf_chk_sp(op1);
            snan = qnan_chk_sp(op1);
            qnan = snan_chk_sp(op1);
            FMCR.INEXMPY1 |=  !(zero) && !(inf) && !(snan) && !(qnan); // 5 delay slots
        } else {
            FMCR.DEN2MPY2 |= 1;                 // 5 delay slots
            zero = !(op1 & 0x7fffffff);
            inf  = inf_chk_sp(op1);
            snan = qnan_chk_sp(op1);
            qnan = snan_chk_sp(op1);
            FMCR.INEXMPY2 |=  !(zero) && !(inf) && !(snan) && !(qnan); // 5 delay slots
        }
    }

    if( inf_chk_sp(op1)) {
        if( !exp2 ) {
            if( datapath == a_path ) {
                FMCR.INVALMPY1 |= 1; // 5 delay slots
            } else {
                FMCR.INVALMPY2 |= 1; // 5 delay slots
            }
            return (1);
        } else {
            if( datapath == a_path ) {
                FMCR.INFOMPY1 |= 1; // 5 delay slots
            } else {
                FMCR.INFOMPY2 |= 1; // 5 delay slots
            }
            return (2);
        }
    }
    if( inf_chk_dp(op2)) {
        if( !exp1 ) {
            if( datapath == a_path ) {
                FMCR.INVALMPY1 |= 1; // 5 delay slots
            } else {
                FMCR.INVALMPY2 |= 1; // 5 delay slots
            }
            return (1);
        } else {
            if( datapath == a_path ) {
                FMCR.INFOMPY1 |= 1; // 5 delay slots
            } else {
                FMCR.INFOMPY2 |= 1; // 5 delay slots
            }
            return (2);
        }
    }
    return (0);

}

static word extract_exp_dp(dword op)
{

    return ((op.high & 0x7ff00000) >> 20);
}

static dword extract_man_dp(dword op)
{
    dword    result;

    result.low  = op.low;
    result.high = (op.high & 0x000fffff) | 0x00100000;
    return (result);
}

static dword increment_dp(dword op)
{
    dword    result;

    if( op.low == 0xffffffff ) {
        result.low = 0;
        result.high = op.high + 1;
    } else {
        result.low = op.low + 1;
        result.high = op.high;
    }
    return (result);
}

static word inf_chk_dp(dword op)
{

    //return( ( (op.high & 0x7ff00000) == 0x7ff00000 ) &&
    //        !(op.high & 0x000fffff)                  &&
    //          !op.low ) ;

    if(((op.high & 0x7ff00000) == 0x7ff00000) &&
       !(op.high & 0x000fffff) &&
       !op.low ) {
        return (1);
    } else {
        return (0);
    }
}

static dword lshift_dp(dword op, word shift)
{
    dword    result;

    shift %= 32;
    result.high = shift ? (op.high << shift) | (((uword) op.low) >> 32 - shift) : op.low;
    result.low = op.low << shift;
    return (result);
}

static dword mpy_sp2dp(word op1, word op2)
{
    word     sign1, sign2, result_sign;
    word     rc;
    word     exp1, exp2;
    word     man1, man2;
    dword    prod_man;
    word     result_man;
    word     result_exp;
    dword    result;
    word     round, sticky;

    sign1 = extract_sign(op1);
    sign2 = extract_sign(op2);
    result_sign = sign1 ? !sign2 : sign2;

    rc = excp_chk_mpy_sp(op1, op2);

    if( rc == 1 ) {
        result.high = result_sign ? 0xffffffff : 0x7fffffff;
        result.low  = 0xffffffff;
        return (result);
    } else if( rc == 2 ) {
        result.high = result_sign ? 0xfff00000 : 0x7ff00000;
        result.low  = 0;
        return (result);
    }

    exp1 = extract_exp_sp(op1);
    exp2 = extract_exp_sp(op2);

    if( !exp1 || !exp2 ) {                         /* one operand is zero or denormal */
        result.high = result_sign ? 0x80000000 : 0;
        result.low  = 0;
        return (result);
    }

    result_exp = exp1 + exp2 + 769; /* == - 127 - 127 + 1023 */

    man1 = extract_man_sp(op1);
    man2 = extract_man_sp(op2);

    prod_man = mpyid(man1, man2);

    if( prod_man.high & 0x00008000 ) {
        result_exp++;
        result.high = (result_sign << 31) | (result_exp << 20) |
                      ((prod_man.high << 5) & 0xfffff) | ((prod_man.low >> 27) & 0x1f);
        result.low  = (prod_man.low << 5) & 0xffffffff;
    } else {
        result.high = (result_sign << 31) | (result_exp << 20) |
                      ((prod_man.high << 6) & 0xfffff) | ((prod_man.low >> 26) & 0x3f);
        result.low  = (prod_man.low << 6) & 0xffffffff;
    }

    return (result);
}

static dword mpy_spdp(word op1, dword op2)
{
    word     sign1, sign2, result_sign;
    word     rc;
    dword    result;
    word     exp1, exp2, result_exp, man1;
    dword    man2, result_man;
    word     pp00, pp01, pp02, pp03, pp10, pp11, pp12, pp13;
    word     pp20, pp21, pp22, pp23, pp30, pp31, pp32, pp33;
    word     prod0, prod1, prod2, prod3;
    word     tmp1;
    word     sticky, round;

    sign1 = extract_sign(op1);
    sign2 = extract_sign(op2.high);
    result_sign = sign1 ? !sign2 : sign2;

    rc = excp_chk_mpy_spdp(op1, op2);
    if( rc == 1 ) {
        result.high = result_sign ? 0xffffffff : 0x7fffffff;
        result.low  = 0xffffffff;
        return (result);
    } else if( rc == 2 ) {
        result.high = result_sign ? 0xfff00000 : 0x7ff00000;
        result.low  = 0;
        return (result);
    }

    exp1 = extract_exp_sp(op1);
    exp2 = extract_exp_dp(op2);

    if( !exp1 || !exp2 ) {                         /* one operand is zero or denormal */
        result.high = result_sign ? 0x80000000 : 0;
        result.low  = 0;
        return (result);
    }

    result_exp = exp1 + exp2 - 127;

    man1 = extract_man_sp(op1);
    man2 = extract_man_dp(op2);

    pp00 = (man1 & 0x0000ffff)            * (man2.low & 0x0000ffff);
    pp01 = (man1 & 0x0000ffff)            * (((unsigned) man2.low) >> 16);
    pp02 = (man1 & 0x0000ffff)            * (man2.high & 0x0000ffff);
    pp03 = (man1 & 0x0000ffff)            * (man2.high >> 16);
    pp10 = (((unsigned) man1) >> 16)     * (man2.low & 0x0000ffff);
    pp11 = (((unsigned) man1) >> 16)     * (((unsigned) man2.low) >> 16);
    pp12 = (((unsigned) man1) >> 16)     * (man2.high & 0x0000ffff);
    pp13 = (((unsigned) man1) >> 16)     * (man2.high >> 16);
    pp20 = 0;
    pp21 = 0;
    pp22 = 0;
    pp23 = 0;
    pp30 = 0;
    pp31 = 0;
    pp32 = 0;
    pp33 = 0;

    prod0 = pp00;
    prod1 = 0;
    prod2 = 0;
    prod3 = 0;

    tmp1 = prod0;
    prod0 += (pp01 << 16);
    prod1 += carry_out(tmp1, (pp01 << 16));
    tmp1 = prod0;
    prod0 += (pp10 << 16);
    prod1 += carry_out(tmp1, (pp10 << 16));
    prod1 += ((unsigned) pp01) >> 16;
    prod1 += ((unsigned) pp10) >> 16;
    tmp1 = prod1;
    prod1 += pp02;
    prod2 += carry_out(tmp1, pp02);
    tmp1 = prod1;
    prod1 += pp11;
    prod2 += carry_out(tmp1, pp11);
    tmp1 = prod1;
    prod1 += pp20;
    prod2 += carry_out(tmp1, pp20);
    tmp1 = prod1;
    prod1 += (pp03 << 16);
    prod2 += carry_out(tmp1, (pp03 << 16));
    tmp1 = prod1;
    prod1 += (pp12 << 16);
    prod2 += carry_out(tmp1, (pp12 << 16));
    tmp1 = prod1;
    prod1 += (pp21 << 16);
    prod2 += carry_out(tmp1, (pp21 << 16));
    tmp1 = prod1;
    prod1 += (pp30 << 16);
    prod2 += carry_out(tmp1, (pp30 << 16));
    prod2 += ((unsigned) pp03) >> 16;
    prod2 += ((unsigned) pp12) >> 16;
    prod2 += ((unsigned) pp21) >> 16;
    prod2 += ((unsigned) pp30) >> 16;
    tmp1 = prod2;
    prod2 += pp13;
    prod3 += carry_out(tmp1, pp13);
    tmp1 = prod2;
    prod2 += pp22;
    prod3 += carry_out(tmp1, pp22);
    tmp1 = prod2;
    prod2 += pp31;
    prod3 += carry_out(tmp1, pp31);
    tmp1 = prod2;
    prod2 += (pp23 << 16);
    prod3 += carry_out(tmp1, (pp23 << 16));
    tmp1 = prod2;
    prod2 += (pp32 << 16);
    prod3 += carry_out(tmp1, (pp32 << 16));
    prod3 += ((unsigned) pp23) >> 16;
    prod3 += ((unsigned) pp32) >> 16;
    prod3 += pp33;

    /* have a 76/77 bit product */
    if( prod2 & 0x00001000 ) {
        result_man.high = (prod2 << 8) | ((prod1 >> 24) & 0x000000ff);
        result_man.low  = (prod1 << 8) | ((prod0 >> 24) & 0x000000ff);
        result_exp++;
        round = (prod0 & 0x00800000) ? 1 : 0;
        sticky = prod0 & 0x007fffff;
    } else {
        result_man.high = (prod2 << 9) | ((prod1 >> 23) & 0x000001ff);
        result_man.low  = (prod1 << 9) | ((prod0 >> 23) & 0x000001ff);
        round = (prod0 & 0x00400000) ? 1 : 0;
        sticky = prod0 & 0x003fffff;
    }

    /* TODO take proper delays into acount for round mode writing */
    result = round_ofuf_chk_dp(result_sign, result_exp, result_man, round, sticky, 0, 5);
    return (result);
}

static word qnan_chk_dp(dword op)
{

    // return( (op.high & 0x7ff80000) == 0x7ff80000 ) ;

    if((op.high & 0x7ff80000) == 0x7ff80000 ) {
        return (1);
    } else {
        return (0);
    }
}

static uword rcp(uword index)
{
    static unsigned char    reciprocalTable[] =
    {
        0x00, 0xfe, 0xfc, 0xfa, 0xf8, 0xf6, 0xf4, 0xf2,
        0xf0, 0xef, 0xed, 0xeb, 0xe9, 0xe7, 0xe5, 0xe4,
        0xe2, 0xe0, 0xde, 0xdd, 0xdb, 0xd9, 0xd7, 0xd6,
        0xd4, 0xd2, 0xd1, 0xcf, 0xce, 0xcc, 0xca, 0xc9,
        0xc7, 0xc6, 0xc4, 0xc2, 0xc1, 0xbf, 0xbe, 0xbc,
        0xbb, 0xb9, 0xb8, 0xb6, 0xb5, 0xb3, 0xb2, 0xb1,
        0xaf, 0xae, 0xac, 0xab, 0xaa, 0xa8, 0xa7, 0xa5,
        0xa4, 0xa3, 0xa1, 0xa0, 0x9f, 0x9d, 0x9c, 0x9b,
        0x9a, 0x98, 0x97, 0x96, 0x95, 0x93, 0x92, 0x91,
        0x90, 0x8e, 0x8d, 0x8c, 0x8b, 0x8a, 0x88, 0x87,
        0x86, 0x85, 0x84, 0x83, 0x82, 0x80, 0x7f, 0x7e,
        0x7d, 0x7c, 0x7b, 0x7a, 0x79, 0x78, 0x76, 0x75,
        0x74, 0x73, 0x72, 0x71, 0x70, 0x6f, 0x6e, 0x6d,
        0x6c, 0x6b, 0x6a, 0x69, 0x68, 0x67, 0x66, 0x65,
        0x64, 0x63, 0x62, 0x61, 0x60, 0x5f, 0x5e, 0x5e,
        0x5d, 0x5c, 0x5b, 0x5a, 0x59, 0x58, 0x57, 0x56,
        0x55, 0x54, 0x54, 0x53, 0x52, 0x51, 0x50, 0x4f,
        0x4e, 0x4e, 0x4d, 0x4c, 0x4b, 0x4a, 0x49, 0x49,
        0x48, 0x47, 0x46, 0x45, 0x44, 0x44, 0x43, 0x42,
        0x41, 0x40, 0x40, 0x3f, 0x3e, 0x3d, 0x3d, 0x3c,
        0x3b, 0x3a, 0x3a, 0x39, 0x38, 0x37, 0x37, 0x36,
        0x35, 0x34, 0x34, 0x33, 0x32, 0x32, 0x31, 0x30,
        0x2f, 0x2f, 0x2e, 0x2d, 0x2d, 0x2c, 0x2b, 0x2b,
        0x2a, 0x29, 0x29, 0x28, 0x27, 0x27, 0x26, 0x25,
        0x25, 0x24, 0x23, 0x23, 0x22, 0x21, 0x21, 0x20,
        0x1f, 0x1f, 0x1e, 0x1e, 0x1d, 0x1c, 0x1c, 0x1b,
        0x1a, 0x1a, 0x19, 0x19, 0x18, 0x17, 0x17, 0x16,
        0x16, 0x15, 0x15, 0x14, 0x13, 0x13, 0x12, 0x12,
        0x11, 0x10, 0x10, 0x0f, 0x0f, 0x0e, 0x0e, 0x0d,
        0x0d, 0x0c, 0x0b, 0x0b, 0x0a, 0x0a, 0x09, 0x09,
        0x08, 0x08, 0x07, 0x07, 0x06, 0x06, 0x05, 0x05,
        0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01
    };

    return (reciprocalTable[index]);
}

static dword rcp_dp(dword op)
{
    dword    result;
    word     sign, exp;
    dword    man;
    uword    index;

    if( snan_chk_dp(op)) {
        result.high = 0x7fffffff;
        result.low  = 0xffffffff;
        if( datapath == a_path ) {
            FAUCR.NAN2AU1 |= 1;
            FAUCR.INVALAU1 |= 1;
        } else {
            FAUCR.NAN2AU2 |= 1;
            FAUCR.INVALAU2 |= 1;
        }
        return (result);
    }
    if( qnan_chk_dp(op)) {
        result.high = 0x7fffffff;
        result.low  = 0xffffffff;
        if( datapath == a_path ) {
            FAUCR.NAN2AU1 |= 1;
        } else {
            FAUCR.NAN2AU2 |= 1;
        }
        return (result);
    }

    sign = extract_sign(op.high);
    exp = extract_exp_dp(op);
    if( exp == 0 ) {
        result.high = sign ? 0xfff00000 : 0x7ff00000;
        result.low  = 0;
        if( datapath == a_path ) {
            FAUCR.DIV0AU1 |= 1;
            FAUCR.INFOAU1 |= 1;
            if( denorm_chk_dp(op)) {
                FAUCR.INEXAU1 |= 1;
                FAUCR.OVERAU1 |= 1;
                FAUCR.DEN2AU1 |= 1;
            }
        } else {
            FAUCR.DIV0AU2 |= 1;
            FAUCR.INFOAU2 |= 1;
            if( denorm_chk_dp(op)) {
                FAUCR.INEXAU2 |= 1;
                FAUCR.OVERAU2 |= 1;
                FAUCR.DEN2AU2 |= 1;
            }
        }
        return (result);
    }
    if( inf_chk_dp(op)) {
        result.high = sign ? 0x80000000 : 0;
        result.low  = 0;
        return (result);
    }
    man = extract_man_dp(op);
    if((exp > 2045) || ((exp == 2045) && ((man.high & 0x000fffff) | man.low))) {               /* op > 2^1022 ?; 2045 = 1022 + 0x3ff */
        result.high = sign ? 0x80000000 : 0;
        result.low  = 0;
        if( datapath == a_path ) {
            FAUCR.UNDERAU1 |= 1;
            FAUCR.INEXAU1 |= 1;
        } else {
            FAUCR.UNDERAU2 |= 1;
            FAUCR.INEXAU2 |= 1;
        }
        return (result);
    }

    index = (man.high >> 12) & 0x000000ff;
    exp = 0x7fd - exp;
    exp += !index;
    result.high = rcp(index) << 12;
    result.high |= (exp << 20) & 0x7ff00000;
    result.high |= sign << 31;
    result.low = 0;
    if((op.high & 0x000fffff) || op.low ) {
        if( datapath == a_path ) {
            FAUCR.INEXAU1 |= 1;
        } else { FAUCR.INEXAU2 |= 1;
        }
    }
    return (result);
}

static word rcp_sp(word op)
{
    word     sign, exp, man;
    uword    index;
    word     result;

    if( snan_chk_sp(op)) {
        if( datapath == a_path ) {
            FAUCR.NAN2AU1 |= 1;
            FAUCR.INVALAU1 |= 1;
        } else {
            FAUCR.NAN2AU2 |= 1;
            FAUCR.INVALAU2 |= 1;
        }
        return (0x7fffffff);
    }
    if( qnan_chk_sp(op)) {
        if( datapath == a_path ) {
            FAUCR.NAN2AU1 |= 1;
        } else {
            FAUCR.NAN2AU2 |= 1;
        }
        return (0x7fffffff);
    }

    sign = extract_sign(op);
    exp = extract_exp_sp(op);
    if( exp == 0 ) {
        if( datapath == a_path ) {
            FAUCR.DIV0AU1 |= 1;
            FAUCR.INFOAU1 |= 1;
            if( denorm_chk_sp(op)) {
                FAUCR.INEXAU1 |= 1;
                FAUCR.OVERAU1 |= 1;
                FAUCR.DEN2AU1 |= 1;
            }
        } else {
            FAUCR.DIV0AU2 |= 1;
            FAUCR.INFOAU2 |= 1;
            if( denorm_chk_sp(op)) {
                FAUCR.INEXAU2 |= 1;
                FAUCR.OVERAU2 |= 1;
                FAUCR.DEN2AU2 |= 1;
            }
        }
        return (sign ? 0xff800000 : 0x7f800000);
    }
    if( inf_chk_sp(op)) {
        return (sign ? 0x80000000 : 0);
    }
    man = extract_man_sp(op);
    if((exp > 253) || ((exp == 253) && (man & 0x007fffff))) {          /* op > 2^126 ? ; 253 = 126 + 3f */
        if( datapath == a_path ) {
            FAUCR.UNDERAU1 |= 1;
            FAUCR.INEXAU1 |= 1;
        } else {
            FAUCR.UNDERAU2 |= 1;
            FAUCR.INEXAU2 |= 1;
        }
        return (sign ? 0x80000000 : 0);
    }

    index = (man >> 15) & 0x000000ff;
    exp = 0xfd - exp;
    exp += !index;
    result =  rcp(index) << 15;
    result |= (sign << 31) | (exp << 23);
    if( op & 0x007fffff ) {
        if( datapath == a_path ) {
            FAUCR.INEXAU1 |= 1;
        } else { FAUCR.INEXAU2 |= 1;
        }
    }
    return (result);
}

static uword rcpsq(uword index)
{
    static unsigned char    sqrtReciprocalTable[] =
    {
        0x6a, 0x69, 0x69, 0x68, 0x67, 0x67, 0x66, 0x65,
        0x65, 0x64, 0x63, 0x63, 0x62, 0x61, 0x61, 0x60,
        0x5f, 0x5f, 0x5e, 0x5d, 0x5d, 0x5c, 0x5b, 0x5b,
        0x5a, 0x5a, 0x59, 0x58, 0x58, 0x57, 0x57, 0x56,
        0x55, 0x55, 0x54, 0x54, 0x53, 0x52, 0x52, 0x51,
        0x51, 0x50, 0x50, 0x4f, 0x4e, 0x4e, 0x4d, 0x4d,
        0x4c, 0x4c, 0x4b, 0x4b, 0x4a, 0x4a, 0x49, 0x48,
        0x48, 0x47, 0x47, 0x46, 0x46, 0x45, 0x45, 0x44,
        0x44, 0x43, 0x43, 0x42, 0x42, 0x41, 0x41, 0x40,
        0x40, 0x3f, 0x3f, 0x3e, 0x3e, 0x3d, 0x3d, 0x3c,
        0x3c, 0x3c, 0x3b, 0x3b, 0x3a, 0x3a, 0x39, 0x39,
        0x38, 0x38, 0x37, 0x37, 0x37, 0x36, 0x36, 0x35,
        0x35, 0x34, 0x34, 0x33, 0x33, 0x33, 0x32, 0x32,
        0x31, 0x31, 0x30, 0x30, 0x30, 0x2f, 0x2f, 0x2e,
        0x2e, 0x2e, 0x2d, 0x2d, 0x2c, 0x2c, 0x2c, 0x2b,
        0x2b, 0x2a, 0x2a, 0x2a, 0x29, 0x29, 0x28, 0x28,
        0x28, 0x27, 0x27, 0x26, 0x26, 0x26, 0x25, 0x25,
        0x25, 0x24, 0x24, 0x23, 0x23, 0x23, 0x22, 0x22,
        0x22, 0x21, 0x21, 0x21, 0x20, 0x20, 0x1f, 0x1f,
        0x1f, 0x1e, 0x1e, 0x1e, 0x1d, 0x1d, 0x1d, 0x1c,
        0x1c, 0x1c, 0x1b, 0x1b, 0x1b, 0x1a, 0x1a, 0x1a,
        0x19, 0x19, 0x19, 0x18, 0x18, 0x18, 0x17, 0x17,
        0x17, 0x16, 0x16, 0x16, 0x15, 0x15, 0x15, 0x14,
        0x14, 0x14, 0x14, 0x13, 0x13, 0x13, 0x12, 0x12,
        0x12, 0x11, 0x11, 0x11, 0x10, 0x10, 0x10, 0x10,
        0x0f, 0x0f, 0x0f, 0x0e, 0x0e, 0x0e, 0x0d, 0x0d,
        0x0d, 0x0d, 0x0c, 0x0c, 0x0c, 0x0b, 0x0b, 0x0b,
        0x0b, 0x0a, 0x0a, 0x0a, 0x0a, 0x09, 0x09, 0x09,
        0x08, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07, 0x06,
        0x06, 0x06, 0x06, 0x05, 0x05, 0x05, 0x05, 0x04,
        0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03, 0x02,
        0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00,
        0x00, 0xff, 0xfe, 0xfd, 0xfc, 0xfb, 0xfa, 0xf9,
        0xf8, 0xf7, 0xf6, 0xf5, 0xf4, 0xf3, 0xf3, 0xf2,
        0xf1, 0xf0, 0xef, 0xee, 0xed, 0xec, 0xeb, 0xea,
        0xea, 0xe9, 0xe8, 0xe7, 0xe6, 0xe5, 0xe4, 0xe4,
        0xe3, 0xe2, 0xe1, 0xe0, 0xdf, 0xdf, 0xde, 0xdd,
        0xdc, 0xdb, 0xdb, 0xda, 0xd9, 0xd8, 0xd7, 0xd7,
        0xd6, 0xd5, 0xd4, 0xd4, 0xd3, 0xd2, 0xd1, 0xd1,
        0xd0, 0xcf, 0xce, 0xce, 0xcd, 0xcc, 0xcb, 0xcb,
        0xca, 0xc9, 0xc9, 0xc8, 0xc7, 0xc6, 0xc6, 0xc5,
        0xc4, 0xc4, 0xc3, 0xc2, 0xc2, 0xc1, 0xc0, 0xc0,
        0xbf, 0xbe, 0xbe, 0xbd, 0xbc, 0xbc, 0xbb, 0xba,
        0xba, 0xb9, 0xb8, 0xb8, 0xb7, 0xb7, 0xb6, 0xb5,
        0xb5, 0xb4, 0xb3, 0xb3, 0xb2, 0xb2, 0xb1, 0xb0,
        0xb0, 0xaf, 0xaf, 0xae, 0xad, 0xad, 0xac, 0xac,
        0xab, 0xaa, 0xaa, 0xa9, 0xa9, 0xa8, 0xa8, 0xa7,
        0xa6, 0xa6, 0xa5, 0xa5, 0xa4, 0xa4, 0xa3, 0xa3,
        0xa2, 0xa2, 0xa1, 0xa0, 0xa0, 0x9f, 0x9f, 0x9e,
        0x9e, 0x9d, 0x9d, 0x9c, 0x9c, 0x9b, 0x9b, 0x9a,
        0x9a, 0x99, 0x99, 0x98, 0x98, 0x97, 0x97, 0x96,
        0x96, 0x95, 0x95, 0x94, 0x94, 0x93, 0x93, 0x92,
        0x92, 0x91, 0x91, 0x90, 0x90, 0x8f, 0x8f, 0x8e,
        0x8e, 0x8d, 0x8d, 0x8c, 0x8c, 0x8c, 0x8b, 0x8b,
        0x8a, 0x8a, 0x89, 0x89, 0x88, 0x88, 0x87, 0x87,
        0x87, 0x86, 0x86, 0x85, 0x85, 0x84, 0x84, 0x83,
        0x83, 0x83, 0x82, 0x82, 0x81, 0x81, 0x80, 0x80,
        0x80, 0x7f, 0x7f, 0x7e, 0x7e, 0x7e, 0x7d, 0x7d,
        0x7c, 0x7c, 0x7b, 0x7b, 0x7b, 0x7a, 0x7a, 0x79,
        0x79, 0x79, 0x78, 0x78, 0x77, 0x77, 0x77, 0x76,
        0x76, 0x76, 0x75, 0x75, 0x74, 0x74, 0x74, 0x73,
        0x73, 0x72, 0x72, 0x72, 0x71, 0x71, 0x71, 0x70,
        0x70, 0x6f, 0x6f, 0x6f, 0x6e, 0x6e, 0x6e, 0x6d,
        0x6d, 0x6d, 0x6c, 0x6c, 0x6b, 0x6b, 0x6b, 0x6a
    };

    return (sqrtReciprocalTable[index]);
}

static dword rcpsq_dp(dword op)
{
    dword    result;
    word     sign, exp, result_exp;
    dword    man;
    uword    index;

    if( snan_chk_dp(op)) {
        if( datapath == a_path ) {
            FAUCR.NAN2AU1 |= 1;
            FAUCR.INVALAU1 |= 1;
        } else {
            FAUCR.NAN2AU2 |= 1;
            FAUCR.INVALAU2 |= 1;
        }
        result.high = 0x7fffffff;
        result.low  = 0xffffffff;
        return (result);
    }
    if( qnan_chk_dp(op)) {
        if( datapath == a_path ) {
            FAUCR.NAN2AU1 |= 1;
        } else {
            FAUCR.NAN2AU2 |= 1;
        }
        result.high = 0x7fffffff;
        result.low  = 0xffffffff;
        return (result);
    }

    sign = extract_sign(op.high);
    exp  = extract_exp_dp(op);
    if( exp == 0 ) {
        if( datapath == a_path ) {
            FAUCR.DIV0AU1 |= 1;
            FAUCR.INFOAU1 |= 1;
            if( denorm_chk_dp(op)) {
                FAUCR.INEXAU1 |= 1;
                FAUCR.DEN2AU1 |= 1;
            }
        } else {
            FAUCR.DIV0AU2 |= 1;
            FAUCR.INFOAU2 |= 1;
            if( denorm_chk_dp(op)) {
                FAUCR.INEXAU2 |= 1;
                FAUCR.DEN2AU2 |= 1;
            }
        }
        result.high = sign ? 0xfff00000 : 0x7ff00000;
        result.low  = 0;
        return (result);
    }
    if( sign ) {
        if( datapath == a_path ) {
            FAUCR.INVALAU1 |= 1;
        } else {
            FAUCR.INVALAU2 |= 1;
        }
        result.high = 0x7fffffff;
        result.low  = 0xffffffff;
        return (result);
    }
    if( inf_chk_dp(op)) {
        result.high = 0;
        result.low  = 0;
        return (result);
    }

    index = (op.high >> 12) & 0x000001ff;
    result_exp = exp;
    if( exp & 1 ) {
        result_exp++;
    }
    result_exp >>= 1;
    result_exp += 511;
    result_exp = 0x7fd - result_exp;
    result_exp += (index == 256);
    result.high = rcpsq(index) << 12;
    result.high |= (result_exp << 20) & 0x7ff00000;
    result.high |= sign << 31;
    result.low = 0;
    if( !(exp & 1) || (op.high & 0x000fffff) || op.low ) {
        if( datapath == a_path ) {
            FAUCR.INEXAU1 |= 1;
        } else { FAUCR.INEXAU2 |= 1;
        }
    }
    return (result);
}

static word rcpsq_sp(word op)
{
    word     sign, exp, man;
    uword    index;
    word     result, result_exp;

    if( snan_chk_sp(op)) {
        if( datapath == a_path ) {
            FAUCR.NAN2AU1 |= 1;
            FAUCR.INVALAU1 |= 1;
        } else {
            FAUCR.NAN2AU2 |= 1;
            FAUCR.INVALAU2 |= 1;
        }
        return (0x7fffffff);
    }
    if( qnan_chk_sp(op)) {
        if( datapath == a_path ) {
            FAUCR.NAN2AU1 |= 1;
        } else {
            FAUCR.NAN2AU2 |= 1;
        }
        return (0x7fffffff);
    }

    sign = extract_sign(op);
    exp  = extract_exp_sp(op);
    if( exp == 0 ) {
        if( datapath == a_path ) {
            FAUCR.DIV0AU1 |= 1;
            FAUCR.INFOAU1 |= 1;
            if( denorm_chk_sp(op)) {
                FAUCR.INEXAU1 |= 1;
                FAUCR.DEN2AU1 |= 1;
            }
        } else {
            FAUCR.DIV0AU2 |= 1;
            FAUCR.INFOAU2 |= 1;
            if( denorm_chk_sp(op)) {
                FAUCR.INEXAU2 |= 1;
                FAUCR.DEN2AU2 |= 1;
            }
        }
        return (sign ? 0xff800000 : 0x7f800000);
    }
    if( sign ) {
        if( datapath == a_path ) {
            FAUCR.INVALAU1 |= 1;
        } else {
            FAUCR.INVALAU2 |= 1;
        }
        return (0x7fffffff);
    }
    if( inf_chk_sp(op)) {
        return (0);
    }

    index = (op >> 15) & 0x000001ff;
    result_exp = exp;
    if( exp & 1 ) {
        result_exp++;
    }
    result_exp >>= 1;
    result_exp += 63;
    result_exp = 0xfd - result_exp;
    result_exp += (index == 256);
    result = rcpsq(index) << 15;
    result |= (sign << 31) | (result_exp << 23);
    if( !(exp & 1) || (op & 0x007fffff)) {
        if( datapath == a_path ) {
            FAUCR.INEXAU1 |= 1;
        } else { FAUCR.INEXAU2 |= 1;
        }
    }
    return (result);
}

static dword round_ofuf_chk_dp(word sign, word exp, dword man, word round, word sticky, word adder, int cr_wr_delay)
{
    word     round_mode;
    dword    result;
    word     overflow;
    word     underflow;
    word     infinity;
    word     inexact;

    if( adder ) {
        round_mode = (datapath == a_path) ? FADCR.ROUNDINGMODEADD1 : FADCR.ROUNDINGMODEADD2;
    } else { round_mode = (datapath == a_path) ? FMCR.ROUNDINGMODEMPY1 : FMCR.ROUNDINGMODEMPY2;
    }

    inexact = round || sticky;
    overflow = 0;
    underflow = 0;
    infinity = 0;

    switch( round_mode & 0x3 ) { // Catapult needs the redundant "& 0x3" to work
        case 0 : /* round to nearest */
            if( round && (sticky || (man.low & 1))) {
                result = increment_dp(man);
                if( result.high & 0x00200000 ) {
                    result.high >>= 1;
                    exp++;
                }
            } else {
                result.high = man.high;
                result.low  = man.low;
            }

            if( exp > 0x000007fe ) { /* overflow */
                result.high = 0;
                result.low  = 0;
                exp = 0x000007ff;
                overflow = 1;
                infinity = 1;
                inexact = 1;
            }
            if( exp < 1 ) { /* underflow */
                result.high = 0;
                result.low  = 0;
                exp = 0;
                underflow = 1;
                inexact = 1;
            }
            break;

        case 1 : /* round to zero */
            result.high = man.high;
            result.low  = man.low;
            if( exp > 0x000007fe ) { /* overflow */
                result.high = 0x000fffff;
                result.low  = 0xffffffff;
                exp = 0x000007fe;
                overflow = 1;
                inexact = 1;
            }
            if( exp < 1 ) { /* underflow */
                result.high = 0;
                result.low  = 0;
                exp = 0;
                underflow = 1;
                inexact = 1;
            }
            break;

        case 2 : /* round to +infinity */
            if( !sign && (round || sticky)) {
                result = increment_dp(man);
                if( result.high & 0x00200000 ) {
                    result.high >>= 1;
                    exp++;
                }
            } else {
                result.high = man.high;
                result.low  = man.low;
            }

            if( exp > 0x000007fe ) { /* overflow */
                if( sign ) {
                    result.high = 0x000fffff;
                    result.low  = 0xffffffff;
                    exp = 0x000007fe;
                } else {
                    result.high = 0;
                    result.low  = 0;
                    exp = 0x000007ff;
                    infinity = 1;
                }
                overflow = 1;
                inexact = 1;
            }
            if( exp < 1 ) { /* underflow */
                if( sign ) {
                    result.high = 0;
                    result.low  = 0;
                    exp = 0;
                } else {
                    result.high = 0;
                    result.low  = 0;
                    exp = 1;
                }
                underflow = 1;
                inexact = 1;
            }
            break;

        case 3 : /* round to -infinity */
            if( sign && (round || sticky)) {
                result = increment_dp(man);
                if( result.high & 0x00200000 ) {
                    result.high >>= 1;
                    exp++;
                }
            } else {
                result.high = man.high;
                result.low  = man.low;
            }

            if( exp > 0x000007fe ) { /* overflow */
                if( sign ) {
                    result.high = 0;
                    result.low  = 0;
                    exp = 0x000007ff;
                    infinity = 1;
                } else {
                    result.high = 0x000fffff;
                    result.low  = 0xffffffff;
                    exp = 0x000007fe;
                }
                overflow = 1;
                inexact = 1;
            }
            if( exp < 1 ) { /* underflow */
                if( sign ) {
                    result.high = 0;
                    result.low  = 0;
                    exp = 1;
                } else {
                    result.high = 0;
                    result.low  = 0;
                    exp = 0;
                }
                underflow = 1;
                inexact = 1;
            }
            break;
    }

    if( adder ) {
        if( datapath == a_path ) {
            FADCR.UNDERADD1 |= underflow; // cr_wr_delay delay slots
            FADCR.INEXADD1  |= inexact; // cr_wr_delay delay slots
            FADCR.OVERADD1  |= overflow; // cr_wr_delay delay slots
            FADCR.INFOADD1  |= infinity; // cr_wr_delay delay slots
        } else {
            FADCR.UNDERADD2 |= underflow; // cr_wr_delay delay slots
            FADCR.INEXADD2  |= inexact; // cr_wr_delay delay slots
            FADCR.OVERADD2  |= overflow; // cr_wr_delay delay slots
            FADCR.INFOADD2  |= infinity; // cr_wr_delay delay slots
        }
    } else {
        if( datapath == a_path ) {
            FMCR.UNDERMPY1 |= underflow; // cr_wr_delay delay slots
            FMCR.INEXMPY1  |= inexact; // cr_wr_delay delay slots
            FMCR.OVERMPY1  |= overflow; // cr_wr_delay delay slots
            FMCR.INFOMPY1  |= infinity; // cr_wr_delay delay slots
        } else {
            FMCR.UNDERMPY2 |= underflow; // cr_wr_delay delay slots
            FMCR.INEXMPY2  |= inexact; // cr_wr_delay delay slots
            FMCR.OVERMPY2  |= overflow; // cr_wr_delay delay slots
            FMCR.INFOMPY2  |= infinity; // cr_wr_delay delay slots
        }
    }

    result.high &= 0x000fffff;
    result.high |= (exp << 20) & 0x7ff00000;
    result.high |= sign << 31;
    return (result);
}

static dword rshift_dp(dword op, word shift)
{
    dword    result;

    shift %= 64;
    if( shift > 31 ) {
        result.low = op.high >> (shift % 32);
        result.high = 0;
    } else {
        result.low  = shift ? (op.high << 32 - shift) | (((uword) op.low) >> shift) : op.low;
        result.high = ((uword) op.high) >> shift;
    }
    return (result);
}

static word snan_chk_dp(dword op)
{

    //return( ( (op.high & 0x7ff80000) == 0x7ff00000 ) &&
    //        ( (op.high & 0x0007ffff) || op.low ) ) ;

    if(((op.high & 0x7ff80000) == 0x7ff00000) &&
       ((op.high & 0x0007ffff) || op.low)) {
        return (1);
    } else {
        return (0);
    }
}

#endif /* #ifdef TMS320C67X */

#if defined(TMS320C66X) || defined(TMS320C67X)
static word carry_out(word op1, word op2)
{
    word    a, b, sum;

    a = op1 & 0x80000000;
    b = op2 & 0x80000000;
    sum = op1 + op2;

    //return( ( a && b ) || ( ( a || b ) && !( sum & 0x80000000 ) ) ) ;

    //  if ( ( a && b ) || (( a || b ) && !( sum & 0x80000000 )) ) {
    //   return 1 ;
    //  } else {
    //   return 0 ;
    //  }
    // Nested if-else statement version of the above dense if-else statement for C-coverage
    if( a && b ) {
        return (1);
    } else if(((a || b) && !(sum & 0x80000000))) {
        return (1);
    } else {
        return (0);
    }
}

static word denorm_chk_sp(word op)
{

    //return( !(op & 0x7f800000) &&
    //         (op & 0x007fffff) ) ;

    if( !(op & 0x7f800000) && (op & 0x007fffff)) {
        return (1);
    } else {
        return (0);
    }
}

static word excp_chk_mpy_sp(word op1, word op2)
{
    word    exp1, exp2;

    if( snan_chk_sp(op1)) {
        if( datapath == a_path ) {
            FMCR.INVALMPY1 |= 1;                            // 3 delay slots
            FMCR.NAN1MPY1 |= 1;                             // 3 delay slots
            FMCR.NAN2MPY1 |= (snan_chk_sp(op2) || qnan_chk_sp(op2));    // 3 delay slots
            FMCR.DEN2MPY1 |= denorm_chk_sp(op2);                // 3 delay slots
        } else {
            FMCR.INVALMPY2 |= 1;                            // 3 delay slots
            FMCR.NAN1MPY2 |= 1;                             // 3 delay slots
            FMCR.NAN2MPY2 |= (snan_chk_sp(op2) || qnan_chk_sp(op2));    // 3 delay slots
            FMCR.DEN2MPY2 |= denorm_chk_sp(op2);                // 3 delay slots
        }
        return (1);
    }
    if( snan_chk_sp(op2)) {
        if( datapath == a_path ) {
            FMCR.INVALMPY1 |= 1;            // 3 delay slots
            FMCR.NAN1MPY1 |= qnan_chk_sp(op1);  // 3 delay slots
            FMCR.NAN2MPY1 |= 1;             // 3 delay slots
            FMCR.DEN1MPY1 |= denorm_chk_sp(op1); // 3 delay slots
        } else {
            FMCR.INVALMPY2 |= 1;            // 3 delay slots
            FMCR.NAN1MPY2 |= qnan_chk_sp(op1);  // 3 delay slots
            FMCR.NAN2MPY2 |= 1;             // 3 delay slots
            FMCR.DEN1MPY2 |= denorm_chk_sp(op1); // 3 delay slots
        }
        return (1);
    }
    if( qnan_chk_sp(op1)) {
        if( datapath == a_path ) {
            FMCR.NAN1MPY1 |= 1;             // 3 delay slots
            FMCR.NAN2MPY1 |= qnan_chk_sp(op2);  // 3 delay slots
            FMCR.DEN2MPY1 |= denorm_chk_sp(op2); // 3 delay slots
        } else {
            FMCR.NAN1MPY2 |= 1;             // 3 delay slots
            FMCR.NAN2MPY2 |= qnan_chk_sp(op2);  // 3 delay slots
            FMCR.DEN2MPY2 |= denorm_chk_sp(op2); // 3 delay slots
        }
        return (1);
    }
    if( qnan_chk_sp(op2)) {
        if( datapath == a_path ) {
            FMCR.NAN2MPY1 |= 1;             // 3 delay slots
            FMCR.DEN1MPY1 |= denorm_chk_sp(op1); // 3 delay slots
        } else {
            FMCR.NAN2MPY2 |= 1;             // 3 delay slots
            FMCR.DEN1MPY2 |= denorm_chk_sp(op1); // 3 delay slots
        }
        return (1);
    }

    exp1 = extract_exp_sp(op1);
    exp2 = extract_exp_sp(op2);

    if( denorm_chk_sp(op1)) {
        if( datapath == a_path ) {
            FMCR.DEN1MPY1 |= 1;                         // 3 delay slots
            FMCR.INEXMPY1 |= (op2 & 0x7fffffff) && !inf_chk_sp(op2);    // 3 delay slots
        } else {
            FMCR.DEN1MPY2 |= 1;                         // 3 delay slots
            FMCR.INEXMPY2 |= (op2 & 0x7fffffff) && !inf_chk_sp(op2);    // 3 delay slots
        }
    }
    if( denorm_chk_sp(op2)) {
        if( datapath == a_path ) {
            FMCR.DEN2MPY1 |= 1;                         // 3 delay slots
            FMCR.INEXMPY1 |= (op1 & 0x7fffffff) && !inf_chk_sp(op1);    // 3 delay slots
        } else {
            FMCR.DEN2MPY2 |= 1;                         // 3 delay slots
            FMCR.INEXMPY2 |= (op1 & 0x7fffffff) && !inf_chk_sp(op1);    // 3 delay slots
        }
    }

    if( inf_chk_sp(op1)) {
        if( !exp2 ) {
            if( datapath == a_path ) {
                FMCR.INVALMPY1 |= 1; // 3 delay slots
            } else {
                FMCR.INVALMPY2 |= 1; // 3 delay slots
            }
            return (1);
        } else {
            if( datapath == a_path ) {
                FMCR.INFOMPY1 |= 1; // 3 delay slots
            } else {
                FMCR.INFOMPY2 |= 1; // 3 delay slots
            }
            return (2);
        }
    }
    if( inf_chk_sp(op2)) {
        if( !exp1 ) {
            if( datapath == a_path ) {
                FMCR.INVALMPY1 |= 1; // 3 delay slots
            } else {
                FMCR.INVALMPY2 |= 1; // 3 delay slots
            }
            return (1);
        } else {
            if( datapath == a_path ) {
                FMCR.INFOMPY1 |= 1; // 3 delay slots
            } else {
                FMCR.INFOMPY2 |= 1; // 3 delay slots
            }
            return (2);
        }
    }
    return (0);
}

static word extract_exp_sp(word op)
{

    return ((op & 0x7f800000) >> 23);
}

static word extract_man_sp(word op)
{

    return ((op & 0x007fffff) | 0x00800000);
}

static word extract_sign(word op)
{

    if( op & 0x80000000 ) {
        return (1);
    } else { return (0);
    }
}

static word inf_chk_sp(word op)
{

    //return( ( (op & 0x7f800000) == 0x7f800000 ) &&
    //        !(op & 0x007fffff) ) ;

    if(((op & 0x7f800000) == 0x7f800000) &&
       !(op & 0x007fffff)) {
        return (1);
    } else {
        return (0);
    }
}

static dword mpyid(word op1, word op2)
{
    word     pp1, pp2;
    dword    result;

    result.low = (op1 & 0x0000ffff) * (op2 & 0x0000ffff);
    result.high = (((signed) op1) >> 16) * (((signed) op2) >> 16);
    pp1 = (op1 & 0x0000ffff) * (((signed) op2) >> 16);
    pp2 = (op2 & 0x0000ffff) * (((signed) op1) >> 16);
    result.high += carry_out(result.low, pp1 << 16);
    result.low += pp1 << 16;
    result.high += ((signed) pp1) >> 16;
    result.high += carry_out(result.low, pp2 << 16);
    result.low += pp2 << 16;
    result.high += ((signed) pp2) >> 16;
    return (result);
}

static word qnan_chk_sp(word op)
{

    //return( (op & 0x7fc00000) == 0x7fc00000 ) ;

    if((op & 0x7fc00000) == 0x7fc00000 ) {
        return (1);
    } else {
        return (0);
    }
}

static word round_int(word op, word sign, word round, word sticky, int cr_wr_delay)
{
    word    round_mode;
    word    result;
    word    check;

    if( round || sticky ) {
        if( datapath == a_path ) {
            FADCR.INEXADD1 |= 1; // cr_wr_delay delay slots
        } else {
            FADCR.INEXADD2 |= 1; // cr_wr_delay delay slots
        }
    }
    result = op;
    round_mode = (datapath == a_path) ? FADCR.ROUNDINGMODEADD1 : FADCR.ROUNDINGMODEADD2;
    if( round_mode == 0 ) {
        if( round && (sticky || (result & 1))) {
            check = 0;
            if((result == 0x7fffffff) && !sign ) {
                check = 1;
            }
            if((result == 0x80000000) && sign ) {
                check = 1;
            }
            if( check ) {
                if( datapath == a_path ) {
                    FADCR.OVERADD1 |= 1; // cr_wr_delay delay slots
                } else {
                    FADCR.OVERADD2 |= 1; // cr_wr_delay delay slots
                }
            } else { result++;
            }
        }
    } else if( round_mode == 2 ) {
        if( !sign && (round || sticky)) {
            if( result == 0x7fffffff ) {
                if( datapath == a_path ) {
                    FADCR.OVERADD1 |= 1; // cr_wr_delay delay slots
                } else {
                    FADCR.OVERADD2 |= 1; // cr_wr_delay delay slots
                }
            } else { result++;
            }
        }
    } else if( round_mode == 3 ) {
        if( sign && (round || sticky)) {
            if( result == 0x80000000 ) {
                if( datapath == a_path ) {
                    FADCR.OVERADD1 |= 1; // cr_wr_delay delay slots
                } else {
                    FADCR.OVERADD2 |= 1; // cr_wr_delay delay slots
                }
            } else { result++;
            }
        }
    }
    if( sign ) {
        result = -result;
    }
    return (result);

}

static word snan_chk_sp(word op)
{

    //return( ( (op & 0x7fc00000) == 0x7f800000 ) &&
    //        ( op & 0x003fffff ) ) ;

    if(((op & 0x7fc00000) == 0x7f800000) && (op & 0x003fffff)) {
        return (1);
    } else {
        return (0);
    }
}

static word spint(word op, int cr_wr_delay)
{
    word    sign;
    word    exp;
    word    man;
    word    round;
    word    sticky;
    word    result;
    word    check;

    sign = extract_sign(op);
    if( snan_chk_sp(op) || qnan_chk_sp(op)) {
        if( datapath == a_path ) {
            FADCR.INVALADD1 |= 1; // cr_wr_delay delay slots
            FADCR.NAN2ADD1 |= 1; // cr_wr_delay delay slots
        } else {
            FADCR.INVALADD2 |= 1; // cr_wr_delay delay slots
            FADCR.NAN2ADD2 |= 1; // cr_wr_delay delay slots
        }
        return (sign ? 0x80000000 : 0x7fffffff);
    }

    exp = extract_exp_sp(op) - 127;
    man = extract_man_sp(op);
    check = 0;
    if( inf_chk_sp(op)) {
        check = 1;
    }
    if( exp > 31 ) {
        check = 1;
    }
    if((exp == 31) && !sign ) {
        check = 1;
    }
    if((exp == 31) && sign && (op & 0x007fffff)) {
        check = 1;
    }
    if( check ) {
        if( datapath == a_path ) {
            FADCR.INEXADD1 |= 1; // cr_wr_delay delay slots
            FADCR.OVERADD1 |= 1; // cr_wr_delay delay slots
        } else {
            FADCR.INEXADD2 |= 1; // cr_wr_delay delay slots
            FADCR.OVERADD2 |= 1; // cr_wr_delay delay slots
        }
        return (sign ? 0x80000000 : 0x7fffffff);
    }

    if( denorm_chk_sp(op)) {
        if( datapath == a_path ) {
            FADCR.INEXADD1 |= 1; // cr_wr_delay delay slots
            FADCR.DEN2ADD1 |= 1; // cr_wr_delay delay slots
        } else {
            FADCR.INEXADD2 |= 1; // cr_wr_delay delay slots
            FADCR.DEN2ADD2 |= 1; // cr_wr_delay delay slots
        }
        return (0);
    }

    if( exp == -127 ) {
        return (0);
    }

    if( exp < 0 ) {
        result = 0;
        round = (exp == -1);
        sticky = (exp == -1) ? (man & 0x007fffff) : 1;
    } else if( exp >= 23 ) {
        result = man << (exp - 23);
        round = 0;
        sticky = 0;
    } else {
        result = man >> (23 - exp);
        man <<= exp + 9;
        round = (man & 0x80000000) ? 1 : 0;
        sticky = (man & 0x7fffffff) ? 1 : 0;
    }

    result = round_int(result, sign, round, sticky, cr_wr_delay);
    return (result);
}

#endif /* #if defined(TMS320C66X) || defined(TMS320C67X) */


// Intrinsic function definitions
#ifdef TMS320C66X
__x128_t _ccmatmpy(int64_ll arg_xdwop1, __x128_t arg_qwop2)
{
    dword       xdwop1;
    qword       qwop2;
    qword       qwdst;
    __x128_t    result;

    INT64_LL_TO_DWORD(arg_xdwop1, xdwop1);
    __X128_T_TO_QWORD(arg_qwop2, qwop2);

    qwdst = ccmatmpy(xdwop1, qwop2); // 3 delay slots

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

int64_ll _ccmatmpyr1(int64_ll arg_xdwop1, __x128_t arg_qwop2)
{
    dword       xdwop1;
    qword       qwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_xdwop1, xdwop1);
    __X128_T_TO_QWORD(arg_qwop2, qwop2);

    dwdst = ccmatmpyr1(xdwop1, qwop2); // 3 delay slots

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _ccmpy32r1(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = ccmpy32r1(dwop1, xdwop2); // 3 delay slots

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

__x128_t _cmatmpy(int64_ll arg_xdwop1, __x128_t arg_qwop2)
{
    dword       xdwop1;
    qword       qwop2;
    qword       qwdst;
    __x128_t    result;

    INT64_LL_TO_DWORD(arg_xdwop1, xdwop1);
    __X128_T_TO_QWORD(arg_qwop2, qwop2);

    qwdst = cmatmpy(xdwop1, qwop2); // 3 delay slots

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

int64_ll _cmatmpyr1(int64_ll arg_xdwop1, __x128_t arg_qwop2)
{
    dword       xdwop1;
    qword       qwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_xdwop1, xdwop1);
    __X128_T_TO_QWORD(arg_qwop2, qwop2);

    dwdst = cmatmpyr1(xdwop1, qwop2); // 3 delay slots

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _cmpy32r1(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = cmpy32r1(dwop1, xdwop2); // 3 delay slots

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

__x128_t _cmpysp(__float2_t arg_dwop1, __float2_t arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    qword       qwdst;
    __x128_t    result;

    __FLOAT2_T_TO_DWORD(arg_dwop1, dwop1);
    __FLOAT2_T_TO_DWORD(arg_xdwop2, xdwop2);

    qwdst.word0 = mpy_sp(dwop1.low,  xdwop2.high);    // 3 delay slots
    qwdst.word1 = mpy_sp(dwop1.low,  xdwop2.low) ^ 0x80000000;     // 3 delay slots
    qwdst.word2 = mpy_sp(dwop1.high, xdwop2.low);    // 3 delay slots
    qwdst.word3 = mpy_sp(dwop1.high, xdwop2.high);    // 3 delay slots

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

int32 _crot270(int32 arg_xop)
{
    uword    xop;
    uword    dst;
    int32    result;

    INT32_TO_UWORD(arg_xop, xop);

    dst = complex_rot270(xop);

    UWORD_TO_INT32(dst, result);
    return (result);
}

int32 _crot90(int32 arg_xop)
{
    uword    xop;
    uword    dst;
    int32    result;

    INT32_TO_UWORD(arg_xop, xop);

    dst = complex_rot90(xop);

    UWORD_TO_INT32(dst, result);
    return (result);
}

int64_ll _dadd(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dadd(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dadd2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dadd2(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dadd_c(int32 arg_scst5, int64_ll arg_xdwop2)
{
    uword       scst5;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT32_TO_UWORD(arg_scst5, scst5);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dadd_c(scst5, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

__float2_t _daddsp(__float2_t arg_dwop1, __float2_t arg_xdwop2)
{
    dword         dwop1;
    dword         xdwop2;
    dword         dwdst;
    __float2_t    result;

    __FLOAT2_T_TO_DWORD(arg_dwop1, dwop1);
    __FLOAT2_T_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = add_sp(dwop1.low, xdwop2.low, 2);      // 2 delay slots
    dwdst.high = add_sp(dwop1.high, xdwop2.high, 2);    // 2 delay slots

    DWORD_TO___FLOAT2_T(dwdst, result);
    return (result);
}

int64_ll _dapys2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dapys2(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _davg2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = avg2(dwop1.low, xdwop2.low);   // 1 delay slot
    dwdst.high = avg2(dwop1.high, xdwop2.high); // 1 delay slot

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _davgnr2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = avgnr2(dwop1.low, xdwop2.low);   // 1 delay slot
    dwdst.high = avgnr2(dwop1.high, xdwop2.high); // 1 delay slot

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _davgnru4(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = avgnru4(dwop1.low, xdwop2.low);  // 1 delay slot
    dwdst.high = avgnru4(dwop1.high, xdwop2.high); // 1 delay slot

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _davgu4(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = avgu4(dwop1.low, xdwop2.low);  // 1 delay slot
    dwdst.high = avgu4(dwop1.high, xdwop2.high); // 1 delay slot

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

__x128_t _dccmpy(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    qword       qwdst;
    __x128_t    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    qwdst = dccmpy(dwop1, xdwop2); // 3 delay slots

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

int64_ll _dccmpyr1(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dccmpyr1(dwop1, xdwop2); // 3 delay slots

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

uint32 _dcmpeq2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword     dwop1;
    dword     xdwop2;
    uword     dst;
    uint32    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dst = cmpeq2(dwop1.high, xdwop2.high) << 2 | cmpeq2(dwop1.low, xdwop2.low);

    UWORD_TO_UINT32(dst, result);
    return (result);
}

uint32 _dcmpeq4(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword     dwop1;
    dword     xdwop2;
    uword     dst;
    uint32    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dst = cmpeq4(dwop1.high, xdwop2.high) << 4 | cmpeq4(dwop1.low, xdwop2.low);

    UWORD_TO_UINT32(dst, result);
    return (result);
}

uint32 _dcmpgt2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword     dwop1;
    dword     xdwop2;
    uword     dst;
    uint32    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dst = cmpgt2(dwop1.high, xdwop2.high) << 2 | cmpgt2(dwop1.low, xdwop2.low);

    UWORD_TO_UINT32(dst, result);
    return (result);
}

uint32 _dcmpgtu4(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword     dwop1;
    dword     xdwop2;
    uword     dst;
    uint32    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dst = ((uword) (0x000000ff & dwop1.low) > (uword) (0x000000ff & xdwop2.low) ? 0x01 : 0) |
          ((uword) (0x0000ff00 & dwop1.low) > (uword) (0x0000ff00 & xdwop2.low) ? 0x02 : 0) |
          ((uword) (0x00ff0000 & dwop1.low) > (uword) (0x00ff0000 & xdwop2.low) ? 0x04 : 0) |
          ((uword) (0xff000000 & dwop1.low) > (uword) (0xff000000 & xdwop2.low) ? 0x08 : 0) |
          ((uword) (0x000000ff & dwop1.high) > (uword) (0x000000ff & xdwop2.high) ? 0x10 : 0) |
          ((uword) (0x0000ff00 & dwop1.high) > (uword) (0x0000ff00 & xdwop2.high) ? 0x20 : 0) |
          ((uword) (0x00ff0000 & dwop1.high) > (uword) (0x00ff0000 & xdwop2.high) ? 0x40 : 0) |
          ((uword) (0xff000000 & dwop1.high) > (uword) (0xff000000 & xdwop2.high) ? 0x80 : 0);

    UWORD_TO_UINT32(dst, result);
    return (result);
}

__x128_t _dcmpy(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    qword       qwdst;
    __x128_t    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    qwdst = dcmpy(dwop1, xdwop2); // 3 delay slots

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

int64_ll _dcmpyr1(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dcmpyr1(dwop1, xdwop2); // 3 delay slots

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dcrot270(int64_ll arg_xdwop)
{
    dword       xdwop;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_xdwop, xdwop);

    dwdst = dcomplex_rot270(xdwop);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dcrot90(int64_ll arg_xdwop)
{
    dword       xdwop;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_xdwop, xdwop);

    dwdst = dcomplex_rot90(xdwop);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _ddotp4h(__x128_t arg_qwop1, __x128_t arg_qwop2)
{
    qword       qwop1;
    qword       qwop2;
    dword       dwdst;
    int64_ll    result;

    __X128_T_TO_QWORD(arg_qwop1, qwop1);
    __X128_T_TO_QWORD(arg_qwop2, qwop2);

    dwdst = ddotp4h(qwop1, qwop2);   // 3 delay slots

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _ddotpsu4h(__x128_t arg_qwop1, __x128_t arg_qwop2)
{
    qword       qwop1;
    qword       qwop2;
    dword       dwdst;
    int64_ll    result;

    __X128_T_TO_QWORD(arg_qwop1, qwop1);
    __X128_T_TO_QWORD(arg_qwop2, qwop2);

    dwdst = ddotpsu4h(qwop1, qwop2);   // 3 delay slots

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

__float2_t _dinthsp(uint32 arg_xop)
{
    uword         xop;
    dword         dwdst;
    __float2_t    result;

    UINT32_TO_UWORD(arg_xop, xop);

    dwdst.low  = intsp(slow16(xop), 2);    // 2 delay slot
    dwdst.high = intsp(shigh16(xop), 2);    // 2 delay slot

    DWORD_TO___FLOAT2_T(dwdst, result);
    return (result);
}

__float2_t _dinthspu(uint32 arg_xop)
{
    uword         xop;
    dword         dwdst;
    __float2_t    result;

    UINT32_TO_UWORD(arg_xop, xop);

    dwdst.low  = intsp(ulow16(xop), 2);    // 2 delay slot
    dwdst.high = intsp(uhigh16(xop), 2);    // 2 delay slot

    DWORD_TO___FLOAT2_T(dwdst, result);
    return (result);
}

__float2_t _dintsp(int64_ll arg_xdwop)
{
    dword         xdwop;
    dword         dwdst;
    __float2_t    result;

    INT64_LL_TO_DWORD(arg_xdwop, xdwop);

    dwdst.low  = intsp(xdwop.low,  2);    // 2 delay slot
    dwdst.high = intsp(xdwop.high, 2);    // 2 delay slot

    DWORD_TO___FLOAT2_T(dwdst, result);
    return (result);
}

__float2_t _dintspu(int64_ll arg_xdwop)
{
    dword         xdwop;
    dword         dwdst;
    __float2_t    result;

    INT64_LL_TO_DWORD(arg_xdwop, xdwop);

    dwdst.low  = intspu(xdwop.low,  2);    // 2 delay slot
    dwdst.high = intspu(xdwop.high, 2);    // 2 delay slot

    DWORD_TO___FLOAT2_T(dwdst, result);
    return (result);
}

int64_ll _dmax2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = max2(dwop1.low, xdwop2.low);
    dwdst.high = max2(dwop1.high, xdwop2.high);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dmaxu4(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = max4(dwop1.low, xdwop2.low);
    dwdst.high = max4(dwop1.high, xdwop2.high);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dmin2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = min2(dwop1.low, xdwop2.low);
    dwdst.high = min2(dwop1.high, xdwop2.high);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dminu4(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = min4(dwop1.low, xdwop2.low);
    dwdst.high = min4(dwop1.high, xdwop2.high);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

__x128_t _dmpy2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    qword       qwdst;
    __x128_t    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    qwdst.word0 = slow16(dwop1.low)   * slow16(xdwop2.low); // 3 delay slot
    qwdst.word1 = shigh16(dwop1.low)  * shigh16(xdwop2.low); // 3 delay slot
    qwdst.word2 = slow16(dwop1.high)  * slow16(xdwop2.high); // 3 delay slot
    qwdst.word3 = shigh16(dwop1.high) * shigh16(xdwop2.high); // 3 delay slot

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

__float2_t _dmpysp(__float2_t arg_dwop1, __float2_t arg_xdwop2)
{
    dword         dwop1;
    dword         xdwop2;
    dword         dwdst;
    __float2_t    result;

    __FLOAT2_T_TO_DWORD(arg_dwop1, dwop1);
    __FLOAT2_T_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = mpy_sp(dwop1.low, xdwop2.low);     // 3 delay slots
    dwdst.high = mpy_sp(dwop1.high, xdwop2.high);   // 3 delay slots

    DWORD_TO___FLOAT2_T(dwdst, result);
    return (result);
}

__x128_t _dmpysu4(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    qword       qwdst;
    __x128_t    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    qwdst.word0 =  (sbyte0(dwop1.low) * ubyte0(xdwop2.low)) & 0xffff |
                  ((sbyte1(dwop1.low) * ubyte1(xdwop2.low)) << 16);  // 3 delay slot
    qwdst.word1 =  (sbyte2(dwop1.low) * ubyte2(xdwop2.low)) & 0xffff |
                  ((sbyte3(dwop1.low) * ubyte3(xdwop2.low)) << 16);  // 3 delay slot
    qwdst.word2 =  (sbyte0(dwop1.high) * ubyte0(xdwop2.high)) & 0xffff |
                  ((sbyte1(dwop1.high) * ubyte1(xdwop2.high)) << 16); // 3 delay slot
    qwdst.word3 =  (sbyte2(dwop1.high) * ubyte2(xdwop2.high)) & 0xffff |
                  ((sbyte3(dwop1.high) * ubyte3(xdwop2.high)) << 16); // 3 delay slot

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

__x128_t _dmpyu2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    qword       qwdst;
    __x128_t    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    qwdst.word0 = ulow16(dwop1.low)   * ulow16(xdwop2.low); // 3 delay slot
    qwdst.word1 = uhigh16(dwop1.low)  * uhigh16(xdwop2.low); // 3 delay slot
    qwdst.word2 = ulow16(dwop1.high)  * ulow16(xdwop2.high); // 3 delay slot
    qwdst.word3 = uhigh16(dwop1.high) * uhigh16(xdwop2.high); // 3 delay slot

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

__x128_t _dmpyu4(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    qword       qwdst;
    __x128_t    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    qwdst.word0 =  (ubyte0(dwop1.low) * ubyte0(xdwop2.low)) & 0xffff |
                  ((ubyte1(dwop1.low) * ubyte1(xdwop2.low)) << 16);  // 3 delay slot
    qwdst.word1 =  (ubyte2(dwop1.low) * ubyte2(xdwop2.low)) & 0xffff |
                  ((ubyte3(dwop1.low) * ubyte3(xdwop2.low)) << 16);  // 3 delay slot
    qwdst.word2 =  (ubyte0(dwop1.high) * ubyte0(xdwop2.high)) & 0xffff |
                  ((ubyte1(dwop1.high) * ubyte1(xdwop2.high)) << 16); // 3 delay slot
    qwdst.word3 =  (ubyte2(dwop1.high) * ubyte2(xdwop2.high)) & 0xffff |
                  ((ubyte3(dwop1.high) * ubyte3(xdwop2.high)) << 16); // 3 delay slot

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

int64_ll _dmvd(int32 arg_op1, int32 arg_xop2)
{
    uword       op1;
    uword       xop2;
    dword       dwdst;
    int64_ll    result;

    INT32_TO_UWORD(arg_op1, op1);
    INT32_TO_UWORD(arg_xop2, xop2);

    dwdst.high = op1;    // 3 delay slots ;
    dwdst.low  = xop2;   // 3 delay slots ;

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int32 _dotp4h(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword    dwop1;
    dword    xdwop2;
    uword    dst;
    int32    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dst   = dotp4h(dwop1, xdwop2);   // 3 delay slots

    UWORD_TO_INT32(dst, result);
    return (result);
}

int64_ll _dotp4hll(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dotp4h_l(dwop1, xdwop2);   // 3 delay slots

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int32 _dotpsu4h(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword    dwop1;
    dword    xdwop2;
    uword    dst;
    int32    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dst   = dotpsu4h(dwop1, xdwop2);   // 3 delay slots

    UWORD_TO_INT32(dst, result);
    return (result);
}

int64_ll _dotpsu4hll(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dotpsu4h_l(dwop1, xdwop2);   // 3 delay slots

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dpackh2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dpackh2(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dpackh4(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = (dwop1.low        & 0xff000000) | (dwop1.low << 8 & 0x00ff0000) |
                 (xdwop2.low  >> 16 & 0x0000ff00) | (xdwop2.low  >> 8 & 0x000000ff);
    dwdst.high = (dwop1.high       & 0xff000000) | (dwop1.high << 8 & 0x00ff0000) |
                 (xdwop2.high >> 16 & 0x0000ff00) | (xdwop2.high >> 8 & 0x000000ff);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dpackhl2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dpackhl2(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dpackl2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dpackl2(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dpackl4(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = (dwop1.low << 8 & 0xff000000) | (dwop1.low << 16 & 0x00ff0000) |
                 (xdwop2.low  >> 8 & 0x0000ff00) | (xdwop2.low        & 0x000000ff);
    dwdst.high = (dwop1.high << 8 & 0xff000000) | (dwop1.high << 16 & 0x00ff0000) |
                 (xdwop2.high >> 8 & 0x0000ff00) | (xdwop2.high       & 0x000000ff);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dpacklh2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dpacklh2(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dpacklh4(uint32 arg_op1, uint32 arg_xop2)
{
    uword       op1;
    uword       xop2;
    dword       dwdst;
    int64_ll    result;

    UINT32_TO_UWORD(arg_op1, op1);
    UINT32_TO_UWORD(arg_xop2, xop2);

    dwdst.low  = (op1 << 8 & 0xff000000) | (op1 << 16 & 0x00ff0000) |
                 (xop2 >> 8 & 0x0000ff00) | (xop2       & 0x000000ff);
    dwdst.high = (op1       & 0xff000000) | (op1 << 8 & 0x00ff0000) |
                 (xop2 >> 16 & 0x0000ff00) | (xop2 >> 8 & 0x000000ff);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dsadd(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dsadd(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dsadd2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dsadd2(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dshl(int64_ll arg_xdwop1, uint32 arg_op2)
{
    dword       xdwop1;
    uword       op2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_xdwop1, xdwop1);
    UINT32_TO_UWORD(arg_op2, op2);

    dwdst = dshl(xdwop1, op2);   // xdwop1.high >> op2 w/ sign-extension, and xdwop1.low >> op2 w/ sign-extension

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dshl2(int64_ll arg_xdwop1, uint32 arg_op2)
{
    dword       xdwop1;
    uword       op2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_xdwop1, xdwop1);
    UINT32_TO_UWORD(arg_op2, op2);

    dwdst = dshl2(xdwop1, op2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dshr(int64_ll arg_xdwop1, uint32 arg_op2)
{
    dword       xdwop1;
    uword       op2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_xdwop1, xdwop1);
    UINT32_TO_UWORD(arg_op2, op2);

    dwdst = dshr(xdwop1, op2);   // xdwop1.high >> op2 w/ sign-extension, and xdwop1.low >> op2 w/ sign-extension

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dshr2(int64_ll arg_xdwop1, uint32 arg_op2)
{
    dword       xdwop1;
    uword       op2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_xdwop1, xdwop1);
    UINT32_TO_UWORD(arg_op2, op2);

    dwdst = dshr2(xdwop1, op2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dshru(int64_ll arg_xdwop1, uint32 arg_op2)
{
    dword       xdwop1;
    uword       op2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_xdwop1, xdwop1);
    UINT32_TO_UWORD(arg_op2, op2);

    dwdst = dshru(xdwop1, op2);   // xdwop1.high >> op2 w/ sign-extension, and xdwop1.low >> op2 w/ sign-extension

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dshru2(int64_ll arg_xdwop1, uint32 arg_op2)
{
    dword       xdwop1;
    uword       op2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_xdwop1, xdwop1);
    UINT32_TO_UWORD(arg_op2, op2);

    dwdst = dshru2(xdwop1, op2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

__x128_t _dsmpy2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    qword       qwdst;
    __x128_t    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);


    qwdst = dsmpy2(dwop1, xdwop2);     // 3 delay slots

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

int64_ll _dspacku4(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = spack4(dwop1.high, dwop1.low);
    dwdst.high = spack4(xdwop2.high, xdwop2.low);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dspint(__float2_t arg_xdwop)
{
    dword       xdwop;
    dword       dwdst;
    int64_ll    result;

    __FLOAT2_T_TO_DWORD(arg_xdwop, xdwop);

    dwdst.low  = spint(xdwop.low, 2);     // 2 delay slots
    dwdst.high = spint(xdwop.high, 2);     // 2 delay slots

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

uint32 _dspinth(__float2_t arg_xdwop)
{
    dword     xdwop;
    uword     dst;
    uint32    result;

    __FLOAT2_T_TO_DWORD(arg_xdwop, xdwop);

    dst = spack2(spinth(xdwop.high), spinth(xdwop.low));       // 2 delay slots

    UWORD_TO_UINT32(dst, result);
    return (result);
}

int64_ll _dssub(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dssub(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dssub2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dssub2(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dsub(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dsub(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dsub2(int64_ll arg_dwop1, int64_ll arg_xdwop2)
{
    dword       dwop1;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT64_LL_TO_DWORD(arg_dwop1, dwop1);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = dsub2(dwop1, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

__float2_t _dsubsp(__float2_t arg_dwop1, __float2_t arg_xdwop2)
{
    dword         dwop1;
    dword         xdwop2;
    dword         dwdst;
    __float2_t    result;

    __FLOAT2_T_TO_DWORD(arg_dwop1, dwop1);
    __FLOAT2_T_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst.low  = sub_sp(dwop1.low, xdwop2.low, 2);      // 2 delay slots
    dwdst.high = sub_sp(dwop1.high, xdwop2.high, 2);    // 2 delay slots

    DWORD_TO___FLOAT2_T(dwdst, result);
    return (result);
}

int64_ll _dxpnd2(uint32 arg_xop)
{
    uword       xop;
    dword       dwdst;
    int64_ll    result;

    UINT32_TO_UWORD(arg_xop, xop);

    dwdst.low  = expand2(xop);     // 1 delay slot
    dwdst.high = expand2(xop >> 2); // 1 delay slot

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _dxpnd4(uint32 arg_xop)
{
    uword       xop;
    dword       dwdst;
    int64_ll    result;

    UINT32_TO_UWORD(arg_xop, xop);

    dwdst.low  = expand4(xop);     // 1 delay slot
    dwdst.high = expand4(xop >> 4); // 1 delay slot

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int32 _land(int32 arg_op1, int32 arg_xop2)
{
    uword    op1;
    uword    xop2;
    uword    dst;
    int32    result;

    INT32_TO_UWORD(arg_op1, op1);
    INT32_TO_UWORD(arg_xop2, xop2);

    dst = (op1 && xop2) ? 1 : 0;

    UWORD_TO_INT32(dst, result);
    return (result);
}

int32 _landn(int32 arg_op1, int32 arg_xop2)
{
    uword    op1;
    uword    xop2;
    uword    dst;
    int32    result;

    INT32_TO_UWORD(arg_op1, op1);
    INT32_TO_UWORD(arg_xop2, xop2);

    dst = (op1 && !xop2) ? 1 : 0;

    UWORD_TO_INT32(dst, result);
    return (result);
}

int32 _lor(int32 arg_op1, int32 arg_xop2)
{
    uword    op1;
    uword    xop2;
    uword    dst;
    int32    result;

    INT32_TO_UWORD(arg_op1, op1);
    INT32_TO_UWORD(arg_xop2, xop2);

    dst = (op1 || xop2) ? 1 : 0;

    UWORD_TO_INT32(dst, result);
    return (result);
}

void _mfence()
{
    // while ( memory_busy() ) ;

}

int64_ll _mpyu2(uint32 arg_op1, uint32 arg_xop2)
{
    uword       op1;
    uword       xop2;
    dword       dwdst;
    int64_ll    result;

    UINT32_TO_UWORD(arg_op1, op1);
    UINT32_TO_UWORD(arg_xop2, xop2);

    dwdst.low = ulow16(op1) * ulow16(xop2); // 3 delay slot
    dwdst.high = uhigh16(op1) * uhigh16(xop2); // 3 delay slot

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

__x128_t _qmpy32(__x128_t arg_qwop1, __x128_t arg_qwop2)
{
    qword       qwop1;
    qword       qwop2;
    qword       qwdst;
    __x128_t    result;

    __X128_T_TO_QWORD(arg_qwop1, qwop1);
    __X128_T_TO_QWORD(arg_qwop2, qwop2);

    qwdst.word0 = qwop1.word0 * qwop2.word0;  // 3 delay slot
    qwdst.word1 = qwop1.word1 * qwop2.word1;  // 3 delay slot
    qwdst.word2 = qwop1.word2 * qwop2.word2;  // 3 delay slot
    qwdst.word3 = qwop1.word3 * qwop2.word3;  // 3 delay slot

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

__x128_t _qmpysp(__x128_t arg_qwop1, __x128_t arg_qwop2)
{
    qword       qwop1;
    qword       qwop2;
    qword       qwdst;
    __x128_t    result;

    __X128_T_TO_QWORD(arg_qwop1, qwop1);
    __X128_T_TO_QWORD(arg_qwop2, qwop2);

    qwdst.word0 = mpy_sp(qwop1.word0, qwop2.word0);    // 3 delay slots
    qwdst.word1 = mpy_sp(qwop1.word1, qwop2.word1);    // 3 delay slots
    qwdst.word2 = mpy_sp(qwop1.word2, qwop2.word2);    // 3 delay slots
    qwdst.word3 = mpy_sp(qwop1.word3, qwop2.word3);    // 3 delay slots

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

__x128_t _qsmpy32r1(__x128_t arg_qwop1, __x128_t arg_qwop2)
{
    qword       qwop1;
    qword       qwop2;
    qword       qwdst;
    __x128_t    result;

    __X128_T_TO_QWORD(arg_qwop1, qwop1);
    __X128_T_TO_QWORD(arg_qwop2, qwop2);

    qwdst.word0 = smpy32r1(qwop1.word0, qwop2.word0); // 3 delay slot  // Need to add rounding!
    qwdst.word1 = smpy32r1(qwop1.word1, qwop2.word1); // 3 delay slot
    qwdst.word2 = smpy32r1(qwop1.word2, qwop2.word2); // 3 delay slot
    qwdst.word3 = smpy32r1(qwop1.word3, qwop2.word3); // 3 delay slot

    QWORD_TO___X128_T(qwdst, result);
    return (result);
}

uint32 _shl2(uint32 arg_xop1, uint32 arg_op2)
{
    uword     xop1;
    uword     op2;
    uword     dst;
    uint32    result;

    UINT32_TO_UWORD(arg_xop1, xop1);
    UINT32_TO_UWORD(arg_op2, op2);

    dst = shl2(xop1, op2);

    UWORD_TO_UINT32(dst, result);
    return (result);
}

int64_ll _unpkbu4(uint32 arg_xop)
{
    uword       xop;
    dword       dwdst;
    int64_ll    result;

    UINT32_TO_UWORD(arg_xop, xop);

    dwdst.low  = unpklu4(xop);
    dwdst.high = unpkhu4(xop);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _unpkh2(uint32 arg_xop)
{
    uword       xop;
    dword       dwdst;
    int64_ll    result;

    UINT32_TO_UWORD(arg_xop, xop);

    dwdst.low  = slow16(xop);
    dwdst.high = shigh16(xop);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _unpkhu2(uint32 arg_xop)
{
    uword       xop;
    dword       dwdst;
    int64_ll    result;

    UINT32_TO_UWORD(arg_xop, xop);

    dwdst.low  = ulow16(xop);
    dwdst.high = uhigh16(xop);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

int64_ll _xorll_c(int32 arg_scst5, int64_ll arg_xdwop2)
{
    uword       scst5;
    dword       xdwop2;
    dword       dwdst;
    int64_ll    result;

    INT32_TO_UWORD(arg_scst5, scst5);
    INT64_LL_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = xor_cl(scst5, xdwop2);

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

#endif /* #ifdef TMS320C66X */

#ifdef TMS320C67X
int32 _dpint(double64 arg_dwop)
{
    dword    dwop;
    uword    dst;
    int32    result;

    DOUBLE64_TO_DWORD(arg_dwop, dwop);

    dst = dpint(dwop);   // 3 delay slots

    UWORD_TO_INT32(dst, result);
    return (result);
}

int64_ll _mpyidll(int32 arg_op1, int32 arg_xop2)
{
    uword       op1;
    uword       xop2;
    dword       dwdst;
    int64_ll    result;

    INT32_TO_UWORD(arg_op1, op1);
    INT32_TO_UWORD(arg_xop2, xop2);

    dwdst = mpyid(op1, xop2);   // 7 delay slots // 8 delay slots

    DWORD_TO_INT64_LL(dwdst, result);
    return (result);
}

double64 _mpysp2dp(float32 arg_op1, float32 arg_xop2)
{
    uword       op1;
    uword       xop2;
    dword       dwdst;
    double64    result;

    FLOAT32_TO_UWORD(arg_op1, op1);
    FLOAT32_TO_UWORD(arg_xop2, xop2);

    dwdst = mpy_sp2dp(op1, xop2);   // 3 delay slots // 4 delay slots

    DWORD_TO_DOUBLE64(dwdst, result);
    return (result);
}

double64 _mpyspdp(float32 arg_op1, double64 arg_xdwop2)
{
    uword       op1;
    dword       xdwop2;
    dword       dwdst;
    double64    result;

    FLOAT32_TO_UWORD(arg_op1, op1);
    DOUBLE64_TO_DWORD(arg_xdwop2, xdwop2);

    dwdst = mpy_spdp(op1, xdwop2);   // 5 delay slots // 6 delay slots

    DWORD_TO_DOUBLE64(dwdst, result);
    return (result);
}

double64 _rcpdp(double64 arg_dwop)
{
    dword       dwop;
    dword       dwdst;
    double64    result;

    DOUBLE64_TO_DWORD(arg_dwop, dwop);

    dwdst = rcp_dp(dwop);    // 0 delay slot // 1 delay slot

    DWORD_TO_DOUBLE64(dwdst, result);
    return (result);
}

float32 _rcpsp(float32 arg_xop)
{
    uword      xop;
    uword      dst;
    float32    result;

    FLOAT32_TO_UWORD(arg_xop, xop);

    dst = rcp_sp(xop);

    UWORD_TO_FLOAT32(dst, result);
    return (result);
}

double64 _rsqrdp(double64 arg_dwop)
{
    dword       dwop;
    dword       dwdst;
    double64    result;

    DOUBLE64_TO_DWORD(arg_dwop, dwop);

    dwdst = rcpsq_dp(dwop);    // 0 delay slot // 1 delay slot

    DWORD_TO_DOUBLE64(dwdst, result);
    return (result);
}

float32 _rsqrsp(float32 arg_xop)
{
    uword      xop;
    uword      dst;
    float32    result;

    FLOAT32_TO_UWORD(arg_xop, xop);

    dst = rcpsq_sp(xop);

    UWORD_TO_FLOAT32(dst, result);
    return (result);
}

int32 _spint(float32 arg_xop)
{
    uword    xop;
    uword    dst;
    int32    result;

    FLOAT32_TO_UWORD(arg_xop, xop);

    dst = spint(xop, 3);   // 3 delay slots

    UWORD_TO_INT32(dst, result);
    return (result);
}

#endif /* #ifdef TMS320C67X */


/*
 *  Automated Revision Information
 *  Changed: $Date: 2011-01-06 16:14:23 -0600 (Thu, 06 Jan 2011) $
 *  Revision: $Revision: 9948 $
 */
/*

C6000 Host Intrinsics Software License Agreement


IMPORTANT - PLEASE READ THE FOLLOWING LICENSE AGREEMENT CAREFULLY.
THIS IS A LEGALLY BINDING AGREEMENT.  AFTER YOU READ THIS LICENSE
AGREEMENT, YOU WILL BE ASKED WHETHER YOU ACCEPT AND AGREE TO THE
TERMS OF THIS LICENSE AGREEMENT.  DO NOT CLICK  "I HAVE READ AND AGREE"
UNLESS: (1) YOU ARE AUTHORIZED TO ACCEPT AND AGREE TO THE TERMS OF THIS
LICENSE AGREEMENT ON BEHALF OF YOURSELF AND YOUR COMPANY; AND (2) YOU
INTEND TO ENTER INTO AND TO BE BOUND BY THE TERMS OF THIS LEGALLY
BINDING AGREEMENT ON BEHALF OF YOURSELF AND YOUR COMPANY.


Important - Read carefully: This C6000 Host Intrinsics Software License
Agreement ("Agreement") is a legal agreement between you (either an
individual or entity) and Texas Instruments Incorporated ("TI").  The
"Licensed Materials" subject to this Agreement include the software
programs that TI has granted you access to download with this Agreement
and any "on-line" or electronic documentation associated with these
programs, or any portion thereof, as well as any updates or upgrades to such
software programs and documentation, if any, or any portion thereof,
provided to you in TI's sole discretion.  By installing, copying or otherwise
using the Licensed Materials you agree to abide by the following provisions.
This Agreement is displayed for you to read prior to using the Licensed
Materials.  If you choose not to accept or agree with these provisions, do not
download or install the Licensed Materials.

1.  License Grant and Use Restrictions.

a.  License Grant.  Subject to the terms of this Agreement, TI hereby
grants to you under all TI intellectual property rights embodied in the
Licensed Materials a limited, non-exclusive, non-transferable, non-
assignable, fully paid-up, royalty-free, non-sublicensable license only to
(i) use the Licensed Materials solely for the purposes of evaluating,
testing, debugging and optimizing applications ("Target Applications")
that execute solely and exclusively on processing devices manufactured
by or for TI ("TI Devices"), and (ii) make a reasonable number of copies
necessary to exercise the right granted to you in Section 1(a)(i) above.
Use of any software applications optimized or developed using the
Licensed Materials on processing devices manufactured by or for an
entity other than TI is a material breach of this Agreement.  It is also a
material breach of this license to use the Licensed Materials to assist in
the design, development or verification of a device that is instruction set
compatible with, or functionally equivalent to, a TI processing device.

b.  Contractors and Suppliers.  The licenses granted to you hereunder
shall include your on-site and off-site suppliers and independent
contractors, while such suppliers and independent contractors are
performing work for or providing services to you, provided that such
suppliers and independent contractors have executed work-for-hire
agreements with you containing terms and conditions not inconsistent
with the terms and conditions set forth in this Agreement, and provided
further that you agree you are responsible for the breach of this
Agreement by any of your suppliers or contractors to the same extent
that you would be if you breached the Agreement yourself.

c.  No Distribution License.  NOTWITHSTANDING ANYTHING TO THE
CONTRARY, THIS AGREEMENT DOES NOT CONVEY ANY
LICENSE TO DISTRIBUTE THE LICENSED MATERIALS TO ANY
THIRD PARTY.  YOU ARE REQUIRED TO EXECUTE A SEPARATE
LICENSE AGREEMENT WITH TI BEFORE DISTRIBUTING THE
LICENSED MATERIALS OR ANY PRODUCTS THAT CONTAIN THE
LICENSED MATERIALS, OR ANY DERIVATIVE THEREOF.

    d.  Limited License to TI and Covenant not to Sue.  Continuing for the
term of this Agreement, you hereby grant to TI under any of your
patents embodied in the Licensed Materials a non-transferable, non-
exclusive, non-assignable, worldwide, fully paid-up, royalty-free license
to make, use, sell, offer to sell, import, export and otherwise distribute
such Licensed Materials.  You covenant not to sue or otherwise assert
Derived Patents against TI and TI's affiliates and their licensees of the
Licensed Materials.  In the event you assign a Derived Patent, you shall
require as a condition of any such assignment that the assignee agree
to be bound by the provisions in this Section 1(d) with respect to such
Derived Patent.  Any attempted assignment or transfer in violation of
this Section 1(d) shall be null and void.  For purposes of this Agreement,
"Derived Patents" means any of your patents issuing from a patent
application that discloses and claims an invention conceived of by you
after delivery of the Licensed Materials, and derived by you from your
access to the Licensed Materials.

    e.  No Other License.  Notwithstanding anything to the contrary, nothing
in this Agreement shall be construed as a license to any intellectual
property rights of TI other than those rights embodied in the Licensed
Materials provided to you by TI.  EXCEPT AS PROVIDED HEREIN, NO
OTHER LICENSE, EXPRESS OR IMPLIED, BY ESTOPPEL OR
OTHERWISE, TO ANY OTHER TI INTELLECTUAL PROPERTY
RIGHTS IS GRANTED HEREIN.

    f.  Restrictions.

i.  You shall not disclose or distribute the source code versions of
the Licensed Materials, or any derivative thereof, to any person
other than your employees and contractors whose job
performance requires access.

ii. Use of any software application optimized or developed using
the Licensed Materials on processing devices manufactured by
or for an entity other than TI is a material breach of this
Agreement.  Use of the Licensed Materials to assist in the
design, development or verification of a device not manufactured
by or for TI is a material breach of this Agreement.  Use of the
Licensed Materials to evaluate, test, debug and optimize
applications for use with processing devices other than those
manufactured by or for TI is a material breach of this Agreement.

iii.    Other than as expressly set forth in this Section 1(f)(iii) and in
Section 1(a) above, you may not otherwise copy or reproduce
the Licensed Materials.

iv. You will not sublicense, transfer or assign the Licensed Materials
or your rights under this Agreement to any third party.

v.  You may use the Licensed Materials with Open Source Software
(as defined below) or with software developed using Open
Source Software (e.g. tools) provided you do not incorporate,
combine or distribute the Licensed Materials in a manner that
subjects the Licensed Materials, or any derivatives thereof, to
any license obligations or any other intellectual property related
terms of such Open Source Software.  "Open Source Software"
means any software licensed under terms requiring that (A) other
software ("Proprietary Software") incorporated, combined or
distributed with such software or developed using such software:
(i) be disclosed or distributed in source code form; or (ii)
otherwise be licensed on terms inconsistent with the terms of this
Agreement, including but not limited to permitting use of the
Proprietary Software on or with devices other than TI Devices, or
(B) the owner of Proprietary Software license any of its patents
to users of the Open Source Software and/or Proprietary
Software incorporated, combined or distributed with such Open
Source Software or developed using such Open Source
Software.

    g.  Termination.  This Agreement is effective until terminated.  You may
terminate this Agreement at any time by written notice to TI.  Without
prejudice to any other rights, if you fail to comply with the terms of this
Agreement, TI may terminate your right to use the Licensed Materials,
or any derivative thereof, and any applications generated using the
Licensed Materials, or any derivative thereof, upon written notice to you.
Upon expiration or termination of this Agreement, you will destroy any
and all copies of the Licensed Materials, including any derivatives
thereof, in your possession, custody or control and provide to TI a
written statement signed by your authorized representative certifying
such destruction. Except for Sections 1(a) and 1(b) and the limited
license to TI set forth in Section 1(d), all provisions of this Agreement
shall survive expiration or termination of the Agreement.

2.  Licensed Materials Ownership.  The Licensed Materials are licensed,
not sold to you, and can only be used in accordance with the terms of
this Agreement.  Subject to the licenses granted to you pursuant to this
Agreement, TI and TI's licensors own and shall continue to own all right,
title and interest in and to the Licensed Materials, including all copies
thereof.  The parties agree that all fixes, modifications and
improvements to the Licensed Materials conceived of or made by TI
that are based, either in whole or in part, on your feedback, suggestions
or recommendations are the exclusive property of TI and all right, title
and interest in and to such fixes, modifications or improvements to the
Licensed Materials will vest solely in TI.  You acknowledge and agree
that regardless of the changes made to the Licensed Materials, your
right to use any and all derivatives of the Licensed Materials shall
remain subject to the terms and conditions of this Agreement.
Moreover, you acknowledge and agree that when your independently
developed software or hardware components are combined, in whole or
in part, with the Licensed Materials, or any derivative thereof, your right
to use the Licensed Materials, or any derivative thereof, embodied in
such resulting combined work shall remain subject to the terms and
conditions of this Agreement.

3.  Intellectual Property Rights.

    a.  The Licensed Materials contain copyrighted material, trade secrets
and other proprietary information of TI and its licensors and are
protected by copyright laws, international copyright treaties and trade
secret laws, as well as other intellectual property laws.  To protect TI's
and its licensors' rights in the Licensed Materials, you agree, except as
specifically permitted by statute by a provision that cannot be waived by
contract, not to "unlock", decompile, reverse engineer, disassemble or
otherwise translate any portions of the Licensed Materials provided to
you in object code format only to a human-perceivable form nor to
permit any person or entity to do so.  You shall not remove, erase, alter,
tamper, cover or obscure any confidentiality, trade secret, proprietary or
copyright notices, trade-marks, proprietary, patent or other identifying
marks or designs printed or stamped on, affixed to, or encoded or
recorded in any component of the Licensed Materials and you shall
reproduce and include in all copies of the Licensed Materials the
copyright notice(s) and proprietary legend(s) of TI and its licensors as
they appear in the Licensed Materials.  TI reserves all rights not
specifically granted under this Agreement.

    b.  Certain Licensed Materials may be based on industry recognized
standards or software programs published by industry recognized
standards bodies and certain third parties may claim to own patents,
copyrights and other intellectual property rights that cover
implementation of those standards.  You acknowledge and agree that
this Agreement does not convey a license to any such third party
patents, copyrights and other intellectual property rights and that you
are solely responsible for any patent, copyright or other intellectual
property right claim that relates to your use or distribution of the
Licensed Materials, or your use or distribution of your products that
include or incorporate the Licensed Materials.  Moreover, you
acknowledge that any fees or royalties paid to TI pursuant to this
Agreement, as applicable, do not include any fees or royalties that may
be payable to any third party based on such third party's interests in the
Licensed Materials or any intellectual property rights that cover
implementation of any industry recognized standard, any software
program published by any industry recognized standards bodies or any
other proprietary technology.

4.  Audit Right.  At TI's request, and within thirty (30) days after receiving
written notice, you shall permit an independent auditor selected by TI to
have access, no more than once each calendar year (unless the
immediately preceding audit revealed a breach of this Agreement) and
during your regular business hours, to all of your equipment, records
and documents as may contain information bearing upon the use of the
Licensed Materials.  You shall keep full, complete, clear and accurate
records with respect to product sales and distributions for a period
beginning with the then-current calendar year and going back three (3)
years.

5.  Confidential Information.  You acknowledge and agree that the
Licensed Materials, and any derivative thereof, contain trade secrets
and other confidential information of TI and its licensors.  You agree to
use the Licensed Materials, or any derivative thereof, solely within the
scope of the licenses set forth herein, to maintain the Licensed
Materials, or any derivative thereof, in strict confidence, to use at least
the same procedures and degree of care that you use to prevent
disclosure of your own confidential information of like importance but in
no instance less than reasonable care, and to prevent disclosure of the
Licensed Materials, or any derivative thereof, to any third party, except
as may be necessary and required in connection with your rights and
obligations hereunder.  You agree to obtain executed confidentiality
agreements with your employees and contractors having access to the
Licensed Materials, or any derivative thereof, and to diligently take
steps to enforce such agreements in this respect.  TI agrees that
industry standard employment agreements used in the normal course of
your business shall satisfy the requirements of this section. TI may
disclose your contact information to TI's applicable licensors.

6.  Warranties and Limitations.  THE LICENSED MATERIALS ARE
PROVIDED "AS IS".  TI MAKES NO WARRANTY OR
REPRESENTATION, EITHER EXPRESS, IMPLIED OR STATUTORY,
REGARDING THE LICENSED MATERIALS, INCLUDING BUT NOT
LIMITED TO, ANY IMPLIED WARRANTIES OF MERCHANTABILITY
OR FITNESS FOR A PARTICULAR PURPOSE OR NON-
INFRINGEMENT OF ANY THIRD PARTY PATENTS, COPYRIGHTS,
TRADE SECRETS OR OTHER INTELLECTUAL PROPERTY RIGHTS.
YOU AGREE TO USE YOUR INDEPENDENT JUDGMENT IN
DEVELOPING YOUR PRODUCTS AND DERIVATIVES OF THE
LICENSED MATERIALS.  NOTHING CONTAINED IN THIS
AGREEMENT WILL BE CONSTRUED AS A WARRANTY OR
REPRESENTATION BY TI TO MAINTAIN PRODUCTION OF ANY TI
SEMICONDUCTOR DEVICE OR OTHER HARDWARE OR
SOFTWARE WITH WHICH THE LICENSED MATERIALS MAY BE
USED.

YOU ACKNOWLEDGE AND AGREE THAT THE LICENSED
MATERIALS MAY NOT BE INTENDED FOR PRODUCTION
APPLICATIONS AND MAY CONTAIN IRREGULARITIES AND
DEFECTS NOT FOUND IN PRODUCTION SOFTWARE.
FURTHERMORE, YOU ACKNOWLEDGE AND AGREE THAT THE
LICENSED MATERIALS HAVE NOT BEEN TESTED OR CERTIFIED
BY ANY GOVERNMENT AGENCY OR INDUSTRY REGULATORY
ORGANIZATION OR ANY OTHER THIRD PARTY ORGANIZATION.
YOU AGREE THAT PRIOR TO USING OR DISTRIBUTING ANY
COMMERCIAL PRODUCT OPTIMIZED OR DEVELOPED USING THE
LICENSED MATERIALS YOU WILL THOROUGHLY TEST THE
PRODUCT AND THE FUNCTIONALITY OF THAT PRODUCT AND BE
SOLELY RESPONSIBLE FOR ANY PROBLEMS OR FAILURES.

IN NO EVENT SHALL TI, OR ANY APPLICABLE LICENSOR, BE
LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, PUNITIVE OR
CONSEQUENTIAL DAMAGES, HOWEVER CAUSED, ON ANY
THEORY OF LIABILITY, IN CONNECTION WITH OR ARISING OUT
OF THIS AGREEMENT OR THE USE OF THE LICENSED
MATERIALS, OR ANY DERIVATIVE THEREOF, REGARDLESS OF
WHETHER TI HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
DAMAGES.  EXCLUDED DAMAGES INCLUDE, BUT ARE NOT
LIMITED TO, COST OF REMOVAL OR REINSTALLATION, OUTSIDE
COMPUTER TIME, LABOR COSTS, LOSS OF DATA, LOSS OF
GOODWILL, LOSS OF PROFITS, LOSS OF SAVINGS, OR LOSS OF
USE OR INTERRUPTION OF BUSINESS.  IN NO EVENT WILL TI'S
AGGREGATE LIABILITY UNDER THIS AGREEMENT OR ARISING
OUT OF YOUR USE OF THE LICENSED MATERIALS, OR ANY
DERIVATIVE THEREOF, EXCEED THE GREATER OF FIVE
HUNDRED U.S. DOLLARS (US$500) OR THE FEES PAID TO TI BY
YOU FOR THE LICENSED MATERIALS UNDER THIS AGREEMENT.

    Because some jurisdictions do not allow the exclusion or limitation of
incidental or consequential damages or limitation on how long an
implied warranty lasts, the above limitations or exclusions may not apply
to you.

7.  Indemnification Disclaimer.  YOU ACKNOWLEDGE AND AGREE
THAT TI SHALL NOT BE LIABLE FOR AND SHALL NOT DEFEND OR
INDEMNIFY YOU AGAINST ANY THIRD PARTY INFRINGEMENT
CLAIM THAT RELATES TO OR IS BASED ON YOUR
MANUFACTURE, USE OR DISTRIBUTION OF THE LICENSED
MATERIALS, OR ANY DERIVATIVE THEREOF, OR YOUR
MANUFACTURE, USE, OFFER FOR SALE, SALE, IMPORTATION OR
DISTRIBUTION OF YOUR PRODUCTS THAT INCLUDE OR
INCORPORATE THE LICENSED MATERIALS, OR ANY DERIVATIVE
THEREOF.

8.  No Technical Support.  TI and TI's licensors are under no obligation to
install, maintain or support the Licensed Materials, or any derivatives
thereof.

9.  Notices.  All notices to TI hereunder shall be delivered to Texas
Instruments Incorporated, 12500 TI Boulevard, Mail Station 8638,
Dallas, Texas 75243, Attention: Contracts Manager, with a copy to
Texas Instruments Incorporated, 13588 N. Central Expressway, Mail
Station 3999, Dallas, Texas 75243, Attention: Law Department - ASP.
All notices shall be deemed served when received by TI.

10. Export Control.  You hereby acknowledge that the Licensed Materials
are subject to export control under the U.S. Commerce Department's
Export Administration Regulations ("EAR").  You further hereby
acknowledge and agree that unless prior authorization is obtained from the
U.S. Commerce Department, neither you nor your customers will export,
re-export or release, directly or indirectly, any technology, software or
software source code (as defined in Part 772 of the EAR), received from
TI, or export, directly or indirectly, any direct product of such technology,
software or software source code (as defined in Part 734 of the EAR), to
any destination or country to which the export, re-export or release of the
technology, software or software source code, or direct product is
prohibited by the EAR.  You agree that none of the Licensed Materials
may be downloaded or otherwise exported or reexported (i) into (or to a
national or resident of) Cuba, Iran, North Korea, Sudan and Syria or any
other country the U.S. has embargoed goods; or (ii) to anyone on the U.S.
Treasury Department's List of Specially Designated Nationals or the U.S.
Commerce Department's Denied Persons List or Entity List.  You
represent and warrant that you are not located in, under the control of, or a
national or resident of any such country or on any such list and you will not
use or transfer the Licensed Materials for use in any sensitive nuclear,
chemical or biological weapons, or missile technology end-uses unless
authorized by the U.S. Government by regulation or specific license or for
a military end-use in, or by any military entity of Albania, Armenia,
Azerbaijan, Belarus, Cambodia, China, Georgia, Iraq, Kazakhstan,
Kyrgyzstan, Laos, Libya, Macau, Moldova, Mongolia, Russia, Tajikistan,
Turkmenistan, Ukraine, Uzbekistan and Vietnam. Any software export
classification made by TI shall be for TI's internal use only and shall not
be construed as a representation or warranty regarding the proper
export classification for such software or whether an export license or
other documentation is required for the exportation of such software.

11. Governing Law and Severability.  This Agreement will be governed by
and interpreted in accordance with the laws of the State of Texas,
without reference to conflict of laws principles.  If for any reason a court
of competent jurisdiction finds any provision of the Agreement to be
unenforceable, that provision will be enforced to the maximum extent
possible to effectuate the intent of the parties, and the remainder of the
Agreement shall continue in full force and effect.  This Agreement shall
not be governed by the United Nations Convention on Contracts for the
International Sale of Goods, or by the Uniform Computer Information
Transactions Act (UCITA).  The parties agree that non-exclusive
jurisdiction for any dispute arising out of or relating to this Agreement
lies within the courts located in the State of Texas.  Notwithstanding the
foregoing, any judgment may be enforced in any United States or
foreign court, and either party may seek injunctive relief in any United
States or foreign court.

12. PRC Provisions.  If you are located in the People's Republic of China
("PRC") or if the Licensed Materials will be sent to the PRC, the
following provisions shall apply and shall supersede any other
provisions in this Agreement concerning the same subject matter:

    a.  Registration Requirements.  You shall be solely responsible for
performing all acts and obtaining all approvals that may be required in
connection with this Agreement by the government of the PRC,
including but not limited to registering pursuant to, and otherwise
complying with, the PRC Measures on the Administration of Software
Products, Management Regulations on Technology Import-Export, and
Technology Import and Export Contract Registration Management
Rules.  Upon receipt of such approvals from the government authorities,
you shall forward evidence of all such approvals to TI for its records.  In
the event that you fail to obtain any such approval or registration, you
shall be solely responsible for any and all losses, damages or costs
resulting therefrom, and shall indemnify TI for all such losses, damages
or costs.

b.  Governing Language.  This Agreement is written and executed in
the English language.  If a translation of this Agreement is required for
any purpose, including but not limited to registration of the Agreement
pursuant to any governmental laws, regulations or rules, you shall be
solely responsible for creating such translation.  Any translation of this
Agreement into a language other than English is intended solely in order
to comply with such laws or for reference purposes, and the English
language version shall be authoritative and controlling.

c.  Export Control.

i.  Diversions of Technology.  You hereby agree that unless
prior authorization is obtained from the U.S. Department of
Commerce, neither you nor your subsidiaries or affiliates shall
knowingly export, re-export or release, directly or indirectly, any
technology, software or software source code (as defined in Part
772 of the Export Administration Regulations of the U.S.
Department of Commerce ("EAR")), received from TI or any of its
affiliated companies, or export, directly or indirectly, any direct
product of such technology, software or software source code (as
defined in Part 734 of the EAR), to any destination or country to
which the export, re-export or release of the technology, software,
software source code or direct product is prohibited by the EAR.

ii. Assurance of Compliance.  You understand and
acknowledge that products, technology (regardless of the form in
which it is provided), software or software source code, received
from TI or any of its affiliates under this Agreement may be under
export control of the United States or other countries.  You shall
comply with the United States and other applicable non-U.S. laws
and regulations governing the export, re-export and release of any
products, technology, software or software source code received
under this Agreement from TI or its affiliates.  You shall not
undertake any action that is prohibited by the EAR.  Without
limiting the generality of the foregoing, you specifically agree that
you shall not transfer or release products, technology, software or
software source code of TI or its affiliates to, or for use by, military
end users or for use in military, missile, nuclear, biological or
chemical weapons end uses.

iii.    Licenses.  Each party shall secure at its own expense, such
licenses and export and import documents as are necessary for
each respective party to fulfill its obligations under this Agreement.
If such licenses or government approvals cannot be obtained, TI
may terminate this Agreement, or shall otherwise be excused from
the performance of any obligations it may have under this
Agreement for which the licenses or government approvals are
required.

13. Contingencies.  TI shall not be in breach of this Agreement and shall
not be liable for any non-performance or delay in performance if such
non-performance or delay is due to a force majeure event or other
circumstances beyond TI's reasonable control, including but not limited
to, shortages of labor, energy, fuel, machinery or materials, technical or
yield failures, war, civil unrest, any government act, law or regulation,
including any judicial order or decree, any communication or power
failure, labor dispute, natural disaster, fire, flood, earthquake, explosion,
terrorist act or Act of God.

14. Entire Agreement.  This is the entire Agreement between you and TI
and this Agreement supersedes any prior agreement between the
parties related to the subject matter of this Agreement.  No amendment
or modification of this Agreement will be effective unless in writing and
signed by a duly authorized representative of TI.  You hereby warrant
and represent that you have obtained all authorizations and other
applicable consents required empowering you to enter into this
Agreement.





Page 1

*/

