#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "punto.hpp"
#include "poligono.hpp"
#include "convex_hull_strategies.hpp"

// Verifica si dos polígonos son equivalentes (rotación o reverso)
bool poligonos_equivalentes(const Poligono<double>& a, const Poligono<double>& b) {
    const auto& ptsA = a.get_vertices();
    const auto& ptsB = b.get_vertices();
    if (ptsA.size() != ptsB.size()) return false;

    int n = ptsA.size();
    for (int shift = 0; shift < n; ++shift) {
        bool iguales = true;
        for (int i = 0; i < n; ++i) {
            if (!(ptsA[i] == ptsB[(i + shift) % n])) {
                iguales = false;
                break;
            }
        }
        if (iguales) return true;

        iguales = true;
        for (int i = 0; i < n; ++i) {
            if (!(ptsA[i] == ptsB[(n - i + shift) % n])) {
                iguales = false;
                break;
            }
        }
        if (iguales) return true;
    }

    return false;
}

// Para los tests
void test_case(const std::vector<Punto<double>>& puntos, const std::string& nombre) {
    GrahamScanAlgorithm graham;
    GiftWrappingAlgorithm gift;

    Poligono<double> hull1 = graham.apply(puntos);
    Poligono<double> hull2 = gift.apply(puntos);

    // Casos esperados vacíos
    if (puntos.size() < 3) {
        if (hull1.num_vertices() == 0 && hull2.num_vertices() == 0) {
            std::cout << "yay! " << nombre << ": sin cerradura convexa (esperado)\n";
        } else {
            std::cout << "cuek " << nombre << ": debería ser vacío\n";
        }
        return;
    }

    if (poligonos_equivalentes(hull1, hull2)) {
        std::cout << "yay! " << nombre << ": los resultados coinciden\n";
    } else {
        std::cout << "cuek " << nombre << ": los algoritmos dan resultados distintos\n";
        std::cout << " Graham: ";
        for (const auto& p : hull1.get_vertices()) std::cout << p << " ";
        std::cout << "\n Gift:   ";
        for (const auto& p : hull2.get_vertices()) std::cout << p << " ";
        std::cout << "\n";
    }
}

int main() {
    test_case({}, "Vacío");
    test_case({{1, 2}}, "Un solo punto");
    test_case({{0, 0}, {1, 1}}, "Dos puntos");
    test_case({{0, 0}, {1, 0}, {0.5, 1}}, "Triángulo simple");
    test_case({{0, 0}, {0, 1}, {1, 0}, {1, 1}}, "Cuadrado");
    test_case({{0, 0}, {1, 1}, {2, 0}}, "Triángulo sin internos");
    return 0;
}
