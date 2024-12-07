# operations and their time complexities
# insert; O(log n)
# extract min/max; O(log n)
# heapify up/down; O(log n) 



class BinaryHeap:
  def __init__(self, heap_type='min'):
    self.heap = []
    self.heap_type = heap_type

  def parent(self, i):
    return (i - 1) // 2

  def left_child(self, i):
    return 2 * i + 1

  def right_child(self, i):
    return 2 * i + 2

  def heapify_up(self, i):
    while i > 0 and self.heap[self.parent(i)] > self.heap[i] if self.heap_type == 'min' else self.heap[self.parent(i)] < self.heap[i]:
      self.heap[i], self.heap[self.parent(i)] = self.heap[self.parent(i)], self.heap[i]
      i = self.parent(i)

  def heapify_down(self, i):
    while True:
      largest = i
      left = self.left_child(i)
      right = self.right_child(i)

      if left < len(self.heap) and self.heap[left] < self.heap[largest] if self.heap_type == 'min' else self.heap[left] > self.heap[largest]:
        largest = left

      if right < len(self.heap) and self.heap[right] < self.heap[largest] if self.heap_type == 'min' else self.heap[right] > self.heap[largest]:
        largest = right 

      if largest != i:
        self.heap[i], self.heap[largest] = self.heap[largest], self.heap[i]
        i = largest

      else:
        break

    def insert(self, value):
      self.heap.append(value)
      self.heapify_up(len(self.heap) - 1)

    def extract_min(self):
      if not self.heap:
        return None
      if len(self.heap) == 1:
        return self.heap.pop()
      root = self.heap[0]
      self.heap[0] = self.heap.pop()
      return root

    def extract_max(self):
      if not self.heap:
        return None
      if len(self.heap) == 1:
        return self.heap..pop()
      root = self.heap[0]
      self.heap[0] = self.heap.pop()
      self.heapify_down(0)
      return root 

