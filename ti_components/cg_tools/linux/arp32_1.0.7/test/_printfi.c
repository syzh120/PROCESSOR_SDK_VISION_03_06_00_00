/*****************************************************************************/
/*  _PRINTFI.C v1.0.7                                                        */
/*                                                                           */
/* Copyright (c) 1995-2015 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/*    This file contains the main routines that all six variations of the    */
/*    printf function use.  The main function in the file is _printfi,       */
/*    and the other functions here are called by it.                         */
/*                                                                           */
/* FUNCTIONS:                                                                */
/*    _printfi       -  Perform the main printf routine                      */
/*    _pproc_fflags  -  Process the format flags for a conversion            */
/*    _pproc_fwp     -  Convert field width and precision into numbers       */
/*    _pproc_str     -  Process the string (%s) conversion                   */
/*    _setfield      -  Performs conversions when the '%' is encountered     */
/*    _pproc_fge     -  Process the conversion for f, g, G, e, and E         */
/*    _pconv_f       -  Perform the %f conversion                            */
/*    _pconv_e       -  Perform the %e conversion                            */
/*    _pconv_g       -  Perform the %g conversion                            */
/*    _fcpy          -  Copy the fraction part of a float to a string        */
/*    _ecpy          -  Copy the "E+xx" part of a float to a string          */
/*    _mcpy          -  Copy the whole number part of a float to a string    */
/*    _pproc_diouxp  -  Process the conversion for d, i, o, u, x, and p      */
/*    _getarg_diouxp -  Get the argument for d, i, o, u, x, or p conversion  */
/*    _ltostr        -  Convert an integer to a string of up to base 16      */
/*    _div           -  Divide two integers                                  */
/*                                                                           */
/* Note:  If NOFLOAT is defined at compile time, this file will be compiled  */
/*        without floating point support.                                    */
/*****************************************************************************/
#include <stdio.h>
#include <format.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>

#define HEX_CONV(conv) (conv == 'x' || conv == 'X' || conv == 'p')

#define SIGNED_CONV(conv) (conv != 'u' && conv != 'o' && !HEX_CONV(conv))

enum { NO_FLAG, MINUS_FLAG, ISNAN_FLAG, ISPINF_FLAG, ISNINF_FLAG };

extern _CODE_ACCESS char *memccpy(char *dest, const char *src, int ch,
				  int count);

#if !defined(NOFLOAT) && !defined(MINIMAL)
#define _PRINTFI _printfi
#elif defined(NOFLOAT)
#define _PRINTFI _printfi_nofloat
#elif defined(MINIMAL)
#define _PRINTFI _printfi_minimal
#endif

extern _CODE_ACCESS int _PRINTFI(char **_format, va_list _ap, void *_op,
                                 int (*_outc)(char, void *), 
				 int (*_outs)(char *, void *, int));

#if !defined(MINIMAL)
static void _pproc_fflags(_PFIELD *pfield, char **it);
static void _pproc_fwp(_PFIELD *pfield, char **it, va_list *_ap);
#endif
static void _pproc_str(_PFIELD *pfield, void *_op, va_list *_ap, int *count,
                       int (*_outc)(char, void *));
static int _setfield(char *fld, _PFIELD *pfield, va_list *_ap);

#if !defined(NOFLOAT) && !defined(MINIMAL)
static char *fcvt(char *buf, long double value,int ndigit,int *decpt,int *sign);
static char *ecvt(char *buf, long double value,int ndigit,int *decpt,int *sign);
static void _pproc_fge(_PFIELD *pfield, int *flags, char **a_it, va_list *_ap);
static void _pconv_f(long double cvt, _PFIELD *pfield, char **a_it);
static void _pconv_e(long double cvt, _PFIELD *pfield, char **a_it);
static void _pconv_g(long double cvt, _PFIELD *pfield, char **a_it);

static char *_fcpy(const char *tmpbuf, int dpt, int precision, char **a_it);
static char *_ecpy(int exp, char letter, char **a_it);
static char *_mcpy(const char *tmpbuf, int dpt, int putdec, char **a_it);
#endif

/*****************************************************************************/
/* When "MINIMAL" is defined, use "unsigned int" instead of "uintmax_t" as   */
/* the largest integer type printf will handle.  In MINIMAL mode, we don't   */
/* allow format specifiers for "long" or "long long", so we don't need       */
/* uintmax_t in the helper functions.  Using "unsigned int" allows us to     */
/* avoid having the _div function drag in the "long" and "long long"         */
/* division helper functions, which would never be used.                     */
/*****************************************************************************/
#if defined(MINIMAL)
typedef          int  big_t;
typedef unsigned int ubig_t;
#else
typedef  intmax_t  big_t;
typedef uintmax_t ubig_t;
#endif

static int _pproc_diouxp(_PFIELD *pfield, int *minus_flag, char **a_it,
                         va_list *_ap);
static ubig_t _getarg_diouxp(_PFIELD *pfield, va_list *_ap);
static int _ltostr(ubig_t cvt, int base, char conv, char **a_it);
static ubig_t _div(ubig_t cvt, int base);

