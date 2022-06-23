#include <stdio.h>
#include "extractlcs.h"
void printError(int args);

int main(int argc, char** argv) {
    if (argc != 4) {
        printError(argc-1);
        return -1;
    }
    controller(argv[1],argv[2],argv[3]);
    return 0;
}

void printError(int args) {
    fprintf(stderr,"\n\nHai inserito %d parametri, devono essere 3!\n",args);
    fprintf(stderr,"\nextractlcs <firstFile> <secondFile> <outputfile>\n\n");
}