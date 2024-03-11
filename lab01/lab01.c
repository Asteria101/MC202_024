#include <stdio.h>
#include <stdlib.h>

#define MAX_DIM 100


typedef struct point {
  int x, y;
} Point;

// y = mx + n
typedef struct line {
  Point ini, end;
  float slope; // m
  float y_intercept; // n
} Line;


/*
* Create and initialize matrix NxN
*/
int **create_matrix(int N) {
    int **matrix = (int **)calloc(N, sizeof(int *));

    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)calloc(N, sizeof(int));
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}


/*
* Prints matrix
*/
void print_matrix(int **matrix, int N) {
    for (int i = 0; i < N; i++) {
        printf("[ ");
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("]\n");
    }
}


/*
* Free allocated memory for matrix
*/
void free_matrix(int **matrix, int N) {
    if (matrix != NULL) {
        for (int i = 0; i < N; i++) {
            if (matrix[i] != NULL) {
                free(matrix[i]);
            }
        }
        free(matrix);
    }
}


/*
* Define line coefficients
*/
void define_coefficients(Line *line) {
    if ((line->end.y != line->ini.y) && (line->end.x != line->ini.x)) {
        float end_y = (float)line->end.y, ini_y = (float)line->ini.y, end_x = (float)line->end.x, ini_x = (float)line->ini.x;
        line->slope = (end_y - ini_y) / (end_x - ini_x);
    }
    else {
        line->slope = 0;
    }

    if (line->ini.x == 0) {
        line->y_intercept = line->ini.y;
    } 
	else if (line->end.x == 0) {
		line->y_intercept = line->end.y;
	}
	else {
        line->y_intercept = line->ini.y - line->ini.x * line->slope;
    }
}


/*
* Draw lines in matrix
*/
void draw_lines(int **matrix, int N, Line line) {
    float y = line.ini.y;
	for (int x = line.ini.x; x < line.end.x; x++) {
        if (x >= N || y >= N) break;

		y = ((line.slope * x) + line.y_intercept);
		
		int a = 99 - (int)y;
		if (y >= 0 && x >= 0) {
			matrix[a][x] = 1;
		}
	}

    // vertical lines
    if (line.slope == 0 && line.y_intercept == 0) {
        for (int y = line.ini.y; y < line.end.y; y++) {
            matrix[y][line.ini.x] = 1;
        }
    }
}


/*
* Verify if and/or where the lines intercept
*/
int verify_intersection(Line line_1, Line line_2, Point *intersection) {
	if (line_1.slope == line_2.slope) {
        float slope = line_1.slope;

        // vertical lines (x = a)
        if ((line_1.ini.x == line_1.end.x) && (line_2.ini.x == line_2.end.x)) {
            if (line_1.ini.x == line_2.ini.x) {
                return 2;
            }
            return 0;
        }
        // horizontal lines (y = b)
        else if ((line_1.ini.y == line_1.end.y) && (line_2.ini.y == line_2.end.y)) {
            if (line_1.ini.y == line_2.ini.y) {
                return 2;
            }
            return 0;
        }
        // line with slope != 0
        else if (slope != 0) {
            if (line_1.y_intercept == line_2.y_intercept) {
                return 2;
            }
            return 0;
        }
		return 0;
    }

	else {
        float x, y;

        if ((line_1.y_intercept != line_2.y_intercept) && (line_1.slope != line_2.slope)) {
            x = -1 * (line_1.y_intercept - line_2.y_intercept) / (line_1.slope - line_2.slope);
            y = line_1.slope * x + line_1.y_intercept;
        }
        else {
            if (line_1.slope == 0) {
                x = line_1.ini.x;
            }
            else if (line_2.slope == 0) {
                x = line_2.ini.x;
            }
            y = x;
        }

        intersection->x = (int)x;
        intersection->y = (int)y;
		
		return 1;
	}

  	return -1;
}


int main(int argc, char *argv[]) {
    Line line_1, line_2;

    /* Read file */
    /*FILE *fp = fopen(argv[1], "r");

    fscanf(
    fp, "(%d %d %d %d) ",
    &line_1.ini.x, &line_1.ini.y, &line_1.end.x, &line_1.end.y
    );

    fscanf(
    fp, "(%d %d %d %d)",
    &line_2.ini.x, &line_2.ini.y, &line_2.end.x, &line_2.end.y
    );

    fclose(fp);*/
    /* End of file */

    /* test 03 - incorrect (zeros where should be ones and vice versa) */
    line_1.ini.x = -20, line_1.ini.y = -20, line_1.end.x = 50, line_1.end.y = 60;
    line_2.ini.x = -30, line_2.ini.y = -20, line_2.end.x = 50, line_2.end.y = 30;

    int **matrix = create_matrix(MAX_DIM);

    define_coefficients(&line_1);
    define_coefficients(&line_2);

    draw_lines(matrix, MAX_DIM, line_1);
    draw_lines(matrix, MAX_DIM, line_2);

	Point intersection;
	int status = verify_intersection(line_1, line_2, &intersection);

	if (status == 0) {
		printf("Retas são paralelas\n");
	}
	else if (status == 1) {
		printf("Retas são concorrentes\n");
		if ((intersection.x > 0 && intersection.x < MAX_DIM) && (intersection.y > 0 && intersection.y < MAX_DIM)) {
			printf("Intersecção ocorre na matriz\n");
			// Mark intersection with 2
			matrix[99 - intersection.y][intersection.x] = 2;
		}
		else {
			printf("Intersecção ocorre fora da matriz\n");
		}

		printf("Intersecção: (%d, %d)\n", intersection.x, intersection.y);

	}
	else if (status == 2) {
		printf("Retas são coincidentes\n");
	}

    print_matrix(matrix, MAX_DIM);
	free_matrix(matrix, MAX_DIM);

    return 0;
}