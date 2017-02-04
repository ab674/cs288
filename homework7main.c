#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BF 4
#define N 4
#define NxN 16
#define DFS 1
#define BFS 2
#define BEST 3
#define BB 4
#define ASTAR 5
#define UNKNOWN 9

#define MAX_PATH 1000

#define DN 0
#define RT 1
#define UP 2
#define LT 3
#define UK 9

#define FVAL 0
#define GVAL 1
#define HVAL 2
#define PATH 3

#define TRUE 1
#define FALSE 0

int level, strategy;

int nodes_same(), str_compare(), count(), find_h();
void swap(), exit_proc(), print_a_node(), print_nodes();
int toggle_dir(), solvable();
void find_path(), print_path(), find_parent();
int path[MAX_PATH], path_buf[MAX_PATH];
void prep_dir_to_str(), dir_to_str();
char *dir_to_sdir[4], strategy_s[10];
int man_dist();
void sel_sort();

struct node {
    int board[N+1][N];
    struct node *next;
};

struct node *start, *goal;
struct node *initialize(), *expand(), *merge(), *filter(), *move(), *prepend(), *append();
struct node *insert_node(), *check_list(), *goal_found();


int main(int argc,char **argv) {
    int iter, cnt = 0, total = 1, ocnt = 0, ccnt = 0;
    int perm;
    struct node *cp, *open, *closed, *succ, *tp;
    open = closed = succ = NULL;
    start = initialize(argc, argv);
    perm = solvable(start);
    if (perm & 1) {
        return 1;
    }
    open = start;
    iter = 0;
    while (open) {
        printf("%d: open=%d + clsd=%d = total=%d\n", iter, ocnt, ccnt, ocnt+ccnt);
        ocnt = count(open);
        ccnt = count(closed);
        cp = open;
        open = open->next;
        cp->next = NULL;
        succ = expand(cp);
        succ = filter(succ, open);
        succ = filter(succ, closed);
        cnt = count(succ);
        total = total+cnt;
        if (succ) {
            open = merge(succ, open, strategy);
        }
        closed = append(cp, closed);
        if ((cp = goal_found(succ, goal))) {
            break;
        }
        iter++;
    }
    printf("%s strategy: %d iterations %d nodes\n",strategy_s, iter+1, total);
    find_path(cp, open, closed);
    return 0;
}

int toggle_dir(int dir) {
    int opp_dir;
    return opp_dir;
}

void print_path(int n, int *path) {
    int i, p;
    for (i = n-1; i >= 0; i--) {
        p = *(path+i);
        if (i > 0) {
            printf("%s -> ", dir_to_sdir[p]);
        }
        else {
            printf("%s", dir_to_sdir[p]);
        }
    }
    printf("\n");
}

void prep_dir_to_str(){
}

void find_path(struct node *cp, struct node *opnp, struct node *cldp) {
    int i, j, dir, opp_dir;
    char *sdir, *opp_sdir;
    int path_cnt = 0, p;
    struct node *tp;
}

void find_parent(struct node *cp, int prev_dir){
    int i, j, k, cnt, row = 0, col = j;
}

struct node *expand(struct node *cp) {
    int i, j, k, cnt, row = 0, col = j;
    struct node *succ, *tp;
    succ = NULL;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            if (cp->board[i][j] == 0) break;
        if (j < N) break;
    }
    if ((i+1) < N) {
        tp = move(cp, i, j, i+1, j, DN);
        succ = append(tp, succ);
    }
    if ((j+1) < N) {
        tp = move(cp, i, j, i, j+1, RT);
        succ = append(tp, succ);
    }
    if ((i-1) < N) {
        tp = move(cp, i, j, i-1, j, UP);
        succ = append(tp, succ);
    }
    if ((j-1) < N) {
        tp = move(cp, i, j, i, j-1, LT);
        succ = append(tp, succ);
    }
    return succ;
}

struct node *prepend(struct node *tp, struct node *sp) {
    struct node *temp = malloc(sizeof(struct node));
    for (int i = 0; i < N+1; i++) {
        for(int j = 0; j < N; j++) {
            temp->board[i][j] = tp->board[i][j];
        }
    }
    struct node *cp;
    cp = sp;
    if (cp == NULL) {
        sp = temp;
    }
    else {
        temp->next = sp;
        sp = temp;
    }
    return sp;
}

