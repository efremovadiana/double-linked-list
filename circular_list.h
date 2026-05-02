#ifndef CIRCULAR_LIST_H_INCLUDED
#define CIRCULAR_LIST_H_INCLUDED

#include <iostream>
#include <stdexcept>

template <typename T>
class CircularList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value);
        Node(T&& value);
    };

    Node* current;
    int size;

public:

    CircularList();
    CircularList(const CircularList& other);
    CircularList(CircularList&& other) noexcept;
    ~CircularList();

    CircularList& operator=(const CircularList& other);
    CircularList& operator=(CircularList&& other) noexcept;


    void insertBefore(const T& value);
    void insertBefore(T&& value);
    void insertAfter(const T& value);
    void insertAfter(T&& value);


    void removeCurrent();


    void next();
    void prev();


    T* getCurrent();
    const T* getCurrent() const;


    bool isEmpty() const;
    int getSize() const;
    void clear();


    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const CircularList<U>& list);
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularList<T>& list);

#include "circular_list.cpp"

#endif // CIRCULAR_LIST_H_INCLUDED
