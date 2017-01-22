//
//  map_usage.cpp
//  101Plan
//
//  Created by zl on 22/01/17.
//  Copyright © 2017年 zhu-liang. All rights reserved.
//

#include <iostream>
#include "map_usage.hpp"

using namespace std;

MapTester::MapTester()
{
    myMap.insert(pair<char, int>('d', 100));
    myMap.insert(pair<char, int>('c', 200));
    myMap.insert(pair<char, int>('a', 200));
    //下面这一句插入没有起作用, 如果调用 myMap.count('a')的话，返回 1
    myMap.insert(pair<char, int>('a', 300));
    myMap['e'] = 203;
}
/*
void MapTester::printAll()
{
    map<char,int>::iterator it;
    for(it = myMap.begin(); it != myMap.end(); it++) {
        cout << it->first << "=>" << it->second <<endl;
    }
}
*/

ostream& operator<<(ostream& os, const MapTester& param)
{
    os << "Content of the map object is" <<endl;
    map<char, int>::const_iterator it = param.myMap.begin();
    for(; it!= param.myMap.end(); it++)
    {
        os << it->first << "=>" << it->second <<endl;
    }
    os << endl;
    return os;
}

bool operator==(const MapTester& lhs, const MapTester& rhs)
{
    return lhs.myMap.size() == rhs.myMap.size() &&
        std::equal(lhs.myMap.begin(), lhs.myMap.end(), rhs.myMap.begin());
}
