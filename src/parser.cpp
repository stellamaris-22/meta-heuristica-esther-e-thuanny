#include "parser.h"
#include <iostream>
#include <vector>
#include <string>

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
 * @brief Construct a new Parser object
 * 
 * @param idx the index of the test we'll be parsing 
 * (Later it'll be updatable)
 */
Parser::Parser(int idx){
    update_grafo(idx);
}

/**
 * @brief Construct a new Parser object
 * 
 * @param file_name the name of the test we'll be parsing 
 * (Later it'll be updatable)
 */
Parser::Parser(std::string file_name){
    this->file_name = file_name;
    update_grafo(-1);
}

/**
 * @brief receives a string, breaks it based on token into
 * multiple strings
 * 
 * @param str string we'll tokenize
 * @param token the token we're using to break the string
 * @return the smaller strings
 */
std::vector<std::string> Parser::tokenizer(std::string str, char token){
    std::vector<std::string> tokens;
    std::string tok;
    for(auto i : str){
        if(i == token){
            tokens.push_back(tok);
            tok = "";
        } 
        else if(i<32) continue;
        else {
            tok += i;
        }
    }
    tokens.push_back(tok);
    return tokens;
}

/**
 * @brief updates the file to be read and 
 * generates the new graph
 * 
 * @param idx the index of the file to be read
 */
void Parser::update_grafo(int idx){
    grafo.clear();
    if(idx-1 > -1){
        std::vector<std::string> file_names{"anna.col", "david.col", "fpsol2.i.1.col", "fpsol2.i.2.col", "fpsol2.i.3.col", "games120.col", "homer.col", "huck.col", "inithx.i.1.col", "inithx.i.2.col", "inithx.i.3.col", "latin_square_10.col", "jean.col", "le450_5a.col", "le450_5b.col", "le450_5c.col", "le450_5d.col", "le450_15a.col", "le450_15b.col", "le450_15c.col", "le450_15d.col", "le450_25a.col", "le450_25b.col", "le450_25c.col", "le450_25d.col", "miles250.col", "miles500.col", "miles750.col", "miles1000.col", "miles1500.col", "mulsol.i.1.col", "mulsol.i.2.col", "mulsol.i.3.col", "mulsol.i.4.col", "mulsol.i.5.col", "myciel2.col", "myciel3.col", "myciel4.col", "myciel5.col", "myciel6.col", "myciel7.col", "queen5_5.col", "queen6_6.col", "queen7_7.col", "queen8_8.col", "queen8_12.col", "queen9_9.col", "queen10_10.col", "queen11_11.col", "queen12_12.col", "queen13_13.col", "queen14_14.col", "queen15_15.col", "queen16_16.col", "school1.col", "school1_nsh.col", "zeroin.i.1.col", "zeroin.i.2.col", "zeroin.i.3.col"};
        file_name = file_names[idx-1];
        std::cout<<file_name<<std::endl;
    } else if(idx!=-1){
        std::cout<<"Ops! Arquivo não encontrado :("<<std::endl;
        return;
    }
    std::string line;
    std::vector<std::string> broken_line;
    std::fstream file;
    file.open("src/test_lib/" + file_name);

    while(std::getline(file, line)){
        broken_line = tokenizer(line);
        //if it's a comment
        if(broken_line[0] == "c") continue;
        //if it's the problem description
        else if(broken_line[0] == "p") {
            n_vertices = std::stoi(broken_line[2]);
            n_edges = std::stoi(broken_line[3]); 
            for(auto i{0}; i<n_vertices; ++i){
                grafo.emplace_back();
                grafo[i].first = i;
            }
        }
        //if it's an edge
        else if(broken_line[0] == "e"){
            //adds the each vertex in the other's list
            grafo[std::stoi(broken_line[2])-1].second.push_back(std::stoi(broken_line[1])-1);
            grafo[std::stoi(broken_line[1])-1].second.push_back(std::stoi(broken_line[2])-1);
        }
        //if it's undefined
        else continue;
    }
    // print_graph(grafo);
    // std::cout<<std::endl;
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
