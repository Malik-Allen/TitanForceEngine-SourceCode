#include "Math.h"

using namespace Kobe;

/// Calculates the dot product between two Vector2
float Math::Dot( const Vector2& v1, const Vector2& v2 )
{
	return (v1.x * v2.x + v1.y * v2.y);
}

/// Calculates the length between two Vector2
float Math::Distance( const Vector2& v1, const Vector2& v2 )
{
	Vector2 result( v1.x - v2.x, v1.y - v2.y );
	return result.magnitude();
}

/// Calculates the angle between two Vector2 in radians
float Math::Angle( const Vector2& v1, const Vector2& v2, const AngleUnitOfMeasurement& unit )
{
	// Using the Dot Product equation to find the angle between vectors wiki: https://en.wikipedia.org/wiki/Dot_product

	float a = Dot( v1, v2 );
	float b = v1.magnitude() * v2.magnitude();

	if ( unit == AngleUnitOfMeasurement::Radians )
		return acos( a / b );							// Radians
	else
		return RADIANS_TO_DEGREES * acos( a / b );	// Degrees
}

/// Linear Interpolation between starting vector2 and end vector2 at rate t
/// When t = 0 returns startPosition. 
/// When t = 1 returns end position. 
/// When t = 0.5 returns midway between start and end positions.
Vector2 Math::Lerp( const Vector2& v1, const Vector2& v2, float t )
{
	return(v1 + t * (v2 - v1));
}

/// Reflects a Vector2 on a Vector2 defined by its normal
Vector2 Math::Reflect( const Vector2& v, const Vector2& n )
{
	float s = 2.0f * Dot( v, n );
	Vector2 proj = n * s;
	Vector2 result = proj - v;
	return result;
}

