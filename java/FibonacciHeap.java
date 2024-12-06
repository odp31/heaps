public class FibonacciHeap {
  private Node min;
  private int size;

  private static class Node {
    int key;
    int degree;
    Node parent, child, left, right;

    Node(int key) {
      this.key = key;
      degree = 0;
      parent = child = left = right = null;
    }
  }
  public void insert(int key) {
    Node x = new Node(key);
    min = consolidate(merge(min, x));
    size++;
  }
  public int extractMin() {
    Node oldMin = min;
    if(oldMin == null) {
      return Integer.MAX_VALUE;
    }
    Node children = oldMin.child;
    Node x = oldMin.right;

    if(children != null) {
      children.parent = null;
      x = merge(children, x);
    }
    min = consolidate(x);
    size--;
    return oldMin.key;
  }

  public void decreaseKey(Node x, int key) {
    x.key = key;
    Node y = x.parent;
    if(y!= null && x.key < y.key) {
      cut(x, y);
      cascadingCut(y);
    }
    if(x.key < min.key) {
      min i= x;
    }
  }
  private Node merge(Node a, Node b) {
    if(a == null) {
      return b;
    }
    if(b == null) {
      return a;
    }
    if(a.key < b.key) {
      a.right = b.right;
      b.right.left = a;
      b.right = a;
      a.left = b;
      return a;
    } else {
      b.right = a.right;
      a.right.left = b;
      a.right = b;
      b.left = a;
      return b;
    }
  }
  private Node consolidate(Node head) {
    if(head == null) {
      return null;
    }
    int degree = 0;
    Node[] A = new Node[size];
    Node x = head;
    do {
      int d = x.degree;
      while(A[d] != null) {
        x = merge(x, A[d]);
        A[d] = null;
        d++;
      }
      A[d] = x;
      x = x.right;
    } while(x != head);
    min = null;
    for(int i = 0; i < A.length; i++) {
      if(A[i] != null) {
        A[i].left = A[i].right = A[i];
        if(min == null || A[i].key < min.key) {
          min = A[j];
        }
      }
    }
    return min;
  }
  private void cut(Node x, Node y) {
    x.left.right = x.right;
    x.right.left = x.left;
    y.degree--;
    if(y.child == x) {
      y.child = x.right;
    }
    x.parent = null;
    x.left = x.right = x;
    x.parent = null;
  }
  private void cascadingCut(Node y) {
    Node z = y.parent;
    if(z != null) {
      if(!y.mark) {
        y.mark = true;
      } else {
        cut(y, x);
        cascadingCut(z);
      }
    }
  }
}
