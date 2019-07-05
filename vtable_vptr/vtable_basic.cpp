#include <iostream>
#include <array>

#include "base.h"

class NonVirtualClass
{
public:
    void foo() {}
};

class VirtualClass
{
public:
    virtual void foo() {}
};

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    std::cout << "Size of NonVirtualClass: " << sizeof(NonVirtualClass) << std::endl;
    std::cout << "Size of VirtualClass: " << sizeof(VirtualClass) << std::endl;
    return 0;
}
