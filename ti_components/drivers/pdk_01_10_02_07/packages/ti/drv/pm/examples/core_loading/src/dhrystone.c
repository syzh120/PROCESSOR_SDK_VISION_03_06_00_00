/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2018
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS int32_tERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file   dhrystone.c
 *
 *  \brief  Dhrystone Code
 */

#include <stdlib.h>
#include <stdio.h>
#include "dhrystone.h"

/* Global Variables: */

Rec_Pointer         Ptr_Glob,
                    Next_Ptr_Glob;
int32_t             int32_t_Glob;
Boolean             Bool_Glob;
char                Ch_1_Glob,
                    Ch_2_Glob;
int32_t             Arr_1_Glob [50];
int32_t             Arr_2_Glob [50] [50];
Rec_Type            Next_Glob = {0};
Rec_Type            Glob = {0};


char Reg_Define[40] = "Register option      Selected.";


Enumeration Func_1 (Capital_Letter Ch_1_Par_Val,
                    Capital_Letter Ch_2_Par_Val);

#define REG register

void Proc_1 (REG Rec_Pointer Ptr_Val_Par);
void Proc_2 (One_Fifty *int32_t_Par_Ref);
void Proc_3 (Rec_Pointer *Ptr_Ref_Par);
void Proc_4 ();
void Proc_5 ();
void Proc_6 (Enumeration Enum_Val_Par, Enumeration *Enum_Ref_Par);
void Proc_7 (One_Fifty int32_t_1_Par_Val, One_Fifty int32_t_2_Par_Val,
                                             One_Fifty *int32_t_Par_Ref);
void Proc_8 (Arr_1_Dim Arr_1_Par_Ref, Arr_2_Dim Arr_2_Par_Ref,
             int32_t int32_t_1_Par_Val, int32_t int32_t_2_Par_Val);

Boolean Func_2 (Str_30 Str_1_Par_Ref, Str_30 Str_2_Par_Ref);
Boolean Func_3 (Enumeration Enum_Par_Val);

extern volatile uint32_t numRun;

void runDhrystone()
{
    One_Fifty       int32_t_1_Loc;
    REG One_Fifty   int32_t_2_Loc;
    One_Fifty       int32_t_3_Loc;
    REG char        Ch_Index;
    Enumeration     Enum_Loc;
    Str_30          Str_1_Loc;
    Str_30          Str_2_Loc;
    REG int32_t     Run_Index;
    REG int32_t     Number_Of_Runs;

    Next_Ptr_Glob = (Rec_Pointer) &Next_Glob;
    Ptr_Glob      = (Rec_Pointer) &Glob;

    Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
    Ptr_Glob->Discr                       = Ident_1;
    Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
    Ptr_Glob->variant.var_1.Int_Comp      = 40;
    strcpy (Ptr_Glob->variant.var_1.Str_Comp,
            "DHRYSTONE PROGRAM, SOME STRING");
    strcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

    Arr_2_Glob [8][7] = 10;
#if defined (BUILD_A15_0)
    Number_Of_Runs = 1000;
#else
    Number_Of_Runs = 10;
#endif
    Arr_2_Glob [8][7] = 10;

    for (Run_Index = 1; Run_Index <= Number_Of_Runs; ++Run_Index)
    {
         Proc_5();
         Proc_4();
         strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
         int32_t_1_Loc = 2;
         int32_t_2_Loc = 3;
         Enum_Loc = Ident_2;
         Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc);
         /* Bool_Glob == 1 */
         while (int32_t_1_Loc < int32_t_2_Loc)  /* loop body executed once */
         {
               int32_t_3_Loc = 5 * int32_t_1_Loc - int32_t_2_Loc;
                 /* int32_t_3_Loc == 7 */
               Proc_7 (int32_t_1_Loc, int32_t_2_Loc, &int32_t_3_Loc);
                 /* int32_t_3_Loc == 7 */
               int32_t_1_Loc += 1;
         }   /* while */
         /* int32_t_1_Loc == 3, int32_t_2_Loc == 3, int32_t_3_Loc == 7 */
         Proc_8 (Arr_1_Glob, Arr_2_Glob, int32_t_1_Loc, int32_t_3_Loc);
         /* int32_t_Glob == 5 */
         Proc_1 (Ptr_Glob);
         for (Ch_Index = 'A'; Ch_Index <= Ch_2_Glob; ++Ch_Index)
         /* loop body executed twice */
         {
             if (Enum_Loc == Func_1 (Ch_Index, 'C'))
             /* then, not executed */
             {
                 Proc_6 (Ident_1, &Enum_Loc);
                 strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
                 int32_t_2_Loc = Run_Index;
                 int32_t_Glob = Run_Index;
             }
         }
         /* int32_t_1_Loc == 3, int32_t_2_Loc == 3, int32_t_3_Loc == 7 */
         int32_t_2_Loc = int32_t_2_Loc * int32_t_1_Loc;
         int32_t_1_Loc = int32_t_2_Loc / int32_t_3_Loc;
         int32_t_2_Loc = 7 * (int32_t_2_Loc - int32_t_3_Loc) - int32_t_1_Loc;
         /* int32_t_1_Loc == 1, int32_t_2_Loc == 13, int32_t_3_Loc == 7 */
         Proc_2 (&int32_t_1_Loc);
         /* int32_t_1_Loc == 5 */
    }   /* loop "for Run_Index" */
    numRun++;
}

