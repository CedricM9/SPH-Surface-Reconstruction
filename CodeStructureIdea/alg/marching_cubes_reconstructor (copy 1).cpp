void marchingCubesReconstructor::calculateDensities(
    std::vector<std::vector<int>>& nearestNeighbors, 
    std::shared_ptr<SPHInterpolationKernel> kernelPointer,
    particleList& particles,
    int h
) {
    float density = 0.0;
    for(int i=0; i<particles.getNumberOfParticles(); i++) {
        for(int j=0; j<nearestNeighbors[i].size(); j++) {
            density += (kernelPointer->evaluate(particles.getParticle(i), particles.getParticle(nearestNeighbors[i][j]), h)) / (h*h*h);    
         } 
        particles.getParticle(i).setDensity(density);
        density = 0.0;
    }

}
    




triangleList marchingCubesReconstructor::reconstruct(
  graph& g,
  particleList& particles,
  const float h,
  const float r,
  std::shared_ptr<levelSetFunction> levelSetPointer,
  std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
  std::shared_ptr<SPHInterpolationKernel> kernelPointer
) {

    //Calculate Denisities at each particle
    std::vector<std::vector<int>> nearestNeighbors = nSearchPointer->find(particles, r);
    calculateDensities(nearestNeighbors, kernelPointer, particles, h);
    
    particleList triangleCoordinates;

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
                float vertexCoordinatesX[2],vertexCoordinatesY[2],vertexCoordinatesZ[2];
                for (int r=0; r<intersectedEdges.size(); r++) {
                    vertexCoordinatesX[0] = g.xMin()+(j*g.cellSize());
                    vertexCoordinatesX[1] = g.xMin()+(j*g.cellSize());
                    vertexCoordinatesY[0] = g.yMin()+(i*g.cellSize());
                    vertexCoordinatesY[1] = g.yMin()+(i*g.cellSize());
                    vertexCoordinatesZ[0] = g.zMin()+(m*g.cellSize());
                    vertexCoordinatesZ[1] = g.zMin()+(m*g.cellSize());

                    for (int t=0; t<2; t++) {
                        if(edgeTable[intersectedEdges[t]][0] == 1) {vertexCoordinatesX[t]+=g.cellSize();}
                        if(edgeTable[intersectedEdges[t]][0] == 2) {vertexCoordinatesX[t]+=g.cellSize();
                                                                    vertexCoordinatesY[t]+=g.cellSize();}
                        if(edgeTable[intersectedEdges[t]][0] == 3) {vertexCoordinatesY[t]+=g.cellSize();}
                        if(edgeTable[intersectedEdges[t]][0] == 4) {vertexCoordinatesZ[t]+=g.cellSize();}
                        if(edgeTable[intersectedEdges[t]][0] == 5) {vertexCoordinatesX[t]+=g.cellSize();
                                                                    vertexCoordinatesZ[t]+=g.cellSize();}
                        if(edgeTable[intersectedEdges[t]][0] == 6) {vertexCoordinatesX[t]+=g.cellSize();
                                                                    vertexCoordinatesY[t]+=g.cellSize();
                                                                    vertexCoordinatesZ[t]+=g.cellSize();}
                        if(edgeTable[intersectedEdges[t]][0] == 7) {vertexCoordinatesX[t]+=g.cellSize();
                                                                    vertexCoordinatesY[t]+=g.cellSize();}
                    }


                    float iso1 = p[edgeTable[intersectedEdges[i]][0]];
                    float iso2 = p[edgeTable[intersectedEdges[i]][1]];

                    float x = (1.0-(iso1/(iso1-iso2)))*(vertexCoordinatesX[0]) + ((iso1/(iso1-iso2))*vertexCoordinatesX[1]);
                    float y = (1.0-(iso1/(iso1-iso2)))*vertexCoordinatesY[0] + ((iso1/(iso1-iso2))*vertexCoordinatesY[1]);
                    float z = (1.0-(iso1/(iso1-iso2)))*vertexCoordinatesZ[0] + ((iso1/(iso1-iso2))*vertexCoordinatesZ[1]);
        
                    particle intersection(x,y,z);

                    triangleCoordinates.addParticle(intersection);  
                }


            }
        }
    }



    double q = levelSetPointer->evaluate(particles);

    double s = kernelPointer->evaluate(5.0);

    triangleList list(triangleCoordinates);
    return list;
}

