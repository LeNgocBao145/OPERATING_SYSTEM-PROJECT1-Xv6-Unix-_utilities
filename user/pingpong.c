#include "user.h"

int main() {
    int p1[2], p2[2]; // Pipes: p1 for parent->child, p2 for child->parent
    char buf;
    int pid;

    // Checking when creating pipes
    if (pipe(p1) == -1 || pipe(p2) == -1) {
        printf("Pipe creation failed\n");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (pid == 0) {  // Child process
        close(p1[1]);  // Do not need to write p1
        close(p2[0]);  // Do not need to read p2

        if (read(p1[0], &buf, 1) <= 0) { // Receive from parent
            printf("Child read failed\n");
            exit(1);
        }

        printf("%d: received ping\n", getpid());

        if (write(p2[1], &buf, 1) == -1) { // Send to parent
            printf("Child write failed\n");
            exit(1);
        }

        close(p1[0]);  // Close after reading p1
        close(p2[1]);  // Close after writing p2
        exit(0);
    } else {  // Parent process
        close(p1[0]);  // Do not need to read p1
        close(p2[1]);  // Do not need to write p2

        if (write(p1[1], "x", 1) == -1) { // Send to child
            printf("Parent write failed\n");
            exit(1);
        }

        if (read(p2[0], &buf, 1) <= 0) { // Receive from child
            printf("Parent read failed\n");
            exit(1);
        }
        printf("%d: received pong\n", getpid());

        close(p1[1]);  // Close after writing p1
        close(p2[0]);  // Close after reading p2
        wait(0); // Wait for child to finish
    }
    exit(0);
}
