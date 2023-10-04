#pragma once

#include "slice.hpp"

/**
 * @brief Stack
 *
 * @tparam T type
 */
template <typename T> class Stack : public Slice<T> {
public:
  Stack() {}
  ~Stack() {}

public:
  void enqueue(T element) { this->append(element); }

  T dequeue() {
    size_t last_index = this->size() - 1;
    T last = this->last();
    this->remove(last_index);
    return last;
  }

  T &peek() { return this->last(); }

  T &first() { return (*this)[0]; }

  T &last() {
    size_t last_index = this->size() - 1;
    return (*this)[last_index];
  }
};