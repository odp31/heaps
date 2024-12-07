class Node:
  def __init__(self, key):
    self.key = key
    self.parent = None
    self.child = None
    self.next = None

class PairingHeap:
  def __init__(self):
    self.min = None

  def insert(self, key):
    node = Node(key)
    self.min = self.merge(self.min, node)

  def merge(self, h1, h2):
    if h1 is None:
      return h2
    if h2 is None:
      return h1
    if h1.key < h2.key:
      h1.next = h2
      return h1
    else:
      h2.next = h1
      return h2

  def extract_min(self):
    if self.min is None:
      return None
    min_node = self.min
    self.min = self.min.next
    children = []
    while min_node.child is not None:
      children.append(min_node.child)
      min_node.child = min_node.child.next

    while len(children) > 1:
      new_children = []
      for i in range(0, len(children), 2):
        new_children.append(self.merge(children[i], children[i + 1] if i + 1 < len(children) else None))
      children = new_children 

    if len(children) > 0:
      self.min = self.merge(self.min, children[0])
    return min_node.key

  def decrease_key(self, node, new_key):
    node.key = new_key
    while node.parent is not None and node.key < node.parent.key:
      node.key, node.parent.key = node.parent.key, node.key
      node = node.parent 
