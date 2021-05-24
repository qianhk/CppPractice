//
// Created by KaiKai on 2021/5/24.
//

#include "stltest.h"
#include <iostream>
#include <vector>
#include <list>
#include <set>

using namespace std;

void stlTestShowInt(int a) {
    cout << a << ' ';
}

void stlTestMain() {
    int casts[10] = {6, 7, 2, 9, 4, 11, 8, 7, 10, 5};
    int casts2[] = {1, 2, 3, 4, 5};
    vector<int> dice(10);
    copy(casts, casts + sizeof(casts) / sizeof(casts[0]), dice.begin());
    cout << "dice: ";
    ostream_iterator<int, char> out_iter(cout, " ");
    copy(dice.begin(), dice.end(), out_iter);
    cout << endl;

    cout << "rbegin rend (implicit): ";
    copy(dice.rbegin(), dice.rend(), out_iter);
    cout << endl;

    cout << "rbegin rend (explicit): ";
    vector<int>::reverse_iterator ri;
    for (ri = dice.rbegin(); ri != dice.rend(); ++ri) {
        cout << *ri << ' ';
    }
    cout << endl;

    sort(dice.begin(), dice.end());

    cout << "rbegin rend (for_each): ";
    for_each(dice.rbegin(), dice.rend(), stlTestShowInt);
    cout << endl;

    cout << "set_union: ";
    int cast2Len = sizeof(casts2) / sizeof(casts2[0]);
    set_union(dice.begin(), dice.end(), casts2, casts2 + cast2Len, out_iter);
    cout << endl;

    vector<int> tmpVec1;
    cout << "set_intersection: ";
    //不能直接tmpVec1.begin()，没有足够空间放
//    set_intersection(dice.begin(), dice.end(), casts2, casts2 + cast2Len, tmpVec1.begin());
    auto &&tmpIter = insert_iterator<vector<int>>(tmpVec1, tmpVec1.begin());
    set_intersection(dice.begin(), dice.end(), casts2, casts2 + cast2Len, tmpIter);
    for_each(tmpVec1.begin(), tmpVec1.end(), stlTestShowInt);
    cout << endl;

    cout << "set_difference: "; //set_difference: 6 7 7 8 9 10 11  前面的迭代器中的且与后面的迭代器中不同的
    tmpVec1.clear();
    tmpIter = insert_iterator<vector<int>>(tmpVec1, tmpVec1.begin());
    set_difference(dice.begin(), dice.end(), casts2, casts2 + cast2Len, tmpIter);
    for_each(tmpVec1.begin(), tmpVec1.end(), stlTestShowInt);
    cout << endl;

    cout << "set_difference2: "; //set_difference2: 1 3
    set<int> C;
    auto &&tmpIterC = insert_iterator<set<int>>(C, C.begin());
    set_difference(casts2, casts2 + cast2Len, dice.begin(), dice.end(), tmpIterC);
    for_each(C.begin(), C.end(), stlTestShowInt);
    cout << endl;
}

/*
 容器: (deque 双端队列) (list 双向链表) (queue队列) (priority_queue最大的元素被移植队首)
 stack (vector 数组容器一种表示) map multimap set multiset
 (bitset c++11后不作为容器看待，视为独立的类别)
 (array 并非stl容器，因为长度是固定的，没有调节容器大小的操作)
 c++ 11后新增: (forward_list 单链表) unordered_map  unordered_multimap unordered_multiset unordered_multiset
 前面序列容器，后面关联容器
 关联容器 set multiset map multimap 底层是基于树结构
 无序关联容器 unordered_set unordered_multiset unordered_map unordered_multimap 底层是基于数据结构哈希表的，提高添加和删除元素速度级提高查找算法效率


 */