#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include "lists.h"
#include "printer.h"

int main(int argc, char* argv[]) {
  char* cmdname = *argv++; --argc;
  char usage[] = "Usage: %s [directory]\n";
  if (argc > 1) {
    fprintf(stderr, usage, cmdname);
    exit(1);
  }
  char* dirName;
  if (argc > 0) {
    dirName = *argv;
  } else {
    dirName = ".";
  }

  if (chdir(dirName) < 0) {
    perror(dirName);
    exit(1);
  }
  DIR* dir = opendir(".");
  if (!dir) {
    perror(dirName);
    exit(1);
  }

  List *directoryList = (List*) calloc(1, sizeof(List));
  directoryList->head = NULL;

  List *fileList = (List*) calloc(1, sizeof(List));
  fileList->head = NULL;

  List *symLinkList = (List*) calloc(1, sizeof(List));
  symLinkList->head = NULL;

  struct dirent* entry;
  while ((entry = readdir(dir))) {

    if(strncmp(entry->d_name, "..", 2) == 0 || strncmp(entry->d_name, ".", 1) == 0) {
      continue;
    }

    struct stat statbuf;

    if(lstat(entry->d_name, &statbuf) < 0) {
      perror(entry->d_name); exit(1);
    }

    if (S_ISREG(statbuf.st_mode)) {
      Element *newFile = createFile(entry->d_name, false);
      addToList(fileList, newFile);

    } else if (S_ISDIR(statbuf.st_mode)) {
      Element *newDir = createDirectory(entry->d_name);
      addToList(directoryList, newDir);

    } else if (S_ISLNK(statbuf.st_mode)) {
      char buf[1024];
      ssize_t len = readlink(entry->d_name, buf, sizeof buf);
      if (len < 0) {
        perror(entry->d_name);
        exit(1);
      }

      char *symLinkName = (char*) calloc(len + 1, sizeof(char));
      strncpy(symLinkName, buf, len);
      symLinkName[len] = '\0';

      Element *symLink = createSymLink(entry->d_name, symLinkName);
      addToList(symLinkList, symLink);
    }
  }

  closedir(dir);

  if(!isEmpty(directoryList)) {
    printf("[Directories]\n");
    printList(directoryList);
    printf("\n");
  }

  if(!isEmpty(fileList)) {
    printf("[Files]\n");
    printList(fileList);
    printf("\n");
  }

  if(!isEmpty(symLinkList)) {
    printf("[SymLinks]\n");
    printList(symLinkList);
  }

}
