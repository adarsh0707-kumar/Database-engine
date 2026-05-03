#include "../include/storage.h"
#include <iostream>
#include<map>

static std::map<std::string, std::vector<std::vector<std::string>>> db;

void create_table(const std::string& name){
    db[name] = {};
    std::cout<<"Table "<< name<<" created\n";
}

void insert_into(const std::string& name, const std::vector<std::string>& values){
    db[name].push_back(values);
    std::cout<<"Inserted into "<< name <<"\n";
}

void select_all(const std::string& name){
    for(auto& row : db[name]){
        for(auto& col : row){
            std::cout << col << " ";
        }
        std::cout << "\n";
    }
}