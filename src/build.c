/**
 * Prepares files for processing
 */


#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

#define BUILD_INPUT_BUFSIZE 1


char * build_get_input();
int build_cycle(char * inp);
struct build_search_struct * build_make_search_map (char * inp);
int build_add_search_item (struct build_search_struct * mapper, char c);
int build_fsize(FILE * f);
int build_process (char c, FILE * f_dest,
                   struct build_search_struct * search_map,
                   int i);



struct build_search_struct {
    char id;
    int val;
    UT_hash_handle hh;
};


/**
 * Main
 */
int main () {
    char * inp;
    inp = build_get_input();
    build_cycle(inp);
    free(inp);
    return 0;
}

char * build_get_input () {
    char * content;
    char * content_new;
    char * buffer;
    int i;
    int new_size;
    // Allocate just one at a time
    new_size = (sizeof(char) * BUILD_INPUT_BUFSIZE);
    content = malloc(new_size);
    if (content == NULL) {
        perror("Failed to allocate content");
        exit(1);
    }
    content[0] = '\n';
    i = 1;
    while (fgets(buffer, BUILD_INPUT_BUFSIZE, stdin)) {
        strcat(content, buffer);
        new_size = sizeof(char) * (BUILD_INPUT_BUFSIZE * (i + 1));
        content_new = (char *)realloc(content, new_size);
        if (content_new == NULL) {
            free(content);
            perror("Failed to reallocate content");
            exit(1);
        }
        else {
            content = content_new;
        }
        i++;
    }
    return content;
}

/**
 * Cycle through source file
 */
int build_cycle (char * inp) {
    FILE * f_source;
    FILE * f_dest;
    char c;
    int i;
    struct build_search_struct * search_map;
    f_source = fopen("data/out.txt", "rt");
    f_dest = fopen("data/prep.data", "wb");
    i = 0;
    search_map = build_make_search_map(inp);
    // Cycle through input characters
    while (!feof(f_source)) {
        c = fgetc(f_source);
        build_process(c, f_dest, search_map, i);
        i++;
    }
    free(search_map);
    fclose(f_source);
    fclose(f_dest);
    return 0;
}

/**
 * Build search mapper
 */
struct build_search_struct * build_make_search_map (char * inp) {
    struct build_search_struct * mapper;
    int i;
    char c;
    mapper = NULL;
    i = 0;
    while (1) {
        c = *(inp + i);
        if (c == '\0') {
            break;
        }
        else {
            build_add_search_item(mapper, c);
            i++;
        }
    }
    return mapper;
}

/**
 * Add search item
 */
int build_add_search_item (struct build_search_struct * mapper, char c) {
    struct build_search_struct * s;
    HASH_FIND_INT(mapper, &c, s);
    if (s == NULL) {
        s = malloc(sizeof(struct build_search_struct));
        s->id = c;
        s->val = 1;
        HASH_ADD_INT(mapper, id, s);
    }
    return 0;
}

/**
 * Get filesize
 */
int build_fsize (FILE * f) {
    int sz;
    fseek(f, 0 , SEEK_END);
    sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    return sz;
}

/**
 * Process a character
 */
int build_process (char c, FILE * f_dest,
                   struct build_search_struct * search_map, 
                   int i) {
    fwrite(&i, sizeof(int), 1, f_dest);
    return 0;
}

