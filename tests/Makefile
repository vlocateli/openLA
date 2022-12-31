CXX_FLAGS =  -ggdb -Wall  -Wextra  -pedantic -std=c++17 -march=native   -O2
CXX_FLAGS += -fsanitize=address,undefined
FILES = test.cc 
LD_LIBS = -lm
EXE = test.out

all: test.cc ../include/matrix.hpp
	$(CXX) $(CXX_FLAGS) $(FILES) -o $(EXE)
