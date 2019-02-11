/****************************************************************************/
/*  vcop.h           v1.0.7                                                 */
/*                                                                          */
/* Copyright (c) 2010-2015 Texas Instruments Incorporated                   */
/* http://www.ti.com/                                                       */
/*                                                                          */
/*  Redistribution and  use in source  and binary forms, with  or without   */
/*  modification,  are permitted provided  that the  following conditions   */
/*  are met:                                                                */
/*                                                                          */
/*     Redistributions  of source  code must  retain the  above copyright   */
/*     notice, this list of conditions and the following disclaimer.        */
/*                                                                          */
/*     Redistributions in binary form  must reproduce the above copyright   */
/*     notice, this  list of conditions  and the following  disclaimer in   */
/*     the  documentation  and/or   other  materials  provided  with  the   */
/*     distribution.                                                        */
/*                                                                          */
/*     Neither the  name of Texas Instruments Incorporated  nor the names   */
/*     of its  contributors may  be used to  endorse or  promote products   */
/*     derived  from   this  software  without   specific  prior  written   */
/*     permission.                                                          */
/*                                                                          */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS   */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT   */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT   */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT   */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    */
/*                                                                          */
/*                                                                           */
/* Header file for VCOP kernels written in VCOP-C.                           */
/*                                                                           */
/* VCOP-C is an embedded language based on C++ that can be used to           */
/* express VCOP kernels.                                                     */
/*                                                                           */
/* VCOP-C kernels can be translated and run in two ways:                     */
/*   1. In emulation mode, using C++ classes defined in this file to         */
/*      execute the kernel on a host computer.                               */
/*   2. In native mode, by using the VCOP-C Kernel Compiler to translate     */
/*      the kernel to native VCOP assembly.                                  */
/*                                                                           */
/* Note that the classes defined for emulation mode implement a superset     */
/* of the language. That is, you can write programs that will compile and    */
/* run in emulation mode but that cannot be translated in native mode.       */
/* The kernel compiler is the ultimate authority on what constitutes a legal */
/* kernel.                                                                   */
/*                                                                           */
/* This C++ implementation uses templates to factor out common features of   */
/* the implementation. The implementation of vectors and address expressions */
/* are partially based on a technique called 'expression templates'.  See    */
/* http://en.wikipedia.org/wiki/Expression_templates for an introduction.    */
/*                                                                           */
/*****************************************************************************/
#ifndef __VCOP_H__
#define __VCOP_H__

#define VCOP_SIMD_WIDTH (8u)        /* number of lanes in VCOP SIMD */

#if VCOP_HOST_EMULATION
/*---------------------------------------------------------------------------*/
/* This code defines C++ classes that allow kernels written in VCOP-C to     */
/* compile and execute on a host system. Usage:                              */
/*                                                                           */
/* mykernel.cpp:                                                             */
/*    #include "vcop.h"           // this file                               */
/*    void my_kernel(...)  {   }  // kernel, written in vcop-c language      */
/*                                                                           */
/* Define emulation mode and compile using a C++ compiler, for example:      */
/*     g++ -DVCOP_HOST_EMULATION=1 mykernel.cpp                              */
/* then execute the program.                                                 */
/*---------------------------------------------------------------------------*/
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <map>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <memory>

/*---------------------------------------------------------------------------*/
/* Map VCOP Compiler Aided Memory Allocation routines to std malloc & free   */
/* for host emulation mode.                                                  */
/*---------------------------------------------------------------------------*/
#define vcop_malloc(heap, size)          malloc(size)
#define vcop_memalign(heap, align, size) malloc(size)
#define vcop_free(ptr)                   free(ptr)
#define vcop_minit()
#define vcop_setview(view)

#define foreach(i,t,m) for(int i=0;i<t;i++)
#define last(lcv,tc) (lcv == (tc-1))

/* Functions in arp32.h that are illegal when compiling in host mode */
#define _vcop_switchbuf(l, m, n, o, p)
#define _tsc_start()
#define _tsc_gettime() (0)
#define __vcop_vloop_ready()
#define __vcop_vloop_done()

#define NO_CIRC  0
#define CIRC_1K  1
#define CIRC_2K  2
#define CIRC_4K  3
#define CIRC_8K  4
#define CIRC_16K 5
#define CIRC_32K 6
/*---------------------------------------------------------------------------*/
/* Define a namespace for the implementation. User-accessible identifiers    */
/* are exported via 'using' directives below.                                */
/*---------------------------------------------------------------------------*/
namespace vcop
{
typedef long long element_t;              /* models 1 SIMD element */

class  VECTOR;
struct ROUNDFN;
struct SATURATION;
template <class Src, bool IsInt> struct VASSIGN;
template <class T> class ISINT;

static inline long long __vcop_bitmask(long long src, int width);
static inline long long __vcop_bitmask_uns(long long src, int width);

#define _bit_mask40s(s) __vcop_bitmask(s, 40)
#define _bit_mask34s(s) __vcop_bitmask(s, 34)
#define _bit_mask33s(s) __vcop_bitmask(s, 33)
#define _bit_mask32s(s) __vcop_bitmask(s, 32)
#define _bit_mask17s(s) __vcop_bitmask(s, 17)
#define _bit_mask6s(s) __vcop_bitmask(s, 6)
#define _bit_mask32u(s) __vcop_bitmask_uns(s, 32)
#define _bit_mask5u(s) __vcop_bitmask_uns(s, 5)

/****************************************************************************/
/* Limited smart pointer class                                              */
/*                                                                          */
/* Memory management for ROUNDFN and SATURATION objects.                    */
/* warning: not suitable for objects allocated with array new               */
/* warning: do NOT declare any smart<const X> objects                       */
/* warning: do not have any references to the objects pointed to except     */
/*          the ones in this class                                          */
/* warning: lots of other caveats, NOT INTENDED FOR GENERAL USE             */
/****************************************************************************/
template <class T>
class smart {
public:
   smart(const smart &x) : value(x.value) { getmap()[value]++; }

   smart(T *p = 0) : value(p) { getmap()[value]++; }

   smart &operator=(const smart &x)
   {
       if (this == &x) return *this;
       map &themap = getmap();
       if (value) { if (!--themap[value]) delete value; }
       themap[value = x.value]++;
       return *this;
   }

   smart &operator=(T *p)
   {
       map &themap = getmap();
       if (value) { if (!--themap[value]) delete value; }
       themap[value = p]++;
       return *this;
   }

   T *operator->(void) const { return value; }

   T &operator*(void) const { return *value; }

   bool operator!() const { return !value; }

   operator bool() const { return value != 0; }

   operator T*(void) const { return value; } 

   ~smart()
   {
       if (!--(getmap()[value])) delete value;
   }

private:
   typedef std::map<T *, int> map;

   map &getmap()
   {
       static map themap;
       return themap;
   }

   T *value;
};


/*---------------------------------------------------------------------------*/
/* VECTOR_BASE Class - Common behaviors of VECTOR and VECTOR_PAIR classes    */
/*                     This class represents the common actions of vector    */
/*                     registers and pairs.                                  */
/*---------------------------------------------------------------------------*/
template <class Vtype>           /* derived type: VECTOR or VECTOR_PAIR */
class VECTOR_BASE
{
public:
   VECTOR_BASE() : 
      roundfn(NULL), saturation(NULL), store_predicate(NULL) {}

   VECTOR_BASE(ROUNDFN* r, SATURATION* s, VECTOR* p) :
      roundfn(r), saturation(s), store_predicate(p) {}

   /* rounding, saturation modifiers */
   Vtype round(int bits);
   Vtype truncate(int bits);
   Vtype operator<<(int bits); 

   /* apply rounding to an element */
   inline element_t apply_rounding(element_t val) const;

   Vtype saturate();
   Vtype saturate(int bits);
   Vtype saturate(element_t min, element_t max);
   Vtype saturate(element_t min, element_t minset,
                  element_t max, element_t maxset);

   void clear_modifiers()
     { roundfn = NULL; saturation = NULL; store_predicate = NULL; }

   smart<ROUNDFN>     roundfn;
   smart<SATURATION>  saturation;
   VECTOR*            store_predicate;
};

/*---------------------------------------------------------------------------*/
/* VCMPGE_EXPR - Wrapper for a >= operator, two types of which exist in VCOP */
/*                                                                           */
/*    The >= operator exists as both a basic logical operation, as well as   */
/*    a special operator for the pack function. This object was created to   */
/*    differentiate between the 40-bit >= (logical) and the special 34-bit   */
/*    signed version of >= done as part of pack().                           */
/*---------------------------------------------------------------------------*/
class VCMPGE_EXPR
{
public:
   VCMPGE_EXPR(const VECTOR &l, const VECTOR &r) : lhs(l), rhs(r) {}
   inline element_t compare(int i);
      
   inline void load(VECTOR &dst);
      
   const VECTOR &lhs;
   const VECTOR &rhs;
};

/*---------------------------------------------------------------------------*/
/* VECTOR Class - Models a Vector Register (Vreg)                            */
/*---------------------------------------------------------------------------*/
class VECTOR : public VECTOR_BASE<VECTOR>
{
public:
   static const int NELEM = VCOP_SIMD_WIDTH;
   typedef VECTOR_BASE<VECTOR> Base;

   /* constructor */
   VECTOR() { init_elements(0); }

   VECTOR(VECTOR& src, ROUNDFN* r, SATURATION* s, VECTOR* p) :
      Base(r, s, p)
      { copy_elements(src); src.clear_modifiers(); }
   
   VECTOR(VCMPGE_EXPR& src)
      { for (int i = 0; i< NELEM; i++) elem[i] = src.compare(i); }

   /*------------------------------------------------------------------------*/
   /* The following is a template metaprogramming construct that allows      */
   /* compile-time behavior to change when a given boolean template argument */
   /* is true.                                                               */
   /*------------------------------------------------------------------------*/
   template<bool B, class T = void>
   struct enable_if {};

   template<class T>
   struct enable_if<true, T> { typedef T type; };

   /*------------------------------------------------------------------------*/
   /* The following two functions are never both viable choices. If T is     */
   /* signed, then type substitution will fail on the unsigned version of    */
   /* the function due to the enable_if construct, and vice versa.           */
   /*------------------------------------------------------------------------*/
   
   /*------------------------------------------------------------------------*/
   /* If type T is signed, we want to bit mask our ull values to 32 bits     */
   /* signed                                                                 */
   /*------------------------------------------------------------------------*/
   template <class T>
   typename enable_if<std::numeric_limits<T>::is_signed>::type
   init_elements(T init)
   { for (int i = 0; i < NELEM; ++i) elem[i] = _bit_mask32s(init); }

   /* If T is unsigned, we want to use a 32 bit unsigned mask instead. */
   template <class T>
   typename enable_if<!std::numeric_limits<T>::is_signed>::type
   init_elements(T init)
   { for (int i = 0; i < NELEM; ++i) elem[i] = _bit_mask32u(init); }
   
   void copy_elements(const VECTOR& src)
      { for (int i = 0; i < NELEM; ++i) elem[i] = src.elem[i]; }

   /* element access */
   element_t& operator[](int i)       { return elem[i]; }
   element_t  operator[](int i) const { return elem[i]; } 

   /* assignment: VECTOR = VECTOR */
   void operator=(const VECTOR &src)
   { 
       for (int i = 0; i < NELEM; ++i) 
	 elem[i] = src.apply_rounding(src.elem[i]); 
   }

   /*------------------------------------------------------------------------*/
   /* init elements: VECTOR = int (or integral type)                         */
   /* load:          VECTOR = memory                                         */
   /* Use appropriate specialization of VASSIGN to select which to call      */
   /*------------------------------------------------------------------------*/
   template <class Src> 
   inline void operator=(Src src) 
      { VASSIGN<Src, ISINT<Src>::value>::apply(*this, src); } 

   /* attach predicate (for store):  VECTOR.predicate(VECTOR) */
   VECTOR predicate(VECTOR& v)
      { return VECTOR((*this), this->roundfn, this->saturation, &v); }

