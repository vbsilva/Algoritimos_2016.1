#include <stdio.h>
#include <stdlib.h>

struct Node {
	int element;
	struct Sentinel *storage;
	struct Node *next;
};

struct Sentinel {
	struct Node *head;
	struct Node *tail;
	int length;
	int weight;

	void (*insert)(struct Sentinel *self, struct Node *t, struct Node *x);
	int (*del)(struct Sentinel *self, struct Node *x);
	struct Node *(*search)(struct Sentinel *self, int pos);

	void (*push)(struct Sentinel *self, struct Node *t);
	int (*pop)(struct Sentinel *self);

	void (*enqueue)(struct Sentinel *self, struct Node *t);
	int (*dequeue)(struct Sentinel *self);
};

struct Sentinel *init();
struct Node *node_list(int);
struct Node *node_stack(int);
struct Node *node_queue(int);

void *ec_malloc(unsigned int);
void free_struct(struct Sentinel *sentinel);

void insert(struct Sentinel *self, struct Node *t, struct Node *x);
int del(struct Sentinel *self, struct Node *x);
struct Node *search(struct Sentinel *self, int pos);

void push(struct Sentinel *self, struct Node *t);
int pop(struct Sentinel *self);

void enqueue(struct Sentinel *self, struct Node *t);
int dequeue(struct Sentinel *self);

int main()
{
	int n;
	char opt;
	int value;
	char caso = 1;
	char loop = 1;

	struct Sentinel *list = init();
	struct Sentinel *queue = init();

	scanf("%d", &n);
	while (caso) {
		caso = 0;
		int i;
		for (i = 0; i < n; ++i) {
			scanf("%d", &value);
			list->insert(list, node_list(value), list->tail);
		}
		loop = 1;
		getchar();
		struct Node *t;
		char debug[10];
		while (loop == 1) {
			if (scanf("%c%s", &opt, debug) == EOF) {
				loop = 0;
			} else if (opt != '\n') {
				scanf ("%d", &value);
				switch (opt) {
					case 'A':
						queue->enqueue(queue, node_queue(value));
						printf("%d %d\n", queue->length, queue->weight);
						break;
					case 'L':
						t = list->search(list, value);
						while (queue->head->next != NULL && queue->head->next->element + t->storage->weight <= t->element && queue->length > 0)
							t->storage->push(t->storage, node_stack(queue->dequeue(queue)));
						printf("%d %d\n", value, t->storage->length);
						break;
					case 'D':
						t = list->search(list, value);
						if (t != NULL && t->storage->length != 0)
							t->storage->pop(t->storage);
						printf("%d %d\n", value, t->storage->length);
						break;
					case 'I':
						t = list->search(list, value);
						if (t != NULL)
							printf("%d %d %d\n", value, t->storage->length, t->storage->weight);
						break;
				}
				getchar();
			} else {
				loop = 0;
				n = atoi(debug);
				caso = 2;
				printf("\n");
			}
		}
		while(list->length > 0) list->del(list, list->head);
		while(queue->length > 0) queue->dequeue(queue);
	}
	free_struct(list);
	free_struct(queue);
	return 0;
}

void *ec_malloc(unsigned int size)
{
	void *ptr = malloc(size);
	if (ptr == NULL) 
		exit(-1);
	return ptr;
}

void free_struct(struct Sentinel *sentinel)
{
	free(sentinel->head);
	free(sentinel->tail);
	free(sentinel);
}

struct Sentinel *init()
{
	struct Sentinel *t = (struct Sentinel *) ec_malloc(sizeof(struct Sentinel));
	t->head = (struct Node *) ec_malloc(sizeof(struct Node));
	t->tail = (struct Node *) ec_malloc(sizeof(struct Node));
	t->head->next = t->tail->next = NULL;
	t->length = 0;
	t->weight = 0;

	t->insert = insert;
	t->del = del;
	t->search = search;
	t->push = push;
	t->pop = pop;
	t->enqueue = enqueue;
	t->dequeue = dequeue;

	return t;
}

struct Node *node_list(int element)
{
	struct Node *t = (struct Node *) ec_malloc(sizeof(struct Node));
	t->element = element;
	t->storage = init();
	t->next = NULL;

	return t;
}

struct Node *node_stack(int element)
{
	struct Node *t = (struct Node *) ec_malloc(sizeof(struct Node));
	t->element = element;
	t->storage = NULL;
	t->next = NULL;

	return t;
}

struct Node *node_queue(int element)
{
	return node_stack(element);
}

void insert(struct Sentinel *self, struct Node *t, struct Node *x)
{
	if (self->head->next == NULL)
		self->head->next = self->tail->next = t;
	else if (x == self->tail) {
		self->tail->next->next = t;
		self->tail->next = t;
	} else {
		t->next = x->next;
		x->next = t;
	}

	self->length++;
	self->weight += t->element;
}

int del(struct Sentinel *self, struct Node *x)
{
	struct Node *t;
	if (self->head->next == NULL || x->next == NULL)
		return 0;
	else {
		t = x->next;
		if (t->next == NULL) {
			self->tail->next = x;
			x->next = NULL;
		} else {
			x->next = t->next;
		}
		self->length--;
		self->weight -= t->element;
	}
	int value = t->element;
	if (t->storage != NULL)
		while (t->storage->length > 0) t->storage->pop(t->storage);
	free(t);
	return value;
}

struct Node *search(struct Sentinel *self, int pos)
{
	int i = 0;
	struct Node *cur = self->head->next;
	if (cur == NULL)
		return NULL;
	while (i != pos && cur->next != NULL) {
		cur = cur->next;
		i++;
	}
	if (i == pos)
		return cur;
	else
		return NULL;
}

void push(struct Sentinel *self, struct Node *t)
{
	self->insert(self, t, self->head);
}

int pop(struct Sentinel *self)
{
	return self->del(self, self->head);
}

void enqueue(struct Sentinel *self, struct Node *t)
{
	self->insert(self, t, self->tail);
}

int dequeue(struct Sentinel *self)
{
	return self->del(self, self->head);
}
