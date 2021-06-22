#ifndef BUILDING_H
#define BUILDING_H

#endif // BUILDING_H

#include <string>
#include <vector>
#include <QDebug>
#include <sstream>

#pragma once

class Building
{
private:
    std::string id;
    std::string description;
    std::string sector;
    std::vector<std::string> location;

public:
    Building();
    ~Building();

    std::string get_id();
    std::string get_description();
    std::string get_sector();
    std::vector<std::string> get_location();

    Building(std::string _id, std::string _description, std::string _sector, std::vector<std::string> _location);
    friend std::ostream& operator<<(std::ostream& os, const Building& b);
    friend std::istream& operator>>(std::istream& is, Building& b);

    std::vector<std::string> tokenize(std::string str, char delimiter);
};

inline Building::Building() {}
inline Building::~Building() {}

inline Building::Building(std::string _id, std::string _description, std::string _sector, std::vector<std::string> _location) :
    id{_id}, description{_description}, sector{_sector}, location{_location} {}

inline std::ostream& operator<<(std::ostream& os, const Building& b)
{
    os << b.id;
    return os;
}

inline std::istream& operator>>(std::istream& is, Building& b)
{
    std::string line;
    std::getline(is, line);
    std::vector<std::string> tokens = b.tokenize(line, ',');

    if(tokens.size() != 4)
        return is;

    b.id = tokens[0];
    b.description = tokens[1];
    b.sector = tokens[2];
    b.location.clear();

   if(tokens[3].find(';'))
    {
        std::vector<std::string> tokens2 = b.tokenize(tokens[3], ';');

        for(auto s : tokens2)
            b.location.push_back(s);
    }
    else
        b.location.push_back(tokens[3]);

    return is;
}

inline std::vector<std::string> Building::tokenize(std::string str, char delimiter)
{
    std::vector<std::string>result;
    std::stringstream ss(str);
    std::string token;

    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

inline std::string Building::get_id()
{
    return this->id;
}

inline std::string Building::get_description()
{
    return this->description;
}

inline std::string Building::get_sector()
{
    return this->sector;
}

inline std::vector<std::string> Building::get_location()
{
    return this->location;
}
