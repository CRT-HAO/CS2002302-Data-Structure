#pragma once

#include "algorithm.hpp"
#include "queue.hpp"
#include <cstddef>
#include <iostream>
#include <string>

class BinaryTreeNode {
public:
  BinaryTreeNode *left_child;
  char symbol;
  std::string temp;
  BinaryTreeNode *right_child;

public:
  BinaryTreeNode(char symbol = '?')
      : symbol(symbol), left_child(nullptr), right_child(nullptr){};
  ~BinaryTreeNode() {
    delete this->left_child;
    delete this->right_child;
  };
};

class BinaryTree {
public:
  static BinaryTreeNode *build(std::string in_order, std::string second_order,
                               bool post_order) {
    BinaryTreeNode *tree = new BinaryTreeNode;
    tree->temp = in_order;

    traversal(tree, second_order, post_order);

    return tree;
  };

  static void traversal(BinaryTreeNode *tree, std::string &second_order,
                        bool post_order) {
    if (!tree)
      return;

    if (second_order.empty())
      return;

    int index = tree->temp.find(
        post_order ? second_order[second_order.length() - 1] : second_order[0]);
    second_order = post_order
                       ? second_order.substr(0, second_order.length() - 1)
                       : second_order.substr(1);
    tree->symbol = tree->temp[index];

    if (tree->temp.length() == 1)
      return;

    if (index != 0) {
      tree->left_child = new BinaryTreeNode;
      tree->left_child->temp = tree->temp.substr(0, index);
    }

    if (tree->temp.length() != index + 1) {
      tree->right_child = new BinaryTreeNode;
      tree->right_child->temp = tree->temp.substr(index + 1);
    }

    // std::cout << "=======================" << std::endl;
    // std::cout << " - symbol: " << tree->symbol << std::endl;
    // std::cout << " - left_temp: " << tree->left_child->temp << std::endl;
    // std::cout << " - right_temp: " << tree->right_child->temp << std::endl;

    if (post_order) {
      traversal(tree->right_child, second_order, post_order);
      traversal(tree->left_child, second_order, post_order);
    } else {
      traversal(tree->left_child, second_order, post_order);
      traversal(tree->right_child, second_order, post_order);
    }
  }

  static std::string toPrefix(BinaryTreeNode *tree) {
    std::string prefix;
    getPrefix(tree, prefix);
    return prefix;
  }

  static std::string toPostfix(BinaryTreeNode *tree) {
    std::string postfix;
    getPostfix(tree, postfix);
    return postfix;
  }

  static std::string toLevelOrder(BinaryTreeNode *tree) {
    if (tree == nullptr)
      return "";

    std::string level_order;

    Queue<BinaryTreeNode *> queue;
    queue.enqueue(tree);

    while (!queue.empty()) {
      int levelSize = queue.size();

      for (int i = 0; i < levelSize; i++) {
        BinaryTreeNode *node = queue.dequeue();
        level_order += node->symbol;

        if (node->left_child)
          queue.enqueue(node->left_child);

        if (node->right_child)
          queue.enqueue(node->right_child);
      }
    }

    return level_order;
  }

private:
  static void getPrefix(BinaryTreeNode *tree, std::string &prefix) {
    if (!tree)
      return;

    prefix += tree->symbol;
    getPrefix(tree->left_child, prefix);
    getPrefix(tree->right_child, prefix);
  }

  static void getPostfix(BinaryTreeNode *tree, std::string &postfix) {
    if (!tree)
      return;

    getPostfix(tree->left_child, postfix);
    getPostfix(tree->right_child, postfix);
    postfix += tree->symbol;
  }
};