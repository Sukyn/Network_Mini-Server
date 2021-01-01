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
int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
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


/* bind() */
if (bind(sockfd, (struct sockaddr*)&my_address, sizeof(struct sockaddr)) < 0)
{
  perror("Le bind n'a pas fonctionné");
  exit(EXIT_FAILURE);
}


struct sockaddr_in client_address;
char buffer[1024];
int addrlen, n;

addrlen = sizeof(client_address);

/* Version où le serveur envoie aussi des messages */
//char *message = "BONJOUR";
//sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &client_address, addrlen);
//printf("Message envoyé.\n");
/* ----------- */

int isTransmissionFinished = 0 ;
  do {
    /* recvfrom() */
    n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, ( struct sockaddr *) &client_address, &addrlen);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);

    /* write() */
    isTransmissionFinished = write(sockfd, buffer, n);


  } while(!isTransmissionFinished);

  /* close() */
  close(sockfd);


return 0;

}
