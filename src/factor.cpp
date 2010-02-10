/*  This file is part of libDAI - http://www.libdai.org/
 *
 *  libDAI is licensed under the terms of the GNU General Public License version
 *  2, or (at your option) any later version. libDAI is distributed without any
 *  warranty. See the file COPYING for more details.
 *
 *  Copyright (C) 2006-2010  Joris Mooij  [joris dot mooij at libdai dot org]
 *  Copyright (C) 2006-2007  Radboud University Nijmegen, The Netherlands
 */


#include <dai/factor.h>


namespace dai {


using namespace std;


Factor BinaryFactor( const Var &n, Real h ) {
    DAI_ASSERT( n.states() == 2 );
    Real buf[2];
    buf[0] = std::exp(-h);
    buf[1] = std::exp(h);
    return Factor(n, &buf[0]);
}


Factor BinaryFactor( const Var &n1, const Var &n2, Real J ) {
    DAI_ASSERT( n1.states() == 2 );
    DAI_ASSERT( n2.states() == 2 );
    DAI_ASSERT( n1 != n2 );
    Real buf[4];
    buf[0] = (buf[3] = std::exp(J));
    buf[1] = (buf[2] = std::exp(-J));
    return Factor( VarSet(n1, n2), &buf[0] );
}


Factor RandomFactor( const VarSet &ns, Real beta ) {
    Factor fac( ns );
    for( size_t t = 0; t < fac.states(); t++ )
        fac[t] = std::exp(rnd_stdnormal() * beta);
    return fac;
}


Factor PottsFactor( const Var &n1, const Var &n2, Real J ) {
    Factor fac( VarSet( n1, n2 ), 1.0 );
    DAI_ASSERT( n1.states() == n2.states() );
    for( size_t s = 0; s < n1.states(); s++ )
        fac[ s * (n1.states() + 1) ] = std::exp(J);
    return fac;
}


Factor DeltaFactor( const Var &v, size_t state ) {
    Factor fac( v, 0.0 );
    DAI_ASSERT( state < v.states() );
    fac[state] = 1.0;
    return fac;
}


} // end of namespace dai
