#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd, n;
    struct sockaddr_in servaddr;
    char buffer[MAXLINE];
    FILE *fp;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error: Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        perror("Error: Socket connection failed");
        exit(EXIT_FAILURE);
    }

    fp = fopen("/mnt/c/CN/lab11/file.txt", "r");

    while (fgets(buffer, MAXLINE, fp) != NULL) {
        send(sockfd, buffer, strlen(buffer), 0);
        bzero(buffer, MAXLINE);
    }

    fclose(fp);
    printf("File sent");
    close(sockfd);

    return 0;
}
