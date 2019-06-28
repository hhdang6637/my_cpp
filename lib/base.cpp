#include "base.h"
#include "func_trace.h"

base::base(bool trace, std::ostream &os) : __trace(trace), __os(os)
{
    if (__trace)
    {
        __os << "called contructer base() " << this << std::endl;
    }
}

base::~base()
{
    if (__trace)
    {
        __os << "called destructor ~base()" << this << std::endl;
    }
}

A::A(/* args */) : base(true)
{
    std::cout << "called contructer A() " << this << std::endl;
}

A::~A()
{
    std::cout << "called destructor ~A()" << this << std::endl;
}
