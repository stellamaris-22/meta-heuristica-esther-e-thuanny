#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/**
 * Esta classe é responsável pela leitura de
 * um arquivo .col de modo a gerar um grafo
 */
class Parser{
    private: 
        std::vector<std::pair<int,std::vector<int>>> grafo;    //!< Matriz gerada pelo grafo recebido
        std::string file_name;                                 //!< To open the test file
        int n_vertices;                                        //!< Number of vertices
        int n_edges;                                           //!< Number of edges
    public:
        /// Constrói um novo parser que lê o arquivo no índice
        Parser(int);
        /// Constrói um novo parser que lê o arquivo pelo nome
        Parser(std::string);
        /// Retorna o grafo gerado
        std::vector<std::pair<int,std::vector<int>>> get_grafo();
        /// Retorna o nome do arquivo escolhido
        std::string get_file_name();
        /// Retorna o número de vértices no grafo
        int get_vertices();
        /// Retorna o número de arestas no grafo
        int get_edges();
    private:
        /// Tokeniza uma string com base em um caracter
        std::vector<std::string> tokenizer(std::string, char=' ');
    public:
        /// Atualiza o grafo com base no índice
        void update_grafo(int);
};
#endif