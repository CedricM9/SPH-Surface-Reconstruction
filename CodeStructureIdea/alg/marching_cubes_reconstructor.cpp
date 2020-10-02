triangleList marchingCubesReconstructor::reconstruct(
  const particleList& verticeCoordinates,
  const verticeISO[8],
  particleList& particles,
  std::shared_ptr<levelSetFunction> levelSetPointer,
  std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
  std::shared_ptr<SPHInterpolationKernel> kernelPointer
) {

   assert(verticeCoordinates.getNumberOfParticles() == 8);


   //Identifies which vertices are within Fluid	
   int isoValue = 0;
   int geometryIdentifier = 0;
   if (verticeISO[0] < isoValue) {geometryIdentifier += 1;}
   if (verticeISO[1] < isoValue) {geometryIdentifier += 2;}
   if (verticeISO[2] < isoValue) {geometryIdentifier += 4;}
   if (verticeISO[3] < isoValue) {geometryIdentifier += 8;}
   if (verticeISO[4] < isoValue) {geometryIdentifier += 16;}
   if (verticeISO[5] < isoValue) {geometryIdentifier += 32;}
   if (verticeISO[6] < isoValue) {geometryIdentifier += 64;}
   if (verticeISO[7] < isoValue) {geometryIdentifier += 128;}



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

	    double iso1 = verticeISO[edgeTable[intersectedEdges[i]][0]];
	    double iso2 = verticeISO[edgeTable[intersectedEdges[i]][1]];
		
	    
	    
	    double x = (1.0-(iso1/(iso1-iso2)))*p1.x() + ((iso1/(iso1-iso2))*p2.x());
	    double y = (1.0-(iso1/(iso1-iso2)))*p1.y() + ((iso1/(iso1-iso2))*p2.y());
	    double z = (1.0-(iso1/(iso1-iso2)))*p1.z() + ((iso1/(iso1-iso2))*p2.z());
	    
	    particle intersection(x,y,z);

	    particles.addParticle(intersection);
	}	



    double q = levelSetPointer->evaluate(particles);
    std::vector<std::vector<int>> nearestNeighbors = nSearchPointer->find(particles, 5.0);
    double s = kernelPointer->evaluate(5.0);

    triangleList list;
    return list;
}

