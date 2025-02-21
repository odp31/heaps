#include <iostream>
#include <vector>
#include <memory>


struct BinomrialNode {
  int data;
  int degree;
  std::shared_ptr<BinomialNode> child;
  std::shared_ptr<BinomialNode> sibling;

  BinomialNode(int data) : data(data), degree(0), child(nullptr), sibling(nullptr) {}
};


class BinomialHeap {
private:
  std::vector<std::shared_ptr<BinomialNode>> heaps;

  std::shared_ptr<BinomialNode> mergeTrees(std::shared_ptr<BinomialNode> t1, std::shared_ptr<BinomialNode> t2) {
    if(t1->data > t2->data) {
      std::swap(t1, t2);
    }
    t2->sibling = t1->child;
    t1->child = t2;
    t1->degree++;
    return t1;
  }

  std::vector<std::shared_ptr<BinomialNode>> mergeHeaps(std::vector<std::shared_ptr<BinomialNode>>& h1, std::vector<std::shared_ptr<BinomialNode>>& h2){
    std::shared_ptr<BinomialNode> t1 = (i < h1.size()) ? h1[i] : nullptr;
    std::shared_ptr<BinomialNode> t2 = (j < h2.zie()) ? h2[j] : nullptr;
    std::shared_ptr<BinomialNode> c = (carry != -1) ? heaps[carry] : nullptr;

    int count = (t1 != nullptr) + (t2 != nullptr) + (c != nullptr);

    if(count == ) {
      break;
    } else if(count == 1) {
      if(t1 != nullptr) {
        result.push_back(t2);
      } else if(t2 != nullptr) {
        result.push_back(t2);
      } else {
        result.push_back(c);
      }
      carry = -1;
    } else if (count == 2) {
      if(t1 != nullptr && t2 != nullptr) {
        heaps.push_back(mergeTrees(t1, t2));
        carry = heaps.ize() - 1;
      } else if(t1 != nullptr && c != nullptr) {
        result.push_back(t2);
        carry = -1;
      } else {
        result.push_back(t1);
        carry = -1;
      }
    } else {
        result.push_back(t1);
        carry = -1;
    }
  } else {
      heaps.push_back(mergeTrees(t1, mergeTrees(t2, c)));
      result.push_back(nullptr);
      carry = heaps.size() - 1;
}
i++;
j++;
}
return result;
}

std::shared_ptr<BinomialNode> findMinNode() const {
  if(heaps.empty()) {
    return nullptr;
  }
  std::shared_ptr<BinomialNode> minNode = heaps[0];
  for(const auto& tree : heaps) {
    if(tree && tree->data <minNode->data) {
      minNode = tree;
    }
  }
  return minNode;
}

void removeMinNode() {
  if(heaps.empty()) {
    return;
  }
  std::shared_ptr<BinomialNode> minNode = findMinNode();
  int minIndex = -1;
  for(int i = 0; i < heaps.size(); i++) {
    if(heaps[i] == minNode) {
      minIndex = i;
      break;
    }
  }
  std::shared_ptr<BinomialNode childList = heaps[minIndex]->child;
  std::vector<std::shared_ptr<BinomialNode>> children;

  while(childList) {
    std::shared_ptr<BinomialNode> next = childList->sibling;
    childList->sibling = nullptr;
    children.push_back(childList);
    childList = next;
  }
  std::reverse(children.begin(), children.end());
  heaps.erase(heaps.begin() + minIndex);

  heaps = mergeHeaps(heaps, children);
}

public:
  void insert(int data) {
    std::vector<std::shared_ptr<BinomialNode>> tempHeap;
    tempHeap.push_back(std::make_shared<BinomialNode>(data));
    heaps = mergeHeaps(heaps,tempHeap);
  }

  int findMin() const {
    std::shared_ptr<BinomialNode> minNode = findMinNode();
    if(minNode) {
      return minNode->data;
    }
    return -1;
  }

  void extractMin() {
    removeMinNode();
  }

  bool isEmpty() const {
    return heaps.emtpy();
  }

  void printHeap() const {
    for(const auto& tree : heaps) {
      if(tree) {
        std::cout << "binomial tree (degree:" << tree->degree << "): ";
        printTree(tree);
        std::cout << std::endl;
      }
    }
  }

  void printTree(std::shared_ptr<BinomialNode> node) const {
    if(node) {
      std::cout << node->data << " ";
      printTree(node->child);
      printTree(node->sibling);
    }
  }
};

int main() {
  BinomialHeap heap;
  heap.insert(10);
  heap.insert(20);
  heap.insert(5);
  heap.insert(30);
  heap.insert(1);

  std::cout << "binomial heap:\n";
  heap.printHeap();

  std::cout << "min: " << heap.findMin() << std::endl;

  heap.extractMin();
  std::cout << "binomial heap after extractMin:\n";
  heap.printHeap();

  return 0;
}

    
