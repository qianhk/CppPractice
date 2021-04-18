#include <stdio.h>
#include <limits.h>
#include <ctype.h>

#define MONTHS 12

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
    printf("Hello, Wo\brld!  0x%llX %%p=%p sizeof(int)=%zd sizeof(long)=%llu %c%c\n",
           (unsigned long long) abc, abc, sizeof(int), sizeof(long), 'K', tolower('K'));
    printf("line1"
           "line2\n");
    while (1) {
        int test = 100;
        printf("please input number: ");
        fflush(stdout);
        test = getchar();
        scanf_s("%d", &test);
        if (test == 0) {
            break;
        }
        getchar();
        printf("Hello, World!  %d\n", test / 3);
    }
    char words[16];
    getchar();
    printf("please input string: ");
    fgets(words, sizeof(words), stdin);
//    gets_s(words, sizeof(words));
    printf("gets: %s", words);
    return 0;
}

/*
 strlen
 strcat   strncat
 strcmp   strncmp
 strcpy   strncpy
 sprintf
 strchr 子字符      strrchr 子字符最后一次出现的位置
 strstr 子字符串的首位置
 strpbrk s1字符串中 包含s2字符串中的任意字符

 islower  toupper
 atoi   strtol
 atof   atol  strtol strtoul  strtod

 */