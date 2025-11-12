#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;

    // big 5 add later if needed

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
        // what to do when list empty
        T temp = list.getHead()->data;
        list.removeHead();
        return temp;
    }

    // Access
    T peek() const override {
        // what to do when list is empty
        return list.gethead()->data;
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};