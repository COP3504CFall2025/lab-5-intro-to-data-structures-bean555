#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{
    size_t front_;
    size_t back_;
    size_t capacity_;
    size_t curr_size_;
    T* array_;

    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() {
        capacity_ = 1;
        curr_size_ = 0;
        front_ = 0;
        back_ = 0;
        array_ = new T[capacity_];
    }
    explicit ABQ(const size_t capacity) {
        capacity_ = capacity;
        curr_size_ = 0;
        front_ = 0;
        back_ = 0;
        array_ = new T[capacity_];
    }
    ABQ(const ABQ& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; i++) {
            array_[i] = other.array_[(other.front_ + i) % other.capacity_];
        }
        front_ = 0;
        back_ = curr_size_;
    }
    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) return *this;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        delete[] array_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; i++) {
            array_[i] = rhs.array_[(rhs.front_ + i) % rhs.capacity_];
        }
        front_ = 0;
        back_ = curr_size_;
        return *this;
    }
    ABQ(ABQ&& other) noexcept {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        front_ = other.front_;
        back_ = other.back_;
        array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.array_ = nullptr;
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) return *this;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        front_ = rhs.front_;
        back_ = rhs.back_;
        delete[] array_;
        array_ = rhs.array_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.front_ = 0;
        rhs.back_ = 0;
        rhs.array_ = nullptr;
    }
    ~ABQ() noexcept override {
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;}
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}
    [[nodiscard]] T* getData() const noexcept {return array_;}

    // Insertion
    void enqueue(const T& data) override {
        if (curr_size_ >= capacity_) {
            T* tempArray = new T[capacity_ * scale_factor_];
            for (size_t i = 0; i < capacity_; i++) {
                tempArray[i] = array_[(front_+i)% capacity_];
            }
            capacity_ *= scale_factor_;
            delete[] array_;
            array_ = tempArray;
            tempArray = nullptr;
            front_ = 0;
            back_ = curr_size_;
        }
        array_[back_] = data;
        back_ = (back_ + 1) % capacity_;
        curr_size_++;
    }

    // Access
    T peek() const override {
        if (curr_size_ == 0) throw std::runtime_error("Queue is empty");
        return array_[front_];
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ == 0) throw std::runtime_error("Queue is empty");
        T temp = array_[front_];
        front_ = (front_ + 1) % capacity_;
        curr_size_--;

        if (curr_size_ * 4 >= capacity_) {
            T* tempArray = new T[capacity_ / scale_factor_];
            for (size_t i = 0; i < capacity_ / scale_factor_; i++) {
                tempArray[i] = array_[(front_ + i) % capacity_];
            }
            capacity_ = capacity_ / scale_factor_;
            delete[] array_;
            array_ = tempArray;
            tempArray = nullptr;
            front_ = 0;
            back_ = curr_size_;
        }
        return temp;
    }

};
