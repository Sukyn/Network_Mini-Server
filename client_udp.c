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






int main(int argc, char *argv[]){

  const char* hostname=argv[1]; /* localhost */
  const char* portname=argv[2];
  struct addrinfo hints;
  memset(&hints,0,sizeof(hints));
  hints.ai_family=AF_UNSPEC;
  hints.ai_socktype=SOCK_DGRAM;
  hints.ai_protocol=0;
  hints.ai_flags=AI_ADDRCONFIG;
  struct addrinfo* res=0;
  int err=getaddrinfo(hostname,portname,&hints,&res);
  if (err!=0) {
      perror("failed to resolve remote socket address");
      exit(EXIT_FAILURE);
  }



  /* PF_INET = TCP/IP, SOCK_DGRAM = UDP */
  int sockfd;
  /* socket() */
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockfd < 0)
  {
    perror("Erreur lors de la création du socket\n") ;
    exit(EXIT_FAILURE);
  }


  char message[SIZE];
  printf("Entrez votre message: ");
  scanf("%[^\n]", message);

  /* sendto() */
  sendto(sockfd, (const char *)message, strlen(message), 0, res->ai_addr, res->ai_addrlen);
  printf("Message du client envoyé !\n");


  /* close() */
  close(sockfd);
  return 0;
}
