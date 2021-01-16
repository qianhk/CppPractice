//
// Created by KaiKai on 2020/11/8.
//

#ifndef TESTDEMO_THREAD_H
#define TESTDEMO_THREAD_H

#include <iostream>
// 必须的头文件是
#include <pthread.h>

using namespace std;

#define NUM_THREADS 5

// 线程的运行函数
void *say_hello(void *args);

class Thread {
public:
    static void doOperate();
};


#endif //TESTDEMO_THREAD_H
