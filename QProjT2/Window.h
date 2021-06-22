#ifndef WINDOW_H
#define WINDOW_H

#endif // WINDOW_H
#include "Observer.h"
#include "Service.h"
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QGridLayout>
#include <QSortFilterProxyModel>
#include <QPushButton>
#include <QTextEdit>
#include <QObject>
#include <QMessageBox>
#include <cmath>
#include <string>

#pragma once

class Window : public QWidget, public Observer
{
    Q_OBJECT

public:
    Window(Service& obs, Ethnologist e, QWidget* parent = Q_NULLPTR);
    ~Window();

    void update() override;

private:
    Service& observable;
    Ethnologist eth;

    QTableView* view = new QTableView();
    QStandardItemModel* model = new QStandardItemModel(1, 4);

    QPushButton* btnAdd = new QPushButton("Add building");
    QTextEdit* txtId = new QTextEdit();
    QTextEdit* txtDescription = new QTextEdit();
    QTextEdit* txtLocation = new QTextEdit();

    QPushButton* btnUpdate = new QPushButton("Update building");
    QTextEdit* txtDescriptionU = new QTextEdit();
    QTextEdit* txtLocationU = new QTextEdit();
    QTextEdit* txtIdU = new QTextEdit();

private slots:
    void add_building();
    void update_building();

private:
    void populate_model();
    void connect_signals();
};


inline Window::Window(Service& obs, Ethnologist e, QWidget* parent) : QWidget(parent), observable{obs}, eth{e}
{
    this->connect_signals();
    this->observable.add_observer(this);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Thematic sector"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Location"));

    populate_model();
    this->model->removeRow(0);

    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setModel(model);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->setSortingEnabled(true);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);

    QGridLayout* gLay = new QGridLayout();

    view->sortByColumn(2, Qt::AscendingOrder);

    txtId->setMaximumSize(300, 25);
    txtDescription->setMaximumSize(300, 25);
    txtLocation->setMaximumSize(300, 25);
    txtDescriptionU->setMaximumSize(300, 25);
    txtLocationU->setMaximumSize(300, 25);
    txtIdU->setMaximumSize(300, 25);

    gLay->addWidget(view, 0, 0, 3, 4);
    gLay->addWidget(btnAdd, 3, 0, 1, 2);
    gLay->addWidget(txtId, 4, 0, 1, 3);
    gLay->addWidget(txtDescription, 5, 0, 1, 3);
    gLay->addWidget(txtLocation, 6, 0, 1, 3);
    gLay->addWidget(btnUpdate, 7, 0, 1, 2);
    gLay->addWidget(txtIdU, 8, 0, 1, 3);
    gLay->addWidget(txtDescriptionU, 9, 0, 1, 3);
    gLay->addWidget(txtLocationU, 10, 0, 1, 3);

    this->setLayout(gLay);
    this->setMinimumHeight(500);
    this->setMinimumWidth(500);
}

inline Window::~Window() {}

inline void Window::update()
{
    this->model->clear();
    populate_model();
}

inline void Window::populate_model()
{
    QList<QStandardItem*> items;

    for(auto source : this->observable.getAllBuildings())
    {
        std::string location = "";
        for(auto l : source.get_location())
            location.append(l + ' ');

        items.append(new QStandardItem(source.get_id().c_str()));
        items.append(new QStandardItem(source.get_description().c_str()));
        items.append(new QStandardItem(source.get_sector().c_str()));
        items.append(new QStandardItem(location.c_str()));

        this->model->appendRow(items);

        if(this->eth.get_area() == source.get_sector())
            for(int column = 0; column < 4; ++column)
                model->setData(model->index(model->rowCount() - 1, column), QColor(Qt::blue), Qt::BackgroundRole);

        items.clear();
    }
}

inline void Window::connect_signals()
{
    QObject::connect(btnAdd, SIGNAL(clicked()), this, SLOT(add_building()));
    QObject::connect(btnUpdate, SIGNAL(clicked()), this, SLOT(update_building()));
}

inline void Window::add_building()
{
    std::string id = this->txtId->toPlainText().toStdString();
    std::string description = this->txtDescription->toPlainText().toStdString();
    std::string location = this->txtLocation->toPlainText().toStdString();
    std::string sector = this->eth.get_area();

    if(description.size() == 0)
    {
        QMessageBox* msg = new QMessageBox();
        msg->setText("Description cannot be empty.");
        msg->show();
        return;
    }

    std::vector<Building> buls = this->observable.getAllBuildings();
    for(auto b : buls)
    {
        if(id == b.get_id())
        {
            QMessageBox* msg = new QMessageBox();
            msg->setText("Id must be uniqe.");
            msg->show();
            return;
        }
    }

    if(location.size() == 0)
    {
        QMessageBox* msg = new QMessageBox();
        msg->setText("Building must occupy at least one spot.");
        msg->show();
        return;
    }
    Building a;
    std::vector<std::string> locations = a.tokenize(location, ' ');

    for(auto b : buls)
    {
        for(auto loc : b.get_location())
            for(auto l : locations)
                if(loc == l)
                {
                    QMessageBox* msg = new QMessageBox();
                    msg->setText("Buildings cannot overlap");
                    msg->show();
                    return;
                }
    }

    for(int i = 0; i < locations.size() - 1; ++i)
        if(locations[i][1] - locations[i + 1][1] > 1 || locations[i][1] - locations[i + 1][1] < -1)
        {
            QMessageBox* msg = new QMessageBox();
            msg->setText("Building must occupy a contguous place.");
            msg->show();
            return;
        }

    Building b(id, description, sector, locations);
    this->observable.addBuilding(b);
    this->observable.notify();
}

inline void Window::update_building()
{
    std::string id = this->txtIdU->toPlainText().toStdString();
    std::string description = this->txtDescriptionU->toPlainText().toStdString();
    std::string location = this->txtLocationU->toPlainText().toStdString();

    std::vector<Building> buls = this->observable.getAllBuildings();
    std::string building_sector;
    for(auto b : buls)
        if(id == b.get_id())
            building_sector = b.get_sector();

    if(building_sector != this->eth.get_area())
    {
        QMessageBox* msg = new QMessageBox();
        msg->setText("This ethnologist cannot modify this building.");
        msg->show();
        return;
    }

    Building a;
    std::vector<std::string> locations = a.tokenize(location, ' ');

    Building b(id, description, this->eth.get_area(), locations);
    this->observable.updateBuilding(id, b);
    this->observable.notify();
}
