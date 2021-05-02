#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#include <memory.h>
#include <stdatomic.h>
#include <stdalign.h>
#include <math.h>
#include <tgmath.h>
#include <assert.h>
#include <stdarg.h>

#define MONTHS 12

_Thread_local int tValue = 3; //每个线程都获得该变量的私有备份

typedef struct Book {
    char title[16];
    char author[16];
    float value;
} BOOK, *PBOOK;

//位字段：
struct {
    unsigned int a: 1;
    unsigned int   : 1;
    unsigned int   : 0; //迫使下一字段与下一个整数对齐
    unsigned int b: 2;
    unsigned int c: 2;
    unsigned int d: 8;
} bitStruct;

//宏参数创建字符串: #运算符
#define PSQR(X) printf("The square of " #X " is %d.\n", ((X) * (X)));

//预处理器黏合剂：##运算符
#define XNAME(n) x ## n
#define PRINT_XN(n) printf("x" #n " = %d\n", x ## n);

//变参宏： ... 和 __VA_ARGS__
#define PR(X, ...) printf("Message " #X ": " __VA_ARGS__)
#define my_print(fmt, ...)  printf(fmt, ##__VA_ARGS__) //当可变参数的个数为0时，去掉前面的,
#define my_print2(fmt, ...)  printf(fmt, __VA_ARGS__) //无可变参数变成printf(fmt,)导致编译不过

#if __STDC_VERSION__ < 201112L
#error Kai Prompt: Not C11
#endif

//泛型选择（ C11 )
#define MYTYPE(X) _Generic((X), \
    int : "int", \
    float : "float", \
    double: "double", \
    default: "other"  \
)

float mysqrtf(float v) {
    float result = sqrtf(v);
    printf("mysqrtf v=%.4f result=%.4f\n", v, result);
}

double mysqrt(double v) {
    double result = sqrt(v);
    printf("mysqrt v=%.8f result=%.8f\n", v, result);
}

#define SQRT(X) _Generic((X), float : mysqrtf, default : mysqrt)(X)

void i_will_exit() {
    printf("i_will_exit\n");
}

void i_will_exit2() {
    printf("i_will_exit2\n");
}

float sum(int lim, ...) {
    va_list ap;
    float tot = 0;
    va_start(ap, lim);
    for (int i = 0; i < lim; ++i) {
        float tmpItem = va_arg(ap, double);
        tot += tmpItem;
    }
    va_end(ap);
    return tot;
}

int main(void) {
    atexit(i_will_exit); //至少有32个，后注册的先调用
    atexit(i_will_exit2);
    PSQR(8);
    PSQR(2 + 4);
    int XNAME(1) = 14; // int x1 = 14;
    int XNAME(2) = 20; // int x2 = 20;
    int x3 = 30;
    PRINT_XN(1);
    PRINT_XN(2);
    PRINT_XN(3);
    PR(1, "x1 = %d\n", x1);
    PR(2, "x2 = %d, x3 = %d\n", x2, x3);
    printf("__FILE_NAME__=%s __FILE=__=%s __DATE__=%s __LINE__=%d __TIME__=%s __TIMESTAMP__=%s\n",
           __FILE_NAME__, __FILE__, __DATE__, __LINE__, __TIME__, __TIMESTAMP__);
    printf("__STDC__=%d __STDC_HOSTED__=%d __STDC_VERSION__=%ld __func__=%s\n",
           __STDC__, __STDC_HOSTED__, __STDC_VERSION__, __func__);

#undef XNAME
#undef PRINT_XN

#ifdef XNAME
    printf("haha defined XNAME\n");
#elif defined(PRINT_XN)
    printf("haha defined PRINT_XN\n");
#else
    printf("haha not defined XNAME and PRINT_XN\n");
#endif

#if x3 == 30
    printf("haha x3 == 30\n");
#else
    printf("haha x3 != 30\n"); // print this, x3 not define
#endif

    assert(x3 >= 30); //运行时检查
    _Static_assert(MONTHS >= 12, "MONTHS must >= 12"); //C11 编译时检查

    printf("MYTYPE(x3)=%s\n", MYTYPE(x3));
    printf("MYTYPE(2.0 * x3)=%s\n", MYTYPE(2.0 * x3));
    printf("MYTYPE(__TIMESTAMP__)=%s\n", MYTYPE(__TIMESTAMP__));

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

    struct Book book1 = {"Title 1", "Author1", 1.1f};
    struct Book book2 = {.value = 1.3f, .title="Title 2", "Author2", 2.2f}; //对同一个变量赋值以后面的为准
    BOOK book3 = {"Title 3", "Author3", 3.3f};
    PBOOK pBook1 = &book1, pBook2 = &book2, pBook3 = &book3;

    double dx;
    char ca;
    char cx;
    double dz;
    char cb;
    char alignas(double) cz; //C11  alignas = _Alignas
    printf("char alignment: %zd\n", alignof(char));  //alignof = _Alignof
    printf("double alignment: %zd\n", _Alignof(double));
    printf("&dx: %p\n", &dx);
    printf("&ca: %p\n", &ca);
    printf("&cx: %p\n", &cx);
    printf("&dz: %p\n", &dz);
    printf("&cb: %p\n", &cb);
    printf("&cz: %p\n", &cz);

    printf("sin(M_PI_2)=%.4f\n", sinf(M_PI_2));
    printf("cos(M_PI_2)=%.4f Macro\n", cos(M_PI_2)); //宏
    printf("cos(M_PI_2)=%.4f Function\n", (cos)(M_PI_2)); //函数

    SQRT(2.f);
    SQRT(2);
    sqrt(2.f);

    float total = sum(4, 1.1f, 2.2f, 3.3f, 4.1f);
    my_print2("return value for sum(3, 1.1, 2.2, 2.5, 3.4)=%.2f\n", total);
    my_print("my_print");
    my_print("      my_print %d\n", 2);


    return 0;
}

#undef XNAME
#undef XNAME_2


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

wchar_t wcslen wcscmp wcscpy wcsncpy ...

 islower isalnum isalpha iscntrl isdigit isgraph islower isprint ispunct isspace isupper isxdigit toupper
 atoi   strtol
 atof   atol  strtol strtoul  strtod

 iswlower iswalnum iswalpha ...

 fopen fseek fflush fgetpos fsetpos feof fclose ferror
 getc putc exit fprintf fscanf fgets fputs rewind ftell
 ungetc setvbuff fread fwrite

 按位取反 ~     与 &       或 |     异或 ^
 设置位 flags |= MASK mask为1保留      清空位  flags &= ~MASK mask为1清空      切换位 flags ^= MASK mask中为1的切换
 检查为的值  if ( (flags & MASK) == MASK)
 number << 1 左移1位乘2   >> 1 右移一位除2



 */
