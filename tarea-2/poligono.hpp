#ifndef POLIGONO_HPP
#define POLIGONO_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> // para std::reverse
#include "punto.hpp"

template <typename T>
class Poligono {
private:
    std::vector<Punto<T>> vertices;

public:
    // Constructor por defecto
    Poligono() = default;

    const std::vector<Punto<T>>& get_vertices() const {
        return vertices;
    }

    // Constructor que recibe un vector de puntos
    Poligono(const std::vector<Punto<T>>& puntos) : vertices(puntos) {}

    // Agrega un punto al polígono
    void agregar_vertice(const Punto<T>& p) {
        vertices.push_back(p);
    }

    // Retorna el número de vértices
    int num_vertices() const {
        return vertices.size();
    }

    // Retorna true si está en counterclockwise
    bool es_ccw() const {
        return area2() > 0;
    }

    // Invierte el orden si está en sentido horario
    void hacer_ccw() {
        if (!es_ccw()) {
            std::reverse(vertices.begin(), vertices.end());
        }
    }

    // Calcula el doble del área (shoelace sin dividir)
    T area2() const;

    // Calcula el área real (como double)
    double area() const {
        return std::abs(static_cast<double>(area2())) / 2.0;
    }

    // Calcula el perímetro
    double perimetro() const;

    // Acceso a vértices por índice
    Punto<T>& operator[](int i) {
        return vertices[i];
    }

    const Punto<T>& operator[](int i) const {
        return vertices[i];
    }

    // Operador << para imprimir el polígono
    friend std::ostream& operator<<(std::ostream& os, const Poligono<T>& poly) {
        os << "[";
        for (size_t i = 0; i < poly.vertices.size(); ++i) {
            os << poly.vertices[i];
            if (i != poly.vertices.size() - 1)
                os << ", ";
        }
        os << "]";
        return os;
    }
};

// Implementación de área2
template <typename T>
T Poligono<T>::area2() const {
    T suma = 0;
    int n = vertices.size();
    if (n < 3) return 0;

    for (int i = 0; i < n; ++i) {
        const Punto<T>& a = vertices[i];
        const Punto<T>& b = vertices[(i + 1) % n];
        suma += a.get_x() * b.get_y() - b.get_x() * a.get_y();
    }

    return suma;
}

// Implementación de perímetro
template <typename T>
double Poligono<T>::perimetro() const {
    double suma = 0.0;
    int n = vertices.size();
    if (n < 2) return 0.0;

    for (int i = 0; i < n; ++i) {
        const Punto<T>& a = vertices[i];
        const Punto<T>& b = vertices[(i + 1) % n];

        double dx = static_cast<double>(b.get_x() - a.get_x());
        double dy = static_cast<double>(b.get_y() - a.get_y());

        suma += std::sqrt(dx * dx + dy * dy);
    }

    return suma;
}

#endif