/*****************************************************************************/
/* _PRINTFI -  Perform the main printf routine                               */
/*                                                                           */
/*    This function processes the format string.  It copies the format       */
/*    string into the result string until a '%' is encountered, where any    */
/*    flags, the field width, the precision, and the type of conversion are  */
/*    read in, stored in a structure called PFIELD, and passed to _SETFIELD, */
/*    where the actual conversion is processed.  This function returns       */
/*    the number of characters output.                                       */
/*                                                                           */
/*    For multi-threaded applications, when this function is called on       */
/*    behalf of fprintf, printf, vfprintf, or vprintf, the call site should  */
/*    be enclosed in a critical section that guarantees single-threaded      */
/*    access to the __TI_LOCK_FILE_TBL resources (_ftable[], _ft_end, and    */
/*    _tmpnams[]).                                                           */
/*                                                                           */
/*****************************************************************************/
_CODE_ACCESS int _PRINTFI(char **_format, va_list _ap, void *_op,
                          int (*_outc)(char, void *), 
			  int (*_outs)(char *, void *, int))
{
   /*------------------------------------------------------------------------*/
   /* Local Variables                                                        */
   /*                                                                        */
   /*    *end     -  A pointer to the end of the format string               */
   /*    *pfield  -  A pointer to a structure _PFIELD, which stores all of   */
   /*                flags and parameters needed to perform a conversion.    */
   /*------------------------------------------------------------------------*/
   char     *end           =  *_format + strlen(*_format);
   int      count          =  0;
   _PFIELD  pfield;

   /*------------------------------------------------------------------------*/
   /* Iterate through the format string until the end of it is reached.      */
   /*------------------------------------------------------------------------*/
   while(*_format < end)
   {
      /*---------------------------------------------------------------------*/
      /* Initialize PFIELD.                                                  */
      /*---------------------------------------------------------------------*/
      pfield.flags     = 0;
      pfield.conv      = 0;
#if !defined(MINIMAL)
      pfield.fwidth    = 0;
      pfield.precision = -1;
#endif

      /*---------------------------------------------------------------------*/
      /* Copy the format string directly to the target string until a '%'    */
      /* is encountered.                                                     */
      /*---------------------------------------------------------------------*/
      for(; **_format != '%' && **_format != '\0'; 
          _outc(*((*_format)++), _op), count++);

      /*---------------------------------------------------------------------*/
      /* If the end of the format string has been reached, break out of the  */
      /* while loop.                                                         */
      /*---------------------------------------------------------------------*/
      if(! (**_format)) break;

      (*_format)++;                   /* Skip to the character after the '%' */

#if !defined(MINIMAL)
      /*---------------------------------------------------------------------*/
      /* Process the flags immediately after the '%'.                        */
      /*---------------------------------------------------------------------*/
      _pproc_fflags(&pfield, _format);

      /*---------------------------------------------------------------------*/
      /* Convert the field width and precision into numbers.                 */
      /*---------------------------------------------------------------------*/
      _pproc_fwp(&pfield, _format, &_ap);
 
      /*---------------------------------------------------------------------*/
      /* If the h, l, or L flag was specified, set the corresponding flag    */
      /* in pfield.                                                          */
      /*---------------------------------------------------------------------*/
      switch (**_format)
      {
#if !defined(NOFLOAT)
	  case 'L': _SET(&pfield, _MFLD); (*_format)++; break;
#endif
	  case 'h':
	  {
	      (*_format)++; 
	      if (**_format == 'h') { _SET(&pfield, _MFHH); (*_format)++; }
	      else _SET(&pfield, _MFH);
	      break;
	  }
	  case 'l':
	  {
	      (*_format)++; 
	      if (**_format == 'l') { _SET(&pfield, _MFLL); (*_format)++; }
	      else _SET(&pfield, _MFL);
              break;
	  }
#ifdef __TI_INT40_T__
          case 'I':
          {
             if ((*(*_format+1)) == '4' && (*(*_format+2)) == '0')
             { _SET(&pfield, _MFI40); (*_format)+=3; }
             break;
          }
#endif
      }
#endif

      /*---------------------------------------------------------------------*/
      /* Set the conversion character in pfield.                             */
      /*---------------------------------------------------------------------*/
      pfield.conv = *((*_format)++);

#if !defined(MINIMAL)
      /*---------------------------------------------------------------------*/
      /* If 'n' is the conversion specifier, process it in this function,    */
      /* since it is the only one that makes no conversions.  It just stores */
      /* the number of characters printed so far into the next argument.     */
      /* Otherwise, call _SETFIELD which performs the conversion.            */
      /*---------------------------------------------------------------------*/
      if(pfield.conv == 'n')
         switch (pfield.flags & (_MFLL | _MFL | _MFH | _MFHH | _MFI40))
         {
#ifdef LLONG_MAX
                           /* The 'll' flag was specified */
            case _MFLL  :  *(va_arg(_ap, long long*)) = (long long)count;
                           break;
#endif
#ifdef __TI_INT40_T__
                           /* The 'I40' flag was specified */
            case _MFI40 :  *(va_arg(_ap, __int40_t *)) = (__int40_t)count;
                           break;
#endif
                           /* The 'l' flag was specified */
            case _MFL   :  *(va_arg(_ap, long*)) = (long)count;
                           break;

                           /* The 'h' flag was specified */
            case _MFH   :  *(va_arg(_ap, short*)) = (short)count;
                           break;

                           /* The 'hh' flag was specified */
            case _MFHH  :  *(va_arg(_ap, char*)) = (char)count;
                           break;

            default     :  *(va_arg(_ap, int*)) = (int)count;
                           break;

         }
      else 
#endif
      if(pfield.conv == 's') 
         _pproc_str(&pfield, _op, &_ap, &count, _outc);   
      else
      {
         /*------------------------------------------------------------------*/
         /* Append the converted string to the result string, and reposition */
         /* its iterator, it2.                                               */
         /*------------------------------------------------------------------*/
         char fld[FORMAT_CONVERSION_BUFSIZE];
	 int  length = 0;
         length = _setfield(fld, &pfield, &_ap);
         count += _outs(fld, _op, length);
      }
   }

   return (count);
}


#if !defined(MINIMAL)
/*****************************************************************************/
/* _PPROC_FFLAGS   -  Process the format flags for a conversion              */
/*                                                                           */
/*    This function takes the flags directly after the '%' and stores them   */
/*    in the _PFIELD structure PFIELD for later reference.                   */
/*                                                                           */
/*****************************************************************************/
static void _pproc_fflags(_PFIELD *pfield, char **it)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*------------------------------------------------------------------------*/
   int flags_done = 0;

   /*---------------------------------------------------------------------*/
   /* Read in all of the flags associated with this conversion, and set   */
   /* the corresponding flags in the PFIELD structure.                    */
   /*---------------------------------------------------------------------*/
   while(! flags_done)
      switch (**it)
      {
         case '-' :  _SET(pfield, _PFMINUS);
                     (*it)++;
                     break;   

         case '+' :  _SET(pfield, _PFPLUS);
                     (*it)++;
                     break;

         case ' ' :  _SET(pfield, _PFSPACE);
                     (*it)++;
                     break;

         case '#' :  _SET(pfield, _PFPOUND);
                     (*it)++;
                     break;

         case '0' :  _SET(pfield, _PFZERO);
                     (*it)++;
                     break;

         default  :  flags_done = 1;
      }

   return;
}


