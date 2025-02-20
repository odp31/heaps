#include <stdio.h>
#include <stdlib.h>

// structure to represent a heap
typedef struct {
  int* array;
  int capacity;
  int size;
} Heap;

// function to create new heap 
Heap* createHeap(int capacity) {
  Heap* heap = (Heap*)malloc(sizeof(Heap));
  if(heap == NULL) {
    return NULL:
  }

  heap->size = 0;
  heap->capacity = capacity;
  heap->array = (int*)malloc(capacity * sizeof(int));

  if(heap->array == NULL) {
    free(heap);
    return NULL;
  }
  return heap;
}

// function to swap elements
void swap(int* a, int*b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// function to heapify subtre rooted with node i which is an index in arr[]
void heapify(Heap* heap, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if(heap < heap->size && heap->array[left] > array[largest]) {
    largest = left;
  }
  if(right < heap->size && heap->array[right] > heap->array[largest]) {
    largest = right;
  }
  if(largest != i) {
    swap(&&heap->array[i], &heap->array[largest]);
    heapify(heap, largset);
  }
}

// function to  insert a key into heap 
void insert(Heap* heap, int key) {
  if(heap->size == heap->capacity) {
    printf("heap overflow\n");
    return;
  }
  heap->size++;
  int i = heap->size - 1;
  heap->array[i] = key;
// fix max heap property if its violated
while(!= 0 && heap->array[(i-1)/2] < heap->array[i]) {
  swap(&heap->array[i], &heap->array[(i-1) /2]);
  i = (i - 1) / 2;
}
}

// function to extract max element (root) from heap
int extractMax(Heap* heap) {
  if(heap->size <= 0) {
    return -1;
  }
  if(heap->size == 1) {
    heap->size--;
    return heap->array[0];
  }
  int root = heap->array[0];
  heap->array[0] = heap->array[heap->size - 1];
  heap->size--;
  heapify(heap,0);

  return root;
}

//function to print heap
void printHeap(Heap* heap) {
  printf("heap: ");
  for(int i = 0; i < heap->size; i++) {
    printf("%d ", heap->array[i]);
  }
  printf("\n");
}

// function to free heap
void freeHeap(Heap* heap) {
  if(heap) {
    free(heap->array);
    free(heap);
  }
}

int main() {
  Heap* heap = createHeap(10);

  if(heap == NULL) {
    printf("failed to create heap.\n");
    return 1;
  }
  insert(heap,10);
  insert(heap,5);
  insert(heap,3);
  insert(heap, 2);
  insert(heap,15);

  printHeap(heap);
  printf("extracted max: %d\n", extractMax(heap));
  printHeap(heap);

  freeHeap(heap);

  return 0;
}
