#include "user.h"

int main() {
    int p1[2], p2[2]; // Pipes: p1 for parent->child, p2 for child->parent
    char buf;
    int pid;

    pipe(p1);
    pipe(p2);

    pid = fork();
    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (pid == 0) {  // Child process
        read(p1[0], &buf, 1);  // Read from parent
        printf("%d: received ping\n", getpid());

        write(p2[1], &buf, 1); // Send back to parent
        exit(0);
    } else {  // Parent process
        write(p1[1], "x", 1); // Send to child

        read(p2[0], &buf, 1); // Receive from child
        printf("%d: received pong\n", getpid());

        wait(0); // Wait for child to finish
    }
    exit(0);
}
