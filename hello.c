#include <stdio.h>

void argumentcounter(char counter[], char counteraddress[]);
void bufferline(int count);
void firstargument(char address[], char firstargumentaddress[]);
void footer();
void header();

int main(int argc, const char * argv[]) {
    
    header();
    
    int totalsize = ((argc+1)*4);
    int argcounter = 0;
    int letterarray[totalsize+1];
    for (int m = 0; m < totalsize+1; m++) {
        letterarray[m] = (int) *(*&argv[0]+m);
        if (letterarray[m] == 00) {
            argcounter++;
        }
        if (argcounter == argc) {
            letterarray[m] = 00;
        }
    }
    
    int memaddressarray[argc+1];
    int memaddressstring = (int) *&argv[0];
    for (int k = 0; k < argc+1; k++) {
        memaddressarray[k] = memaddressstring;
        memaddressstring += (4);
    }
    
    for (int l = argc; l >= 0; l--) {
        int localsplit1 = letterarray[3+(l*4)];
        int localsplit2 = letterarray[2+(l*4)];
        int localsplit3 = letterarray[1+(l*4)];
        int localsplit4 = letterarray[0+(l*4)];
        printf("       |  %.2x  |  %.2x  |  %.2x  |  %.2x  | %.8x \n", localsplit1, localsplit2, localsplit3, localsplit4, memaddressarray[l]);
        bufferline(1);
    }
    
    bufferline(3);
    
    int j = argc;
    char argumentstring[9];
    sprintf(argumentstring, "%.8x", (int) *&argv[j]);
    char localsplit1[3] = {argumentstring[0], argumentstring[1]};
    char localsplit2[3] = {argumentstring[2], argumentstring[3]};
    char localsplit3[3] = {argumentstring[4], argumentstring[5]};
    char localsplit4[3] = {argumentstring[6], argumentstring[7]};
    char argumentaddressstring[9];
    sprintf(argumentaddressstring, "%.8x", (int) &argv[j]);
    printf("       |  %s  |  %s  |  %s  |  %s  | %s \n", localsplit1, localsplit2, localsplit3, localsplit4, argumentaddressstring);
    bufferline(1);
    
    for (int i = argc-1; i >= 0; i--) {
        char argumentstring[9];
        sprintf(argumentstring, "%.8x", (int) *&argv[i]);
        char localsplit1[3] = {argumentstring[0], argumentstring[1]};
        char localsplit2[3] = {argumentstring[2], argumentstring[3]};
        char localsplit3[3] = {argumentstring[4], argumentstring[5]};
        char localsplit4[3] = {argumentstring[6], argumentstring[7]};
        char argumentaddressstring[9];
        sprintf(argumentaddressstring, "%.8x", (int) &argv[i]);
        printf("argv+%d |  %s  |  %s  |  %s  |  %s  | %s \n", i, localsplit1, localsplit2, localsplit3, localsplit4, argumentaddressstring);
        bufferline(1);
    }
    
    bufferline(3);
    
    char firstargumentstring[9];
    sprintf(firstargumentstring, "%.8x", (int) &argv[0]);

    char firstargumentaddressstring[9];
    sprintf(firstargumentaddressstring, "%.8x", (int) &argv);
    
    firstargument(firstargumentstring, firstargumentaddressstring);
    
    bufferline(1);
    
    char counterstring[9];
    sprintf(counterstring, "%.8x", (int) argc);
    
    char counteraddressstring[9];
    sprintf(counteraddressstring, "%.8x", (int) &argc);
    
    argumentcounter(counterstring, counteraddressstring);
    
    footer();
    
    return 0;
}

void argumentcounter(char counter[], char counteraddress[]) {
    char localcounter1[3] = {counter[0], counter[1]};
    char localcounter2[3] = {counter[2], counter[3]};
    char localcounter3[3] = {counter[4], counter[5]};
    char localcounter4[3] = {counter[6], counter[7]};
    printf("argc   |  %s  |  %s  |  %s  |  %s  | %s \n", localcounter1, localcounter2, localcounter3, localcounter4, counteraddress);
}

void bufferline(int count) {
    for (int i = 0; i < count; i++) {
        printf("       +------+------+------+------+\n");
    }
}

void firstargument(char address[], char firstargumentaddress[]) {
    char localsplit1[3] = {address[0], address[1]};
    char localsplit2[3] = {address[2], address[3]};
    char localsplit3[3] = {address[4], address[5]};
    char localsplit4[3] = {address[6], address[7]};
    printf("argv   |  %s  |  %s  |  %s  |  %s  | %s \n", localsplit1, localsplit2, localsplit3, localsplit4, firstargumentaddress);
}

void footer() {
    printf("       +------+------+------+------+\n");
    printf("       +------+------+------+------+\n");
    printf("       +------+------+------+------+\n");
    printf("       +------+------+------+------+ 00000000\n");
}

void header() {
    printf("       +------+------+------+------+ FFFFFFFF\n");
    printf("       +------+------+------+------+\n");
    printf("       +------+------+------+------+\n");
    printf("       +------+------+------+------+\n");
}


