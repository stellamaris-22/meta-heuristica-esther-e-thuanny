#include <iostream>
#include <chrono>
#include <fstream>
#include "manager.h"
#include "parser.h"

int main(){
    Manager m;
    m.initialize();
    if(!m.all)m.solve();
    
    return 0; 

}