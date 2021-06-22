#ifndef OBSERVER_H
#define OBSERVER_H

#endif // OBSERVER_H

#include <vector>

#pragma once

class Observer
{
public:
    virtual void update() = 0;
    virtual ~Observer() {}
};

class Observable
{
private:
    std::vector<Observer*> observers;

public:
    virtual ~Observable() {}

    void add_observer(Observer* obs)
    {
        observers.push_back(obs);
    }

    void remove_observer(Observer* obs)
    {
        auto it = std::find(observers.begin(), observers.end(), obs);

        if(it != observers.end())
            observers.erase(it);
    }

    void notify()
    {
        for(auto obs: observers)
            obs->update();
    }
};
