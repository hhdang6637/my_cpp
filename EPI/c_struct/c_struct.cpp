#include <iostream>

struct no_aligment
{
    char a;
    int b;
};

struct aligment
{
    char a;
    int b;
} __attribute__((packed));

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    no_aligment t1;
    std::cout << "sizeof(no_aligment)   = " << sizeof(no_aligment) << std::endl;
    std::cout << "addr of no_aligment   = " << &t1 << std::endl;
    std::cout << "addr of no_aligment.a = " << (void*)&(t1.a) << std::endl;
    std::cout << "addr of no_aligment.b = " << &(t1.b) << std::endl;

    aligment t2;
    std::cout << "sizeof(aligment)   = " << sizeof(aligment) << std::endl;
    std::cout << "addr of aligment   = " << &t2 << std::endl;
    std::cout << "addr of aligment.a = " << (void*)&(t2.a) << std::endl;
    std::cout << "addr of aligment.b = " << &(t2.b) << std::endl;
    return 0;
}
