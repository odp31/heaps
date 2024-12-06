// complete binary tree, meaning every level is filled except possibly the last which is filled from left 
// to right
// max heap; value of each node >= values of children
// min heap; value of each node <= values of children 

import java.util.ArrayList;
import java.util.List;

public class BinaryHeap {
  private final List<Integer> heap;
  private final boolean isMaxHeap;

  public BinaryHeap(boolean isMaxHeap) {
    this.heap = new ArrayList<>();
    this.isMaxHeap = isMaxHeap;
  }
  private int getParentIndex(int childIndex) {
    return (childIndex - 1) / 2;
  }
  private int getLeftChildIndex(int parentIndex) {
    return 2 * parentIndex + 1;
  }
  private int getRightChildIndex(int parentIndex) {
    return 2 * parentIndex + 2;
  }
  private void heapifyUp(int index) {
    int parentIndex = getParentIndex(index);
    if(parentIndex >= 0) {
      if(isMaxHeap) {
        if(heap.get(index) > heap.get(parentIndex)) {
          swap(index, parentIndex);
          heapifyUp(parentIndex);
        }
      } else {
        if(heap.get(index) < heap.get(parentIndex)) {
          swap(index, parentIndex);
          heapifyUp(parentIndex);
        }
      }
    }
  }
  private void heapifyDown(int index) {
    int leftChildIndex = getLeftChildIndex(index);
    int rightChildIndex = getRightChildIndex(index);
    int largestOrSmallestIndex = index;

    if(isMaxHeap) {
      if(leftChildIndex < heap.size() && heap.get(leftChildIndex) > heap.get(largestOrSmallestIndex)) {
        largestOrSmallestIndex = leftChildIndex;
      }
      if(rightChildIndex < heap.size() && heap.get(rightChildIndex) > heap.get(largestOrSmallestIndex)){
        largestOrSmallestIndex = rightChildIndex;
      }
    } else {
      if(leftChildIndex < heap.size() && heap.get(leftChildIndex) < heap.get(largestOrSmallestIndex)) {
        largestOrSmallestIndex = leftChildIndex;
      }
      if(rightChildIndex < heap.size() && heap.get(rightChildIndex) < heap.get(largestOrSmallestIndex)) {
        largestOrSmallestIndex = rightChildIndex;
      }
    }
    if(largestOrSmallestIndex != index) {
      swap(index, largestOrSmallestIndex);
      heapifyDown(largestOrSmallestIndex);
    }
  }

  private void swap(int index1, int index2) {
    int temp = heap.get(index1);
    heap.set(index1, heap.get(index2));
    heap.set(index2, temp);
  }
  public void insert(int value) {
    heap.add(value);
    heapifyUp(heap.size() - 1);
  }
  public int extractMax() {
    if(heap.isEmpty()) {
      throw new IllegalStateException("heap is empty");
    }
    int max = heap.get(0);
    swap(0, heap.size() - 1);
    heap.remove(heap.size() - 1);
    heapifyDown(0);
    return max;
  }

  public int extractMin() {
    if(heap.isEmpty()) {
      throw new IllegalStateException("Heap is empty");
    }
    int min = heap.get(0);
    swap(0, heap.size() - 1);
    heap.remove(heap.size() - 1);
    heapifyDown(0);
    return min;
  }

  public int peek() {
    if(heap.isEmpty()) {
      throw new IllegalStateException("heap is empty");
    }
    return heap.get(0);
  }

  public boolean isEmpty() {
    return heap.isEmpty();
  }
}
    
