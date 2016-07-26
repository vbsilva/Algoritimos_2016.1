#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define swap(a, b) ((&(a) == &(b)) ? (a) : ((a)^=(b),(b)^=(a),(a)^=(b)))

int abs(int a) { return (a < 0) ? -a : a; }
int partition(int **, int, int);
void qsort2(int **, int, int);
void quicksort(int **, int);

static int *T;

int main()
{
	int M;
	scanf("%d", &M);
	int casos = 0;
	
	while (casos < M) {
		int N;
		scanf("%d", &N);
		int *V = (int *) malloc(sizeof(int) * N);
		int i;
		int K = 0;
		for (i = 0; i < N; i++) {
			scanf("%d", &V[i]);
			K += V[i];
		}
		T = (int *) malloc(sizeof(int) * (K + 1));
		memset(T, 0, sizeof(int) * (K + 1));
		quicksort(&V, N);
		int R = 0;

		T[0] = 1;
		
		int j;
		for (i = 0; i < N; i++) { 
			for (j = R; j >= 0; j--)
				if (T[j]) T[j + V[i]] = 1;	
			R = min((K/2),(R + V[i]));
		}

		int H0 = 0, H1 = 0;
		for (i = K/2; i >= 0; i--) {
			if (T[i] != 0) {
				H0 = i;
				H1 = K - H0;
				break;
			}
		}
		
		printf("caso %d: %d %d\n", casos, H0, H1);	
		casos++;
	}
	
	return 0;
}

int partition(int **V, int l, int r)
{
	int i = l, j = r;
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

void qsort2(int **V, int l, int r)
{
	if (r <= l)
		return;
	int p = partition(V, l, r);
	qsort2(V, l, p - 1);
	qsort2(V, p + 1, r);
}

void quicksort(int **V, int n)
{
	qsort2(V, 0, n - 1); 
}
