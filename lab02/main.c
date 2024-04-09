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


/* 
* Reads the information to build the maze from a file
*/
p_maze read_info(char *filename) {
    FILE *fp = fopen(filename, "r");

    p_maze M = (p_maze)calloc(1, sizeof(maze));

    fscanf(fp, "%d %d %d %d\n", &M->nx, &M->ny, &M->nz, &M->n_entries);

    M->entry = (point *)calloc(M->n_entries, sizeof(point));
    M->exit = (point *)calloc(M->n_entries, sizeof(point));

    // allocating memory for the maze
    M->data = (char ***)calloc(M->nz, sizeof(char **));

    int j = 0, i = 0;
    for (int z = 0; z < M->nz; z++) {
        M->data[z] = (char **)calloc(M->ny, sizeof(char *));

        for (int y = 0; y < M->ny; y++) {
            M->data[z][y] = (char *)calloc(M->nx, sizeof(char));

            for (int x = 0; x < M->nx; x++) {
                fscanf(fp, "%c", &M->data[z][y][x]);
                fscanf(fp, "   ");

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
* Frees allocated memory for the maze
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
    
    // checks if point is an exit
    for (int j = 0; j < M->n_exits; j++) {
        if ((P.z == M->exit[j].z) && (P.y == M->exit[j].y) && (P.x == M->exit[j].x)) {
            return ans = true;
        }
    }
    
    point neighbors[6] = {
        {P.x - 1, P.y, P.z}, 
        {P.x + 1, P.y, P.z}, 
        {P.x, P.y - 1, P.z}, 
        {P.x, P.y + 1, P.z},
        {P.x, P.y, P.z - 1},
        {P.x, P.y, P.z + 1}
    };

    for (int i = 0; (i < 6) && (ans != true); i++) {
        if ((neighbors[i].z >= 0) && (neighbors[i].z < M->nz) && (neighbors[i].y >= 0) && (neighbors[i].y < M->ny) && (neighbors[i].x >= 0) && (neighbors[i].x < M->nx)) {
            if (M->data[neighbors[i].z][neighbors[i].y][neighbors[i].x] != 'X') {
                char correct_value = M->data[neighbors[i].z][neighbors[i].y][neighbors[i].x];
                M->data[neighbors[i].z][neighbors[i].y][neighbors[i].x] = 'X';
                ans = backtrack(M, neighbors[i]);
                M->data[neighbors[i].z][neighbors[i].y][neighbors[i].x] = correct_value;
            }
        }
    }

    return ans;
}


int main(int argc, char **argv) {
    p_maze Maze = NULL;

    if (argc != 2) {
        Error("%s <arquivo texto do labirinto>", "main", argv[0]); 
    }

    Maze = read_info(argv[1]);

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
