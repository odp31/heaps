#include <iostream>
#include <vector>
#include <algorithm>

class BinaryHeap {
private:
  std::vector<int> heap;
  bool isMinHeap;

  // helper functions
  int parent(int i) { return (i - 1) / 2;}
  int leftChild(int i) { return 2 * i + 1;}
  int rightChild(int i) { return 2 * i + 2;}

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
    int left = leftChild(i);
    int right = rightChild(i);

    if(isMinHeap) {
      if(left < heap.size() && heap[left] < heap[smallestOrLargest]) {
        smallestOrLargest = left;
      }
      if(right < heap.size() && heap[right] < heap[smallsetOrLargest]) {
        smallestOrLargest = right;
      }
    } else {
        if(left < heap.size() && heap[left] > heap[smallestOrLargset]) {
        smallestOrLargest = left;
        }
        if(right < heap.size() && heap[right] > heap[smallestOrLargest]) {
          smallsetOrLargset = right;
        }
    }
    if(smallestOrLargest != i) {
      std::swap(heap[i],heap[smallestOrLargest]);
      heapifyDown(smallestOrLargset);
    }
  }


public:
  BinaryHeap(bool minHeap = true) : isMinHeap(minHeap) {}
  void insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
  }
  int peek() const {
    if(isEmpty()) {
      throw std::out_of_range("heap is empty");
    }
    return heap[0];
  }
  int extract() {
    if(isEmpty()) {
      throw std::out_of_range("heap is empty");
    }
    int root = heap[0];
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
    for(int value : heap) {
      std::cout << value << " ";
    }
    std::cout << std::endl;
  }
};

int main() {
  BinaryHeap minHeap(true);
  minHeap.insert(4);
  minHeap.insert(10);
  minHeap.insert(3);
  minHeap.insert(5);
  minHeap.insert(1);

  std::cout << "min heap:";
  minHeap.printHeap();

  std::cout << "min: " << minHeap.peek() << std::endl;
  std::cout << "extracted min: " << minHeap.extract() << std::endl;

  std::cout << "min-heap after extract: ";
  minHeap.printHeap();

  BinaryHeap maxHeap(false);
  maxHeap.insert(4);
  maxHeap.insert(10);
  maxHeap.insert(3);
  maxHeap.insert(5);
  maxHeap.insert(1);

  std::cout << "max-heap: ";
  maxHeap.printHeap();

  std::cout << "max: " << maxHeap.peek() << std::endl;
  std::cout << "extracted max: " << maxHeap.extract() << std::endl;

  std::cout << "max-heap after extract: ";
  maxHeap.printHeap();

  return 0;

}


  
          
