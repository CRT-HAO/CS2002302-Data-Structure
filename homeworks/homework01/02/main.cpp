#include "binary_tree.hpp"
#include "queue.hpp"

#include <iostream>
#include <string>

using namespace std;

int main() {
  string infix, second_fix_type, second_fix, output_type;
  cin >> infix >> second_fix_type >> second_fix >> output_type;

  // check is the second fix is post order
  bool post_order = false;
  if (second_fix_type == "prefix")
    post_order = false;
  else if (second_fix_type == "postfix")
    post_order = true;
  else {
    cout << "Error: invalid second fix type" << endl;
    return 1;
  }

  // build tree
  BinaryTreeNode *tree = BinaryTree::build(infix, second_fix, post_order);

  // convert tree to output fix
  string output_fix;
  if (output_type == "prefix")
    output_fix = BinaryTree::toPrefix(tree);
  else if (output_type == "postfix")
    output_fix = BinaryTree::toPostfix(tree);
  else {
    cout << "Error: invalid output fix type" << endl;
    return 1;
  }

  // convert to level order
  string level_order = BinaryTree::toLevelOrder(tree);

  // output
  cout << output_fix << endl << level_order << endl;

  return 0;
}