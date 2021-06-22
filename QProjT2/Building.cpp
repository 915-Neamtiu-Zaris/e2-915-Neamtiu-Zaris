/*#include "Building.h"
#include <sstream>

Building::Building() {}
Building::~Building() {}

Building::Building(std::string _id, std::string _description, std::string _sector, std::vector<std::string> _location) :
    id{_id}, description{_description}, sector{_sector}, location{_location} {}

std::ostream& operator<<(std::ostream& os, const Building& b)
{
    os << b.id;
    return os;
}

std::istream& operator>>(std::istream& is, Building& b)
{
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = b.tokenize(line, ';');

    if (tokens.size() != 3)
        return is;

    b.id = tokens[0];
    b.description = tokens[1];
    b.sector = tokens[2];

    std::vector<std::string> tokens2 = b.tokenize(tokens[3], ';');

    for(auto s : tokens2)
        b.location.push_back(s);

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
