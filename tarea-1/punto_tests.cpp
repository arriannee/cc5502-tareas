#include <cassert>
#include <iostream>
#include "punto.hpp"

void test_constructor() {
    Punto<double> p1(1.0, 2.0, 3.0);
    assert(p1 == Punto<double>(1.0, 2.0, 3.0));

    Punto<int> p2(4, 5);
    assert(p2 == Punto<int>(4, 5, 0));  // El constructor 2D pone z=0 por defecto
}

void test_distancia() {
    Punto<double> a(0.0, 0.0, 0.0);
    Punto<double> b(3.0, 4.0, 0.0);
    assert(a.distancia(b) == 5.0);  // Teorema de Pitágoras

    Punto<double> c(1.0, 2.0, 2.0);
    Punto<double> d(4.0, 6.0, 6.0);
    double dist = c.distancia(d);
    assert(std::abs(dist - 6.4031) < 0.0001);  // Distancia 3D con tolerancia
}

void test_igualdad() {
    Punto<int> p1(1, 2, 3);
    Punto<int> p2(1, 2, 3);
    Punto<int> p3(4, 5, 6);

    assert(p1 == p2);
    assert(!(p1 == p3));
}

int main() {
    test_constructor();
    test_distancia();
    test_igualdad();

    std::cout << "Todos los tests pasaron correctamente." << std::endl;
    return 0;
}
