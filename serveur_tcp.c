/*
* Code du serveur
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

/* Port local du serveur */
#define PORT 9600

int main() {

/* socket() */
int sockfd = socket(PF_INET, SOCK_STREAM, 0);
if (sockfd < 0)
{
  perror("Erreur lors de la création du socket\n") ;
  exit(EXIT_FAILURE);
}

struct sockaddr_in my_address;
my_address.sin_family = PF_INET;
my_address.sin_port = htons(PORT);
my_address.sin_addr.s_addr = inet_addr("0.0.0.0");
my_address.sin_zero[8]='\0';

int addrlen = sizeof(struct sockaddr);

/* bind() */
if (bind(sockfd, (struct sockaddr*)&my_address, addrlen) < 0)
{
  perror("Le bind n'a pas fonctionné");
  exit(EXIT_FAILURE);
}

/* listen() */
listen(sockfd, 5);

/* accept() */
int accepted = 0;
do {
  accepted = accept(sockfd, (struct sockaddr*)&my_address, &addrlen);
} while(!accepted);

int isTransmissionFinished = 0;
char buffer[1024];
do {
  /* read() */
  read(sockfd, buffer, 100);
  /* write() */
  isTransmissionFinished = write(sockfd, buffer, 100);
} while (!isTransmissionFinished);

/* close() */
close(sockfd);
}
