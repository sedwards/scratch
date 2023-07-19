#include <stdio.h> 
#include <stdlib.h>
#include <termios.h>

struct int_list {
    size_t size;
    int value[];
};

extern char _binary_______AUTHORS_start;
extern char _binary_______AUTHORS_end;

size_t data_size = 0; 

int main()
{
  char *authors = &_binary_______AUTHORS_start;
  while ( authors != &_binary_______AUTHORS_end ) 
    putchar(*authors++);
}

    //printf("Contents of Array %s\n",*authors++);


//   while ( p != &_binary_______AUTHORS_end )
//     buffer = (char*) malloc(sizeof(*p++));
  //       buffer = p;


#if 0
char nonconst_data[] = "xxxxx";    //.data 
const char const_data[] = "yyyyy"; //.rodata 
long zero_data = 0;                //.bss 
 
 
int foo(int x){                    //.text 
    for(int i=0; i<10; i++) 
        x+=x/2*i; 
    return x; 
} 
 
__attribute__((section(".text"))) char human_text_array[] = "this is unusual"; //.text 
__attribute__((section("my_segment"))) char my_segment_data[] = "non-dotted segment names aren't reserved";  
 
int main(){                        //.text 
    printf("%d\n", foo(42)); 
    puts(human_text_array); 
 
    human_text_array[0]='T'; //<- segfault because the systems will mark everything in .text read only 
    return 0; 
} 

extern char _binary_______AUTHORS_start;
extern char _binary_______AUTHORS_end;

size_t data_size = 0; 

int main()
{
  char *authors = &_binary_______AUTHORS_start;

  while ( authors != &_binary_______AUTHORS_end ) {
    authors = realloc(authors,(data_size + 1) * sizeof(authors)); 
    authors[data_size++];
    printf("Contents of Array %s\n",authors);
  }
} 

//size_t authors_block;
int main()
{
   // char*  p = &_binary_______AUTHORS_start;
   // while ( p != &_binary_______AUTHORS_end ) putchar(*p++);

  //  return 0;

  char*  p = &_binary_______AUTHORS_start;
  while ( p != &_binary_______AUTHORS_end ) {            
        //c=fgetc(fp);                         // get a character/byte from the file
        //printf("Read from file %02x\n\r",c); // and show it in hex format

    char*  p = &_binary_______AUTHORS_start;

     buffer = (char*) malloc(sizeof(*p++));
         buffer = p;
      //{

  }
}

THis is interesting, not what i needed but intersting

#include <stdio.h>

void reverse(char *p){
    char c;
    char* q = p;
    while (*q) q++;
    q--; // point to the end
    while (p < q) {
        c = *p;
        *p++ = *q;
        *q-- = c;
    }
}

int main(){
    char s[]  = "DCBA";
    reverse( s);
    printf("%s\n", s); // ABCD
}

    WCHAR *strW, *start, *end;
    HRSRC rsrc = FindResourceW( shell32_hInstance, L"AUTHORS", (LPCWSTR)RT_RCDATA );
    char *strA = LockResource( LoadResource( shell32_hInstance, rsrc ));
    DWORD sizeW, sizeA = SizeofResource( shell32_hInstance, rsrc );

    if (!strA) return;
    sizeW = MultiByteToWideChar( CP_UTF8, 0, strA, sizeA, NULL, 0 ) + 1;
    if (!(strW = heap_alloc( sizeW * sizeof(WCHAR) ))) return;
    MultiByteToWideChar( CP_UTF8, 0, strA, sizeA, strW, sizeW );
    strW[sizeW - 1] = 0;

    start = wcspbrk( strW, L"\r\n" );  /* skip the header line */
    while (start)
    {
        while (*start && wcschr( L"\r\n", *start )) start++;
        if (!*start) break;
        end = wcspbrk( start, L"\r\n" );
        if (end) *end++ = 0;
        SendMessageW( list, LB_ADDSTRING, -1, (LPARAM)start );
        start = end;
    }
    heap_free( strW );

  extern "C" const uint8_t _binary_text_txt_start[];
  extern "C" const uint8_t _binary_text_txt_size;

  void setup() {
    Serial.begin(9600);
    Serial.write(_binary_text_txt_start, (size_t) &_binary_text_txt_size);
  }

  void loop(){}
#endif

