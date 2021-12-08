// This tells catch to define a main function in this file
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "DoubleVector.hpp"
#include "VectorHelper.hpp"
#include <vector>
#include <array>
#include <iomanip>

/*
 * Note, that the following is not tested:
 * - data is deleted in the destructor
 * - the right text is printed to the console
 * - the user input is done correctly
 * - error messages are given when input in wrong
 * ... simply because it's not easy to test.
 */
 
TEST_CASE( "DoubleVector_defaultInitialization" )
{
    int n = 5;

    cie::DoubleVector vector( n );

    REQUIRE( vector.size( ) == n );
    
    for( int i = 0; i < n; ++i )
    {
        CHECK( vector.at( i ) == 0.0 );    
    }
}

TEST_CASE( "DoubleVector_simpleAssignment" )
{
    double values[] = { 1.0 / 3.0, -2.5, 77.7 };

    int n = sizeof( values ) / sizeof( values[0] );

    cie::DoubleVector vector( n );

    REQUIRE( vector.size( ) == n );
    
    // Set values
    for( int i = 0; i < n; ++i )
    {
        vector.at( i ) = values[i];    
    }

    // Read values    
    for( int i = 0; i < n; ++i )
    {
        CHECK( vector.at( i ) == Approx( values[i] ) );    
    }
}

TEST_CASE( "DoubleVector_resizeLarger" )
{
    double values[] = { -2.1, 6.6 };

    int n = sizeof( values ) / sizeof( values[0] );

    cie::DoubleVector vector( n );

    REQUIRE( vector.size( ) == n );
    
    // Set values
    for( int i = 0; i < n; ++i )
    {
        vector.at( i ) = values[i];    
    }
    
    vector.resize( n + 2 );
    
    REQUIRE( vector.size( ) == n + 2 );
    
    // Read values that were already there    
    for( int i = 0; i < n; ++i )
    {
        CHECK( vector.at( i ) == Approx( values[i] ) );    
    }
    
    // Check if new values are default initialized
    for( int i = n; i < n + 2; ++i )
    {
        CHECK( vector.at( i ) == 0.0 );
    }
}

TEST_CASE( "DoubleVector_resizeSmaller" )
{
    double values[] = { -2.1, 6.6, 3.2, -5.4 };

    int n = sizeof( values ) / sizeof( values[0] );

    cie::DoubleVector vector( n );

    REQUIRE( vector.size( ) == n );
    
    // Set values
    for( int i = 0; i < n; ++i )
    {
        vector.at( i ) = values[i];    
    }
    
    vector.resize( n - 3 );
    
    REQUIRE( vector.size( ) == n - 3 );
    
    // Read values up to new size    
    for( int i = 0; i < n - 3; ++i )
    {
        CHECK( vector.at( i ) == Approx( values[i] ) );    
    }
}

TEST_CASE( "DoubleVector_push_back" )
{
    double values[] = { 4.3, 4.2, 4.1, 4.0 };
    
    int n = sizeof( values ) / sizeof( values[0] ) - 1;
    
    cie::DoubleVector vector( n );
    
    REQUIRE( vector.size( ) == n );
    
    for( int i = 0; i < n; ++i )
    {
        vector.at( i ) = values[i];
    }
    
    vector.push_back( values[n] );
    
    REQUIRE( vector.size( ) == n + 1 );
    
    for( int i = 0; i < n + 1; ++i )
    {
        CHECK( vector.at( i ) == values[i] );
    }
}

TEST_CASE( "DoubleVector_pushToEmptyVector" )
{
    double values[] = { 2.2, 2.3, 3.4 };
    
    int n = sizeof( values ) / sizeof( values[0] );

    cie::DoubleVector vector( 0 );
    
    REQUIRE( vector.size( ) == 0 );
    
    for( int i = 0; i < n; ++i )
    {
        vector.push_back( values[i] );
    }
    
    REQUIRE( vector.size( ) == n );

    for( int i = 0; i < n; ++i )
    {
        CHECK( vector.at( i ) == values[i] );
    }
}

TEST_CASE( "dotProduct" )
{
    double values1[] = { 3.2, -5.3, 0.1, 7.7 };
    double values2[] = { 0.9, 0.4, 11.1, 6.2 };
    
    int n = 4;
    
    double expectedDotProduct = values1[0] * values2[0] +
                                values1[1] * values2[1] +
                                values1[2] * values2[2] +
                                values1[3] * values2[3];
    
    cie::DoubleVector vector1( n );
    cie::DoubleVector vector2( n );
    
    REQUIRE( vector1.size( ) == n );
    REQUIRE( vector2.size( ) == n );
    
    for( int i = 0; i < n; ++i )
    {
        vector1.at( i ) = values1[i];
        vector2.at( i ) = values2[i];
    }
    
    CHECK( cie::dotProduct( vector1, vector2 ) == Approx( expectedDotProduct ) );
}


