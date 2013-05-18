#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>

template<class T,int N>
struct Vector {
    T values[N];

    Vector& operator +=(const Vector& v) {
        for(int i=0;i<N;++i) {
            values[i] += v[i];
        }
        return *this;
    }
    Vector& operator -=(const Vector& v) {
        for(int i=0;i<N;++i) {
            values[i] -= v[i];
        }
        return *this;
    }
    Vector& operator *=(T s) {
        for(int i=0;i<N;++i) {
            values[i] *= s;
        }
        return *this;
    }
    Vector& operator /=(T s) {
        s = 1/s;
        for(int i=0;i<N;++i) {
            values[i] *= s;
        }
        return *this;
    }
    Vector operator+(const Vector& v) const {
        Vector ret = *this;
        return (ret += v);
    }
    Vector operator-(const Vector& v) const {
        Vector ret = *this;
        return (ret -= v);
    }
    Vector operator*(T s) const {
        Vector ret = *this;
        return (ret *= s);
    }
    Vector operator/(T s) const {
        return *this * (1/s);
    }

    T& operator[](size_t n) {
        return values[n];
    }
    const T& operator[](size_t n) const {
        return values[n];
    }

    T magSquared() const {
        T ret = 0;
        for(int i=0;i<N;++i) {
            ret += values[i]*values[i];
        }
        return ret;
    }
    T mag() const {
        return std::sqrt(this->magSquared());
    }
};

template<class T,int N>
Vector<T,N> operator*(T s,Vector<T,N> v) {
    return v*s;
}

template<class T,int N>
Vector<T,N> norm(const Vector<T,N>& v) {
    return v/v.mag();
}
template<class T,int N>
Vector<T,N> dot(const Vector<T,N>& a,const Vector<T,N>& b) {
    T ret = 0;
    for(int i=0;i<N;++i) {
        ret += a[i]*b[i];
    }
    return ret;
}

typedef Vector<float,2>  Vec2f;
typedef Vector<float,3>  Vec3f;
typedef Vector<double,2> Vec2d;
typedef Vector<double,3> Vec3d;

#endif
