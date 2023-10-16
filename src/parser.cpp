#include "parser.h"
#include <iostream>
#include <vector>
#include <string>

//Para debug
template <typename T>
void print_graph(std::vector<std::pair<int,std::vector<T>>> vec){
    for(const auto& i : vec){
        for(const auto& j : i.second){
            std::cout<<j<<' ';
        }
        std::cout<<std::endl;
    }
}

/**
 * Constrói um novo Parser
 * 
 * @param idx o índice do teste requisitado
 */
Parser::Parser(int idx){
    update_grafo(idx);
}

/**
 * Constrói um novo Parser
 * 
 * @param file_name o nome do teste requisitado
 */
Parser::Parser(std::string file_name){
    this->file_name = file_name;
    //-1 indica que o nome já foi escolhido
    update_grafo(-1);
}

/**
 * Recebe uma string e a quebra em outras com base
 * no token recebido
 * 
 * @param str string a ser tokenize
 * @param token o token usado para quebrar a string
 * @return as strings menores geradas
 */
std::vector<std::string> Parser::tokenizer(std::string str, char token){
    std::vector<std::string> tokens;
    std::string tok;
    //para cada caracter da string
    for(auto i : str){
        //se o caracter é o token, adicionamos a 
        //string gerada até então e a resetamos
        if(i == token){
            tokens.push_back(tok);
            tok = "";
        }
        //caso seja um caracter inválido, ignora
        else if(i<32) continue;
        //caso seja um caracter qualquer, adiciona-o 
        //à string menor que estamos construindo
        else {
            tok += i;
        }
    }
    //coloca a última string gerada e retorna todas as strings
    tokens.push_back(tok);
    return tokens;
}

/**
 * atualiza o arquivo a ser lido
 * e gera o novo grafo
 * 
 * @param idx o índice do arquivo a ser lido
 */
void Parser::update_grafo(int idx){
    grafo.clear();
    //caso seja um índice válido
    if(idx-1 > -1 && idx < 60){
        std::vector<std::string> file_names{"original.col","anna.col", "david.col", "fpsol2.i.1.col", "fpsol2.i.2.col", "fpsol2.i.3.col", "games120.col", "homer.col", "huck.col", "inithx.i.1.col", "inithx.i.2.col", "inithx.i.3.col", "latin_square_10.col", "jean.col", "le450_5a.col", "le450_5b.col", "le450_5c.col", "le450_5d.col", "le450_15a.col", "le450_15b.col", "le450_15c.col", "le450_15d.col", "le450_25a.col", "le450_25b.col", "le450_25c.col", "le450_25d.col", "miles250.col", "miles500.col", "miles750.col", "miles1000.col", "miles1500.col", "mulsol.i.1.col", "mulsol.i.2.col", "mulsol.i.3.col", "mulsol.i.4.col", "mulsol.i.5.col", "myciel2.col", "myciel3.col", "myciel4.col", "myciel5.col", "myciel6.col", "myciel7.col", "queen5_5.col", "queen6_6.col", "queen7_7.col", "queen8_8.col", "queen8_12.col", "queen9_9.col", "queen10_10.col", "queen11_11.col", "queen12_12.col", "queen13_13.col", "queen14_14.col", "queen15_15.col", "queen16_16.col", "school1.col", "school1_nsh.col", "zeroin.i.1.col", "zeroin.i.2.col", "zeroin.i.3.col"};
        file_name = file_names[idx-1];
        std::cout<<file_name<<std::endl;
    //e não seja porque o nome já foi definido
    } else if(idx!=-1){
        //o arquivo não existe
        std::cout<<"Ops! Arquivo não encontrado :("<<std::endl;
        return;
    }
    std::string line;
    std::vector<std::string> broken_line;
    std::fstream file;
    //abre o arquivo solicitado
    file.open("src/test_lib/" + file_name);

    //enquanto não chegarmos ao fim do arquivo
    while(std::getline(file, line)){
        broken_line = tokenizer(line);
        //se é um comentário
        if(broken_line[0] == "c") continue;
        //se é a descrição do problema
        else if(broken_line[0] == "p") {
            n_vertices = std::stoi(broken_line[2]);
            n_edges = std::stoi(broken_line[3]); 
            //aloca o espaço do grafo
            for(auto i{0}; i<n_vertices; ++i){
                grafo.emplace_back();
                grafo[i].first = i;
            }
        }
        //se é uma aresta
        else if(broken_line[0] == "e"){
            //adiciona cada vértice na lista de adjacência do outro
            grafo[std::stoi(broken_line[2])-1].second.push_back(std::stoi(broken_line[1])-1);
            grafo[std::stoi(broken_line[1])-1].second.push_back(std::stoi(broken_line[2])-1);
        }
        //se não estiver definido
        else continue;
    }
}

std::vector<std::pair<int,std::vector<int>>> Parser::get_grafo(){
    return grafo;
}

int Parser::get_vertices(){
    return n_vertices;
}

int Parser::get_edges(){
    return n_edges;
}


std::string Parser::get_file_name(){
    return file_name;
}