/*****************************************************************************/
/* _PPROC_FWP   -  Convert the field width and precision from the format     */
/*                 string into numbers.                                      */
/*                                                                           */
/*    This function reads the field and precision out of the format string   */
/*    and converts them into numbers that will be stored in the _PFIELD      */
/*    structure pointed to by PFIELD.  They will be needed for future        */
/*    reference.                                                             */
/*                                                                           */
/*****************************************************************************/
static void _pproc_fwp(_PFIELD *pfield, char **it, va_list *_ap)
{
   char tmpstr[10];
   char *tmpptr;

   /*------------------------------------------------------------------------*/
   /* If a '*' was given for the field width, use the next argument as       */
   /* the field width for the conversion.  Otherwise, copy the following     */
   /* numerical characters into a temporary string, and convert that         */
   /* string into an integer, which will be used for the field width.        */
   /*------------------------------------------------------------------------*/
   if(**it == '*')
   {
      pfield->fwidth = va_arg(*_ap, int);

      /*---------------------------------------------------------------------*/
      /* If the argument given for the field width is negative, treat it as  */
      /* if the '-' flag was used, and the field width was positive.         */
      /*---------------------------------------------------------------------*/
      if(pfield->fwidth < 0) 
      {
         pfield->fwidth = -(pfield->fwidth);
         _SET(pfield, _PFMINUS);
      }

      (*it)++;
   }
   else
   {
      /*---------------------------------------------------------------------*/
      /* Initialize the temporary string and iterator that will hold the     */
      /* field width temporarily.                                            */
      /*---------------------------------------------------------------------*/
      tmpptr = tmpstr;
      memset(tmpptr, '\0', 10);

      while((**it >= '0') && (**it <= '9')) *(tmpptr++) = *((*it)++);

      if(*tmpstr != '\0') pfield->fwidth = atoi(tmpstr);
   }

   /*------------------------------------------------------------------------*/
   /* If a '.' appears as the next character, process the following          */
   /* characters as a precision.                                             */
   /*------------------------------------------------------------------------*/
   if(**it == '.')
   {
      (*it)++;

      /*---------------------------------------------------------------------*/
      /* If a '*' was given for the precision, use the next argument as      */
      /* the precision for the conversion.  Otherwise, copy the following    */
      /* numerical characters into a temporary string, and convert that      */
      /* string into an integer, which will be used for the precision.       */
      /*---------------------------------------------------------------------*/
      if(**it == '*')
      {
         pfield->precision = va_arg(*_ap, int);
         (*it)++;
      }
      else
      {
         /*------------------------------------------------------------------*/
         /* Initialize the temporary string and iterator that will hold      */
         /* the field width temporarily.                                     */
         /*------------------------------------------------------------------*/
         tmpptr = tmpstr;
         memset(tmpptr, '\0', 10);

         while((**it >= '0') && (**it <= '9'))  *(tmpptr++) = *((*it)++);

         if(*tmpstr != '\0') pfield->precision = atoi(tmpstr);
         else                pfield->precision = 0;
      }
   }
   return;
}
#endif


/*****************************************************************************/
/* _PPROC_STR  -  Processes the string conversion (%s)                       */
/*                                                                           */
/*    This function places all or a portion of the input string into the     */
/*    the temporary string.  It returns a zero, unless the input string had  */
/*    a length of zero.  In this case, a one is returned.                    */
/*                                                                           */
/*****************************************************************************/
static void _pproc_str(_PFIELD *pfield, void *_op, va_list *_ap, int *count,
                       int (*_outc)(char, void *))
{
    /*------------------------------------------------------------------------*/
    /* Local variables                                                        */
    /*------------------------------------------------------------------------*/
    char *strbuf;
    int   buflen;
    int   i;
#if !defined(MINIMAL)
    int   len;
#endif

    /*------------------------------------------------------------------------*/
    /* Get the next argument.                                                 */
    /*------------------------------------------------------------------------*/
    strbuf = va_arg(*_ap, char*);

    /*------------------------------------------------------------------------*/
    /* Handle NULL strings.                                                   */
    /*------------------------------------------------------------------------*/
    if (strbuf == NULL)
    {
       _outc('\0', _op);
       return;
    }

#if !defined(MINIMAL)
    buflen = (pfield->precision >= 0 && pfield->precision < strlen(strbuf)) ?
    pfield->precision : strlen(strbuf);
    len = (pfield->fwidth > buflen) ? pfield->fwidth : buflen;
    *count += len;

    if (buflen < len && !_STCHK(pfield, _PFMINUS))
        for (i = 0; i < len - buflen; i++)
            _outc(' ', _op);

    for (i = 0; i < buflen; i++)
        _outc(*strbuf++, _op);   

    if (buflen < len && _STCHK(pfield, _PFMINUS))
        for (i = 0; i < len - buflen; i++)
            _outc(' ', _op);
#else
    buflen = strlen(strbuf);
    *count += buflen;

    for (i = 0; i < buflen; i++)
        _outc(*strbuf++, _op);   
#endif
}


