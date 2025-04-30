#include <iostream>
#include <cassert>
#include "poligono.hpp"

int main() {
    // Triángulo CW: (0,0), (4,3), (4,0)
    std::vector<Punto<int>> puntos = {
        Punto<int>(0, 0, 0),
        Punto<int>(4, 3, 0),
        Punto<int>(4, 0, 0)
    };

    Poligono<int> poligono(puntos);

    // Test número de vértices
    assert(poligono.num_vertices() == 3);

    // Test impresión
    std::cout << "Poligono: " << poligono << std::endl;

    // Test acceso por índice
    assert(poligono[1] == Punto<int>(4, 3, 0));

    // Test orientación
    std::cout << "Es CCW: " << std::boolalpha << poligono.es_ccw() << std::endl;
    assert(poligono.es_ccw() == false);

    // Test corrección de orientación
    poligono.hacer_ccw();
    std::cout << "Es CCW ahora?: " << std::boolalpha << poligono.es_ccw() << std::endl;
    assert(poligono.es_ccw() == true);

    // Test perímetro (de triángulo 3-4-5)
    double per = poligono.perimetro();
    std::cout << "Perimetro: " << per << std::endl;
    assert(std::abs(per - 12.0) < 1e-6);

    // Test área doble
    int a2 = poligono.area2();
    std::cout << "Area * 2: " << a2 << std::endl;
    assert(a2 == 12);

    // Test área normal
    double area = poligono.area();
    std::cout << "Area: " << area << std::endl;
    assert(std::abs(area - 6.0) < 1e-6);

    std::cout << "Todos los tests pasaron correctamente." << std::endl;
    return 0;
}
