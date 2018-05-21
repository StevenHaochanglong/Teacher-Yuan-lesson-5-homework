#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int _1636, char **arguments)
{
   FILE *file;
   char *buffer;
   int length, count;

   if (! arguments[1]) {
      
      printf("the program requires at least one argument.%c", 10);
      exit(1);
   }

   file = fopen(arguments[1], "r");
   fseek(file, 0, 2);
   length = ftell(file);
   fseek(file, 0, 0);

   buffer = malloc(length);

   if (buffer == 0) {

      printf("the progrm was not able to allocate memory.%c", 10);
      exit(1);
   }

   printf("%d%c", length, 10);

   count = fread(buffer, 1, length, file);

   printf("%d%c", count, 10);
}
