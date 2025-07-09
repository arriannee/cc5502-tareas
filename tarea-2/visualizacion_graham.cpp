#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include "punto.hpp"
#include "poligono.hpp"

std::vector<Punto<double>> leer_puntos(const std::string& archivo) {
    std::ifstream in(archivo);
    std::vector<Punto<double>> puntos;
    double x, y;
    while (in >> x >> y) {
        puntos.emplace_back(x, y);
    }
    return puntos;
}

// Para poder visualizar paso a paso
void drawHull(sf::RenderWindow& window, const std::vector<Punto<double>>& puntos, const std::vector<Punto<double>>& hull, float scale) {
    window.clear(sf::Color::White);

    // Dibujar puntos originales
    for (const auto& p : puntos) {
        sf::CircleShape circle(2);
        circle.setFillColor(sf::Color::Black);
        circle.setPosition(p.get_x() * scale, p.get_y() * scale);
        window.draw(circle);
    }

    // Dibujar líneas del hull
    if (hull.size() >= 2) {
        sf::VertexArray lines(sf::LineStrip, hull.size() + 1);
        for (size_t i = 0; i < hull.size(); ++i) {
            lines[i].position = sf::Vector2f(hull[i].get_x() * scale, hull[i].get_y() * scale);
            lines[i].color = sf::Color::Red;
        }
        // Cerrar la figura
        lines[hull.size()].position = sf::Vector2f(hull[0].get_x() * scale, hull[0].get_y() * scale);
        lines[hull.size()].color = sf::Color::Red;
        window.draw(lines);
    }

    window.display();
    sf::sleep(sf::milliseconds(100)); // tiempo entre pasos
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Graham Scan Visualization");

    std::vector<Punto<double>> puntos = leer_puntos("puntos.txt");

    std::vector<Punto<double>> ordenados = puntos;

    // Encontrar el punto más abajo a la izquierda
    auto it = std::min_element(ordenados.begin(), ordenados.end(), [](const auto& a, const auto& b) {
        return (a.get_y() < b.get_y()) || (a.get_y() == b.get_y() && a.get_x() < b.get_x());
    });
    std::iter_swap(ordenados.begin(), it);
    const auto& p0 = ordenados[0]; // p0 seguro al inicio


    // Ordenar por ángulo polar
    std::sort(ordenados.begin() + 1, ordenados.end(), [&](const auto& a, const auto& b) {
        double cp = (a.get_x() - p0.get_x()) * (b.get_y() - p0.get_y()) - (a.get_y() - p0.get_y()) * (b.get_x() - p0.get_x());
        if (cp == 0) {
            double da = std::pow(a.get_x() - p0.get_x(), 2) + std::pow(a.get_y() - p0.get_y(), 2);
            double db = std::pow(b.get_x() - p0.get_x(), 2) + std::pow(b.get_y() - p0.get_y(), 2);
            return da < db;
        }
        return cp > 0;
    });

    std::vector<Punto<double>> hull;

    for (const auto& p : ordenados) {
        while (hull.size() >= 2) {
            const auto& a = hull[hull.size() - 2];
            const auto& b = hull[hull.size() - 1];
            double cp = (b.get_x() - a.get_x()) * (p.get_y() - a.get_y()) - (b.get_y() - a.get_y()) * (p.get_x() - a.get_x());
            if (cp <= 0) {
                hull.pop_back();
            } else break;
        }
        hull.push_back(p);
        drawHull(window, puntos, hull, 1.0f); // visualizar paso a paso
    }

    Poligono<double> poligono(hull);
    if (!poligono.es_ccw()) {
        std::reverse(hull.begin(), hull.end());
    }

    // Mantener ventana abierta
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
