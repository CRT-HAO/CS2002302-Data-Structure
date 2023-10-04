#pragma once

#include <stdexcept>

/**
 * @brief Slice
 * Dynamic array data structure, inspired by go's slice
 *
 * @tparam T type
 */
template <typename T> class Slice {
private:
  T *data;
  std::size_t length;
  std::size_t capacity;

public:
  Slice() : data(nullptr), length(0), capacity(0) {}

  Slice(std::size_t initial_capacity)
      : data(new T[initial_capacity]), length(0), capacity(initial_capacity) {}

  virtual ~Slice() { delete[] data; }

  std::size_t size() const { return length; }

  std::size_t cap() const { return capacity; }

  void append(const T &item) {
    if (length >= capacity) {
      // expand capacity 2 times when the capacity too small
      std::size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
      T *new_data = new T[new_capacity];

      // re-assign the datas
      for (std::size_t i = 0; i < length; ++i) {
        new_data[i] = data[i];
      }

      // release old datas and assign new datas
      delete[] data;
      data = new_data;
      capacity = new_capacity;
    }

    // set the append data
    data[length++] = item;
  }

  void remove(std::size_t index) {
    if (index >= length) {
      throw std::out_of_range("Index out of range");
    }

    T *new_data = new T[capacity];
    for (std::size_t i = 0; i < length - 1; ++i) {
      if (i >= index)
        new_data[i] = data[i + 1];
      else
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;

    length--;
  }

  T &operator[](std::size_t index) {
    if (index >= length) {
      throw std::out_of_range("Index out of range");
    }
    return data[index];
  }

  const T &operator[](std::size_t index) const {
    if (index >= length) {
      throw std::out_of_range("Index out of range");
    }
    return data[index];
  }
};