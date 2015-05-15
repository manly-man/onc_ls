#include "printer.h"

int getTerminalWidth() {

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

int getMaxLength(List *list) {

  int maxLength = 0;
  int newLength = 0;

  Element *iterator = list->head;
  while (iterator) {
    switch (iterator->type) {
      case TYPE_DIR:
        if ((newLength = strlen(iterator->Data.directory->name)) > maxLength) {
          maxLength = newLength;
        }
        break;
      case TYPE_FILE:
        if ((newLength = strlen(iterator->Data.file->name)) > maxLength) {
          maxLength = newLength;
        }
        break;
      case TYPE_SYMLINK:
        if ((newLength = strlen(iterator->Data.symLink->name)) > maxLength) {
          maxLength = newLength;
        }
        break;
      default:
        printf("Unkown type");
    }
    iterator = iterator->next;
  }
  return maxLength;
}

char *getFilenameExt(char *filename) {
  char *dot = strrchr(filename, '.');
  if(!dot || dot == filename) return "";
  return dot + 1;
}

void printList(List *list) {

  Element *iterator = list->head;

  int maxLength = getMaxLength(list);
  int terminalWidth = getTerminalWidth();

  char *name = "";

  if(maxLength < 1) {
    printf("Length of longest filename is smaller than 1");
    return;
  }

  // maxLength + 1 because we seperate columns using whitespace
  maxLength++;
  double amountOfCols = floor(terminalWidth / maxLength);

  int columnCounter = 0;
  while (iterator) {

    if(columnCounter >= amountOfCols) {
      columnCounter = 0;
      printf("\n");
    }

    switch (iterator->type) {
      case TYPE_DIR:
        name = iterator->Data.directory->name;
        printf(KBLU "%-*s" RESET, maxLength, name);
        break;
      case TYPE_FILE:
        name = iterator->Data.file->name;
        if(iterator->Data.file->isExecutable) {
          printf(KRED "%-*s" RESET, maxLength, name);
        } else if(strncmp(getFilenameExt(name), "md", 10) == 0) {
          printf(KYEL "%-*s" RESET, maxLength, name);
        } else {
          printf(KWHT "%-*s" RESET, maxLength, name);
        }
        break;
      case TYPE_SYMLINK:
        name = iterator->Data.symLink->name;
        printf(KGRN "%-*s " RESET " -> " KBLU "%s\n" RESET, maxLength, name, iterator->Data.symLink->symLinkTo);
        break;
      default:
        printf("Unkown type");
    }

    columnCounter++;
    iterator = iterator->next;
  }
  printf("\n");
}
