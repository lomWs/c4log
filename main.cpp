#include <iostream>

using std::cin;
using std::cout;

#include "Logger.h"

int main(){
    //EASY USEFUL EXAMPLE 
    Logger logger("log");


    logger.writeOnFile("Error: no file such");
    logger.writeOnFile("Success: operation complete");
    
    return 0;
}
