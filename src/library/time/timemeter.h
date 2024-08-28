#pragma once

#include <chrono>
#include <iostream>

#include <boost/static_assert.hpp>

namespace rdi {

/*!
 * \brief The TimeMeter class - класс для измерения времени
 */
template <class _Tp_time = std::chrono::milliseconds> // <-- по умолчанию шаблон в миллисекундах
class TimeMeter {
    BOOST_STATIC_ASSERT_MSG(std::chrono::__is_duration<_Tp_time>::value,
                            "This type is not a duration type");

    using time_point = decltype(std::chrono::high_resolution_clock::now());
    using time_unit = _Tp_time;
    using duration_type = typename time_point::duration;
    using time_type = typename time_point::rep;

public:
    TimeMeter() { start = std::chrono::high_resolution_clock::now(); }

    time_type currentTime() const
    {
        time_point finish = std::chrono::high_resolution_clock::now();
        duration_type duration = finish - start;
        return std::chrono::duration_cast<time_unit>(duration).count();
    }

    ~TimeMeter() {}

private:
    time_point start;
};
}

/* Examples */

/*
 * void sample1()
 * {
 *      rdi::TimeMeter<std::chrono::microseconds> timeMeter;
 *      vector<int> ans;
 *      for (int i = 0; i < 1000000; ++i) {
 *          ans.push_back(i);
 *      }
 * }
 * ----> В конце функции объект разрушится и выведет сообщение сколько времени понадобилось в
 * микросекундах на добавление 1000000 элементов в массив
 */

/*
 * void sample2()
 * {
 *      rdi::TimeMeter<std::chrono::microseconds> timeMeter;
 *      vector<int> ans;
 *      for (int i = 0; i < 1000000; ++i) {
 *          ans.push_back(i);
 *      }
 *      std::cout << timeMeter.currentTime() << std::endl; <----текущее время
 * }
 * ----> Тут копия 1 примера, за исключением вызова функции текущего времени на данный момент
 */
