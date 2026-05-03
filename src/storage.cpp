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

void select_data(const Command &cmd)
{

    if (db.find(cmd.table) == db.end())
    {
        std::cout << "Table not found\n";
        return;
    }

    int column_index = -1;

    // Simple mapping (hardcoded for now)

    if (cmd.where_column == "id")
        column_index = 0;

    if (cmd.where_column == "name")
        column_index = 1;

    for (auto &row : db[cmd.table])
    {

        if (cmd.has_where)
        {
            if (column_index == -1)
                continue;
            if (row[column_index] != cmd.where_value)
                continue;
        }

        for (auto &col : row)
        {
            std::cout << col << " ";
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

            while (ss >> val)
            {
                row.push_back(val);
            }

            db[table].push_back(row);
        }
        file.close();
    }

    std::cout << "Data loaded into memory\n";
}

void delete_data(const Command &cmd)
{
    if (db.find(cmd.table) == db.end())
    {
        std::cout << "Table not found\n";
        return;
    }

    int column_index = -1;

    // Simple mapping (hardcoded for now)

    if (cmd.where_column == "id")
        column_index = 0;

    else if (cmd.where_column == "name")
        column_index = 1;

    auto &rows = db[cmd.table];

    rows.erase(
        std::remove_if(rows.begin(), rows.end(), [&](const std::vector<std::string> &row)
                       { return cmd.has_where &&
                                row[column_index] == cmd.where_value; }),
        rows.end()
    );

    // Rewrite file
    std::ofstream file(get_file_path(cmd.table));
    for (auto &row : rows)
    {
        for (auto &col : row)
        {
            file << col << " ";
        }
        file << "\n";
    }
    file.close();
    std::cout << "Data deleted from " << cmd.table << "\n";
}