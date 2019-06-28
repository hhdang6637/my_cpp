#if !defined(_BASE_CLASE_)
#define _BASE_CLASE_

#include <iostream>

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

class A : public base
{
private:
    /* data */
public:
    A(/* args */);
    ~A() override;
};

#endif // _BASE_CLASE_
