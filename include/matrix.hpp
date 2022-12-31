#ifndef MATRIX_HPP
#define MATRIX_HPP
#include<cassert>
#include<iostream>
#include<cstring>
#include<sstream>

namespace openLA{
	inline void usage()
	{
		std::cerr << "Usage: matrix <number of rows> ";
		std::cerr << "<number of columns> <initial value of size_t type>\n";
		exit(1);
	}	
	template <typename T>
	class Matrix{
		private:
			T* m_matrix{nullptr};
			size_t m_number_of_rows{0};
			size_t m_number_of_columns{0};
			size_t m_total_elements{0};
		public:
			Matrix(const size_t rows,const size_t columns)
			{
				try
				{
					m_matrix =  new T [rows * columns];
					m_number_of_rows = rows;
					m_number_of_columns = columns;
					m_total_elements = rows * columns;
				}
				catch(std::bad_alloc())
				{
					throw std::runtime_error("Couldn't allocate memory\n");
				}
			}
			Matrix(const size_t rows,const size_t columns,const T type)
				: Matrix{rows,columns}
			{
				try
				{
					for(size_t i = 0;i<m_total_elements;i++){
						m_matrix[i] = type;
					}
				}
				catch(std::bad_alloc())
				{
					throw std::runtime_error("Couldn't allocate memory\n");
				}
			
			}
			~Matrix()
			{
					delete [] m_matrix;
					m_matrix = nullptr;
					m_number_of_rows = m_number_of_columns = m_total_elements = 0;
			}
			T* operator[](const size_t index)
			{
				if(index >= m_total_elements){
					throw std::logic_error("index out of bounds\n");
				}
				if(m_matrix == nullptr){
					throw std::logic_error("trying to dereference a nullptr\n");
				}
				return m_matrix+index;
			}
			inline void set_index(size_t row,size_t column, T value)
			{
				if(row >= m_number_of_rows || column > m_number_of_columns){
					throw std::runtime_error("Index of (set_index) out of bounds");
				}
				m_matrix[column * row + column] = value;
			}
			friend std::ostream& operator<<(std::ostream &stream,const openLA::Matrix<T> &m)
			{
				
				assert(m.m_matrix != nullptr);
				for(size_t i = 0;i<m.m_total_elements;i++){
					if(i % m.m_number_of_columns == 0 && i != 0){
						stream << '\n';
					}
					stream << m.m_matrix[i] << " " ;
				}
				
				return stream;
			
			}
			friend std::ostream& operator<<(std::ostream &stream,const openLA::Matrix<T>*&m)
			{
				
				assert(m != nullptr);
				assert(m->m_matrix != nullptr);
				for(size_t i = 0;i<m->m_total_elements;i++){
					if(i % m->m_number_of_columns == 0 && i != 0){
						stream  << '\n';
					}
					stream << m->m_matrix[i] << " " ;
				}
				
				return stream;
			
			}
			friend Matrix<T>* operator +(const Matrix<T> &m1,const Matrix<T> &m2)
			{
				assert(m1.m_matrix != nullptr);
				assert(m2.m_matrix != nullptr);
				if(m1.m_number_of_rows != m2.m_number_of_rows && m1.m_number_of_columns != m2.m_number_of_columns){
					throw std::logic_error("Number of columns/rows of Matrices are different\n");
				}
				Matrix<T> *result = new Matrix{m1.m_number_of_rows,m1.m_number_of_columns};
				for(size_t i = 0;i<result->m_total_elements;i++){
					assert(result != nullptr);
					assert(result->m_matrix != nullptr);
					result->m_matrix[i] = m1.m_matrix[i] + m2.m_matrix[i];
				}
				return result;
			}
			friend Matrix<T>* operator *(Matrix<T> &m1, Matrix<T> &m2)
			{
				assert(m1.m_matrix != nullptr);
				assert(m2.m_matrix != nullptr);
				if(m1.m_number_of_columns != m2.m_number_of_rows){
					throw std::logic_error("Number of columns/rows of Matrices are different\n");
				}
				Matrix<T> *result = new Matrix{m1.m_number_of_rows,m2.m_number_of_columns};
				
				for(size_t i = 0;i<result->m_total_elements;i++){
					assert(result != nullptr);
					assert(result->m_matrix != nullptr);
					for(size_t j = 0;j<m1.m_total_elements;j++){
						for(size_t k = 0;k<m2.m_total_elements;k++){
							result->m_matrix[i] = m1.m_matrix[j] * m2.m_matrix[k];
						}
					}
				}
				
				return result;

			}
			friend Matrix<T>* operator-(Matrix<T> &m1,Matrix<T> &m2)
			{
					assert(m1.m_matrix != nullptr);
					assert(m2.m_matrix != nullptr);
					if(m1.m_number_of_rows != m2.m_number_of_rows && m1.m_number_of_columns != m2.m_number_of_columns)
					{
						throw std::logic_error("Number of rows and columns are different\n");
					}
					Matrix<T> *result = new Matrix{m1.m_number_of_rows,m1.m_number_of_columns};
					for(size_t i = 0;i<result->m_total_elements;i++){
						assert(result != nullptr);
						assert(result->m_matrix != nullptr);
						result->m_matrix[i] = m1.m_matrix[i] - m2.m_matrix[i];
					}
					return result;
			}
	};
}//openLA
#endif // MATRIX_HPP 
