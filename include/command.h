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
    UNKNOWN
};

struct Command
{
    CommandType type;
    std::string table;
    std::vector<std::string> values;
};

#endif // COMMAND_H