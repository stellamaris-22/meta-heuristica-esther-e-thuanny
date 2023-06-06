#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "manager.h"

//purely to debug stuff
template <typename T>
void print_graph(std::vector<std::vector<T>> vec){
    for(const auto& i : vec){
            for(const auto& j : i){
            std::cout<<j<<' ';
        }
        std::cout<<std::endl;
    }
}

/**
 * This function is responsible for initializing our graph
 * and its restrictions as requested by the user
 */
void Manager::initialize(){
    /// variables
    std::string file_name, line,  mini;
    std::fstream file;
    int lin{0};

    /// opens file
    display_initialization();
    std::getline(std::cin, file_name);
    file.open(file_name);

    /// reads file
    while(std::getline(file, line)){
        //updates amount of lines in graph
        grafo.emplace_back();
        for(auto i : line){
            if(i == '0' || i == '1') grafo[lin].push_back(i == '1');
        }
        ++lin;
    }

    //Prompts for maximum times & maximum classrooms & minimization thing
    std::cout<<"Por favor, digite o número máximo de horários (0 caso não queira limitar): ";
    std::cin>>max_horarios;
    std::cout<<"Por favor, digite o número máximo de salas (0 caso não queira limitar): ";
    std::cin>>max_salas;
    std::cout<<"Gostaria de minimizar horários ou salas? (default: horários)\n";
    std::cin>>mini;
    for(auto& i : mini) i = std::tolower(i);
    if(mini == "salas" || mini == "sala") minimize_rooms = true;
};

/**
 * @brief The method that actually solves the problem
 * and shows the solution obtained
 */
void Manager::solve(){
    welsh_powell();
    display_solution();
};

/**
 * Prompts user for file with graph, explains format asked in file
 * and introduces problem and how its solved
 */
void Manager::display_initialization(){
    std::cout<<"Bem-vindo(a) a nosso *resolvedor de timetabling*!\n"
             <<"(Sim, Thuanny, eu vou arrumar esse nome)\n"
             <<"Este algoritmo recebe uma matriz de adjacência em um arquivo\n"
             <<"A matriz deve representar as restrições entre salas ou hor"
             <<"Por favor, digite o caminho para o arquivo: ";
};

/**
 * @brief Displays the table with the solution obtained
 */
void Manager::display_solution(){
    if(!found_solution){
        std::cout<<"Ops! Não conseguimos encontrar uma solução para o seu problema :("<<std::endl;
        return;
    }
    //STUB
    print_graph(grafo);
};

// bool Manager::comp(std::vector<int> a, std::vector<int> b){
//     return a.size() > b.size();
// };

/*
 * Checks wether or not the intersection between two 
 * sorted vectors is empty
 */
template <typename T>
bool empty_intersection(std::vector<T> a, std::vector<T> b){
    for(auto i1{0u}, i2{0u}; i1 < a.size() && i2 < b.size();){
        if(a[i1] == b[i2]) return false;
        else if(a[i1] < b[i2]) ++i1;
        else if(a[i1] > b[i2]) ++i2;
    }
    return true;
}

/**
 * @brief Algorythm used to color our graph
 * according to the restrictions given  
 */
void Manager::welsh_powell(){
    bool colored;
    //sorting vertices based on their degree
    std::sort(grafo.begin(), grafo.end(), comp);
    //if we defined a maximum
    auto n_cores = minimize_rooms ? (max_salas ? max_salas : grafo.size()) : (max_horarios ? max_horarios : grafo.size());
    //creates every color partition
    for(auto i{0u}; i<n_cores; ++i) solucao.emplace_back();
    //first vertex (0) goes to first color
    solucao[0].push_back(0);
    //for each uncolored vertex
    for(auto i{1u}; i<grafo.size(); ++i){
        colored = false;
        //for every color partition
        for(auto& j : solucao){ 
            //if this color's adjacent vertices aren't already in color j
            if(empty_intersection(grafo[i], j)){
                colored = true;
                //color i in j
                j.push_back(i);
                //analyze next vertex
                break;
            }
        }
        if(!colored){
            found_solution = false;
            return;
        }
    }
};



