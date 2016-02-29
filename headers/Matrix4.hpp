//
// Matrix4.hpp
// Cristian Troncoso 2/15/2016
//
#ifndef Matrix4_hpp
#define Matrix4_hpp

#include <math.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Vector4D.hpp"

//class Vector4D;

class Matrix4
{
private:
    float data[16];
    
public:
    /*!
     * \Brief    : Constructor, Initializes the matrix to zero.
     */
    Matrix4()
    {
        data[0]     = 0.0; data[1]  = 0.0; data[2]  = 0.0; data[3]  = 0.0;;
        data[4]     = 0.0; data[5]  = 0.0; data[6]  = 0.0; data[7]  = 0.0;;
        data[8]     = 0.0; data[9]  = 0.0; data[10] = 0.0; data[11] = 0.0;;
        data[12]    = 0.0; data[13] = 0.0; data[14] = 0.0; data[15] = 0.0;;
    }
    
    /*!
     * \Brief    : Constructor, Initializes the matrix to a constant.
     */
    Matrix4(float c)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                data[i * 4 + j] = c;
            }
        }
    }
    /*!
     * \Brief    : Constructor, Initializes from another matrix.
     */
    Matrix4(Matrix4& m)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                data[i * 4 + j] = data[i * 4 + j];
            }
        }
    }
    /*!
     * \Brief   : Destructor.
     */
    ~Matrix4(){}
    /*!
    * \Brief    : Return the raw data of this matrix.
    */
    float* get(int vector,int element)
    {
       return data;
    }
    /*!
    * \Brief    : Negation.
    */
    inline Matrix4 operator-( void ) const
    {
        Matrix4 m;
        for(int i = 0; i < 16; i++)
        {
            m.data[i] = (-1 * data[i]);
        }
        return m;
    }
    /*!
    * \Brief    : Matrix Addition.
    */
    inline Matrix4 operator+(const Matrix4& m)
    {
        Matrix4 ret;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                ret.data[i * 4 + j] = data[i * 4 + j] + m.data[i * 4 + j];
            }
        }
        return ret;
    }
    /*!
    * \Brief    : Matrix Subtraction.
    */
    inline Matrix4 operator-(const Matrix4& m)
    {
        Matrix4 ret;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                ret.data[i * 4 + j] = data[i * 4 + j] - m.data[i * 4 + j];
            }
        }
        return ret;
    }
    /*!
     *\Brief     : scalar multiplication.
     */
    inline Matrix4 operator*( const double& c ) const
    {
        Matrix4 ret;
        for(int i = 0; i < 16; i++)
        {
            ret.data[i] = c * data[i];
        }
        return ret;
    }
    /*!
     * \Brief   : Addition / assignment.
     */
    inline void operator+=(const Matrix4& m)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                data[i * 4 + j] = data[i * 4 + j] + m.data[i * 4 + j];
            }
        }
    }
    /*!
     * \Brief   : Vector4D matrix multiplication.
     */
    inline Vector4D operator*(const Vector4D& a) const
    {
        Vector4D b;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                b[i] += data[j * 4 + i] * a[j];
            }
        }
        return b;
    }

    /*!
     * \Brief   : Returns the transpose.
     */
    Matrix4 transpose(void)
    {
       Matrix4 transpose;
       for(int x = 0; x < 4; ++x)
       {
          for(int y = 0; y < 4; ++y)
          {
             transpose.data[x*4+y] = data[y*4+x];
          }
       }
       return transpose;
    }
    /*!
     * \Brief   : Inverse.
     */
    Matrix4 inverse(void)
    {
        Matrix4 b;
        
        //Calculate the inverse of this matrix
        
        return b;
    }
    /*!
     * \Brief   : Calculate the inverse of this matrix with the assumption that it is ortho-normal.
     */
    Matrix4 orthoNormalInverse(void)
    {
        Matrix4 b;
        //This will be useful when implementing cameras!
        return b;
    }
    /*!
     * \Brief   : Return the value a location j.
     */
    inline double operator[]( int j ) const
    {
        return data[j];
    }
    /*!
     * \Brief   : Print out data.
     */
    void print(std::string comment)
    {
        //Width constants and variables
        static const int pointWidth = 1;
        static const int precisionWidth = 4;
        int integerWidth = 1;
        
        //Determine the necessary width to the left of the decimal point
        float* elementPtr = (float*)data;
        float maxValue = fabsf(*(elementPtr++));
        while(elementPtr++ < ((float*)data+16)) if(fabsf(*elementPtr) > maxValue) maxValue = fabsf(*elementPtr);
        while(maxValue >= 10.0) { ++integerWidth; maxValue /= 10.0; }
        
        //Sum up the widths to determine the cell width needed
        int cellWidth = integerWidth + pointWidth + precisionWidth;
        
        //Set the stream parameters for fixed number of digits after the decimal point
        //and a set number of precision digits
        std::cout << std::fixed;
        std::cout << std::setprecision(precisionWidth);
        
        //Print the comment
        std::cout << comment << std::endl;
        
        //Loop through the matrix elements, format each, and print them to screen
        float cellValue;
        for(int element = 0; element < 4; element++)
        {
            std::cout << std::setw(1) << (element == 0 ? "[" : " ");
            for(int vector = 0; vector < 4; vector++)
            {
                cellValue =  data[element * 4 + vector];
                std::cout << std::setw(cellWidth + (cellValue >= 0.0 ? 1 : 0)) << cellValue;
                std::cout << std::setw(0) << (vector < 3 ? " " : "");
            }
            std::cout << std::setw(1) << (element == 3 ? "]" : " ") << std::endl;
        }
    }
};
#endif // End Matrix_hpp