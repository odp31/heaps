// heap ordered tree with no structural constraints

public class PairingHeap {
  private Node min;

  private static class Node {
    int key;
    Node parent, child, left, right;

    Node(int key) {
      this.key = key;
    }
  }
  public void insert(int key) {
    Node newNode = new Node(key);
    min = merge(min, newNode);
  }
  public int extractMin() {
    if(min == null) {
      throw new IllegalStateException("heap is empty");
    }
    Node oldMin = min;
    Node children = oldMin.child;
    min = mergePairs(children);
    return oldMin.key;
  }
  private Node merge(Node x, Node y) {
    if(x == null) {
      return y;
    }
    if(y == null) {
      return x;
    }
    if(x.key < y.key) {
      x.right = merge(x.right, y);
      return x;
    } else {
      y.right = merge(x, y.right);
      return y;
    }
  }
  private Node mergePairs(Node h) {
    if(h == null) {
      return null;
    }
    if(h.right == null) {
      return h;
    }
    Node h1 = merge(h, h.right.right);
    Node h2 = merge(h.right.left, h.right.right.right);
    return mergePairs(merge(h1, h2));
  }
}
