#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

extern FILE _binary_______AUTHORS_start;
extern FILE _binary_______AUTHORS_end;

int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}

int get_malloc_size(void *vp)
{
  char *cp = (char*)vp;
  static int __done = -1;
  static int __offset = -1;
  return *(int*)(cp-__offset);
}

void * my_malloc(size_t s)
{
  size_t * ret = malloc(sizeof(size_t) + s);
  *ret = s;
  return &ret[1];
}

void my_free(void * ptr)
{
  free( (size_t*)ptr - 1);
}

size_t allocated_size(void * ptr)
{
  return ((size_t*)ptr)[-1];
}

size_t get_number_of_elements(void * ptr)
{
  size_t num = sizeof(ptr)/sizeof(ptr[0]);
  return num;
}

#if 0
        // Get the elements of the array
        for (i = 0; i < n; ++i) {
            ptr[i] = i + 1;
        }
 
        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < n; ++i) {
            printf("%d, ", ptr[i]);
        }
#endif


int main(int argc, char **argv)
{
  int fd, retval;
  FILE *fp = NULL;
  FILE *fp_end = NULL;
  char *authors;

  /* read the start of the binary block */
  fp = &_binary_______AUTHORS_start;
  fp_end = &_binary_______AUTHORS_start;

  printf("0x%lx\n", (unsigned long)&_binary_______AUTHORS_start);
  printf("0x%lx\n", (unsigned long)&_binary_______AUTHORS_end);

  printf("Memory address is: %p\n", fp);
  printf("Memory address is: %p\n", fp_end);

  /* Print memory address and contents, useful for debugging 
   * ------ 
    printf("Memory address is: %p and its value is: %s", fp, *fp);
    printf("Memory address is: %p and its value is: %s", fp_end, *fp_end);
    printf("Memory address is: %p and its value is: %s",
              _binary_______AUTHORS_end , &_binary_______AUTHORS_end); */

  /* Get the size of the number of elements for the data
   * Not really that useful since we did all of this in
   * FILE* rather than char*
  //size_t fp_element_size = sizeof(fp)/sizeof(fp[0]);
  //printf("fp_element_size is %zu\n",fp_element_size);

  //size_t fp_end_element_size = sizeof(fp_end)/sizeof(fp_end[0]);
  //printf("fp_end_element_size is %zu\n",fp_end_element_size); */

  /* Create new pointer to array buffer for all the authors */
  char *buffer;
  buffer = (char*)my_malloc(10000 * ((sizeof(*fp)) + (sizeof(*fp_end))) + 1);

    const char newline[] = {'\n'};
    const char terminator[] = {'\0'};
    strcpy(buffer,(char*)fp);
    strcat(buffer,(char*)fp_end);
    strcat(buffer,newline);
    strcat(buffer,terminator);
    
  printf("Buffer Contents %s", buffer);

  my_free(buffer);
}

