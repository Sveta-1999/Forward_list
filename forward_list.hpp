#include "forward_list.h"

template <typename T>
SS_STL::forward_list<T>::forward_list(size_t count)
{
    m_head = new Node();
    Node * current = m_head;
    for(int i = 0; i < count - 1; ++i)
    {
        current -> m_next = new Node();
        current = current -> m_next;
    }
    m_begin = m_head;
    current -> m_next = new Node();
    m_end = current -> m_next;
}

template <typename T>
SS_STL::forward_list<T>::forward_list(size_t count, const T& value)
{
    m_head = new Node(value);
    Node * current = m_head;
    for(int i = 0; i < count - 1; ++i)
    {
        current -> m_next = new Node(value);
        current = current -> m_next; 
    }
    m_begin = m_head;
    current -> m_next = new Node();
    m_end = current -> m_next;
}

template <typename T>
SS_STL::forward_list<T>::forward_list(std::initializer_list<T> init)
{
    auto ls = init.begin();
    m_head = new Node(*ls);
    ++ls;
    Node * current = m_head;
    for(int i = 1; i < init.size(); ++i, ++ls)
    {
        current -> m_next = new Node(*ls);
        current = current -> m_next;
    }
    m_begin = m_head;
    current -> m_next = new Node();
    m_end = current -> m_next; 
}

template <typename T>
SS_STL::forward_list<T>::forward_list(const forward_list& other)
{
    Node* current = other.m_head;
    m_head = new Node(current->m_value);
    Node* current1 = m_head;
    while(current->m_next != nullptr)
    {
        current = current -> m_next;
        current1 -> m_next = new Node(current -> m_value);
        current1 = current1 -> m_next;
    }
    m_begin = m_head;
    m_end = current1;
}

template <typename T>
SS_STL::forward_list<T>::forward_list(forward_list&& other)
{
    m_head = other.m_head;
    m_begin = other.m_begin;
    m_end = other.m_end;
    other.m_head = nullptr;
    other.m_begin = nullptr;
    other.m_end = nullptr;
}

template <typename T>
SS_STL::forward_list<T>& SS_STL::forward_list<T>::operator=(const forward_list& other)
{
    if(this == &other)
    {
        return *this;
    }
    clear();
    m_head = new Node(other.m_head -> m_value);
    Node* current = other.m_head;
    Node* current1 = m_head;
    while(current -> m_next != nullptr)
    {
        current = current -> m_next;
        current1 -> m_next = new Node(current -> m_value);
        current1 = current1 -> m_next;
    }
    m_begin = m_head;
    m_end = current1;
    return *this;
}

template<typename T>
SS_STL::forward_list<T>& SS_STL::forward_list<T>::operator=(forward_list&& other)
{
    m_head = other.m_head;
    m_begin = other.m_begin;
    m_end = other.m_end;
    other.m_head = nullptr;
    other.m_begin = nullptr;
    other.m_end = nullptr;
    return *this;
}

template <typename T>
bool SS_STL::forward_list<T>::operator<(const forward_list& rhs ) const
{
    return std::lexicographical_compare(m_begin, m_end, rhs.m_begin, rhs.m_end);
}

template <typename T>
bool SS_STL::forward_list<T>::operator>(const forward_list& rhs ) const
{
    return (rhs < *this);
}

template <typename T>
bool SS_STL::forward_list<T>::operator>=(const forward_list& rhs ) const
{
    return !(*this < rhs);
}

template <typename T>
bool SS_STL::forward_list<T>::operator<=(const forward_list& rhs ) const
{
    return !(*this < rhs);
}   

template <typename T>
bool SS_STL::forward_list<T>::operator==(const forward_list& rhs ) const
{
    auto iter = m_begin;
    auto iter1 = rhs.begin();
    while(iter != m_end)
    {
        if(*iter != *iter1)
        {
            return false;
        }
        ++iter;
        ++iter1;
    }
    return true;
}

template <typename T>
bool SS_STL::forward_list<T>::operator!=(const forward_list& rhs ) const
{
    return !(rhs == *this);
}

