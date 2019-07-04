
#include <iostream>
#include <memory>
#include <stdexcept>
#include "base.h"
#include "func_trace.h"

class A1
{
public:
    A1(){
        FUNC_TRACE()
    };
    virtual ~A1() noexcept(false) {
        FUNC_TRACE()
        throw std::runtime_error("exception of A1 detructor");
    };
};

class A2
{
public:
    A2(){
        FUNC_TRACE()
    };
    virtual ~A2() noexcept(false) {
        FUNC_TRACE()
        A1 a1;
        throw std::runtime_error("exception of A2 detructor");
    };
};

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    try
    {
        A2 a2;
    }
    catch (std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}
