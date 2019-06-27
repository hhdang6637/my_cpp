
#include <iostream>

class trace_log
{
private:
    std::string __fName;
public:
    trace_log(const char *f_name);
    ~trace_log();
};

trace_log::trace_log(const char *f_name) : __fName(f_name)
{
    std::cout << "----------- enter " << __fName << " -----------" << std::endl;
}

trace_log::~trace_log()
{
    std::cout << "----------- leave " << __fName << " -----------" << std::endl;
}


class base
{
private:
    /* data */
public:
    base(/* args */);
    virtual ~base();
};

base::base(/* args */)
{
    std::cout << "called contructer base() " << this << std::endl;
}

base::~base()
{
    std::cout << "called destructor ~base()" << this << std::endl;
}

class A : public base
{
private:
    /* data */
public:
    A(/* args */);
    ~A() override;
};

A::A(/* args */)
{
    std::cout << "called contructer A() " << this << std::endl;
}

A::~A()
{
    std::cout << "called destructor ~A()" << this << std::endl;
}

void without_uniqueu_ptr()
{
    trace_log t(__FUNCTION__);
    base *a_ptr = new (std::nothrow) A();
    if (a_ptr != nullptr)
    {
        delete a_ptr;
    }
}

void with_uniqueu_ptr()
{
    trace_log t(__FUNCTION__);
    std::unique_ptr<base> a_ptr(new (std::nothrow) A());
}

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    without_uniqueu_ptr();
    with_uniqueu_ptr();
    return 0;
}
