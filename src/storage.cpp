#include "../include/storage.h"
#include <iostream>
#include<map>

static std::map<std::string, std::vector<std::vector<std::string>>> db;

void create_table(const std::string& name){
    db[name] = {};
    std::cout<<"Table "<< name<<" created\n";
}
