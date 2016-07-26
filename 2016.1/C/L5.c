#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *ec_malloc(unsigned int);

struct Node {
	int value;
	struct Node *next;
};

struct Queue {
	struct Node *head;
	struct Node *tail;
	int length;
	
	void (*push)(struct Queue *queue, int value);
	int (*pop)(struct Queue *queue);
};

struct Queue *init();
void push(struct Queue *, int);
int pop(struct Queue *);

int main()
{
	int caso = 0;
	int N;
	int S;
	int K;
	int V;

	int **AdjList;

	int i;
	int j;
	while (scanf("%d", &N) != EOF) {
		scanf("%d", &S);
			
		AdjList = (int **) ec_malloc(sizeof(int *) * N);

		for (i = 0; i < N; ++i) {
			scanf("%d", &K);
			AdjList[i] = (int *) ec_malloc(sizeof(int) * (K + 1 ));
			AdjList[i][K] = -1;
			for (j = 0; j < K; j++) {
				scanf("%d", &V);
				AdjList[i][j] = V;	
			}
		}

		if (caso != 0)
			printf("\n");
		printf("caso %d:", caso++);
		
		int *d = (int *) ec_malloc(sizeof(int) * N);
		int *quant = (int *) ec_malloc(sizeof(int) * N);
		memset(d, -1, sizeof(int) * N);
		memset(quant, 0, sizeof(int) * N);
		quant[0] = 1;
		int tmp = 0;

		struct Queue *queue = init();
		queue->push(queue, S);
		d[S] = 0;

		while (queue->length != 0) {
			int u = queue->pop(queue);
			for (j = 0; AdjList[u][j] != -1; j++) {
				int v = AdjList[u][j];
				if (d[v] == -1) {
					d[v] = d[u] + 1;
					quant[d[v]]++;
					queue->push(queue, v);
				}
			}
		}

		for (i = 0; i < N; i++) {
			if (quant[i] != 0) {
				tmp += quant[i];
				printf(" %d", tmp);
			} else {
				printf("\n");
				break;
			}
		}

		for (i = 0; i < N; ++i)
			free(AdjList[i]);
		free(AdjList);
		free(queue);
	}

	return 0;
}

void *ec_malloc(unsigned int size)
{
	void *ptr = malloc(size);
	if (!ptr) {
		fprintf(stderr, "[!!!] Malloc Failed! [!!!]\n");
		exit(-1);
	}

	return ptr;
}

struct Queue *init()
{
	struct Queue *tmp = (struct Queue *) ec_malloc(sizeof(struct Queue));
	tmp->head = (struct Node *) ec_malloc(sizeof(struct Node));
	tmp->tail = (struct Node *) ec_malloc(sizeof(struct Node));
	tmp->head->next = tmp->tail->next = NULL;
	tmp->length = 0;

	tmp->push = push;
	tmp->pop = pop;

	return tmp;
}

void push(struct Queue *queue, int value)
{	
	struct Node *tmp = (struct Node *) ec_malloc(sizeof(struct Node));
	tmp->value = value;
	tmp->next = NULL;

	if (queue->head->next == NULL)
		queue->head->next = queue->tail->next = tmp;
	else {
		queue->tail->next->next = tmp;
		queue->tail->next = tmp;
	}

	queue->length++;
}

int pop(struct Queue *queue)
{
	struct Node *tmp;
	if (queue->head->next == NULL)
		return 0;
	else {
		tmp = queue->head->next;	
		if (tmp->next == NULL) {
			queue->tail->next = queue->head->next;
			queue->head->next  = NULL;
		} else {
			queue->head->next = tmp->next;
		}
		queue->length--;
	}
	int value = tmp->value;
	free(tmp);
	return value;
}
