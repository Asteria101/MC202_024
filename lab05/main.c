#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define MAX_SIZE_IP 16


struct info {
	char ip[MAX_SIZE_IP];
	int priority;
};

typedef struct avl_node {
	struct info info;
	int balanced;
	struct avl_node *left, *right;
}AVL;

typedef AVL *p_avl;


/* Prototypes */
void remove_info(p_avl *T, struct info data, char *h);


/* Basic functions */

/*
* Initializes data of information
*/
struct info initialize(int size, int priority, char *ip) {
	struct info data;

	strcpy(data.ip, ip);
	data.priority = priority;
	
	return data;
}


/*
* Returns a new node of the AVL tree
*/
p_avl create_node(struct info data) {
	p_avl T = malloc(1 * sizeof(AVL));
	if (T == NULL) {
		exit(1);
	}

	T->info = initialize(strlen(data.ip) + 1, data.priority, data.ip);

	T->balanced = 0;

	T->left = NULL;
	T->right = NULL;

	return T;
}


/*
* Visits AVL tree in pre-order
*/
void visit_pre_order(p_avl T) {
	if (T != NULL) {
		// Visit the current node
		printf("- %s: %d\n", T->info.ip, T->info.priority);
		// Visit the left subtree
		visit_pre_order(T->left);
		// Visit the right subtree
		visit_pre_order(T->right);
	}
}


/*
* Checks if the AVL tree is full
*/
int is_full_avl(p_avl T) {
	if (T == NULL) {
		return 1;
	}
	else if (T->left == NULL && T->right == NULL) {
		return 1;
	}
	else if (T->left != NULL && T->right != NULL) {
		return is_full_avl(T->left) && is_full_avl(T->right);
	}
	else {
		return 0;
	}
}


/*
* Calculates the height of the AVL tree
*/
int height(p_avl T) {
	if (T == NULL) {
		return 0;
	}
	int left_height = height(T->left);
	int right_height = height(T->right);
	return 1 + (left_height > right_height ? left_height : right_height);
}


/*
* Determines the biggest route between two nodes in the AVL tree
*/
int biggest_route(p_avl T) {
	if (T != NULL) {
		int left_height = height(T->left);
		int right_height = height(T->right);
		
		int left_route = biggest_route(T->left);
		int right_route = biggest_route(T->right);
		
		int max_route = left_height + right_height;
		
		if (left_route > max_route) {
			max_route = left_route;
		}
		
		if (right_route > max_route) {
			max_route = right_route;
		}
		
		return 1 + max_route;
	}
	else {
		return 0;
	}
}


/*
* Destroys AVL tree
*/
void destroy_avl(p_avl *T) {
	if (*T != NULL) {
		destroy_avl(&(*T)->left);
		destroy_avl(&(*T)->right);
		free(*T);
		*T = NULL;
	}
}


/*
* Prints the tree in a readable format
*/
void ImprimeAVL(p_avl T, int h, int height) {
	int i;
	if (T != NULL) {
		ImprimeAVL(T->right, h + 1, height);

		for (i = 0; i < h; i++) {
			printf("   		");
		}

		if (T->balanced < 0) {
			printf("%s %d (%d)",T->info.ip, T->info.priority, T->balanced);
		}
		else{
			printf("%s %d (%d)",T->info.ip, T->info.priority, T->balanced);
		}
		for (i=0; i < height - h; i++) {
			printf("----------------");
		}
		printf("\n");

		ImprimeAVL(T->left, h + 1,height);    
	}
}



/* Rotations */

/*
* Simple left rotation
*/
void rotate_left(p_avl *T) {
	p_avl right_son = (*T)->right;
	(*T)->right = right_son->left;
	right_son->left = (*T);
	(*T) = right_son;
}


/*
* Simple right rotation
*/
void rotate_right(p_avl *T) {
	p_avl left_son = (*T)->left;
	(*T)->left = left_son->right;
	left_son->right = (*T);
	(*T) = left_son;
}


/*
* Double left rotation
*/
void rotate_double_left(p_avl *T) {
	rotate_right(&(*T)->right);
	rotate_left(T);
}


/*
* Double right rotation
*/
void rotate_double_right(p_avl *T) {
	rotate_left(&(*T)->left);
	rotate_right(T);
}



/* Balancing */

/*
* Ajusts balance after double rotation of insertion
*/
void balance_doble_rotation(p_avl A, p_avl B, p_avl C) {
	switch (C->balanced) {
		case -1:
			A->balanced = 1;
			B->balanced = 0;
			break;
		
		case 0:
			A->balanced = 0;
			B->balanced = 0;
			break;

		case +1:
			A->balanced = 0;
			B->balanced = -1;
			break;
	}
	C->balanced = 0;
}


