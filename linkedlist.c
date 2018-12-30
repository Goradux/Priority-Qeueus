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

	/*
	if ((*head)->priority > priorityNew) {
		// Insert new Node before head
		temp->next = *head;
		(*head) = temp;
	}
	else { */
		// Traverse the list and find a
		// position to insert new node
							// "<=" ensures FIFO
		while (start->next != NULL && start->next->priority <= priorityNew) {
			start = start->next;
		}
		// here we are at the right position
		temp->next = start->next;
		start->next = temp;
	//}
}

int isEmpty(Node** head) {
	return (*head) == NULL;
}

void insertBest(long size) {
	clock_t start_t;
	clock_t end_t;
	clock_t total_t;
	long counter;

	double clockNumbers[size];
	for (int i = 0; i <= size; i++){
		clockNumbers[i] = clock();
		//printf("%lf ",randomNumbers[i]);
	}

	Node* pq = newNode(0, clock()-start_t);
	for (counter = 0; counter <= size; counter++) {
		//double clockV = clock()-start_t;
		insert(&pq, counter, (-1)*clockNumbers[counter]);
	}

	start_t = clock();
	insert(&pq, -1, -100000000);
	end_t = clock();
	total_t = (double)(end_t - start_t);

	printf("Best case, insert\n");
	printf("Total CPU clocks to queue up %ld elements: %ld\n", size, total_t  );
	return;
}

void insertWorst(long size) {
	clock_t start_t;
	clock_t end_t;
	clock_t total_t;
	long counter;

	double randomNumbers[size];
	for (int i = 0; i <= size; i++){
		randomNumbers[i] = clock();
		//printf("%lf ",randomNumbers[i]);
	}


	Node* pq = newNode(0, clock()-start_t);
	for (counter = 0; counter <= size; counter++) {
		//double clockV = clock()-start_t;
		insert(&pq, counter, (-1)*randomNumbers[counter]);
	}
	start_t = clock();
	insert(&pq, counter, clock());
	end_t = clock();

	total_t = (double)(end_t - start_t);

	printf("Worst case, insert\n");
	printf("Total CPU clocks to queue up %ld elements: %ld\n", size, total_t  );
	return;
}

void insertAverage(long size){
	//time_t t;
	srand(time(NULL));

	clock_t start_t;
	clock_t end_t;
	clock_t total_t;
	long counter;

	double randomNumbers[size];
	for (int i = 0; i <= size; i++){
		randomNumbers[i] = i%500;
		//printf("%lf ",randomNumbers[i]);
	}
	//printf("\n" );

	//printf("%ld\n", start_t);

	Node* pq = newNode(0, rand()%500);
	for (counter = 0; counter <= size; counter++) {
		insert(&pq, counter, size-counter);
	}
	start_t = clock();
	insert(&pq, counter, rand()%size);
	end_t = clock();
	//printf("%ld\n", end_t);

	total_t = (double)(end_t - start_t);

	printf("Average case, insert\n");
	printf("Total CPU clocks to queue up %ld elements: %ld\n", size, total_t  );
	return;
}

void testInsert(long size) {

	insertBest(size);
	insertAverage(size);
	insertWorst(size);

	return;
}

void testDeleteMax(long size){
	clock_t start_t;
	clock_t end_t;
	clock_t total_t;
	long counter;

	Node* pq = newNode(0, clock()-start_t);
	for (counter = 0; counter <= size; counter++) {
		double clockV = clock()-start_t;
		insert(&pq, counter, -clockV);
	}

	start_t = clock();
	//while (!isEmpty(&pq)) {
		deleteMax(&pq);
	//}
	end_t = clock();
	total_t = (double)(end_t - start_t);

	printf("Any case, deleteMax\n");
	printf("Total CPU clocks to delete %ld elements: %ld\n", size, total_t  );
	return;
}

int main(){
	testInsert(1000);
	printf("\n" );
	testInsert(10000);
	printf("\n" );
	testInsert(100000);
	printf("\n" );
	testInsert(1000000);

	//printf("-------\n");
	//printf("-------\n");
	//printf("-------\n");
	//testDeleteMax(10000);
	//testDeleteMax(100000);
	//testDeleteMax(1000000);

	return 0;
}
