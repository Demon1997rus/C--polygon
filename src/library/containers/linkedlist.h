#pragma once

#include <memory>

namespace rdi {

namespace detail {
struct BaseNode {
    BaseNode *next = nullptr;
};

template <class T>
struct Node : BaseNode {
    template <class... Args>
    Node(Args &&... args) : data(std::forward<Args>(args)...)
    {
    }

    T data;
};
}

template <class T>
class ForwardList {
    // usings
public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using rvalue_reference = value_type &&;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using BaseNode = detail::BaseNode;
    using Node = detail::Node<value_type>;

    // iterators
public:
    struct iterator {
        BaseNode *m_node = nullptr;

        iterator() noexcept = default;

        iterator(BaseNode *node) noexcept : m_node(node) {}

        iterator &operator++() noexcept
        {
            m_node = m_node->next;
            return *this;
        }

        iterator operator++(int) noexcept
        {
            iterator temp = *this;
            m_node = m_node->next;
            return temp;
        }

        reference operator*() const noexcept { return static_cast<Node *>(m_node)->data; }

        pointer operator->() const noexcept { return &static_cast<Node *>(m_node)->data; }

        bool operator==(const iterator &rhs) const noexcept { return m_node == rhs.m_node; }

        bool operator!=(const iterator &rhs) const noexcept { return !(*this == rhs); }
    };

    struct const_iterator {
        const BaseNode *m_node = nullptr;

        const_iterator() noexcept = default;

        const_iterator(BaseNode *node) noexcept : m_node(node) {}

        const_iterator &operator++() noexcept
        {
            m_node = m_node->next;
            return *this;
        }

        const_iterator operator++(int) noexcept
        {
            const_iterator temp = *this;
            m_node = m_node->next;
            return temp;
        }

        const_reference operator*() const noexcept
        {
            return static_cast<const Node *>(m_node)->data;
        }

        const_pointer operator->() const noexcept
        {
            return &static_cast<const Node *>(m_node)->data;
        }

        bool operator==(const const_iterator &rhs) const noexcept
        {
            return m_node == rhs.m_node;
        }

        bool operator!=(const const_iterator &rhs) const noexcept { return !(*this == rhs); }
    };

    // constructors
public:
    ForwardList() noexcept = default;

    // public interface
public:
    iterator begin() noexcept { return iterator(m_base.next); }
    const_iterator begin() const noexcept { return const_iterator(m_base.next); }

    iterator end() noexcept { return iterator(nullptr); }
    const_iterator end() const noexcept { return const_iterator(nullptr); }

    template <class... Args>
    inline iterator emplace_after(iterator pos, Args &&... args)
    {
        std::unique_ptr<Node> node(new Node(std::forward<Args>(args)...));
        node->next = pos.m_node->next;
        pos.m_node->next = node.get();
        return node.release();
    }

    void push_front(const_reference value) { emplace_after(&m_base, value); }

    void push_front(rvalue_reference value) { emplace_after(&m_base, std::move(value)); }

    iterator insert_after(iterator pos, const_reference value)
    {
        return emplace_after(pos, value);
    }

    iterator insert_after(iterator pos, rvalue_reference value)
    {
        return emplace_after(pos, std::move(value));
    }

    iterator erase_after(iterator pos)
    {
        std::unique_ptr<Node> next(static_cast<Node *>(pos.m_node->next));
        pos.m_node->next = next->next;
        return pos.m_node->next;
    }

    void pop_front() { erase_after(&m_base); }

protected:
    BaseNode m_base;
};
} // namespace rdi
