#include "convex_hull_strategies.hpp"
#include "poligono.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cmath>


Poligono<double> GiftWrappingAlgorithm::apply(const std::vector<Punto<double>>& cloud) {
    if (cloud.size() < 3) return Poligono<double>();  // No hay cerradura convexa

    std::vector<Punto<double>> hull;
    int leftmost = 0;

    // Encontrar el punto más a la izquierda
    for (int i = 1; i < cloud.size(); ++i) {
        if (cloud[i].get_x() < cloud[leftmost].get_x() ||
           (cloud[i].get_x() == cloud[leftmost].get_x() && cloud[i].get_y() < cloud[leftmost].get_y())) {
            leftmost = i;
        }
    }

    int p = leftmost;
    do {
        hull.push_back(cloud[p]);
        int q = (p + 1) % cloud.size();

        for (int r = 0; r < cloud.size(); ++r) {
            if (cross(cloud[p], cloud[q], cloud[r]) < 0) {
                q = r;
            }
        }

        p = q;
    } while (p != leftmost);

    return Poligono<double>(hull);
}
