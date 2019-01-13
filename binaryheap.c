#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEFTCHILD(x) 2*x+1
#define RIGHTCHILD(x) 2*x+2
#define PARENT(x) (x-1)/2

typedef struct node {
  int data;
  int priority;
} node;

typedef struct minHeap {
  int size;
  node *element;
} minHeap;

minHeap initMinHeap() {
  minHeap hp;
  hp.size = 0;
  return hp;
}

void insertNode(minHeap *hp, int data, int priority) {
  //allocating space
  if (hp->size) {
    hp->element = realloc(hp->element, (hp->size+1)*sizeof(node));
  } else {
    hp->element = malloc(sizeof(node));
  }

  //initializing the node with value
  node nd;
  nd.data = data;
  nd.priority = priority;

  //positioning the node at the right position in the min heap
  int i = (hp->size)++;
  while(i && nd.priority < hp->element[PARENT(i)].priority) {
    hp->element[i] = hp->element[PARENT(i)];
    i = PARENT(i);
  }
  hp->element[i] = nd;
}

void swap(node *n1, node *n2) {
  node temp = *n1;
  *n1 = *n2;
  *n2 = temp;
}

void heapify(minHeap *hp, int i) {
  int smallest = (LEFTCHILD(i) < hp-> size && hp->element[LEFTCHILD(i)].priority < hp->element[i].priority) ? LEFTCHILD(i) : i;
  if (RIGHTCHILD(i) < hp->size && hp->element[RIGHTCHILD(i)].priority < hp->element[smallest].priority) {
    smallest = RIGHTCHILD(i);
  }
  if (smallest != i) {
    swap(&(hp->element[i]), &(hp->element[smallest]));
    heapify(hp, smallest);
  }
}

void deleteNode(minHeap *hp) {
  if (hp->size) {
    hp->element[0] = hp->element[--(hp->size)];
    hp->element = realloc(hp->element, hp->size*sizeof(node));
    heapify(hp, 0);
  } else {
    printf("\nMin Heap is empty!\n");
    free(hp->element);
  }
}

//insert at the head of the heap
void insertWorst(int input) {
  clock_t start_t;
  clock_t end_t;
  clock_t total_t;

  int i;
  int size = input;

  minHeap hp = initMinHeap();
  for (i = 0; i < size; i++) {
    insertNode(&hp, i, i);
  }
  printf("Worst case\n");
  start_t = clock();
  for (i = 0; i < 500; i++) {
    insertNode(&hp, 0, -1 - i);
  }
  end_t = clock();
  total_t = (double)(end_t - start_t);
  printf("Clock ticks taken: %ld\n", total_t);
}

//insert at the end of the heap
void insertBest(int input) {
  clock_t start_t;
  clock_t end_t;
  clock_t total_t;

  int i;
  int size = input;

  minHeap hp = initMinHeap();
  for (i = 0; i < size; i++) {
    insertNode(&hp, i, i);
  }
  printf("best case\n");
  start_t = clock();
  for (i = 0; i < 500; i++) {
    insertNode(&hp, 0, input + 1 + i);
  }
  end_t = clock();
  total_t = (double)(end_t - start_t);
  printf("Clock ticks taken: %ld\n", total_t);
}

void insertAverage(int input) {

  srand(time(NULL));

  clock_t start_t;
  clock_t end_t;
  clock_t total_t;

  int i;
  int size = input;

  minHeap hp = initMinHeap();
  for (i = 0; i < size; i++) {
    insertNode(&hp, i, i);
  }
  printf("Average case\n");
  start_t = clock();
  for (i = 0; i < 500; i++) {
    insertNode(&hp, 0, rand()%size);
  }
  end_t = clock();
  total_t = (double)(end_t - start_t);
  printf("Clock ticks taken: %ld\n", total_t);
}


void testDelete(int input) {
  clock_t start_t;
  clock_t end_t;
  clock_t total_t;

  int i;
  int size = input;

  minHeap hp = initMinHeap();
  for (i = 0; i < size; i++) {
    insertNode(&hp, i, i);
  }
  printf("Delete case\n");
  start_t = clock();
  for (i = 0; i < 500; i++) {
    deleteNode(&hp);
  }
  end_t = clock();
  total_t = (double)(end_t - start_t);
  printf("Clock ticks taken: %ld\n", total_t);
}

void testInsert(int size) {
  printf("Testing insert for %d\n", size);
  insertBest(size);
  insertAverage(size);
  insertWorst(size);
  printf("-------------\n");
}

int main() {
  int queueSize = 1000000;
  testInsert(queueSize);
  testDelete(queueSize);
  printf("\n");
  return 0;
}
