#include <iostream>
#include <fstream>
#include <chrono>
#include "generator_strategies.hpp"
#include "random_generator.cpp"
#include "convex_mixture_generator.hpp"
#include "convex_hull_strategies.hpp"

std::ofstream archivo_csv;

void medir_algoritmo(ConvexHullStrategy* algoritmo, PointGenerator* generador, int n, double porcentaje, const std::string& nombre_algo) {
    auto puntos = generador->generate(n, porcentaje);

    auto inicio = std::chrono::high_resolution_clock::now();
    Poligono<double> hull = algoritmo->apply(puntos);
    auto fin = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duracion = fin - inicio;

    std::cout << "Algoritmo: " << nombre_algo << ", n = " << n << ", % en hull = " << porcentaje * 100
              << ", Tiempo: " << duracion.count() << " segundos" << std::endl;

    // Escribir en el CSV
    archivo_csv << nombre_algo << "," << n << "," << porcentaje << "," 
                << (dynamic_cast<RandomGenerator*>(generador) ? "Random" : "Mixto") << ","
                << duracion.count() << "\n";
}

int main() {
    archivo_csv.open("resultados.csv");
    archivo_csv << "algoritmo,n,porcentaje,tipo_generador,tiempo\n"; // encabezado

    RandomGenerator randomGen;
    ConvexMixtureGenerator mixGen;
    GrahamScanAlgorithm graham;
    GiftWrappingAlgorithm gift;

    std::vector<int> tamanos = {10000, 100000, 1000000, 10000000};
    std::vector<double> porcentajes = {0.01, 0.1, 0.5, 0.9};

    for (int n : tamanos) {
        for (double p : porcentajes) {
            std::cout << "⋅˚₊‧ ଳ ‧₊˚ ⋅﹌﹌﹌﹌﹌₊ ⊹ n = " << n << ", p = " << p << " ⋅˚₊‧ ଳ ‧₊˚ ⋅﹌﹌﹌﹌﹌₊ ⊹\n";
            medir_algoritmo(&graham, &randomGen, n, p, "Graham-Random");
            medir_algoritmo(&gift, &randomGen, n, p, "Gift-Random");
            medir_algoritmo(&graham, &mixGen, n, p, "Graham-Mix");
            medir_algoritmo(&gift, &mixGen, n, p, "Gift-Mix");
            std::cout << "⋅˚₊‧ ଳ ‧₊˚ ⋅﹌﹌﹌﹌﹌₊ ⊹ Fin de la iteración ⋅˚₊‧ ଳ ‧₊˚ ⋅﹌﹌﹌﹌﹌₊ ⊹\n \n";
        }
    }

    archivo_csv.close();
    return 0;
}
