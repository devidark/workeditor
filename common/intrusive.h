/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include <boost/noncopyable.hpp>
#include <boost/intrusive_ptr.hpp>
#include "fw/assert.h"

namespace NVis {

//! Класс для наследования и получение inrusive-объекта для boost::intrusive_ptr
class IntrusivePtrBase
    : public boost::noncopyable
{
    public:
        IntrusivePtrBase()
            : references_counter_(0)
        {}

        virtual ~IntrusivePtrBase()
        {
            ASSERT(references_counter_ == 0);
        }

        void Acquire()
        {
            ++references_counter_;
        }

        void Release()
        {
            --references_counter_;
        }

        unsigned GetCounter()
        {
            return references_counter_;
        }

    private:
        unsigned references_counter_;
};

//! Оболочка интрузивного указателя
template <class T>
class IntrusivePtr : public boost::intrusive_ptr<T>
{
    typedef boost::intrusive_ptr<T> B;

    public:
        IntrusivePtr()
        {}

        IntrusivePtr(T* t)
            : B(t)
        {}

        IntrusivePtr(const IntrusivePtr& x)
            : B(x)
        {}

        IntrusivePtr& operator=(const IntrusivePtr& x)
        {
            return static_cast<IntrusivePtr&>(B::operator=(x));
        }
};

inline void intrusive_ptr_add_ref(IntrusivePtrBase* ptr)
{
    ptr->Acquire();
}

inline void intrusive_ptr_release(IntrusivePtrBase* ptr)
{
    ptr->Release();
}

}   // NVis
