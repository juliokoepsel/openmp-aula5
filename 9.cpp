#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    int n = 1000000;

    std::vector<int> vetor(n);
    for (int i = 0; i < n; ++i) {
        vetor[i] = (rand() % 9) + 1;
    }

    int pares = 0;
    int impares = 0;

    omp_set_num_threads(4);

    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        if (vetor[i] % 2 == 0) {
            #pragma omp atomic
            pares++;
        } else {
            #pragma omp atomic
            impares++;
        }
    }

    std::cout << "Contagem de elementos pares: " << pares << std::endl;
    std::cout << "Contagem de elementos ímpares: " << impares << std::endl;
    return 0;
}
