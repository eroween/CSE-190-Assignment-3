//
// Vector3D.hpp
// Cristian Troncoso 2/15/2016
//
#ifndef Vector3D_hpp
#define Vector3D_hpp

#include <string>
#include "Vector4D.hpp"

class Vector4D;

class Vector3D
{

protected:
    double x, y, z;             /**< Components */
public:

    /*!
     * \Brief   : Constructor, Initializes vector (0,0,0).
     */
    Vector3D(): x( 0.0 ), y( 0.0 ), z( 0.0 ) { }
    /*!
     * \Brief   : Constructor, Initializes to vector (x,y,z).
     */
    Vector3D(double x, double y, double z) : x( x ), y( y ), z( z ) { }
    /*!
     * \Brief   : Constructor, Initializes to vector (d,d,d).
     */
    Vector3D( double d ) : x( d ), y( d ), z( d ) { }
    /*!
     * \Brief   : Constructor, Initializes from another Vector3D.
     */
    Vector3D( const Vector3D& v ) : x( v.x ), y( v.y ), z( v.z ) { }
    /*!
     * \Brief   : Destructor
     */
    ~Vector3D(){}
    /*!
     * \Brief   : Return a reference to the Vector data.
     */
    float* ptr()
    {
        // TODO : Test and verify
        return (float*)(&x);
    }
    /*!
     * \Brief   : Return a reference to the data of the vector
     */
    double* xyz()
    {
        return &x;
    }
    /*!
     * \Brief   : Set a value at a specific index in a Vector.
     */
    void set(int index, double value)
    {
        (&x) [index] = value;
    }
    /*!
     * \Brief   : Return a reference to a specified index (location).
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
    inline Vector3D operator+(const Vector3D& a) const
    {
        return Vector3D(x + a.x, y + a.y , z + a.z);
    }
    /*!
     * \Brief   : Subtraction.
     */
    inline Vector3D operator-(const Vector3D& a)
    {
        return Vector3D(x - a.x, y - a.y , z - a.z);
    }
    /*!
     * \Brief   : Negation.
     */
    inline Vector3D operator-( void ) const
    {
        return Vector3D( -x, -y, -z );
    }
    /*!
     * \Brief   : Right scalar multiplication.
     */
    inline Vector3D operator*( const double& c ) const
    {
        return Vector3D( x * c, y * c, z * c );
    }
    /*!
     * \Brief   : Left scalar multiplication.
     *
     */
    //inline Vector3D operator*( const double& c, const Vector3D& v ) const
    //{
    //    return Vector3D( c * v.x, c * v.y, c * v.z );
    //}
    /*!
     * \Brief   : scalar division.
     */
    inline Vector3D operator/( const double& c ) const
    {
        const double rc = 1.0/c;
        return Vector3D( rc * x, rc * y, rc * z );
    }
    /*!
     * \Brief   : addition / assignment
     */
    inline void operator+=( const Vector3D& v )
    {
        x += v.x; y += v.y; z += v.z;
    }
    /*!
     * \Brief   : subtraction / assignment.
     */
    inline void operator-=( const Vector3D& v )
    {
        x -= v.x; y -= v.y; z -= v.z;
    }
    /*!
     * \Brief   : scalar multiplication / assignment.
     */
    inline void operator*=( const double& c )
    {
        x *= c; y *= c; z *= c;
    }
    /*!
     * \Brief   : scalar division / assignment.
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
        return sqrt( x*x + y*y + z*z );
    }
    /*!
     * \Brief   :Returns Euclidean length squared.
     */
    inline double magnitude2( void ) const
    {
        return x*x + y*y + z*z;
    }
    /*!
     * \Brief   :Returns unit vector.
     */
    inline Vector3D unit( void ) const
    {
        double rNorm = 1. / sqrt( x*x + y*y + z*z );
        return Vector3D( rNorm*x, rNorm*y, rNorm*z );
    }
    /**
     * \Brief   : Divides by Euclidean length.
     */
    inline void normalize( void )
    {
        (*this) /= magnitude();
    }
    /*!
     * \Brief   : Convert a Vector3D to Vecotor4D.
     */
    //Vector4D toVector4D(float w)
    //{
    //    return Vector4D(x, y, z, w);
    //}
    /*!
    * \Brief    : Dot product.
    */
    inline double dot( const Vector3D& u, const Vector3D& v )
    {
        return u.x*v.x + u.y*v.y + u.z*v.z ;
    }
    /*!
    * \Brief    : Cross product.
    */
    inline Vector3D cross( const Vector3D& u, const Vector3D& v )
    {
        return Vector3D( u.y*v.z - u.z*v.y,
                         u.z*v.x - u.x*v.z,
                         u.x*v.y - u.y*v.x );
    }
    /*!
    * \Brief    : Print out Vector.
    */
    void print(std::string comment)
    {
        std::cout << comment << std::endl;
        std::cout << "<x:" << x <<  ", y:" << y << ", z:" << z << ">" << std::endl;
    }
};

#endif //Vector3D_hpp
