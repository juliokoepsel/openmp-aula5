#include <iostream>
#include <omp.h>
#include <vector>

int main() {
    int n = 100;

    std::vector<int> vetor(n);
    for (int i = 0; i < n; ++i) {
        vetor[i] = i + 1;
    }

    omp_set_num_threads(4);

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < n; ++i) {
            vetor[i] *= 10;
        }

        #pragma omp barrier

        #pragma omp single
        std::cout << "barrier" << std::endl;

        #pragma omp for
        for (int i = 0; i < n; ++i) {
            vetor[i] += 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        std::cout << vetor[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
