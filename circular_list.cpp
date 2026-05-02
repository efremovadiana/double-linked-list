#ifndef CIRCULAR_LIST_CPP
#define CIRCULAR_LIST_CPP

#include "circular_list.h"


template <typename T>
CircularList<T>::Node::Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

template <typename T>
CircularList<T>::Node::Node(T&& value) : data(std::move(value)), next(nullptr), prev(nullptr) {}


template <typename T>
CircularList<T>::CircularList() : current(nullptr), size(0) {}

template <typename T>
CircularList<T>::CircularList(const CircularList& other) : current(nullptr), size(0) {
    if (other.isEmpty()) return;

    Node* otherCurrent = other.current;
    do {
        insertAfter(otherCurrent->data);
        if (size > 1) next();
        otherCurrent = otherCurrent->next;
    } while (otherCurrent != other.current);
}

template <typename T>
CircularList<T>::CircularList(CircularList&& other) noexcept
    : current(other.current), size(other.size) {
    other.current = nullptr;
    other.size = 0;
}

template <typename T>
CircularList<T>::~CircularList() {
    clear();
}

template <typename T>
CircularList<T>& CircularList<T>::operator=(const CircularList& other) {
    if (this != &other) {
        clear();

        if (!other.isEmpty()) {
            Node* otherCurrent = other.current;
            do {
                insertAfter(otherCurrent->data);
                if (size > 1) next();
                otherCurrent = otherCurrent->next;
            } while (otherCurrent != other.current);
        }
    }
    return *this;
}

template <typename T>
CircularList<T>& CircularList<T>::operator=(CircularList&& other) noexcept {
    if (this != &other) {
        clear();
        current = other.current;
        size = other.size;
        other.current = nullptr;
        other.size = 0;
    }
    return *this;
}

template <typename T>
void CircularList<T>::insertBefore(const T& value) {
    Node* newNode = new Node(value);

    if (isEmpty()) {
        newNode->next = newNode;
        newNode->prev = newNode;
        current = newNode;
    } else {
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
    }
    size++;
}

template <typename T>
void CircularList<T>::insertBefore(T&& value) {
    Node* newNode = new Node(std::move(value));

    if (isEmpty()) {
        newNode->next = newNode;
        newNode->prev = newNode;
        current = newNode;
    } else {
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
    }
    size++;
}

template <typename T>
void CircularList<T>::insertAfter(const T& value) {
    Node* newNode = new Node(value);

    if (isEmpty()) {
        newNode->next = newNode;
        newNode->prev = newNode;
        current = newNode;
    } else {
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
    }
    size++;
}

template <typename T>
void CircularList<T>::insertAfter(T&& value) {
    Node* newNode = new Node(std::move(value));

    if (isEmpty()) {
        newNode->next = newNode;
        newNode->prev = newNode;
        current = newNode;
    } else {
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
    }
    size++;
}

template <typename T>
void CircularList<T>::removeCurrent() {
    if (isEmpty()) {
        throw std::runtime_error("Ошибка 1: список пуст");
    }

    if (size == 1) {
        delete current;
        current = nullptr;
        size = 0;
    } else {
        Node* toDelete = current;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;
        delete toDelete;
        size--;
    }
}


template <typename T>
void CircularList<T>::next() {
    if (isEmpty()) {
        throw std::runtime_error("Ошибка 2: список пуст");
    }
    current = current->next;
}

template <typename T>
void CircularList<T>::prev() {
    if (isEmpty()) {
        throw std::runtime_error("Ошибка 3: список пуст");
    }
    current = current->prev;
}


template <typename T>
T* CircularList<T>::getCurrent() {
    if (isEmpty()) {
        throw std::runtime_error("Ошибка 4: список пуст");
    }
    return &(current->data);
}

template <typename T>
const T* CircularList<T>::getCurrent() const {
    if (isEmpty()) {
        throw std::runtime_error("Ошибка 5: список пуст");
    }
    return &(current->data);
}


template <typename T>
bool CircularList<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
int CircularList<T>::getSize() const {
    return size;
}

template <typename T>
void CircularList<T>::clear() {
    while (!isEmpty()) {
        removeCurrent();
    }
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularList<T>& list) {
    if (list.isEmpty()) {
        os << "[]";
        return os;
    }

    os << "[";
    typename CircularList<T>::Node* current = list.current;
    do {
        os << current->data;
        current = current->next;
        if (current != list.current) {
            os << ", ";
        }
    } while (current != list.current);
    os << "]";

    return os;
}

#endif
