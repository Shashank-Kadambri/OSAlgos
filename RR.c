#include <stdio.h>
#include <stdlib.h>

struct Node {
    int pid; // process id
    int burst_time; // burst time
    int waiting_time; // waiting time
    int turnaround_time; // don't know yet
    struct Node* next;
};

int time_slice = 1;
float avg_wt = 0, avg_ta = 0;   // these two are not being used anywhere
int count = 0;  // can make this local

struct Node* head = NULL;
struct Node* tail = NULL;

void addProcessToList(int id, int bt) {
    struct Node* p = malloc(sizeof(struct Node));
    p -> pid = id;
    p -> burst_time = bt;
    p -> waiting_time = 0;
    p -> turnaround_time = 0;
    ++count;
    if(tail == NULL) {
		tail = p;
		tail -> next = p;
    } else {
	    p -> next = tail -> next;
		tail -> next = p;
		tail = tail -> next;
	}
    return;
}

void display(void) {
    if(tail != NULL) {
        printf("\n** Ready queue **\n");
        struct Node* temp = tail -> next;
        do {
            printf("P%d ", temp -> pid);
            temp = temp -> next;
        } while(temp != tail -> next);
    } else {
        printf("\n** No processes present in ready queue\n");
    }
    return;
}

void startExecution(void) {
    if(tail != NULL) {
        int flag = 1;
        struct Node* curr = tail -> next;
        struct Node* prev = tail;
        printf("\nHERE\ntime_slice = %d", time_slice);
        while(flag) {
            if(curr -> burst_time > time_slice) {
                printf("P%d: running for %d bursts\n", curr -> pid, time_slice);
                curr -> turnaround_time += time_slice;   
                curr -> burst_time -= time_slice;
                curr = curr -> next;
                prev = prev -> next;
                
                /*Node *temp=curr;
                do{
                    temp->WT+=time_slice;
                    temp=temp->next;    
                }while(temp!=curr);*/

            } else {
                //printf("P%d: running for %d bursts\n",curr->ID,curr->BT);
                //printf("P%d terminated\nWaiting time= %d\nTurnaround time=%d\n",curr->ID,curr->WT/2,curr->WT+curr->TA);
                //Node *temp=curr;
                curr = curr -> next;
                prev -> next = curr;
                //free(temp);
                if(curr == curr -> next && curr -> burst_time <= time_slice) {
                    //printf("P%d: running for %d bursts\n",curr->ID,curr->BT);
                    tail = NULL;
                    flag = 0;
                }
            }
        }
    } else {
        printf("\n** No processes present in ready queue\n");
    }
    return;
}

int main(void) {
    int choice, id, bt;
    do{
        printf("\n\t\t**** Round-Robin Menu ****\n");
        printf("\t\t1. Add a process\n");
        printf("\t\t2. View ready queue\n");
        printf("\t\t3. Start execution\n");
        printf("\t\t4. Enter time slice (default = 1)\n");
        printf("\t\t5. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: printf("\nEnter process id: ");
                    scanf("%d", &id);
                    printf("Enter burst time: ");
                    scanf("%d", &bt);
                    addProcessToList(id, bt);
                    break;

            case 2: display();
                    break;

            case 3: startExecution();
                    break;

            case 4: printf("\nEnter time slice: ");
                    scanf("%d", &time_slice);
                    break;

            default: if(choice != 5)
                        printf("INVALID CHOICE!!\n");
        }
        printf("\n\n\n");
    } while(choice != 5);
    return 0;
}