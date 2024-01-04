#ifndef VECTOR_HH
#define VECTOR_HH 1
#pragma once
#include <memory>
#include <iostream>
#include "types.hh"
namespace openLA{
template<class T>
    class vector{
        public:
            std::shared_ptr<T> m_vector;
            size_t m_total_elements;
            vector<T>(size_t size)
            : m_total_elements {size}
            {
                try{
                    m_vector =  std::make_unique<T>(size);
                }catch(std::bad_alloc())
                {
                    throw std::runtime_error("Couldn't allocate memory\n");
                }catch(...)
                {
                    std::cerr << "Unhandled exception\n";
                }
            }
            vector<T>()
            : vector<T>(0)
            {
            }
            T operator[] (const usize index);
    };
}
template<class T>
T openLA::vector<T>::operator[] ( const usize index)
{
    return *(m_vector + index);
}
template<class T>
T dot_product (const openLA::vector<T> &p, const openLA::vector<T> &q)
{
    if(p.m_total_elements != q.m_total_elements){
        throw std::logic_error("ERROR: vectors have diferent\
                lenght!\n");
    }
    T sum{};
    for(usize i = 0; i < p.m_total_elements; i++){
       sum += p.m_vector[i] * q.m_vector[i]; 
    }

    return sum;
}
#endif // VECTOR_HH
