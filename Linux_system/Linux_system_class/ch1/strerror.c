




#include <stdio.h>
#include <string.h>

void show_msg(int err_code);
int main()
{
   int i;
   	for(i=0;i<134;i++)
   	show_msg(i);


return 0;
}

void show_msg(int err_code)
{

 fprintf(stderr,"%4d: %s\n",err_code,strerror(err_code));


}
