//
//  map_usage.hpp
//  101Plan
//
//  Created by zl on 22/01/17.
//  Copyright © 2017年 zhu-liang. All rights reserved.
//

#ifndef map_usage_hpp
#define map_usage_hpp

#include <stdio.h>
#include <map>
#include <ostream>

using TrivalMap = std::map<char, int>;

class MapTester {
    
public:
    MapTester();
    MapTester(const MapTester&) = default;
    MapTester& operator=(const MapTester&) = default;
    ~MapTester() = default;
    //void printAll();

public:
    TrivalMap myMap;
};

std::ostream& operator<<(std::ostream& os, const MapTester& param);
bool operator==(const MapTester& lhs, const MapTester& rhs);
#endif /* map_usage_hpp */
