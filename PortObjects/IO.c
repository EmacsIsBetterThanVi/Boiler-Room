#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
int main(int argv, char **argc){
  int server_socket;
  struct sockaddr_un server_addr;
  int connection_result;

  server_socket = socket(AF_UNIX, SOCK_STREAM, 0);

  server_addr.sun_family = AF_UNIX;
  strcpy(server_addr.sun_path, argc[2]);
  while(connection_result==-1){
  connection_result = connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
  }
  char c;
  while(c!=24){
    read(server_socket, &c, 1);
    if(c==5){
      c=getchar();
      write(server_socket, &c, 1);
    } else{
      printf("%c", c);
    }
  }
  return 0;
}