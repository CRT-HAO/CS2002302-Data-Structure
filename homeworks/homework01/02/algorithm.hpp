#pragma once

#include "slice.hpp"

#include <string>

template <typename T>
Slice<T> subset(Slice<T> slice, size_t start, size_t end) {
  Slice<T> new_slice;
  for (size_t i = start; i < end; ++i) {
    new_slice.append(slice[i]);
  }
  return new_slice;
}

template <typename T> int find(Slice<T> slice, T item) {
  for (size_t i = 0; i < slice.size(); ++i) {
    if (slice[i] == item)
      return i;
  }

  return -1;
}

std::string reverse(const std::string &str) {
  std::string reverse(str.size(), '\0');

  for (size_t i = 0; i < str.size(); ++i)
    reverse[i] = str[str.size() - i];

  return reverse;
}