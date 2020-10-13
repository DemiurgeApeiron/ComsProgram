#include <iostream>
using namespace std;
#pragma once
class DataBase
{
public:
    DataBase() = default;
    virtual ~DataBase();
    virtual string display();
};

string DataBase::display() { return "name"; }

DataBase::~DataBase() {}
