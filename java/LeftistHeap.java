// heap ordered tree with a special property; difference in the depths of the two children of any node
// is at most one 

public class LeftistHeap{
  private Node root;
  private static class Node {
    int key;
    int rank;
    Node left, right;

    Node(int key) {
      this.key = key;
      this.rank = 0;
    }
  }
  public void insert(int key) {
    Node newNode = new Node(key);
    root = merge(root, newNode);
  }
  public int extractMin() {
    int min = root.key;
    Node left = root.left;
    Node right = root.right;
    root = merge(left, right);
    return min;
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
  private void updateRank(Node x) {
    if(x == null) {
      return;
    }
    x.rank = 1 + Math.min(rank(x.left), rank(x.right));
  }
  private int rank(Node x) {
    return x == null ? -1 : x.rank;
  }
}
