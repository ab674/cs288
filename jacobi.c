#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define N 100
#define MAX_ITER 10000

int jacobi();
void init();
int convergence();
void srand();
void print_vector();
void print_equation();

float a[N][N], b[N];
float x[N], buf[N];
int n;
float error;

int main(int argc, char **argv) {
    int n_iter;
    n = atoi(argv[1]);
    error = atof(argv[2]);
    init();
    n_iter = jacobi();
    return 0;
}

int jacobi() {
    int i, j, k = 0;
    float sum;
    do {
        for (i = 0; i < n; i++) {
            sum = 0;
            for (j = 0; j < n; j++) {
                if (i != j) {
                    sum = sum + a[i][j] * x[j];
                }
            }
            buf[i] = (b[i] - sum) / a[i][i];
        }
        for (i = 0; i < n; i++) {
            x[i] = buf[i];
        }
        k++;
    }
    while (!convergence(k));
    printf("K: %i\n", k);
    printf("Solution: ");
    for (i = 0; i < n; i++) {
        printf("%f ", buf[i]);
    }
    printf("\n");
    return k;
}

int convergence(int iter) {
    int i, j, flag = 0, count = 0;
    float sum, temp[N];
    for(i = 0; i < n; i++) {
        sum = 0;
        for (j = 0; j < n; j++) {
            sum = sum + a[i][j] * x[j];
        }
        temp[i] = sum-b[i];
    }
    for (i = 0; i < n; i++) {
        if (fabs(temp[0]) < error) {
            count++;
            flag = 1;
        }
    }
    return flag;
}

void init(char **argv){
    int i, j;
    float sum;
    int seed = time(0) % 100;
    srand(seed);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            a[i][j] = rand() & 0x7;
            if (rand() & 0x1) {
                a[i][j] = -a[i][j];
            }
        }
        sum = 0;
        for (j = 0; j < n; j++) {
            if (i != j) {
                sum = sum + abs(a[i][j]);
            }
        }
        if (a[i][i] < sum) {
            a[i][i] = sum + a[i][i];
        }
    }
    for (i = 0; i < n; i++) {
        x[i]=1;
    }
    srand(seed);
    for (i = 0; i < n; i++) {
        b[i] = rand() & 0x7;
        if (rand() & 0x1) {
            b[i] = -b[i];
        }
    }
    print_equation();
}

void print_equation() {
    int i, j;
    printf("A*x=b\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%2d ", (int) (a[i][j]));
        }
        printf(" * x%d = %d\n", i, (int) (b[i]));
    }
    printf("\n");
}

void print_vector(float *l) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%.6f ", l[i]);
    }
    printf("\n");
}
