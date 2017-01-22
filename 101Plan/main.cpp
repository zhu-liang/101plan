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

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Show Time!\n";
    
    //test with map
    MapTester tester;
    //tester.printAll();
    cout << tester;
    performBinarySearchTreeTest();
    cout << "---------" <<endl;
    return 0;
}
