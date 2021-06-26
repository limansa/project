 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <assert.h>


struct task {
        int pri;
       
        //reserved
};


struct task tasklist[]={
        {.pri=5},
        {.pri=4},
        {.pri=1},
        {.pri=2},
        {.pri=3},
        };



static void show_list2(int *p, int size);
static void show_list(struct task *p, int size);
static int  compare(const void *p1, const void *p2);

static int  compare(const void *p1, const void *p2)
 {
   int a=tasklist[*(int *)p1].pri;
   int b=tasklist[*(int *)p2].pri;
    
  if (a<b) return -1;
    else if (a==b) return 0;
    else return 1;

 }

       
int  main(int argc, char *argv[])
 {
/*     
	struct task tasklist[]={
	{.pri=5},
	{.pri=4},
	{.pri=1},
	{.pri=2},
	{.pri=3},
	};
*/	  
        int priority[5]={0,1,2,3,4};


	show_list(tasklist,5);
        qsort(priority,5 , sizeof(int), compare);
	printf("-Proirity Info--\n");
	show_list2(priority,5);
         
        exit(EXIT_SUCCESS);
 }


static void show_list2(int *p, int size)
{
  int j;
   for (j = 0; j < size; j++)
       printf("priority list[%d]=%d \n",j,p[j]);  



}

static void show_list(struct task *p, int size)
{
  int j;
   for (j = 0; j < size; j++)
       printf("Task list[%d]=%d \n",j,p[j].pri);



}