/*****************************************************************************/
/* _SETFIELD   -  Performs conversions when the '%' is encountered           */
/*                                                                           */
/*    This function takes pfield, and calls the appropriate processing       */
/*    function for the conversion required in the _PFIELD structure.  It     */
/*    returns a pointer to the result string.                                */
/*                                                                           */
/*****************************************************************************/
static int _setfield(char *fld, _PFIELD *pfield, va_list *_ap)
{
   /*------------------------------------------------------------------------*/
   /* Local variable declarations, and a description of their use            */
   /*                                                                        */
   /*    FLD is a temporary string that will hold the conversion.  F_START   */
   /*    will be a pointer to the beginning of the field, and if a           */
   /*    field width was specified, F_END will be a pointer to the end of    */
   /*    the field.  This designated field is located at the beginning of    */
   /*    the string FLD.   A_END is a pointer to the end of the string FLD,  */
   /*    and this is where the primary conversion will take place.  Using    */
   /*    A_IT, an iterator beginning at the end of FLD, the number will be   */
   /*    written one digit at a time starting with the rightmost digit.      */
   /*    Using the pointer WHERE, the number in string form will be moved    */
   /*    to its appropriate place within the field after making adjustments  */
   /*    called for by various flags in the format specification (a minus    */
   /*    sign, leading zeros, etc.).  The string FLD will then be returned.  */
   /*                                                                        */
   /*    MINUS_FLAG is exactly what it says ( = 1 if number is negative).    */
   /*                                                                        */
   /*------------------------------------------------------------------------*/
   char *f_start   =  (char *)fld;
#if !defined(MINIMAL)
   char *f_end     =  f_start + pfield->fwidth;
   int  plus_flag  = 0;
#else
   char *f_end     =  f_start;
#endif
   char *a_end     =  f_start + FORMAT_CONVERSION_BUFSIZE -1; 
   char *a_it      =  a_end;
   char *where;
   int  minus_flag = 0;
   int  flags = NO_FLAG;
   char temp_char = 0;
   int  str_terminator = 0;
  
   /*------------------------------------------------------------------------*/
   /* Initialize the temporary string.  Then, since we are working from      */
   /* right to left, begin with the NULL character.                          */
   /*------------------------------------------------------------------------*/
   memset(fld, ' ', FORMAT_CONVERSION_BUFSIZE);
   *(a_it--) = '\0'; 

   /*------------------------------------------------------------------------*/
   /* Call the appropriate processing function.                              */
   /*------------------------------------------------------------------------*/
   switch(pfield->conv)
   {
      case 'd' :
#if !defined (MINIMAL)
      case 'i' :
      case 'u' :
      case 'X' :  
      case 'p' :  
#endif
      case 'o' :
      case 'x' :  _pproc_diouxp(pfield, &minus_flag, &a_it, _ap);
                  break;  

#if !defined(NOFLOAT) && !defined(MINIMAL)
      case 'g' :  
      case 'G' : 
      case 'e' :
      case 'E' :
      case 'f' :
      case 'F' :  _pproc_fge(pfield, &flags, &a_it, _ap);
                  break;
#endif
  
      case 'c' :  temp_char = va_arg(*_ap, int);
                  /*----------------------------------------------------------*/
                  /* Set str_terminator to 1 if '\0' is seen.                 */
                  /*----------------------------------------------------------*/
		  str_terminator = (temp_char == '\0')? 1:0;
                  *(a_it--) = temp_char;
#if !defined(MINIMAL)
                  _UNSET(pfield, _PFPLUS);
#endif
                  break;
      case '%' :  strcpy(f_start, "%");  
	 	  /*----------------------------------------------------------*/
	          /* strcpy() will append terminating null '\0' to the end,   */
	          /* so string length is 1.                                   */
                  /*----------------------------------------------------------*/
	          return 1;
   }

   /*------------------------------------------------------------------------*/
   /* Potentially print a sign indicator, but only for signed conversions.   */
   /* The '+' and ' ' flags are only valid for signed conversions.           */
   /*------------------------------------------------------------------------*/
#if !defined(MINIMAL)
   if (SIGNED_CONV(pfield->conv))
#endif
       switch (flags)
       {
           case MINUS_FLAG: minus_flag = 1;
           case NO_FLAG:
           {
#if !defined(MINIMAL)
               plus_flag = _STCHK(pfield, _PFPLUS);
#endif
	   
               /*------------------------------------------------------------*/
               /* If the number was negative, or the '+' flag was used,      */
               /* insert the sign.                                           */
               /*------------------------------------------------------------*/
               if (minus_flag) *(a_it--) = '-';
#if !defined(MINIMAL)
               else if (plus_flag) *(a_it--) = '+';
	   
               /*------------------------------------------------------------*/
               /* If the number was positive, the '+' flag was not used, and */
               /* the ' ' flag was used, insert a space.                     */
               /*------------------------------------------------------------*/
               if(! minus_flag && ! plus_flag && _STCHK(pfield, _PFSPACE))
                   *(a_it--) = ' ';
#endif
           }
       }

   /*------------------------------------------------------------------------*/
   /* If the '-' flag was used or the resulting string is larger than the    */
   /* field, left justify the result in the array.  Otherwise right-justify  */
   /* it.                                                                    */
   /*------------------------------------------------------------------------*/
#if !defined(MINIMAL)
   where = (_STCHK(pfield, _PFMINUS) ||
           ((a_end - a_it) > pfield->fwidth)) ? f_start :
           (f_end - (a_end - a_it)+1);
#else
   where = (((a_end - a_it) > 0)) ? f_start :
           (f_end - (a_end - a_it)+1);
#endif

   a_it = (char *)memccpy(where, a_it+1, '\0', FORMAT_CONVERSION_BUFSIZE);

   /*------------------------------------------------------------------------*/
   /* In case of (..."%c", '\0'...), the above memccpy() will miss the TRUE  */
   /* '\0', treating it as a terminator. Here we need to add it back.        */
   /*------------------------------------------------------------------------*/
   if (str_terminator)
	*(a_it++) = '\0';

   /*------------------------------------------------------------------------*/
   /* If a resulting left-justified string is smaller than the field width,  */
   /* move the terminating NULL character to the end of the field.           */
   /*------------------------------------------------------------------------*/
   if(a_it <= f_end)
   {
      memset(a_it - 1, ' ', f_end - a_it + 1);
      *f_end = '\0';
   }

#if !defined(MINIMAL)
   /*------------------------------------------------------------------------*/
   /* If the '0' flag was used, and the resulting string is right-justified, */
   /* fill in the leading zeros.                                             */
   /*------------------------------------------------------------------------*/
   if (_STCHK(pfield, _PFZERO))
   {
       /*--------------------------------------------------------------------*/
       /* Skip if no '0' were inserted.  If we didn't skip, the swap would   */
       /* mistakenly clobber the sign or base indicator.                     */
       /*--------------------------------------------------------------------*/
       if (where != f_start)
       {
           memset(f_start, '0', (where - f_start));
         
           /*----------------------------------------------------------------*/
           /* Those '0's were supposed to go after any indication of sign or */
           /* base.  Move the zeros to the right of such indication.         */
           /*----------------------------------------------------------------*/
           if (HEX_CONV(pfield->conv))
           {
               if (_STCHK(pfield, _PFPOUND))
               {
                   /*--------------------------------------------------------*/
                   /* Swap the 'x' or 'X' and the first zero.                */
                   /*--------------------------------------------------------*/
                   *(f_start+1) = *(where+1);
                   *(where+1) = '0';
               }
           }
           /*----------------------------------------------------------------*/
           /* The sign-indicating flags ('+' and ' ') are only valid for     */
           /* signed conversions, and are ignored for unsigned conversions.  */
           /*----------------------------------------------------------------*/
           else if (minus_flag || plus_flag || _STCHK(pfield, _PFSPACE))
           {
               /*------------------------------------------------------------*/
               /* Swap the sign indicator and the first zero                 */
               /*------------------------------------------------------------*/
               *f_start = *where;
               *where = '0';
           }
       }
   }
   else
#endif
      memset(f_start, ' ', (where - f_start));

   /*------------------------------------------------------------------------*/
   /* Return the length of the result string. Because strlen() depends on    */
   /* '\0' to terminate, in case of (...%c,'\0'...), we need to count one    */
   /* more character for length.                                             */
   /*------------------------------------------------------------------------*/
   return strlen(fld)+str_terminator;                  
}


