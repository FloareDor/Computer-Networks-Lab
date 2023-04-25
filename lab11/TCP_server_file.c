#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd, new_sockfd, n;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    char buffer[MAXLINE];
    FILE *fp;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error: Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        perror("Error: Socket bind failed");
        exit(EXIT_FAILURE);
    }

    if ((listen(sockfd, 5)) != 0) {
        perror("Error: Socket listen failed");
        exit(EXIT_FAILURE);
    }

    len = sizeof(cliaddr);

    new_sockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
    if (new_sockfd < 0) {
        perror("Error: Socket accept failed");
        exit(EXIT_FAILURE);
    }

    fp = fopen("/mnt/c/CN/lab11/received.txt", "w");

    while (1) {
        n = recv(new_sockfd, buffer, MAXLINE, 0);
        if (n <= 0)
            break;
        fputs(buffer, fp);
        bzero(buffer, MAXLINE);
    }

    fclose(fp);
    printf("File created....");
    close(new_sockfd);
    printf("Closing Connection");
    close(sockfd);

    return 0;
}
