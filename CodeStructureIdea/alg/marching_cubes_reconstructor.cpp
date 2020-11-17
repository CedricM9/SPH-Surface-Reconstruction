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

/*
particle marchingCubesReconstructor::interpolate(float c,
                                              float iso1,
                                              float iso2,
                                              float x1,
                                              float y1,
                                              float z1,
                                              float x2,
                                              float y2,
                                              float z2
) {
    particle p;
    float factor;
    if (abs(c-iso1) < 0.0001)
        return(p1);
    if (abs(c-iso2) < 0.0001)
        return(p2);
    if (abs(iso1-iso2) < 0.0001)
        return(p1);
    factor = (c - iso1) / (iso2 - iso1);
    p.x = p1.x + mu * (p2.x - p1.x);
    p.y = p1.y + mu * (p2.y - p1.y);
    p.z = p1.z + mu * (p2.z - p1.z);

    return(p);
}
*/


triangleList marchingCubesReconstructor::reconstruct(
  graph& g,
  particleList& particles,
  const float h,
  const float r,
  std::shared_ptr<levelSetFunction> levelSetPointer,
  std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
  std::shared_ptr<SPHInterpolationKernel> kernelPointer
) {
    kernelPointer->setRadius(h);

    //Calculate Denisities at each particle
    std::vector<std::vector<unsigned int>> nearestNeighbors = nSearchPointer->find(particles, r);
    calculateDensities(nearestNeighbors, kernelPointer, particles, h);
    
    for (int i = 0; i < particles.getNumberOfParticles(); ++i) {
        particle cur = particles.getParticle(i);
        std::cout << cur.x() << " " << cur.y() << " " << cur.z() << ", density: " << particles.getParticle(i).density() << std::endl;
    }
    particleList triangleCoordinates;
    triangleList list;

    // Format [x][y][z]
    std::array<float, 8> p = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    std::array<float, 4> L = {0.0, 0.0, 0.0, 0.0};
    std::vector<std::array<float, 2>> E(g.numCells(0), {0.0, 0.0});
    std::vector<std::vector<float>> D;
    for (int i = 0; i < g.numCells(0); ++i) {
        std::vector<float> t(g.numCells(1), 0.0);
        D.push_back(t);
    }
    std::array<float, 2> temp = {0.0, 0.0};

    float c = 0.4;
    float compactSupport = r;
    int geometryIdentifier = 0;

    int numImportantGridcells = 0;

    //levelSetPointer->evaluate(particles, tempParticle, h, c, compactSupport, nSearchPointer, kernelPointer);

    //g.numCells-1 ???
    for(int m=0; m<g.numCells(2); m++) {
        for(int i=0; i<g.numCells(1); i++) {
            for(int j=0; j<g.numCells(0); j++) {
                if(j==0) {
                    //particle tempParticle1(g.xMin()+j*g.cellSize(), g.yMin()+(i+1)*g.cellSize(), g.zMin()+m*g.cellSize());
		            p[3] = levelSetPointer->evaluate(particles, g.xMin()+j*g.cellSize(), g.yMin()+(i+1)*g.cellSize(), g.zMin()+m*g.cellSize(), h, c, compactSupport, nSearchPointer, kernelPointer);

                    //particle tempParticle2(g.xMin()+j*g.cellSize(), g.yMin()+(i+1)*g.cellSize(), g.zMin()+(m+1)*g.cellSize());   
		            p[7] = levelSetPointer->evaluate(particles, g.xMin()+j*g.cellSize(), g.yMin()+(i+1)*g.cellSize(), g.zMin()+(m+1)*g.cellSize(), h, c, compactSupport, nSearchPointer, kernelPointer);  
		            if(i==0) {
                        //particle tempParticle3(g.xMin()+j*g.cellSize(), g.yMin()+i*g.cellSize(), g.zMin()+m*g.cellSize());
			            p[0] = levelSetPointer->evaluate(particles, g.xMin()+j*g.cellSize(), g.yMin()+i*g.cellSize(), g.zMin()+m*g.cellSize(), h, c, compactSupport, nSearchPointer, kernelPointer);

                        //particle tempParticle4(g.xMin()+j*g.cellSize(), g.yMin()+i*g.cellSize(), g.zMin()+(m+1)*g.cellSize());
			            p[4] = levelSetPointer->evaluate(particles, g.xMin()+j*g.cellSize(), g.yMin()+i*g.cellSize(), g.zMin()+(m+1)*g.cellSize(), h, c, compactSupport, nSearchPointer, kernelPointer);
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
                   //particle tempParticle5(g.xMin()+(j+1)*g.cellSize(), g.yMin()+i*g.cellSize(), g.zMin()+m*g.cellSize());
		    p[1] = levelSetPointer->evaluate(particles, g.xMin()+(j+1)*g.cellSize(), g.yMin()+i*g.cellSize(), g.zMin()+m*g.cellSize(), h, c, compactSupport, nSearchPointer, kernelPointer);
                    
                    //particle tempParticle6(g.xMin()+(j+1)*g.cellSize(), g.yMin()+i*g.cellSize(), g.zMin()+(m+1)*g.cellSize());
		    p[5] = levelSetPointer->evaluate(particles, g.xMin()+(j+1)*g.cellSize(), g.yMin()+i*g.cellSize(), g.zMin()+(m+1)*g.cellSize(), h, c, compactSupport, nSearchPointer, kernelPointer);
		} else {
		    p[1] = E[j][0];
		    p[5] = E[j][1];
		}
				
		if(m==0) {
                    //particle tempParticle7(g.xMin()+(j+1)*g.cellSize(), g.yMin()+(i+1)*g.cellSize(), g.zMin()+m*g.cellSize());
		    p[2] = levelSetPointer->evaluate(particles, g.xMin()+(j+1)*g.cellSize(), g.yMin()+(i+1)*g.cellSize(), g.zMin()+m*g.cellSize(), h, c, compactSupport, nSearchPointer, kernelPointer);
		} else {
		    p[2] = D[j][i];
		}
				
                //particle tempParticle8(g.xMin()+(j+1)*g.cellSize(), g.yMin()+(i+1)*g.cellSize(), g.zMin()+(m+1)*g.cellSize());
		p[6] = levelSetPointer->evaluate(particles, g.xMin()+(j+1)*g.cellSize(), g.yMin()+(i+1)*g.cellSize(), g.zMin()+(m+1)*g.cellSize(), h, c, compactSupport, nSearchPointer, kernelPointer);

		L[0] = p[1];
		L[1] = p[2];
		L[2] = p[5];
		L[3] = p[6];
		E[j][0] = p[2];
		E[j][1] = p[6];
		D[j][i] = p[6];
                

                
                //Identifies which vertices are within Fluid	
                geometryIdentifier = 0;
                if (p[0] < c) {geometryIdentifier += 1;}
                if (p[1] < c) {geometryIdentifier += 2;}
                if (p[2] < c) {geometryIdentifier += 4;}
                if (p[3] < c) {geometryIdentifier += 8;}
                if (p[4] < c) {geometryIdentifier += 16;}
                if (p[5] < c) {geometryIdentifier += 32;}
                if (p[6] < c) {geometryIdentifier += 64;}
                if (p[7] < c) {geometryIdentifier += 128;}

//                if (m==13) std::cout << geometryIdentifier << "  " << p[0] << "  " << p[3] << "  " << p[4] << "  " << p[7] << std::endl;
                /*if (p[0] < c) std::cout << "0  " << p[0] << "  " << geometryIdentifier << std::endl;
                if (p[1] < c) std::cout << "1  " << p[1] << "  " << geometryIdentifier << std::endl;
                if (p[2] < c) std::cout << "2  " << p[2] << "  " << geometryIdentifier << std::endl;
                if (p[3] < c) std::cout << "3  " << p[3] << "  " << geometryIdentifier << std::endl;
                if (p[4] < c) std::cout << "4  " << p[4] << "  " << geometryIdentifier << std::endl;
                if (p[5] < c) std::cout << "5  " << p[5] << "  " << geometryIdentifier << std::endl;
                if (p[6] < c) std::cout << "6  " << p[6] << "  " << geometryIdentifier << std::endl;
                if (p[7] < c) std::cout << "7  " << p[7] << "  " << geometryIdentifier << std::endl;
                */
                std::cout << "-------------------" << std::endl;
                std::cout << "ISO: " << geometryIdentifier << std::endl;
                std::cout << p[0] << " " << p[1] << " " << p[2] << " " << p[3] << " " << p[4] << " " << p[5] << " " << p[6] << " " << p[7] << " " << std::endl;

                //Ignores fully encased cells and ones without intersections
                if((geometryIdentifier == 0) || (geometryIdentifier == 255)) {
                    continue;
                }
                //if(geometryIdentifier == 0) continue;
                //if(geometryIdentifier == 255) geometryIdentifier = 51;

                //geometryIdentifier = 51;

                numImportantGridcells++;

                //Creates Vector that includes Intersected Edges
                std::vector<int> intersectedEdges;
                std::set<int> edgesSet;
                for(int k=0; k<16; k++) {
                    if (geometryTable[geometryIdentifier][k] != -1){                                                                             
                        intersectedEdges.push_back(geometryTable[geometryIdentifier][k]);
                        edgesSet.insert(geometryTable[geometryIdentifier][k]);
                    }
                }

                std::cout << "# of Edges: " << intersectedEdges.size() << std::endl;
                
                // Add new triangles.
                int numberParticles = list.getNumberOfParticles();
                std::cout << "# of Particles: " << numberParticles << std::endl;
                for (int k=0; k<intersectedEdges.size(); k+=3) {
                    int index1 = numberParticles + std::distance(edgesSet.begin(), edgesSet.find(intersectedEdges[k]));
                    int index2 = numberParticles + std::distance(edgesSet.begin(), edgesSet.find(intersectedEdges[k+1]));
                    int index3 = numberParticles + std::distance(edgesSet.begin(), edgesSet.find(intersectedEdges[k+2]));
                    list.addTriangle(index1, index2, index3);
                }


                //Linear Interpolation of Intersection Coordinates
                float vertexCoordinatesX[2],vertexCoordinatesY[2],vertexCoordinatesZ[2];
                std::set<int>::iterator edgeIterator = edgesSet.begin();
                //std::cout << "set size: " << edgesSet.size() << std::endl;
                for (int r=0; r<edgesSet.size(); r++, edgeIterator++) {
                    int edgeNumber = *edgeIterator;
                    vertexCoordinatesX[0] = g.xMin()+(j*g.cellSize());
                    vertexCoordinatesX[1] = g.xMin()+(j*g.cellSize());
                    vertexCoordinatesY[0] = g.yMin()+(i*g.cellSize());
                    vertexCoordinatesY[1] = g.yMin()+(i*g.cellSize());
                    vertexCoordinatesZ[0] = g.zMin()+(m*g.cellSize());
                    vertexCoordinatesZ[1] = g.zMin()+(m*g.cellSize());

                    for (int t=0; t<2; t++) {
                        if(edgeTable[edgeNumber][t] == 1) {vertexCoordinatesX[t]+=g.cellSize();}
                        if(edgeTable[edgeNumber][t] == 2) {vertexCoordinatesX[t]+=g.cellSize();
                                                           vertexCoordinatesY[t]+=g.cellSize();}
                        if(edgeTable[edgeNumber][t] == 3) {vertexCoordinatesY[t]+=g.cellSize();}
                        if(edgeTable[edgeNumber][t] == 4) {vertexCoordinatesZ[t]+=g.cellSize();}
                        if(edgeTable[edgeNumber][t] == 5) {vertexCoordinatesX[t]+=g.cellSize();
                                                           vertexCoordinatesZ[t]+=g.cellSize();}
                        if(edgeTable[edgeNumber][t] == 6) {vertexCoordinatesX[t]+=g.cellSize();
                                                           vertexCoordinatesY[t]+=g.cellSize();
                                                           vertexCoordinatesZ[t]+=g.cellSize();}
                        if(edgeTable[edgeNumber][t] == 7) {vertexCoordinatesY[t]+=g.cellSize();
                                                           vertexCoordinatesZ[t]+=g.cellSize();}
                    }

                    float iso1 = p[edgeTable[edgeNumber][0]];
                    float iso2 = p[edgeTable[edgeNumber][1]];
                    //std::cout << "iso1 " << iso1 << std::endl;
                    //
                    //triangleCoordinates.addParticle(interpolate(c, iso1, iso2, vertexCoordinatesX[0], vertexCoordinatesY[0], vertexCoordinatesZ[0], vertexCoordinatesX[1], vertexCoordinatesY[1], vertexCoordinatesZ[1])
                    float x = (1.0-(iso1/(iso1-iso2)))*(vertexCoordinatesX[0]) + ((iso1/(iso1-iso2))*vertexCoordinatesX[1]);
                    float y = (1.0-(iso1/(iso1-iso2)))*vertexCoordinatesY[0] + ((iso1/(iso1-iso2))*vertexCoordinatesY[1]);
                    float z = (1.0-(iso1/(iso1-iso2)))*vertexCoordinatesZ[0] + ((iso1/(iso1-iso2))*vertexCoordinatesZ[1]);
                    
                    //std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
 
                    particle intersection(x,y,z);

                    triangleCoordinates.addParticle(intersection);  

                    list.addParticle(intersection);  
                    //std::cout << "particles: " << list.getNumberOfParticles() << ", triangles: " << list.getNumberOfTriangles() << std::endl;

                }
                std::cout << "-------------------" << std::endl;

            }
        }
    }

    //for (int i = 0; i < list.getNumberOfParticles(); ++i) {
    //    std::cout << "x = " << list.getParticle(i).x() << ", y = " << list.getParticle(i).y() << ", z = " << list.getParticle(i).z() << std::endl;
    //}
    for (int i = 0; i < list.getNumberOfTriangles(); ++i) {
        std::array<particle, 3> triang = list.getTriangle(i);
        for (int j = 0; j < 3; ++j) {
            std::cout << "x = " << triang[j].x() << ", y = " << triang[j].y() << ", z = " << triang[j].z() << std::endl;
        }
        std::cout << "---" << std::endl;
    }
    std::cout << std::endl << std::endl;
    std::cout << "Graph X: " << g.xMin() << "->" << g.xMax() << std::endl;
    std::cout << "Graph Y: " << g.yMin() << "->" << g.yMax() << std::endl;
    std::cout << "Graph Z: " << g.zMin() << "->" << g.zMax() << std::endl << std::endl;
    
    std::cout << "#Cells X: " << g.numCells(0) << std::endl;
    std::cout << "#Cells Y: " << g.numCells(1) << std::endl;
    std::cout << "#Cells Z: " << g.numCells(1) << std::endl;
    std::cout << "Cell Size: " << g.cellSize() << std::endl;
    
    std::cout << "#Releveant Gridcells: " << numImportantGridcells << std::endl;
    std::cout << "particles: " << list.getNumberOfParticles() << ", triangles: " << list.getNumberOfTriangles() << std::endl;

/*
    for(int i=0; i<16; i++) {
        std::cout << geometryTable[204][i] << std::endl;
    }    
*/
    //double q = levelSetPointer->evaluate(particles);

    //double s = kernelPointer->evaluate(5.0);

    //triangleList list(triangleCoordinates);
    return list;
}

