#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

class RedBlackTree {
public:
  class Node {
  public:
    Node *parent;
    Node *leftChild;
    char value;
    Node *rightChild;
    bool red;

  public:
    Node()
        : parent(nullptr), leftChild(nullptr), rightChild(nullptr), red(false) {
    }
    Node(char value, bool red = false)
        : parent(nullptr), leftChild(nullptr), rightChild(nullptr), red(red),
          value(value) {}
  };

public:
  Node *root;
  size_t n_rotations;

public:
  RedBlackTree() : root(nullptr), n_rotations(0) {}

private:
  void rotateLeft(Node *node) {
    // std::cout << "left rotate " << int(node->value) << std::endl;

    // the new right child for the node
    Node *newRightChild = node->rightChild->leftChild;
    // the new root for the subtree
    Node *newRoot = node->rightChild;

    // set node's right child to the new right child
    node->rightChild = newRightChild;
    if (node->rightChild != nullptr)
      node->rightChild->parent = node;

    if (node->parent == nullptr)
      // if the node was root, replace it with the new root
      this->root = newRoot;
    else if (node->parent->rightChild == node)
      // if the node is parent's right child, now replace parent's right child
      // with the new root
      node->parent->rightChild = newRoot;
    else
      // otherwise the node is parent's left child, now replace parent's left
      // child with the new root
      node->parent->leftChild = newRoot;

    newRoot->leftChild = node;
    newRoot->parent = node->parent;
    node->parent = newRoot;

    // this->n_rotations += 1;
  }

  void rotateRight(Node *node) {
    // std::cout << "left rotate " << int(node->value) << std::endl;

    // the new left child for the node
    Node *newLeftChild = node->leftChild->rightChild;
    // the new root for the subtree
    Node *newRoot = node->leftChild;

    // set node's right child to the new right child
    node->leftChild = newLeftChild;
    if (node->leftChild != nullptr)
      node->leftChild->parent = node;

    if (node->parent == nullptr)
      // if the node was root, replace it with the new root
      this->root = newRoot;
    else if (node->parent->rightChild == node)
      // if the node is parent's right child, now replace parent's right child
      // with the new root
      node->parent->rightChild = newRoot;
    else
      // otherwise the node is parent's left child, now replace parent's left
      // child with the new root
      node->parent->leftChild = newRoot;

    newRoot->rightChild = node;
    newRoot->parent = node->parent;
    node->parent = newRoot;

    // this->n_rotations += 1;
  }

  Node *binaryInsert(Node *node, Node *newNode) {
    // std::cout << "insert " << int(newNode->value) << "(" << newNode << ")"
    //           << " into " << int(node ? node->value : -1) << "(" << node <<
    //           ")"
    //           << std::endl;
    if (node == nullptr)
      return newNode;

    if (newNode->value >= node->value) {
      node->rightChild = this->binaryInsert(node->rightChild, newNode);
      node->rightChild->parent = node;
    } else {
      node->leftChild = this->binaryInsert(node->leftChild, newNode);
      node->leftChild->parent = node;
    }

    return node;
  }

  void fixCase1(Node *node, Node *parent, Node *grandparent, Node *uncle) {
    parent->red = false;
    grandparent->red = true;
    uncle->red = false;
  }

  void fixInsert(Node *node) {
    while (node != this->root && node->parent != nullptr && node->parent->red) {
      Node *parent = node->parent;
      Node *grandparent = parent->parent;
      Node *uncle = nullptr;

      if (parent == grandparent->leftChild) {
        // left side

        uncle = grandparent->rightChild;

        if (uncle != nullptr && uncle->red) {
          // case 1

          this->fixCase1(node, parent, grandparent, uncle);

          // switch current node to grandparent
          node = grandparent;
        } else {
          if (parent->rightChild == node) {
            // case 2
            // if the uncle is black(or null) and the node is right child (looks
            // like a triangle)

            this->rotateLeft(parent);
            node = parent->parent;
            parent = node;
          }

          // case 3
          // if the uncle is black(or null) and the node is left child (looks
          // like a line)

          parent->red = false;
          grandparent->red = true;
          this->rotateRight(grandparent);

          this->n_rotations += 1;
        }
      } else {
        // right side

        uncle = grandparent->leftChild;

        if (uncle != nullptr && uncle->red) {
          // case 1

          this->fixCase1(node, parent, grandparent, uncle);

          // switch current node to grandparent
          node = grandparent;
        } else {
          if (parent->leftChild == node) {
            // case 2
            // if the uncle is black(or null) and the node is left child (looks
            // like a triangle)

            this->rotateRight(parent);
            node = parent->parent;
            parent = node;
          }

          // case 3
          // if the uncle is black(or null) and the node is right child (looks
          // like a line)

          parent->red = false;
          grandparent->red = true;
          this->rotateLeft(grandparent);

          this->n_rotations += 1;
        }
      }
    }

    // finally, set the root to black
    this->root->red = false;
  }

  void printTreeHelper(Node *root, int space) const {
    if (root != nullptr) {
      space += 10;
      printTreeHelper(root->rightChild, space);
      std::cout << std::endl;
      for (int i = 10; i < space; i++)
        std::cout << " ";
      std::cout << int(root->value) << "(" << (root->red ? "r" : "b") << ")"
                << std::endl;
      printTreeHelper(root->leftChild, space);
    }
  }

public:
  void insert(char val) {
    Node *newNode = new Node(val, true);
    Node *node = this->binaryInsert(this->root, newNode);
    if (this->root == nullptr)
      this->root = node;
    this->fixInsert(newNode);
  }

  void printTree(std::ostream &out) const {
    // this->printTreeHelper(this->root, out);
    std::cout << "================================================"
              << std::endl;
    this->printTreeHelper(this->root, 0);
  }
};