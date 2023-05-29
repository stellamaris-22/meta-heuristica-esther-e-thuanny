#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "manager.h"

//purely to debug stuff
void print_graph(std::vector<std::vector<bool>> vec){
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
    std::cout<<"Qual dos dois (defult: horários) você gostaria de minimizar? ";
    std::cin>>mini;
    for(auto& i : mini) i = std::tolower(i);
    if(mini == "salas" || mini == "sala") minimize_rooms = true;
};


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
             <<"Por favor, digite o caminho para o arquivo: ";
};


void Manager::display_solution(){
    if(!found_solution){
        std::cout<<"Ops! Não conseguimos encontrar uma solução para o seu problema :("<<std::endl;
        return;
    }
};


void Manager::welsh_powell(){

};