void Proc_1 (REG Rec_Pointer Ptr_Val_Par)
{
    REG Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;
                                            /* == Ptr_Glob_Next */
    /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
    /* corresponds to "rename" in Ada, "with" in Pascal           */
    
    structassign (*Ptr_Val_Par->Ptr_Comp, *Ptr_Glob);
    Ptr_Val_Par->variant.var_1.Int_Comp = 5;
    Next_Record->variant.var_1.Int_Comp
            = Ptr_Val_Par->variant.var_1.Int_Comp;
    Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
    Proc_3 (&Next_Record->Ptr_Comp);
        /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp
                            == Ptr_Glob->Ptr_Comp */
    if (Next_Record->Discr == Ident_1)
        /* then, executed */
    {
        Next_Record->variant.var_1.Int_Comp = 6;
        Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp,
            &Next_Record->variant.var_1.Enum_Comp);
        Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
        Proc_7 (Next_Record->variant.var_1.Int_Comp, 10,
            &Next_Record->variant.var_1.Int_Comp);
    }
    else /* not executed */
    {
        structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
    }
} /* Proc_1 */

void Proc_2 (One_Fifty *int32_t_Par_Ref)
{
    One_Fifty  int32_t_Loc;
    Enumeration   Enum_Loc = Ident_2;
    
    int32_t_Loc = *int32_t_Par_Ref + 10;
    do /* executed once */
        if (Ch_1_Glob == 'A')
        {
            int32_t_Loc -= 1;
            *int32_t_Par_Ref = int32_t_Loc - int32_t_Glob;
            Enum_Loc = Ident_1;
        } /* if */
    while (Enum_Loc != Ident_1); /* true */
} /* Proc_2 */


