#include <cstdio>
#include <climits>
#include <cctype>
#include <iostream>
#include <vector>
#include <array>
#include <ctime>
#include "baseclass.h"

extern int gTestValue;
//extern const int gTestConstValue2;

int main() {

    printf(R"(raw ansi string \"\n")");
    printf(R"Kai(   self has )")Kai");
    std::cout << std::endl;
    wprintf(LR"(raw wide string \"\n")");
    wprintf(LR"Kai(   self has )")Kai");
    std::wcout << std::endl;

    float d = 4321.123456789f;
    std::cout << std::fixed;
    std::cout.precision(2);
    std::cout.setf(std::ios_base::showpoint);
    std::cout << "float d=" << d << R"(    "extern int gTestValue"=)" << gTestValue;
    std::cout << std::endl;

    std::vector<int> vi{6, 7};
    vi.push_back(10);
//    vi.at(0) = 16;
    for (const auto &item : vi) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;

    std::array<int, 10> ai{1, 3, 4};
    ai[1] = 2;
    ai[6] = 7;
    ai.at(7) = 8;
    for (auto &item : ai) {
        ++item;
    }
    for (const auto &item : ai) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;

    printf("clock per sec: %d\n", CLOCKS_PER_SEC);
    clock_t delay = 0.1 * CLOCKS_PER_SEC;
    clock_t start = clock();
    while (clock() - start < delay) {
        --delay, ++delay;
    }
    std::cout << "after clock\n";

    outputTestConstValueInfo();
    printf("&gTestValue in Main: %p\n", &gTestValue);
    printf("&gTestConstValue in Main: %p\n", &gTestConstValue);
    printf("&gTestConstValue2 in Main: %p\n", &gTestConstValue2);

    int ia = 1, ib = 2, ic = 3, id = 4;
    float fa = 10.1, fb = 20.2;
    kaicpp::kaiswap(ia, ib);
    kaicpp::kaiswap(fa, fb);
    kaicpp::kaiswap(ic, id);
    printf("ia=%d ib=%d fa=%.1f fb=%.1f ic=%d id=%d\n", ia, ib, fa, fb, ic, id);
    kaicpp::ft(ia, fa);
    return 0;
}

/*


 */