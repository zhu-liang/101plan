//
//  smart_ptr.cpp
//  101Plan
//
//  Created by zl on 15/02/17.
//  Copyright © 2017年 zhu-liang. All rights reserved.
//

/*
 我们知道auto_ptr通过复制构造或者通过=赋值后,原来的auto_ptr对象就报废了.所有权转移到新的对象中去了.而通过shared_ptr可以让多个智能指针对象同时拥有某一块内存的访问权.但假如我们不希望多个内存块被多个智能指针对象共享,同时又不会像auto_ptr那样不知不觉的就让原来的auto_ptr对象失效,可咋整呢?
 
 这个时候就要使用unique_ptr了,顾名思义嘛,unique是唯一的意思.说明它跟auto_ptr有点类似,就是同时只能有一个智能指针对象指向某块内存.但它还有些其他特性.
 
 1.无法进行复制构造与赋值操作.
 比如auto_ptr<int> ap(new int(88 );
 
 auto_ptr<int> one (ap) ; // ok
 
 auto_ptr<int> two = one; //ok
 
 但unique_ptr不支持上述操作
 
 unique_ptr<int> ap(new int(88 );
 
 unique_ptr<int> one (ap) ; // 会出错
 
 unique_ptr<int> two = one; //会出错
 
 
 2.可以进行移动构造和移动赋值操作
 就是像上面这样一般意义上的复制构造和赋值或出错.但在函数中作为返回值却可以用.
 
 unique_ptr<int> GetVal( ){
 
 unique_ptr<int> up(new int(88 );
 
 return up;
 
 }
 
 
 
 unique_ptr<int> uPtr = GetVal();   //ok
 
 
 
 实际上上面的的操作有点类似于如下操作
 
 unique_ptr<int> up(new int(88 );
 
 unique_ptr<int> uPtr2 = std:move( up) ; //这里是显式的所有权转移. 把up所指的内存转给uPtr2了,而up不再拥有该内存.另外注意如果你使用vs2008是没有std:move这函数的.
 
 //vs2010开始才有,是c++ 11标准出现的内容.
 
 
 
 
 3.可做为容器元素
 我们知道auto_ptr不可做为容器元素.而unique_ptr也同样不能直接做为容器元素,但可以通过一点间接的手段
 
 例如:
 
 unique_ptr<int> sp(new int(88) );
 
 vector<unique_ptr<int> > vec;
 
 vec.push_back(std::move(sp));
 
 //vec.push_back( sp ); 这样不行,会报错的.
 
 //cout<<*sp<<endl;但这个也同样出错,说明sp添加到容器中之后,它自身报废了.
 
 
 
 总结:
 从上面的例子可以看出,unique_ptr和auto_ptr真的非常类似.其实你可以这样简单的理解,auto_ptr是可以说你随便赋值,但赋值完了之后原来的对象就不知不觉的报废.搞得你莫名其妙.而unique就干脆不让你可以随便去复制,赋值.如果实在想传个值就哪里,显式的说明内存转移std:move一下.然后这样传值完了之后,之前的对象也同样报废了.只不过整个move你让明显的知道这样操作后会导致之前的unique_ptr对象失效.
*/

#include "smart_ptr.hpp"
#include <iostream>
#include <memory>
#include "smart_ptr_impl.hpp"

using namespace std;

class TestClass {
public:
    TestClass()
    {
        cout << "Test Class Constructor" <<endl;
    }
    
    ~TestClass()
    {
        cout << "Test Class Destructor " << iMem << endl;
    }
    
    TestClass(const TestClass& ref) = default;
    
    TestClass& operator=(const TestClass& other)
    {
        this->iMem = other.iMem;
        return *this;
    }
    
    TestClass(int iVal)
    {
        cout << "Test Class Constructor with param " << iVal  <<endl;
        iMem = iVal;
    }
    
    int getVal() {
        return iMem;
    }
private:
    int iMem;
};

void justTestRefCount(shared_ptr<TestClass> param)
{
    cout << endl <<"---" <<endl;
    shared_ptr<TestClass> local = param;
    cout << "local ref count " << local.use_count() <<endl;
    cout << "param ref count " << param.use_count() <<endl << "-----" <<endl;
}

shared_ptr<TestClass> getSharedPtr()
{
    shared_ptr<TestClass> pShared = make_shared<TestClass>(10000);
    cout << "pShared ref count " << pShared.use_count() <<endl;
    shared_ptr<TestClass> pSharedNew = pShared;
    cout << "pShared ref count  " << pShared.use_count() <<endl;
    cout << "pSharedNew ref count " << pSharedNew.use_count() <<endl;
    shared_ptr<TestClass> pSharedNewer = pSharedNew;
    cout << "pShared ref count " << pShared.use_count() <<endl;
    cout << "pSharedNew ref count " << pSharedNew.use_count() <<endl;
    cout << "pSharedNewer ref count " << pSharedNewer.use_count() <<endl;
    
    justTestRefCount(pSharedNewer);
    cout << "pSharedNewer ref count " << pSharedNewer.use_count() <<endl;
    return pSharedNewer;
}

zl_shared_ptr<TestClass> zl_getSharedPtr()
{
    zl_shared_ptr<TestClass> pShared (new TestClass(10001));
    cout << "pShared ref count " << pShared.use_count() <<endl;
    zl_shared_ptr<TestClass> pSharedNew(pShared);
    cout << "pShared ref count  " << pShared.use_count() <<endl;
    cout << "pSharedNew ref count " << pSharedNew.use_count() <<endl;
    zl_shared_ptr<TestClass> pSharedNewer = pSharedNew;
    cout << "pShared ref count " << pShared.use_count() <<endl;
    cout << "pSharedNew ref count " << pSharedNew.use_count() <<endl;
    cout << "pSharedNewer ref count " << pSharedNewer.use_count() <<endl;
    return pSharedNewer;
}


void perform_smart_ptr_ops()
{
    //TestClass* pNew = new TestClass();
#if 0
    TestClass a(2);
    TestClass b = a;
    cout << "b's iMem " << b.getVal() <<endl;

    unique_ptr<TestClass> pNew(new TestClass(100));
    
    unique_ptr<TestClass> pNewer = std::move(pNew);
    cout << "pNewer Value is " << pNewer->getVal() <<endl;
    
    // the following line will have run time error;
    //cout << "pNew Value is " << pNew->getVal() <<endl;
#endif
    
#if 1
    shared_ptr<TestClass> pRet = getSharedPtr();
    cout << "Member is " << pRet->getVal();
#else
    zl_shared_ptr<TestClass> pRet = zl_getSharedPtr();
    cout << "Member is " << pRet->getVal();
#endif
}