   /* assignment operators */
   inline void operator+=(const VECTOR& src);
   inline void operator-=(const VECTOR& src);
   inline void operator*=(const VECTOR& src);
   inline void operator&=(const VECTOR& src);
   inline void operator|=(const VECTOR& src);
   inline void operator^=(const VECTOR& src);

   /* output contents of vector (for host debug, cause errors in vcc) */
   inline void print();
   inline void printx();
   inline void printlx();

   /* data members */
private:
   element_t elem[NELEM];
};

element_t VCMPGE_EXPR::compare(int i)
{
   return _bit_mask40s(_bit_mask40s(lhs[i]) - _bit_mask40s(rhs[i])) >= 0;
}

void VCMPGE_EXPR::load(VECTOR &dst)
{
   for (int i = 0; i < VECTOR::NELEM; i++) dst[i] = compare(i);
}

/* output contents of vector (for debug) */
void VECTOR::print()
{
   for (int i = 0; i < NELEM; ++i) 
       std::cout << elem[i] << ' ';
   std::cout << std::endl; 
}

/* output contents of vector in hex (for debug) */
void VECTOR::printx()
{
   for (int i = 0; i < NELEM; ++i) 
       std::cout << std::setbase(16) << std::setw(4)
                 << (unsigned) (elem[i] & 0xFFFFu) << ' ';
   std::cout << std::endl; 
}

/* output contents of vector in hex (for debug) */
void VECTOR::printlx()
{
   for (int i = 0; i < NELEM; ++i) 
       std::cout << std::setbase(16) << std::setw(4)
                 << (unsigned) (elem[i] & 0xFFFFFFFFu) << ' ';
   std::cout << std::endl; 
}

/*---------------------------------------------------------------------------*/
/* VASSIGN Class                                                             */
/*    Handle overloaded assignment to a vector object.  Template parameter   */
/*    specifies whether src operand is integral (VINIT) or memory (VLOAD).   */
/*---------------------------------------------------------------------------*/
/* specialization for integral src */
template <class Src>
struct VASSIGN<Src, true>
{
   static void apply(VECTOR& dst, Src &src) { dst.init_elements(src); }
};

/* specialization for memory src */
template <class Src>
struct VASSIGN<Src, false>
{
   static void apply(VECTOR& dst, Src &src) { src.load(dst); }
};

/*---------------------------------------------------------------------------*/
/* VECTOR_PAIR class -                                                       */
/*    Models a vector pair, for interleaved loads/stores and                 */
/* two-input/two-output operations.                                          */
/*---------------------------------------------------------------------------*/
class VECTOR_PAIR : public VECTOR_BASE<VECTOR_PAIR>
{
public:
   typedef VECTOR_BASE<VECTOR_PAIR> Base;

   VECTOR_PAIR(VECTOR& v1, VECTOR& v2) : first(v1), second(v2) {}

   VECTOR_PAIR(const VECTOR_PAIR& src) :
      first(src.first), second(src.second) { }

   VECTOR_PAIR(VECTOR_PAIR& src, ROUNDFN* r, SATURATION* s, VECTOR* p) :
      Base(r, s, p), 
      first(src.first),
      second(src.second) { src.clear_modifiers(); }

   /* assignment: VECTOR_PAIR = VECTOR_PAIR */
   VECTOR_PAIR& operator=(const VECTOR_PAIR &src) 
      { first = src.first; second = src.second; return *this; } 

   /* load: VECTOR_PAIR = VLVALUE */
   template <class Dist> 
   inline void operator=(Dist mem)    { mem.load(*this); }   /* vload */

   /*------------------------------------------------------------------------*/
   /* element access (pair is indexed as if it were a single vector, but     */
   /* twice as wide)                                                         */
   /*------------------------------------------------------------------------*/
   element_t& operator[](int i) 
      { return i < VECTOR::NELEM ? first[i] : second[i-VECTOR::NELEM]; }

   element_t operator[](int i) const
      { return i < VECTOR::NELEM ? first[i] : second[i-VECTOR::NELEM]; }

   /*------------------------------------------------------------------------*/
   /* map linear index to interleaved index                                  */
   /* 0-->0  1-->8  2-->1  3-->9  etc                                        */
   /*------------------------------------------------------------------------*/
   static int interleave_index(int i)
      { return (i & 1u) == 0 ? (i >> 1) : (i >> 1) + VECTOR::NELEM; }

   /* pair operations */
   inline VECTOR_PAIR& interleave();
   inline VECTOR_PAIR& deinterleave();
   inline VECTOR_PAIR& interleave2();
   inline VECTOR_PAIR& deinterleave2();
   inline VECTOR_PAIR& interleave4();
   inline VECTOR_PAIR& minmax();
   inline VECTOR_PAIR& addsub();
   inline VECTOR_PAIR& swap(const VECTOR& cnd);

   /* data members */
   VECTOR& first;
   VECTOR& second;
};

/* Form a pair from two vectors: (VECTOR, VECTOR) */
static inline VECTOR_PAIR operator,(VECTOR& v1, VECTOR& v2)
{
   return VECTOR_PAIR(v1, v2);
}

/*---------------------------------------------------------------------------*/
/* Rounding and Saturation classes                                           */
/*  These operators are attached to vectors via the rounding and saturation  */
/*  modifiers (e.g. Vreg.round()). They operate as follows:                  */
/*     0 Each rounding or saturation mode is derived from a common API.      */
/*     1 The modifier constructs an instance of a derived class              */
/*       corresponding to the specified rounding mode.                       */
/*     2 A copy of the vector (or pair) object is constructed, with the      */
/*       derived object attached (copying prevents modifiying the original   */
/*       object).                                                            */
/*     3 Upon store, the rounding or saturation is invoked via its apply()   */
/*       method.                                                             */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Rounding Mode classes                                                     */
/*---------------------------------------------------------------------------*/
/* rounding class abstract API */
struct ROUNDFN { virtual element_t apply(element_t) const = 0; };

/* class to represent basic rounding */
class ROUND_BASIC : public ROUNDFN
{
public:
   ROUND_BASIC(int b) : bits(b) {}

   virtual element_t apply(element_t val) const
   {
      int rnd_add = (bits > 0) ? (1 << (bits - 1)) : 0;
      return _bit_mask40s((val + rnd_add) >> bits);
   }

protected:
   int bits;
};

/* .round() modifier -- create new vector expr with rounding attached */
template <class Vtype>
Vtype VECTOR_BASE<Vtype>::round(int b) 
{
   return Vtype(static_cast<Vtype&>(*this), 
	        new ROUND_BASIC(b), 
	        saturation, store_predicate); 
}

/* class to represent truncation rounding mode */
struct TRUNCATE : public ROUND_BASIC
{
public:
   TRUNCATE(int b) : ROUND_BASIC(b) {}

   element_t apply(element_t val) const { return _bit_mask40s(val >> bits); }
};

/* .truncate() modifier -- create new vector expr with truncation attached */
template <class Vtype>
Vtype VECTOR_BASE<Vtype>::truncate(int b)
{
   return Vtype(static_cast<Vtype&>(*this),
	        new TRUNCATE(b), 
	        saturation, store_predicate);
}

/* class to represent left shift rounding mode */
class LEFTSHIFT : public ROUND_BASIC
{
public:
   LEFTSHIFT(int b) : ROUND_BASIC(b) {}

   element_t apply(element_t val) const { return _bit_mask40s(val << bits); }
};

/* << operator -- create new vector expr with leftshift attached */
template <class Vtype>
Vtype VECTOR_BASE<Vtype>::operator<< (int b)
{
   return Vtype(static_cast<Vtype&>(*this), 
	        new LEFTSHIFT(b), 
	        saturation, store_predicate); 
}

/* apply rounding to an element */
template <class Vtype>
element_t VECTOR_BASE<Vtype>::apply_rounding(element_t val) const
{ 
   if (roundfn) val = roundfn->apply(val);
   return val;
}

/*---------------------------------------------------------------------------*/
/* SATURATION class - applied to value upon store                            */
/*---------------------------------------------------------------------------*/
class SATURATION
{
public:
   /* Four arguments gives us all parameters for the saturation */
   SATURATION(element_t min_, element_t minset_, 
	      element_t max_, element_t maxset_) : 
      min(min_), minset(minset_), max(max_), maxset(maxset_),
      saturate_to_type(false), saturate_by_bits(false)
   {}

   /* No arguments tells the compiler to saturate to the base address' type */
   SATURATION() :
      min(0), minset(0), max(0), maxset(0),
      saturate_to_type(true), saturate_by_bits(false)
   {}

   /* Two arguments clamps values to min <= val <= max */
   SATURATION(element_t min_, element_t max_) :
      min(min_), minset(min), max(max_), maxset(max),
      saturate_to_type(false), saturate_by_bits(false)
   {}

   /* One argument caps the value to a certain number of bits */
   SATURATION(int b) :
      saturate_by_bits(true), bits(b)
   {}

   template <class T>
   static T apply(SATURATION &s, element_t val); /* below */

private: 
   element_t min;
   element_t minset;
   element_t max;
   element_t maxset;
   element_t  bits;
   bool      saturate_by_bits;
   bool      saturate_to_type;   /* saturation limits implied by store type */
};

template <class T>
T SATURATION::apply(SATURATION& s, element_t val) 
{
   element_t min, max;
   /* Get min and max from the templated type and saturate the value */
   if (s.saturate_to_type)
   {
      min = std::numeric_limits<T>::min();
      max = std::numeric_limits<T>::max();

      if      (val >= max) val = max;
      else if (val < min)  val = min;
   }
   else if (s.saturate_by_bits)
   { 
      /* Get the type's min to see if the type is signed or unsigned */
      element_t type_min = std::numeric_limits<T>::min();
      if (type_min < 0 )
      {
         /* If it's signed, (min,max) == (-2^(n-1), 2^(n-1)-1) */
         max = (1 << (s.bits - 1)) - 1;
         min = -(1 << (s.bits - 1));
      }
      else
      {
         /* If unsigned, (min,max) == (0,2^(n-1)) */
         max = (1 << s.bits) - 1;
         min = 0;
      }

      if      (val >= max) val = max;
      else if (val < min)  val = min;
   }
   else
   {
      /*---------------------------------------------------------------------*/
      /* Signedness is taken from the store's (T) type                       */
      /* Bounds are interpreted as integers to avoid ambiguity with shorts   */
      /*---------------------------------------------------------------------*/
      if (std::numeric_limits<T>::is_signed)
      {
         if      (val >= (int)s.max) val = (int)s.maxset;
         else if (val < (int)s.min)  val = (int)s.minset;
      }
      else
      {
         if      (val >= (unsigned int)s.max) val = (unsigned int)s.maxset;
         else if (val < (unsigned int)s.min)  val = (unsigned int)s.minset;
      }
   }
   /* Sign extend the 64-bit value if needed */
   return (T)val;
}


/* .saturate() modifiers - create new vector expr with saturation attached */
template <class Vtype>
Vtype VECTOR_BASE<Vtype>::saturate()
{
   return Vtype(static_cast<Vtype&>(*this), 
	        roundfn, 
	        new SATURATION(), 
		store_predicate); 
}

template <class Vtype>
Vtype VECTOR_BASE<Vtype>::saturate(int bits)
{
   return Vtype(static_cast<Vtype&>(*this),
	        roundfn, 
	        new SATURATION(bits),
		store_predicate); 
}

template <class Vtype>
Vtype VECTOR_BASE<Vtype>::saturate(element_t min, element_t max)
{
   return Vtype(static_cast<Vtype&>(*this), 
	        roundfn, 
	        new SATURATION(min, max), 
		store_predicate); 
}

template <class Vtype>
Vtype VECTOR_BASE<Vtype>::saturate(element_t min, element_t minset,
                                   element_t max, element_t maxset)
{
   return Vtype(static_cast<Vtype&>(*this), 
	        roundfn, 
	        new SATURATION(min, minset, max, maxset), 
		store_predicate); 
}


/****************************************************************************/
/* ADDRESS EXPRESSION CLASSES                                               */
/*   Address expressions represent the memory operand in a load or store.   */
/*   These are modeled with the following classes:                          */
/*      AGEN - an address generator, e.g. A0                                */
/*      VPTR - a base address, e.g. "data" in "data[A0]"                    */
/*      VPTR_ARR - Base address for an array of pointers to base addresses  */
/*                 used in foreach loops. Ex: "data" in "data[I0][A0]"      */
/*      VPTR_EXPR - a base address expression, e.g. "(data+1)"              */
/*      VLVALUE - Combines a VPTR_EXPR and an AGEN, e.g. "data...[A0]"      */
/*      VMODEs - Collection of classes that model distribution modes        */
/*   Address expressions are templatized on the underlying data type ("T"), */
/*   e.g. unsigned short, int, etc.                                         */
/*   TODO: use abstract integral types, do not rely on host types           */
/****************************************************************************/
template <class T> class VLVALUE;
template <class T, class Vtype, class Amode> class VMODE_BASE;
template <class T> class NPT; 
template <class T> class ONEPT;
template <class T> class CIRC2;
template <class T> class DS2;
template <class T> class US2;
template <class T> class INTERLEAVE;
template <class T> class DEINTERLEAVE;
template <class T> class CUSTOM;
template <class T> class OFFSET_NP1;
template <class T> class SCATTER;
template <class T> class SKIP;
template <class T> class COLLATE;
template <class T> class NBITS;
template <class T> class EXPAND;
template <class T> class TBL_LOAD;
template <class T> class HISTOGRAM;

/*---------------------------------------------------------------------------*/
/* Macros and globals to help execute table lookup, expand/collate, and      */
/* histogram loops.                                                          */
/*---------------------------------------------------------------------------*/
template <int N>
struct vcop_state
{
   static int hist_cnt;
   static int table_cnt;
   static int data_pts;
};

template <int N>
int vcop_state<N>::hist_cnt;
template <int N>
int vcop_state<N>::table_cnt;
template <int N>
int vcop_state<N>::data_pts;

#define _HISTOGRAM(h) vcop::vcop_state<0>::hist_cnt = h;

#define _LOOKUP(t,d)  vcop::vcop_state<0>::table_cnt = t; \
                      vcop::vcop_state<0>::data_pts  = d;

#define _EXPAND(i) i.root.reset_agen();
#define _COLLATE(i) i.root.reset_agen();

/*---------------------------------------------------------------------------*/
/* AGEN Class - models an address generator.                                 */
/*---------------------------------------------------------------------------*/
class AGEN
{
public:
   AGEN() : value(0) {}
   AGEN(int rhs) : value(rhs) {}

