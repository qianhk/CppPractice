//
// Created by KaiC on 2021/4/6.
//

#include "leftright.h"
#include <iostream>
#include <vector>


std::vector<int> return_vector() {
    std::vector<int> tmp{1, 2, 3, 4, 5};
    //return std::move(tmp);
    printf("Right Ref: tmp addr=0x%llx\n", (long long) &tmp);
    return tmp;
}

class A {
public:
    void foo() const { std::cout << "A::foo() const\n"; }

    void foo() { std::cout << "A::foo()\n"; }

    void testRightRef(int &&a) {
        void *pAddr = &a;
        printf("Right Ref Param Addr: 0x%llx\n", (long long) pAddr);
    }
};

A bar() { return A(); }           //返回临时对象，为右值
const A cbar() { return A(); }    //返回带const的右值（带CV限定符）

int mainLeftRight() {
    std::vector<int> &&rval_ref = return_vector();
    const std::vector<int> &rval_ref2 = return_vector();
    std::vector<int> test_vec = return_vector();
    test_vec.push_back(6);
    rval_ref = test_vec;
    test_vec.push_back(7);
    printf("Right Ref vector: 0x%llx 0x%llx 0x%llx\n", (long long) &rval_ref, (long long) &rval_ref2, (long long) &test_vec);

    bar().foo();  // 非const对象调用A::foo()的非const版本
    cbar().foo(); // const对象调用A::foo()的const版本
    //void *pAddr = &bar(); //error: taking the address of a temporary object of type 'A'
    A &&aaa = bar();
    const void *pAddr = &aaa;
    const A &bbb = bar();
    pAddr = &bbb;

    bar().testRightRef(3);

    const int &testRef = 5;
    int &&testRef2 = 6;
    printf("Right Ref1: %d 0x%llx 0x%llx\n", testRef2, (long long) &testRef, (long long) &testRef2);
    return testRef2;
}
