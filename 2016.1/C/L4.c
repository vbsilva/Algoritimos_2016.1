#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct UnionFind {
	int *p;
	int *rank;
	int *area;
};

struct UnionFind *make_set(int);
int find_set(struct UnionFind **, int);
int is_same_set(struct UnionFind **, int, int);
void union_set(struct UnionFind **, int, int);
void check_edges(struct UnionFind **, int, int);
char check_winner(struct UnionFind **, int, int);

void *ec_malloc(unsigned int);

static char **board;

int main()
{
	// input variables
	int size;
	char first;
	int row, column;

	// output variables
	int current_case = 0;
	char winner = 'N';
	int area = 0;

	char *line = (char *) ec_malloc(51);
	int i;
	while (scanf("%d", &size) > 0) {
		if (current_case != 0)
			printf("\n");
		scanf(" %c%*c", &first);
		winner = 'N';
		area = 0;
		int turn = first == 'B' ? 0 : 1;

		board = (char **) ec_malloc(sizeof(char *) * size + 2);
		memset(board, 'N', size + 2);
		for (i = 0; i < size + 2; ++i) {
			board[i] = (char *) ec_malloc(sizeof(char) * size + 2);
			memset(board[i], 'N', size + 2);
		}

		while (fgets(line, 51, stdin) != NULL && line[0] != '\n') {
			row = atoi(strtok(line, " "));
			column = atoi(strtok(NULL, "\n"));

			board[row + 1][column + 1] = turn == 0 ? 'B' : 'W';

			turn = (turn + 1) % 2;
		}	

		struct UnionFind *set = make_set(size);

		for (i = 0; i < size * size; ++i) {
			check_edges(&set, i, size);
		}
		for (i = 0; i < size * size; ++i) {
			winner = check_winner(&set, i, size);
			if (winner != 'N') {
				area = set->area[find_set(&set, i)];
				break;
			}
		}


		printf("caso %d: %c %d\n", current_case, winner, area);
		current_case++;
		free(set->p);
		free(set->rank);
		free(set->area);
		free(set);
	}
	return 0;
}

struct UnionFind *make_set(int size)
{
	int i;

	struct UnionFind *tmp = (struct UnionFind *) ec_malloc(sizeof(struct UnionFind));

	tmp->p = (int *) ec_malloc(sizeof(int) * size * size);
	tmp->rank = (int *) ec_malloc(sizeof(int) * size * size);
	tmp->area = (int *) ec_malloc(sizeof(int) * size * size);

	for (i = 0; i < size * size; ++i) {
		tmp->p[i] = i;
		tmp->area[i] = 1;
		tmp->rank[i] = 1;
		int row = (i / size) + 1;
		int column = (i % size) + 1;
		if (board[row][column] == 'B')
			tmp->rank[i] = size - column;
		else
			tmp->rank[i] = size - row;
		
	}

	return tmp;
}

int find_set(struct UnionFind **set, int i)
{
	return (*set)->p[i] == i ? i : ((*set)->p[i] = find_set(set, (*set)->p[i]));
}

int is_same_set(struct UnionFind **set, int i, int j)
{
	return find_set(set, i) == find_set(set, j);
}

void union_set(struct UnionFind **set, int i, int j)
{
	if (!is_same_set((set), i, j)) {
		int x = find_set((set), i), y = find_set((set), j);
		if ((*set)->rank[x] > (*set)->rank[y]) {
			(*set)->p[y] = x;
			(*set)->area[x] = (*set)->area[x] + (*set)->area[y];
		} else {
			(*set)->p[x] = y;
		//	if ((*set)->rank[x] == (*set)->rank[y])
		//		(*set)->rank[y]++;
			(*set)->area[y] = (*set)->area[y] + (*set)->area[x];
		}
		x = find_set((set), i), y = find_set((set), j);

	}
}

void check_edges(struct UnionFind **set, int i, int size)
{
	int row = (i / size);
	int column = (i % size);
	int row_b = row + 1;
	int column_b = column + 1;
	char start = board[row_b][column_b];	
	if (start == 'N')
		return;
	
	if (board[row_b - 1][column_b] == start) {
		union_set(set, i, ((row - 1)*size) + column);
	}

	if (board[row_b - 1][column_b + 1] == start) {
		union_set(set, i, ((row - 1)*size) + (column + 1));
	}

	if (board[row_b][column_b + 1] == start) {
		union_set(set, i, ((row)*size) + (column + 1));
	}

	if (board[row_b + 1][column_b] == start) {
		union_set(set, i, ((row + 1)*size) + column);
	}

	if (board[row_b][column_b - 1] == start) {
		union_set(set, i, ((row)*size) + (column - 1));
	}

	if (board[row_b + 1][column_b - 1] == start) {
		union_set(set, i, ((row + 1)*size) + (column - 1));
	}
}

char check_winner(struct UnionFind **set, int i, int size)
{
	int row = (i / size);
	int column = (i % size);
	char start = board[row + 1][column + 1];

	int x = find_set(set, i);
	int row_p = (x / size);
	int column_p = (x % size);

	if (start == 'B') {
		return (column == size - 1 && column_p == 0) ? 'B' : 'N';
	} else {
		return (row == size - 1 && row_p == 0) ? 'W' : 'N';	
	}
}

void *ec_malloc(unsigned int size)
{
	void *ptr = malloc(size);
	if (ptr == NULL) {
		fprintf(stderr, "[!!!] DOOMSDAY [!!!] Malloc returned NULL\n");
		exit(-1);
	}

	return ptr;
}

