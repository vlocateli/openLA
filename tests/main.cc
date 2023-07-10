//#include "../include/matrix.hpp"
#include "../include/matrix_rewritten.hh"
#include "../include/test.hh"
static constexpr size_t ROWS = 5;
static constexpr size_t COLS = 5;
int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	auto m1 {openLA::dimension2::Matrix<size_t>(ROWS * 2,COLS * 2,0)};
	//auto m2 {openLA::dimension2::Matrix<size_t>(ROWS,COLS * 2,std::initializer_list<size_t>{ 
	//																	1,2,3,4,5,6,7,8,9,10,
	//																	11,12,13,14,15,16,17,18,19,20,
	//																	21,22,23,24,25,26,27,28,29,30,
	//																	31,32,33,34,35,36,37,38,39,40,
	//																	41,42,43,44,45,46,47,48,49,50 })};
	std::cout << "m1\n" << m1 << '\n';
	//std::cout << "m2\n" << m2 << '\n';
	//if(m1 == m2){
	//	std::cout << "equal\n";
	//}else{
	//	std::cout << "not equal\n";
	//}
	//test_vector1();
	//test_matrix1();
	//test_matrix2();
	//test_matrix3();
}

