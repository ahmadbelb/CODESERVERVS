#pragma once

namespace cie
{

// Class definition
class DoubleVector
{
public:
    DoubleVector( );

    DoubleVector(const DoubleVector& other);

    DoubleVector& operator=(const DoubleVector& other);

    double& operator[](int index);

    double operator[](int index) const;

    DoubleVector( int size );
    
    ~DoubleVector( );
    
    double& at( int index );
    double at(int index) const;
    
    int size( ) const;
    
    void resize( int newSize );
    
    void push_back( double value );
    
private:
    double* data_;
    int size_;
};

// Free floating functions for user interaction
void print( DoubleVector& v );
void userInput( DoubleVector& v );

// Free floating functions for computations with vectors
double dotProduct( DoubleVector& v1, DoubleVector& v2 ); 

} // namespace cie
