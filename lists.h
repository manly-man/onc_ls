#ifndef LISTS_H
#define LISTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TYPE_DIR 1
#define TYPE_FILE 2
#define TYPE_SYMLINK 3

typedef struct Directory {

    char *name;
} Directory;

typedef struct File {

    char *name;
    bool isExecutable;
} File;

typedef struct SymLink {

    char *name;
    char *symLinkTo;
} SymLink;

typedef struct Element {

    unsigned char type;
    struct Element *next;
    union Data {
        Directory *directory;
        File *file;
        SymLink *symLink;
    } Data;
} Element;

typedef struct List {

    Element *head;
} List;

Element *addToList(List *list, Element *toAdd);

bool isEmpty(List *list);

Element *createDirectory(char *name);
Element *createFile(char *name, bool isExecutable);
Element *createSymLink(char *name, char *symLinkTo);

#endif
