
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setup_console(int t);

int main()
{
  char c; 
  printf("press 'q' to exit\n");
  while(1) {
      c = getchar();
//      printf("get char :%c\n",c);
      switch (c) {

          case 'a':
              printf("option :%c\n",c);
              break;
          case 'q':
              printf("option :%c\n",c);            
              break;

          default:
              printf("unknown option :%c\n",c);
              break;
       }

          if (c=='q') break;
   }

 
 return 0;
}


