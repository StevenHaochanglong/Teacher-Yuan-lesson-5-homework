#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "errno.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"

#define MAXLINE 80


int get_socket(int address, short port)
{
   int fd;
/*   
   struct sockaddr_in _3468;

   _3468.sin_family = 2;
   _3468.sin_port = htons(port);
   _3468.sin_addr.s_addr = address;
*/
   //sAF_INET：IPV4, SOCK_DGRAM->UDP
   if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
      return -1;
/*
   fpr UDP, connect is not necessary
   if (connect(connector, (struct sockaddr *) &_3468, 16) == -1)
      return -1;
*/
   return fd;
}

/*socket --> sendto*/
int main(int _1636, char **arguments)
{
   FILE *file;
   //char *buffer;
   int length, count;
   char sendline[MAXLINE], recvline[MAXLINE + 1];

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

   printf("file size: %d%c", length, 10);

   int fd;
   short port;
   int address;
   struct sockaddr_in _3468;

   port = (short)atoi(arguments[3]);
   address = inet_addr(arguments[2]/*"127.0.0.1"*/);
   
   memset(&_3468, 0, sizeof(_3468)); 
   _3468.sin_family = AF_INET;//IPV4
   _3468.sin_port = htons(port);//注意网络序转换 
   _3468.sin_addr.s_addr = address;
   
   fd = get_socket(address, port);//only socket() inside

   if(fd < 0) 
   { 
       printf("create socket fail!\n"); 
       return -1; 
   } 
   
   
   while(1) {
   
       count = fread(sendline, 1, MAXLINE/*length*/, file);
    
       if(count == -1) {
         perror("read error \n");
         exit(1);
       }
    
       if(count != 0) {
       	
    	   //printf("%d%c", count, 10);
    
    
    	   //send(fd, sendline, count, 0);
    	   sendto(fd, sendline, count, 0, (struct sockaddr*)&_3468, sizeof(_3468));
	       printf("Send(%d):%c%s%c", count,10, sendline, 10);
      	}
        else {
			close(fd);
    		return;
        }
   }
}
