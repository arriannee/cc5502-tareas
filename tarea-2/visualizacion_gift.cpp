#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include "punto.hpp"

std::vector<Punto<double>> leer_puntos(const std::string& archivo) {
    std::ifstream in(archivo);
    std::vector<Punto<double>> puntos;
    double x, y;
    while (in >> x >> y) {
        puntos.emplace_back(x, y);
    }
    return puntos;
}

// Producto cruzado
double cross(const Punto<double>& o, const Punto<double>& a, const Punto<double>& b) {
    return (a.get_x() - o.get_x()) * (b.get_y() - o.get_y()) - 
           (a.get_y() - o.get_y()) * (b.get_x() - o.get_x());
}

// Visualización paso a paso
void drawStep(sf::RenderWindow& window, const std::vector<Punto<double>>& puntos,
              const std::vector<Punto<double>>& hull, const Punto<double>& actual,
              const Punto<double>& candidato, const std::vector<Punto<double>>& tests,
              float scale) {
    window.clear(sf::Color::White);

    // Puntos originales
    for (const auto& p : puntos) {
        sf::CircleShape circle(2);
        circle.setFillColor(sf::Color::Black);
        circle.setPosition(p.get_x() * scale, p.get_y() * scale);
        window.draw(circle);
    }

    // Pruebas (líneas grises)
    for (const auto& test : tests) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(actual.get_x() * scale, actual.get_y() * scale), sf::Color(150, 150, 150)),
            sf::Vertex(sf::Vector2f(test.get_x() * scale, test.get_y() * scale), sf::Color(150, 150, 150))
        };
        window.draw(line, 2, sf::Lines);
    }

    // Línea hacia candidato en verde
    sf::Vertex mejor[] = {
        sf::Vertex(sf::Vector2f(actual.get_x() * scale, actual.get_y() * scale), sf::Color::Green),
        sf::Vertex(sf::Vector2f(candidato.get_x() * scale, candidato.get_y() * scale), sf::Color::Green)
    };
    window.draw(mejor, 2, sf::Lines);

    // Hull en rojo
    if (hull.size() >= 2) {
        sf::VertexArray lines(sf::LineStrip, hull.size() + 1);
        for (size_t i = 0; i < hull.size(); ++i) {
            lines[i].position = sf::Vector2f(hull[i].get_x() * scale, hull[i].get_y() * scale);
            lines[i].color = sf::Color::Red;
        }
        lines[hull.size()].position = sf::Vector2f(hull[0].get_x() * scale, hull[0].get_y() * scale);
        lines[hull.size()].color = sf::Color::Red;
        window.draw(lines);
    }

    window.display();
    sf::sleep(sf::milliseconds(100));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Gift Wrapping Visualization");

    std::vector<Punto<double>> puntos = leer_puntos("puntos.txt");

    std::vector<Punto<double>> hull;
    int leftmost = 0;
    for (int i = 1; i < puntos.size(); ++i) {
        if (puntos[i].get_x() < puntos[leftmost].get_x() ||
            (puntos[i].get_x() == puntos[leftmost].get_x() && puntos[i].get_y() < puntos[leftmost].get_y())) {
            leftmost = i;
        }
    }

    int p = leftmost;
    do {
        hull.push_back(puntos[p]);
        int q = (p + 1) % puntos.size();
        std::vector<Punto<double>> pruebas;

        for (int r = 0; r < puntos.size(); ++r) {
            if (r == p || r == q) continue;
            pruebas.push_back(puntos[r]);
            if (cross(puntos[p], puntos[q], puntos[r]) < 0)
                q = r;
            drawStep(window, puntos, hull, puntos[p], puntos[q], pruebas, 1.0f);
        }

        p = q;
    } while (p != leftmost);

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
