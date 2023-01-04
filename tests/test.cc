#include "../include/matrix.hpp"

int main()
{
	
	auto m1 = std::make_shared<openLA::Matrix<size_t>>(5,5,1);
	auto m2 = std::make_shared<openLA::Matrix<size_t>>(5,5,1);
	m1->set_at_index(1, 1, 2);
	auto result {std::make_shared<openLA::Matrix<size_t>>(5,5,0)};
	std::cout << *m1 << '\n'<<'\n';
	std::cout << *m2 << '\n'<<'\n';
	result = m1 * m2;
	std::cout << *result << '\n';
}

