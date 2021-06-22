#include "mainwindow.h"

#include <QApplication>
#include <vector>
#include <QDebug>
#include "Window.h"

#pragma once

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    Service s;

    s.readEthnologists();
    s.readBuildings();

    std::vector<Ethnologist> eth = s.getAllEthnologists();
    std::vector<Building> bul = s.getAllBuildings();

    for(auto e : eth)
        qInfo() << e.get_name().c_str() << ' ' << e.get_area().c_str();

    for(auto b : bul)
    {
        qInfo() << b.get_id().c_str() << ' ' << b.get_description().c_str() << ' ' << b.get_sector().c_str();

        for(auto loc : b.get_location())
           qInfo() << loc.c_str();
    }

    QString colours[10] = {"cyan","magenta", "red",
                              "darkRed", "darkCyan", "darkMagenta",
                             "green", "darkGreen", "yellow",
                              "blue"};
    int color;

    for(auto e : eth)
    {
        Window* w = new Window(s, e);

        color = rand() % 10;

        w->setWindowTitle(e.get_name().c_str());
        w->setStyleSheet("background-color:" + colours[color]);
        w->show();
    }

    return a.exec();
}