template <typename T>
bool SS_STL::forward_list<T>::empty()
{
    return (m_head == nullptr);
}

template <typename T>
void SS_STL::forward_list<T>::clear()
{
    if(m_head != nullptr)
    {
        Node* current = m_head -> m_next;
        delete m_head;
        m_head = nullptr;
        while(current -> m_next != nullptr)
        {
            m_head = current;
            current = current -> m_next;
            delete m_head;
            m_head =  nullptr;
        }
    }
    m_begin = nullptr;
    m_end = nullptr;
}

template <typename T>
void SS_STL::forward_list<T>::push_front(const T& value)
{
    Node* current = new Node(value);
    current -> m_next = m_head;
    m_head = current;
    m_begin = m_head;
}

template <typename T>
void SS_STL::forward_list<T>::pop_front()
{
    Node* current = m_head;
    m_head = m_head -> m_next;
    m_begin = m_head;
    current -> m_value = {};
    delete current;
}

template <typename T>
typename SS_STL::forward_list<T>::Iterator SS_STL::forward_list<T>::insert_after(Iterator pos, const T& value)
{
    Node* current = pos.getIter() -> m_next;
    pos.getIter() -> m_next = new Node(value);
    pos.getIter() -> m_next -> m_next = current;
    return Iterator(current -> m_next);
}

template <typename T>
typename SS_STL::forward_list<T>::Iterator SS_STL::forward_list<T>::insert_after(Iterator pos, size_t count, const T& value)
{
    Node* current = new Node(value);
    Node* current1 = current;
    --count;
    while(count)
    {
        current -> m_next = new Node(value);
        current = current -> m_next;
        --count;
    }
    Node* tmp = pos.getIter() -> m_next;
    pos.getIter() -> m_next = current1;
    current -> m_next = tmp;
    return Iterator(current1);
}

template <typename T>
typename SS_STL::forward_list<T>::Iterator SS_STL::forward_list<T>::erase_after(Iterator pos)
{
    Node* current = pos.getIter();
    Node* current1 = pos.getIter() -> m_next -> m_next;
    Node* tmp = pos.getIter() -> m_next;
    current -> m_next = current1;
    delete tmp;
    tmp = nullptr;
    return Iterator(current);
}

template <typename T>
typename SS_STL::forward_list<T>::Iterator SS_STL::forward_list<T>::erase_after(Iterator first, Iterator last)
{
    Node* current = first.getIter();
    Node* current1 = last.getIter();
    Node* tmp = current -> m_next;
    while(tmp != current1)
    {
        Node* tmp1 = tmp;
        tmp = tmp -> m_next;
        delete tmp1;
        tmp1 = nullptr;
    }
    current -> m_next = current1;
    return Iterator(current1);
}

template <typename T>
void SS_STL::forward_list<T>::assign(size_t count, const T& value)
{
    clear();
    m_head = new Node(value);
    Node* current = m_head;
    for(int i = 0; i < count - 1; ++i)
    {
        current -> m_next = new Node(value);
        current = current -> m_next;
    }
    m_begin = m_head;
    current -> m_next = new Node();
    m_end = current -> m_next;
}

template <typename T>
void SS_STL::forward_list<T>::swap(forward_list& other)
{
    Node* tmp1 = m_head;
    m_head = other.m_head;
    other.m_head = tmp1;
    Iterator iter = m_begin;
    m_begin = other.m_begin;
    other.m_begin = iter;
    iter = m_end;
    m_end = other.m_end;
    other.m_end = iter;
}

template <typename T>
void SS_STL::forward_list<T>::sort()
{
    Node* key = nullptr;
    Iterator j;
    Iterator tmp = ++m_begin;
    for(Iterator i = tmp; i != m_end; ++i)
    {
        key = m_head -> m_next;
        j = m_head;

    }
}

