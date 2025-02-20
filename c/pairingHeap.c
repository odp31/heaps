#include <stdio.h>
#include <stdlib.h>

// strucutre for pairing heap node 
typedef struct Node {
  int key;
  struct Node* child;
  struct Node* sibling;
} Node;

// function to create new pairing heap node
Node* createNode(int key) {
  Node* node = (Node*)malloc(sizeof(Node));
  if(node == NULL) {
    return NULL;
  }
  node->key = key;
  node->child = NULL;
  node->sibling = NULL;
  return node;
}

//function to merge two pairing heaps 
Node* merge(Node* h1, Node* h2) {
  if(h1 == NULL) {
    return h2;
  }
  if(h2 == NULL) {
    return h1;
  }
  if(h1->key <= h2->key) {
    h2->sibling = h1->child;
    h1->child = h2;
    return h1;
  } else {
    h1->sibling = h2->child;
    h2->child = h1;
    return h2;
  }
}

// function to pairwise merge list of heaps
Node* pairwiseMerge(Node* heap) {
  if(heap == NULL || heap->sibling == NULL) {
    return heap;
  }
  Node* a = heap;
  Node* b = heap->sibling;
  Node* rest = b->sibling;

  a->sibling = NULL;
  b->sibling = NULL;

  return merge(merge(a,b), pairwiseMerge(rest));
}

//function to insert key into pairing heap
Node* insert(Node* root, int key) {
  Node* newNode = createNode(key);
  if(newNode == NULL) return root; 
  return merge(root, newNode);
}

// function to extract min from heap
Node* extractMin(Node** root) {
  if(*root == NULL) {
    return NULL;
  }
  Node* minNode = *root;
  *root = pairwiseMerge((*root)->child);

  return minNode;
}

// function to free pairing heap
void freePairingHeap(Node* root) {
  if(root!= NULL) {
    freePairingHeap(root->child);
    freePairingHeap(root->sibling);
    free(root);
  }
}
// function to print pairing heap
void printPairingHeap(Node* root) {
  if(root != NULL) {
    printf("%d ", root->key);
    printPairingHeap(root->child);
    printPairingHeap(root->sibling);
  }
}

int main() {
  Node* root = NULL;
  root = insert(root, 10);
  root = insert(root, 5);
  root = insert(root, 3);
  root = insert(root, 15);
  root = insert(root, 2);

  printf("pairing heap (preorder): ");
  printPairingHeap(root);
  printf("\n");

  Node* minNode = extractMin(&root);
  if(minNode != NULL) {
    printf("extracted min: %d\n", minNode->key);
    free(minNode);
  }
  printf("pairing heap after extractMin: ");
  printPairingHeap(root);
  printf("\n");

  freePairingHeap(root);

  return 0;
}


