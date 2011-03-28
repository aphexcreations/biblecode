/**
 * Prepares files for processing
 */


#include <stdio.h>

int prepare_process (char c, FILE * f_dest);


/**
 * Main
 */
int main () {
    FILE * f_source;
    FILE * f_dest;
    char c;
    f_source = fopen("data/in.txt", "rt");
    f_dest = fopen("data/out.txt", "wt");
    // Cycle through input characters
    while (!feof(f_source)) {
        c = fgetc(f_source);
        prepare_process(c, f_dest);
    }
    fclose(f_source);
    fclose(f_dest);
    return 0;
}

/**
 * Process a character
 */
int prepare_process (char c, FILE * f_dest) {
    // If uppercase, convert to lowercase
    if (c >= 0x41 && c <= 0x5A) {
        c += 0x20;
    }
    // If lowercase
    if (c >= 0x61 && c <= 0x7A) {
        fputc(c, f_dest);
    }
    return 0;
}

