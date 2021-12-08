#include "DoubleVector.hpp"

#include <iostream>
#include <algorithm>

namespace cie
{

DoubleVector::DoubleVector() : data_(nullptr), size_(0) {}

DoubleVector::DoubleVector( int size ) :
    data_( new double[size] ),
    size_( size )
{
    for( int i = 0; i < size; ++i )
    {
        data_[i] = 0.0;    
    }
}
DoubleVector::DoubleVector(const DoubleVector& other) :  data_(new double[other.size_]),size_(other.size_)
{

    std::copy(other.data_, other.data_ + other.size_, data_);
}

DoubleVector& DoubleVector::operator=(const DoubleVector& other)
{
    if ( this != &other )
    {
        double* newData = new double[other.size_];
        std::copy(other.data_, other.data_ + other.size_, newData);
        
        delete[] data_;

        size_ = other.size_;
        data_ = newData;
    }
    return *this;
}

DoubleVector::~DoubleVector( )
{
    delete[] data_;
}

double& DoubleVector::at( int index )
{
    if( index >= size_ )
    {
        std::cout << "Error: Vector access at invalid index!" << std::endl;
    }

    // In reality one would throw an exception instead of returning an invalid reference
    return data_[index];
}

double& DoubleVector::operator[](int index)
{
    return at(index);
}
int DoubleVector::size( )
{
    return size_;
}

void DoubleVector::resize( int newSize )
{
    double* newData = new double[newSize];
    
    for( int i = 0; i < size_ && i < newSize; ++i )
    {
        newData[i] = data_[i];
    }
    
    for( int i = newSize - 1; i >= size_; --i )
    {
        newData[i] = 0.0;
    }
    
    delete[] data_;
    
    data_ = newData;
    size_ = newSize;
}

void DoubleVector::push_back( double value )
{
    resize( size_ + 1 );
    
    data_[size_ - 1] = value;
}
    
void print( DoubleVector& v )
{
    for( int i = 0; i < v.size( ); ++i )
    {
        std::cout << v.at( i ) << " ";
    }
    
    std::cout << std::endl;
}

void userInput( DoubleVector& v )
{
    for( int i = 0; i < v.size( ); ++i )
    {
        std::cout << "element " << i << ": ";
        
        std::cin >> v.at( i );
    }
}

double dotProduct( DoubleVector& v1, DoubleVector& v2 )
{
    if( v1.size( ) != v2.size( ) )
    { 
        std::cout << "Error: vectors have different size!" << std::endl;
        
        return 0;
    }
    
    double result = 0;
    
    for( int i = 0; i < v1.size( ); ++i )
    {
        result += v1.at( i ) * v2.at( i );
    }
    
    return result;
}

} // namespace cie
