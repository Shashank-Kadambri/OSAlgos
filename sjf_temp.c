/*
	arrival time is assumed to be 0 for all the processes
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
	int pid;
	int burst_time;
	struct Node* next;
};		// global object node

struct Node* head = NULL;
struct Node* tail = NULL;

void addProcessToList(int id, int bt) {
	struct Node* temp = malloc(sizeof(struct Node));
	temp -> pid = id;
	temp -> burst_time = bt;
	temp -> next = NULL;
	if(head == NULL) {
		head = tail = temp;
	} else {
		if(head -> burst_time > bt) {
			temp -> next = head;
			head = temp;
		} else if(tail -> burst_time < bt) {
			tail -> next = temp;
			tail = temp;
		} else {
			struct Node* ptr = head;
			// while((ptr -> next != NULL) && ((ptr -> burst_time) <= bt < (ptr -> next -> burst_time))) {

			// }
			while((ptr -> next != NULL) && (ptr -> next -> burst_time < bt)) {
				ptr = ptr -> next;
			}
			temp -> next = ptr -> next;
			ptr -> next = temp;
		}
	}
	return;
}

void display(void) {
	struct Node* temp = head;
	if(temp == NULL) {
		printf("\n*** No processes present in the ready queue ***\n");
	} else {
		printf("\nReady queue:\n");
		while(temp != NULL) {
			printf("P%d  ", temp -> pid);
			temp = temp -> next;
		}
	}
	return;
}

void startExecution(void) {
	struct Node* temp = head;
	struct Node* prev = head;
	int count = 0;
	int turnaround_time = 0; 
	float waiting_time = 0.0, total_waiting_time = 0.0;
	if(temp == NULL) {
		printf("\n*** No processes present in the ready queue ***\n");
	} else {
		// printf("\nReady queue:\n");
		while(temp != NULL) {
			prev = temp;
			printf("\n\nExecuting process P%d...\n", temp -> pid);
			printf("Burst time = %d\n", temp -> burst_time);
			turnaround_time += temp -> burst_time;
			waiting_time = (turnaround_time) - (prev -> burst_time);
			total_waiting_time += waiting_time;
			printf("Turn around time = %d\n", turnaround_time);
			printf("Waiting time = %0.2f\n", waiting_time);
			++count;
			temp = temp -> next;
			// if(temp == NULL) {
			// 	free(
			// 	head = tail = NULL;
			// } else {
			// 	free(prev);
			// }
		}
		printf("\n\nAverage waiting time = %0.2f", total_waiting_time / count);
	}
	return;
}

void destroyQueue(void) {
	struct Node* temp = head;
	struct Node* prev;
	while(temp != NULL) {
		prev = temp;
		temp = temp -> next;
		free(prev);
	}
	head = tail = NULL;
}

int main(void) {
	int choice, id, bt;
	do {
		printf("\t\t*** Shortest Job First ***\n\n\t\t");
		printf("1. Add a process\n\t\t");
		printf("2. View ready queue\n\t\t");
		printf("3. Start execution\n\t\t");
		printf("4. Exit\n\n");
		printf("Enter your choice : ");
		scanf("%d", &choice);
		switch(choice) {
			case 1 : {
				printf("\nEnter the process ID : ");
				scanf("%d", &id);
				printf("Enter burst time : ");
				scanf("%d", &bt);
				addProcessToList(id, bt);
			} break;

			case 2 : {
				display();
			} break;

			case 3 : {
				startExecution();
			} break;

			default : {
				if(choice != 4)
					printf("\nINVALID CHOICE!");
			}
		}
		printf("\n\n");
		for(int i = 0; i < 80; ++i) {
			printf("*");
		}
		// printf("\n\n%50c", '*');
		printf("\n\n\n");
	} while(choice != 4);
	destroyQueue();
	return 0;
}