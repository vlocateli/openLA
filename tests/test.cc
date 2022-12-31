#include "../include/matrix.hpp"

int main(){
	openLA::Matrix<size_t> m1(5,3,0);
	openLA::Matrix<size_t> m2(3,5,2);
	std::cout << m1 << '\n';
	std::cout << '\n';
	std::cout << m2 << '\n';
	openLA::Matrix<size_t> *result { new openLA::Matrix<size_t> {10,10,1}}; 
#if 0
	result = m1 + m2;
	std::cout << "addition\n";
	std::cout << *result << '\n';
	std::cout << "subtraction\n";
	result = m1 - m2;
	std::cout << *result << '\n';
	std::cout << "product\n";
#endif
	m1.set_index(1,1,1);
	m1.set_index(2, 1, 1);
	result = m1 * m2;
	std::cout << *result << '\n';
	delete result;

}

