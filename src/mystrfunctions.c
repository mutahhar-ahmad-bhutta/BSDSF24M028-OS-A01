#include "../include/mystrfunctions.h"

// Returns the number of characters in s (not counting the '\0')
int mystrlen(const char* s) {
    int count = 0;
    while (s[count] != '\0') {
        count++;
    }
    return count;
}

// Copies src into dest (including the '\0'). Returns the number of characters copied.
int mystrcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return i;
}

// Copies at most n characters of src into dest, and always ends dest with '\0'.
// Returns the number of characters copied.
int mystrncpy(char* dest, const char* src, int n) {
    int i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return i;
}

// Appends src to the end of dest. Returns the new length of dest.
int mystrcat(char* dest, const char* src) {
    int start = mystrlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[start + i] = src[i];
        i++;
    }
    dest[start + i] = '\0';
    return start + i;
}
