#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

enum State {
	READING,
	SEARCHING
};

struct AVL_Node {
	struct AVL_Node *left;
	struct AVL_Node *right;
	struct IN *val;
	int bf;
};

struct root_bool {
	struct AVL_Node *root;
	int height_changed;
};

struct IN {
	unsigned int key_number;
	char *key;
	int *lines;
	int lines_count;
	int size;
};

int height(struct AVL_Node *);

struct AVL_Node *AVL_search(struct AVL_Node *, unsigned int, char *);
struct AVL_Node *AVL_rotate_left(struct AVL_Node *);
struct AVL_Node *AVL_rotate_right(struct AVL_Node *);
struct root_bool *AVL_insert(struct AVL_Node *, struct IN *);

unsigned int hashcode(char *);
void *ec_malloc(unsigned int);
struct IN *create_dict(char *, int);
void print_IN(struct AVL_Node *, char *);

static int depth = 0;

int main()
{
	char *read_line = (char *) ec_malloc(sizeof(char) * 102);
	char *key = (char *) ec_malloc(sizeof(char) * 101);
	struct AVL_Node *root = NULL;       	
	struct root_bool *ins = NULL;
	enum State state = READING;
	int line = 1;

	while(fgets(read_line, 101, stdin) != NULL) {
		if (read_line[0] == '$') {
			if (strcmp(read_line, "$TEXTO\n") == 0) {
				state = READING;
				line = 1;
			} 
			if (strcmp(read_line, "$CONSULTAS\n") == 0) {
				state = SEARCHING;
			}
		} else {
			if (state == READING) {
				key = strtok(read_line, " \n");
				while (key != NULL) {
					ins = AVL_insert(root, create_dict(key, line));
					root = ins->root;
					free(ins);
					key = strtok(NULL, " \n");
				}
				line++;
			} else {
				key = strtok(read_line, "\n");
				print_IN(root, key);	
			}
		}
	}	
	free(read_line);
	return 0;
}

void print_IN(struct AVL_Node *root, char *key) 
{
	// print key
	printf("%s ", key);
	// print depth
	depth = 0;
	struct AVL_Node *tmp = AVL_search(root, hashcode(key), key);
	if (tmp == NULL) {
		printf("0\n");
		return;
	} else {
		printf("%d ", depth);
	}
	// print lines
	int i;
	for (i = 0; i < tmp->val->lines_count; ++i)
		printf("%d%c", tmp->val->lines[i], i != tmp->val->lines_count - 1 ? ' ' : '\n');	
}

int height(struct AVL_Node *root)
{
	if (root == NULL)
		return 0;
	else {
		int l = height(root->left);
		int r = height(root->right);
		return (1 + max(l, r));
	}
}

struct AVL_Node *AVL_search(struct AVL_Node *root, unsigned int v, char *key)
{
	if (root == NULL)
		return NULL;
	else if (root->val->key_number == v) {
		depth++;
		int c = strcmp(root->val->key, key);
		if (c == 0)
			return root;
		else if (c > 0)
			return AVL_search(root->left, v, key);
		else
			return AVL_search(root->right, v, key);
	} else if (v < root->val->key_number) {
		depth++;
		return AVL_search(root->left, v, key);
	} else if (root->val->key_number < v) {
		depth++;
		return AVL_search(root->right, v, key);	
	} else {
	       return NULL;
	}	       
}

struct AVL_Node *AVL_rotate_left(struct AVL_Node *root)
{
	struct AVL_Node *r = root->right;
	struct AVL_Node *rl = r->left;
	r->left = root;
	root->right = rl;
	if (r->bf > 0)
		root->bf = root->bf - 1 - r->bf;
	else
		root->bf = root->bf - 1;
	if (root->bf < 0)
		r->bf = r->bf - 1 + root->bf;
	else
		r->bf = r->bf - 1;
	return r;
}