/*
* Ajusts balance after simple rotation of insertion
*/
void balance_simple_rotation(p_avl A, p_avl B) {
	A->balanced = B->balanced = 0;
}


/*
* Ajusts balance after simple right rotation of removal
*/
void balance_right(p_avl A, p_avl B, char *h) {
	if (B->balanced == -1) {
		A->balanced = 0;
		B->balanced = 0;
		(*h) = 1;
	}
	else {
		A->balanced = -1;
		B->balanced = 1;
		(*h) = 0;
	}
}


/*
* Ajusts balance after simple left rotation of removal
*/
void balance_left(p_avl A, p_avl B, char *h) {
	if (B->balanced == 1) {
		A->balanced = 0;
		B->balanced = 0;
		(*h) = 1;
	}
	else {
		A->balanced = 1;
		B->balanced = -1;
		(*h) = 0;
	}
}


/*
* Ajusts balance after double right rotation of removal
*/
void balance_double_right(p_avl A, p_avl B, p_avl C) {
	switch (C->balanced) {
		case -1:
			A->balanced = 1;
			B->balanced = 0;
			break;
		
		case 0:
			A->balanced = 0;
			B->balanced = 0;
			break;

		case 1:
			A->balanced = 0;
			B->balanced = -1;
			break;
	}
	C->balanced = 0;
}


/*
* Ajusts balance after double left rotation of removal
*/
void balance_double_left(p_avl A, p_avl B, p_avl C) {
	switch (C->balanced) {
		case -1:
			A->balanced = 0;
			B->balanced = 1;
			break;
		
		case 0:
			A->balanced = 0;
			B->balanced = 0;
			break;

		case 1:
			A->balanced = -1;
			B->balanced = 0;
			break;
	}
	C->balanced = 0;
}


/*
* Balances AVL tree after insertion on the right
*/
void treat_growth_right(p_avl *T, char *h) {
	p_avl A, B, C;

	A = (*T);
	B = (*T)->right;
	C = B->left;

	switch(A->balanced) {
		case 1:
			if (B->balanced == 1) { // rotate
				rotate_left(T);
				balance_simple_rotation(A, B); // update balance
			}
			else { // B->balanced == -1
				rotate_double_left(T);
				balance_doble_rotation(B, A, C); // update balance
			}  
			*h = 0;
			break;

		case 0:
			A->balanced = 1;
			(*h) = 1; 	
			break;

		case -1:
			A->balanced = 0;
			(*h) = 0; 	
			break;
	}
}


/*
* Balances AVL tree after insertion on the left
*/
void treat_growth_left(p_avl *T, char *h) {
	p_avl A, B, C;

	A = (*T);
	B = (*T)->left;
	C = B->right;

	switch(A->balanced) {
		case -1:
			if (B->balanced == -1) { // rotate
				rotate_right(T);
				balance_simple_rotation(A, B); // update balance
			}
			else { // B->balanced == 1
				rotate_double_right(T);
				balance_doble_rotation(A, B, C); // update balance
			}  
			*h = 0;
			break;

		case 0:
			(*T)->balanced = -1;
			(*h) = 1; 	
			break;

		case 1:
			(*T)->balanced = 0;
			(*h) = 0; 	
			break;
	}
}


/*
* Balances AVL tree after removal on the left
*/
void treat_shrink_right(p_avl *T, char *h) {
	p_avl A, B, C;

	A = (*T);
	B = (*T)->left;

	switch(A->balanced) {
		case -1:
			if (B->balanced <= 0) {
				rotate_right(T);
				balance_right(A, B, h);

			}
			else {
				C = B->right;
				rotate_double_right(T);
				balance_double_right(A, B, C);
				(*h) = 1;
			}
			break;

		case 0:
			(*T)->balanced = -1;
			(*h) = 0;
			break;

		case 1:
			(*T)->balanced = 0;
			(*h) = 1;
			break;
	}
}


/*
* Balances AVL tree after removal on the right
*/
void treat_shrink_left(p_avl *T, char *h) {
	p_avl A, B, C;

	A = (*T);
	B = (*T)->right;

	switch(A->balanced) {
		case 1:
			if (B->balanced >= 0) {
				rotate_left(T);
				balance_left(A, B, h);
			}
			else {
				C = B->left;
				rotate_double_left(T);
				balance_double_left(A, B, C);
				(*h) = 1;
			}
			break;

		case 0:
			A->balanced = 1;
			(*h) = 0;
			break;

		case -1:
			A->balanced = 0;
			(*h) = 1;
			break;
	}
}


/*
* Case for leaf or node with one child
*/
int remove_node_degree_0or1(p_avl *T, char *h) {
	p_avl aux;

	if ((*T)->left == NULL) {
		aux = (*T);
		(*T) = (*T)->right;
		free(aux);
	}
	else {
		if ((*T)->right == NULL) {
			aux = (*T);
			(*T) = (*T)->left;
			free(aux);
		}
		else {
			return 0;
		}
	}
	*h = 1;
	return 1;
}


