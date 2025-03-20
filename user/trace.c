#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc < 3){
    fprintf(2, "Usage: trace mask command...\n");
    exit(1);
  }

  int mask = atoi(argv[1]); // Chuyển đối số đầu tiên thành số nguyên (mask)
  trace(mask);  // Gọi system call trace

  exec(argv[2], &argv[2]); // Thực thi chương trình được truyền vào
  exit(0);
}
