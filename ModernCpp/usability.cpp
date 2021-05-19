//
//

#include "usability.h"
#include <iostream>
#include <vector>
#include <tuple>

#define LEN 10

int len_foo() {
    int i = 2;
    return i;
}

constexpr int len_foo_constexpr() {
    return 5;
}

constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

std::tuple<int, double, std::string> f() {
    return std::make_tuple(1, 2.3, "456");
}

void usabilityMain() {
    if (std::is_same<decltype(NULL), decltype(0)>::value)  //always false
        std::cout << "NULL == 0" << std::endl;
    if (std::is_same<decltype(NULL), decltype((void *) 0)>::value)  //always false
        std::cout << "NULL == (void *)0" << std::endl;
    if (std::is_same<decltype(NULL), std::nullptr_t>::value)  //always false
        std::cout << "NULL == nullptr" << std::endl;
    if (std::is_same<decltype(NULL), decltype(NULL)>::value)  //always true
        std::cout << "NULL == NULL" << std::endl;

    char arr_1[10];                      // 合法
    char arr_2[LEN];                     // 合法

    int len = 10;
    // 注意，现在大部分编译器其实都带有自身编译优化，很多非法行为在编译器优化的加持下会变得合法，若需重现编译报错的现象需要使用老版本的编译器。
    // clang++ -v Apple clang version 11.0.0 是能正常运行的
//    int arr_3[len];                  // 非法
//    arr_3[1] = 100;

    const int len_2 = len + 1;
    constexpr int len_2_constexpr = 1 + 2 + 3;
    char arr_4[len_2];                // 非法
    char arr_4_2[len_2_constexpr];         // 合法

    // char arr_5[len_foo()+5];          // 非法
    char arr_6[len_foo_constexpr() + 1]; // 合法

    std::cout << fibonacci(10) << std::endl;
    // 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
    std::cout << fibonacci(10) << std::endl;

    std::vector<int> vec = {1, 2, 3, 4};

    // 在 c++17 之前
    const std::vector<int>::iterator itr1 = std::find(vec.begin(), vec.end(), 2);
    if (itr1 != vec.end()) {
        *itr1 = 3;
    }

    // 需要重新定义一个新的变量
    const std::vector<int>::iterator itr2 = std::find(vec.begin(), vec.end(), 3);
    if (itr2 != vec.end()) {
        *itr2 = 4;
    }

    //c++ 17  if 里可定义局部变量名
    if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3);
            itr != vec.end()) {
        *itr = 4;
    }

    auto [x, y, z] = f(); //std::make_tuple c++ 11 但自动解包c++ 17
    std::cout << "std::make_tuple " << x << ", " << y << ", " << z << std::endl;

    if (std::is_same<decltype(x), int>::value)
        std::cout << "type x == int" << std::endl;
    if (std::is_same<decltype(x), float>::value)
        std::cout << "type x == float" << std::endl;
    if (std::is_same<decltype(x), decltype(z)>::value)
        std::cout << "type z == type x" << std::endl;
}
