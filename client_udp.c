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

  /* PF_INET = TCP/IP, SOCK_DGRAM = UDP */
  int sockfd;
  /* socket() */
  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
  {
    perror("Erreur lors de la création du socket\n") ;
    exit(EXIT_FAILURE);
  }


  struct sockaddr_in server_address;
  server_address.sin_family = PF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = inet_addr("0.0.0.0");
  server_address.sin_zero[8]='\0';

  /* bind() */
  if (bind(sockfd, (struct sockaddr*)&server_address, sizeof(struct sockaddr)) < 0)
  {
    perror("Le bind n'a pas fonctionné");
    exit(EXIT_FAILURE);
  }


  char message[SIZE];
  printf("Entrez votre message: ");
  scanf("%[^\n]", message);

  /* sendto() */
  sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &server_address, sizeof(server_address));
  printf("Message du client envoyé !\n");

  /* Version où le serveur envoie également des messages au client */
  //char buffer[1024];
  //int n, len;
  //n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr *) &server_address, &len);
  //buffer[n] = '\0';
  //printf("Le serveur a dit : %s\n", buffer);
  /* ------------ */


  /* close() */
  close(sockfd);
  return 0;
}
