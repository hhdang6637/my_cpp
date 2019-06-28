
#include <iostream>
#include <memory>
#include "base.h"
#include "func_trace.h"

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

void uniqueu_ptr_tranfer_ownership()
{
    FUNC_TRACE();
    A *sp = new A();
    std::unique_ptr<A> up1(sp);
    // std::unique_ptr<A> up2(sp); -> crash, cause duplicate free sp's memory

    // std::unique_ptr<A> up2(up1);  // unique_ptr delete copy contructor

    // but unique_ptr have move contructor
    std::unique_ptr<A> up2(std::move(up1));
}

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    // raw_ptr();
    // uniqueu_ptr();
    // uniqueu_ptr_relese();
    uniqueu_ptr_tranfer_ownership();

    return 0;
}
