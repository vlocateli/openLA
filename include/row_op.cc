#include "../include/matrix.hh"
namespace openLA{
	template<typename T>
	openLA::dimension2::Matrix<T> gauss_jordan_elimination(
	const openLA::dimension2::Matrix<T> &m)
	{
		auto result {openLA::dimension2::Matrix<T>(m.m_number_of_rows,
					m.m_number_of_columns)};

		while(m.get_element(0, 0) != 1){
			for(usize y = 0; y <  m.m_number_of_columns; y++){
				for(usize x = 0; x < m.m_number_of_rows; x++){
					if(!y && m.get_element(y,x)){
					}
				}
			}
		}
		
	}
	template<typename T>
	auto is_row_echelon(const openLA::dimension2::Matrix<T> &m)
	{
		for(usize y = 0; y < m.m_number_of_columns ; y++){
			for(usize x = 0; x < m.m_number_of_rows; x++){
				
			}
		}
	}
} 
