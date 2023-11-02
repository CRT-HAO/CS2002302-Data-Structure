#include "rbt.hpp"

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

using namespace std;

void getPostfixOnlyBlack(RedBlackTree::Node *root, std::string &postfix) {
  if (root == nullptr)
    return;

  getPostfixOnlyBlack(root->leftChild, postfix);
  getPostfixOnlyBlack(root->rightChild, postfix);
  if (!(root->red))
    // save value if root is black
    postfix += root->value;
}

void getPrefixOnlyRed(RedBlackTree::Node *root, std::string &prefix) {
  if (root == nullptr)
    return;

  if (root->red)
    // save value if root is red
    prefix += root->value;
  getPrefixOnlyRed(root->leftChild, prefix);
  getPrefixOnlyRed(root->rightChild, prefix);
}

int main() {
  RedBlackTree tree;

  string input;
  getline(cin, input);

  stringstream ss(input);

  for (string s; ss >> s;) {
    char c;
    if (s.length() == 1 && s[0] >= 'A' && s[0] <= 'z')
      c = s[0];
    else
      c = stoi(s);

    tree.insert(c);
  }

  // tree.printTree(cout);

  std::string postfixBlack;
  std::string prefixRed;
  getPostfixOnlyBlack(tree.root, postfixBlack);
  getPrefixOnlyRed(tree.root, prefixRed);

  for (const char &c : postfixBlack)
    cout << int(c);
  cout << '_';
  for (const char &c : prefixRed)
    cout << int(c);
  cout << '_' << tree.n_rotations;

  return 0;
}