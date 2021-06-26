
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>

void setup_console(int t);

int main()
{
  char c; 

   setup_console(1);
  while(1) {
      c = getchar();
      printf("get char :%c\n",c);
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

   setup_console(0);
 
 return 0;
}


void setup_console(int t)
{

        struct termios our_termios;
        static struct termios old_termios;

        if(t)
        {
                tcgetattr(0, &old_termios);
                memcpy(&our_termios, &old_termios, sizeof(struct termios));
                our_termios.c_lflag &= !(ECHO | ICANON);
                tcsetattr(0, TCSANOW, &our_termios);
        }
        else
                tcsetattr(0, TCSANOW, &old_termios);

}
