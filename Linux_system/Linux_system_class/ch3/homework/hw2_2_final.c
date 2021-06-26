#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define ELEMENT_NUM 5

typedef struct kool_list
{
	int to;
	struct list_head list;
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
int main(int argc, char **argv){

	St_kool_list_Tag *tmp;
	struct list_head *pos, *q;
	unsigned int i;
	int cmp_index[ELEMENT_NUM]; 
	St_kool_list_Tag mylist;
	INIT_LIST_HEAD(&mylist.list);
	/* or you could have declared this with the following macro
	 * LIST_HEAD(mylist); which declares and initializes the list
	 */

	/* adding elements to mylist */
	for(i=0; i<ELEMENT_NUM;i++){
		tmp= (St_kool_list_Tag *)malloc(sizeof(St_kool_list_Tag));
		cmp_index[i]=(int)tmp;
		/* INIT_LIST_HEAD(&tmp->list); 
		 *
		 * this initializes a dynamically allocated list_head. we
		 * you can omit this if subsequent call is add_list() or 
		 * anything along that line because the next, prev
		 * fields get initialized in those functions.
		 */
		printf("enter to and from:");
		scanf("%d %d", &tmp->to, &tmp->from);

		/* add the new item 'tmp' to the list of items in mylist */
		list_add(&(tmp->list), &(mylist.list));
		/* you can also use list_add_tail() which adds new items to
		 * the tail end of the list
		 */
	}
	printf("\n");


	/* now you have a circularly linked list of items of type struct kool_list.
	 * now let us go through the items and print them out
	 */


	/* list_for_each() is a macro for a for loop. 
	 * first parameter is used as the counter in for loop. in other words, inside the
	 * loop it points to the current item's list_head.
	 * second parameter is the pointer to the list. it is not manipulated by the macro.
	 */
	printf("traversing the list using list_for_each()\n");
	list_for_each(pos, &mylist.list){

		/* at this point: pos->next points to the next item's 'list' variable and 
		 * pos->prev points to the previous item's 'list' variable. Here item is 
		 * of type struct kool_list. But we need to access the item itself not the 
		 * variable 'list' in the item! macro list_entry() does just that. See "How
		 * does this work?" below for an explanation of how this is done.
		 */
		 tmp= list_entry(pos, St_kool_list_Tag, list);

		 /* given a pointer to struct list_head, type of data structure it is part of,
		  * and it's name (struct list_head's name in the data structure) it returns a
		  * pointer to the data structure in which the pointer is part of.
		  * For example, in the above line list_entry() will return a pointer to the
		  * struct kool_list item it is embedded in!
		  */

		 printf("to= %d from= %d\n", tmp->to, tmp->from);
		 //printf("");

	}
	printf("\n");
	printf("========== qsort with index ==========\n");
	qsort(cmp_index,ELEMENT_NUM, sizeof(int), kool_list_cmpindex);
	printf("----------- show the data -----------\n");
	for(i=0;i<ELEMENT_NUM;i++)
    	{
      	printf("cmp_index[%d].to=%d cmp_index[%d].from=%d\n",i,((St_kool_list_Tag*)(cmp_index[i]))->to,i,((St_kool_list_Tag*)(cmp_index[i]))->from);
    	}
	/* since this is a circularly linked list. you can traverse the list in reverse order
	 * as well. all you need to do is replace 'list_for_each' with 'list_for_each_prev'
	 * everything else remain the same!
	 *
	 * Also you can traverse the list using list_for_each_entry() to iterate over a given
	 * type of entries. For example:
	 */
	printf("traversing the list using list_for_each_entry()\n");
	list_for_each_entry(tmp, &mylist.list, list)
		 printf("to= %d from= %d\n", tmp->to, tmp->from);
	printf("\n");
	

	/* now let's be good and free the kool_list items. since we will be removing items
	 * off the list using list_del() we need to use a safer version of the list_for_each() 
	 * macro aptly named list_for_each_safe(). Note that you MUST use this macro if the loop 
	 * involves deletions of items (or moving items from one list to another).
	 */
	printf("deleting the list using list_for_each_safe()\n");
	list_for_each_safe(pos, q, &mylist.list){
		 tmp= list_entry(pos, St_kool_list_Tag, list);
		 printf("freeing item to= %d from= %d\n", tmp->to, tmp->from);
		 list_del(pos);
		 free(tmp);
	}

	return 0;
}