#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include "exceptions.hpp"
#include "algorithm.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::list
 * allocate random memory addresses for data and they are doubly-linked in a list.
 */
template<typename T>
class list {
protected:
    class node {
    public:
        T *data;
        node *prev;
        node *next;
        
        node() : data(nullptr), prev(nullptr), next(nullptr) {}
        node(const T &value) : data(new T(value)), prev(nullptr), next(nullptr) {}
        ~node() {
            if (data != nullptr) {
                delete data;
                data = nullptr;
            }
        }
    };

protected:
    node *head;
    node *tail;
    size_t count;

    /**
     * insert node cur before node pos
     * return the inserted node cur
     */
    node *insert(node *pos, node *cur) {
        cur->prev = pos->prev;
        cur->next = pos;
        pos->prev->next = cur;
        pos->prev = cur;
        return cur;
    }
    /**
     * remove node pos from list (no need to delete the node)
     * return the removed node pos
     */
    node *erase(node *pos) {
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;
        return pos;
    }

public:
    class const_iterator;
    class iterator {
    private:
        friend class list<T>;
        friend class const_iterator;
        node *ptr;
        const list<T> *container;

    public:
        iterator(node *p = nullptr, const list<T> *c = nullptr) : ptr(p), container(c) {}
        
        /**
         * iter++
         */
        iterator operator++(int) {
            if (ptr == nullptr || ptr == container->tail) {
                throw invalid_iterator();
            }
            iterator temp = *this;
            ptr = ptr->next;
            return temp;
        }
        /**
         * ++iter
         */
        iterator & operator++() {
            if (ptr == nullptr || ptr == container->tail) {
                throw invalid_iterator();
            }
            ptr = ptr->next;
            return *this;
        }
        /**
         * iter--
         */
        iterator operator--(int) {
            if (ptr == nullptr || ptr->prev == nullptr || ptr->prev == container->head) {
                throw invalid_iterator();
            }
            iterator temp = *this;
            ptr = ptr->prev;
            return temp;
        }
        /**
         * --iter
         */
        iterator & operator--() {
            if (ptr == nullptr || ptr->prev == nullptr || ptr->prev == container->head) {
                throw invalid_iterator();
            }
            ptr = ptr->prev;
            return *this;
        }
        /**
         * TODO *it
         * remember to throw if iterator is invalid
         */
        T & operator *() const {
            if (ptr == nullptr || ptr->data == nullptr) {
                throw invalid_iterator();
            }
            return *(ptr->data);
        }
        /**
         * TODO it->field
         * remember to throw if iterator is invalid
         */
        T * operator ->() const {
            if (ptr == nullptr || ptr->data == nullptr) {
                throw invalid_iterator();
            }
            return ptr->data;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory).
         */
        bool operator==(const iterator &rhs) const {
            return ptr == rhs.ptr;
        }
        bool operator==(const const_iterator &rhs) const {
            return ptr == rhs.ptr;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return ptr != rhs.ptr;
        }
        bool operator!=(const const_iterator &rhs) const {
            return ptr != rhs.ptr;
        }
    };
    /**
     * TODO
     * has same function as iterator, just for a const object.
     * should be able to construct from an iterator.
     */
    class const_iterator {
    private:
        friend class list<T>;
        node *ptr;
        const list<T> *container;

    public:
        const_iterator(node *p = nullptr, const list<T> *c = nullptr) : ptr(p), container(c) {}
        const_iterator(const iterator &other) : ptr(other.ptr), container(other.container) {}
        
        const_iterator operator++(int) {
            if (ptr == nullptr || ptr == container->tail) {
                throw invalid_iterator();
            }
            const_iterator temp = *this;
            ptr = ptr->next;
            return temp;
        }
        
        const_iterator & operator++() {
            if (ptr == nullptr || ptr == container->tail) {
                throw invalid_iterator();
            }
            ptr = ptr->next;
            return *this;
        }
        
        const_iterator operator--(int) {
            if (ptr == nullptr || ptr->prev == nullptr || ptr->prev == container->head) {
                throw invalid_iterator();
            }
            const_iterator temp = *this;
            ptr = ptr->prev;
            return temp;
        }
        
        const_iterator & operator--() {
            if (ptr == nullptr || ptr->prev == nullptr || ptr->prev == container->head) {
                throw invalid_iterator();
            }
            ptr = ptr->prev;
            return *this;
        }
        
        const T & operator *() const {
            if (ptr == nullptr || ptr->data == nullptr) {
                throw invalid_iterator();
            }
            return *(ptr->data);
        }
        
        const T * operator ->() const {
            if (ptr == nullptr || ptr->data == nullptr) {
                throw invalid_iterator();
            }
            return ptr->data;
        }
        
        bool operator==(const iterator &rhs) const {
            return ptr == rhs.ptr;
        }
        bool operator==(const const_iterator &rhs) const {
            return ptr == rhs.ptr;
        }
        
        bool operator!=(const iterator &rhs) const {
            return ptr != rhs.ptr;
        }
        bool operator!=(const const_iterator &rhs) const {
            return ptr != rhs.ptr;
        }
    };
    /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */
    list() : count(0) {
        head = new node();
        tail = new node();
        head->next = tail;
        tail->prev = head;
    }
    
    list(const list &other) : count(0) {
        head = new node();
        tail = new node();
        head->next = tail;
        tail->prev = head;
        for (node *p = other.head->next; p != other.tail; p = p->next) {
            push_back(*(p->data));
        }
    }
    
    /**
     * TODO Destructor
     */
    virtual ~list() {
        clear();
        delete head;
        delete tail;
    }
    
