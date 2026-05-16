#ifndef LIST_INTERFACE_H_INCLUDED
#define LIST_INTERFACE_H_INCLUDED

#include "circular_list.h"
#include <vector>
#include <memory>
#include <stdexcept>

template <typename T>
class NListsInterface {
private:
    std::vector<CircularList<T>> lists;
    size_t currentListIndex;

public:
    NListsInterface() : currentListIndex(0) {}

    void addList() {
        lists.emplace_back();
    }

    void addList(const CircularList<T>& list) {
        lists.push_back(list);
    }

    void addList(CircularList<T>&& list) {
        lists.push_back(std::move(list));
    }

    void removeList(size_t index) {
        if (index >= lists.size()) {
            throw std::runtime_error("Ошибка: индекс списка вне диапазона");
        }
        lists.erase(lists.begin() + index);
        if (currentListIndex >= lists.size() && !lists.empty()) {
            currentListIndex = lists.size() - 1;
        }
    }

    void switchToList(size_t index) {
        if (index >= lists.size()) {
            throw std::runtime_error("Ошибка: индекс списка вне диапазона");
        }
        currentListIndex = index;
    }

    CircularList<T>& getCurrentList() {
        if (lists.empty()) {
            throw std::runtime_error("Ошибка: нет ни одного списка");
        }
        return lists[currentListIndex];
    }

    const CircularList<T>& getCurrentList() const {
        if (lists.empty()) {
            throw std::runtime_error("Ошибка: нет ни одного списка");
        }
        return lists[currentListIndex];
    }

    CircularList<T>& getList(size_t index) {
        if (index >= lists.size()) {
            throw std::runtime_error("Ошибка: индекс списка вне диапазона");
        }
        return lists[index];
    }

    const CircularList<T>& getList(size_t index) const {
        if (index >= lists.size()) {
            throw std::runtime_error("Ошибка: индекс списка вне диапазона");
        }
        return lists[index];
    }

    size_t getListsCount() const {
        return lists.size();
    }

    bool isEmpty() const {
        return lists.empty();
    }

    void clearAll() {
        lists.clear();
        currentListIndex = 0;
    }

    void insertBeforeCurrent(const T& value) {
        getCurrentList().insertBefore(value);
    }

    void insertAfterCurrent(const T& value) {
        getCurrentList().insertAfter(value);
    }

    void removeCurrent() {
        getCurrentList().removeCurrent();
    }

    void next() {
        getCurrentList().next();
    }

    void prev() {
        getCurrentList().prev();
    }

    T* getCurrent() {
        return getCurrentList().getCurrent();
    }

    const T* getCurrent() const {
        return getCurrentList().getCurrent();
    }

    void printAllLists(std::ostream& os = std::cout) const {
        for (size_t i = 0; i < lists.size(); ++i) {
            os << "Список " << i << ": " << lists[i] << std::endl;
        }
    }

    void copyFromToList(size_t sourceIndex, size_t destIndex) {
        if (sourceIndex >= lists.size() || destIndex >= lists.size()) {
            throw std::runtime_error("Ошибка: индекс списка вне диапазона");
        }
        lists[destIndex] = lists[sourceIndex];
    }

    void moveFromToList(size_t sourceIndex, size_t destIndex) {
        if (sourceIndex >= lists.size() || destIndex >= lists.size()) {
            throw std::runtime_error("Ошибка: индекс списка вне диапазона");
        }
        lists[destIndex] = std::move(lists[sourceIndex]);
    }

    size_t getCurrentListIndex() const {
    return currentListIndex;
}
};

#endif // LIST_INTERFACE_H_INCLUDED
