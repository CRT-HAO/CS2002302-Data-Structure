#include "passenger.hpp"
#include "queue.hpp"
#include "slice.hpp"
#include "stack.hpp"
#include "taxi.hpp"

#include <iostream>
#include <sstream>

using namespace std;

const int MAX_WEIGHT = 200;

int main() {
  string line;
  getline(cin, line);
  stringstream ss(line);

  // append input passengers
  Queue<Passenger *> passengers;
  for (int weight = 0; (ss >> weight);)
    passengers.enqueue(new Passenger(weight));

  Stack<Taxi *> lineup;
  // create first taxi, if there has more than one passenger
  if (passengers.size() != 0)
    lineup.enqueue(new Taxi(MAX_WEIGHT));

  // proccess the passengers get on a taxi
  for (; passengers.size() != 0;) {
    int taxi_current_weight = lineup.peek()->getWeight();

    if (passengers.size() != 0 &&
        (taxi_current_weight + passengers.peek()->weight) <= MAX_WEIGHT) {
      // get on the newest created taxi
      lineup.last()->addPassenger(passengers.dequeue());
    } else {
      // create a new taxi if the taxi is full
      lineup.enqueue(new Taxi(MAX_WEIGHT));
    }
  }

  // output result
  cout << lineup.size() << endl;
  for (; lineup.size() != 0;) {
    lineup.dequeue()->printPassengers(cout);
    if (lineup.size() != 0)
      cout << ' ';
  }

  return 0;
}