TEST_CASE( "DoubleVector_defaultConstructor" )
{
    cie::DoubleVector vector;

    CHECK( vector.size( ) == 0 );
}

TEST_CASE( "DoubleVector_copyConstructor" )
{
    int n = 5;

    cie::DoubleVector vector( n );

    REQUIRE( vector.size( ) == n );

    for( int i = 0; i < n; ++i )
    {
       vector.at( i ) = i;
    }

    cie::DoubleVector copy( vector );

    REQUIRE( copy.size( ) == n );

    for( int i = 0; i < n; ++i )
    {
        CHECK( copy.at( i ) == i );
    }
}

TEST_CASE( "DoubleVector_assignmentOperator_correctValues" )
{
	int n = 4;

    cie::DoubleVector vector( n );

    for( int i = 0; i < n; ++i )
    {
    	vector.at( i ) = 10.4 - i;
    }

    cie::DoubleVector copy;

    copy = vector;

    REQUIRE( copy.size( ) == n );

    // Check if a deep copy was done
    CHECK( &copy.at( 0 ) != &vector.at( 0 ) );

    for( int i = 0; i < n; ++i )
    {
    	CHECK( copy.at( i ) == 10.4 - i );
    }
}

TEST_CASE( "DoubleVector_assignmentOperator_defaultConstructed" )
{
    cie::DoubleVector vector;

    cie::DoubleVector copy1;
    cie::DoubleVector copy2( 3 );

    copy1 = vector;
    copy2 = vector;

    CHECK( copy1.size( ) == 0 );
    CHECK( copy2.size( ) == 0 );
}

TEST_CASE( "DoubleVector_assignmentOperator_selfAssignment" )
{
    cie::DoubleVector vector( 2 );

    vector.at( 0 ) = 2.0;
    vector.at( 1 ) = 1.2;

    cie::DoubleVector& vectorReference = vector;

    vector = vectorReference;

    REQUIRE( vector.size( ) == 2 );

    CHECK( vector.at( 0 ) == 2.0 );
    CHECK( vector.at( 1 ) == 1.2 );
}

TEST_CASE( "DoubleVector_arraySubscript" )
{
    cie::DoubleVector vector( 3 );

    // Check if address of array subscript and at( ) are the same
    CHECK( &vector.at( 0 ) == &vector[0] );

    vector[0] =  3.2;
    vector[1] =  2.1;
    vector[2] = -1.2;

    CHECK( vector.at( 0 ) ==  3.2 );
    CHECK( vector.at( 1 ) ==  2.1 );
    CHECK( vector.at( 2 ) == -1.2 );
}


TEST_CASE( "DoubleVector_helpers" )
{
    cie::DoubleVector vector( 3 );

    vector[0] =  3.2;
    vector[1] =  2.1;
    vector[2] = -1.2;
    
    double comparisonValueDouble = -3.14;
    int comparisonValueInt = -3;

    CHECK(helper::areAllElementsGreaterThan(comparisonValueDouble, vector) == true);
    CHECK(helper::areAllElementsGreaterThan(comparisonValueInt, vector) == true);

    std::vector<double> standardVectorDouble( 3 );

    standardVectorDouble[0] = -1.2;
    standardVectorDouble[1] =  2.1;
    standardVectorDouble[2] =  3.2;

    CHECK(helper::areAllElementsGreaterThan(comparisonValueDouble, standardVectorDouble) == true);
    CHECK(helper::areAllElementsGreaterThan(comparisonValueInt, standardVectorDouble) == true);

    std::vector<int> standardVectorInt( 3 );

    standardVectorInt[0] = -1;
    standardVectorInt[1] =  2;
    standardVectorInt[2] =  3;

    CHECK(helper::areAllElementsGreaterThan(comparisonValueDouble, standardVectorInt) == true);
    CHECK(helper::areAllElementsGreaterThan(comparisonValueInt, standardVectorInt) == true);

    CHECK(helper::dotProduct(vector, standardVectorDouble) == Approx( -3.27 ));
    CHECK(helper::dotProduct(vector, standardVectorInt) == Approx( -2.6 ));

    std::array<int, 3> standardArrayInt;

    standardArrayInt[0] = 2;
    standardArrayInt[1] = 4;
    standardArrayInt[2] = -6;

    CHECK(helper::areAllElementsGreaterThan(comparisonValueDouble, standardArrayInt) == false);
    CHECK(helper::areAllElementsGreaterThan(comparisonValueInt, standardArrayInt) == false);

    CHECK(helper::dotProduct(vector, standardArrayInt) == Approx(22.));


}

