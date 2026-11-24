#ifndef MYDEQUE_HPP
#define MYDEQUE_HPP

#include <iostream>
#include <cassert>
#include <cstddef>
#include <utility>
#include "basedeque.hpp"

template <typename T>
class MyDeque : public BaseDeque<T> {
    T* tab;
    std::size_t msize;
    std::size_t head;
    std::size_t tail;
public:
    MyDeque(std::size_t s = 10) : msize(s + 1), head(0), tail(0) {
        tab = new T[s + 1];
        assert(tab != nullptr);
    }

    ~MyDeque() {
        delete[] tab;
    }

    MyDeque(const MyDeque& other);
    MyDeque(MyDeque&& other);
    MyDeque& operator=(const MyDeque& other);
    MyDeque& operator=(MyDeque&& other);

    bool empty() const override { return head == tail; }
    bool full() const override { return (tail + 1) % msize == head; }
    std::size_t size() const override { return (tail + msize - head) % msize; }
    std::size_t max_size() const override { return msize - 1; }

    void push_front(const T& item) override;
    void push_front(T&& item) override;
    void push_back(const T& item) override;
    void push_back(T&& item) override;

    T& front() override {
        assert(!empty());
        return tab[head];
    }

    T& back() override {
        assert(!empty());
        return tab[(tail + msize - 1) % msize];
    }

    void pop_front() override;
    void pop_back() override;
    void clear() override;
    void display() const override;
    void display_reversed() const override;

    T& operator[](std::size_t pos) override;
    const T& operator[](std::size_t pos) const override;
    void erase(std::size_t pos) override;
    int index(const T& item) const override;
    void insert(std::size_t pos, const T& item) override;
    void insert(std::size_t pos, T&& item) override;
};

template <typename T>
MyDeque<T>::MyDeque(const MyDeque& other)
    : BaseDeque<T>(other), msize(other.msize), head(other.head), tail(other.tail) {
    tab = new T[msize];
    assert(tab != nullptr);
    for (std::size_t i = other.head; i != other.tail; i = (i + 1) % msize) {
        tab[i] = other.tab[i];
    }
}

template <typename T>
MyDeque<T>::MyDeque(MyDeque&& other)
    : BaseDeque<T>(std::move(other)), tab(other.tab), msize(other.msize), head(other.head), tail(other.tail) {
    other.tab = nullptr;
    other.msize = 1;
    other.head = 0;
    other.tail = 0;
}

template <typename T>
MyDeque<T>& MyDeque<T>::operator=(const MyDeque& other) {
    if (this != &other) {
        T* new_tab = new T[other.msize];
        assert(new_tab != nullptr);
        for (std::size_t i = other.head; i != other.tail; i = (i + 1) % other.msize) {
            new_tab[i] = other.tab[i];
        }
        delete[] tab;
        tab = new_tab;
        msize = other.msize;
        head = other.head;
        tail = other.tail;
    }
    return *this;
}

template <typename T>
MyDeque<T>& MyDeque<T>::operator=(MyDeque&& other) {
    if (this != &other) {
        delete[] tab;
        tab = other.tab;
        msize = other.msize;
        head = other.head;
        tail = other.tail;
        other.tab = nullptr;
        other.msize = 1;
        other.head = 0;
        other.tail = 0;
    }
    return *this;
}

template <typename T>
void MyDeque<T>::push_front(const T& item) {
    assert(!full());
    head = (head + msize - 1) % msize;
    tab[head] = item;
}

template <typename T>
void MyDeque<T>::push_front(T&& item) {
    assert(!full());
    head = (head + msize - 1) % msize;
    tab[head] = std::move(item);
}

template <typename T>
void MyDeque<T>::push_back(const T& item) {
    assert(!full());
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::push_back(T&& item) {
    assert(!full());
    tab[tail] = std::move(item);
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_front() {
    assert(!empty());
    head = (head + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_back() {
    assert(!empty());
    tail = (tail + msize - 1) % msize;
}

template <typename T>
void MyDeque<T>::clear() {
    head = 0;
    tail = 0;
}

template <typename T>
void MyDeque<T>::display() const {
    for (std::size_t i = head; i != tail; i = (i + 1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void MyDeque<T>::display_reversed() const {
    std::size_t i = tail;
    while (i != head) {
        i = (i + msize - 1) % msize;
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
T& MyDeque<T>::operator[](std::size_t pos) {
    assert(pos < size());
    return tab[(head + pos) % msize];
}

template <typename T>
const T& MyDeque<T>::operator[](std::size_t pos) const {
    assert(pos < size());
    return tab[(head + pos) % msize];
}

template <typename T>
void MyDeque<T>::erase(std::size_t pos) {
    std::size_t n = size();
    assert(pos < n);
    for (std::size_t i = pos; i + 1 < n; ++i) {
        tab[(head + i) % msize] = std::move(tab[(head + i + 1) % msize]);
    }
    tail = (tail + msize - 1) % msize;
}

template <typename T>
int MyDeque<T>::index(const T& item) const {
    std::size_t n = size();
    for (std::size_t i = 0; i < n; ++i) {
        if (tab[(head + i) % msize] == item) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

template <typename T>
void MyDeque<T>::insert(std::size_t pos, const T& item) {
    std::size_t n = size();
    assert(!full());
    assert(pos <= n);
    if (pos == 0) {
        push_front(item);
        return;
    }
    if (pos == n) {
        push_back(item);
        return;
    }
    for (std::size_t i = n; i > pos; --i) {
        tab[(head + i) % msize] = std::move(tab[(head + i - 1) % msize]);
    }
    tab[(head + pos) % msize] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::insert(std::size_t pos, T&& item) {
    std::size_t n = size();
    assert(!full());
    assert(pos <= n);
    if (pos == 0) {
        push_front(std::move(item));
        return;
    }
    if (pos == n) {
        push_back(std::move(item));
        return;
    }
    for (std::size_t i = n; i > pos; --i) {
        tab[(head + i) % msize] = std::move(tab[(head + i - 1) % msize]);
    }
    tab[(head + pos) % msize] = std::move(item);
    tail = (tail + 1) % msize;
}

#endif
