//
// Created by KaiKai on 2021/4/24.
//

#ifndef CPPPRACTICE_BASECLASS_H
#define CPPPRACTICE_BASECLASS_H

#include "baseclass_impl.h"

const int gTestConstValue = 100;
extern const int gTestConstValue2;

class BaseClass {

};

void outputTestConstValueInfo();

namespace kaicpp {
    template<typename T>
    void kaiswap(T &a, T &b);

    template<typename T1, typename T2>
    void ft(T1 x, T2 y);
}

//void kaiswap2(int &a, int &b);


#endif //CPPPRACTICE_BASECLASS_H
