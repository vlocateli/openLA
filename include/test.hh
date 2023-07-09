#ifndef TEST_HH
#define TEST_HH
#include"../include/matrix_rewritten.hh"
#include "../include/vector.hh"
#if __cplusplus <= 199711L
  #error This library needs at least a C++11 compliant compiler
#endif


extern void test_vector1()
{
	// testing constructors
	openLA::Vector<size_t> v1; // without arguments
	openLA::Vector<size_t> v2(10); // size only
	openLA::Vector<size_t> v3(10,0); // size and initial value
	openLA::Vector<size_t> v4(10,std::initializer_list<size_t>{1,2,3,4,5
															   ,6,7,8,9,10});
	//size and initializer list
	
	assert(v1.capacity() == 0);
	assert(v2.capacity() == 10);
	assert(v3.capacity() == 10);

	std::cout << "V1" << '\n';
	std::cout << v1 << '\n';
	std::cout << "V3" << '\n';
	std::cout << v3 << '\n';
	std::cout << "V4" << '\n';
	std::cout << v4 << '\n';
}

extern void test_matrix1()
{
	using namespace openLA;
	Matrix<size_t> m1(3,3,0);
	std::cout << "m1\n";
	std::cout << m1 << "\n";
	m1.pretty_print(std::cout);
}

#endif // TEST_HH
