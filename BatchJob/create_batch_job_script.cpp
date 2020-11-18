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

    script << "### Requested time\n#SBATCH --time=" << requestedMinutes << "\n\n";

    script << "### Requested memory needed per process in MB\n#SBATCH --mem-per-cpu=" << std::to_string(requestedMB) << "\n\n";

    script << "### Requested number of compute slots\n#SBATCH --ntasks=4\n\n";

    script << "### Change to working directory\n$PWD\n\n";

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
           << "\ncompactSupport=" << std::to_string(compactSupport)
           << "\nopenMPThreads=" << std::to_string(openMPThreads) << "\n\n";

    script << "### Execute the application\n./surfaceReconstructin.exe "
           << "inputFileFormat $outputFileFormat $neighborhoodSearch $kernelFunction $levelFunction $reconstructionMethod "
           << "$inputFolder $outputFolder $smoothingLength $compactSupport $openMPThreads";
}
