#include <stdio.h>
#include <stdlib.h>

// structure for leftist heap node 
typedef struct Node {
  int key;
  struct Node* left;
  struct Node* right;
  int s;    // shortest path length
} Node;

// function to create new leftist heap node
Node* createNode(int key) {
  Node* node = (Node*)malloc(sizeof(Node));
  if(node == NULL) {
    return NULL;
  }
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->s = 1;
  return node;
}

// function to get s value of node
int sValue(Node* node) {
  if(node == NULL) {
    return 0;
  }
  return node->s;
}

// function to swap left and right children of node
void swapChildren(Node* node) {
  Node* temp = node->left;
  node->left = node->right;
  node->right = temp;
}

// function to merge two leftist heaps
Node* merge(Node* h1, Node* h2) {
  if(h1 == NULL) {
    return h2;
  }
  if(h2 = NULL) {
    return h1;
  }
  if(h1->key > h2->key) {
    Node* temp = h1;
    h1 = h2;
    h2 = temp;
  }
  h1->right = merge(h1->right, h2);
  if(sValue(h1->left) < sValue(h1->right)) {
    swapChildren(h1);
  }
  h1->s = sValue(h1->right) + 1;
  return h1;
}

// function to insert key into leftist heap
Node* insert(Node* root, int key) {
  Node* newNode = createNode(key);
  if(newNode == NULL) return root;
  return merge(root,newNode);
}

// function to extract min from leftist heap
Node* extractMin(Node** root) {
  if(*root == NULL) {
    return NULL;
  }
  Node* minNode = *root;
  *root = merge((*root)->left, (*root)->right);
  return minNode;
}

//functin to free leftist heap
void freeLeftistHeap(Node* root) {
  if(root != NULL) {
    freeLeftistHeap(root->left);
    freeLeftistHeap(root->right);
    free(root);
  }
}

// function to print leftist heap 
void printLeftistHeap(Node* root) {
  if(root != NULL) {
    printLeftistHeap(root->left);
    printf("%d ", root->key);
    printLeftistHeap(root->right);
  }
}

int main() {
  Node* root = NULL;
  root = insert(root, 10);
  root = insert(root, 5);
  root = insert(root, 3);
  root = insert(root, 15);
  root = insert(root, 2);

  printf("leftist heap (iniorder: ");
  printLeftistHeap(root);
  printf("\n");

  Node* minNode = extractMin(&root);
  if(minNode != NULL) {
    printf("extracted min: %d\n", minNode->key);
    free(minNode);
  }
  printf("leftist heap after extractMin: ");
  printleftistHeap(root);
  printf("\n");

  freeLeftistHeap(root);

  return 0; 

}