    /**
     * TODO Assignment operator
     */
    list &operator=(const list &other) {
        if (this == &other) return *this;
        clear();
        for (node *p = other.head->next; p != other.tail; p = p->next) {
            push_back(*(p->data));
        }
        return *this;
    }
    
    /**
     * access the first / last element
     * throw container_is_empty when the container is empty.
     */
    const T & front() const {
        if (empty()) throw container_is_empty();
        return *(head->next->data);
    }
    
    const T & back() const {
        if (empty()) throw container_is_empty();
        return *(tail->prev->data);
    }
    
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        return iterator(head->next, this);
    }
    
    const_iterator cbegin() const {
        return const_iterator(head->next, this);
    }
    
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        return iterator(tail, this);
    }
    
    const_iterator cend() const {
        return const_iterator(tail, this);
    }
    
    /**
     * checks whether the container is empty.
     */
    virtual bool empty() const {
        return count == 0;
    }
    
    /**
     * returns the number of elements
     */
    virtual size_t size() const {
        return count;
    }

    /**
     * clears the contents
     */
    virtual void clear() {
        node *p = head->next;
        while (p != tail) {
            node *temp = p;
            p = p->next;
            delete temp;
        }
        head->next = tail;
        tail->prev = head;
        count = 0;
    }
    
    /**
     * insert value before pos (pos may be the end() iterator)
     * return an iterator pointing to the inserted value
     * throw if the iterator is invalid
     */
    virtual iterator insert(iterator pos, const T &value) {
        if (pos.container != this) throw invalid_iterator();
        node *new_node = new node(value);
        insert(pos.ptr, new_node);
        count++;
        return iterator(new_node, this);
    }
    
    /**
     * remove the element at pos (the end() iterator is invalid)
     * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
     * throw if the container is empty, the iterator is invalid
     */
    virtual iterator erase(iterator pos) {
        if (empty()) throw container_is_empty();
        if (pos.container != this || pos.ptr == tail || pos.ptr == nullptr) throw invalid_iterator();
        node *next_node = pos.ptr->next;
        erase(pos.ptr);
        delete pos.ptr;
        count--;
        return iterator(next_node, this);
    }
    
    /**
     * adds an element to the end
     */
    void push_back(const T &value) {
        node *new_node = new node(value);
        insert(tail, new_node);
        count++;
    }
    
    /**
     * removes the last element
     * throw when the container is empty.
     */
    void pop_back() {
        if (empty()) throw container_is_empty();
        node *last = tail->prev;
        erase(last);
        delete last;
        count--;
    }
    
    /**
     * inserts an element to the beginning.
     */
    void push_front(const T &value) {
        node *new_node = new node(value);
        insert(head->next, new_node);
        count++;
    }
    
    /**
     * removes the first element.
     * throw when the container is empty.
     */
    void pop_front() {
        if (empty()) throw container_is_empty();
        node *first = head->next;
        erase(first);
        delete first;
        count--;
    }
    
    /**
     * sort the values in ascending order with operator< of T
     */
    void sort() {
        if (count <= 1) return;
        
        // Allocate raw memory using char array
        char *buffer = new char[sizeof(T) * count];
        T *arr = reinterpret_cast<T*>(buffer);
        size_t idx = 0;
        
        // Copy construct elements into array
        for (node *p = head->next; p != tail; p = p->next) {
            new (arr + idx) T(*(p->data));
            idx++;
        }
        
        // Sort the array
        std::function<bool(const T&, const T&)> cmp = [](const T &a, const T &b) { return a < b; };
        sjtu::sort(arr, arr + count, cmp);
        
        // Copy back to list
        idx = 0;
        for (node *p = head->next; p != tail; p = p->next) {
            *(p->data) = arr[idx];
            arr[idx].~T();  // Explicitly call destructor
            idx++;
        }
        
        // Free the raw memory
        delete[] buffer;
    }
    
    /**
     * merge two sorted lists into one (both in ascending order)
     * compare with operator< of T
     * container other becomes empty after the operation
     * for equivalent elements in the two lists, the elements from *this shall always precede the elements from other
     * the order of equivalent elements of *this and other does not change.
     * no elements are copied or moved
     */
    void merge(list &other) {
        if (this == &other) return;
        node *p1 = head->next;
        node *p2 = other.head->next;
        
        while (p1 != tail && p2 != other.tail) {
            if (*(p2->data) < *(p1->data)) {
                node *temp = p2->next;
                other.erase(p2);
                insert(p1, p2);
                p2 = temp;
            } else {
                p1 = p1->next;
            }
        }
        
        while (p2 != other.tail) {
            node *temp = p2->next;
            other.erase(p2);
            insert(tail, p2);
            p2 = temp;
        }
        
        count += other.count;
        other.count = 0;
    }
    
    /**
     * reverse the order of the elements
     * no elements are copied or moved
     */
    void reverse() {
        if (count <= 1) return;
        
        node *current = head->next;
        while (current != tail) {
            node *next_node = current->next;
            node *prev_node = current->prev;
            current->next = prev_node;
            current->prev = next_node;
            current = next_node;
        }
        
        node *first = head->next;
        node *last = tail->prev;
        
        head->next = last;
        last->prev = head;
        tail->prev = first;
        first->next = tail;
    }
    
    /**
     * remove all consecutive duplicate elements from the container
     * only the first element in each group of equal elements is left
     * use operator== of T to compare the elements.
     */
    void unique() {
        if (count <= 1) return;
        node *p = head->next;
        while (p != tail && p->next != tail) {
            if (*(p->data) == *(p->next->data)) {
                node *temp = p->next;
                erase(temp);
                delete temp;
                count--;
            } else {
                p = p->next;
            }
        }
    }
};

}

#endif //SJTU_LIST_HPP
