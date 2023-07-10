#ifndef TEST_HH
#define TEST_HH
#include"../include/matrix.hpp"
#include "../include/vector.hh"
#include<iostream>
#include<chrono>
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
	openLA::dimension2::Matrix<size_t> m1(10,10,0);
	
	assert(v1.capacity() == 0);
	assert(v2.capacity() == 10);
	assert(v3.capacity() == 10);

	std::cout << "V1" << '\n';
	std::cout << v1 << '\n';
	std::cout << "V3" << '\n';
	std::cout << v3 << '\n';
	std::cout << "V4" << '\n';
	std::cout << v4 << '\n';
	std::cout << m1 << '\n';
}

extern void test_matrix1()
{
	openLA::dimension2::Matrix<size_t> m1(3,3,0);
	std::cout << "m1\n";
	std::cout << m1 << "\n";
}
extern void test_matrix2()
{
	openLA::dimension2::Matrix<size_t> m1(3,3,{1,2,3,
											   4,5,6,
											   7,8,9});
	openLA::dimension2::Matrix<size_t> m2(3,3,{1,2,3,
											   4,5,6,
											   7,8,9});

	std::cout << "m1\n";
	std::cout << m1 << '\n';
	std::cout << "m2\n";
	std::cout << m2 << '\n';
	std::cout << "testing operator +\n";
	std::cout << m1 + m2 << '\n';
	std::cout << "testing operator -\n";
	std::cout << m1 - m2 << '\n';
	std::cout << "testing operator *\n";
	std::cout << m1 * m2 << '\n';
}
extern void test_matrix3()
{
	using namespace openLA::dimension2;
	using T = size_t;
	Matrix<T> m (1024,1024,0);
	Matrix<T> n (1024,1024,0);
	m.random_fill(0,1025);
	n.random_fill(0,1025);
	const auto start = std::chrono::steady_clock::now();
	auto r = m * n;
	const auto end = std::chrono::steady_clock::now();
    const std::chrono::duration<double> elapsed_seconds = end - start;	
	std::cout << "elapsed time: "<< elapsed_seconds.count()  << "s"<< '\n';
}
#endif // TEST_HH
