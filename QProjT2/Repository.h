#ifndef REPOSITORY_H
#define REPOSITORY_H

#endif // REPOSITORY_H

#pragma once

#include <vector>
#include <algorithm>
#include "RepositoryException.h"
#include <QDebug>
// STL vector based Repository module

template<typename T>
class STLRepository {
private:
    std::vector<T> vector;

public:
    // Constructor.
    STLRepository();

    // Destructor.
    ~STLRepository();

    // Add an element.
    void add(T elem);

    // Remove element by position.
    T removeElem(int pos);

    // Remove element by name.
    T removeByName(std::string name);

    // Update an element by name.
    T updateElem(std::string name, T newElem);

    // Get all elements.
    typename std::vector<T> getAllElements();

    // Get element by position.
    T getElement(int pos);

    // Get the number of total elements.
    int getNrElements();

    // Searches for element, returns pointer to element.
    T* searchElem(std::string name);
};

template<typename T>
inline STLRepository<T>::STLRepository()
{
}

template<typename T>
inline STLRepository<T>::~STLRepository()
{
}

template<typename T>
inline void STLRepository<T>::add(T elem)
{
    // Push back element.
    this->vector.push_back(elem);
}

template<typename T>
inline T STLRepository<T>::removeElem(int pos)
{
    // Removes element on position "pos", returns the removed element.
    // Throws "RepositoryException" if the desired element does not exist.

    T elemTBR;
    try
    {
        elemTBR = this->vector.at(pos);
        this->vector.erase(this->vector.begin() + pos);
    }
    catch (const std::exception& oor)
    {
        throw oor;
    }

    return elemTBR;
}

template<typename T>
inline T STLRepository<T>::removeByName(std::string name)
{
    // Removes element with the specified name, returns the removed element.
    // Throws "RepositoryException" if the desired element does not exist.

    if (this->existsElem(name) != nullptr)
        throw RepositoryException("The element that you want to remove does not exist!");

    T elemTBR;

    for(unsigned int i = 0; i < this->vector.size(); ++i)
        if (this->vector[i].get_name() == name)
        {
            elemTBR = this->vector[i];
            this->removeElem(i);
            break;
        }

    return elemTBR;
}

template<typename T>
inline T STLRepository<T>::updateElem(std::string name, T newElem)
{
    // Updates element with the specified name to "newElem".
    // Throws "RepositoryException" if the desired element does not exist.

    //if (this->searchElem(name) != nullptr)
        //throw RepositoryException("The element that you want to update does not exist!");

    T elemTBR;

    for(auto& elem : this->vector)
        if (elem.get_id() == name)
        {
            elemTBR = elem;
            elem = newElem;
        }

    return elemTBR;
}

template<typename T>
inline typename std::vector<T> STLRepository<T>::getAllElements()
{
    // Gets all elements.
    return this->vector;
}

template<typename T>
inline T STLRepository<T>::getElement(int pos)
{
    // Get element at position "pos".
    return this->vector[pos];
}

template<typename T>
inline int STLRepository<T>::getNrElements()
{
    return this->vector.size();
}

template<typename T>
inline T* STLRepository<T>::searchElem(std::string name)
{
    // Returns reference to element with specfied name, nullptr if the element does not exist.

    for(int i = 0; i < this->vector.size(); ++i)
        if(vector[i].get_id() == name)
            return &vector[i];

    return nullptr;
}
