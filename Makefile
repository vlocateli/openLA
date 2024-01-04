?DEBUG = 1
CXX_FLAGS = -Wall  -Wextra  -std=c++17 -pedantic -march=native\
			-Wconversion -fPIC -Warray-bounds -fanalyzer\
			-Wwrite-strings -Wno-parentheses -gdwarf-4 -funroll-loops

ifeq ($(DEBUG),1)
CXX_FLAGS += -ggdb -fsanitize=address,undefined -O1
else
CXX_FLAGS += -O2 -DNDEBUG
endif 

LD_LIBS = -lm -fopenmp
EXE = test.out
SRC_FILES = ./tests/main.cc 
FILES = ./tests/main.cc ./include/matrix.hh ./include/vector.hh
FILES +=./include/test.hh

.PHONY: all clean run tests 

all: tests 

tests: $(FILES)
	$(CXX) $(CXX_FLAGS) $(SRC_FILES) -o $(EXE) 


run: tests 
	./$(EXE) 

clean: 
	$(RM)  src/*.swp *.o *.out error.txt
