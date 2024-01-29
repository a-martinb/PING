#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define MAX_BUF_SIZE 2048 // Aumentamos el tamaño del buffer

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    char message[MAX_BUF_SIZE];
    int port;

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
        recvfrom(server_socket, message, MAX_BUF_SIZE, 0, (struct sockaddr*)&client_addr, &client_addr_len);

        // Obtener el tiempo actual
        struct timeval tv;
        gettimeofday(&tv, NULL);
        long start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;

        // Construir la respuesta al cliente
        snprintf(message, MAX_BUF_SIZE, "Tamaño del paquete recibido: %lu bytes, Direccion IP del cliente: %s, ICMP_SEQ=%s, TIME=%ld ms", strlen(message), inet_ntoa(client_addr.sin_addr), message, start_time);

        // Enviar la respuesta al cliente
        sendto(server_socket, message, strlen(message), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
    }

    close(server_socket);
    return 0;
}
