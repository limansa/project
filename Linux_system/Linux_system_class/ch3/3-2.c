#include <string.h>
#include <stdio.h>

int  main( void )
{
   char string[] = "cgacabbagiaae";
   int  result;
   char *p,*q;
   result = strspn( string, "abcg" );
   printf( "The portion of '%s' containing only a, b, or c "  "is %d bytes long\n", string, result );

   p=string;
   result=0;
   while((q=strpbrk(p, "abc"))) {
   
      printf( "%s\n",q);

	   p=++q;
	  ++result;
   
  }
 return 0;
}
