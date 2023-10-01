#include <stdio.h>

typedef struct {
    int argc;
    char **argv;
} ParameterProgram;

void run(ParameterProgram program) {
    if (program.argc < 2) {
        printf("Could not find any input parameters, please run the program again.\n");
        return;
    }

    printf("Program starts...\n");

    printf("%d parameters have been added:\n", program.argc - 1);
    for (int i = 1; i < program.argc; i++) {
        printf("\t%d. %s\n", i, program.argv[i]);
    }
    printf("=========================\n");
    printf("Please choose the order number that matches your choice (%d-%d): ", 1, program.argc - 1);
    int choice;
    scanf("%d", &choice);
    while ((choice >= program.argc) || (choice < 1) || sizeof(choice) != sizeof(int))
    {
        int flag = 0;
        printf("Out of range, choose again? \n");
        printf("[Enter 1 for Yes, others for No]\n");
        scanf("%d", &flag);
        if (flag != 1)
        {
            printf("Quit the program....\n");
            return ;
        }
        printf("Please make a choice (%d-%d): ", 1, program.argc - 1);
        scanf("%d", &choice);
    }

    printf("=========================\n");
    printf("You have choosed %s!\n", program.argv[choice]);
    printf("Thank you! Quit the program...\n");
}

int main(int argc, char *argv[]) {
    ParameterProgram program = {argc, argv};
    run(program);
    return 0;
}
