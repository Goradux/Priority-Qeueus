#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int data;
	double priority;
	struct node* next;
} Node;

Node* newNode(int dataNew, double priorityNew) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = dataNew;
	temp->priority = priorityNew;
	temp->next = NULL;

	return temp;
}

// value of the highest priority element
int headValue(Node** head) {
	return (*head)->data;
}

void deleteMax(Node** head) {
	Node* temp = *head;
	(*head) = (*head)->next;
	free(temp);
}

void insert(Node** head, int dataNew, double priorityNew) {
	Node* start = (*head);

	// new Node
	Node* temp = newNode(dataNew, priorityNew);

	// shortcut case
	// if new priority is higher than heads,
	// insert new head
	if ((*head)->priority > priorityNew) {
		// Insert new Node before head
		temp->next = *head;
		(*head) = temp;
	}
	else {
		// Traverse the list and find a
		// position to insert new node
		while (start->next != NULL && start->next->priority < priorityNew) {
			start = start->next;
		}
		// here we are at the right position
		temp->next = start->next;
		start->next = temp;
	}
}

int isEmpty(Node** head) {
	return (*head) == NULL;
}

int main(){
	//struct Node first;
	//first.value = 10;
	//first.priority = 11;

	clock_t start_t;
	clock_t end_t;
	clock_t total_t;

	long counter;

	start_t = clock();
	Node* pq = newNode(4,1);
	for (counter = 0; counter <= 10000; counter++) {
		double clockV = clock();
		insert(&pq, clockV, clockV);
	}
	//insert(&pq, 5, 2);
	//insert(&pq, 6, 3);
	//insert(&pq, 7, 0);
	end_t = clock();
	total_t = (double)(end_t - start_t);

	while (!isEmpty(&pq)) {
		printf("%d ", headValue(&pq));
		deleteMax(&pq);
	}

	printf("Total time taken by CPU: %ld\n", total_t  );

	//int integer = 0;
	//printf("check this number %d\n", integer);
	return 0;
}
