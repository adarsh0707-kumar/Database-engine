#include "../include/parser.h"
#include <sstream>

Command parse_command(const std::string& input){
    std::stringstream ss(input);
    std::string word;

    Command cmd;
    cmd.type = UNKNOWN;

    ss >> word;

    if(word == "CREATE"){
        std::string tmp;
        ss >> tmp >> cmd.table;
        cmd.type = CREATE;
    }
    else if(word == "INSERT"){
        ss >> cmd.table;
        cmd.type = INSERT;

        std::string val;
        while(ss >> val){
            cmd.values.push_back(val);
        }
    }
    else if(word == "SELECT"){
        ss >> cmd.table;
        cmd.type = SELECT;
    }
    return cmd;
}