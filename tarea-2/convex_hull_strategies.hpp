#ifndef CONVEX_HULL_STRATEGIES_HPP
#define CONVEX_HULL_STRATEGIES_HPP

#include "punto.hpp"
#include "poligono.hpp"
#include <vector>

// Clase base: Strategy
class ConvexHullStrategy {
public:
    virtual Poligono<double> apply(const std::vector<Punto<double>>& cloud) = 0;
    virtual ~ConvexHullStrategy() = default;
};

// Gift Wrapping Algorithm (Jarvis March)
class GiftWrappingAlgorithm : public ConvexHullStrategy {
public:
    Poligono<double> apply(const std::vector<Punto<double>>& cloud) override;
};

// Graham Scan Algorithm
class GrahamScanAlgorithm : public ConvexHullStrategy {
public:
    Poligono<double> apply(const std::vector<Punto<double>>& cloud) override;
};

#endif
