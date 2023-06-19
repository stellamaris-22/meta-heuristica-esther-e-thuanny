#include <iostream>
#include <chrono>
#include <fstream>
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
    //the name of every file in our test_lib
//     std::vector<std::string> file_names{"anna.col", "david.col", "fpsol2.i.1.col", "fpsol2.i.2.col", "fpsol2.i.3.col", "games120.col", "homer.col", "huck.col", "inithx.i.1.col", "inithx.i.2.col", "inithx.i.3.col", "latin_square_10.col", "jean.col", "le450_5a.col", "le450_5b.col", "le450_5c.col", "le450_5d.col", "le450_15a.col", "le450_15b.col", "le450_15c.col", "le450_15d.col", "le450_25a.col", "le450_25b.col", "le450_25c.col", "le450_25d.col", "miles250.col", "miles500.col", "miles750.col", "miles1000.col", "miles1500.col", "mulsol.i.1.col", "mulsol.i.2.col", "mulsol.i.3.col", "mulsol.i.4.col", "mulsol.i.5.col", "myciel2.col", "myciel3.col", "myciel4.col", "myciel5.col", "myciel6.col", "myciel7.col", "queen5_5.col", "queen6_6.col", "queen7_7.col", "queen8_8.col", "queen8_12.col", "queen9_9.col", "queen10_10.col", "queen11_11.col", "queen12_12.col", "queen13_13.col", "queen14_14.col", "queen15_15.col", "queen16_16.col", "school1.col", "school1_nsh.col", "zeroin.i.1.col", "zeroin.i.2.col", "zeroin.i.3.col"};
//     
//     std::ofstream out_file;
//     out_file.open("time_output.txt");
//     //loops through our files
//     for(auto i{0u}; i<file_names.size(); ++i){
//         //the file we're taking the test from
//         std::string curr_file{"src/test_lib/" + file_names[i]}; //path to our tests folder + test we're taking
//         //to run each test
        Manager m;
        m.initialize();
        m.solve();
//         //Iniciar medição
//         std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
//         
//         m.solve();
// 
//         //Finalizar medição
//         std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
//         
//         std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
// 
// 
//         out_file << "Teste "<<file_names[i]<<std::endl;
//         out_file << "Número de vértices: " << m.get_vertices()<<std::endl;
//         out_file << "Número de arestas: " << m.get_arestas()<<std::endl;
//         out_file << "Número de cores utilizadas: " << m.get_colors()<<std::endl;
//         out_file << "Tempo de execução: " << duration.count() << " milissegundos\n" << std::endl;
//     }

    



    return 0; 

}