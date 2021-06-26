#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <time.h>


#define NodeSize 10
//#define ARRAY_CHANGE

struct kool_list
{
	int to;
	//struct list_head;
	int from;
};

typedef struct kool_list KOOL;

KOOL list[NodeSize];

void 
Init(KOOL list[], int size)
{
	int i;
	srand(time(NULL));	
	for(i=0; i<size ; i++)
	{
		list[i].to = rand()%10 + 1;
	}
}

void 
PrintList(KOOL list[], int size)
{
	int i;
	for(i = 0 ; i<size ;i++)
	{
		printf("%d => %d\n", i, list[i].to);
	}
}

#ifdef ARRAY_CHANGE

static int
cmpKool_List(const void  *p1, const void *p2)
{
	KOOL *s1,*s2;
	s1 = (KOOL *)p1;
	s2 = (KOOL *)p2;	

	if(s1->to > s2->to)
		return 1;
	else if(s1->to == s2->to)
		return 0;
	else
		return -1;
}
#else

static int
cmpKool_List(const void *p1, const void *p2)
{
	if(list[*(const int *)p1].to > list[*(const int *)p2].to)
		return 1;
	if(list[*(const int *)p1].to == list[*(const int *)p2].to)
		return 0;
	else 
		return -1;
}
#endif

int
main(int argc, char *argv[])
{
#ifdef ARRAY_CHANGE
#else
	int i;
	int maplist[NodeSize]={0,1,2,3,4,5,6,7,8,9};
#endif
	Init(list,NodeSize);
	PrintList(list,NodeSize);
#ifdef ARRAY_CHANGE
	qsort(&list, NodeSize, sizeof(KOOL), cmpKool_List);
#else
	qsort(&maplist, NodeSize, sizeof(int), cmpKool_List);
#endif
	printf("==================================\n");
#ifdef ARRAY_CHANGE
	PrintList(list,NodeSize);
#else
	for(i=0; i<NodeSize; i++)
	{
		printf("%d => %d\n", maplist[i], list[maplist[i]].to);
	}
#endif
	return 0;
}
