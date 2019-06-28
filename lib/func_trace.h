#if !defined(__AUTO_TRACE_IN_OUT_FUNC__)
#define __AUTO_TRACE_IN_OUT_FUNC__

#include <iostream>
#include <string>

class func_trace final
{
private:
    std::string __function_name;
    std::ostream &__os;

public:
    explicit func_trace(const char *, std::ostream &os = std::clog);
    virtual ~func_trace();
};

#define FUNC_TRACE() func_trace ft_xxy(__FUNCTION__);
#define FUNC_TRACE_WITH_OS(OUTSTREAM) func_trace ft_xxy(__FUNCTION__, (OUTSTREAM));

#endif // __AUTO_TRACE_IN_OUT_FUNC__
