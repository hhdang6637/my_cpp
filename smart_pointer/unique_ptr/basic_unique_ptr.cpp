
#include <iostream>
#include "func_trace.h"

class base
{
private:
    bool __trace;
    std::ostream &__os;
    /* data */
public:
    base(bool trace = false, std::ostream &os = std::cout);
    virtual ~base();
};

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

class A : public base
{
private:
    /* data */
public:
    A(/* args */);
    ~A() override;
};

A::A(/* args */) : base(true)
{
    std::cout << "called contructer A() " << this << std::endl;
}

A::~A()
{
    std::cout << "called destructor ~A()" << this << std::endl;
}

void raw_ptr()
{
    FUNC_TRACE();
    base *a_ptr = new (std::nothrow) A();
    if (a_ptr != nullptr)
    {
        std::cout << "got A with addr " << a_ptr << std::endl;
        delete a_ptr;
    }
}

void uniqueu_ptr()
{
    FUNC_TRACE();
    std::unique_ptr<base> a_ptr(new (std::nothrow) A());
    if (a_ptr.get())
    {
        std::cout << "got A with addr " << a_ptr.get() << std::endl;
    }
}

void uniqueu_ptr_relese()
{
    FUNC_TRACE();
    std::unique_ptr<base> a_ptr(new (std::nothrow) A());
    if (a_ptr.get())
    {
        std::cout << "got A with addr " << a_ptr.get() << std::endl;
        std::cout << "release it " << std::endl;
        a_ptr = nullptr;
    }

    std::unique_ptr<base> a_ptr1(new (std::nothrow) A());
    if (a_ptr1.get())
    {
        std::cout << "got a_ptr1 with addr " << a_ptr1.get() << std::endl;
        std::cout << "manual release it " << std::endl;
        base *b = a_ptr1.release();
        delete b;
    }

    std::unique_ptr<base> a_ptr_reset(new (std::nothrow) A());
    if (a_ptr_reset.get())
    {
        std::cout << "got a_ptr_reset with addr " << a_ptr_reset.get() << std::endl;
        std::cout << "reset it " << std::endl;
        a_ptr_reset.reset();
    }
}

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    raw_ptr();
    uniqueu_ptr();
    uniqueu_ptr_relese();
    return 0;
}
