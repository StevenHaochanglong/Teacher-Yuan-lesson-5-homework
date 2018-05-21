#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int _1636, char **arguments)
{
   FILE *file;
   int length;

   if (! arguments[1]) {
      
      printf("the program requires at least one argument.%c", 10);
      exit(1);
   }

   file = fopen(arguments[1], "r");
   fseek(file, 0, 2);
   length = ftell(file);

   printf("%d%c", length, 10);
}