   /* assignment: Agen = <expression> ;  */
   void operator=(int rhs) { value = rhs; }

   int value;
};

/*---------------------------------------------------------------------------*/
/* Collate specifier for VSTORE                                              */
/*   This are combined with a VPTR expression (below) to form the collate    */
/*   addressing mode.  It is invoked as a constructor, therefore modeled by  */
/*   a distinct class.                                                       */
/*      VPTR [ collate( VECTOR ) ]  = ...                                    */
/*---------------------------------------------------------------------------*/
class collate
{
public:
   collate(const VECTOR&v ) : predicate(v) {}
   const VECTOR& predicate;
};

/*---------------------------------------------------------------------------*/
/* Expand distribution specifier for VLOAD                                   */
/*   This are combined with a VPTR expression (below) to form the expand     */
/*   addressing mode.  It is invoked as a constructor, therefore modeled by  */
/*   a distinct class.                                                       */
/*      Vdst = VPTR [ expand( VECTOR ) ];                                    */
/*---------------------------------------------------------------------------*/
class expand
{
public:
   expand(const VECTOR& v) : predicate(v) {}
   const VECTOR& predicate;
};


template <class T> class VPTR_EXPR; 

/*---------------------------------------------------------------------------*/
/* VPTR - Data buffer pointer for loads and stores.                          */
/*   These correspond to kernel parameters declared with types __vptr_XXX,   */
/*   and form the root of address expressions. Objects of this type are not  */
/*   transient -- they correspond to declared variables (specifically,       */
/*   passed-in kernel parameters).                                           */
/*                                                                           */
/*   VPTR is derived from VPTR_EXPR because a leaf VPTR *is* a VPTR_EXPR.    */
/*   Grammatically:                                                          */
/*      VLVALUE   : VPTR_EXPR [ AGEN ]                                       */
/*      VPTR_EXPR : VPTR                                                     */
/*                | VPTR_EXPR +/- offset                                     */
/*---------------------------------------------------------------------------*/
template <class T>               /* underlying data type  */
class VPTR : public VPTR_EXPR<T>
{
public:
   /*------------------------------------------------------------------------*/
   /* Construct a VPTR from a plain-old pointer.                             */
   /* A VPTR is a VPTR_EXPR with itself as the root and no offset            */
   /*------------------------------------------------------------------------*/
   VPTR(void *a) : VPTR_EXPR<T>(*this, 0), addr((T*)a) {}

   /* base address (value of passed-in data pointer) */
   T*   addr;

   void reset_agen() { local_agen.value = 0; }

   /*------------------------------------------------------------------------*/
   /* 'local_agen' holds a persistent offset value for the collate operator. */
   /* Each VPTR object captures one such offset. The expectation is that     */
   /* a pointer is not used for multiple such stores. It's modeled as an     */
   /* Agen -- which after all, is simply an address offset -- to unify       */
   /* collate with other addressing modes.                                   */
   /*------------------------------------------------------------------------*/
   AGEN local_agen;
};

/*---------------------------------------------------------------------------*/
/* VPTR_ARR - Class used when an argument is given with __vptr_<type>_arr    */
/*            its only function is to return a VPTR when given an offset.    */
/*            Used for repeat loops.                                         */
/*---------------------------------------------------------------------------*/
template <class T>
class VPTR_ARR
{
public:
   VPTR_ARR(void *a) : ptr_arr((T**)a) {}

   VPTR<T> operator[](int i)
   {
      /*---------------------------------------------------------------------*/
      /* Make sure we only use a single object to represent each index of    */
      /* the array to keep around changes that may occur to the object       */
      /* across iterations.                                                  */
      /*---------------------------------------------------------------------*/
      if (generated_vptrs.find(i) == generated_vptrs.end())
         generated_vptrs[i] = new VPTR<T>(ptr_arr[i]);

      return *generated_vptrs[i];
   }

   std::map<int, VPTR<T>*> generated_vptrs;
   T** ptr_arr;
};

/*---------------------------------------------------------------------------*/
/* VPTR_EXPR - Base address expression for loads and stores.                 */
/*   A VPTR_EXPR consists of a root (the data pointer) and an offset.        */
/*---------------------------------------------------------------------------*/
template <class T>
class VPTR_EXPR
{
public:
   typedef T element;

   VPTR_EXPR(VPTR<T>& r, int o) : root(r), offset(o) {}

   /* attach an AGEN to form a VLVALUE : VPTR_EXPR [ AGEN ] */
   VLVALUE<T> operator[](AGEN& a) { return VLVALUE<T>(*this, a); }

   /*------------------------------------------------------------------------*/
   /* attach a collate() operator: VPTR_EXPR [ collate (VECTOR) ]            */
   /* use root's captive Agen to hold persistent offset                      */
   /*------------------------------------------------------------------------*/
   COLLATE<T> operator[](const collate& e)
     { return COLLATE<T>((*this)[root.local_agen], e.predicate); }
   
   /*------------------------------------------------------------------------*/
   /* attach a expand() operator: VPTR_EXPR [ expand (VECTOR) ]              */
   /* use root's captive Agen to hold persistent offset                      */
   /*------------------------------------------------------------------------*/
   EXPAND<T> operator[](const expand& e)
     { return EXPAND<T>((*this)[root.local_agen], e.predicate); }

   /* address arithmetic - return new VPTR_EXPRS with adjusted offsets */
   VPTR_EXPR<T> operator+(int k) { return VPTR_EXPR<T>(root, offset + k); }
   VPTR_EXPR<T> operator-(int k) { return VPTR_EXPR<T>(root, offset - k); }

   /* return the address represented by this expression */
   T* address() { return (T*)((char *)root.addr + offset); }

   /*------------------------------------------------------------------------*/
   /* overload for unary *, for use in sizeof: sizeof(*base)                 */
   /* this function is not intended to be called; it only exists so          */
   /* the compiler can evaluate sizeof expressions                           */
   /*------------------------------------------------------------------------*/
   T operator*() { return *root.addr; }

   VPTR<T>&   root;          /* underlying pointer variable */
   int        offset;        /* offset */
};

/*---------------------------------------------------------------------------*/
/* VLVALUE - Base expression with Agen attached: VPTR_EXPR [ AGEN ]          */
/*---------------------------------------------------------------------------*/
template <class T>
class VLVALUE
{
public:
   VLVALUE(VPTR_EXPR<T>& b, AGEN& a) : base(b), agen(a) {}

   /*------------------------------------------------------------------------*/
   /* vector store: VLVALUE = VECTOR (or VECTOR_PAIR)                        */
   /* Use default distribution (npt()) since we would have attached a        */
   /* distribution before this point if it existed                           */
   /*------------------------------------------------------------------------*/
   template <class Vtype>
   void operator=(Vtype src)  { (*this).npt() = src; }

   /*------------------------------------------------------------------------*/
   /* Circular buffer operator. Returns an NPT distribution because the      */
   /* object would not be calling this method if another distribution were   */
   /* used.                                                                  */
   /*------------------------------------------------------------------------*/
   NPT<T> operator%(int size)   { return NPT<T>(*this,size); }

   /*------------------------------------------------------------------------*/
   /* vector load: VECTOR = VLVALUE (invoked by VECTOR::operator=)           */
   /* use default distribution (npt())                                       */
   /*------------------------------------------------------------------------*/
   template <class Vtype>
   void load(Vtype& dst)      { dst = (*this).npt(); }

   /*------------------------------------------------------------------------*/
   /* modifiers to specify distribution modes: VLVALUE . npt()  etc.         */
   /* these are factory methods that create an object of the appropriate     */
   /* class, which will be invoked to perform the load or store.             */
   /*------------------------------------------------------------------------*/
   NPT<T>          npt()                { return NPT<T>(*this);             }
   ONEPT<T>        onept()              { return ONEPT<T>(*this);           }
   CIRC2<T>        circ2()              { return CIRC2<T>(*this);           }
   DS2<T>          ds2()                { return DS2<T>(*this);             }
   US2<T>          us2()                { return US2<T>(*this);             } 
   INTERLEAVE<T>   interleave()         { return INTERLEAVE<T>(*this);      }
   DEINTERLEAVE<T> deinterleave()       { return DEINTERLEAVE<T>(*this);    }
   OFFSET_NP1<T>   offset_np1()         { return OFFSET_NP1<T>(*this);      }
   SCATTER<T>      p_scatter(VECTOR& v) { return SCATTER<T>(*this, v);      }
   SCATTER<T>      s_scatter(VECTOR& v) { return SCATTER<T>(*this, v);      }
   SKIP<T>         skip()               { return SKIP<T>(*this);            }
   CUSTOM<T>       dist(int offsets[])  { return CUSTOM<T>(*this, offsets); }
   CUSTOM<T>       dist(int k0, int k1, int k2, int k3, int k4,
                        int k5, int k6, int k7);
   NBITS<T>        nbits()              { return NBITS<T>(*this);           }
   
   /*------------------------------------------------------------------------*/
   /* Table Lookup and Histogram operations                                  */
   /*------------------------------------------------------------------------*/
   TBL_LOAD<T>   lookup(VECTOR index)
                   { 
                      smart<ROUNDFN>    i_rnd = index.roundfn;
                      smart<SATURATION> i_sat = index.saturation;
                      index.clear_modifiers();
                      return TBL_LOAD<T>(*this, i_rnd, i_sat, index);
                   }
   NPT<T>   table_npt()
   { return NPT<T>(*this, 0,
                   vcop_state<0>::table_cnt*vcop_state<0>::data_pts); }

