//
// Created by KaiKai on 2021/4/24.
//

#include "baseclass.h"
#include <iostream>

int gTestValue = 11;
const int gTestConstValue2 = 100;

void outputTestConstValueInfo() {
    printf("&gTestValue in baseClass: %p __func__=%s\n", &gTestValue, __func__);
    printf("&gTestConstValue in baseClass: %p\n", &gTestConstValue);
    printf("&gTestConstValue2 in baseClass: %p\n", &gTestConstValue2);
}

template<>
void kaicpp::kaiswap(int &a, int &b) {
    printf("kaiswap custom version a=%d b=%d\n", a, b);
    int t = a;
    a = b;
    b = t;
}
