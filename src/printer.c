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

void printList(List *list) {

  Element *iterator = list->head;

  int maxLength = getMaxLength(list);
  int terminalWidth = getTerminalWidth();

  int remainingSpace = terminalWidth;
  char *name = "";

  while (iterator) {
    switch (iterator->type) {
      case TYPE_DIR:
        name = iterator->Data.directory->name;
        if(strnlen(name, maxLength) < remainingSpace) {
          printf(KBLU "%-*s  " RESET, (int) strnlen(name, maxLength), name);
          remainingSpace -= strnlen(name, maxLength) + 2;
        } else {
          printf("\n");
          remainingSpace = terminalWidth;
        }
        break;
      case TYPE_FILE:
        name = iterator->Data.file->name;
        if(strnlen(name, maxLength) < remainingSpace) {
          printf(KMAG "%-*s  " RESET, (int) strnlen(name, maxLength), name);
          remainingSpace -= strnlen(name, maxLength) + 2;
        } else {
          printf("\n");
          remainingSpace = terminalWidth;
        }
        break;
      case TYPE_SYMLINK:
        name = iterator->Data.symLink->name;
        printf(KGRN "%-*s -> %s\n" RESET, maxLength, name, iterator->Data.symLink->symLinkTo);
        break;
      default:
        printf("Unkown type");
    }
    iterator = iterator->next;
  }
  printf("\n");
}
