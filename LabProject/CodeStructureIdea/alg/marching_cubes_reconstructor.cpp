#include <array>
#include <iterator>
#include <set>
#include <vector>

void marchingCubesReconstructor::calculateDensities(
    std::vector<std::vector<unsigned int>>& nearestNeighbors, 
    std::shared_ptr<SPHInterpolationKernel> kernelPointer,
    particleList& particles,
    float h
) {
    float density = 0.0;
    for(int i=0; i<particles.getNumberOfParticles(); i++) {
        for(int j=0; j<nearestNeighbors[i].size(); j++) {
            density += (kernelPointer->evaluate(particles.getParticle(i), particles.getParticle(nearestNeighbors[i][j]))) / (h*h*h);    
         } 
        particles.getParticle(i).setDensity(density);
        density = 0.0;
    }
}


triangleList marchingCubesReconstructor::reconstruct(
  graph& g,
  particleList& particles,
  const float smoothingLength,
  const float compactSupport,
  const float iso,
  std::shared_ptr<levelSetFunction> levelSetPointer,
  std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
  std::shared_ptr<SPHInterpolationKernel> kernelPointer
) {
    particleList triangleCoordinates;
    triangleList list;
    unsigned int geometryIdentifier = 0;


    kernelPointer->setRadius(smoothingLength);

    //Calculate Denisities at each particle
    std::vector<std::vector<unsigned int>> nearestNeighbors = nSearchPointer->find(particles, compactSupport);
    calculateDensities(nearestNeighbors, kernelPointer, particles, smoothingLength);

    // Format [x][y][z]
    std::array<float, 2> temp = {0.0, 0.0};
    std::array<float, 8> p = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    std::array<float, 4> L = {0.0, 0.0, 0.0, 0.0};
    std::vector<std::array<float, 2>> E(g.numCells(0), {0.0, 0.0});
    std::vector<std::vector<float>> D;
    for (int i = 0; i < g.numCells(0); ++i) {
        std::vector<float> t(g.numCells(1), 0.0);
        D.push_back(t);
    }


    for(int m=0; m<g.numCells(2); m++) {
        for(int i=0; i<g.numCells(1); i++) {
            for(int j=0; j<g.numCells(0); j++) {

		float v0[3] = {g.xMin()+j*g.cellSize(), g.yMin()+i*g.cellSize(), g.zMin()+m*g.cellSize()};
                float v1[3] = {g.xMin()+(j+1)*g.cellSize(), g.yMin()+i*g.cellSize(), g.zMin()+m*g.cellSize()};
                float v2[3] = {g.xMin()+(j+1)*g.cellSize(), g.yMin()+(i+1)*g.cellSize(), g.zMin()+m*g.cellSize()};
                float v3[3] = {g.xMin()+j*g.cellSize(), g.yMin()+(i+1)*g.cellSize(), g.zMin()+m*g.cellSize()};
                float v4[3] = {g.xMin()+j*g.cellSize(), g.yMin()+i*g.cellSize(), g.zMin()+(m+1)*g.cellSize()};
                float v5[3] = {g.xMin()+(j+1)*g.cellSize(), g.yMin()+i*g.cellSize(), g.zMin()+(m+1)*g.cellSize()};
                float v6[3] = {g.xMin()+(j+1)*g.cellSize(), g.yMin()+(i+1)*g.cellSize(), g.zMin()+(m+1)*g.cellSize()};
                float v7[3] = {g.xMin()+j*g.cellSize(), g.yMin()+(i+1)*g.cellSize(), g.zMin()+(m+1)*g.cellSize()};
                
                if(j==0) {
		            p[3] = levelSetPointer->evaluate(particles, v3[0], v3[1], v3[2], smoothingLength, compactSupport, compactSupport, nSearchPointer, kernelPointer);
		            p[7] = levelSetPointer->evaluate(particles, v7[0], v7[1], v7[2], smoothingLength, compactSupport, compactSupport, nSearchPointer, kernelPointer);  
		            if(i==0) {
			            p[0] = levelSetPointer->evaluate(particles, v0[0], v0[1], v0[2], smoothingLength, compactSupport, compactSupport, nSearchPointer, kernelPointer);
			            p[4] = levelSetPointer->evaluate(particles, v4[0], v4[1], v4[2], smoothingLength, compactSupport, compactSupport, nSearchPointer, kernelPointer);
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
		            p[1] = levelSetPointer->evaluate(particles, v1[0], v1[1], v1[2], smoothingLength, compactSupport, compactSupport, nSearchPointer, kernelPointer);
                    
		            p[5] = levelSetPointer->evaluate(particles, v5[0], v5[1], v5[2], smoothingLength, compactSupport, compactSupport, nSearchPointer, kernelPointer);
		        } else {
		            p[1] = E[j][0];
		            p[5] = E[j][1];
		        }
				
		        if(m==0) {
		            p[2] = levelSetPointer->evaluate(particles, v2[0], v2[1], v2[2], smoothingLength, compactSupport, compactSupport, nSearchPointer, kernelPointer);
		        } else {
		            p[2] = D[j][i];
	        	}
				
		        p[6] = levelSetPointer->evaluate(particles, v6[0], v6[1], v6[2], smoothingLength, compactSupport, compactSupport, nSearchPointer, kernelPointer);

		        L[0] = p[1];
		        L[1] = p[2];
		        L[2] = p[5];
		        L[3] = p[6];
		        E[j][0] = p[2];
		        E[j][1] = p[6];
		        D[j][i] = p[6];
                

                //Identifies which vertices are within Fluid	
                geometryIdentifier = 0;
                if (p[0] < iso) {geometryIdentifier += 1;}
                if (p[1] < iso) {geometryIdentifier += 2;}
                if (p[2] < iso) {geometryIdentifier += 4;}
                if (p[3] < iso) {geometryIdentifier += 8;}
                if (p[4] < iso) {geometryIdentifier += 16;}
                if (p[5] < iso) {geometryIdentifier += 32;}
                if (p[6] < iso) {geometryIdentifier += 64;}
                if (p[7] < iso) {geometryIdentifier += 128;}

                //Ignores fully encased cells and ones without intersections
                if((geometryIdentifier == 0) || (geometryIdentifier == 255)) {
                    continue;
                }

                //Creates Vector that includes Intersected Edges
                std::vector<int> intersectedEdges;
                std::set<int> edgesSet;
                for(int k=0; k<16; k++) {
                    if (geometryTable[geometryIdentifier][k] != -1){                                                                             
                        intersectedEdges.push_back(geometryTable[geometryIdentifier][k]);
                        edgesSet.insert(geometryTable[geometryIdentifier][k]);
                    }
                }

                // Store number of particles before adding new points and indices of already existing points.
                int numberParticlesBefore = list.getNumberOfParticles();
                std::vector<int> edgesIndices(edgesSet.size(), -1);


                //Linear Interpolation of Intersection Coordinates
                float vertexCoordinatesX[2],vertexCoordinatesY[2],vertexCoordinatesZ[2];
                std::set<int>::iterator edgeIterator = edgesSet.begin();

                float intersectionCoordinates[2][3];
                for (int r=0; r<edgesSet.size(); r++, edgeIterator++) {
                    int edgeNumber = *edgeIterator;
                    for (int t=0; t<2; t++) {
                        if (edgeTable[edgeNumber][t] == 0) {intersectionCoordinates[t][0]=v0[0];
                                                            intersectionCoordinates[t][1]=v0[1];
                                                            intersectionCoordinates[t][2]=v0[2];}
                        if (edgeTable[edgeNumber][t] == 1) {intersectionCoordinates[t][0]=v1[0];
                                                            intersectionCoordinates[t][1]=v1[1];
                                                            intersectionCoordinates[t][2]=v1[2];}
                        if (edgeTable[edgeNumber][t] == 2) {intersectionCoordinates[t][0]=v2[0];
                                                            intersectionCoordinates[t][1]=v2[1];
                                                            intersectionCoordinates[t][2]=v2[2];}
                        if (edgeTable[edgeNumber][t] == 3) {intersectionCoordinates[t][0]=v3[0];
                                                            intersectionCoordinates[t][1]=v3[1];
                                                            intersectionCoordinates[t][2]=v3[2];}
                        if (edgeTable[edgeNumber][t] == 4) {intersectionCoordinates[t][0]=v4[0];
                                                            intersectionCoordinates[t][1]=v4[1];
                                                            intersectionCoordinates[t][2]=v4[2];}
                        if (edgeTable[edgeNumber][t] == 5) {intersectionCoordinates[t][0]=v5[0];
                                                            intersectionCoordinates[t][1]=v5[1];
                                                            intersectionCoordinates[t][2]=v5[2];}
                        if (edgeTable[edgeNumber][t] == 6) {intersectionCoordinates[t][0]=v6[0];
                                                            intersectionCoordinates[t][1]=v6[1];
                                                            intersectionCoordinates[t][2]=v6[2];}
                        if (edgeTable[edgeNumber][t] == 7) {intersectionCoordinates[t][0]=v7[0];
                                                            intersectionCoordinates[t][1]=v7[1];
                                                            intersectionCoordinates[t][2]=v7[2];}
                    }

                    float iso1 = p[edgeTable[edgeNumber][0]];
                    float iso2 = p[edgeTable[edgeNumber][1]];
                    

                    float x = (1.0-(iso1/(iso1-iso2)))*(intersectionCoordinates[0][0]) + ((iso1/(iso1-iso2))*intersectionCoordinates[1][0]);
                    float y = (1.0-(iso1/(iso1-iso2)))*intersectionCoordinates[0][1] + ((iso1/(iso1-iso2))*intersectionCoordinates[1][1]);
                    float z = (1.0-(iso1/(iso1-iso2)))*intersectionCoordinates[0][2] + ((iso1/(iso1-iso2))*intersectionCoordinates[1][2]);
                    
                    particle intersection(x,y,z);
                    edgesIndices[r] = list.addParticleWithCheck(intersection);

                }

                // Add new triangles.
                for (int k=0; k<intersectedEdges.size(); k+=3) {
                    std::array<int, 3> indices;
                    for (int triangleVertexIndex = 0; triangleVertexIndex < 3; ++triangleVertexIndex) {
                        int distance = std::distance(edgesSet.begin(), edgesSet.find(intersectedEdges[k + triangleVertexIndex]));
                        int newOnes = std::count(edgesIndices.begin(), edgesIndices.begin() + distance, -1);
                        if (edgesIndices[distance] == -1) {
                            indices[triangleVertexIndex] = numberParticlesBefore + newOnes;
                        } else {
                            indices[triangleVertexIndex] = edgesIndices[distance];
                        }
                    }
                    list.addTriangle(indices[0], indices[1], indices[2]);
                }


            }
        }
    }
    /*
    std::cout << "Graph X: " << g.xMin() << "->" << g.xMax() << std::endl;
    std::cout << "Graph Y: " << g.yMin() << "->" << g.yMax() << std::endl;
    std::cout << "Graph Z: " << g.zMin() << "->" << g.zMax() << std::endl << std::endl;
    
    std::cout << "#Cells X: " << g.numCells(0) << std::endl;
    std::cout << "#Cells Y: " << g.numCells(1) << std::endl;
    std::cout << "#Cells Z: " << g.numCells(1) << std::endl;
    std::cout << "Cell Size: " << g.cellSize() << std::endl;
    
    std::cout << "particles: " << list.getNumberOfParticles() << ", triangles: " << list.getNumberOfTriangles() << std::endl;
    */

    return list;
}
