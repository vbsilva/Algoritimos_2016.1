#include <stdio.h>
#include <stdlib.h>

#define swap(a, b) ((&(a) == &(b)) ? (a) : ((a)^=(b),(b)^=(a),(a)^=(b)))
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

long int partition(long int **, long int, long int);
void qsort2(long int **, long int, long int);
void quicksort(long int **, long int);

long int binary_search(long int **, long int, long int);

int main()
{
	long int N, M, P, K, A;
	int caso = 0;

	while (scanf("%ld %ld %ld %ld %ld", &N, &M, &K, &P, &A) != EOF) {
		long int i, j;
		long int *bolas = (long int *) malloc(sizeof(*bolas) * N);		
		for (i = 0; i < N; ++i) {
			bolas[i] = 0;
			scanf("%ld", &bolas[i]);
		}
		quicksort(&bolas, N);

		long int **jogador = (long int **) malloc(P * sizeof(long int *));
		long int *score = (long int *) malloc(sizeof(*score) * P);
		for (i = 0; i < P; ++i) {
			jogador[i] = (long int *) malloc(K * sizeof(long int));
		}

		printf("caso %d:", caso++);
		for (i = 0; i < P; ++i) {
			score[i] = 0;
			for (j = 0; j < K; ++j) {
				jogador[i][j] = 0;
				scanf("%ld", (&jogador[i][j]));
				score[i] += binary_search(&bolas, N, jogador[i][j]);
			}
			if (score[i] == A)
				printf(" %ld", i);
		}
		printf("\n\n");
		for (i = 0; i < P; ++i)
			free(jogador[i]);
		free(jogador);
		free(bolas);
		free(score);
	}

	return 0;
}

long int partition(long int **V, long int l, long int r)
{
	long int i = l, j = r;
	long int m = ((l + r) / 2);
	long int p = max(min(l, m), min(max(l, m), r)); 
	if (p == r)
		swap((*V)[l], (*V)[r]);
	else if (p == m)
		swap((*V)[l], (*V)[m]);

	while (i < j) {
		while (i <= r && (*V)[i] <= (*V)[l]) {
			i++;
		}
		while ((*V)[l] < (*V)[j]) {
			j--;
		}
		if (i < j)
			swap((*V)[i], (*V)[j]);
	}
	swap((*V)[l], (*V)[j]);

	return j;
}

void qsort2(long int **V, long int l, long int r)
{
	if (r <= l)
		return;
	long int p = partition(V, l, r);
	qsort2(V, l, p - 1);
	qsort2(V, p + 1, r);
}

void quicksort(long int **V, long int n)
{
	qsort2(V, 0, n - 1); 
}

long int binary_search(long int **A, long int n, long int K)
{
	long int l = 0;
	long int r = n - 1;
	while (l <= r) {
		long int m = (l + r) / 2;
		if (K == (*A)[m])
			return m;
		else if (K < (*A)[m])
			r = m - 1;
		else
			l = m + 1;
	}

	return -1;
}

