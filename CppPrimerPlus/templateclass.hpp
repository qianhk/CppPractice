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

    //成员模板
    template<typename T>
    class beta {
    private:
        template<typename V> //nested template class member
        class hold {
        private:
            V val;
        public:
            explicit hold(V v = 0) : val(v) {}

            void show() const { std::cout << "hold show: " << val << std::endl; }

            void show2() const;

            V value() const { return val; }
        };

        template<typename V> //only declaration
        class hold2;

        hold<T> q;
        hold<int> n;
    public:
        beta(T t, int i) : q(t), n(i) {}

        template<typename U>
        U blab(U u, T t) { return (n.value() + q.value()) * u / t; }

        //only declaration
        template<typename U>
        U blab2(U u, T t);

        void show() const {
            q.show();
            n.show();
        };

        void show2() const;

    };

    // here  class or member definition
    template<typename T>
    template<typename V>
    class beta<T>::hold2 {
    private:
        V val;
    };

    template<typename T>
    template<typename V>
    void beta<T>::hold<V>::show2() const { std::cout << "hold show2: " << val << std::endl; }

    template<typename T>
    void beta<T>::show2() const {
        q.show();
        n.show();
    }

    template<typename T>
    template<typename U>
    U beta<T>::blab2(U u, T t) { return (n.value() + q.value()) * u / t; }

    //将模板用作参数
    template<template<typename T, int maxCount> class Thing, typename U, typename V, int n> //Thing是模板参数，前面是类型
    class Crab {
    private:
        Thing<U, n> s1;
        Thing<V, n> s2;
    public:
        explicit Crab() = default;

        bool push(U a, V x) { return s1.push(a) && s2.push(x); }

        bool pop(U &a, V &x) { return s1.pop(a) && s2.pop(x); }
    };
}

#endif //CPPPRACTICE_TEMPLATECLASS_HPP
