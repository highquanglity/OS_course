#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

// Define a structure for shared data
struct SharedData {
    int x, y, z;  // Variables for calculations
    int ready;     // Flag to indicate data readiness
};

// Function to initialize shared data
void initSharedData(struct SharedData* data, int x, int y) {
    data->x = x;
    data->y = y;
    data->ready = 0;
}

// Function to perform calculation
void calculate(struct SharedData* data) {
    data->z = data->x + data->y;
    data->ready = 0;
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
    int shm_ID = shmget(key_t, sizeof(struct SharedData), IPC_CREAT | 0666);
    if (shm_ID < 0) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment to the process's address space
    struct SharedData* data = shmat(shm_ID, NULL, 0);
    if (data == (struct SharedData*) -1) {
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
        // Wait until parent sets ready flag to 1
        while (data->ready == 0) {
            sleep(1);
        }

        // Perform the calculation
        logMessage("INFO", "Child Working");
        calculate(data);

        // Exit child process
        exit(EXIT_SUCCESS);
    } else { // Parent process
        logMessage("INFO", "Parent Working");

        // Read values for x and y from the user and initialize shared data
        int x, y;
        printf("Enter the value of x: ");
        scanf("%d", &x);
        printf("Enter the value of y: ");
        scanf("%d", &y);
        initSharedData(data, x, y);

        // Notify child to start calculation
        data->ready = 1;
        logMessage("INFO", "Parent Waiting");

        // Wait until child sets ready flag to 0 after the calculation
        while (data->ready != 0) {
            sleep(1);
        }

        logMessage("INFO", "Parent Working");
        // Display the calculated result
        printf("The value of z is %d\n", data->z);

        // Detach from shared memory and remove the shared memory segment
        shmdt(data);
        shmctl(shm_ID, IPC_RMID, NULL);

        // Exit parent process
        exit(EXIT_SUCCESS);
    }

    return 0;
}
