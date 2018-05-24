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

int get_listener(int address_in, short port)
{
   int listener, flag;
   struct sockaddr_in address;

   address.sin_family = AF_INET;//2;
   address.sin_port = htons(port);
   address.sin_addr.s_addr = address_in;//inet_addr("0.0.0.0");

   //UDP socket: socket(AF_INET, SOCK_DGRAM, 0); /* create a socket */
   if ((listener = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
   	  printf("socket error !!! %c",10);
      return -1;
   	}

   if (bind(listener, (struct sockaddr *) &address, sizeof (address)) == -1) {
      printf("bind error !!! %c",10);
 	  //handle_error(bind);
      return -1;
   	}
/*
//UDP: do not need listen() and accept()
   if (listen(listener, 1024) == -1) {//1024 means maximum connections
       printf("listen error !!! %c",10);
      return -1;
   	}
*/

   return listener;
}


/* server: socket-->bind-->recvfrom-->sendto-->close */ 
int main(int _1636, char **arguments)
{
/*
   FILE *file;
   char *buffer;
   int length, count;
*/
   if ((! arguments[1]) || (! arguments[2])) {
      
      printf("the program requires at least 2 argument.%c", 10);
      printf("1st argument: IP address%c", 10);
      printf("2nd argument: Port number.%c", 10);
      exit(1);
   }
   

   int listener,flag;
   short port;
   int address;
   char _3049;
   int ct = 0;
   
   char mesg[MAXLINE];
   struct sockaddr_in client_addr; //clent_addr用于记录发送方的地址信息  
   socklen_t len = sizeof(client_addr);//16;
   
   printf("Starting Listen %c", 10);
   port = (short)atoi(arguments[2]);
   address = inet_addr(arguments[1]/*"0.0.0.0"*/);
   
   printf("IP: %s, Port: %d %c", arguments[1], port, 10);
   listener = get_listener(address, port);
   //socket() and bind() in get_listener
   if(listener  == -1) {
	 printf("Get Listen failed %c", 10);
	 exit(1);
   }

//you can set udp socket as non block with enabling the below comments
/*   
   flag = fcntl(listener, F_GETFL, 0);
   fcntl(listener, F_SETFL, flag | O_NONBLOCK);//set socket as non block mode
*/   
   while (1)
   	{
	   printf("Starting recv %c", 10);
	   while(1) {
			//char _3049;
			int _5433, _6506;
		   
			_6506 = time(0);

			//printf("Before receiving %c", 10);
		    _5433 = recvfrom(listener, mesg, MAXLINE, 0, (struct sockaddr *)&client_addr, &len);
			//recvfrom是拥塞函数，没有数据就一直拥塞 
			//_5433 = recv(listener, mesg, MAXLINE, MSG_DONTWAIT);

			//printf("After receiving %c", 10);
		   
			if (_5433 == 0 || (_5433 == -1 && errno != 11)) {
		   
			  printf("aborting%c", 10);
			  usleep(10000);

		      ct = 0;
			  continue;
			} 
/*		   
			if (time(0) - _6506 > 6) {
		   
			  printf("aborting because of delay%c", 10);
			  //close(acceptor);
		      ct = 0;
			  break;
			}
*/		   
			if (_5433 == -1) {

			    if((errno == EWOULDBLOCK) || (errno == EAGAIN))
			    {/*The socket is marked  non-blocking  and  the  receive  operation
              would  block,  or a receive timeout had been set and the timeout
              expired before data was received.  */
					printf("-");
					usleep(10000);
					ct = 0;
					continue;
				}

   			    printf("return error: %hhu%c", _5433, 10);
   			    usleep(10000);
   		        ct = 0;
   			    close(listener);
   			    return;
			}
		  ct = _5433;
		   
	      printf("%cRecv(%d):%c%s%c",10, ct, 10,mesg);//打印client发过来的信息

	      usleep(50000);     
	   }
   	}
}

