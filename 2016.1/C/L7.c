#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(a,b,T) do { T tmp = a; a = b; b = tmp; } while(0);
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

void *ec_malloc(unsigned int);

int backtrack(int *, int, int, int, int, int);

static int length = 0;

int main()
{
	int K;
	int casos = 0;

	int L;
	scanf("%d", &K);
	
	int *p;
	while (casos < K) {
		scanf("%d", &L);

		if (length < L) {
			p = (int *) ec_malloc(sizeof(int) * L);
		}
		length = L;
		int M;
		int Q;

		int i = 0;
		for (; i < L; i++) 
			scanf("%d", &p[i]);
		
		scanf("%d %d", &M, &Q);

		int tmp = backtrack(p, Q, 0, 0, M, 0);
		printf("caso %d: %d\n", casos++, tmp);	
	}	
	return 0;
}

void *ec_malloc(unsigned int size)
{
	void *ptr = malloc(size);
	if (!ptr) {
		fprintf(stderr, "[!!!] MALLOC [!!!]\n");
		exit(1);
	}
	return ptr;
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

/**A  = Vetor de preços
 * M  = Quantidade mínima de itens
 * S  = Quantidade máxima de gasto
 **B  = Vetor de solução
 * i  = item atual
 * p  = soma parcial dos preços
*/
