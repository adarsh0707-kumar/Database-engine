#include "../include/storage.h"
#include <iostream>
#include<map>
#include <fstream>

static std::map<std::string, std::vector<std::vector<std::string>>> db;


std::string get_file_path(const std::string& table) {
    return "data/" + table + ".table";
}

void create_table(const std::string& name){
    db[name] = {};
    
    std::ofstream file(get_file_path(name));

    file.close();

    std::cout<<"Table "<< name<<" created\n";
}

void insert_into(const std::string& name, const std::vector<std::string>& values){
    db[name].push_back(values);

    std::ofstream file(get_file_path(name), std::ios::app);

    for(auto& val: values){
        file << val << " ";
    }

    file << "\n";

    file.close();
    
    std::cout << "Inserted into " << name << "\n";
}

void select_all(const std::string& name){
    // for(auto& row : db[name]){
    //     for(auto& col : row){
    //         std::cout << col << " ";
    //     }
    //     std::cout << "\n";
    // }

    std::ifstream file(get_file_path(name));

    if(!file.is_open()){
        std::cout << "Table not found\n";
        return;
    }

    std::string line;

    while(getline(file, line)){
        std::cout << line << std::endl;
    }
    file.close();
}