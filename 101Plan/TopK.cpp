//
//  TopK.cpp
//  101Plan
//
//  Created by zl on 06/02/17.
//  Copyright © 2017年 zhu-liang. All rights reserved.
//

#include "TopK.hpp"

#if 0

int k = 10;
int n = 100000;
int heap[10] = {0};

void topK()
{
    
}


void heapSortTopToDown(int pos)
{
    // 计算其子节点
    int j = 2 * pos + 1;
    int temp = heap[pos];
    
    while( j < k)
    {
        if (j+1 < k && heap[j+1] < heap[j])
        {
            j++;
        }
        if (heap[j])
    }
}

void createInitialHeap()
{
    for(int i = 0; i<k; i++)
    {
        scanf("%d", &heap[i]);
    }
    
    //数组中有了最前面的10个值, 调整堆，变为最小堆
    for(int i = k/2 -1; i>=0; i--)
    {
        headSortTopToDown(i);
    }
}

#endif
