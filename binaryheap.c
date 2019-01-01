#include <stdio.h>
#include <stdlib.h>

#define LCHILD(x) 2*x+1
#define RCHILD(x) 2*x+2
#define PARENT(x) (x-1)/2

typedef struct node {
  int data;
} node;

typedef struct minHeap {
  int size;
  node *elem;
} minHeap;

minHeap initMinHeap(int size) {
  minHeap hp;
  hp.size = 0;
  return hp;
}

void insertNode(minHeap *hp, int data) {
  //allocating space
  if (hp->size) {
    hp->elem = realloc(hp->elem, (hp->size+1)*sizeof(node));
  } else {
    hp->elem = malloc(sizeof(node));
  }

  //initializing the node with value
  node nd;
  nd.data = data;

  //positioning the node at the right position in the min heap
  int i = (hp->size)++;
  while(i && nd.data < hp->elem[PARENT(i)].data) {
    hp->elem[i] = hp->elem[PARENT(i)];
    i = PARENT(i);
  }
  hp->elem[i] = nd;
}

void swap(node *n1, node *n2) {
  node temp = *n1;
  *n1 = *n2;
  *n2 = temp;
}

void heapify(minHeap *hp, int i) {
  int smallest = (LCHILD(i) < hp-> size && hp->elem[LCHILD(i)].data < hp->elem[i].data) ? LCHILD(i) : i;
  if (RCHILD(i) < hp->size && hp->elem[RCHILD(i)].data < hp->elem[smallest].data) {
    smallest = RCHILD(i);
  }
  if (smallest != i) {
    swap(&(hp->elem[i]), &(hp->elem[smallest]));
    heapify(hp, smallest);
  }
}

void deleteNode(minHeap *hp) {
  if (hp->size) {
    printf("Deleting node %d\n\n", hp->elem[0].data);
    hp->elem[0] = hp->elem[--(hp->size)];
    hp->elem = realloc(hp->elem, hp->size*sizeof(node));
    heapify(hp, 0);
  } else {
    printf("\nMin Heap is empty!\n");
    free(hp->elem);
  }
}

void buildMinHeap(minHeap *hp, int *arr, int size) {
  int i;

  //Insertion into the heap without violating the shape property
  for (i = 0; i < size; i++) {
    if (hp->size) {
      hp->elem = realloc(hp->elem, (hp->size+1)*sizeof(node));
    } else {
      hp->elem = malloc(sizeof(node));
    }
    node nd;
    nd.data = arr[i];
    hp->elem[(hp->size)++] = nd;
  }

  //Making sure that heap property is also satisfied
  for (i = (hp->size-1)/2; i>=0; i--) {
    heapify(hp, i);
  }
}

// example https://robin-thomas.github.io/min-heap/

void test() {
  int i;
  int size = 10000;
  int arr[size];

  for (i = 0; i < size; i++) {
    arr[i] = i;
  }

  minHeap hp;
  buildMinHeap(&hp, arr, size);
  printf("heap was built!\n");
}

int main() {
  test();
  return 0;
}
