//
// Created by KaiKai on 2021/5/9.
//

#include "exceptiondemo.h"
#include <iostream>
#include <cstdlib>
#include <exception>

//double hmean_abort(double a, double b) throw(xxx) 可能抛出xxx异常; throw() 不会抛出异常
// c++ 11 抛弃了这种异常规范的用法，后续可能从标准中剔除，因为编译器难以判断函数内容是否真的匹配这种异常规范的声明
//double hmean_abort(double a, double b) noexcept; //C++ 11 新增这种用法表示不会抛出异常，但普通代码仍然不推荐使用

double hmean_abort(double a, double b) {
    if (a == -b) {
        std::cout << "untenable argument to hmean(): std::abort()\n";
//        std::abort();
    }
    return 2.0 * a * b / (a + b);
}

double hmean_throw_const_char_string(double a, double b) {
    if (a == -b) {
        const char *exString = "untenable argument to hmean(): hmean_throw_const_char_string";
        std::cout << "throw exception const char *: " << (void *) exString << std::endl;
        throw exString;
    }
    return 2.0 * a * b / (a + b);
}

class bad_hmean {
private:
    double v1, v2;
public:
    explicit bad_hmean(double a = 0, double b = 0) : v1(a), v2(b) {};
    void mesg() const;
};

inline void bad_hmean::mesg() const {
    std::cout << "bad_hmean_mesg: (" << v1 << ", " << v2 << "): invalid argument a == -b.\n";
}


double hmean_throw_bad_hmean(double a, double b) {
    if (a == -b) {
        const bad_hmean &hmean = bad_hmean(a, b);
        std::cout << "throw exception bad_hmean: " << &hmean << std::endl;
        throw hmean;
    }
    return 2.0 * a * b / (a + b);
}

class bad_hmean2 : public std::exception {
private:
    double v1, v2;
    char whatstr[64];
public:
    explicit bad_hmean2(double a = 0, double b = 0) : v1(a), v2(b) {
        sprintf(whatstr, R"(bad_hmean2_mesg: (%.4f, %.4f) : invalid argument a == -b)", a, b);
    };

    const char *what() const _NOEXCEPT override {
        return whatstr;
    }
};

double hmean_throw_bad_hmean2(double a, double b) {
    if (a == -b) {
//        const bad_hmean2 &hmean = bad_hmean2(a, b);
//        std::cout << "throw exception bad_hmean2: " << &hmean << std::endl;
//        throw hmean;
        throw bad_hmean2(a, b);
    }
    return 2.0 * a * b / (a + b);
}

double hmean_throw_bad_hmean3(double a, double b) throw(int) {
    if (a == -b) {
        throw bad_hmean2(a, b);
    }
    return 2.0 * a * b / (a + b);
}

void myQuit() {
    std::cout << "myQuit, Terminating due to uncaugh exception.\n";
}

void myUnexpected() {
    std::cout << "myUnexpected\n";
}

void exceptionTestMain() {

    std::set_terminate(myQuit);
    std::set_unexpected(myUnexpected);

    double x, y, z;
    x = 3, y = 6;
    z = hmean_abort(x, y);
    z = hmean_abort(10, -10);

    z = hmean_throw_const_char_string(x, y);
    try {
        z = hmean_throw_const_char_string(10, -10);
    } catch (const char *s) { //指针地址相同，未浅复制
        std::cout << "catch hmean_throw_const_char_string: " << s << " address=" << (void *) s << std::endl;
    }

    try {
        z = hmean_throw_bad_hmean(10, -10);
    } catch (const bad_hmean &bg) { //对象会浅复制，即便使用引用；此处依然推荐使用引用，因为当函数是虚函数时，可通过基类执行派生类重写的函数
        bg.mesg();
        std::cout << "catch bad_hmean address=" << &bg << std::endl;
    }

    try {
        z = hmean_throw_bad_hmean2(10, -10);
    } catch (const bad_hmean2 &bg) { //对象会浅复制
        std::cout << "catch bad_hmean2 address=" << &bg << " " << bg.what() << std::endl;
    }

    try {
//        z = hmean_throw_bad_hmean2(10, -10);
    } catch (std::logic_error &logic_error) {
        //不会捕获到这个异常
        std::cout << "no catch : logic_error\n";
    } catch (std::runtime_error &runtime_error) {
        //不会捕获到这个异常
        std::cout << "no catch : runtime_error\n";
    }
    // 会走到std::set_terminate 设置的 myQuit ，但并不能阻止terminate
    // mac os 系统输出：libc++abi: terminate_handler unexpectedly returned

    try {
        z = hmean_throw_bad_hmean2(10, -10);
    } catch (...) {
        //捕获所有类型异常，但应该不见得真的各种各样的异常都能捕获到
        std::cout << "catch ... \n";
    }

//    z = hmean_throw_bad_hmean3(10, -10);
    // 声明抛出int异常，但是抛出的是其它unexpected异常，触发std::set_unexpected 设置的 myUnexpected
    // 然后继续crash, mac os 系统输出 libc++abi: unexpected_handler unexpectedly returned
}

