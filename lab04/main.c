#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef MAX
#define MAX(x,y) (((x) > (y))?(x):(y))
#endif

typedef struct binary_tree *p_binTree;

typedef struct binary_tree {
    char data;
    p_binTree right, left;
} Binary_tree;


/*
* Creates node for binary tree
*/
p_binTree create_node(p_binTree right, p_binTree left, char info) {
    p_binTree T = calloc(1, sizeof(Binary_tree));
    T->data = info;
    T->left = left;
    T->right = right;

    return T;
}


/*
*  Returns the number of nodes on the left and on the right
*/
void n_left_right(char *sim, char root, int *nl, int *nr) {
    int i;
    int n = strlen(sim);

    *nl = *nr = i = 0;
    while (sim[i] != root) {
        i++;
    }
    (*nl) = i;
    (*nr) = n - (*nl) - 1;
}


/*
*  Copies the nodes from the simetric order to arrays 
*/
void nodes_sim(char *sim, int nl, int nr, char **l_sim, char **r_sim){
    int i, j;

    if (nl > 0) { // checks if there is nodes on the left
        *l_sim = calloc(nl, sizeof(char));
        for (i = 0; i < nl; i++) {
            (*l_sim)[i] = sim[i]; // copies to l_sim the elements of sim;
        }
    }
    else {
        *l_sim = NULL;
    }

    if (nr > 0) {
        *r_sim = calloc(nr, sizeof(char));
        for (i = 0, j = nl + 1; i < nr; i++, j++) {
            (*r_sim)[i] = sim[j];
        }
    }
    else {
        *r_sim = NULL;
    }
}


/*
*  Copies the nodes from the pre order to arrays
*/
void nodes_pre(char *pre, int nl, int nr, char **l_pre, char **r_pre) {
    int i, j;

    if (nl > 0) { // checks if there is nodes on the left
        *l_pre = calloc(nl, sizeof(char));
        for (i = 0; i < nl; i++) {
            (*l_pre)[i] = pre[i]; // copies to l_pre the elements of pre;
        }
    }
    else {
        *l_pre = NULL;
    }

    if (nr > 0) {
        *r_pre = calloc(nr, sizeof(char));
        for (i = 0, j = nl; i < nr; i++, j++) {
            (*r_pre)[i] = pre[j];
        }
    }
    else {
        *r_pre = NULL;
    }
}


/*
* Build tree using simetric and pre-order
*/
p_binTree build_tree(char *sim, char *pre, int n) {
    char *l_sim = NULL, *r_sim = NULL;
    char *l_pre = NULL, *r_pre = NULL;
    int nl, nr; //number of nodes on the left and right

    p_binTree p = NULL, left = NULL, right = NULL;

    if (n == 1) {
        p = create_node(NULL, NULL, sim[0]);
    }
    else {
        n_left_right(sim, pre[0], &nl, &nr);
        nodes_sim(sim, nl, nr, &l_sim, &r_sim);
        nodes_pre(pre + 1, nl, nr, &l_pre, &r_pre);

        if (l_sim != NULL) {
            left = build_tree(l_sim, l_pre, strlen(l_sim));
        }
        if (r_sim != NULL) {
            right = build_tree(r_sim, r_pre, strlen(r_sim));
        }
        p = create_node(left, right, pre[0]);
    }

    return p;
}


/*
*  Calculates the tree height
*/
int height(p_binTree T) {
    if (T != NULL) {
        return (1 + MAX(height(T->left), height(T->right)));
    }
    else {
        return 0;
    }
}


/*
* Calculate the degree of each node in symmetric traversal
*/
void calculate_degree(p_binTree T, int *degree, char *s) {
    if (T != NULL) {
        calculate_degree(T->left, degree, s);

        int node_degree = 0;
        if (T->left != NULL) {  
            node_degree++;
        }
        if (T->right != NULL) {
            node_degree++;
        }
        int index = strchr(s, T->data) - s;
        degree[index] = node_degree;

        calculate_degree(T->right, degree, s);
    }
}


/*
*  Prints the binary Tree
*/
void print_tree(p_binTree T, int h, int height) {
    int i;

    if (T != NULL) {
        print_tree(T->right, h + 1, height);

        for (i = 0; i < h; i++) {
            printf("   ");
        }
        printf("%c", T->data);

        for (i = 0; i <  h; i++) {
            printf("---");
        }
        printf("\n");
        
        print_tree(T->left, h+1, height);
    }
}


/*
*  Visits the tree in pre order traversal
*/
void pre_order(p_binTree T, char **s) {
    if (T != NULL) {
        printf(*s, "%c ", T->data);
        (*s) = (*s) + strlen(*s);

        pre_order(T->left, s);
        pre_order(T->right, s);
    }
}


/*
*  Visits the tree in simetric traversal
*/
void simetric(p_binTree T, char **s) {
    if (T != NULL) {
        simetric(T->left, s);

        printf(*s, "%c ", T->data);
        (*s) = (*s) + strlen(*s);

        simetric(T->right, s);
    }

}


/*
* Frees memory of binary tree
*/
void destroy_tree(p_binTree *T) {
    p_binTree p = *T;

    if (p != NULL) {
        destroy_tree(&(p->left));
        destroy_tree(&(p->right));

        free(p);
    }
}


int main(int argc, char **argv) {
    p_binTree T = NULL;

    char *pre, *sim;
    int n;

    /* Read file */
    FILE *fp_pre = fopen(argv[1], "r"), *fp_sim = fopen(argv[2], "r");
    fscanf(fp_pre, "%d\n", &n);
    fscanf(fp_sim, "%d\n", &n);

    pre = calloc(n, sizeof(char));
    sim = calloc(n, sizeof(char));

    for (int i = 0; i < n; i++) {
        fscanf(fp_pre, "%c", &pre[i]);
        fscanf(fp_sim, "%c", &sim[i]);
    }

    fclose(fp_pre);
    fclose(fp_sim);
    /* End of file */

    T = build_tree(sim, pre, n);

    printf("Altura da arvore: %d\n", height(T));
    printf("Grau de cada nó em percurso simétrico:\n");

    int *degree = calloc(n, sizeof(int));

    calculate_degree(T, degree, sim);

    for (int i = 0; i < n; i++) {
        printf("%c: %d\n", sim[i], degree[i]);
    }

    destroy_tree(&T);

    return 0;
}