#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int main() {
    const long long num_pontos = 100000000;
    
    long long pontos_dentro_do_circulo = 0;

    omp_set_num_threads(4);

    std::srand(static_cast<unsigned int>(std::time(0)));

    #pragma omp parallel
    {
        long long pontos_dentro_local = 0;

        #pragma omp for
        for (long long i = 0; i < num_pontos; ++i) {
            double x = static_cast<double>(std::rand()) / RAND_MAX;
            double y = static_cast<double>(std::rand()) / RAND_MAX;

            if (x * x + y * y <= 1.0) {
                pontos_dentro_local++;
            }
        }

        #pragma omp critical
        {
            pontos_dentro_do_circulo += pontos_dentro_local;
        }

        #pragma omp barrier
    }

    double pi = 4.0 * pontos_dentro_do_circulo / num_pontos;

    std::cout << "Valor calculado de PI: " << pi << std::endl;
    return 0;
}
