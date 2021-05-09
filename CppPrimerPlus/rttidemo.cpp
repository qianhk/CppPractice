//
// Created by KaiKai on 2021/5/9.
//

#include "rttidemo.h"
#include "baseclass.h"

using namespace kaicpp;

void rttiDemoMain() {
    BaseClass baseClass = BaseClass(3000);
    DerivedClass derivedClass = DerivedClass();
    BaseClass *pBase = &baseClass;
    DerivedClass *pDerived = &derivedClass;
    pBase = pDerived;
    pDerived = dynamic_cast<DerivedClass *>(pBase); // ok
    pBase = &baseClass;
    pDerived = dynamic_cast<DerivedClass *>(pBase); // return 0
//    pDerived->printInfoVirtual(); //空指针 EXC_BAD_ACCESS (code=1, address=0x0)
    RTTIDemo rttiDemo;
    RTTIDemo *pRttiDemo = &rttiDemo;

    //无继承关系，转出来的指针不为null，直接等于pRttiDemo, 二进制重新解释，含义由程序员代码自行决定
    pBase = reinterpret_cast<BaseClass *>(pRttiDemo);
//    pBase->printInfoVirtual(); //EXC_BAD_ACCESS (code=EXC_I386_GPFLT) 野指针

    const std::type_info &info0 = typeid(pRttiDemo);
    const std::type_info &info1 = typeid(pBase); //0x0000000100f404e0
    pBase = &baseClass; //指向相同类的type_info是同一个实例
    const std::type_info &info2 = typeid(pBase); //0x0000000100f404e0
    pBase = &derivedClass;
    const std::type_info &info3 = typeid(pBase); //0x0000000100f404e0
    pDerived = &derivedClass;
    const std::type_info &info4 = typeid(pDerived); //0x0000000100f40500
    bool boolResult = info1 == info2;
    boolResult = info2 == info4;
    //mac os: info rttiDemo=P8RTTIDemo base=PN6kaicpp9BaseClassE derived=PN6kaicpp12DerivedClassE~DerivedClass
    //mac os : 没有虚函数的类也能得到name，但都不是原始类名，name的值取决于编译器实现
    printf("info rttiDemo=%s base=%s derived=%s", info0.name(), info1.name(), info4.name());
}
