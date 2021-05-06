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
namespace kaicppsub2 = kaicpp::subns::subns2;
using std::endl;

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

    int ia = 1, ib = 2, ic = 3, id = 4, ie = kaicpp::subns::subns2::innerValue, ig = kaicppsub2::innerValue;
    float fa = 10.1, fb = 20.2;
    kaicpp::kaiswap(ia, ib);
    kaicpp::kaiswap(fa, fb);
    kaicpp::kaiswap(ic, id);
    printf("ia=%d ib=%d fa=%.1f fb=%.1f ic=%d id=%d\n", ia, ib, fa, fb, ic, id);
    kaicpp::ft(ia, fa);
    float result = kaicpp::testAutoResult(ie, fa);
    result = kaicpp::testAutoResult(ig, fa);
    int noNeedInt = kaicpp::MONTHS;
    noNeedInt = kaicpp::ENum2;
    noNeedInt = kaicpp::TestEnum::Enum1;

    kaicpp::BaseClass baseClass(10);
    noNeedInt = baseClass.Months;
    noNeedInt = kaicpp::BaseClass::MONTHS;
    noNeedInt = kaicpp::BaseClass::TestM::Months;

    baseClass.costs;
    noNeedInt = int(kaicpp::egg::Media); //类作用域内的枚举不能隐式转换
    noNeedInt = static_cast<int>(kaicpp::tshirt::Large);
//    kaicpp::BaseClass baseClass2 = 10;// 构造函数加了explicit后必须显示转换
    std::cout << baseClass << endl;
    baseClass << std::cout << endl;
    noNeedInt = static_cast<int>(baseClass);
    kaicpp::BaseClass baseClass2(baseClass);
    kaicpp::BaseClass baseClass3 = baseClass; //有可能是复制构造后再赋值，取决于编译器的实现
    baseClass3.setTestValue(42);
    baseClass2 = baseClass3;
    char &c = baseClass2[3];
    baseClass3 = 82;
    baseClass3 = baseClass3;
    std::cout << "----------------1-------------\n";
    kaicpp::BaseClass baseClass4 = baseClass + baseClass2;
    std::cout << "----------------2-------------\n";
    baseClass4 = baseClass + baseClass3;
    std::cout << "----------------3-------------\n";
//    baseClass + baseClass2 = baseClass4;
    std::cout << "----------------4-------------\n";
    return 0;
}

/*


 */