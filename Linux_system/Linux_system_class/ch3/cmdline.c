

#include <stdio.h>
void show_usage(char *pro);

int main(int argc, char **argv)
{
 
   char *prog_name=argv[0];
  char *cp;
  while (--argc) {
		cp = *++argv;
		if (*cp == '-') {
			++cp;
	
				switch(*cp) {
				case 'i':
					 ++argv; argc--;
					 if (!*argv) { 
						 printf("missing  argument\n") ;
						 show_usage(prog_name);
					 } else
					 printf("has i flag, %s\n",*argv);
					 	
 					 break;
				case 'o':
					 ++argv; argc--;
					 printf("has o flag, %s\n",*argv);
     					 break;
				case 'v':
 					
				        printf("has v flag\n");
                                         break;
				default: 
				        show_usage(argv[0]);
				

               }

             }


  }
return 0;
}


void show_usage(char *pro)
{

   fprintf(stderr,"%s [-i filename] [-o filename] [-v]",pro);
   exit(0);


}





