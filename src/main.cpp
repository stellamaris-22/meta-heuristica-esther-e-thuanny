#include "manager.h"
#include "parser.h"

template <typename T>
void print_graph(std::vector<std::vector<T>> vec){
    for(const auto& i : vec){
            for(const auto& j : i){
            std::cout<<j<<' ';
        }
        std::cout<<std::endl;
    }
}

int main(){
    

}