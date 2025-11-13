#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() {
        list =  LinkedList<T>();
    }

    // possible big 5 insertion
    LLQ(const LLQ& donor) { // copy constructor
        list = donor.list;
    }

    LLQ(LLQ&& donor) { // move constructor
        list = std::move(donor.list);
    }

    LLQ& operator=(const LLQ& donor) { // copy assignment
        if (this == &donor) return *this;
        list.clear();
        list = donor.list;
        return *this;
    }

    LLQ& operator=(LLQ&& donor) { // move assignment
        if (this == &donor) return *this;
        list.clear();
        list = std::move(donor.list);
        return *this;
    }

    ~LLQ() override {
        list.clear();
    }


    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override {
        if (list.getCount() == 0) throw std::runtime_error("List is empty");
        T temp = list.getHead()->data;
        list.removeHead();
        return temp;
    }

    // Access
    T peek() const override {
        if (list.getCount() == 0) throw std::runtime_error("List is empty");
        return list.getHead()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    void printForward() {
        list.printForward();
    }
    void printReverse() {
        list.printReverse();
    }

};