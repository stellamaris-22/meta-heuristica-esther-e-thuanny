#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include "manager.h"
#include "parser.h"

//purely to debug stuff
template <typename T>
void print_graph(std::vector<std::vector<T>> vec){
    for(const auto& i : vec){
        for(const auto& j : i){
            std::cout<<j<<' ';
        }
        if(!i.empty())std::cout<<std::endl;
    }
}

/**
 * This function is responsible for initializing our graph
 * and its restrictions as requested by the user
 */
void Manager::initialize(){
    Parser p(1);
    grafo = p.get_grafo();
    n_vertices = p.get_vertices();
    n_arestas = p.get_edges();
};

/**
 * This function is responsible for initializing our graph
 * and its restrictions as requested by the user
 */
void Manager::initialize(std::string file_name){
    Parser p(file_name);
    grafo = p.get_grafo();
    n_arestas = p.get_edges();
    n_vertices = p.get_vertices();
};

int Manager::get_vertices(){
    return n_vertices;
}
int Manager::get_arestas(){
    return n_arestas;
}

/**
 * @brief The method that actually solves the problem
 * and shows the solution obtained
 */
void Manager::solve(){
    welsh_powell();
    // display_solution();
};

int Manager::get_colors(){
    return n_colors;
}

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
    print_graph(solucao);
};

/*
 * Checks wether or not the intersection between two 
 * sorted vectors is empty
 */
template <typename T>
bool empty_intersection(std::vector<T> a, std::vector<T> b){
    //loops through both vectors (O(n1+n2))
    for(auto i1{0u}, i2{0u}; i1 < a.size() && i2 < b.size();){
        //if there is a common element
        if(a[i1] == b[i2]) return false;
        //advance index on the vector with smallest element
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
    //wether or not a certain vertex was colored
    bool colored;

    //sorting vertices based on their degree (O(n log n))
    std::sort(grafo.begin(), grafo.end(), [](const std::vector<int>& a, const std::vector<int>& b) {return a.size() > b.size();});
    
    //if we defined a maximum
    auto n_cores{grafo.size()};
    n_colors = 0;
    //creates every color partition
    for(auto i{0u}; i<n_cores; ++i) solucao.emplace_back();
    //first vertex goes to first color
    solucao[0].push_back(0);
    //for each uncolored vertex (O(n))
    for(auto i{1u}; i<grafo.size(); ++i){
        //each one starts as non-colored
        colored = false;
        //for every color partition (O(n))
        for(auto& j : solucao){ 
            //if this color's adjacent vertices aren't already in color j (O(n))
            bool canColor = true;
            
            // Verifica se o vértice i pode ser colorido com a cor atual
            for (auto v : j) {
                if (!empty_intersection(grafo[i], grafo[v])) {
                    canColor = false;
                    break;
                }
            }

            if (canColor) {
                colored = true;
                if(j.empty()) ++n_colors;
                j.push_back(i);
                break;
            }
        }
        //if a certain vertex could not be colored, there is no solution
        if(!colored){
            found_solution = false;
            return;
        }
    }
    //if it got here, we could color all vertexes
    found_solution = true; 
};