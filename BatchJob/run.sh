#!/bin/bash

input_file_format=vtk
output_file_format=vtk

nsearch=spatialHashing
kernel=cubicSpline
level=dimensionless
reconstruction=marchingCubes

input_folder=/media/sf_Software_Lab/newd/test_input
output_folder=/media/sf_Software_Lab/newd/test_output

smoothing_length=0.028
compact_support=0.4

export OMP_NUM_THREADS=4

./surfaceReconstruction.exe $input_file_format $output_file_format $nsearch $kernel $level $reconstruction $input_folder $output_folder $smoothing_length $compact_support
