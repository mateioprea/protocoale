#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(int argc,char** argv){
  msg r,t;
  mine p;
  int size;
  init(HOST,PORT);
  
  if (recv_message(&r)<0){
    perror("Receive message");
    return -1;
  }
	memcpy (&p,r.payload,sizeof(p));
	//printf ("%d \n", p.type);
	printf("%s \n",p.data);
	int f = open (p.data,O_RDONLY);
	if (recv_message(&r)<0){
		perror("Receive message");
		return -1;
   }
	memcpy (&p,r.payload,sizeof(p));
	memcpy (&size,p.data,sizeof(int));
	printf ("%d \n", size);
	int i;
	for (i=0;i<2;i++){
	if (recv_message(&r)<0){
    perror("Receive message");
    return -1;
  }
    char w[100];
    int len;
	memcpy (&p,r.payload,sizeof(p));
	memcpy (&len,p.data,sizeof(int));
	memcpy (w,p.data+sizeof(int),len*sizeof(char));
	w[len]=0;
	printf ("%s",w);
	}

  if (f < 0 ) {
 	printf ("eroare la deschiderea fisereului");
 	return 0;
 	}
  printf("[%s] Got msg with payload: %s\n",argv[0],r.payload);

  sprintf(t.payload,"ACK(%s)",r.payload);
  t.len = strlen(t.payload+1);
  send_message(&t);
  return 0;
}
