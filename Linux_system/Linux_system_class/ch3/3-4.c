 #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>
       #include <assert.h>

       static int
       cmpstringp(const void *p1, const void *p2)
       {
           /* The actual arguments to this function are "pointers to
              pointers to char", but strcmp() arguments are "pointers
              to char", hence the following cast plus dereference */
	  return strcmp(*(const char **) p1,  *(const char **) p2);
       }

       
int  main(int argc, char *argv[])
       {
           int j;
           assert(argc > 1);
           qsort(&argv[1], argc - 1, sizeof(char *), cmpstringp);
           for (j = 1; j < argc; j++)
               puts(argv[j]);
           exit(EXIT_SUCCESS);
       }

