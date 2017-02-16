//
//  cplusplus11.hpp
//  101Plan
//
//  Created by zl on 16/02/17.
//  Copyright © 2017年 zhu-liang. All rights reserved.
//

#ifndef cplusplus11_hpp
#define cplusplus11_hpp

#include <stdio.h>

#define LOG(...) {\
fprintf(stderr, "%s: Line %d:\t", __FILE__, __LINE__);\
fprintf(stderr, __VA_ARGS__); \
fprintf(stderr, "\n");\
}

#endif /* cplusplus11_hpp */
