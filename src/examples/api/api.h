#pragma once

#include <boost/function.hpp>

typedef void (*func_t)(int);

void process_ptr_func(func_t f);

void process_boost_func(boost::function<void(int)> func);
