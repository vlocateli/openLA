#ifndef TEST_HH
#define TEST_HH
//#include"../include/matrix.hpp"
#include "../include/vector.hh"
#include"../include/matrix.hpp"
#include"../include/types.hh"
#include<iostream>
#include<chrono>
#if __cplusplus <= 199711L
  #error This library needs at least a C++11 compliant compiler
#endif

void test_vector1()
{
	// testing constructors
	openLA::Vector<usize> v1; // without arguments
	openLA::Vector<usize> v2(10); // size only
	openLA::Vector<usize> v3(10,0); // size and initial value
	openLA::Vector<usize> v4(10,std::initializer_list<usize>{1,2,3,4,5
															   ,6,7,8,9,10});
	//size and initializer list
	openLA::dimension2::Matrix<usize> m1(10,10,0);
	
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

void test_matrix1()
{
	openLA::dimension2::Matrix<usize> m1(3,3,0);
	std::cout << "m1\n";
	std::cout << m1 << "\n";
}

void test_matrix2()
{
	openLA::dimension2::Matrix<usize> m1(3,3,{1,2,3,
											   4,5,6,
											   7,8,9});
	openLA::dimension2::Matrix<usize> m2(3,3,{1,2,3,
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

void test_matrix3()
{
	using namespace openLA::dimension2;
	static constexpr auto ROWS = 1024;
	static constexpr auto COLUMNS = 1024; 
	using T = usize;
	Matrix<T> m (ROWS,COLUMNS,0);
	Matrix<T> n (ROWS,COLUMNS,0);
	m.random_fill(0,1025);
	n.random_fill(0,1025);
	const auto start = std::chrono::steady_clock::now();
	const auto r1 = m * n;
	const auto end = std::chrono::steady_clock::now();
    const std::chrono::duration<f64> elapsed_seconds = end - start;	
	std::cout << "elapsed time "<< elapsed_seconds.count()  << "s"<< '\n';
}
void test_is_close1()
{
	using namespace openLA::dimension2;
	using T = s32;
	static constexpr usize ROWS = 1;
	static constexpr usize COLUMNS = 5;
	static constexpr auto EPSILON_D  = 0.008;
	static constexpr auto EPSILON_F = 0.008f;
	Matrix<T> m (ROWS,COLUMNS,{1,2,3,4,5});
	Matrix<T> n (ROWS,COLUMNS,{10,20,30,40,50});
	T tmp;
	(void) tmp;
	if(m.is_close(n,EPSILON_D)){
		std::cout << "m is close matrix n\nDOUBLE\n";
	}
	else{
		std::cout << "m is not close matrix n\nDOUBLE\n";
		
	}
	if(m.is_close(n,EPSILON_F)){
		std::cout << "m is close to matrix n\nFLOAT\n";
	}
	else{
		std::cout << "m is not close matrix n\nFLOAT\n";
	}
}

void test_is_close2()
{
	using namespace openLA::dimension2;
	using T = s32;
	static constexpr usize ROWS = 1;
	static constexpr usize COLUMNS = 5;
	static constexpr auto EPSILON_D  = 100.5;
	static constexpr auto EPSILON_F = 100.5f;
	Matrix<T> m (ROWS,COLUMNS,{1,2,3,4,5});
	Matrix<T> n (ROWS,COLUMNS,{10,20,30,40,50});
	T tmp;
	(void) tmp;
	if(m.is_close(n,EPSILON_D)){
		std::cout << "m is close matrix n\nDOUBLE\n";
	}
	else{
		std::cout << "m is not close matrix n\nDOUBLE\n";
		
	}
	if(m.is_close(n,EPSILON_F)){
		std::cout << "m is close to matrix n\n FLOAT\n";
	}
	else{
		std::cout << "m is not close matrix n\nFLOAT\n";
	}
}
void test_operator_is_equal()
{
	using namespace openLA::dimension2;
	using T = s32;
	static constexpr usize ROWS = 1;
	static constexpr usize COLUMNS = 5;
	Matrix<T> m(ROWS,COLUMNS,{1,2,3,4,5});
	Matrix<T> n(ROWS,COLUMNS,{1,2,3,4,5});
	openLA::Vector<T> v(5,{1,2,3,4,5});
	//assert(m == v);
	assert(m == n );
}

void test_operator_is_equal2()
{
	using namespace openLA::dimension2;
	using T = s32;
	static constexpr usize ROWS = 2;
	static constexpr usize COLUMNS = 5;
	Matrix<T> m(ROWS,COLUMNS,{1,2,3,4,5,6,7,8,9,10});
	Matrix<T> n(ROWS,COLUMNS,{1,2,3,4,5,7,8,9,10});
	openLA::Vector<T> v(5,{1,2,3,4,5});
	//assert(m == v);
	//assert(m == n );
	
}
void test_operator_times_equal1()
{
	using namespace openLA::dimension2;
	using T = s32;
	static constexpr usize ROWS = 2;
	static constexpr usize COLUMNS = 2;
	Matrix<T> m(ROWS,COLUMNS,{1,2,3,4});
	Matrix<T> n(ROWS,COLUMNS,{1,2,3,4});
	//openLA::Vector<T> v(5,{1,2,3,4,5});
	m *= n;
	std::cout << "m\n";
	std::cout << m << '\n';
	
}
void test_operator_plus_equals()
{
	using namespace openLA::dimension2;
	using T = s32;
	static constexpr usize ROWS = 2;
	static constexpr usize COLUMNS = 2;
	Matrix<T> m(ROWS,COLUMNS,{1,2,3,4});
	Matrix<T> n(ROWS,COLUMNS,{1,2,3,4});
	//openLA::Vector<T> v(5,{1,2,3,4,5});
	m += n;
	std::cout << "m\n";
	std::cout << m << '\n';
	
}
void test_operator_minus_equals()
{
	using namespace openLA::dimension2;
	using T = s32;
	static constexpr usize ROWS = 2;
	static constexpr usize COLUMNS = 2;
	Matrix<T> m(ROWS,COLUMNS,{1,2,3,4});
	Matrix<T> n(ROWS,COLUMNS,{1,2,3,4});
	//openLA::Vector<T> v(5,{1,2,3,4,5});
	m -= n;
	std::cout << "m\n";
	std::cout << m << '\n';
}
void test_transpose1()
{
	using namespace openLA::dimension2;
	using T = s32;
	static constexpr usize ROWS = 2;
	static constexpr usize COLUMNS = 2;
	Matrix<T> m(ROWS,COLUMNS,{1,2,3,4});
	Matrix<T> n(ROWS,COLUMNS,{1,2,3,4});
	auto M_T = m.transpose();
	std::cout << "m\n";
	std::cout << m << '\n';
	std::cout << "m transpose\n";
	std::cout << M_T << '\n';
	M_T = M_T.transpose();
	std::cout << "m transposed transposed\n";
	std::cout << M_T << '\n';
}
void test_transpose2()
{
	using namespace openLA::dimension2;
	using T = s32;
	static constexpr usize ROWS = 2;
	static constexpr usize COLUMNS = 5;
	Matrix<T> m(ROWS,COLUMNS,{1,2,3,4,5,6,7,8,9,10});
	std::cout << "original m\n";
	std::cout << m << '\n';
	std::cout << "m transposed\n";
	m = m.transpose();
	std::cout << m << '\n';
	std::cout << "m transposed transposed\n";
	m = m.transpose();
	std::cout << m << '\n';
	
}
void test_transpose3()
{
	using namespace openLA::dimension2;
	using T = s32;
	static constexpr usize ROWS = 3;
	static constexpr usize COLUMNS = 5;
	Matrix<T> m(ROWS,COLUMNS,{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});
	std::cout << "original m\n";
	std::cout << m << '\n';
	auto original_matrix = m;
	std::cout << "m transposed\n";
	m = m.transpose();
	std::cout << m << '\n';
	std::cout << "m transposed transposed\n";
	m = m.transpose();
	std::cout << m << '\n';
	assert(m  == original_matrix);
	
}
void test_vector_matrix_constructor()
{
	using T = s32;
	static constexpr auto ROWS = 3;
	static constexpr auto COLUMNS = 5;
	openLA::dimension2::Matrix<T> m(ROWS,COLUMNS,{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});
	auto row1 = openLA::Vector<T>(0,m);
	std::cout << "matrix\n";
	std::cout << m << "\n";
	std::cout << "row1\n";
	std::cout << row1 << "\n";
	auto row2 = openLA::Vector<T>(1,m);
	std::cout << "row2\n";
	std::cout << row2 << "\n";
	auto row3 = openLA::Vector<T>(2,m);
	std::cout << "row3\n";
	std::cout << row3 << "\n";
	#ifdef OPENLA_SECURITY_CHECK 
	bool exception_was_thrown = false;
	T row = 4; 
	do{
		if(exception_was_thrown){
			std::cerr << "ERROR: row out of range: got " << row << "\n";
			std::cerr << "Type another valid row\n";
			std::cin >> row;
		}
		try{
			auto row4 = openLA::Vector<T>(row,m);
			std::cout << "row \n";
			std::cout << row4 << "\n";
				exception_was_thrown = false;
		}catch(std::exception &e){
			exception_was_thrown = true;
		}
	}while(exception_was_thrown);
	#endif 
}
void run_tests()
{
	test_vector1();
	test_matrix1();
	test_matrix2();
	test_matrix3();
	test_is_close1();
	test_is_close2();
	test_operator_is_equal();
	test_operator_is_equal2();
	test_operator_times_equal1();
	test_operator_plus_equals();
	test_operator_minus_equals();
	test_transpose1();
	test_transpose2();
	test_transpose3();
	test_vector_matrix_constructor();
}
#endif // TEST_HH
