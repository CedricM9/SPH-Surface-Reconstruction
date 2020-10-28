QT       += core gui 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -fopenmp

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
LIBS += -fopenmp


SOURCES += \
    CompactNSearch/src/CompactNSearch.cpp \
    main.cpp \
    mainwindow.cpp \
    surfrec_io/code/io.cpp \
    surfrec_io/extern/partio/src/lib/core/Particle.cpp \
    surfrec_io/extern/partio/src/lib/core/ParticleCaching.cpp \
    surfrec_io/extern/partio/src/lib/core/ParticleHeaders.cpp \
    surfrec_io/extern/partio/src/lib/core/ParticleSimple.cpp \
    surfrec_io/extern/partio/src/lib/core/ParticleSimpleInterleave.cpp \
    surfrec_io/extern/partio/src/lib/io/BGEO.cpp \
    surfrec_io/extern/partio/src/lib/io/BIN.cpp \
    surfrec_io/extern/partio/src/lib/io/GEO.cpp \
    surfrec_io/extern/partio/src/lib/io/MC.cpp \
    surfrec_io/extern/partio/src/lib/io/PDA.cpp \
    surfrec_io/extern/partio/src/lib/io/PDB.cpp \
    surfrec_io/extern/partio/src/lib/io/PDC.cpp \
    surfrec_io/extern/partio/src/lib/io/PRT.cpp \
    surfrec_io/extern/partio/src/lib/io/PTC.cpp \
    surfrec_io/extern/partio/src/lib/io/PTS.cpp \
    surfrec_io/extern/partio/src/lib/io/ParticleIO.cpp \
    surfrec_io/extern/partio/src/lib/io/RIB.cpp \
    surfrec_io/extern/partio/src/lib/io/ZIP.cpp \
    surfrec_io/extern/zlib/src/adler32.c \
    surfrec_io/extern/zlib/src/compress.c \
    surfrec_io/extern/zlib/src/crc32.c \
    surfrec_io/extern/zlib/src/deflate.c \
    surfrec_io/extern/zlib/src/gzio.c \
    surfrec_io/extern/zlib/src/infback.c \
    surfrec_io/extern/zlib/src/inffast.c \
    surfrec_io/extern/zlib/src/inflate.c \
    surfrec_io/extern/zlib/src/inftrees.c \
    surfrec_io/extern/zlib/src/trees.c \
    surfrec_io/extern/zlib/src/uncompr.c \
    surfrec_io/extern/zlib/src/zutil.c

