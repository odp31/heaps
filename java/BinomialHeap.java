// data structure that consists of a set of binomial trees each of which has a degree
// at most one binomial tree of each degree
// more complex than a binary heap but offers better amortized time complexity for certain operations


public class BinomialHeap {
  private Node head;
  private boolean isMinHeap;

  public BinomialHeap(boolean isMinHeap) {
    this.isMinHeap = isMinHeap;
    head = null;
  }
  private static class Node {
    int key;
    int degree;
    Node child, sibling, parent;
    Node(int key) {
      this.key = key;
      degree = 0;
      child = sibling = parent = null;
    }
  }
  private Node mergeTrees(Node a, Node b) {
    if(a == null) {
      return b;
    }
    if(b == null) {
      return a;
    }
    if(a.degree < b.degree) {
      a.sibling = mergeTrees(a.sibling, b);
      return a;
    } else {
      b.sibling = mergeTrees(a, b.sibling);
      return b;
    }
  }

  private Node mergeHeaps(BinomialHeap other) {
    Node result = mergeTrees(this.head, other.head);
    this.head = null;
    other.head = null;
    return result;
  }
  public void insert(int key) {
    Node newNode = new Node(key);
    BinomialHeap newHeap = new BinomialHeap(isMinHeap);
    newHeap.head = newNode;
    this.head = mergeHeaps(this);
  }
  public int extractMin() {
    if(head == null) {
      throw new IllegalStateException("heap is empty");
    }
    Node minNode = null, prevNode = null, x = head;
    int minKey = Integer.MAX_VALUE;

    while(x != null) {
      if(x.key < minKey) {
        minKey = x.key;
        minNode = x;
        prevNode = x; 
      }
      x = x.sibling;
    }
    if(prevNode != null) {
      prevNode.sibling = minNode.sibling;
    } else {
      head = minNode.sibling;
    }
    Node trees = minNode.child; 
    BinomialHeap newHeap = new BinomialHeap(isMinHeap);
    newHeap.head = trees;
    this.head = mergeHeaps(newHeap);
    return minKey;
  }
}
