/* dorg2r.f -- translated by f2c (version of 4 June 1993  1:43:59).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;

/*<       SUBROUTINE DORG2R( M, N, K, A, LDA, TAU, WORK, INFO ) >*/
/* Subroutine */ int dorg2r_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    doublereal d__1;

    /* Local variables */
    static integer i, j, l;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *), dlarf_(char *, integer *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *, doublereal *, 
	    ftnlen), xerbla_(char *, integer *, ftnlen);


/*  -- LAPACK routine (version 2.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     February 29, 1992 */

/*     .. Scalar Arguments .. */
/*<       INTEGER            INFO, K, LDA, M, N >*/
/*     .. */
/*     .. Array Arguments .. */
/*<       DOUBLE PRECISION   A( LDA, * ), TAU( * ), WORK( * ) >*/
/*     .. */

/*  Purpose */
/*  ======= */

/*  DORG2R generates an m by n real matrix Q with orthonormal columns, */
/*  which is defined as the first n columns of a product of k elementary 
*/
/*  reflectors of order m */

/*        Q  =  H(1) H(2) . . . H(k) */

/*  as returned by DGEQRF. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix Q. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix Q. M >= N >= 0. */

/*  K       (input) INTEGER */
/*          The number of elementary reflectors whose product defines the 
*/
/*          matrix Q. N >= K >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the i-th column must contain the vector which */
/*          defines the elementary reflector H(i), for i = 1,2,...,k, as 
*/
/*          returned by DGEQRF in the first k columns of its array */
/*          argument A. */
/*          On exit, the m-by-n matrix Q. */

/*  LDA     (input) INTEGER */
/*          The first dimension of the array A. LDA >= max(1,M). */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i), as returned by DGEQRF. */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (N) */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -i, the i-th argument has an illegal value */

/*  ===================================================================== 
*/

/*     .. Parameters .. */
/*<       DOUBLE PRECISION   ONE, ZERO >*/
/*<       PARAMETER          ( ONE = 1.0D+0, ZERO = 0.0D+0 ) >*/
/*     .. */
/*     .. Local Scalars .. */
/*<       INTEGER            I, J, L >*/
/*     .. */
/*     .. External Subroutines .. */
/*<       EXTERNAL           DLARF, DSCAL, XERBLA >*/
/*     .. */
/*     .. Intrinsic Functions .. */
/*<       INTRINSIC          MAX >*/
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

/*<       INFO = 0 >*/
    /* Parameter adjustments */
    --work;
    --tau;
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */
    *info = 0;
/*<       IF( M.LT.0 ) THEN >*/
    if (*m < 0) {
/*<          INFO = -1 >*/
	*info = -1;
/*<       ELSE IF( N.LT.0 .OR. N.GT.M ) THEN >*/
    } else if (*n < 0 || *n > *m) {
/*<          INFO = -2 >*/
	*info = -2;
/*<       ELSE IF( K.LT.0 .OR. K.GT.N ) THEN >*/
    } else if (*k < 0 || *k > *n) {
/*<          INFO = -3 >*/
	*info = -3;
/*<       ELSE IF( LDA.LT.MAX( 1, M ) ) THEN >*/
    } else if (*lda < max(1,*m)) {
/*<          INFO = -5 >*/
	*info = -5;
/*<       END IF >*/
    }
/*<       IF( INFO.NE.0 ) THEN >*/
    if (*info != 0) {
/*<          CALL XERBLA( 'DORG2R', -INFO ) >*/
	i__1 = -(*info);
	xerbla_("DORG2R", &i__1, 6L);
/*<          RETURN >*/
	return 0;
/*<       END IF >*/
    }

/*     Quick return if possible */

/*<    >*/
    if (*n <= 0) {
	return 0;
    }

/*     Initialise columns k+1:n to columns of the unit matrix */

/*<       DO 20 J = K + 1, N >*/
    i__1 = *n;
    for (j = *k + 1; j <= i__1; ++j) {
/*<          DO 10 L = 1, M >*/
	i__2 = *m;
	for (l = 1; l <= i__2; ++l) {
/*<             A( L, J ) = ZERO >*/
	    a[l + j * a_dim1] = 0.;
/*<    10    CONTINUE >*/
/* L10: */
	}
/*<          A( J, J ) = ONE >*/
	a[j + j * a_dim1] = 1.;
/*<    20 CONTINUE >*/
/* L20: */
    }

/*<       DO 40 I = K, 1, -1 >*/
    for (i = *k; i >= 1; --i) {

/*        Apply H(i) to A(i:m,i:n) from the left */

/*<          IF( I.LT.N ) THEN >*/
	if (i < *n) {
/*<             A( I, I ) = ONE >*/
	    a[i + i * a_dim1] = 1.;
/*<    >*/
	    i__1 = *m - i + 1;
	    i__2 = *n - i;
	    dlarf_("Left", &i__1, &i__2, &a[i + i * a_dim1], &c__1, &tau[i], &
		    a[i + (i + 1) * a_dim1], lda, &work[1], 4L);
/*<          END IF >*/
	}
/*<    >*/
	if (i < *m) {
	    i__1 = *m - i;
	    d__1 = -tau[i];
	    dscal_(&i__1, &d__1, &a[i + 1 + i * a_dim1], &c__1);
	}
/*<          A( I, I ) = ONE - TAU( I ) >*/
	a[i + i * a_dim1] = 1. - tau[i];

/*        Set A(1:i-1,i) to zero */

/*<          DO 30 L = 1, I - 1 >*/
	i__1 = i - 1;
	for (l = 1; l <= i__1; ++l) {
/*<             A( L, I ) = ZERO >*/
	    a[l + i * a_dim1] = 0.;
/*<    30    CONTINUE >*/
/* L30: */
	}
/*<    40 CONTINUE >*/
/* L40: */
    }
/*<       RETURN >*/
    return 0;

/*     End of DORG2R */

/*<       END >*/
} /* dorg2r_ */

