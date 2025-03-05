#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX 280
#define FIRST_PRIME 2

int generate_numbers();
int filter_numbers(int read_fd, int prime);

int main(int argc, char *argv[])
{
    int current_prime;
    int read_fd = generate_numbers();

    while (read(read_fd, &current_prime, sizeof(int)) > 0) {
        printf("prime %d\n", current_prime);
        read_fd = filter_numbers(read_fd, current_prime);
    }

    exit(0);
}

int generate_numbers() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        close(fd[0]);
        for (int i = FIRST_PRIME; i <= MAX; i++) {
            write(fd[1], &i, sizeof(int));
        }
        close(fd[1]);
        exit(0);
    }
    close(fd[1]);
    return fd[0];
}

int filter_numbers(int read_fd, int prime) {
    int fd[2];
    int num;
    pipe(fd);

    if (fork() == 0) {
        close(fd[0]);
        while (read(read_fd, &num, sizeof(int)) > 0) {
            if (num % prime != 0) {
                write(fd[1], &num, sizeof(int));
            }
        }
        close(read_fd);
        close(fd[1]);
        exit(0);
    }
    close(read_fd);
    close(fd[1]);
    return fd[0];
}
