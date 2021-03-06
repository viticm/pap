// Copyright (c) 1997-2001  ETH Zurich (Switzerland).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.2-branch/QP_solver/include/CGAL/QP_solver/QP__filtered_base.C $
// $Id: QP__filtered_base.C 28526 2006-02-15 11:54:47Z fischerk $
// 
//
// Author(s)     : Sven Schoenherr <sven@inf.fu-berlin.de>
//                 Bernd Gaertner <gaertner@inf.ethz.ch>
//                 Franz Wessendorp <fransw@inf.ethz.ch>
//                 Kaspar Fischer <fischerk@inf.ethz.ch>

CGAL_BEGIN_NAMESPACE

// =============================
// class implementation (cont'd)
// =============================

// set-up
template < class Rep_, class NT_, class ET2NT_ >
void  QP__filtered_base<Rep_,NT_,ET2NT_>::
set( )
{
    // reserve memory for NT versions of current solution
    //int  l = std::min( this->solver().number_of_variables(),
    //		       this->solver().number_of_constraints());
    int l = this->solver().get_l();
    lambda_NT.resize( l, nt0);
    set( l, Is_linear());
}

// initialization
template < class Rep_, class NT_, class ET2NT_ >
void  QP__filtered_base<Rep_,NT_,ET2NT_>::
init( )
{
    // get properties of quadratic program
    int  n = this->solver().number_of_variables();
    int  m = this->solver().number_of_constraints();
    int  s = this->solver().number_of_slack_variables();

    // clear row and column maxima, if necessary
    if ( ! row_max_A.empty()) row_max_A.clear();
    if ( ! handled_A.empty()) handled_A.clear();
    if ( ! col_max  .empty()) col_max  .clear();
    init( Is_linear());

    // initialize row and column maxima
    // assuming nonneg coefficients
    row_max_c = nt0;
    C_auxiliary_iterator v_it;
    for ( v_it = this->solver().c_auxiliary_value_iterator_begin();
              v_it != this->solver().c_auxiliary_value_iterator_end(); ++v_it) {
        if (*v_it > row_max_c) row_max_c = (*v_it);
    }
        
    handled_A.insert( handled_A.end(), m, false);
    row_max_A.insert( row_max_A.end(), m, nt0);

    col_max.insert( col_max.end(), n,   nt0);               // original
    col_max.insert( col_max.end(), s, nt1);               // slack
    							  //auxiliary
    for ( v_it = this->solver().c_auxiliary_value_iterator_begin();
          v_it != this->solver().c_auxiliary_value_iterator_end(); ++v_it) {
	      col_max.insert( col_max.end(), (*v_it));
    }
}

// operations
template < class Rep_, class NT_, class ET2NT_ >
void  QP__filtered_base<Rep_,NT_,ET2NT_>::
init_NT( )
{
    // ToDo: scale 'x_B_O', 'lambda', and 'd' if necessary

    // get inexact version of 'lambda'
    std::transform( this->solver().lambda_numerator_begin(),
		    this->solver().lambda_numerator_end(),
		    lambda_NT.begin(), et2nt_obj);

    // get inexact version of 'x_B_O'
    init_NT( Is_linear());

    // get inexact version of 'd'
    d_NT = et2nt_obj( this->solver().variables_common_denominator());
}

template < class Rep_, class NT_, class ET2NT_ >
void  QP__filtered_base<Rep_,NT_,ET2NT_>::
update_maxima( )
{
    // get properties of quadratic program
    int  n = this->solver().number_of_variables();
    int  c = this->solver().number_of_basic_constraints();
    int  b = this->solver().number_of_basic_original_variables();

    // initialize error bounds
    bound1    = d_NT * row_max_c;
    bound2_wq = d_NT;

    // update row and column maxima of 'A'
    A_iterator  a_it = this->solver().a_begin();
    R_iterator  r_it = this->solver().row_type_begin();
    int         row, col;
    NT          row_max, z;

    Basic_constraint_index_iterator  it;
    Values_NT_iterator v_it = lambda_NT.begin();
    for ( it =  this->solver().basic_constraints_index_begin();
	  it != this->solver().basic_constraints_index_end(); ++it, ++v_it) {
	row = *it;

	// row not handled yet?
	if ( ! handled_A[ row]) {

	    // slack variable (or artificial in phase I) involved?
	    row_max = (    ( r_it[ row] != Rep::EQUAL)
			|| ( this->solver().phase() == 1) ? nt1 : nt0);

	    // scan row and update maxima
	    for ( col = 0; col < n; ++col) {
		z = CGAL::abs( a_it[ col][ row]);
		if ( z > row_max      ) row_max       = z;
		if ( z > col_max[ col]) col_max[ col] = z;
	    }
	    row_max_A[ row] = row_max;
	    handled_A[ row] = true;
	}
	// update bounds
	z = CGAL::abs( *v_it);
	if ( z > bound2_wq) bound2_wq = z;
	z *= row_max_A[ row];
	if ( z > bound1) bound1 = z;
    }

    // update row and column maxima of 'D', if necessary
    if (this->solver().phase() == 1) {
    	update_maxima( Tag_true());
    } else {
        update_maxima( Is_linear());
    }

    // finalize error bounds
    // ToDo: use std::numeric_limits for 'machine epsilon'
    NT  q = std::ldexp( 1.015625 * ( c+b+1) * ( c+b+2), -53);
    bound1    *= q;
    bound2_wq *= q;

    CGAL_qpe_debug {
	this->vout() << std::endl
	       << "first bound for certification: " << bound1 << std::endl;
    }
}

