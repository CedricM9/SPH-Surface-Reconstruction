template <typename T>
triangleList<T> marchingCubesReconstructor<T>::reconstruct(
  const particleList<T>& particles,
  std::shared_ptr<levelSetFunction<T>> levelSetPointer,
  std::shared_ptr<compactNeighborhoodSearch<T>> nSearchPointer,
  std::shared_ptr<SPHInterpolationKernel<T>> kernelPointer
) {

    // TODO: implement marching cubes algorithm.

    T q = levelSetPointer->evaluate(particles);
    std::vector<std::vector<int>> nearestNeighbors = nSearchPointer->find(particles, 5.0);
    T s = kernelPointer->evaluate(5.0);

    triangleList<T> list;
    return list;
}

