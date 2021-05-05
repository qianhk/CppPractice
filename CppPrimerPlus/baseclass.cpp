//
// Created by KaiKai on 2021/4/24.
//

#include "baseclass.h"
#include <iostream>
#include <vector>

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

auto kaicpp::testAutoResult(int x, float y) -> decltype(x + y) {
    return x + y;
}

kaicpp::BaseClass::BaseClass(int testValue) : mTestValue(testValue) {}

std::ostream &kaicpp::operator<<(std::ostream &os, const kaicpp::BaseClass &c) {
    os << "kaicppBaseClass1<<_" << c.mTestValue;
    return os;
}

std::ostream &kaicpp::BaseClass::operator<<(std::ostream &os) {
    os << "kaicppBaseClass2<<_" << this->mTestValue;
    return os;
}

kaicpp::BaseClass::operator int() const {
    std::cout << __FUNCTION__ << std::endl;
    return mTestValue;
}

kaicpp::BaseClass::BaseClass(const kaicpp::BaseClass &other) {
    std::cout << "CopyConstruct_other.value=" << other.mTestValue << std::endl;
    mTestValue = other.mTestValue;
}

kaicpp::BaseClass &kaicpp::BaseClass::operator=(const kaicpp::BaseClass &other) {
    //clear old data or delete pointer
    printf("operator= old.value=%d newValue=%d\n", mTestValue, other.mTestValue);
    this->mTestValue = other.mTestValue;
    return *this;
}

void kaicpp::BaseClass::setTestValue(int testValue) {
    mTestValue = testValue;
}
