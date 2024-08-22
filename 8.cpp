#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    int n = 1000000;
    int intervalo = 100;

    std::vector<int> vetor(n);
    for (int i = 0; i < n; ++i) {
        vetor[i] = rand() % intervalo;
    }

    std::vector<int> histograma(intervalo, 0);

    omp_set_num_threads(4);

    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        int valor = vetor[i];

        #pragma omp critical
        {
            histograma[valor]++;
        }
    }

    for (int i = 0; i < intervalo; ++i) {
        std::cout << "Valor " << i << ": " << histograma[i] << " ocorrências" << std::endl;
    }

    return 0;
}
