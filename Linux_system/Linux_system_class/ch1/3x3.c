#include <stdio.h>
#include <stdlib.h>
void transpose (int a[][3], int row, int col);

int main()
{

 int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};

  transpose(a,3,3);
  
  int i,j,temp;
  for (i=0;i<3;i++) {
     for (j=0;j<3;j++) 
	printf("%d\t",a[i][j]);
     printf("\n");
  }


}

void transpose (int a[][3], int row, int col)
{

  int i,j,temp;

    int (*t)[3]=malloc(row*col*sizeof(int));

   for (i=0;i<row;i++)
    for (j=0;j<col;j++) 
	t[i][j]=a[i][j];

  for (j=0;j<row;j++)
    for (i=0;i<col;i++) {
	a[j][i]=t[i][j];
 	
    }


}







