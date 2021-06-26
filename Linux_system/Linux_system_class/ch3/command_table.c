
#include <stdio.h>

void quit_command();
void help_command();

struct command
{
	  char *name;
	    void (*function) ();
};

#define COMMAND(NAME)  { #NAME, NAME ## _command }

struct command commands[] =
{
	  COMMAND (quit),
	  COMMAND (help),
		
};

int main()
{
	int i;
  for (i=0;i<sizeof(commands)/sizeof(commands[0]);i++)
	   commands[i].function();

return  0;
}

void quit_command()
{
  printf("%s called\n",__func__);

}

void help_command()
{
	  printf("%s called\n",__func__);

}


/*
struct command commands[] =
{
	  { "quit", quit_command},
	    { "help", help_command},
		  ...
};







*/

