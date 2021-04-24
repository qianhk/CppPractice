#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#include <memory.h>
#include <stdatomic.h>

#define MONTHS 12

_Thread_local int tValue = 3; //每个线程都获得该变量的私有备份

int main(void) {
    const int maxCount = 3;
    int testValue = INT_MAX;
    const int *abc = &maxCount;
    int days[][MONTHS] = {{31, [2]=31, 30, [5] = 30},
                          {31, 29, [2]=31, 30, [5] = 30}};
//    int testSz[maxCount] = {0};
//    *abc = 4;
//    abc = &testValue;
    _Bool testBool = 1;
    printf("Hello, Wo\brld!  0x%llX %%p=%p sizeof(int)=%zd sizeof(long)=%llu %c%c tV=%d\n",
           (unsigned long long) abc, abc, sizeof(int), sizeof(long), 'K', tolower('K'), tValue);
    printf("Line4444"
           "Line5555\n");
//    while (1) {
//        int test = 100;
//        printf("please input number: ");
//        fflush(stdout);
//        test = getchar();
////        scanf_s("%d", &test);
//        scanf("%d", &test);
//        if (test == 0) {
//            break;
//        }
//        getchar();
//        printf("Hello, World!  %d\n", test / 3);
//    }
    char words[16] = "default";
//    getchar();
    printf("please input string: ");
//    fgets(words, sizeof(words), stdin);
//    gets_s(words, sizeof(words));
    printf("gets: %s\n", words);

    int ar[10] = {0};
    //restrict允许编译器优化代码，只能用于指针，表明restar是访问对象唯一且初始的方式
    int *restrict restar = (int *) malloc(10 * sizeof(int));
//    int *restar2 = restar;
    memset(restar, 0, 10 * sizeof(int));
    int *par = ar;
    for (int n = 0; n < 10; n++) {
        par[n] += 5;
        restar[n] += 5;
        ar[n] *= 2;
        par[n] += 3;
//        restar2[n] += 1;
        restar[n] += 3; // restar[n] += 5; restar[n] += 3; 可能会被合并成 restar[n] += 8;
        printf("n=%d v=%d    ", n, restar[n]);
    }
    free(restar);
    printf("\n");

    _Atomic int hogs;
    atomic_store(&hogs, 12);
    printf("hogs=%d\n", hogs);

    return 0;
}

/*
 strlen
 strcat   strncat
 strcmp   strncmp
 strcpy   strncpy
 _snprintf_s _snwprintf_s
 sprintf  %c 单个字符  %d 有符号十进制  %e 浮点数，e记数法 %E %f %g 自动选%f或%e %G
    %o 无符号八进制 %p 指针 %s 字符串 %u 无符号十进制 %x 无符号十六进制 %X %%  %i(=%d) %a %A 浮点数、十六进制和p记数法
 strchr 子字符      strrchr 子字符最后一次出现的位置
 strstr 子字符串的首位置
 strpbrk s1字符串中 包含s2字符串中的任意字符



 islower isalnum isalpha iscntrl isdigit isgraph islower isprint ispunct isspace isupper isxdigit toupper
 atoi   strtol
 atof   atol  strtol strtoul  strtod

 */
