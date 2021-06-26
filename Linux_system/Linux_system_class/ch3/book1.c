#include <stdio.h>
#include <stdlib.h>

typedef struct _book {
  char name[32];
  float price;

 }Book;


static int  compare_price(const void *p1, const void *p2)
 {
   int a=(*(Book **)p1)->price;
   int b=(*(Book **)p2)->price;

    if (a<b) return -1;
    else if (a==b) return 0;
    else return 1;
 }

static int  compare_name(const void *p1, const void *p2)
 {
   return strcmp((*(Book **)p1)->name,(*(Book **)p2)->name);
 }


static void show_book(Book **p, int size)
{
  int j;
   for (j = 0; j < size; j++)
       printf("%d: {%-15s, %6.2f} \n",j,p[j]->name, p[j]->price);
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

 Book * pBooks[] ={
 &books[0],
 &books[1],
 &books[2],
 &books[3],
 &books[4]
 };

  // sorted by price ...
  qsort(&pBooks[0],5 , sizeof(Book*), compare_price);
  show_book(&pBooks[0],5);

  printf("\n");

  // sorted by name ...
  qsort(&pBooks[0],5 , sizeof(Book*), compare_name);
  show_book(&pBooks[0],5);

 return 0;
}