   SKIP<T>  table_skip()
   { return SKIP<T>(*this, 0,
                    vcop_state<0>::table_cnt*vcop_state<0>::data_pts); }

   HISTOGRAM<T>    hist_update(VECTOR index, VECTOR& weight)
                   {
                      smart<ROUNDFN>    i_rnd = index.roundfn;
                      smart<SATURATION> i_sat = index.saturation;
                      index.clear_modifiers();
                      return HISTOGRAM<T>(*this, i_rnd, i_sat, index, weight);
                   }
   NPT<T>          weight_load() { return NPT<T>(*this); }

   /* data members */
   VPTR_EXPR<T>& base;
   AGEN&         agen;
};

template <class T>
CUSTOM<T> VLVALUE<T>::dist(int k0, int k1, int k2, int k3, 
   	                   int k4, int k5, int k6, int k7)
{
   int offsets[] = { k0, k1, k2, k3, k4, k5, k6, k7 };  
   return CUSTOM<T>(*this, offsets);
}

/*---------------------------------------------------------------------------*/
/* VMODE_BASE - Base class for addressing mode ("disribution mode") classes  */
/*---------------------------------------------------------------------------*/
template <class T, class Vtype, class Amode>
class VMODE_BASE
{
public:
   VMODE_BASE(VLVALUE<T>& v, int s=0) : base(v.base), agen(v.agen),
                                        circ_size(s) {}
   VMODE_BASE(Amode& a) : base(a.base), agen(a.agen), circ_size(a.circ_size) {}

   /* address() returns the base address plus Agen value */
   T* address();

   /* address_postinc() increments the captive Agen, for collating stores */
   T* address_postinc() 
   { 
      T* result = address(); 
      agen.value += sizeof(T);
      return result;
   }

   /*------------------------------------------------------------------------*/
   /* Circular buffer operator. Returns an instance of this object with a    */
   /* circular buffer size attached to it                                    */
   /*------------------------------------------------------------------------*/
   Amode operator%(int size) { circ_size = size; 
                               return Amode(static_cast<Amode&>(*this)); }

   /* store_element() - helper fn for store methods, stores a single element */
   void store_element(int i, int offset, const Vtype& vexpr, element_t val);

   /* apply_rs() - apply rounding and saturation                             */
   element_t apply_rs(const Vtype&, element_t);

   /* data members, copied from parent VLVALUE */
   VPTR_EXPR<T>& base;
   AGEN&         agen;
   int           circ_size;
};

/* address() returns the base address plus Agen value */
template <class T, class Vtype, class Amode>
T* VMODE_BASE<T, Vtype, Amode>::address()
{
   unsigned int circ_mask;

   /*------------------------------------------------------------------------*/
   /* Circular buffer number of 1 must map to 0x3FF                          */
   /*                           2 must map to 0x7FF                          */
   /*                           3 must map to 0xFFF                          */
   /*                           4 must map to 0x1FFF                         */
   /*                           5 must map to 0x3FFF                         */
   /*                           6 must map to 0x5FFF                         */
   /*------------------------------------------------------------------------*/
   if (circ_size == 0)
      circ_mask = 0xffffffffu;
   else
      circ_mask = (0x200u << circ_size) - 1u;

   return (T*)(((uint64_t)base.address() & ~circ_mask) |
              (((uint64_t)base.address() + agen.value) & circ_mask));
}

/* store_element() - helper function for store() methods */
template <class T, class Vtype, class Amode>
void VMODE_BASE<T, Vtype, Amode>::store_element(
                               int          i,       /* element index */
                               int          offset,  /* memory offset */
                               const Vtype& vexpr,   /* rhs VECTOR (or pair) */
			       element_t    val)     /* scalar to store */
{
   /* test vector's store predicate, if attached */
   if (vexpr.store_predicate && (*vexpr.store_predicate)[i] == 0)
      return;

   /* apply rounding and saturation */
   val = apply_rs(vexpr, val); 

   /* do the store */
   address()[offset] = val;
}

/* apply rounding and saturation */
template <class T, class Vtype, class Amode>
element_t VMODE_BASE<T, Vtype, Amode>::apply_rs(const Vtype& vexpr,
                                                element_t val)
{
   val = vexpr.apply_rounding(val);
   if (vexpr.saturation) val = SATURATION::apply<T>(*vexpr.saturation, val); 
   return val;
}

/*---------------------------------------------------------------------------*/
/* Addressing Mode Classes                                                   */
/* Perform load/store using specified distribution mode.                     */
/* Addressing modes that can be used for both loads and stores have both     */
/* methods; others only have one or the other.                               */
/*---------------------------------------------------------------------------*/
template <class T>
class NPT : public VMODE_BASE<T, VECTOR, NPT<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, NPT<T> > Base;
   NPT(VLVALUE<T>& v, int s=0, int c=VECTOR::NELEM) : Base(v,s),
                                                      num_elem(c) {}
   NPT(const NPT<T>& a) : Base(a), num_elem(a.num_elem) {}

   void load(VECTOR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM; ++i)
	 vexpr[i] = Base::address()[i];
   }
   void operator=(const VECTOR& vexpr)
   {
      for (int i = 0; i < num_elem; ++i)
	 Base::store_element(i, i, vexpr, vexpr[i]); 
   }

   int num_elem;
};

template <class T>
class ONEPT : public VMODE_BASE<T, VECTOR, ONEPT<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, ONEPT<T> > Base;
   ONEPT(VLVALUE<T>& v, int s=0) : Base(v,s) {}
   ONEPT(const ONEPT<T>& a) : Base(a) {} 

   void load(VECTOR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM; ++i)
	 vexpr[i] = Base::address()[0];
   }
   void operator=(const VECTOR& vexpr)
   {
      Base::store_element(0, 0, vexpr, vexpr[0]); 
   }
};

template <class T>
class CIRC2 : public VMODE_BASE<T, VECTOR, CIRC2<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, CIRC2<T> > Base;
   CIRC2(VLVALUE<T>& v, int s=0) : Base(v,s) {}
   CIRC2(const CIRC2<T>& a) : Base(a) {}

   void load(VECTOR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM; ++i)
	 vexpr[i] = Base::address()[i%2];
   }
};

template <class T>
class DS2 : public VMODE_BASE<T, VECTOR, DS2<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, DS2<T> > Base;
   DS2(VLVALUE<T>& v, int s=0) : Base(v,s) {}
   DS2(const DS2<T>& a) : Base(a) {}

   void load(VECTOR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM; ++i)
	 vexpr[i] = Base::address()[i*2];
   }
   void operator=(const VECTOR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM; i+=2)
	 Base::store_element(i, i/2, vexpr, vexpr[i]); 
   }
};

template <class T>
class US2 : public VMODE_BASE<T, VECTOR, US2<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, US2<T> > Base;
   US2(VLVALUE<T>& v, int s=0) : Base(v,s) {}
   US2(const US2<T>& a) : Base(a) {}

   void load(VECTOR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM; ++i)
	 vexpr[i] = Base::address()[i/2];
   }
};

/*---------------------------------------------------------------------------*/
/* OFFSET_NP1 skips words, regardless of type. Must convert offset to        */
/* word units.                                                               */
/*---------------------------------------------------------------------------*/
template <class T>
class OFFSET_NP1 : public VMODE_BASE<T, VECTOR, OFFSET_NP1<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, OFFSET_NP1<T> > Base;
   OFFSET_NP1(VLVALUE<T>& v, int s=0) : Base(v,s) {}
   OFFSET_NP1(const OFFSET_NP1<T>& a) : Base(a) {}

   void operator=(const VECTOR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM; ++i)
	 Base::store_element(i, 
         (sizeof(int) / sizeof(T)) * i * (VECTOR::NELEM+1), vexpr, vexpr[i]);
   }
};

template <class T>
class CUSTOM : public VMODE_BASE<T, VECTOR, CUSTOM<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, CUSTOM<T> > Base;
   CUSTOM(VLVALUE<T>& v, int o[], int s=0) : Base(v,s)
      { memcpy(offsets, o, sizeof(offsets)); }
   CUSTOM(const CUSTOM<T>& a) : Base(a)
      { memcpy(offsets, a.offsets, sizeof(offsets)); }

   void load(VECTOR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM; ++i)
	 vexpr[i] = Base::address()[offsets[i]];
   }
   int offsets[VECTOR::NELEM]; 
};

template <class T>
class SCATTER : public VMODE_BASE<T, VECTOR, SCATTER<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, SCATTER<T> > Base;
   SCATTER(VLVALUE<T>& v, VECTOR& i, int s=0) : Base(v), index(i) {}
   SCATTER(const SCATTER<T>& a) : Base(a), index(a.index) {}

   void operator=(const VECTOR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM; ++i)
      {
         element_t val = vexpr[i];
         if (vexpr.store_predicate && (*vexpr.store_predicate)[i] == 0)
            return;

         val = Base::apply_rs(vexpr, val); 

         ((T*)((char*)Base::address() + index[i]))[0] = val;
      }
   }
   VECTOR& index;
};

template <class T>
class SKIP : public VMODE_BASE<T, VECTOR, SKIP<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, SKIP<T> > Base;
   SKIP(VLVALUE<T>& v, int s=0, int c=VECTOR::NELEM) : Base(v,s),
                                                       num_elem(c) {}
   SKIP(const SKIP<T>& a) : Base(a), num_elem(a.num_elem) {}

   void operator=(const VECTOR& vexpr)
   {
      for (int i = 0; i < num_elem; ++i)
	 Base::store_element(i, i*2, vexpr, vexpr[i]); 
   }

   int num_elem;
};

template <class T>
class INTERLEAVE : public VMODE_BASE<T, VECTOR_PAIR, INTERLEAVE<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR_PAIR, INTERLEAVE<T> > Base;
   INTERLEAVE(VLVALUE<T>& v, int s=0) : Base(v,s) {}
   INTERLEAVE(const INTERLEAVE<T>& a) : Base(a) {}

   void operator=(const VECTOR_PAIR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM * 2; ++i)
	 Base::store_element(i, i, vexpr, 
	                     vexpr[VECTOR_PAIR::interleave_index(i)]);
   }
};

template <class T>
class DEINTERLEAVE : public VMODE_BASE<T, VECTOR_PAIR, DEINTERLEAVE<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR_PAIR, DEINTERLEAVE<T> > Base;
   DEINTERLEAVE(VLVALUE<T>& v, int s=0) : Base(v,s) {}
   DEINTERLEAVE(const DEINTERLEAVE<T>& a) : Base(a) {}

   void load(VECTOR_PAIR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM * 2; ++i)
	 vexpr[VECTOR_PAIR::interleave_index(i)] = Base::address()[i]; 
   }
};

template <class T>
class COLLATE : public VMODE_BASE<T, VECTOR, COLLATE<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, COLLATE<T> > Base;
   COLLATE(VLVALUE<T> v, const VECTOR& p, int s=0) : Base(v,s), predicate(p) {}
   COLLATE(const COLLATE<T>& a) : Base(a), predicate(a.predicate) {}

   void operator=(const VECTOR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM; ++i)
         if (predicate[i]) 
	    *Base::address_postinc() = Base::apply_rs(vexpr, vexpr[i]); 
   }
   const VECTOR& predicate;
};

template <class T>
class NBITS : public VMODE_BASE<T, VECTOR, NBITS<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, NBITS<T> > Base;
   NBITS(VLVALUE<T>& v, int s=0) : Base(v,s) {}
   NBITS(const NBITS<T>& a) : Base(a) {}

   void load(VECTOR& vexpr)
   {
      T value = (T)Base::address()[0];
      for (int i = 0; i < VECTOR::NELEM; ++i)
         vexpr[i] = ((value >> i) & 1u) ?
                     (std::numeric_limits<T>::is_signed ? -1 : 1) : 0; 
   }
};

