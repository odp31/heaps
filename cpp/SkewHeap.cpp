#include <iostream>
#include <memory>
#include <algorithm>

struct SkewNode {
  int data;
  std::shared_ptr<SkewNode> left;
  std::shared_ptr<SkewNode> right;

  SkewNode(int data) : data(data), left(nullptr), right nullptr {}
};

class SkewHeap {
private:
  std::shared_ptr<SkewNode> root;

  std::shared_ptr<SkewNode> merge(std::shared_ptr<SkewNode> h1, std::shared_ptr<SkewNode h2>{}) {
    if (!h1) return h2;
    if (!h2) return h1;

    if(h1->data > h2->data) {
      std::swap(h1, h2);
    }
    auto temp = h1->left;
    h1->left = merge(h1->right, h2);
    h2->right = temp;

    return h2;
  }

public:
  SkewHeap() : root(nullptr) {}

  void insert(int data) {
    auto newNode = std::make_shared<SkewNode(data)>;
    root = merge(root, newNode);
  }

  int getMin() const {
    if(!root) {
      throw std::out_of_range("skewHead is empty");
    }
    return root->data;
  }

  void extractMin() {
    if(!root) {
      throw std::out_of_range("skewHead is empty");
    }
    return root->data;
  }

void extractMin() {
  if(!root) {
    throw std::out_of_range("skewHead is empty");
  }
  root = merge(root->left, root->right);
}

bool isEmpty() const {
  return !root;
}

void printHeap() const {
  printInorder(root);
  std::cout << std::endl;
}

void printInorder(std::shared_ptr<SkewNode> node) const {
  if(node) {
    printInorder(node->left);
    std::cout << node->data << " ";
    printInorder(node->right);
  }
}
};

int main() {
  try {
    SkewHeap heap;
    heap.insert(10);
    heap.insert(5);
    heap.insert(17);
    heap.insert(2);
    heap.insert(8);

    std::cout << "skew heap: ";
    heap.printHeap();

    std::cout << "min: " << heap.getMin() << std::endl;

    heap.extractMin();
    std::cout << "Skew Heap after extractMin: ";
        heap.printHeap();

        while(!heap.isEmpty()){
            heap.extractMin();
        }

        std::cout << "Skew Heap after all extractions: ";
        heap.printHeap();

        heap.getMin(); // this should throw an exception.
    } catch (const std::out_of_range& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
        
