CPPC=g++ 
CPPC_FLAGS=-Wall -Wextra -pedantic -Ofast -march=native -fopenmp

CNSEARCH_DIR=/media/sf_Software/CompactNeighborhoodSearch
CNSEARCH_INC_DIR=$(CNSEARCH_DIR)/include
CNSEARCH_LIB_DIR=$(CNSEARCH_DIR)/lib
CNSEARCH_LIB=CompactNSearch

TEST=/media/sf_Software/CompactNSearch/src/CompactNSearch.cpp

all : test_compactnsearch.exe

test_compactnsearch.exe : test_compactnsearch.cpp
	$(CPPC) $(CPPC_FLAGS) -I$(CNSEARCH_INC_DIR) -L$(CNSEARCH_LIB_DIR) test_compactnsearch.cpp $(TEST) -o test_compactnsearch.exe -l$(CNSEARCH_LIB)

clean :
	rm -fr test_compactnsearch.exe

.PHONY: all doc clean

