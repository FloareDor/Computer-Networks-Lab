#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888
#define MAX_BUFFER_SIZE 1024

int main() {
    int serverSocket, clientSocket, len;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[MAX_BUFFER_SIZE];
    socklen_t addrLen = sizeof(struct sockaddr);

    // Create a UDP socket
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));

    // Set the server address information
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket to the server address
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // Receive data from the client
        if ((len = recvfrom(serverSocket, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&clientAddr, &addrLen)) < 0) {
            perror("Failed to receive message");
            exit(EXIT_FAILURE);
        }

        buffer[len] = '\0';
        printf("Received message from client: %s\n", buffer);

        // Send data back to the client
        printf("Enter message to send to client: ");
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        if (sendto(serverSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&clientAddr, addrLen) < 0) {
            perror("Failed to send message");
            exit(EXIT_FAILURE);
        }

        printf("Sent message to client: %s\n", buffer);
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}