template <class T>
class EXPAND : public VMODE_BASE<T, VECTOR, EXPAND<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, EXPAND<T> > Base;
   EXPAND(VLVALUE<T> v, const VECTOR& p, int s=0) : Base(v,s), predicate(p) {}
   EXPAND(const EXPAND<T>& a) : Base(a), predicate(a.predicate) {}

   void load(VECTOR& vexpr)
   {
      for (int i = 0; i < VECTOR::NELEM; ++i)
         if (predicate[i]) 
	    vexpr[i] = *Base::address_postinc();
         else
            vexpr[i] = 0;
   }
   const VECTOR& predicate;
};

/*---------------------------------------------------------------------------*/
/* TBL_LOAD - Object to contain table lookup.                                */
/*---------------------------------------------------------------------------*/
template <class T>
class TBL_LOAD : public VMODE_BASE<T, VECTOR, TBL_LOAD<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, TBL_LOAD<T> > Base;
   TBL_LOAD(VLVALUE<T> v, ROUNDFN* r,SATURATION* sa, VECTOR i, int s=0) 
              : Base(v,s)
   {
      index            = i;
      index.roundfn    = r;
      index.saturation = sa;
   }
   TBL_LOAD(TBL_LOAD<T>& a, ROUNDFN* r, SATURATION* s, VECTOR i)
              : Base(a)
   {
      index            = i;
      index.roundfn    = r;
      index.saturation = s;
   }
   
   void load(VECTOR& vexpr)
   {
      VECTOR r_index;
      int bank_width = (4*VCOP_SIMD_WIDTH)/vcop_state<0>::table_cnt;
      
      for (int i = 0; i < VCOP_SIMD_WIDTH; i++)
         r_index[i] = Base::apply_rs(index,index[i]);

      for (int i = 0; i < vcop_state<0>::table_cnt; i++)
      {
         for (int j = 0; j < vcop_state<0>::data_pts; j++)
         {
            /* Calculate the 'base' address we want to access in the table */
            int table_offset = ((r_index[i]+j)*sizeof(T));
            int mem_row    = table_offset/bank_width;
            int bank_offst = table_offset%bank_width;
            T*  ld_addr    = (T*)((char *) Base::address() 
                                         + mem_row*4*VCOP_SIMD_WIDTH
                                         + i * bank_width + bank_offst);
            vexpr[i*vcop_state<0>::data_pts + j] = *ld_addr;
         }
      }
   }

   VECTOR index;
};

/*---------------------------------------------------------------------------*/
/* HISTOGRAM Execution - A histogram object is created to perform 3 jobs:    */
/*                       loading of data from histogram bins, incrementing,  */
/*                       and storage of that data back to the original bins. */
/* Note: In VCOP-C this single instructions is the equivalent of 3 assembly  */
/*       instructions.                                                       */
/*                                                                           */
/*       VHLD hist_base[Vindex][agen], V0, RND_SAT:Px                        */
/*       VADD V0, Vweight, V0                                                */
/*       VHST V0, hist_base[Vindex][agen]                                    */
/*---------------------------------------------------------------------------*/
template <class T>
class HISTOGRAM : public VMODE_BASE<T, VECTOR, HISTOGRAM<T> >
{
public:
   typedef VMODE_BASE<T, VECTOR, HISTOGRAM<T> > Base;
   HISTOGRAM(VLVALUE<T> v, ROUNDFN* r,SATURATION* sa, VECTOR i,
             const VECTOR& w, int s=0) : Base(v,s), weight(w) 
   {
      index            = i;
      index.roundfn    = r;
      index.saturation = sa;
   }
   HISTOGRAM(HISTOGRAM<T>& a, ROUNDFN* r, SATURATION* s, VECTOR i,
             const VECTOR& w) : Base(a), weight(w)
   {
      index            = i;
      index.roundfn    = r;
      index.saturation = s;
   }
   
   /*------------------------------------------------------------------------*/
   /* This function leverages the load called from VECTOR_BASE to perform    */
   /* all 3 main functions of a histogram (load, increment, store)           */
   /*                                                                        */
   /* Rounding and saturation for the index register are taken from vepxr,   */
   /* and it is used as the intermediate location of histogram data that is  */
   /* incremented and then stored, to mimic the execution of the target.     */
   /*------------------------------------------------------------------------*/
   void load(VECTOR& vexpr)
   {
      int bank_width = (4*VCOP_SIMD_WIDTH)/vcop_state<0>::hist_cnt;
      for (int i = 0; i < vcop_state<0>::hist_cnt; i++)
      {
         /* Dummy register used to saturate to type */
         VECTOR data_sat,r_index;

         /* Apply user-defined rounding and saturation to obtain indicies */
         r_index[i] = Base::apply_rs(index, index[i]);

         /* Calculate the address of the bin we want to update */
         int mem_row =    (r_index[i]*sizeof(T))/bank_width;
         int bank_offst = (r_index[i]*sizeof(T))%bank_width;
         T*  ldst_addr = (T*)((char *) Base::address() 
                                     + mem_row*4*VCOP_SIMD_WIDTH
                                     + i * bank_width + bank_offst);

         /* Load the histogram bin (VHLD) */
         vexpr[i] = *ldst_addr;

         /* Increment the bin register (VADD) */
         vexpr[i]+=weight[i];
         
         /* As part of histogram store, saturate the value to type min/max */
         vexpr[i] = Base::apply_rs(data_sat.saturate(),vexpr[i]); 
         
         /* Store the incremented bin register back to the address (VHST) */
         ldst_addr[0] = vexpr[i];
      }
   }

   VECTOR index;
   const VECTOR& weight;
};

/*---------------------------------------------------------------------------*/
/* VECTOR arithmetic operations                                              */
/*---------------------------------------------------------------------------*/
/* v1 + v2  ;  VADD  */
static inline VECTOR operator+(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
      dst[i] = _bit_mask40s(src1[i]) + _bit_mask40s(src2[i]);
   return dst;
}

/*---------------------------------------------------------------------------*/
/*   v0 += v1            ;   VADD                                            */
/*   v0 += v1 + v2       ;   VADD3                                           */
/*   v0 += v1 * v2       ;   VMADD                                           */
/*   v0 += abs(v1 - v2)  ;   VSAD                                            */
/*---------------------------------------------------------------------------*/
void VECTOR::operator+=(const VECTOR& src)
{
   for (int i = 0; i < NELEM; ++i) 
      elem[i] = _bit_mask40s(elem[i]) + 
                _bit_mask40s(src.apply_rounding(src[i]));
}

/* v1 - v2  ;  VSUB  */
static inline VECTOR operator-(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
      dst[i] = _bit_mask40s(src1[i]) - _bit_mask40s(src2[i]); 
   return dst;
}

/*---------------------------------------------------------------------------*/
/*   v0 -= v1       ;   VSUB                                                 */
/*   v0 -= v1 * v1  ;   VMSUB                                                */
/*---------------------------------------------------------------------------*/
void VECTOR::operator-=(const VECTOR& src)
{
   for (int i = 0; i < NELEM; ++i)
      elem[i] = _bit_mask40s(elem[i]) - 
                _bit_mask40s(src.apply_rounding(src[i])); 
}

/*---------------------------------------------------------------------------*/
/* abs(v1)             ; VABS                                                */
/* abs(v1 - v2)        ; VABSDIF                                             */
/* v0 += abs(v2 - v3)  ; VSAD                                                */
/*---------------------------------------------------------------------------*/
static inline VECTOR abs(const VECTOR& src)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i)
   {
      element_t src_40s = _bit_mask40s(src[i]);
      dst[i] = src_40s < 0 ? -src_40s : src_40s;
   }
   return dst;
}

/* (v1 * v2)   ;  VMPY */
static inline VECTOR operator*(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
      dst[i] = _bit_mask17s(src1[i]) * _bit_mask17s(src2[i]); 
   return dst;
}

/* v0 *= v1    ;  VMPY */
void VECTOR::operator*=(const VECTOR& src)
{
   for (int i = 0; i < NELEM; ++i)
   {
      element_t tmp = _bit_mask17s(elem[i]) * _bit_mask17s(src[i]);
      tmp = src.apply_rounding(tmp);
      elem[i] = tmp;
   }
}

/* (v1 & v2)   ;  VAND */
static inline VECTOR operator&(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
      dst[i] = _bit_mask40s(src1[i]) & _bit_mask40s(src2[i]); 
   return dst;
}

/* v0 &= v1 & v1   ;  VAND3 */
void VECTOR::operator&=(const VECTOR& src)
{
   for (int i = 0; i < NELEM; ++i) 
      elem[i] = _bit_mask40s(elem[i]) & _bit_mask40s(src.elem[i]); 
}

/*---------------------------------------------------------------------------*/
/* v1 & ~v2    ; VANDN                                                       */
/* v0 &= ~v1   ; VANDN                                                       */
/* v0 = ~v1    ; VNOT                                                        */
/*---------------------------------------------------------------------------*/
static inline VECTOR operator~(const VECTOR& src)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
      dst[i] = _bit_mask40s(~src[i]);
   return dst;
}

/* (v1 | v2)   ;  VOR */
static inline VECTOR operator|(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
      dst[i] = _bit_mask40s(src1[i]) | _bit_mask40s(src2[i]); 
   return dst;
}

/*---------------------------------------------------------------------------*/
/* v0 |= v1 | v2   ;  VOR3                                                   */
/* v0 |= v1 << v2  ;  VSHFOR                                                 */
/* v0 |= v1 >> v2  ;  VSHFOR                                                 */
/*---------------------------------------------------------------------------*/
void VECTOR::operator|=(const VECTOR& src)
{
   for (int i = 0; i < NELEM; ++i) 
      elem[i] = _bit_mask40s(elem[i]) | _bit_mask40s(src.elem[i]); 
}

/* v1 ^ v2   ;  VXOR */
static inline VECTOR operator^(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
      dst[i] = _bit_mask40s(src1[i]) ^ _bit_mask40s(src2[i]); 
   return dst;
}

/* v0 ^= v1 ^ v2   ;  VXOR3  */
void VECTOR::operator^=(const VECTOR& src)
{
   for (int i = 0; i < NELEM; ++i) 
      elem[i] = _bit_mask40s(elem[i]) ^ _bit_mask40s(src.elem[i]); 
}

/*---------------------------------------------------------------------------*/
/* min(v1, v2)        ;  VMIN                                                */
/* v1 = min(v1, v2)   ;  VMIN                                                */
/*---------------------------------------------------------------------------*/
static inline VECTOR min(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      element_t diff = _bit_mask34s(src1[i] - src2[i]);
      dst[i] = (diff < 0 ? _bit_mask33s(src1[i]) : _bit_mask33s(src2[i]));
   }
   return dst;
}

/*---------------------------------------------------------------------------*/
/* max(v1, v2)        ;  VMAX                                                */
/* v1 = max(v1, v2)   ;  VMAX                                                */
/*---------------------------------------------------------------------------*/
static inline VECTOR max(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      element_t diff = _bit_mask34s(src1[i] - src2[i]);
      dst[i] = (diff > 0 ? _bit_mask33s(src1[i]) : _bit_mask33s(src2[i]));
   }
   return dst;
}

/*---------------------------------------------------------------------------*/
/* minf(v1, v2)        ;  VMINSETF                                           */
/* v1 = minf(v1, v2)   ;  VMINSETF                                           */
/*---------------------------------------------------------------------------*/
static inline VECTOR_PAIR minf(const VECTOR& src1, VECTOR& src2)
{
   static VECTOR dst;
   static VECTOR temp_src2;
   temp_src2.copy_elements(src2);

   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      temp_src2[i] = (_bit_mask34s(src1[i] - src2[i]) < 0);
      
      if(temp_src2[i])
         dst[i]  = _bit_mask33s(src1[i]);
      else
         dst[i] =  _bit_mask33s(src2[i]);
   }
   return VECTOR_PAIR(dst,temp_src2);
}

