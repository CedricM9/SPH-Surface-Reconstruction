# SPH-Surface-Reconstruction
This software was co-developed by Cedric Maume, [Corinna Muller](https://github.com/cm314), and [Henrik Muller](https://github.com/HKMueller) as a part of our Computational Engineering Science B.S degree at the RWTH Aachen.

---
### Features 
The purpose of the software is to construct a mesh over an SPH fluid simulation by way of the Marching Cubes Algorithm. The process can be executed either through the implemented GUI or by utilizing a batch job. 
The software includes a fully functioning GUI that was created using Qt. It enables not only the reconstruction through the interface, but also includes a viewport with which one can view the simulation data or the resultant mesh. The ability to generate a batch job for the RWTH Compute Cluster is also present, and the parameters for it can be set in the interface itself

The software is not very runtime efficient given too many particles or with a very high gridcell resolution. The memory usage is incredibly low and should therefore run on any computer. There is a lot of headroom for optimization in order to generate more detailed meshes.

##### Supported File Formats
- VTK
- PLY
- BGEO

---
### Back End Compilation
1. Install all required software following the owner's instructions:
- CompactNSearch: https://github.com/InteractiveComputerGraphics/CompactNSearch
- Partio: https://github.com/wdas/partio
- happly: https://github.com/nmwsharp/happly
- OpenMesh: https://graphics.rwth-aachen.de:9000/OpenMesh/OpenMesh
2. Clone the GitHub repository: 
```bash
git clone https://github.com/CedricM9/SPH-Surface-Reconstruction.git
```
3. Change to the BackEndCompilation folder: 
```bash
cd BackEndCompilation
```
4. Set all necessary environment variables for the third-party software:
```bash
export CNSEARCH_DIR = <main directory of the CompactNSearch installation>
export PARTIO_DIR = <main directory of the partio installation>
export HAPPLY_DIR = <directory containing happly.h>
export OMESH_DIR = <main directory of the OpenMesh installation>
```
5. Build* the example main file using make:
```bash
make
```
6. Take care that all dynamic library paths are set:
```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<main directory of the partio installation>/lib/:
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<main directory of the OpenMesh installation>/lib/:
```
7. Execute the example: 
```bash
./main.exe
```
8. Make changes in the main.cpp for your concerns. <br>
<br>
*If the linker returns the message "cannot find -lCompactNSearch" try adding the file CompactNSearch.cpp from the src folder of the CompactNSearch repository to the Makefile to   be compiled along with main.cpp instead of linking to -l$(CNSEARCH_LIB).

---
### Documentation using doxygen
1. Clone the GitHub repository: 
```bash
git clone https://github.com/CedricM9/SPH-Surface-Reconstruction.git
```
2. Change to the source code folder: 
```bash
cd LabProject/SurfaceReconstruction/doc
```
3. Generate the documentation: 
```bash
make doc
```
4. Open the documentation: 
```bash
open html/files.html
```

---
### Batch Job Submission
1. Set all parameters in the GUI that should be used for the batch job.
2. Click on Generate batch script in the GUI.
3. Enter the run-time in minutes and the requested memory in MB according to the prompts.
4. Clone the Github repository on the RWTH Compute Cluster: 
```bash
git clone https://github.com/CedricM9/SPH-Surface-Reconstruction.git
```
5. Change to the BatchJob directory: 
```bash
cd BatchJob
```
6. Build the executable using make:
```bash
make
```
7. Copy the batch job script generated by the GUI and the executable surfaceReconstruction.exe to the same folder and change to this folder.
8. Check in the batch job script if input and output folder are correct for the compute cluster and adjust them if necessary.
9. Submit the job:
```bash
sbatch < <batch script filename>
```
