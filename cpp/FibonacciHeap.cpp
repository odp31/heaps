#include <iostream>
#include <memory>
#include <vector>
#include <limits>
#include <algorithm>

struct FibonacciNode {
  int data;
  int degree;
  bool mark;
  std::shared_ptr<FibonacciNode> parent;
  std::shared_ptr<FibonacciNode> child;
  std::shared_ptr<FibonacciNode> left;
  std::shared_ptr<FibonacciNode> right;

  FibonacciNode(int data) : data(data), degree(0), mark(false), parent(nullptr), child(nullptr), left(nullptr), right(nullptr), {}
};

class FibonacciHeap {
private:
  std::shared_ptr<FibonacciNode> minNode;
  int nodeCount;

  void consolidate() {
    if(minNode == nullptr) return;

    std::vector<std::shared_ptr<FibonacciNode>> degreeTable;
    std::vector<std::shared_ptr<FibonacciNode>>nodeList;

    auto current = minNode;
    do {
      nodeList.push_back(current);
      current = current->right;
    } while (current != minNode);

    for(const auto& node : nodeList) {
      auto x = node;
      int degree = x->degree;
      while(degreeTable.size() > degree && degreeTable[degree] != nullptr) {
        auto y = degreeTable[degree];
        if(x->data > y->data) std::swap(x, y);

        link(y, x);
        degreeTable[degree] = nullptr;
        degree++;
      }
      if(degreeTable.size() < = degree) degreeTable.resize(degree+1);
      degreeTable[degree] = x;
    }
    minNode = nullptr;
    for(const auto& node : degreeTable) {
      if(node != nullptr) {
        minNode = node;
        minNode->left = minNode;
        minNode->right = minNode;
      } else {
        concatentate(minNode, node);
        if(node->data < minNode->data){
          minNode = node;
        }
      }
    }
  }
}

void link(std::shared_ptr<FibonacciNode> y, std::shared_ptr<FibonacciNode> x){
  removeNodeFromList(y);
  y->parent = x;
  if(x->child == nullptr){
    x->child = y;
    y->left = y;
    y->right = y;
  } else {
    concatenate(x->child, y);
  }
  x->degree++;
  y->mark = false;
}


void cut(std::shared_ptr<FibonacciNode> node, std::shared_ptr<FibonacciNode> parent) {
  removeNodeFromList(node);
  parent->degree--;
  concatenate(minNode, node);
  node->parent = nullptr; 
  node->mark = false;
}

void cascadingCut(std::shared_ptr<FibonacciNode> node){
  auto parent = node->parent;
  if(parent != nullptr) {
    if(!node->mark) {
      node->mark = true;
    } else {
      cut(node, parent);
      cascadingCut(parent);
    }
  }
}

void removeFromList(std::shared_ptr<FibonacciNode> node) {
  node->left->right = node->right;
  node->right->left = node->left;

  if(node->parent != nullptr && node->parent->parent->child == node && node->left == node)
    node->parent->child = nullptr;
  else if(node->parent != nullptr && node->parent->child == node)
    node->parent->child = node->right;
}

void concatenate(std:shared_ptr<FibonacciNode> list1, std::shared_ptr<FibonacciNode> list2) {
  auto temp1 = list1->right;
  auto temp2 = list2->left;

  list1->right = list2;
  list2->left = list1;
  temp1->left = temp2;  
  temp2->right = temp1;
}

public:
  FibonacciHeap() : minNode(nullptr), nodeCount(0) {}

  void insert(int dat) {
    auto newNode = std::make_shared<FibonacciNode>(data);
    if(minNode == nullptr) {
      minNode = newNode;
      minNode->left = minNode;
      minNode->right = minNode;
    } else {
      concatenate(minNode, newNode);
      if(newNode->data < minNode->data) {
        minNode = newNode;
      }
    }
    nodeCount++;
  }

  int getMin() const {
    if(minNode == nullptr) {
      return std::numeric_limits<int>::max();
    }
    return minNode->data;
  }

  void extractMin() {
    if(minNode == nullptr) return;

    auto z = minNode;
    if(z->child != nullptr) {
      auto child = z->child;
      do {
        auto next = child->right;
        child->parent = nullptr;
        concatenate(minNode, child);
        child = next;
      } while (child != z-> child);
    }
    removeNodeFromList(z);
    if(z == z-> right) {
      minNode = nullptr;
    } else {
      minNode = z->right;
      consolidate();
    }
    nodeCount--;
  }


  void decreaseKey(std::shared_ptr<FibonacciNode> node, int newData) {
        if (newData > node->data) return;

        node->data = newData;
        auto parent = node->parent;
        if (parent != nullptr && node->data < parent->data) {
            cut(node, parent);
            cascadingCut(parent);
        }
        if (node->data < minNode->data) {
            minNode = node;
        }
    }

    int size() const {
        return nodeCount;
    }

    bool isEmpty() const{
        return nodeCount == 0;
    }

    // Helper function to find a node by value (for decreaseKey demo)
    std::shared_ptr<FibonacciNode> findNode(int value) {
        if (minNode == nullptr) return nullptr;
        std::vector<std::shared_ptr<FibonacciNode>> visited;
        std::vector<std::shared_ptr<FibonacciNode>> queue;
        queue.push_back(minNode);

        while (!queue.empty()) {
            auto current = queue.front();
            queue.erase(queue.begin());

            if (current->data == value) return current;
            if(std::find(visited.begin(), visited.end(), current) == visited.end()){
              visited.push_back(current);
              auto child = current->child;
              if (child != nullptr) {
                  auto start = child;
                  do {
                      queue.push_back(child);
                      child = child->right;
                  } while (child != start);
              }
              queue.push_back(current->right);
            }
        }
        return nullptr;
    }
};

