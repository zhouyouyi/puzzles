#ifndef FPMATH_H
#define FPMATH_H

#include <cmath>
#include <functional>

/// define simple comparison operators for doubles
const double FP_EPSILON = 0.000001; // 1.0e-6

inline bool EQ( double d1, double d2, double ep = FP_EPSILON )
{   return (isinf(d1) ? (d1==d2) : (fabs( d1 - d2 ) < ep)); }

inline bool GE( double d1, double d2, double ep = FP_EPSILON )
{   return d1 >= ( d2 - ep ); }

inline bool GT( double d1, double d2, double ep = FP_EPSILON )
{   return d1 > ( d2 + ep ); }

inline bool NE( double d1, double d2, double ep = FP_EPSILON )
{   return !EQ( d1, d2, ep ); }

inline bool LE( double d1, double d2, double ep = FP_EPSILON )
{   return !GT( d1, d2, ep ); }

inline bool LT( double d1, double d2, double ep = FP_EPSILON )
{   return !GE( d1, d2, ep ); }

// fuzzy compare to 0
inline bool EQZ( double d, double ep = FP_EPSILON )
{   return fabs( d ) < ep; }

inline bool GEZ( double d, double ep = FP_EPSILON )
{   return d >= -ep; }

inline bool GTZ( double d, double ep = FP_EPSILON )
{   return d > ep; }

inline bool NEZ( double d, double ep = FP_EPSILON )
{   return !EQZ( d, ep ); }

inline bool LEZ( double d, double ep = FP_EPSILON )
{   return !GTZ( d, ep ); }

inline bool LTZ( double d, double ep = FP_EPSILON )
{   return !GEZ( d, ep ); }

struct FPLess : std::binary_function<double, double, bool>
{
    bool operator () (double a, double b) const { return LT(a, b); }
};

struct FPGreater : std::binary_function<double, double, bool>
{
    bool operator () (double a, double b) const { return GT(a, b); }
};

#endif
