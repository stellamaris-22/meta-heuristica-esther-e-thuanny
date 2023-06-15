#include <iostream>
#include <chrono>
#include "manager.h"
#include "parser.h"




template <typename T>
void print_graph(std::vector<std::vector<T>> vec){
    for(const auto& i : vec){
            for(const auto& j : i){
            std::cout<<j<<' ';
        }
        std::cout<<std::endl;
    }
}

int main(){
    Manager m;
    m.initialize();

    //Iniciar medição
    std::chrono ::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    
    m.solve();

    //Finalizar medição
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    

    std::cout <<"Tempo de execução: "<< duration.count() << " milissegundos" << std::endl;


    return 0; 

}