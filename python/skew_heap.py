class Node:
  def __init__(self, key):
    self.key = key
    self.left = None
    self.right = None

class SkewHeap:
  def __init__(self):
    self.root = None

  def merge(self, h1, h2):
    if h1 is None:
      return h2
    if h2 is None:
      return h1
    if h1.key < h2.key:
      h1.right = self.merge(h1.right, h2)
      return h1
    else:
      h2.right = self.merge(h2.right, h1)
      return h2


  def insert(self, key):
    node = Node(key)
    self.root = self.merge(self.root, node)

  def extract_min(self):
    if self.root is None:
      return None
    min_node = self.root
    self.root = self.merge(self.root.left, self.root.right)
    return min_node.key

  def decrease_key(self, node, new_key):
    node.key = new_key
    while node.parent is not None and node.key < node.parent.key:
      node.key, node.parent.key = node.parent.key, node.key
      node = node.parent 
