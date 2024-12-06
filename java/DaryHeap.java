// complete D-ary tree where each node has at most D children
// generalization of a binary heap 

public class DaryHeap{
  private final int d;
  private final List<Integer> heap;
  private final boolean isMaxHeap;

  public DaryHeap(int d, boolean isMaxHeap){
    this.d = d;
    this.heap = new ArrayList<>();
    this.isMaxHeap = isMaxHeap;
  }
  private int getParentIndex(int childIndex) {
    return(childIndex - 1) / d;
  }
  private int getChildIndex(int parentIndex, int childNumber) {
    return d * parentIndex + childNumber + 1;
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
        if (heap.get(index) < heap.get(parentIndex)) {
          swap(index, parentIndex);
          heapifyUp(parentIndex);
        }
      }
    }
  }
  private void heapifyDown(int index) {
    int largestOrSmallestIndex = index;
    for(int i = 0; i < d; i++) {
      int childIndex = getChildIndex(index, i);
      if(childIndex < heap.size()) {
        if(isMaxHeap) {
          if(heap.get(childIndex) > heap.get(largestOrSmallestIndex)) {
            largestOrSmallestIndex = childIndex;
          }
        } else {
          if(heap.get(childIndex) < heap.get(largestOrSmallestIndex)) {
            largestOrSmallestIndex = childIndex;
          }
        }
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
      throw new IllegalStateException("heap is empty");
    }
    int min = heap.get(0);
    swap(0, heap.size() - 1);
    heap.remove(heap.size() - 1);
    heapifyDown(0);
    return min;
  }
}
