#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

// Define a structure for shared var
struct VarShared {
    int x, y, z;  
    int ready;     
};

// Function to perform calculation
void calculate(struct VarShared* var) {
    var->z = var->x + var->y;
    var->ready = 0;
}

// Function to log messages
void logMessage(const char* tag, const char* message) {
    time_t rawtime;
    struct tm* timeinfo;
    char timestamp[20]; // Buffer to store formatted timestamp

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%H:%M:%S", timeinfo);

    printf("[%s] [%s]: %s\n", timestamp, tag, message);
}

int main() {
    // Generate a unique key for shared memory
    int key_t = 41354;

    // Create or access the shared memory segment
    int shm_ID = shmget(key_t, sizeof(struct VarShared), IPC_CREAT | 0666);
    if (shm_ID < 0) {
        perror("Failed to create shared memory segment (shmget())");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment to the process's address space
    struct VarShared* var = shmat(shm_ID, NULL, 0);
    if (var == (struct VarShared*) -1) {
        perror("Failed to attach shared memory segment (shmat())");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t child_PID = fork();
    if (child_PID == -1) {
        perror("Failed to fork process (fork())");
        exit(EXIT_FAILURE);
    }

    if (child_PID == 0) { // Child process
        // Wait until parent sets ready flag to 1
        while (var->ready == 0) {
            sleep(1);
        }

        // Perform the calculation
        logMessage("INFO", "Child Working");
        calculate(var);

        // Exit child process
        exit(EXIT_SUCCESS);
    } else { // Parent process
        logMessage("INFO", "Parent Working");

        // Read values for x and y from the user and initialize shared var
        printf("Enter the value of x: ");
        scanf("%d", &var->x);

        printf("Enter the value of y: ");
        scanf("%d", &var->y);


        // Notify child to start calculation
        var->ready = 1;
        logMessage("INFO", "Parent Waiting");

        // Wait until child sets ready flag to 0 after the calculation
        while (var->ready != 0) {
            sleep(1);
        }

        logMessage("INFO", "Parent Working");
        // Display the calculated result
        printf("The value of z is %d\n", var->z);

        // Detach from shared memory and remove the shared memory segment
        shmdt(var);
        shmctl(shm_ID, IPC_RMID, NULL);

        // Exit parent process
        exit(EXIT_SUCCESS);
    }

    return 0;
}
