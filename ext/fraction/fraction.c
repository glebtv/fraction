/*
** find rational approximation to given real number
** David Eppstein / UC Irvine / 8 Aug 1993
**
** With corrections from Arno Formella, May 2008
**
** Made into a ruby module by Christopher Lord, Nov 2009
**
** usage: require 'fraction'
**
**        n,d,err = 0.33.fraction
**
** based on the theory of continued fractions
** if x = a1 + 1/(a2 + 1/(a3 + 1/(a4 + ...)))
** then best approximation is found by truncating this series
** (with some adjustments in the last term).
**
** Note the fraction can be recovered as the first column of the matrix
**  ( a1 1 ) ( a2 1 ) ( a3 1 ) ...
**  ( 1  0 ) ( 1  0 ) ( 1  0 )
** Instead of keeping the sequence of continued fraction terms,
** we just keep the last partial product of these matrices.
*/

#include "ruby.h"
#include <stdio.h>

static VALUE rb_cFraction;

void core_fraction(double val, long maxden, long * n, long * d, double * e)
{
   int ai;
   long sign = 1;
   long m11 = 1, m22 = 1;
   long m12 = 0, m21 = 0;
   if (val < 0.0) {
      // work in positive space, it seems we can get confused by negatives
      sign = -1;
      val *= -1.0;
   }
   double x = val;
   long count = 0;

   // loop finding terms until denom gets too big
   while (m21 *  ( ai = (long)x ) + m22 <= maxden) {
      if (++count > 50000000) break; // break after 'too many' iterations
      long t = m11 * ai + m12;
      m12 = m11;
      m11 = t;
      t = m21 * ai + m22;
      m22 = m21;
      m21 = t;
      if(x==(double)ai) break;
      x = 1/(x - (double) ai);
      if(x>(double)0x7FFFFFFF) break;
   }
   *n = m11 * sign;
   *d = m21;
   *e = val - ((double)m11 / (double)m21);
}

VALUE fraction_create_fraction_from(int argc, VALUE * argv, VALUE self)
{
   VALUE fraction = rb_class_new_instance(0, NULL, rb_cFraction);

   VALUE res = rb_ary_new2(3);
   VALUE maxdenr;
   long maxden = 10; // the default
   rb_scan_args(argc, argv, "01", &maxdenr);
   if (!NIL_P(maxdenr))
     maxden = NUM2INT(maxdenr);
   double x = NUM2DBL(self);
   long n, d;
   double e;
   core_fraction(x, maxden, &n, &d, &e);

   VALUE numer1 = INT2NUM(n);
   VALUE denom1 = INT2NUM(d);
   VALUE err1 = rb_float_new(e);

   rb_iv_set(fraction, "@numerator", numer1);
   rb_iv_set(fraction, "@denominator", denom1);
   rb_iv_set(fraction, "@result", err1);

   return fraction;
}

void Init_fraction() {

   rb_cFraction = rb_define_class("Fraction", rb_cObject);

   rb_define_method(rb_cNumeric, "to_fraction", fraction_create_fraction_from, -1);
   rb_define_method(rb_cFloat,   "to_fraction", fraction_create_fraction_from, -1);
}

