#include "../include/matrix.hpp"
#include "../include/test.hh"
static constexpr size_t ROWS = 5;
static constexpr size_t COLS = 5;
int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	auto m1 { std::make_shared<openLA::dimension2::Matrix<size_t>>(ROWS,COLS,std::initializer_list<size_t>{
																			  1,0,0,0,0,
																			  0,1,0,0,0,
																			  0,0,1,0,0,
																			  0,0,0,1,0,
																			  0,0,0,0,1})};
	auto m2 { std::make_shared<openLA::dimension2::Matrix<size_t>>(ROWS,COLS,std::initializer_list<size_t>{
																			  1,0,0,0,0,
																			  0,1,0,0,0,
																			  0,0,1,0,0,
																			  0,0,0,1,0,
																			  0,0,0,0,1})};
	std::cout << "m1\n" << m1 << '\n';
	std::cout << "m2\n" << m2 << '\n';
	if(m1 == m2){
		std::cout << "equal\n";
	}else{
		std::cout << "not equal\n";
	}

	test_vector1();
	test_matrix1();
}

