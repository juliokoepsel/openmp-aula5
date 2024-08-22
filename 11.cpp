#include <iostream>
#include <omp.h>
#include <vector>

int main() {
    const int num_dados = 100;

    std::vector<int> dados(num_dados, 0);
    bool dados_disponiveis = false;

    const int num_consumidores = 4;
    int num_threads = num_consumidores + 1;
    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0) { // produtor
            for (int i = 0; i < num_dados; ++i) {
                dados[i] = i + 1;
            }
            #pragma omp flush(dados_disponiveis, dados)
            dados_disponiveis = true;
            #pragma omp flush(dados_disponiveis)
        } else { // consumidores
            while (true) {
                #pragma omp flush(dados_disponiveis, dados)
                if (dados_disponiveis) {
                    #pragma omp flush(dados)
                    int i;
                    #pragma omp critical
                    {
                        i = (omp_get_thread_num() - 1) * (num_dados / num_consumidores);
                        int end = (omp_get_thread_num() - 1 + 1) * (num_dados / num_consumidores);
                        if (end > num_dados) end = num_dados;

                        std::cout << "Thread " << omp_get_thread_num() << " processando dados: ";
                        for (int j = i; j < end; ++j) {
                            std::cout << dados[j] << " ";
                        }
                        std::cout << std::endl;
                    }
                    break;
                }
            }
        }
    }

    return 0;
}
