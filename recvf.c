#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "errno.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"


int get_listener(int address_in, short port)
{
   int listener, flag;
   struct sockaddr_in address;

   address.sin_family = 2;
   address.sin_port = htons(port);
   address.sin_addr.s_addr = address_in;//inet_addr("0.0.0.0");
   //AF_INET = IPV4, SOCK_STREAM->TCP
   if ((listener = socket(AF_INET/*2*/,SOCK_STREAM /*1*/, 0)) == -1) {
   	  printf("socket error !!! %c",10);
      return -1;
   	}

   if (bind(listener, (struct sockaddr *) &address, sizeof (address)) == -1) {
      printf("bind error !!! %c",10);
 	  //handle_error(bind);
      return -1;
   	}

   if (listen(listener, 1024) == -1) {//1024 means maximum connections
       printf("listen error !!! %c",10);
      return -1;
   	}

   flag = fcntl(listener, F_GETFL, 0);
   fcntl(listener, F_SETFL, flag | O_NONBLOCK);//set socket as non block mode

   return listener;
}

int get_acceptor(int listener)
{
   int acceptor, _8352, _3584;
   struct sockaddr_in _7231;

   _8352 = 16;//sizeof(struct sockaddr_in)
   _3584 = 0;

   while (++_3584) {

      acceptor = accept(listener, (struct sockaddr *) &_7231, &_8352);

      if (acceptor != -1) {

         //receivefile(acceptor);
         return acceptor;
      }
	  
	  if((errno == EWOULDBLOCK) || (errno == EAGAIN))
	  {/*The socket is marked non-blocking and no connections are present
              to be accepted. */
		  printf("-");
		  usleep(10000);
		  continue;
	  }
	  
	  printf("accept return --%d-- %c",_3584,10);

      usleep(100000);
   }
}

/* server: socket-->bind-->listen-->accept-->recv-->[sendto-->]close */ 
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
   
   int listener;
   int acceptor;
   short port;
   char _3049;
   int ct = 0;
   
   printf("Starting Listen %c", 10);
   port = (short)atoi(arguments[2]);
   printf("IP: %s, Port: %d %c", arguments[1], port, 10);
   listener = get_listener(inet_addr(arguments[1]/*"0.0.0.0"*/), port);
   if(listener  == -1) {
	 printf("Get Listen failed %c", 10);
	 exit(1);
   }
   while (1)
   	{
	   printf("Starting Accept %c", 10);
	   acceptor = get_acceptor(listener);
	   if(acceptor  == -1) {
		 printf("Get Acceptor failed %c", 10);
		 exit(1);
	   }
	   
	   printf("Starting recv %c", 10);
	   while(1) {
			char _3049;
			int _5433, _6506;
		   
			_6506 = time(0);

			//printf("Before receiving %c", 10);
		   
			_5433 = recv(acceptor, &_3049, 1, MSG_DONTWAIT);
			ct ++;

			//printf("After receiving %c", 10);
		   
			if (_5433 == 0 || (_5433 == -1 && errno != 11)) {
		   
			  printf("aborting%c", 10);
		      ct = 0;
			  break;
			} 
		   
			if (time(0) - _6506 > 6) {
		   
			  printf("aborting because of delay%c", 10);
			  //close(acceptor);
		      ct = 0;
			  break;
			}
		   
			if (_5433 == -1) {

			   printf("return error: %hhu%c", _5433, 10);
			   usleep(10000);
		       ct = 0;
			   return;
			}
		   
	      printf("Byte(%d) : %hhu%c", ct, _3049, 10);

	      usleep(50000);     
	   }
   	}
}

