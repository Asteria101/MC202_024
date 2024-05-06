#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


/*
* Raise error
*/
void Error(char *msg, char *function, ...) {
    va_list args; /* list of arguments */
    char msg_final[4096];

    va_start(args, function);
    vsprintf(msg_final, msg, args);
    va_end(args);

    printf("Erro em %s: %s\n", function, msg_final);
    fflush(stdout);
    exit(1);
}


struct node {
    int data;
    p_node prox;
};

typedef struct node *p_node;

struct pixel {
    int x, y; // coordinates
};

typedef struct pixel *p_pixel;

struct image {
    int **position;
    int height, width;
};

typedef struct image *p_image;


/*
*  Function for reading the image
*/
p_image read_image(char *filename) {
    FILE *fp = fopen(filename, "r");
    p_image I = (p_image)calloc(1, sizeof(struct image));

    fscanf(fp, "%d %d\n", &I->width, &I->height);

    I->position = (int **)calloc(I->height, sizeof(int *));

    for (int y = 0; y < I->height; y++) {
        I->position[y] = (int *)calloc(I->width, sizeof(int));
        for (int x = 0; x < I->width; x++) {
            char current_char;
            fscanf(fp, "%c ", &current_char);
            I->position[y][x] = (int)(current_char - '0');
        }
        fscanf(fp, "\n");
    }
    fclose(fp);
    return I;
}


/*
*  Creates node for linked list
*/
p_node create_node(int x) {
    p_node n = malloc(sizeof(struct node));
    n->data = x;
    n->prox = NULL;

    return n;
}


/*
*  Verifies if the list is empty or not
*/
int is_list_empty(p_node head) {
    return (head == NULL);
}


/*
*  Inserts element at the end of the list
*/
void insert_end(p_node *head, int x) {
    p_node p = create_node(x);

    if (is_list_empty(*head)) (*head) = p;

    else {
        p_node current = (*head);

        while (current->prox != NULL) {
            current = current->prox;
        }
        current->prox = p;
    } 
}


/*
*  Removes at the beginning 
*/
void remove_ini(p_node *head) {
    if (!is_list_empty(*head)) {
        (*head) = (*head)->prox;
    }
}


/*
*  Destroy linked list
*/
void destroy_list(p_node *head) {
    while (!is_list_empty(*head)) {
        remove_ini(head);
    }
}


/*
*  Destroy image
*/
void destroy_image(p_image *I) {
    if ((*I) != NULL) {
        for (int i = 0; i < (*I)->height; i++) {
            free((*I)->position[i]);
        }
        free((*I)->position);
        free((*I));
        (*I) == NULL;
    }
}


/*
*  Function to get a node in an index
*/
p_node get_node(p_node head, int index) {
    p_node current = head;
    int i = 0;
    while (current->prox != NULL) {
        if (i == index) {
            return current;
        }
        else {
            current = current->prox;
            i++;
        }
    }
}


/*
*  Returns adjancent pixels of P
*/
p_pixel get_adjacents(struct pixel P) {
    struct pixel pixels[8] = {
        {P.x - 1, P.y - 1},
        {P.x - 1, P.y},
        {P.x - 1, P.y + 1},
        {P.x, P.y - 1}, 
        {P.x, P.y + 1},
        {P.x + 1, P.y - 1},
        {P.x + 1, P.y},
        {P.x + 1, P.y + 1},
    };

    return pixels;
}


/*
*  Finds the smallest value between the adjacents pixels and atributes to the main pixel
*/
void Erosion(p_node *head, int n, int m) {
    p_node temp = calloc(n * m, sizeof(struct node));
    int ref_value, value;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ref_value = 1;
            struct pixel P = {i, j};
            p_pixel pixels = get_adjacents(P);

            for (int k = 0; k < 8; k++) {
                if ((pixels[k].x >= 0) && (pixels[k].y >= 0) && (pixels[k].x < n) && (pixels[k].y < m)) {
                    value = get_node(&head, i * m + j)->data;

                    if (value < ref_value) {
                        ref_value = value;
                    }
                }
            }
            temp[i * m + j].data = ref_value;


            // Copies the eroded values to the original list
            p_node p = get_node(&head, i * m + j);
            p->data = temp[i * m + j].data;
        }
    }

    free(temp);
}


/*
*
*/
void Dilatation