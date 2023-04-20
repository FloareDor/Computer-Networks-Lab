#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define MAX_BUFFER_SIZE 1024

int main() {
    int clientSocket, len;
    struct sockaddr_in serverAddr;
    char buffer[MAX_BUFFER_SIZE];

    // Create a UDP socket
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));

    // Set the server address information
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SERVER_PORT);

    while (1) {
        printf("Enter message to send to server: ");
        fgets(buffer, MAX_BUFFER_SIZE, stdin);

        // Send data to the server
        if (sendto(clientSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
            perror("Failed to send message");
            exit(EXIT_FAILURE);
        }

        printf("Sent message to server: %s\n", buffer);

        // Receive data from the server
        if ((len = recvfrom(clientSocket, buffer, MAX_BUFFER_SIZE, 0, NULL, NULL)) < 0) {
            perror("Failed to receive message");
            exit(EXIT_FAILURE);
        }

        buffer[len] = '\0';
        printf("Received message from server: %s\n", buffer);
    }

    // Close the client socket
    close(clientSocket);

    return 0;
}
