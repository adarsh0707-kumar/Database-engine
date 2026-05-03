#include "../include/executor.h"
#include "../include/parser.h"
#include <iostream>

int main(){
    std::string input;
    std:: cout << "MiniDB > ";

    while(std::getline(std::cin, input)){
        
    if(input == "Exit") break;

    Command cmd = parse_command(input);
    execute_command(cmd);

    std::cout << "MiniDb > ";
    }

    return 0;
}
