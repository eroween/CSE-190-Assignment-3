//
// Vector4D.hpp
// Cristian Troncoso 2/15/2016
//
#ifndef Vector4D_hpp
#define Vector4D_hpp

#include <math.h>
#include <iostream>
#include <cstring>
#include "Vector3D.hpp"


class Vector4D
{
    
protected:
    double x, y, z, w;      /**< Components */
public:
    /*!
     * \Brief   : Constructor, Initializes vector (0,0,0,0).
     */
    Vector4D(): x( 0.0 ), y( 0.0 ), z( 0.0 ), w(0.0) { }
    /*!
     * \Brief   : Constructor, Initializes to vector (x,y,z,w).
     */
    Vector4D(double x, double y, double z, double w) : x( x ), y( y ), z( z ), w(w) { }
    /*!
     * \Brief   : Constructor, Initializes to vector (d,d,d,d).
     */
    Vector4D( double d ) : x( d ), y( d ), z( d ), w(d) { }
    /*!
     * \Brief   : Constructor, Initializes  from another Vector4D.
     */
    Vector4D( const Vector4D& v ) : x( v.x ), y( v.y ), z( v.z ), w(v.w) { }
    /*!
     * \Brief   : Destructor
     */
    ~Vector4D(){}
    /*!
     * \Brief   : Return a reference to the Vector data.
     */
    float* ptr()
    {
        // TODO : Test and verify
        return (float*)(&x);
    }
    /*!
     * \Brief   : Return a reference to the Vector data.
     */
    double* xyz()
    {
        return &x;
    }
    /*!
     * \Brief   : Set a value at a specific index location.
     */
    void set(int index, double value)
    {
        (&x) [index] = value;
    }
    /*!
     * \Brief   : Return a reference to a specified location.
     */
    inline double& operator [] (const int& loc)
    {
        return (&x) [loc];
    }
    /*!
     * \Brief   : Return a "constant" reference to a specified location.
     */
    inline const double& operator [] (const int& loc) const
    {
        return (&x) [loc];
    }
    /*!
     * \Brief   : Addition.
     */
    inline Vector4D operator+(const Vector4D& a) const
    {
        return Vector4D(x + a.x, y + a.y , z + a.z, w + a.w);
    }
    /*!
     * \Brief   : Subtraction.
     */
    inline Vector4D operator-(const Vector4D& a)
    {
        return Vector4D(x - a.x, y - a.y , z - a.z, w - a.w);
    }
    /*!
     * \Brief   : Negation.
     */
    inline Vector4D operator-( void ) const
    {
        return Vector4D( -x, -y, -z , -w);
    }
    
    /*!
     * \Brief   : Right scalar multiplication.
     */
    inline Vector4D operator*( const double& c ) const
    {
        return Vector4D( x * c, y * c, z * c, w * c );
    }
    /*!
     * \Brief   : Left scalar multiplication.
     */
    //inline Vector4D operator*( const double& c, const Vector4D& v ) const
    //{
    //    return Vector4D( c * v.x, c * v.y, c * v.z, c * v.w);
    //}
    /*!
     * \Brief   : Scalar division.
     */
    inline Vector4D operator/( const double& c ) const
    {
        const double rc = 1.0/c;
        return Vector4D( rc * x, rc * y, rc * z, rc * w );
    }
    /*!
     * \Brief   : Addition / assignment
     */
    inline void operator+=( const Vector4D& v )
    {
        x += v.x; y += v.y; z += v.z; w += v.w;
    }
    /*!
     * \Brief   : Subtraction / assignment.
     */
    inline void operator-=( const Vector4D& v )
    {
        x -= v.x; y -= v.y; z -= v.z; w -=v.w;
    }
    /*!
     * \Brief   : Scalar multiplication / assignment.
     */
    inline void operator*=( const double& c )
    {
        x *= c; y *= c; z *= c; w *= c;
    }
    /*!
     * \Brief   : Scalar division / assignment.
     */
    inline void operator/=( const double& c )
    {
        (*this) *= ( 1./c );
    }
    /*!
     * \Brief   : Returns Euclidean length.
     */
    inline double magnitude( void ) const
    {
        return sqrt( x*x + y*y + z*z + w*w);
    }
    /*!
     * \Brief   :Returns Euclidean length squared.
     */
    inline double magnitude2( void ) const
    {
        return x*x + y*y + z*z + w*w;
    }
    /*!
     * \Brief   :Returns unit vector.
     */
    inline Vector4D unit( void ) const
    {
        double rNorm = 1. / sqrt( x*x + y*y + z*z + w*w);
        return Vector4D( rNorm*x, rNorm*y, rNorm*z, rNorm*w );
    }
    /**
     * \Brief   : Divides by Euclidean length.
     */
    inline void normalize( void )
    {
        (*this) /= magnitude();
    }
    /*!
     * \Brief   : Convert a Vector4D to Vecotor3D.
     */
    Vector3D toVector3D()
    {
        return Vector3D(x,y,z);
    }
    /*!
     * \Brief   : Dot product.
     */
    inline double dot( const Vector4D& u, const Vector4D& v )
    {
        return u.x*v.x + u.y*v.y + u.z*v.z + u.w*v.w ;
    }
    /*!
     * \Brief   : Print out Vector.
     */
    void print(std::string comment)
    {
        std::cout << comment << std::endl;
        std::cout << "<x:" << x <<  ", y:" << y << ", z:" << z << ">" << std::endl;
    }
};
    
#endif //Vector4D_hpp
