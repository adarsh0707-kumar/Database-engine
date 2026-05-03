#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

void create_table(const std::string& name);
void insert_into(const std::string &name, const std::vector<std::string> &values);
void select_all(const std::string &name);

void load_all_tables();

#endif // STORAGE_H