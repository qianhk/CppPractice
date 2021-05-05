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

kaicpp::BaseClass::BaseClass(int testValue) : mTestValue(testValue) {
    ++sJs;
    std::cout << "BaseClass(int) js=" << sJs << " _value=" << testValue << std::endl;
    strcpy(mCity, "BaseClass(int)");
}

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
    ++sJs;
    std::cout << "CopyConstruct_js=" << sJs << " other.value=" << other.mTestValue << std::endl;
    strcpy(mCity, "BaseClass(const BaseClass&)");
    mTestValue = other.mTestValue;
}

kaicpp::BaseClass &kaicpp::BaseClass::operator=(const kaicpp::BaseClass &other) {
    if (this != &other) { // Operator=() does not handle self-assignment properly 处理自我赋值
        //clear old data or delete pointer
        printf("operator=1 old.value=%d newValue=%d\n", mTestValue, other.mTestValue);
        this->mTestValue = other.mTestValue;
        strcpy(mCity, "BaseClass::operator=1");
    }
    return *this;
}


kaicpp::BaseClass &kaicpp::BaseClass::operator=(int testValue) {
    printf("operator=2 old.value=%d newValue=%d\n", mTestValue, testValue);
    this->mTestValue = testValue;
    strcpy(mCity, "BaseClass::operator=2");
    return *this;
}

void kaicpp::BaseClass::setTestValue(int testValue) {
    mTestValue = testValue;
}

bool kaicpp::BaseClass::operator==(const kaicpp::BaseClass &rhs) const {
    return mTestValue == rhs.mTestValue;
}

bool kaicpp::BaseClass::operator!=(const kaicpp::BaseClass &rhs) const {
    return !(rhs == *this);
}

bool kaicpp::BaseClass::operator<(const kaicpp::BaseClass &rhs) const {
    return mTestValue < rhs.mTestValue;
}

bool kaicpp::BaseClass::operator>(const kaicpp::BaseClass &rhs) const {
    return rhs < *this;
}

bool kaicpp::BaseClass::operator<=(const kaicpp::BaseClass &rhs) const {
    return !(rhs < *this);
}

bool kaicpp::BaseClass::operator>=(const kaicpp::BaseClass &rhs) const {
    return !(*this < rhs);
}

char &kaicpp::BaseClass::operator[](int i) {
    return mCity[i];
}

int kaicpp::BaseClass::sJs = 0;

kaicpp::BaseClass::~BaseClass() {
    printf("~BaseClass() js=%d value=%d city=%s\n", sJs, mTestValue, mCity);
    --sJs;
}
