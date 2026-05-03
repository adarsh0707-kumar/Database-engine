#include "../include/parser.h"
#include <sstream>
#include<algorithm>


std::string clean(const std::string& str){
    std::string s = str;
    
    s.erase(remove(s.begin(), s.end(), ';'), s.end());
    s.erase(remove(s.begin(), s.end(), '('), s.end());
    s.erase(remove(s.begin(), s.end(), ')'), s.end());

    return s;
}

Command parse_command(const std::string& input)
{
    std::stringstream ss(input);
    std::string word;

    Command cmd;
    cmd.type = UNKNOWN;

    ss >> word;

    if(word == "CREATE"){
        std::string tmp, table;

        ss >> tmp >> table;
        cmd.type = CREATE;
        cmd.table = clean(table);
    }
    else if(word == "INSERT"){
        std::string tem, table, values_word;

        ss >> tem >> table >> values_word;
        cmd.type = INSERT;
        cmd.table = clean(table);

        std::string val;
        while(ss >> val){
            cmd.values.push_back(clean(val));
        }
    }
    else if(word == "SELECT"){
        std::string star, from, table;

        ss >> star >> from >> table;
        cmd.type = SELECT;
        cmd.table = clean(table);
    }
    return cmd;
}