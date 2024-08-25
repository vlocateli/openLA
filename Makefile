?DBG = 1
CFLAGS = -Wall  -Wextra  -std=c++17 -pedantic -march=native -Werror\
			-Wconversion  -Warray-bounds \
			-Wwrite-strings -Wno-parentheses -funroll-loops
?SAN = 1

ifeq ($(DBG),1)
CFLAGS += -ggdb -O1
else
CFLAGS += -O2 -DNDEBUG
endif 

ifeq ($(SAN),1)
CFLAGS += -fsanitize=address,undefined
endif

LD_LIBS = -lm -fopenmp
EXE = test.out
SRC = ./tests/main.cc 
INCLUDE = ./include/matrix.hh ./include/vector.hh
FILES +=./tests/test.hh

.PHONY: all clean run tests 

all: tests 

tests: $(INCLUDE) $(SRC)
	$(CXX) $(CFLAGS) $(SRC) -o $(EXE) 


run: tests 
	./$(EXE) 

clean: 
	$(RM)  src/*.swp *.out