HEADERS += \
    CompactNSearch/extern/libmorton/libmorton/include/morton.h \
    CompactNSearch/extern/libmorton/libmorton/include/morton2D.h \
    CompactNSearch/extern/libmorton/libmorton/include/morton2D_LUTs.h \
    CompactNSearch/extern/libmorton/libmorton/include/morton3D.h \
    CompactNSearch/extern/libmorton/libmorton/include/morton3D_LUTs.h \
    CompactNSearch/extern/libmorton/libmorton/include/morton_BMI.h \
    CompactNSearch/extern/libmorton/libmorton/include/morton_LUT_generators.h \
    CompactNSearch/extern/libmorton/libmorton/include/morton_common.h \
    CompactNSearch/include/CompactNSearch \
    CompactNSearch/include/CompactNSearch.h \
    CompactNSearch/include/Config.h \
    CompactNSearch/include/DataStructures.h \
    CompactNSearch/include/PointSet.h \
    mainwindow.h \
    surfrec_io/code/io.h \
    surfrec_io/extern/Eigen/Eigen/Cholesky \
    surfrec_io/extern/Eigen/Eigen/CholmodSupport \
    surfrec_io/extern/Eigen/Eigen/Core \
    surfrec_io/extern/Eigen/Eigen/Dense \
    surfrec_io/extern/Eigen/Eigen/Eigen \
    surfrec_io/extern/Eigen/Eigen/Eigenvalues \
    surfrec_io/extern/Eigen/Eigen/Geometry \
    surfrec_io/extern/Eigen/Eigen/Householder \
    surfrec_io/extern/Eigen/Eigen/IterativeLinearSolvers \
    surfrec_io/extern/Eigen/Eigen/Jacobi \
    surfrec_io/extern/Eigen/Eigen/KLUSupport \
    surfrec_io/extern/Eigen/Eigen/LU \
    surfrec_io/extern/Eigen/Eigen/MetisSupport \
    surfrec_io/extern/Eigen/Eigen/OrderingMethods \
    surfrec_io/extern/Eigen/Eigen/PaStiXSupport \
    surfrec_io/extern/Eigen/Eigen/PardisoSupport \
    surfrec_io/extern/Eigen/Eigen/QR \
    surfrec_io/extern/Eigen/Eigen/QtAlignedMalloc \
    surfrec_io/extern/Eigen/Eigen/SPQRSupport \
    surfrec_io/extern/Eigen/Eigen/SVD \
    surfrec_io/extern/Eigen/Eigen/Sparse \
    surfrec_io/extern/Eigen/Eigen/SparseCholesky \
    surfrec_io/extern/Eigen/Eigen/SparseCore \
    surfrec_io/extern/Eigen/Eigen/SparseLU \
    surfrec_io/extern/Eigen/Eigen/SparseQR \
    surfrec_io/extern/Eigen/Eigen/StdDeque \
    surfrec_io/extern/Eigen/Eigen/StdList \
    surfrec_io/extern/Eigen/Eigen/StdVector \
    surfrec_io/extern/Eigen/Eigen/SuperLUSupport \
    surfrec_io/extern/Eigen/Eigen/UmfPackSupport \
    surfrec_io/extern/Eigen/Eigen/src/Cholesky/LDLT.h \
    surfrec_io/extern/Eigen/Eigen/src/Cholesky/LLT.h \
    surfrec_io/extern/Eigen/Eigen/src/Cholesky/LLT_LAPACKE.h \
    surfrec_io/extern/Eigen/Eigen/src/CholmodSupport/CholmodSupport.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/ArithmeticSequence.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Array.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/ArrayBase.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/ArrayWrapper.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Assign.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/AssignEvaluator.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Assign_MKL.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/BandMatrix.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Block.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/BooleanRedux.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/CommaInitializer.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/ConditionEstimator.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/CoreEvaluators.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/CoreIterators.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/CwiseBinaryOp.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/CwiseNullaryOp.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/CwiseTernaryOp.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/CwiseUnaryOp.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/CwiseUnaryView.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/DenseBase.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/DenseCoeffsBase.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/DenseStorage.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Diagonal.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/DiagonalMatrix.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/DiagonalProduct.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Dot.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/EigenBase.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/ForceAlignedAccess.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Fuzzy.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/GeneralProduct.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/GenericPacketMath.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/GlobalFunctions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/IO.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/IndexedView.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Inverse.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Map.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/MapBase.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/MathFunctions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/MathFunctionsImpl.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Matrix.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/MatrixBase.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/NestByValue.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/NoAlias.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/NumTraits.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/PartialReduxEvaluator.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/PermutationMatrix.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/PlainObjectBase.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Product.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/ProductEvaluators.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Random.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Redux.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Ref.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Replicate.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Reshaped.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/ReturnByValue.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Reverse.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Select.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/SelfAdjointView.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/SelfCwiseBinaryOp.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Solve.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/SolveTriangular.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/SolverBase.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/StableNorm.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/StlIterators.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Stride.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Swap.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Transpose.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Transpositions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/TriangularMatrix.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/VectorBlock.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/VectorwiseOp.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/Visitor.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/AVX/Complex.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/AVX/MathFunctions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/AVX/PacketMath.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/AVX/TypeCasting.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/AVX512/Complex.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/AVX512/MathFunctions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/AVX512/PacketMath.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/AVX512/TypeCasting.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/AltiVec/Complex.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/AltiVec/MathFunctions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/AltiVec/PacketMath.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/CUDA/Complex.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/Default/ConjHelper.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/Default/GenericPacketMathFunctions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/Default/GenericPacketMathFunctionsFwd.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/Default/Half.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/Default/Settings.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/Default/TypeCasting.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/GPU/MathFunctions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/GPU/PacketMath.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/GPU/TypeCasting.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/HIP/hcc/math_constants.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/MSA/Complex.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/MSA/MathFunctions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/MSA/PacketMath.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/NEON/Complex.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/NEON/MathFunctions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/NEON/PacketMath.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/NEON/TypeCasting.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/SSE/Complex.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/SSE/MathFunctions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/SSE/PacketMath.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/SSE/TypeCasting.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/SYCL/InteropHeaders.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/SYCL/MathFunctions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/SYCL/PacketMath.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/SYCL/SyclMemoryModel.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/SYCL/TypeCasting.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/ZVector/Complex.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/ZVector/MathFunctions.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/arch/ZVector/PacketMath.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/functors/AssignmentFunctors.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/functors/BinaryFunctors.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/functors/NullaryFunctors.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/functors/StlFunctors.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/functors/TernaryFunctors.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/functors/UnaryFunctors.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/GeneralBlockPanelKernel.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/GeneralMatrixMatrix.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/GeneralMatrixMatrixTriangular_BLAS.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/GeneralMatrixMatrix_BLAS.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/GeneralMatrixVector.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/GeneralMatrixVector_BLAS.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/Parallelizer.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/SelfadjointMatrixMatrix.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/SelfadjointMatrixMatrix_BLAS.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/SelfadjointMatrixVector.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/SelfadjointMatrixVector_BLAS.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/SelfadjointProduct.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/SelfadjointRank2Update.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/TriangularMatrixMatrix.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/TriangularMatrixMatrix_BLAS.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/TriangularMatrixVector.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/TriangularMatrixVector_BLAS.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/TriangularSolverMatrix.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/TriangularSolverMatrix_BLAS.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/products/TriangularSolverVector.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/BlasUtil.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/ConfigureVectorization.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/Constants.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/DisableStupidWarnings.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/ForwardDeclarations.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/IndexedViewHelper.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/IntegralConstant.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/MKL_support.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/Macros.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/Memory.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/Meta.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/NonMPL2.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/ReenableStupidWarnings.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/ReshapedHelper.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/StaticAssert.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/SymbolicIndex.h \
    surfrec_io/extern/Eigen/Eigen/src/Core/util/XprHelper.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/ComplexEigenSolver.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/ComplexSchur.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/ComplexSchur_LAPACKE.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/EigenSolver.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/GeneralizedEigenSolver.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/HessenbergDecomposition.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/RealQZ.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/RealSchur.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/RealSchur_LAPACKE.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/SelfAdjointEigenSolver_LAPACKE.h \
    surfrec_io/extern/Eigen/Eigen/src/Eigenvalues/Tridiagonalization.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/AlignedBox.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/AngleAxis.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/EulerAngles.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/Homogeneous.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/Hyperplane.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/OrthoMethods.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/ParametrizedLine.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/Quaternion.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/Rotation2D.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/RotationBase.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/Scaling.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/Transform.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/Translation.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/Umeyama.h \
    surfrec_io/extern/Eigen/Eigen/src/Geometry/arch/Geometry_SSE.h \
    surfrec_io/extern/Eigen/Eigen/src/Householder/BlockHouseholder.h \
    surfrec_io/extern/Eigen/Eigen/src/Householder/Householder.h \
    surfrec_io/extern/Eigen/Eigen/src/Householder/HouseholderSequence.h \
    surfrec_io/extern/Eigen/Eigen/src/IterativeLinearSolvers/BasicPreconditioners.h \
    surfrec_io/extern/Eigen/Eigen/src/IterativeLinearSolvers/BiCGSTAB.h \
    surfrec_io/extern/Eigen/Eigen/src/IterativeLinearSolvers/ConjugateGradient.h \
    surfrec_io/extern/Eigen/Eigen/src/IterativeLinearSolvers/IncompleteCholesky.h \
    surfrec_io/extern/Eigen/Eigen/src/IterativeLinearSolvers/IncompleteLUT.h \
    surfrec_io/extern/Eigen/Eigen/src/IterativeLinearSolvers/IterativeSolverBase.h \
    surfrec_io/extern/Eigen/Eigen/src/IterativeLinearSolvers/LeastSquareConjugateGradient.h \
    surfrec_io/extern/Eigen/Eigen/src/IterativeLinearSolvers/SolveWithGuess.h \
    surfrec_io/extern/Eigen/Eigen/src/Jacobi/Jacobi.h \
    surfrec_io/extern/Eigen/Eigen/src/KLUSupport/KLUSupport.h \
    surfrec_io/extern/Eigen/Eigen/src/LU/Determinant.h \
    surfrec_io/extern/Eigen/Eigen/src/LU/FullPivLU.h \
    surfrec_io/extern/Eigen/Eigen/src/LU/InverseImpl.h \
    surfrec_io/extern/Eigen/Eigen/src/LU/PartialPivLU.h \
    surfrec_io/extern/Eigen/Eigen/src/LU/PartialPivLU_LAPACKE.h \
    surfrec_io/extern/Eigen/Eigen/src/LU/arch/Inverse_SSE.h \
    surfrec_io/extern/Eigen/Eigen/src/MetisSupport/MetisSupport.h \
    surfrec_io/extern/Eigen/Eigen/src/OrderingMethods/Amd.h \
    surfrec_io/extern/Eigen/Eigen/src/OrderingMethods/Eigen_Colamd.h \
    surfrec_io/extern/Eigen/Eigen/src/OrderingMethods/Ordering.h \
    surfrec_io/extern/Eigen/Eigen/src/PaStiXSupport/PaStiXSupport.h \
    surfrec_io/extern/Eigen/Eigen/src/PardisoSupport/PardisoSupport.h \
    surfrec_io/extern/Eigen/Eigen/src/QR/ColPivHouseholderQR.h \
    surfrec_io/extern/Eigen/Eigen/src/QR/ColPivHouseholderQR_LAPACKE.h \
    surfrec_io/extern/Eigen/Eigen/src/QR/CompleteOrthogonalDecomposition.h \
    surfrec_io/extern/Eigen/Eigen/src/QR/FullPivHouseholderQR.h \
    surfrec_io/extern/Eigen/Eigen/src/QR/HouseholderQR.h \
    surfrec_io/extern/Eigen/Eigen/src/QR/HouseholderQR_LAPACKE.h \
    surfrec_io/extern/Eigen/Eigen/src/SPQRSupport/SuiteSparseQRSupport.h \
    surfrec_io/extern/Eigen/Eigen/src/SVD/BDCSVD.h \
    surfrec_io/extern/Eigen/Eigen/src/SVD/JacobiSVD.h \
    surfrec_io/extern/Eigen/Eigen/src/SVD/JacobiSVD_LAPACKE.h \
    surfrec_io/extern/Eigen/Eigen/src/SVD/SVDBase.h \
    surfrec_io/extern/Eigen/Eigen/src/SVD/UpperBidiagonalization.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCholesky/SimplicialCholesky.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCholesky/SimplicialCholesky_impl.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/AmbiVector.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/CompressedStorage.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/ConservativeSparseSparseProduct.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/MappedSparseMatrix.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseAssign.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseBlock.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseColEtree.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseCompressedBase.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseCwiseBinaryOp.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseCwiseUnaryOp.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseDenseProduct.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseDiagonalProduct.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseDot.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseFuzzy.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseMap.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseMatrix.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseMatrixBase.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparsePermutation.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseProduct.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseRedux.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseRef.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseSelfAdjointView.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseSolverBase.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseSparseProductWithPruning.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseTranspose.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseTriangularView.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseUtil.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseVector.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/SparseView.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseCore/TriangularSolver.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLUImpl.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_Memory.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_Structs.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_SupernodalMatrix.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_Utils.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_column_bmod.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_column_dfs.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_copy_to_ucol.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_gemm_kernel.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_heap_relax_snode.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_kernel_bmod.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_panel_bmod.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_panel_dfs.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_pivotL.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_pruneL.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseLU/SparseLU_relax_snode.h \
    surfrec_io/extern/Eigen/Eigen/src/SparseQR/SparseQR.h \
    surfrec_io/extern/Eigen/Eigen/src/StlSupport/StdDeque.h \
    surfrec_io/extern/Eigen/Eigen/src/StlSupport/StdList.h \
    surfrec_io/extern/Eigen/Eigen/src/StlSupport/StdVector.h \
    surfrec_io/extern/Eigen/Eigen/src/StlSupport/details.h \
    surfrec_io/extern/Eigen/Eigen/src/SuperLUSupport/SuperLUSupport.h \
    surfrec_io/extern/Eigen/Eigen/src/UmfPackSupport/UmfPackSupport.h \
    surfrec_io/extern/Eigen/Eigen/src/misc/Image.h \
    surfrec_io/extern/Eigen/Eigen/src/misc/Kernel.h \
    surfrec_io/extern/Eigen/Eigen/src/misc/RealSvd2x2.h \
    surfrec_io/extern/Eigen/Eigen/src/misc/blas.h \
    surfrec_io/extern/Eigen/Eigen/src/misc/lapack.h \
    surfrec_io/extern/Eigen/Eigen/src/misc/lapacke.h \
    surfrec_io/extern/Eigen/Eigen/src/misc/lapacke_mangling.h \
    surfrec_io/extern/Eigen/Eigen/src/plugins/ArrayCwiseBinaryOps.h \
    surfrec_io/extern/Eigen/Eigen/src/plugins/ArrayCwiseUnaryOps.h \
    surfrec_io/extern/Eigen/Eigen/src/plugins/BlockMethods.h \
    surfrec_io/extern/Eigen/Eigen/src/plugins/CommonCwiseBinaryOps.h \
    surfrec_io/extern/Eigen/Eigen/src/plugins/CommonCwiseUnaryOps.h \
    surfrec_io/extern/Eigen/Eigen/src/plugins/IndexedViewMethods.h \
    surfrec_io/extern/Eigen/Eigen/src/plugins/MatrixCwiseBinaryOps.h \
    surfrec_io/extern/Eigen/Eigen/src/plugins/MatrixCwiseUnaryOps.h \
    surfrec_io/extern/Eigen/Eigen/src/plugins/ReshapedMethods.h \
    surfrec_io/extern/happly.h \
    surfrec_io/extern/partio/src/lib/Partio.h \
    surfrec_io/extern/partio/src/lib/PartioAttribute.h \
    surfrec_io/extern/partio/src/lib/PartioConfig.h \
    surfrec_io/extern/partio/src/lib/PartioIterator.h \
    surfrec_io/extern/partio/src/lib/PartioVec3.h \
    surfrec_io/extern/partio/src/lib/core/KdTree.h \
    surfrec_io/extern/partio/src/lib/core/Mutex.h \
    surfrec_io/extern/partio/src/lib/core/ParticleCaching.h \
    surfrec_io/extern/partio/src/lib/core/ParticleHeaders.h \
    surfrec_io/extern/partio/src/lib/core/ParticleSimple.h \
    surfrec_io/extern/partio/src/lib/core/ParticleSimpleInterleave.h \
    surfrec_io/extern/partio/src/lib/io/PartioEndian.h \
    surfrec_io/extern/partio/src/lib/io/ZIP.h \
    surfrec_io/extern/partio/src/lib/io/half2float.h \
    surfrec_io/extern/partio/src/lib/io/pdb.h \
    surfrec_io/extern/partio/src/lib/io/readers.h \
    surfrec_io/extern/vtkio/ByteBuffer.h \
    surfrec_io/extern/vtkio/VTKStream.h \
    surfrec_io/extern/vtkio/dynamic_types.h \
    surfrec_io/extern/vtkio/endianness.h \
    surfrec_io/extern/vtkio/stream_io.h \
    surfrec_io/extern/vtkio/tables.h \
    surfrec_io/extern/zlib/src/crc32.h \
    surfrec_io/extern/zlib/src/deflate.h \
    surfrec_io/extern/zlib/src/inffast.h \
    surfrec_io/extern/zlib/src/inffixed.h \
    surfrec_io/extern/zlib/src/inflate.h \
    surfrec_io/extern/zlib/src/inftrees.h \
    surfrec_io/extern/zlib/src/trees.h \
    surfrec_io/extern/zlib/src/zconf.h \
    surfrec_io/extern/zlib/src/zlib.h \
    surfrec_io/extern/zlib/src/zutil.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    resources.qrc

