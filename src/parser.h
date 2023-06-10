#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/**
 * This class is responsible for parsing
 * a .col file (.col.b is still a wip)
 */
class Parser{
    private: 
        std::vector<std::vector<int>> grafo;    //!< Matriz gerada pelo grafo recebido
        std::string file_name;                  //!< To open the test file
    public:
        /// Builds a new parser
        Parser(int);
    private:
        /// Screen with commands for users to put a file to solve the problem
        void read();
        /// Screen with our final table
        void get_grafo();
        /// Tokenizes each line of .col document
        std::vector<std::string> tokenizer(std::string, char=' ');
    public:
        /// Updates the file for testing
        void update_grafo(int);
};
#endif