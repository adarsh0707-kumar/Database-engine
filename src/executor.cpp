#include "../include/executor.h"
#include "../include/storage.h"
#include <iostream>

void execute_command(const Command& cmd){
    switch(cmd.type){
        case CREATE:
            create_table(cmd.table);
            break;
        case INSERT:
            insert_into(cmd.table, cmd.values);
            break;
        case SELECT:
            select_data(cmd);
            break;
        case DELETE:
            delete_data(cmd);
            break;
        default:
            std::cout << "Unknown command\n";  
    }
}