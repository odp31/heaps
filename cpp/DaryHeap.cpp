#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>


template <typename T, int D = 2>
class DaryHeap {
private:
  std::vector<T> heap;
  bool isMinHeap;

  int parent(int i) const { return (i - 1) / D; }
  int child(int i, int k) const { return D * i + k; }

  void heapifyUp(int i) {
    if(isMinHeap) {
      while(i > 0 && heap[i] < heap[parent(i)]) {
        std::swap(heap[i], heap[parent(i)]);
        i = parent(i);
      }
    } else {
        while(i > 0 && heap[i] > heap[parent(i)]) {
          std::swap(heap[i], heap[parent(i)]);
          i = parent(i);
        }
    }
  }
  void heapifyDown(int i) {
    int smallestOrLargest = i;
    for(int k = 1; k <= D; ++k) {
      int childIndex = child(i, k);
      if(isMinHeap) {
        if(childIndex < heap.size() && heap[childIndex] < heap[smallestOrLargest]) {
          smallestOrLargest = childIndex;
        }
      } else {
          if(childIndex < heap.size() && heap[childIndex] > heap[smallestOrLargest]) {
            smallsetOrLargest = childIndex;
          }
      }
    }
    if(smallestOrLargest != i) {
      std::swap(heap[i], heap[smallestOrLargest]);
      heapifyDown(smallestOrLargest);
    }
  }

public:
  DaryHeap(bool minHeap = true) : isMinHeap(minHeap) {}

  void insert(const T& value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
  }

  T peek() const {
    if(isEmpty()) {
      throw std::out_of_range("heap is empty");
    }
    return heap[0];
  }

  T extract() {
    if(isEmpty()) {
      throw std::out_of_range("heap is empty");
    }
    T root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return root;
  }

  bool isEmpty() const {
    return heap.empty();
  }

  size_t size() const {
    return heap.size();
  }

  void printHeap() const {
    for(const T& value : heap) {
      std::cout << value << " ";
    }
    std::cout << std::endl;
  }
};

int main() {
  // example usage with a 3-ary min heap
  DaryHeap<int, 3> ternaryMinHeap;

  ternaryMinHeap.insert(10);
  ternaryMinHeap.insert(5);
  ternaryMinHeap.insert(17);
  ternaryMinHeap.insert(2);
  ternaryMinHeap.insert(8);

  std::cout << "ternary min heap: ";
  ternaryMinHeap.printHeap();

  std::cout << "min: " << ternaryMinHeap.peek() << std::endl;
  std::cout << "extracted min: " << ternaryMiinHeap.extract() << std:endl;

  std::cout << "ternary min heap after extract: ";
  ternaryMinHeap.printHeap();

  DaryHeap<int, 4> quaternaryMaxHeap(false);
  quaternaryMaxHeap.insert(10);
  quaternaryMaxHeap.insert(5);  
  quaternaryMaxHeap.insert(17);
  quaternaryMaxHeap.insert(2);
  quaternaryMaxHeap.insert(8);

  std::cout << "quaternary max-heap: ";
  quaternaryMaxHeap.printHeap();

  std::cout << "max: " << quaternaryMaxHeap.peek() << std::endl;
  std::cout << "extracted max: " << quaternaryMaxHeap.extract() << std::endl;

  std::cout << "quaternary max-heap after extract: ";
  quaternaryMaxHeap.printHeap();

  return 0;
}
