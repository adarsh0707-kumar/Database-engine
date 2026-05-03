#ifndef COMMAND_H
#define COMMAND_H

#include<string>
#include<vector>

enum CommandType
{
    CREATE,
    INSERT,
    SELECT,
    DELETE,
    UPDATE,
    UNKNOWN
};

struct Command
{
    CommandType type;
    std::string table;
    std::vector<std::string> values;

    std::string where_column;
    std::string where_value;
    bool has_where = false;

    std::string update_column;
    std::string update_value;
};

#endif // COMMAND_H