template <typename T>
void SS_STL::forward_list<T>::merge(forward_list& other)
{
    if (other.m_head == nullptr) 
    {
        return;
    }
    if (m_head == nullptr) 
    {
        m_head = other.m_head;
    } 
    else 
    {
        Node* new_ptr = m_head;
        Node* ptr = other.m_head;
        Node* prev = m_head;
        while (new_ptr != nullptr && ptr != nullptr) 
        {
            if (new_ptr->m_value > ptr->m_value) 
            {
                other.m_head = other.m_head->m_next;
                if (new_ptr == m_head) 
                {
                    m_head->m_next = prev;
                    ptr = m_head;
                    new_ptr = m_head;
                } 
                else
                {
                    ptr->m_next = new_ptr;
                    prev->m_next = ptr;
                    prev = prev -> m_next;
                }
                ptr = other.m_head;
            } 
            else
            {
                prev = new_ptr;
                new_ptr = new_ptr->m_next;
            }
        }
        if (new_ptr == nullptr && ptr != nullptr) 
        {
            std::cout << "prev->m_value";
            prev -> m_next = ptr;
            ptr = nullptr; 
        }
        prev = nullptr;
        new_ptr = nullptr;
    }
    other.m_head = nullptr;
    /*Node* current = m_head;
    Node* current1 = other.m_head;
    Node* tmp = current -> m_next;
    Node* tmp1 = current1 -> m_next;
    //std::cout << "current = " << current << "  current1 = " << current1 << "  tmp = " << tmp << "  tmp1 = " << tmp1;
    while(current1 -> m_next)
    {
        if((current -> m_value < current1 -> m_value) &&(current -> m_next -> m_value > current1 -> m_value))
        {
            // other.m_head = other.m_head -> m_next;
            // current -> m_next = current1;
            // current = current -> m_next;
            // tmp = current -> m_next;
            // current1 = other.m_head;
            // tmp1 = current1 -> m_next;
            current -> m_next = current1;
            current1 -> m_next = tmp;
            current = current -> m_next;
            current1 = tmp1;
            tmp1 = current1 -> m_next;
        }
            // else if(current -> m_next -> m_value <= current1 -> m_value)
            // {
            //     current -> m_next = current1;
            //     current1 -> m_next = tmp;
            //     current = current1;
            //     current -> m_next = tmp;
            //     current1 = tmp1;
            //     tmp1 = current1 -> m_next;
            // }
        }
        else if((current -> m_value < current1 -> m_value) &&(current -> m_next -> m_value < current1 -> m_value))
        {
            current1 -> m_next = current;
            current1 = tmp1;
            tmp1 = current1 -> m_next;
        }
        else if((current -> m_value > current1 -> m_value))
        {

        }
        else
        {

        }
        //current -> m_next = current1;
        
    }
    // current1 = nullptr;
    // current = nullptr;
    // tmp = nullptr;
    // other.m_head = nullptr;
    */
}

/*template <typename T>
void SS_STL::forward_list<T>::splice_after(Iterator pos, forward_list& other)
{
    
}*/

/*template <typename T>
void SS_STL::forward_list<T>::unique()
{
    for(Iterator i = m_begin; i != m_end; ++i )
    {
        Iterator iter = i;
        Iterator decIter = iter;
        ++iter;
        for(; iter != m_end; ++iter)
        {
            if(*i == *iter )
            {
                
            }

        }
    }
}*/

template <typename T>
void SS_STL::forward_list<T>::remove(const T& value)
{
    while(*m_begin == value)
    {
        pop_front();
    }
    Iterator tmp = m_begin;
    Iterator tmp1;
    while (tmp != m_end)
    {
        if(*tmp == value)
        {
            ++tmp;
            erase_after(tmp1);
        }
        else
        {
            tmp1 = tmp;
            ++tmp;
        }
    }
}

template <typename T>
void SS_STL::forward_list<T>::revers()
{
    Iterator iter;
    for(Iterator i = m_begin; i != m_end; ++i)
    {
        iter = i;
        ++iter;
        for(; iter != m_end; ++iter)
        {
            std::swap(*i, *iter);
        }
    }
}