/*---------------------------------------------------------------------------*/
/* maxf(v1, v2)        ;  VMAXSETF                                           */
/* v1 = maxf(v1, v2)   ;  VMAXSETF                                           */
/*---------------------------------------------------------------------------*/
static inline VECTOR_PAIR maxf(const VECTOR& src1, VECTOR& src2)
{
   static VECTOR dst;
   static VECTOR temp_src2;

   for (int i = 0; i < VECTOR::NELEM; ++i)
   {
      temp_src2[i] = (_bit_mask34s(src1[i] - src2[i]) > 0);
      
      if(temp_src2[i])
         dst[i]  = _bit_mask33s(src1[i]);
      else
         dst[i] =  _bit_mask33s(src2[i]);
   }
   return VECTOR_PAIR(dst,temp_src2);
}

/*---------------------------------------------------------------------------*/
/* v1 << v2        ; VSHF                                                    */
/* v0 |= v1 << v2  ; VSHFOR                                                  */
/*---------------------------------------------------------------------------*/
static inline VECTOR operator<<(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      element_t val   = _bit_mask40s(src1[i]);
      element_t count = _bit_mask6s(src2[i]);
      
      dst[i] =  (std::abs((int)count) >= 40 ? 0
                                            : (count >= 0 ? val << count
                                                          : val >> -count));
      dst[i] = _bit_mask40s(dst[i]);
   }
   return dst;
}

/*  -v1        ; ??? */
static inline VECTOR operator-(const VECTOR& src)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
      dst[i] = -src[i];
   return dst;
}

/* round(v1, v2)   ;  VROUND */
static inline VECTOR round(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      unsigned int bits = _bit_mask5u(src2[i]);
      if (bits == 0) dst[i] = _bit_mask40s(src1[i]);
      else           dst[i] = _bit_mask40s((src1[i] + (1 << (bits-1)))
                                           >> bits);
   }
   return dst;
}

/* v1 == v2   ;  VCMPEQ */
static inline VECTOR operator==(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
      dst[i] = (_bit_mask40s(src1[i]) == _bit_mask40s(src2[i])); 
   return dst;
}

/* v1 > v2   ;  VCMPGT */
static inline VECTOR operator>(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
      dst[i] = (_bit_mask40s(src1[i]) > _bit_mask40s(src2[i])); 
   return dst;
}

/* v1 >= v2   ;  VCMPGE */
static inline VCMPGE_EXPR operator>=(const VECTOR& src1, const VECTOR& src2)
{
   return VCMPGE_EXPR(src1, src2);
}

/* v1 < v2   ;  VCMPGT */
static inline VECTOR operator<(const VECTOR& src1, const VECTOR& src2)
{
   return (src2 > src1); 
}

/* v1 <= v2   ;  VCMPGE */
static inline VCMPGE_EXPR operator<=(const VECTOR& src1, const VECTOR& src2)
{
   return (src2 >= src1); 
}

/* v3 = select(v1, v2, v3)           ; VSEL */
static inline VECTOR select(const VECTOR& src1, const VECTOR& src2,
                            const VECTOR& src3)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      if  (_bit_mask40s(src1[i]) != 0) 
	 dst[i] = _bit_mask40s(src2[i]); 
      else if (_bit_mask40s(src1[i]) == 0) 
	 dst[i] = _bit_mask40s(src3[i]); 
   }
   return dst;
}

/* pack(v1 >= v2)                 ; VBITPK */
static inline VECTOR pack(const VCMPGE_EXPR &src)
{
   VECTOR dst;

   int val = 0;
   for (int i = 0; i < VECTOR::NELEM; ++i)
   {
      element_t x = _bit_mask40s(src.lhs[i]);
      element_t y = _bit_mask40s(src.rhs[i]);
      element_t diff_34b = _bit_mask34s(x - y);

      val |= (diff_34b >= 0) << i;
   }

   dst.init_elements(val);
   return dst;
}

/* v3 = unpack(v1, v2)   ; VBITUNPK */
/*****************************************************************************/
/* For each bit in src1[0], if the value at bit n in [0..NELEM] is 1, then   */
/* dst[n] = src2[n], otherwise, dst[n] = 0.                                  */
/*****************************************************************************/
static inline VECTOR unpack(const VECTOR& src1, VECTOR& src2)
{
   VECTOR dst;
   int val = src1[0];
   for (int i = 0; i < VECTOR::NELEM; ++i) 
       if ((val >> i) & 1u)
           dst[i] = _bit_mask40s(src2[i]);
   return dst;
}

/* apply_sign(src1, src2)   ; VSIGN */
static inline VECTOR apply_sign(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      element_t val1 = _bit_mask40s(src1[i]); 
      element_t val2 = _bit_mask40s(src2[i]); 
      dst[i] = ((val1 == 0) ? 0 : ((val1 < 0)  ? -val2 : val2)); 
   }
   return dst;
}

/* interleave_bits(v1, v2)   ; VBITI */
static inline VECTOR interleave_bits(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      int val = 0;
      for (int j = 0; j < 16; ++j)
      {
	 val |= ((src2[i] >> j) & 1u) << j*2;
	 val |= ((src1[i] >> j) & 1u) << j*2 + 1;
      }
      dst[i] = _bit_mask32u(val);
   }
   return dst;
}

/* deinterleave_bits(v1) ; VBITDI */
static inline VECTOR_PAIR deinterleave_bits(const VECTOR& src)
{
   static VECTOR v1, v2;

   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      element_t srci_32u = _bit_mask32u(src[i]);
      int val1 = 0, val2 = 0;

      for (int j = 0; j < 16; ++j)
      {
	 val2 |= ((srci_32u >> (j*2))     & 1u) << j;
	 val1 |= ((srci_32u >> (j*2 + 1)) & 1u) << j;
      }
      v1[i] = val1;
      v2[i] = val2;
   }

   return VECTOR_PAIR(v1, v2); 
}

/* jus16(v1) ; VSHF16 */
static inline VECTOR_PAIR jus16(const VECTOR& src)
{
   static VECTOR v1, v2;

   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      element_t srci_33b = _bit_mask33s(src[i]);
      v1[i] = (srci_33b & 0xffffu) << 16;
      v2[i] = srci_33b >> 16;
   }

   return VECTOR_PAIR(v1, v2); 
}

/*---------------------------------------------------------------------------*/
/* binlog(v1)   ; VBINLOG                                                    */
/* implementation copied from C model -- see for details                     */
/*---------------------------------------------------------------------------*/
static inline VECTOR binlog(const VECTOR& src)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      unsigned int x = _bit_mask32u(src[i]);
      unsigned int y;

      if      (x & (1U<<31))  y = (15U<<28)  | ((x - (1U<<31)) >> 3);
      else if (x & (1U<<30))  y = (14U<<28)  | ((x - (1U<<30)) >> 2);
      else if (x & (1U<<29))  y = (13U<<28)  | ((x - (1U<<29)) >> 1);
      else if (x & (1U<<28))  y = (12U<<28)  | ((x - (1U<<28)) >> 0);
      else if (x & (1U<<27))  y = (11U<<28)  | ((x - (1U<<27)) << 1);
      else if (x & (1U<<26))  y = (10U<<28)  | ((x - (1U<<26)) << 2);
      else if (x & (1U<<25))  y = ( 9U<<28)  | ((x - (1U<<25)) << 3);
      else if (x & (1U<<24))  y = ( 8U<<28)  | ((x - (1U<<24)) << 4); 
      else if (x & (1U<<23))  y = ( 7U<<28)  | ((x - (1U<<23)) << 5); 
      else if (x & (1U<<22))  y = ( 6U<<28)  | ((x - (1U<<22)) << 6); 
      else if (x & (1U<<21))  y = ( 5U<<28)  | ((x - (1U<<21)) << 7);
      else if (x & (1U<<20))  y = ( 4U<<28)  | ((x - (1U<<20)) << 8); 
      else if (x & (1U<<19))  y = ( 3U<<28)  | ((x - (1U<<19)) << 9); 
      else if (x & (1U<<18))  y = ( 2U<<28)  | ((x - (1U<<18)) << 10);
      else if (x & (1U<<17))  y = ( 1U<<28)  | ((x - (1U<<17)) << 11);
      else                    y = ( 0U<<28)  | ( x             << 11);

      dst[i] = _bit_mask32u(y);
   }
   return dst;
}

/* count_bits(v1)   ; VBITC */
static inline VECTOR count_bits(const VECTOR& src)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      int val = 0;
      for (int j = 0; j < 32; ++j)
	 if (((src[i] >> j) & 1u) != 0) ++val;
      dst[i] = val;
   }
   return dst;
}

/* reverse_bits(v1)  ; VBITR */
static inline VECTOR reverse_bits(const VECTOR& src)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      unsigned int val = 0;
      for (int j = 0; j < 32; ++j)
         val |= ((src[i] >> j) & 1u) << (31-j); 
      dst[i] = val;
   }
   return dst;
}

/* transpose_bits(v1)  ; VBITTR */
static inline VECTOR transpose_bits(const VECTOR& src)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      int val = 0;
      for (int j = 0; j < VECTOR::NELEM; ++j)
         val |= ((src[j] >> i) & 1u) << j;
      dst[i] = val;
   }
   return dst;
}

/* v3 = leading_bit(v1, v2)    ; LMBD  */
static inline VECTOR leading_bit(const VECTOR& src1, const VECTOR& src2)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      int pos = 39; 
      int bit = (src2[i] & 1u); 
      for ( ; pos >= 0; --pos) 
	 if (((src1[i] >> pos) & 1u) == bit) break; 
      dst[i] = pos;   /* -1 if not found */
   }
   return dst;
}

/* v1 + hi(v2)       ; VADDH */
static inline VECTOR hi(const VECTOR& src)
{
   VECTOR dst;
   for (int i = 0; i < VECTOR::NELEM; ++i) 
      dst[i] = _bit_mask40s(src[i]) >> 32; 
   return dst;
}

/*---------------------------------------------------------------------------*/
/* (v1,v2).minmax()   ; VSORT2                                               */
/* (vmin, vmax) = (v1,v2).minmax()   ; VSORT2                                */
/*---------------------------------------------------------------------------*/
VECTOR_PAIR& VECTOR_PAIR::minmax()
{
   for (int i = 0; i < VECTOR::NELEM; ++i) 
   {
      element_t first_40s = _bit_mask40s(first[i]);
      element_t second_40s = _bit_mask40s(second[i]);
      
      element_t diff_34s = _bit_mask34s(first[i]-second[i]);
      
      if (diff_34s >= 0)
      {
         first[i]  = _bit_mask33s(second_40s);
         second[i] = _bit_mask33s(first_40s); 
      }
      else
      {
         first[i]  = _bit_mask33s(first_40s); 
         second[i] = _bit_mask33s(second_40s);
      }
   }
   return *this;
}

/*---------------------------------------------------------------------------*/
/* (v1, v2).addsub()   ; VADDSUB                                             */
/* (vsum, vdif) = (v1,v2).addsub()   ; VADDSUB                               */
/*---------------------------------------------------------------------------*/
VECTOR_PAIR& VECTOR_PAIR::addsub()
{
   VECTOR sum  = first + second;
   VECTOR diff = first - second;
   first  = sum;
   second = diff;

   return *this;
}

/*---------------------------------------------------------------------------*/
/* (v1, v2).interleave()  ; VINTRLV                                          */
/* (vd1, vd2) = (v1, v2).interleave()  ; VINTRLV                             */
/*---------------------------------------------------------------------------*/
VECTOR_PAIR& VECTOR_PAIR::interleave()
{
   VECTOR      v1 = first, v2 = second;
   VECTOR_PAIR src(v1, v2); 

   for (int i = 0; i < VECTOR::NELEM * 2; ++i) 
      (*this)[i] = src[interleave_index(i)]; 
   
   return *this;
}

/*---------------------------------------------------------------------------*/
/* (v1, v2).deinterleave()   ; VDINTRLV                                      */
/* (vd1, vd2) = (v1, v2).deinterleave()  ; VDINTRLV                          */
/*---------------------------------------------------------------------------*/
VECTOR_PAIR& VECTOR_PAIR::deinterleave()
{
   VECTOR      v1 = first, v2 = second;
   VECTOR_PAIR src(v1, v2); 

   for (int i = 0; i < VECTOR::NELEM * 2; ++i) 
      (*this)[interleave_index(i)] = src[i];

   return *this;
}

