?DBG = 1
CFLAGS = -Wall  -Wextra  -std=c++17 -pedantic -march=native -Werror\
			-Wconversion -fPIC -Warray-bounds \
			-Wwrite-strings -Wno-parentheses -gdwarf-4 -funroll-loops
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
FILES = ./tests/main.cc ./include/matrix.hh ./include/vector.hh
FILES +=./include/test.hh

.PHONY: all clean run tests 

all: tests 

tests: $(FILES)
	$(CXX) $(CFLAGS) $(SRC) -o $(EXE) 


run: tests 
	./$(EXE) 

clean: 
	$(RM)  src/*.swp *.out
