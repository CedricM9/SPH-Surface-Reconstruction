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
  graph& g,
  const particleList& particles,
  std::shared_ptr<levelSetFunction> levelSetPointer,
  std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
  std::shared_ptr<SPHInterpolationKernel> kernelPointer
) {

    // Format [x][y][z]
    float p[8];
    float L[4];
    float E[g.numCells(0)][2];
    float D[g.numCells(0)][g.numCells(1)];
    float temp[2];

    int isoValue = 0;
    int geometryIdentifier = 0;

    //g.numCells-1 ???
    for(int m=0; m<g.numCells(2); m++) {
        for(int i=0; i<g.numCells(1); i++){
            for(int j=0; j<g.numCells(0); j++) {
                if(j==0) {
					p[3] = calculateISO(g.xMin()+(j*g.cellSize()), g.yMin()+(i*g.cellSize())+g.cellSize(), g.zMin()+(m*g.cellSize()));
					p[7] = calculateISO(g.xMin()+(j*g.cellSize()), g.yMin()+(i*g.cellSize())+g.cellSize(), g.zMin()+(m*g.cellSize())+g.cellSize());   
					if(i==0) {
						p[0] = calculateISO(g.xMin()+(j*g.cellSize()), g.yMin()+(i*g.cellSize()), g.zMin()+(m*g.cellSize()));
						p[4] = calculateISO(g.xMin()+(j*g.cellSize()), g.yMin()+(i*g.cellSize()), g.zMin()+(m*g.cellSize())+g.cellSize());
					} else {
						p[0] = temp[0];
						p[4] = temp[1];
					}
					temp[0] = p[3];
					temp[1] = p[7];
				} else {
					p[0] = L[0];
					p[3] = L[1];
					p[4] = L[2];
					p[7] = L[3];
				}

				if(i==0) {
					p[1] = calculateISO(g.xMin()+(j*g.cellSize())+g.cellSize(), g.yMin()+(i*g.cellSize()), g.zMin()+(m*g.cellSize()));
					p[5] = calculateISO(g.xMin()+(j*g.cellSize())+g.cellSize(), g.yMin()+(i*g.cellSize()), g.zMin()+(m*g.cellSize())+g.cellSize());
				} else {
					p[1] = E[j][0];
					p[5] = E[j][1];
				}
				
				if(m==0) {
					p[2] = calculateISO(g.xMin()+(j*g.cellSize())+g.cellSize(), g.yMin()+(i*g.cellSize())+g.cellSize(), g.zMin()+(m*g.cellSize()));
				} else {
					p[2] = D[j][i];
				}
				
				p[6] = calculateISO(g.xMin()+(j*g.cellSize())+g.cellSize(), g.yMin()+(i*g.cellSize())+g.cellSize(), g.zMin()+(m*g.cellSize())+g.cellSize());

				L[0] = p[1];
				L[1] = p[2];
				L[2] = p[5];
				L[3] = p[6];
				E[j][0] = p[2];
				E[j][1] = p[6];
				D[j][i] = p[6];
                

                
                //Identifies which vertices are within Fluid	
                geometryIdentifier = 0;
                if (p[0] < isoValue) {geometryIdentifier += 1;}
                if (p[1] < isoValue) {geometryIdentifier += 2;}
                if (p[2] < isoValue) {geometryIdentifier += 4;}
                if (p[3] < isoValue) {geometryIdentifier += 8;}
                if (p[4] < isoValue) {geometryIdentifier += 16;}
                if (p[5] < isoValue) {geometryIdentifier += 32;}
                if (p[6] < isoValue) {geometryIdentifier += 64;}
                if (p[7] < isoValue) {geometryIdentifier += 128;}

                
                //Ignores fully encased cells and ones without intersections
                if((geometryIdentifier == 0) || (geometryIdentifier == 256)) {
                    break;
                }


                //Creates Vector that includes Intersected Edges
                std::vector<int> intersectedEdges;
                    for(int i=0; i<16; i++) {
                        if (geometryTable[geometryIdentifier][i] != -1){
                            intersectedEdges.push_back(geometryTable[geometryIdentifier][i]);
                        } else {
                            break;
                        }
                     }



                //Linear Interpolation of Intersection Coordinates
                for (int i=0; i<intersectedEdges.size(); i++) {
                    /* 
                    particle p1();
                    //p1.equals(verticeCoordinates.getParticle(edgeTable[intersectedEdges[i]][0]));	
                    particle p2();
                    //p2.equals(verticeCoordinates.getParticle(edgeTable[intersectedEdges[i]][1]));
                   

                    double iso1 = p[edgeTable[intersectedEdges[i]][0]];
                    double iso2 = p[edgeTable[intersectedEdges[i]][1]];
	    
        
        
                    double x = (1.0-(iso1/(iso1-iso2)))*p1.x() + ((iso1/(iso1-iso2))*p2.x());
                    double y = (1.0-(iso1/(iso1-iso2)))*p1.y() + ((iso1/(iso1-iso2))*p2.y());
                    double z = (1.0-(iso1/(iso1-iso2)))*p1.z() + ((iso1/(iso1-iso2))*p2.z());
        
                    particle intersection(x,y,z);

                    particles.addParticle(intersection);

                    */
                }
            }
        }
    }


/*
    double q = levelSetPointer->evaluate(particles);
    std::vector<std::vector<int>> nearestNeighbors = nSearchPointer->find(particles, 5.0);
    double s = kernelPointer->evaluate(5.0);
*/
    triangleList list;
    return list;
}

