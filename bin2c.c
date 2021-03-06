#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const unsigned int max_column = 78;
static const unsigned int tab_size = 8;

size_t fsize(FILE *fd) {
  fseek(fd, 0, SEEK_END);
  size_t size = (size_t)ftell(fd); // warning ftell return signed long
  fseek(fd, 0, SEEK_SET);
  return size;
}

int main(int argc, char **argv) {
  unsigned char c = 0;
  unsigned int column = 0;
  unsigned int i = 0;
  size_t count = 0;
  size_t size = 0;
  char aux_char;
  FILE *fp;
  char *name;

  if (argc != 2) {
    printf("Usage: bin2c file\n");
    exit(1);
  }

  fp = fopen(argv[1], "rb");
  if (!fp) {
    printf("Cannot open %s", argv[1]);
    exit(1);
  }

  size = fsize(fp);
  name = basename(argv[1]);

  i = sizeof(name);
  while (i--) {
    aux_char = name[i];
    if (aux_char == '.') {
      name[i] = '_';
    }
  }

  printf("static const size_t %s_size = %lu;\n", name, size);
  printf("static const unsigned char %s_data[] = {\n\t", name);

  while (count < size) {
    count++;
    c = (unsigned char)getc(fp);
    column += 6;
    if (column >= max_column) {
      printf("\n\t");
      column = tab_size;
    }
    if (count == size) {
      printf("0x%02X", c);
      continue;
    }
    printf("0x%02X, ", c);
  }

  printf("\n};\n");
  return 0;
}
