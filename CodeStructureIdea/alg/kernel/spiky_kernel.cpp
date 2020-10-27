spikyKernel::spikyKernel() {}

void spikyKernel::setRadius(float compactSupport) {
    h_ = compactSupport;
    a_ = 15/((M_PI)*pow(h_,6));
}
    

double spikyKernel::evaluate(particle& p1, particle& p2) {

    float xDistance = p2.x() - p1.x();
    float yDistance = p2.y() - p1.y();
    float zDistance = p2.z() - p1.z();

    float r = sqrt( (xDistance*xDistance) + (yDistance*yDistance) + (zDistance*zDistance));
    float result = 0.0;

    if ((r >= 0) && (r <= h_)) {result = pow(h_-r,3);}
    else {return 0;}
    return a_*result;
}

