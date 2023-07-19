#include <stdio.h> 

extern char _binary_______AUTHORS_start;
extern char _binary_______AUTHORS_end;

int main(int argc, char **argv)
{
  int fd, retval;
  char *fp = NULL;

  /* read the start of the binary block */
  fp = &_binary_______AUTHORS_start;

//  char output[200] = {0x00};
  char output[2048];
  int index = 0;

  while ( fp != &_binary_______AUTHORS_end )
  {
    /* putchar(*fp++); */
    int index = 0;
    output[index++] = (char)putchar(*fp);
    fp++;
  }
  putchar('\n');
  printf("[%s]\0\n\0\n", output);
}

