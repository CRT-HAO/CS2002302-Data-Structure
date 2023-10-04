#pragma once

#include "slice.hpp"

/**
 * @brief Queue
 *
 * @tparam T type
 */
template <typename T> class Queue : public Slice<T> {
public:
  Queue() {}
  ~Queue() {}

public:
  void enqueue(T element) { this->append(element); }

  T dequeue() {
    T first = this->first();
    this->remove(0);
    return first;
  }

  T &peek() { return this->first(); }
};