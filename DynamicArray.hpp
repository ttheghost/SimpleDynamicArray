#pragma once
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T> class DynamicArray {
private:
  T *data_;
  size_t size_;
  size_t capacity_;

  void reserve_more() {
    size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    T *new_data = new T[new_capacity];
    for (size_t i = 0; i < size_; i++) {
      new_data[i] = std::move(data_[i]);
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }

public:
  DynamicArray() : data_(nullptr), size_(0), capacity_(0) {
    std::cout << "Default constructor\n";
  }

  ~DynamicArray() {
    std::cout << "Destructor (size=" << size_ << ")\n";
    delete[] data_;
  }

  DynamicArray(const DynamicArray &other)
      : data_(new T[other.capacity_]), size_(other.size_),
        capacity_(other.capacity_) {
    std::cout << "Copy constructor (copying " << size_ << " elements)\n";
    std::copy(other.data_, other.data_ + size_, data_);
  }

  DynamicArray &operator=(const DynamicArray &other) {
    std::cout << "Copy assignment (copying " << other.size_ << " elements)\n";
    if (this != &other) {
      T *new_data = new T[other.capacity_];
      std::copy(other.data_, other.data_ + other.size_, new_data);

      delete[] data_;
      data_ = new_data;
      size_ = other.size_;
      capacity_ = other.capacity_;
    }
    return *this;
  }

  DynamicArray(DynamicArray &&other) noexcept
      : data_(std::exchange(other.data_, nullptr)),
        size_(std::exchange(other.size_, 0)),
        capacity_(std::exchange(other.capacity_, 0)) {
    std::cout << "Move constructor (transferred " << size_ << " elements)\n";
  }

  DynamicArray &operator=(DynamicArray &&other) noexcept {
    std::cout << "Move assignment (transferred " << other.size_
              << " elements)\n";
    if (this != &other) {
      delete[] data_;

      data_ = std::exchange(other.data_, nullptr);
      size_ = std::exchange(other.size_, 0);
      capacity_ = std::exchange(other.capacity_, 0);
    }
    return *this;
  }

  void push_back(const T &value) {
    if (size_ == capacity_) {
      reserve_more();
    }
    data_[size_++] = value;
  }

  void push_back(T &&value) {
    if (size_ == capacity_) {
      reserve_more();
    }
    data_[size_++] = std::move(value);
  }

  T &operator[](size_t index) {
    if (index > size_) {
      throw std::out_of_range("Index out of range");
    }
    return data_[index];
  }

  const T &operator[](size_t index) const {
    if (index > size_) {
      throw std::out_of_range("Index out of range");
    }
    return data_[index];
  }

  size_t size() { return size_; }
  size_t capacity() { return capacity_; }
};
