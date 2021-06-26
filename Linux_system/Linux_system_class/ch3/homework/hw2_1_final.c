#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#define ELEMENT_NUM 5
#define RANDOM_MAX 1000
typedef struct kool_list
{
    int to;
    //struct list_head;
    int from;
}St_kool_list_Tag;

int kool_list_cmpindex(const void *p1, const void *p2)
{
    int *mem_addr_p1 = (int *)p1;
    int *mem_addr_p2 = (int *)p2;
    St_kool_list_Tag *St_tmp1 = (St_kool_list_Tag*)(*mem_addr_p1);
    St_kool_list_Tag *St_tmp2 = (St_kool_list_Tag*)(*mem_addr_p2);
    int value;
    value = (*St_tmp1).to - (*St_tmp2).to;
    if(value>0)
    {
	return 1;
    }
    else if(value == 0)
    {
	return 0;
    }
    else
    {
	return -1;
    }
}
int  main(int argc, char *argv[])
{
    int j;
    St_kool_list_Tag k_list[ELEMENT_NUM];
    int cmp_index[ELEMENT_NUM]; 
    for(j=0;j<ELEMENT_NUM;j++)
    {
	k_list[j].to=(rand()%RANDOM_MAX);
	cmp_index[j]=(int)(&k_list[j]);
    }
    printf("\nthe value of array is:\n");
    for(j=0;j<ELEMENT_NUM;j++)
    {
	printf("k_list[%d].to=%d\n",j,k_list[j].to);
    }
    qsort(cmp_index,ELEMENT_NUM, sizeof(int), kool_list_cmpindex);
    printf("The result of index qsort\n");
    for(j=0;j<ELEMENT_NUM;j++)
    {
        printf("k_list[%d].to=%d\n",(int)(abs((int)k_list - cmp_index[j])/sizeof(St_kool_list_Tag)),((St_kool_list_Tag*)(cmp_index[j]))->to);
    }
    exit(EXIT_SUCCESS);
}

