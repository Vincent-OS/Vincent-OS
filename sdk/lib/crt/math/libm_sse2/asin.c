
/*******************************************************************************
MIT License
-----------

Copyright (c) 2002-2019 Advanced Micro Devices, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this Software and associated documentaon files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*******************************************************************************/

#include "libm.h"
#include "libm_util.h"

#define USE_VAL_WITH_FLAGS
#define USE_NAN_WITH_FLAGS
#define USE_HANDLE_ERROR
#include "libm_inlines.h"
#undef USE_NAN_WITH_FLAGS
#undef USE_VAL_WITH_FLAGS
#undef USE_HANDLE_ERROR

#include "libm_errno.h"

#ifdef _MSC_VER
#pragma function(asin)
#endif

double FN_PROTOTYPE(asin)(double x)
{
  /* Computes arcsin(x).
     The argument is first reduced by noting that arcsin(x)
     is invalid for abs(x) > 1 and arcsin(-x) = -arcsin(x).
     For denormal and small arguments arcsin(x) = x to machine
     accuracy. Remaining argument ranges are handled as follows.
     For abs(x) <= 0.5 use
     arcsin(x) = x + x^3*R(x^2)
     where R(x^2) is a rational minimax approximation to
     (arcsin(x) - x)/x^3.
     For abs(x) > 0.5 exploit the identity:
      arcsin(x) = pi/2 - 2*arcsin(sqrt(1-x)/2)
     together with the above rational approximation, and
     reconstruct the terms carefully.
    */

  /* Some constants and split constants. */

  static const double
    piby2_tail  = 6.1232339957367660e-17, /* 0x3c91a62633145c07 */
    hpiby2_head = 7.8539816339744831e-01, /* 0x3fe921fb54442d18 */
    piby2       = 1.5707963267948965e+00; /* 0x3ff921fb54442d18 */
  double u, v, y, s=0.0, r;
  int xexp, xnan, transform=0;

  unsigned long long ux, aux, xneg;
  GET_BITS_DP64(x, ux);
  aux = ux & ~SIGNBIT_DP64;
  xneg = (ux & SIGNBIT_DP64);
  xnan = (aux > PINFBITPATT_DP64);
  xexp = (int)((ux & EXPBITS_DP64) >> EXPSHIFTBITS_DP64) - EXPBIAS_DP64;

  /* Special cases */

  if (xnan)
    {
      return _handle_error("asin", OP_ASIN, ux|0x0008000000000000, _DOMAIN,
                          0, EDOM, x, 0.0, 1);
    }
  else if (xexp < -28)
    { /* y small enough that arcsin(x) = x */
      return val_with_flags(x, AMD_F_INEXACT);
    }
  else if (xexp >= 0)
    { /* abs(x) >= 1.0 */
      if (x == 1.0)
        return val_with_flags(piby2, AMD_F_INEXACT);
      else if (x == -1.0)
        return val_with_flags(-piby2, AMD_F_INEXACT);
      else
        return _handle_error("asin", OP_ASIN, INDEFBITPATT_DP64, _DOMAIN,
                            AMD_F_INVALID, EDOM, x, 0.0, 1);
    }

  if (xneg) y = -x;
  else y = x;

  transform = (xexp >= -1); /* abs(x) >= 0.5 */

  if (transform)
    { /* Transform y into the range [0,0.5) */
      r = 0.5*(1.0 - y);
      /* VC++ intrinsic call */
      _mm_store_sd(&s, _mm_sqrt_sd(_mm_setzero_pd(), _mm_load_sd(&r)));
      y = s;
    }
  else
    r = y*y;

  /* Use a rational approximation for [0.0, 0.5] */

  u = r*(0.227485835556935010735943483075 +
         (-0.445017216867635649900123110649 +
          (0.275558175256937652532686256258 +
           (-0.0549989809235685841612020091328 +
            (0.00109242697235074662306043804220 +
             0.0000482901920344786991880522822991*r)*r)*r)*r)*r)/
    (1.36491501334161032038194214209 +
     (-3.28431505720958658909889444194 +
      (2.76568859157270989520376345954 +
       (-0.943639137032492685763471240072 +
        0.105869422087204370341222318533*r)*r)*r)*r);

  if (transform)
    { /* Reconstruct asin carefully in transformed region */
        {
          double c, s1, p, q;
          unsigned long long us;
          GET_BITS_DP64(s, us);
          PUT_BITS_DP64(0xffffffff00000000 & us, s1);
          c = (r-s1*s1)/(s+s1);
          p = 2.0*s*u - (piby2_tail-2.0*c);
          q = hpiby2_head - 2.0*s1;
          v = hpiby2_head - (p-q);
        }
    }
  else
    {
      /* Use a temporary variable to prevent VC++ rearranging
            y + y*u
         into
            y * (1 + u)
         and getting an incorrectly rounded result */
      double tmp;
      tmp = y * u;
      v = y + tmp;
    }

  if (xneg) return -v;
  else return v;
}
