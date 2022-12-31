//#include "../include/matrix.hpp"
#include<iostream>
#include<sstream>
int main(int argc, char**argv){
	if(argc != 4){
		std::cerr << "Usage: matrix <number of rows> <number of columns> <initializer type>\n";
		return 1;
	}
	size_t rows;
	size_t columns;
	size_t number;
	std::cout << "argv[1] = "<< argv[1]<<'\n';
	std::stringstream buffer(argv[1]);
	buffer >> rows;
	std::cout << "rows = "<<rows << '\n';
	buffer.str(std::string());
	buffer << argv[2];
	buffer >> columns;
	std::cout << "columns = "<< columns << '\n';
	buffer.str(std::string());
	std::cout << "argv[3] = " << argv[3] << '\n';
	buffer << argv[3];
	std::cout << buffer.str() << '\n';
	buffer >> number;
	std::cout << "number = "<<number << '\n';

	//openLA::Matrix<size_t> matrix(rows,columns,number);
	//std::cout << matrix << '\n';

}
