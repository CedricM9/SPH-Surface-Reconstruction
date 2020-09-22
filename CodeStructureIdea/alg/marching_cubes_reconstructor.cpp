triangleList marchingCubesReconstructor::reconstruct(
  const particleList& particles,
  std::shared_ptr<levelSetFunction> levelSetPointer,
  std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
  std::shared_ptr<SPHInterpolationKernel> kernelPointer
) {

    // TODO: implement marching cubes algorithm.

    double q = levelSetPointer->evaluate(particles);
    std::vector<std::vector<int>> nearestNeighbors = nSearchPointer->find(particles, 5.0);
    double s = kernelPointer->evaluate(5.0);

    triangleList list;
    return list;
}

