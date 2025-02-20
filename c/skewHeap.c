#include <stdio.h>
#include <stdlib.h>

// structure for skew heap node
typedef struct Node {
  int key;
  struct Node* left;
  struct Node* right;
} Node;

// function to create new skew heap node
Node* createNode(int key) {
  Node* node = (Node*)malloc(sizeof(Node));
  if(node == NULL) {
    return NULL;
  }
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  return node;
}

// function to merge 2 skew heaps
Node* merge(Node* h1, Node* h2) {
  if(h1 == NULL) {
    return h2;
  }
  if(h2 == NULL) {
    return h1;
  }
  if(h1->key > h2->key) {
    Node* temp = h1;
    h1 = h2;
    h2 = temp;
  }

  Node* temp = h1->left;
  h1->left = merge(h1->right, h2);
  h1->right = temp;

  return h1;
}

// function to insert a key into a skew heap
Node* insert(Node* root, int key) {
  Node* newNode = createNode(key);
  if(newNode == NULL) return root;
  return merge(root, newNode);
}

//function to extract minmum element from skew heap
Node* extractMin(Node** root) {
  if(*root == NULL) {
    return NULL;
  }
  Node* minNode = *root;
  *root = merge((*root)->left,(*root)->right);

  return minNode;
}

// function to free skew heap 
void freeSkewHeap(Node* root) {
  if(root != NULL) {
    freeSkewHeap(root->left);
    freeSkewHeap(root->right);
    free(root);
  }
}
// function to print skew heap
void printSkewHeap(Node* root) {
  if(root!= NULL) {
    printSkewHeap(root->left);
    printf("%d ", root->key);
    printSkewHeap(root->right);
  }
}


int main() {
  Node* root = NULL;

  root = insert(root, 10);
  root = insert(root, 5);
  root = insert(root, 3); 
  root = insert(root, 15);
  root = insert(root, 2);

  printf("skew heap (inorder): ");
  printSkewHeap(root);
  printf("\n");

  Node* minNode = extractMin(&root);
  if(minNode != NULL) {
    printf("extracted min: %d\n", minNode->key);
    free(minNode);
  }
  printf("skew heap after extractMin: ");
  printSkewHeap(root);
  printf("\n");

  freeSkewHeap(root);

  return 0;
}