void Proc_3 (Rec_Pointer *Ptr_Ref_Par)
{
    if (Ptr_Glob != Null)
        /* then, executed */
        *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
    Proc_7 (10, int32_t_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
} /* Proc_3 */

void Proc_4 ()
{
    Boolean Bool_Loc;
    
    Bool_Loc = Ch_1_Glob == 'A';
    Bool_Glob = Bool_Loc | Bool_Glob;
    Ch_2_Glob = 'B';
} /* Proc_4 */

void Proc_5 ()
{
    Ch_1_Glob = 'A';
    Bool_Glob = false;
} /* Proc_5 */

void Proc_6 (Enumeration Enum_Val_Par, Enumeration *Enum_Ref_Par)
{
    *Enum_Ref_Par = Enum_Val_Par;
    if (! Func_3 (Enum_Val_Par))
        /* then, not executed */
        *Enum_Ref_Par = Ident_4;
    switch (Enum_Val_Par)
    {
        case Ident_1: 
            *Enum_Ref_Par = Ident_1;
            break;
        case Ident_2: 
            if (int32_t_Glob > 100)
                *Enum_Ref_Par = Ident_1;
            else *Enum_Ref_Par = Ident_4;
                break;
        case Ident_3: /* executed */
            *Enum_Ref_Par = Ident_2;
            break;
        case Ident_4:
            break;
        case Ident_5: 
            *Enum_Ref_Par = Ident_3;
            break;
    } /* switch */
} /* Proc_6 */
 
 
 void Proc_7 (One_Fifty int32_t_1_Par_Val, One_Fifty int32_t_2_Par_Val,
              One_Fifty *int32_t_Par_Ref)
{
    One_Fifty int32_t_Loc;
    
    int32_t_Loc = int32_t_1_Par_Val + 2;
    *int32_t_Par_Ref = int32_t_2_Par_Val + int32_t_Loc;
} /* Proc_7 */
 
 
 void Proc_8 (Arr_1_Dim Arr_1_Par_Ref, Arr_2_Dim Arr_2_Par_Ref,
             int32_t int32_t_1_Par_Val, int32_t int32_t_2_Par_Val)
{
      REG One_Fifty int32_t_Index;
      REG One_Fifty int32_t_Loc;

      int32_t_Loc = int32_t_1_Par_Val + 5;
      Arr_1_Par_Ref [int32_t_Loc] = int32_t_2_Par_Val;
      Arr_1_Par_Ref [int32_t_Loc+1] = Arr_1_Par_Ref [int32_t_Loc];
      Arr_1_Par_Ref [int32_t_Loc+30] = int32_t_Loc;
      for (int32_t_Index = int32_t_Loc; int32_t_Index <= int32_t_Loc+1; ++int32_t_Index)
        Arr_2_Par_Ref [int32_t_Loc] [int32_t_Index] = int32_t_Loc;
      Arr_2_Par_Ref [int32_t_Loc] [int32_t_Loc-1] += 1;
      Arr_2_Par_Ref [int32_t_Loc+20] [int32_t_Loc] = Arr_1_Par_Ref [int32_t_Loc];
      int32_t_Glob = 5;
} /* Proc_8 */
 
 
Enumeration Func_1 (Capital_Letter Ch_1_Par_Val,
                                          Capital_Letter Ch_2_Par_Val)
{
    Capital_Letter        Ch_1_Loc;
    Capital_Letter        Ch_2_Loc;
    
    Ch_1_Loc = Ch_1_Par_Val;
    Ch_2_Loc = Ch_1_Loc;
    if (Ch_2_Loc != Ch_2_Par_Val)
        /* then, executed */
        return (Ident_1);
    else  /* not executed */
    {
        Ch_1_Glob = Ch_1_Loc;
        return (Ident_2);
    }
} /* Func_1 */

Boolean Func_2 (Str_30 Str_1_Par_Ref, Str_30 Str_2_Par_Ref)
{
    REG One_Thirty        int32_t_Loc;
        Capital_Letter    Ch_Loc;
    
    int32_t_Loc = 2;
    while (int32_t_Loc <= 2) /* loop body executed once */
        if (Func_1 (Str_1_Par_Ref[int32_t_Loc],
                    Str_2_Par_Ref[int32_t_Loc+1]) == Ident_1)
        /* then, executed */
        {
        Ch_Loc = 'A';
        int32_t_Loc += 1;
        } /* if, while */
    if (Ch_Loc >= 'W' && Ch_Loc < 'Z')
        /* then, not executed */
        int32_t_Loc = 7;
    if (Ch_Loc == 'R')
        /* then, not executed */
        return (true);
    else /* executed */
    {
        if (strcmp (Str_1_Par_Ref, Str_2_Par_Ref) > 0)
        /* then, not executed */
        {
        int32_t_Loc += 7;
        int32_t_Glob = int32_t_Loc;
        return (true);
        }
        else /* executed */
        return (false);
    } /* if Ch_Loc */
} /* Func_2 */


Boolean Func_3 (Enumeration Enum_Par_Val)
{
    Enumeration Enum_Loc;
    
    Enum_Loc = Enum_Par_Val;
    if (Enum_Loc == Ident_3)
        /* then, executed */
        return (true);
    else /* not executed */
        return (false);
} /* Func_3 */
