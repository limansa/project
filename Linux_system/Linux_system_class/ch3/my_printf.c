#include <stdio.h>
#include <stdarg.h>
#include <string.h>
void my_printf(char *fmt, ...);

int main()
{

 my_printf("abcd\n");
 my_printf("@d @s\n",5,"hello_world");

}



 void my_printf(char *fmt, ...) {
                   va_list ap;
                   int d;
                   char c, *s;

                   va_start(ap, fmt);

                   while (*fmt) {
			if (*fmt != '@') {
				putchar(*fmt++);			
				continue;
			}

#if 1 
                        switch(*++fmt) {
                        case 's':       /* string */
                             s = va_arg(ap, char *);
                             printf("%s", s);
                             //write(1,s,strlen(s));
                             break;
                        case 'd':       /* int */
                             d = va_arg(ap, int);
                             printf("%d", d);
                             break;
                        case 'c':          /* char */
                             /* need a cast here since va_arg only
                                takes fully promoted types */
                             c = (char) va_arg(ap, int);
                             printf("%c", c);
                             break;

			
                        }
			fmt++;

		}
                   va_end(ap);
#endif
	
     }

