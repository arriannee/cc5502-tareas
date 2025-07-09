#include "generator_strategies.hpp"
#include <random>
#include <cmath>

class ConvexMixtureGenerator : public PointGenerator {
public:
    std::vector<Punto<double>> generate(int n, double porcentaje) override {
        std::vector<Punto<double>> puntos;
        int n_hull = n * porcentaje;
        int n_inside = n - n_hull;

        std::default_random_engine rng(std::random_device{}());
        std::uniform_real_distribution<double> angle_dist(0, 2 * M_PI);
        std::uniform_real_distribution<double> radius_dist(400, 500);
        std::uniform_real_distribution<double> inside_dist(100, 400);

        // Puntos en la envolvente (en forma de círculo)
        for (int i = 0; i < n_hull; ++i) {
            double angle = angle_dist(rng);
            double r = radius_dist(rng);
            puntos.emplace_back(std::cos(angle) * r + 500, std::sin(angle) * r + 500);
        }

        // Puntos dentro
        for (int i = 0; i < n_inside; ++i) {
            puntos.emplace_back(inside_dist(rng), inside_dist(rng));
        }

        return puntos;
    }
};
