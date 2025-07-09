#ifndef UTILS_HPP
#define UTILS_HPP

#include "punto.hpp"

inline double cross(const Punto<double>& o, const Punto<double>& a, const Punto<double>& b) {
    return (a.get_x() - o.get_x()) * (b.get_y() - o.get_y()) - 
           (a.get_y() - o.get_y()) * (b.get_x() - o.get_x());
}

inline double dist2(const Punto<double>& a, const Punto<double>& b) {
    return (a.get_x() - b.get_x()) * (a.get_x() - b.get_x()) + 
           (a.get_y() - b.get_y()) * (a.get_y() - b.get_y());
}

#endif
