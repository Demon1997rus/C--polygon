#include "api.h"

void process_ptr_func(func_t f)
{
    int i = 1;
    f(i);
}

void process_boost_func(boost::function<void(int)> func)
{
    int i = 1;
    func(i);
}