/*---------------------------------------------------------------------------*/
/* (v1.v2).interleave2()   ; VINTRLV2                                        */
/* (vd1, vd2) = (v1, v2).interleave2()  ; VINTRLV2                           */
/*---------------------------------------------------------------------------*/
VECTOR_PAIR& VECTOR_PAIR::interleave2()
{
   VECTOR      v1 = first, v2 = second;

   for (int i = 0; i < VECTOR::NELEM ; i++)
   {
      int base_ind = (i / 4) * 2 + (i & 1u);

      (*this)[i]               = ((i & 2u) == 0) ? v1[base_ind]
                                                : v2[base_ind];
      (*this)[i+VECTOR::NELEM] = ((i & 2u) == 0) ? v1[base_ind + 4]
                                                : v2[base_ind + 4];
   }
   return *this;
}

/*---------------------------------------------------------------------------*/
/* (v1.v2).interleave4()   ; VINTRLV4                                        */
/* (vd1, vd2) = (v1, v2).interleave4()  ; VINTRLV4                           */
/*---------------------------------------------------------------------------*/
VECTOR_PAIR& VECTOR_PAIR::interleave4()
{
   VECTOR      v1 = first, v2 = second;

   for (int i = 0; i < VECTOR::NELEM; i++)
   {
      (*this)[i]               = ((i & 4u) == 0) ? v1[i & 3u]
                                               : v2[i & 3u];
      (*this)[i+VECTOR::NELEM] = ((i & 4u) == 0) ? v1[(i & 3u) + 4]
                                               : v2[(i & 3u) + 4];
   }
   return *this;
}

/*---------------------------------------------------------------------------*/
/* (v1.v2).deinterleave2()   ; VDINTRLV2                                     */
/* (vd1, vd2) = (v1, v2).deinterleave2()  ; VDINTRLV2                        */
/*---------------------------------------------------------------------------*/
VECTOR_PAIR& VECTOR_PAIR::deinterleave2()
{
   VECTOR      v1 = first, v2 = second;

   for (int i = 0; i < VECTOR::NELEM ; i++)
   {
      int base_ind = ((i & 2u) >> 1) * 4 + (i & 1u);

      (*this)[i]               = ((i < 4) ? v1[base_ind]
                                          : v2[base_ind]);
      (*this)[i+VECTOR::NELEM] = ((i < 4) ? v1[base_ind+2]
                                          : v2[base_ind+2]);
   }
   return *this;
}

/*---------------------------------------------------------------------------*/
/* (v1.v2).swap(v3)   ; VSWAP                                                */
/* (vd1, vd2) = (v1, v2).swap(vcnd)  ; VSWAP                                 */
/*---------------------------------------------------------------------------*/
VECTOR_PAIR& VECTOR_PAIR::swap(const VECTOR& cnd)
{
   element_t temp;

   for (int i = 0; i < VECTOR::NELEM ; i++)
   {
      if (cnd[i] & 1u)
      {
         temp                     = (*this)[i];
         (*this)[i]               = (*this)[i+VECTOR::NELEM];
         (*this)[i+VECTOR::NELEM] = temp;
      }
   }
   return *this;
}

/*---------------------------------------------------------------------------*/
/* __vcop_bitmask() - Truncate a value to a particular width. Used to mimic  */
/*    VCOP bit widths in vector arithmetic operations.                       */
/*---------------------------------------------------------------------------*/
static inline long long __vcop_bitmask(long long src, int width)
{
   long long y, sign_mask, quant_mask;
   sign_mask = 1;
   sign_mask <<= (width - 1);
   quant_mask = sign_mask - 1;

   if (src & sign_mask)
      y = -sign_mask + (src & quant_mask);
   else
      y = src & quant_mask;

   return y;
}

static inline long long __vcop_bitmask_uns(long long src, int width)
{
   unsigned long long quant_mask;
   quant_mask = 1u;
   quant_mask = (quant_mask << width) - 1u;

   return (src & quant_mask);
}

/*---------------------------------------------------------------------------*/
/* ISINT - Compile-time test to determine if T is an integral type           */
/*    ISINT<T>::value == true if so, false if not                            */
/*    Note that none of the functions here are called, or even implemented;  */
/*    they are only used in sizeof() context for compile-time processing.    */
/*    See Modern C++ Design, Alexandrescu, page 34.                          */
/*---------------------------------------------------------------------------*/
template <class T>
class ISINT
{
   static T  makeT();        /* dummy expression with type T */
   struct c1 { char a; };    /* sizeof(c1) == 1 */
   struct c2 { char a[2]; }; /* sizeof(c2) == 2 */
   static c1 test(int);      /* returns size 1 if arg is covertible to int  */
   static c2 test(...);      /* returns size 2 if not  */
   public:
   static const bool value = ( sizeof(test(makeT())) == sizeof(c1) );
};


} /* end namespace VCOP */

/*---------------------------------------------------------------------------*/
/* Define types and identifiers for user declarations.                       */
/* Export identifiers available to the user from the namespace.              */
/*---------------------------------------------------------------------------*/
typedef vcop::VPTR<char>            __vptr_int8;
typedef vcop::VPTR<unsigned char>   __vptr_uint8;
typedef vcop::VPTR<int>             __vptr_int32;
typedef vcop::VPTR<unsigned int>    __vptr_uint32;
typedef vcop::VPTR<short>           __vptr_int16;
typedef vcop::VPTR<unsigned short>  __vptr_uint16;
typedef vcop::VPTR_ARR<char>           __vptr_int8_arr;
typedef vcop::VPTR_ARR<unsigned char>  __vptr_uint8_arr;
typedef vcop::VPTR_ARR<int>            __vptr_int32_arr;
typedef vcop::VPTR_ARR<unsigned int>   __vptr_uint32_arr;
typedef vcop::VPTR_ARR<short>          __vptr_int16_arr;
typedef vcop::VPTR_ARR<unsigned short> __vptr_uint16_arr;
typedef vcop::VECTOR                __vector;
typedef vcop::AGEN                  __agen;

/*---------------------------------------------------------------------------*/
/* These are internal registers that can be used in place of user-defined    */
/* ones                                                                      */
/*---------------------------------------------------------------------------*/
template <int N>
struct global_vregs
{
   static __vector reg;
};

template <int N> __vector global_vregs<N>::reg;

#define V0 global_vregs<0>::reg
#define V1 global_vregs<1>::reg
#define V2 global_vregs<2>::reg
#define V3 global_vregs<3>::reg
#define V4 global_vregs<4>::reg
#define V5 global_vregs<5>::reg
#define V6 global_vregs<6>::reg
#define V7 global_vregs<7>::reg
#define V8 global_vregs<8>::reg
#define V9 global_vregs<9>::reg
#define V10 global_vregs<10>::reg
#define V11 global_vregs<11>::reg
#define V12 global_vregs<12>::reg
#define V13 global_vregs<13>::reg
#define V14 global_vregs<14>::reg
#define V15 global_vregs<15>::reg

using vcop::collate;
using vcop::expand;
using vcop::abs;
using vcop::min;
using vcop::max;
using vcop::round;
using vcop::select;
using vcop::pack;
using vcop::unpack;
using vcop::apply_sign;
using vcop::interleave_bits;
using vcop::deinterleave_bits;
using vcop::binlog;
using vcop::count_bits;
using vcop::reverse_bits;
using vcop::transpose_bits;
using vcop::leading_bit;
using vcop::hi;
using vcop::jus16;

#else /* VCOP_HOST_EMULATION */

/*---------------------------------------------------------------------------*/
/* This code is used when the kernel is translated for native execution      */
/* on VCOP. It defines macros that allow the initialization code             */
/* to compile.                                                               */
/*---------------------------------------------------------------------------*/

#ifndef VCOP_HOST_EMULATION
  #define VCOP_HOST_EMULATION 0
#endif

#include "arp32.h"
#include "vcopmem.h"

/*---------------------------------------------------------------------------*/
/* ARP32 VCOP SWITCHBUF Intrinsic                                            */
/*---------------------------------------------------------------------------*/
void __BUILTIN_M _vcop_switchbuf(__CONST(0, 0xFFFFF) unsigned int);

/*---------------------------------------------------------------------------*/
/* VCOP COMPILER AIDED MEMORY ALLOCATION                                     */
/*                                                                           */
/* void *vcop_malloc(VCOP_MEMHEAP heap, int size)                            */
/*       - Allocate 'size' bytes from a VCOP heap, using heap id values:     */
/*         VCOP_IBUFLA, VCOP_IBUFHA, VCOP_IBUFLB, VCOP_IBUFHB, VCOP_WMEM     */
/*                                                                           */
/* void *vcop_memalign(VCOP_MEMHEAP heap, VCOP_ALIGNSPEC align, int size)    */
/*       - Allocate 'size' bytes from a VCOP heap, using heap id values as   */
/*         above and alignment specification values:                         */
/*         VCOP_DEFAULT_ALIGN = 0x20 (used by vcop_malloc()),                */
/*         VCOP_1K, VCOP_2K, VCOP_4K, VCOP_8K, VCOP_16K                      */
/*                                                                           */
/* void  vcop_free(void *userptr)                                            */
/*       - Free memory indicated by pointer.  Allocator will automatically   */
/*         determine the corresponding heap                                  */
/*                                                                           */
/* void  vcop_setview(VCOP_MEMVIEW view)                                     */
/*       - Set allocator according to VCOP_MEMFLAT or VCOP_MEMALIASED view.  */
/*         Under aliased view, allocator will also manage memory for aliased */
/*         heaps when memory is allocated from IBUFLA or IBUFHA.             */
/*         views: VCOP_MEMFLAT (default) or VCOP_MEMALIASED                  */ 
/*                                                                           */
/* void  vcop_minit()                                                        */
/*       - Reset the state of the VCOP memory allocator.  This routine is    */
/*         invoked automatically when vcop_malloc() is called for the very   */
/*         first time.  Note: It does NOT free previously allocated memory.  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
void  vcop_setview  (VCOP_MEMVIEW view);
void *vcop_malloc   (VCOP_MEMHEAP heap, int size);
void *vcop_memalign (VCOP_MEMHEAP heap, VCOP_ALIGNSPEC align, int size);
void  vcop_free     (void *userptr);
void  vcop_minit    (void);

/* Maximum and Minimum values for the vcop integral types. */
#define VCC_S32_MAX 2147483647
#define VCC_S32_MIN (-2147483648L)

#define VCC_U32_MAX 4294967295U
#define VCC_U32_MIN 0

#define VCC_S16_MAX 32767
#define VCC_S16_MIN (-32768)

#define VCC_U16_MAX 65535
#define VCC_U16_MIN 0

#define VCC_S8_MAX 127
#define VCC_S8_MIN (-128)

#define VCC_U8_MAX 255
#define VCC_U8_MIN 0

/* Memory locations for the start of VCOP buffers. Taken from linker.cmd */
#define ibufla ((void*) 0x40050000)
#define ibufha ((void*) 0x40054000)
#define ibuflb ((void*) 0x40070000)
#define ibufhb ((void*) 0x40074000)
#define wbuf   ((void*) 0x40040000)

/* Types for data buffer pointers used in the kernel */
typedef char*            __vptr_int8;
typedef unsigned char*   __vptr_uint8;
typedef short*           __vptr_int16;
typedef unsigned short*  __vptr_uint16;
typedef int*             __vptr_int32;
typedef unsigned int*    __vptr_uint32;
typedef char**           __vptr_int8_arr;
typedef unsigned char**  __vptr_uint8_arr;
typedef short**          __vptr_int16_arr;
typedef unsigned short** __vptr_uint16_arr;
typedef int**            __vptr_int32_arr;
typedef unsigned int**   __vptr_uint32_arr;

/* Macros used in vector core intrinsics to refer to Pregs and Agens */
#define _PREG(n) (n)
#define _AGEN(n) (n)
#define _VREG(n)    (__vcop_vreg((n)))
#define _VPAIR(n,m) (__vcop_pair((n),(m)))

