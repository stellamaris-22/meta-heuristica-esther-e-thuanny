#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include <string>

/**
 * This class is responsible for receiving a graph representing a timetable 
 * restriction problem and specifications and giving an optimized solution
 */
class Manager{
    private: 
        std::vector<std::vector<int>> grafo;        //!< Matriz de adjacência (grafo recebido)
        unsigned short max_horarios{0};             //!< Limite de horários (0 caso não haja limite)
        unsigned short max_salas{0};                //!< Limite de salas (0 caso não haja limite)
        std::vector<std::vector<int>> solucao;      //!< Solução gerada (double-check type)
        unsigned short horarios_usados{0};          //!< Número de horários usados na solução
        unsigned short salas_usadas{0};             //!< Número de salas usadas na solução
        bool found_solution{false};                 //!< Se foi ou não encontrada uma solução para aquele problema
        bool minimize_rooms{false};                 //!< O que estamos minimizando: salas (true) ou horários (false)
        int n_colors;                               //!< Número de cores utilizadas
        int n_vertices;                             //!< Número de vértices no grafo
        int n_arestas;                              //!< Número de arestas no grafo
    public:
        /// Builds a new manager
        Manager()=default;
        /// Initializes our graph and restrictions
        void initialize();
        void initialize(std::string);
        /// Solves timetabling problem asked & prints solution
        void solve();
        
        int get_colors();
        int get_vertices();
        int get_arestas();
    private:
        /// Screen with commands for users to put a file to solve the problem
        void display_initialization();
        /// Screen with our final table
        void display_solution();
        /// Welsh-Powell algorythm execution
        void welsh_powell();
};
#endif