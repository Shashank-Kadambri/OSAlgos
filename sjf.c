#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int main(void) {
	int at[MAX], bt[MAX], wt[MAX], tat[MAX];
	int* ready_queue;
	int sum_wait = 0, sum_tat = 0;
	int n, i, j, min, time, smallest = 0;

	printf("\nEnter no. of processes: ");
	scanf("%d", &n);
	ready_queue = malloc(sizeof(int) * n);
	for(i = 0; i < n; ++i) {
		printf("\nEnter arrival time for process P%d: ", i + 1);
		scanf("%d", &at[i]);
		printf("Enter burst time for process P%d: ", i + 1);
		scanf("%d", &bt[i]);
	}

	for(i = 0; i < n; ++i) {
		for(j = 0; j < n; ++j) {
			if(at[j] <= at[smallest])
				smallest = j;
		}
		// smallest has the index value of the process to be executed first, which has arrived first
		time += bt[smallest];
		tat[smallest] = time - at[smallest];
		wt[smallest] = tat[smallest] - bt[smallest];
		sum_tat += tat[smallest];
		sum_wait += wt[smallest];
		
	}
	return 0;
}