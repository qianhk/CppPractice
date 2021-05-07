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
