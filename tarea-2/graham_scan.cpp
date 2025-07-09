#include "convex_hull_strategies.hpp"
#include "poligono.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cmath>

Poligono<double> GrahamScanAlgorithm::apply(const std::vector<Punto<double>>& cloud) {
    if (cloud.size() < 3) return Poligono<double>();  // No hay cerradura convexa

    std::vector<Punto<double>> puntos = cloud;

    // Paso 1: Encontrar el punto más abajo a la izquierda
    auto p0 = *std::min_element(puntos.begin(), puntos.end(), [](const Punto<double>& a, const Punto<double>& b) {
        return (a.get_y() < b.get_y()) || (a.get_y() == b.get_y() && a.get_x() < b.get_x());
    });

    // Paso 2: Ordenar por ángulo polar respecto a p0
    std::sort(puntos.begin(), puntos.end(), [&](const Punto<double>& a, const Punto<double>& b) {
        double cp = cross(p0, a, b);
        if (cp == 0)
            return dist2(p0, a) < dist2(p0, b);  // Puntos colineales: ordenar por cercanía
        return cp > 0; // menor ángulo => a más a la izquierda que b
    });

    // Paso 3: Construir la cerradura con stack (aquí usamos vector)
    std::vector<Punto<double>> hull;
    for (const auto& p : puntos) {
        while (hull.size() >= 2 && cross(hull[hull.size()-2], hull[hull.size()-1], p) <= 0) {
            hull.pop_back();  // Remueve el que forma giro hacia la derecha
        }
        hull.push_back(p);
    }

    return Poligono<double>(hull);
}