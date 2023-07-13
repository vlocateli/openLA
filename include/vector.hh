#ifndef VECTOR_HH 
#define VECTOR_HH
#include <iostream>
namespace openLA{
template<class T>

class Vector{
	private:
	T* m_vector;
	size_t m_size;
	public:
	Vector(const size_t size){
		try{
			m_vector = new T[size];
			m_size = size;
		}catch(std::bad_alloc &err){
			throw std::runtime_error("Couldn't allocate memory");
		}
	}
	T* get_vector()
	{
		return m_vector;
	}
	T* get_vector() const 
	{
		return m_vector;
	}
	T operator[](const size_t index)
	{
		#ifdef OPENLA_SECURITY_CHECK
		if(index >= m_size)
		{
			throw std::invalid_argument("ERROR: index out of bounds. Aborting...");
		}
		#endif 
		return *(m_vector+index);
	}
	Vector()
	{
		m_vector = nullptr;
		m_size = 0;
	}
	Vector(const size_t size,const T value)
	:Vector{size}
	{
		for(size_t i = 0;i<size;i++){
			m_vector[i] = value;
		}
	}
	~ Vector()
	{
		delete [] m_vector;
		m_size = 0;
	}
	Vector(const size_t size,const std::initializer_list<T> &list)
	:Vector{size}
	{
		if(m_size != list.size()){
			throw std::runtime_error("ERROR: size of list is diferent from size of the vector. Aborting...");
		}
		size_t i = 0;
		for(const T* p = list.begin();p != list.end();p++){
			m_vector[i] = *p;
			i++;
		}
	}
	size_t capacity() const
	{
		return m_size;
	}
	friend std::ostream& operator << (std::ostream &stream, const openLA::Vector<T> *&v)
	{
		for(size_t i = 0; i< v->m_size;i++){
			stream << v[i] << " ";
		}
		return stream;
	}
	friend std::ostream &operator<<(std::ostream &stream, openLA::Vector<T> &v)
	{
		for(size_t i = 0; i< v.m_size;i++){
			stream << v[i] << " ";
		}
		return stream;
	}
};
}
#endif