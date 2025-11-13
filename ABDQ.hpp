#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
        capacity_ = 1;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    explicit ABDQ(std::size_t capacity) {
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    ABDQ(const ABDQ& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }

    ABDQ(ABDQ&& other) noexcept {
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;

        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) return *this;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;

        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;
        return *this;
    }
    ~ABDQ() override {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ >= capacity_) {
            T* temp = new T[capacity_ * SCALE_FACTOR];
            for (size_t i = 0; i < size_; i++) {
                temp[i] = data_[i];
            }
            delete[] data_;
            data_ = temp;
            front_ = 0;
            back_ = size_;
            capacity_ *= SCALE_FACTOR;
        }
        front_ = (front_ + capacity_ - 1) % capacity_;
        data_[front_] = item;
        size_++;
    }
    void pushBack(const T& item) override {
        if (size_ >= capacity_) {
            T* temp = new T[capacity_ * SCALE_FACTOR];
            for (size_t i = 0; i < size_; i++) {
                temp[i] = data_[i];
            }
            delete[] data_;
            data_ = temp;
            front_ = 0;
            back_ = size_;
            capacity_ *= SCALE_FACTOR;
        }
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) throw std::runtime_error("Empty array");
        T temp = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        return temp;
    }
    T popBack() override {
        if (size_ == 0) throw std::runtime_error("Empty array");
        T temp = data_[back_];
        back_ = (back_ + capacity_ - 1) % capacity_;
        size_--;
        return temp;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) throw std::runtime_error("Empty array");
        return data_[front_];
    }
    const T& back() const override {
        if (size_ == 0) throw std::runtime_error("Empty array");
        return data_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

    void ensureCapacity() {
        T* tempArray = new T[capacity_ * SCALE_FACTOR];
        for (size_t i = 0; i < size_; i++) {
            tempArray[i] = data_[i];
        }
        capacity_ *= SCALE_FACTOR;
        delete[] data_;
        data_ = tempArray;
        front_ = 0;
        back_ = size_;
    }

    void shrinkIfNeeded() {
        if (size_*4 <= capacity_) {
            T* tempArray = new T[capacity_ / 2];
            for (size_t i = 0; i < size_; i++) {
                tempArray[i] = data_[i];
            }
            delete[] data_;
            data_ = tempArray;
            tempArray = nullptr;
            capacity_ = capacity_ / 2;
            front_ = 0;
            back_ = size_;
        }
    }

};
