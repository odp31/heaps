# specific type of heap data structure that prioritizes efficient merging operations 
# it maintains a property 

class Node:
  def __init__(self, key):
    self.key = key
    self.left = None
    self.right = None
    self.null_path_length = 0

class LeftistHeap:
  def __init__(self):
    self.root = None

  def merge(self, h1, h2):
    if h1 is None:
      return h2
    if h2 is None:
      return h1

    if h1.key < h2.key:
      h1.right = self.merge(h1.right, h2)
    else:
      h1, h2 = h2, h1
      h1.right = self.merge(h1.left, h2)
      h1.left = h2.left
      h2.left = None
    h1.null_path_length = self.update_null_path_length(h1)
    return h1

  def update_null_path_length(self, node):
    if node is None:
      return 0
    return 1 + max(self.update_null_path_length(node.left), self.update_null_path_length(node.right))

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
