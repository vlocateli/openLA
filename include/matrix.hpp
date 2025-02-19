#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <math.h>

#include <cassert>
#include <cstring>
#include <iostream>
#include <memory>
#include <random>

#include "../include/types.hh"
#define USAGE()                                                        \
  std::cerr << "Usage: matrix <number of rows> ";                      \
  std::cerr << "<number of columns> <initial value of size_t type>\n"; \
  exit(1)
#define SET_AT_INDEX(m, col, row, value) \
  (m)->m_matrix[(m_number_of_columns * row + col)] = value
#define DEBUG_ENABLE 1
#define DEBUG_PRINT(fmt, ...)          \
  do {                                 \
    fprintf(stderr, fmt, __VA_ARGS__); \
  } while (0);
#define DEBUG_PRINT_MAT(m)                                      \
  {                                                             \
    do {                                                        \
      for (size_t i = 0, i < (m)->m_number_of_rows, i++) {      \
        for (size_t k = 0, k < (m)->m_number_of_columns, k++) { \
          std::cerr << (m)->get_element(i, k);                  \
        }                                                       \
        std::cerr << '\n';                                      \
      }                                                         \
    } while (0);
#define DEBUG(x)                          \
  do {                                    \
    std::cerr << #x << ": " << x << '\n'; \
  } while (0);
static constexpr auto n_threads{8};

#if 0
#define OPENLA_SECURITY_CHECK
#endif
namespace openLA {
namespace dimension2 {
template <typename T>
class Matrix {
 private:
  std::shared_ptr<T[]> m_matrix;
  size_t m_number_of_rows{0};
  size_t m_number_of_columns{0};
  size_t m_total_elements{0};

 public:
  Matrix(const size_t rows, const size_t columns) {
    try {
      m_matrix = std::make_unique<T[]>(rows * columns);
      m_number_of_rows = rows;
      m_number_of_columns = columns;
      m_total_elements = rows * columns;
    } catch (std::bad_alloc()) {
      throw std::runtime_error("Couldn't allocate memory\n");
    }
  }
  Matrix(const size_t rows, const size_t columns, const T type)
      : Matrix{rows, columns} {
    try {
      for (size_t i = 0; i < m_total_elements; i++) {
        m_matrix[i] = type;
      }
    } catch (std::bad_alloc()) {
      throw std::runtime_error("Couldn't allocate memory\n");
    }
  }
  Matrix(const size_t rows, const size_t columns,
         const std::initializer_list<T> &list)
      : Matrix{rows, columns} {
    try {
#ifdef OPENLA_SECURITY_CHECK
      if (list.size() != m_total_elements) {
        throw std::invalid_argument(
            "ERROR: list size is diferent from total number of elments from "
            "the matrix. Aborting...");
      }
#endif
      size_t i = 0;
      for (const T *k = list.begin(); k != list.end(); k++) {
        m_matrix[i] = *k;
        i++;
      }
    } catch (std::bad_alloc()) {
      throw std::runtime_error("Couldn't allocate memory");
    }
  }
  ~Matrix() {
    m_matrix = nullptr;
    m_number_of_rows = m_number_of_columns = m_total_elements = 0;
  }
  T *operator[](const size_t index) {
#ifdef OPENLA_SECURITY_CHECK
    if (index >= m_total_elements) {
      throw std::logic_error("index out of bounds\n");
    }
    if (!m_matrix) {
      throw std::logic_error("trying to dereference a nullptr\n");
    }
#endif
    return m_matrix + index;
  }
  Matrix &operator()(const size_t &row, const size_t &column) {
#ifdef OPENLA_SECURITY_CHECK
    if (row >= m_number_of_rows || column >= m_number_of_columns) {
      throw std::logic_error("index out of bounds");
    }
    if (!m_matrix) {
      throw std::logic_error("trying to dereference a nullptr");
    }
#endif
    return m_matrix[m_number_of_columns * row + column];
  }

  friend std::ostream &operator<<(
      std::ostream &stream,
      const std::shared_ptr<openLA::dimension2::Matrix<T>> &m) noexcept {
    assert(m != nullptr);
    assert(m->m_matrix != nullptr);

    for (size_t i = 0; i < m->m_number_of_rows; i++) {
      stream << "[ ";
      for (size_t j = 0; j < m->m_number_of_columns; j++) {
        stream << m->get_element(i, j) << " ";
      }
      stream << ']' << '\n';
    }

    return stream;
  }
  friend std::ostream &operator<<(
      std::ostream &stream, const openLA::dimension2::Matrix<T> &m) noexcept {
    for (size_t i = 0; i < m.m_number_of_rows; i++) {
      stream << "[ ";
      for (size_t j = 0; j < m.m_number_of_columns; j++) {
        stream << m.get_element(i, j) << "  ";
      }
      stream << ']' << '\n';
    }
    return stream;
  }
  auto out_of_bounds(const size_t rows, const size_t columns) {
    if (rows >= this->m_number_of_rows ||
        columns >= this->m_number_of_columns) {
      throw std::invalid_argument(
          "number of row/columns out of bounds\nAborting...");
    }
  }
  friend std::shared_ptr<openLA::dimension2::Matrix<T>> operator+(
      const std::shared_ptr<openLA::dimension2::Matrix<T>> &m1,
      const std::shared_ptr<openLA::dimension2::Matrix<T>> &m2) {
    assert(m1->m_matrix != nullptr);
    assert(m2->m_matrix != nullptr);
    if (m1->m_number_of_rows != m2->m_number_of_rows &&
        m1->m_number_of_columns != m2->m_number_of_columns) {
      throw std::logic_error(
          "Number of columns/rows of Matrices are different\n");
    }
    auto result = std::make_shared<openLA::dimension2::Matrix<T>>(
        Matrix{m1->m_number_of_rows, m1->m_number_of_columns});
    for (size_t i = 0; i < result->m_total_elements; i++) {
      assert(result->m_matrix != nullptr);
      result->m_matrix[i] = m1->m_matrix[i] + m2->m_matrix[i];
    }
    return result;
  }
  friend openLA::dimension2::Matrix<T> operator+(
      const openLA::dimension2::Matrix<T> &m1,
      const openLA::dimension2::Matrix<T> &m2) {
    assert(m1.m_matrix != nullptr);
    assert(m2.m_matrix != nullptr);
    if (m1.m_number_of_rows != m2.m_number_of_rows &&
        m1.m_number_of_columns != m2.m_number_of_columns) {
      throw std::logic_error(
          "Number of columns/rows of Matrices are different\n");
    }
    auto result = openLA::dimension2::Matrix<T>(
        Matrix{m1.m_number_of_rows, m1.m_number_of_columns});
    for (size_t i = 0; i < result.m_total_elements; i++) {
      assert(result.m_matrix != nullptr);
      result.m_matrix[i] = m1.m_matrix[i] + m2.m_matrix[i];
    }
    return result;
  }
  inline void set(size_t row, size_t column, T value) {
#ifdef OPENLA_SECURITY_CHECK
    if (row >= m_number_of_rows || column >= m_number_of_columns) {
      throw std::runtime_error("Index of (set) out of bounds");
    }
#endif
    SET_AT_INDEX(this, column, row, value);
  }
  inline T get_element(const size_t row, const size_t column) const noexcept {
    return m_matrix[m_number_of_columns * row + column];
  }
#ifdef OPENLA_SECURITY_CHECK
  friend openLA::dimension2::Matrix<T> operator*=(
      openLA::dimension2::Matrix<T> &lhs,
      const openLA::dimension2::Matrix<T> &rhs) {
    assert(lhs.m_number_of_columns == rhs.m_number_of_rows);
    if (lhs.m_matrix == nullptr) {
      throw std::logic_error(
          "ERROR: First argument has a nullptr matrix\nAborting...\n");
    }
    if (rhs.m_matrix == nullptr) {
      throw std::logic_error(
          "ERROR: Second argument has a nullptr matrix\nAborting...\n");
    }
    lhs = lhs * rhs;
    return lhs;
  }
#else
  friend openLA::dimension2::Matrix<T> operator*=(
      openLA::dimension2::Matrix<T> &lhs,
      const openLA::dimension2::Matrix<T> &rhs) noexcept {
    lhs = lhs * rhs;
    return lhs;
  }
#endif
  friend openLA::dimension2::Matrix<T> operator+=(
      openLA::dimension2::Matrix<T> &lhs,
      const openLA::dimension2::Matrix<T> &rhs) noexcept {
    return (lhs = lhs + rhs);
  }
  friend openLA::dimension2::Matrix<T> operator-=(
      openLA::dimension2::Matrix<T> &lhs,
      const openLA::dimension2::Matrix<T> &rhs) noexcept {
    return (lhs = lhs - rhs);
  }
  friend std::shared_ptr<openLA::dimension2::Matrix<T>> operator*(
      const std::shared_ptr<openLA::dimension2::Matrix<T>> &m1,
      const std::shared_ptr<openLA::dimension2::Matrix<T>> &m2) {
    assert(m1->m_matrix != nullptr);
    assert(m2->m_matrix != nullptr);
    if (m1->m_number_of_columns != m2->m_number_of_rows) {
      throw std::logic_error(
          "ERROR: Number of columns/rows of Matrices are different\n");
    }
#ifdef OPENLA_SECURITY_CHECK
    if (m1->m_matrix == nullptr) {
      throw std::runtime_error(
          "ERROR: first argument is nullptr.\nAborting...\n");
    }
    if (m2->m_matrix == nullptr) {
      throw std::runtime_error(
          "ERROR: second argument is nullptr.\nAborting...\n");
    }
#endif
    auto result = std::make_shared<openLA::dimension2::Matrix<T>>(
        Matrix{m2->m_number_of_rows, m1->m_number_of_columns, 0});
    assert(result->m_matrix != nullptr);
    for (size_t x = 0; x < result->m_number_of_columns; x++) {
      for (size_t y = 0; y < result->m_number_of_rows; y++) {
        T tmp = 0;
        for (size_t i = 0; i < m1->m_number_of_columns; i++) {
          tmp += m1->get_element(y, i) * m2->get_element(i, x);
        }
        result->set(y, x, tmp);
      }
    }
    return result;
  }
  friend openLA::dimension2::Matrix<T> operator*(
      const openLA::dimension2::Matrix<T> &m1,
      const openLA::dimension2::Matrix<T> &m2) {
    assert(m1.m_matrix != nullptr);
    assert(m2.m_matrix != nullptr);
    if (m1.m_number_of_columns != m2.m_number_of_rows) {
      throw std::logic_error(
          "ERROR: Number of columns/rows of Matrices are different\n");
    }
#ifdef OPENLA_SECURITY_CHECK
    if (m1.m_matrix == nullptr) {
      throw std::runtime_error(
          "ERROR: first argument is nullptr.\nAborting...\n");
    }
    if (m2.m_matrix == nullptr) {
      throw std::runtime_error(
          "ERROR: second argument is nullptr.\nAborting...\n");
    }
#endif
    auto result = openLA::dimension2::Matrix<T>(
        Matrix{m2.m_number_of_rows, m1.m_number_of_columns, 0});
    assert(result.m_matrix != nullptr);
    usize x{}, y{}, i{};
    for (x = 0; x < result.m_number_of_columns; x++) {
      for (y = 0; y < result.m_number_of_rows; y++) {
        T tmp = 0;
        for (i = 0; i < m1.m_number_of_columns; i++) {
#ifdef OPENLA_SECURITY_CHECK
          result.out_of_bounds(y, x);
          result.out_of_bounds(y, i);
#endif
          tmp += m1.get_element(y, i) * m2.get_element(i, x);
        }
        result.set(y, x, tmp);
      }
    }
    return result;
  }

  friend bool operator==(
      const std::shared_ptr<openLA::dimension2::Matrix<T>> &m1,
      const std::shared_ptr<openLA::dimension2::Matrix<T>> &m2) noexcept {
    if (m1->m_number_of_columns != m2->m_number_of_columns &&
        m1->m_number_of_rows != m2->m_number_of_rows) {
      return false;
    }
    for (size_t x = 0; x < m1->m_number_of_columns; x++) {
      for (size_t y = 0; y < m2->m_number_of_rows; y++) {
        if (m1->get_element(y, x) != m2->get_element(y, x)) {
          return false;
        }
      }
    }
    return true;
  }

  friend bool operator==(const openLA::dimension2::Matrix<T> &lhs,
                         const openLA::dimension2::Matrix<T> &rhs) noexcept {
    if (lhs.m_number_of_rows != rhs.m_number_of_rows ||
        lhs.m_number_of_columns != rhs.m_number_of_columns) {
      return false;
    }

    for (usize x = 0; x < lhs.m_number_of_columns; x++) {
      for (usize y = 0; y < rhs.m_number_of_rows; y++) {
        if (lhs.get_element(y, x) != rhs.get_element(y, x)) {
          return false;
        }
      }
    }
    return true;
  }
#if 0
			friend bool operator == (const openLA::dimension2::Matrix<T> &lhs, const openLA::Vector<T> &rhs) noexcept
			{
				if(lhs.m_number_of_rows > 1 || lhs.m_number_of_columns != rhs.capacity())
				{
					return false;
				}
				constexpr auto y = 0;
				for(usize x = 0; x < lhs.m_number_of_columns ; x++){
					// FIXME: create a get or at function for vector
					if(lhs.get_element(y, x) != rhs.get_vector()[x]){
						return false;
					}
				}
				return true;
			}
#endif

  friend std::shared_ptr<openLA::dimension2::Matrix<T>> operator-(
      const std::shared_ptr<openLA::dimension2::Matrix<T>> &m1,
      const std::shared_ptr<openLA::dimension2::Matrix<T>> &m2) {
    assert(m1->m_matrix != nullptr);
    assert(m2->m_matrix != nullptr);
    if (m1->m_number_of_rows != m2->m_number_of_rows &&
        m1->m_number_of_columns != m2->m_number_of_columns) {
      throw std::logic_error("Number of rows and columns are different\n");
    }
    auto result = std::make_shared<openLA::dimension2::Matrix<T>>(
        Matrix{m1->m_number_of_rows, m2->m_number_of_columns, 0});
    assert(result->m_matrix != nullptr);
    for (size_t i = 0; i < result.m_total_elements; i++) {
      result->m_matrix[i] = m1->m_matrix[i] - m2->m_matrix[i];
    }
    return result;
  }
  friend openLA::dimension2::Matrix<T> operator-(
      const openLA::dimension2::Matrix<T> &m1,
      const openLA::dimension2::Matrix<T> &m2) {
    assert(m1.m_matrix != nullptr);
    assert(m2.m_matrix != nullptr);
    if (m1.m_number_of_rows != m2.m_number_of_rows &&
        m1.m_number_of_columns != m2.m_number_of_columns) {
      throw std::logic_error("Number of rows and columns are different\n");
    }
    auto result = openLA::dimension2::Matrix<T>(
        Matrix{m1.m_number_of_rows, m2.m_number_of_columns, 0});
    assert(result.m_matrix != nullptr);
    for (size_t i = 0; i < result.m_total_elements; i++) {
      result.m_matrix[i] = m1.m_matrix[i] - m2.m_matrix[i];
    }
    return result;
  }
  openLA::dimension2::Matrix<T> &random_fill(size_t range_from,
                                             size_t range_to) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<T> distribution(range_from, range_to);
    for (size_t i = 0; i < this->m_number_of_rows; i++) {
      for (size_t j = 0; j < this->m_number_of_columns; j++) {
        this->set(i, j, distribution(generator));
      }
    }
    return *this;
  }
  // bool is_close(const openLA::dimension2::Matrix<T> &n,const f32 epsilon)
  //{
  //	#ifdef OPENLA_SECURITY_CHECK
  //	if(m.m_matrix == nullptr || n.m_matrix == nullptr){
  //		throw std::invalid_argument("ERROR: trying to dereference a
  //nullptr. Aborting...");
  //	}
  //	#endif
  //	for( usize i = 0; i < m_total_elements; i++){
  //		for(usize j = 0; j < n.m_total_elements; j++){
  //			if(fabs(m_matrix[i] - n.m_matrix[j]) > epsilon){
  //				return false;
  //			}
  //		}
  //	}
  //	return true;
  // }

  openLA::dimension2::Matrix<T> transpose() {
    auto transposed_matrix =
        openLA::dimension2::Matrix<T>(m_number_of_columns, m_number_of_rows);

    for (usize y = 0; y < m_number_of_columns; y++) {
      for (usize x = 0; x < m_number_of_rows; x++) {
        auto element = get_element(x, y);
        // x , y
        transposed_matrix.set(y, x, element);
      }
    }

    return transposed_matrix;
  }
  bool is_close(openLA::dimension2::Matrix<T> &n, const f64 epsilon) {
#ifdef OPENLA_SECURITY_CHECK
    if (m_matrix == nullptr || n.m_matrix == nullptr) {
      throw std::invalid_argument(
          "ERROR: trying to dereference a nullptr. Aborting...");
    }
#endif
    for (usize i = 0; i < m_total_elements; i++) {
      for (usize j = 0; j < n.m_total_elements; j++) {
        if (fabs(m_matrix[i] - n.m_matrix[j]) > epsilon) {
          return false;
        }
      }
    }
    return true;
  }
  bool is_square()
  {
      if (m_number_of_columns == m_number_of_rows) {
        return true;
      }
      return false;
  }
  bool is_size_power_of_two()
  {
      bool rows = m_number_of_rows && !(m_number_of_rows & (m_number_of_rows - 1));
      bool cols = m_number_of_columns && !(m_number_of_columns & (m_number_of_columns - 1));
      if (rows && cols){
          return true;
      }
      return false;
  }
  Matrix<T> make_block_matrix(const Matrix<T>& M)
  {
  }
};
}  // dimension2
}  // openLA
#endif // MATRIX_HPP
