/*#include "Ethnologist.h"
#include <sstream>

Ethnologist::Ethnologist()
{
}

Ethnologist::~Ethnologist() {}

Ethnologist::Ethnologist(std::string name, std::string area) : name{name}, area{area}
{
}

std::string Ethnologist::get_name()
{
    return this->name;
}

std::string Ethnologist::get_area()
{
    return this->area;
}

std::ostream& operator<<(std::ostream& os, const Ethnologist& e)
{
    os << e.name << e.area;
    return os;
}

std::istream& operator>>(std::istream& is, Ethnologist& e)
{
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = e.tokenize(line, ';');

    if (tokens.size() != 3)
        return is;

    e.name = tokens[0];
    e.area = tokens[1];

    return is;
}

std::vector<std::string> tokenize(std::string str, char delimiter)
{
    std::vector<std::string>result;
    std::stringstream ss(str);
    std::string token;

    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}
*/
