#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 300

struct clip *build_a_lst();
struct clip *append();
int find_length();
void print_lst();
void split_line();

struct clip {
    char *user;
    int views;
    char *time;
    int id;
    char *title;
    struct clip *next;
} *head;

int main(int argc, char **argv) {
    int n;
    head = build_a_lst(*(argv+1));
    n = find_length(head);
    printf("%d clips\n", n);
    print_lst(head);
    return 0;
}

void split_line(char **fields, char *line) {
    int i = 0;
    char *token, *delim;
    delim = ",\n";
    token = strtok(line, delim);
    fields[i] = malloc(strlen(token));
    strcpy(fields[i], token);
    i++;
    while (token) {
        token = strtok(NULL, delim);
        if (token != NULL) {
            fields[i] = malloc(strlen(token));
            strcpy(fields[i], token);
            i++;
        }
    }
}

struct clip *append(struct clip* hp, char **five) {
    struct clip* cp = hp;
    struct clip* tp = NULL;
    int i = 0;
    char string1[500];
    char string2[500];
    char string3[500];
    tp = malloc(sizeof(struct clip));
    tp->next = NULL;
    strcpy(string1, five[i]);
    tp->user = malloc(sizeof(string1));
    strcpy(tp->user, string1);
    tp->views = atoi(five[++i]);
    strcpy(string2, five[++i]);
    tp->time = malloc(sizeof(string2));
    strcpy(tp->time, string2);
    tp->id = atoi(five[++i]);
    strcpy(string3, five[++i]);
    tp->title = malloc(sizeof(string3));
    strcpy(tp->title, string3);
    if (cp == NULL) {
        hp = tp;
    }
    else {
        while (cp->next != NULL) {
            cp = cp->next;
        }
        cp->next = tp;
    }
    return hp;
}

struct clip *build_a_lst(char *fn) {
    FILE *fp;
    struct clip *hp = NULL;
    char *fields[5];
    char line[LINE_LENGTH];
    fp = fopen(fn, "r");
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        split_line(fields, line);
        hp = append(hp, fields);
    }
    fclose(fp);
    return hp;
}

int find_length(struct clip *hp) {
    int count = 0;
    struct clip* cp = hp;
    while (cp) {
        count++;
        cp = cp->next;
    }
    return count;
}

void print_lst(struct clip *cp) {
    while (head != NULL) {
        printf("%s, %i, %s, %i, %s\n", head->user, head->views, head->time, head->id, head->title);
        head = head->next;
    }
}