// Returns vector projection of vector u onto vector v
Vector2 Math::Project( const Vector2& u, const Vector2& v )
{

	// Vector projection of vector u onto v: https://en.wikipedia.org/wiki/Vector_projection

	float mag = sqrt( pow( v.x, 2.0f ) + pow( v.y, 2.0f ) );	// Checking the magnitude of the Vector to be projected on
#ifdef _DEBUG
	if ( fabs( mag ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing nearly by zero!" );
		throw errorMsg;
	}
#endif
	Vector2 normal( v.x / mag, v.y / mag );	// Normal of the Vector3 to be projected onto
	float scalar = ((Dot( u, v )) / (mag * mag));	// Dividing the Dot Product between the Projected Vector3 and the Normal by the Normal's magnitude squared

	return v * scalar;	// Returning the normal scaled to the length of the projected Vector3's shadow
}


Vector3 Math::normalize( const Vector3& v )
{
	float a = sqrt( pow( v.x, 2.0f ) + pow( v.y, 2.0f ) + pow( v.z, 2.0f ) );
#ifdef _DEBUG
	if ( fabs( a ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing nearly by zero!" );
		throw errorMsg;
	}
#endif
	return Vector3( v.x / a, v.y / a, v.z / a );
}

/// Calculates the dot product of two Vector3
float Math::Dot( const Vector3& v1, const Vector3& v2 )
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/// Calculates the length between two Vector3
float Math::Distance( const Vector3& v1, const Vector3& v2 )
{
	Vector3 result( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
	return result.magnitude();
}

/// Calculates the angle between two Vector3
float Math::Angle( const Vector3& v1, const Vector3& v2, const AngleUnitOfMeasurement& unit )
{
	// Using the Dot Product equation to find the angle between vectors wiki: https://en.wikipedia.org/wiki/Dot_product

	float a = Math::Dot( v1, v2 );	// Dot Product
	float b = v1.magnitude() * v2.magnitude();	// Multiplying the magnitudes of each vector

	if ( unit == AngleUnitOfMeasurement::Radians )
		return acos( a / b );						// Radian
	else
		return RADIANS_TO_DEGREES * acos( a / b );	// Degrees
}

/// Linear Interpolation between starting vector3 and end vector3 at rate t
/// When t = 0 returns startPosition. 
/// When t = 1 returns end position. 
/// When t = 0.5 returns midway between start and end positions.
Vector3 Math::Lerp( const Vector3& v1, const Vector3& v2, float t )
{
	return (v1 + t * (v2 - v1));
}

/// Reflects a Vector3 on a Vector3 defined by its normal
Vector3 Math::Reflect( const Vector3& v, const Vector3& n )
{
	float s = 2.0f * Dot( v, n );	// Double the dot product to get the scale at the correct resultant angle
	Vector3 proj = n * s;		// Taking the dot product and scaling the normal by it
	Vector3 result = proj - v;	// Finding the resultant vector through difference
	return result;
}

/// Calculates the cross product between two Vector3
Vector3 Math::Cross( const Vector3& a, const Vector3& b )
{
	return Vector3( a.y * b.z - a.z * b.y,
					-(a.x * b.z - a.z * b.x),
					a.x * b.y - a.y * b.x );
}

// Returns vector projection of vector u onto vector v
Vector3 Math::Project( const Vector3& u, const Vector3& v )
{

	// Vector projection of vector u onto v: https://en.wikipedia.org/wiki/Vector_projection

	float mag = sqrt( pow( v.x, 2.0f ) + pow( v.y, 2.0f ) + pow( v.z, 2.0f ) );	// Checking the magnitude of the Vector3 to be projected on
#ifdef _DEBUG
	if ( fabs( mag ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing nearly by zero!" );
		throw errorMsg;
	}
#endif
	Vector3 normal( v.x / mag, v.y / mag, v.z / mag );	// Normal of the Vector3 to be projected onto
	float scalar = ((Dot( u, v )) / (mag * mag));	// Dividing the Dot Product between the Projected Vector3 and the Normal by the Normal's magnitude squared

	return v * scalar;	// Returning the normal scaled to the length of the projected Vector3's shadow
}

/// Calculates the perpindicular normal to the passed in Vector3's normal
/// The result can be infinite, so pass through a the x, and y values you would like to work with
/// The passed Vector3 must have a non-zero z-component
Vector3 Math::OrthoNormalize( const Vector3& v, float x_, float y_ )
{

	// Wiki on Orthonormalization: https://en.wikipedia.org/wiki/Orthogonalization

	float mag = sqrt( pow( v.x, 2.0f ) + pow( v.y, 2.0f ) + pow( v.z, 2.0f ) );
#ifdef _DEBUG
	if ( fabs( mag ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing nearly by zero!" );
		throw errorMsg;
	}
#endif

	Vector3 normal( v.x / mag, v.y / mag, v.z / mag );
	Vector3 result;
	result.x = x_;
	result.y = y_;

#ifdef _DEBUG
	if ( fabs( normal.z ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing nearly by zero!" );
		throw errorMsg;
	}
#endif

	result.z = (normal.x * x_ + normal.y * y_) / -normal.z;	// The Dot Product of orthogonal(perpindicular) vectors is zero, 
															// So with that in mind you can isolate for any component 
															// While passing through imaginary numbers for the other components 
															// In this case we are isolating for the z-component
	return result.normalized();
}

/// Calculates the Spherical Linear Interpolation between the passed starting point and end position at the rate of t
/// If the angle between the two Vector3 is less than 10 degrees than we use linear interpolation
/// When t = 0 returns startPosition 
/// When t = 1 returns end position 
/// When t = 0.5 returns midway between start and end positions
Vector3 Math::SLerp( const Vector3& v1, const Vector3& v2, float t )
{

	// SLerp: https://en.wikipedia.org/wiki/Slerp

	float a = sqrt( pow( v1.x, 2.0f ) + pow( v1.y, 2.0f ) + pow( v1.z, 2.0f ) );
#ifdef _DEBUG
	if ( fabs( a ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing nearly by zero!" );
		throw errorMsg;
	}
#endif

	Vector3 n1( v1.x / a, v1.y / a, v1.z / a );	// Working with the direction of v1

	float b = sqrt( pow( v2.x, 2.0f ) + pow( v2.y, 2.0f ) + pow( v2.z, 2.0f ) );
#ifdef _DEBUG
	if ( fabs( b ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing nearly by zero!" );
		throw errorMsg;
	}
#endif

	Vector3 n2( v2.x / b, v2.y / b, v2.z / b );	// Working with the direction of v2

	float angle = Angle( n1, n2 );

	if ( -n1.x == n2.x && -n1.y == n2.y && -n1.z == n2.z )
	{	// Checking to see if v1 is equal to -v2, in other words are they in the opposite direction
		angle = -180.0f * DEGREES_TO_RADIANS;	// If so, we will just set the angle to 180 degrees to be on the safe side
	}

#ifdef _DEBUG
	if ( fabs( angle ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing nearly by zero!" );
		throw errorMsg;
	}
#endif

	if ( angle < (10.0f * DEGREES_TO_RADIANS) )
	{
		// When the angle between the two points are very small, we will use linear interpolation instead 
		// This is to avoid problems with the division in SLerp 
		// When v1 and v2 are very close the angle is smaller meaning sin(angle) will be small as well 
		// Which will result in division by a very small number, which will give us inaccurate results
		return Lerp( v1, v2, t );
	}

	float c = angle * (1.0f - t);
	float k1 = sin( c ) / sin( angle );
	float d = angle * t;
	float k2 = sin( d ) / sin( angle );

	Vector3 result = n1 * k1 + n2 * k2;	// Spherical Linear Interpolation Eqxn (multiplication of the direction by the length)

	return result;
}

/// Calculates the dot product between two Vector4
float Math::Dot( const Vector4& v1, const Vector4& v2 )
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

/// Calculates the length between two Vector4
float Math::Distance( const Vector4& v1, const Vector4& v2 )
{
	Vector4 result( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w );
	return sqrt( pow( result.x, 2.0f ) + pow( result.y, 2.0f ) + pow( result.z, 2.0f ) + pow( result.w, 2.0f ) );
}

/// Linear Interpolation between starting vector4 and end vector4 at rate t
/// When t = 0 returns startPosition
/// When t = 1 returns end position
/// When t = 0.5 returns midway between start and end positions
Vector4 Math::Lerp( const Vector4& v1, const Vector4& v2, float t )
{
	return (v1 + t * (v2 - v1));
}

/// Calculates Projection of one Vector4 onto another Vector4
Vector4 Math::Project( const Vector4& u, const Vector4& v )
{
	float mag = sqrt( pow( v.x, 2.0f ) + pow( v.y, 2.0f ) + pow( v.z, 2.0f ) + pow( v.w, 2.0f ) );
#ifdef _DEBUG
	if ( fabs( mag ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing nearly by zero!" );
		throw errorMsg;
	}
#endif
	Vector4 normal( v.x / mag, v.y / mag, v.z / mag, v.w / mag );
	float scalar = Dot( u, v ) / (mag * mag);
	return normal * scalar;

}

///// ***** MATRIX4 ***** \\\\\
// Shoutout and thank you to scott

/// Rotates this Matrix4 about any of the provided axes, and the given the degrees of rotation
Matrix4 Math::Rotate( float degrees, float x, float y, float z )
{
	float cosAngle, sinAngle, cosm;
	Vector3 rotateAxis( x, y, z );
	rotateAxis = normalize( rotateAxis );
	degrees *= DEGREES_TO_RADIANS;				// We do out math using radians
	cosAngle = cos( degrees );
	sinAngle = sin( degrees );
	cosm = (1.0f - cosAngle);

	Matrix4 m;

	/// We obtain the below rotation matrix via concatination (combining matrices), 
	/// Using the 3 independent axis rotation matrices ofcourse!

	m[0] = (rotateAxis.x * rotateAxis.x * cosm) + cosAngle;
	m[1] = (rotateAxis.x * rotateAxis.y * cosm) + (rotateAxis.z * sinAngle);
	m[2] = (rotateAxis.x * rotateAxis.z * cosm) - (rotateAxis.y * sinAngle);
	m[3] = 0.0;

	m[4] = (rotateAxis.y * rotateAxis.x * cosm) - (rotateAxis.z * sinAngle);
	m[5] = (rotateAxis.y * rotateAxis.y * cosm) + cosAngle;
	m[6] = (rotateAxis.y * rotateAxis.z * cosm) + (rotateAxis.x * sinAngle);
	m[7] = 0.0;

	m[8] = (rotateAxis.z * rotateAxis.x * cosm) + (rotateAxis.y * sinAngle);
	m[9] = (rotateAxis.z * rotateAxis.y * cosm) - (rotateAxis.x * sinAngle);
	m[10] = (rotateAxis.z * rotateAxis.z * cosm) + cosAngle;
	m[11] = 0.0;

	m[12] = 0.0;
	m[13] = 0.0;
	m[14] = 0.0;
	m[15] = 1.0;

	return m;
}

/// Rotates this Matrix4 about any of the provided axes as a Vector4, and the given the degrees of rotation
Matrix4 Math::Rotate( const float degrees, const Vector3& axis )
{
	return Math::Rotate( degrees, axis.x, axis.y, axis.z );
}

/// Preforms a uniform scaling, provided the scale factor on each axis
Matrix4 Math::Scale( float x, float y, float z )
{
	return Matrix4( x, 0.0f, 0.0f, 0.0f,
					0.0f, y, 0.0f, 0.0f,
					0.0f, 0.0f, z, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f );
}

/// Preforms uniform scaling, provided the scale factor on each axis as a Vector3
Matrix4 Math::Scale( const Vector3& scale )
{
	return Math::Scale( scale.x, scale.y, scale.z );
}

/// Geometric operation of Perspective projection
Matrix4 Math::Perspective( const float fovy, const float aspect, const float zNear, const float zFar )
{
	// Aspect ratio is calculated by divindg the height of the screen by its width in pixels
	// Fov along the y axis is usually 90 degrees for humans
	// zNear defines the position of out near plane and zFar the position of the far plane.

	float cot = 1.0f / tan( fovy * 0.5f * DEGREES_TO_RADIANS );

	// Keep in mind we are using the right-hand rule
	// We are using the Matrix to create the View Frustum with a Perspective Projection
	// To be then projected on the Normalized Device Coordinates becase that is what is used by OpenGL
	Matrix4 result( cot / aspect, 0.0f, 0.0f, 0.0f,
					0.0f, cot, 0.0f, 0.0f,
					0.0f, 0.0f, (zNear + zFar) / (zNear - zFar), -1.0,
					0.0, 0.0, (2.0f * zNear * zFar) / (zNear - zFar), 0.0 );
	return result;
}


/// This creates a transform from Normalized Device Coordinates (NDC) to 
/// screen coordinates. OpenGL uses NDC as	(Left-Hand Rule)		 
///	              ------------------------------
///	             /|                           /|
///	            / |                          / |
///	           /  |                         /  |
///	          /   |                        /   |
///	         /    |                       /    |
///	        /     |                      /     |
///	       /      |                     /      |
///	      /       |                    /       |
///	     /        |                   /        |
///	    /         |                  /         |
///	   /----------------------------/ (1.0,1.0)|
///	   |          |                 |          |
///	   |          |                 |          |      +Y
///	   |          |                 |          | 
///	   |          |-----------------|----------|      ^
///	   |         /                  |         /       |
///	   |        /                   |        /        |       -Z
///	   |       /                    |       /         |
///	   |      /                     |      /          |     /
///	   |     /                      |     /           |    /
///	   |    /                       |    /            |   /
///	   |   /                        |   /             |  /
///	   |  /                         |  /              | /
///	   | /                          | /               |/
///	   |/ (-1.0,-1.0)               |/                ----------------> +X
///	   ------------------------------
Matrix4 Math::ViewportNDC( int width_, int height_ )
{
	// When using the NDC the z that we use will not ever be negative, it will be between 0 and 1, anything outside that will not be drawn.

	float minZ = 0.0f;
	float maxZ = 1.0f;

	Matrix4 m;
	Matrix4 m1 = Math::Scale( 1.0f, -1.0f, 1.0f );
	Matrix4 m2 = Math::Scale( float( width_ ) / 2.0f, float( height_ ) / 2.0f, maxZ - minZ );
	Matrix4 m3 = Math::Translate( float( width_ ) / 2.0f, float( height_ ) / 2.0f, minZ );
	m = m3 * m2 * m1;

	/***
	m[0] = float(width_)/2.0f;
	m[5] = -float(height_)/2.0f;
	m[10] =  maxZ - minZ;
	m[12] = float(width_)/2.0f;
	m[13] = float(height_)/2.0f;
	m[14] = minZ;
	m[15] = 1.0f; ***/

	return m;
}

/// This Orthographic function is a dimension reducing operatorion
Matrix4 Math::Orthographic( float xMin_, float xMax_, float yMin_, float yMax_, float zMin_, float zMax_ )
{

	Matrix4 m;

	Matrix4 m1 = Math::Scale( 2.0f / (xMax_ - xMin_), 2.0f / (yMax_ - yMin_), -2.0f / (zMax_ - zMin_) );
	Matrix4 m2 = Math::Translate( -(xMax_ + xMin_) / (xMax_ - xMin_), -(yMax_ + yMin_) / (yMax_ - yMin_), -(zMax_ + zMin_) / (zMax_ - zMin_) );
	m = m2 * m1;
	// Above the Matrix we use to obtain the below Matrix
	// Below is the Matrix to define orthographic projection
	// Keeping parallel lines parallel and maintain th size of far and near things the same

	/***
	m[0] = 2.0f / (xMax - xMin);
	m[5] = 2.0f / (yMax - yMin);
	m[10] = -2.0f / (zMax - zMin);
	m[12] = -((xMax + xMin) / (xMax - xMin));
	m[13] = -((yMax + yMin) / (yMax - yMin));
	m[14] = -((zMax + zMin) / (zMax - zMin));
	m[15] = 1.0f;
	***/
	return m;
}

/// The orthographic projection matrix is linear and affine but nothing else so there is has no inverse
/// Therefore, it is labeled singular or non-invertable.
/// I would still like to back transform from screen space to world space though
/// This undoes what the orthographic matrix creates
/// Multiply screen coordinates by this matrix and you should get x and y world coordinates
Matrix4 Math::UnOrtho( const Matrix4& ortho )
{
	Matrix4 m;
	m[0] = 1.0f / ortho[0];
	m[5] = 1.0f / ortho[5];
	m[10] = 1.0f / ortho[10];
	m[12] = -ortho[12] * m[0];
	m[13] = -ortho[13] * m[5];
	m[14] = -ortho[14] * m[10];
	m[15] = 1.0f;
	return m;
}

/// Translates this Matrix4 across the given direction components
Matrix4 Math::Translate( float x_, float y_, float z_ )
{
	return Matrix4( 1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					x_, y_, z_, 1.0f );
}

/// Translates this Matrix4 across the given Vector3 components
Matrix4 Math::Translate( const Vector3& translate_ )
{
	return Math::Translate( translate_.x, translate_.y, translate_.z );
}

/// Look At functions creating the eye, look at position and up position of a camera
Matrix4 Math::LookAt( float eyeX, float eyeY, float eyeZ,
					   float atX, float atY, float atZ,
					   float upX, float upY, float upZ )
{

	Vector3 at( atX, atY, atZ );
	Vector3 up( upX, upY, upZ );
	Vector3 eye( eyeX, eyeY, eyeZ );

	Matrix4 result;

	Vector3 forward = normalize( at - eye );					// Creating the direction vector which is the -eyeDirec currently
	up = normalize( up );										// Working with direction of the up vector no need for the magnitude
	Vector3 side = normalize( Cross( forward, up ) );		// Creating the side of the camera
	up = Cross( side, forward );								// Then using the side and forward vector's we can make the new up direction


	// Below is the Matrix to used represnt the Eye(LookAt)
	result[0] = side.x;
	result[1] = side.y;
	result[2] = side.z;
	result[3] = 0.0;

	result[4] = up.x;
	result[5] = up.y;
	result[6] = up.z;
	result[7] = 0.0;

	result[8] = -forward.x;
	result[9] = -forward.y;
	result[10] = -forward.z;
	result[11] = 0.0;

	result[12] = -Dot( side, eye );
	result[13] = -Dot( up, eye );
	result[14] = Dot( forward, eye );
	result[15] = 1.0;

	return result;
}

/// Look At functions creating the eye, look at position and up position of a camera
Matrix4 Math::LookAt( const Vector3& eye, const Vector3& at, const Vector3& up )
{
	return LookAt( eye.x, eye.y, eye.z, at.x, at.y, at.z, up.x, up.y, up.z );
}

/// Take the transpose of a matrix, swap row with columns
Matrix4 Math::Transpose( const Matrix4& m )
{
	return Matrix4( m[0], m[4], m[8], m[12],
					m[1], m[5], m[9], m[13],
					m[2], m[6], m[10], m[14],
					m[3], m[7], m[11], m[15] );

}

/// 2x2 inverse is easy, 3x3 is a pain, 4x4 no way, this is tough stuff
Matrix4 Math::Inverse( const Matrix4& m )
{
	Matrix4 inverseM;
	float determinate;

	inverseM[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
	inverseM[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
	inverseM[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
	inverseM[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
	inverseM[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
	inverseM[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
	inverseM[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
	inverseM[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
	inverseM[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
	inverseM[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
	inverseM[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
	inverseM[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
	inverseM[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
	inverseM[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
	inverseM[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
	inverseM[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

	determinate = m[0] * inverseM[0] + m[1] * inverseM[4] + m[2] * inverseM[8] + m[3] * inverseM[12];

	// When the determinant is less than zero, it means the Matrix has been reflected
	// When the determninant is zero then this Matrix has been projected, meaning that a column or row is filled with zeroes
	// When the determinant is one than this Matrix is an identity Matrix
	// With any other determinant result, this inverse matrix will reverse a rotation, transformation, scale, etcimpacting said matrix 
#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
	if ( fabs( determinate ) < VERY_SMALL )
	{
		std::string errorMsg( "Divide by nearly zero in Math::inverse!" );
		throw errorMsg;
	}
#endif
	determinate = 1.0f / determinate;
	for ( int i = 0; i < 16; i++ )
	{
		inverseM[i] *= determinate;
	}
	return inverseM;
}


/// Calculates the normalized conjugate of a Quaternion
Quaternion Math::Inverse( const Quaternion& q )
{
	Quaternion conj( -q.x, -q.y, -q.z, q.w );

	float mag = sqrt( pow( conj.x, 2.0f ) + pow( conj.y, 2.0f ) + pow( conj.z, 2.0f ) + pow( conj.w, 2.0f ) );

#ifdef _DEBUG
	if ( fabs( mag ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing by nearly zero!" );
		throw errorMsg;
	}
#endif

	return Quaternion( conj.x / mag, conj.y / mag, conj.z / mag, conj.w / mag );
}

/// Returns the conjugate of the passed Quaternion
Quaternion Math::Conjugate( const Quaternion& q )
{
	return Quaternion( -q.x, -q.y, -q.z, q.w );
}

/// Calculates the unit quaternion
Quaternion Math::Normalize( const Quaternion& q )
{
	float mag = sqrt( pow( q.x, 2.0f ) + pow( q.y, 2.0f ) + pow( q.z, 2.0f ) + pow( q.w, 2.0f ) );
#ifdef _DEBUG
	if ( fabs( mag ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing by a magnitude of nearly zero!" );
		throw errorMsg;
	}
#endif
	return Quaternion( q.x / mag, q.y / mag, q.z / mag, q.w / mag );
}

/// Calculates the dot product between two quaternions
float Math::Dot( const Quaternion& q1, const Quaternion& q2 )
{
	return (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w);
}

/// **WIP::Calculates the angle between two Quaternions
float Math::Angle( const Quaternion& q1, const Quaternion& q2 )
{
	float a = (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w);
	float b = sqrt( pow( q1.x, 2.0f ) + pow( q1.y, 2.0f ) + pow( q1.z, 2.0f ) + pow( q1.w, 2.0f ) ) * sqrt( pow( q2.x, 2.0f ) + pow( q2.y, 2.0f ) + pow( q2.z, 2.0f ) + pow( q2.w, 2.0f ) );
	return acos( a / b );
}

/// Rotates a given point about the Quaternion
Vector3 Math::Rotate( const Quaternion& q, const Vector3& v )
{
	Quaternion q2( v.x, v.y, v.z, 0.0f );
	Quaternion result = q * q2 * Inverse( q );
	return Vector3( result.x, result.y, result.z );

}

/// **WIP::Linear Interpolation between starting Quaternion and end Quaternion at rate t
/// When t = 0 returns startPosition
/// When t = 1 returns end position
/// When t = 0.5 returns midway between start and end positions
Quaternion Math::Lerp( const Quaternion& q1, const Quaternion& q2, float t )
{
	return Normalize( ((1.0f - t) * q1) + (t * q2) );
}

/// **WIP:: Calculates the Spherical Linear Interpolation between the passed starting point and end position at the rate of t
/// If the angle between the two Vector3 is less than 10 degrees than we use linear interpolation
/// When t = 0 returns startPosition 
/// When t = 1 returns end position 
/// When t = 0.5 returns midway between start and end positions
Quaternion Math::SLerp( const Quaternion& q1, const Quaternion& q2, float t )
{
	float a = sqrt( pow( q1.x, 2.0f ) + pow( q1.y, 2.0f ) + pow( q1.z, 2.0f ) + pow( q2.w, 2.0f ) );
#ifdef _DEBUG
	if ( fabs( a ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing nearly by zero!" );
		throw errorMsg;
	}
#endif

	Quaternion n1( q1.x / a, q1.y / a, q1.z / a, q1.w / a );	// Working with the direction of q1

	float b = sqrt( pow( q2.x, 2.0f ) + pow( q2.y, 2.0f ) + pow( q2.z, 2.0f ) + pow( q2.w, 2.0f ) );
#ifdef _DEBUG
	if ( fabs( b ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing nearly by zero!" );
		throw errorMsg;
	}
#endif

	Quaternion n2( q2.x / b, q2.y / b, q2.z / b, q2.w / b );	// Working with the direction of q2

	float angle = Angle( n1, n2 );

	if ( -n1.x == n2.x && -n1.y == n2.y && -n1.z == n2.z && -n1.w == n2.w )
	{	// Checking to see if q1 is equal to -q2, in other words are they in the opposite direction
		angle = -180.0f * DEGREES_TO_RADIANS;	// If so, we will just set the angle to 180 degrees to be on the safe side
	}

#ifdef _DEBUG
	if ( fabs( angle ) < VERY_SMALL )
	{
		std::string errorMsg( "Error! Dividing nearly by zero!" );
		throw errorMsg;
	}
#endif

	if ( angle < (10.0f * DEGREES_TO_RADIANS) )
	{	
		// When the angle between the two points are very small, we will use linear interpolation instead 
		// This is to avoid problems with the division in SLerp 
		// When q1 and q2 are very close the angle is smaller meaning sin(angle) will be small as well 
		// Which will result in division by a very small number, which will give us inaccurate results
		return Lerp( q1, q2, t );
	}

	float c = angle * (1.0f - t);
	float k1 = sin( c ) / sin( angle );
	float d = angle * t;
	float k2 = sin( d ) / sin( angle );

	Quaternion result = n1 * k1 + n2 * k2;	// Spherical Linear Interpolation Eqxn (multiplication of the direction by the length)

	return result;
}


/// Converting a Quaternion into a 4x4 Matrix
Matrix4 Math::QuaternionToMatrix( const Quaternion& q )
{

	Matrix4 m;

	m[0] = (1.0f - (2.0f * pow( q.y, 2.0f )) - (2.0f * pow( q.z, 2.0f )));
	m[1] = (2.0f * q.x * q.y) + (2.0f * q.w * q.z);
	m[2] = (2.0f * q.x * q.z) - (2.0f * q.w * q.y);
	m[3] = 0.0f;

	m[4] = (2.0f * q.x * q.y) - (2.0f * q.w * q.z);
	m[5] = (1.0f - (2.0f * pow( q.x, 2.0f )) - (2.0f * pow( q.z, 2.0f )));
	m[6] = (2.0f * q.y * q.z) + (2.0f * q.w * q.x);
	m[7] = 0.0f;

	m[8] = (2.0f * q.x * q.z) + (2.0f * q.w * q.y);
	m[9] = (2.0f * q.y * q.z) - (2.0f * q.w * q.x);
	m[10] = (1.0f - (2.0f * pow( q.x, 2.0f )) - (2.0f * pow( q.y, 2.0f )));
	m[11] = 0.0f;

	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 0.0f;
	m[15] = 1.0f;

	return m;
}

/// Converting a Matrix into a Quaternion
Quaternion Math::MatrixToQuaternion( const Matrix4& m )
{
	float t;
	Quaternion q;

	if ( m[10] < 0.0f )
	{

		if ( m[0] > m[5] )
		{
			t = 1.0f + m[0] - m[5] - m[10];
			q.Load( t, m[1] + m[4], m[8] + m[2], m[6] - m[9] );

		}
		else
		{
			t = 1.0f - m[0] + m[5] - m[10];
			q.Load( m[1] + m[4], t, m[6] + m[9], m[8] - m[2] );
		}
	}
	else
	{

		if ( m[0] < -m[5] )
		{
			t = 1.0f - m[0] - m[5] + m[10];
			q.Load( m[8] + m[2], m[6] + m[9], t, m[1] - m[4] );
		}
		else
		{
			t = 1.0f + m[0] + m[5] + m[10];
			q.Load( m[6] - m[9], m[8] - m[2], m[1] - m[4], t );
		}
	}

	q *= (0.5f / sqrt( t ));

	return q;

}

/// Converting an Euler(Y, Z, X) into a Quaternion 
Quaternion Math::EulerToQueaternion( const Euler& e1 )
{

	Euler e( e1.x * DEGREES_TO_RADIANS, e1.y * DEGREES_TO_RADIANS, e1.z * DEGREES_TO_RADIANS );

	float c1 = cos( e.y / 2.0f );
	float c2 = cos( e.z / 2.0f );
	float c3 = cos( e.x / 2.0f );
	float s1 = sin( e.y / 2.0f );
	float s2 = sin( e.z / 2.0f );
	float s3 = sin( e.x / 2.0f );

	float c1c2 = c1 * c2;
	float s1s2 = s1 * s2;

	float w = (c1c2 * c3) - (s1s2 * s3);
	float x = (c1c2 * s3) + (s1s2 * c3);
	float y = (s1 * c2 * c3) + (c1 * s2 * s3);
	float z = (c1 * s2 * c3) - (s1 * c2 * s3);

	return Quaternion( x, y, z, w );
}

/// Converting a Quaternion into an Euler(Y, Z, X)
Euler Math::QuaternionToEuler( const Quaternion& q )
{

	float sqw = q.w * q.w;
	float sqx = q.x * q.x;
	float sqy = q.y * q.y;
	float sqz = q.z * q.z;

	float sum = sqx + sqy + sqz + sqw;
	float testCase = (q.x * q.y) + (q.z * q.w);

	float yaw, roll, pitch;

	if ( testCase > 0.499f * sum )
	{
		yaw = 2.0f * atan2( q.x, q.w );
		roll = PI / 2.0f;
		pitch = 0.0f;
	}
	else if ( testCase < -0.499f * sum )
	{
		yaw = -2.0f * atan2( q.x, q.w );
		roll = -PI / 2.0f;
		pitch = 0.0f;
	}
	else
	{
		yaw = atan2( (2.0f * q.y * q.w) - (2.0f * q.x * q.z), sqx - sqy - sqz + sqw );
		roll = asin( 2.0f * testCase / sum );
		pitch = atan2( (2.0f * q.x * q.w) - (2.0f * q.y * q.z), -sqx + sqy - sqz + sqw );
	}

	return Euler( pitch * RADIANS_TO_DEGREES, yaw * RADIANS_TO_DEGREES, roll * RADIANS_TO_DEGREES );

}