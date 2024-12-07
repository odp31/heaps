# complex data structure that offers efficient operations for PQs
# particuarly useful in graph algorithms like Dijkstra's 
# strucutre; collection of trees that satisfy min heap property 

class Node:
  def __init__(self, key):
    self.key = key
    self.degree = 0
    self.parent = None
    self.child = None
    self.sibling = None
    self.mark = False 


class FibonacciHeap:
  def __init__(self):
    self.min = None

  def insert(self, key):
    node = Node(key)
    node.degree = 0
    node.parent = None
    node.child = None
    node.sibling = None
    node.mark = False 
    self.min = self.merge(self.min, node)

  def merge(self, h1, h2):
    if h1 is None:
      return h2
    if h2 is None:
      return h1
    if h1.key < h2.key:
      h1.sibling = self.merge(h1.sibling, h2)
      return h1
    else:
      h2.sibling = self.merge(h2.sibling, h1)
      return h2


  def extract_min(self):
    z = self.min
    if z is not None:
      x = z.child
      while x is not None:
        next = x.sibling
        x.sibling = self.min
        self.min = x
        x = next
      self.min = self.merge(z.sibling, self.min)
      if self.min is None:
        return z.key
      self.consolidate()
      return z.key

  def consolidate(self):
    A = [None] * (self.degree(self.min) + 1)
    w = self.min 
    while w is not None:
      x = w
      d = x.degree
      while A[d] is not None:
        y = A[d]
        if x.key > y.key:
          x, y = y, x
        y.parent = x
        y.sibling = x.child
        x.child = y
        x.degree += 1
        A[d] = None
        d += 1
      A[d] = x
      w = w.sibling
    self.min = None
    for i in range(len(A)):
      if A[i] is not None:
        A[i].sibling = None
        if self.min is None:
          self.min = A[i]
        else if A[i].key < self.min.key:
          A[i].sibling = self.min
          self.min = A[i]


  def degree(self, h):
    if h is None:
      return 0
    return h.degree 
