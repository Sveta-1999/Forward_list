#ifndef _FORWARD_LIST
#define _FORWARD_LIST

#include <iostream>
#include <iterator>
#include <initializer_list>

namespace SS_STL
{
    template <typename T>
    class forward_list {
    private:
        struct Node {
        public:
            Node() : m_value(T{}), m_next(nullptr){};
            Node(const T& value) : m_next{nullptr}, m_value{value} {}
        public:
            T m_value;
            Node* m_next;
        }; //struct Node
    public:
    class Iterator : public std::iterator<std::forward_iterator_tag, T> {
    /*private:
        using iterator_category = std::forward_iterator_tag;
        using defference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;*/
    public:
        Iterator() : m_iter{nullptr} {}
        Iterator(Node* Iter) : m_iter{Iter} {}
        Iterator(const Iterator& other) : m_iter{other.m_iter} {}
    public:
        Iterator& operator++()
        {
            m_iter = m_iter->m_next;
            return *this;
        }
        Iterator operator++( int )
        {
            Iterator tmp(*this);
            m_iter = m_iter->m_next;
            return tmp;
        }
        Iterator& operator=(const Iterator& rhs)
        {
            m_iter = rhs.m_iter;
            return *this;
        }
        Iterator& operator=(Node* rhs) 
        { 
            m_iter = rhs; 
            return *this; 
        }
        T& operator*() 
        { 
            return m_iter->m_value; 
        }
        T* operator->() 
        { 
            return &(m_iter->m_value);
        }
        bool operator==(const Iterator& rhs) 
        { 
            return (m_iter == rhs.m_iter);
        }
        bool operator!=(const Iterator& rhs) 
        { 
            return (m_iter != rhs.m_iter); 
        }
        Node* getIter() 
        { 
            return m_iter;
        }
    private:
        Node* m_iter;
    }; //class Iterator
    public:
        ~forward_list(){ clear();}
        forward_list() : m_head{nullptr}, m_begin{nullptr}, m_end{nullptr} {};
        forward_list(size_t count);
        forward_list(size_t count, const T& value);
        forward_list(std::initializer_list<T> init);
        forward_list(const forward_list& other);
        forward_list(forward_list&& other);

        forward_list& operator=(const forward_list& other);
        forward_list& operator=(forward_list&& other);

        friend std::ostream& operator<<(std::ostream& os, const forward_list<T>& ls)
        {
            forward_list<T>::Iterator iter;
            for(iter = ls.begin(); iter != ls.end(); ++iter)
            {
                os << *iter;
            }
            return os;
        }
    public:
        bool operator==(const forward_list<T>& rhs) const;
        bool operator!=(const forward_list<T>& rhs) const;
        bool operator<(const forward_list<T>& rhs) const;
        bool operator>(const forward_list<T>& rhs) const;
        bool operator<=(const forward_list<T>& rhs) const;
        bool operator>=(const forward_list<T>& rhs) const;
    public:
        bool empty();
        void clear();
        void push_front(const T& value);
        void pop_front();
        Iterator insert_after(Iterator pos, const T& value);
        Iterator insert_after(Iterator pos, size_t count, const T& value);
        Iterator erase_after(Iterator pos);
        Iterator erase_after(Iterator first, Iterator last);
        void swap(forward_list& other);
        void merge(forward_list& other);//??????????????????????????????????
        void splice_after(Iterator pos, forward_list& other); //???????????????????????????????
        void assign(size_t count, const T& value);
        void unique();
        void remove(const T& value);
        void revers();
        void sort();

    public:
        Iterator begin() const { return m_begin; }
        Iterator end() const { return m_end; }
    private:
        Node* m_head;
        Iterator m_begin;
        Iterator m_end;


    }; // forward_list
} //SS_STL

#endif //_FORWARD_LIST