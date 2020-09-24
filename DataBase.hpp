#include <iostream>
using namespace std;
#pragma once
template <class T>
class DataBase
{
public:
    DataBase()=default;
    virtual ~DataBase();
    virtual T display();
};
template <class T>
T DataBase<T>::display(){return "name";}
template <class T>
DataBase<T>::~DataBase(){}



