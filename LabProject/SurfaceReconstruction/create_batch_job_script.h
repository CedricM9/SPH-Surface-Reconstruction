#ifndef CREATE_BATCH_JOB_SCRIPT_H
#define CREATE_BATCH_JOB_SCRIPT_H
#include <string>

void create_script(std::string filename,
                   std::string inputFileFormat, std::string outputFileFormat,
                   std::string neighborhoodSearch, std::string kernelFunction, std::string levelFunction, std::string reconstructionMethod,
                   std::string inputFolder, std::string outputFolder,
                   float smoothingLength, float compactSupport, float isoValue, int numCellsInLargestAxis,
                   int openMPThreads, int requestedMinutes, int requestedMB);

#include "create_batch_job_script.cpp"

#endif // CREATE_BATCH_JOB_SCRIPT_H
