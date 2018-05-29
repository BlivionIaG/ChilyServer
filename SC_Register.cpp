#include "SC_Register.hpp"

SC_Register::~SC_Register()
{
    if (path.length() > 0)
        saveFile(path);
}

std::vector<std::string> SC_Register::loadFile(std::string path)
{
    std::string line;
    std::fstream file;
    std::vector<std::string> data;

    file.open(path, std::fstream::in);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            data.push_back(line);
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }

    return data;
}

void SC_Register::saveFile(std::string path)
{
    std::fstream file;
    file.open(path, std::fstream::out);

    if (file.is_open())
    {
        for (auto &i : log)
        {
            file << cmdFormat::toString(i) << std::endl;
        }

        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
}

void SC_Register::addToLog(std::vector<std::string> entry)
{
    for (auto &it : entry)
        addToLog(it);
}

std::string SC_Register::getLine()
{
    if (readCursor < (int)log.size())
    {
        return cmdFormat::toString(log[readCursor++]);
    }

    return "";
}
