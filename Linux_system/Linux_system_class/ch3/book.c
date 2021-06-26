#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _book {
  char name[32];
  float price;
  

 }Book;


static int  compare_by_name(const void *p1, const void *p2);

static int  compare(const void *p1, const void *p2);


static int  compare(const void *p1, const void *p2)
 {
   int a=((Book *)p1)->price;
   int b=((Book *)p2)->price;

    if (a<b) return -1;
    else if (a==b) return 0;
    else return 1;




 }


static int  compare_by_name(const void *p1, const void *p2)
{
		    char* a=((Book *)p1)->name;
			char * b=((Book *)p2)->name;
            return strcmp(a,b);
			

}






static void show_book(Book *p, int size)
{
  int j;
   for (j = 0; j < size; j++)
       printf("%d: {%-15s, %6.2f} \n",j,p[j].name, p[j].price);



}





int main()
{
  
  Book books[]={
 {"Java",20.0},
 {"Linux System",12.0},
 {"C++",10.6},
 {"Pic single chip",8.1},
 {"ARM",25.3},
 };
 
  show_book(&books[0],5);
  printf("---after sorting ------\n");
  // sorted by price ...
  //qsort(&books[0],5 , sizeof(Book), compare);
  qsort(&books[0],5 , sizeof(Book), compare_by_name);

  show_book(&books[0],5);

 return 0;
}
