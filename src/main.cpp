#include "../include/executor.h"
#include "../include/parser.h"
#include "../include/storage.h"
#include <iostream>

int main(){
    std::string input;
    std:: cout << "MiniDB > ";

    load_all_tables();

    while(std::getline(std::cin, input)){
        
    if(input == "Exit") break;

    Command cmd = parse_command(input);
    execute_command(cmd);

    std::cout << "MiniDb > ";
    }

    return 0;
}
