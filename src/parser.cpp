#include "parser.h"
#include <iostream>
#include <vector>
#include <string>

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
 * @brief Construct a new Parser object
 * 
 * @param idx the index of the test we'll be parsing 
 * (Later it'll be updatable)
 */
Parser::Parser(int idx){
    update_grafo(idx);
    // print_graph(grafo);
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
    //Note: for now, idx is useless
    file_name = "test_graph.txt"; //it'll be based off of idx later
    std::string line;
    std::vector<std::string> broken_line;
    int n_vertices;
    std::fstream file;
    file.open(file_name);

    while(std::getline(file, line)){
        broken_line = tokenizer(line);
        //if it's a comment
        if(broken_line[0] == "c") continue;
        //if it's the problem description
        else if(broken_line[0] == "p") {
            n_vertices = std::stoi(broken_line[2]);
            // n_edges = std::stoi(broken_line[3]); i won't really need it, will I?
            for(auto i{0}; i<n_vertices; ++i){
                grafo.emplace_back();
            }
        }
        //if it's an edge
        else if(broken_line[0] == "e"){
            //adds the each vertex in the other's list
            grafo[std::stoi(broken_line[2])-1].push_back(std::stoi(broken_line[1]));
            grafo[std::stoi(broken_line[1])-1].push_back(std::stoi(broken_line[2]));
        }
        //if it's undefined
        else continue;
    }
}

std::vector<std::vector<int>> Parser::get_grafo(){
    return grafo;
}