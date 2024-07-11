?DEBUG = 1
CFLAGS = -Wall  -Wextra  -std=c++17 -pedantic -march=native\
			-Wconversion -fPIC -Warray-bounds -fanalyzer\
			-Wwrite-strings -Wno-parentheses -gdwarf-4 -funroll-loops
?SAN = 1
ifeq ($(DEBUG),1)
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
	$(RM)  src/*.swp *.o *.out
