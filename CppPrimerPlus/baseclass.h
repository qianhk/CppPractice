//
// Created by KaiKai on 2021/4/24.
//

#ifndef CPPPRACTICE_BASECLASS_H
#define CPPPRACTICE_BASECLASS_H

#include "baseclass_impl.h"

const int gTestConstValue = 100;
extern const int gTestConstValue2;

void outputTestConstValueInfo();

namespace kaicpp {
    template<typename T>
    void kaiswap(T &a, T &b);

    template<typename T1, typename T2>
    void ft(T1 x, T2 y);

    auto testAutoResult(int x, float y) -> decltype(x + y);

    namespace subns {
        namespace subns2 {
            const int innerValue = 200;
        }
    }

    enum {
        MONTHS = 12
    };

    enum TestEnum {
        Enum1, ENum2
    };

    class BaseClass {
    public:
        //默认可实现：默认构造函数 默认析构函数 复制构造函数 赋值运算符 地址运算符
        // C++11 还有：移动构造函数 移动赋值运算符
        explicit BaseClass(int testValue); //禁止隐式转换
        BaseClass(const BaseClass &other);
        BaseClass &operator=(const BaseClass &other);
        static const int MONTHS = 12;
        enum TestM {
            Months = 12
        };
        double costs[MONTHS];
        double costs2[Months];

        void setTestValue(int testValue);

    public:
        std::ostream &operator<<(std::ostream &os); //成员函数重载<<
        explicit operator int() const; //转换函数

    protected:
        friend std::ostream &operator<<(std::ostream &os, const BaseClass &c); //全局函数重载<<

    private:
        int mTestValue;
    };

    enum class egg { //不加class编译不过，属于相同的作用域
        Small, Media, Large, Jumbo
    };
    enum class tshirt { //不加class编译不过，属于相同的作用域，限制作用域在类里
        Small, Media, Large, Xlarge
    };
}

//void kaiswap2(int &a, int &b);

#endif //CPPPRACTICE_BASECLASS_H
