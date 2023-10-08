#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **files;
    int numFiles;
} FileManager;

void initializeFileManager(FileManager *manager, int argc, char *argv[]) {
    manager->numFiles = argc - 2;
    manager->files = (char **)malloc(manager->numFiles * sizeof(char *));
    for (int i = 0; i < manager->numFiles; i++) {
        manager->files[i] = strdup(argv[i + 2]);
    }
}

void displayEmptyFiles(FileManager *manager) {
    for (int i = 0; i < manager->numFiles; i++) {
        printf("\t %d. %s\n", i + 1, manager->files[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        printf("You haven't have any empty files in the folder\n");
        return -1;
    }

    FileManager manager;
    initializeFileManager(&manager, argc, argv);

    if (!strcmp(argv[1], "p")) {
        displayEmptyFiles(&manager);
        return 1;
    } else {
        printf("Please choose delete or not: type '1': delete, other: not delete\n");
        int choice;
        scanf("%d", &choice);
        free(manager.files); // free allocated memory
        if (choice == 1) {
            // delete file
            return 0;
        } else {
            // keep file
            return 1;
        }
    }
}
