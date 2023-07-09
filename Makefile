
CXX_FLAGS =   -Wall  -Wextra  -pedantic -std=c++17 -march=native -Werror  -O2
LD_LIBS = -lm
EXE = test.out
SRC_FILES = ./tests/main.cc 
FILES = ./tests/main.cc ./include/matrix.hpp ./include/vector.hh 
FILES +=./include/test.hh

.PHONY: all

all: tests 

tests: $(FILES)
	$(CXX) $(CXX_FLAGS) $(SRC_FILES) -o $(EXE) 


run: tests 
	./$(EXE) 

debug: CXX_FLAGS += -ggdb -fsanitize=address,undefined -O1
	

debug: tests 

.PHONY: clean 

clean: 
	$(RM)  *.o *.out 
