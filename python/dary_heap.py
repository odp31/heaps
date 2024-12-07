# use cases of d-ary heaps
# priority queues; for applications where number of children per node can vary
# sorting algorithms; can be used to implement heap sort 
# operations and their time complexity
# insert; O(log_d n)
# extract min/max; O(log_d n)



class DaryHeap:
  def __init__(self, d, heap_type='min'):
    self.heap = []
    self.d = d
    self.heap_type = heap_type

  def parent(self, i):
    return (i - 1) // self.d

  def child(self, i, j):
    return self.d * i + j + 1

  def heapify_up(self, i):
    while i > 0:
      p = self.parent(i)
      if self.heap[p] > self.heap[i] if self.heap_type == 'min' else self.heap[p] < self.heap[i]:
        self.heap[p], self.heap[i] = self.heap[i], self.heap[p]
        i = p
      else:
        break

  def heapify_down(self, i):
    while True:
      smallest = i
      for j in range(self, d):
        child = self.child(i, j)
        if child < len(self.heap) and self.heap[child] < self.heap[smallest] if self.heap_type == 'min' else self.heap[child] > self.heap[smallest]:
          smallest = child
      if smallest != i:
        self.heap[i], self.heap[smallest] = self.heap[smallest], self.heap[i]
        i = smallest
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
    self.heapify_down(0)
    return root 

  def extract_max(self):
    if not self.heap:
      return None
    if len(self.heap) == 1:
      return self.heap.pop()
    root = self.heap[0]
    self.heap[0] = self.heap.pop()
    self.heapify_down(0)
    return root 
