#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *array;
  int size;
  int capacity;
} Heap;

// function to initialize a heap
Heap* createHeap(int capacity) {
  Heap* heap = (Heap*)malloc(sizeof(Heap));
  heap->array = (int*)malloc(capacity* sizeof(int));
  heap->size = 0;
  heap->capacity = capacity;
  return heap;
}
// function to heapify a subtree rooted at index i 
void heapify(Heap* heap, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if(left < heap->size && heap->array[left] > heap->array[largest])
    largest = left;
  if(right < heap->size && heap->array[right] > heap->array[largest])
    largest = right;
  if(largest != i) {
    int temp = heap->array[i];
    heap->array[i] = heap->array[largest];
    heap->array[largest] = temp;
    heapify(heap, largest);
  }
}
// function to insert a key into heap
void insertKey(Heap* heap, int key) {
  if(heap->size == heap->capacity) {
    printf("overflow\n");
    return;
  }  
  heap->size++;
  heap->array[heap->size - 1] = key;

  // heapify inserted node up to maintain heap property
  for(int i = (heap->size - 1) / 2; i >= 0; i--) {
    heapify(heap, i);
  }
}
// function to extract root (max) element
int extractMax(Heap* heap) {
  if(heap->size == 0) {
    printf("underflow\n");
    return INT_MIN;
  }
  int root = heap->array[0];
  heap->array[0] = heap->array[heap->size - 1];
  heap->size--;

  heapify(heap, 0);
  return root;
}
// function to print contents of heap
void printArray(int arr[], int n) {
  for(int i = 0; i < n; ++i) {
    printf("%d ", arr[i]);
  printf("\n");
  }
