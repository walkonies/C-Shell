/* demo program for scanf 
   int scanf(const char *fmt, ptr1, ptr2, ... ptrn);
*/
#include <stdio.h>
main()
{
 int i1, i2;
 float flt;
 char str1[10], str2[10];
 
 scanf("%2d %2d %f %s %s", &i1, &i2, &flt, str1, str2);
 
 printf("i1 would be set to %d\n", i1);
 printf("i2 would be set to %d\n", i2);
 printf("flt would be set to %f\n", flt);
 printf("str1 would be set to %s\n", str1);
 printf("str2 would be set to %s\n", str2);
 
 return 0;
 }


// SORT !!

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int pstrcmp( const void* a, const void* b )
{
  return strcmp( *(const char**)a, *(const char**)b );
}

int main()
{
  const char* xs[] =
  {
    "Korra",
    "Zhu Li",
    "Asami",
    "Mako",
    "Bolin",
    "Tenzin",
    "Varrick",
  };
  const size_t N = sizeof(xs) / sizeof(xs[0]);

  puts( "(unsorted)" );
  for (int n = 0; n < N; n++)
    puts( xs[ n ] );

  // Do the thing!
  qsort( xs, N, sizeof(xs[0]), pstrcmp );

  puts( "\n(sorted)" );
  for (int n = 0; n < N; n++)
    puts( xs[ n ] );
}