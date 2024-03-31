#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


#ifndef bool
typedef enum Bool {false, true} bool;
#endif

typedef struct Point {
    int x, y, z;
}point;

typedef struct Maze {
    char ***data;
    int nx, ny, nz; // dimensions
    int n_entries, n_exits; // number of entries and exits in the maze
    point *entry, *exit;
}maze;

typedef maze *p_maze;


void Erro(char *msg, char *funcao, ...) {
    va_list args; /* lista de argumentos */
    char msg_final[4096];

    va_start(args, funcao); /* inicializa a lista args para recuperar argumentos após o argumento funcao */
    vsprintf(msg_final, msg, args); /* envia a lista inteira de argumentos em args para formatação em msg_final */
    va_end(args); /* finaliza o processo de recuperação */

    printf("Erro em %s: %s\n",funcao,msg_final);
    fflush(stdout);
    exit(1);
}


/* 
* Reads the information to build the maze from a file
*/
p_maze read_info(char *filename) {
    FILE *fp = fopen(filename, "r");

    p_maze M = (p_maze)calloc(1, sizeof(maze));

    //scanf("%d %d %d %d\n", &M->nx, &M->ny, &M->nz, &M->n_entries);

    fscanf(fp, "%d %d %d %d\n", &M->nx, &M->ny, &M->nz, &M->n_entries);

    M->entry = (point *)calloc(M->n_entries, sizeof(point));
    M->exit = (point *)calloc(M->n_entries, sizeof(point));

    // allocating memory for the maze
    M->data = (char ***)calloc(M->nz, sizeof(char **));

    for (int z = 0; z < M->nz; z++) {
        M->data[z] = (char **)calloc(M->ny, sizeof(char *));
        for (int y = 0; y < M->ny; y++) {
            M->data[z][y] = (char *)calloc(M->nx, sizeof(char));
        }
    }

    // writing on the maze
    int j = 0, i = 0;
    for (int z = 0; z < M->nz; z++) {
        for (int y = 0; y < M->ny; y++) {
            for (int x = 0; x < M->nx; x++) {
                fscanf(fp, "%c   ", &M->data[z][y][x]);

                if (M->data[z][y][x] == 'E') {
                    M->entry[i].z = z, M->entry[i].y = y, M->entry[i].x = x;
                    M->data[z][y][x] = 'P';
                    i++;
                }
                else {
                    if (M->data[z][y][x] == 'S') {
                        M->exit[j].z = z, M->exit[j].y = y, M->exit[j].x = x;
                        M->data[z][y][x] = 'P';
                        j++;
                        M->n_exits = j;
                    }
                }
            }
            fscanf(fp, "\n");
        }
    }

    fclose(fp);
    return M;
}


/*
* Frees the allocated memory for the maze
*/
void destroy_maze(p_maze M) {
    if (M == NULL) exit(1);
    
    if (M->data != NULL) {
        for (int z = 0; z < M->nz; z++) {
            if (M->data[z] != NULL) {
                for (int y = 0; y < M->ny; y++) {
                    if (M->data[z][y] != NULL) {
                        free(M->data[z][y]);
                    }
                }
                free(M->data[z]);
            }
        }
        free(M->data);
    }
    free(M);
    M = NULL;
}


/*
* Determines if the entrance leads to an exit
*/
bool backtrack(p_maze M, point P) {
    bool ans = false;
    
    for (int j = 0; j < M->n_exits; j++) {
        if ((P.z == M->exit[j].z) && (P.y == M->exit[j].y) && (P.x == M->exit[j].x)) {
            return true;
        }
        else {
            point *C = (point *)calloc(6, sizeof(point));

            C[0].z = P.z;
            C[0].y = P.y;
            C[0].x = P.x - 1;

            C[1].z = P.z;
            C[1].y = P.y;
            C[1].x = P.x + 1;

            C[2].z = P.z;
            C[2].y = P.y - 1;
            C[2].x = P.x;

            C[3].z = P.z;
            C[3].y = P.y + 1;
            C[3].x = P.x;

            C[4].z = P.z - 1;
            C[4].y = P.y;
            C[4].x = P.x;

            C[5].z = P.z + 1;
            C[5].y = P.y;
            C[5].x = P.x;

            for (int i = 0; (i < 6) && (ans != true); i++) {
                if ((C[i].z >= 0) && (C[i].z < M->nz) && (C[i].y >= 0) && (C[i].y < M->ny) && (C[i].x >= 0) && (C[i].x < M->nx)) {
                    if (M->data[C[i].z][C[i].y][C[i].x] != 'X') {
                        char correct_value = M->data[C[i].z][C[i].y][C[i].x];
                        M->data[C[i].z][C[i].y][C[i].x] = 'X';

                        ans = backtrack(M, C[i]);
                        M->data[C[i].z][C[i].y][C[i].x] = correct_value;
                    }
                }
            }
            free(C);
        }
    }
    
    return ans;
}


int main(int argc, char **argv) {
    p_maze Maze = NULL;

    if (argc != 2) {
        Erro("%s <arquivo texto do labirinto>", "main", argv[0]); 
    }

    Maze = read_info(argv[1]);
    //Maze = read_info();

    /*for (int i = 0; i < Maze->nz; i++) {
        for (int j = 0; j < Maze->ny; j++) {
            for (int k = 0; k < Maze->nx; k++) {
                printf("%c   ", Maze->data[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }*/

    for (int i = 0; i < Maze->n_entries; i++) {
        if (backtrack(Maze, Maze->entry[i])) {
            printf("[Entrada %d] Saída encontrada!\n", i);
        }
        else {
            printf("[Entrada %d] Saída não encontrada!\n", i);
        }
    }

    destroy_maze(Maze);
    return 0;
}