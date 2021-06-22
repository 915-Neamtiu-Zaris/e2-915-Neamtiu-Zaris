#ifndef SERVICE_H
#define SERVICE_H

#endif // SERVICE_H

#include "Observer.h"
#include "Repository.h"
#include "Ethnologist.h"
#include "Building.h"
#include <fstream>

#pragma once

class Service : public Observable
{
private:
    STLRepository<Ethnologist> repo_e;
    STLRepository<Building> repo_b;

public:
    Service();
    ~Service();

    void addEthnologist(Ethnologist e);
    void addBuilding(Building b);
    void updateBuilding(std::string id, Building b);

    std::vector<Ethnologist> getAllEthnologists();
    std::vector<Building> getAllBuildings();

    void readEthnologists();
    void readBuildings();
};