#if !defined(NOFLOAT) && !defined(MINIMAL)
/****************************************************************************/
/* THIS FUNCTION IS NON-STANDARD AND IS PROVIDED ONLY AS A BUILDING BLOCK   */
/* FOR PRINTF.                                                              */
/****************************************************************************/
static char *fcvt(char *out, long double value,int ndigit, int *decpt,int *sign)
{
    int   digits = 0;                  /* NUMBER OF DIGITS BEFORE .       */
    char *pos    = out + 1;     
    int   temp;

    out[0] = '0';                      /* JUST IN CASE WE ROUND.          */
    ndigit++;                          /* DO ONE EXTRA DIGIT FOR ROUNDING */

    /*--------------------------------------------------------------------*/
    /* PERFORM PRESCALING - MAKE SURE NUMBER HAS INTEGRAL WHOLE PART      */
    /*--------------------------------------------------------------------*/
    if (*sign = (value < 0)) value = -value;
    while (value > 0x7FFFFFFF) { value /= 10; digits++; }
    while (value && value < 1) { value *= 10; digits--; }

    /*--------------------------------------------------------------------*/
    /* WRITE OUT INTEGRAL PART OF NUMBER.                                 */
    /*--------------------------------------------------------------------*/
    pos   += temp    = ltoa((long)value, pos);
    *decpt = digits + temp; 

    ndigit += digits;

    /*--------------------------------------------------------------------*/
    /* WRITE OUT FRACTIONAL PART OF NUMBER                                */
    /*--------------------------------------------------------------------*/
    if (ndigit > 0) do
    {
         value -= (long)value;
         *pos++ = (int)(value *= 10.0) + '0';
    }
    while (--ndigit);

    /*--------------------------------------------------------------------*/
    /* PERFORM ROUNDING.  NOTE THAT pos IS CURRENTLY POINTING AT AN EXTRA */
    /* DIGIT WHICH WAS CONVERTED FOR THIS PURPOSE.                        */
    /*--------------------------------------------------------------------*/
    if (*--pos >= '5')
    {
	char *ptr = pos;
	while ((*--ptr += 1) > '9') *ptr = '0';
	if (ptr == out) 
        {
	   if (pos > out) *pos   = 0;
	   else           out[1] = 0;

           *decpt += 1;
           return out;
        }
    }
	
    *pos = 0;
    return out + 1;
}


/****************************************************************************/
/* THIS FUNCTION IS NON-STANDARD AND IS PROVIDED ONLY AS A BUILDING BLOCK   */
/* FOR PRINTF.                                                              */
/****************************************************************************/
static char *ecvt(char *out, long double value, int ndigit,int *decpt,int *sign)
{
    int   digits = 0;                  /* NUMBER OF DIGITS BEFORE .       */
    char *pos    = out + 1;     
    int   temp;

    out[0] = '0';                      /* JUST IN CASE WE ROUND.          */
    ndigit++;                          /* DO ONE EXTRA DIGIT FOR ROUNDING */

    /*--------------------------------------------------------------------*/
    /* PERFORM PRESCALING - MAKE SURE NUMBER HAS INTEGRAL WHOLE PART      */
    /*--------------------------------------------------------------------*/
    if (*sign = (value < 0)) value = -value;
    while (value > 0x7FFFFFFF) { value /= 10; digits++; }
    while (value && value < 1) { value *= 10; digits--; }

    /*--------------------------------------------------------------------*/
    /* WRITE OUT INTEGRAL PART OF NUMBER.                                 */
    /*--------------------------------------------------------------------*/
    pos    += temp = ltoa((long)value, pos);
    *decpt  = digits + temp;

    /*--------------------------------------------------------------------*/
    /* WRITE OUT FRACTIONAL PART OF NUMBER                                */
    /*--------------------------------------------------------------------*/
    if (temp >= ndigit) 
	pos = out + ndigit + 1;
    else if ((ndigit -= temp) > 0) do
    {
        value -= (long)value;
        *pos++ = (int)(value *= 10.0) + '0';
    } 
    while (--ndigit);

    /*--------------------------------------------------------------------*/
    /* PERFORM ROUNDING.  NOTE THAT pos IS CURRENTLY POINTING AT AN EXTRA */
    /* DIGIT WHICH WAS CONVERTED FOR THIS PURPOSE.                        */
    /*--------------------------------------------------------------------*/
    if (*--pos >= '5')
    {
	char *ptr = pos;
	while ((*--ptr += 1) > '9') *ptr = '0';
	if (ptr == out) { *--pos = 0; *decpt += 1; return out; }
    }
	
    *pos = 0;
    return out + 1;
}

/*****************************************************************************/
/* _PPPROC_FGE   -  Process the conversion for f, g, G, e, and E             */
/*                                                                           */
/*    This function takes the structure PFIELD, which contains all of the    */
/*    flags and parameters to process the conversion, and it does this       */
/*    conversion, and stores the result in the string pointed to by          */
/*    *A_IT.                                                                 */
/*****************************************************************************/
static void _pproc_fge(_PFIELD *pfield, int *flags,
                       char **a_it, va_list *_ap)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*------------------------------------------------------------------------*/
   long double cvt =  0;
#if defined(isnan) && defined(isinf)
   int is_cap = pfield->conv == toupper(pfield->conv);
#endif

   /*------------------------------------------------------------------------*/
   /* Determine what kind of argument is coming next, and read it into CVT.  */
   /*------------------------------------------------------------------------*/
   switch(_STCHK(pfield, _MFLD))
   {
      case  0  :  cvt = (double)va_arg((*_ap), double);
                  break;

      default  :  cvt = va_arg((*_ap), long double);

   }

   /*------------------------------------------------------------------------*/
   /* If the value is a special IEEE representation, return a flag           */
   /*------------------------------------------------------------------------*/
#if defined(isnan) && defined(isinf)
   if (isnan(cvt))
   {
       *((*a_it)--) = is_cap ? 'N' : 'n';
       *((*a_it)--) = is_cap ? 'A' : 'a';
       *((*a_it)--) = is_cap ? 'N' : 'n';
       *flags = ISNAN_FLAG;
       return;
   }
   else if (isinf(cvt))
       if (cvt < 0)
       {
	   *((*a_it)--) = is_cap ? 'F' : 'f'; 
	   *((*a_it)--) = is_cap ? 'N' : 'n'; 
	   *((*a_it)--) = is_cap ? 'I' : 'i'; 
	   *((*a_it)--) = '-'; 
	   *flags = ISNINF_FLAG;
	   return;
       }
       else
       {
	   *((*a_it)--) = is_cap ? 'F' : 'f'; 
	   *((*a_it)--) = is_cap ? 'N' : 'n'; 
	   *((*a_it)--) = is_cap ? 'I' : 'i'; 
	   *((*a_it)--) = '+'; 
	   *flags = ISPINF_FLAG;
	   return;
       }
