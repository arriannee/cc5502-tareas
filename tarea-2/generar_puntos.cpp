#include <fstream>
#include <random>

int main() {
    std::ofstream archivo("puntos.txt");
    std::default_random_engine rng(std::random_device{}());
    std::uniform_real_distribution<double> dist_x(50, 700);
    std::uniform_real_distribution<double> dist_y(50, 700);

    int cantidad = 30;
    for (int i = 0; i < cantidad; ++i) {
        double x = dist_x(rng);
        double y = dist_y(rng);
        archivo << x << " " << y << "\n";
    }

    archivo.close();
    return 0;
}
