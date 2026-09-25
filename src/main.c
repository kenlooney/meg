#include <stdio.h>
#include <string.h>

void print_help() {
  puts("");
  puts("Options:");
  puts("  -h, --help    display this help and exit");
}
int main(int argc, char **argv) {
  if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
    print_help();
    return 0;
  }
 
  return 0;
}
