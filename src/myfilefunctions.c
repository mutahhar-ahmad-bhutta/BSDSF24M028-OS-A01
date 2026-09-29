#include "../include/myfilefunctions.h"
#include <stdlib.h>   // malloc, realloc, free
#include <string.h>   // strstr, strlen, strcpy

// Counts lines, words and characters in the file.
// Returns 0 on success, -1 on failure.
int wordCount(FILE* file, int* lines, int* words, int* chars) {
    if (file == NULL || lines == NULL || words == NULL || chars == NULL) {
        return -1;
    }

    *lines = 0;
    *words = 0;
    *chars = 0;

    int c;            // int, not char, so it can hold EOF
    int inWord = 0;   // 1 = we are currently inside a word, 0 = not

    while ((c = fgetc(file)) != EOF) {
        (*chars)++;

        if (c == '\n') {
            (*lines)++;
        }

        if (c == ' ' || c == '\t' || c == '\n') {
            inWord = 0;
        } else if (inWord == 0) {
            inWord = 1;
            (*words)++;
        }
    }
    return 0;
}

// Finds every line that contains search_str.
// Fills *matches with a newly allocated list of those lines.
// Returns the number of matches, or -1 on failure.
int mygrep(FILE* fp, const char* search_str, char*** matches) {
    if (fp == NULL || search_str == NULL || matches == NULL) {
        return -1;
    }

    char line[1024];
    char** result = NULL;
    int count = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, search_str) != NULL) {
            // grow the list by one slot
            char** temp = realloc(result, (count + 1) * sizeof(char*));
            if (temp == NULL) {
                for (int i = 0; i < count; i++) free(result[i]);
                free(result);
                return -1;
            }
            result = temp;

            // make a copy of the line and store it in the new slot
            result[count] = malloc(strlen(line) + 1);
            if (result[count] == NULL) {
                for (int i = 0; i < count; i++) free(result[i]);
                free(result);
                return -1;
            }
            strcpy(result[count], line);
            count++;
        }
    }

    *matches = result;
    return count;
}