template < class Rep_, class NT_, class ET2NT_ >                // QP case
void  QP__filtered_base<Rep_,NT_,ET2NT_>::
update_maxima( Tag_false)
{
    int  n = this->solver().number_of_variables();

    // update row and column maxima of 'D'
    D_row_iterator  d_row_it;
    int             row, col;
    NT              row_max, z;

    Basic_variable_index_iterator  it;
    Values_NT_iterator v_it = x_B_O_NT.begin();
    for ( it =  this->solver().basic_original_variables_index_begin();
	  it != this->solver().basic_original_variables_index_end();
	  ++it, ++v_it) {
	row = *it;

	// row not handled yet?
	if ( ! handled_D[ row]) {
	    d_row_it = this->solver().d_begin()[ row];

	    // scan row and update maxima
	    row_max = nt0;
	    for ( col = 0; col < n; ++col, ++d_row_it) {
		z = CGAL::abs( *d_row_it);
		if ( z > row_max      ) row_max       = z;
		if ( z > col_max[ col]) col_max[ col] = z;
	    }
	    row_max_D[ row] = row_max;
	    handled_D[ row] = true;
	}
	// update bounds
	z = CGAL::abs( (*v_it));
	if ( z > bound2_wq) bound2_wq = z;
	z *= row_max_D[ row];
	if ( z > bound1) bound1 = z;
    }
}

template < class Rep_, class NT_, class ET2NT_ >                // LP case
void  QP__filtered_base<Rep_,NT_,ET2NT_>::
update_maxima( Tag_true)
{

    // update basic original variables maxima
    NT              z;

    Values_NT_iterator v_it;
    for ( v_it = x_B_O_NT.begin(); v_it != x_B_O_NT.end(); ++v_it) {

	// update bounds
	z = CGAL::abs( (*v_it));
	if ( z > bound2_wq) bound2_wq = z;
    }
}

template < class Rep_, class NT_, class ET2NT_ >
bool  QP__filtered_base<Rep_,NT_,ET2NT_>::
certify_mu_j_NT( int j) const
{
    // compute 'mu_j' with inexact arithmetic again
    NT  mu = mu_j_NT( j);

    CGAL_qpe_debug {
	this->vout() << "mu_" << j << " [NT]: " << mu;
    }

    // check against first bound
    if ( mu >= bound1) {
	CGAL_qpe_debug {
	    this->vout() << "  ok [1]" << std::endl;
	}
	return true;
    }

    // compute and check against second bound
    NT  bound2 = bound2_wq * col_max[ j];
    if ( mu >= bound2) {
	CGAL_qpe_debug {
	    this->vout() << "  ok [2: " << bound2 << "]" << std::endl;
	}
	return true;
    }

    // compute and check exact 'mu_j'
    ET  mu_et = this->mu_j( j);

    CGAL_qpe_debug {
	this->vout() << "  " << ( mu_et >= this->et0 ? "ok" : "MISSED")
	       << " [exact: " << mu_et << "]" << std::endl;
    }
    return ( mu_et >= this->et0);
}

// transition
template < class Rep_, class NT_, class ET2NT_ >
void  QP__filtered_base<Rep_,NT_,ET2NT_>::
transition( )
{
    // get properties of quadratic program
    int  n = this->solver().number_of_variables();

    // update row and column maxima with original objective vector 'c'
    C_iterator  c_it = this->solver().c_begin();
    NT  z;
    row_max_c = nt0;
    for ( int i = 0; i < n; ++i, ++c_it) {
	z = CGAL::abs( *c_it);
	if ( z > row_max_c  ) row_max_c   = z;
	if ( z > col_max[ i]) col_max[ i] = z;
    }

    // initialize row maxima of 'D', if necessary
    transition( n, Is_linear());
}

CGAL_END_NAMESPACE

// ===== EOF ==================================================================
