#ifndef VECTOR_HH
#define VECTOR_HH 1
#include <memory>
#include <iostream>
#include <cstring>
#include "types.hh"
#include "utilities.hh"
namespace openLA{
template<class T>
    class Vector{
        public:
            std::shared_ptr<T [] > m_vector;
            size_t m_total_elements;
            using iterator = std::shared_ptr<T []>;
            using const_iterator = const std::shared_ptr<T []>;
            Vector(usize size)
            : m_total_elements {size}
            {
                try{
                    m_vector =  std::make_unique<T []>(size);
                }catch(std::bad_alloc())
                {
                    throw std::runtime_error("Couldn't allocate memory\n");
                }catch(...)
                {
                    std::cerr << "Unhandled exception\n";
                }
            }
            Vector()
            : Vector<T>(0)
            {
            }
           Vector(const Vector<T>& other);
           Vector(const Vector<T>&& other);
            Vector(const usize size, T initial_val)
                : Vector<T>(size)
                {
                    for(usize i = {}; i < m_total_elements; i++){
                        m_vector[i] = initial_val;
                    }
                }
            const_iterator cbegin() const { return m_vector; };
            const_iterator cend() const { return m_vector + m_total_elements; }
            const_iterator begin() const { return cbegin(); };
            const_iterator end() const   { return cend();}
            iterator begin() { return m_vector; };
            iterator end()   { return m_vector + m_total_elements; };

            template<typename P>
            friend openLA::Vector<P> operator+  (openLA::Vector<P> &lhs, 
                                                 openLA::Vector<P> &rhs)
                                                 noexcept
            {
                assert(lhs.m_total_elements == rhs.m_total_elements);
                usize size{lhs.m_total_elements};

                openLA::Vector<P> res(size);
                for(usize i = 0; i < res.m_total_elements; i++){
                    res.m_vector[i] = lhs.m_vector[i] + rhs.m_vector[i];
                }

                return res;
            }
            template<typename P>
            friend openLA::Vector<P> operator-  (openLA::Vector<P> &lhs,
                                                 openLA::Vector<P> &rhs)
                                                 noexcept
            {
                assert(lhs.m_total_elements == rhs.m_total_elements);
                usize size{lhs.m_total_elements};
                openLA::Vector<P> res(size);
                for(usize i = 0; i < res.m_total_elements; i++){
                    res.m_vector[i] = lhs.m_vector[i] - rhs.m_vector[i];
                }

                return res;
            }
            template<typename P>
            friend openLA::Vector<P> operator*  (openLA::Vector<P> &lhs, 
                                                 openLA::Vector<P> &rhs)
                                                 noexcept
            {
                assert(lhs.m_total_elements == rhs.m_total_elements);
                usize size{lhs.m_total_elements};
                openLA::Vector<P> res(size);
                for(usize i = 0; i < res.m_total_elements; i++){
                    res.m_vector[i] = lhs.m_vector[i] * rhs.m_vector[i];
                }

                return res;
            }
            template<typename P>
            friend std::ostream& operator<<      (std::ostream &stream,
                                                 const openLA::Vector<P> &vec)
            {
            
                stream << "[ ";
                for(usize i = 0; i < vec.m_total_elements; i++)
                {
                    stream << vec.m_vector[i] << ' ';
                }
                stream << " ]";
                return stream;
            }
            T& operator[] (const usize index) noexcept
            {
                return m_vector[index];
            }
            openLA::Vector<T> resize(const usize new_size) noexcept;
    };
} // openLA
template<typename T>
openLA::Vector<T> openLA::Vector<T>::resize(const usize new_size) noexcept
{
    if(new_size == m_total_elements){
        return *this;
    }
    openLA::Vector<T> new_vec(new_size);
    for(usize i = 0; i < m_total_elements; i++)
    {
        new_vec[i] = m_vector[i];
    }
    *this = new_vec;
    return *this;
}

template<typename T>
openLA::Vector<T>::Vector(const openLA::Vector<T>& other) 
{
}
#endif // VECTOR_HH
