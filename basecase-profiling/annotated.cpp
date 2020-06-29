*** File /usr/include/c++/4.8.2/cmath:
                // -*- C++ -*- C forwarding header.
                
                // Copyright (C) 1997-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /** @file include/cmath
                 *  This is a Standard C++ Library file.  You should @c \#include this file
                 *  in your programs, rather than any of the @a *.h implementation files.
                 *
                 *  This is the C++ version of the Standard C Library header @c math.h,
                 *  and its contents are (mostly) the same as that header, but are all
                 *  contained in the namespace @c std (except for names which are defined
                 *  as macros in C).
                 */
                
                //
                // ISO C++ 14882: 26.5  C library
                //
                
                #pragma GCC system_header
                
                #include <bits/c++config.h>
                #include <bits/cpp_type_traits.h>
                #include <ext/type_traits.h>
                #include <math.h>
                
                #ifndef _GLIBCXX_CMATH
                #define _GLIBCXX_CMATH 1
                
                // Get rid of those macros defined in <math.h> in lieu of real functions.
                #undef abs
                #undef div
                #undef acos
                #undef asin
                #undef atan
                #undef atan2
                #undef ceil
                #undef cos
                #undef cosh
                #undef exp
                #undef fabs
                #undef floor
                #undef fmod
                #undef frexp
                #undef ldexp
                #undef log
                #undef log10
                #undef modf
                #undef pow
                #undef sin
                #undef sinh
                #undef sqrt
                #undef tan
                #undef tanh
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR double
                  abs(double __x)
                  { return __builtin_fabs(__x); }
                #endif
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  abs(float __x)
                  { return __builtin_fabsf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  abs(long double __x)
                  { return __builtin_fabsl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    abs(_Tp __x)
                    { return __builtin_fabs(__x); }
                
                  using ::acos;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  acos(float __x)
                  { return __builtin_acosf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  acos(long double __x)
                  { return __builtin_acosl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    acos(_Tp __x)
                    { return __builtin_acos(__x); }
                
                  using ::asin;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  asin(float __x)
                  { return __builtin_asinf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  asin(long double __x)
                  { return __builtin_asinl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    asin(_Tp __x)
                    { return __builtin_asin(__x); }
                
                  using ::atan;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  atan(float __x)
                  { return __builtin_atanf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  atan(long double __x)
                  { return __builtin_atanl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    atan(_Tp __x)
                    { return __builtin_atan(__x); }
                
                  using ::atan2;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  atan2(float __y, float __x)
       ##### ->   { return __builtin_atan2f(__y, __x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  atan2(long double __y, long double __x)
                  { return __builtin_atan2l(__y, __x); }
                #endif
                
                  template<typename _Tp, typename _Up>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    atan2(_Tp __y, _Up __x)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return atan2(__type(__y), __type(__x));
                    }
                
                  using ::ceil;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  ceil(float __x)
                  { return __builtin_ceilf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  ceil(long double __x)
                  { return __builtin_ceill(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    ceil(_Tp __x)
                    { return __builtin_ceil(__x); }
                
                  using ::cos;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  cos(float __x)
   147934924 ->   { return __builtin_cosf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  cos(long double __x)
                  { return __builtin_cosl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    cos(_Tp __x)
                    { return __builtin_cos(__x); }
                
                  using ::cosh;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  cosh(float __x)
                  { return __builtin_coshf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  cosh(long double __x)
                  { return __builtin_coshl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    cosh(_Tp __x)
                    { return __builtin_cosh(__x); }
                
                  using ::exp;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  exp(float __x)
   305412876 ->   { return __builtin_expf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  exp(long double __x)
                  { return __builtin_expl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    exp(_Tp __x)
                    { return __builtin_exp(__x); }
                
                  using ::fabs;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  fabs(float __x)
                  { return __builtin_fabsf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  fabs(long double __x)
                  { return __builtin_fabsl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    fabs(_Tp __x)
                    { return __builtin_fabs(__x); }
                
                  using ::floor;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  floor(float __x)
                  { return __builtin_floorf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  floor(long double __x)
                  { return __builtin_floorl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    floor(_Tp __x)
                    { return __builtin_floor(__x); }
                
                  using ::fmod;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  fmod(float __x, float __y)
                  { return __builtin_fmodf(__x, __y); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  fmod(long double __x, long double __y)
                  { return __builtin_fmodl(__x, __y); }
                #endif
                
                  template<typename _Tp, typename _Up>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    fmod(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return fmod(__type(__x), __type(__y));
                    }
                
                  using ::frexp;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline float
                  frexp(float __x, int* __exp)
                  { return __builtin_frexpf(__x, __exp); }
                
                  inline long double
                  frexp(long double __x, int* __exp)
                  { return __builtin_frexpl(__x, __exp); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    frexp(_Tp __x, int* __exp)
                    { return __builtin_frexp(__x, __exp); }
                
                  using ::ldexp;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  ldexp(float __x, int __exp)
                  { return __builtin_ldexpf(__x, __exp); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  ldexp(long double __x, int __exp)
                  { return __builtin_ldexpl(__x, __exp); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    ldexp(_Tp __x, int __exp)
                    { return __builtin_ldexp(__x, __exp); }
                
                  using ::log;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  log(float __x)
       ##### ->   { return __builtin_logf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  log(long double __x)
                  { return __builtin_logl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    log(_Tp __x)
                    { return __builtin_log(__x); }
                
                  using ::log10;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  log10(float __x)
         815 ->   { return __builtin_log10f(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  log10(long double __x)
                  { return __builtin_log10l(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    log10(_Tp __x)
                    { return __builtin_log10(__x); }
                
                  using ::modf;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline float
                  modf(float __x, float* __iptr)
                  { return __builtin_modff(__x, __iptr); }
                
                  inline long double
                  modf(long double __x, long double* __iptr)
                  { return __builtin_modfl(__x, __iptr); }
                #endif
                
                  using ::pow;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  pow(float __x, float __y)
                  { return __builtin_powf(__x, __y); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  pow(long double __x, long double __y)
                  { return __builtin_powl(__x, __y); }
                
                #if __cplusplus < 201103L
                  // _GLIBCXX_RESOLVE_LIB_DEFECTS
                  // DR 550. What should the return type of pow(float,int) be?
                  inline double
                  pow(double __x, int __i)
                  { return __builtin_powi(__x, __i); }
                
                  inline float
                  pow(float __x, int __n)
                  { return __builtin_powif(__x, __n); }
                
                  inline long double
                  pow(long double __x, int __n)
                  { return __builtin_powil(__x, __n); }
                #endif
                #endif
                
                  template<typename _Tp, typename _Up>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
   654530572 ->     pow(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
   654530572 ->       return pow(__type(__x), __type(__y));
   654530572 ->     }
                
                  using ::sin;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  sin(float __x)
   147933113 ->   { return __builtin_sinf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  sin(long double __x)
                  { return __builtin_sinl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    sin(_Tp __x)
                    { return __builtin_sin(__x); }
                
                  using ::sinh;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  sinh(float __x)
                  { return __builtin_sinhf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  sinh(long double __x)
                  { return __builtin_sinhl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    sinh(_Tp __x)
                    { return __builtin_sinh(__x); }
                
                  using ::sqrt;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  sqrt(float __x)
  1576443686 ->   { return __builtin_sqrtf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  sqrt(long double __x)
                  { return __builtin_sqrtl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
       ##### ->     sqrt(_Tp __x)
       ##### ->     { return __builtin_sqrt(__x); }
                
                  using ::tan;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  tan(float __x)
                  { return __builtin_tanf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  tan(long double __x)
                  { return __builtin_tanl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    tan(_Tp __x)
                    { return __builtin_tan(__x); }
                
                  using ::tanh;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  tanh(float __x)
                  { return __builtin_tanhf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  tanh(long double __x)
                  { return __builtin_tanhl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    tanh(_Tp __x)
                    { return __builtin_tanh(__x); }
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace
                
                #if _GLIBCXX_USE_C99_MATH
                #if !_GLIBCXX_USE_C99_FP_MACROS_DYNAMIC
                
                // These are possible macros imported from C99-land.
                #undef fpclassify
                #undef isfinite
                #undef isinf
                #undef isnan
                #undef isnormal
                #undef signbit
                #undef isgreater
                #undef isgreaterequal
                #undef isless
                #undef islessequal
                #undef islessgreater
                #undef isunordered
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                #if __cplusplus >= 201103L
                  constexpr int
                  fpclassify(float __x)
                  { return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL,
                				FP_SUBNORMAL, FP_ZERO, __x); }
                
                  constexpr int
                  fpclassify(double __x)
                  { return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL,
                				FP_SUBNORMAL, FP_ZERO, __x); }
                
                  constexpr int
                  fpclassify(long double __x)
                  { return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL,
                				FP_SUBNORMAL, FP_ZERO, __x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                              int>::__type
                    fpclassify(_Tp __x)
                    { return __x != 0 ? FP_NORMAL : FP_ZERO; }
                
                  constexpr bool
                  isfinite(float __x)
                  { return __builtin_isfinite(__x); }
                
                  constexpr bool
                  isfinite(double __x)
                  { return __builtin_isfinite(__x); }
                
                  constexpr bool
                  isfinite(long double __x)
                  { return __builtin_isfinite(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                              bool>::__type
                    isfinite(_Tp __x)
                    { return true; }
                
                  constexpr bool
                  isinf(float __x)
                  { return __builtin_isinf(__x); }
                
                  constexpr bool
                  isinf(double __x)
                  { return __builtin_isinf(__x); }
                
                  constexpr bool
                  isinf(long double __x)
                  { return __builtin_isinf(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                              bool>::__type
                    isinf(_Tp __x)
                    { return false; }
                
                  constexpr bool
                  isnan(float __x)
                  { return __builtin_isnan(__x); }
                
                  constexpr bool
                  isnan(double __x)
                  { return __builtin_isnan(__x); }
                
                  constexpr bool
                  isnan(long double __x)
                  { return __builtin_isnan(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                              bool>::__type
                    isnan(_Tp __x)
                    { return false; }
                
                  constexpr bool
                  isnormal(float __x)
                  { return __builtin_isnormal(__x); }
                
                  constexpr bool
                  isnormal(double __x)
                  { return __builtin_isnormal(__x); }
                
                  constexpr bool
                  isnormal(long double __x)
                  { return __builtin_isnormal(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                              bool>::__type
                    isnormal(_Tp __x)
                    { return __x != 0 ? true : false; }
                
                  constexpr bool
                  signbit(float __x)
                  { return __builtin_signbit(__x); }
                
                  constexpr bool
                  signbit(double __x)
                  { return __builtin_signbit(__x); }
                
                  constexpr bool
                  signbit(long double __x)
                  { return __builtin_signbit(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                              bool>::__type
                    signbit(_Tp __x)
                    { return __x < 0 ? true : false; }
                
                  constexpr bool
                  isgreater(float __x, float __y)
                  { return __builtin_isgreater(__x, __y); }
                
                  constexpr bool
                  isgreater(double __x, double __y)
                  { return __builtin_isgreater(__x, __y); }
                
                  constexpr bool
                  isgreater(long double __x, long double __y)
                  { return __builtin_isgreater(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename
                    __gnu_cxx::__enable_if<(__is_arithmetic<_Tp>::__value
                			    && __is_arithmetic<_Up>::__value), bool>::__type
                    isgreater(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return __builtin_isgreater(__type(__x), __type(__y));
                    }
                
                  constexpr bool
                  isgreaterequal(float __x, float __y)
                  { return __builtin_isgreaterequal(__x, __y); }
                
                  constexpr bool
                  isgreaterequal(double __x, double __y)
                  { return __builtin_isgreaterequal(__x, __y); }
                
                  constexpr bool
                  isgreaterequal(long double __x, long double __y)
                  { return __builtin_isgreaterequal(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename
                    __gnu_cxx::__enable_if<(__is_arithmetic<_Tp>::__value
                			    && __is_arithmetic<_Up>::__value), bool>::__type
                    isgreaterequal(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return __builtin_isgreaterequal(__type(__x), __type(__y));
                    }
                
                  constexpr bool
                  isless(float __x, float __y)
                  { return __builtin_isless(__x, __y); }
                
                  constexpr bool
                  isless(double __x, double __y)
                  { return __builtin_isless(__x, __y); }
                
                  constexpr bool
                  isless(long double __x, long double __y)
                  { return __builtin_isless(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename
                    __gnu_cxx::__enable_if<(__is_arithmetic<_Tp>::__value
                			    && __is_arithmetic<_Up>::__value), bool>::__type
                    isless(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return __builtin_isless(__type(__x), __type(__y));
                    }
                
                  constexpr bool
                  islessequal(float __x, float __y)
                  { return __builtin_islessequal(__x, __y); }
                
                  constexpr bool
                  islessequal(double __x, double __y)
                  { return __builtin_islessequal(__x, __y); }
                
                  constexpr bool
                  islessequal(long double __x, long double __y)
                  { return __builtin_islessequal(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename
                    __gnu_cxx::__enable_if<(__is_arithmetic<_Tp>::__value
                			    && __is_arithmetic<_Up>::__value), bool>::__type
                    islessequal(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return __builtin_islessequal(__type(__x), __type(__y));
                    }
                
                  constexpr bool
                  islessgreater(float __x, float __y)
                  { return __builtin_islessgreater(__x, __y); }
                
                  constexpr bool
                  islessgreater(double __x, double __y)
                  { return __builtin_islessgreater(__x, __y); }
                
                  constexpr bool
                  islessgreater(long double __x, long double __y)
                  { return __builtin_islessgreater(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename
                    __gnu_cxx::__enable_if<(__is_arithmetic<_Tp>::__value
                			    && __is_arithmetic<_Up>::__value), bool>::__type
                    islessgreater(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return __builtin_islessgreater(__type(__x), __type(__y));
                    }
                
                  constexpr bool
                  isunordered(float __x, float __y)
                  { return __builtin_isunordered(__x, __y); }
                
                  constexpr bool
                  isunordered(double __x, double __y)
                  { return __builtin_isunordered(__x, __y); }
                
                  constexpr bool
                  isunordered(long double __x, long double __y)
                  { return __builtin_isunordered(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename
                    __gnu_cxx::__enable_if<(__is_arithmetic<_Tp>::__value
                			    && __is_arithmetic<_Up>::__value), bool>::__type
                    isunordered(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return __builtin_isunordered(__type(__x), __type(__y));
                    }
                
                #else
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    fpclassify(_Tp __f)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL,
                				  FP_SUBNORMAL, FP_ZERO, __type(__f));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isfinite(_Tp __f)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isfinite(__type(__f));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isinf(_Tp __f)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isinf(__type(__f));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isnan(_Tp __f)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isnan(__type(__f));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isnormal(_Tp __f)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isnormal(__type(__f));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    signbit(_Tp __f)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_signbit(__type(__f));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isgreater(_Tp __f1, _Tp __f2)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isgreater(__type(__f1), __type(__f2));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isgreaterequal(_Tp __f1, _Tp __f2)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isgreaterequal(__type(__f1), __type(__f2));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isless(_Tp __f1, _Tp __f2)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isless(__type(__f1), __type(__f2));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    islessequal(_Tp __f1, _Tp __f2)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_islessequal(__type(__f1), __type(__f2));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    islessgreater(_Tp __f1, _Tp __f2)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_islessgreater(__type(__f1), __type(__f2));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isunordered(_Tp __f1, _Tp __f2)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isunordered(__type(__f1), __type(__f2));
                    }
                
                #endif
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace
                
                #endif /* _GLIBCXX_USE_C99_FP_MACROS_DYNAMIC */
                #endif
                
                #if __cplusplus >= 201103L
                
                #ifdef _GLIBCXX_USE_C99_MATH_TR1
                
                #undef acosh
                #undef acoshf
                #undef acoshl
                #undef asinh
                #undef asinhf
                #undef asinhl
                #undef atanh
                #undef atanhf
                #undef atanhl
                #undef cbrt
                #undef cbrtf
                #undef cbrtl
                #undef copysign
                #undef copysignf
                #undef copysignl
                #undef erf
                #undef erff
                #undef erfl
                #undef erfc
                #undef erfcf
                #undef erfcl
                #undef exp2
                #undef exp2f
                #undef exp2l
                #undef expm1
                #undef expm1f
                #undef expm1l
                #undef fdim
                #undef fdimf
                #undef fdiml
                #undef fma
                #undef fmaf
                #undef fmal
                #undef fmax
                #undef fmaxf
                #undef fmaxl
                #undef fmin
                #undef fminf
                #undef fminl
                #undef hypot
                #undef hypotf
                #undef hypotl
                #undef ilogb
                #undef ilogbf
                #undef ilogbl
                #undef lgamma
                #undef lgammaf
                #undef lgammal
                #undef llrint
                #undef llrintf
                #undef llrintl
                #undef llround
                #undef llroundf
                #undef llroundl
                #undef log1p
                #undef log1pf
                #undef log1pl
                #undef log2
                #undef log2f
                #undef log2l
                #undef logb
                #undef logbf
                #undef logbl
                #undef lrint
                #undef lrintf
                #undef lrintl
                #undef lround
                #undef lroundf
                #undef lroundl
                #undef nan
                #undef nanf
                #undef nanl
                #undef nearbyint
                #undef nearbyintf
                #undef nearbyintl
                #undef nextafter
                #undef nextafterf
                #undef nextafterl
                #undef nexttoward
                #undef nexttowardf
                #undef nexttowardl
                #undef remainder
                #undef remainderf
                #undef remainderl
                #undef remquo
                #undef remquof
                #undef remquol
                #undef rint
                #undef rintf
                #undef rintl
                #undef round
                #undef roundf
                #undef roundl
                #undef scalbln
                #undef scalblnf
                #undef scalblnl
                #undef scalbn
                #undef scalbnf
                #undef scalbnl
                #undef tgamma
                #undef tgammaf
                #undef tgammal
                #undef trunc
                #undef truncf
                #undef truncl
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                  // types
                  using ::double_t;
                  using ::float_t;
                
                  // functions
                  using ::acosh;
                  using ::acoshf;
                  using ::acoshl;
                
                  using ::asinh;
                  using ::asinhf;
                  using ::asinhl;
                
                  using ::atanh;
                  using ::atanhf;
                  using ::atanhl;
                
                  using ::cbrt;
                  using ::cbrtf;
                  using ::cbrtl;
                
                  using ::copysign;
                  using ::copysignf;
                  using ::copysignl;
                
                  using ::erf;
                  using ::erff;
                  using ::erfl;
                
                  using ::erfc;
                  using ::erfcf;
                  using ::erfcl;
                
                  using ::exp2;
                  using ::exp2f;
                  using ::exp2l;
                
                  using ::expm1;
                  using ::expm1f;
                  using ::expm1l;
                
                  using ::fdim;
                  using ::fdimf;
                  using ::fdiml;
                
                  using ::fma;
                  using ::fmaf;
                  using ::fmal;
                
                  using ::fmax;
                  using ::fmaxf;
                  using ::fmaxl;
                
                  using ::fmin;
                  using ::fminf;
                  using ::fminl;
                
                  using ::hypot;
                  using ::hypotf;
                  using ::hypotl;
                
                  using ::ilogb;
                  using ::ilogbf;
                  using ::ilogbl;
                
                  using ::lgamma;
                  using ::lgammaf;
                  using ::lgammal;
                
                  using ::llrint;
                  using ::llrintf;
                  using ::llrintl;
                
                  using ::llround;
                  using ::llroundf;
                  using ::llroundl;
                
                  using ::log1p;
                  using ::log1pf;
                  using ::log1pl;
                
                  using ::log2;
                  using ::log2f;
                  using ::log2l;
                
                  using ::logb;
                  using ::logbf;
                  using ::logbl;
                
                  using ::lrint;
                  using ::lrintf;
                  using ::lrintl;
                
                  using ::lround;
                  using ::lroundf;
                  using ::lroundl;
                
                  using ::nan;
                  using ::nanf;
                  using ::nanl;
                
                  using ::nearbyint;
                  using ::nearbyintf;
                  using ::nearbyintl;
                
                  using ::nextafter;
                  using ::nextafterf;
                  using ::nextafterl;
                
                  using ::nexttoward;
                  using ::nexttowardf;
                  using ::nexttowardl;
                
                  using ::remainder;
                  using ::remainderf;
                  using ::remainderl;
                
                  using ::remquo;
                  using ::remquof;
                  using ::remquol;
                
                  using ::rint;
                  using ::rintf;
                  using ::rintl;
                
                  using ::round;
                  using ::roundf;
                  using ::roundl;
                
                  using ::scalbln;
                  using ::scalblnf;
                  using ::scalblnl;
                
                  using ::scalbn;
                  using ::scalbnf;
                  using ::scalbnl;
                
                  using ::tgamma;
                  using ::tgammaf;
                  using ::tgammal;
                
                  using ::trunc;
                  using ::truncf;
                  using ::truncl;
                
                  /// Additional overloads.
                  constexpr float
                  acosh(float __x)
                  { return __builtin_acoshf(__x); }
                
                  constexpr long double
                  acosh(long double __x)
                  { return __builtin_acoshl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    acosh(_Tp __x)
                    { return __builtin_acosh(__x); }
                
                  constexpr float
                  asinh(float __x)
                  { return __builtin_asinhf(__x); }
                
                  constexpr long double
                  asinh(long double __x)
                  { return __builtin_asinhl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    asinh(_Tp __x)
                    { return __builtin_asinh(__x); }
                
                  constexpr float
                  atanh(float __x)
                  { return __builtin_atanhf(__x); }
                
                  constexpr long double
                  atanh(long double __x)
                  { return __builtin_atanhl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    atanh(_Tp __x)
                    { return __builtin_atanh(__x); }
                
                  constexpr float
                  cbrt(float __x)
                  { return __builtin_cbrtf(__x); }
                
                  constexpr long double
                  cbrt(long double __x)
                  { return __builtin_cbrtl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    cbrt(_Tp __x)
                    { return __builtin_cbrt(__x); }
                
                  constexpr float
                  copysign(float __x, float __y)
                  { return __builtin_copysignf(__x, __y); }
                
                  constexpr long double
                  copysign(long double __x, long double __y)
                  { return __builtin_copysignl(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    copysign(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return copysign(__type(__x), __type(__y));
                    }
                
                  constexpr float
                  erf(float __x)
                  { return __builtin_erff(__x); }
                
                  constexpr long double
                  erf(long double __x)
                  { return __builtin_erfl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    erf(_Tp __x)
                    { return __builtin_erf(__x); }
                
                  constexpr float
                  erfc(float __x)
                  { return __builtin_erfcf(__x); }
                
                  constexpr long double
                  erfc(long double __x)
                  { return __builtin_erfcl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    erfc(_Tp __x)
                    { return __builtin_erfc(__x); }
                
                  constexpr float
                  exp2(float __x)
                  { return __builtin_exp2f(__x); }
                
                  constexpr long double
                  exp2(long double __x)
                  { return __builtin_exp2l(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    exp2(_Tp __x)
                    { return __builtin_exp2(__x); }
                
                  constexpr float
                  expm1(float __x)
                  { return __builtin_expm1f(__x); }
                
                  constexpr long double
                  expm1(long double __x)
                  { return __builtin_expm1l(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    expm1(_Tp __x)
                    { return __builtin_expm1(__x); }
                
                  constexpr float
                  fdim(float __x, float __y)
                  { return __builtin_fdimf(__x, __y); }
                
                  constexpr long double
                  fdim(long double __x, long double __y)
                  { return __builtin_fdiml(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    fdim(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return fdim(__type(__x), __type(__y));
                    }
                
                  constexpr float
                  fma(float __x, float __y, float __z)
                  { return __builtin_fmaf(__x, __y, __z); }
                
                  constexpr long double
                  fma(long double __x, long double __y, long double __z)
                  { return __builtin_fmal(__x, __y, __z); }
                
                  template<typename _Tp, typename _Up, typename _Vp>
                    constexpr typename __gnu_cxx::__promote_3<_Tp, _Up, _Vp>::__type
                    fma(_Tp __x, _Up __y, _Vp __z)
                    {
                      typedef typename __gnu_cxx::__promote_3<_Tp, _Up, _Vp>::__type __type;
                      return fma(__type(__x), __type(__y), __type(__z));
                    }
                
                  constexpr float
                  fmax(float __x, float __y)
                  { return __builtin_fmaxf(__x, __y); }
                
                  constexpr long double
                  fmax(long double __x, long double __y)
                  { return __builtin_fmaxl(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    fmax(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return fmax(__type(__x), __type(__y));
                    }
                
                  constexpr float
                  fmin(float __x, float __y)
                  { return __builtin_fminf(__x, __y); }
                
                  constexpr long double
                  fmin(long double __x, long double __y)
                  { return __builtin_fminl(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    fmin(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return fmin(__type(__x), __type(__y));
                    }
                
                  constexpr float
                  hypot(float __x, float __y)
                  { return __builtin_hypotf(__x, __y); }
                
                  constexpr long double
                  hypot(long double __x, long double __y)
                  { return __builtin_hypotl(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    hypot(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return hypot(__type(__x), __type(__y));
                    }
                
                  constexpr int
                  ilogb(float __x)
                  { return __builtin_ilogbf(__x); }
                
                  constexpr int
                  ilogb(long double __x)
                  { return __builtin_ilogbl(__x); }
                
                  template<typename _Tp>
                    constexpr
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    int>::__type
                    ilogb(_Tp __x)
                    { return __builtin_ilogb(__x); }
                
                  constexpr float
                  lgamma(float __x)
                  { return __builtin_lgammaf(__x); }
                
                  constexpr long double
                  lgamma(long double __x)
                  { return __builtin_lgammal(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    lgamma(_Tp __x)
                    { return __builtin_lgamma(__x); }
                
                  constexpr long long
                  llrint(float __x)
                  { return __builtin_llrintf(__x); }
                
                  constexpr long long
                  llrint(long double __x)
                  { return __builtin_llrintl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              long long>::__type
                    llrint(_Tp __x)
                    { return __builtin_llrint(__x); }
                
                  constexpr long long
                  llround(float __x)
                  { return __builtin_llroundf(__x); }
                
                  constexpr long long
                  llround(long double __x)
                  { return __builtin_llroundl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              long long>::__type
                    llround(_Tp __x)
                    { return __builtin_llround(__x); }
                
                  constexpr float
                  log1p(float __x)
                  { return __builtin_log1pf(__x); }
                
                  constexpr long double
                  log1p(long double __x)
                  { return __builtin_log1pl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    log1p(_Tp __x)
                    { return __builtin_log1p(__x); }
                
                  // DR 568.
                  constexpr float
                  log2(float __x)
                  { return __builtin_log2f(__x); }
                
                  constexpr long double
                  log2(long double __x)
                  { return __builtin_log2l(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    log2(_Tp __x)
                    { return __builtin_log2(__x); }
                
                  constexpr float
                  logb(float __x)
                  { return __builtin_logbf(__x); }
                
                  constexpr long double
                  logb(long double __x)
                  { return __builtin_logbl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    logb(_Tp __x)
                    { return __builtin_logb(__x); }
                
                  constexpr long
                  lrint(float __x)
                  { return __builtin_lrintf(__x); }
                
                  constexpr long
                  lrint(long double __x)
                  { return __builtin_lrintl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              long>::__type
                    lrint(_Tp __x)
                    { return __builtin_lrint(__x); }
                
                  constexpr long
                  lround(float __x)
                  { return __builtin_lroundf(__x); }
                
                  constexpr long
                  lround(long double __x)
                  { return __builtin_lroundl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              long>::__type
                    lround(_Tp __x)
                    { return __builtin_lround(__x); }
                
                  constexpr float
                  nearbyint(float __x)
                  { return __builtin_nearbyintf(__x); }
                
                  constexpr long double
                  nearbyint(long double __x)
                  { return __builtin_nearbyintl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    nearbyint(_Tp __x)
                    { return __builtin_nearbyint(__x); }
                
                  constexpr float
                  nextafter(float __x, float __y)
                  { return __builtin_nextafterf(__x, __y); }
                
                  constexpr long double
                  nextafter(long double __x, long double __y)
                  { return __builtin_nextafterl(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    nextafter(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return nextafter(__type(__x), __type(__y));
                    }
                
                  constexpr float
                  nexttoward(float __x, long double __y)
                  { return __builtin_nexttowardf(__x, __y); }
                
                  constexpr long double
                  nexttoward(long double __x, long double __y)
                  { return __builtin_nexttowardl(__x, __y); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    nexttoward(_Tp __x, long double __y)
                    { return __builtin_nexttoward(__x, __y); }
                
                  constexpr float
                  remainder(float __x, float __y)
                  { return __builtin_remainderf(__x, __y); }
                
                  constexpr long double
                  remainder(long double __x, long double __y)
                  { return __builtin_remainderl(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    remainder(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return remainder(__type(__x), __type(__y));
                    }
                
                  inline float
                  remquo(float __x, float __y, int* __pquo)
                  { return __builtin_remquof(__x, __y, __pquo); }
                
                  inline long double
                  remquo(long double __x, long double __y, int* __pquo)
                  { return __builtin_remquol(__x, __y, __pquo); }
                
                  template<typename _Tp, typename _Up>
                    inline typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    remquo(_Tp __x, _Up __y, int* __pquo)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return remquo(__type(__x), __type(__y), __pquo);
                    }
                
                  constexpr float
                  rint(float __x)
                  { return __builtin_rintf(__x); }
                
                  constexpr long double
                  rint(long double __x)
                  { return __builtin_rintl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    rint(_Tp __x)
                    { return __builtin_rint(__x); }
                
                  constexpr float
                  round(float __x)
                  { return __builtin_roundf(__x); }
                
                  constexpr long double
                  round(long double __x)
                  { return __builtin_roundl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    round(_Tp __x)
                    { return __builtin_round(__x); }
                
                  constexpr float
                  scalbln(float __x, long __ex)
                  { return __builtin_scalblnf(__x, __ex); }
                
                  constexpr long double
                  scalbln(long double __x, long __ex)
                  { return __builtin_scalblnl(__x, __ex); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    scalbln(_Tp __x, long __ex)
                    { return __builtin_scalbln(__x, __ex); }
                 
                  constexpr float
                  scalbn(float __x, int __ex)
                  { return __builtin_scalbnf(__x, __ex); }
                
                  constexpr long double
                  scalbn(long double __x, int __ex)
                  { return __builtin_scalbnl(__x, __ex); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    scalbn(_Tp __x, int __ex)
                    { return __builtin_scalbn(__x, __ex); }
                
                  constexpr float
                  tgamma(float __x)
                  { return __builtin_tgammaf(__x); }
                
                  constexpr long double
                  tgamma(long double __x)
                  { return __builtin_tgammal(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    tgamma(_Tp __x)
                    { return __builtin_tgamma(__x); }
                 
                  constexpr float
                  trunc(float __x)
                  { return __builtin_truncf(__x); }
                
                  constexpr long double
                  trunc(long double __x)
                  { return __builtin_truncl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    trunc(_Tp __x)
                    { return __builtin_trunc(__x); }
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace
                
                #endif // _GLIBCXX_USE_C99_MATH_TR1
                
                #endif // C++11
                
                #endif


Top 10 Lines:

     Line      Count

      483 1576443686
      434  654530572
      242  305412876
      204  147934924
      445  147933113
      377        815

Execution Summary:

       12   Executable lines in this file
       12   Lines executed
   100.00   Percent of the file executed

2832255986   Total number of line executions
236021332.17   Average executions per line


*** File /root/newtroll/main_v2.3.2.cpp:
                /*####################################################################
                 ###  TROLL
                 ###  Individual-based forest dynamics simulator
                 ###    Version 1: Jerome Chave
                 ###    Version 2.1 & 2.2: Isabelle Marechaux & Jerome Chave
                 ###    Version 2.3 onwards: Isabelle Marechaux, Fabian Fischer, Jerome Chave
                 ###
                 ###  History:
                 ###    version 0.1 --- JC - 22 Sep 97
                 ###    version 0.2 --- JC - 06 Oct 97
                 ###    version 0.3 --- JC - 11-14 Nov 97
                 ###    version 1.0 --- JC - stable version Chave, Ecological Modelling (1999)
                 ###    version 1.1 --- JC - 02-30 Sep 98
                 ###    version 1.2 --- JC - 22 Jan 00
                 ###    version 1.3 --- JC - 28 Sep 01 stable version Chave, American Naturalist (2001)
                 ###
                 ###    version 2.0 --- JC - 23 Mar 11 (physiology-based version, translation of comments into English)
                 ###    version 2.01 --- IM - oct-nov 13
                 ###    version 2.02 --- IM - apr-may 2015
                 ###    version 2.03 --- IM - jul 2015
                 ###    version 2.04 --- IM - jul 2015 (monthly timestep)
                 ###    version 2.1  --- IM - dec 2015 (undef/defined alternative versions)
                 ###    version 2.11 --- IM - jan 2016 timestep better used
                 ###    version 2.12 --- JC - jan 2016 porting to GitHub for social coding, check of the MPI routines and update, new header for code, trivia: reindentation (orphan lines removed)
                 ###    version 2.2  --- IM - may 2016 core changes in: daily coupling with environment; respiration; treefall module; leaf pool dynamics
                 ###    version 2.3  --- FF - oct-nov 2016: bug fixing (including UpdateSeed() bug), general reworking of code, changes in CalcLAI(), initialisation from data, toolbox with alternative fine flux calculation (cf. end of script)
                 ###    version 2.3.0 --- IM & JC - janv-feb 2017: new tree size threshold to maturity (dbhmature), changes in input file structure, corrections of temperature dependencies in GPPleaf. Code acceleration (use of lookup tables instead of functions in the calculations of the Fluxh() and GPPleaf() routines; faster whole-tree GPP calculation. This results in an increase in speed of a factor 4.
                 ###    version 2.3.1 --- IM & JC - feb-mar 2017: introduces the dispersal cell, or dcell concept (square subplot of linear size length_dcell)
                 ###    code acceleration FASTGPP concept improved.
                 ###    DCELL: GNU scientific library is needed -- on osx, type "brew install gsl"
                 ###    DCELL: Compile command (osx/linux):
                 ###                    g++ -O3 -Wall -o troll main_xx.cpp -lgsl -lgslcblas -lm
                 ###    DCELL: Code profiling (unix): g++ -O3 -Wall -o troll main_xx.cpp -lgsl -lgslcblas -lm -g -pg
                 ###
                 ####################################################################*/
                
                
                /*
                 Glossary: MPI = Message Passing Interface. Software for sharing information
                 across processors in parallel computers. If global variable MPI is not defined,
                 TROLL functions on one processor only.
                 */
                
                #undef MPI              /* If flag MPI defined, parallel routines (MPI software) are switched on */
                #undef easyMPI          /* If flag easyMPI defined, parallel routine for fast search of parameter space are switched on */
                #undef toolbox          /* never to be defined! Toolbox is an assortment of alternative formulations of TROLL procedures, attached to the code */
                
                #undef DCELL // this explores the need for an intermediate grid cell size
                
                /* Libraries */
                # include <cstdio>
                # include <iostream>
                # include <fstream>
                # include <cstdlib>
                # include <string>
                # include <limits>
                # include <ctime>
                # include <cmath>
                # include <cstring>
                # ifdef MPI
                # include "mpi.h"
                # endif
                # ifdef easyMPI
                # include "mpi.h"
                # endif
                
                using namespace std;
                
                /* Global constants (e.g. PI and various derivatives...) */
                # define PI 3.141592654
                # define twoPi 6.2831853071
                # define Pis2 1.570796327
                # define iPi 0.3183099
                char buffer[256], inputfile[256], outputinfo[256], inputfile_data[256], *bufi(0), *buf(0), *bufi_data(0);
                
                
                /* random number generators */
                double genrand2(void);
                void sgenrand2(unsigned long);
                unsigned long genrand2i(void);
                void sgenrand2i(unsigned long);
                
                /* file output streams */
                
       ##### -> fstream out,out2;
                
       ##### -> fstream output[38];
                
                /****************/
                /* User control */
                /****************/
                
                /* options can be turned on (1) or off (0). This comes, however, at computational costs. Where routines have to be called frequently, if-conditioning should be done as far outside the loop as possible (e.g. for DAILYLIGHT outside voxel loops) */
                /* currenly, options are set below, but inclusion in parameter sheet needed (for control from R) */
                
                bool
                _FASTGPP=0,             /* This defines an option to compute only GPP from the topmost value of PPFD and GPP, instead of looping within the crown. Much faster and more accurate */
                _BASICTREEFALL=1,       /* if defined: treefall is a source of tree death (and if TREEFALL not defined, this is modeled through simple comparison between tree height and a threshold t_Ct, if not defined, treefall is not represented as a separated and independent source of death, but instead, all tree death are due to the deathrate value) */
                _TREEFALL=0,            /* computation of the force field if TREEFALL is defined, neighboring trees contribute to fell each tree */
                _DAILYLIGHT=1,          /* if defined: the rate of carbon assimilation integrates an average daily fluctuation of light (thanks to GPPDaily). Should be defined to ensure an appropriate use of Farquhar model */
                _SEEDTRADEOFF=0,        /* if defined: the number of seeds produced by each tree is determined by the tree NPP allocated to reproduction and the species seed mass, otherwise the number of seeds is fixed; besides, seedling recruitment in one site is not made by randomly and 'equiprobably' picking one species among the seeds present at that site but the probability of recruitment among the present seeds is proportional to the number of seeds (in s_Seed[site]) time the seed mass of each species */
                _NDD=0,                 /* if defined, negative density dependant processes affect both the probability of seedling recruitment and the local tree death rate. The term of density-dependance is computed as the sum of conspecific tree basal area divided by their distance to the focal tree within a neighbourhood (circle of radius 15m) */
                _OUTPUT_reduced=1,      /* reduced set of ouput files */
                _OUTPUT_last100=0,      /* output that tracks the last 100 years of the simulation for the whole grid (2D) */
                _OUTPUT_fullLAI=0,       /* output of full final voxel field */
                _FromData=0;            /* if defined, an additional input file can be provided to start simulations from an existing data set or a simulated data set (5 parameters are needed: x and y coordinates, dbh, species_label, species */
                
                
                /********************************/
                /* Parameters of the simulation */
                /********************************/
                
                int sites,          /* number of sites */
                cols,               /* nb of columns */
                rows,               /* nb of lines */
                numesp,             /* nb of species */
                iterperyear,        /* nb of iter in a year (=12 if monthly timestep, =365 if daily timestep) */
                nbiter,             /* total nb of timesteps */
                iter,               /* current timestep */
                nbout,              /* nb of outputs */
                freqout;            /* frequency HDF outputs */
                
                #ifdef DCELL
                gsl_rng *gslrand;
                int length_dcell,   /* v2.3.1 linear size of a dcell */
                linear_nb_dcells,    /* linear number of dcells note that nbdcells = linear_nb_dcells^2 */
                sites_per_dcell,    /* number of sites per dcell */
                nbdcells;           /* total number of dcells */
                int **MAP_DCELL(0);   /* list of sites per dcell (for fast fillin) */
                double *prior_DCELL(0); /* prior for picking the dispersal sites within the dcell -- vector of size sites_per_dcell and with all entries equal to 1/sites_per_dcell (because the dispersal is equiprobable) */
                unsigned int *post_DCELL(0); /* number of seeds per site within the dcell */
                double *prior_GERM(0); /* prior for picking the germination event within a site -- vector of size numesp and with entries equal to the number of seeds multiplied by seedsize */
                unsigned int *post_GERM(0); /* vector with only one non-null entry (the successful germination event) */
                #endif
                
                int HEIGHT,         /* max height (in m) */
                dbhmaxincm,         /* max DBH times 100 (ie dbh in cm *100 = in meters) */
                RMAX,               /* max crown radius */
                SBORD;              /* RMAX*cols */
                
                float NV,           /* nb cells per m (vertical) */
                NH,                 /* nb cells per m (horizontal) */
                LV,                 /* LV = 1.0/NV */
                LH,                 /* LH = 1.0/NH */
                timestep;           /* duration of one timestep (in years)=1/iterperyear */
                
                float p_nonvert,    /* ratio of non-vertical incident light */
                Cseedrain,          /* constant used to scale total seed rain per hectare across species */
                nbs0,               /* nb of seeds produced and dispersed by each mature tree when SEEDTRADEOFF is not defined */
                Cair,               /* atmosphericCO2 concentration, if we aim at making CO2 vary (scenarios), CO2 will have to have the same status as other climatic variables  */
                iCair;              /* inverse of Cair */
                
                /* new version 2.2 */
                float daily_light[24];    /* normalized (ie between 0 and 1) daily light variation (used if DAILYLIGHT defined) */
                float daily_vpd[24];      /* normalized (ie between 0 and 1) daily vpd variation (used if DAILYLIGHT defined) */
                float daily_T[24];        /* normalized (ie between 0 and 1) daily T variation (used if DAILYLIGHTdefined) */
                
                /*parameter for NDD*/
                float R,                    /* distance beyond which NDD effect is not accounted anymore*/
                deltaR,                     /* NDD strength parameter in recruitment */
                deltaD,                     /* NDD strength parameter in deathrate */
                BAtot;
                
                
                /*********************************************/
                /* Environmental variables of the simulation */
                /*********************************************/
                
                /* Climate input data  */
                /* these climate input data are given in the input file, its structure depends on the timestep and scenario used for the simulation */
                /* new version 2.2 */
                float *Temperature(0);                      /* in degree Celsius */
                float *DailyMaxTemperature(0);              /* in degree Celsius */
                float *NightTemperature(0);                 /* in degree Celsius */
                float *Rainfall(0);                         /* in mm */
                float *WindSpeed(0);                        /* in m/s */
                float *MaxIrradiance(0);                    /* in W/m2 */
                float *MeanIrradiance(0);                   /* in W/m2 */
                float *SaturatedVapourPressure(0);          /* in kPa */
                float *VapourPressure(0);                   /* in kPa */
                float *VapourPressureDeficit(0);            /* in kPa */
                float *DailyVapourPressureDeficit(0);       /* in kPa */
                float *DailyMaxVapourPressureDeficit(0);    /* in kPa */
                
                /* New in v.2.3.0 */
                int nbTbins;                    /*nb of bins for the temperature lookup tables */
                float iTaccuracy;                /* inverse of accuracy of a temperature bin (e.g. Taccuracy us 0.1 or 0.5 °C, so iTaccuracy is 10.0 or 2.0, resp) */
                float *LookUp_KmT(0);                   /* lookup table for fast comput of Farquhar as a function of T */
                /* !! leaf temperature must be comprised between 0°C and 60°C
                 (T_leaf is stored every 0.5°C, so 120 values in total */
                float *LookUp_GammaT(0);                   /* lookup table for fast comput of Farquhar */
                float *LookUp_tempRday(0);                 /* lookup table for fast comput of Farquhar */
                float *LookUp_VcmaxT(0);                   /* lookup table for fast comput of Farquhar */
                float *LookUp_JmaxT(0);                   /* lookup table for fast comput of Farquhar */
                
                float *LookUp_flux(0);                 /* lookup table for faster computation of PPFD*/
                float *LookUp_VPD(0);                  /* lookup table for faster computation of VPD */
                float *LookUp_T(0);                    /* lookup table for faster computation of T */
                float *LookUp_Rstem(0);                /* lookup table for faster computation of Rstem */
                float *LookUp_Rnight(0);                /* lookup table for faster computation of Rstem */
                
                /***** Environmental variables, changed at each timestep *****/
                float temp,         /* Temperature */
                tmax,               /* Daily max temperature */
                tnight,             /* Night mean temperature */
                precip,             /* Rainfall  */
                WS,                 /* WindSpeed */
                Wmax,               /* Daily max irradiance (average for timestep) (in micromol PAR photon/m^2/s)*/
                /* used in the photosynthesis part. see if it would not be better to have value in the right unit in the input file, however W/m2 is the common unit of meteo station */
                /* below: new version 2.2 */
                Wmean,              /* mean irradiance (in W/m2)*/
                e_s,                /* SaturatedVapourPressure */
                e_a,                /* VapourPressure*/
                VPDbasic,           /* VapourPressureDeficit */
                VPDday,             /* DailyVapourPressureDeficit */
                VPDmax;             /* DailyMaxVapourPressureDeficit */
                
                
                /****************************************/
                /*  Common variables for the species    */
                /* (simplifies initial version 170199)  */
                /****************************************/
                
                //int Cm;           /* Treefall threshold */
                float klight,       /* light absorption rate or extinction cefficient used in Beer-Lambert law to compute light within the canopy */
                phi,                /* apparent quantum yield (in micromol C/micromol photon). phi is the quantum yield multiplied by leaf absorbance (in the literature, the quantum yield is often given per absorbed light flux, so one should multiply incident PPFD by leaf absorbance, see Poorter et al American Journal of Botany (assumed to be 0.91 for tropical tree species). Even though holding phi constant across species is widely assumed, in reality, phi varies across species and environmental conditions (see eg Domingues et al 2014 Plant Ecology & Diversity) */
                theta,              /* parameter of the Farquhar model set to 0.7 in this version. For some authors, it should be species-dependent or temperature dependent, but these options are not implemented here */
                g1,                 /* g1 parameter of Medlyn et al's model of stomatal conductance. v230: defined as a global parameter shared by species, instead of a Species class's variable */
                alpha,              /* apparent quantum yield to electron transport in mol e-/mol photons, equal to the true quantum yield multiplied by the leaf absorbance -- v.2.2 */
                vC,                 /* variance of treefall threshold */
                H0,                 /* initial height (in m) */
                DBH0,               /* initial DBH (in m) */
                de0,                /* initial crown Crown_Depth (in m) */
                de1,                /* Crown_Depth/height slope */
                /* fallocwood and falloccanopy new -- v.2.2 */
                fallocwood,         /* fraction of biomass allocated to above ground wood (branches+stem) */
                falloccanopy,       /* fraction of biomass allocated to canopy (leaves + reproductive organs + twigs) */
                dens,               /* initial leaf density (in m^2/m^3) */
                ra1,                /* crown radius - dbh slope */
                ra0,                /* initial crown radius (in m) */
                m,                  /* basal death rate */
                m1;                 /* deathrate-wsg slope -- new v.2.2 */
                
                
                float **LAI3D(0);   /* leaf density (per volume unit) */
                unsigned short *Thurt[3];            /* Treefall field */
                
                int    *SPECIES_GERM (0);
                float  *PROB_S (0); /* _SEEDTRADEOFF */
                float tempRday;     /* temporary variable used for the computation of leaf day respiration -- new v.2.2 */
                
                
                /***************/
                /* Diagnostics */
                /***************/
                
                int nbdead_n1,             /* nb deaths other than treefall dbh > 1 cm, computed at each timestep */
                nbdead_n10,                /* nb deaths other than treefall dbh > 10 cm, computed at each timestep */
                nblivetrees,            /* nb live trees for each timestep  */
                nbdead_c1,                 /* nb deaths caused by a treefall dbh > 1 cm, computed at each timestep, _BASICTREEFALL */
                nbdead_c10,                /* nb deaths caused by a treefall dbh > 10 cm, computed at each timestep, _BASICTREEFALL */
                nbTreefall1,            /* nb treefalls for each timestep (dbh > 1cm), _BASICTREEFALL */
                nbTreefall10;           /* nb treefalls for each timestep (dbh > 10 cm), _BASICTREEFALL */
                
                //long int *persist;	/* persistence histogram */
                int *nbdbh(0);          /* dbh size distribution */
                float *layer(0);        /* vertical LAI histogram */
                
                /**************/
                /* Processors */
                /**************/
                
                int mpi_rank,mpi_size;
                int easympi_rank,easympi_size;
                
                
                /******************/
                /* MPI procedures */
                /******************/
                
                #ifdef MPI
                unsigned short **LAIc[2];
                void
                MPI_ShareSeed(unsigned char **,int),
                MPI_ShareField(unsigned short **,unsigned short ***,int),
                MPI_ShareTreefall(unsigned short **,int);
                #endif
                
                
                /**********************/
                /* Simulator routines */
                /**********************/
                
                void
                Initialise(void),
                InitialiseFromData(void),
                AllocMem(void),
                BirthInit(void),
                Evolution(void),
                UpdateField(void),
                UpdateTreefall(void),               // _BASICTREEFALL
                UpdateTree(void),
                Average(void),
                OutputField(void),
                FreeMem(void);
                
                /**********************/
                /** Output routines ***/
                /**********************/
                
                void
                OutputSnapshot(fstream& output),
                OutputSnapshotDetail(fstream& output),
                OutputSpeciesParameters(fstream& output),
                OutputFullLAI(fstream& output_CHM, fstream& output_LAD);
                
                /****************************/
                /* Various inline functions */
                /****************************/
                
                
   871335198 -> inline float flor(float f) {
   871335198 ->     if(f>0.) return f;
   871335198 ->     else return 0.;
   871335198 -> }
                inline float florif(int i) {
                    if(i>0) return float(i);
                    else return 0.;
                }
         726 -> inline float maxf(float f1, float f2) {
         726 ->     if(f1>f2) return f1;
         726 ->     else return f2;
         726 -> }
  5907644284 -> inline float minf(float f1, float f2) {
  5907644284 ->     if(f1<f2) return f1;
  5907644284 ->     else return f2;
  5907644284 -> }
 11775954108 -> inline int min(int i1, int i2) {
 11775954108 ->     if(i1<i2) return i1;
 11775954108 ->     else return i2;
 11775954108 -> }
  4724642744 -> inline int max(int i1, int i2) {
  4724642744 ->     if(i1>i2) return i1;
  4724642744 ->     else return i2;
  4724642744 -> }
       ##### -> inline int sgn(float f) {
       ##### ->     if(f>0.0) return 1;
       ##### ->     else return -1;
       ##### -> }
                
                
                /*############################################
                 ############################################
                 ###########     Species  class   ###########
                 ############################################
                 ############################################*/
                
                class Species {
                    
                public:
                    int    s_nbind,			/* nb of individuals per species */
                    s_dormDuration,         /* seed dormancy duration -- not used in v.2.2 */
                    s_nbext;                /* total number of incoming seeds in the simulated plot at each timestep (seed rain) -- v.2.2 */
                    char	s_name[256];	/* species name */
                    float  s_LCP,			/* light compensation point  (in micromol photon/m^2/s) */
                    s_Rdark,                /* dark respiration rate (at PPFD = 0) in micromol C/m^2/s) */
                    s_ds,                   /* average dispersal distance */
                    //  de1,                /* (crown depth) - height slope deprecated v.2.1 */
                    s_dmax,                 /* maximal dbh (given in m) */
                    s_hmax,                 /* maximal height (given in m) */
                    s_dbh0,                 /* Initial dbh at recruitement, computed for each species with the species-specific allometric relationship at h=H0=1m -- in v230 */
                    s_Vcmax,                /* maximal rate of carboxylation, on an area basis (in micromolC/m^2/s) */
                    s_Vcmaxm,               /* maximal rate of carboxylation, on a mass basis (in micromolC/g-1/s) */
                    s_Jmax,                 /* maximal rate of electron transport, on an area basis (in micromol/m^2/s) */
                    s_Jmaxm,                /* maximal rate of electron transport, on a mass basis (in micromol/g-1/s) */
                    s_fci,                  /* fraction of CO2 partial pressure in intercellular spaces divided by ambiant CO2 partial pressure (both in microbar, or ppm = micromol/mol) */
                    s_Gamma,                /* compensation point for the carboxylation rate, here NORMALIZED by atm CO2 concentration (Cair) */
                    s_Km,                   /* apparent kinetic constant for the rubiscco = Kc*(1+[O]/Ko), here normalized by atm CO2 concentration (Cair) */
                    //s_d13C,                 /* isotopic carbon discrimination NOW normalized at zero height -- deprecated v.2.2 */
                    s_LMA,                  /* leaf mass per area (in g/m^2) */
                    s_Nmass,                /* leaf nitrogen concentration (in g/g) v.2.01 */
                    s_Pmass,                /* leaf phosphorous concentration (in g/g) v.2.01 */
                    s_wsg,                  /* wood specific gravity (in g/cm^3) */
                    s_ah,                   /* parameter for allometric height-dbh equation */
                    s_seedmass,             /* seed mass, in g (from Baraloto & Forget 2007 dataset, in classes) v.2.3: seeminlgy deprecated in v.2.2, but still necessary for SEEDTRADEOFF */
                    s_iseedmass,            /* inverse of seed mass, v.2.3: seeminlgy deprecated in v.2.2, but still necessary for SEEDTRADEOFF */
                    //s_factord13Ca,        /* deprecated v.2.2 -- factor used for a previous version of ci/ca ratio computation, from d13C value */
                    //s_factord13Cb,        /* deprecated v.2.2 -- factor used for a previous version of ci/ca ratio computation, from d13C value */
                    /* Below: new in v.2.2 */
                    s_leaflifespan,         /* average leaf lifespan, in month */
                    s_time_young,           /* leaf resident time in the young leaf class */
                    s_time_mature,          /* leaf resident time in the mature leaf class */
                    s_time_old,             /* leaf resident time in the old leaf class */
                    s_output_field[24];         /* scalar output fields per species (<24) */
                    
                #ifdef DCELL
                    int *s_DCELL;	/* number of seeds from the species in each dcell */
                    int *s_Seed;	/* presence/absence of seeds at each site; if def SEEDTRADEOFF, the number of seeds */
                #else
                    int *s_Seed;	/* presence/absence of seeds; if def SEEDTRADEOFF, the number of seeds */
                #endif
                    
                #ifdef MPI
                    unsigned char *s_Gc[4]; /* MPI: seeds on neighboring procs */
                #endif
                    
                    
         164 ->     Species() {
         164 ->         s_nbind=0;
         164 ->         s_Seed=0;
                #ifdef DCELL
                        s_DCELL=0;
                #endif
         164 ->     };                              /* constructor */
                    
         164 ->     virtual ~Species() {
         164 ->         delete [] s_Seed;
                #ifdef DCELL
                        delete [] s_DCELL;
                #endif
         164 ->     };                              /* destructor */
                    
                    void Init(int,fstream&);        /* init Species class */
                #ifdef DCELL
                    void FillSeed(int,int,int);         /* assigns the produced seeds to s_DCELL */
                #else
                    void FillSeed(int,int);         /* fills s_Seed field (and s_Gc (MPI)) */
                #endif
                    void UpdateSeed(void);       /* Updates s_Seed field */
                #ifdef MPI
                    void AddSeed(void);             /* MPI: adds fields s_Gc  to field s_Seed */
                #endif
                    inline float DeathRateNDD(float, float,int, float); /* _NDD, overloading with function in following line */
                    inline float DeathRate(float, float, int);  /* actual death rate -- new argument int v.2.2 */
                    inline float GPPleaf(float, float, float);    /* Computation of the light-limited leaf-level NPP per m^2 (in micromol/m^2/s) -- two new arguments float v.2.2 */
                    /* Farquhar von Caemmerer Berry model */
                    inline float dailyGPPleaf(float, float, float, float, float);    /* computation of the daily average assimilation rate, taking into account the daily variation in light, VPD and temperature two new arguments float v.2.2, _DAILYLIGHT */
                };
                
                
                /*############################
                 ###  Initialize Species  ###
                 ###    Species::Init     ###
                 ############################*/
                
         163 -> void Species::Init(int nesp,fstream& is) {
                    
                    int site;
                    float regionalfreq;     // "regional" relative abundance of the species -- new name v.2.2
                    float SLA;              // specific leaf area = 1/LMA
                    
                    /*** Read parameters ***/
                    
                    //new input file -- in v230
         163 ->     is  >> s_name >> s_LMA >> s_Nmass >>  s_Pmass  >> s_wsg >> s_dmax >> s_hmax  >> s_ah >> s_seedmass >> regionalfreq;
                    
                    // instead of seedmass we are given seedvolume
                    // from this we assume a conversion factor of 1 to wet mass (~density of water, makes seeds float)
                    // to convert to drymass we use a conversion factor of 0.4 (~40% of the seed are water)
                    
         163 ->     s_seedmass *= 0.4;
         163 ->     s_iseedmass=1.0/s_seedmass;
         163 ->     s_ds=40.0;
                    
         163 ->     s_dbh0=s_ah*H0/(s_hmax-H0);
                    
                #ifdef DCELL
                    /* NEW in 2.3.1: input of seeds per timestep and per dcell is assumed proportional to seed size (large seeds are less numerous) this is compensated for by a lower recruitment probability for small seeds compared to large ones. Thus, in essence, we still have the seed number regeneration tradeoff but we allow more stochasticity in this process. Also, at least one seed arrives in the dcell from each species at each timestep (this is the +1 term) */
                #endif
                    
                    // uniform composition of the seed rain -- in v230
         163 ->     regionalfreq=1.0/float(numesp);
                    
         163 ->     if(_SEEDTRADEOFF){
         163 ->         s_nbext = (int(regionalfreq*Cseedrain*s_iseedmass)+1);
                    }
                    else {
         163 ->         s_nbext = int(regionalfreq*Cseedrain*(sites*LH*LH/10000));
                    }
                    
         163 ->     SLA=10000.0/s_LMA;    // computation of specific leaf area in cm^2/g for use in Domingues et al 2010 model of photosynthetic capacities
                    
                    //s_leaflifespan=1.5+pow(10,(7.18+3.03*log10(s_LMA*0.0001)));           //this is the expression from Reich et al 1991 Oecologia (San Carlos Rio Negro).
         163 ->     s_leaflifespan=pow(10,(2.040816*(2.579713-log10(SLA))));    //this is the expression from Reich et al. 1997 PNAS (provides probably more realistic estimates for species with high LMA).
                    //s_leaflifespan=0.5+pow(10,(-2.509+1.71*log10(s_LMA)));    //this is the expression from Wright et al 2004 Nature (leaf economics spectrum).
         163 ->     s_time_young=1;
         163 ->     s_time_mature=s_leaflifespan/3.0;
         163 ->     s_time_old=s_leaflifespan-s_time_mature-s_time_young;
                    
                    /*** Normalization of the parameters ***/
                    /* vertical (NV) and horizontal (NH) scales */
                    
         163 ->     s_ah   *= NV*LH;
         163 ->     s_ds   *= NH;
         163 ->     s_hmax *= NV;
         163 ->     s_dmax *= NH;
         163 ->     s_dbh0 *= NH;
                    
         163 ->     s_nbind=0;
         163 ->     s_fci = 0.0;
                    
         163 ->     s_Vcmaxm=pow(10.0, minf((-1.56+0.43*log10(s_Nmass*1000.0)+0.37*log10(SLA)), (-0.80+0.45*log10(s_Pmass*1000.0)+0.25*log10(SLA))));
                    // this is equation 2 in Domingues et al 2010 PCE (coefficients from fig7) which made better fits than equation 1 (without LMA)
         163 ->     s_Jmaxm=pow(10.0, minf((-1.50+0.41*log10(s_Nmass*1000.0)+0.45*log10(SLA)), (-0.74+0.44*log10(s_Pmass*1000.0)+0.32*log10(SLA))));
                    // added as a Species member variable 14-04-2015; this is equ 2 in Domingues et al 2010 PCE (coefficients from fig7)
                    
         163 ->     s_Vcmax=s_Vcmaxm*s_LMA;
         163 ->     s_Jmax=s_Jmaxm*s_LMA;
                    
         163 ->     s_Rdark=s_LMA*(8.5341-130.6*s_Nmass-567.0*s_Pmass-0.0137*s_LMA+11.1*s_Vcmaxm+187600.0*s_Nmass*s_Pmass)*0.001;
                    
                    //s_Rdark corresponds to leaf maintenance respiration. From Table 6 in Atkin et al 2015 New phytologist v.2.0 */
                    
                    //s_Rdark=(82.36*(s_LMA*1e-3)-0.1561)*(s_LMA*1e-3);                 /* from Domingues et al 2007 */
                    //s_Rdark=0.01*s_Vcmax;                                             /* parameterization of Rdark commonly used in vegetation models */
                    //s_Rdark=0.02*s_Vcmax-0.01;                                        /* parameterization of von Caemmerer 2000 Table 2.3 page 45 */
                    
         163 ->     s_Gamma = 38.0*iCair;
                    
                    // s_Gamma at 25°C computed according to von Caemmerer 2000 formula: gamma=Kc*O*0.25/(2*Ko), with Kc=260 microbar, Ko=179mbar and O=210 mbar (the last value is from Farquhar et al 1980, the first two one are from von Caemmerer 2000 table 2.3 page 45). gamma is set to 36.9 on Atkin et al 2015. Could be a global variable. v.2.0
                    
         163 ->     s_LCP = s_Rdark/phi;    /* Computation of the light compensation point from dark respiration and the quantum yield phi. By definition, Rdark is in micromolC/m^2/s and it is used in the Species::NPP() routine */
                    
                    
                    
                #ifdef DCELL
                    if (NULL==(s_DCELL = new int[nbdcells])) cerr<<"!!! Mem_Alloc s_DCELLn";
                    for(int dcell=0;dcell<nbdcells;dcell++) s_DCELL[dcell]=0;
                    /***  field initialization ***/
                    if (NULL==(s_Seed = new int[sites])) cerr<<"!!! Mem_Alloc\n";
                    for(site=0;site<sites;site++) s_Seed[site]=0;
                #else
                    /***  field initialization ***/
         163 ->     if (NULL==(s_Seed = new int[sites])) cerr<<"!!! Mem_Alloc\n";
         163 ->     for(site=0;site<sites;site++) s_Seed[site]=0;
                #endif
                    
                #ifdef MPI
                    for(int i=0;i<4;i++) {
                        if (NULL==(s_Gc[i] = new unsigned char[sites])) cerr<<"!!! Mem_Alloc\n";
                        for(site=0;site<sites;site++) s_Gc[i][site]=0;
                    }
                #endif
         163 -> }
                
                
                /*############################
                 ###     Species Seeds     ###
                 ###   Species::FillSeed   ###
                 ###  Species::UpdateSeed  ###
                 ###   Species::AddSeed    ###
                 #############################*/
                
                /*###  Species::FillSeed  ###*/
                /* creates one seed at point (col,row) */
                
                #ifdef DCELL
                /* in the new approach with a mean field seed flux (DCELL), the function FillSeed has a new
                 role: it fills the vector s_DCELL that stores the number of produced seeds per timestep and per dcell */
                
                void Species::FillSeed(int dcol, int drow, int nbs) {
                    
                    s_DCELL[dcol+linear_nb_dcells*drow]+=nbs;
                }
                
                #else
                
   147772310 -> void Species::FillSeed(int col, int row) {
                    int site;
   147772310 ->     if(col < cols) {
   147772310 ->         if((row >= 0) && (row < rows)) {
   147772310 ->             site=col+cols*row;
   147772310 ->             if(_SEEDTRADEOFF){
   147772310 ->                 s_Seed[site]++;                         /* ifdef SEEDTRADEOFF, s_Seed[site] is the number of seeds of this species at that site */
                            }
                            else{
   147772310 ->                 if(s_Seed[site]!=1) s_Seed[site]=1;     /* If s_Seed[site] = 0, site is not occupied, if s_Seed[site] > 1, s_Seed[site] is the age of the youngest seed  */
                            }
                        }
                        
                #ifdef MPI                                       /* on each processor a stripe of forest is simulated.
                Nearest neighboring stripes are shared. Rque, this version is not valid ifdef SEEDTRADEOFF */
                        else if((row+rows >=0) && (row < 0)) {
                            site=col+cols*(row+rows);
                            if(s_Gc[0][site]!=1) s_Gc[0][site]=1;
                        }
                        else if((row >=rows) && (row < 2*rows)) {
                            site=col+cols*(row-rows);
                            if(s_Gc[1][site]!=1) s_Gc[1][site]=1;
                        }
                #endif
                    }
   147772310 -> }
                #endif
                
                
                
                /*### Species::UpdateSeed ###*/
                /* updates s_Seed field */
                /* new in v.2.3: not called within loop over sites, instead includes loop --> less function calling, BUT: no check of site occupation anymore, cf. below */
                
                #ifdef DCELL
                /* in the new approach with a mean field seed flux (DCELL), the function UpdateSeed
                 has a new role: it uses the vector s_DCELL to fill the s_Seed local seed bank */
                
                void Species::UpdateSeed() {
                    int site;
                    for(site=0;site<sites;site++) s_Seed[site]=0;
                    for(int dcell=0;dcell<nbdcells;dcell++){ // loop over dcells
                        int localseeds=min(s_DCELL[dcell],sites_per_dcell);
                        // store number of seeds in this dcell
                        // localseeds is capped by the max number of available sites in the dcell
                        s_DCELL[dcell]=0;
                        gsl_ran_multinomial(gslrand,sites_per_dcell,localseeds,prior_DCELL,post_DCELL);
                        //cerr << "Localseeds in dcell\t" << dcell << " : " << localseeds << endl;
                        /*float sumprior=0.0,sumpost=0;
                         for(int i=0;i<sites_per_dcell;i++){
                         sumprior+=prior_DCELL[i];sumpost+=post_DCELL[i];
                         }*/
                        //cerr <<"localseeds\t"<< localseeds << "\tsumprior\t"<< sumprior << "\tsumpost\t"<< sumpost << "\n";
                        // sample equiprobably all the sites in the dcell
                        for(int i=0;i<sites_per_dcell;i++){ // update the s_Seed site
                            site=MAP_DCELL[dcell][i];
                            s_Seed[site] = post_DCELL[i];
                            //cerr << "site\t" << site << "\tdcell\t" << dcell << "\tlocal_site\t" << i << "\tpost_DCELL[i]\t" << post_DCELL[i] << "\ts_Seed[site]\t" << s_Seed[site] << endl;
                        }
                    }
                    /*int summ=0;
                     for(site=0;site<sites;site++) summ=summ+s_Seed[site];
                     cerr << "Localseeds of species \t" << s_name  << "\t: " << summ << endl; */
                    
                    
                }
                #else
      978000 -> void Species::UpdateSeed() {
                    
                    /* should probably be modified, since as implemented now seeds are erased every timestep (i.e. month in default mode)--> to be discussed */
                    
      978000 ->     if(_SEEDTRADEOFF){
      978000 ->         for(int site=0;site<sites;site++){
                # ifdef MPI
                            s_Gc[0][site]=s_Gc[1][site]=s_Gc[2][site]=s_Gc[3][site]=0;
                #endif
      978000 ->             s_Seed[site]=0;
                        }
                    }
                    
                    else{
                        /* new in v.2.3: version 2.2 checked whether site was occupied by tree: T[site].t_age>0) s_Seed[site]=0;     */
                        /* v.2.3 does not do this within UpdateSeed() anymore. Instead, it sets all occupied sites to zero directly within UpdateTree() */
      978000 ->         for(int site=0;site<sites;site++){
                            
                # ifdef MPI
                            s_Gc[0][site]=s_Gc[1][site]=s_Gc[2][site]=s_Gc[3][site]=0;
                #endif
                            /* seed bank ages or disappears */
      978000 ->             if(s_Seed[site]==s_dormDuration) s_Seed[site]=0;
      978000 ->             else if(s_Seed[site]!=0) s_Seed[site]++;            // v.2.3: bug fix: before, procedure was not restricted to existing seeds, therefore creation of seeds
                        }
                    }
      978000 -> }
                #endif
                
                #ifdef MPI
                /* deprecated in v.2 -- needs a new concept for spatial parallelization -- hopefully soon */
                /*########################################
                 ###  Calculation of shared fields s_Gc ###
                 ########################################*/
                void Species::AddSeed() {
                    /* Stripes shared by several processors are redefined */
                    for(int site=0;site<sites;site++) {
                        if(p_rank){
                            if(!s_Seed[site]) s_Seed[site] = s_Gc[2][site];
                            if(s_Seed[site]>1)
                                if(s_Gc[2][site]) s_Seed[site] = min(s_Seed[site],s_Gc[2][site]);
                        }
                        if(p_rank<size-1){
                            if(!s_Seed[site]) s_Seed[site] = s_Gc[3][site];
                            if(s_Seed[site]>1)
                                if(s_Gc[3][site]) s_Seed[site] = min(s_Seed[site],s_Gc[3][site]);
                        }
                    }
                }
                #endif
                
                
                /*############################
                 ###   Species::DeathRate  ###
                 #############################*/
                
                /* Here we assume a light-dependent version of the mortality.
                 basal is the minimal species death rate, depending on the species wood density.
                 When PPFD is smaller than the light compensation point, mortality risk is increased.
                 When NDD is defined, this death rate is increased by density-dependence effect that impact survival of trees with a dbh<10cm . */
                
                
                /* v.2.2 Simplify function Species::DeathRate -- JChave */
                
                /* Changed v.2.2, _NDD */
                /* v;2.3.0 function has been renamed to avoid possible confusion downstream */
                
                
       ##### -> inline float Species::DeathRateNDD(float PPFD, float dbh, int nppneg, float ndd) {
                    
       ##### ->     float dr=0;
       ##### ->     float basal=m*(1-s_wsg);
       ##### ->     float dd=deltaD*ndd*(1-2*dbh/s_dmax);
                    
       ##### ->     dr=basal;
       ##### ->     if (nppneg > s_leaflifespan) {
       ##### ->         dr+=1.0/timestep;
                    }
       ##### ->     if (dd > 0) {
       ##### ->         dr+=dd;
                    }
                    
       ##### ->     return dr*timestep;
       ##### -> }
                
                
                
   681532889 -> inline float Species::DeathRate(float PPFD, float dbh, int nppneg) {
                    
   681532889 ->     float dr=0;
   681532889 ->     float basal=m-m1*s_wsg;
                    
   681532889 ->     dr=basal;
                    
   681532889 ->     if (nppneg > s_leaflifespan) dr+=1.0/timestep;
                    
   681532889 ->     if (iter == int(nbiter-1))
   681532889 ->         output[26]<< s_wsg << "\t" << basal << "\t"  << dbh << "\t"  << dr   <<  "\n";
                    
   681532889 ->     return dr*timestep;
   681532889 -> }
                
                /*#############################################
                 ###   Farquhar von Caemmerer Berry model  ###
                 ###           Species:: NPP               ###
                 #############################################*/
                
                /* This function returns the leaf-level carbon assimilation rate in micromoles C/m^2/s according to Farquhar-von Caemmerer-Berry model */
                /* The function Species::dailyGPPleaf returns the primary productivity per unit leaf area, i.e. in micromoles C/m^2/s.
                 It is converted into gC per m^2 of leaf per timestep by "*189.3*timestep" accounting only for the light hours (12 hours instead of 24): 189.3=12*3600*365.25*12/1000000
                 BEWARE: 12 is the molar mass of C, and also the number of light hours in a day
                 BEWARE: timestep is given as fraction of a year, so what is computed is actually the full assimilation per year which, in turn, is multiplied by the fraction per year that is under consideration
                 BEWARE: slight inconsistency through use of 365.25 when daily timestep is likely to be given as 365, but not incorrect
                 Commented version below was in use prior to version 2.3.0 -- use of lookup tables for acceleration of T dependence. cf. Bernacchi et al 2003 PCE; von Caemmerer 2000
                 derivation of s_fci (ci/ca) according to Medlyn et al 2011, see also Prentice et al 2014 Ecology Letters and Lin et al 2015 Nature Climate Change --- initial version: s_fci = minf(-0.04*s_d13C-0.3*(log(PPFD)-s_factord13Cb)*s_factord13Ca-0.57, 1.0);
                 from d13C (see cernusak et al 2013) without explicit model of stomatal conductance; min added in order to prevent ci:ca bigger than 1 (even though Ehleringer et al 1986 reported some values above 1 (Fig3) */
                
                
  1576443286 -> inline float Species::GPPleaf(float PPFD, float VPD, float T) {
                    
                    /* v.2.3.0: theta defined as a global variable */
                    //theta=0.7;   // this is the fixed value of theta used by von Caemmerer 2000
                    
                    //float theta=0.76+0.018*T-0.00037*T*T;         // theta, but temperature dependent cf. Bernacchi et al 2003 PCE
                    
                    /* Parameters for Farquhar model, with temperature dependencies */
  1576443286 ->     int convT= int(iTaccuracy*T); // temperature data at a resolution of Taccuracy=0.1°C -- stored in lookup tables ranging from 0°C to 50°C ---
  1576443286 ->     float KmT    =LookUp_KmT[convT];
  1576443286 ->     float GammaT =LookUp_GammaT[convT];
  1576443286 ->     tempRday    +=s_Rdark*LookUp_tempRday[convT];
  1576443286 ->     float VcmaxT =s_Vcmax*LookUp_VcmaxT[convT];
  1576443286 ->     float JmaxT  =s_Jmax*LookUp_JmaxT[convT];
                    
  1576443286 ->     s_fci=g1/(g1+sqrt(VPD));
                    
                    /* FvCB model */
                    
  1576443286 ->     float I=alpha*PPFD;
  1576443286 ->     float J = (I+JmaxT-sqrt((JmaxT+I)*(JmaxT+I)-4.0*theta*JmaxT*I))*0.5/theta;
  1576443286 ->     float A = minf(VcmaxT/(s_fci+KmT),0.25*J/(s_fci+2.0*GammaT))*(s_fci-GammaT);
                    
  1576443286 ->     return A;
  1576443286 -> }
                
                /* dailyGPPleaf returns the assimilation rate (computed from Species::GPPleaf) averaged across the daily fluctuations in climatic conditions (light, VPD and T), in micromoles C/m^2/s */
                
                /* used only by _DAILYLIGHT */
                
                
  1500709556 -> inline float Species::dailyGPPleaf(float PPFD, float VPD, float T, float dens, float CD) {
  1500709556 ->     float ppfde,dailyA=0.0;
                    
  1500709556 ->     for(int i=0; i<24; i++) {
  1500709556 ->         ppfde=PPFD*daily_light[i];
  1500709556 ->         if(ppfde > 0.1)
                            // new v.2.3.0: compute GPP only if enough light is available threshold is arbitrary, but set to be low: in full sunlight ppfd is aroung 700 W/m2, and even at dawn, it is ca 3% of the max value, or 20 W/m2. The minimum threshold is set to 0.1 W/m2
                            // Future update: compute slightly more efficiently, using 3-hourly values? This will have to be aligned with climate forcing layers (e.g. NCAR)
  1500709556 ->             dailyA+=GPPleaf(ppfde, VPD*daily_vpd[i], T*daily_T[i]);
                        //the 6 lines in comment below corresponds to a finer version in which the multiplier is computed and used every 48 half hour, ie. with the corresponding environment instead of assuming a constant multiplier correponding the one at maximum incoming irradiance
                        //float hhA=0;
                        //hhA=GPPleaf(PPFD*daily_light[i], VPD*daily_vpd[i], T*daily_T[i]);
                        //float alpha=phi*PPFD*daily_light[i]/hhA;
                        //float D=klight*dens*CD;
                        //hhA*=alpha/(D*(alpha-1))*log(alpha/(1+(alpha-1)*exp(-D)));
                        //dailyA+=hhA;
                    }
                    //daily_light is the averaged (across one year, meteo station Nouragues DZ) and normalized (from 0 to 1) daily fluctuation of light, with half-hour time step, during the day time (from 7am to 7pm, ie 12 hours in total), same for daily_vpd and daily_T. Taking into account these daily variation is necessary considering the non-linearity of FvCB model
                    
  1500709556 ->     if(_FASTGPP){
  1500709556 ->         float alpha=phi*PPFD/GPPleaf(PPFD, VPD, T);             //alpha is a non-dimensional figure used to compute the multiplier below
  1500709556 ->         float D=klight*dens*CD;                                 //D is a non-dimensional figure used to compute the multiplier below
  1500709556 ->         float m=alpha/(D*(alpha-1))*log(alpha/(1+(alpha-1)*exp(-D)));
  1500709556 ->         if (m>=1.0 || CD > 7.0) {
  1500709556 ->             cout << "m pb FASTGPP !!!" << endl;
                            
                        }
  1500709556 ->         dailyA*=alpha/(D*(alpha-1))*log(alpha/(1+(alpha-1)*exp(-D)));  // the FvCB assimilation rate computed at the top of the tree crown is multiplied by a multiplier<1, to account for the lower rate at lower light level within the crown depth. This multiplier is computed assuming that change in photosynthetic assimilation rate within a tree crown is mainly due to light decrease due to self-shading following a Michealis-menten relationship (ie. we assume that 1/ the change is not due to changes in VPD or temperature, which are supposed homogeneous at the intra-crown scale, and 2/ that other tree contributions to light decrease is neglected).
                    }
  1500709556 ->     dailyA*=0.0417;                                 // 0.0417=1/24 (24=12*2 = number of half hours in the 12 hours of daily light)
  1500709556 ->     tempRday*=0.0417;
  1500709556 ->     return dailyA;
  1500709556 -> }
                
                
                /*############################################
                 ############################################
                 ############     Tree  class    ############
                 ############################################
                 ############################################*/
                
                class Tree {
                    
                private:
                    float t_C;                    /* flexural force intensity, _TREEFALL, float? */
                    
                public:
                    int   t_site,           /* location */
                    t_NPPneg;               /* diagnostic variable: number of consecutive timesteps with NPP<0 -- V.2.2 */
                    float t_dbh_thresh,       /* dbh threshold */
                    t_hmax,                 /* hmax, but not real maximum */
                    t_angle,                /* orientation of applied force, _TREEFALL */
                    t_dbhmature,            /* reproductive size threshold IM janv2017 -- v230 */
                    t_dbh,                  /* diameter at breast height (in m, but used in number of horizontal cells throughout all the code) */
                    t_Tree_Height,          /* total tree height (in m, but used in number of vertical cells throughout all the code) */
                    t_Crown_Depth,          /* crown depth (in m, but used in number of vertical cells throughout all the code) */
                    t_Crown_Radius,         /* crown radius (in m, but used in number of horizontal cells throughout all the code)*/
                    t_Ct,                   /* flexural force threshold, _BASICTREEFALL */
                    t_GPP,                  /* tree gross primary productivity */
                    t_NPP,                  /* tree net primary productivity (in gC/timestep) */
                    t_Rday,                 /* leaf respiration during day */
                    t_Rnight,               /* leaf respiration during night */
                    t_Rstem,                /* stem respiration */
                    t_PPFD,                 /* light intensity received by the tree (computed by Tree::Flux, depending of the LAI at the tree height) */
                    t_VPD,                    /* VPD at tree height -- v.2.2 */
                    t_T,                    /* Temperature at tree height -- v.2.2 */
                    t_ddbh,                 /* increment of dbh per timestep */
                    t_age,                  /* tree age */
                    t_youngLA,              /* total young leaf area, in m2 -- v.2.2  */
                    t_matureLA,             /* total mature leaf area, in m2 -- v.2.2  */
                    t_oldLA,                /* total old leaf area, in m2 -- v.2.2  */
                    t_leafarea,             /* total crown leaf area in m2 -- v.2.2  */
                    t_dens,                 /* tree crown average leaf density in m2/m2 -- v.2.2  */
                    t_litter;               /* tree litterfall at each timestep, in g (of dry mass) -- v.2.2  */
                    float *t_NDDfield;      /* _NDD */
                    
                    Species *t_s;
                    
                    unsigned short
                    t_from_Data,            /* indicator of whether tree is born through initialisation or through simulation routine */
                    t_sp_lab,               /* species label */
                    t_hurt;                 /* treefall index */
                    
      160000 ->     Tree(){                 /* constructor */
      160000 ->         t_from_Data = 0;
      160000 ->         t_sp_lab = 0;
      160000 ->         t_age = 0;
      160000 ->         t_hurt = 0;
      160000 ->         t_NPP=t_GPP=t_Rday=t_Rnight=t_Rstem=t_PPFD=t_VPD=t_T=0.0; /* new v.2.2 */
                        
      160000 ->         if(_TREEFALL){
      160000 ->             t_C  = 0;
      160000 ->             t_angle = 0.0;
                        }
      160000 ->         if(_BASICTREEFALL) t_Ct = 0.0;
                        
      160000 ->         t_dbh = t_Tree_Height = t_Crown_Radius = 0.0;
                        
      160000 ->     };
                    
      160000 ->     virtual ~Tree() {
      160000 ->         delete [] t_NDDfield;   /* _NDD */
      160000 ->     };	/* destructor */
                    
                    
                    void Birth(Species*,int,int);	/* tree birth */
                    
                    
                    void BirthFromData(Species *S, int nume, int site0, float dbh_measured); /* tree initialisation from field data */
                    void Death();                   /* tree death */
                    void Growth();                  /* tree growth */
                    void Fluxh(int h);             /* compute mean light flux received by the tree crown layer at height h new version (PPFD symmetrical with T and VPD) -- v230 */
                    void UpdateLeafDynamics();           /* computes within-canopy leaf dynamics (IM since v 2.1, as a standalone function in v.2.3.0) */
                    void UpdateTreeBiometry();      /* compute biometric relations, including allometry -- contains a large part of empirical functions */
                    int   Couple();                 /* force exerted by other trees, _TREEFALL */
                    
                    void DisperseSeed();            /* update Seed field */
                    void FallTree();                /* tree falling routine, _TREEFALL */
                    
                    void Update();                  /* tree evolution at each timestep */
                    void Average();                 /* local computation of the averages */
                    void CalcLAI();
                    //void TrunkLAI();              /* computation  of trunk LAI -- deprecated v.2.2 */
                    void histdbh();                 /* computation of dbh histograms */
                    void OutputTreeStandard();  /* creates standard output for trees, writes directly to cout stream */
                    void OutputTreeStandard(fstream& output);         /* overloading of function, creates standard output for trees */
                };
                
                
                /*##############################################
                 ####	            Tree birth              ####
                 ####  called by BirthInit and UpdateTree   ####
                 ##############################################*/
                
                
    27111540 -> void Tree::Birth(Species *S, int nume, int site0) {
                    
    27111540 ->     t_site = site0;
    27111540 ->     t_sp_lab = nume;            /* t_sp_lab is the species label of a site. Can be defined even if the site is empty (cf. persistence function defined in Chave, Am Nat. 2001) */
    27111540 ->     t_NPPneg=0.0;
    27111540 ->     t_s = S+t_sp_lab;
    27111540 ->     t_age = 1;
    27111540 ->     t_hurt = 0;
    27111540 ->     t_dbh=(t_s->s_dbh0);
    27111540 ->     t_ddbh=0.0;
    27111540 ->     t_dbh_thresh = ((t_s->s_dmax)-t_dbh)*flor(1.0+log(genrand2())*0.01)+t_dbh;
    27111540 ->     t_hmax = (t_s->s_hmax);
    27111540 ->     t_Tree_Height = H0;
    27111540 ->     t_Crown_Radius  = ra0;
    27111540 ->     t_Crown_Depth = de0;
    27111540 ->     t_dens=dens;
                    
    27111540 ->     t_youngLA=t_dens*PI*t_Crown_Radius*LH*t_Crown_Radius*LH*t_Crown_Depth*LV;
                    /* initially, all stems have only young leaves -- LA stands for leaf area */
    27111540 ->     t_matureLA=0;           /* this is the amount of leaf area at maturity */
    27111540 ->     t_oldLA=0;              /* leaf area of senescing leaves */
    27111540 ->     t_leafarea=t_youngLA;   /* should be sum of LA young+mature+old, but the equation is correct initially */
    27111540 ->     tempRday=0.0;
                    
    27111540 ->     float hrealmax=3*t_hmax * t_dbh_thresh/(3*t_dbh_thresh + 2*t_s->s_ah);
                    
    27111540 ->     t_dbhmature=t_s->s_dmax*0.5; // this correponds to the mean thresholds of tree size to maturity, according to Visser et al. 2016 Functional Ecology (suited to both understory short-statured species, and top canopy large-statured species). NOTE that if we decide to keep it as a fixed species-specific value, this could be defined as a Species calss variable, and computed once in Species::Init. -- v230
                    //float u=genrand2();
                    //t_dbhmature=maxf(0, -(t_s->s_dmax)*0.25*log((1-u)/u)+t_s->s_dmax*0.5);    // IM test 02-2017, try to introduce intra-species inter-individual variability in dbhmature, following a sigmoidal repartition function, as in Visser et al. 2016 and Wright et al. 2005
                    
    27111540 ->     if(_BASICTREEFALL) t_Ct = hrealmax*flor(1.0-vC*sqrt(-log(genrand2())));
    27111540 ->     (t_s->s_nbind)++;
    27111540 ->     nblivetrees++;
                    
                    /* setting diagnostic variables */
    27111540 -> }
                
                
                /*##############################################
                 ####   Tree Initialization from Data       ####
                 ##############################################*/
                
       ##### -> void Tree::BirthFromData(Species *S, int nume, int site0, float dbh_measured) {
                    
                    // entirely modelled following Tree::Birth
                    // main differences: dbh is given, related parameters are not set to fixed initial values, but derived through allometries
                    // for comments regarding allometries and t_leafarea cf. Tree::Growth
                    // for comments regarding everything else cf. Tree::Birth
                    
       ##### ->     t_site = site0;
       ##### ->     t_sp_lab = nume;
       ##### ->     t_NPPneg=0;
       ##### ->     t_s = S+t_sp_lab;
       ##### ->     t_age = 1;          //value not correct, but generally not problematic, used mainly as diagnostic variable and as indicator of whether tree is alive or not (death itself is independent of age), BUT: use as diagnostic variable cannot be ensured anymore and be careful if conditioning on t_age (e.g. for maturation)
       ##### ->     t_from_Data = 1;    //indicates that tree stems from data (and therefore t_age could not be used, etc.)
       ##### ->     t_hurt = 0;
                    
       ##### ->     if((t_s->s_dmax)*1.5 > dbh_measured) t_dbh = dbh_measured;                          // force dbh to be within limits of TROLL specifications
                    else {
       ##### ->         t_dbh = (t_s->s_dmax);
       ##### ->         cout << "Warning: DBH_measured > 1.5*DBH_max for species. DBH set to DBH_max for species \n";
                    }
                    
       ##### ->     t_ddbh=0.0;
       ##### ->     t_dbh_thresh = (t_s->s_dmax);
       ##### ->     t_hmax = (t_s->s_hmax);
                    
       ##### ->     t_Tree_Height = t_hmax * t_dbh/(t_dbh + (t_s->s_ah));
       ##### ->     t_Crown_Radius  = 0.80+10.47*t_dbh-3.33*t_dbh*t_dbh;;
       ##### ->     if (t_Tree_Height<5.0) t_Crown_Depth = 0.133+0.168*t_Tree_Height;
       ##### ->     else t_Crown_Depth = -0.48+0.26*t_Tree_Height;
       ##### ->     t_dens=dens;
       ##### ->     t_leafarea=t_dens*PI*t_Crown_Radius*LH*t_Crown_Radius*LH*t_Crown_Depth;
       ##### ->     t_youngLA=0.25*t_leafarea;
       ##### ->     t_matureLA=0.5*t_leafarea;
       ##### ->     t_oldLA=0.25*t_leafarea;
       ##### ->     Fluxh(int(t_Tree_Height)+1);
       ##### ->     tempRday=0.0;
                    
                    /* v.2.3.0 in version 2.3 and prior, fluxes were also initialized, resulting in a longer code, with multiple repetitions of the same empirical functions. It is better *NOT* to call empirical functions more than once. */
                    
       ##### ->     float hrealmax = 3*t_hmax * t_dbh_thresh/(3*t_dbh_thresh + 2*t_s->s_ah);
                    
       ##### ->     t_dbhmature=t_s->s_dmax*0.5; // after Visser et al. (2016)
                    
       ##### ->     if(_BASICTREEFALL) t_Ct = hrealmax*flor(1.0-vC*sqrt(-log(genrand2())));
       ##### ->     (t_s->s_nbind)++;
       ##### ->     nblivetrees++;
                    
       ##### -> }
                
                
                
                /*################################################
                 #### Contribution of each tree in LAI field  ####
                 ####          called by UpdateField          ####
                 #################################################*/
                
                /* modified in v.2.3: additional contribution to voxels that are not fully occupied by the tree crown. !!!: this does not calculate LAI3D directly, this only calculates the density in each voxel belonging to a tree. The final LAI field is calculated outside of the class Tree */
                
   960000000 -> void Tree::CalcLAI() {
   960000000 ->     if(t_age>0) {
                        int crown_base,
                        crown_top,
                        crown_r,
                        row_trunc,
                        col_trunc,
                        xx,yy,
                        col,row,
                        site;
                        
   960000000 ->         crown_r=int(t_Crown_Radius);
   960000000 ->         row_trunc=t_site/cols;
   960000000 ->         col_trunc=t_site%cols;
   960000000 ->         crown_base = int(t_Tree_Height-t_Crown_Depth);
   960000000 ->         crown_top = int(t_Tree_Height);
                        // loop over the tree crown
   960000000 ->         for(col=max(0,col_trunc-crown_r);col<=min(cols-1,col_trunc+crown_r);col++) {
   960000000 ->             for(row=max(0,row_trunc-crown_r);row<=min(rows-1,row_trunc+crown_r);row++) {
   960000000 ->                 xx=col_trunc-col;
   960000000 ->                 yy=row_trunc-row;
   960000000 ->                 if(xx*xx+yy*yy<=crown_r*crown_r){  // check whether voxel is within crown
   960000000 ->                     site=col+cols*row+SBORD;
   960000000 ->                     if(crown_top-crown_base == 0) {
   960000000 ->                         LAI3D[crown_top][site] += t_dens*t_Crown_Depth;
                                    }
                                    else{
   960000000 ->                         LAI3D[crown_top][site] += t_dens*(t_Tree_Height-crown_top);
   960000000 ->                         LAI3D[crown_base][site] += t_dens*(crown_base+1-(t_Tree_Height-t_Crown_Depth));
   960000000 ->                         if(crown_top-crown_base>=2){
   960000000 ->                             for(int h=crown_base+1;h <= crown_top-1;h++)
   960000000 ->                                 LAI3D[h][site] += t_dens;    // loop over the crown depth
                                        }
                                        
                                    }
                                }
                            }
                        }
                    }
   960000000 -> }
                
                
                
                /*###################################################
                 ####  Computation of PPFD right above the tree  ####
                 ####    called by Tree::Birth and Growth   in     ####
                 ####################################################*/
                
                /* v.2.3.: Tree::Fluxh() computes the average light flux received by a tree crown layer at height h , and also the average VPD and T it is thriving in (modified 1/02/2016)*/
                
  1500709556 -> void Tree::Fluxh(int h) {
  1500709556 ->     int count=0,
                    xx,yy,radius_int;
  1500709556 ->     float absorb=0.0;
  1500709556 ->     t_PPFD = 0.0;
  1500709556 ->     t_VPD  = 0.0;
  1500709556 ->     t_T    = 0.0;
  1500709556 ->     radius_int = int(t_Crown_Radius);
  1500709556 ->     if(radius_int == 0) {
  1500709556 ->         count=1;
  1500709556 ->         if (h < HEIGHT) absorb = minf(LAI3D[h][t_site+SBORD],19.5);
                        // absorb = 0.0 by default
  1500709556 ->         int intabsorb=int(absorb*20.0);
  1500709556 ->         t_PPFD = Wmax*LookUp_flux[intabsorb];
  1500709556 ->         t_VPD  = VPDmax*LookUp_VPD[intabsorb];
  1500709556 ->         t_T    = tmax - LookUp_T[intabsorb];
                    }
                    else {
                        int row0,col0;
  1500709556 ->         row0=t_site/cols;
  1500709556 ->         col0=t_site%cols;
  1500709556 ->         for(int col=max(0,col0-radius_int);col<min(cols,col0+radius_int+1);col++) {
  1500709556 ->             for(int row=max(0,row0-radius_int);row<min(rows,row0+radius_int+1);row++) {
                                //loop over the tree crown
  1500709556 ->                 xx=col0-col;
  1500709556 ->                 yy=row0-row;
  1500709556 ->                 if(xx*xx+yy*yy <= radius_int*radius_int) {
                                    //is the voxel within crown?
  1500709556 ->                     count++;
  1500709556 ->                     if (h < HEIGHT) absorb = minf(LAI3D[h][col+cols*row+SBORD],19.5);
  1500709556 ->                     int intabsorb=int(absorb*20.0);
  1500709556 ->                     t_PPFD += Wmax*LookUp_flux[intabsorb];
  1500709556 ->                     t_VPD  += VPDmax*LookUp_VPD[intabsorb];
  1500709556 ->                     t_T    += tmax - LookUp_T[intabsorb];
                                }
                            }
                        }
                    }
  1500709556 ->     t_PPFD *= 1.0/float(count);
  1500709556 ->     t_VPD  *= 1.0/float(count);
  1500709556 ->     t_T    *= 1.0/float(count);
  1500709556 -> }
                
                
                /*############################################
                 ####            Tree growth              ####
                 ####         called by UpdateTree        ####
                 #############################################*/
                
   654536679 -> void Tree::Growth() {
                    
                    /* Flux Tree variables */
   654536679 ->     t_GPP=0.0;
   654536679 ->     t_NPP=0.0;
   654536679 ->     t_Rday=0.0;
   654536679 ->     t_Rnight=0.0;
   654536679 ->     t_Rstem=0.0;
   654536679 ->     tempRday=0.0;
                    
                    /* Local environmental Tree variables */
   654536679 ->     t_PPFD=0.0;
   654536679 ->     t_VPD=0.0;
   654536679 ->     t_T=0.0;
                    
                    /* Leaf dynamics module */
                    //t_litter=0.0;
                    //float flush=0.0; // flushing leaves
                    
                    /* variables for flux computations */
                    
   654536679 ->     t_age+= timestep;                               /* new v.2.2: increments are not 1 yr, but the duration of the timestep (usually 1 or <1, i.e. 1/12 if monthly, 1/365 if daily */
                    
                    // computation of average t_GPP (per area) from the sum of GPP of each tree crown layer:
                    
                    // Farquhar is applied once per tree crown (at the top of the crown) (48 times per timestepifdef DAILIGHT, once per timestep if not), a pultiplier is net used to account for the decrease in photosynthetic rate with light decreae within the tree crown.
                    /* v.2.3.1 -- fast GPP calculation option. In addition, the daily computation of the Farquhar model is now the default option (_DAILYLIGHT is deprecated) */
   654536679 ->     if(_FASTGPP){
   654536679 ->         Fluxh(int(t_Tree_Height)+1);
   654536679 ->         t_GPP = (t_s->dailyGPPleaf(t_PPFD, t_VPD, t_T, t_dens, t_Crown_Depth));
   654536679 ->         t_Rday += tempRday;
   654536679 ->         tempRday=0.0;
                    }
                    else{
   654536679 ->         int crown_base=int(t_Tree_Height-t_Crown_Depth)+1; // for flux above crown base
   654536679 ->         int crown_top=int(t_Tree_Height)+1;                // for flux above crown top
                        
   654536679 ->         for(int h=crown_base; h<=crown_top; h++) {
   654536679 ->             Fluxh(h);
   654536679 ->             t_GPP+=t_s->dailyGPPleaf(t_PPFD, t_VPD, t_T, t_dens, t_Crown_Depth);
   654536679 ->             t_Rday+=tempRday;
   654536679 ->             tempRday=0.0;
                        }
   654536679 ->         float inb_layer=1.0/float(crown_top-crown_base+1);  // for averaging procedure
   654536679 ->         t_GPP   *=inb_layer;
   654536679 ->         t_Rday  *=inb_layer;
                    }
                    
                    /* Computation of GPP. New v.2.2: assumes an efficiency of 0.5 for young and old leaves vs. 1 for mature leaves */
                    //t_GPP*=(0.5*t_youngLA+t_matureLA+0.5*t_oldLA)*189.3*timestep;
                    
                    /* effLA is the scaling factor used for all fluxes new in v.2.3.0 */
   654536679 ->     float effLA=0.5*(t_leafarea+t_matureLA)*189.3*timestep;
                    
   654536679 ->     t_GPP*=effLA;
                    
                    /* new v.2.2. sapwood thickness (useful to compute stem respiration) */
   654536679 ->     float sapthick=0.04;
   654536679 ->     if (t_dbh < 0.08) sapthick=0.5*t_dbh;
                    
                    /* new v.2.2 stem respiration -- update lookup v230 */
   654536679 ->     int convT= int(iTaccuracy*temp); // temperature data at a resolution of Taccuracy=0.1°C -- stored in lookup tables ranging from 0°C to 50°C ---
   654536679 ->     int convTnight= int(iTaccuracy*tnight); // temperature data at a resolution of Taccuracy=0.1°C -- stored in lookup tables ranging from 0°C to 50°C ---
   654536679 ->     t_Rstem=sapthick*(t_dbh-sapthick)*(t_Tree_Height-t_Crown_Depth)*LookUp_Rstem[convT];
   654536679 ->     t_Rday *= effLA*0.40;
   654536679 ->     t_Rnight=(t_s->s_Rdark)*effLA*LookUp_Rnight[convTnight];
                    
   654536679 ->     t_NPP = 0.75*(t_GPP - 1.5*(t_Rday+t_Rnight+t_Rstem));
                    /* Rleaf=Rday+Rnight is multiplied by 1.5 to also account for fine root respiration (cf as in Fyllas et al 2014 and Malhi 2012); Rstem is multiplied by 1.5 to account for coarse root respiration (according to the shoot root biomass ratio of 0.2 - Jérôme's paper in prep- and also to branch respiration (Meir & Grace 2002, Cavaleri 2006, Asao 2005). */
                    
   654536679 ->     if(t_NPP<0.0){
   654536679 ->         t_NPPneg++;
   654536679 ->         t_NPP=0.0;
                        /* v.2.3.0 -- Line of code below was odd. If NPP <0.0, then to ensure C balance it should be simply reset to NPP=0 at this stage */
                        //t_NPP=t_GPP - 1.5*(t_Rday+t_Rnight+t_Rstem); REMOVED AS OF v.2.3.0.a4
                    }
                    else {
   654536679 ->         t_NPPneg=0;
                        /**** NPP allocation to wood and tree size increment *****/
   654536679 ->         UpdateTreeBiometry();
                    }
                    
                    /**** NPP allocation to leaves *****/
   654536679 ->     UpdateLeafDynamics();
                    
                    /* Output for control purposes */
                    
                #ifdef BEWARE_OF_PARAMETERIZED_OUTPUTS
                    // option below (FF v 2.3.1 may not work for some choices of timesteps
                #endif
                    
   654536679 ->     if(!_OUTPUT_reduced){
   654536679 ->         if (iter == 2) OutputTreeStandard(output[28]);
   654536679 ->         if (iter == int(nbiter/2)) OutputTreeStandard(output[29]);
   654536679 ->         if (iter == int(nbiter-1)) OutputTreeStandard(output[30]);
                        
   654536679 ->         if (t_site==2500) OutputTreeStandard(output[11]);
   654536679 ->         if (t_site==10380) OutputTreeStandard(output[12]);
   654536679 ->         if (t_site==100950) OutputTreeStandard(output[13]);
   654536679 ->         if (t_site==12090) OutputTreeStandard(output[14]);
   654536679 ->         if (t_site==120090) OutputTreeStandard(output[15]);
   654536679 ->         if (t_site==150667) OutputTreeStandard(output[16]);
                    }
   654536679 -> }
                
                /*####################################################
                 ####       Leaf dynamics and C allocation        ####
                 ####         called by Tree::Growth              ####
                 #####################################################*/
                
   654536679 -> void Tree::UpdateLeafDynamics() {
                    
                    // make a standalone function for leaf dynamics & litter?
                    
                    /**** NPP allocation to leaves *****/                                       /* rk: in this current scheme of leaf demography and phenology in three leaf age classes: only the old leaves generate treefall, and the dynamic of leaves cycle is generated by the dynamic of NPP, with a total leaf biomass varying - as opposed to De Weirdt et al 2012 in ORCHIDEE, but as in Wu et al 2016 but importantly without prescribing litterfall- */
                    
   654536679 ->     float flush=2.0*t_NPP*falloccanopy*0.68/(t_s->s_LMA);                           /* this is to convert the NPP allocated to leaves (falloccanopy is the fraction of biomass assumed to be alloacted to canopy (leaves+reproductive organs+twigs) at each timestep - Malhi et al 2011-, 68% of which is allocated to leaves - chave et al 2008, Chave et al 2010-), in new leaf area (2 is to convert carbon mass in biomass and LMA to convert leaf biomass into leaf area).*/
                    
                    /* litter module */
                    
                    
   654536679 ->     t_litter=t_oldLA/(t_s->s_time_old);
                    
                    /* leaf cycle */
                    
   654536679 ->     float new_mature = t_youngLA/(t_s->s_time_young);
   654536679 ->     float new_old    = t_matureLA/(t_s->s_time_mature);
   654536679 ->     t_youngLA  += flush - new_mature;
   654536679 ->     t_matureLA += new_mature - new_old;
   654536679 ->     t_oldLA    += new_old - t_litter;
   654536679 ->     t_leafarea  = t_youngLA + t_matureLA + t_oldLA;
                    
                    /* update t_dens */
                    
   654536679 ->     t_litter*=t_s->s_LMA;
                    
   654536679 ->     float crownvolume=PI*t_Crown_Radius*LH*t_Crown_Radius*LH*t_Crown_Depth*LV;
   654536679 ->     t_dens=t_leafarea/crownvolume;
                    
   654536679 -> }
                
   213842063 -> void Tree::UpdateTreeBiometry(){
                    /* New standalone function in v.2.3.0 */
                    
                    /* Tree dbh increment */
   213842063 ->     t_ddbh=0.0;
   213842063 ->     float volume=2.0*t_NPP/(t_s->s_wsg) * fallocwood * 1.0e-6;
   213842063 ->     if (t_dbh>t_dbh_thresh) volume*=flor(3.0-2.0*t_dbh/t_dbh_thresh);
                    
                    /* volume in m^3: the first factor of 2 is to convert C into biomass. the 1/s_wsg to convert biomass into volume. the 1e-6 term converts cm^3 into m^3 (the sole metric unit in the model). fallocwood is the fraction of biomass allocated to aboveground wood (stem + branches) growth. For the time being, we shall assume that a fixed proportion of NPP is allocated into AGB production. Currently, 0.20=%biomasse allocated to stem increment could be a global variable, even though this % allocation could in fact vary with resouce variation/co-limitation*/
                    
                    /* taking into account wood elements recycling (ex. fallen branches etc...) */
                    //t_ddbh = flor( volume* 4.0/( 3.0*PI*t_dbh*LH*t_Tree_Height*LV ) )* NH;
   213842063 ->     t_ddbh = flor( volume/(0.559*t_dbh*LH*t_Tree_Height*LV*(3.0-t_dbh/(t_dbh+t_s->s_ah))) )* NH;
                    
                    /* With V=pi*r^2*h, increment of volume = dV = 2*pi*r*h*dr + pi*r^2*dh */
                    /* With isometric growth assumption (ddbh/dbh=dh/h)and dbh=2*r: dV=3/4*pi*dbh*h*ddbh, ddbh in m, it follows: ddbh = 4/3 * V = 4/3 * 1/(pi*dbh*h)   */
                    
   213842063 ->     t_dbh += t_ddbh;
                    
                    /* update of tree height */
                    /* alternative calculation in concordance with isometric growth assumption: dh = h*ddbh/dbh */
                    /* t_Tree_Height += t_Tree_Height*t_ddbh/t_dbh; */
                    
   213842063 ->     t_Tree_Height = t_hmax * t_dbh/(t_dbh + (t_s->s_ah));
                    
                    /* update of tree crown depth -- allometry deduced from Piste Saint-Elie dataset */
   213842063 ->     if (t_Tree_Height<5.0) t_Crown_Depth = 0.17 + 0.13*t_Tree_Height;
   213842063 ->     else t_Crown_Depth = -0.48+0.26*t_Tree_Height;
                    /*t_Crown_Depth=exp(-1.169+1.098*log(t_Tree_Height));
                     29/04/15: try with allometry used in Fyllas et al 2014 (see SI, from Poorter et al 2006)*/
                    
   213842063 ->     t_Crown_Radius  = 0.80+10.47*t_dbh-3.33*t_dbh*t_dbh;
                    // allometry deduced from Piste Saint-Elie dataset
                    //t_Crown_Radius=sqrt(iPi*exp(-1.853+1.888*log(t_Tree_Height)));
                    // 29/04/15: try with allometry used in Fyllas et al 2014 (see SI, from Poorter et al 2006)
   213842063 -> }
                
                
                /*####################################################
                 ####           Death of the tree                ####
                 ####         called by Tree::Update             ####
                 ####################################################*/
                
    27002806 -> void Tree::Death() {
                    
    27002806 ->     t_age=0;
    27002806 ->     t_dbh = t_Tree_Height = t_Crown_Radius = t_Crown_Depth= 0.0;
    27002806 ->     t_hurt = 0;
    27002806 ->     if(_TREEFALL){
    27002806 ->         t_angle = 0.;
    27002806 ->         t_C = t_Ct = 0;
                    }
    27002806 ->     if ((t_s->s_nbind)>0) (t_s->s_nbind)--;
    27002806 ->     nblivetrees--;
    27002806 ->     t_s = NULL;
                    
    27002806 -> }
                
                
                /*#################################
                 ####      Seed dispersal      ####
                 ####  called by UpdateField   ####
                 #################################*/
                
   654421349 -> void Tree::DisperseSeed(){
                    /* New v.2.0 reproduction can only occur for trees that receive enough
                     light (twice the LCP) */
                    /* New v.2.1 threshold of maturity is defined as a size threshold
                     (and not age as before), following Wright et al 2005 JTE */
   654421349 ->     if((t_dbh>=t_dbhmature)&&(t_PPFD>2.0*(t_s->s_LCP))) {
                        float rho,theta_angle;
   654421349 ->         int nbs=0;
   654421349 ->         if(_SEEDTRADEOFF){
   654421349 ->             nbs=int(t_NPP*2.0*falloccanopy*0.08*0.5*(t_s->s_iseedmass)*0.05);    /* nbs is the number of seeds produced at this time step; it is computed from the NPP (in g) allocated to reproductive organs -fruits and seeds-, *2 is to convert in biomass,  * 0.40 is to obtain the NPP allocated to canopy (often measured as litterfall), drawn from Malhi et al 2011 Phil. trans roy. Soc. and 0.08 is the part of litterfall corresponding the fruits+seeds, drawn from Chave et al 2008 JTE; assumed to be twice the biomass dedicated to seeds only (ie without fruits), and then divided by the mass of a seed to obtain the number of seeds */
                            //nbs=(int)nbs;
                        }
   654421349 ->         else nbs=nbs0;
                        //else nbs=int(t_NPP*2*falloccanopy*0.08*0.5); /* test 17/01/2017: use a factor to translate NPP into seeds produced, but not species specific, not linked to mass of grains */
                        
   654421349 ->         for(int ii=0;ii<nbs;ii++){                                                 /* Loop over number of produced seeds */
                            
   654421349 ->             rho = 2.0*((t_s->s_ds)+t_Crown_Radius)*float(sqrt(fabs(log(genrand2()*iPi))));    /* Dispersal distance rho: P(rho) = rho*exp(-rho^2) */
   654421349 ->             theta_angle = float(twoPi*genrand2());                                                /* Dispersal angle theta */
   654421349 ->             t_s->FillSeed(flor(int(rho*cos(theta_angle))+t_site%cols), /* column */               /* Update of field s_Seed */
   654421349 ->                           flor(int(rho*sin(theta_angle))+t_site/cols));      /* line */
                            
                        }
                    }
                    
   654421349 -> }
                //#endif
                
                
                /*##################################
                 ####   Tree death and growth   ####
                 ####   called by UpdateTree    ####
                 ##################################*/
                
   960000000 -> void Tree::Update() {
                    
                    int death;
                    
   960000000 ->     if(t_age) {
                        
   960000000 ->         if(_NDD)
   960000000 ->             death = int(genrand2()+t_s->DeathRateNDD(t_PPFD, t_dbh,t_NPPneg, t_NDDfield[t_sp_lab]));
                        else
   960000000 ->             death = int(genrand2()+t_s->DeathRate(t_PPFD, t_dbh, t_NPPneg));
                        
   960000000 ->         if(death){
                            /* Natural death caused by unsustained photosynthesis and density dependance */
   960000000 ->             nbdead_n1++;
                            /* Increments number of deaths */
   960000000 ->             if(t_dbh*LH>0.1) nbdead_n10++;
                            /* same but only for trees > 10cm */
                            /* New v.2.2. new outputs */
   960000000 ->             if(!_OUTPUT_reduced) {
   960000000 ->                 if(iter == 2) output[23] << "N\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   960000000 ->                 if(iter == int(nbiter/2)) output[24]<< "N\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   960000000 ->                 if(iter == int(nbiter-1)) output[25]<< "N\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
                            }
   960000000 ->             Death();
                        }
   960000000 ->         else if(_BASICTREEFALL && t_Tree_Height<2*t_hurt*genrand2()) {          // given probability of death is 1-0.5*t_Tree_Height/t_hurt
                            /* Death caused by a treefall (t_hurt) */
   960000000 ->             nbdead_c1++;   /* Increments number of treefalls */
   960000000 ->             if(t_dbh*LH>0.1) nbdead_c10++;/* same but only for trees > 10cm */
   960000000 ->             if(!_OUTPUT_reduced){
   960000000 ->                 if(iter == 2) output[23] << "OT\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   960000000 ->                 if(iter == int(nbiter/2)) output[24]<< "OT\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   960000000 ->                 if(iter == int(nbiter-1)) output[25]<< "OT\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
                            }
   960000000 ->             Death();
                        }
                        else {/* If no death, then growth */
   960000000 ->             t_hurt = 0;
   960000000 ->             Growth();
                        }
                    }
   960000000 -> }
                
                
                /*##################################
                 ####           Treefall         ####
                 #### called by UpdateTreefall   ####
                 ####################################*/
                
                
   654536679 -> void Tree::FallTree() {
                    int xx,yy;
                    //if(_TREEFALL)
                    //if(Couple()>t_Ct) { /* above a given stress threshold the tree falls */
                    
   654536679 ->     if(genrand2()*t_Tree_Height > t_Ct){
                        // given: probability of treefall = 1-t_Ct/t_Tree_Height
   654536679 ->         float t_angle = float(twoPi*genrand2());
                        // random angle
                        int row0,col0,h_int, r_int;
   654536679 ->         float h_true = t_Tree_Height*LV;
   654536679 ->         nbTreefall1++;
   654536679 ->         if(t_dbh*LH>0.1) nbTreefall10++;
   654536679 ->         Thurt[0][t_site+sites] = int(t_Tree_Height);
                        // Thurt[0] saves the integer tree height, here exactly at the place where the tree fell...
   654536679 ->         row0=t_site/cols;       /* fallen stem destructs other trees */
   654536679 ->         col0=t_site%cols;
   654536679 ->         h_int = int(h_true*NH);
   654536679 ->         for(int h=1;h<h_int;h++) {
                            // loop on the fallen stem (horizontally)
   654536679 ->             xx=int(flor(col0+h*cos(t_angle)));
                            // get projection in col (= xx) direction, where xx is absolute location
   654536679 ->             if(xx<cols){
   654536679 ->                 yy=   int(row0+h*sin(t_angle));
                                // get projection in row (= yy) direction, where yy is absolute location
   654536679 ->                 Thurt[0][xx+(yy+rows)*cols] = int(t_Tree_Height);                           // Thurt[0] where the stem fell, calculation: xx+(yy+rows)*cols= xx + yy*cols + rows*cols = xx + yy*cols + sites
                            }
                        }
   654536679 ->         xx=col0+int((h_true*NH-t_Crown_Radius)*cos(t_angle));
                        // where crown ends/starts
                        /* fallen crown destructs other trees */
   654536679 ->         yy=row0+int((h_true*NH-t_Crown_Radius)*sin(t_angle));
   654536679 ->         r_int = int(t_Crown_Radius);
   654536679 ->         for(int col=max(0,xx-r_int);col<min(cols,xx+r_int+1);col++) {
                            /* loop on the fallen crown (horizontally) */
   654536679 ->             for(int row=yy-r_int;row<yy+r_int+1;row++) {
   654536679 ->                 if((col-xx)*(col-xx)+(row-yy)*(row-yy)<r_int*r_int) Thurt[0][col+(row+rows)*cols] = int((t_Tree_Height-t_Crown_Radius*NV*LH)*0.5);
                            }
                        }
   654536679 ->         if(iter == 2) output[23] << "T\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   654536679 ->         if(iter == int(nbiter/2)) output[24]<< "T\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   654536679 ->         if(iter == int(nbiter-1)) output[25]<< "T\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   654536679 ->         Death();
                    }
                    //}
   654536679 -> }
                
       ##### -> int Tree::Couple() {
                    int site2,quadist,haut0,xx,yy, radius_int,h_int;
                    float fx, fy,temp,lai;
       ##### ->     radius_int = int(t_Crown_Radius);
       ##### ->     h_int = int(t_Tree_Height);
       ##### ->     haut0 = int(t_Tree_Height-t_Crown_Depth);
       ##### ->     if(radius_int){
                        int row0,col0;
       ##### ->         row0=t_site/cols;
       ##### ->         col0=t_site%cols;
       ##### ->         fx = fy = 0.0;
       ##### ->         for(int col=max(0,col0-radius_int);col<min(cols,col0+radius_int+1);col++) {
       ##### ->             for(int row=row0-radius_int;row<=row0+radius_int;row++) {
       ##### ->                 xx=col0-col;
       ##### ->                 yy=row0-row;
       ##### ->                 quadist = xx*xx+yy*yy;
       ##### ->                 if((quadist<=radius_int*radius_int)&&quadist) {
                                    //site2 = col+cols*(row+RMAX); //modif 23/03/2011
       ##### ->                     site2 = col+cols*row+SBORD;
       ##### ->                     for(int h=haut0;h<=h_int;h++) {
       ##### ->                         if(h_int<HEIGHT) lai = LAI3D[h_int][site2]-LAI3D[h_int+1][site2];
       ##### ->                         else  lai = LAI3D[h_int][site2];
       ##### ->                         if(lai>dens) { // needs to be changed when TREEFALL is revised
       ##### ->                             temp = 1.0/sqrt(float(quadist));
       ##### ->                             if(temp>0.0) {
       ##### ->                                 fx += float(xx)*temp;
       ##### ->                                 fy += float(yy)*temp;
                                            }
                                        }
                                    }
                                }
                            }
                        }
       ##### ->         t_C = int(sqrt(fx*fx+fy*fy)*t_Tree_Height);
       ##### ->         if(fx!=0.0) t_angle=atan2(fy,fx);
       ##### ->         else t_angle = Pis2*sgn(fy);
                    }
       ##### ->     else{t_C = 0; t_angle = 0.0; }
       ##### ->     return t_C;
       ##### -> }
                
                
                
                /*#####################################################
                 ####      For Average and OutputField             ####
                 ######################################################*/
                
   960000000 -> void Tree::Average() {
   960000000 ->     if(t_age>0) {
   960000000 ->         if(t_dbh*LH >= 0.1) {
   960000000 ->             (t_s->s_output_field[1])++;
   960000000 ->             t_s->s_output_field[6] += t_dbh*LH*t_dbh*LH;
                        }
   960000000 ->         if(t_dbh*LH >= 0.3) (t_s->s_output_field[2])++;
   960000000 ->         t_s->s_output_field[3] += t_dbh*LH*t_dbh*LH;
   960000000 ->         t_s->s_output_field[4] += t_NPP*1.0e-6;
   960000000 ->         t_s->s_output_field[5] += t_GPP*1.0e-6;
   960000000 ->         t_s->s_output_field[7] += 0.0673*pow(t_s->s_wsg*t_Tree_Height*LV*t_dbh*t_dbh*LH*LH*10000, 0.976);  // this is the allometrtic equ 4 in Chave et al. 2014 Global Change Biology to compute above ground biomass
   960000000 ->         t_s->s_output_field[8] += t_Rday*1.0e-6;
   960000000 ->         t_s->s_output_field[9] += t_Rnight*1.0e-6;
   960000000 ->         t_s->s_output_field[10] += t_Rstem*1.0e-6;
   960000000 ->         t_s->s_output_field[11] += t_litter*1.0e-6;
                        
                    }
   960000000 -> }
                
      640000 -> void Tree::histdbh() {
      640000 ->     if(t_age) nbdbh[int(100.*t_dbh*LH)]++;
                    // compute the diameter distribution density
                    // where dbh is in cm (it is in number of horizontal cells throughout the code)
                    // values are always rounded down (so nbdbh[30] gives you trees with more than 30 cm dbh, and less than 31))
      640000 -> }
                
                
                /*#####################################################
                 ####      User Output for Control Purposes        ####
                 ######################################################*/
                
                
       ##### -> void Tree::OutputTreeStandard(fstream& output){
       ##### ->     output << iter << "\t" << t_site << "\t" << t_sp_lab << "\t" << t_Tree_Height << "\t" << t_dbh << "\t"  << t_ddbh << "\t" << t_litter << "\t" << t_age << "\t" << t_leafarea << "\t" << t_youngLA<< "\t" << t_matureLA << "\t" << t_oldLA << "\t" << t_Crown_Radius << "\t" << t_Crown_Depth << "\t" << t_dens  <<  "\t" << t_PPFD  <<"\t" << t_GPP  <<"\t" << t_NPP <<"\t" << t_Rstem <<"\t" << t_Rday  <<"\t" << t_Rnight << "\t" << t_site << "\t" << LAI3D[int(t_Tree_Height)][t_site+SBORD] << "\t" << LAI3D[int(t_Tree_Height-t_Crown_Depth)+1][t_site+SBORD] << endl;
       ##### -> }
                
       ##### -> void Tree::OutputTreeStandard(){
       ##### ->     cout << iter << "\t" << t_site << "\t" << t_sp_lab << "\t" << t_Tree_Height << "\t" << t_dbh << "\t"  << t_ddbh << "\t" << t_litter << "\t" << t_age << "\t" << t_leafarea << "\t" << t_youngLA<< "\t" << t_matureLA << "\t" << t_oldLA << "\t" << t_Crown_Radius << "\t" << t_Crown_Depth << "\t" << t_dens  <<  "\t" << t_PPFD  <<"\t" << t_GPP  <<"\t" << t_NPP <<"\t" << t_Rstem <<"\t" << t_Rday  <<"\t" << t_Rnight << "\t" << t_site << "\t" << LAI3D[int(t_Tree_Height)][t_site+SBORD] << "\t" << LAI3D[int(t_Tree_Height-t_Crown_Depth)+1][t_site+SBORD] << endl;
       ##### -> }
                
                
                /* Class objects */
                
                Species *S=NULL;
                Tree *T=NULL;
                
                
                /*############################################
                 ############################################
                 ############     MAIN PROGRAM    ###########
                 ############################################
                 ############################################*/
                
                //int main(int argc,char *argv[]) {
       ##### -> int main(){
                    
                    /***********************/
                    /*** Initializations ***/
                    /***********************/
                #ifdef MPI   /* Lookup processor number / total number of processors */
                    MPI_Init(&argc,&argv);
                    MPI_Comm_rank(MPI_COMM_WORLD,&p_rank);
                    MPI_Comm_size(MPI_COMM_WORLD,&size);
                #else
       ##### ->     mpi_rank = 0;
       ##### ->     mpi_size = 1;
                #endif
                #ifdef easyMPI
                    MPI::Init();
                    easympi_rank = MPI::COMM_WORLD.Get_rank();
                    easympi_size = MPI::COMM_WORLD.Get_size();
                    //MPI_Get_library_version(version, &len);
                    //std::cout << "Hello, world!  I am " << rank << " of " << size << "(" << version << ", " << len << ")" << std::endl;
                    //cout<< "Hello, world!  I am " << easympi_rank << " of " << easympi_size<<endl;
                #else
       ##### ->     easympi_rank = 0;
       ##### ->     easympi_size =1;
                #endif
                    
                    
                #ifdef DCELL
                    // Stuff for constant number generator
                    const gsl_rng_type *Trandgsl;
                    gsl_rng_env_setup();
                    Trandgsl = gsl_rng_default;
                    gslrand = gsl_rng_alloc (Trandgsl);
                #endif
                    /*
                    for(int argn=1;argn<argc;argn++){ // Arguments of the input and output files 
                        if(*argv[argn] == '-'){
                            switch(*(argv[argn]+1)){
                                case 'i':
                                    bufi = argv[argn]+2;
                                    break;
                                case 'o':
                                    buf = argv[argn]+2;
                                    break;
                                case 'f':                      // new v.2.3: initialisation from field, 'f' for "forest", "field data" 
                                    bufi_data = argv[argn]+2;
                                    break;
                                case 'n':
                                    easympi_rank=atoi(argv[argn]+2); // new v.2.2 
                            }
                        } 
                    }*/
                  
       ##### ->     cout<< easympi_rank;
       ##### ->     int t=(int) time(NULL);
       ##### ->     int seed =3*t+2*(easympi_rank+1)+1;
       ##### ->     sgenrand2i(seed);
       ##### ->     sgenrand2(seed);
       ##### ->     cout<< "On proc #" << easympi_rank << " seed: " << seed <<  " rng: "<< genrand2() << endl;
       ##### ->     cout << genrand2()<< endl;
       ##### ->     cout << genrand2()<< endl;
                    
                    // input files
                
                    //sprintf(inputfile,"%s",bufi);
       ##### ->     sprintf(inputfile,"%s","input_file_v231.txt");
                    //sprintf(buf, "%s", "output"); 
                
                    
                    
                
       ##### ->     if(_FromData){
       ##### ->         sprintf(inputfile_data,"%s",bufi_data);
                    }
                    //in this version of the code, the code user is expected to use the input txt file name with its extension name, as eg. "input.txt", when setting the program's argument
                    //sprintf(inputfile,"%s.txt",bufi);
                    
       ##### ->     if(!_OUTPUT_reduced)
                    {
       ##### ->         sprintf(outputinfo,"%s_%i_par.txt",buf, easympi_rank);                     /* Files with general output info */
       ##### ->         cout<< "On proc #" << easympi_rank << " seed: " << seed <<  " rng: "<< genrand2() <<  endl;
       ##### ->         out.open(outputinfo, ios::out);
       ##### ->         if(!out) cerr<< "ERROR with par file"<< endl;
       ##### ->         sprintf(outputinfo,"%s_%i_info.txt",buf, easympi_rank);
       ##### ->         out2.open(outputinfo, ios::out);
       ##### ->         if(!out2) cerr<< "ERROR with info file"<< endl;
                    }
       ##### ->     Initialise();           /* Read global parameters */
                    
       ##### ->     AllocMem();             /* Memory allocation */
                    
       ##### ->     if(_FromData){
       ##### ->         InitialiseFromData();   /* Initial configuration of the forest, read from data */
                    }
                    
       ##### ->     BirthInit();            /* Initial configuration of the forest */
       ##### ->     out.close();
                    
       ##### ->     cout << "klight is: " << klight << endl;
       ##### ->     cout << "CO2 concentration is: " << Cair << endl;
                    
                    /***********************/
                    /*** Evolution loop  ***/
                    /***********************/
                    
       ##### ->     double start_time,stop_time, duration=0.0;           /* for simulation duration */
       ##### ->     stop_time = clock();
       ##### ->     for(iter=0;iter<nbiter;iter++) {
       ##### ->         start_time = stop_time;
                        
       ##### ->         Evolution();
       ##### ->         stop_time = clock();
       ##### ->         duration +=flor(stop_time-start_time);
                        
                        /****** Output for 100 year analysis ******/
                        
       ##### ->         if(_OUTPUT_last100 && nbiter>100 && iter > (nbiter-101)) OutputSnapshotDetail(output[33]);  // 100 years development
                        
                        /****** Final Outputs ******/
                        
       ##### ->         if(iter == nbiter-2){
       ##### ->             OutputSnapshot(output[10]);                         // Final Pattern
                            
                            
       ##### ->             if(!_OUTPUT_reduced){
       ##### ->                 OutputSnapshot(output[10]);                         // Final Pattern
       ##### ->                 OutputSpeciesParameters(output[18]);
                            }
       ##### ->             if(_OUTPUT_fullLAI){
       ##### ->                 OutputFullLAI(output[36],output[37]);               // CHM and LAD patterns
                            }
                        }
                    }
                    
                    /*************************/
                    /*** End of simulation ***/
                    /*************************/
                    
       ##### ->     float durf = duration/double(CLOCKS_PER_SEC);        /* output of the effective CPU time */
                #ifdef MPI
                    MPI_Reduce(&durf,&durf,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                #endif
       ##### ->     if(!mpi_rank) {
       ##### ->         cout << "\n";
                #ifdef MPI
                        out2 << "Number of processors : "<< mpi_size << "\n";
                #endif
       ##### ->         out2 << "Average computation time : "<< durf/float(mpi_size) << " seconds.\n";
       ##### ->         out2 << "End of simulation.\n";
       ##### ->         cout << "\nNumber of processors : "<< mpi_size << "\n";
       ##### ->         cout << "Average computation time : "<< durf/float(mpi_size) << " seconds.\n";
       ##### ->         cout << "End of simulation.\n";
                    }
       ##### ->     out2.close();
                    
                    /*Free dynamic memory */ /* added in oct2013 */
       ##### ->     FreeMem();
                    
                #ifdef easyMPI
                    MPI::Finalize();
                #endif
                    
       ##### ->     exit(1);
                }
                
                
                /*###########################################
                 ############################################
                 #######  Initialization routines    ########
                 ############################################
                 ############################################*/
                
           1 -> void Initialise() {
                    
                    int ligne;
                    
           1 ->     fstream In(inputfile, ios::in);
                    
                    /*** Initialization of the simulation parametres ***/
                    /***************************************************/
                    
           1 ->     if (In) {
           1 ->         for(ligne=0;ligne<4;ligne++) In.getline(buffer,128,'\n');
                        
                        /*General parameters */
           1 ->         In >> cols; In.getline(buffer,128,'\n');
           1 ->         In >> rows; In.getline(buffer,128,'\n');
           1 ->         sites = rows*cols;
                #ifdef DCELL
                        In >> length_dcell; In.getline(buffer,128,'\n');
                        sites_per_dcell = length_dcell*length_dcell;
                        nbdcells = int(sites/sites_per_dcell);
                        linear_nb_dcells = int(cols/length_dcell);
                        cerr << "Number of dcells" << nbdcells << endl;
                        cerr << "Lin number of dcells" << linear_nb_dcells << endl;
                #endif
           1 ->         In >> nbiter; In.getline(buffer,128,'\n');
           1 ->         In >> iterperyear; In.getline(buffer,128,'\n');
           1 ->         timestep=1.0/float(iterperyear);
           1 ->         cerr << "iterperyear " << iterperyear << endl;
           1 ->         In >> NV; In.getline(buffer,128,'\n');
           1 ->         In >> NH; In.getline(buffer,128,'\n');
           1 ->         LV = 1.0/NV;
           1 ->         LH = 1.0/NH;
           1 ->         In >> nbout; In.getline(buffer,128,'\n');
           1 ->         if(nbout) freqout = nbiter/nbout;
           1 ->         In >> numesp; In.getline(buffer,128,'\n');
           1 ->         In >> p_nonvert; In.getline(buffer,128,'\n');
           1 ->         for (int i=0; i<=23; i++) In >> daily_light[i];
           1 ->         In.getline(buffer,128,'\n');
           1 ->         for (int i=0; i<=23; i++) In >> daily_vpd[i];
           1 ->         In.getline(buffer,128,'\n');
           1 ->         for (int i=0; i<=23; i++) In >> daily_T[i];
           1 ->         In.getline(buffer,128,'\n');
           1 ->         In.getline(buffer,128,'\n');
                        
                        /*Characters shared by species */
           1 ->         In >> klight; In.getline(buffer,128,'\n');
           1 ->         theta = 0.70; /* v.2.3.0 This could be added in the input file, just like klight */
           1 ->         In >> phi; In.getline(buffer,128,'\n');
           1 ->         In >> g1; In.getline(buffer,128,'\n');
           1 ->         In >> vC; In.getline(buffer,128,'\n');
           1 ->         In >> DBH0; In.getline(buffer,128,'\n');
           1 ->         In >> H0; In.getline(buffer,128,'\n');
           1 ->         In >> ra0; In.getline(buffer,128,'\n');
           1 ->         In >> ra1; In.getline(buffer,128,'\n');
           1 ->         In >> de0; In.getline(buffer,128,'\n');
           1 ->         In >> de1; In.getline(buffer,128,'\n');
           1 ->         In >> dens; In.getline(buffer,128,'\n');
           1 ->         In >> fallocwood; In.getline(buffer,128,'\n');
           1 ->         In >> falloccanopy; In.getline(buffer,128,'\n');
           1 ->         In >> Cseedrain; In.getline(buffer,128,'\n');
           1 ->         In >> nbs0; In.getline(buffer,128,'\n');
           1 ->         In >> m; In.getline(buffer,128,'\n');
           1 ->         In >> m1; In.getline(buffer,128,'\n');
           1 ->         In >> Cair; In.getline(buffer,128,'\n');
           1 ->         iCair = 1.0/Cair;
           1 ->         if (_NDD) {
           1 ->             In >> R; In.getline(buffer,128,'\n');
           1 ->             In >> deltaR; In.getline(buffer,128,'\n');
           1 ->             In >> deltaD; In.getline(buffer,128,'\n');
                        }
                        
           1 ->         DBH0 *= NH;
           1 ->         H0   *= NV;
           1 ->         ra0  *= NH;
           1 ->         de0  *= NV;
           1 ->         alpha = 4.0*phi;
                        /* apparent quantum yield to electron transport in mol e-/mol photons */
                        // see Mercado et al 2009 , the conversion of the apparent quantum yield in micromolCO2/micromol quantum into micromol e-/micxromol quantum is done by multipliyng by 4, since four electrons are needed to regenerate RuBP.
                        /* alpha is fixed at 0.3 mol e-/mol photons in Medlyn et al 2002
                         but see equ8 and Appendix 1 in Farquahr et al 1980: it seems that alpha should vary with leaf thickness: there is a fraction of incident light which is lost by absorption by other leaf parts than the chloroplast lamellae, and this fraction f may increase with leaf thickness.
                         With the values of the paper: alpha= 0.5*(1-f)=0.5*(1-0.23)=0.385, but this is a theoretical value and observations often report lower values (see ex discussion in medlyn et al 2005 Tree phsyiology, Lore Veeryckt values, Mercado et al 2009 Table 10, Domingues et al. 2014)*/
                    }
                    
                    else {
           1 ->         cout<< "ERROR with the input file of parameters" << endl;
                    }
                    
                    
                    /*** Information in file info ***/
                    /***********************************/
                    
           1 ->     if(!mpi_rank){
           1 ->         out2 << "\nTROLL simulator\n\n";
           1 ->         out2 << "\n   2D discrete network: horizontal step = " << LH
           1 ->         << " m, one tree per "<< LH*LH << " m^2 \n\n";
           1 ->         out2 << "\n   Tree : (t_dbh,t_Tree_Height,t_Crown_Radius,t_Crown_Depth) \n\n";
           1 ->         out2 << "\n            + one species label \n\n";
           1 ->         out2 << " Number of sites      : "<<rows<<"x"<<cols<<"\n";
           1 ->         out2 << " Number of iterations : "<<nbiter<<"\n";
           1 ->         out2 << " Duration of timestep : "<<timestep<<" years\n";
           1 ->         out2 << " Number of Species    : "<<numesp << "\n\n";
           1 ->         out2.flush();
                    }
                    
                    
                    /*** Initialization of trees ***/
                    /*******************************/
                    
           1 ->     if(NULL==(T=new Tree[sites])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc Tree" << endl;
                    }
                    
           1 ->     if(_NDD){
           1 ->         for(int site=0;site<sites;site++) {
           1 ->             if (NULL==(T[site].t_NDDfield = new float[numesp+1])) cerr<<"!!! Mem_Alloc\n";
           1 ->             for(int ii=0;ii<(numesp+1);ii++) T[site].t_NDDfield[ii]=0;
                        }
                    }
                    
                    
                    /*** Initialization of species ***/
                    /*********************************/
                    
                    int sp;
           1 ->     if(NULL==(S=new Species[numesp+1])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc Species" << endl;
                    }
                    
           1 ->     for(ligne=0;ligne<3;ligne++) In.getline(buffer,128,'\n');                           /* Read species parameters (ifstream In) */
           1 ->     for(sp=1;sp<=numesp;sp++) {
           1 ->         S[sp].Init(sp,In);
                    }
                    
                    /*** Initialization of environmental variables ***/
                    /*************************************************/
                    
           1 ->     In.getline(buffer,128,'\n');
           1 ->     In.getline(buffer,128,'\n');
           1 ->     In.getline(buffer,128,'\n');
                    
           1 ->     if(NULL==(Temperature=new float[iterperyear])) {                                // rk, the current structure of code suppose that environment is periodic (a period = a year), if one want to make climate vary, with interannual variation and climate change along the simulation, one just need to provide the full climate input of the whole simulation (ie number of columns=iter and not iterperyear) and change iterperyear by nbiter here.
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc Temperature" << endl;
                    }
                    
           1 ->     for (int i=0; i<iterperyear; i++) In >> Temperature[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "Temperature" << i << "\t"  << Temperature[i] <<  "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(DailyMaxTemperature=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc DailyMaxTemperature" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> DailyMaxTemperature[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "DailyMaxTemperature" << i << "\t"  << DailyMaxTemperature[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(NightTemperature=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc NightTemperature" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> NightTemperature[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "NightTemperature" << i << "\t"  << NightTemperature[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(Rainfall=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc Rainfall" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> Rainfall[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "Rainfall" << i << "\t"  << Rainfall[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(WindSpeed=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc WindSpeed" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> WindSpeed[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "WindSpeed" << i << "\t"  << WindSpeed[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(MaxIrradiance=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc Irradiance" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> MaxIrradiance[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "MaxIrradiance" << i << "\t"  << MaxIrradiance[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(MeanIrradiance=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc Irradiance" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> MeanIrradiance[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "MeanIrradiance" << i << "\t"  << MeanIrradiance[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(SaturatedVapourPressure=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc SaturatedVapourPressure" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> SaturatedVapourPressure[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "SaturatedVapourPressure" << i << "\t"  << SaturatedVapourPressure[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(VapourPressure=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc VapourPressure" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> VapourPressure[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "VapourPressure" << i << "\t"  << VapourPressure[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(VapourPressureDeficit=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc VapourPressureDeficit" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> VapourPressureDeficit[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "VapourPressureDeficit" << i << "\t"  << VapourPressureDeficit[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(DailyVapourPressureDeficit=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc DailyVapourPressureDeficit" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> DailyVapourPressureDeficit[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "DailyVapourPressureDeficit" << i << "\t"  << DailyVapourPressureDeficit[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(DailyMaxVapourPressureDeficit=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc DailyMaxVapourPressureDeficit" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> DailyMaxVapourPressureDeficit[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "DailyMaxVapourPressureDeficit" << i << "\t"  << DailyMaxVapourPressureDeficit[i] << "\t";
                    //cout<<endl;
                    
           1 ->     temp = Temperature[iter%iterperyear];
           1 ->     tmax=DailyMaxTemperature[iter%iterperyear];
           1 ->     tnight=NightTemperature[iter%iterperyear];
           1 ->     precip=Rainfall[iter%iterperyear];
           1 ->     WS=WindSpeed[iter%iterperyear];
           1 ->     Wmax=MaxIrradiance[iter%iterperyear]*1.678;       // 1.678 is to convert irradiance from W/m2 to micromol of PAR /s /m2, the unit used in the FvCB model of photosynthesis
           1 ->     Wmean=MeanIrradiance[iter%iterperyear];            // still in W/m2
           1 ->     e_s=SaturatedVapourPressure[iter%iterperyear];
           1 ->     e_a=VapourPressure[iter%iterperyear];
           1 ->     VPDbasic=VapourPressureDeficit[iter%iterperyear];
           1 ->     VPDday=DailyVapourPressureDeficit[iter%iterperyear];
           1 ->     VPDmax=DailyMaxVapourPressureDeficit[iter%iterperyear];
                    
           1 ->     In.close();
                    /* Close ifstream In */
                    
           1 ->     nbTbins=500;
           1 ->     float Taccuracy=0.1;
           1 ->     iTaccuracy=1.0/Taccuracy;
           1 ->     cerr << "Built-in maximal temperature: " << float(nbTbins)*Taccuracy <<endl;
           1 ->     if(NULL==(LookUp_KmT=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_KmT" << endl;
           1 ->     if(NULL==(LookUp_GammaT=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_GammaT" << endl;
           1 ->     if(NULL==(LookUp_tempRday=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_tempRday" << endl;
           1 ->     if(NULL==(LookUp_VcmaxT=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_VcmaxT" << endl;
           1 ->     if(NULL==(LookUp_JmaxT=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_JmaxT" << endl;
           1 ->     if(NULL==(LookUp_Rstem=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_Rstem" << endl;
           1 ->     if(NULL==(LookUp_Rnight=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_Rnight" << endl;
           1 ->     for(int i=0;i<nbTbins;i++) { // loop over "T" in GPPleaf()
           1 ->         float temper=float(i)*Taccuracy;
           1 ->         LookUp_KmT[i] = 404.0*exp(((temper-25.0)/(298*0.00831*(273+temper)))*59.36)*
           1 ->         (1+210*1.0/248.0*exp(-(temper-25.0)/(298*0.00831*(273+temper))*35.94))*iCair;
           1 ->         LookUp_GammaT[i]=37.0*exp(((temper-25.0)/(298*0.00831*(273+temper)))*23.4)*iCair;
           1 ->         LookUp_tempRday[i]=exp((temper-25.0)*0.1*log(3.09-0.0215*(25.0+temper)));
           1 ->         LookUp_VcmaxT[i]=exp(26.35-65.33/(0.00831*(temper+273.15)));
           1 ->         LookUp_JmaxT[i]=exp(17.57-43.54/(0.00831*(temper+273.15)));
                        
           1 ->         LookUp_Rstem[i]=39.6*378.7*PI*timestep*exp((temper-25.0)/10.0*log(2.0));
           1 ->         LookUp_Rnight[i]=exp((temper-25.0)*0.1*log(3.09-0.0215*(25.0+temper)));
                        /* exp((temp-25)/10*log(2)) is the temperature dependency of Rstem, supposing a constant Q10=2, according to Ryan et al 1994 and Meir & Grace 2002
                         exp((tnight-25)*0.1*log(3.09-0.0215*(25+tnight))) is the temperature dependencies used by Atkin 2015 (equ1) */
                        
                        
                    }
                    
                    
           1 ->     if(NULL==(LookUp_flux=new float[400])) cerr<<"!!! Mem_Alloc LookUp_flux" << endl;
           1 ->     if(NULL==(LookUp_VPD=new float[400])) cerr<<"!!! Mem_Alloc LookUp_VPD" << endl;
           1 ->     if(NULL==(LookUp_T=new float[400])) cerr<<"!!! Mem_Alloc LookUp_T" << endl;
           1 ->     for(int i=0;i<400;i++) { // loop over "absorb" in Fluxh()
           1 ->         float absorbance=float(i)/20.0;
           1 ->         LookUp_flux[i]=exp(-klight*absorbance);
           1 ->         LookUp_VPD[i]= 0.25+sqrt(maxf(0.0 , 0.08035714*(7.0-absorbance)));
                        // this expressions results from fit of observations of relationships between VPD and height within dense canopy (HOBO data on COPAS tower, Shuttleworth et al 1985; Camargo & Kapos 1995 journal of Tropical Ecology)
           1 ->         LookUp_T[i] =  0.4285714*(minf(7.0,absorbance));
                        // 0.4285714=3/7, assuming deltaT between the top canopy and dense understorey is constant = 3°C, could be refined.
                        
                    }
                    
           1 ->     In.open(inputfile, ios::in);
           1 ->     if(!mpi_rank) {
           1 ->         do{
           1 ->             In.getline(buffer,256,'\n');
           1 ->             out << buffer <<endl;
           1 ->         }while (!In.eof()) ;
                    }
                    
           1 ->     In.close();
                    /* Close ifstream In */
                    
                    
                    
                    /*** Initialization of output streams ***/
                    /****************************************/
                    
                    
                    
                    char nnn[200];
           1 ->     if(!mpi_rank) {
           1 ->         if(_OUTPUT_reduced){
           1 ->             sprintf(nnn,"%s_%i_outputs.txt",buf, easympi_rank);
           1 ->             output[0].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_final_pattern.txt",buf, easympi_rank);
           1 ->             output[10].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_vertd.txt",buf, easympi_rank);
           1 ->             output[32].open(nnn,ios::out);
           1 ->             sprintf(nnn,"%s_%i_litterfall.txt",buf, easympi_rank);
           1 ->             output[27].open(nnn, ios::out);
                            //sprintf(nnn,"%s_%i_endstate.txt",buf, easympi_rank);
                            //output[30].open(nnn, ios::out);
                        }
                        else{
           1 ->             sprintf(nnn,"%s_%i_abund.txt",buf, easympi_rank);
           1 ->             output[0].open(nnn, ios::out);
           1 ->             if (!output[0]) {
           1 ->                 cout<< "ERROR with abund file"<< endl;
                            }
           1 ->             sprintf(nnn,"%s_%i_abu10.txt",buf, easympi_rank);
           1 ->             output[1].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_abu30.txt",buf, easympi_rank);
           1 ->             output[2].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_ba.txt",buf, easympi_rank);
           1 ->             output[3].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_npp.txt",buf, easympi_rank);
           1 ->             output[4].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_gpp.txt",buf, easympi_rank);
           1 ->             output[5].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_ba10.txt",buf, easympi_rank);
           1 ->             output[6].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_ppfd0.txt",buf, easympi_rank);
           1 ->             output[7].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_death.txt",buf, easympi_rank);
           1 ->             output[8].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_state.txt",buf, easympi_rank);
           1 ->             output[9].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_final_pattern.txt",buf, easympi_rank);
           1 ->             output[10].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_site1.txt",buf, easympi_rank);
                            
                            // used to be added to explore potential link with Belassen curve, could be suppressed, but maybe useful to have an idea of the magnitude and distribution of increment of dbh
                            
           1 ->             output[11].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_site2.txt",buf, easympi_rank);
           1 ->             output[12].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_site3.txt",buf, easympi_rank);
           1 ->             output[13].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_site4.txt",buf, easympi_rank);
           1 ->             output[14].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_site5.txt",buf, easympi_rank);
           1 ->             output[15].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_site6.txt",buf, easympi_rank);
           1 ->             output[16].open(nnn, ios::out);
                            
                            //output[17] for parameter space is valid both for reduced and standard output, defined below
                            
           1 ->             sprintf(nnn,"%s_%i_sp_par.txt",buf, easympi_rank);
           1 ->             output[18].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_agb.txt",buf, easympi_rank);
           1 ->             output[19].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_Rday.txt",buf, easympi_rank);
           1 ->             output[20].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_Rnight.txt",buf, easympi_rank);
           1 ->             output[21].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_Rstem.txt",buf, easympi_rank);
           1 ->             output[22].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_death1.txt",buf, easympi_rank);
           1 ->             output[23].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_death2.txt",buf, easympi_rank);
           1 ->             output[24].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_death3.txt",buf, easympi_rank);
           1 ->             output[25].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_deathrate.txt",buf, easympi_rank);
           1 ->             output[26].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_litterfall.txt",buf, easympi_rank);
           1 ->             output[27].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_leafdens1.txt",buf, easympi_rank);
           1 ->             output[28].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_leafdens2.txt",buf, easympi_rank);
           1 ->             output[29].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_leafdens3.txt",buf, easympi_rank);
           1 ->             output[30].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_dbh.txt",buf, easympi_rank);
           1 ->             output[31].open(nnn,ios::out);
           1 ->             sprintf(nnn,"%s_%i_100yearsofsolitude.txt",buf, easympi_rank);
           1 ->             output[33].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_NDDfield.txt",buf, easympi_rank);
           1 ->             output[34].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_cica.txt",buf, easympi_rank);
           1 ->             output[35].open(nnn, ios::out);
                        }
                        
                        /*sprintf(nnn,"%s_%i_paramspace.txt",buf, easympi_rank);
                         output[17].open(nnn, ios::out);
                         
                         output[17] << "proc"  << "\t" << easympi_rank << endl;
                         output[17] << "phi"  << "\t" << phi << endl;
                         output[17] << "k"  << "\t" <<klight << endl;
                         output[17] << "fallocwood"  << "\t" << fallocwood << endl;
                         output[17] << "falloccanopy"  << "\t" << falloccanopy << endl;
                         output[17] << "m"  << "\t" << m << endl;
                         output[17] << "m1"  << "\t" << m1 << endl;
                         if(_OUTPUT_fullLAI){
                         sprintf(nnn,"%s_%i_CHM.txt",buf, easympi_rank);
                         output[36].open(nnn, ios::out);
                         sprintf(nnn,"%s_%i_LAI3D_avg.txt",buf, easympi_rank);
                         output[37].open(nnn, ios::out);
                         }*/
           1 ->     }
                    
                    
           1 -> }
                
                
                /***************************************
                 *** Initialisation from inventories ***
                 ***************************************/
                
                
       ##### -> void InitialiseFromData(){
                    // prepare data set beforehand: col/x_dim, row/y_dim, dbh_measured, species_label,
                    
       ##### ->     fstream In(inputfile_data, ios::in);                                                // input stream
                    float col_data, row_data, dbh_measured, sp_lab_data;                            // values needed for tree initialisation
                    
       ##### ->     int col_int, row_int, data_read=0, data_initialised=0;                          // diagnostics
       ##### ->     float height_max=0;                                                             // diagnostics
                    
       ##### ->     nblivetrees=0;
                    
                    //for (int line=0;line<30;line++) In.getline(buffer,128,'\n');
                    
       ##### ->     cout << "Reading from file " << inputfile_data << "\n";
                    
       ##### ->     In.getline(buffer,256,'\n');                                                    // skip header lines
                    
       ##### ->     cout << "Header line skipped \n";
                    
       ##### ->     while ((In >> col_data >> row_data >> dbh_measured  >> sp_lab_data) && data_read < sites)       // restricting to data sets with a maximum number of values corresponding to no. of sites
                    {
       ##### ->         In.getline(buffer, 256, '\n'); // reads additional information into buffer
                        
       ##### ->         if((sp_lab_data > 0) && (sp_lab_data <= numesp) && (col_data >= 0) && (col_data < cols) && (row_data >= 0) && (row_data < rows)){
                            
                            // read only species that are rendered in TROLL (species label to be added via R / comparison input file and data)
                            // cout << "col: " << round(col_data) << " row: " << round(row_data) << " species: " << sp_lab_data << " dbh: " << dbh_measured << " data measured \n";
                            
       ##### ->             dbh_measured = 0.001*dbh_measured;          //here given in mm, converting to m
       ##### ->             cout << dbh_measured << "\n";
       ##### ->             col_int = (int) (col_data+0.5f);            //rounding, works since negatives have been eliminated before
       ##### ->             row_int = (int) (row_data+0.5f);
                            
                            // immediate tree birth
                            
       ##### ->             if(T[col_int+row_int*cols].t_age==0) T[col_int+row_int*cols].BirthFromData(S,sp_lab_data,col_int+row_int*cols,dbh_measured);
                            
       ##### ->             if(height_max<T[col_int+row_int*cols].t_Tree_Height) height_max = T[col_int+row_int*cols].t_Tree_Height;
                            
                            // first attempt: simple, only trees with coordinates, only known species
                            // other possibilities: not spatially explicit and/or assign species randomnly to trees whose species are not known
                            
       ##### ->             data_initialised++;
                        }
       ##### ->         data_read++;
                    }
                    
       ##### ->     cout << "\n" << data_read << " rows read from file. " << data_initialised << " rows usable for initialisation from data. \n";
       ##### ->     cout << "Maximum height of trees included is: " << height_max << "\n";
       ##### ->     cout << "NBtrees from Data:\t" << nblivetrees << "\n";
       ##### ->     cout << "Initialisation from data finished \n";
       ##### -> }
                
                
                /***************************************
                 *** Field dynamic memory allocation ***
                 ***************************************/
                
           1 -> void AllocMem() {
                    
                    int spp,haut,i;
                    
                    // HEIGHT = 80;
                    // instead of static definition of height, calculate according to maximum height that can be reached by trees
                    
           1 ->     HEIGHT = 0;
                    
           1 ->     for(spp=1;spp<=numesp;spp++) {
           1 ->         HEIGHT = max(HEIGHT,int(S[spp].s_hmax*S[spp].s_dmax*1.5/(S[spp].s_dmax*1.5+S[spp].s_ah)));  //   in number of vertical cells
                    }
                    
           1 ->     cout << "HEIGHT " << HEIGHT << endl;
                    
                    float d,r;
           1 ->     d = 0.0;
           1 ->     r = 0.0;
           1 ->     for(spp=1;spp<=numesp;spp++){
           1 ->         d = maxf(d,S[spp].s_dmax*1.5);
                        /* in number of horizontal cells */
           1 ->         r = maxf(r,ra0+S[spp].s_dmax*1.5*ra1);
                        /* in number of horizontal cells */
                    }
                    
           1 ->     RMAX = int(r+p_nonvert*NH*LV*HEIGHT);
                    //  RMAX = int(r);
           1 ->     SBORD = cols*RMAX;
           1 ->     dbhmaxincm = int(100.*d);
                    
           1 ->     if(!mpi_rank) {
                        /*cout << "HEIGHT : " << HEIGHT
                         << " RMAX : " << RMAX << " DBH : " << DBH <<"\n";
                         cout.flush();*/
                        
           1 ->         if(RMAX>rows){
                            /* Consistency tests */
           1 ->             cerr << "Error : RMAX > rows \n";
           1 ->             exit(-1);
                        }
           1 ->         if(HEIGHT > rows){
           1 ->             cerr << "Error : HEIGHT > rows \n";
           1 ->             exit(-1);
                        }
                    }
                    
                    
                    /*** Initialization of dynamic Fields ***/
                    /****************************************/
                    
           1 ->     if (NULL==(nbdbh=new int[dbhmaxincm])) cerr<<"!!! Mem_Alloc\n";                         /* Field for DBH histogram */
           1 ->     if (NULL==(layer=new float[HEIGHT+1])) cerr<<"!!! Mem_Alloc\n";                         /* Field for variables averaged by vertical layer */
           1 ->     if (NULL==(SPECIES_GERM=new int[numesp+1])) cerr<<"!!! Mem_Alloc\n";                           /* Field for democratic seed germination */
           1 ->     if(_SEEDTRADEOFF){
           1 ->         if (NULL==(PROB_S=new float[numesp+1])) cerr<<"!!! Mem_Alloc\n";
                    }
           1 ->     if(_NDD){
           1 ->         if (NULL==(PROB_S=new float[numesp+1])) cerr<<"!!! Mem_Alloc\n";
                    }
                    //  if (NULL==(persist=new long int[nbiter])) cerr<<"!!! Mem_Alloc\n";                  /* Field for persistence */
                    //  if (NULL==(distr=new int[cols])) cerr<<"!!! Mem_Alloc\n";
                    
           1 ->     if (NULL==(LAI3D=new float*[HEIGHT+1]))                                                   /* Field 3D */
           1 ->         cerr<<"!!! Mem_Alloc\n";                                                            /* Trees at the border of the simulated forest need to know the canopy occupancy by trees in the neighboring processor.*/
           1 ->     for(haut=0;haut<(HEIGHT+1);haut++)                                                          /* For each processor, we define a stripe above (labelled 0) and a stripe below (1). Each stripe is SBORD in width.*/
           1 ->         if (NULL==(LAI3D[haut]=new float[sites+2*SBORD]))                                   /* ALL the sites need to be updated.*/
           1 ->             cerr<<"!!! Mem_Alloc\n";
           1 ->     for(haut=0;haut<(HEIGHT+1);haut++)
           1 ->         for(int site=0;site<sites+2*SBORD;site++)
           1 ->             LAI3D[haut][site] = 0.0;
                    
           1 ->     if (NULL==(Thurt[0]=new unsigned short[3*sites]))                                       /* Field for treefall impacts */
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->     for(i=1;i<3;i++)
           1 ->         if (NULL==(Thurt[i]=new unsigned short[sites]))
           1 ->             cerr<<"!!! Mem_Alloc\n";
                    
                #ifdef DCELL
                    /* MAP_DCELL is a list of vectors -- there is one vector per dcell, and the vector has as many entries as the number of sites per dcell, and returns the absolute site value of these sites -- this is useful to distribute seeds across the dcell */
                    int x0,y0,x,y,site0,site,dcol,drow;
                    if (NULL==(MAP_DCELL=new int*[nbdcells])) cerr<<"!!! Mem_Alloc\n";
                    for(int dcell=0;dcell<nbdcells;dcell++){
                        if (NULL==(MAP_DCELL[dcell]=new int[sites_per_dcell])) cerr<<"!!! Mem_Alloc\n";
                        for(x0=0;x0<length_dcell;x0++)
                            for(y0=0;y0<length_dcell;y0++){
                                site0=x0+y0*length_dcell;
                                dcol=dcell%linear_nb_dcells;
                                drow=dcell/linear_nb_dcells;
                                x=dcol*length_dcell+x0;
                                y=drow*length_dcell+y0;
                                //cerr << "x_MAP " << x << "\ty_MAP " << y << "\t";
                                site=x+y*cols;
                                MAP_DCELL[dcell][site0] = site;
                            }
                    }
                    if (NULL==(prior_DCELL=new double[sites_per_dcell])) cerr<<"!!! Mem_Alloc\n";
                    for(int i=0;i<sites_per_dcell;i++) prior_DCELL[i]=1.0;
                    if (NULL==(post_DCELL=new unsigned int[sites_per_dcell])) cerr<<"!!! Mem_Alloc\n";
                    for(int i=0;i<sites_per_dcell;i++) post_DCELL[i]=0;
                    
                    if (NULL==(prior_GERM=new double[numesp+1])) cerr<<"!!! Mem_Alloc\n";
                    for(int i=0;i<=numesp;i++) prior_GERM[i]=0.0;
                    if (NULL==(post_GERM=new unsigned int[numesp+1])) cerr<<"!!! Mem_Alloc\n";
                    for(int i=0;i<=numesp;i++) post_GERM[i]=0;
                    
                #endif
                    
                #ifdef MPI                                                                                      /* Fields for MPI operations */
                    for(i=0;i<2;i++){                                                                       /*  Two fields: one for the CL north (0) one for the CL south (1) */
                        if (NULL==(LAIc[i]=new unsigned short*[HEIGHT+1]))                                    /* These fields contain the light info in the neighboring procs (2*SBORD in width, not SBORD !). They are used to update local fields */
                            cerr<<"!!! Mem_Alloc\n";
                        for(haut=0;haut<(HEIGHT+1);haut++)
                            if (NULL==(LAIc[i][haut]=new unsigned short[2*SBORD]))
                                cerr<<"!!! Mem_Alloc\n";
                    }
                #endif
           1 -> }
                
                
                /***************************************
                 **** Initial non-local germination ****
                 ***************************************/
                
           1 -> void BirthInit() {
                    
           1 ->     if(!_FromData){
           1 ->         nblivetrees=0;
                    }
                #ifdef MPI
                    MPI_Barrier(MPI_COMM_WORLD);
                #endif
           1 ->     cout<<endl;
           1 -> }
                
                
                /*###############################################
                 ###############################################
                 #######  Evolution at each timestep    ########
                 ###############################################
                 ###############################################*/
                
        6000 -> void Evolution() {
                    
        6000 ->     UpdateField();                                          /* Update light fields and seed banks */
        6000 ->     UpdateTree();                                           /* Update trees */
        6000 ->     if(_BASICTREEFALL) UpdateTreefall();                    /* Compute and distribute Treefall events */
        6000 ->     Average();                                              /* Compute averages for outputs */
        6000 ->     OutputField();                                          /* Output the statistics */
        6000 -> }
                
                
                /*##################################
                 ####    Compute field LAI 3D    ###
                 ####    Compute field Seed     ####
                 ##################################*/
                
        6000 -> void UpdateField() {
                    
                    int site,haut;
        6000 ->     int spp=0;
                    
                    
                    /* set the iteration environment -- nb: the current structure of code suppose that environment is periodic (a period = a year), if one wants to input a variable climate, with interannual variation and climate change along the simulation, a full climatic input needs to be input (ie number of columns=iter and not iterperyear) and change iterperyear by nbiter here. */
                    //CURRENTLY NOT USED: precip, WS, Wmean, e_s, e_a,VPDbasic,VPDday
        6000 ->     temp=Temperature[iter%iterperyear];
        6000 ->     tmax=DailyMaxTemperature[iter%iterperyear];
        6000 ->     tnight=NightTemperature[iter%iterperyear];
        6000 ->     precip=Rainfall[iter%iterperyear];
        6000 ->     WS=WindSpeed[iter%iterperyear];
        6000 ->     Wmax=MaxIrradiance[iter%iterperyear]*1.678;       // 1.678 is to convert irradiance from W/m2 to micromol of PAR /s /m2, the unit used in the FvCB model of photosynthesis
        6000 ->     Wmean=MeanIrradiance[iter%iterperyear];            // still in W/m2
        6000 ->     e_s=SaturatedVapourPressure[iter%iterperyear];
        6000 ->     e_a=VapourPressure[iter%iterperyear];
        6000 ->     VPDbasic=VapourPressureDeficit[iter%iterperyear];
        6000 ->     VPDday=DailyVapourPressureDeficit[iter%iterperyear];
        6000 ->     VPDmax=DailyMaxVapourPressureDeficit[iter%iterperyear];
                    
                    /***  Compute Field LAI3D  ***/
                    /*****************************/
                    
                    
                #ifdef MPI
                    /* Reinitialize field LAI3D */
                    for(i=0;i<2;i++)
                        for(haut=0;haut<(HEIGHT+1);haut++)
                            for(site=0;site<2*SBORD;site++)
                                LAIc[i][haut][site] = 0;
                #endif
                    
                    int sbsite;
                    
        6000 ->     for(haut=0;haut<(HEIGHT+1);haut++)
        6000 ->         for(sbsite=0;sbsite<sites+2*SBORD;sbsite++)
        6000 ->             LAI3D[haut][sbsite] = 0.0;
                    
        6000 ->     for(site=0;site<sites;site++)                                    /* Each tree contribues to LAI3D */
        6000 ->         T[site].CalcLAI();
                    
        6000 ->     for(haut=HEIGHT;haut>0;haut--){                                 /* LAI is computed by summing LAI from the canopy top to the ground */
        6000 ->         for(site=0;site<sites;site++){
        6000 ->             sbsite=site+SBORD;
        6000 ->             LAI3D[haut-1][sbsite] += LAI3D[haut][sbsite];
        6000 ->             if (LAI3D[haut-1][sbsite] < 0) T[site].OutputTreeStandard();
                        }
                    }
                    
                    /*  for(site=0;site<sites;site++)       Trunks shade the cells in which they are
                     T[site].TrunkLAI();*/
                    
                #ifdef MPI
                    /* Communicate border of field */
                    /*MPI_ShareField(LAI3D,LAIc,2*SBORD);
                     This MPI command no longer exists in openMPI
                     Action 20/01/2016 TODO: FIX THIS */
                    MPI_ShareField(LAI3D,LAIc,2*SBORD);
                    for(haut=0;haut<(HEIGHT+1);haut++){
                        /* Add border effects in local fields */
                        if(mpi_rank)
                            for(site=0;site<2*SBORD;site++)
                                LAI3D[haut][site] += LAIc[0][haut][site];
                        if(mpi_rank<mpi_size-1)
                            for(site=0;site<2*SBORD;site++)
                                LAI3D[haut][site+sites] += LAIc[1][haut][site];
                    }
                #endif
                    
                    /*** Evolution of the field Seed **/
                    /*********************************/
                    
                    /* Pass seeds across processors => two more fields to be communicated between n.n. (nearest neighbor) processors.
                     NB: dispersal distance is bounded by the value of 'rows'.
                     At least 99 % of the seeds should be dispersed within the stripe or on the n.n. stripe.
                     Hence rows > 4.7*max(dist_moy_dissemination),for an exponential dispersal kernel.*/
                    
                #ifdef DCELL
                    if(iter%iterperyear == 0){
                        for(spp=1;spp<=numesp;spp++) {                              /* External seed rain: constant flux from the metacommunity */
                            for(int dcell=0;dcell<nbdcells;dcell++){
                                // loop over dcells and add exactly s_nbext seeds to s_DCELL
                                S[spp].s_DCELL[dcell]=S[spp].s_nbext;
                                //if(spp<10) cerr << "BeforeDis, dcell#\t" << dcell << "\ts_DCELL[dcell]\t" << S[spp].s_DCELL[dcell] << "\tS[spp].s_nbext\t" << S[spp].s_nbext <<endl;
                            }
                        }
                        for(site=0;site<sites;site++)                                       /* disperse seeds produced by mature trees */
                            if(T[site].t_age)
                                T[site].DisperseSeed();
                #else
        6000 ->         for(site=0;site<sites;site++)                                       /* disperse seeds produced by mature trees */
        6000 ->             if(T[site].t_age)
        6000 ->                 T[site].DisperseSeed();
                #endif
                #ifdef DCELL
                    }
                #endif
                    
                #ifdef MPI                                                              /* Seeds passed across processors */
                    for(spp=1;spp<=numesp;spp++) {
                        MPI_ShareSeed(S[spp].s_Gc,sites);
                        S[spp].AddSeed();
                    }
                #endif
                    
                #ifdef DCELL  // This entire section is commented as it is no longer needed in DCELL
                #else
        6000 ->     if(_SEEDTRADEOFF){
        6000 ->         if(!mpi_rank || S[spp].s_nbind*sites > 50000){
        6000 ->             for(spp=1;spp<=numesp;spp++) {                              /* External seed rain: constant flux from the metacommunity */
        6000 ->                 for(int ii=0;ii<S[spp].s_nbext;ii++){
        6000 ->                     site = genrand2i()%sites;
        6000 ->                     S[spp].s_Seed[site]++;
                                }
                            }
                        }
                    }
                    else {
        6000 ->         if(!mpi_rank || S[spp].s_nbind*sites > 50000){
        6000 ->             for(spp=1;spp<=numesp;spp++) {                              /* External seed rain: constant flux from the metacommunity */
        6000 ->                 for(int ii=0;ii<S[spp].s_nbext;ii++){
        6000 ->                     site = genrand2i()%sites;
        6000 ->                     if(S[spp].s_Seed[site]!=1)
        6000 ->                         S[spp].s_Seed[site] = 1; /* check for optimization */
                                }
                            }
                        }
                    }
                #endif
                    
                    
                #ifdef MPI
                    MPI_Barrier(MPI_COMM_WORLD);
                #endif
                    
        6000 ->     if(_NDD){
                        /*** Evolution of the field NDDfield **/
                        /**************************************/
                        
        6000 ->         float normBA=10000.0/(0.001+PI*R*R*BAtot);
        6000 ->         for(site=0;site<sites;site++) {
                            
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) {
                                /*if ((iter == int(nbiter-1))&&(site>80000)&&(site<85000))  {
                                 sor[142]<< T[site].t_NDDfield[spp] << "\t" ;
                                 }*/
        6000 ->                 T[site].t_NDDfield[spp]=0;
                            }
                            //if (iter == int(nbiter-1))  sor[142]<< "\n";
                            
        6000 ->             int row0=T[site].t_site/cols;
        6000 ->             int col0=T[site].t_site%cols;
        6000 ->             for(int col=max(0,col0-R);col<=min(cols-1,col0+R);col++) {
        6000 ->                 for(int row=max(0,row0-R);row<=min(rows-1,row0+R);row++) {                   /* loop over the neighbourhood */
        6000 ->                     int xx=col0-col;
        6000 ->                     int yy=row0-row;
        6000 ->                     float d=sqrt(xx*xx+yy*yy);
        6000 ->                     if((d<=R)&&(d>0))  {                                             /* is the voxel within the neighbourhood?  */
        6000 ->                         int j=cols*row+col;
        6000 ->                         if(T[j].t_age) T[site].t_NDDfield[T[j].t_sp_lab]+= PI* T[j].t_dbh * T[j].t_dbh*0.25*normBA;
                                        
                                    }
                                    
                                    
                                }
                                
                            }
                        }
                    }
        6000 -> }
                
                
                /*##############################
                 ####	Birth, Growth       ####
                 ####	and death of trees  ####
                 ##############################*/
                
        6000 -> void UpdateTree() {
                    
                    int site,spp;
                    float flux;
                    
                #ifdef DCELL
                    
                    for(spp=1;spp<=numesp;spp++) S[spp].UpdateSeed();
                    
                    // A much simpler version of seed recruitment is implemented again based on the idea
                    // of a multinomial sampling of the s_Seed field.
                    
                    for(site=0;site<sites;site++){
                        int nbseeds=0;
                        for(spp=1;spp<=numesp;spp++) nbseeds+=S[spp].s_Seed[site];
                        if(T[site].t_age == 0 && nbseeds > 0){
                            //int summ=0;
                            //for(spp=1;spp<=numesp;spp++) summ+=S[spp].s_Seed[site];
                            //cerr << site << "\t" << summ << endl;
                            prior_GERM[0]=0.0;post_GERM[0]=0;
                            for(spp=1;spp<=numesp;spp++){
                                prior_GERM[spp]=double(S[spp].s_Seed[site]*S[spp].s_seedmass);
                                post_GERM[spp]=0;
                            }
                            //for(spp=1;spp<=numesp;spp++) cerr << prior_GERM[spp] << " ";
                            
                            gsl_ran_multinomial(gslrand,numesp+1,1,prior_GERM,post_GERM);
                            float sumprior=0.0,sumpost=0;
                            for(int i=1;i<=numesp;i++){
                                sumprior+=prior_GERM[i];sumpost+=post_GERM[i];
                            }
                            //cerr << numesp << "\t"<< sumprior << "\t"<< sumpost << "\n";
                            
                            //for(spp=1;spp<=numesp;spp++)
                            //    cerr << spp << "\tpost_GERM\t" << post_GERM[spp] << endl;
                            int selected_species=0;
                            for(spp=1;spp<=numesp;spp++) if(post_GERM[spp]==1){
                                selected_species=spp;
                                break;}
                            //cerr << "selected species:\t" << spp <<endl;
                            flux = Wmax*exp(-flor(LAI3D[0][site+SBORD])*klight);
                            if(flux>(S[selected_species].s_LCP))
                                T[site].Birth(S,selected_species,site);
                            /* If enough light, germination, initialization of NPP (LCP is the species light compensation point -- here, light is the sole environmental resources tested as a limiting factor for germination, but we should think about adding nutrients (N,P) and water conditions... */
                            for(spp=1;spp<=numesp;spp++) S[spp].s_Seed[site]=0;
                            
                            //}
                        }
                    }
                #else
                    int iii;
        6000 ->     if(_SEEDTRADEOFF){
        6000 ->         for(site=0;site<sites;site++) {                                             /***** Local germination *****/
        6000 ->             if(T[site].t_age == 0) {
        6000 ->                 iii=0;
        6000 ->                 float tot=0;                                                        /* _SEEDTRADEOFF */
        6000 ->                 for(spp=1;spp<=numesp;spp++){                                       /* lists all the species with a seed present at given site... */
        6000 ->                     if(S[spp].s_Seed[site]) {
        6000 ->                         SPECIES_GERM[iii]=spp;
        6000 ->                         if(_NDD){
        6000 ->                             float p=S[spp].s_Seed[site]*S[spp].s_seedmass/(T[site].t_NDDfield[spp]*10000+1);
        6000 ->                             PROB_S[iii]=tot+ p;
        6000 ->                             tot+=p;
                                        }
                                        else{
        6000 ->                             PROB_S[iii]=tot+ S[spp].s_Seed[site]*S[spp].s_seedmass;
        6000 ->                             tot+=S[spp].s_Seed[site]*S[spp].s_seedmass;
                                        }
        6000 ->                         iii++;
                                    }
                                }
        6000 ->                 if(iii) {                                                           /* ... and then randomly select one of these species */
        6000 ->                     double p=genrand2();                                    /* if SEEDTRADEOFF is defined, probability of species recruit are proportional to the number of seeds time the seed mass, if NDD is also defined the probablility is also inversly proportional to the species NDDfield term at that site */
        6000 ->                     float itot=1.0/tot;
        6000 ->                     int s=0;
        6000 ->                     while (p>PROB_S[s]*itot) {s++;}
        6000 ->                     spp=SPECIES_GERM[s];
        6000 ->                     flux = Wmax*exp(-flor(LAI3D[0][site+SBORD])*klight);
        6000 ->                     if(flux>(S[spp].s_LCP)){
                                        /* If enough light, germination, initialization of NPP (LCP is the species light compensation point*/
                                        /* here, light is the sole environmental resources tested as a limiting factor for germination, but we should think about adding nutrients (N,P) and water conditions... */
        6000 ->                         T[site].Birth(S,spp,site);
                                    }
                                }
                            }
                        }
                    }
                    
                    else {
                        
        6000 ->         for(site=0;site<sites;site++) {                                     /***** Local germination *****/
        6000 ->             if(T[site].t_age == 0) {
        6000 ->                 iii=0;
                                
        6000 ->                 float tot=0;
                                
        6000 ->                 for(spp=1;spp<=numesp;spp++){                               /* lists all the species with a seed present at given site... */
        6000 ->                     if(S[spp].s_Seed[site]) {
        6000 ->                         SPECIES_GERM[iii]=spp;
                                        
        6000 ->                         if(_NDD){
        6000 ->                             float p=1.0/(1.0+deltaR*T[site].t_NDDfield[spp]);
        6000 ->                             PROB_S[iii]=tot+ p;
        6000 ->                             tot+=p;
                                        }
                                        
        6000 ->                         iii++;
                                    }
                                }
        6000 ->                 if(iii) {                                                   /* ... and then randomly select one of these species */
                                    
        6000 ->                     if(_NDD){
        6000 ->                         double p=genrand2();                                    /* if SEEDTRADEOFF is define, probability of species recruit are proportional to the number of seeds time the seed mass, if NDD is  defines the probablility is also inversly proportional to the species NDDfield term at that site */
        6000 ->                         float itot=1/tot;
        6000 ->                         int s=0;
        6000 ->                         while (p>PROB_S[s]*itot) {s++;}
        6000 ->                         spp=SPECIES_GERM[s];
                                    }
                                    else {
                                    
        6000 ->                     spp = SPECIES_GERM[rand()%iii];
                                        
                                    }
                                    
                                    /* otherwise all species with seeds present are equiprobable */
        6000 ->                     flux = Wmax*exp(-flor(LAI3D[0][site+SBORD])*klight);
        6000 ->                     if(flux>(S[spp].s_LCP)){
                                        /* If enough light, germination, initialization of NPP (LCP is the species light compensation point*/
                                        /* here, light is the sole environmental resources tested as a limiting factor for germination, but we should think about adding nutrients (N,P) and water conditions... */
        6000 ->                         T[site].Birth(S,spp,site);
                                    }
                                }
                            }
                            else{
        6000 ->                 for(spp=1;spp<=numesp;spp++) S[spp].s_Seed[site]=0;
                            }
                        }
                    }
                #endif
                    
        6000 ->     nbdead_n1=nbdead_n10=0;
        6000 ->     if(_BASICTREEFALL){
        6000 ->         nbdead_c1=nbdead_c10=0;
                    }
        6000 ->     for(site=0;site<sites;site++) {
                        /***** Tree evolution: Growth or death *****/
        6000 ->         T[site].Update();
                    }
                    
                #ifdef DCELL
                    // This loop has been moved upwards before the tree birth loop
                #else
        6000 ->     for(spp=1;spp<=numesp;spp++) S[spp].UpdateSeed();
                #endif
                    
        6000 -> }
                
                
                /******************************
                 *** Treefall gap formation ***
                 ******************************/
                
                
        6000 -> void UpdateTreefall(){
                    int site;
                    
        6000 ->     for(site=0;site<sites;site++){
        6000 ->         Thurt[0][site] = Thurt[0][site+2*sites] = 0;
        6000 ->         Thurt[0][site+sites] = 0;
                    }
                    
        6000 ->     nbTreefall1 = 0;
        6000 ->     nbTreefall10=0;
        6000 ->     for(site=0;site<sites;site++)
        6000 ->         if(T[site].t_age) {
        6000 ->             T[site].FallTree();
                        }
                    
                    
                #ifdef MPI
                    /* Treefall field passed to the n.n. procs */
                    MPI_ShareTreefall(Thurt, sites);
                #endif
                    
        6000 ->     for(site=0;site<sites;site++)
                    /* Update of Field hurt */
        6000 ->         if(T[site].t_age) {
        6000 ->             T[site].t_hurt = Thurt[0][site+sites];
                #ifdef MPI
                            if(mpi_rank) T[site].t_hurt = max(T[site].t_hurt,Thurt[1][site]);
                            if(mpi_rank<mpi_size-1) T[site].t_hurt = max(T[site].t_hurt,Thurt[2][site]);
                #endif
                        }
        6000 -> }
                
                
                
                /*###############################################
                 ###############################################
                 #######        Output routines         ########
                 ###############################################
                 ###############################################*/
                
                /*********************************************************
                 *** Calculation of the global averages every timestep ***
                 *********************************************************/
                
        6000 -> void Average(void){
                    
                    int site,spp,i;
        6000 ->     float sum1=0.0,sum10=0.0,sum30=0.0,ba=0.0,npp=0.0,gpp=0.0, ba10=0.0, agb=0.0, rday=0.0, rnight=0.0, rstem=0.0, litterfall=0.0;
                    
        6000 ->     if(!mpi_rank) {
        6000 ->         for(spp=1;spp<=numesp;spp++)
        6000 ->             for(i=0;i<12;i++)
        6000 ->                 S[spp].s_output_field[i]=0;
                        
        6000 ->         float inbcells = 1.0/float(sites*mpi_size);
        6000 ->         float inbhectares = inbcells*NH*NH*10000.0;
        6000 ->         if(_OUTPUT_reduced){
        6000 ->             output[0] << iter << "\t";
        6000 ->             for(spp=1;spp<=numesp;spp++)
        6000 ->                 output[0] << float(S[spp].s_nbind)*inbhectares << "\t";
                        }
                        else{
        6000 ->             for(i=0;i<7;i++) output[i] << iter << "\t";
        6000 ->             for(i=20;i<23;i++) output[i] << iter << "\t";
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << float(S[spp].s_nbind)*inbhectares << "\t";
                        }
        6000 ->         for(site=0;site<sites;site++)T[site].Average();
                        
        6000 ->         cout << iter << "\tNBtrees\t"<<nblivetrees << endl;
                        
        6000 ->         for(spp=1;spp<=numesp;spp++) {
        6000 ->             S[spp].s_output_field[1] *= inbhectares;
                            //species number of trees with dbh>10cm
        6000 ->             S[spp].s_output_field[2] *= inbhectares;
                            //species number of trees with dbh>30cm
        6000 ->             S[spp].s_output_field[3] *= 3.1415*0.25*inbhectares;
                            //species basal area
        6000 ->             S[spp].s_output_field[4] *= inbhectares;
                            //species total NPP (sum of t_NPP) in MgC (per timestep)
        6000 ->             S[spp].s_output_field[5] *= inbhectares;
                            //species total GPP (sum of t_GPP) in MgC (per timestep)
        6000 ->             S[spp].s_output_field[6] *= 3.1415*0.25*inbhectares;
                            //species basal area; with only trees with dbh>10cm
        6000 ->             S[spp].s_output_field[7] *= inbhectares;
                            //species aboveground biomass
        6000 ->             S[spp].s_output_field[8] *= inbhectares;
                            /* species leaf Rday in MgC (per timestep) */
        6000 ->             S[spp].s_output_field[9] *= inbhectares;
                            //species leaf Rnight in MgC (per timestep)
        6000 ->             S[spp].s_output_field[10] *= inbhectares;
                            //species Rstem  in MgC (per timestep)
        6000 ->             S[spp].s_output_field[11] *= inbhectares;
                            //species litterfall  in MgC (per timestep)
        6000 ->             sum1+= float(S[spp].s_nbind)*inbhectares;
        6000 ->             sum10 += S[spp].s_output_field[1];
        6000 ->             sum30 += S[spp].s_output_field[2];
        6000 ->             ba += S[spp].s_output_field[3];
        6000 ->             npp += S[spp].s_output_field[4];
        6000 ->             gpp += S[spp].s_output_field[5];
        6000 ->             ba10 += S[spp].s_output_field[6];
        6000 ->             agb += S[spp].s_output_field[7];
        6000 ->             rday += S[spp].s_output_field[8];
        6000 ->             rnight += S[spp].s_output_field[9];
        6000 ->             rstem += S[spp].s_output_field[10];
        6000 ->             litterfall += S[spp].s_output_field[11];
                            
                            
        6000 ->             if(!_OUTPUT_reduced){
        6000 ->                 for(i=1;i<7;i++) output[i] << S[spp].s_output_field[i] << "\t";
        6000 ->                 output[19] << S[spp].s_output_field[7] << "\t";
        6000 ->                 output[20] << S[spp].s_output_field[8] << "\t";
        6000 ->                 output[21] << S[spp].s_output_field[9] << "\t";
        6000 ->                 output[22] << S[spp].s_output_field[10] << "\t";
        6000 ->                 output[27] << S[spp].s_output_field[11] << "\t";
                            }
                            
        6000 ->             output[27] << S[spp].s_output_field[11] << "\t";
                            
        6000 ->             if (_NDD) {
        6000 ->                 BAtot=ba;
                            }
                            
                        }
        6000 ->         if(_OUTPUT_reduced){
        6000 ->             output[0] << sum1 << "\t";                                                     //total number of trees (dbh>1cm=DBH0)
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << S[spp].s_output_field[1] << "\t";
        6000 ->             output[0] << sum10 << "\t";                                                    //total number of trees (dbh>10cm=DBH0)
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << S[spp].s_output_field[2] << "\t";
        6000 ->             output[0] << sum30 << "\t";                                                    //total number of trees (dbh>30cm=DBH0)
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << S[spp].s_output_field[6] << "\t";
        6000 ->             output[0] << ba10 << "\t";
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << S[spp].s_output_field[4] << "\t";
        6000 ->             output[0] << npp << "\t";
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << S[spp].s_output_field[5] << "\t";
        6000 ->             output[0] << gpp << "\t";
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << S[spp].s_output_field[7] << "\t";
        6000 ->             output[0] << agb << endl;
                            
        6000 ->             output[27] << litterfall << endl;
                            
                        }
                        else{
                            
        6000 ->             output[0] << sum1 << endl;          //total number of trees (dbh>1cm=DBH0)
        6000 ->             output[1] << sum10 << endl;         //total number of trees with dbh>10cm
        6000 ->             output[2] << sum30 << endl;         //total number of trees with dbh>30cm
        6000 ->             output[3] << ba << endl;            //total basal area
        6000 ->             output[4] << npp << endl;           //total NPP in MgC per ha (per time step)
        6000 ->             output[5] << gpp << endl;           //total GPP in MgC par ha (per time step)
        6000 ->             output[6] << ba10 << endl;          //total basal area with only trees with dbh>10cm
        6000 ->             output[19] << agb << endl;          //total above ground biomass
        6000 ->             output[20] << rday << endl;         //total leaf day respiration
        6000 ->             output[21] << rnight << endl;       //total leaf night respiration
        6000 ->             output[22] << rstem << endl;        //total stem respiration
        6000 ->             output[27] << litterfall << endl;   //total litterfall
                            
        6000 ->             float tototest=0.0, tototest2=0.0, flux;
        6000 ->             for(site=0;site<sites;site++) {
        6000 ->                 flux = Wmax*exp(-flor(LAI3D[0][site+SBORD])*klight);
        6000 ->                 tototest += flux;
        6000 ->                 tototest2 += flux*flux;
                            }
        6000 ->             tototest /=float(sites*LH*LH);                              // Average light flux (PPFD) on the ground
        6000 ->             tototest2 /=float(sites*LH*LH);
        6000 ->             if(iter)
        6000 ->                 output[7] << iter<< "\tMean PPFDground\t"<< tototest << "\t" << sqrt(tototest2-tototest*tototest) << "\n";
                            
                            
        6000 ->             if(_BASICTREEFALL) output[8] << iter << "\t" << nbdead_n1*inbhectares << "\t" << nbdead_n10*inbhectares<< "\t" << nbdead_c1*inbhectares << "\t" << nbdead_c10*inbhectares << "\t" << nbTreefall1*inbhectares << "\t" << nbTreefall10*inbhectares << "\t" << endl;
        6000 ->             else output[8] << iter << "\t" << nbdead_n1*inbhectares << "\t" << nbdead_n10*inbhectares<< "\t" << endl;
                        }
                    }
                    
                #ifdef MPI
                    MPI_Reduce(&(S[spp].s_nbind),&sind,1,
                               MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
                    MPI_Reduce(S[spp].s_output_field,S[spp].s_output_field,5,
                               MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                    MPI_Reduce(Mortality,Mortality,4,
                               MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                    MPI_Reduce(&S[spp].s_output_field[6],&S[spp].s_output_field[6],5,
                               MPI_FLOAT,MPI_MAX,0,MPI_COMM_WORLD);
                #endif
                    
        6000 ->     if(!mpi_rank) {
        6000 ->         if(iter == 200){                                        // State at the 200th iteration (for all living trees: dbh, height, crown radius and depth and dbh increment)
        6000 ->             for(site=0;site<sites;site++) {
        6000 ->                 if(T[site].t_dbh>0.0)
        6000 ->                     output[9] << T[site].t_dbh*LH*100 << "\t" << T[site].t_Tree_Height
        6000 ->                     << "\t" << T[site].t_Crown_Radius*LH
        6000 ->                     << "\t" << T[site].t_Crown_Depth*LV
        6000 ->                     << "\t" << T[site].t_ddbh*LH*100 << "\n";
                            }
                        }
                    }
                    
                #ifdef MPI
                    /* This section corresponds to the parallel version of
                     the reporting of the global diagnostic variables. Since much work has been done
                     on routine Average over the past years, this would need a full rewrite
                     !!!!Action 20/01/2016: rework the parallel version of function Average!!!!
                     
                     MPI_Reduce(&(S[spp].s_nbind),&sind,1,
                     MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
                     MPI_Reduce(S[spp].s_output_field,S[spp].s_output_field,5,
                     MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                     MPI_Reduce(Mortality,Mortality,4,
                     MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                     MPI_Reduce(&S[spp].s_output_field[6],&S[spp].s_output_field[6],5,
                     MPI_FLOAT,MPI_MAX,0,MPI_COMM_WORLD);
                     */
                #endif
        6000 ->     cout.flush();
        6000 -> }
                
                
                /*********************************
                 **** Output of Fields Shares ****
                 *********************************/
                
                
        6000 -> void OutputField(){
                    
                    /* output for dbh histogram and mean LAI by height class */
                    
                    int site,haut;
                    
        6000 ->     if((nbout)&&((iter%freqout)==freqout-1)) {
                        // output fields, nbout times during simulation (every freqout iterations)
                        
                        int d;
        6000 ->         for(d=0;d<dbhmaxincm;d++) nbdbh[d]=0;
        6000 ->         for(site=0;site<sites;site++) T[site].histdbh();
                        
        6000 ->         for(haut=0;haut<(HEIGHT+1);haut++){
        6000 ->             layer[haut] = 0;
        6000 ->             for(site=0;site<sites;site++) layer[haut] += LAI3D[haut][site+SBORD];
                        }
                        
                #ifdef MPI
                        MPI_Status status;
                        MPI_Reduce(nbdbh,nbdbh,dbhmaxincm,
                                   MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
                        
                        MPI_Reduce(layer,layer,HEIGHT,
                                   MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                #endif
                        
        6000 ->         if(!mpi_rank) {
                            
                            // output of the dbh histograms (output[31])
        6000 ->             for(d=1;d<dbhmaxincm;d++) output[31] << d << "\t" << nbdbh[d]  << "\n";
        6000 ->             output[31] <<  "\n";
                            
                            // output of the mean LAI per height class (output[32])
        6000 ->             float norm = 1.0/float(sites*LH*LH*mpi_size);
        6000 ->             for(haut=0;haut<(HEIGHT+1);haut++) output[32] << haut*LV << "\t" << layer[haut]*norm << "\n";
        6000 ->             output[32] <<  "\n";
                        }
                    }
        6000 -> }
                
                /*********************************
                 ******** Output routines ********
                 *********************************/
                
                /* This provides a snapshot of the forest whenever called. Per default, this function is used to create the final pattern */
                
           1 -> void OutputSnapshot(fstream& output){
           1 ->     for(int row=0;row<rows;row++)
           1 ->         for(int col=0;col<cols;col++){
           1 ->             output << col << "\t" << row << "\t" << T[col + cols*row].t_age << "\t" << T[col + cols*row].t_dbh << "\t" << T[col + cols*row].t_Tree_Height << "\t" << T[col + cols*row].t_Crown_Radius << "\t" << T[col + cols*row].t_Crown_Depth << "\t" << T[col + cols*row].t_sp_lab << "\t" << T[col + cols*row].t_leafarea << "\t" << T[col + cols*row].t_ddbh << "\t" << T[col + cols*row].t_GPP   << endl;
                        }
           1 -> }
                
                /* This can be used to take snapshots of the forest in more detail and track its development over time. Currently used for 100 years development analysis. */
                
       ##### -> void OutputSnapshotDetail(fstream& output){
       ##### ->     for(int row=0;row<rows;row++)
       ##### ->         for(int col=0;col<cols;col++){
       ##### ->             output << iter << "\t" << col+cols*row << "\t" << col << "\t" << row << "\t" << T[col + cols*row].t_age << "\t" << T[col + cols*row].t_sp_lab << "\t" << T[col + cols*row].t_dbh << "\t" << T[col + cols*row].t_Tree_Height << "\t" << T[col + cols*row].t_Crown_Radius << "\t" << T[col + cols*row].t_Crown_Depth << "\t" << T[col + cols*row].t_leafarea << "\t" << T[col + cols*row].t_dens << "\t" << T[col + cols*row].t_GPP << "\t" << T[col + cols*row].t_hurt << endl;
                        }
       ##### -> }
                
                /* This provides relevant species parameters whenever called */
                
                
       ##### -> void OutputSpeciesParameters(fstream& output){
       ##### ->     for(int sp=1;sp<=numesp;sp++) output << S[sp].s_name << "\t" << S[sp].s_Nmass << "\t" << S[sp].s_Pmass << "\t" << S[sp].s_LMA << "\t" << S[sp].s_Vcmax << "\t" << S[sp].s_Jmax << "\t" << S[sp].s_Rdark << "\t" << S[sp].s_LCP << "\n";
       ##### -> }
                
                
                /* This creates a Canopy Height Model and LAD profile whenever called */
                
                
       ##### -> void OutputFullLAI(fstream& output_CHM, fstream& output_LAD){
       ##### ->     for(int s=0;s<sites;s++){
       ##### ->         int height_canopy=0;
       ##### ->         for(int h=0;h<(HEIGHT);h++){
       ##### ->             if(LAI3D[h][s+SBORD] > 0) height_canopy = max(h,height_canopy);
                        }
       ##### ->         output_CHM << s << "\t" << int(s/cols) << "\t" << int(s%cols) << "\t"  << height_canopy << endl;
                    }
       ##### ->     float isites = 1.0/sites;
       ##### ->     for(int h=0;h<(HEIGHT);h++){
       ##### ->         float LAI3D_avg = 0.0;
       ##### ->         for(int s=0;s<sites;s++){
       ##### ->             if((LAI3D[h][s+SBORD]-LAI3D[h+1][s+SBORD]) < 0) cerr << "Be careful negative PAD!" << endl;
       ##### ->             LAI3D_avg+=LAI3D[h][s+SBORD]-LAI3D[h+1][s+SBORD];
                        }
       ##### ->         output_LAD << h << "\t" << LAI3D_avg * isites << endl;
                    }
       ##### -> }
                
                /*********************************
                 ********** MPI Routines *********
                 *********************************/
                
                
                #ifdef MPI
                
                /* Communication of border fields in the parallel version of the code */
                /* Only if the MPI option has been enabled */
                void MPI_ShareSeed(unsigned char **c, int n) {
                    
                    MPI_Status status;
                    
                    if(p_rank == size-1)
                        MPI_Sendrecv(c[0],n,MPI_UNSIGNED_CHAR,size-2,0,
                                     c[3],n,MPI_UNSIGNED_CHAR,0,0,MPI_COMM_WORLD,&status);
                    if(p_rank == 0)
                        MPI_Sendrecv(c[0],n,MPI_UNSIGNED_CHAR,size-1,0,
                                     c[3],n,MPI_UNSIGNED_CHAR,1,0,MPI_COMM_WORLD,&status);
                    if((p_rank) && (p_rank < size-1))
                        MPI_Sendrecv(c[0],n,MPI_UNSIGNED_CHAR,p_rank-1,0,
                                     c[3],n,MPI_UNSIGNED_CHAR,p_rank+1,0,MPI_COMM_WORLD,&status);
                    
                    if(p_rank == 0)
                        MPI_Sendrecv(c[1],n,MPI_UNSIGNED_CHAR,1,1,
                                     c[2],n,MPI_UNSIGNED_CHAR,size-1,1,MPI_COMM_WORLD,&status);
                    if(p_rank == size-1)
                        MPI_Sendrecv(c[1],n,MPI_UNSIGNED_CHAR,0,1,
                                     c[2],n,MPI_UNSIGNED_CHAR,size-2,1,MPI_COMM_WORLD,&status);
                    if((p_rank) && (p_rank < size-1))
                        MPI_Sendrecv(c[1],n,MPI_UNSIGNED_CHAR,p_rank+1,1,
                                     c[2],n,MPI_UNSIGNED_CHAR,p_rank-1,1,MPI_COMM_WORLD,&status);
                }
                
                void MPI_ShareField(unsigned short **cl, unsigned short ***cp, int n) {
                    
                    MPI_Status status;
                    for(int haut=0;haut<(HEIGHT+1);haut++) {
                        if(p_rank == 0)
                            MPI_Sendrecv(cl[haut],n,MPI_UNSIGNED_SHORT,size-1,haut,
                                         cp[1][haut],n,MPI_UNSIGNED_SHORT,1,haut,
                                         MPI_COMM_WORLD,&status);
                        if(p_rank == size-1)
                            MPI_Sendrecv(cl[haut],n,MPI_UNSIGNED_SHORT,size-2,haut,
                                         cp[1][haut],n,MPI_UNSIGNED_SHORT,0,haut,
                                         MPI_COMM_WORLD,&status);
                        if((p_rank) && (p_rank < size-1))
                            MPI_Sendrecv(cl[haut],n,MPI_UNSIGNED_SHORT,p_rank-1,haut,
                                         cp[1][haut],n,MPI_UNSIGNED_SHORT,p_rank+1,haut,
                                         MPI_COMM_WORLD,&status);
                        
                        if(p_rank == 0)
                            MPI_Sendrecv(cl[haut]+sites,n,MPI_UNSIGNED_SHORT,1,haut+HEIGHT,
                                         cp[0][haut],n,MPI_UNSIGNED_SHORT,size-1,haut+HEIGHT,
                                         MPI_COMM_WORLD,&status);
                        if(p_rank == size-1)
                            MPI_Sendrecv(cl[haut]+sites,n,MPI_UNSIGNED_SHORT,0,haut+HEIGHT,
                                         cp[0][haut],n,MPI_UNSIGNED_SHORT,size-2,haut+HEIGHT,
                                         MPI_COMM_WORLD,&status);
                        if((p_rank) && (p_rank < size-1))
                            MPI_Sendrecv(cl[haut]+sites,n,MPI_UNSIGNED_SHORT,p_rank+1,haut+HEIGHT,
                                         cp[0][haut],n,MPI_UNSIGNED_SHORT,p_rank-1,haut+HEIGHT,
                                         MPI_COMM_WORLD,&status);
                    }
                }
                
                void MPI_ShareTreefall(unsigned short **c, int n) {
                    
                    MPI_Status status;
                    if(p_rank == 0)
                        MPI_Sendrecv(c[0],n,MPI_UNSIGNED_SHORT,size-1,0,
                                     c[2],n,MPI_UNSIGNED_SHORT,1,0,MPI_COMM_WORLD,&status);
                    if(p_rank == size-1)
                        MPI_Sendrecv(c[0],n,MPI_UNSIGNED_SHORT,size-2,0,
                                     c[2],n,MPI_UNSIGNED_SHORT,0,0,MPI_COMM_WORLD,&status);
                    if((p_rank) && (p_rank < size-1))
                        MPI_Sendrecv(c[0],n,MPI_UNSIGNED_SHORT,p_rank-1,0,
                                     c[2],n,MPI_UNSIGNED_SHORT,p_rank+1,0,MPI_COMM_WORLD,&status);
                    
                    if(p_rank == 0)
                        MPI_Sendrecv(c[0]+2*n,n,MPI_UNSIGNED_SHORT,1,1,
                                     c[1],n,MPI_UNSIGNED_SHORT,size-1,1,MPI_COMM_WORLD,&status);
                    if(p_rank == size-1)
                        MPI_Sendrecv(c[0]+2*n,n,MPI_UNSIGNED_SHORT,0,1,
                                     c[1],n,MPI_UNSIGNED_SHORT,size-2,1,MPI_COMM_WORLD,&status);
                    if((p_rank) && (p_rank < size-1))
                        MPI_Sendrecv(c[0]+2*n,n,MPI_UNSIGNED_SHORT,p_rank+1,1,
                                     c[1],n,MPI_UNSIGNED_SHORT,p_rank-1,1,MPI_COMM_WORLD,&status);
                }
                
                #endif
                
                
                
                /******************************************
                 ******************************************
                 *******  Free dynamic memory  ************
                 ******************************************
                 ******************************************/
                
           1 -> void FreeMem () {
                    
           1 ->     delete [] T;
           1 ->     delete [] S;
           1 ->     delete [] nbdbh;
           1 ->     delete [] layer;
           1 ->     delete [] SPECIES_GERM;
           1 ->     if(_SEEDTRADEOFF){
           1 ->         delete [] PROB_S;
                    }
                    
           1 ->     if(_NDD){
           1 ->         delete [] PROB_S;
                    }
                    
                    int h;
           1 ->     for (h=0; h<(HEIGHT+1); h++) {
           1 ->         delete [] LAI3D[h];
                    }
           1 ->     delete [] LAI3D;
                    
                    int i;
           1 ->     for (i=0; i<3; i++) {
           1 ->         delete [] Thurt[i];
                    }
           1 -> }
                
                
                /***********************************
                 ***********************************
                 ***** RANDOM NUMBER GENERATOR *****
                 ***********************************
                 ***********************************/
                
                /* Copyright (C) 1997 Makoto Matsumoto and Takuji Nishimura.       */
                /* When you use this, send an email to: matumoto@math.keio.ac.jp   */
                /* with an appropriate reference to your work.                     */
                
                //#include<stdio.h>
                
                /* Period parameters */
                #define N 624
                #define M 397
                #define MATRIX_A 0x9908b0df   /* constant vector a */
                #define UPPER_MASK 0x80000000 /* most significant w-r bits */
                #define LOWER_MASK 0x7fffffff /* least significant r bits */
                
                /* Tempering parameters */
                #define TEMPERING_MASK_B 0x9d2c5680
                #define TEMPERING_MASK_C 0xefc60000
                #define TEMPERING_SHIFT_U(y)  (y >> 11)
                #define TEMPERING_SHIFT_S(y)  (y << 7)
                #define TEMPERING_SHIFT_T(y)  (y << 15)
                #define TEMPERING_SHIFT_L(y)  (y >> 18)
                
                static unsigned long mt[N]; /* the array for the state vector  */
                static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */
                
                /* initializing the array with a NONZERO seed */
                void sgenrand2(unsigned long seed)
           1 -> {
                    /* setting initial seeds to mt[N] using         */
                    /* the generator Line 25 of Table 1 in          */
                    /* [KNUTH 1981, The Art of Computer Programming */
                    /*    Vol. 2 (2nd Ed.), pp102]                  */
           1 ->     mt[0]= seed & 0xffffffff;
           1 ->     for (mti=1; mti<N; mti++)
           1 ->         mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;
           1 -> }
                
                /* generating reals */
                /* unsigned long */ /* for integer generation */
                double genrand2()
  2340583938 -> {
                    unsigned long y;
                    static unsigned long mag01[2]={0x0, MATRIX_A};
                    /* mag01[x] = x * MATRIX_A  for x=0,1 */
                    
  2340583938 ->     if (mti >= N) { /* generate N words at one time */
                        int kk;
                        
  2340583938 ->         if (mti == N+1)   /* if sgenrand() has not been called, */
  2340583938 ->             sgenrand2(4357); /* a default initial seed is used   */
                        
  2340583938 ->         for (kk=0;kk<N-M;kk++) {
  2340583938 ->             y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
  2340583938 ->             mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
                        }
  2340583938 ->         for (;kk<N-1;kk++) {
  2340583938 ->             y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
  2340583938 ->             mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
                        }
  2340583938 ->         y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
  2340583938 ->         mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];
                        
  2340583938 ->         mti = 0;
                    }
                    
  2340583938 ->     y = mt[mti++];
  2340583938 ->     y ^= TEMPERING_SHIFT_U(y);
  2340583938 ->     y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
  2340583938 ->     y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
  2340583938 ->     y ^= TEMPERING_SHIFT_L(y);
                    
  2340583938 ->     return ( (double)y / (unsigned long)0xffffffff ); /* reals */
                    /* return y; */ /* for integer generation */
  2340583938 -> }
                
                
                /* initializing the array with a NONZERO seed */
                void sgenrand2i(unsigned long seed)
           1 -> {
                    /* setting initial seeds to mt[N] using         */
                    /* the generator Line 25 of Table 1 in          */
                    /* [KNUTH 1981, The Art of Computer Programming */
                    /*    Vol. 2 (2nd Ed.), pp102]                  */
           1 ->     mt[0]= seed & 0xffffffff;
           1 ->     for (mti=1; mti<N; mti++)
           1 ->         mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;
           1 -> }
                
                unsigned long genrand2i()
   504078704 -> {
                    unsigned long y;
                    static unsigned long mag01[2]={0x0, MATRIX_A};
                    /* mag01[x] = x * MATRIX_A  for x=0,1 */
                    
   504078704 ->     if (mti >= N) { /* generate N words at one time */
                        int kk;
                        
   504078704 ->         if (mti == N+1)   /* if sgenrand() has not been called, */
   504078704 ->             sgenrand2i(4357); /* a default initial seed is used   */
                        
   504078704 ->         for (kk=0;kk<N-M;kk++) {
   504078704 ->             y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
   504078704 ->             mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
                        }
   504078704 ->         for (;kk<N-1;kk++) {
   504078704 ->             y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
   504078704 ->             mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
                        }
   504078704 ->         y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
   504078704 ->         mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];
                        
   504078704 ->         mti = 0;
                    }
                    
   504078704 ->     y = mt[mti++];
   504078704 ->     y ^= TEMPERING_SHIFT_U(y);
   504078704 ->     y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
   504078704 ->     y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
   504078704 ->     y ^= TEMPERING_SHIFT_L(y);
                    
   504078704 ->     return y;
   504078704 -> }
                
                
                /***********************************
                 ***********************************
                 ********** TROLL TOOLBOX **********
                 ***********************************
                 ***********************************/
                
                
                /* This section includes variations of TROLL procedures that could be used interchangeably with already existing procedures */
                /* For reasons of readability (syntax highlighting) these sections are kept within a "toolbox" flag instead of commenting them out */
                /* some of them could also be included as boolean options --> to be discussed */
                
                #ifdef toolbox
                
                /***********************************
                 ************ FINE FLUX ************
                 ***********************************/
                
                /* This is an an alternative version of the flux calculations */
                /* main idea: remove extremely productive top layers of trees that block entire photosynthesis in lower layers and smear out the effect in a number of finer layers (nb_layers, here chosen to be five) */
                /* be aware: performance cost */
                
                float Tree::Fluxh(int h) {
                    int count=0,
                    xx,yy,radius_int,
                    nb_layers=5;                                                   // number of layers for fine resolution of flux
                    t_VPD=0;
                    t_T=0;
                    float absorb=0.0,flux = 0.0;
                    float absorb_highres=0.0, flux_highres =0.0, VPD_highres=0.0 , T_highres=0.0,
                    inb_layers=1.0/nb_layers;
                    radius_int = int(t_Crown_Radius);
                    if(radius_int == 0) {
                        count=1;
                        if (h >= HEIGHT) {
                            absorb=0;
                            flux = exp(-absorb*klight);
                        }
                        else {
                            absorb = LAI3D[h][t_site+SBORD];                              //calculate the absorption to which fine layers will be added
                            
                            if(h==0) flux = exp(-absorb*klight);
                            else{
                                // spread out LAI over x differentlayers within voxel (assumption: leaf layer every 1/x m, uniform distribution)
                                absorb_highres = (LAI3D[h-1][t_site+SBORD]-LAI3D[h][t_site+SBORD])*inb_layers;
                                
                                // PROCESS: calculate highly resolved fluxed for every layer within voxel
                                // important: multiplication of absorb with factor i corresponds to gradually increasing optical thickness (LAD)
                                // important: layers have to be added to LAI3D above
                                for(int i=0;i<nb_layers;i++){
                                    flux_highres += exp(-(absorb+i*absorb_highres)*klight);
                                    VPD_highres += 0.25+sqrt(maxf(0.0 , 0.08035714*(7-(absorb+i*absorb_highres))));
                                    // this expressions results from fit of observations of relationships between VPD and height within dense canopy (HOBO data on COPAS tower, Shuttleworth et al 1985; Camargo & Kapos 1995 journal of Tropical Ecology)
                                    T_highres += tmax-0.4285714*(minf(7,(absorb+i*absorb_highres)));
                                    // 0.4285714=3/7, assuming deltaT between the top canopy and dense understorey is constant = 3°C, could be refined.
                                }
                                flux = flux_highres*inb_layers;
                                t_VPD=VPD_highres*inb_layers;
                                t_T=T_highres*inb_layers;
                            }
                            
                        }
                    }
                    else {
                        int row0,col0;
                        row0=t_site/cols;
                        col0=t_site%cols;
                        for(int col=max(0,col0-radius_int);col<min(cols,col0+radius_int+1);col++) {
                            for(int row=max(0,row0-radius_int);row<min(rows,row0+radius_int+1);row++) {                     //loop over the tree crown
                                xx=col0-col;
                                yy=row0-row;
                                if(xx*xx+yy*yy <= radius_int*radius_int) {                                                  //is the voxel within crown?
                                    flux_highres = 0.0;
                                    VPD_highres = 0.0;
                                    T_highres = 0.0;
                                    count++;
                                    if (h >= HEIGHT) {
                                        absorb=0;
                                        flux += exp(-absorb*klight);
                                        t_VPD+=0.25+sqrt(maxf(0.0 , 0.08035714*(7-absorb)));
                                        t_T+=tmax-0.4285714*(minf(7,absorb));
                                    }
                                    else {
                                        absorb = LAI3D[h][col+cols*row+SBORD];                              //calculate the absorption that will need to be added to fine layers
                                        
                                        if(h==0) flux += exp(-absorb*klight);
                                        else{
                                            // spread out LAI over x differentlayers within voxel (assumption: leaf layer every 1/x m, uniform distribution)
                                            absorb_highres = (LAI3D[h-1][col+cols*row+SBORD]-LAI3D[h][col+cols*row+SBORD])*inb_layers;
                                            
                                            // PROCESS: calculate highly resolved flux for every layer within voxel
                                            // important: multiplication of absorb with factor i corresponds to gradually increasing optical thickness (LAD)
                                            // important: layers have to be added to LAI3D above (absorb)
                                            for(int i=0;i<nb_layers;i++){
                                                flux_highres += exp(-(absorb+i*absorb_highres)*klight);
                                                VPD_highres += 0.25+sqrt(maxf(0.0 , 0.08035714*(7-(absorb+i*absorb_highres))));
                                                T_highres += tmax-0.4285714*(minf(7,(absorb+i*absorb_highres)));
                                            }
                                            flux_highres = flux_highres*inb_layers;
                                            VPD_highres = VPD_highres*inb_layers;
                                            T_highres = T_highres*inb_layers;
                                            t_VPD+=VPD_highres;
                                            t_T+=T_highres;
                                            flux += flux_highres;
                                        }
                                        
                                    }
                                }
                            }
                        }
                    }
                    flux*=Wmax/float(count);
                    t_VPD*=VPDmax/float(count);
                    t_T*=1/float(count);
                    
                    return flux;
                }
                
                #endif
                


Top 10 Lines:

     Line      Count

      338 11775954108
      334 5907644284
      342 4724642744
     3235 2340583938
      753 1576443286
      784 1500709556
     1069 1500709556
     1019  960000000
     1357  960000000
     1501  960000000

Execution Summary:

     1197   Executable lines in this file
     1197   Lines executed
   100.00   Percent of the file executed

37299369594   Total number of line executions
31160709.77   Average executions per line
