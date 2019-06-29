#include "base.h"
#include "func_trace.h"

unsigned long base::count = 0;

std::ostream &base::__OS = std::clog;

base::base(bool trace) : __trace(trace)
{
    base::count++;
    if (__trace)
    {
        base::__OS << "called contructer base() " << this << std::endl;
    }
}

base::~base()
{
    if (__trace)
    {
        base::__OS << "called destructor ~base()" << this << std::endl;
    }
    base::count--;
}

A::A(bool trace) : base(trace)
{
    if (__trace)
    {
        base::__OS << "called contructer A() " << this << std::endl;
    }
}

A::~A()
{
    if (__trace)
    {
        base::__OS << "called destructor ~A()" << this << std::endl;
    }
}
