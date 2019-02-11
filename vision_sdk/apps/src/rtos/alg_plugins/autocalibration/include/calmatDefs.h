/*Header file defining calmat storage format*/
#ifndef _CALMAT_DEFS_H_
#define _CALMAT_DEFS_H_

// Calibration table precision
//(format is int32 with 1 bit sign)
#define CALMAT_R_SHIFT 30 // Rotation Matrix in [R|T] Q1.30
#define CALMAT_T_SHIFT 10 // Translation Matrix in [R|T] Q21.10
#define CALMAT_H_SHIFT 20 // Perspective matrix precision H Q11.20

#endif
