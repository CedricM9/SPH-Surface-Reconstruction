CPPC = g++
CPP_FLAGS = -std=c++17 -lstdc++fs -lz -fopenmp

MAIN_DIR = ../CodeStructureIdea
QT_DIR=../LabProject

DATA_INC_DIR = $(MAIN_DIR)/data
KERNEL_INC_DIR = $(MAIN_DIR)/alg/kernel
LEVEL_INC_DIR = $(MAIN_DIR)/alg/level
NSEARCH_INC_DIR = $(MAIN_DIR)/alg/nsearch
POST_INC_DIR = $(MAIN_DIR)/alg/post
ALG_INC_DIR = $(MAIN_DIR)/alg
IN_INC_DIR = $(MAIN_DIR)/in
OUT_INC_DIR = $(MAIN_DIR)/out

CNSEARCH_DIR=$(QT_DIR)/CompactNSearch
CNSEARCH_INC_DIR=$(CNSEARCH_DIR)/include

EXTERN_DIR=$(QT_DIR)/surfrec_io/extern
PARTIO_INC_DIR=$(EXTERN_DIR)/partio/src/lib
VTKIO_INC_DIR=$(EXTERN_DIR)/vtkio
HAPPLY_INC_DIR=$(EXTERN_DIR)

OMESH_DIR=$(QT_DIR)/OpenMesh
OMESH_INC_DIR=$(QT_DIR)

CNSEARCH_SRC=$(CNSEARCH_DIR)/src/CompactNSearch.cpp

PARTIO_IO=$(wildcard $(PARTIO_INC_DIR)/io/*.cpp)
PARTIO_CORE=$(wildcard $(PARTIO_INC_DIR)/core/*.cpp)
PARTIO_SRC=$(PARTIO_IO) $(PARTIO_CORE)

OM_IO=$(wildcard $(OMESH_DIR)/Core/IO/*.cc)
OM_READER=$(wildcard $(OMESH_DIR)/Core/IO/reader/*.cc)
OM_WRITER=$(wildcard $(OMESH_DIR)/Core/IO/writer/*.cc)
OM_MESH=$(wildcard $(OMESH_DIR)/Core/Mesh/*.cc)
OM_SYSTEM=$(wildcard $(OMESH_DIR)/Core/System/*.cc)
OM_UTILS=$(wildcard $(OMESH_DIR)/Core/Utils/*.cc)
OM_DECIMATER=$(wildcard $(OMESH_DIR)/Tools/Decimater/*.cc)
OMESH_SRC=$(OM_IO) $(OM_READER) $(OM_WRITER) $(OM_MESH) $(OM_SYSTEM) $(OM_UTILS) $(OM_DECIMATER)

all : surfaceReconstruction.exe

surfaceReconstruction.exe : surfaceReconstruction.cpp
	$(CPPC) -I$(DATA_INC_DIR) -I$(KERNEL_INC_DIR) -I$(LEVEL_INC_DIR) -I$(NSEARCH_INC_DIR) -I$(POST_INC_DIR) -I$(ALG_INC_DIR) -I$(IN_INC_DIR) -I$(OUT_INC_DIR) -I$(CNSEARCH_INC_DIR) -I$(PARTIO_INC_DIR) -I$(VTKIO_INC_DIR) -I$(HAPPLY_INC_DIR) -I$(OMESH_INC_DIR) surfaceReconstruction.cpp $(CNSEARCH_SRC) $(PARTIO_SRC) $(OMESH_SRC) $(CPP_FLAGS) -o surfaceReconstruction.exe
    
doc:
	cd doc && $(MAKE)

clean:
	rm -rf surfaceReconstruction.exe
