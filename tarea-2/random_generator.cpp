#include "generator_strategies.hpp"
#include <random>

class RandomGenerator : public PointGenerator {
public:
    std::vector<Punto<double>> generate(int n, double porcentaje = 0.0) override {
        std::vector<Punto<double>> puntos;
        std::default_random_engine rng(std::random_device{}());
        std::uniform_real_distribution<double> dist(0, 1000);

        for (int i = 0; i < n; ++i) {
            puntos.emplace_back(dist(rng), dist(rng));
        }

        return puntos;
    }
};
