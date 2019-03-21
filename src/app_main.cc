#include <stdlib.h>
#include <stdio.h>

#include "fkps.h"

int main(int argc, char* args[]) {
    
    if (argc != 4) {
        printf("Wrong number of arguments\n");
        return 0;
    }

    int toPart  = atoi(args[1]);
    int n       = atoi(args[2]);
    char *fname = args[3];
    
    printf("Going to partition %d into %d\n", toPart, n);

    FakeProjectiveSpaces_t *fakeProjectiveSpaces = FakeProjectiveSpacesInit(n, fname);
    if (fakeProjectiveSpaces == NULL) { printf("Could not initialize.\n"); return -1; }

    FakeProjectiveSpacesPartition(fakeProjectiveSpaces, toPart, 1);
    FakeProjectiveSpacesDeInit(fakeProjectiveSpaces);
    
    return 0;   
}