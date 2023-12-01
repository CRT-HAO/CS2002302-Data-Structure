#include <iostream>
#include <vector>

using namespace std;

typedef struct {
  int priority;
  char character;
} Element;

int insertionSort(vector<Element> &elements, const string &compare_str) {
  int i, j;
  Element temp;
  int index = -1;

  for (i = 1; i < elements.size(); i++) {
    temp = elements[i];
    j = i - 1;

    while (j >= 0 && temp.priority < elements[j].priority) {
      elements[j + 1] = elements[j];
      j = j - 1;
    }
    elements[j + 1] = temp;

    if (index == -1) {
      bool equal = true;
      for (size_t k = 0; k < elements.size(); k++) {
        equal &= elements[k].character == compare_str[k];
      }

      if (equal)
        index = i;
    }
  }

  return index;
}

int selectionSort(vector<Element> &elements, const string &compare_str) {
  int i, j, min_idx;
  int index = -1;

  // One by one move boundary of
  // unsorted subarray
  for (i = 0; i < elements.size() - 1; i++) {

    // Find the minimum element in
    // unsorted array
    min_idx = i;
    for (j = i + 1; j < elements.size(); j++) {
      if (elements[j].priority < elements[min_idx].priority)
        min_idx = j;
    }

    // Swap the found minimum element
    // with the first element
    if (min_idx != i)
      swap(elements[min_idx], elements[i]);

    if (index == -1) {
      bool equal = true;
      for (size_t k = 0; k < elements.size(); k++) {
        equal &= elements[k].character == compare_str[k];
      }

      if (equal)
        index = i;
    }
  }

  return index;
}

int main() {
  string word;
  cin >> word;
  size_t length = word.length();

  vector<Element> elements(length);

  for (size_t i = 0; i < length; i++) {
    int priority;
    cin >> priority;
    elements[i].priority = priority;
  }

  for (size_t i = 0; i < length; i++) {
    char c;
    cin >> c;
    elements[i].character = c;
  }

  vector<Element> insertion = elements;
  int i = insertionSort(insertion, word);

  vector<Element> selection = elements;
  int s = selectionSort(selection, word);

  if (i != -1 && s != -1)
    cout << "Word found in insertion sort step " << (i + 1)
         << " and selection sort step " << (s + 1) << "." << endl;
  else {
    if (i != -1)
      cout << "Word found in insertion sort step " << (i + 1) << "." << endl;
    else if (s != -1)
      cout << "Word found in selection sort step " << (s + 1) << "." << endl;
    else
      cout << "Word not found." << endl;
  }

  for (const Element &e : selection)
    cout << e.character;
  cout << endl;

  return 0;
}