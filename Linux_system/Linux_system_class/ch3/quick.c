#include <stdio.h>

/*Bubble Sort -- Implementation*/
/* Bubble sort for integers */
#define SWAP(a,b)   { int t; t=a; a=b; b=t; }



void quicksort( int *a, int low, int high );
int partition( int *a, int low, int high );

void show_array(int a[],int n);
int main()
{

 
 int a[]={18,2,20,34,12};
 printf("Orig :\t");
 show_array(a,5);
 quicksort(a,0,5-1);
 return 0;
}


/*============================*/

/*Quicksort*/
void quicksort( int *a, int low, int high )
   {
   int pivot;
   static i=0;
   /* Termination condition! */
     printf("Step%d:\t",i++);
    show_array(a,5);

   if ( high > low )
     {
     pivot = partition( a, low, high );
     quicksort( a, low, pivot-1 );
     quicksort( a, pivot+1, high );
     }
}


/*============================*/

/*Quicksort - Partition*/
int partition( int *a, int low, int high ) {
   int left, right;
   int pivot_item;
   int pivot;
   pivot_item = a[low];
   pivot = left = low;
   right = high;
   while ( left < right ) {
     /* Move left while item < pivot */
     while( a[left] <= pivot_item ) left++;
     /* Move right while item > pivot */
     while( a[right] >= pivot_item ) right--;
     if ( left < right ) SWAP(a[left],a[right]);
     }
   /* right is final position for the pivot */
   a[low] = a[right];
   a[right] = pivot_item;
   return right;
}



void show_array(int a[],int n)
{
 int i; 
   for(i=0;i<n;i++) {
     printf("%d  ",a[i]);
 
   }

  printf("\n");


}


