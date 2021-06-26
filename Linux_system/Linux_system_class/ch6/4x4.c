#include <stdio.h>


void show_4array(int a[][4]);
void matrix_product(int (*a)[4], int (*b)[4],int (*c)[4]);
int main()
{

   int a[4][4]={1,2,3,4,
                5,6,7,8,
                9,10,11,12,
		13,14,15,16
	       };


    int b[4][4]={1,5,9,13,
                2,6,10,14,
                3,7,11,15,
                4,8,12,16
               };

    int c[4][4]={0};
    matrix_product(a,b,c);

    show_4array(c);   
}

void matrix_product(int (*a)[4], int (*b)[4],int (*c)[4])
{

    int i,j,k;

    for (i=0;i<4;i++)
       for (j=0;j<4;j++)
          for (k=0;k<4;k++)
         c[i][j]+=a[i][k]*b[k][j];
        
}


void show_4array(int a[][4])
{
  int i,j;
  for (i=0;i<4;i++) {
    for (j=0;j<4;j++)
      printf("%d\t",a[i][j]);

    printf("\n");
  }
}




