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
#include <sys/wait.h>

/* Port local du serveur */
#define PORT 9600

int main() {

/* socket() */
int client_socket, lg;
char buffer[512];
pid_t commeTuVeux;

int sockfd = socket(PF_INET, SOCK_STREAM, 0);
if (sockfd < 0)
{
  perror("Erreur lors de la création du socket\n") ;
  exit(EXIT_FAILURE);
}

struct sockaddr_in my_address, client_address;


my_address.sin_family = PF_INET;
my_address.sin_port = htons(PORT);
my_address.sin_addr.s_addr = inet_addr("127.0.0.1");
my_address.sin_zero[8]='\0';

int addrlen = sizeof(struct sockaddr);

/* bind() */
if (bind(sockfd, (struct sockaddr*)&my_address, addrlen) < 0)
{
  perror("Le bind n'a pas fonctionné");
  exit(EXIT_FAILURE);
} else printf("listening\n");

/* listen() */
listen(sockfd, 5);



/* accept() */
int accepted = 0;
do {
  client_socket = accept(sockfd, (struct sockaddr*)&my_address, &addrlen);

  commeTuVeux = fork();
  if (commeTuVeux == 0)
  {
    close(sockfd);

    lg = read(client_socket,buffer, 512);
    printf("le serveur %d a recu: %s\n", commeTuVeux, buffer);
    sprintf(buffer,"%s",buffer);
    write(client_socket,buffer, 512);
    shutdown(client_socket,2);
    close(client_socket);
    accepted = 1;
  }
  else wait(NULL);
} while(!accepted);

printf("%d a quitté", commeTuVeux);
shutdown(sockfd,2);
close(sockfd);

}
