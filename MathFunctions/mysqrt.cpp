//
// Created by tianc on 2021/1/10.
//

#include "mysqrt.h"
#include <iostream>
#include <cmath>
#include "Table.h"

double mysqrt(double input) {
    fprintf(stdout, "in MathFunctions library: mysqrt input %g tableSize=%lu\n", input, sizeof(sqrtTable) / sizeof(sqrtTable[0]));
    return sqrt(input);
}
