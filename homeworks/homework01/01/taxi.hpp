#pragma once

#include "passenger.hpp"
#include "slice.hpp"

#include <iostream>

class Taxi {
private:
  Slice<Passenger *> _passengers;
  int _weight_limit;

public:
  Taxi(int weight_limit = 0) : _weight_limit(weight_limit) {}
  Taxi(const Taxi &taxi)
      : _passengers(taxi._passengers), _weight_limit(taxi._weight_limit) {}

public:
  int getWeight() const {
    int weight = 0;
    for (size_t i = 0; i < _passengers.size(); ++i)
      weight += _passengers[i]->weight;

    return weight;
  }

  void addPassenger(Passenger *passenger) {
    this->_passengers.append(passenger);
  }

  void printPassengers(std::ostream &o) const {
    for (size_t i = 0; i < _passengers.size(); ++i) {
      o << _passengers[i]->weight;
      if (i != _passengers.size() - 1)
        o << ' ';
    }
  }
};