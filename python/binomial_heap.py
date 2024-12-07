# specialized heap data structure that supports efficient merging, insertion and deletion-min operations
# composed of binomial trees each with a specific degree

class Node:
  def __init__(self, key):
    self.key = key
    self.degree = 0
    self.parent = None
    self.child = None
    self.sibling = None

class BinomialHeap:
  def __init__(self):
    self.head = None

  def merge(self, h1, h2):
    if h1 is None:
      return h2
    if h2 is None:
      return h1

    if h1.degree < h2.degree:
      h1, h2 = h2, h1

    h1.sibling = self.merge(h1.sibling, h2)
    if h1.child is None:
      h1.child = h1.sibling
    else:
      h1.child.sibliing = h1.sibling
    h1.sibling = None
    h1.degree += 1
    return h1


  def insert(self, key):
    new_node = Node(key)
    self.head = self.merge(self.head, new_node)

  def extract_min(self):
    if self.head is None:
      return None
    min_node = None
    prev_node = None
    x = self.head
    while x is not None:
      if min_node is None or x.key < min_node.key:
        min_node = x
        prev_node = prev_x
      prev_x = x
      x = x.sibling 
    if prev_node is None:
      self.head = min_node.child
    else:
      prev_node.sibling = min_node.child

    min_node.child = None
    min_heap = min_node.child
    while min_heap is not None:
      next = min_heap.sibling
      min_heap.sibling = None
      self.head = self.merge(self.head, min_heap)
      min_heap = next
    return min_node.key

  def decrease_key(self, x, new_key):
    x.key = new_key
    y = x
    while y is not None and y.key < y.parent.key:
      y.key, y.parent.key = y.parent.key, y.key
      y = y.parent 
