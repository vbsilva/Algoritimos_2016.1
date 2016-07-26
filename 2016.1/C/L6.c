#include <stdio.h>
#include <stdlib.h>

#define INF (1 << 30)
#define swap(a,b,T) do { T tmp = a; a = b; b = tmp; } while(0);

struct Edge {
	int value;
	int weight;
};

//Heap functions
void pq_init(int);
int pq_empty();
void pq_insert(struct Edge *);
struct Edge *pq_del_min();
void pq_double();
void fix_up(int);
void fix_down(int);

void *ec_malloc(unsigned int);

int find_area(int *, long *, long *, int, long, int);

static struct Edge *heap;
static int heap_size;
static int *heap_pos;

int main()
{
	int V;
	int DR;
	int caso = 0;

	while (scanf("%d %d", &V, &DR) != EOF) {
		struct Edge **AdjList = (struct Edge **) ec_malloc(sizeof(struct Edge *) * V);
		int i;
		int j;
		int *D = (int *) ec_malloc(sizeof(int) * V);
		for (i = 0; i < V; ++i) {
			scanf("%d", &D[i]);
			AdjList[i] = (struct Edge *) ec_malloc(sizeof(struct Edge) * D[i]);		
			int R;
			int B;
			for (j = 0; j < D[i]; ++j) {
				scanf("%d %d", &R, &B);
				AdjList[i][j].value = R;
				AdjList[i][j].weight = ((1<<20) / B);
			}
		}

		int M;
		scanf("%d", &M);

		if (caso != 0)
			printf("\n");
		printf("caso %d:\n", caso++);

		int k = 0;
		int *S, *T;
		long *Z;
		S = (int *) ec_malloc(sizeof(int) * M);
		T = (int *) ec_malloc(sizeof(int) * M);
		Z = (long *) ec_malloc(sizeof(long) * M);
		for (k = 0; k < M; ++k) {
			scanf("%d %d %ld", &S[k], &T[k], &Z[k]);
		}

		int size = V;
		pq_init(size);

		int *dist = (int *) ec_malloc(sizeof(int) * V);
		int *p = (int *) ec_malloc(sizeof(int) * V);
		long *c = (long *) ec_malloc(sizeof(long) * V);
		heap_pos = (int *) ec_malloc(sizeof(int) * V);
		for (i = 0; i < V; ++i) {
			dist[i] = INF;
			p[i] = i;
			c[i] = 0;
			heap_pos[i] = 0;
		}

		long delay = 0;
		int area = 0;

		dist[DR] = 0;

		struct Edge *tmp = (struct Edge *) ec_malloc(sizeof(struct Edge));
		tmp->value = DR;
		tmp->weight = 0;
		pq_insert(tmp);

		while (!pq_empty()) {
			struct Edge *front = pq_del_min();
			int d = front->weight;
			int u = front->value;
			if (d > dist[u])
				continue;
			for (j = 0; j < D[u]; j++) {
				struct Edge *v = &AdjList[u][j];
				if (dist[u] + v->weight <= dist[v->value]) {
					if (dist[u] + v->weight == dist[v->value]) {
						//Find precursor
						int pre_u = u;
						int pre_v = p[v->value];
						while (pre_u == pre_v && pre_v != DR) {
							pre_u = p[pre_u];
							pre_v = p[pre_v]; 
						}
						if (pre_u < pre_v) {
							p[v->value] = u;
							c[v->value] = v->weight;				

							tmp->value = v->value;
							tmp->weight = dist[v->value];
							pq_insert(tmp);
						}
					} else {
						dist[v->value] = dist[u] + v->weight;
						p[v->value] = u;
						c[v->value] = v->weight;				

						tmp->value = v->value;
						tmp->weight = dist[v->value];
						pq_insert(tmp);
					}
				}
			}
		}
		for (k = 0; k < M; ++k) {
			delay = 0;
			area = find_area(p, c, &delay, S[k], Z[k], T[k]);
			area += find_area(p, c, &delay, T[k], Z[k], S[k]) - 1;
			printf("%d %ld\n", area, delay);
		}
	}
	return 0;
}


void pq_init(int maxN)
{
	heap = (struct Edge *) ec_malloc(sizeof(struct Edge) * (maxN + 1));
	heap_size = 0;
}

int pq_empty()
{
	return heap_size == 0;
}

void pq_insert(struct Edge *v)
{
	int i = heap_pos[v->value];
	if (i != 0) {
		heap[i] = *v;
		fix_up(i);
	} else {
		heap[++heap_size] = *v;
		heap_pos[v->value] = heap_size;
		fix_up(heap_size);
	}
}

struct Edge *pq_del_min()
{
	swap(heap_pos[heap[1].value], heap_pos[heap[heap_size].value], int);
	swap(heap[1], heap[heap_size], struct Edge);
	fix_down(1);
	return &heap[heap_size--];
}

void pq_double()
{
	heap = (struct Edge *) realloc(heap, heap_size * 2 * sizeof(struct Edge));
}

void fix_up(int k)
{
	while (k > 1 && heap[k/2].weight > heap[k].weight) {
		swap(heap_pos[heap[k].value], heap_pos[heap[k/2].value], int);
		swap(heap[k], heap[k/2], struct Edge);
		k = k / 2;
	}
}

void fix_down(int k)
{
	int j;
	while (2 * k <= (heap_size - 1)) {
		j = 2 * k;
		if (j < (heap_size - 1) && heap[j].weight > heap[j+1].weight)
			j++;
		if (!(heap[k].weight > heap[j].weight))
			break;
		swap(heap_pos[heap[k].value], heap_pos[heap[j].value], int);
		swap(heap[k], heap[j], struct Edge);
		k = j;
	}
}

int find_area(int *p, long *c, long *delay, int i, long Z, int W)
{
	int j = 0;
	
	while (p[i] != i) {
		j++;
		*delay += ((c[i] * Z) / (1 << 20));
		i = p[i];
	}
	return j;
}

void *ec_malloc(unsigned int size)
{
	void *ptr = malloc(size);
	if (!ptr) {
		fprintf(stderr, "[!!!] MALLOC FAILED [!!!]\n");
		exit(-1);
	}
	return ptr;
}

