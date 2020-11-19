#!/usr/local_rwth/bin/zsh

### Job name
#SBATCH --job-name=surfaceReconstruction

### File / path where STDOUT & STDERR will be written
### %J is the job ID
#SBATCH --output=surfaceReconstruction.%J.log

### Requested time
#SBATCH --time=00:60:00

### Requested memory needed per process in MB
#SBATCH --mem-per-cpu=512

### Requested number of compute slots
#SBATCH --cpus-per-task=4

### Set the number of threads in the cluster environment as specified above
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

### Load a gcc compiler supporting C++17
module load gcc/8

### Create necessary variables
inputFileFormat=vtk
outputFileFormat=vtk

neighborhoodSearch=spatialHashing
kernelFunction=cubicSpline
levelFunction=dimensionless
reconstructionMethod=marchingCubes

inputFolder=/media/sf_Software_Lab/newd/test_input
outputFolder=/media/sf_Software_Lab/newd/test_output

smoothingLength=0.028000
compactSupport=0.400000

### Execute the application
./surfaceReconstruction.exe inputFileFormat $outputFileFormat $neighborhoodSearch $kernelFunction $levelFunction $reconstructionMethod $inputFolder $outputFolder $smoothingLength $compactSupport