#endif
   /*------------------------------------------------------------------------*/
   /* If CVT is negative, set the MINUS_FLAG and reverse the sign of CVT.    */
   /*------------------------------------------------------------------------*/
   if (cvt < 0) { *flags = MINUS_FLAG; cvt = -cvt; }

   /*------------------------------------------------------------------------*/
   /* Call the proper conversion function                                    */
   /*------------------------------------------------------------------------*/
   switch(pfield->conv)
   {
      case 'f' :
      case 'F' :  _pconv_f(cvt, pfield, a_it);
                  break;
      case 'e' :
      case 'E' :  _pconv_e(cvt, pfield, a_it);
                  break;
      case 'g' :
      case 'G' :  _pconv_g(cvt, pfield, a_it);
   }
}


/*****************************************************************************/
/* _PCONV_F -  Perform the %f conversion                                     */
/*****************************************************************************/
static void _pconv_f(long double cvt, _PFIELD *pfield, char **a_it)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*------------------------------------------------------------------------*/
   char  tmpbuf[F_CONVERSION_BUFSIZE];
   char *result;
   char *frac_ptr;
   int   dpt, 
         sign, 
         putdec;

   /*------------------------------------------------------------------------*/
   /* If no precision was specified, set it to 6.                            */
   /*------------------------------------------------------------------------*/
   if(pfield->precision < 0) pfield->precision = 6;

   /*------------------------------------------------------------------------*/
   /* Call the FCVT float to string function, then copy the fractional part, */
   /* determine whether or not a decimal point should be placed, and copy    */
   /* whole number part.                                                     */
   /*------------------------------------------------------------------------*/
   frac_ptr = *a_it;
   result = fcvt(tmpbuf, cvt, pfield->precision, &dpt, &sign);
   _fcpy(result, dpt, pfield->precision, a_it);

   /*------------------------------------------------------------------------*/
   /* If the output has no fractional part, don't write the decimal point.   */
   /* If # flag was specified, then we write the decimal point always.       */
   /*------------------------------------------------------------------------*/
   putdec = (frac_ptr != *a_it || _STCHK(pfield, _PFPOUND));
   _mcpy(result, dpt, putdec, a_it);
}


/*****************************************************************************/
/* _PCONV_E -  Perform the %e conversion                                     */
/*****************************************************************************/
static void _pconv_e(long double cvt, _PFIELD *pfield, char **a_it)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*------------------------------------------------------------------------*/
   char  tmpbuf[FLOAT_VALUE_BUFSIZE];
   char *result;
   int   dpt, 
         sign, 
         putdec, 
         exp      = 0;

   /*------------------------------------------------------------------------*/
   /* If no precision was specified, set it to 6.                            */
   /*------------------------------------------------------------------------*/
   if(pfield->precision < 0) pfield->precision = 6;

   /*------------------------------------------------------------------------*/
   /* Check if CVT is within legal range -HUGE_VALL <= CVT <= HUGE_VALL      */
   /*------------------------------------------------------------------------*/
   if (cvt >= HUGE_VALL) cvt = HUGE_VALL;
   else if (cvt <= -HUGE_VALL) cvt = -HUGE_VALL;

   /*------------------------------------------------------------------------*/
   /* Convert CVT to x.xxxe+xx form, keeping the exponent in EXP.            */
   /*------------------------------------------------------------------------*/
   if(cvt)
   {
      for(;cvt < 1; cvt *= 10, exp--);
      for(;cvt >= 10; cvt /= 10, exp++);
   }

   /*------------------------------------------------------------------------*/
   /* Call the FCVT float to string function, copy the exponent part, the    */
   /* fractional part, then determine whether or not a decimal point should  */
   /* be placed, and copy the whole number part.                             */
   /*------------------------------------------------------------------------*/
   result = fcvt(tmpbuf, cvt, pfield->precision, &dpt, &sign);
   if(dpt==2) /* fcvt() might have rounded the number */
   {
       dpt--; exp++; result[strlen(result)-1] = 0;
   }
   _ecpy(exp, pfield->conv, a_it);
   _fcpy(result, dpt, pfield->precision, a_it);
   putdec = (dpt != (int)strlen(result) || _STCHK(pfield, _PFPOUND)) ? 1 : 0;
   _mcpy(result, dpt, putdec, a_it);
}


/*****************************************************************************/
/* _PCONV_G -  Perform the %g conversion                                     */
/*****************************************************************************/
static void _pconv_g(long double cvt, _PFIELD *pfield, char **a_it)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*------------------------------------------------------------------------*/
   char  tmpbuf[FLOAT_VALUE_BUFSIZE];
   char  *result;
   int   dpt, 
         sign, 
         i,
         digit_seen,
	 putdec, 
         exp         = 0;

   /*------------------------------------------------------------------------*/
   /* If the precision was given as 0, set it to one.                        */
   /*------------------------------------------------------------------------*/
   if(pfield->precision == 0) pfield->precision = 1;

   /*------------------------------------------------------------------------*/
   /* If no precision was specified, set it to 6.                            */
   /*------------------------------------------------------------------------*/
   if(pfield->precision < 0) pfield->precision = 6;

   result = ecvt(tmpbuf, cvt, pfield->precision, &dpt, &sign);

   /*------------------------------------------------------------------------*/
   /* If the exponent is less than -4, or greater than or equal to the       */
   /* precision, convert the number as a %e conversion.  Otherwise convert   */
   /* it as a %f conversion.                                                 */
   /*------------------------------------------------------------------------*/
   if(dpt < -3 || dpt > pfield->precision)
   {
      for(;dpt > 1; dpt--, exp++);
      for(;dpt < 1; dpt++, exp--);

      _ecpy(exp, pfield->conv-2, a_it);
   }

   /*------------------------------------------------------------------------*/
   /* Copy the fractional part of the number.  Ecvt produces exactly the     */
   /* number of significant digits specified by the precision, so copy all   */
   /* digits.                                                                */
   /*------------------------------------------------------------------------*/
   for (digit_seen = 0, i = strlen(result) - 1; i >= dpt; --i)
   {
      char digit = (i >= 0) ? result[i] : '0'; 

      if (digit != '0' || digit_seen || _STCHK(pfield, _PFPOUND))
      {
         *((*a_it)--) = digit;
	 digit_seen = 1;
      }
   }

   /*------------------------------------------------------------------------*/
   /* If the '#' flag was used, or there was a fractional part to the number */
   /* a decimal point will be placed.                                        */
   /*------------------------------------------------------------------------*/
   putdec = (_STCHK(pfield, _PFPOUND) || digit_seen) ? 1 : 0;

   _mcpy(result, dpt, putdec, a_it);
}


