cubicSplineKernel::cubicSplineKernel() {}

void cubicSplineKernel::setRadius(float compactSupport) {
    h_ = compactSupport;
    a_ = 3.0/(2.0*(M_PI));
}

float cubicSplineKernel::evaluate(float x, float y, float z, particle p2) {

    float xDistance = x - p2.x();
    float yDistance = y - p2.y();
    float zDistance = z - p2.z();

    float r = sqrt((xDistance*xDistance) + (yDistance*yDistance) + (zDistance*zDistance));
    float q = r / h_;  
    float q2 = q*q;
    float q3 = q2*q;

    //std::complex<float> resultantParticle(xVal, yVal);
    //float q = (std::norm(resultantParticle)+(zVal*zVal)) / h;
    float result = 0.0;

    if ((q >= 0) && (q < 1)) {result = ((2.0/3.0) - q2 + (q3/2.0));} 
    if ((q >= 1) && (q < 2)) {result = (pow(2-q,3)/6.0);}
    if (q >= 2) {return 0.0;}
 
    return a_*result;
}

float cubicSplineKernel::evaluate(particle p1, particle p2) {

    float xDistance = p1.x() - p2.x();
    float yDistance = p1.y() - p2.y();
    float zDistance = p1.z() - p2.z();

    float r = sqrt((xDistance*xDistance) + (yDistance*yDistance) + (zDistance*zDistance));
    float q = r / h_;  
    float q2 = q*q;
    float q3 = q2*q;

    //std::complex<float> resultantParticle(xVal, yVal);
    //float q = (std::norm(resultantParticle)+(zVal*zVal)) / h;
    float result = 0.0;

    if ((q >= 0) && (q < 1)) {result = ((2.0/3.0) - q2 + (q3/2.0));} 
    if ((q >= 1) && (q < 2)) {result = (pow(2-q,3)/6.0);}
    if (q >= 2) {return 0.0;}
 
    return a_*result;
}

