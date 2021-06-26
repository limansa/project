 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <assert.h>

#include "list.h"


struct kool_list{
        int to;
        struct list_head list;
        int from;
};


static void show_list(struct kool_list *p, int size);
static int  compare(const void *p1, const void *p2);

static int  compare(const void *p1, const void *p2)
 {
   int a=((struct kool_list *)p1)->to;
   int b=((struct kool_list *)p2)->to;
   
    if (a<b) return -1; 
    else if (a==b) return 0;
    else return 1;
   
 


 }

       
int  main(int argc, char *argv[])
 {
           int j;

	struct kool_list mylist[]={
	{3,{0},0},
	{6,{0},0},
	{1,{0},0},
	{9,{0},0},
	{2,{0},0},
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
       printf("%d \n",p[j].to);  



}








