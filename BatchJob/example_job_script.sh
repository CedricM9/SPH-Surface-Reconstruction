#!/usr/local_rwth/bin/zsh

### Job name
#SBATCH --job-name=surfaceReconstruction

### File / path where STDOUT & STDERR will be written
### %J is the job ID
#SBATCH --output=surfaceReconstruction.%J.log

### Requested time
#SBATCH --time=1:00

### Requested memory needed per process in MB
#SBATCH --mem-per-cpu=512

### Requested number of compute slots
#SBATCH --ntasks=4

### Change to working directory
$PWD

### Execute the application
./surfaceReconstructin.exe 2 3 4
