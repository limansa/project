//Fibonacci Series using Recursion 
#include<stdio.h> 
int fib(int n) 
{ 
   printf("%d, ", n);
   if (n <= 1) 
      return n; 
   return fib(n-1) + fib(n-2); 
} 

int main () 
{ 
  int n = 5;
  printf("\n%d\n", fib(n));
  return 0; 
} 