DISTFILES += \
    CompactNSearch/.github/workflows/build-linux.yml \
    CompactNSearch/.github/workflows/build-windows.yml \
    CompactNSearch/CMakeLists.txt \
    CompactNSearch/LICENSE \
    CompactNSearch/README.md \
    CompactNSearch/demo/CMakeLists.txt \
    CompactNSearch/extern/libmorton/LICENSE \
    CompactNSearch/extern/libmorton/README.md \
    surfrec_io/extern/Eigen/CMakeLists.txt \
    surfrec_io/extern/Eigen/signature_of_eigen3_matrix_library \
    surfrec_io/extern/partio/CMakeLists.txt \
    surfrec_io/extern/partio/README \
    surfrec_io/extern/partio/src/lib/CMakeLists.txt \
    surfrec_io/extern/zlib/CMakeLists.txt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/OpenMesh/Lib/ -lOpenMeshCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/OpenMesh/Lib/ -lOpenMeshCored
else:unix: LIBS += -L$$PWD/OpenMesh/Lib/ -lOpenMeshCore

INCLUDEPATH += $$PWD/OpenMesh/Core
DEPENDPATH += $$PWD/OpenMesh/Core

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/OpenMesh/Lib/ -lOpenMeshTools
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/OpenMesh/Lib/ -lOpenMeshToolsd
else:unix: LIBS += -L$$PWD/OpenMesh/Lib/ -lOpenMeshTools

INCLUDEPATH += $$PWD/OpenMesh/Tools
DEPENDPATH += $$PWD/OpenMesh/Tools
