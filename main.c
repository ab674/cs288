#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

#define OK 1
#define NOK 0
#define NELM 10000000
//#define N 1048576
//#define N 2097152
//#define N 4194304
//#define N 8388608
//#define N 16777216
#define N 33554432

void selection_sort();
void swap();

void merge_sort();
void msort_recursive();
void merge();

void int_radix_sort();
void float_radix_sort();
void swap();
void self_check();

int rand(void);
void srand();
int rand_r();
void init_lst();
void print_lst();

int n, lst[N],tmp[N];

void selection_sort(int list[],int n) {
    int x, y;
    for (x = 0; x < n; x++) {
        int indx_min = x;
        for (y = x; y < n; y++) {
            if (list[indx_min] > list[y]) {
                indx_min = y;
            }
        }
        int tmp = list[x];
        list[x] = list[indx_min];
        list[indx_min] = tmp;
    }
}

void merge(int list[], int temp[], int left, int mid, int right) {
    int i, left_end, num_elements, tmp_pos;
    left_end =  mid-1;
    tmp_pos = left;
    num_elements = right-left+1;
    while ((left <= left_end) && (mid <= right)) {
        if (list[left] <= list[mid]) {
            temp[tmp_pos++] = list[left++];
        }
        else {
            temp[tmp_pos++] = list[mid++];
        }
    }
    while (left <= left_end) {
        temp[tmp_pos++] = list[left++];
    }
    while ( mid <= right) {
        temp[tmp_pos++] = list[mid++];
    }
    for (i = 0; i <= num_elements; i++) {
        list[right] = temp[right];
        right--;
    }
}

void msort_recursive(int list[], int temp[], int left, int right) {
    int mid;
    if (right > left) {
        mid = (right+left)/2;
        msort_recursive(list, temp, left, mid);
        msort_recursive(list, temp, mid+1, right);
        merge(list, temp, left, mid+1, right);
    }
}

void merge_sort(int list[], int temp[], int n) {
    msort_recursive(list, temp, 0, n-1);
}

void int_radix_sort(int lst[], int temp[], int n) {
    int group = 8;
    int bucket = 1<<group;
    int cnt[bucket];
    int map[bucket];
    int mask = bucket-1;
    int *src = NULL, *dest = NULL;
    int i, j, k, a, x, idx;
    idx = 32;
    for (a = 0; a < n; a++) {
        temp[a] = 0;
    }
    for (x = 0; x < idx; x = x+group) {
        if ((x % 2) == 0) {
            src = lst;
            dest = temp;
        }
        for (i = 0; i < bucket; i++) {
            cnt[i] = 0;
        }
        for (j = 0; j < n; j++) {
            cnt[src[j]>>x & mask]++;
            k = src[j]>>x & mask;
        }
        for (i = 0; i < bucket; i++) {
            map[i] = 0;
        }
        for (k = 1; k <= bucket; k++) {
            map[k] = (cnt[k-1] + map[k-1]);
        }
        for (i = 0; i < n; i++) {
            dest[map[src[i]>>x & mask]++] = src[i];
        }
    }
    for (i = 0; i < n; i++) {
        lst[i] = dest[i];
    }
}

void print_lst(int *l, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ",l[i]);
    }
    printf("\n");
}

void init_lst(int *l, int n) {
    int i;
    srand(1234);
    for (i = 0; i < n; i++) {
        l[i] = rand();
    }
}

void self_check(int *list, int n) {
    int i, flag = OK, *listp;
    listp = list;
    for (i = 0; i < n-1; i++) {
        if (listp[i] > listp[i+1]) {
            flag = NOK;
            break;
        }
    }
    if (flag == OK) {
        printf("LIST SORTED\n\n");
    }
    else {
        printf("LIST NOT SORTED AT %d\n\n", i);
    }
}

int main(int argc, char **argv) {
    long int del_sec, del_msec;
    struct timeval tv_s, tv_e;
    if (argc > 1) {
        n = atoi(argv[1]);
    }
    else {
        n = NELM;
    }
    printf("N = %d ELEMENTS\n", n);
    init_lst(lst, n);
    gettimeofday(&tv_s, NULL);
    selection_sort(lst, n);
    //merge_sort(lst, tmp, n);
    //int_radix_sort(lst, tmp, n);
    gettimeofday(&tv_e, NULL);
    del_sec = (tv_e.tv_sec-tv_s.tv_sec);
    del_msec = (tv_e.tv_usec-tv_s.tv_usec)/10000;
    printf("%1li.%06li FOR %d ELEMENTS\n", del_sec, del_msec, NELM);
    self_check(lst, n);
    return 0;
}
