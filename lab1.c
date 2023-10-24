#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define LOCAL_PORT 4563
#define MAX_BUFFER_SIZE 1024

int udp_socket;
struct sockaddr_in local_addr, remote_addr;

void *read_from_udp(void *arg) {
    char buffer[MAX_BUFFER_SIZE];
    socklen_t addr_len = sizeof(remote_addr);

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = recvfrom(udp_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&remote_addr, &addr_len);
        if (bytes_received > 0) {
            write(STDOUT_FILENO, buffer, bytes_received);
        }
    }
}

void *write_to_udp(void *arg) {
    char buffer[MAX_BUFFER_SIZE];

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (bytes_read > 0) {
            sendto(udp_socket, buffer, bytes_read, 0, (struct sockaddr *)&remote_addr, sizeof(remote_addr));
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <remote_host_ip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Parse remote host IP address from command-line argument
    if (inet_pton(AF_INET, argv[1], &remote_addr.sin_addr) != 1) {
        perror("Invalid remote host IP address");
        exit(EXIT_FAILURE);
    }

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(LOCAL_PORT);

    // Create UDP socket
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure local address structure and bind the socket
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(LOCAL_PORT);
    local_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(udp_socket, (struct sockaddr *)&local_addr, sizeof(local_addr)) == -1) {
        perror("Bind failed");
        close(udp_socket);
        exit(EXIT_FAILURE);
    }

    pthread_t read_thread, write_thread;

    // Create threads for reading and writing
    if (pthread_create(&read_thread, NULL, read_from_udp, NULL) != 0) {
        perror("Read thread creation failed");
        close(udp_socket);
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&write_thread, NULL, write_to_udp, NULL) != 0) {
        perror("Write thread creation failed");
        close(udp_socket);
        exit(EXIT_FAILURE);
    }

    // Wait for threads to finish
    pthread_join(read_thread, NULL);
    pthread_join(write_thread, NULL);

    // Close the socket
    close(udp_socket);

    return 0;
}
