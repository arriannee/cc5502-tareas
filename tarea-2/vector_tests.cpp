#include <cassert>
#include <iostream>
#include "vector.hpp"

using namespace std;

void test_constructor_y_igualdad() {
    Vector<double> v1(1.0, 2.0);
    Vector<double> v2(Punto<double>(1.0, 2.0));
    assert(v1 == v2);
}

void test_magnitud() {
    Vector<double> v(3.0, 4.0);  // magnitud = 5
    assert(v.magnitud() == 5.0);
}

void test_producto_punto() {
    Vector<double> a(1.0, 2.0);
    Vector<double> b(3.0, 4.0);
    double resultado = a.producto_punto(b);  // 1*3 + 2*4 = 11
    assert(resultado == 11.0);
}

void test_producto_cruz() {
    Vector<double> a(1.0, 0.0);
    Vector<double> b(0.0, 1.0);
    Vector<double> cruz = a.producto_cruz(b);  // debería dar (0,0,1)
    assert(cruz == Vector<double>(0.0, 0.0)); // solo trabajamos con x, y
}

void test_suma() {
    Vector<double> a(1.0, 2.0);
    Vector<double> b(3.0, 4.0);
    Vector<double> suma = a + b;
    assert(suma == Vector<double>(4.0, 6.0));
}

void test_escalar() {
    Vector<double> a(2.0, 3.0);
    Vector<double> resultado = a * 2;
    assert(resultado == Vector<double>(4.0, 6.0));
}

int main() {
    test_constructor_y_igualdad();
    test_magnitud();
    test_producto_punto();
    test_producto_cruz();
    test_suma();
    test_escalar();

    cout << "Todos los tests de Vector<T> pasaron correctamente. c:" << endl;
    return 0;
}