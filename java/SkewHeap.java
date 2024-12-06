// heap ordered tree with no specific structural constraints 

public class SkewHeap{
  private Node root;
  private static class Node {
    int key;
    Node left, right;
    Node(int key) {
      this.key = key;
    }
  }
  public void insert(int key) {
    root = merge(root, new Node(key));
  }
  public int extractMin() {
    if(root == null) {
      throw new IllegalStateException("heap is empty");
    }
    int min = root.key;
    root = merge(root.left, root.right);
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
}
