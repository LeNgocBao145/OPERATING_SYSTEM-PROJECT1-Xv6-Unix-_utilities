#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int main() {
    struct sysinfo info;
    if (sysinfo(&info) < 0) {
        printf("sysinfotest: failed\n");
        exit(1);
    }
    printf("Free memory: %ld bytes\n", info.freemem);
    printf("Not UNUSED processes: %ld\n", info.nproc);
    printf("Load average: %ld\n", info.loadavg);
    printf("sysinfotest: OK\n");
    exit(0);
}
