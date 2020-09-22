CPPC = g++
CPP_FLAGS = -std=c++11
DATA_INC_DIR = data
KERNEL_INC_DIR = alg/kernel
LEVEL_INC_DIR = alg/level
NSEARCH_INC_DIR = alg/nsearch
ALG_INC_DIR = alg
IN_INC_DIR = in
OUT_INC_DIR = out

all : main.exe

main.exe : main.cpp
	$(CPPC) $(CPP_FLAGS) -I$(DATA_INC_DIR) -I$(KERNEL_INC_DIR) -I$(LEVEL_INC_DIR) -I$(NSEARCH_INC_DIR) -I$(ALG_INC_DIR) -I$(IN_INC_DIR) -I$(OUT_INC_DIR) main.cpp -o main.exe
    
doc:
	cd doc && $(MAKE)

clean:
	rm -rf main.exe
	cd doc && $(MAKE) clean
