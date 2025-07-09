#include <iostream>
#include <cmath>
#include "punto.hpp"

template <typename T>
class Vector {
private:
    Punto<T> p;

public:
    // Constructor por defecto
    Vector() : p(0, 0, 0) {};

    // Constructor con coordenadas x e y (z = 0)
    Vector(T x, T y) : p(x, y, 0) {};

    // Constructor con 3 coordenadas
    Vector(T x, T y, T z) : p(x, y, z) {}

    // Constructor con Punto
    Vector(Punto<T> punto) : p(punto) {};

    // Constructor copia 
    Vector(const Vector<T>& otro) : p(otro.p) {};

    // Valores deben mantenerse como T, a menos que haya una raíz cuadrada, que los fuerza a double.

    // Magnitud del vector
    double magnitud() const {
        return std::sqrt(
            p.get_x() * p.get_x() +
            p.get_y() * p.get_y() +
            p.get_z() * p.get_z()
        );
    }

    // Producto Punto
    T producto_punto(const Vector<T>& otro) const {
        return p.get_x() * otro.p.get_x()
            + p.get_y() * otro.p.get_y()
            + p.get_z() * otro.p.get_z();
    }

    // Producto Cruz
    Vector<T> producto_cruz(const Vector<T>& otro) const {
        T z = p.get_x() * otro.p.get_z() - p.get_y() * otro.p.get_x();
        return Vector<T>(0, 0, z);
    }

    // Suma +
    Vector<T> operator+(const Vector<T>& otro) const {
        return Vector<T>(p.get_x() + otro.p.get_x(),
            p.get_y() + otro.p.get_y(),
            p.get_z() + otro.p.get_z()
        );
    }

    // Comparación == (es suficiente???)
    bool operator==(const Vector<T>& otro) const {
        return p == otro.p;
    }

    // Multiplicación por un escalar
    Vector<T> operator*(T escalar) const {
        return Vector<T>(
            p.get_x() * escalar, 
            p.get_y() * escalar,
            p.get_z() * escalar
        );
    }

    // Imprimir vector
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
        os << "(" << v.p.get_x() << "," << v.p.get_y() << "," << v.p.get_z() << ")";
        return os; 
    }

};