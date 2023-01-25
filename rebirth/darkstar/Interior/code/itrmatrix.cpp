//----------------------------------------------------------------------------

//	Matrix Inversion
//	by Richard Carling
//	from "Graphics Gems", Academic Press, 1990

// Should move this into the math library.

//----------------------------------------------------------------------------

#include <ml.h>
#include <math.h>

#define SMALL_NUMBER	1.e-8


//----------------------------------------------------------------------------

struct Matrix4
{
	double element[4][4];
};

bool inverse( Matrix4 *in, Matrix4 *out );


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

bool itrInverse(TMat3F& tmat)
{
	Matrix4 mat,imat;
	mat.element[0][0] = tmat.m[0][0];
	mat.element[0][1] = tmat.m[0][1];
	mat.element[0][2] = tmat.m[0][2];
	mat.element[0][3] = 0;
	mat.element[1][0] = tmat.m[1][0];
	mat.element[1][1] = tmat.m[1][1];
	mat.element[1][2] = tmat.m[1][2];
	mat.element[1][3] = 0;
	mat.element[2][0] = tmat.m[2][0];
	mat.element[2][1] = tmat.m[2][1];
	mat.element[2][2] = tmat.m[2][2];
	mat.element[2][3] = 0;
	mat.element[3][0] = tmat.p.x;
	mat.element[3][1] = tmat.p.y;
	mat.element[3][2] = tmat.p.z;
	mat.element[3][3] = 1.0;

	if (!inverse(&mat,&imat))
		return false;

	tmat.m[0][0] = imat.element[0][0];
	tmat.m[0][1] = imat.element[0][1];
	tmat.m[0][2] = imat.element[0][2];
	//mat.element[0][3];
	tmat.m[1][0] = imat.element[1][0];
	tmat.m[1][1] = imat.element[1][1];
	tmat.m[1][2] = imat.element[1][2];
	//mat.element[1][3];
	tmat.m[2][0] = imat.element[2][0];
	tmat.m[2][1] = imat.element[2][1];
	tmat.m[2][2] = imat.element[2][2];
	//mat.element[2][3];
	tmat.p.x = imat.element[3][0];
	tmat.p.y = imat.element[3][1];
	tmat.p.z = imat.element[3][2];
	//mat.element[3][3];
	return true;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


/*
 * double = det2x2( double a, double b, double c, double d )
 * 
 * calculate the determinant of a 2x2 matrix.
 */

double det2x2( double a, double b, double c, double d)
{
    double ans;
    ans = a * d - b * c;
    return ans;
}

/*
 * double = det3x3(  a1, a2, a3, b1, b2, b3, c1, c2, c3 )
 * 
 * calculate the determinant of a 3x3 matrix
 * in the form
 *
 *     | a1,  b1,  c1 |
 *     | a2,  b2,  c2 |
 *     | a3,  b3,  c3 |
 */

double det3x3( double a1, double a2, double a3, double b1, 
	double b2, double b3, double c1, double c2, double c3 )
{
    double ans;

    ans = a1 * det2x2( b2, b3, c2, c3 )
        - b1 * det2x2( a2, a3, c2, c3 )
        + c1 * det2x2( a2, a3, b2, b3 );
    return ans;
}

/* 
 *   adjoint( original_matrix, inverse_matrix )
 * 
 *     calculate the adjoint of a 4x4 matrix
 *
 *      Let  a   denote the minor determinant of matrix A obtained by
 *           ij
 *
 *      deleting the ith row and jth column from A.
 *
 *                    i+j
 *     Let  b   = (-1)    a
 *          ij            ji
 *
 *    The matrix B = (b  ) is the adjoint of A
 *                     ij
 */

void adjoint( Matrix4 *in, Matrix4 *out )
{
    double a1, a2, a3, a4, b1, b2, b3, b4;
    double c1, c2, c3, c4, d1, d2, d3, d4;

    /* assign to individual variable names to aid  */
    /* selecting correct values  */

	a1 = in->element[0][0]; b1 = in->element[0][1]; 
	c1 = in->element[0][2]; d1 = in->element[0][3];

	a2 = in->element[1][0]; b2 = in->element[1][1]; 
	c2 = in->element[1][2]; d2 = in->element[1][3];

	a3 = in->element[2][0]; b3 = in->element[2][1];
	c3 = in->element[2][2]; d3 = in->element[2][3];

	a4 = in->element[3][0]; b4 = in->element[3][1]; 
	c4 = in->element[3][2]; d4 = in->element[3][3];


    /* row column labeling reversed since we transpose rows & columns */

    out->element[0][0]  =   det3x3( b2, b3, b4, c2, c3, c4, d2, d3, d4);
    out->element[1][0]  = - det3x3( a2, a3, a4, c2, c3, c4, d2, d3, d4);
    out->element[2][0]  =   det3x3( a2, a3, a4, b2, b3, b4, d2, d3, d4);
    out->element[3][0]  = - det3x3( a2, a3, a4, b2, b3, b4, c2, c3, c4);
        
    out->element[0][1]  = - det3x3( b1, b3, b4, c1, c3, c4, d1, d3, d4);
    out->element[1][1]  =   det3x3( a1, a3, a4, c1, c3, c4, d1, d3, d4);
    out->element[2][1]  = - det3x3( a1, a3, a4, b1, b3, b4, d1, d3, d4);
    out->element[3][1]  =   det3x3( a1, a3, a4, b1, b3, b4, c1, c3, c4);
        
    out->element[0][2]  =   det3x3( b1, b2, b4, c1, c2, c4, d1, d2, d4);
    out->element[1][2]  = - det3x3( a1, a2, a4, c1, c2, c4, d1, d2, d4);
    out->element[2][2]  =   det3x3( a1, a2, a4, b1, b2, b4, d1, d2, d4);
    out->element[3][2]  = - det3x3( a1, a2, a4, b1, b2, b4, c1, c2, c4);
        
    out->element[0][3]  = - det3x3( b1, b2, b3, c1, c2, c3, d1, d2, d3);
    out->element[1][3]  =   det3x3( a1, a2, a3, c1, c2, c3, d1, d2, d3);
    out->element[2][3]  = - det3x3( a1, a2, a3, b1, b2, b3, d1, d2, d3);
    out->element[3][3]  =   det3x3( a1, a2, a3, b1, b2, b3, c1, c2, c3);
}

/*
 * double = det4x4( matrix )
 * 
 * calculate the determinant of a 4x4 matrix.
 */
double det4x4( Matrix4 *m )
{
    double ans;
    double a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, 			d4;

    /* assign to individual variable names to aid selecting */
	/*  correct elements */

	a1 = m->element[0][0]; b1 = m->element[0][1]; 
	c1 = m->element[0][2]; d1 = m->element[0][3];

	a2 = m->element[1][0]; b2 = m->element[1][1]; 
	c2 = m->element[1][2]; d2 = m->element[1][3];

	a3 = m->element[2][0]; b3 = m->element[2][1]; 
	c3 = m->element[2][2]; d3 = m->element[2][3];

	a4 = m->element[3][0]; b4 = m->element[3][1]; 
	c4 = m->element[3][2]; d4 = m->element[3][3];

    ans = a1 * det3x3( b2, b3, b4, c2, c3, c4, d2, d3, d4)
        - b1 * det3x3( a2, a3, a4, c2, c3, c4, d2, d3, d4)
        + c1 * det3x3( a2, a3, a4, b2, b3, b4, d2, d3, d4)
        - d1 * det3x3( a2, a3, a4, b2, b3, b4, c2, c3, c4);
    return ans;
}

/* 
 *   inverse( original_matrix, inverse_matrix )
 * 
 *    calculate the inverse of a 4x4 matrix
 *
 *     -1     
 *     A  = ___1__ adjoint A
 *         det A
 */
bool inverse( Matrix4 *in, Matrix4 *out )
{
    int i, j;
    double det;

    /* calculate the adjoint matrix */

    adjoint( in, out );

    /*  calculate the 4x4 determinant
     *  if the determinant is zero, 
     *  then the inverse matrix is not unique.
     */

    det = det4x4( in );

    if (fabs( det ) < SMALL_NUMBER)
		return false;

    /* scale the adjoint matrix to get the inverse */

    for (i=0; i<4; i++)
		for(j=0; j<4; j++)
	    out->element[i][j] = out->element[i][j] / det;
	return true;
}