struct node *append(struct node *tp, struct node *sp) {
    struct node *cp;
    cp = malloc(sizeof(struct node));
    cp = sp;
    if (cp == NULL) {
        sp = tp;
    }
    else {
        while (cp->next) {
            cp = cp->next;
        }
        tp->next = NULL;
        cp->next = tp;
    }
    return sp;
}

void swap(struct node *cp, int i, int j, int k, int l) {
    int tmp;
}

struct node *move(struct node *cp, int a, int b, int x, int y, int dir) {
    struct node *newp;
    int i, j, k, l, tmp, f, g, h;
    newp = malloc(sizeof(struct node));
    for(i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            newp->board[i][j] = cp->board[i][j];
        }
    }
    tmp = newp->board[a][b];
    newp->board[a][b] = newp->board[x][y];
    newp->board[x][y] = tmp;
    g = count(newp);
    h = man_dist(newp);
    f = g + h;
    newp->board[4][0] = f;
    newp->board[4][1] = g;
    newp->board[4][2] = h;
    newp->board[4][3] = dir;
    return newp;
}

struct node *goal_found(struct node *cp, struct node *gp) {
    int flag = FALSE;
    while (cp) {
        if (flag == nodes_same(cp, gp)) {
            return cp;
        }
        cp = cp->next;
    }
    return 0;
}

int count(struct node *cp) {
    int cnt = 0;
    while (cp) {
        cnt++;
        cp = cp->next;
    }
    return cnt;
}

struct node *merge(struct node *succ, struct node *open, int flg) {
    struct node *csucc, *copen, *tp;
    copen = open;
    csucc = succ;
    tp = malloc(sizeof(struct node));
    if (flg == DFS) {
    }
    else if (flg == BFS) {
    }
    else if (flg == BEST) {
    }
    else {
        if (open == NULL) {
            while (csucc) {
                struct node *tp = malloc(sizeof(struct node));
                tp->next = NULL;
                for (int i = 0; i < N+1; i++) {
                    for (int j = 0; j < N; j++) {
                        tp->board[i][j] = csucc->board[i][j];
                    }
                }
                copen = insert_node(tp, copen);
                csucc = csucc->next;
            }
        }
        else {
            while (csucc != NULL) {
                copen = insert_node(csucc, copen);
                csucc = csucc->next;
            }
        }
    }
    return open;
}

struct node *insert_node(struct node *succ, struct node *open, int x) {
    int cnt = 0;
    struct node *copen, *topen, *csucc, *new_open = NULL;
    struct node *tp = malloc(sizeof(struct node));
    tp->next = NULL;
    copen = malloc(sizeof(struct node));
    copen->next = NULL;
    topen = malloc(sizeof(struct node));
    topen->next = NULL;
    csucc = succ;
    copen = open;
    if (open == NULL) {
        return succ;
    }
    else {
        while (copen) {
            if (csucc->board[4][0] < copen->board[4][0]) {
                if (cnt == 0) {
                    new_open = prepend(csucc, copen);
                    break;
                }
                else if (cnt != 0) {
                    for (int i = 0; i < N+1; i++) {
                        for (int j = 0; j < N; j++) {
                            tp->board[i][j] = csucc->board[i][j];
                        }
                    }
                    topen->next = tp;
                    tp->next = copen;
                    new_open = open;
                    break;
                }
            }
            if (new_open != NULL) {
                break;
            }
            cnt++;
            topen = copen;
            copen = copen->next;
        }
    }
    if (new_open != NULL) {
        return new_open;
    }
    else {
        copen = open;
        return new_open = append(csucc, copen);
    }
}

int find_h(int current[N+1][N], int goalp[N+1][N]) {
    int h = 0, i, j, k, l, done;
    return h;
}

int nodes_same(struct node *xp, struct node *yp) {
    int i, j, flg = FALSE;
    int cnt = 0;
    if (xp == NULL) {
    }
    else if (yp == NULL) {
    }
    else {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (xp->board[i][j] == yp->board[i][j]) {
                    cnt++;
                }
            }
        }
    }
    if (cnt == 16) {
        flg = TRUE;
    }
    return flg;
}

