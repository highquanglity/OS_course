// gcc -pthread -o main main.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Define a structure for shared var
struct Var_init {
    int x, y, z;
    volatile int ready; // Use volatile to prevent compiler optimization
};

// Function to perform calculation
void calculate(struct Var_init* var) {
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

void* childThread(void* arg) {
    struct Var_init* var = (struct Var_init*)arg;
    
    // Wait until ready flag is set by the parent
    while (var->ready == 1) {
        sleep(1); // Sleep for 1 second to reduce CPU usage
    }

    // Perform the calculation
    logMessage("INFO", "Child thread");
    calculate(var);
    logMessage("INFO", "Finished Calculation");

    pthread_exit(NULL);
}

int main() {
    struct Var_init var;
    var.ready = 1; // Set ready flag to 1 initially
    
    pthread_t thread;
    pthread_create(&thread, NULL, childThread, (void*)&var);

    logMessage("INFO", "Parent thread");
    printf("Enter the value of x: ");
    scanf("%d", &var.x);
    printf("Enter the value of y: ");
    scanf("%d", &var.y);

    // Notify child to start calculation
    var.ready = 0;

    // Wait for the child thread to finish
    pthread_join(thread, NULL);

    logMessage("INFO", "Parent thread");
    // Display the calculated result
    printf("The value of z is %d\n", var.z);

    return 0;
}
