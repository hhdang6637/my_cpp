#include "func_trace.h"

func_trace::func_trace(const char *fname, std::ostream &os) : __function_name(fname), __os(os)
{
    __os << "func_trace: enter " << __function_name << std::endl;
}

func_trace::~func_trace()
{
    __os << "func_trace: leave " << __function_name << std::endl;
}
