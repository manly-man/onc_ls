#include "lists.h"

Element *createDirectory(char *name) {

    Directory *dir = (Directory*) calloc(1, sizeof(Directory));
    if(!dir) exit(1);
    dir->name = name;

    Element *newElement = (Element*) calloc(1, sizeof(Element));
    newElement->type = TYPE_DIR;
    newElement->next = 0;
    newElement->Data.directory = dir;

    return newElement;
}

Element *createFile(char *name, bool isExecutable) {

    File *file = (File*) calloc(1, sizeof(File));
    if(!file) exit(1);
    file->name = name;

    Element *newElement = (Element*) calloc(1, sizeof(Element));
    if(!newElement) exit(1);
    newElement->type = TYPE_FILE;
    newElement->next = 0;
    newElement->Data.file = file;

    return newElement;
}

Element *createSymLink(char *name, char *symLinkTo) {

    SymLink *symLink = (SymLink*) calloc(1, sizeof(SymLink));
    if(!symLink) exit(1);
    symLink->name = name;
    symLink->symLinkTo = symLinkTo;

    Element *newElement = (Element*) calloc(1, sizeof(Element));
    if(!newElement) exit(1);
    newElement->type = TYPE_SYMLINK;
    newElement->next = 0;
    newElement->Data.symLink = symLink;

    return newElement;
}

Element *addToList(List *list, Element *toAdd) {

    if(list->head == 0) {
        list->head = toAdd;
        return toAdd;
    }

    Element *iterator = list->head;
    while (iterator->next != 0) {
        iterator = iterator->next;
    }

    iterator->next = toAdd;

    return toAdd;
}

bool isEmpty(List *list) {

    return list->head ? false : true;
}
