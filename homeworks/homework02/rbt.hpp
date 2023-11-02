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

    newRoot->red = false;
    newRoot->leftChild->red = true;

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

    newRoot->red = false;
    newRoot->rightChild->red = true;

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

  Node *changeColor(Node *root, Node *newNode) {
    if (root == nullptr || newNode == nullptr)
      return nullptr;

    Node *result = root;

    if (newNode->value > root->value) {
      result = changeColor(root->rightChild, newNode);
    } else if (newNode->value < root->value) {
      result = changeColor(root->leftChild, newNode);
    }

    if (!(root->red) && (root->leftChild != nullptr && root->leftChild->red) &&
        (root->rightChild != nullptr && root->rightChild->red)) {
      // check if current root is black and left child and right child are red,
      // reverse their color

      root->red = true;
      root->leftChild->red = false;
      root->rightChild->red = false;
    }

    if (result == nullptr)
      return root;

    return result;
  }

  void fixTree(Node *node, Node *newNode) {
    if (node == nullptr || newNode == nullptr)
      return;

    Node *child = nullptr;
    Node *grandchild = nullptr;

    bool left = false;
    bool right = false;

    if (newNode->value >= node->value) {
      // right
      child = node->rightChild;
      right = true;

      if (child == nullptr)
        return;

      if (newNode->value >= child->value) {
        // right
        grandchild = child->rightChild;
      } else {
        // left
        grandchild = child->leftChild;
      }
    } else {
      // left
      child = node->leftChild;
      left = true;

      if (child == nullptr)
        return;

      if (newNode->value >= child->value) {
        // right
        grandchild = child->rightChild;
      } else {
        // left
        grandchild = child->leftChild;
      }
    }

    if (grandchild == nullptr)
      return;

    if (child->red && grandchild->red) {
      // if child and grandchild are red, do rotation

      if (node->rightChild == child) {
        // right
        if (child->leftChild == grandchild)
          // RL (triangle)
          this->rotateRight(child);

        // RR (line)
        this->rotateLeft(node);

        this->n_rotations += 1;
      } else if (node->leftChild == child) {
        // left
        if (child->rightChild == grandchild)
          // LR (triangle)
          this->rotateLeft(child);

        // LL (line)
        this->rotateRight(node);

        this->n_rotations += 1;
      }
    } else {
      // otherwise child or grandchild is black, keep fix the tree

      if (right)
        this->fixTree(node->rightChild, newNode);
      else if (left)
        this->fixTree(node->leftChild, newNode);
    }
  }

public:
  void insert(char val) {
    // insert: change color > rotate > insert > rotate > change root to black

    // initialize new node in red
    Node *newNode = new Node(val, true);

    // change color
    this->changeColor(this->root, newNode);

    // fix tree (rotate)
    this->fixTree(this->root, newNode);

    // insert
    Node *node = this->binaryInsert(this->root, newNode);
    if (this->root == nullptr)
      this->root = node;

    // fix tree (rotate)
    this->fixTree(this->root, newNode);

    // change root to black
    this->root->red = false;
  }

  void printTree(std::ostream &out) const {
    // this->printTreeHelper(this->root, out);
    std::cout << "================================================"
              << std::endl;
    this->printTreeHelper(this->root, 0);
  }
};