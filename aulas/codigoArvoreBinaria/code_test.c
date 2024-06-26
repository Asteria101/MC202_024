#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct binary_tree *p_binTree;

typedef struct binary_tree {
    char data;
    p_binTree right, left;
} Binary_tree;

/*
*  Visits the tree in pos order
*/
void pos_order(p_binTree T, char **s) {
    if (T != NULL) {
        pos_order(T->left, s);
        pos_order(T->right, s);

        printf(*s, "%c ", T->data);
        (*s) = (*s) + strlen(*s);
    }
}


/*
*  Copies the nodes from the pos order to arrays
*/
void nodes_pos(char *pos, int nl, int nr, char **l_pos, char **r_pos) {
    int i, j;

    if (nl > 0) { // checks if there is nodes on the left
        *l_pos = calloc(nl, sizeof(char));
        for (i = 0; i < nl; i++) {
            (*l_pos)[i] = pos[i]; // copies to l_pos the elements of pos;
        }
    }
    else {
        *l_pos = NULL;
    }

    if (nr > 0) {
        *r_pos = calloc(nr, sizeof(char));
        for (i = 0, j = nl; i < nr; i++, j++) {
            (*r_pos)[i] = pos[j];
        }
    }
    else {
        *r_pos = NULL;
    }
}


/*
*
*/
void search_prev(p_binTree T, p_binTree *prev, char info, char *found) {
    if (T != NULL && !(*found)) {
        search_prev(T->left, prev, info, found);

        if (!(*found)) {
            if (T->data != info){
                (*prev) = T;

            search_prev(T->right, prev, info, found);
            } else {
                if (*prev != NULL) {
                    (*found)=1;
                }
            }
        }
    }
}