/* Type used to model vector registers by scalar core compiler */
typedef unsigned int __vcop_vreg_t;

/*---------------------------------------------------------------------------*/
/* Parameter block for initializing parameter registers from scalar core     */
/* P0 and P1 are implied values, for first location is P2                    */
/*---------------------------------------------------------------------------*/
extern unsigned short __vcop_parameter_block[];
#define _VCOP_PARM(n) (__vcop_parameter_block[n-2])

/* Macros for parameter block initializations */
#define __vcop_pblock_init16(pb,n,x) \
   pb[n-2] = (unsigned short)(x)

#define __vcop_pblock_init32(pb,n,x) \
    pb[n-2] = (unsigned short)(((unsigned int)(x)) & 0xFFFFu); \
    pb[n-1] = (unsigned short)(((unsigned int)(x)) >> 16)

#define __vcop_pblock_4param_init(pb,n,hic,his,loc,los) \
   ((pb[n-2] = ((unsigned short)(hic))), \
    (pb[n-1] = ((unsigned short)(his))),   \
    (pb[n]   = ((unsigned short)(loc))),   \
    (pb[n+1] = ((unsigned short)(los))))   \

/* Builds the preg used for custom distributions. */
#define _CUSTOM(x) (unsigned int)( (x[0] | x[1] << 4 | x[2] << 8 | x[3] << 12)|\
                        (x[4] << 16 | x[5] << 20 | x[6] << 24 | x[7] << 28) )

/* constants and macro for encoding VSTORE rounding/saturation mode */
enum { RM_NONE=0, RM_ROUND=1, RM_TRUNC=2 };
enum { SM_NONE=0, SM_SYMM=1, SM_ASYMM=2, SM_4PARAM=3, 
       SM_SYMM32=4, SM_ASYMM32=5 };

#define __vcop_vop_round(sat_mode, rnd_bits) \
        (((sat_mode) << 5) | ((rnd_bits) & 0x1Fu))

#define __vcop_store_round_sat(sat_mode, sat_preg, rnd_mode, rnd_bits) \
      (((sat_mode)<<13) | ((sat_preg)<<7) | ((rnd_mode)<<5) | (rnd_bits & 0x1Fu))

/* vcmple and vcmplt turn into vcmpge and vcmpgt with switched sources */
#define __vcop_vcmple(s1, s2, d) __vcop_vcmpge(s2, s1, d)
#define __vcop_vcmplt(s1, s2, d) __vcop_vcmpgt(s2, s1, d)

/* Constants and buffer switch management (vcop_macros.h) */
#define NO_SAT           0
#define SYMM             1
#define ASYMM            2
#define S4PARAM          3
#define SYMM32           4
#define ASYMM32          5
                         
#define NO_RND           0
#define RND              1
#define TRU              2
#define LSH              3
                         
#define NO_CIRC          0
#define CIRC_1K          1
#define CIRC_2K          2
#define CIRC_4K          3
#define CIRC_8K          4
#define CIRC_16K         5
#define CIRC_32K         6
                         
#define WBUF_VCOP        (1u)
#define WBUF_SYST        (0u)
#define IBUFHB_VCOP      (1u)
#define IBUFHB_SYST      (0u)
#define IBUFHA_VCOP      (1u)
#define IBUFHA_SYST      (0u)
#define IBUFLB_VCOP      (1u)
#define IBUFLB_SYST      (0u)
#define IBUFLA_VCOP      (1u)
#define IBUFLA_SYST      (0u)

#define FLAT_MEM_VIEW    0
#define ALIAS_128K_VIEW  0x11

#define MEM_BUF_VIEW      0x40080020
#define MEM_BUF_SWITCH    0x40080024

#define BUF_PING         1
#define BUF_PONG         0

/*-----------------------------------------------------------------------*/
/* These two intrinsics define the signals VWDONE and VWRDY:             */
/*    VWDONE: Force scalar core to wait for the vector core to run to    */
/*            completion.                                                */
/*    VWRDY : Force scalar core to wait until vector core is ready to    */
/*            accept additional vector instructions.                     */
/*-----------------------------------------------------------------------*/
void     _vcop_vloop_done();    /* VWDONE */
void     _vcop_vloop_ready();   /* VWRDY */

/*-----------------------------------------------------------------------*/
/* This macro decides which buffers belong to the System (ARP32/DMA)     */
/* and which belong to VCOP. A value of '1' in the buffer locations      */
/* implies the buffer is owned by the VCOP, a value of '0' means the     */
/* buffer is owned by the System.                                        */
/*-----------------------------------------------------------------------*/
#define VCOP_WRITE_BUF_SWITCH(v)               _vcop_switchbuf(v)
#define VCOP_BUF_SWITCH_SET(w, hb, lb, ha, la) _vcop_switchbuf(     \
                                 ((unsigned int)(w  & 0xFu) << 16) | \
                                 ((unsigned int)(hb & 0xFu) << 12) | \
                                 ((unsigned int)(lb & 0xFu) << 8)  | \
                                 ((unsigned int)(ha & 0xFu) << 4)  | \
                                               ((la & 0xFu))   )

/*-----------------------------------------------------------------------*/
/* These macros switch between the 'ping' buffer setup and the 'pong'    */
/* buffer setup for concurrent ARP32 setup during EVE execution.         */
/*-----------------------------------------------------------------------*/
static inline void VCOP_BUF_SWITCH_AVCOP()
{
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_VCOP,
                        IBUFLA_VCOP);
}

static inline void VCOP_BUF_SWITCH_BVCOP()
{
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST,
                        IBUFLA_SYST);
}

/*-----------------------------------------------------------------------*/
/* This macro merely toggles all the values around effecting a context   */
/* switch between the VCOP and System buffers. This is useful when       */
/* communicating with DMA and ping-pong buffering is needed.             */
/* This also eleminates the need to remember which buffer belonged to    */
/* whom prior to switching.                                              */
/*-----------------------------------------------------------------------*/
static inline unsigned int VCOP_BUF_SWITCH_TOGGLE (unsigned int flag)
{
    if (flag == BUF_PING)  VCOP_BUF_SWITCH_AVCOP();
    else                   VCOP_BUF_SWITCH_BVCOP();
    flag   = (flag ^ 0x1u);
    return (flag);
}

/*-----------------------------------------------------------------------*/
/* This function reads and returns the value contained in the            */
/* MEM_BUF_SWITCH MMR.                                                   */
/*-----------------------------------------------------------------------*/
static inline unsigned int VCOP_READ_BUF_SWITCH()
{
   volatile unsigned int mem_switch_val = *(volatile unsigned int*)(MEM_BUF_SWITCH);
   return mem_switch_val;
}

/*-----------------------------------------------------------------------*/
/* This macro sets the memory view to be either FLAT_MEM_VIEW or the     */
/* ALIAS_128K_VIEW. FLAT_MEM_VIEW is what ARP32 see always. The          */
/* ALIAS_128K_VIEW has the IBUFLB and IBUFHB aliased with IBUFLA and     */
/* IBUFHA.                                                               */
/*-----------------------------------------------------------------------*/

static inline void VCOP_SET_MEM_VIEW (unsigned int VIEW)
{
   volatile unsigned int value_guard;
   *(volatile unsigned int *)(MEM_BUF_VIEW) = VIEW;
   value_guard = *(volatile unsigned int *)(MEM_BUF_VIEW);
}
	
/*-----------------------------------------------------------------------*/
/* This macro initializes the pregs' offset to 0.                        */
/*-----------------------------------------------------------------------*/

#define WPREG_INIT() {offset = 0;}

/*-----------------------------------------------------------------------*/
/* This macro helps initialize a parameter register with a 32-bit        */
/* address value.                                                        */
/*-----------------------------------------------------------------------*/

#define WPREG32(ptr)  {                                                                                     \
	                  pregs[offset++] = (unsigned short) ((unsigned int) (ptr) & 0x0000FFFFu);               \
                          pregs[offset++] = (unsigned short) (((unsigned int) (ptr) >> 16) & 0x0000FFFFu);   \
	              }


/*-----------------------------------------------------------------------*/
/* This macro helps initialize a parameter register with a value which   */
/* is a sum of an immediate value and a 32-bit address value giving an   */
/* giving an 'offset' from that particular address.                      */
/*-----------------------------------------------------------------------*/

#define WPREGL32(ptr, imm)  {                                                                    \
	                       temp = (unsigned int) (ptr) + imm;                                    \
	                       pregs[offset++] = (unsigned short) (temp & 0x0000FFFFu);               \
                               pregs[offset++] = (unsigned short) ((temp >> 16) & 0x0000FFFFu);   \
	                    }


/*-----------------------------------------------------------------------*/
/* This macro helps setup the circular buffer address for a parameter    */
/* register.                                                             */
/*-----------------------------------------------------------------------*/

#define WPREGCIRC32(ptr, circ) {                                                                                            \
	                                   temp = (unsigned int) (ptr) + imm;                                                   \
	                                   pregs[offset++] = (unsigned short) (temp & 0x0000FFFFu);                              \
                                           pregs[offset++] = (unsigned short) (((temp + (circ << 20)) >> 16) & 0x0000FFFFu); \
                               }


/*-----------------------------------------------------------------------*/
/* This macro helps setup an offset from a address as a new circular     */
/* buffer address.                                                       */
/*-----------------------------------------------------------------------*/

#define WPREGCIRCL32(ptr, imm1, circ) {                                                                                     \
	                                   temp = (unsigned int) (ptr) + imm;                                                   \
	                                   pregs[offset++] = (unsigned short) (temp & 0x0000FFFFu);                              \
                                           pregs[offset++] = (unsigned short) (((temp + (circ << 20)) >> 16) & 0x0000FFFFu); \
	                              }


/*-----------------------------------------------------------------------*/
/* This macro helps initialize a parameter register with a 16-bit value. */
/*-----------------------------------------------------------------------*/

#define WPREG16(val) pregs[offset++] = val;


/*-----------------------------------------------------------------------*/
/* This macro helps initialize a parameter register with a 16-bit value. */
/* It also returns the offset into the 'pregs' array for that particular */
/* value. This is very useful for returning the location of the          */
/* saturation parameters which is needed by the WPREG_RNDMS_SATMP macro  */
/* to set the value of 'prm'.                                            */
/*-----------------------------------------------------------------------*/

#define WPREG16_RETOFST(val, ofst) {               \
	ofst = offset + 2;                             \
	pregs[offset++]  = val;                        \
}


/*-----------------------------------------------------------------------*/
/* This macro helps setup the round mode along with the shift amount.    */
/* The three modes are NO_RND = no rounding, RND = rounding and          */
/* TRU = truncation.                                                     */
/*-----------------------------------------------------------------------*/

#define WPREG_RNDMS(rnd_mode, rnd_shift)  pregs[offset++] = ((rnd_mode << 5) | (rnd_shift << 0));

/*-----------------------------------------------------------------------*/
/* This macro helps setup the round mode, shift amount and saturation    */
/* mode and parameters as well.                                          */
/* The saturation modes are: NO_SAT, SYMM, ASYMM, S4PARAM, SYMM32 and    */
/* ASYMM32. For details look at the latest EVE Spec.                     */
/*-----------------------------------------------------------------------*/

#define WPREG_RNDMS_SATMP(rnd_mode, rnd_shift, sat_mode, prm) pregs[offset++] = ((sat_mode << 13) | (prm << 7) | (rnd_mode << 5) | (rnd_shift << 0));

static inline void  __vcop_buffers_system()
{
   VCOP_BUF_SWITCH_SET(WBUF_SYST, 
	               IBUFHB_SYST, IBUFLB_SYST, 
		       IBUFHA_SYST, IBUFLA_SYST); 
}

static inline void __vcop_buffers_vcop()
{
   VCOP_BUF_SWITCH_SET(WBUF_VCOP, 
	               IBUFHB_VCOP, IBUFLB_VCOP, 
		       IBUFHA_VCOP, IBUFLA_VCOP); 
}
/* End vcop_macros.h */

#endif

#endif /*__VCOP_H__ */