/*
* Substitutes the value of a node by the value of leftmost son, and removes the leftmost son
*/
void remove_leftmost_son(p_avl *T, p_avl *leftmost, char *h) {
	if ((*leftmost)->left == NULL) {
		(*T)->info = (*leftmost)->info;
		remove_node_degree_0or1(leftmost, h);
	}
	else {
		remove_leftmost_son(T, &((*leftmost)->left), h);
		if (*h) {
			treat_shrink_left(leftmost, h);
		}
	}
}


/*
* Removes a node from the AVL tree
*/
void actual_remove(p_avl *T, char *h) {
	int balanced;
	if (remove_node_degree_0or1(T, h) == 0) { // node with degree 2
		balanced = (*T)->balanced;
		remove_leftmost_son(T, &((*T)->right), h);
		(*T)->balanced = balanced;
		if (*h) {
			treat_shrink_right(T, h);
		}
	}
}



/* Operations */

/*
* Inserts on AVL tree
*/
void insert(p_avl *T, struct info data, char *h) {
	if ((*T) == NULL) {
		(*T) = create_node(data);
		*h = 1;
	} 
	else {
		if ((*T)->info.priority <= data.priority) {
			insert(&((*T)->right), data, h);
			if ((*h) == 1) { // tree grew on the right
				treat_growth_right(T, h);
			} 
		}
		else {
			insert(&((*T)->left), data, h);
			if ((*h) == 1) { // tree grew on the left
				treat_growth_left(T, h);
			}
		}
	}
}


/*
* Removes from AVL tree
*/
void remove_info(p_avl *T, struct info data, char *h) {
	if ((*T) != NULL) {
		if ((*T)->info.priority != data.priority) {
			if ((*T)->info.priority < data.priority) {
				remove_info(&((*T)->right), data, h);
				if ((*h) == 1) {
					treat_shrink_right(T, h);
				}
			}
			else {
				remove_info(&((*T)->left), data, h);
				if ((*h) == 1) {
					treat_shrink_left(T, h);
				}
			}
		}
		else if (strcmp((*T)->info.ip, data.ip) != 0) {
			remove_info(&((*T)->right), data, h);
			if ((*h) == 1) {
				treat_shrink_right(T, h);
			}
		}
		else {
			actual_remove(T, h);
		}
	}
}



int main(int argc, char **argv) {
	p_avl T = NULL;

	char higher = 0, lower = 0;
	int n_nodes, n_operations;

	FILE *information = NULL, *operations = NULL;

	information = fopen(argv[1], "r");
	if (information == NULL) exit(1);
	
	char *ip = calloc(16, sizeof(char));

	// creating AVL tree
	fscanf(information, "%d\n", &n_nodes);
	for (int i = 0; i < n_nodes; i++) {	
		memset(ip, '\0', 16 * sizeof(char)); 

		int priority = 0;
		fscanf(information, "%s %d\n", ip, &priority);

		struct info data = initialize(strlen(ip) + 1, priority, ip);

		insert(&T, data, &higher);
	}

	fclose(information);


	// printing information after building the AVL tree in preorder
	printf("[INFO] Apos construcao:\n");
	visit_pre_order(T);
	if (is_full_avl(T)) {
		printf("Arvore esta cheia\n");
	}
	else {
		printf("Arvore nao esta cheia\n");
	}

	printf("A rota mais longa possivel passa por %d nos\n", biggest_route(T));
	printf("\n");


	operations = fopen(argv[2], "r");
	if (operations == NULL) {
		exit(1);
	}

	// performing operations
	fscanf(operations, "%d\n", &n_operations);
	for (int i = 0; i < n_operations; i++) {
		memset(ip, '\0', 16 * sizeof(char));
		int priority = 0;

		int operation;

		fscanf(operations, "%d %s %d\n", &operation, ip, &priority);

		struct info data = initialize(strlen(ip) + 1, priority, ip);

		switch (operation) {
		case 1:
			insert(&T, data, &higher);
			break;
		
		case -1:
			remove_info(&T, data, &lower);
			break;
		}
	}

	fclose(operations);


	if (ip != NULL) {
		free(ip);
	}


	// printing information after doing the operation on the AVL tree in preorder
	printf("[INFO] Apos atualizacao:\n");
	visit_pre_order(T);
	if (is_full_avl(T)) {
		printf("Arvore esta cheia\n");
	}
	else {
		printf("Arvore nao esta cheia\n");
	}

	printf("A rota mais longa possivel passa por %d nos\n", biggest_route(T));

	destroy_avl(&T);
	

	return 0;
}