struct AVL_Node *AVL_rotate_right(struct AVL_Node *root)
{
	struct AVL_Node *l = root->left;
	struct AVL_Node *lr = l->right;
	l->right = root;
	root->left = lr;
	if (l->bf < 0)
		root->bf = root->bf + 1 - l->bf;
	else
		root->bf = root->bf + 1;
	if (root->bf > 0)
		l->bf = l->bf + 1 + root->bf;
	else
		l->bf = l->bf + 1;
	return l;
}

struct root_bool *AVL_insert(struct AVL_Node *root, struct IN *v)
{
	struct root_bool *handler;
	int c = 0;
	if (root == NULL) {
		handler = (struct root_bool *) ec_malloc(sizeof(struct root_bool));
		struct AVL_Node *tmp = (struct AVL_Node *) ec_malloc(sizeof(struct AVL_Node));
		tmp->left = NULL;
		tmp->right = NULL;
		tmp->val = v;
		tmp->bf = 0;
		handler->root = tmp;
		handler->height_changed = 1;
		return handler;
	} else if (v->key_number < root->val->key_number) {
		handler = AVL_insert(root->left, v);
		root->left = handler->root;
		root->bf = root->bf - handler->height_changed;
	} else if (root->val->key_number == v->key_number) { // 
		if ((c = strcmp(v->key, root->val->key)) == 0) {
			if (root->val->lines_count == root->val->size) {
				root->val->size *= 2;
				root->val->lines = realloc(root->val->lines, root->val->size * sizeof(int));
			}
			if (root->val->lines[root->val->lines_count - 1] != v->lines[0])
				root->val->lines[root->val->lines_count++] = v->lines[0];
			free(v->key);
			free(v->lines);	
			free(v);
			handler = (struct root_bool *) ec_malloc(sizeof(struct root_bool));
			handler->root = root;
			handler->height_changed = 0;
			return handler;
		} else if (c < 0) {
			handler = AVL_insert(root->left, v);
			root->left = handler->root;
			root->bf -= handler->height_changed;
		} else {
			handler = AVL_insert(root->right, v);
			root->right = handler->root;
			root->bf = root->bf + handler->height_changed;
		}
	} else {
		handler = AVL_insert(root->right, v);
		root->right = handler->root;
		root->bf = root->bf + handler->height_changed;
	}

	if (handler->height_changed == 0) {
		handler->root = root;
		return handler;
	} else if (root->bf == 0) {
		handler->root = root;
		handler->height_changed = 0;
		return handler;
	} else if (root->bf == 1 || root->bf == -1) {
		handler->root = root;
		handler->height_changed = 1;
		return handler;
	} else if (root->bf == -2) {
		if (root->left->bf == 1)
			root->left = AVL_rotate_left(root->left);
		root = AVL_rotate_right(root);
		handler->root = root;
		handler->height_changed = 0;
		return handler;
	} else {
		if (root->right->bf == -1)
			root->right = AVL_rotate_right(root->right);
		root = AVL_rotate_left(root);
		handler->root = root;
		handler->height_changed = 0;
		return handler;
	}
}

unsigned int hashcode(char *key)
{ 
	int len = strlen(key);
	if (len == 0)
		return 0;
	
	char sub[len];
	memcpy(sub, key, len - 1); 
	sub[len - 1] = '\0'; 
	
	return (26 * hashcode(sub) + (key[len - 1] - 'a')) % 11881376;
}

void *ec_malloc(unsigned int size)
{
	void *ptr;
	ptr = malloc(size);
	if (ptr == NULL) {
		fprintf(stderr, "[!!!] END OF THE WORLD [!!!] Malloc returned NULL!\n");
		exit(-1);
	}

	return ptr;
}

struct IN *create_dict(char *key, int line)
{
	struct IN *dict = (struct IN *) ec_malloc(sizeof(struct IN));
	dict->key = (char *) ec_malloc(sizeof(char) * 101);
	strcpy(dict->key, key);
	dict->lines = (int *) ec_malloc(sizeof(int) * 121);
	dict->lines[0] = line;
	dict->lines_count = 1;
	dict->key_number = hashcode(key);
	dict->size = 121;
	return dict;
}
