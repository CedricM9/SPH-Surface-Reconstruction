template<typename T>
particle<T>::particle(T x, T y, T z) : x_(x), y_(y), z_(z) {}

template<typename T>
T& particle<T>::x() {
    return x_;
}

template<typename T>
T& particle<T>::y() {
    return y_;
}

template<typename T>
T& particle<T>::z() {
    return z_;
}

