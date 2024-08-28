#ifndef ONPTRCLASS_H
#define ONPTRCLASS_H

#include <memory>

class OnPtrClass {
public:
    // Пустое состояние, память не выделена
    OnPtrClass() = default;

    // Инициализация значением
    OnPtrClass(int value) : ptr_value(new int(value)) {}

    // Конструктор копирования
    OnPtrClass(const OnPtrClass &other) :
        ptr_value(other.ptr_value ? new int(*other.ptr_value) : nullptr)
    {
    }

    // Присваивание копированием
    OnPtrClass &operator=(const OnPtrClass &other)
    {
        if (this != &other) {
            other.ptr_value ? ptr_value.reset(new int(*other.ptr_value)) : ptr_value.reset();
        }
        return *this;
    }

    // Конструктор перемещения
    OnPtrClass(OnPtrClass &&other) noexcept : ptr_value(std::move(other.ptr_value)) {}

    // Присваивание перемещением
    OnPtrClass &operator=(OnPtrClass &&other) noexcept
    {
        if (this != &other) {
            ptr_value = std::move(other.ptr_value);
        }
        return *this;
    }

private:
    std::unique_ptr<int> ptr_value; // <--- Будем использовать умный указатель, они такие же
                                    // быстрые как и сырые указатели
};

#endif // ONPTRCLASS_H
