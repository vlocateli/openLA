#ifndef MATRIX_HPP
#define MATRIX_HPP
#include<cassert>
#include<iostream>
#include<cstring>
#include<sstream>
#include<memory>
#define USAGE() \
		std::cerr << "Usage: matrix <number of rows> "; \
		std::cerr << "<number of columns> <initial value of size_t type>\n";\
		exit(1)
#define SET_AT_INDEX(m,col,row,value) (m)->m_matrix[m_number_of_columns*(row) + (col)] = value

namespace openLA{
	template <typename T>
	class Matrix{
		private:
			//T*	   m_matrix{nullptr};
			std::shared_ptr<T []> m_matrix;
			size_t m_number_of_rows{0};
			size_t m_number_of_columns{0};
			size_t m_total_elements{0};
		public:
			Matrix(const size_t rows,const size_t columns)
			{
				try
				{
					m_matrix =  std::make_unique<T []>(rows * columns);
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
					//delete [] m_matrix;
					m_matrix = nullptr;
					m_number_of_rows = m_number_of_columns = m_total_elements = 0;
			}
			T* operator[](const size_t index)
			{
				if(index >= m_total_elements){
					throw std::logic_error("index out of bounds\n");
				}
				if(!m_matrix){
					throw std::logic_error("trying to dereference a nullptr\n");
				}
				return m_matrix+index;
			}
			
			inline void set_at_index(size_t row,size_t column, T value)
			{
				if(row >= m_number_of_rows || column > m_number_of_columns){
					throw std::runtime_error("Index of (set_index) out of bounds");
				}
				SET_AT_INDEX(this,column, row,value);
			}
			friend std::ostream& operator<<(std::ostream &stream,const openLA::Matrix<T> &m) noexcept
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
			//Matrix(Matrix &&m){
            //    std::cout << "Move" << "\n\n";
            //    std::swap(m.m_matrix, m_matrix);
            //    m_number_of_rows = m.m_number_of_rows;
            //    m_number_of_columns = m.m_number_of_columns;
            //    m_total_elements = m.m_total_elements;
            //}
			friend std::ostream& operator<<(std::ostream &stream,const openLA::Matrix<T>*&m) noexcept
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
			friend std::shared_ptr<openLA::Matrix<T>>  operator +(const std::shared_ptr<openLA::Matrix<T>> &m1,const std::shared_ptr<openLA::Matrix<T>> &m2)
			{
				assert(m1->m_matrix != nullptr);
				assert(m2->m_matrix != nullptr);
				if(m1->m_number_of_rows != m2->m_number_of_rows && m1->m_number_of_columns != m2->m_number_of_columns){
					throw std::logic_error("Number of columns/rows of Matrices are different\n");
				}
				auto result =  std::make_shared<openLA::Matrix<T>>(Matrix{m1->m_number_of_rows,m1->m_number_of_columns});
				for(size_t i = 0;i<result->m_total_elements;i++){
					assert(result->m_matrix != nullptr);
					result->m_matrix[i] = m1->m_matrix[i] + m2->m_matrix[i];
				}
				return result;
			}
			friend std::shared_ptr<openLA::Matrix<T>>  operator *(const std::shared_ptr<openLA::Matrix<T>> &m1,const std::shared_ptr<openLA::Matrix<T>> &m2)
			{
				assert(m1->m_matrix != nullptr);
				assert(m2->m_matrix != nullptr);
				if(m1->m_number_of_columns != m2->m_number_of_rows){
					throw std::logic_error("Number of columns/rows of Matrices are different\n");
				}
				auto result = std::make_shared<openLA::Matrix<T>>(Matrix{m1->m_number_of_rows,m2->m_number_of_columns,0});
				assert(result->m_matrix != nullptr);
#if 0
				for(auto i = 0;i<result->m_total_elements;i++)
				{
					if(i % result->m_number_of_columns == 0 && i != 0)
					{
						std::cout << '\n';
					}
					std::cout << result->m_matrix[i] << " ";
				
				}
#endif
				for(size_t i = 0;i<result->m_total_elements;i++){
					for(size_t j = 0;j<m1->m_total_elements;j++){
						for(size_t k = 0;k<m2->m_total_elements;k+=m2->m_number_of_columns){
							//assert(result->m_matrix[i] == 0);
							result->m_matrix[i] += m1->m_matrix[j] * m2->m_matrix[k];
						}
					}
				}
				
				return result;

			}
			friend std::shared_ptr<openLA::Matrix<T>>  operator -(const std::shared_ptr<openLA::Matrix<T>> &m1,const std::shared_ptr<openLA::Matrix<T>> &m2)
			{
					assert(m1->m_matrix != nullptr);
					assert(m2->m_matrix != nullptr);
					if(m1->m_number_of_rows != m2->m_number_of_rows && m1->m_number_of_columns != m2->m_number_of_columns)
					{
						throw std::logic_error("Number of rows and columns are different\n");
					}
					auto result = std::make_shared<openLA::Matrix<T>>(Matrix{m1->m_number_of_rows,m2->m_number_of_columns,0});
					assert(result->m_matrix != nullptr);
					for(size_t i = 0;i<result.m_total_elements;i++){
						result->m_matrix[i] = m1->m_matrix[i] - m2->m_matrix[i];
					}
					return result;
			}
#endif
	};
}//openLA
