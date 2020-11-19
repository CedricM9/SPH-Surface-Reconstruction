#include <fstream>
#include <string>

void create_script(std::string filename,
                   std::string inputFileFormat, std::string outputFileFormat,
                   std::string neighborhoodSearch, std::string kernelFunction, std::string levelFunction, std::string reconstructionMethod,
                   std::string inputFolder, std::string outputFolder,
                   float smoothingLength, float compactSupport, int openMPThreads,
                   int requestedMinutes, int requestedMB) {
    std::ofstream script;
    script.open(filename);

    script << "#!/usr/local_rwth/bin/zsh\n\n";

    script << "### Job name\n#SBATCH --job-name=surfaceReconstruction\n\n";

    script << "### File / path where STDOUT & STDERR will be written\n### %J is the job ID\n#SBATCH --output=surfaceReconstruction.%J.log\n\n";

    script << "### Requested time\n#SBATCH --time=00:" << requestedMinutes << ":00\n\n";

    script << "### Requested memory needed per process in MB\n#SBATCH --mem-per-cpu=" << std::to_string(requestedMB) << "\n\n";

    script << "### Requested number of compute slots\n#SBATCH --cpus-per-task=" << std::to_string(openMPThreads) << "\n\n";

    script << "### Set the number of threads in the cluster environment as specified above\nexport OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK\n\n";

    script << "### Load a gcc compiler supporting C++17\nmodule load gcc/8\n\n";

    script << "### Create necessary variables\n" 
           << "inputFileFormat=" << inputFileFormat
           << "\noutputFileFormat=" << outputFileFormat
           << "\n\nneighborhoodSearch=" << neighborhoodSearch
           << "\nkernelFunction=" << kernelFunction
           << "\nlevelFunction=" << levelFunction
           << "\nreconstructionMethod=" << reconstructionMethod
           << "\n\ninputFolder=" << inputFolder
           << "\noutputFolder=" << outputFolder
           << "\n\nsmoothingLength=" << std::to_string(smoothingLength)
           << "\ncompactSupport=" << std::to_string(compactSupport) << "\n\n";

    script << "### Execute the application\n./surfaceReconstruction.exe "
           << "inputFileFormat $outputFileFormat $neighborhoodSearch $kernelFunction $levelFunction $reconstructionMethod "
           << "$inputFolder $outputFolder $smoothingLength $compactSupport";
}
