#ifndef TEST_HH
#define TEST_HH
#include <chrono>
#include <iostream>

#include "../include/matrix.hh"
#include "../include/vector.hh"
#if __cplusplus <= 199711L
#error This library needs at least a C++11 compliant compiler
#endif
static constexpr usize SIZE{1024};
namespace vector {
void test_vector_c1() {
  openLA::Vector<usize> v1;
  openLA::Vector<usize> v2(SIZE);
  assert(v1.size() == 0);
  assert(v2.size() == SIZE);
}
void test_vector_resize() {
  openLA::Vector<usize> v1;
  v1.resize(10);
  assert(v1.size() == 10);
  openLA::Vector<usize> v2(20);
  for (usize i = 0; i < 20; i++) {
    v2[i] = i;
  }
  std::cout << v2 << '\n';
  v2.resize(22);
  std::cout << v2 << '\n';
  v2.resize(10);
  std::cout << v2 << '\n';
}
void test_vector_add() {
  openLA::Vector<usize> v1(10, 1);
  openLA::Vector<usize> v2(10, 2);
  std::cout << v1 + v2 << '\n';
}
void test_vector_sub() {
  openLA::Vector<usize> v1(10, 2);
  openLA::Vector<usize> v2(10, 2);
  std::cout << v1 - v2 << '\n';
}
void test_vector_mul() {
  openLA::Vector<usize> v1(10, 2);
  openLA::Vector<usize> v2(10, 2);
  std::cout << v1 * v2 << '\n';
}
void test_vector_move_constructor() {
    openLA::Vector<usize> v1(10,2);
    openLA::Vector<usize> v2(std::move(v1));
}
#if 0
void test_iterators() {
    openLA::Vector<usize> v(10,2);
    for(auto i = v.begin(); i != v.end(); i++) {
    
    }
}
#endif
}  // namespace vector
namespace matrix {
void test_matrix1() {
  openLA::dimension2::Matrix<usize> m1(3, 3, 0);
  std::cout << "m1\n";
  std::cout << m1 << "\n";
}

void test_matrix2() {
  openLA::dimension2::Matrix<usize> m1(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
  openLA::dimension2::Matrix<usize> m2(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});

  std::cout << "m1\n";
  std::cout << m1 << '\n';
  std::cout << "m2\n";
  std::cout << m2 << '\n';
  std::cout << "testing operator +\n";
  std::cout << m1 + m2 << '\n';
  std::cout << "testing operator -\n";
  std::cout << m1 - m2 << '\n';
  std::cout << "testing operator *\n";
  std::cout << m1 * m2 << '\n';
}

void test_matrix3() {
  using namespace openLA::dimension2;
  static constexpr auto ROWS = 1024;
  static constexpr auto COLUMNS = 1024;
  using T = usize;
  Matrix<T> m(ROWS, COLUMNS);
  Matrix<T> n(ROWS, COLUMNS);
  static constexpr auto MIN{1024};
  static constexpr auto MAX{2048};
  m.random_fill(MIN, MAX);
  n.random_fill(MIN, MAX);
  const auto start = std::chrono::steady_clock::now();
  const auto r1 = m * n;
  const auto end = std::chrono::steady_clock::now();
  const std::chrono::duration<f64> elapsed_seconds = end - start;
  std::cout << "elapsed time " << elapsed_seconds.count() << "s" << '\n';
}
void test_is_close1() {
  using namespace openLA::dimension2;
  using T = s32;
  static constexpr usize ROWS = 1;
  static constexpr usize COLUMNS = 5;
  static constexpr auto EPSILON_D = 0.008;
  static constexpr auto EPSILON_F = 0.008f;
  Matrix<T> m(ROWS, COLUMNS, {1, 2, 3, 4, 5});
  Matrix<T> n(ROWS, COLUMNS, {10, 20, 30, 40, 50});
  T tmp;
  (void)tmp;
  if (m.is_close(n, EPSILON_D)) {
    std::cout << "m is close matrix n\nDOUBLE\n";
  } else {
    std::cout << "m is not close matrix n\nDOUBLE\n";
  }
  if (m.is_close(n, EPSILON_F)) {
    std::cout << "m is close to matrix n\nFLOAT\n";
  } else {
    std::cout << "m is not close matrix n\nFLOAT\n";
  }
}

void test_is_close2() {
  using namespace openLA::dimension2;
  using T = s32;
  static constexpr usize ROWS = 1;
  static constexpr usize COLUMNS = 5;
  static constexpr auto EPSILON_D = 100.5;
  static constexpr auto EPSILON_F = 100.5f;
  Matrix<T> m(ROWS, COLUMNS, {1, 2, 3, 4, 5});
  Matrix<T> n(ROWS, COLUMNS, {10, 20, 30, 40, 50});
  T tmp;
  (void)tmp;
  if (m.is_close(n, EPSILON_D)) {
    std::cout << "m is close matrix n\nDOUBLE\n";
  } else {
    std::cout << "m is not close matrix n\nDOUBLE\n";
  }
  if (m.is_close(n, EPSILON_F)) {
    std::cout << "m is close to matrix n\n FLOAT\n";
  } else {
    std::cout << "m is not close matrix n\nFLOAT\n";
  }
}
void test_operator_is_equal() {
  using namespace openLA::dimension2;
  using T = s32;
  static constexpr usize ROWS = 1;
  static constexpr usize COLUMNS = 5;
  Matrix<T> m(ROWS, COLUMNS, {1, 2, 3, 4, 5});
  Matrix<T> n(ROWS, COLUMNS, {1, 2, 3, 4, 5});
  // assert(m == v);
  assert(m == n);
}

void test_operator_is_equal2() {
  using namespace openLA::dimension2;
  using T = s32;
  static constexpr usize ROWS = 2;
  static constexpr usize COLUMNS = 5;
  Matrix<T> m(ROWS, COLUMNS, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  Matrix<T> n(ROWS, COLUMNS, {1, 2, 3, 4, 5, 7, 8, 9, 10});
  // assert(m == v);
  // assert(m == n );
}
void test_operator_times_equal1() {
  using namespace openLA::dimension2;
  using T = s32;
  static constexpr usize ROWS = 2;
  static constexpr usize COLUMNS = 2;
  Matrix<T> m(ROWS, COLUMNS, {1, 2, 3, 4});
  Matrix<T> n(ROWS, COLUMNS, {1, 2, 3, 4});
  // openLA::Vector<T> v(5,{1,2,3,4,5});
  m *= n;
  std::cout << "m\n";
  std::cout << m << '\n';
}
void test_operator_plus_equals() {
  using namespace openLA::dimension2;
  using T = s32;
  static constexpr usize ROWS = 2;
  static constexpr usize COLUMNS = 2;
  Matrix<T> m(ROWS, COLUMNS, {1, 2, 3, 4});
  Matrix<T> n(ROWS, COLUMNS, {1, 2, 3, 4});
  // openLA::Vector<T> v(5,{1,2,3,4,5});
  m += n;
  std::cout << "m\n";
  std::cout << m << '\n';
}
void test_operator_minus_equals() {
  using namespace openLA::dimension2;
  using T = s32;
  static constexpr usize ROWS = 2;
  static constexpr usize COLUMNS = 2;
  Matrix<T> m(ROWS, COLUMNS, {1, 2, 3, 4});
  Matrix<T> n(ROWS, COLUMNS, {1, 2, 3, 4});
  // openLA::Vector<T> v(5,{1,2,3,4,5});
  m -= n;
  std::cout << "m\n";
  std::cout << m << '\n';
}
void test_transpose1() {
  using namespace openLA::dimension2;
  using T = s32;
  static constexpr usize ROWS = 2;
  static constexpr usize COLUMNS = 2;
  Matrix<T> m(ROWS, COLUMNS, {1, 2, 3, 4});
  Matrix<T> n(ROWS, COLUMNS, {1, 2, 3, 4});
  auto M_T = m.transpose();
  std::cout << "m\n";
  std::cout << m << '\n';
  std::cout << "m transpose\n";
  std::cout << M_T << '\n';
  M_T = M_T.transpose();
  std::cout << "m transposed transposed\n";
  std::cout << M_T << '\n';
}
void test_transpose2() {
  using namespace openLA::dimension2;
  using T = s32;
  static constexpr usize ROWS = 2;
  static constexpr usize COLUMNS = 5;
  Matrix<T> m(ROWS, COLUMNS, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  std::cout << "original m\n";
  std::cout << m << '\n';
  std::cout << "m transposed\n";
  m = m.transpose();
  std::cout << m << '\n';
  std::cout << "m transposed transposed\n";
  m = m.transpose();
  std::cout << m << '\n';
}
void test_transpose3() {
  using namespace openLA::dimension2;
  using T = s32;
  static constexpr usize ROWS = 3;
  static constexpr usize COLUMNS = 5;
  Matrix<T> m(ROWS, COLUMNS,
              {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
  std::cout << "original m\n";
  std::cout << m << '\n';
  auto original_matrix = m;
  std::cout << "m transposed\n";
  m = m.transpose();
  std::cout << m << '\n';
  std::cout << "m transposed transposed\n";
  m = m.transpose();
  std::cout << m << '\n';
  assert(m == original_matrix);
}

void test_is_power_of_two()
{
    using namespace openLA::dimension2;
    Matrix<int> M(4,4);
    if (!M.is_size_power_of_two()) {
        std::cerr << "Algorithm wrong\n";
    }
    Matrix<int> m(0,0);
    if (m.is_size_power_of_two()) {
        std::cerr << "Algorithm wrong\n";
    }
}
}  // namespace matrix

void run_tests() {
  matrix::test_matrix1();
  matrix::test_matrix2();
  matrix::test_matrix3();
  matrix::test_is_close1();
  matrix::test_is_close2();
  matrix::test_operator_is_equal();
  matrix::test_operator_is_equal2();
  matrix::test_operator_times_equal1();
  matrix::test_operator_plus_equals();
  matrix::test_operator_minus_equals();
  matrix::test_transpose1();
  matrix::test_transpose2();
  matrix::test_transpose3();
  matrix::test_is_power_of_two();
#if 0
  vector::test_vector_c1();
  vector::test_vector_resize();
  vector::test_vector_add();
  vector::test_vector_sub();
  vector::test_vector_mul();
  vector::test_vector_move_constructor();
#endif
}
#endif  // TEST_HH
