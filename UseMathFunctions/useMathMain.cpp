//
// Created by tianc on 2021/1/10.
//

#include "useMathMain.h"
#include <cmath>
#include <iostream>
#include "CTestConfig.h"

#ifdef USE_MYMATH
#include "mysqrt.h"
#endif

int mainUseMath(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stdout, "Usage: %s number\n", argv[0]);
        return -1;
    }

//    double inputValue2 = atof(argv[1]);
    double inputValue = std::strtod(argv[1], nullptr);

//    char str[30] = "a20.30300 This is test";
//    char *ptr;
//    double ret;
//    ret = strtod(str, &ptr);
//    printf("数字（double）是 %lf\n", ret);
//    printf("字符串部分是 |%s|\n", ptr);

#ifdef USE_MYMATH
    double outputValue = mysqrt(inputValue);
#else
    double outputValue = sqrt(inputValue);
#endif
    fprintf(stdout, "The square root of %g is %g\n", inputValue, outputValue);
    return 0;
}
