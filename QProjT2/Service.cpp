#include "Service.h"

Service::Service()
{
}

Service::~Service()
{
}

void Service::addEthnologist(Ethnologist e)
{
    this->repo_e.add(e);
}

void Service::addBuilding(Building b)
{
    this->repo_b.add(b);
}

void Service::readEthnologists()
{
    std::ifstream fin("ethnologists.txt");

    if (!fin.is_open())
    {
        qInfo() << "FIle erorr";
        return;
    }

    qInfo() << "FIle opne";

    Ethnologist e;
    while (fin >> e)
    {
        this->addEthnologist(e);
        qInfo() << e.get_name().c_str() << ' ' << e.get_area().c_str();
    }

    fin.close();
}

void Service::readBuildings()
{
    std::ifstream fin("buildings.txt");

    if (!fin.is_open())
        return;

    Building p;
    while (fin >> p)
    {
        this->addBuilding(p);
        qInfo() << p.get_id().c_str() << ' ' << p.get_description().c_str() << ' ' << p.get_sector().c_str();
    }

    fin.close();
}

std::vector<Ethnologist> Service::getAllEthnologists()
{
    return this->repo_e.getAllElements();
}

std::vector<Building> Service::getAllBuildings()
{
    return this->repo_b.getAllElements();
}
