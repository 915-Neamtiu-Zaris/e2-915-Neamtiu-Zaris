#ifndef ETHNOLOGIST_H
#define ETHNOLOGIST_H

#endif // ETHNOLOGIST_H

#include <string>
#include <vector>
#include <sstream>

#pragma once

class Ethnologist
{
private:
    std::string name;
    std::string area;

public:
    Ethnologist();
    ~Ethnologist();

    Ethnologist(std::string name, std::string area);

    std::string get_name();
    std::string get_area();

    friend std::ostream& operator<<(std::ostream& os, const Ethnologist& e);
    friend std::istream& operator>>(std::istream& is, Ethnologist& e);

    std::vector<std::string> tokenize(std::string str, char delimiter);
};

inline Ethnologist::Ethnologist()
{
}

inline Ethnologist::~Ethnologist() {}

inline Ethnologist::Ethnologist(std::string name, std::string area) : name{name}, area{area}
{
}

inline std::string Ethnologist::get_name()
{
    return this->name;
}

inline std::string Ethnologist::get_area()
{
    return this->area;
}

inline std::ostream& operator<<(std::ostream& os, const Ethnologist& e)
{
    os << e.name << e.area;
    return os;
}

inline std::istream& operator>>(std::istream& is, Ethnologist& e)
{
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = e.tokenize(line, ';');

    if(tokens.size() != 2)
        return is;

    e.name = tokens[0];
    e.area = tokens[1];

    return is;
}

inline std::vector<std::string> Ethnologist::tokenize(std::string str, char delimiter)
{
    std::vector<std::string>result;
    std::stringstream ss(str);
    std::string token;

    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}
