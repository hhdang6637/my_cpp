
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
    std::unique_ptr<base> a_ptr(new (std::nothrow) A(true));
    if (a_ptr.get())
    {
        std::cout << "got A with addr " << a_ptr.get() << std::endl;
        std::cout << "release it " << std::endl;
        a_ptr = nullptr;
    }

    std::unique_ptr<base> a_ptr1(new (std::nothrow) A(true));
    if (a_ptr1.get())
    {
        std::cout << "got a_ptr1 with addr " << a_ptr1.get() << std::endl;
        std::cout << "manual release it " << std::endl;
        base *b = a_ptr1.release();
        delete b;
    }

    std::unique_ptr<base> a_ptr_reset(new (std::nothrow) A(true));
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
    A *sp = new A(true);
    std::unique_ptr<A> up1(sp);
    // std::unique_ptr<A> up2(sp); -> crash, cause duplicate free sp's memory

    // std::unique_ptr<A> up2(up1);  // unique_ptr delete copy contructor

    // but unique_ptr have move contructor
    std::unique_ptr<A> up2(std::move(up1));
}

void uniqueu_ptr_source_sink()
{
    FUNC_TRACE();
    std::cout << "test uniqueu_ptr source " << std::endl;
    auto sink = [](std::unique_ptr<base> up) {
        (void)up;
    };

    std::unique_ptr<base> a_ptr(new (std::nothrow) A(true));
    // sink(a_ptr);                 // unique_ptr delete copy contructor
    sink(std::move(a_ptr));

    std::cout << "a_ptr must be deleted before reach this line" << std::endl;

    auto source = []() -> std::unique_ptr<base> {
        std::unique_ptr<base> a_ptr(new (std::nothrow) A(true));
        return a_ptr;
    };

    std::unique_ptr<base> a_ptr1 = source();

    if (base::get_number_inst_of_base() != 1)
    {
        throw std::runtime_error("uniqueu_ptr_source_sink: number instance of base is not expected");
    }
}

class test_class_uniqueu_ptr final
{
private:
    std::unique_ptr<base> __a1;
    std::unique_ptr<base> __a2;

public:
    explicit test_class_uniqueu_ptr(base *a1 = nullptr, base *a2 = nullptr) : __a1(a1), __a2(a2){};
    ~test_class_uniqueu_ptr(){};

    void operator=(test_class_uniqueu_ptr &&r)
    {
        FUNC_TRACE();
        __a1 = std::move(r.__a1);
        __a2 = std::move(r.__a2);
    }
};

void uniqueu_ptr_in_class()
{
    FUNC_TRACE();
    {
        test_class_uniqueu_ptr test(new (std::nothrow) A(true), new (std::nothrow) A(true));
        if (base::get_number_inst_of_base() != 2)
        {
            throw std::runtime_error("uniqueu_ptr_in_class: number instance of base is not expected");
        }
    }

    if (base::get_number_inst_of_base() != 0)
    {
        throw std::runtime_error("uniqueu_ptr_in_class: number instance of base is not expected");
    }

    test_class_uniqueu_ptr test1(new (std::nothrow) A(true), new (std::nothrow) A(true));
    test_class_uniqueu_ptr test2;
    test2 = std::move(test1);

    test2 = test_class_uniqueu_ptr(new (std::nothrow) A(true), new (std::nothrow) A(true));

    /* althoug we create 4 but we expect to have only two instance of base */
    if (base::get_number_inst_of_base() != 2)
    {
        throw std::runtime_error("uniqueu_ptr_in_class: number instance of base is not expected");
    }
}

void uniqueu_ptr_with_array()
{
    FUNC_TRACE();
    {
        std::unique_ptr<A[]> a_ptr(new (std::nothrow) A[10]);
        for (size_t i = 0; i < 10; i++)
        {
            a_ptr[i].set_trace(true); // it's OK to access unique_ptr of array as array
        }
    }

    if (base::get_number_inst_of_base() != 0)
    {
        throw std::runtime_error("uniqueu_ptr_in_class: number instance of base is not expected");
    }
}

void uniqueu_ptr_change_default_del()
{
    FUNC_TRACE();
    // with lamda
    auto ldel = [](base *a) {
        std::cout << "we're going to delete " << a << std::endl;
        delete a;
    };

    std::unique_ptr<base, decltype(ldel)> a_ptr(new (std::nothrow) A(true), ldel);

    // with class deleter
    struct a_deleter
    {
        void operator()(base *a)
        {
            std::cout << "we're going to delete " << a << std::endl;
            delete a;
        }
    };
    std::unique_ptr<base, a_deleter> a1_ptr(new (std::nothrow) A(true));
}

#include <dirent.h>

void uniqueu_ptr_auto_release_resource()
{
    FUNC_TRACE();

    auto closeDir = [](DIR *d) {
        std::cout << "auto close dir " << d << std::endl;
        closedir(d);
    };

    std::unique_ptr<DIR, decltype(closeDir)> pDir(::opendir("."), closeDir);
    // process each directory entry:
    struct dirent *dp;
    while ((dp = readdir(pDir.get())) != nullptr)
    {
        std::cout << "process " << dp->d_name << std::endl;
    }
}

int main(int argc __attribute__((unused)), char const *argv[] __attribute__((unused)))
{
    try
    {
        // raw_ptr();
        // uniqueu_ptr();
        // uniqueu_ptr_relese();
        // uniqueu_ptr_tranfer_ownership();
        // uniqueu_ptr_source_sink();
        // uniqueu_ptr_in_class();
        // uniqueu_ptr_with_array
        // uniqueu_ptr_change_default_del();
        uniqueu_ptr_auto_release_resource();
    }
    catch (std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}
