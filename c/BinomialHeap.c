#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int key;
  struct Node* parent;
  struct Node* child;
  struct Node* sibling;
} Node;

typedef struct BinomialHeap {
  Node* head;
} BinomialHeap;

// function to create a new node
Node newNode(int key) {
  Node* node = (Node*)malloc(sizeof(Node));
  node->key = key;
  node->parent = node->child = node->sibling = NULL;
  return node;
}
// function to merge two binomial trees of same order
Node* mergeTrees(Node* a, Node* b) {
  if(a->key > b->key) {
    b->parent = a;
    a->child = b;
    return a;
  } else {
      a->parent = b;
      b->child = a;
      return b;
  }
}
// function to merge two binomial heaps
BinomialHeap* mergeHeaps(BinomialHeap* h1, BinomialHeap* h2) {
  Node* head1 = h1->head;
  Node* head2 = h2->head;
  Node* head = NULL;
  Node* prev = NULL;
  Node* next;

  while(head1 != NULL && head2 != NULL) {
    if(head1 -> degree < head2 -> degree) {
      next = head1;
      head1 = head1->sibling;
    } else {
        next = head2;
        head2 = head2->sibling;
    }
    if(prev == NULL) {
      head = next;
    } else {
        prev->sibling = next;
    }
    prev = next;
  }
  if(head1 != NULL) {
    prev->sibling = head1;
  } else if(head2 != NULL) {
      prev->sibling = head2;
  }
  h1->head = head;
  h2->head = NULL;
  return h1;
}
// ufnction to insert key into heap
void insertKey(BinomialHeap* heap, int key) {
  Node* node = newNode(key);
  BinomialHeap* newHeap = (BinomialHeap*)malloc(sizeof(BinomialHeap));
  newHeap->head = node;
  heap = mergeHeaps(heap, newHeap);
}
// function to extract minimum key from heap
int extractMin(BinomialHeap* heap) {
  if(heap->head == NULL) {
    return -1;
  }
  Node* minNode = heap->head;
  Node* prev = NULL;
  Node* next = heap->head;

  while(next != NULL) {
    if(next->key < minNode -> key) {
      minNode = next;
      prev = next;
    }
    next = next->sibling;
  }
  if(prev == NULL) {
    heap->head = minNode -> child;
  } else {
    prev-> sibling = minNode->child;
  }
  Node* child = minNode->child;
  while(child!= NULL) {
    child->parent = NULL;
    child = child->sibling;
  }
  BinomialHeap* newHeap = (BinomialHeap*)malloc(sizeof(BinomialHeap));
  newHeap->head = minNode->child;
  heap = mergeHeaps(heap, newHeap);
  return minNode->key;
}
