#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 12345 // Mismo puerto que el servidor
#define BUFFER_SIZE 1024

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <mensaje>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd, recv_len;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    // Crear socket TCP
    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        handle_error("Error al crear el socket");
    }

    // Configurar dirección del servidor
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        handle_error("Dirección IP no válida");
    }

    // Conectar al servidor
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        handle_error("Error al conectar al servidor");
    }

    printf("Conexión establecida con el servidor en %s:%d\n", "127.0.0.1", PORT);

    // Enviar datos al servidor
    if (send(sockfd, argv[1], strlen(argv[1]), 0) == -1) {
        handle_error("Error al enviar datos al servidor");
    }

    printf("Datos enviados al servidor: %s\n", argv[1]);

    // Recibir respuesta del servidor
    if ((recv_len = recv(sockfd, buffer, BUFFER_SIZE, 0)) == -1) {
        handle_error("Error al recibir respuesta del servidor");
    }

    buffer[recv_len] = '\0'; // Agregar terminador de cadena
    printf("Respuesta recibida del servidor: %s\n", buffer);

    // Cerrar socket
    close(sockfd);

    return 0;
}

