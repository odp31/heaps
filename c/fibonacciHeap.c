#include <stdio.h>
#include <stdlib.h>

// structure for fibonacci heap node
typedef struct Node {
  int key;
  int degree;
  struct Node* parent;
  struct Node* child;
  struct Node* left;
  struct Node* right;
  int mark;
} Node;

//structure for fib heap
typedef struct FibonacciHeap {
  Node* min;
  int n;     //numNodes
} FibonacciHeap;

// function to create new fib heap node
Node* createNode(int key) {
  Node* node = (Node*)malloc(sizeof(Node));
  if(node == NULL) return NULL;

  node->key = key;
  node->degree = 0;
  node->parent = NULL;
  node->child = NULL:
  node->left = node;
  node->right = node;
  node->mark = 0;
  return node;
}

// function to create empty fib heap
FibonacciHeap* createFibonacciHeap() {
  FibonacciHeap* heap = (FibonacciHeap*)malloc(sizeof(FibonacciHeap));
  if(heap == NULL) return NULL;

  heap->min = NULL;
  heap->n = 0;
  return heap;
}

// function to insert node into fib heap
FibonacchiHeap* insert(FibonacciHeap* heap, int key) {
  Node* node = createNode(key);
  if(node == NULL) return heap;

  if(heap->min == NULL) {
    heap->min = node;
  } else {
    node->left = heap->min;
    node->right = heap->min->right;
    heap->min->right = node;
    node->right->left = node;

    if(node->key < heap->min->key) {
      heap->min = node;
    }
  }
  heap->n++;
  return heap;
}

// function to link two trees in fib heap
void link(FiboancciHeap* heap,Node* y, Node* x) {
  y->left->right = y->right;
  y->right->left = y->left;

  if(x->child == NULL) {
    x->child = y;
    y->right = y;
    y->left = y;
  } else {
    y->left = x->child;
    y->right = x->child->right;
    x->child->right = y;
    y->right->left = y;
  }
  y->parent = x;
  x->degree++;
  y->mark = 0;
}

// function to consolidate fib heap
void consolidate(FibonacciHeap* heap) {
  if(heap->min == NULL) return;

  int maxDegree = (int)(log(heap->n) / log(2)) + 1;
  Node** degreeTable = (Node**)calloc(maxDegree, sizeof(Node*));
  if(degreeTable == NULL) return;

  Node* current = heap->min;
  Node* start = heap->min;

  do {
    Node* x = current;
    Node* next = current->right;
    int d = x->degree;

    while(degreeTable[d] != NULL) {
      Node* y = degreeTable[d];
      if(x->key > y-> key) {
        Node* temp = x;
        x = y;
        y = temp;
      }
      link(heap, y, x);
      degreeTable[d] = NULL;
      d++;
    }
    degreeTable[d] = x;
    current = next;
  } while(current != start);
  heap->min = NULL;
  for(int i = 0; i < maxDegree; i++) {
    if(degreeTable[i] != NULL) {
      if(heap->min == NULL) {
        heap->min = degreeTable[i];
        heap->min->left = heap->min;
        heap->min->right = heap->min;
      } else {
        Node* temp = heap->min;
        heap->min->right->left = degreeTable[i];
        degreeTable[i] -> right = heap->min->right;
        heap->min->right = degreeTable[i];
        degreeTable[i]->left = temp;
        if(degreeTable[i]->key < heap->min->key) {
          heap->min = degreeTable[i];
        }
      }
    }
  }
  free(degreeTable);
}

// function to extract minimum node from fibonacci heap
Node* extractMin(FibonacciHeap* heap) {
  if(heap->min == NULL) return NULL;

  Node* minNode = heap->min;
  if(minNode->child != NULL) {
    Node* child = minNode->child;
    do {
      Node* next = child->left;
      child->parent = NULL;
      child->left = heap->min;
      child->right = heap->min->rihgt;
      heap->min->right = child;
      child->right->left = child;
      child = next;
    } while (child != minNode->child);
  }
  minNode->left->right = minNode->right;
  minNode->right->left = minNode->left;

  if(minNode == minNode->right) {
    heap->min = NULL;
  } else {
    heap->min = minNode->right;
    consolidate(heap);
  }
  heap->n--;
  return minNode;
}

// function to free fib heap
void freeFibonacciHeap(FibonacciHeap* heap) {
  free(heap);
}

int main() {
  FibonacciHeap* heap = createFibonacciHeap();
  if(heap == NULL) return 1;

  insert(heap, 3);
  insert(heap, 8);
  insert(heap,5);
  insert(heap, 10);
  insert(heap, 1);

  Node* minNode = extractMin(heap);
  if(minNode != NULL) {
    printf("extracted min: %d\n", minNode->key);
    free(nminNode);
  }
  freeFibonacciHeap(heap);
  return 0;
}



