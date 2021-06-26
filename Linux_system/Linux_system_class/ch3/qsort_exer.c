 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <assert.h>

#include "list.h"


struct kool_list{
        int to;
        char *name;
        int from;
};


static void show_list(struct kool_list *p, int size);
static int  compare(const void *p1, const void *p2);

static int  compare(const void *p1, const void *p2)
 {
   char * a=((struct kool_list *)p1)->name;
   char * b=((struct kool_list *)p2)->name;
   
   return strcmp(a,b); 
 


 }

       
int  main(int argc, char *argv[])
 {
           int j;

	struct kool_list mylist[]={
	{3,"hello",0},
	{6,"world",0},
	{1,"ittraining",0},
	{9,"embedded",0},
	{2,"linux",0},
	};

	show_list(&mylist[0],5);
    qsort(&mylist[0],5 , sizeof(struct kool_list), compare);
	printf("------after sorting-------\n");
	show_list(&mylist[0],5);
         
        exit(EXIT_SUCCESS);
 }


static void show_list(struct kool_list *p, int size)
{
  int j;
   for (j = 0; j < size; j++)
       printf("%d %s\n",p[j].to,p[j].name);  



}








