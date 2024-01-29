#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>

#define BUFFER_SIZE 1024

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <hostname/IP> <puerto>\n", argv[0]);
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
    serv_addr.sin_port = htons(atoi(argv[2]));

    struct hostent *server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "Error: No se pudo resolver el nombre del host\n");
        exit(EXIT_FAILURE);
    }
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // Conectar al servidor
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        handle_error("Error al conectar al servidor");
    }

    printf("Conexión establecida con el servidor %s:%s\n", argv[1], argv[2]);

    // Enviar datos al servidor
    char *data = "Datos enviados desde el cliente";
    if (send(sockfd, data, strlen(data), 0) == -1) {
        handle_error("Error al enviar datos al servidor");
    }

    printf("Datos enviados al servidor\n");

    // Recibir respuesta del servidor
    if ((recv_len = recv(sockfd, buffer, BUFFER_SIZE, 0)) == -1) {
        handle_error("Error al recibir respuesta del servidor");
    }

    printf("Respuesta recibida del servidor: %s\n", buffer);

    // Cerrar socket
    close(sockfd);

    return 0;
}
