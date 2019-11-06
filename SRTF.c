#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct Node {
	int id;
	int bt;
} process;

int main(void) {
	struct Node tmp, p[MAX];
	int n, i, j, tbt, t, bt;

	printf("\nEnter no. of processes: ");
	scanf("%d", &n);

	i = tbt = 0;
	while(i < n) {
		printf("\n\nFor process P%d\n", i + 1);
		printf("Enter burst time: ");	
		scanf("%d", &bt);
		tbt += bt;
		p[i].id = i + 1;
		p[i].bt = bt;
		++i;		
	}
    
	i = 0, j = i + 1;
	while(i < n) {
		while(j < n) {
			if(p[i].bt > p[j].bt) {
				tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
			++j;
		}
		++i;
		j = i + 1;
	}

	printf("\n\nTime\t\tProcess\n");
	t = i = bt = 0;
	j = i + 1;
	while(t < tbt) {	
		printf("%d\t\t\t%d\n", t + 1, p[bt].id);
		--p[bt].bt;
		// printf("\n");
		if(p[bt].bt == 0)
			++bt;
		i = bt;
		j = bt + 1;
		while(i < n) {
			while(j < n) {
				if(p[i].bt > p[j].bt) {
					tmp = p[i];
					p[i] = p[j];
					p[j] = tmp;
				}
				++j;
			}
			++i;
			j = i + 1;
		}
		++t;
	}
	return 0;
}