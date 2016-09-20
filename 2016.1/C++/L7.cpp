#include <cstdio>

int backtrack(int *, int, int, int, int, int);

static int length = 0;

int main()
{
	int K;
	int casos = 0;
	int L;
	scanf("%d", &K);
	
	while (casos < K) {
		scanf("%d", &L);
		int p[L];
		length = L;

		int M, Q;
		for (int i = 0; i < L; i++) {
			scanf("%d", &p[i]);
		}
		scanf("%d %d", &M, &Q);

		int tmp = backtrack(p, Q, 0, 0, M, 0);
		printf("caso %d: %d\n", casos++, tmp);
	}
	return 0;
}

int backtrack(int *A, int Q, int i, int p, int M, int qtd)
{
	if (p > Q || qtd + (length - qtd) < M)
		return 0;
	if (i == length) {
		if (p <= Q && qtd >= M)
			return 1;
		return 0;
	}
	int retorno = backtrack(A, Q, i + 1, p, M, qtd);
	retorno += backtrack(A, Q, i + 1, p + A[i], M, qtd + 1);
	return retorno;
}
