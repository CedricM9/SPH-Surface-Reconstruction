CPPC = g++
CPP_FLAGS = -std=c++17 -lstdc++fs -lz -fopenmp

MAIN_DIR = ../CodeStructureIdea
DATA_INC_DIR = $(MAIN_DIR)/data
KERNEL_INC_DIR = $(MAIN_DIR)/alg/kernel
LEVEL_INC_DIR = $(MAIN_DIR)/alg/level
NSEARCH_INC_DIR = $(MAIN_DIR)/alg/nsearch
POST_INC_DIR = $(MAIN_DIR)/alg/post
ALG_INC_DIR = $(MAIN_DIR)/alg
IN_INC_DIR = $(MAIN_DIR)/in
OUT_INC_DIR = $(MAIN_DIR)/out

CNSEARCH_DIR=/media/sf_Software/CompactNeighborhoodSearch
CNSEARCH_INC_DIR=$(CNSEARCH_DIR)/include
CNSEARCH_LIB_DIR=$(CNSEARCH_DIR)/lib
CNSEARCH_LIB=CompactNSearch

EIGEN_DIR=/media/sf_Software/Eigen

PARTIO_INC_DIR=/media/sf_Software_Lab/newd/SPH-Surface-Reconstruction/LabProject/surfrec_io/extern/partio/src/lib
#PARTIO_DIR=/media/sf_Software/partio
#PARTIO_INC_DIR=$(PARTIO_DIR)/include
#PARTIO_LIB_DIR=$(PARTIO_DIR)/lib
#PARTIO_LIB=$(PARTIO_LIB_DIR)/libpartio.so

VTKIO_DIR=/media/sf_Software/vtkio
VTKIO_INC_DIR=$(VTKIO_DIR)

HAPPLY_INC_DIR=/media/sf_Software/happly

OMESH_DIR=/home/corinna/OpenMesh
OMESH_DIR_C=/home/corinna/openmesh
OMESH_INC_DIR=$(OMESH_DIR_C)/include
OMESH_LIB_DIR=$(OMESH_DIR_C)/lib
OMESH_CORE_LIB=OpenMeshCore
OMESH_TOOLS_LIB=OpenMeshTools

TEST=/media/sf_Software/CompactNSearch/src/CompactNSearch.cpp

PARTIO_IO=$(wildcard $(PARTIO_INC_DIR)/io/*.cpp)
PARTIO_CORE=$(wildcard $(PARTIO_INC_DIR)/core/*.cpp)
TEST2=$(PARTIO_IO) $(PARTIO_CORE) -lz

OM_MESH=$(wildcard $(OMESH_DIR)/Core/Mesh/*.cc)
TEST3=$(OM_MESH)

all : surfaceReconstruction.exe

surfaceReconstruction.exe : surfaceReconstruction.cpp
	$(CPPC) $(CPP_FLAGS) -I$(DATA_INC_DIR) -I$(KERNEL_INC_DIR) -I$(LEVEL_INC_DIR) -I$(NSEARCH_INC_DIR) -I$(POST_INC_DIR) -I$(ALG_INC_DIR) -I$(IN_INC_DIR) -I$(OUT_INC_DIR) -I$(CNSEARCH_INC_DIR) -I$(EIGEN_DIR) -I$(PARTIO_INC_DIR) -I$(VTKIO_DIR) -I$(HAPPLY_INC_DIR) -I$(OMESH_INC_DIR) surfaceReconstruction.cpp $(TEST) $(TEST3) $(TEST2) -lstdc++fs -o surfaceReconstruction.exe
    
doc:
	cd doc && $(MAKE)

clean:
	rm -rf surfaceReconstruction.exe
