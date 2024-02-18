#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>

#define MAX_BUF_SIZE 2048 // Aumentamos el tamaño del buffer

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    char message[MAX_BUF_SIZE];
    int port;
    clock_t start, end;
    double elapsed_time;


    // Solicitar al usuario ingresar el puerto del servidor
    printf("Ingrese el puerto del servidor: ");
    scanf("%d", &port);

    // Crear el socket UDP
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Enlazar el socket a la dirección y puerto
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al enlazar el socket");
        exit(EXIT_FAILURE);
    }

    printf("Servidor UDP en ejecución en el puerto %d\n", port);

    while (1) {
        // Recibir datos del cliente
        socklen_t client_addr_len = sizeof(client_addr);
        memset(message, 0, sizeof(message));
        ssize_t bytes_received = recvfrom(server_socket, message, MAX_BUF_SIZE, 0, (struct sockaddr*)&client_addr, &client_addr_len);
        if (bytes_received < 0) {
            perror("Error al recibir datos del cliente");
            continue;
        }

        start = clock();

        end = clock();
        elapsed_time = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;

        // Construir la respuesta al cliente
        snprintf(message, MAX_BUF_SIZE, "Tamaño del paquete recibido: %zd bytes, Direccion IP del cliente: %s, ICMP_SEQ=%zd, TIME=%.2f ms", bytes_received, inet_ntoa(client_addr.sin_addr), bytes_received, elapsed_time);
        //sendto(sockfd, (const char *)&elapsed_time, sizeof(elapsed_time), 0, (const struct sockaddr *)&client_addr, client_len);
        // Enviar la respuesta al cliente
        ssize_t bytes_sent = sendto(server_socket, message, strlen(message), 0, (struct sockaddr*)&client_addr, sizeof(client_addr), (const char *)&elapsed_time, sizeof(elapsed_time),0);
        if (bytes_sent < 0) {
            perror("Error al enviar la respuesta al cliente");
            continue;
        }
    }

    close(server_socket);
    return 0;
}
