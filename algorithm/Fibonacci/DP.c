//Fibonacci Series using Dynamic Programming 
#include<stdio.h> 
  
int fib(int n) 
{
  /* Declare an array to store Fibonacci numbers. */
  int f[n+2];   // 1 extra to handle case, n = 0, at least f[0] and f[1]
  int i; 
  
  /* 0th and 1st number of the series are 0 and 1*/
  f[0] = 0; 
  f[1] = 1; 
  
  for (i = 2; i <= n; i++) 
  { 
      /* Add the previous 2 numbers in the series 
         and store it */
      f[i] = f[i-1] + f[i-2]; 
      printf("f[%d]=%d\n", i, f[i]);
  } 
 // printf("--f[%d]=%d\n", i, f[i]); //i will be out of range
  return f[n]; 
} 
  
int main () 
{ 
  int n = 9; 
  printf("Answer%d\n", fib(n)); 
  getchar(); 
  return 0; 
}