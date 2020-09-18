#include <iostream>
#include <vector>
using namespace std;
#pragma onece;

template <class T>
class Puerto{
protected:

public:
    Puerto(T &_puerto);
    ~Puerto();
};
template <class T>
Puerto<T>::Puerto(T &_puerto){

}
template <class T>
Puerto<T>::~Puerto(){
}
