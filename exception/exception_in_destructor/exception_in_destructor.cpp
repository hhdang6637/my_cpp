
#include <iostream>
#include <memory>
#include <stdexcept>
#include "base.h"
#include "func_trace.h"

class A1
{
    A a;
public:
    A1(){
        FUNC_TRACE()
    };
    virtual ~A1() noexcept(false) {
        FUNC_TRACE()
        A a;
        throw std::runtime_error("exception of A1 detructor");
    };
};

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    try
    {
        A1 a1;
    }
    catch (std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}
