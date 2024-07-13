#include <limits>
#ifndef VECTOR_HH
#define VECTOR_HH 1
#include <cstring>
#include <iostream>
#include <memory>

#include "types.hh"
#include "utilities.hh"
namespace openLA {
template <class T>
class Vector {
    private:
  std::shared_ptr<T[]> m_vector;
  size_t m_total_elements;
    public:
  using iterator = std::shared_ptr<T[]>;
  using const_iterator = const std::shared_ptr<T[]>;
  Vector(usize size) : m_total_elements{size} {
    try {
      m_vector = std::make_unique<T[]>(size);
    } catch (std::bad_alloc()) {
      throw std::runtime_error("Couldn't allocate memory\n");
    } catch (...) {
      std::cerr << "Unhandled exception\n";
    }
  }
  Vector() : Vector<T>(0) {}
  Vector(const Vector<T>& other);
  Vector(const Vector<T>&& other);
  Vector(const usize size, T initial_val) : Vector<T>(size) {
    for (usize i = {}; i < m_total_elements; i++) {
      m_vector[i] = initial_val;
    }
  }
  std::unique_ptr<T> data() const {
    return m_vector;
  }
  size_t size() const  {
    return m_total_elements;
  }
  const_iterator cbegin() const { return m_vector; };
  const_iterator cend() const { return m_vector + m_total_elements; }
  const_iterator begin() const { return cbegin(); };
  const_iterator end() const { return cend(); }
  iterator begin() { return m_vector; };
  iterator end() { return m_vector + m_total_elements; };

  template <typename P>
  friend openLA::Vector<P> operator+(openLA::Vector<P>& lhs,
                                     openLA::Vector<P>& rhs) noexcept {
    assert(lhs.m_total_elements == rhs.m_total_elements);
    usize size{lhs.m_total_elements};

    openLA::Vector<P> res(size);
    for (usize i = 0; i < res.m_total_elements; i++) {
      res.m_vector[i] = lhs.m_vector[i] + rhs.m_vector[i];
    }

    return res;
  }
  template <typename P>
  friend openLA::Vector<P> operator-(openLA::Vector<P>& lhs,
                                     openLA::Vector<P>& rhs) noexcept {
    assert(lhs.m_total_elements == rhs.m_total_elements);
    usize size{lhs.m_total_elements};
    openLA::Vector<P> res(size);
    for (usize i = 0; i < res.m_total_elements; i++) {
      res.m_vector[i] = lhs.m_vector[i] - rhs.m_vector[i];
    }

    return res;
  }
  template <typename P>
  friend openLA::Vector<P> operator*(openLA::Vector<P>& lhs,
                                     openLA::Vector<P>& rhs) noexcept {
    assert(lhs.m_total_elements == rhs.m_total_elements);
    usize size{lhs.m_total_elements};
    openLA::Vector<P> res(size);
    for (usize i = 0; i < res.m_total_elements; i++) {
      res.m_vector[i] = lhs.m_vector[i] * rhs.m_vector[i];
    }

    return res;
  }
  template <typename P>
  friend std::ostream& operator<<(std::ostream& stream,
                                  const openLA::Vector<P>& vec) {
    stream << "[ ";
    for (usize i = 0; i < vec.m_total_elements; i++) {
      stream << vec.m_vector[i] << ' ';
    }
    stream << " ]";
    return stream;
  }
  T& operator[](const usize index) noexcept { return m_vector[index]; }
  void resize(const usize& new_size) noexcept;
  bool operator==(const openLA::Vector<T>& rhs) {
    if (rhs.m_vector == m_vector && rhs.m_total_elements == m_total_elements) {
      return true;
    }

    return false;
  }
  openLA::Vector<T>& operator=(openLA::Vector<T>& rhs) {
    if (this == &rhs) {
      return *this;
    }
    Vector<T> new_vector(rhs.m_total_elements);
    for (size_t i = 0; i < rhs.m_total_elements; i++) {
      new_vector.m_vector[i] = rhs.m_vector[i];
    }

    m_vector = std::move(new_vector.m_vector);
    m_total_elements = rhs.m_total_elements;

    return *this;
  }
};
}  // namespace openLA
template <typename T>
void openLA::Vector<T>::resize(const usize& new_size) noexcept {
  if (new_size == m_total_elements) {
    return;
  }
  openLA::Vector<T> new_vec(new_size);
  if (new_size > m_total_elements) {
      for (usize i = 0; i < m_total_elements; i++) {
        new_vec.m_vector[i] = m_vector[i];
      }
      
  }
  else if(new_size < m_total_elements) {
    for(usize i = 0; i < new_size; i++) {
        new_vec.m_vector[i] = m_vector[i];
    }
  }
  *this = new_vec;
}

template <typename T>
openLA::Vector<T>::Vector(const openLA::Vector<T>& other) {
  m_total_elements = other.m_total_elements;
  resize(m_total_elements);
  for (usize i = 0; i < m_total_elements; i++) {
    m_vector[i] = other.m_vector[i];
  }
}

#endif  // VECTOR_HH
