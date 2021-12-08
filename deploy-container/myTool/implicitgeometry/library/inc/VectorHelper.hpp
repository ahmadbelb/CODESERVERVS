#include "DoubleVector.hpp"


namespace helper
{
	// check if all elements of the vector is greater than value, return true if yes.
    // Assume VectorType has a valid [] operator and size() member function. 
	template<typename T, typename VectorType>
	bool areAllElementsGreaterThan(T value, const VectorType& vector);


	// A generic dotproduct. Assume each vectortype has a valid [] operator and a size() member function.
	template<typename VectorType1, typename VectorType2>
	double dotProduct(const VectorType1& v1, const VectorType2& v2);


}
#include "VectorHelper_impl.hpp"



