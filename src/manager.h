#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

/**
 * Esta classe é responsável por receber um grafo com arestas de restrição
 * e gerar uma coloração dele que pode ser interpretada como tabela
 */
class Manager{
    private: 
        std::vector<std::pair<int,std::vector<int>>> grafo;         //!< Matriz de adjacência (grafo recebido)
        unsigned short max_horarios{0};                             //!< Limite de horários (0 caso não haja limite)
        unsigned short max_salas{0};                                //!< Limite de salas (0 caso não haja limite)
        std::vector<std::vector<int>> solucao;                      //!< Solução gerada (double-check type)
        unsigned short horarios_usados{0};                          //!< Número de horários usados na solução
        unsigned short salas_usadas{0};                             //!< Número de salas usadas na solução
        bool found_solution{false};                                 //!< Se foi ou não encontrada uma solução para aquele problema
        bool minimize_rooms{false};                                 //!< O que estamos minimizando: salas (true) ou horários (false)
        unsigned int n_colors;                                               //!< Número de cores utilizadas
        int n_vertices;                                             //!< Número de vértices no grafo
        int n_arestas;                                              //!< Número de arestas no grafo
        bool execute{false};                                        //!< Se vamos ou não executar aquele teste
        std::string file_name;                                      //!< Arquivo de onde tiraremos o teste
        std::chrono::milliseconds tempo;                            //!< Duração do experimento                  
        int curr_idx;                                               //!< Índice do teste sendo executado
    public:
        bool all{false};                                            //!< Se todos os testes serão executados
        /// Constrói um novo Manager
        Manager()=default;
        /// Inicializam o grafo solicitado
        void initialize();
        void initialize(std::string);
        /// Resolve o problema de coloração e imprime o resultado
        void solve();
        /// Retorna a quantidade de cores utilizadas
        int get_colors();
        /// Retorna a quantidade de vértices no grafo
        int get_vertices();
        /// Retorna a quantidade de arestas no grafo
        int get_arestas();
    private:
        /// Tela com comandos para o usuário escolher um arquivo
        void display_initialization();
        /// Tela com as partições geradas
        void display_solution();
        /// Tela com os resultados em LaTeX
        void display_simple();
        /// Execução do algoritmo de Welsh-Powell
        void welsh_powell();
        /// Execução da heurística desenvolvida pelas autoras deste trabalho
        void albuquerque_wanderley();
        /// Execução do algoritmo exato autoral (backtracking)
        void ET(std::pair<int, std::vector<int>>, std::vector<std::pair<int, std::vector<int>>>, std::vector<std::vector<int>>, unsigned int);
        /// Método que chama o método recursivo da maneira correta
        void controle_ET();
        /// Execução do algoritmo exato encontrado na literatura (branch and bound)
        void Zykov();
        /// Método auxiliar ao algoritmo de Zykov
        void ColorZ(std::vector<std::pair<int,std::vector<int>>>);


};
#endif