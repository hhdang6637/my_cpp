#include <iostream>
#include <array>

#include "base.h"

class zero_size
{
private:
    virtual void zero_size_f1()
    {
        std::cout << "called  zero_size_f1" << std::endl;
    };

    virtual void zero_size_f2()
    {
        std::cout << "called  zero_size_f2" << std::endl;
    };
public:

    zero_size(/* args */){
        //std::cout << "create zero_size" << std::endl;
    };
    virtual ~zero_size(){
        //std::cout << "delete zero_size" << std::endl;
    };
};

class zero_size_l1 : public zero_size
{
private:
    virtual void zero_size_f1() override
    {
        std::cout << "called zero_size_l1_f1" << std::endl;
    };

public:
    zero_size_l1(/* args */){
        // std::cout << "create zero_size_l1" << std::endl;
    };
    virtual ~zero_size_l1() override{
        // std::cout << "delete zero_size_l1" << std::endl;
    };
};

void print_size_of_vptr()
{
    std::array<char, 128> line;
    snprintf(line.data(), line.size(), "size of zero_size : %lu", sizeof(zero_size));
    std::cout << line.data() << std::endl;
    snprintf(line.data(), line.size(), "size of zero_size_l1 : %lu", sizeof(zero_size_l1));
    std::cout << line.data() << std::endl;
}

typedef void (*Fun)(void);

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    // print_size_of_vptr();
    zero_size *z1 = new (std::nothrow) zero_size_l1();
    // std::cout << *((int *)(&z1)) << std::endl;
    Fun pFun = (Fun) * ((int *)*(int *)(z1 + 0) + 0);
    pFun();
    // pFun = (Fun) * ((int *)*(int *)(z1 + 1) + 0);
    // pFun();

    return 0;
}
