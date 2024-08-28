#pragma once

#include <string>

#include <boost/move/move.hpp>
#include <boost/swap.hpp>

namespace rdi { namespace examples {

namespace others {
class Characteristics {
};
}
/*! -----------------------------Эмуляция перемещения----------------------------- !*/
/*!
 * \brief The ExampleBoostMove class - использование эмуляции перемещения C++11.
 * Одна из главных особенностей стандарта C++11 – это rvalue-ссылки, та же
 * move-семантика. Эта особенность позволяет нам изменять временные	объекты,
 * «крадя» у них ресурсы. Как вы можете	догадаться,	стандарт C++03 не имеет
 * rvalue-ссылок, но, используя	библиотеку Boost.Move, можно написать переносимый код,
 * который эмулирует их. Ниже пример класс.
 */
class ExampleBoostMove {
public:
    std::string name;
    std::string second_name;
    others::Characteristics character;

private:
    BOOST_COPYABLE_AND_MOVABLE(ExampleBoostMove)

public:
    ExampleBoostMove() = default;

    ExampleBoostMove(const ExampleBoostMove &other) :
        name(other.name), second_name(other.second_name), character(other.character)
    {
    }

    ExampleBoostMove(BOOST_RV_REF(ExampleBoostMove) other) { this->swap(other); }

    ExampleBoostMove &operator=(BOOST_COPY_ASSIGN_REF(ExampleBoostMove) other)
    {
        ExampleBoostMove temp(other);
        this->swap(temp);
        return *this;
    }

    ExampleBoostMove &operator=(BOOST_RV_REF(ExampleBoostMove) other) noexcept
    {
        ExampleBoostMove temp(boost::move(other));
        this->swap(temp);
        return *this;
    }

    void swap(ExampleBoostMove &rhs) noexcept
    {
        this->name.swap(rhs.name);
        this->second_name.swap(rhs.second_name);
        boost::swap(this->character, rhs.character);
    }
};
}}
