#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

int main(int argc,char** argv){
  init(HOST,PORT);
  msg t;
  mine p;
  struct stat f_status;
  int f = open (argv[1],O_RDONLY);//deschidem fisierul
  fstat (f, &f_status);
  int size = f_status.st_size; //size de cat are fisieru 
  char w[100]; // in asta imi salvez caracterele din fisier
  	if (f<0){
  		printf("Eroare");
  		return 0;
  		}//daca e gol eroare + return
  	p.type = 1; // pentru type = 1 avem numele fisierului
  	memcpy (p.data,argv[1],strlen(argv[1])+1); //copiem datele
  		
  	t.len = sizeof(p); //dimensiunea mesajului
  	memcpy (t.payload,&p,t.len); // punem mesajul in payload
  	send_message (&t);
  	p.type = 2; // pentru type = 2 e dimensiunea fisierului
  	memcpy (p.data,&size,sizeof(size)); //copiem datele
  		
  	t.len = sizeof(p); //dimensiunea mesajului pe care-l trimitem
  	memcpy (t.payload,&p,t.len); //copiem mesajul in payload
  	send_message (&t);
	p.type = 3; // copierea efectiva a mesajului 
	int i; // copiem 2 cate 2 bytes ( dimensiunea noastra fiind de 
        // 4 bytes - cele 3 cifre + /0 adica endul fisierului
	for (i = 0 ; i<2;i++){
	int num_read = read (f,w,2); // citim din f in w si 
        //punem in variabila num_read ( am facut-o int pentru ca nu stiam cat
        //sa aloc pentru ea daca nu salvam undeva 
	memcpy (p.data,&num_read, sizeof(num_read));//punem in data ceea ce-am
        //citit din fisier
	memcpy (p.data+sizeof(int),w, num_read*sizeof(char));
	memcpy (t.payload, &p, t.len);// incarcam in payload
	send_message (&t);//send
	}
  sprintf(t.payload,"Hello World of PC");
  t.len = strlen(t.payload)+1;
  send_message(&t);

  if (recv_message(&t)<0){
    perror("receive error");
  }
  else {
    printf("[%s] Got reply with payload: %s\n",argv[0],t.payload);
  }

  return 0;
}
