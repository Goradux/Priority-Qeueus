#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LCHILD(x) 2*x+1
#define RCHILD(x) 2*x+2
#define PARENT(x) (x-1)/2

typedef struct node {
  int data;
  int priority;
} node;

typedef struct minHeap {
  int size;
  node *elem;
} minHeap;

minHeap initMinHeap() {
  minHeap hp;
  hp.size = 0;
  return hp;
}

void insertNode(minHeap *hp, int data, int priority) {
  //allocating space
  if (hp->size) {
    hp->elem = realloc(hp->elem, (hp->size+1)*sizeof(node));
  } else {
    hp->elem = malloc(sizeof(node));
  }

  //initializing the node with value
  node nd;
  nd.data = data;
  nd.priority = priority;

  //positioning the node at the right position in the min heap
  int i = (hp->size)++;
  while(i && nd.priority < hp->elem[PARENT(i)].priority) {
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
  int smallest = (LCHILD(i) < hp-> size && hp->elem[LCHILD(i)].priority < hp->elem[i].priority) ? LCHILD(i) : i;
  if (RCHILD(i) < hp->size && hp->elem[RCHILD(i)].priority < hp->elem[smallest].priority) {
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

/*
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
*/

// example https://robin-thomas.github.io/min-heap/

void test() {
  clock_t start_t;
  clock_t end_t;
  clock_t total_t;

  int i;
  int size = 10000000;

  minHeap hp = initMinHeap();
  for (i = 0; i < size; i++) {
    insertNode(&hp, i, i);
  }
  printf("heap was built!\n");
  start_t = clock();
  //for (i = 1000; i > 0; i--) {
    insertNode(&hp, 0, 0);
  //}
  end_t = clock();
  total_t = (double)(end_t - start_t);
  printf("node inserted %ld\n", total_t);
}

int main() {
  test();
  return 0;
}
