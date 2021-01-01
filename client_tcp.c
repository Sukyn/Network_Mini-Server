/*
* Code du client
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define SIZE 100
#define PORT 9600





int main(){

  /* PF_INET = TCP/IP, SOCK_STREAM = TCP */
  int sockfd;
  /* socket() */
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("Erreur lors de la création du socket\n") ;
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in dest_addr;
  dest_addr.sin_family = PF_INET;
  dest_addr.sin_port = htons(PORT);
  dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  dest_addr.sin_zero[8]='\0';
  /* connect() */
  connect(sockfd,(struct sockaddr*)&dest_addr, sizeof(struct sockaddr));


  /* read() */
  char buffer[1024];
  scanf("%[^\t\n]", buffer);
  printf("YOU ENTERED : %s\n", buffer);
  //read(sockfd, buffer, SIZE);

  /* write() */
  write(sockfd, buffer, SIZE);

  /* close() */
  close(sockfd);
  return 0;

}
