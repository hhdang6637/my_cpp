#if !defined(_BASE_CLASE_)
#define _BASE_CLASE_

#include <iostream>

class base
{
private:
    static unsigned long count;

protected:
    bool __trace;
    static std::ostream &__OS;

public:
    base(bool trace = true);
    virtual ~base();

    void set_trace(bool trace) { __trace = trace; }

    static unsigned long get_number_inst_of_base() { return base::count; };
};

class A : public base
{
private:
public:
    A(bool trace = true);
    ~A() override;
};

#endif // _BASE_CLASE_
