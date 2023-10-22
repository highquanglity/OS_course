#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

void logger(const char* tag, const char* message) {
    time_t rawtime;
    struct tm * timeinfo;
    char timestamp[20]; // Buffer to store formatted timestamp

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%H:%M:%S", timeinfo);

    printf("[%s] [%s]: %s\n", timestamp, tag, message);
}

// Define a structure for shared data
struct shared_data {
    int x, y, z;  // Variables for calculations
    int ready;     // Flag to indicate data readiness
};

int main() {
    int key_t = 41354;
    
    // Create shared memory segment
    int shm_ID = shmget(key_t, sizeof(struct shared_data), IPC_CREAT | 0666);
    if (shm_ID < 0) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory segment to the process's address space
    struct shared_data *data = shmat(shm_ID, NULL, 0);
    if (data == (struct shared_data*) -1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        while (data->ready == 0) {
            // Wait until parent sets ready flag to 1
            sleep(1);
        }
        
        // Perform the calculation
        logger("INFO", "Child Working");
        data->z = data->x + data->y;
        data->ready = 0; // Calculation done, set ready flag to 0

        exit(EXIT_SUCCESS);
    } else { // Parent process
        logger("INFO", "Parent Working");
        
        // Read values for x and y from the user
        printf("Enter the value of x: ");
        scanf("%d", &data->x);

        printf("Enter the value of y: ");
        scanf("%d", &data->y);

        data->ready = 1; // Set ready flag to 1 to notify child to start calculation
        logger("INFO", "Parent Waiting");
        while (data->ready != 0) {
            // Wait until child sets ready flag to 0 after the calculation
            sleep(1);
        }
        logger("INFO", "Parent Working");

        // Display the calculated result
        printf("The value of z is %d\n", data->z);

        // Detach from shared memory and remove the shared memory segment
        shmdt(data);
        shmctl(shm_ID, IPC_RMID, NULL);

        exit(EXIT_SUCCESS);
    }

    return 0;
}
