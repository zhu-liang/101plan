//
//  color_type.hpp
//  101Plan
//
//  Created by zl on 22/01/17.
//  Copyright © 2017年 zhu-liang. All rights reserved.
//

#ifndef color_type_hpp
#define color_type_hpp

#include <stdio.h>
#include <ostream>

enum class COLOR_TYPE:int8_t {
    GREY,
    BLACK,
    RED
};

std::ostream& operator<<(std::ostream& os, const COLOR_TYPE& type)
{
    switch(type)
    {
        case COLOR_TYPE::GREY:
            os << "Grey Color" << std::endl;
            break;
        case COLOR_TYPE::BLACK:
            os << "Black Color" << std::endl;
            break;
        case COLOR_TYPE::RED:
            os << "Red Color" << std::endl;
            break;
        default:
            break;
    }
    return os;
}
#endif /* color_type_hpp */
