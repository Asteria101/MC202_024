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
    struct node *prox;
};

typedef struct node *p_node;

struct pixel {
    int x, y; // coordinates
};

typedef struct pixel *p_pixel;

struct image {
    int **position;
    int width, height;
};

typedef struct image *p_image;


/* Global variables */
FILE *p_out_file = NULL;
p_node head = NULL;


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
    }

    for (int y = 0; y < I->height; y++) {
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
*  Prints the linked list as a 2D matrix
*/
void print_list(p_node head, int rows, int columns) {
    p_node current = head;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (current != NULL) {
                printf("%d ", current->data);
                char data = current->data + '0';

                if (p_out_file != NULL) {
                    fprintf(p_out_file, "%c ", data);
                }
                current = current->prox;
            }
        }
        printf("\n");
        if (p_out_file != NULL) {
            fprintf(p_out_file, "\n");
        }
    }
}


/*
*  Recieves the elements from the image and store in a list
*/
void fill_list(p_image I) {
    for (int i = 0; i < I->height; i++) {
        for (int j = 0; j < I->width; j++) {
            insert_end(&head, I->position[i][j]);
        }
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
    }
}


/*
*  Function to get a node in an index
*/
p_node get_node(p_node head, int index) {
    p_node current = head;
    int i = 0;
    while (current != NULL) {
        if (i == index) {
            return current;
        }
        current = current->prox;
        i++;
    }

    return NULL;
}


/*
*  Returns adjancent pixels of P
*/
p_pixel get_adjacents(struct pixel P) {
    p_pixel pixels = calloc(8, sizeof(struct pixel));
    pixels[0].x = P.x - 1;
    pixels[0].y = P.y - 1;

    pixels[1].x = P.x - 1;
    pixels[1].y = P.y;

    pixels[2].x = P.x - 1;
    pixels[2].y = P.y + 1;

    pixels[3].x = P.x;
    pixels[3].y = P.y - 1;

    pixels[4].x = P.x;
    pixels[4].y = P.y + 1;

    pixels[5].x = P.x + 1;
    pixels[5].y = P.y - 1;

    pixels[6].x = P.x + 1;
    pixels[6].y = P.y;

    pixels[7].x = P.x + 1;
    pixels[7].y = P.y + 1;

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
            struct pixel P;
            P.x = i;
            P.y = j;
            p_pixel pixels = get_adjacents(P);

            for (int k = 0; k < 8; k++) {
                if ((pixels[k].x >= 0) && (pixels[k].y >= 0) && (pixels[k].x < n) && (pixels[k].y < m)) {
                    value = get_node(*head, pixels[k].x * m + pixels[k].y)->data;

                    if (value < ref_value) {
                        ref_value = value;
                    }
                }
            }
            temp[i * m + j].data = ref_value;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Copies the eroded values to the original list
            p_node p = get_node(*head, i * m + j);
            p->data = temp[i * m + j].data;
        }
    }

    free(temp);
}


/*
*  Finds the maximun value between the adjacents pixels and atributes to the main pixel
*/
void Dilatation(p_node *head, int n, int m) {
    p_node temp = calloc(n * m, sizeof(struct node));
    int ref_value, value;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ref_value = 0;
            struct pixel P = {i, j};
            p_pixel pixels = get_adjacents(P);

            for (int k = 0; k < 8; k++) {
                if ((pixels[k].x >= 0) && (pixels[k].y >= 0) && (pixels[k].x < n) && (pixels[k].y < m)) {
                    value = get_node(*head, pixels[k].x * m + pixels[k].y)->data;

                    if (value > ref_value) {
                        ref_value = value;
                    }
                }
            }
            temp[i * m + j].data = ref_value;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Copies the eroded values to the original list
            p_node p = get_node(*head, i * m + j);
            p->data = temp[i * m + j].data;
        }
    }

    free(temp);
}


/*
*  Softens the borders, breaks up narrowings and eliminates final projections
*/
void Opening(p_node *head, int n, int m) {
    Erosion(head, n, m);
    Dilatation(head, n, m);
}


/*
*  Softens the borders, fill in holes and joins narrowings
*/
void Closing(p_node *head, int n, int m) {
    Dilatation(head, n, m);
    Erosion(head, n, m);
}


/*
* Prints the results
*/
void results(p_image I, int columns, int rows) {
    printf("Dilation\n");
    if (p_out_file != NULL) {
        fprintf(p_out_file, "%s\n", "Dilation");
    }
    Dilatation(&head, columns, rows);
    print_list(head, rows, columns);
    destroy_list(&head);
    fill_list(I);

    printf("Erosion\n");
    if (p_out_file != NULL) {
        fprintf(p_out_file, "%s\n", "Erosion");
    }
    Erosion(&head, columns, rows);
    print_list(head, rows, columns);
    destroy_list(&head);
    fill_list(I);

    printf("Opening\n");
    if (p_out_file != NULL) {
        fprintf(p_out_file, "%s\n", "Opening");
    }
    Opening(&head, columns, rows);
    print_list(head, rows, columns);
    destroy_list(&head);
    fill_list(I);

    printf("Closing\n");
    if (p_out_file != NULL) {
        fprintf(p_out_file, "%s\n", "Closing");
    }
    Closing(&head, columns, rows);
    print_list(head, rows, columns);
    destroy_list(&head);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        Error(
            "%s <arquivo texto de entrada> [<arquivo texto de saida>]\n"
            "Por exemplo, ./main ./arq1.in ./arq1.out\n", "main", argv[0]
            );
    }

    char *out_file = argv[2];
    if (out_file != NULL) {
        p_out_file = fopen(argv[2], "w");

        if (p_out_file == NULL) {
            printf("Falha na abertura do arquivo\n");
            return -1;
        }
    }

    p_image Image = NULL;
    Image = read_image(argv[1]);

    int rows = Image->width; 
    int columns = Image->height;

    fill_list(Image);

    results(Image, columns, rows);

    destroy_image(&Image);

    if (p_out_file != NULL) {
        fclose(p_out_file);
    }

    return 0;
}