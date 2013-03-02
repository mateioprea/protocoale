#ifndef LIB
#define LIB

typedef struct {
  // int type;
  int len;
  char payload[1400];
} msg;
typedef struct {
	int type;
	char data[1024];
}mine;

void init(char* remote,int remote_port);
void set_local_port(int port);
void set_remote(char* ip, int port);
int send_message(const msg* m);
int recv_message(msg* r);
//msg* receive_message_timeout(int timeout);

#endif

