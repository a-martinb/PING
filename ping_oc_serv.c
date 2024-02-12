#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

#define MAX_BUF_SIZE 2048 // Aumentamos el tamaño del buffer

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char message[MAX_BUF_SIZE];
    int port;

    // Solicitar al usuario ingresar el puerto del servidor
    printf("Ingrese el puerto del servidor: ");
    scanf("%d", &port);

    // Crear el socket TCP
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error al crear el socket del servidor");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    // Enlazar el socket a la dirección y puerto
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al enlazar el socket del servidor");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(server_socket, 5) < 0) {
        perror("Error al intentar escuchar en el socket");
        exit(EXIT_FAILURE);
    }

    printf("Servidor TCP en ejecución en el puerto %d\n", port);

    while (1) {
        // Aceptar la conexión entrante
        socklen_t client_addr_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("Error al aceptar la conexión del cliente");
            continue;
        }

        // Recibir datos del cliente
        memset(message, 0, sizeof(message));
        ssize_t bytes_received = recv(client_socket, message, MAX_BUF_SIZE, 0);
        if (bytes_received < 0) {
            perror("Error al recibir datos del cliente");
            close(client_socket);
            continue;
        }



        // Construir la respuesta al cliente
        snprintf(message, MAX_BUF_SIZE, "Tamaño del paquete recibido: %zd bytes, Direccion IP del cliente: %s, ICMP_SEQ=%d, TIME=%ld ms", bytes_received, inet_ntoa(client_addr.sin_addr), 0, start_time);

        // Enviar la respuesta al cliente
        ssize_t bytes_sent = send(client_socket, message, strlen(message), 0);
        if (bytes_sent < 0) {
            perror("Error al enviar la respuesta al cliente");
            continue;
        }

        

    }

    // Cerrar el socket del servidor (este código nunca se ejecutará en este bucle)
    close(server_socket);

    return 0;
}