/*****************************************************************************/
/* _FCPY -  Copy the fraction part of a float to a string                    */
/*****************************************************************************/
static char *_fcpy(const char *tmpbuf, int dpt, int precision, char **a_it)
{
   /*------------------------------------------------------------------------*/
   /* Find the index of the least significant digit, as specified by the     */
   /* precision.                                                             */
   /*------------------------------------------------------------------------*/
   int   i   = dpt + precision - 1; 
   int   max = strlen(tmpbuf);

   /*------------------------------------------------------------------------*/
   /* Copy exactly 'precision' digits.                                       */
   /*------------------------------------------------------------------------*/
   while (precision-- > 0)
   {
      char digit = (i >= 0 && i < max) ? tmpbuf[i] : '0'; 
      *((*a_it)--) = digit;
      --i;
   }

   return (*a_it);
}


/*****************************************************************************/
/* _ECPY -  Copy the "e+xx" part of a float to a string                      */
/*****************************************************************************/
static char *_ecpy(int exp, char letter, char **a_it)
{
   _ltostr((exp > 0) ? exp : -exp, 10, 'd', a_it);
   if(exp < 10 && exp > -10) *((*a_it)--) = '0';
   *((*a_it)--) = (exp < 0) ? '-' : '+';
   *((*a_it)--) = letter;

   return (*a_it);
}


/*****************************************************************************/
/* _MCPY -  Copy the whole number part of a float to a string                */
/*****************************************************************************/
static char *_mcpy(const char *tmpbuf, int dpt, int putdec, char **a_it)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*------------------------------------------------------------------------*/
   int   i;
   char  *tmpptr = NULL;

   /*------------------------------------------------------------------------*/
   /* If the number has both a whole number part and a fractional part,      */
   /* position TMPPTR to the last character of the whole number.             */
   /*------------------------------------------------------------------------*/
   if(dpt > 0 && dpt <= (int)strlen(tmpbuf)) tmpptr = (char *)tmpbuf + dpt -1;

   /*------------------------------------------------------------------------*/
   /* Place a decimal point if PUTDEC is set.                                */
   /*------------------------------------------------------------------------*/
   if(putdec) *((*a_it)--) = '.';

   /*------------------------------------------------------------------------*/
   /* Place any whole number trailing zeros.                                 */
   /*------------------------------------------------------------------------*/
   for(i = dpt; i > (int)strlen(tmpbuf); i--) *((*a_it)--) = '0';

   /*------------------------------------------------------------------------*/
   /* Copy the rest of the whole number.                                     */
   /*------------------------------------------------------------------------*/
   if(i > 0) for(; tmpptr >= tmpbuf; tmpptr--) *((*a_it)--) = *tmpptr;
   else *((*a_it)--) = '0';

   return (*a_it);
}
#endif


/*****************************************************************************/
/* _PPROC_DIOUXP   -  Process the conversion for d, i, o, u, x, and p        */
/*                                                                           */
/*    This function takes the structure PFIELD, which contains all of the    */
/*    flags and parameters to process the conversion, and it does this       */
/*    conversion, and stores the result in the string pointed to by          */
/*    *A_IT.                                                                 */
/*                                                                           */
/*****************************************************************************/
static int _pproc_diouxp(_PFIELD *pfield, int *minus_flag, char **a_it, 
                         va_list *_ap)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*------------------------------------------------------------------------*/
   int digits =  0;
   int base   = 10;
   ubig_t cvt;

#if !defined(MINIMAL)
   /*------------------------------------------------------------------------*/
   /* If no precision was given, set it to 1.                                */
   /*------------------------------------------------------------------------*/
   if(pfield->precision < 0) pfield->precision = 1; 
   else                      _UNSET(pfield, _PFZERO);
#endif

   /*------------------------------------------------------------------------*/
   /* Set the base of the number by the type of conversion specified.        */
   /*------------------------------------------------------------------------*/
   switch(pfield->conv)
   {
#if !defined(MINIMAL)
      case 'p' :
      case 'X' :  
#endif
      case 'x' :
                  base = 16;
                  break;

      case 'o' :  base = 8;
                  break;

      default  :
#if !defined(MINIMAL)
      case 'u' :
      case 'i' :
#endif
      case 'd' :
                  base = 10;
  	          break;
   }  

   /*------------------------------------------------------------------------*/
   /* Get the next argument.                                                 */
   /*------------------------------------------------------------------------*/
   cvt = _getarg_diouxp(pfield, _ap);

#if !defined(MINIMAL)
   /*------------------------------------------------------------------------*/
   /* If the precision is 0, and the number is 0, and the # flag is not      */
   /* used, print no characters and return 1.  However, given the same       */
   /* conditions except the # flag is used, write a single '0'.  We fall     */
   /* through to accomplish this in _ltostr.                                 */
   /*------------------------------------------------------------------------*/
   if(pfield->precision == 0 && cvt == 0 && !_STCHK(pfield, _PFPOUND))
       return 1;
#endif

   /*------------------------------------------------------------------------*/
   /* If the number is signed and negative, set the minus sign flag, and     */
   /* negate the number.                                                     */
   /*------------------------------------------------------------------------*/
   if((pfield->conv == 'd' 
#if !defined(MINIMAL)
|| pfield->conv == 'i'
#endif
      )  && ((big_t)cvt < 0))
   {
      *minus_flag = 1;
      cvt = -(big_t)cvt;
   }

   /*------------------------------------------------------------------------*/
   /* Call the function to convert the number to a string, and add the       */
   /* total number of digits assigned into DIGITS.                           */
   /*------------------------------------------------------------------------*/
   digits += _ltostr(cvt, base, pfield->conv, a_it);

#if !defined(MINIMAL)
   /*------------------------------------------------------------------------*/
   /* Fill in the remainder of the precision with zeros.                     */
   /*------------------------------------------------------------------------*/
   while(digits++ < pfield->precision) *((*a_it)--) = '0';

   /*------------------------------------------------------------------------*/
   /* If the "#" flag was used in the X, x, or p conversion, prefix a "0x"   */
   /* or "0X" to the hexadecimal number.  We treat the p conversion exactly  */
   /* the same as the x conversion; this means that when "%p" will print     */
   /* "3", "%#p" will print "0x3".  The standard explicitly says using #     */
   /* with p is undefined behavior, so we can handle this any way we like,   */
   /* don't need to document it, and can change it without notice.           */
   /*------------------------------------------------------------------------*/
   if (HEX_CONV(pfield->conv) && _STCHK(pfield, _PFPOUND))
   {
      *((*a_it)--) = (pfield->conv == 'p' ? 'x' : pfield->conv);
      *((*a_it)--) = '0';
   }

   /*------------------------------------------------------------------------*/
   /* If the "#' flag was used in the o conversion, prefix a "0" to the      */
   /* octal number, but only if the first digit is not already '0'.          */
   /*------------------------------------------------------------------------*/
   if(pfield->conv == 'o' && _STCHK(pfield, _PFPOUND) && (*a_it)[1] != '0')
       *((*a_it)--) = '0';
