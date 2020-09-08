CPPC=g++ 
CPPC_FLAGS=-Wall -Wextra -pedantic -Ofast -march=native

PARTIO_DIR=/media/sf_Software/partio
PARTIO_INC_DIR=$(PARTIO_DIR)/include
PARTIO_LIB_DIR=$(PARTIO_DIR)/lib
PARTIO_LIB=$(PARTIO_LIB_DIR)/libpartio.so

HAPPLY_INC_DIR=/media/sf_Software/happly

all : test_partio.exe test_happly.exe

test_partio.exe : test_partio.cpp
	$(CPPC) $(CPPC_FLAGS) -I$(PARTIO_INC_DIR) -L$(PARTIO_LIB_DIR) test_partio.cpp -o test_partio.exe $(PARTIO_LIB)

test_happly.exe : test_happly.cpp
	$(CPPC) $(CPPC_FLAGS) -I$(HAPPLY_INC_DIR) test_happly.cpp -o test_happly.exe
clean :
	rm -fr test_happly.exe test_partio.exe my_output_file.ply

.PHONY: all doc clean

