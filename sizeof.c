#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define VERSION "0.1"

struct sizeentry {
  const char *name;
  size_t size;
};

#include HEADER

static const int len = sizeof(sizes) / sizeof(struct sizeentry);

static size_t getsize(const char *type) {
  int i;

  for (i = 0; i < len; i++)
    if (strcmp(type, sizes[i].name) == 0)
      return sizes[i].size;
  return 0;
}

int main(int argc, char * const argv[]) {
  int i, opt;
  size_t s;
  const char *opts = "hlv";

  while ((opt = getopt(argc, argv, opts)) != -1)
    switch (opt) {
      case 'h':
        printf("Usage: %s [-%s] [types ...]\n", argv[0], opts);
        break;
      case 'l':
        for (i = 0; i < len; i++) puts(sizes[i].name);
        break;
      case 'v':
        printf("%s v %s\n", argv[0], VERSION);
        break;
      default:
        exit(1);
    }

  for (i = optind; i < argc; i++)
    if ((s = getsize(argv[i]))) {
      printf("%s: %d\n", argv[i], s);
    } else {
      fprintf(stderr, "%s: unknown type: %s\n", argv[0], argv[i]);
      exit(1);
    }

  return 0;
}

