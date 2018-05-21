#define TFM_DESC

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "tomcrypt.h"


//P1:计算一个文件的 SHA256, (digest.c)
//sha256_init
//sha256_process
//sha256_done

//fopen, fread, fwrite, fclose
//open, read, write, close
char *read_file(char *path, int *length) {

   FILE *file;
   char *contents = NULL;

   file = fopen(path, "r+");
   
   if (file != NULL)
   {
       //printf ("fopen ok %c", 10);
	   
	   fseek(file, 0, SEEK_END);
       //printf ("fopen ok 1%c", 10);
	   *length = ftell(file);
       printf ("fopen file length: %d%c", *length,10);
	   fseek(file, 0, SEEK_SET);

	   contents = malloc(*length + 1);
       //printf ("fopen ok 3 %c", 10);
	   
	   if(contents != NULL)
	   {
	       //printf("malloc OK !!!!\n",10);
	       fread(contents, 1, *length, file);
	   }
	   else
	   {
           printf("malloc error !!!!\n",10);
	   }
	   contents[*length] = '\0';			   /* 字符串结束标志 */
	   //printf( "%s", contents);
	   fclose(file);
   	}
   else
   {
	 printf("open file failed !!! %c",10);
   }

   return contents;
}

char *digest(char *buffer, int size)
{
   hash_state resource;
   char *digest;

   digest = malloc(32 + 1);
   sha256_init(&resource);
   sha256_process(&resource, buffer, size);
   sha256_done(&resource, digest);

   digest[32] = '\0';

   return digest;
}



//P2:创造新的私钥匙，公钥匙和地址 (generate.c)

//P3:使用私钥做签章 (sign.c)
//P4:使用公钥做签章的验证 (verify.c)
//P5:使用公钥做加密(encrypt.c)
//P6:使用私钥来解密(decrypt.c)

//涉及到的概念：1）跟加密相关的操作，2）如何打开、阅读、编写和关上文件

//sha256_init
//sha256_process
//sha256_done

//fopen, fread, fwrite, fclose
//open, read, write, close

//32bits system: 4 Byte, 2 bytes, 1 bytes 可以直接操作，无需指针,大于 4Byte，用指针
//64bits system: 8 Bytes, 4 Byte, 2 bytes, 1 bytes 可以直接操作，无需指针，大于 8Byte，用指针
//字符串，通过需要申请内存

//man 2 open //没有f开头的，写2
//man 3 fopen //f 开头的,必须写3，

int main(int _1636, char **arguments)
{
	char *path;
	int length;
	char *filedata;

	char *digestcontent;
	int i;
	

	if (! arguments[1]) {
	   
	   printf("the program requires at least one argument.%c", 10);
	   exit(1);
	}
	
    //printf("Enger path name: %c",10);
	/*
	fgets(path, sizeof(path), stdin);
	path[strlen(path) - 1] = '\0';
	*/
	path = arguments[1];
	filedata = read_file(path, &length);
	
	if(filedata != NULL)
    {
		digestcontent = digest(filedata, length);
	    printf("%s%c", digestcontent,10);
	}
	else
    {
       printf("read file failed !!! %c", 10);
	}

    if(digestcontent != NULL)
	    free(digestcontent);
	
    return 0;
}



