//
//  smart_ptr_impl.hpp
//  101Plan
//
//  Created by zl on 15/02/17.
//  Copyright © 2017年 zhu-liang. All rights reserved.
//

#ifndef smart_ptr_impl_hpp
#define smart_ptr_impl_hpp

#include <stdio.h>

template<typename T>
class zl_shared_ptr {
public:
    zl_shared_ptr(T* ref)
    {
        m_ptr = ref;
        m_ref_count = 1;
    }
    
    zl_shared_ptr()
    {
        m_ptr = nullptr;
        m_ref_count = 0;
    }
    
    zl_shared_ptr(const zl_shared_ptr& other)
    {
        m_ptr = other.m_ptr;
        m_ref_count = other.m_ref_count;
        m_ref_count++;
    }
    
    zl_shared_ptr& operator=(const zl_shared_ptr& other)
    {
        other.m_ref_count++;
        destructor();
        m_ptr = other.m_ptr;
        m_ref_count = other.m_ref_count;
        return *this;
    }
    
    T& operator *()
    {
        return *m_ptr;
    }
    
    T* operator->()
    {
        return m_ptr;
    }
    
    void destructor() {
        if(m_ref_count == 1) {
            delete m_ptr;
            m_ptr = nullptr;
        }
        else
            m_ref_count--;
    }
    
    ~zl_shared_ptr()
    {
        destructor();
    }
    
    unsigned int use_count()
    {
        return m_ref_count;
    }
    
    
private:
    unsigned int m_ref_count;
    T*  m_ptr;
};
#endif /* smart_ptr_impl_hpp */
