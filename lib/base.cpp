#include "base.h"
#include "func_trace.h"

unsigned long base::count = 0;

base::base(bool trace, std::ostream &os) : __trace(trace), __os(os)
{
    base::count++;
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
    base::count--;
}

A::A(bool trace, std::ostream &os) : base(trace, os)
{
    if (__trace)
    {
        std::cout << "called contructer A() " << this << std::endl;
    }
}

A::~A()
{
    if (__trace)
    {
        std::cout << "called destructor ~A()" << this << std::endl;
    }
}
