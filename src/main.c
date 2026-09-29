#include <stdio.h>
#include <stdlib.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main() {
    printf("--- Testing String Functions ---\n");

    char buffer[100];
    int r;

    r = mystrlen("Hello");
    printf("mystrlen(\"Hello\") = %d\n", r);

    r = mystrcpy(buffer, "Hello");
    printf("mystrcpy  -> \"%s\" (copied %d chars)\n", buffer, r);

    r = mystrncpy(buffer, "Operating", 4);
    printf("mystrncpy -> \"%s\" (copied %d chars, n = 4)\n", buffer, r);

    mystrcpy(buffer, "Hello");
    r = mystrcat(buffer, " World");
    printf("mystrcat  -> \"%s\" (new length %d)\n", buffer, r);

    printf("\n--- Testing File Functions ---\n");

    FILE* fp = fopen("test.txt", "r");
    if (fp == NULL) {
        printf("Error: could not open test.txt\n");
        return 1;
    }

    int lines, words, chars;
    if (wordCount(fp, &lines, &words, &chars) == 0) {
        printf("wordCount -> lines = %d, words = %d, chars = %d\n", lines, words, chars);
    }

    rewind(fp);

    char** matches = NULL;
    int count = mygrep(fp, "hello", &matches);
    if (count >= 0) {
        printf("mygrep    -> %d line(s) contain \"hello\":\n", count);
        for (int i = 0; i < count; i++) {
            printf("   %s", matches[i]);
            free(matches[i]);
        }
        free(matches);
    }

    fclose(fp);
    return 0;
}
