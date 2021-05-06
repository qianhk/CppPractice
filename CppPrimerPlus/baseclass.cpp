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

//成员数据被初始化顺序与他们出现在类声明中的顺序相同，与初始化器(成员初始化列表)中的排列顺序无关
kaicpp::BaseClass::BaseClass(int testValue) : /*mTestValue2(2), */ mTestValue(testValue) {
    ++sJs;
    ++sTotalJs;
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
    ++sTotalJs;
    std::cout << "CopyConstruct_js=" << sJs << " other.value=" << other.mTestValue << std::endl;
    strcpy(mCity, "BaseClass(const BaseClass&)");
    mTestValue = other.mTestValue;
}

kaicpp::BaseClass &kaicpp::BaseClass::operator=(const kaicpp::BaseClass &other) {
    if (this == &other) { // 如果没有则 Operator=() does not handle self-assignment properly 处理自我赋值
        return *this;
    }
    //clear old data or delete pointer
    //delete []mPointers; delete mPointer;
    printf("operator=1 old.value=%d newValue=%d\n", mTestValue, other.mTestValue);
    this->mTestValue = other.mTestValue;
    strcpy(mCity, "BaseClass::operator=1");
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
int kaicpp::BaseClass::sTotalJs = 0;

kaicpp::BaseClass::~BaseClass() {
    printf("~BaseClass() js=%d totalJs=%d value=%d city=%s\n", sJs, sTotalJs, mTestValue, mCity);
    --sJs;
}

const kaicpp::BaseClass kaicpp::BaseClass::operator+(const kaicpp::BaseClass &r) const {
    return kaicpp::BaseClass(mTestValue + r.mTestValue);
}

kaicpp::DerivedClass::DerivedClass() : BaseClass(1010) {
    printf("%s\n", __FUNCTION__ );
}

void kaicpp::BaseClass::printInfoVirtual() {
    printf("BaseClass %s\n", __FUNCTION__ );
}

void kaicpp::BaseClass::printInfoNoVirtual() {
    printf("BaseClass %s\n", __FUNCTION__ );
}

void kaicpp::DerivedClass::printInfoVirtual() {
    printf("DerivedClass %s\n", __FUNCTION__ );
}

void kaicpp::DerivedClass::printInfoNoVirtual() {
    printf("DerivedClass %s\n", __FUNCTION__ );
}

kaicpp::DerivedClass::~DerivedClass() {
    printf("%s\n", __FUNCTION__ );
}