#endif

   return (0);
}


/*****************************************************************************/
/* _GETARG_DIOUXP -  Get the argument for a d, i, o, u, x, or p conversion   */
/*                                                                           */
/*    This function takes the next argument off the argument list, after     */
/*    determining what kind of argument it is.  It decides this by checking  */
/*    to see if the 'h' or the 'l' flag was used.  It returns the next       */
/*    argument.                                                              */
/*****************************************************************************/
static ubig_t _getarg_diouxp(_PFIELD *pfield, va_list *_ap)
{
   /*------------------------------------------------------------------------*/
   /* Local variables                                                        */
   /*------------------------------------------------------------------------*/
   ubig_t cvt = 0;

   if (pfield->conv == 'p') cvt = (ubig_t)(uintptr_t)va_arg(*_ap, void *);
   else
   /*------------------------------------------------------------------------*/
   /* Get the number from the next argument.  Determine what kind of         */
   /* argument by checking for the h or l flag in the format specification.  */
   /*------------------------------------------------------------------------*/
#if !defined(MINIMAL)
   switch(_STCHK(pfield, (_MFH | _MFHH | _MFL | _MFLL | _MFI40)))
   {
      case _MFH   :  switch(pfield->conv)
                     {
                        case 'd' :
                        case 'i' : 
			    cvt = va_arg(*_ap, int);
			    break;
			    
                        case 'o' :
                        case 'u' :
                        case 'x' :
                        case 'X' : 
			    cvt = (unsigned short) va_arg(*_ap, unsigned int);
                     }
                     break;

      case _MFHH  :  switch(pfield->conv)
                     {
                        case 'd' :
                        case 'i' : 
			    cvt = va_arg(*_ap, int);
			    break;
			    
                        case 'o' :
                        case 'u' :
                        case 'x' :
                        case 'X' : 
			    cvt = (unsigned char) va_arg(*_ap, unsigned int);
                     }
                     break;

      case _MFL   :  switch(pfield->conv)
                     {
                        case 'd' :
                        case 'i' : 
			    cvt = va_arg(*_ap, long int);
			    break;

                        case 'o' :
                        case 'u' :
                        case 'x' :
                        case 'X' : 
			    cvt = va_arg(*_ap, unsigned long int);
                     }
                     break;
#ifdef LLONG_MAX
      case _MFLL  :  switch(pfield->conv)
                     {
                        case 'd' :
                        case 'i' : 
			    cvt = va_arg(*_ap, long long int);
			    break;

                        case 'o' :
                        case 'u' :
                        case 'x' :
                        case 'X' : 
			    cvt = va_arg(*_ap, unsigned long long int);
                     }
                     break;
#endif   
#ifdef __TI_INT40_T__
      case _MFI40 :  switch(pfield->conv)
                     {
                        case 'd' :
                        case 'i' :
                            cvt = va_arg(*_ap, __int40_t);
                            break;

                        case 'o' :
                        case 'u' :
                        case 'x' :
                        case 'X' :
                            cvt = va_arg(*_ap, unsigned __int40_t);
                     }
                     break;
#endif
      default     :  
#endif  /* MINIMAL */
	             switch(pfield->conv)
                     {
                        case 'd' :
#if !defined(MINIMAL)
                        case 'i' : 
#endif
			    cvt = va_arg(*_ap, int);
			    break;
 
                        case 'o' :
#if !defined(MINIMAL)
                        case 'u' :
                        case 'X' :
#endif
                        case 'x' :
			    cvt = va_arg(*_ap, unsigned int);
                     }
#if !defined(MINIMAL)
   }
#endif

   return (cvt);
}


/*****************************************************************************/
/* _LTOSTR  -  Convert an integer to a string of up to base 16               */
/*                                                                           */
/*    This function takes an ubig_t integer, converts it to a string         */
/*    which is pointed to by *A_IT.  The result will also be converted to    */
/*    a base corresponding to the variable base.                             */
/*                                                                           */
/*****************************************************************************/
static int _ltostr(ubig_t cvt, int base, char conv, char **a_it)
{
   /*------------------------------------------------------------------------*/
   /* Local Variables                                                        */
   /*------------------------------------------------------------------------*/
   ubig_t  quot,
           rem;
#if !defined(MINIMAL)
       char  *bnum = "0123456789abcdef0123456789ABCDEF";
#else
       char  *bnum = "0123456789abcdef";
#endif

   /*------------------------------------------------------------------------*/
   /* The number CVT will be converted to a string by taking the remainder   */
   /* of a division of it by its base, and converting it to a character.     */
   /* The number CVT is then set equal to itself divided by its base, and    */
   /* this continues until CVT is 0.                                         */
   /*------------------------------------------------------------------------*/

   if(! cvt) *((*a_it)--) = '0';

   while(cvt)
   {
      quot = _div(cvt, base);
      rem = cvt - (quot * base);

#if !defined(MINIMAL)
      if(conv == 'X') rem += 16;
#endif
      *((*a_it)--) = bnum[rem];
      cvt = quot;
   }

   return (strlen(*a_it) - 1);
}


/*****************************************************************************/
/* _DIV  -  Divide two integers                                              */
/*                                                                           */
/*    This function takes a ubig_t, and divides it by an integer.            */
/*    Division must take place in unsigned arithmetic, because signed '/'    */
/*    can overflow.  This function is used by _LTOSTR when it is converting  */
/*    an unsigned int to a string.                                           */
/*                                                                           */
/*****************************************************************************/
static ubig_t _div(ubig_t cvt, int base)
{
    /*-----------------------------------------------------------------------*/
    /* Use shifts to optimize power-of-two bases                             */
    /*-----------------------------------------------------------------------*/
    switch(base)
    {
	case  8: return cvt >> 3;
	case 16: return cvt >> 4;
    }

    /*-----------------------------------------------------------------------*/
    /* Perform divide in narrowest arithmetic possible, for speed.	     */
    /*-----------------------------------------------------------------------*/
         if (cvt <= UINT_MAX)  return (unsigned int)cvt / base;
    else if (cvt <= ULONG_MAX) return (unsigned long)cvt / base;
#ifdef __TI_INT40_T__
    else if (cvt <= UINT40_T_MAX) return (unsigned __int40_t)cvt / base;
#endif
    else return cvt / base;
}
