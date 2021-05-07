//
// Created by KaiKai on 2021/5/7.
//

#ifndef CPPPRACTICE_TEMPLATECLASS_HPP
#define CPPPRACTICE_TEMPLATECLASS_HPP

#include <iostream>

namespace kaicpp {

    template<typename T, int maxCount> //int maxCount: 非类型参数
    class Stack { //模板不是类和成员函数的定义，只是C++编译器指令，说明如何生成类和成员函数定义，具体实现称为实例化，所有模板信息需放在一起
    public:
        bool isEmpty() const;
        bool push(const T &item);
        bool pop(T &item);
    private:
//        const static int MAX = 3;
        T items[maxCount];
        int mTop = 0; // C++ 11 support
    };

//        kaicpp::TestTemplateClass<kaicpp::BaseClass> testT1;
//        kaicpp::TestTemplateClass<kaicpp::BaseClass, float> testT2;
    template<typename T, typename T3, typename T2 = int>
    class TestTemplateClass {
    };

    template
    class kaicpp::Stack<float, 30>; //显式实例化

    template<>
    class TestTemplateClass<Stack<float, 30>, double> {
        //显式具体化 c++11 不要求 >> 之间有空格
    };

    template<>
    class TestTemplateClass<const char *, double, float> { //显式具体化
    };

    template<class T>
    class TestTemplateClass<T, double, float> { //部分具体化
    };
    //编译器将选择具体化程度最高的

    template<typename T, int maxCount>
    bool Stack<T, maxCount>::isEmpty() const {
        bool empty = mTop == 0;
        printf("stack is empty: %d\n", empty);
        return empty;
    }

    template<typename T, int maxCount>
    bool Stack<T, maxCount>::push(const T &item) {
        if (mTop < maxCount) {
            items[mTop++] = item;
            std::cout << "push success: " << item << std::endl;
            return true;
        }
        std::cout << "push failed: " << item << std::endl;
        return false;
    }

    template<typename T, int maxCount>
    bool Stack<T, maxCount>::pop(T &item) {
        if (mTop > 0) {
            item = items[--mTop];
            std::cout << "pop success: " << item << std::endl;
            return true;
        }
        std::cout << "pop failed: " << std::endl;
        return false;
    }
}

#endif //CPPPRACTICE_TEMPLATECLASS_HPP
