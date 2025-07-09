#ifndef PUNTO_HPP
#define PUNTO_HPP

#include <iostream>
#include <cmath>

template <typename T>
class Punto {
private:
    T x;
    T y;
    T z;

public:
    // Constructor por defecto
    Punto() : x(0), y(0), z(0) {}

    // Constructor con dos coordenadas (2D)
    Punto(T x, T y) : x(x), y(y), z(0) {}

    // Constructor con tres coordenadas (3D)
    Punto(T x, T y, T z) : x(x), y(y), z(z) {}

    // Constructor de copia
    Punto(const Punto<T>& otro) : x(otro.x), y(otro.y), z(otro.z) {}

    // Método para calcular distancia
    T distancia(const Punto<T>& otro) const {
        T dx = x - otro.x;
        T dy = y - otro.y;
        T dz = z - otro.z;
        return std::sqrt(dx*dx + dy*dy + dz*dz);
    }

    // Sobrecarga del operador ==
    bool operator==(const Punto<T>& otro) const {
        return (x == otro.x && y == otro.y && z == otro.z);
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream& os, const Punto<T>& p) {
        os << "(" << p.x << "," << p.y << "," << p.z << ")";
        return os;
    }

    // Getters
    T get_x() const { return x; }
    T get_y() const { return y; }
    T get_z() const { return z; }
    
};
#endif