#ifndef GENERATOR_STRATEGY_HPP
#define GENERATOR_STRATEGY_HPP

#include <vector>
#include "punto.hpp"

class PointGenerator {
public:
    virtual std::vector<Punto<double>> generate(int n, double porcentaje = 0.0) = 0;
    virtual ~PointGenerator() = default;
};

#endif
