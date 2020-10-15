graph marchingCubesReconstructor::createGrid(
    const particleList& particles,
    const int accuracy
)   {

    assert(accuracy > 0 && accuracy <= 10);    
        
    float smallestX, largestX, smallestY, largestY, smallestZ, largestZ = 0.0;
    
    for(int i=0; i<particles.getNumberOfParticles(); i+=accuracy) {
        if(particles.getParticle(i).x() < smallestX) {smallestX = particles.getParticle(i).x();}
        if(particles.getParticle(i).x() > largestX)  {largestX = particles.getParticle(i).x();}

        if(particles.getParticle(i).y() < smallestY) {smallestY = particles.getParticle(i).y();}
        if(particles.getParticle(i).y() > largestY)  {largestY = particles.getParticle(i).y();}

        if(particles.getParticle(i).z() < smallestZ) {smallestZ = particles.getParticle(i).z();}
        if(particles.getParticle(i).z() > largestZ)  {largestZ = particles.getParticle(i).z();}

    }
    
    float largestSide = largestX - smallestX;
    if((largestY - smallestY) > largestSide) {largestSide = largestY - smallestY;}
    if((largestZ - smallestZ) > largestSide) {largestSide = largestZ - smallestZ;}

    graph g(smallestX, largestX, smallestY, largestY, smallestZ, largestZ);
    g.adjustCellSize(largestSide / (100 + (accuracy*10)));
    
    return g;
}
    




triangleList marchingCubesReconstructor::reconstruct(
  const graph& g,
  const particleList& particles,
  std::shared_ptr<levelSetFunction> levelSetPointer,
  std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
  std::shared_ptr<SPHInterpolationKernel> kernelPointer
) {

    // Format [x][y][z]
    float sliceISO[g.numCells(0)][g.numCells(1)][8];
    int isoValue = 0;
    bool firstSlice = false;

    //g.numCells-1 ???
    // SAVE RAM BY NOT SAVING ALL VERTICES BUT ONLY 4
    for(int m=1; m<g.numCells(2); m++) {
        for(int i=0; i<g.numCells(1); i++){
            for(int j=0; j<g.numCells(0); j++) {
                if(!firstSlice) {
                    sliceISO[j][i][0] = calculateISO(g.xMin+(j*g.cellSize()), g.yMin+(i*g.cellSize()), g.zMin);
                    sliceISO[j][i][1] = calculateISo(g.xMin+(j*g.cellSize())+g.cellSize(), g.yMin+(i*g.cellSize()), g.zMin);
                    sliceISO[j][i][2] = calculateISO(g.xMin+(j*g.cellSize())+g.cellSize(), g.yMin+(i*g.cellSize())+g.cellSize(), g.zMin);
                    sliceISO[j][i][3] = calculateISO(g.xMin+(j*g.cellSize()), g.yMin+(i*g.cellSize())+g.cellSize(), g.zMin);
                    sliceISO[j][i][4] = calculateISO(g.xMin+(j*g.cellSize()), g.yMin+(i*g.cellSize()), g.zMin+g.cellSize());
                    sliceISO[j][i][5] = calculateISo(g.xMin+(j*g.cellSize())+g.cellSize(), g.yMin+(i*g.cellSize()), g.zMin+g.cellSize());
                    sliceISO[j][i][6] = calculateISO(g.xMin+(j*g.cellSize())+g.cellSize(), g.yMin+(i*g.cellSize())+g.cellSize(), g.zMin+g.cellSize());
                    sliceISO[j][i][7] = calculateISO(g.xMin+(j*g.cellSize()), g.yMin+(i*g.cellSize())+g.cellSize(), g.zMin+g.cellSize());
                } else {
                    sliceISO[j][i][0] = sliceISO[j][i][4];
                    sliceISO[j][i][1] = sliceISO[j][i][5];
                    sliceISO[j][i][2] = sliceISO[j][i][6];
                    sliceISO[j][i][3] = sliceISO[j][i][7];
                    sliceISO[j][i][4] = calculateISO(g.xMin+(j*g.cellSize()), g.yMin+(i*g.cellSize()), g.zMin+(m*g.cellSize())+g.cellSize());
                    sliceISO[j][i][5] = calculateISo(g.xMin+(j*g.cellSize())+g.cellSize(), g.yMin+(i*g.cellSize()), g.zMin+(m*g.cellSize())+g.cellSize());
                    sliceISO[j][i][6] = calculateISO(g.xMin+(j*g.cellSize())+g.cellSize(), g.yMin+(i*g.cellSize())+g.cellSize(), g.zMin+(m*g.cellSize())+g.cellSize());
                    sliceISO[j][i][7] = calculateISO(g.xMin+(j*g.cellSize()), g.yMin+(i*g.cellSize())+g.cellSize(), g.zMin+(m*g.cellSize())+g.cellSize());       
                }
                

                
                //Identifies which vertices are within Fluid	
                int geometryIdentifier = 0;
                if (sliceISO[j][i][0] < isoValue) {geometryIdentifier += 1;}
                if (sliceISO[j][i][1] < isoValue) {geometryIdentifier += 2;}
                if (sliceISO[j][i][2] < isoValue) {geometryIdentifier += 4;}
                if (sliceISO[j][i][3] < isoValue) {geometryIdentifier += 8;}
                if (sliceISO[j][i][4] < isoValue) {geometryIdentifier += 16;}
                if (sliceISO[j][i][5] < isoValue) {geometryIdentifier += 32;}
                if (sliceISO[j][i][6] < isoValue) {geometryIdentifier += 64;}
                if (sliceISO[j][i][7] < isoValue) {geometryIdentifier += 128;}

                
                //Ignores fully encased cells and ones without intersections
                if(geometryIdentifier == 0 !! geometryIdentifier == 256) {
                    break;
                }


                //Creates Vector that includes Intersected Edges
                vector<int> intersectedEdges;
                    for(int i=0; i<16; i++) {
                        if (geometryTable[geometryIdentifier][i] != -1){
                            intersectedEdges.push_back(geometryTable[geometryIdentifier][i]);
                        } else {
                            break;
                        }
                     }



                //Linear Interpolation of Intersection Coordinates
                for (int i=0; i<intersectedEdges.size(); i++) {
                    particle p1();
                    p1.equals(verticeCoordinates.getParticle(edgeTable[intersectedEdges[i]][0]));	
                    particle p2();
                    p2.equals(verticeCoordinates.getParticle(edgeTable[intersectedEdges[i]][1]));

                    double iso1 = sliceISO[j][i][edgeTable[intersectedEdges[i]][0]];
                    double iso2 = sliceISO[j][i][edgeTable[intersectedEdges[i]][1]];
	    
        
        
                    double x = (1.0-(iso1/(iso1-iso2)))*p1.x() + ((iso1/(iso1-iso2))*p2.x());
                    double y = (1.0-(iso1/(iso1-iso2)))*p1.y() + ((iso1/(iso1-iso2))*p2.y());
                    double z = (1.0-(iso1/(iso1-iso2)))*p1.z() + ((iso1/(iso1-iso2))*p2.z());
        
                    particle intersection(x,y,z);

                    particles.addParticle(intersection);
                }

            }
        }
        firstSlice = true;
    }



    double q = levelSetPointer->evaluate(particles);
    std::vector<std::vector<int>> nearestNeighbors = nSearchPointer->find(particles, 5.0);
    double s = kernelPointer->evaluate(5.0);

    triangleList list;
    return list;
}

