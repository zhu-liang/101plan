//
//  main.cpp
//  101Plan
//
//  Created by zl on 22/01/17.
//  Copyright © 2017年 zhu-liang. All rights reserved.
//

#include <iostream>
#include "map_usage.hpp"
#include "binary_search_tree.hpp"

#include "smart_ptr.hpp"
#include "cplusplus11.hpp"

using namespace std;

class Foo {
public:
    int iMem = 1;
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Show Time!\n";
    
    //test with map
    MapTester tester;
    //tester.printAll();
    cout << tester;
    performBinarySearchTreeTest();
    cout << "---------" <<endl;
    
    perform_smart_ptr_ops();
    
    Foo a;
    const Foo& b = a;
    //b.iMem = 2;
    cout << "b.iMem " << b.iMem <<endl;
    
    LOG("%d", 100);
    return 0;
}
