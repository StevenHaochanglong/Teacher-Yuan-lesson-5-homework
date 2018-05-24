#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "errno.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"

int get_connector(int address, short port)
{
   int connector;
   struct sockaddr_in _3468;

   _3468.sin_family = 2;
   _3468.sin_port = htons(port);
   _3468.sin_addr.s_addr = address;
   //AF_INET = IPV4, SOCK_STREAM->TCP
   if ((connector = socket(AF_INET, SOCK_STREAM, 0)) == -1)
      return -1;

   if (connect(connector, (struct sockaddr *) &_3468, 16) == -1)
      return -1;

      return connector;
}

/*socket --> connect --> send*/
int main(int _1636, char **arguments)
{
   FILE *file;
   char *buffer;
   int length, count;

   if (! arguments[1]) {
      
      printf("the program requires at least 3 argument.%c", 10);
      printf("1st argument: /path/filename%c", 10);
      printf("2nd argument: IP address%c", 10);
      printf("3rd argument: Port number.%c", 10);
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

   int connector;
   short port;
   
   port = (short)atoi(arguments[3]);
   connector = get_connector(inet_addr(arguments[2]/*"127.0.0.1"*/), port);

   send(connector, buffer, count, 0);
}
