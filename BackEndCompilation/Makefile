CPPC = g++
CPP_FLAGS = -std=c++17 -fopenmp

SRC_DIR = ../LabProject/SurfaceReconstruction
DATA_INC_DIR    = $(SRC_DIR)/data
KERNEL_INC_DIR  = $(SRC_DIR)/alg/kernel
LEVEL_INC_DIR   = $(SRC_DIR)/alg/level
NSEARCH_INC_DIR = $(SRC_DIR)/alg/nsearch
POST_INC_DIR    = $(SRC_DIR)/alg/post
ALG_INC_DIR     = $(SRC_DIR)/alg
IN_INC_DIR      = $(SRC_DIR)/in
OUT_INC_DIR     = $(SRC_DIR)/out
INC_DIRS        = -I$(DATA_INC_DIR) -I$(KERNEL_INC_DIR) -I$(LEVEL_INC_DIR) -I$(NSEARCH_INC_DIR) -I$(POST_INC_DIR) -I$(ALG_INC_DIR) -I$(IN_INC_DIR) -I$(OUT_INC_DIR)

# environment variable CNSEARCH_DIR has to be set to main directory of the CompactNSearch installation
CNSEARCH_INC_DIR=$(CNSEARCH_DIR)/include
CNSEARCH_LIB_DIR=$(CNSEARCH_DIR)/lib
CNSEARCH_LIB=CompactNSearch

# environment variable PARTIO_DIR has to be set to main directory of the partio installation
PARTIO_INC_DIR=$(PARTIO_DIR)/include
PARTIO_LIB_DIR=$(PARTIO_DIR)/lib
PARTIO_LIB=$(PARTIO_LIB_DIR)/libpartio.so

VTKIO_DIR=../LabProject/External/surfrec_io/extern/vtkio
VTKIO_INC_DIR=$(VTKIO_DIR)

# environment variable HAPPLY_DIR has to be set to the directory containing happly.h
HAPPLY_INC_DIR=$(HAPPLY_DIR)

# environment variable OMESH_DIR has to be set to main directory of the OpenMesh installation
OMESH_INC_DIR=$(OMESH_DIR)/include
OMESH_LIB_DIR=$(OMESH_DIR)/lib
OMESH_CORE_LIB=OpenMeshCore
OMESH_TOOLS_LIB=OpenMeshTools

all : main.exe

main.exe : main.cpp
	$(CPPC) $(CPP_FLAGS) $(INC_DIRS) -I$(CNSEARCH_INC_DIR) -I$(PARTIO_INC_DIR) -I$(VTKIO_DIR) -I$(HAPPLY_INC_DIR) -I$(OMESH_INC_DIR) -L$(PARTIO_LIB_DIR) -L$(OMESH_LIB_DIR) main.cpp -o main.exe $(PARTIO_LIB) -l$(OMESH_CORE_LIB) -l$(OMESH_TOOLS_LIB) -l$(CNSEARCH_LIB)
    
doc:
	cd $(SRC_DIR)/doc && $(MAKE)

clean:
	rm -rf main.exe
	cd $(SRC_DIR)/doc && $(MAKE) clean
