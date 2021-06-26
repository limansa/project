 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <assert.h>



struct task {
        int pri;
       
        //reserved
};


static void show_list(struct task *p, int size);
static int  compare(const void *p1, const void *p2);

static int  compare(const void *p1, const void *p2)
 {
   int a=((struct task *)p1)->pri;
   int b=((struct task *)p2)->pri;
   
    if (a<b) return -1; 
    else if (a==b) return 0;
    else return 1;
   
 }

       
int  main(int argc, char *argv[])
 {
     
	struct task tasklist[]={
	{.pri=5},
	{.pri=4},
	{.pri=1},
	{.pri=2},
	{.pri=3},
	};

	show_list(&tasklist[0],5);
  qsort(&tasklist[0],5 , sizeof(struct task), compare);
	printf("-after qsort()--\n");
	show_list(&tasklist[0],5);
         
        exit(EXIT_SUCCESS);
 }


static void show_list(struct task *p, int size)
{
  int j;
   for (j = 0; j < size; j++)
       printf("task list[%d]=%d \n",j,p[j].pri);  



}








