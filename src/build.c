/**
 * Prepares files for processing
 */


#include <stdio.h>
#include <stdlib.h>

int build_fsize(FILE * f);
int build_process (char c, FILE * f_dest, int * mapper, int i);



/**
 * Main
 */
int main () {
    FILE * f_source;
    FILE * f_dest;
    char c;
    int * mapper;
    int i;
    f_source = fopen("data/out.txt", "rt");
    f_dest = fopen("data/prep.data", "wb");
    // Allocate array
    mapper = (int *)malloc(sizeof(int)*build_fsize(f_source));
    // Cycle through input characters
    while (!feof(f_source)) {
        i = ftell(f_source);
        c = fgetc(f_source);
        build_process(c, f_dest, mapper, i);
    }
    free(mapper);
    fclose(f_source);
    fclose(f_dest);
    return 0;
}

/**
 * Get filesize
 */
int build_fsize(FILE * f) {
    int sz;
    fseek(f, 0 , SEEK_END);
    sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    return sz;
}

/**
 * Process a character
 */
int build_process (char c, FILE * f_dest, int * mapper, int i) {
    fwrite(&i, sizeof(int), 1, f_dest);
    return 0;
}

