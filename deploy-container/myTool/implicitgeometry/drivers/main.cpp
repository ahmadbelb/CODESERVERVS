#include "DoubleVector.hpp"
#include <iostream>

int main( )
{
    cie::DoubleVector vector1( 3 );
    cie::DoubleVector vector2( 3 );
    
    std::cout << "Input vector 1" << std::endl;
    cie::userInput( vector1 );
    
    std::cout << "\nInput vector 2" << std::endl;
    cie::userInput( vector2 );
    
    std::cout << "\nBoth vectors are:\nvector1 = ";
    cie::print( vector1 );
    std::cout << "vector2 = ";
    cie::print( vector2 );
    
    std::cout << "\nDot product is: " << cie::dotProduct( vector1, vector2 ) << std::endl;
    
    vector1.push_back( 1.0 );
    vector2.push_back( 1.0 );
    
    // This should give previous one + 1
    std::cout << "\nNew dot product is: " << cie::dotProduct( vector1, vector2 ) << std::endl;
	
	
	//...............
	 std::vector<double> standardVectorDouble( 3 );

    standardVectorDouble[0] = -1.2;
    standardVectorDouble[1] =  2.1;
    standardVectorDouble[2] =  3.2;

	std::cout << "\nNew dot product between a vector and a standard vector: " << helper::dotProduct(vector1, standardVectorDouble)    << std::endl;
	
	//Bonus Question: Try to multiply two do the dot product of a DoubleVector and a vector of strings. What happens? 
	
	
    return 0;
}