struct node *filter(struct node *succ, struct node *hp) {
    struct node *lsp, *rsp;
    struct node *tp;
    lsp = rsp = succ;
    if (hp == NULL) {
        return succ;
    }
    else {
        while (rsp) {
            tp = hp;
            while (tp && rsp) {
                if (nodes_same(tp, rsp)) {
                    if (lsp == rsp) {
                        lsp = rsp = rsp->next;
                        succ = succ->next;
                        if (hp != NULL) {
                            tp = hp;
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        lsp->next = rsp->next;
                        if (rsp->next) {
                            rsp = rsp->next;
                        }
                        else {
                            break;
                        }
                    }
                }
                else
                    tp = tp->next;
            }
            lsp = rsp;
            if (rsp != NULL) {
                rsp = rsp->next;
            }
        }
    }
    return succ;
}

void print_nodes(struct node *cp, char name[20]) {
    printf("%s:\n", name);
    while (cp) {
        print_a_node(cp);
        cp=cp->next;
    }
}

void print_a_node(struct node *np) {
    int i, j;
    for (i = 0; i < N+1; i++) {
        for (j = 0; j < N; j++) {
            printf("%2d ", np->board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int solvable(struct node *cp) {
    int i = 0, j = 0, k = 0, lst[NxN], cnt = 0, total = 0, num1 = 0, num2 = 0, num3 = 0, num4 = 0, temp1 = 0, temp2 = 0;
    int gboard[N][N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    while (i < NxN) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                if (cp->board[j][k] == i) {
                    num1 = j;
                    num2 = k;
                }
            }
        }
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                if (gboard[j][k] == i) {
                    num3 = j;
                    num4 = k;
                }
            }
        }
        temp1 = abs(n1-n3);
        temp2 = abs(n2-n4);
        lst[i] = temp1+temp2;
        i++;
    }
    for (i = 0; i < NxN; i++) {
        cnt = cnt+lst[i];
    }
    total = cnt/(NxN - 1);
    printf("Permutation is: ");
    if (total%2 != 0) {
        printf("odd (%i)\n", total);
    }
    else {
        printf("even (%i)\n", total);
    }
    return total;
}

struct node *initialize(int argc, char **argv) {
    int i, j, k, npe, n, idx, gidx, inv;
    struct node *tp;
    tp = (struct node *) malloc(sizeof(struct node));
    idx = 1;
    for (j = 0; j < N; j++) {
        for (k = 0; k < N; k++) {
            tp->board[j][k] = atoi(argv[idx++]);
        }
    }
    for (k = 0; k < N; k++) {
        tp->board[N][k] = 0;
    }
    tp->next = NULL;
    start = tp;
    printf("init state: \n");
    print_a_node(start);
    tp = (struct node *) malloc(sizeof(struct node));
    gidx = 1;
    for (j = 0; j < N; j++) {
        for (k = 0; k < N; k++) {
            tp->board[j][k] = gidx++;
        }
    }
    tp->board[N-1][N-1] = 0;
    for (k = 0; k < N; k++) {
        tp->board[N][k] = 0;
    }
    tp->next = NULL;
    goal = tp;
    printf("goal state: \n");
    print_a_node(goal);
    strcpy(strategy_s, argv[idx]);
    if (strcmp(strategy_s, "dfs") == 0) {
        strategy = DFS;
    }
    else if (strcmp(strategy_s, "bfs") == 0) {
        strategy = BFS;
    }
    else if (strcmp(strategy_s, "best") == 0) {
        strategy = BEST;
    }
    else if (strcmp(strategy_s, "bb") == 0) {
        strategy = BB;
    }
    else if (strcmp(strategy_s, "astar") == 0) {
        strategy = ASTAR;
    }
    else {
        strategy = UNKNOWN;
    }
    printf("strategy=%s\n", strategy_s);
    return start;
}

void exit_proc(char *msg) {
    printf("Error: %s\n", msg);
    exit(1);
}

void sel_sort(int list[], int n) {
    int temp, i, k;
    for (i = 0; i < n; i++) {
        for (k = 0; k < n; k++) {
            if (list[i] > list[k] && i < k) {
                temp = list[i];
                list[i] = list[k];
                list[k] = temp;
            }
        }
    }
}

int man_dist(struct node *cp) {
    int i = 0, j = 0, k = 0, lst[NxN], cnt = 0, total = 0, num1 = 0, num2 = 0, num3 = 0, num4 = 0, temp1 = 0, temp2 = 0;
    int gboard[N][N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    while (i < NxN) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                if (cp->board[j][k] == i) {
                    num1 = j;
                    num2 = k;
                }
            }
        }
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                if (gboard[j][k] == i) {
                    num3 = j;
                    num4 = k;
                }
            }
        }
        temp1 = abs(n1-n3);
        temp2 = abs(n2-n4);
        lst[i] = temp1+temp2;
        i++;
    }
    for (i = 0; i < NxN; i++) {
        cnt = cnt+lst[i];
    }
    return cnt;
}
