#include "../include/storage.h"
#include <iostream>
#include <map>
#include <fstream>
#include <filesystem>
#include <sstream>

static std::map<std::string, std::vector<std::vector<std::string>>> db;



std::string get_file_path(const std::string &table)
{
    if (!std::filesystem::exists("data"))
    {
        std::filesystem::create_directory("data");
    }
    
    return "data/" + table + ".table";
}

void create_table(const std::string &name)
{
    db[name] = {};

    std::ofstream file(get_file_path(name));

    file.close();

    std::cout << "Table " << name << " created\n";
}

void insert_into(const std::string &name, const std::vector<std::string> &values)
{
    db[name].push_back(values);

    std::ofstream file(get_file_path(name), std::ios::app);

    for (auto &val : values)
    {
        file << val << " ";
    }

    file << "\n";

    file.close();

    std::cout << "Inserted into " << name << "\n";
}

void select_all(const std::string &name)
{

    if (db.find(name) == db.end())
    {
        std::cout << "Table not found\n";
        return;
    }

    for(auto& row : db[name]){
        for(auto& col : row){
            std::cout << col <<" ";
        }
        std::cout << std::endl;
    }
}

void load_all_tables()
{
    for (const auto &entry : std::filesystem::directory_iterator("data"))
    {

        std::string file_path = entry.path().string();

        // extract table name from file name

        std::string filename = entry.path().filename().string();

        std::string table = filename.substr(0, filename.find(".table"));

        std::ifstream file(file_path);
        std::string line;

        while (getline(file, line))
        {
            std::stringstream ss(line);
            std::string val;
            std::vector<std::string> row;

            while(ss>> val){
                row.push_back(val);
            }

            db[table].push_back(row);

        }
        file.close();

    }

    std::cout <<"Data loaded into memory\n";
}