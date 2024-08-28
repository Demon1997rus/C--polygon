#pragma once

#include <memory>

/*!
 * \brief The OnlySharedPointer class - пример класса, который можно создать только через
 * shared_ptr
 */
class OnlySharedPointer : public std::enable_shared_from_this<OnlySharedPointer> {
    struct Private {
    };

public:
    OnlySharedPointer(Private) {}

    static std::shared_ptr<OnlySharedPointer> create()
    {
        return std::make_shared<OnlySharedPointer>(Private());
    }

    std::shared_ptr<OnlySharedPointer> getPtr() { return shared_from_this(); }
};
